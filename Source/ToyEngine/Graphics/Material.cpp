#include "ToyEngine/Graphics/Material.h"


namespace ToyEngine
{



int Material::GetShaderPropertieCount() const
{
    return m_Shader->GetProperties().size();
}

} // end of namespace ToyEngine