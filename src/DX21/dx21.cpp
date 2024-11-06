// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>

#include "dx21.h"

bool dx21::writeFile(const std::string& filename)
{
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
            checksum += std::accumulate(voice_data.begin(), voice_data.end(), 0);
            message.insert(message.end(), voice_data.begin(), voice_data.end());
        }
    }
    else
    {
        voice_buffer.packed = packed;
        voice_buffer.writeMessage(voice_data);
        checksum += std::accumulate(voice_data.begin(), voice_data.end(), 0);
        message.insert(message.end(), voice_data.begin(), voice_data.end());
    }
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
    ch; //0xf0
    ch; //0x43
    ch; //0x00
    ch; //0x03 or 0x04

    if (ch == 0x04) packed = true;
    else packed = false;
    ch; //0x20 or 0x00
    ch; //0x00 or 0x5d

    std::vector<uint8_t> voice_data;
    if (packed)
    {
        for (size_t i = 0; i < dx21_voices.size(); ++i)
        {
            dx21_voices[i].packed = packed;
            dx21_voices[i].readMessage(message);
        }
    }
    else
    {
        voice_buffer.packed = packed;
        voice_buffer.readMessage(message);
    }

    ch; //checksum
    ch; //0xf7
}

