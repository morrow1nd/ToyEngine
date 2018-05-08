#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/RenderAPI.h"


// TODO: tem code
#include "TRL/GpuProgram.h"
#include "TRL/GpuBuffer.h"
#include "TRL/AttributeData.h"


namespace ToyEngine
{


using namespace TRL;

class SceneManager;
class CCamera;
class CMeshRenderer;
class CMeshFilter;
class CTransformComponentManager;
class CMeshFilterComponentManager;
class CMeshRendererComponentManager;
class CCameraComponentManager;


class RenderBeast
{
public:
    RenderBeast(RenderAPI& renderAPI)
        :
        programInited(false),
        attribInited(false),

        m_RenderAPI(renderAPI),
        m_TransformCmpMgr(nullptr),
        m_MeshFilterCmpMgr(nullptr),
        m_MeshRendererCmpMgr(nullptr)
    {}


public:
    void Init();

    void DeInit();

    void Update(float deltaTime);


private:
    void _RenderCamera(float deltaTime, CCamera& camera);
    void _RenderMesh(float deltaTime, CCamera& camera, CMeshFilter& mesh, CMeshRenderer& meshRenderer);


private:
    RenderAPI& m_RenderAPI;
    
    SceneManager* m_SceneManager;

    CTransformComponentManager* m_TransformCmpMgr;
    CMeshFilterComponentManager* m_MeshFilterCmpMgr;
    CMeshRendererComponentManager* m_MeshRendererCmpMgr;
    CCameraComponentManager* m_CameraCmpMgr;

    
    // TODO: tem code
    bool programInited;
    TRL::GpuProgram program;
    bool attribInited;
    TRL::GpuBuffer vbo;
    TRL::GpuBuffer ebo;
    TRL::AttributeData attrib;
};


} // end of namespace ToyEngine