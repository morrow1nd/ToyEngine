#include "ToyEngine/Graphics/RenderBeast/RenderBeast.h"
#include "ToyEngine/Debug/Logger.h"
#include "ToyEngine/Debug/Assert.h"
#include "ToyEngine/Engine/Engine.h"
#include "ToyEngine/Scene/SceneManager.h"
#include "ToyEngine/Scene/Components/CTransform.h"
#include "ToyEngine/Scene/Components/CMeshFilter.h"
#include "ToyEngine/Scene/Components/CMeshRenderer.h"


namespace ToyEngine
{


void RenderBeast::Init()
{
    m_SceneManager = Engine::Instance().GetModule<SceneManager>();
    if (m_SceneManager == nullptr)
    {
        TOY_LOG_ERROR("RenderBeast::Init: GetModule<SceneManager>() return nullptr");
        return;
    }

    m_TransformCmpMgr = m_SceneManager->GetComponentManagerC<CTransform, CTransformComponentManager>();
    m_MeshFilterCmpMgr = m_SceneManager->GetComponentManagerC<CMeshFilter, CMeshFilterComponentManager>();
    m_MeshRendererCmpMgr = m_SceneManager->GetComponentManagerC<CMeshRenderer, CMeshRendererComponentManager>();

    TOY_ASSERT(m_TransformCmpMgr, "GetComponentManagerC<CTransform, CTransformComponentManager>() return nullptr");
    TOY_ASSERT(m_MeshFilterCmpMgr, "GetComponentManagerC<CMeshFilter, CMeshFilterComponentManager>() return nullptr");
    TOY_ASSERT(m_MeshRendererCmpMgr, "GetComponentManagerC<CMeshRenderer, CMeshRendererComponentManager>() return nullptr");
}

void RenderBeast::DeInit()
{
    m_SceneManager = nullptr;
    m_TransformCmpMgr = nullptr;
    m_MeshFilterCmpMgr = nullptr;
    m_MeshRendererCmpMgr = nullptr;
}

void RenderBeast::Update(float deltaTime)
{
    //m_MeshFilterCmpMgr
}


} // end of namespace ToyEngine