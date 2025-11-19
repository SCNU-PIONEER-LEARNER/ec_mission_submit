#include "CanTemplate.hpp"
#include "App.hpp"
#include "BspCan.hpp"
#include "can.h"

void CanTemplate::bspInit() { BspCan::instance().init(&hcan1); }

void CanTemplate::coreInit() { App::instance()->initApp(); }

void CanTemplate::init() {
  bspInit();
  coreInit();
}

void initCanTemplate() { CanTemplate::instance()->init(); }
