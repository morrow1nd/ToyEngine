#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Resource/Resource.h"


namespace ToyEngine
{


class FileSystemResourceFactory
{
public:
    HResource CreateResource(ResourceType resourceType);
};


} // end of namespace ToyEngine