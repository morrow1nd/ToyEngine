#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/RenderAPI.h"
#include "ToyEngine/Engine/EngineModule.h"
#include "ToyEngine/Debug/Logger.h"
#include "ToyEngine/Graphics/RenderBeast/RenderBeast.h"


namespace ToyEngine
{


class RendererManager : public EngineModule
{
public:
    RendererManager(EngineModuleId moduleId)
        :
        EngineModule(moduleId, "RendererManager"),
        m_RenderAPI(),
        m_RenderBeast(m_RenderAPI)
    {}


public:
    virtual void StartUp() override
    {
        EngineModule::StartUp();

        m_RenderBeast.Init();
        TOY_LOG_INFO("RendererManager::StartUp");
    }

    virtual void ShutDown() override
    {
        TOY_LOG_INFO("RendererManager::ShutDown");
        m_RenderBeast.DeInit();
        EngineModule::ShutDown();
    }

    virtual void PostUpdate(float deltaTime) override
    {
        m_RenderBeast.Update(deltaTime);
    }

public:
    RenderAPI& GetRenderAPI() { return m_RenderAPI; }


private:
    TRL::RenderAPI m_RenderAPI;

    RenderBeast m_RenderBeast;
};


} // end of namespace ToyEngine