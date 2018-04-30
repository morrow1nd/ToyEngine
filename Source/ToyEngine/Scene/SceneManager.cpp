#include "ToyEngine/Scene/SceneManager.h"
#include "ToyEngine/Scene/IComponent.h"
#include "ToyEngine/Scene/Scene.h"


namespace ToyEngine
{


void SceneManager::StartUp()
{
    m_CurrScene = new Scene();
}

void SceneManager::ShutDown()
{
    if (m_CurrScene != nullptr)
    {
        delete m_CurrScene;
    }
}


} // end of namespace ToyEngine