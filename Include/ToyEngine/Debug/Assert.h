#pragma once

#include "ToyEngineConfig.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Debug/Logger.h"


namespace ToyEngine
{

#define TOY_MACRO_TO_STRING(x) #x

// For the reason: https://stackoverflow.com/a/19343239
#define TOY_MACRO_TWICE(x) TOY_MACRO_TO_STRING(x)

// Assert in debug build
#define TOY_ASSERT(condition, fmt, ...) \
if(!condition) \
{ \
    TOY_LOG_ERROR(__FILE__ ":" __FUNCTION__ ":L" TOY_MACRO_TWICE(__LINE__) ": TOY_ASSERT fail: " fmt, ##__VA_ARGS__); \
}


} // end of namespace ToyEngine