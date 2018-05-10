#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Serialization/Serializable.h"
#include "ToyUtility/Serialization/Serializer.h"
#include "ToyEngine/Scene/SceneObjectManager.h"
#include "ToyEngine/Scene/IComponentManager.h"


namespace ToyEngine
{


class Scene : public ToyUtility::Serializable
{
public:
    Scene(){ }


public:
    const ToyUtility::List<SceneObject>& GetChildren() const { return m_Children; }

    void AttachChild(SceneObject so);


public:
    virtual void Serialize(ToyUtility::Serializer& serializer) const override;
    virtual void UnSerialize(ToyUtility::Serializer& serializer) override;


private:
    ToyUtility::List<SceneObject> m_Children;
};


} // end of namespace ToyEngine