#include "CalcuNeed.hpp"

float uint_to_float(int _x_int, float _x_min, float _x_max, int _bits)
{
    float span = _x_max - _x_min;
    float offset = _x_min;
    return ((float)_x_int) * span / ((float)((1 << _bits) - 1)) + offset;
}

uint16_t float_to_uint(float _x_int, float _x_min, float _x_max, int _bits)
{
    /// Converts a float to an unsigned int, given range and number of _bits ///
    float span = _x_max - _x_min;
    float offset = _x_min;

    return (uint16_t)((_x_int - offset) * ((float)((1 << _bits) - 1)) / span);
}

float get_minor_arc(float ang1, float ang2, float angle_range)
{
    return (fmodf(((ang1) - (ang2) + (angle_range) * 1.5f), (angle_range)) -
            (angle_range) / 2.f);
}