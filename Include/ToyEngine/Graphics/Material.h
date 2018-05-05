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
    int GetShaderPropertieCount() const;
    const ShaderPropertie& GetShaderPropertieInfo(int index) const;
    const void* GetShaderPropertieValue(int index) const;

    // TODO: setters


private:
    ToyUtility::SPtr<Shader> m_Shader;
    void* m_ShaderPropertieValues;
};


} // end of namespace ToyEngine