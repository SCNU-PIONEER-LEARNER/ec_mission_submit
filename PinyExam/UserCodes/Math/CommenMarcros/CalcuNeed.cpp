#include "CalcuNeed.hpp"

float get_minor_arc(float ang1, float ang2, float angle_range)
{
    return (fmodf(((ang1) - (ang2) + (angle_range) * 1.5f), (angle_range)) -
            (angle_range) / 2.f);
}

float sCurve(float _vMax, float _cnt, float _tAccCnt)
{
    float cntcnt;
    if (_cnt < 0.0f) {
        _cnt = -_cnt;
        _vMax = -_vMax;
    }
    cntcnt = _cnt / _tAccCnt;
    if (_cnt < _tAccCnt / 2.0f) {
        return 2.0f * _vMax * (cntcnt * cntcnt);
    } else if (_cnt < _tAccCnt) {
        cntcnt = cntcnt - 1.0f;
        return _vMax * (1.0f - 2.0f * (cntcnt * cntcnt));
    } else
        return _vMax;
}

float clampArc(float _angle, float _startAngle, float _endAngle,
                      float _range)
{
    auto normalize = [_range](float _a) {
        _a = std::fmodf(_a, _range);
        return (_a < 0 ? _a + _range : _a);
    };

    float a = normalize(_angle);
    float start = normalize(_startAngle);
    float end = normalize(_endAngle);

    if (start <= end) {
        // minor arc
        if (a >= start && a <= end)
            return _angle;
        float distToStart = std::fmin(a - start, start + _range - a);
        float distToEnd = std::fmin(end - a, a + _range - end);
        return distToStart < distToEnd ? _startAngle : _endAngle;
    } else {
        // major arc
        if (a >= start || a <= end)
            return _angle;
        float distToStart = std::fmin(start - a, a + _range - start);
        float distToEnd = std::fmin(a - end, end + _range - a);
        return distToStart < distToEnd ? _startAngle : _endAngle;
    }
}

float rangeMap(float _scale, float _min, float _max)
{
    const float period = _max - _min;
    if (period <= 0) {
        return _min;
    }
    float offset = std::fmod(_scale - _min, period);
    if (offset < 0) {
        offset += period;
    }
    float rslt = offset + _min;
    return rslt;
}
uint16_t float2uint(float _xInt, float _xMin, float _xMax,
                                  int _bits)
{
    /// Converts a float to an unsigned int, given range and number of _bits ///
    float span = _xMax - _xMin;
    float offset = _xMin;
    uint16_t rawSet =
            (uint16_t)((_xInt - offset) * ((float)((1 << _bits) - 1)) / span);
    return rawSet;
}