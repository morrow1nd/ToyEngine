#pragma once

#include "ToyEngineConfig.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Debug/Logger.h"


namespace ToyEngine
{


// Assert in debug build
#define TOY_ASSERT(condition, fmt, ...) \
if(!condition) \
{ \
    TOY_LOG_ERROR("TOY_ASSERT fail: " fmt, ##__VA_ARGS__); \
}


} // end of namespace ToyEngine