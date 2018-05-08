#pragma once


#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Scene/SceneObject.h"


namespace ToyEngine
{


class IComponent;


class IComponentManager
{
public:
    virtual IComponent* GetComponent(SceneObject so) = 0;
    virtual IComponent& AddComponent(SceneObject so) = 0;
    virtual void DestoryComponent(SceneObject so) = 0;
    virtual bool HasComponent(SceneObject so) const = 0;

    virtual int GetComponentCount() const = 0;
};


} // end of namespace ToyEngine