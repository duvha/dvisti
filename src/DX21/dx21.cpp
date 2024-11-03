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
    uint8_t checksum;

    std::ofstream file(filename, std::ifstream::binary | std::ifstream::out);
    if (!file.is_open()) return false;

    file << 0xf0;
    file << 0x43;
    file << 0x00;
    if (packed)
    {
        file << 0x04;
        file << 0x20;
        file << 0x00;
    }
    else
    {
        file << 0x03;
        file << 0x00;
        file << 0x5d;
    }

    std::ostringstream voice_data;
    if (packed)
    {
        for (size_t i = 0; i < dx21_voices.size(); ++i)
        {
            dx21_voices[i].packed = packed;
            voice_data << dx21_voices[i];
        }
    }
    else
    {
        voice_buffer.packed = packed;
        voice_data << voice_buffer;
    }
    file << voice_data.str();
    checksum = std::accumulate(voice_data.str().begin(), voice_data.str().end(), 0);
    checksum &= 0x7f;
    file << checksum;
    file << 0xf7;

    file.close();
    return true;
}

bool dx21::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ifstream::binary | std::ifstream::in);
    if (!file.is_open()) return false;

    uint8_t ch;
    file >> ch; //0xf0
    file >> ch; //0x43
    file >> ch; //0x00
    file >> ch; //0x03 or 0x04

    if (ch == 0x04) packed = true;
    else packed = false;
    file >> ch; //0x20 or 0x00
    file >> ch; //0x00 or 0x5d

    std::vector<uint8_t> voice_data;
    if (packed)
    {
        for (size_t i = 0; i < dx21_voices.size(); ++i)
        {
            dx21_voices[i].packed = packed;
            file >> dx21_voices[i];
        }
    }
    else
    {
        voice_buffer.packed = packed;
        file >> voice_buffer;
    }

    file >> ch; //checksum
    file >> ch; //0xf7

    file.close();
    return true;
}
