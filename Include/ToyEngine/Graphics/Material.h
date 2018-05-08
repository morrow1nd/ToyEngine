#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyUtility/Container/List.h"
#include "ToyEngine/Graphics/Shader.h"


namespace ToyEngine
{


// Material is consisted of Shader and ShaderSetup // TODO: change this line
class Material
{
public:
    int GetShaderPropertieCount() const;
    const ShaderPropertie* GetShaderPropertieInfo(int index) const;

    void SetShaderPropertieValue(int index, const void* data, int copyLength);
    const void* GetShaderPropertieValue(int index) const;
    int GetShaderPropertieValueLength(int index) const;

    void SetShader(ToyUtility::SPtr<Shader> shader);
    ToyUtility::SPtr<Shader> GetShader() const { return m_Shader; }


private:
    void _RecalcShaderPropertieValueOffsets();


private:
    ToyUtility::SPtr<Shader> m_Shader;

    ToyUtility::List<int> m_Offsets;
    int m_AllValueLength;
    void* m_ShaderPropertieValues;
};


} // end of namespace ToyEngine