#include "ToyEngine/Resource/ResourceHandle.h"

#include "ToyEngine/Resource/Resource.h"


namespace ToyEngine
{


ResourceHandle::ResourceHandle(Resource * res, bool readOnly)
    :
    m_Res(res)
{
    if (m_Res != nullptr)
    {
        m_Res->Retain();
    }
}

ResourceHandle::~ResourceHandle()
{
    if (m_Res != nullptr)
    {
        m_Res->Release();
        m_Res = nullptr;
    }
}

ResourceHandle::ResourceHandle(const ResourceHandle& res)
    :
    m_Res(res.m_Res)
{
    if (m_Res != nullptr)
    {
        m_Res->Retain();
    }
}

ResourceHandle::ResourceHandle(ResourceHandle && res)
{
    std::swap(m_Res, res.m_Res);
}

ResourceHandle & ResourceHandle::operator=(const ResourceHandle & rhs)
{
    m_Res = rhs.m_Res;

    if (m_Res != nullptr)
    {
        m_Res->Retain();
    }

    return *this;
}

ResourceHandle & ResourceHandle::operator=(ResourceHandle && rhs)
{
    std::swap(m_Res, rhs.m_Res);

    return *this;
}


} // end of namespace ToyEngine