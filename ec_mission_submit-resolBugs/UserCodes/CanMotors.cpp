#include "BspCan.hpp"
#include "CanMotors.hpp"
#include "App.hpp"
#include "can.h"

void CanMotors::bspInit()
{
    BspCan::instance().init(&hcan2);
}

void CanMotors::coreInit() { App::instance()->initApp(); }

void CanMotors::init()
{
    bspInit();
    coreInit();
}

void initCanMotors() { CanMotors::instance()->init(); }
