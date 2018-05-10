#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Event/Event.h"


namespace ToyEngine
{


enum class ToyEngineEventId
{
    Begin,

    // Scene
    Scene_CreateSO,
    Scene_DestorySO,
    Scene_Serialize,

    End,
};


} // end of namespace ToyEngine