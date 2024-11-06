// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include <string>

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
        voice_data.insert(voice_data.end(), op_data.begin(), op_data.end());
    }
    if (packed)
    {
        ch = ((lfo_sync & 0x1) << 6) & ((feedback_level & 0x7) << 3) & (algorithm & 0x7);
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
        ch = ((pitch_modulation_sensitivity & 0x7) << 4) & ((amplitude_modulation_sensitivity & 0x3) << 2) & (lfo_wave & 0x3);
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
        ch = ((chorus_switch & 0x1) << 4) & ((play_mode & 0x1) << 3) & ((sustain_foot_switch & 0x1) << 2) & ((portamento_foot_switch & 0x1) << 1) & (portamento_mode & 0x1);
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
    if (packed)
    {
        voice_data.resize(128);
    }
}

void dx21_voice::readMessage(std::vector<uint8_t>& message)
{
/*    uint8_t ch;

    for(size_t i = 0; i < voice.op_order.size(); ++i)
    {
        if (voice.packed) voice.dx21_operators[voice.op_order[i]].packed = true;
        else voice.dx21_operators[voice.op_order[i]].packed = false;
        input >> voice.dx21_operators[voice.op_order[i]];
    }
    if (voice.packed)
    {
        input >> ch;
        voice.lfo_sync = (ch >> 6) & 0x1;
        voice.feedback_level = (ch >> 3) & 0x7;
        voice.algorithm = ch & 0x7;
    }
    else
    {
        input >> voice.algorithm
        >> voice.feedback_level;
    }
    input >> voice.lfo_speed
    >> voice.lfo_delay
    >> voice.lfo_pitch_modulation_depth
    >> voice.lfo_amplitude_modulation_depth;
    if (voice.packed)
    {
        input >> ch;
        voice.pitch_modulation_sensitivity = (ch >> 4) & 0x7;
        voice.amplitude_modulation_sensitivity = (ch >> 2) & 0x3;
        voice.lfo_wave = ch & 0x3;
    }
    else
    {
        input >> voice.lfo_sync
        >> voice.lfo_wave
        >> voice.pitch_modulation_sensitivity
        >> voice.amplitude_modulation_sensitivity;
    }
    input >> voice.transpose;
    if (voice.packed)
    {
        input >> voice.pitch_bend_range
        >> ch;
        voice.chorus_switch = (ch >> 4 ) & 0x1;
        voice.play_mode = (ch >> 3) & 0x1;
        voice.sustain_foot_switch = (ch >> 2) & 0x1;
        voice.portamento_foot_switch = (ch >> 1) & 0x1;
        voice.portamento_mode = ch & 0x1;
    }
    else
    {
        input >> voice.play_mode
        >> voice.pitch_bend_range
        >> voice.portamento_mode;
    }
    input >> voice.portamento_time
    >> voice.foot_volume;
    if (!voice.packed)
    {
        input >> voice.sustain_foot_switch
        >> voice.portamento_foot_switch
        >> voice.chorus_switch;
    }
    input >> voice.mw_pitch_modulation_range
    >> voice.mw_amplitude_modulation_range
    >> voice.bc_pitch_modulation_range
    >> voice.bc_amplitude_modulation_range
    >> voice.bc_pitch_bias_range
    >> voice.bc_eg_bias_range;
    for(size_t i = 0; i < voice.voice_name.size(); ++i)
    {
        input >> voice.voice_name[i];
    }
    input >> voice.pitch_eg_rate1
    >> voice.pitch_eg_rate2
    >> voice.pitch_eg_rate3
    >> voice.pitch_eg_level1
    >> voice.pitch_eg_level2
    >> voice.pitch_eg_level3;
    std::string str;
    input >> std::setw(55) >> str;
*/
}
