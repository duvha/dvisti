// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include <fstream>
#include <string>
#include <vector>

#include "dx21.h"

bool dx21::writeFile(const std::string& filename)
{
    packed = true;
    std::ofstream file(filename, std::ifstream::binary | std::ifstream::out);
    if (!file.is_open()) return false;

    std::vector<uint8_t> message;
    writeMessage(message);
    file.write(reinterpret_cast<char*>(message.data()), message.size());
    file.close();
    return true;
}

void dx21::writeMessage(std::vector<uint8_t>& message)
{
    uint8_t checksum=0;

    message.push_back(0xf0);
    message.push_back(0x43);
    message.push_back(0x00);
    if (packed)
    {
        message.push_back(0x04);
        message.push_back(0x20);
        message.push_back(0x00);
    }
    else
    {
        message.push_back(0x03);
        message.push_back(0x00);
        message.push_back(0x5d);
    }

    std::vector<uint8_t> voice_data;
    if (packed)
    {
        for (size_t i = 0; i < dx21_voices.size(); ++i)
        {
            dx21_voices[i].packed = packed;
            dx21_voices[i].writeMessage(voice_data);
            for (std::vector<uint8_t>::iterator it = voice_data.begin(); it < voice_data.end(); ++it)
            {
                message.push_back(*it);
                checksum += *it;
            }
        }
    }
    else
    {
        voice_buffer.packed = packed;
        voice_buffer.writeMessage(voice_data);
        for (std::vector<uint8_t>::iterator it = voice_data.begin(); it < voice_data.end(); ++it)
        {
            message.push_back(*it);
            checksum += *it;
        }
    }
    checksum = ~checksum + 1;
    checksum &= 0x7f;
    message.push_back(checksum);
    message.push_back(0xf7);
}

bool dx21::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ifstream::binary | std::ifstream::in);
    if (!file.is_open()) return false;
    std::vector<uint8_t> message((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    readMessage(message);

    return true;
}

void dx21::readMessage(std::vector<uint8_t>& message)
{
    uint8_t ch;
    size_t pos=0;

    ch = message[pos++]; //0xf0

    ch = message[pos++]; //0x43
    ch = message[pos++]; //0x00
    ch = message[pos++]; //0x03 or 0x04

    if (ch == 0x04) packed = true;
    else packed = false;
    ch = message[pos++]; //0x20 or 0x00
    ch = message[pos++]; //0x00 or 0x5d

    std::vector<uint8_t> voice_data;
    if (packed)
    {
        for (size_t i = 0; i < dx21_voices.size(); ++i)
        {
            dx21_voices[i].packed = packed;
            dx21_voices[i].readMessage(message, pos);
        }
    }
    else
    {
        voice_buffer.packed = packed;
        voice_buffer.readMessage(message, pos);
    }

    ch = message[pos++]; //checksum
    ch = message[pos++]; //0xf7
}

