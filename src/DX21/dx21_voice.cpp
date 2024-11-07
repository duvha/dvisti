// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include "dx21_voice.h"

dx21_voice::dx21_voice()
{

}

dx21_voice::dx21_voice(const dx21_voice& other)
{

}

dx21_voice::~dx21_voice()
{

}

void dx21_voice::writeMessage(std::vector<uint8_t>& voice_data)
{
    voice_data.clear();
    uint8_t ch;

    std::vector<uint8_t> op_data;
    for(size_t i = 0; i < op_order.size(); ++i)
    {
        dx21_operators[op_order[i]].packed = packed;
        dx21_operators[op_order[i]].writeMessage(op_data);
        for (std::vector<uint8_t>::iterator it = op_data.begin(); it < op_data.end(); ++it) voice_data.push_back(*it);
    }
    if (packed)
    {
        ch = ((lfo_sync & 0x1) << 6) | ((feedback_level & 0x7) << 3) | (algorithm & 0x7);
        voice_data.push_back(ch);
    }
    else
    {
        voice_data.push_back(algorithm);
        voice_data.push_back(feedback_level);
    }
    voice_data.push_back(lfo_speed);
    voice_data.push_back(lfo_delay);
    voice_data.push_back(lfo_pitch_modulation_depth);
    voice_data.push_back(lfo_amplitude_modulation_depth);
    if (packed)
    {
        ch = ((pitch_modulation_sensitivity & 0x7) << 4) | ((amplitude_modulation_sensitivity & 0x3) << 2) | (lfo_wave & 0x3);
        voice_data.push_back(ch);
    }
    else
    {
        voice_data.push_back(lfo_sync);
        voice_data.push_back(lfo_wave);
        voice_data.push_back(pitch_modulation_sensitivity);
        voice_data.push_back(amplitude_modulation_sensitivity);
    }
    voice_data.push_back(transpose);
    if (packed)
    {
        voice_data.push_back(pitch_bend_range);
        ch = ((chorus_switch & 0x1) << 4) | ((play_mode & 0x1) << 3) | ((sustain_foot_switch & 0x1) << 2) | ((portamento_foot_switch & 0x1) << 1) | (portamento_mode & 0x1);
        voice_data.push_back(ch);
    }
    else
    {
        voice_data.push_back(play_mode);
        voice_data.push_back(pitch_bend_range);
        voice_data.push_back(portamento_mode);
    }
    voice_data.push_back(portamento_time);
    voice_data.push_back(foot_volume);
    if (!packed)
    {
        voice_data.push_back(sustain_foot_switch);
        voice_data.push_back(portamento_foot_switch);
        voice_data.push_back(chorus_switch);
    }
    voice_data.push_back(mw_pitch_modulation_range);
    voice_data.push_back(mw_amplitude_modulation_range);
    voice_data.push_back(bc_pitch_modulation_range);
    voice_data.push_back(bc_amplitude_modulation_range);
    voice_data.push_back(bc_pitch_bias_range);
    voice_data.push_back(bc_eg_bias_range);
    for(size_t i = 0; i < voice_name.size(); ++i)
    {
        voice_data.push_back(voice_name[i]);
    }
    voice_data.push_back(pitch_eg_rate1);
    voice_data.push_back(pitch_eg_rate2);
    voice_data.push_back(pitch_eg_rate3);
    voice_data.push_back(pitch_eg_level1);
    voice_data.push_back(pitch_eg_level2);
    voice_data.push_back(pitch_eg_level3);
    if (packed) voice_data.resize(128);
    voice_data[91] = 0x01; //???
}

void dx21_voice::readMessage(std::vector<uint8_t>& message, size_t& pos)
{
    uint8_t ch;

    for(size_t i = 0; i < op_order.size(); ++i)
    {
        dx21_operators[op_order[i]].packed = packed;
        dx21_operators[op_order[i]].readMessage(message, pos);
    }
    if (packed)
    {
        ch = message[pos++];
        lfo_sync = (ch >> 6) & 0x1;
        feedback_level = (ch >> 3) & 0x7;
        algorithm = ch & 0x7;
    }
    else
    {
        algorithm = message[pos++];
        feedback_level = message[pos++];
    }
    lfo_speed = message[pos++];
    lfo_delay = message[pos++];
    lfo_pitch_modulation_depth = message[pos++];
    lfo_amplitude_modulation_depth = message[pos++];
    if (packed)
    {
        ch = message[pos++];;
        pitch_modulation_sensitivity = (ch >> 4) & 0x7;
        amplitude_modulation_sensitivity = (ch >> 2) & 0x3;
        lfo_wave = ch & 0x3;
    }
    else
    {
        lfo_sync = message[pos++];
        lfo_wave = message[pos++];
        pitch_modulation_sensitivity = message[pos++];
        amplitude_modulation_sensitivity = message[pos++];
    }
    transpose = message[pos++];
    if (packed)
    {
        pitch_bend_range = message[pos++];
        ch = message[pos++];
        chorus_switch = (ch >> 4 ) & 0x1;
        play_mode = (ch >> 3) & 0x1;
        sustain_foot_switch = (ch >> 2) & 0x1;
        portamento_foot_switch = (ch >> 1) & 0x1;
        portamento_mode = ch & 0x1;
    }
    else
    {
        play_mode = message[pos++];
        pitch_bend_range = message[pos++];
        portamento_mode = message[pos++];
    }
    portamento_time = message[pos++];
    foot_volume = message[pos++];
    if (!packed)
    {
        sustain_foot_switch = message[pos++];
        portamento_foot_switch = message[pos++];
        chorus_switch = message[pos++];
    }
    mw_pitch_modulation_range = message[pos++];
    mw_amplitude_modulation_range = message[pos++];
    bc_pitch_modulation_range = message[pos++];
    bc_amplitude_modulation_range = message[pos++];
    bc_pitch_bias_range = message[pos++];
    bc_eg_bias_range = message[pos++];;
    for(size_t i = 0; i < voice_name.size(); ++i)
    {
        voice_name[i] = message[pos++];
    }
    pitch_eg_rate1 = message[pos++];
    pitch_eg_rate2 = message[pos++];
    pitch_eg_rate3 = message[pos++];
    pitch_eg_level1 = message[pos++];
    pitch_eg_level2 = message[pos++];
    pitch_eg_level3 = message[pos++];
    if (packed) pos += 55;
}
