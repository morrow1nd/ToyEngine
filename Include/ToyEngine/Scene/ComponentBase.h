#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Scene/IComponent.h"
#include "ToyEngine/Scene/SceneObject.h"


namespace ToyEngine
{


class ComponentBase : public IComponent
{
public:
    // TODO: maybe we should rename to SetSO
    virtual void Init(SceneObject so) override
    {
        m_SO = so;
    }

    virtual const SceneObject& GetSceneObject() const override
    {
        return m_SO;
    }

    virtual const SceneObject& SO() const override
    {
        return m_SO;
    }

    virtual void Destory() override
    {
    }


protected:
    SceneObject m_SO;
};


} // end of namespace ToyEngine