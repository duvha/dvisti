#include <vector>

#include "dx21_operator.h"

std::ostream& operator<<(std::ostream& output, const dx21_operator& op)
{
        uint8_t ch;
        output << op.attack_rate
                << op.decay1_rate
                << op.decay2_rate
                << op.release_rate
                << op.decay1_level
                << op.scaling_level;
        if (op.packed)
        {
                ch = ((op.amplitude_modulation & 0x1) << 6) & ((op.eg_bias_sensitivity & 0x7) << 3) & (op.key_velocity & 0x7);
                output << ch;
        }
        else
        {
                output << op.scaling_rate
                        << op.eg_bias_sensitivity
                        << op.amplitude_modulation
                        << op.key_velocity;
        }
        output << op.output_level
                << op.oscillator_frequency;
        if (op.packed)
        {
                ch = ((op.scaling_rate & 0x3) << 3) & (op.detune & 0x7);
                output << ch;
        }
        else
        {
                output << op.detune;
        }

        return output;
}

std::vector<uint8_t> dx21_operator::writeMessage()
{
        std::vector<uint8_t> message;
        uint8_t ch;

        message.push_back(attack_rate);
        message.push_back(decay1_rate);
        message.push_back(decay2_rate);
        message.push_back(release_rate);
        message.push_back(decay1_level);
        message.push_back(scaling_level);
        if (packed)
        {
                ch = ((amplitude_modulation & 0x1) << 6) & ((eg_bias_sensitivity & 0x7) << 3) & (key_velocity & 0x7);
                message.push_back(ch);
        }
        else
        {
                message.push_back(scaling_rate);
                message.push_back(eg_bias_sensitivity);
                message.push_back(amplitude_modulation);
                message.push_back(key_velocity);
        }
        message.push_back(output_level);
        message.push_back(oscillator_frequency);
        if (packed)
        {
                ch = ((scaling_rate & 0x3) << 3) & (detune & 0x7);
                message.push_back(ch);
        }
        else
        {
                message.push_back(detune);
        }

        return message;
}

std::istream& operator>>(std::istream& input, dx21_operator& op)
{
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

    return input;
}
