#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Container/List.h"
#include "ToyEngine/Scene/ComponentBase.h"
#include "ToyEngine/Graphics/Material.h"


namespace ToyEngine
{


class CMeshRenderer : public ComponentBase
{
public:
    const ToyUtility::List<Material>& GetMaterials() const { return m_Mats; }


private:
    ToyUtility::List<Material> m_Mats;
};


} // end of namespace ToyEngine