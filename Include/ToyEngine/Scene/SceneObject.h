#pragma once

#include <functional>
#include "ToyUtility/Prerequisites/PreDefine.h"


namespace ToyEngine
{


class SceneObject
{
public:
    static SceneObject Null;


public:
    typedef ToyUtility::uint32 IdType;

    SceneObject()
        :
        m_Id(Null.GetId())
    {}

    SceneObject(SceneObject::IdType id)
        :
        m_Id(id)
    {}

    bool operator==(const SceneObject& rh) const
    {
        return this->m_Id == rh.m_Id;
    }

    bool operator!=(const SceneObject& rh) const
    {
        return this->m_Id != rh.m_Id;
    }

    ToyUtility::uint32 GetId() const { return m_Id; }


private:
    ToyUtility::uint32 m_Id;
};

class SceneObjectHasher
{
public:
    size_t operator()(const SceneObject& so) const
    {
        return std::hash<SceneObject::IdType> ()(so.GetId());
    }
};


} // end of namespace ToyEngine