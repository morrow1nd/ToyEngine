#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Serialization/Serializable.h"
#include "ToyUtility/DesignPattern/IUncopyable.h"


namespace ToyEngine
{


class Resource : public ToyUtility::Serializable, private ToyUtility::IUncopyable
{
public:


private:
    // uuid
    // path
    // status
    // real resource data(in drived class)
};


} // end of namespace ToyEngine