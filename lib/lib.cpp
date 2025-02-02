#include "lib.h"
#include "memory/memory.cpp"

bool connected = false;
Memory<SSharedMemory_t> mem(SHARED_MEMORY_NAME);

Napi::Value Connect(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (connected)
        return env.Undefined();

    mem.open();

    // Check if game closed
    if (mem.get()->gameState == EGameState::CLOSED)
    {
        mem.close();
        return env.Undefined();
    }

    connected = true;
    return env.Undefined();
}

Napi::Value Disconnect(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!connected)
        return env.Undefined();

    mem.close();

    connected = false;
    return env.Undefined();
}

Napi::Value IsConnected(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, connected);
}

Napi::Value Read(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!connected)
        return env.Null();

    SSharedMemory_t *memData = mem.get();

    if (memData->version != SHARED_MEMORY_VERSION)
        return env.Null();

    Napi::Object obj = Napi::Object::New(env);
    obj.Set("sequenceNumber", memData->sequenceNumber);
    obj.Set("version", memData->version);
    obj.Set("gameState", (int)memData->gameState);

    obj.Set("driverName", memData->driverName);
    obj.Set("kartId", memData->kartId);
    obj.Set("kartName", memData->kartName);
    obj.Set("driveType", (int)memData->driveType);
    obj.Set("numberOfGears", memData->numberOfGears);
    obj.Set("maxRpm", memData->maxRpm);
    obj.Set("limiter", memData->limiter);
    obj.Set("shiftRpm", memData->shiftRpm);
    obj.Set("engineCooling", (int)memData->engineCooling);
    obj.Set("engineOptTemperature", memData->engineOptTemperature);

    Napi::Array engineTemperatureAlarm = Napi::Array::New(env, 2);
    for (int i = 0; i < 2; i++)
        engineTemperatureAlarm[i] = memData->engineTemperatureAlarm[i];
    obj.Set("engineTemperatureAlarm", engineTemperatureAlarm);

    obj.Set("maxFuel", memData->maxFuel);
    obj.Set("category", memData->category);
    obj.Set("dash", memData->dash);

    obj.Set("setupFileName", memData->setupFileName);

    obj.Set("time", memData->time);
    obj.Set("trackPos", memData->trackPos);
    obj.Set("rpm", memData->rpm);
    obj.Set("cylinderHeadTemperature", memData->cylinderHeadTemperature);
    obj.Set("waterTemperature", memData->waterTemperature);
    obj.Set("gear", memData->gear);
    obj.Set("fuel", memData->fuel);
    obj.Set("speedometer", memData->speedometer);
    obj.Set("posX", memData->posX);
    obj.Set("posY", memData->posY);
    obj.Set("posZ", memData->posZ);
    obj.Set("velocityX", memData->velocityX);
    obj.Set("velocityY", memData->velocityY);
    obj.Set("velocityZ", memData->velocityZ);
    obj.Set("accelerationX", memData->accelerationX);
    obj.Set("accelerationY", memData->accelerationY);
    obj.Set("accelerationZ", memData->accelerationZ);

    Napi::Array rot = Napi::Array::New(env, 3);
    for (int i = 0; i < 3; i++)
    {
        Napi::Array arr = Napi::Array::New(env, 3);
        for (int j = 0; j < 3; j++)
            arr[j] = memData->rot[i][j];
        rot[i] = arr;
    }
    obj.Set("rot", rot);

    obj.Set("yaw", memData->yaw);
    obj.Set("pitch", memData->pitch);
    obj.Set("roll", memData->roll);
    obj.Set("yawVelocity", memData->yawVelocity);
    obj.Set("pitchVelocity", memData->pitchVelocity);
    obj.Set("rollVelocity", memData->rollVelocity);
    obj.Set("inputSteer", memData->inputSteer);
    obj.Set("inputThrottle", memData->inputThrottle);
    obj.Set("inputBrake", memData->inputBrake);
    obj.Set("inputFrontBrake", memData->inputFrontBrake);
    obj.Set("inputClutch", memData->inputClutch);

    Napi::Array wheelSpeed = Napi::Array::New(env, 4);
    Napi::Array wheelMaterial = Napi::Array::New(env, 4);
    for (int i = 0; i < 4; i++)
    {
        wheelSpeed[i] = memData->wheelSpeed[i];
        wheelMaterial[i] = memData->wheelMaterial[i];
    }
    obj.Set("wheelSpeed", wheelSpeed);
    obj.Set("wheelMaterial", wheelMaterial);

    obj.Set("steerTorque", memData->steerTorque);

    obj.Set("lap", memData->lap);
    obj.Set("lastLapTime", memData->lastLapTime);
    obj.Set("lastLapValid", memData->lastLapValid);
    obj.Set("bestLapTime", memData->bestLapTime);
    obj.Set("estimatedLapTimeToLastLap", memData->estimatedLapTimeToLastLap);
    obj.Set("estimatedLapTimeToBestLap", memData->estimatedLapTimeToBestLap);
    obj.Set("lastLapDeltaToLastLap", memData->lastLapDeltaToLastLap);
    obj.Set("lastLapDeltaToBestLap", memData->lastLapDeltaToBestLap);
    obj.Set("lapDeltaToLastLap", memData->lapDeltaToLastLap);
    obj.Set("lapDeltaToBestLap", memData->lapDeltaToBestLap);

    obj.Set("lastSplitIndex", memData->lastSplitIndex);

    Napi::Array lastSplits = Napi::Array::New(env, MAX_SPLITS);
    Napi::Array bestSplits = Napi::Array::New(env, MAX_SPLITS);
    for (int i = 0; i < MAX_SPLITS; i++)
    {
        lastSplits[i] = memData->lastSplits[i];
        bestSplits[i] = memData->bestSplits[i];
    }
    obj.Set("lastSplits", lastSplits);
    obj.Set("bestSplits", bestSplits);

    obj.Set("trackId", memData->trackId);
    obj.Set("trackName", memData->trackName);
    obj.Set("trackLength", memData->trackLength);

    Napi::Array racedata = Napi::Array::New(env, MAX_SPLITS + 2);
    for (int i = 0; i < MAX_SPLITS + 2; i++)
        racedata[i] = memData->racedata[i];
    obj.Set("racedata", racedata);

    obj.Set("numTrackSegments", memData->numTrackSegments);

    Napi::Array trackSegments = Napi::Array::New(env, memData->numTrackSegments);
    for (int i = 0; i < memData->numTrackSegments; i++)
    {
        Napi::Object segment = Napi::Object::New(env);
        segment.Set("type", (int)memData->trackSegments[i].type);
        segment.Set("length", memData->trackSegments[i].length);
        segment.Set("radius", memData->trackSegments[i].radius);
        segment.Set("angle", memData->trackSegments[i].angle);
        segment.Set("startX", memData->trackSegments[i].startX);
        segment.Set("startY", memData->trackSegments[i].startY);
        segment.Set("startZ", memData->trackSegments[i].startZ);
        trackSegments[i] = segment;
    }
    obj.Set("trackSegments", trackSegments);

    obj.Set("eventType", (int)memData->eventType);
    obj.Set("eventName", memData->eventName);
    obj.Set("numEventEntries", memData->numEventEntries);

    Napi::Array eventEntries = Napi::Array::New(env, memData->numEventEntries);
    for (int i = 0; i < memData->numEventEntries; i++)
    {
        Napi::Object segment = Napi::Object::New(env);
        segment.Set("raceNumber", memData->eventEntries[i].raceNumber);
        segment.Set("name", memData->eventEntries[i].name);
        segment.Set("kartName", memData->eventEntries[i].kartName);
        segment.Set("kartShortName", memData->eventEntries[i].kartShortName);
        segment.Set("category", memData->eventEntries[i].category);
        segment.Set("unactive", memData->eventEntries[i].unactive);
        segment.Set("numberOfGears", memData->eventEntries[i].numberOfGears);
        segment.Set("maxRPM", memData->eventEntries[i].maxRPM);
        eventEntries[i] = segment;
    }
    obj.Set("eventEntries", eventEntries);

    obj.Set("session", memData->session);
    obj.Set("sessionSeries", memData->sessionSeries);

    Napi::Array sessionGroups = Napi::Array::New(env, 2);
    for (int i = 0; i < 2; i++)
        sessionGroups[i] = memData->sessionGroups[i];
    obj.Set("sessionGroups", sessionGroups);

    obj.Set("sessionState", memData->sessionState);
    obj.Set("sessionLength", memData->sessionLength);
    obj.Set("sessionLaps", memData->sessionLaps);
    obj.Set("numSessionEntries", memData->numSessionEntries);

    obj.Set("weatherCondition", (int)memData->weatherCondition);
    obj.Set("airTemperature", memData->airTemperature);
    obj.Set("trackTemperature", memData->trackTemperature);

    obj.Set("bestEventLapTime", memData->bestEventLapTime);
    obj.Set("bestSessionLapTime", memData->bestSessionLapTime);

    Napi::Array sessionEntries = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array sessionGrid = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxLap = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxLastLapTime = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxLastLapValid = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxBestLapTime = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxEstimatedLapTimeToLastLap = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxEstimatedLapTimeToBestLap = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxLastLapDeltaToLastLap = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxLastLapDeltaToBestLap = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxLapDeltaToLastLap = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxLapDeltaToBestLap = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxLastSplitIndex = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxLastSplits = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxBestSplits = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxLastSpeed = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxBestSpeed = Napi::Array::New(env, memData->numSessionEntries);
    Napi::Array kartIdxVehicleData = Napi::Array::New(env, memData->numSessionEntries);
    for (int i = 0; i < memData->numSessionEntries; i++)
    {
        sessionEntries[i] = memData->sessionEntries[i];
        sessionGrid[i] = memData->sessionGrid[i];
        kartIdxLap[i] = memData->kartIdxLap[i];
        kartIdxLastLapTime[i] = memData->kartIdxLastLapTime[i];
        kartIdxLastLapValid[i] = memData->kartIdxLastLapValid[i];
        kartIdxBestLapTime[i] = memData->kartIdxBestLapTime[i];
        kartIdxEstimatedLapTimeToLastLap[i] = memData->kartIdxEstimatedLapTimeToLastLap[i];
        kartIdxEstimatedLapTimeToBestLap[i] = memData->kartIdxEstimatedLapTimeToBestLap[i];
        kartIdxLastLapDeltaToLastLap[i] = memData->kartIdxLastLapDeltaToLastLap[i];
        kartIdxLastLapDeltaToBestLap[i] = memData->kartIdxLastLapDeltaToBestLap[i];
        kartIdxLapDeltaToLastLap[i] = memData->kartIdxLapDeltaToLastLap[i];
        kartIdxLapDeltaToBestLap[i] = memData->kartIdxLapDeltaToBestLap[i];

        kartIdxLastSplitIndex[i] = memData->kartIdxLastSplitIndex[i];

        Napi::Array arrLastSplits = Napi::Array::New(env, MAX_SPLITS);
        Napi::Array arrBestSplits = Napi::Array::New(env, MAX_SPLITS);
        for (int j = 0; j < MAX_SPLITS; j++)
        {
            arrLastSplits[j] = memData->kartIdxLastSplits[i][j];
            arrBestSplits[j] = memData->kartIdxBestSplits[i][j];
        }
        kartIdxLastSplits[i] = arrLastSplits;
        kartIdxBestSplits[i] = arrBestSplits;

        kartIdxLastSpeed[i] = memData->kartIdxLastSpeed[i];
        kartIdxBestSpeed[i] = memData->kartIdxBestSpeed[i];

        Napi::Object vehicleData = Napi::Object::New(env);
        vehicleData.Set("raceNumber", memData->kartIdxVehicleData[i].raceNumber);
        vehicleData.Set("active", memData->kartIdxVehicleData[i].active);
        vehicleData.Set("rpm", memData->kartIdxVehicleData[i].rpm);
        vehicleData.Set("gear", memData->kartIdxVehicleData[i].gear);
        vehicleData.Set("speed", memData->kartIdxVehicleData[i].speed);
        vehicleData.Set("steer", memData->kartIdxVehicleData[i].steer);
        vehicleData.Set("throttle", memData->kartIdxVehicleData[i].throttle);
        vehicleData.Set("brake", memData->kartIdxVehicleData[i].brake);
        kartIdxVehicleData[i] = vehicleData;
    }
    obj.Set("sessionEntries", sessionEntries);
    obj.Set("sessionGrid", sessionGrid);
    obj.Set("kartIdxLap", kartIdxLap);
    obj.Set("kartIdxLastLapTime", kartIdxLastLapTime);
    obj.Set("kartIdxLastLapValid", kartIdxLastLapValid);
    obj.Set("kartIdxBestLapTime", kartIdxBestLapTime);
    obj.Set("kartIdxEstimatedLapTimeToLastLap", kartIdxEstimatedLapTimeToLastLap);
    obj.Set("kartIdxEstimatedLapTimeToBestLap", kartIdxEstimatedLapTimeToBestLap);
    obj.Set("kartIdxLastLapDeltaToLastLap", kartIdxLastLapDeltaToLastLap);
    obj.Set("kartIdxLastLapDeltaToBestLap", kartIdxLastLapDeltaToBestLap);
    obj.Set("kartIdxLapDeltaToLastLap", kartIdxLapDeltaToLastLap);
    obj.Set("kartIdxLapDeltaToBestLap", kartIdxLapDeltaToBestLap);
    obj.Set("kartIdxLastSplitIndex", kartIdxLastSplitIndex);
    obj.Set("kartIdxLastSplits", kartIdxLastSplits);
    obj.Set("kartIdxBestSplits", kartIdxBestSplits);
    obj.Set("kartIdxLastSpeed", kartIdxLastSpeed);
    obj.Set("kartIdxBestSpeed", kartIdxBestSpeed);
    obj.Set("kartIdxVehicleData", kartIdxVehicleData);

    obj.Set("numCommunications", memData->numCommunications);

    Napi::Array communications = Napi::Array::New(env, memData->numCommunications);
    for (int i = 0; i < memData->numCommunications; i++)
    {
        Napi::Object segment = Napi::Object::New(env);
        segment.Set("lap", memData->communications[i].lap);
        segment.Set("time", memData->communications[i].time);
        segment.Set("raceNumber", memData->communications[i].raceNumber);
        segment.Set("session", memData->communications[i].session);
        segment.Set("sessionSeries", memData->communications[i].sessionSeries);
        segment.Set("type", (int)memData->communications[i].type);
        segment.Set("state", (int)memData->communications[i].state);
        segment.Set("reason", (int)memData->communications[i].reason);
        segment.Set("offence", (int)memData->communications[i].offence);
        segment.Set("penaltyType", (int)memData->communications[i].penaltyType);
        communications[i] = segment;
    }
    obj.Set("communications", communications);

    obj.Set("numTrackPositions", memData->numTrackPositions);

    Napi::Array trackPositions = Napi::Array::New(env, memData->numTrackPositions);
    for (int i = 0; i < memData->numTrackPositions; i++)
    {
        Napi::Object segment = Napi::Object::New(env);
        segment.Set("raceNumber", memData->trackPositions[i].raceNumber);
        segment.Set("posX", memData->trackPositions[i].posX);
        segment.Set("posY", memData->trackPositions[i].posY);
        segment.Set("posZ", memData->trackPositions[i].posZ);
        segment.Set("yaw", memData->trackPositions[i].yaw);
        segment.Set("trackPos", memData->trackPositions[i].trackPos);
        trackPositions[i] = segment;
    }
    obj.Set("trackPositions", trackPositions);

    Napi::Object classification = Napi::Object::New(env);
    classification.Set("session", memData->classification.session);
    classification.Set("sessionSeries", memData->classification.sessionSeries);
    classification.Set("sessionState", memData->classification.sessionState);
    classification.Set("sessionTime", memData->classification.sessionTime);
    classification.Set("numEntries", memData->classification.numEntries);

    Napi::Array classificationEntries = Napi::Array::New(env, memData->classification.numEntries);
    for (int i = 0; i < memData->classification.numEntries; i++)
    {
        Napi::Object segment = Napi::Object::New(env);
        segment.Set("raceNumber", memData->classification.entries[i].raceNumber);
        segment.Set("state", (int)memData->classification.entries[i].state);
        segment.Set("bestLapTime", memData->classification.entries[i].bestLapTime);
        segment.Set("bestSpeed", memData->classification.entries[i].bestSpeed);
        segment.Set("bestLapNum", memData->classification.entries[i].bestLapNum);
        segment.Set("numLaps", memData->classification.entries[i].numLaps);
        segment.Set("gap", memData->classification.entries[i].gap);
        segment.Set("gapLaps", memData->classification.entries[i].gapLaps);
        segment.Set("penalty", memData->classification.entries[i].penalty);
        segment.Set("inPit", memData->classification.entries[i].inPit);
        classificationEntries[i] = segment;
    }
    classification.Set("entries", classificationEntries);

    obj.Set("classification", classification);

    obj.Set("requestedSpectateVehicle", memData->requestedSpectateVehicle);
    obj.Set("selectedSpectateVehicle", memData->selectedSpectateVehicle);
    obj.Set("numSpectateVehicles", memData->numSpectateVehicles);

    Napi::Array spectateVehicles = Napi::Array::New(env, memData->numSpectateVehicles);
    for (int i = 0; i < memData->numSpectateVehicles; i++)
    {
        Napi::Object segment = Napi::Object::New(env);
        segment.Set("raceNumber", memData->spectateVehicles[i].raceNumber);
        segment.Set("name", memData->spectateVehicles[i].name);
        spectateVehicles[i] = segment;
    }
    obj.Set("spectateVehicles", spectateVehicles);

    obj.Set("requestedCamera", memData->requestedCamera);
    obj.Set("selectedCamera", memData->selectedCamera);
    obj.Set("numCameras", memData->numCameras);

    Napi::Array cameras = Napi::Array::New(env, memData->numCameras);
    for (int i = 0; i < memData->numCameras; i++)
        cameras[i] = memData->cameras[i];
    obj.Set("cameras", cameras);

    return obj;
}

