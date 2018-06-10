#include "ToyEngine/Resource/RShader.h"


namespace ToyEngine
{


ToyUtility::SPtr<const Shader> RShader::GetShader()
{
    if (m_Shader == nullptr)
    {
        // TODOH: generater Shader
    }

    return m_Shader;
}


} // end of namespace ToyEngine