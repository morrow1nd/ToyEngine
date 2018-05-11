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

    RegisterEvent((ToyUtility::EventId)ToyEngineEventId::Scene_Serialize,
        std::bind(&SceneManager::_SceneSerializeHandler, this, std::placeholders::_1));
    RegisterEvent((ToyUtility::EventId)ToyEngineEventId::Scene_UnSerialize,
        std::bind(&SceneManager::_SceneUnSerializeHandler, this, std::placeholders::_1));

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
    auto& soTfm = static_cast<CTransform&>(m_TransformComponentManager.AddComponent(so));

    if (parent == SceneObject::Null)
    {
        m_CurrScene->AttachChild(so);
    }
    else
    {
        auto& parentTfm = GetComponent<CTransform>(parent);
        soTfm.SetParent(parentTfm);
    }

    m_TemEvent.SetId(ToyEngineEventId::Scene_CreateSO);
    m_TemEvent.SetArg2(so.GetId());
    Engine::Instance().SendEvent(m_TemEvent);

    return so;
}

void SceneManager::DestorySceneObject(SceneObject so)
{
    m_TemEvent.SetId(ToyEngineEventId::Scene_DestorySO);
    m_TemEvent.SetArg2(so.GetId());
    Engine::Instance().SendEvent(m_TemEvent);

    m_TransformComponentManager.DestoryComponent(so);

    m_SceneObjectManager.DestorySceneObject(so);
}

#define TOY_SCENE_SERIALIZER_COMPONENTS_HELPER(ComponentName, ComponentManagerMember) \
serializer.BeginDictionary(#ComponentName "_List"); \
{ \
    auto i = ComponentManagerMember.GetIterator(); \
    auto end = ComponentManagerMember.GetIteratorEnd(); \
    for (; i != end; ++i) \
    { \
        const ComponentName* component = static_cast<const ComponentName*>(i->second); \
        component->Serialize(serializer); \
    } \
} \
serializer.EndDictionary();

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
        TOY_SCENE_SERIALIZER_COMPONENTS_HELPER(CTransform, m_TransformComponentManager);
        TOY_SCENE_SERIALIZER_COMPONENTS_HELPER(CMeshFilter, m_MeshFilterComponentManager);
        TOY_SCENE_SERIALIZER_COMPONENTS_HELPER(CMeshRenderer, m_MeshRendererComponentManager);
        TOY_SCENE_SERIALIZER_COMPONENTS_HELPER(CCamera, m_CameraComponentManager);
    }
    serializer.EndDictionary();
}

void SceneManager::_SceneUnSerializeHandler(ToyUtility::Event & e)
{
    ToyUtility::Serializer& serializer = e.GetArg4<ToyUtility::Serializer>();
    
}


} // end of namespace ToyEngine