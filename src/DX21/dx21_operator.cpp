#include "dx21_operator.h"

dx21_operator::dx21_operator()
        : attack_rate(31, 0 , 31),
        decay1_rate(31, 0, 31),
        decay2_rate(31, 0, 31),
        release_rate(15, 0, 15),
        decay1_level(15, 0, 15),
        scaling_level(0),
        scaling_rate(0, 0, 3),
        eg_bias_sensitivity(0, 0, 7),
        amplitude_modulation(0, 0, 1),
        key_velocity(0, 0, 7),
        output_level(0),
        oscillator_frequency(0, 0, 63),
        detune(0, 0, 7)
{

}

void dx21_operator::writeMessage(std::vector<uint8_t>& op_data)
{
        op_data.clear();
        uint8_t ch;

        op_data.push_back(attack_rate.value());
        op_data.push_back(decay1_rate.value());
        op_data.push_back(decay2_rate.value());
        op_data.push_back(release_rate.value());
        op_data.push_back(decay1_level.value());
        op_data.push_back(scaling_level.value());
        if (packed)
        {
                ch = ((amplitude_modulation.value() & 0x1) << 6) | ((eg_bias_sensitivity.value() & 0x7) << 3) | (key_velocity.value() & 0x7);
                op_data.push_back(ch);
        }
        else
        {
                op_data.push_back(scaling_rate.value());
                op_data.push_back(eg_bias_sensitivity.value());
                op_data.push_back(amplitude_modulation.value());
                op_data.push_back(key_velocity.value());
        }
        op_data.push_back(output_level.value());
        op_data.push_back(oscillator_frequency.value());
        if (packed)
        {
                ch = ((scaling_rate.value() & 0x3) << 3) | (detune.value() & 0x7);
                op_data.push_back(ch);
        }
        else
        {
                op_data.push_back(detune.value());
        }
}

void dx21_operator::readMessage(std::vector<uint8_t>& message, size_t& pos)
{
        uint8_t ch, temp;

        attack_rate = message[pos++];
        decay1_rate = message[pos++];
        decay2_rate = message[pos++];
        release_rate = message[pos++];
        decay1_level = message[pos++];
        scaling_level = message[pos++];
        if (packed)
        {
                ch = message[pos++];
                temp = ch & 0x7;
                key_velocity = temp;
                temp = (ch >> 3) & 0x7;
                eg_bias_sensitivity = temp;
                temp = (ch >> 6) & 0x1;
                amplitude_modulation = temp;
        }
        else
        {
                scaling_rate = message[pos++];
                eg_bias_sensitivity = message[pos++];
                amplitude_modulation = message[pos++];
                key_velocity = message[pos++];
        }
        output_level = message[pos++];
        oscillator_frequency = message[pos++];
        if (packed)
        {
                ch = message[pos++];
                temp = (ch >> 3) & 0x3;
                scaling_rate = temp;
                temp = ch & 0x7;
                detune = temp;
        }
        else
        {
                detune = message[pos++];;
        }
}
