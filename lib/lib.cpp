#include "lib.h"
#include "memory/memory.cpp"

Memory<SSharedMemory_t> mem(SHARED_MEMORY_NAME);

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    return exports;
}