#include "dx21_operator.h"

void dx21_operator::writeMessage(std::vector<uint8_t>& op_data)
{
        op_data.clear();
        uint8_t ch;

        op_data.push_back(attack_rate);
        op_data.push_back(decay1_rate);
        op_data.push_back(decay2_rate);
        op_data.push_back(release_rate);
        op_data.push_back(decay1_level);
        op_data.push_back(scaling_level);
        if (packed)
        {
                ch = ((amplitude_modulation & 0x1) << 6) & ((eg_bias_sensitivity & 0x7) << 3) & (key_velocity & 0x7);
                op_data.push_back(ch);
        }
        else
        {
                op_data.push_back(scaling_rate);
                op_data.push_back(eg_bias_sensitivity);
                op_data.push_back(amplitude_modulation);
                op_data.push_back(key_velocity);
        }
        op_data.push_back(output_level);
        op_data.push_back(oscillator_frequency);
        if (packed)
        {
                ch = ((scaling_rate & 0x3) << 3) & (detune & 0x7);
                op_data.push_back(ch);
        }
        else
        {
                op_data.push_back(detune);
        }
}

void dx21_operator::readMessage(std::vector<uint8_t>& message)
{
/*
        uint8_t ch;

        input >> op.attack_rate
        >> op.decay1_rate
        >> op.decay2_rate
        >> op.release_rate
        >> op.decay1_level
        >> op.scaling_level;
        if (op.packed)
        {
                input >> ch;
                op.key_velocity = ch & 0x7;
                op.eg_bias_sensitivity = (ch >> 3) & 0x7;
                op.amplitude_modulation = (ch >> 6) & 0x1;
        }
        else
        {
                input >> op.scaling_rate
                >> op.eg_bias_sensitivity
                >> op.amplitude_modulation
                >> op.key_velocity;
        }
        input >> op.output_level
        >> op.oscillator_frequency;
        if (op.packed)
        {
                input >> ch;
                op.scaling_rate = (ch >> 3) & 0x3;
                op.detune = ch & 0x7;
        }
        else
        {
                input >> op.detune;
        }
*/
}
