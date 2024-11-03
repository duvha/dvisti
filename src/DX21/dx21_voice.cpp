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

std::ostream& operator<<(std::ostream& output, const dx21_voice& voice)
{
    uint8_t ch;

    for(size_t i = 0; i < voice.op_order.size(); ++i)
    {
        voice.dx21_operators[voice.op_order[i]].packed = voice.packed;
        output << voice.dx21_operators[voice.op_order[i]];
    }
    if (voice.packed)
    {
        ch = ((voice.lfo_sync & 0x1) << 6) & ((voice.feedback_level & 0x7) << 3) & (voice.algorithm & 0x7);
        output << ch;
    }
    else
    {
        output << voice.algorithm
                <<voice.feedback_level;
    }
    output << voice.lfo_speed
            << voice.lfo_delay
            << voice.lfo_pitch_modulation_depth
            << voice.lfo_amplitude_modulation_depth;
    if (voice.packed)
    {
        ch = ((voice.pitch_modulation_sensitivity & 0x7) << 4) & ((voice.amplitude_modulation_sensitivity & 0x3) << 2) & (voice.lfo_wave & 0x3);
        output << ch;
    }
    else
    {
        output << voice.lfo_sync
                << voice.lfo_wave
                << voice.pitch_modulation_sensitivity
                << voice.amplitude_modulation_sensitivity;
    }
    output << voice.transpose;
    if (voice.packed)
    {
        output << voice.pitch_bend_range;
        ch = ((voice.chorus_switch & 0x1) << 4) & ((voice.play_mode & 0x1) << 3) & ((voice.sustain_foot_switch & 0x1) << 2) & ((voice.portamento_foot_switch & 0x1) << 1) & (voice.portamento_mode & 0x1);
            output << ch;
    }
    else
    {
        output << voice.play_mode
                <<voice.pitch_bend_range
                << voice.portamento_mode;
    }
    output << voice.portamento_time
            << voice.foot_volume;
    if (!voice.packed)
    {
        output << voice.sustain_foot_switch
                << voice.portamento_foot_switch
                << voice.chorus_switch;
    }
    output << voice.mw_pitch_modulation_range
            << voice.mw_amplitude_modulation_range
            << voice.bc_pitch_modulation_range
            << voice.bc_amplitude_modulation_range
            << voice.bc_pitch_bias_range
            << voice.bc_eg_bias_range;
    for(size_t i = 0; i < voice.voice_name.size(); ++i)
    {
        output << voice.voice_name[i];
    }
    output << voice.pitch_eg_rate1
            << voice.pitch_eg_rate2
            << voice.pitch_eg_rate3
            << voice.pitch_eg_level1
            << voice.pitch_eg_level2
            << voice.pitch_eg_level3;
    ch = output.fill('\0');
    output << std::setw(55) << '\0';

    return output;
}

std::vector<uint8_t> dx21_voice::writeMessage()
{
    uint8_t ch;
    m_message.clear();

    std::vector<uint8_t> op_message;
    for(size_t i = 0; i < op_order.size(); ++i)
    {
        dx21_operators[op_order[i]].packed = packed;
        op_message = dx21_operators[op_order[i]].writeMessage();
        m_message.insert(m_message.end(), op_message.begin(), op_message.end());
    }
    if (packed)
    {
        ch = ((lfo_sync & 0x1) << 6) & ((feedback_level & 0x7) << 3) & (algorithm & 0x7);
        m_message.push_back(ch);
    }
    else
    {
        m_message.push_back(algorithm);
        m_message.push_back(feedback_level);
    }
    m_message.push_back(lfo_speed);
    m_message.push_back(lfo_delay);
    m_message.push_back(lfo_pitch_modulation_depth);
    m_message.push_back(lfo_amplitude_modulation_depth);
    if (packed)
    {
        ch = ((pitch_modulation_sensitivity & 0x7) << 4) & ((amplitude_modulation_sensitivity & 0x3) << 2) & (lfo_wave & 0x3);
        m_message.push_back(ch);
    }
    else
    {
        m_message.push_back(lfo_sync);
        m_message.push_back(lfo_wave);
        m_message.push_back(pitch_modulation_sensitivity);
        m_message.push_back(amplitude_modulation_sensitivity);
    }
    m_message.push_back(transpose);
    if (packed)
    {
        m_message.push_back(pitch_bend_range);
        ch = ((chorus_switch & 0x1) << 4) & ((play_mode & 0x1) << 3) & ((sustain_foot_switch & 0x1) << 2) & ((portamento_foot_switch & 0x1) << 1) & (portamento_mode & 0x1);
        m_message.push_back(ch);
    }
    else
    {
        m_message.push_back(play_mode);
        m_message.push_back(pitch_bend_range);
        m_message.push_back(portamento_mode);
    }
    m_message.push_back(portamento_time);
    m_message.push_back(foot_volume);
    if (!packed)
    {
        m_message.push_back(sustain_foot_switch);
        m_message.push_back(portamento_foot_switch);
        m_message.push_back(chorus_switch);
    }
    m_message.push_back(mw_pitch_modulation_range);
    m_message.push_back(mw_amplitude_modulation_range);
    m_message.push_back(bc_pitch_modulation_range);
    m_message.push_back(bc_amplitude_modulation_range);
    m_message.push_back(bc_pitch_bias_range);
    m_message.push_back(bc_eg_bias_range);
    for(size_t i = 0; i < voice_name.size(); ++i)
    {
        m_message.push_back(voice_name[i]);
    }
    m_message.push_back(pitch_eg_rate1);
    m_message.push_back(pitch_eg_rate2);
    m_message.push_back(pitch_eg_rate3);
    m_message.push_back(pitch_eg_level1);
    m_message.push_back(pitch_eg_level2);
    m_message.push_back(pitch_eg_level3);
    //ch = output.fill('\0');
    //output << std::setw(55) << '\0';

    return m_message;
}

std::istream& operator>>(std::istream& input, dx21_voice& voice)
{
    uint8_t ch;

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

    return input;
}
