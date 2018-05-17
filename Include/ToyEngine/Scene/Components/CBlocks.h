#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Scene/ComponentBase.h"
#include "ToyEngine/Scene/ComponentManagerHelper.h"


namespace ToyEngine
{


class CBlocks : public ComponentBase
{
public:


    // Serializable
public:
    virtual void Serialize(ToyUtility::Serializer& serializer) const override{ }
    virtual void Unserialize(ToyUtility::Unserializer& serializer) override{ }


private:

};


TE_USING_COMPONENT_MANAGER_HELPER(CBlocks);


} // end of namespace ToyEngine