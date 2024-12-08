// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef DX21_H
#define DX21_H

#include <array>
#include <vector>
#include <string>
#include <cstdint>

#include "dx21_voice.h"
#include "rtmidi/RtMidi.h"

/**
 * @todo write docs
 */
class dx21
{
public:
    dx21();
    ~dx21();

    //mutable bool packed;

    bool writeFile(const std::string& , int );
    void writeMessage(int );
    bool readFile(const std::string& );
    void readMessage();
    void sendMessage(int );
    void getMessage();
    void sendSingle();
    void sendBulk();
    void requestSingle();
    void requestBulk();

private:
    enum out_message {m_outSingle, m_outBulk, m_requestSingle, m_requestBulk};
    std::array<float, 64> frequency_ratios = { 0.50,  0.71,  0.78,  0.87,  1.00,  1.41,
                                               1.57,  1.73,  2.00,  2.82,  3.00,  3.14,
                                               3.46,  4.00,  4.24,  4.71,  5.00,  5.19,
                                               5.65,  6.00,  6.28,  6.92,  7.00,  7.07,
                                               7.85,  8.00,  8.48,  8.65,  9.00,  9.42,
                                               9.89, 10.00, 10.38, 10.99, 11.00, 11.30,
                                              12.00, 12.11, 12.56, 12.72, 13.00, 13.84,
                                              14.00, 14.10, 14.13, 15.00, 15.55, 15.57,
                                              15.70, 16.96, 17.27, 17.30, 18.37, 18.84,
                                              19.03, 19.78, 20.41, 20.76, 21.20, 21.98,
                                              22.49, 23.55, 24.22, 25.95 };
    std::array<dx21_voice, 32> dx21_voices;
    dx21_voice voice_buffer;
    std::vector<uint8_t> m_message;
    std::vector<uint8_t> m_parameters;
    RtMidiIn* midi_in;
    RtMidiOut* midi_out;
};

#endif // DX21_H
