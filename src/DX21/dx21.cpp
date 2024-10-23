// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include "dx21.h"

int dx21::write()
{
    for (size_t i = 0; i < fm_voices.size(); ++i)
    {
        ss << fm_voices[i];
    }

    return 0;
}

int dx21::read()
{
    for (size_t i = 0; i < fm_voices.size(); ++i)
    {
        ss >> fm_voices[i];
    }

    return 0;
}
