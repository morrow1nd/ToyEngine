#include "ToyEngine/Resource/RMaterial.h"

#include "ToyUtility/Serialization/JsonUnserializer.h"


namespace ToyEngine
{


ToyUtility::SPtr<Material> RMaterial::GetMaterial()
{
    if (m_Material == nullptr)
    {
        m_Material = ToyUtility::SPtr<Material>(new Material());
    }

    return m_Material;
}


} // end of namespace ToyEngine