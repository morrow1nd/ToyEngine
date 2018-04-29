#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Scene/Components/CTransform.h"
#include "Base/IModule.h"
#include "ToyEngine/Scene/IComponentManager.h"
#include "ToyEngine/Scene/SceneObjectManager.h"


namespace ToyEngine
{


class Scene;
class IComponentManager;

class SceneManager : public IModule
{
public:
    SceneManager()
        : m_CurrScene(nullptr)
    {
    }

    virtual void StartUp(Engine& engine) override;
    virtual void ShutDown() override;

    template<typename ComponentType>
    IComponentManager* GetComponentManager()
    {
        return GetComponentManagerHelper<ComponentType>().GetComponentManager(*this);
    }

    Scene* GetCurrScene()
    {
        return m_CurrScene;
    }
    
    const Scene* GetCurrScene() const
    {
        return m_CurrScene;
    }

    SceneObject CreateSceneObject()
    {
        auto so = m_SceneObjectManager.CreateSceneObject();

        // Every SceneObject has a CTransform component
        m_CTransformComponentManager.AddComponent(so);

        return so;
    }

    void DestorySceneObject(SceneObject so)
    {
        m_CTransformComponentManager.DestoryComponent(so);

        m_SceneObjectManager.DestorySceneObject(so);
    }

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


private:
    friend class GetComponentManagerHelper;

    template<typename ComponentType>
    struct GetComponentManagerHelper
    {
        IComponentManager* GetComponentManager(SceneManager& sceneManager)
        {
            return nullptr;
        }
    };

    template<>
    struct GetComponentManagerHelper<CTransform>
    {
        IComponentManager* GetComponentManager(SceneManager& sceneManager)
        {
            return &(sceneManager.m_CTransformComponentManager);
        }
    };


private:
    Scene* m_CurrScene;

    SceneObjectManager m_SceneObjectManager;

    CTransformComponentManager m_CTransformComponentManager;
};


} // end of namespace ToyEngine