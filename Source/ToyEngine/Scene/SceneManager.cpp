#include "ToyEngine/Scene/SceneManager.h"
#include "ToyEngine/Scene/IComponent.h"
#include "ToyEngine/Scene/Scene.h"
#include "ToyEngine/Engine/Engine.h"


namespace ToyEngine
{


void SceneManager::StartUp()
{
    EngineModule::StartUp();

    m_CurrScene = new Scene();
}

void SceneManager::ShutDown()
{
    if (m_CurrScene != nullptr)
    {
        delete m_CurrScene;
    }

    EngineModule::ShutDown();
}

SceneObject SceneManager::CreateSceneObject()
{
    auto so = m_SceneObjectManager.CreateSceneObject();

    // Every SceneObject has a CTransform component
    m_CTransformComponentManager.AddComponent(so);

    m_Event.SetId(ToyEngineEventId::Scene_CreateSO);
    m_Event.SetArg2(so.GetId());
    Engine::Instance().SendEvent(m_Event);

    return so;
}

void SceneManager::DestorySceneObject(SceneObject so)
{
    m_Event.SetId(ToyEngineEventId::Scene_DestorySO);
    m_Event.SetArg2(so.GetId());
    Engine::Instance().SendEvent(m_Event);

    m_CTransformComponentManager.DestoryComponent(so);

    m_SceneObjectManager.DestorySceneObject(so);
}


} // end of namespace ToyEngine