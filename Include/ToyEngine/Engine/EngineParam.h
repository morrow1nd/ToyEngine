#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"


namespace ToyEngine
{


// Engine Start Up Param
struct EngineParam
{
    ToyUtility::String AssetsDirPath;
    ToyUtility::String StartUpScenePath;
};


} // end of namespace ToyEngine