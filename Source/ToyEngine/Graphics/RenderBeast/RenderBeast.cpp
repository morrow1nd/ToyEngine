#include "ToyEngine/Graphics/RenderBeast/RenderBeast.h"
#include "ToyEngine/Debug/Logger.h"
#include "ToyEngine/Debug/Assert.h"
#include "ToyEngine/Engine/Engine.h"
#include "ToyEngine/Scene/SceneManager.h"
#include "ToyEngine/Scene/Components/CTransform.h"
#include "ToyEngine/Scene/Components/CMeshFilter.h"
#include "ToyEngine/Scene/Components/CMeshRenderer.h"
#include "ToyEngine/Scene/Components/CCamera.h"

#include "TRL/GpuShader.h"


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
    m_CameraCmpMgr = m_SceneManager->GetComponentManagerC<CCamera, CCameraComponentManager>();

    TOY_ASSERT(m_TransformCmpMgr, "GetComponentManagerC<CTransform, CTransformComponentManager>() return nullptr");
    TOY_ASSERT(m_MeshFilterCmpMgr, "GetComponentManagerC<CMeshFilter, CMeshFilterComponentManager>() return nullptr");
    TOY_ASSERT(m_MeshRendererCmpMgr, "GetComponentManagerC<CMeshRenderer, CMeshRendererComponentManager>() return nullptr");
    TOY_ASSERT(m_CameraCmpMgr, "GetComponentManagerC<CCamera, CCameraComponentManager>() return nullptr");
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
    auto camerai = m_CameraCmpMgr->GetIterator();
    auto cameraEnd = m_CameraCmpMgr->GetIteratorEnd();
    for (; camerai != cameraEnd; ++camerai)
    {        
#if(TOY_ENGINE_MORE_RUNTIME_CHECK)
        TE_ICOMPONENT_TO_DERIVED_WITH_CHECK(camerai, CCamera, camerap);
        if (camerap != nullptr)
        {
            _RenderCamera(deltaTime, *camerap);
        }
#else
        _RenderCamera(deltaTime, *static_cast<CCamera*>(camerai->second));
#endif
    }
}

void RenderBeast::_RenderCamera(float deltaTime, CCamera& camera)
{
    auto meshRendereri = m_MeshRendererCmpMgr->GetIterator();
    auto meshRendererEnd = m_MeshRendererCmpMgr->GetIteratorEnd();

    for (; meshRendereri != meshRendererEnd; ++meshRendereri)
    {
        CMeshRenderer* meshRenderer = nullptr;
        CMeshFilter* meshFilter = nullptr;

        // TODO: more runtime check
        meshRenderer = static_cast<CMeshRenderer*>(meshRendereri->second);
        IComponent* cmp = m_MeshFilterCmpMgr->GetComponent(meshRenderer->SO());
        if (cmp != nullptr)
        {
            meshFilter = static_cast<CMeshFilter*>(cmp);
        }

        if (meshRenderer != nullptr && meshFilter != nullptr)
        {
            _RenderMesh(deltaTime, camera, *meshFilter, *meshRenderer);
        }
    }
}

void RenderBeast::_RenderMesh(float deltaTime, CCamera& camera, CMeshFilter& mesh, CMeshRenderer& meshRenderer)
{
    if (programInited == false)
    {
        GpuShader vertShader, fragShader;
        vertShader.Init(meshRenderer.GetMaterial(0)
            ->GetShader()->GetSubShaders()[0]
            .GetPasses()[0].GetVertexShaderCode(),
            GpuShaderType::GPU_VERTEX_SHADER);
        if (vertShader.IsCompiledSucc() == false)
        {
            std::cout << "vert: " + vertShader.GetCompileLogInfo() << std::endl;
        }

        fragShader.Init(meshRenderer.GetMaterial(0)
            ->GetShader()->GetSubShaders()[0]
            .GetPasses()[0].GetFragShaderCode(),
            GpuShaderType::GPU_FRAGMENT_SHADER);
        if (fragShader.IsCompiledSucc() == false)
        {
            std::cout << "frag: " + fragShader.GetCompileLogInfo() << std::endl;
        }

        program.Init(vertShader, fragShader);

        programInited = true;
    }

    if (attribInited == false)
    {
        float ver[1024 * 10];
        unsigned int ind[1024];

        auto listOfPos = mesh.GetVertices();
        auto indices = mesh.GetTriangles();

        for (int i = 0; i < listOfPos.size(); ++i)
        {
            ver[i * 3 + 0] = listOfPos[i].x;
            ver[i * 3 + 1] = listOfPos[i].y;
            ver[i * 3 + 2] = listOfPos[i].z;
        }

        for (int j = 0; j < indices.size(); ++j)
        {
            ind[j] = indices[j];
        }


        vbo.Init();
        vbo.Bind(GPU_ARRAY_BUFFER);
        vbo.UploadData(ver, listOfPos.size() * 3 * sizeof(GpuFloat), GpuBufferDataType::GPU_STATIC_DRAW);

        ebo.Init();
        ebo.Bind(GPU_ELEMENT_ARRAY_BUFFER);
        ebo.UploadData(ind, indices.size() * sizeof(GpuUInt), GpuBufferDataType::GPU_STATIC_DRAW);

        attrib.Init();
        attrib.Active();
        auto var = program.FindAttribute("ToyPosition");
        if (var == AttributeVariable::None)
        {
            std::cout << "can't find ...";
        }

        attrib.SetAttributeArray(var, vbo, GpuVariableComponentSize::_3, GPU_FLOAT, AttributeData::NormalizeAction::NotNeedNormalize, 3 * sizeof(float), 0);
        attrib.SetIndicesBuffer(ebo, 6, GPU_UNSIGNED_INT);
        attrib.Inactive();

        attribInited = true;
    }

    auto& meshTransform = m_SceneManager->GetComponent<CTransform>(mesh.SO());
    auto vp = camera.GetProjectionMatrix() * camera.GetViewMatrix() * meshTransform.GetWorldMatrix();

    auto out = vp.multiply(Vector3(0,0,0));

    attrib.Active();
    m_RenderAPI.ActiveGpuProgram(program);

    auto mvp = program.FindUniform("ToyMVP");
    program.SetUniformMatrix4Array(mvp, 1, false, (TRL::GpuFloat*)(&vp));

    m_RenderAPI.DrawIndices(GpuPrimitiveType::GPU_TRIANGLES, attrib);
}


} // end of namespace ToyEngine