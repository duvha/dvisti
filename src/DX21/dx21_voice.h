// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef DX21_VOICE_H
#define DX21_VOICE_H

#include <array>
#include <vector>
#include <cstdint>

#include "../data.h"
#include "dx21_operator.h"

/**
 * @todo write docs
 */
class dx21_voice
{
public:
    dx21_voice();
    void readMessage(std::vector<uint8_t>&, int&, bool);
    void writeMessage(std::vector<uint8_t>&, bool );

private:
    std::array<int, 4> op_order {3, 1, 2, 0};
    std::array<dx21_operator, 4> dx21_operators;

    Data algorithm;
    Data feedback_level;
    Data lfo_speed;
    Data lfo_delay;
    Data lfo_pitch_modulation_depth;
    Data lfo_amplitude_modulation_depth;
    Data lfo_sync;
    Data lfo_wave;
    Data pitch_modulation_sensitivity;
    Data amplitude_modulation_sensitivity;
    Data transpose;
    Data play_mode;
    Data pitch_bend_range;
    Data portamento_mode;
    Data portamento_time;
    Data foot_volume;
    Data sustain_foot_switch;
    Data portamento_foot_switch;
    Data chorus_switch;
    Data mw_pitch_modulation_range;
    Data mw_amplitude_modulation_range;
    Data bc_pitch_modulation_range;
    Data bc_amplitude_modulation_range;
    Data bc_pitch_bias_range;
    Data bc_eg_bias_range;
    std::array<uint8_t, 10> voice_name;
    Data pitch_eg_rate1;
    Data pitch_eg_rate2;
    Data pitch_eg_rate3;
    Data pitch_eg_level1;
    Data pitch_eg_level2;
    Data pitch_eg_level3;
};

#endif // DX21_VOICE_H
