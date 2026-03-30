#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "LED.hpp"
void initCanTemplate();
#ifdef __cplusplus
}

class CanTemplate {
public:
  static CanTemplate *instance() {
    static CanTemplate instance;
    return &instance;
  }

  CanTemplate(const CanTemplate &) = delete;
  CanTemplate &operator=(const CanTemplate &) = delete;

  void bspInit();
  void coreInit();

  void init();

private:
  CanTemplate() = default;
};

#endif