Napi::Value RequestSpectateVehicle(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!connected)
        return env.Undefined();

    int index = info[0].As<Napi::Number>().Int32Value();
    SSharedMemory_t *memData = mem.get();
    memData->sequenceNumber++;
    mem.write();
    memData->requestedSpectateVehicle = index;
    memData->sequenceNumber++;
    mem.write();
    return env.Undefined();
}

Napi::Value RequestCamera(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (!connected)
        return env.Undefined();

    int index = info[0].As<Napi::Number>().Int32Value();
    SSharedMemory_t *memData = mem.get();
    memData->sequenceNumber++;
    mem.write();
    memData->requestedCamera = index;
    memData->sequenceNumber++;
    mem.write();
    return env.Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "connect"), Napi::Function::New(env, Connect));
    exports.Set(Napi::String::New(env, "disconnect"), Napi::Function::New(env, Disconnect));
    exports.Set(Napi::String::New(env, "isConnected"), Napi::Function::New(env, IsConnected));
    exports.Set(Napi::String::New(env, "read"), Napi::Function::New(env, Read));
    exports.Set(Napi::String::New(env, "requestSpectateVehicle"), Napi::Function::New(env, RequestSpectateVehicle));
    exports.Set(Napi::String::New(env, "requestCamera"), Napi::Function::New(env, RequestCamera));
    return exports;
}