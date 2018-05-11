#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Engine/EngineModule.h"


namespace ToyEngine
{


class ResourceManager : public EngineModule
{
public:
    ResourceManager(EngineModuleId moduleId)
        :
        EngineModule(moduleId, "ResourceManager")
    {}


public:
    virtual void StartUp() override
    {
        EngineModule::StartUp();

    }

    virtual void ShutDown() override
    {

        EngineModule::ShutDown();
    }
};


} // end of namespace ToyEngine