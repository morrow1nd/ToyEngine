#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Engine/EngineModule.h"
#include "ToyEngine/Scene/Components/CMeshFilter.h"
#include "ToyEngine/Scene/Components/CMeshRenderer.h"
#include "ToyEngine/Debug/Logger.h"


namespace ToyEngine
{


class RendererManager : public EngineModule
{
public:
    RendererManager(EngineModuleId moduleId)
        :
        EngineModule(moduleId, "RendererManager")
    {}


public:
    virtual void StartUp() override
    {
        EngineModule::StartUp();

        TOY_LOG_INFO("RendererManager::StartUp");
    }

    virtual void ShutDown() override
    {
        TOY_LOG_INFO("RendererManager::ShutDown");
        EngineModule::ShutDown();
    }

    virtual void Update(float deltaTime) override
    {

    }

    virtual void PostUpdate(float deltaTime) override
    {

    }


private:
};


} // end of namespace ToyEngine