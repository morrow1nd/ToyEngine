#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"


namespace ToyEngine
{


class Resource;


// Ref-counted class for Resource, and a pointer to the real Resource
class ResourceHandle
{
public:
    ResourceHandle()
        :
        m_Res(nullptr)
    {}

    ResourceHandle(Resource* res, bool readOnly = true);
    
    ~ResourceHandle();

    // Copy constructor
    ResourceHandle(const ResourceHandle& res);

    // Move constructor
    ResourceHandle(ResourceHandle&& res);

    // Copy operator
    ResourceHandle& operator=(const ResourceHandle& rhs);

    // Move operator
    ResourceHandle& operator=(ResourceHandle&& rhs);

    bool operator==(const ResourceHandle& rhs) const { return m_Res == rhs.m_Res; }


public:
    bool Empty() const { return m_Res == nullptr; }

    Resource* operator->() const { return m_Res; }


protected:
    Resource* m_Res;
};

// Used to cast inner pointer
template<typename _ResourceClass>
class ResourceHandleCase : public ResourceHandle
{
public:
    using ResourceClass = _ResourceClass;

    ResourceHandleCase(ResourceHandle r)
        :
        ResourceHandle(r)
    { }


    ResourceClass* operator->() const { return dynamic_cast<ResourceClass*>(m_Res); }
};

using HResource = ResourceHandle;

template<typename T>
using HResourceCase = ResourceHandleCase<T>;


} // end of namespace ToyEngine