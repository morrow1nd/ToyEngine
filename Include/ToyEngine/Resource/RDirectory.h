#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Resource/Resource.h"


namespace ToyEngine
{


class RDirectory : public Resource
{
public:
    RDirectory(bool readOnly)
        :
        Resource(readOnly)
    { }


public:
    virtual ToyEngine::ResourceType ResourceType() const override { return kResourceDirectory; }

    virtual void Copy(HResource dest) override;
};


} // end of namespace ToyEngine