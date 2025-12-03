#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "LED.hpp"
void initCanMotors();
#ifdef __cplusplus
}

class CanMotors {
public:
    static CanMotors *instance()
    {
        static CanMotors instance;
        return &instance;
    }

    CanMotors(const CanMotors &) = delete;
    CanMotors &operator=(const CanMotors &) = delete;

    void bspInit();
    void coreInit();

    void init();

private:
    CanMotors() = default;
};

#endif
