#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/DesignPattern/IModule.h"
#include "ToyUtility/Event/Event.h"
#include "ToyEngine/Engine/EngineModule.h"
#include "ToyEngine/Scene/SceneObjectManager.h"
#include "ToyEngine/Engine/EngineEventId.h"

// Component Managers
#include "ToyEngine/Scene/Components/CTransform.h"
#include "ToyEngine/Scene/Components/CMeshFilter.h"
#include "ToyEngine/Scene/Components/CMeshRenderer.h"
#include "ToyEngine/Scene/Components/CCamera.h"


namespace ToyEngine
{


#define TOY_GET_COMPONENT_MANAGER_HELPER_SPECFIY(ComponentType, ComponentManagerMemberName)     \
template<>                                                                                      \
struct _GetComponentManagerHelper<ComponentType>                                                \
{                                                                                               \
    IComponentManager* GetComponentManager(SceneManager& sceneManager)                          \
    {                                                                                           \
        return &(sceneManager.ComponentManagerMemberName);                                      \
    }                                                                                           \
};


class Scene;
class IComponentManager;


class SceneManager : public EngineModule
{
public:
    SceneManager(EngineModuleId moduleId)
        :
        EngineModule(moduleId, "SceneManager"),
        m_CurrScene(nullptr)
    {}


    virtual void StartUp() override;
    virtual void ShutDown() override;

    template<typename ComponentType>
    IComponentManager* GetComponentManager()
    {
        return _GetComponentManagerHelper<ComponentType>().GetComponentManager(*this);
    }

    template<typename ComponentType, typename ComponentManagerType>
    ComponentManagerType* GetComponentManagerC()
    {
        return static_cast<ComponentManagerType*>(
            _GetComponentManagerHelper<ComponentType>().GetComponentManager(*this));
    }

    Scene* GetCurrScene()
    {
        return m_CurrScene;
    }
    
    const Scene* GetCurrScene() const
    {
        return m_CurrScene;
    }

    SceneObject CreateSceneObject(SceneObject parent = SceneObject::Null);

    void DestorySceneObject(SceneObject so);

    template<typename ComponentType>
    ComponentType& HasComponent(SceneObject so)
    {
        auto componentManager = GetComponentManager<ComponentType>();
        if (componentManager != nullptr)
        {
            return componentManager->HasComponent(so);
        }

        return false;
    }

    template<typename ComponentType>
    ComponentType& GetComponent(SceneObject so)
    {
        return *static_cast<ComponentType*>(&(GetComponentManager<ComponentType>()->AddComponent(so)));
    }

    template<typename ComponentType>
    void DestoryComponent(SceneObject so)
    {
        GetComponentManager<ComponentType>()->DestoryComponent(so);
    }


    // GetComponentManager
private:
    friend class _GetComponentManagerHelper;

    template<typename ComponentType>
    struct _GetComponentManagerHelper
    {
        IComponentManager* GetComponentManager(SceneManager& sceneManager)
        {
            return nullptr;
        }
    };

    TOY_GET_COMPONENT_MANAGER_HELPER_SPECFIY(CTransform, m_CTransformComponentManager);
    TOY_GET_COMPONENT_MANAGER_HELPER_SPECFIY(CMeshFilter, m_CMeshFilterComponentManager);
    TOY_GET_COMPONENT_MANAGER_HELPER_SPECFIY(CMeshRenderer, m_MeshRendererComponentManager);
    TOY_GET_COMPONENT_MANAGER_HELPER_SPECFIY(CCamera, m_CameraComponentManager);

    CTransformComponentManager m_CTransformComponentManager;
    CMeshFilterComponentManager m_CMeshFilterComponentManager;
    CMeshRendererComponentManager m_MeshRendererComponentManager;
    CCameraComponentManager m_CameraComponentManager;


private:
    void _SceneSerializeHandler(ToyUtility::Event& e);



    // Template cache data
private:
    ToyUtility::Event m_Event;


private:
    Scene* m_CurrScene;

    SceneObjectManager m_SceneObjectManager;
};


} // end of namespace ToyEngine