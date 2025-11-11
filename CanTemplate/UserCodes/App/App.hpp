#pragma once

#ifdef __cplusplus
extern "C" {
#endif
void sendCanData();
void getCanData();
#ifdef __cplusplus
}

class App {
public:
  static App *instance() {
    static App instance;
    return &instance;
  }
  App(const App &) = delete;
  App &operator=(const App &) = delete;

  void initApp();

  void sendCanData();
  void getCanData();

private:
  App() = default;
};

#endif // __cplusplus
