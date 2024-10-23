// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef DX21_VOICE_H
#define DX21_VOICE_H

#include <array>
#include <stdint.h>

#include "dx21_operator.h"

/**
 * @todo write docs
 */
class dx21_voice
{
public:
    /**
     * Default constructor
     */
    dx21_voice();

    /**
     * Copy constructor
     *
     * @param other TODO
     */
    dx21_voice(const dx21_voice& other);

    /**
     * Destructor
     */
    ~dx21_voice();

    friend std::ostream& operator<<(std::ostream&, const dx21_voice&);
    friend std::istream& operator>>(std::istream&, dx21_voice&);


private:
    std::array<int, 4> op_order {4, 2, 3, 1};
    std::array<dx21_operator, 4> dx21_operators;
    uint8_t algorithm;
    uint8_t feedback_level;
    uint8_t lfo_speed;
    uint8_t lfo_delay;
    uint8_t lfo_pitch_modulation_depth;
    uint8_t lfo_amplitude_modulation_depth;
    uint8_t lfo_sync;
    uint8_t lfo_wave;
    uint8_t pitch_modulation_sensitivity;
    uint8_t amplitude_modulation_sensitivity;
    uint8_t transpose;
    uint8_t play_mode;
    uint8_t pitch_bend_range;
    uint8_t portamento_mode;
    uint8_t portamento_time;
    uint8_t foot_volume;
    bool sustain_foot_switch;
    bool portamento_foot_switch;
    bool chorus_switch;
    uint8_t mw_pitch_modulation_range;
    uint8_t mw_amplitude_modulation_range;
    uint8_t bc_pitch_modulation_range;
    uint8_t bc_amplitude_modulation_range;
    uint8_t bc_pitch_bias_range;
    uint8_t bc_eg_bias_range;
    std::array<uint8_t, 10> voice_name;
    uint8_t pitch_eg_rate1;
    uint8_t pitch_eg_rate2;
    uint8_t pitch_eg_rate3;
    uint8_t pitch_eg_level1;
    uint8_t pitch_eg_level2;
    uint8_t pitch_eg_level3;
};

#endif // DX21_VOICE_H
