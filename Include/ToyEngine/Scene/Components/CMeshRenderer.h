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

    int GetMaterialCount() const { return m_Mats.size(); }

    ToyUtility::SPtr<Material> GetMaterial(int index) { return m_Mats[index]; }

    void SetMaterial(int index, ToyUtility::SPtr<Material> material)
    {
        int size = m_Mats.size();
        if (index >= 0 && index < size)
        {
            m_Mats[index] = material;
        }
    }

    void PushMaterial(ToyUtility::SPtr<Material> material)
    {
        m_Mats.push_back(material);
    }


    // Serializable
public:
    virtual void Serialize(ToyUtility::Serializer& serializer) const override;
    virtual void UnSerialize(ToyUtility::Serializer& serializer) override;


private:
    ToyUtility::List<ToyUtility::SPtr<Material>> m_Mats;
};

TE_USING_COMPONENT_MANAGER_HELPER(CMeshRenderer);


} // end of namespace ToyEngine