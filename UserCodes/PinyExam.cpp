#include "BspCan.hpp"
#include "PinyExam.hpp"
#include "App.hpp"


void CanMotors::bspInit()
{
    BspCan::instance().init(&hcan1);
    BspCan::instance().init(&hcan2);
}

void CanMotors::coreInit() { App::instance()->initApp(); }

void CanMotors::init()
{
    bspInit();
    coreInit();
}

void initCanMotors() { CanMotors::instance()->init(); }
