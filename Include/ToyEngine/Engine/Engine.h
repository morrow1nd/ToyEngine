#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DesignPattern/ISingleton.h"
#include "ToyUtility/Event/EventHub.h"
#include "ToyEngine/Engine/EngineParam.h"

// Modules
#include "ToyEngine/Debug/DebugModule.h"
#include "ToyEngine/Resource/ResourceManager.h"
#include "ToyEngine/Scene/SceneManager.h"
#include "ToyEngine/Graphics/RendererManager.h"


// TODO List:
// * add virtual destructor for virtual class
// * remove ToyUtility/Math's old code(cassert, coding style)



namespace ToyEngine
{


#define TOY_ENGINE_MODULE_GETTER_HELPER(ModuleClass, ModuleMemberName)  \
template<>                                                              \
struct _GetModuleHelper<ModuleClass>                                    \
{                                                                       \
    ModuleClass* GetModule(Engine& engine)                              \
    {                                                                   \
        return &(engine.ModuleMemberName);                              \
    }                                                                   \
};


class Engine : public ToyUtility::ISingleton<Engine>, public ToyUtility::EventHub
{
public:
    Engine()
        :
        m_DebugModule(1),
        m_ResourceManager(2),
        m_SceneManager(3),
        m_RendererManager(4)
    {}


public:
    void StartUp(const EngineParam& startUpParam)
    {
        m_StartUpParam = startUpParam;

        // This sequence is very important
        m_Modules.push_back(&m_DebugModule);
        m_Modules.push_back(&m_ResourceManager);
        m_Modules.push_back(&m_SceneManager);
        m_Modules.push_back(&m_RendererManager);

        for (auto i = m_Modules.begin(), end = m_Modules.end(); i != end; ++i)
        {
            RegisterListener(*i);
        }

        for (auto i = m_Modules.begin(), end = m_Modules.end(); i != end; ++i)
        {
            (*i)->StartUp();
        }
    }

    void Step(float deltaTime)
    {
        int moduleSize = m_Modules.size();

        for (int i = 0; i < moduleSize; ++i)
        {
            m_Modules[i]->Update(deltaTime);
        }

        for (int i = 0; i < moduleSize; ++i)
        {
            m_Modules[i]->PostUpdate(deltaTime);
        }
    }

    void ShutDown()
    {
        // reverse
        for (auto i = m_Modules.rbegin(), end = m_Modules.rend(); i != end; ++i)
        {
            (*i)->ShutDown();
        }
    }

    template<typename ModuleType>
    ModuleType* GetModule()
    {
        return _GetModuleHelper<ModuleType>().GetModule(*this);
    }

    const EngineParam& GetStartUpParam() const { return m_StartUpParam; }


    // Module Getter
private:
    friend class _GetModuleHelper;

    template<typename ModuleType>
    struct _GetModuleHelper
    {
        ModuleType* GetModule(Engine& engine)
        {
            return nullptr;
        }
    };

    TOY_ENGINE_MODULE_GETTER_HELPER(SceneManager, m_SceneManager);
    TOY_ENGINE_MODULE_GETTER_HELPER(RendererManager, m_RendererManager);
    TOY_ENGINE_MODULE_GETTER_HELPER(DebugModule, m_DebugModule);


private:
    DebugModule m_DebugModule;
    ResourceManager m_ResourceManager;
    SceneManager m_SceneManager;
    RendererManager m_RendererManager;

    ToyUtility::List<EngineModule*> m_Modules;
    EngineParam m_StartUpParam;
};


} // end of namespace ToyEngine