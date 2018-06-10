#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"


namespace ToyEngine
{


enum ResourceType;


class ResourcePath
{
public:
    static ResourceType GetTypeByExtension(const ToyUtility::String& extension);


public:
    ResourcePath()
        :
        m_Path("")
    {}

    ResourcePath(ToyUtility::String&& path)
        :
        m_Path(std::move(path))
    {}

    ResourcePath(const ToyUtility::String& path)
        :
        m_Path(path)
    {}

    ToyUtility::String FullPath() const
    {
        return m_Path;
    }

    bool Empty() const { return m_Path.empty(); }


    // TODOM: use a string pool, rather than using the full path string
private:
    ToyUtility::String m_Path;
};

class ResourcePathHasher : public std::unary_function< ToyEngine::ResourcePath, size_t >
{
public:
    size_t operator()(const ToyEngine::ResourcePath& path) const
    {
        return std::hash<ToyUtility::String>()(path.FullPath());
    }
};

class ResourcePathEqualTo
{
public:
    bool operator()(const ToyEngine::ResourcePath& lhs, const ToyEngine::ResourcePath& rhs) const
    {
        return lhs.FullPath() == rhs.FullPath();
    }
};


} // end of namespace ToyEngine