#ifndef DX21_OPERATOR_H
#define DX21_OPERATOR_H

#include <cstdint>
#include <vector>

#include "../data.h"

class dx21_operator
{
public:
     dx21_operator();
     void writeMessage(std::vector<uint8_t>& );
     void readMessage(std::vector<uint8_t>&, size_t& );
     mutable bool packed;

     Data attack_rate;
     Data decay1_rate;
     Data decay2_rate;
     Data release_rate;
     Data decay1_level;
     Data scaling_level;
     Data scaling_rate;
     Data eg_bias_sensitivity;
     Data amplitude_modulation;
     Data key_velocity;
     Data output_level;
     Data oscillator_frequency;
     Data detune;
};

#endif // DX21_OPERATOR_H
