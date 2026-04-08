#pragma once

#ifdef __cplusplus

class App {
public:
    static App *instance()
    {
        static App instance;
        return &instance;
    }
    App(const App &) = delete;
    App &operator=(const App &) = delete;

    void initApp();
    static void ctrlTask(void *_param);

private:
    App() = default;
};

#endif // __cplusplus
