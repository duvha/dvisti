#ifndef DX21_OPERATOR_H
#define DX21_OPERATOR_H

#include <stdint.h>
#include <fstream>

class dx21_operator
{
public:
     friend std::ostream& operator<<(std::ostream&, const dx21_operator&);
     friend std::istream& operator>>(std::istream&, dx21_operator&);

private:
     uint8_t attack_rate;
     uint8_t decay1_rate;
     uint8_t decay2_rate;
     uint8_t release_rate;
     uint8_t decay1_level;
     uint8_t scaling_level;
     uint8_t scaling_rate;
     uint8_t eg_bias_sensitivity;
     bool amplitude_modulation;
     uint8_t key_velocity;
     uint8_t output_level;
     uint8_t oscillator_frequency;
     uint8_t detune;
};

#endif // DX21_OPERATOR_H
