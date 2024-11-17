// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include "dx21_voice.h"

dx21_voice::dx21_voice()
    : algorithm(0, 0, 7),
    feedback_level(0, 0, 7),
    lfo_speed(35),
    lfo_delay(0),
    lfo_pitch_modulation_depth(0),
    lfo_amplitude_modulation_depth(0),
    lfo_sync(0, 0, 1),
    lfo_wave(2, 0, 3),
    pitch_modulation_sensitivity(6),
    amplitude_modulation_sensitivity(0),
    transpose(23, 0, 48),
    play_mode(0, 0, 1),
    pitch_bend_range(4 , 0, 12),
    portamento_mode(0, 0, 1),
    portamento_time(0),
    foot_volume(40),
    sustain_foot_switch(1 , 0, 1),
    portamento_foot_switch(1, 0, 1),
    chorus_switch(0, 0, 1),
    mw_pitch_modulation_range(50),
    mw_amplitude_modulation_range(0),
    bc_pitch_modulation_range(0),
    bc_amplitude_modulation_range(0),
    bc_pitch_bias_range(50),
    bc_eg_bias_range(0),
    voice_name {'I', 'n', 'i', 't', '.', 'V', 'o', 'i', 'c', 'e'},
    pitch_eg_rate1(99),
    pitch_eg_rate2(99),
    pitch_eg_rate3(99),
    pitch_eg_level1(50),
    pitch_eg_level2(50),
    pitch_eg_level3(50)
{
    uint8_t temp = 90;
    dx21_operators[0].output_level.setValue(temp);
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
        ch = ((lfo_sync.value() & 0x1) << 6) | ((feedback_level.value() & 0x7) << 3) | (algorithm.value() & 0x7);
        voice_data.push_back(ch);
    }
    else
    {
        voice_data.push_back(algorithm.value());
        voice_data.push_back(feedback_level.value());
    }
    voice_data.push_back(lfo_speed.value());
    voice_data.push_back(lfo_delay.value());
    voice_data.push_back(lfo_pitch_modulation_depth.value());
    voice_data.push_back(lfo_amplitude_modulation_depth.value());
    if (packed)
    {
        ch = ((pitch_modulation_sensitivity.value() & 0x7) << 4) | ((amplitude_modulation_sensitivity.value() & 0x3) << 2) | (lfo_wave.value() & 0x3);
        voice_data.push_back(ch);
    }
    else
    {
        voice_data.push_back(lfo_sync.value());
        voice_data.push_back(lfo_wave.value());
        voice_data.push_back(pitch_modulation_sensitivity.value());
        voice_data.push_back(amplitude_modulation_sensitivity.value());
    }
    voice_data.push_back(transpose.value());
    if (packed)
    {
        voice_data.push_back(pitch_bend_range.value());
        ch = ((chorus_switch.value() & 0x1) << 4) | ((play_mode.value() & 0x1) << 3) | ((sustain_foot_switch.value() & 0x1) << 2) | ((portamento_foot_switch.value() & 0x1) << 1) | (portamento_mode.value() & 0x1);
        voice_data.push_back(ch);
    }
    else
    {
        voice_data.push_back(play_mode.value());
        voice_data.push_back(pitch_bend_range.value());
        voice_data.push_back(portamento_mode.value());
    }
    voice_data.push_back(portamento_time.value());
    voice_data.push_back(foot_volume.value());
    if (!packed)
    {
        voice_data.push_back(sustain_foot_switch.value());
        voice_data.push_back(portamento_foot_switch.value());
        voice_data.push_back(chorus_switch.value());
    }
    voice_data.push_back(mw_pitch_modulation_range.value());
    voice_data.push_back(mw_amplitude_modulation_range.value());
    voice_data.push_back(bc_pitch_modulation_range.value());
    voice_data.push_back(bc_amplitude_modulation_range.value());
    voice_data.push_back(bc_pitch_bias_range.value());
    voice_data.push_back(bc_eg_bias_range.value());
    for(size_t i = 0; i < voice_name.size(); ++i)
    {
        voice_data.push_back(voice_name[i]);
    }
    voice_data.push_back(pitch_eg_rate1.value());
    voice_data.push_back(pitch_eg_rate2.value());
    voice_data.push_back(pitch_eg_rate3.value());
    voice_data.push_back(pitch_eg_level1.value());
    voice_data.push_back(pitch_eg_level2.value());
    voice_data.push_back(pitch_eg_level3.value());
    if (packed) voice_data.resize(128);
    voice_data[91] = 0x01; //???
}

void dx21_voice::readMessage(std::vector<uint8_t>& message, size_t& pos)
{
    uint8_t ch;
    uint8_t temp;

    for(size_t i = 0; i < op_order.size(); ++i)
    {
        dx21_operators[op_order[i]].packed = packed;
        dx21_operators[op_order[i]].readMessage(message, pos);
    }
    if (packed)
    {
        ch = message[pos++];
        temp = (ch >> 6) & 0x1;
        lfo_sync = temp;
        temp = (ch >> 3) & 0x7;
        feedback_level = temp;
        temp = ch & 0x7;
        algorithm = temp;
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
        ch = message[pos++];
        temp = (ch >> 4) & 0x7;
        pitch_modulation_sensitivity = temp;
        temp = (ch >> 2) & 0x3;
        amplitude_modulation_sensitivity = temp;
        temp = ch & 0x3;
        lfo_wave = temp;
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
        temp = (ch >> 4 ) & 0x1;
        chorus_switch = temp;
        temp = (ch >> 3) & 0x1;
        play_mode = temp;
        temp = (ch >> 2) & 0x1;
        sustain_foot_switch = temp;
        temp = (ch >> 1) & 0x1;
        portamento_foot_switch = temp;
        temp = ch & 0x1;
        portamento_mode = temp;
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
