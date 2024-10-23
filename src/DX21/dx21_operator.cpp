#include "fm_operator.h"

std::istream& operator>>(std::istream& input, fm_operator& op) {
    uint8_t ch;
    input >> op.attack_rate
            >> op.decay1_rate
            >> op.decay2_rate
            >> op.release_rate
            >> op.decay1_level
            >> op.scaling_level
            >> ch;
    op.key_velocity = ch & 0x7;
    op.eg_bias_sensitivity = (ch >> 3) & 0x7;
    op.amplitude_modulation = (ch >> 6) & 0x1;
    input >> op.output_level
            >> op.oscillator_frequency
            >> ch;
    op.scaling_rate = (ch >> 3) & 0x3;
    op.detune = ch & 0x7;

    return input;
}

std::ostream& operator<<(std::ostream& output, const fm_operator& op) {
    uint8_t ch;
    output << op.attack_rate << op.decay1_rate << op.decay2_rate << op.release_rate << op.decay1_level << op.scaling_level;
    ch = ((op.amplitude_modulation & 0x1) << 6) & ((op.eg_bias_sensitivity & 0x7) << 3) & (op.key_velocity & 0x7);
    output << ch << op.output_level << op.oscillator_frequency;
    ch = ((op.scaling_rate & 0x3) << 3) & (op.detune & 0x7);
    output << ch;

    return output;
}
