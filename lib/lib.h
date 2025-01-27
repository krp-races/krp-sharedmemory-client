#ifndef LIB_H
#define LIB_H

#include <iostream>
#include "napi.h"
#include "sharedmemory.h"

Napi::Value Connect(const Napi::CallbackInfo &info);
Napi::Value Disconnect(const Napi::CallbackInfo &info);
Napi::Value IsConnected(const Napi::CallbackInfo &info);
Napi::Value Read(const Napi::CallbackInfo &info);
Napi::Value RequestSpectateVehicle(const Napi::CallbackInfo &info);
Napi::Value RequestCamera(const Napi::CallbackInfo &info);

Napi::Object Init(Napi::Env env, Napi::Object exports);
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

#endif