#ifndef LIB_H
#define LIB_H

#include <iostream>
#include "napi.h"
#include "sharedmemory.h"

Napi::Object Init(Napi::Env env, Napi::Object exports);

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

#endif