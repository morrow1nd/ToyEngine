#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyEngine/Graphics/Shader.h"


namespace ToyEngine
{


// Material is consisted of Shader and ShaderSetup // TODO: change this line
class Material
{
public:


private:
    ToyUtility::SPtr<Shader> m_Shader;
    // ShaderSetup
};


} // end of namespace ToyEngine