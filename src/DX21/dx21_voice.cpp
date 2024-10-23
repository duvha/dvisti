// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include "fm_voice.h"

fm_voice::fm_voice()
{

}

fm_voice::fm_voice(const fm_voice& other)
{

}

fm_voice::~fm_voice()
{

}

std::ostream& operator<<(std::ostream& output, const fm_voice& voice)
{
    uint8_t ch;

    for(size_t i = 0; i < voice.op_order.size(); ++i)
    {
        output << voice.fm_operators[voice.op_order[i]];
    }
    output << voice.algorithm
            << voice.feedback_level
            << voice.lfo_speed
            << voice.lfo_delay
            << voice.lfo_pitch_modulation_depth
            << voice.lfo_amplitude_modulation_depth
            << voice.lfo_sync
            << voice.lfo_wave
            << voice.pitch_modulation_sensitivity
            << voice.amplitude_modulation_sensitivity
            << voice.transpose
            << voice.play_mode
            << voice.pitch_bend_range
            << voice.portamento_mode
            << voice.portamento_time
            << voice.foot_volume
            << voice.sustain_foot_switch
            << voice.portamento_foot_switch
            << voice.chorus_switch
            << voice.mw_pitch_modulation_range
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

    return output;
}

std::istream& operator>>(std::istream& input, fm_voice& voice)
{
    uint8_t ch;

    for(size_t i = 0; i < voice.op_order.size(); ++i)
    {
        input >> voice.fm_operators[voice.op_order[i]];
    }
    input >> voice.algorithm
        >> voice.feedback_level
        >> voice.lfo_speed
        >> voice.lfo_delay
        >> voice.lfo_pitch_modulation_depth
        >> voice.lfo_amplitude_modulation_depth
        >> voice.lfo_sync
        >> voice.lfo_wave
        >> voice.pitch_modulation_sensitivity
        >> voice.amplitude_modulation_sensitivity
        >> voice.transpose
        >> voice.play_mode
        >> voice.pitch_bend_range
        >> voice.portamento_mode
        >> voice.portamento_time
        >> voice.foot_volume
        >> voice.sustain_foot_switch
        >> voice.portamento_foot_switch
        >> voice.chorus_switch
        >> voice.mw_pitch_modulation_range
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

    return input;
}
