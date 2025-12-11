#pragma once

#include "stm32f4xx_hal.h"

class Dma {
public:
    /**
     * @brief dma ram auto alloc 
     */
    void *ram_alloc(size_t size);

    /**
     * @brief dma ram free 
     */
    void ram_free(void *_ptr);

    static Dma &instance()
    {
        static Dma instance;
        return instance;
    }

protected:
    Dma(const Dma &) = delete;
    Dma &operator=(const Dma &) = delete;
    Dma() = default;
};
