#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Scene/SceneObject.h"


namespace ToyEngine
{


class IComponent
{
public:
    virtual void Init(SceneObject so) = 0;
    virtual const SceneObject& GetSceneObject() const = 0;
    virtual const SceneObject& SO() const = 0;
    virtual void Destory() = 0;
};


} // end of namespace ToyEngine