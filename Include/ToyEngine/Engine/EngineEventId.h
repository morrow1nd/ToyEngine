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


    End,
};


} // end of namespace ToyEngine