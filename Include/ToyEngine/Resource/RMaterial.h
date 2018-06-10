#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyEngine/Resource/RBinary.h"
#include "ToyEngine/Graphics/Material.h"


namespace ToyEngine
{


//class RMaterialPropertieInfo
//{
//public:
//    enum class Type
//    {
//        _Begin,
//        Unknown,
//
//        Texture2D, // UUID
//        
//        _End,
//    };
//
//public:
//    RMaterialPropertieInfo()
//        :
//        m_Type(Type::Unknown),
//        m_ArraySize(1)
//    {}
//
//
//    Type GetType() const { return m_Type; }
//    void SetType(Type type) { m_Type = type; }
//
//    bool IsArray() const { return m_ArraySize > 1; }
//    ToyUtility::uint16 GetArraySize() const { return m_ArraySize; }
//    void SetArraySize(ToyUtility::uint16 arraySize) { m_ArraySize = arraySize; }
//
//
//private:
//    Type m_Type;
//    ToyUtility::uint16 m_ArraySize;
//};


class RMaterial : public RBinary
{
public:
    RMaterial(bool readOnly)
        :
        RBinary(readOnly)
    { }


public:
    virtual ToyEngine::ResourceType ResourceType() const override { return kResourceMaterial; }

    ToyUtility::SPtr<Material> GetMaterial();


private:
    ToyUtility::SPtr<Material> m_Material;
};


} // end of namespace ToyEngine