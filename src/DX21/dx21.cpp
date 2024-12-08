// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "dx21.h"

dx21::dx21()
{
    midi_in = new RtMidiIn();
    midi_in->openPort(0);
    midi_in->ignoreTypes(false, true, true);

    midi_out = new RtMidiOut();
}

dx21::~dx21()
{
    delete midi_out;
    delete midi_in;
}

bool dx21::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ifstream::binary | std::ifstream::in);
    if (!file.is_open()) return false;
    file.unsetf(std::ios::skipws);
    m_message.clear();
    m_message.insert(m_message.begin(), std::istream_iterator<unsigned char>(file), std::istream_iterator<unsigned char>());
    file.close();

    readMessage();

    return true;
}

void dx21::getMessage()
{
    m_message.clear();
    midi_in->getMessage(&m_message);

    readMessage();
}

void dx21::readMessage()
{
    uint8_t ch;
    int pos=0;
    bool packed;

    if (m_message.empty()) return;

    ch = m_message[pos++]; //0xf0
    if (ch != 0xf0) return; // not a sysex file

    ch = m_message[pos++]; //0x43
    if (ch != 0x43) return; // not a Yamaha file

    ch = m_message[pos++]; //0x00
    switch (ch & 0xf0)
    {
        case 0x00: // single/bulk voice receive
            ch = m_message[pos++]; //0x03 or 0x04
            if (ch == 0x04) packed = true; //bulk voices
            else packed = false;
            ch = m_message[pos++]; //0x20 or 0x00
            ch = m_message[pos++]; //0x00 or 0x5d

            if (packed)
            {
                for (int i = 0; i < dx21_voices.size(); ++i)
                {
                    dx21_voices[i].readMessage(m_message, pos, packed);
                }
            }
            else
            {
                voice_buffer.readMessage(m_message, pos, packed);
                m_parameters.clear();
                //m_parameters.resize(93);
                std::copy(m_message.begin()+6, m_message.begin()+6+93, std::back_inserter(m_parameters));
            }

            ch = m_message[pos++]; //checksum
            break;

        case 0x10: // parameter change
            ch = m_message[pos++];
            if (ch != 0x12) return; // not a parameter change message

            uint8_t parameter = m_message[pos++];
            uint8_t data = m_message[pos++];
            m_parameters[parameter] = data;
            int i=0;
            voice_buffer.readMessage(m_parameters, i, false);
            break;
    }

    ch = m_message[pos++]; //0xf7
}

bool dx21::writeFile(const std::string& filename, int message)
{
    std::ofstream file(filename, std::ifstream::binary | std::ifstream::out);
    if (!file.is_open()) return false;

    writeMessage(message);
    file.write(reinterpret_cast<char*>(m_message.data()), m_message.size());
    file.close();

    return true;
}

void dx21::sendMessage(int message)
{
    writeMessage(message);

    midi_out->sendMessage(m_message.data(), m_message.size());
}

void dx21::sendSingle()
{
    sendMessage(out_message::m_outSingle);
}

void dx21::sendBulk()
{
    sendMessage(out_message::m_outBulk);
}

void dx21::requestSingle()
{
    sendMessage(out_message::m_requestSingle);
}

void dx21::requestBulk()
{
    sendMessage(out_message::m_requestBulk);
}

void dx21::writeMessage(int message)
{
    std::vector<uint8_t> voice_data;
    uint8_t checksum=0;

    m_message.clear();
    m_message.push_back(0xf0);
    m_message.push_back(0x43);
    switch (message)
    {
        case out_message::m_outSingle:
        case out_message::m_outBulk:
            bool packed;
            if (message == m_outSingle) packed = false;
            else packed = true;
            m_message.push_back(0x00);
            if (packed)
            {
                m_message.push_back(0x04);
                m_message.push_back(0x20);
                m_message.push_back(0x00);
            }
            else
            {
                m_message.push_back(0x03);
                m_message.push_back(0x00);
                m_message.push_back(0x5d);
            }

            if (packed)
            {
                for (size_t i = 0; i < dx21_voices.size(); ++i)
                {
                    dx21_voices[i].writeMessage(voice_data, packed);
                    for (std::vector<uint8_t>::iterator it = voice_data.begin(); it < voice_data.end(); ++it)
                    {
                        m_message.push_back(*it);
                        checksum += *it;
                    }
                }
            }
            else
            {
                voice_buffer.writeMessage(voice_data, packed);
                for (std::vector<uint8_t>::iterator it = voice_data.begin(); it < voice_data.end(); ++it)
                {
                    m_message.push_back(*it);
                    checksum += *it;
                }
            }
            checksum = (~checksum + 1) & 0x7f;
            m_message.push_back(checksum);

            break;

        case out_message::m_requestSingle:
            m_message.push_back(0x20);
            m_message.push_back(0x03);

            break;

        case out_message::m_requestBulk:
            m_message.push_back(0x20);
            m_message.push_back(0x04);

            break;
    }
    m_message.push_back(0xf7);
}
