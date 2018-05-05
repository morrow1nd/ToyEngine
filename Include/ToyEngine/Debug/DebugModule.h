#pragma once

#include "ToyEngineConfig.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Engine/EngineModule.h"
#include "ToyEngine/Debug/Logger.h"


namespace ToyEngine
{


class DebugModule : public EngineModule
{
public:
    DebugModule(EngineModuleId moduleId)
        :
        EngineModule(moduleId, "DebugModule")
    {
    }


public:
    virtual void StartUp() override
    {
        EngineModule::StartUp();

        ToyLogger::Instance().Init();
    }

    virtual void ShutDown() override
    {
        ToyLogger::Instance().DeInit();

        EngineModule::ShutDown();
    }
};


} // end of namespace ToyEngine