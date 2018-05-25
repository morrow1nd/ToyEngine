#include <iostream>
#include <cstdlib>

#include <vector>
#include <memory>
#include <Windows.h>

#include "ToyEngine/Engine/Engine.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Serialization/JsonSerializer.h"
#include "ToyUtility/DataStream/FileDataStream.h"
#include "GLFW/glfw3.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "GLFW/../../../../stb/include/stb_image.h"

#include "ToyEngine/Scene/SceneManager.h"
#include "ToyEngine/Scene/Components/CCamera.h"
#include "ToyEngine/Scene/Components/CMeshRenderer.h"
#include "ToyEngine/Scene/Components/CMeshFilter.h"

#include "ToyEngine/Graphics/Material.h"
#include "ToyEngine/Scene/Scene.h"


using namespace std;
using namespace ToyEngine;
using namespace ToyUtility;
using namespace TRL;


void UserLogic();



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle Example", NULL, NULL);
    if (window == NULL)
    {
        // TODO: showErrorMsgBox(...)
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // TODO: showErrorMsgBox(...)
        // std::cout << "Failed to initialize GLAD" << std::endl;
        return -2;
    }

    EngineParam param;
    Engine::Instance().StartUp(param);
    
    UserLogic();

    while (true)
    {
        ToyEngine::Engine::Instance().Step(0.1f);

        glfwSwapBuffers(window);
        glfwPollEvents();

        Sleep(100); // 0.1 second
    }

    system("pause");
    return 0;
}


void UserLogic()
{
    auto sceneManager = Engine::Instance().GetModule<SceneManager>();
    auto cameraSO = sceneManager->CreateSceneObject();
    auto cameraMgr = sceneManager->GetComponentManagerC<CCamera, CCameraComponentManager>();
    CCamera* camera = static_cast<CCamera*>(&cameraMgr->AddComponent(cameraSO));
    camera->SetNearClipDistance(0.1f);
    camera->SetFarClipDistance(10000);
    camera->SetAspectRatio(800.0f / 600.0f);

    auto meshSO = sceneManager->CreateSceneObject();
    auto meshFilterCmpMgr = sceneManager->GetComponentManagerC<CMeshFilter, CMeshFilterComponentManager>();
    auto meshRendererCmgMgr = sceneManager->GetComponentManagerC<CMeshRenderer, CMeshRendererComponentManager>();
    
    CMeshFilter* meshFilter = static_cast<CMeshFilter*>(&meshFilterCmpMgr->AddComponent(meshSO));
    CMeshRenderer* meshRenderer = static_cast<CMeshRenderer*>(&meshRendererCmgMgr->AddComponent(meshSO));

    meshFilter->SetVertices({
        {0.5f,  0.5f, 0.0f,},
        {0.5f, -0.5f, 0.0f,},
        {-0.5f, -0.5f, 0.0f,},
        {-0.5f,  0.5f, 0.0f},
        });
    meshFilter->PushSubMesh({
        0, 1, 3,
        3, 2, 1,
        });

    const char *vertexShaderSource = R"(
#version 330 core

in vec3 ToyPosition; // in model space

uniform mat4 ToyMVP;

void main()
{
    gl_Position = ToyMVP * vec4(ToyPosition, 1);
}
)";
    const char *fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

    Pass pass;
    pass.SetName("pass");
    pass.SetVertexShaderCode(vertexShaderSource);
    pass.SetFragShaderCode(fragmentShaderSource);

    SubShader subShader;
    subShader.SetName("subShader");
    subShader.PushPass(pass);

    SPtr<Shader> shader = SPtr<Shader>(new Shader(ShaderName("name"), {}, {subShader}, ShaderName("fallback_shader")));
    SPtr<Material> material = SPtr<Material>(new Material());
    material->SetShader(shader);

    meshRenderer->PushMaterial(material);

    auto& cameraTrfm = sceneManager->GetComponent<CTransform>(cameraSO);
    auto& meshTrfm = sceneManager->GetComponent<CTransform>(meshSO);

    meshTrfm.SetPosition(Vector3(0, 0, 10));
    meshTrfm.Rotate(Vector3::UNIT_Y, Degree(45));

    cameraTrfm.LookAt(meshTrfm.GetWorldTransform().GetPosition());

    camera->SetTransform(cameraTrfm.GetWorldTransform());

    FileDataStream stream("D:\\test.json", DataStream::AccessMode::WRITE);
    JsonSerializer serializer(stream);
    sceneManager->GetCurrScene()->Serialize(serializer);
    serializer.Flush();
}
