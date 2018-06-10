#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Resource/RBinary.h"


namespace ToyEngine
{


class RScene : public RBinary
{
public:
    RScene(bool readOnly)
        :
        RBinary(readOnly)
    { }


public:
    virtual ToyEngine::ResourceType ResourceType() const override { return kResourceScene; }
};


} // end of namespace ToyEngine