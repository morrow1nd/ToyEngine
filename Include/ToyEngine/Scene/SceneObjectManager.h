#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Container/UnorderedSet.h"
#include "ToyEngine/Scene/SceneObject.h"


namespace ToyEngine
{


class SceneObjectManager
{
public:
    SceneObjectManager()
        : m_IdIndex(1)
    {
    }

    SceneObject CreateSceneObject()
    {
        SceneObject so(m_IdIndex++);
        m_SceneObjects.insert(so);
        return so;
    }

    void DestorySceneObject(SceneObject so)
    {
        m_SceneObjects.erase(so);
    }

    
private:
    UnorderedSet<SceneObject, SceneObjectHasher> m_SceneObjects;
    SceneObject::IdType m_IdIndex;
};


} // end of namespace ToyEngine