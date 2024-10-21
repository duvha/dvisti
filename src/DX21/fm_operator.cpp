#include "fm_operator.h"

std::istream& operator>>(std::istream& input, fm_operator& op) {
    input >> op.attack_rate
            >> op.decay1_rate
            >> op.decay2_rate
            >> op.release_rate
            >> op.decay1_level
            >> op.scaling_level
            >> op.scaling_rate
            >> op.eg_bias_sensitivity
            >> op.amplitude_modulation
            >> op.key_velocity
            >> op.output_level
            >> op.oscillator_frequency
            >> op.detune;

    return input;
}


std::ostream& operator<<(std::ostream& output, const fm_operator& op) {
    output << op.attack_rate
            << op.decay1_rate
            << op.decay2_rate
            << op.release_rate
            << op.decay1_level
            << op.scaling_level
            << op.scaling_rate
            << op.eg_bias_sensitivity
            << op.amplitude_modulation
            << op.key_velocity
            << op.output_level
            << op.oscillator_frequency
            << op.detune;

    return output;
}
