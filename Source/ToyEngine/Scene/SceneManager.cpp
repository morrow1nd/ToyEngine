#include "ToyEngine/Scene/SceneManager.h"
#include "ToyEngine/Scene/IComponent.h"
#include "ToyEngine/Scene/Scene.h"
#include "ToyEngine/Engine/Engine.h"


namespace ToyEngine
{


void SceneManager::StartUp()
{
    EngineModule::StartUp();

    auto& param = Engine::Instance().GetStartUpParam();
    // TODO: load scene from param.StartUpScenePath

    RegisterEvent((ToyUtility::EventId)ToyEngineEventId::Scene_Serialize, std::bind(&SceneManager::_SceneSerializeHandler, this, std::placeholders::_1));

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

SceneObject SceneManager::CreateSceneObject(SceneObject parent)
{
    auto so = m_SceneObjectManager.CreateSceneObject();

    // Every SceneObject has a CTransform component
    auto& soTfm = static_cast<CTransform&>(m_CTransformComponentManager.AddComponent(so));

    if (parent == SceneObject::Null)
    {
        m_CurrScene->AttachChild(so);
    }
    else
    {
        auto& parentTfm = GetComponent<CTransform>(parent);
        soTfm.SetParent(parentTfm);
    }

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

void SceneManager::_SceneSerializeHandler(ToyUtility::Event & e)
{
    ToyUtility::Serializer& serializer = e.GetArg4<ToyUtility::Serializer>();
    serializer.BeginDictionary("Scene");
    {
        serializer.BeginDictionary("SceneObject_List");
        {
            for each(SceneObject so in m_SceneObjectManager.GetSceneObjects())
            {
                serializer.Push(so.GetId());
            }
        }
        serializer.EndDictionary();
        serializer.BeginDictionary("Transform_List");
        {
            auto i = m_CTransformComponentManager.GetIterator();
            auto end = m_CTransformComponentManager.GetIteratorEnd();
            for (; i != end; ++i)
            {
                const CTransform* cfm = static_cast<const CTransform*>(i->second);
                cfm->Serialize(serializer);
            }
        }
        serializer.EndDictionary();
    }
    serializer.EndDictionary();
}


} // end of namespace ToyEngine