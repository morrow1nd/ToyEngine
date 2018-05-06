#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/RenderAPI.h"


namespace ToyEngine
{


using namespace TRL;

class SceneManager;
class CTransformComponentManager;
class CMeshFilterComponentManager;
class CMeshRendererComponentManager;


class RenderBeast
{
public:
    RenderBeast(RenderAPI& renderAPI)
        :
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
    RenderAPI& m_RenderAPI;
    
    SceneManager* m_SceneManager;

    CTransformComponentManager* m_TransformCmpMgr;
    CMeshFilterComponentManager* m_MeshFilterCmpMgr;
    CMeshRendererComponentManager* m_MeshRendererCmpMgr;
};


} // end of namespace ToyEngine