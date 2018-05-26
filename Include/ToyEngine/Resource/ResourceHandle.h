#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"


namespace ToyEngine
{


class Resource;


// Ref-counted class for Resource, and a pointer to the real Resource
class ResourceHandle
{


private:
    Resource* m_Res;
};

using HResource = ResourceHandle;


} // end of namespace ToyEngine