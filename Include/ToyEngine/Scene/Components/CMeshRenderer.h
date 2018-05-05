#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyEngine/Scene/ComponentBase.h"
#include "ToyEngine/Graphics/Material.h"
#include "ToyEngine/Scene/ComponentManagerHelper.h"


namespace ToyEngine
{


class CMeshRenderer : public ComponentBase
{
public:
    const ToyUtility::List<ToyUtility::SPtr<Material>>& GetMaterials() const { return m_Mats; }


private:
    ToyUtility::List<ToyUtility::SPtr<Material>> m_Mats;
};

USING_COMPONENT_MANAGER_HELPER(CMeshRenderer);


} // end of namespace ToyEngine