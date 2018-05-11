#include "ToyEngine/Scene/Scene.h"
#include "ToyUtility/Event/Event.h"
#include "ToyEngine/Engine/EngineEventId.h"
#include "ToyEngine/Engine/Engine.h"


namespace ToyEngine
{

void Scene::AttachChild(SceneObject so)
{
    m_Children.push_back(so);
}

void Scene::Serialize(ToyUtility::Serializer& serializer) const
{
    ToyUtility::Event event;
    event.SetId(ToyEngineEventId::Scene_Serialize);
    event.SetArg4(&serializer);
    Engine::Instance().SendEvent(event);
}

void Scene::Unserialize(ToyUtility::Serializer & serializer)
{
    ToyUtility::Event event;
    event.SetId(ToyEngineEventId::Scene_UnSerialize);
    event.SetArg4(&serializer);
    Engine::Instance().SendEvent(event);
}


} // end of namespace ToyEngine