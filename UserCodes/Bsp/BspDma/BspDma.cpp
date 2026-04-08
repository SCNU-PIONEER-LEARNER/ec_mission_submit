#include "BspDma.hpp"
#include <cstdlib>


void *Dma::ram_alloc(size_t _size)
{
    constexpr size_t alignment = 4;
    _size = (_size + alignment - 1) & ~(alignment - 1); // 统一处理对齐

    void *ptr = aligned_alloc(4, _size); // 分配对齐内存
    return ptr;
}

void Dma::ram_free(void *_ptr) { free(_ptr); }
