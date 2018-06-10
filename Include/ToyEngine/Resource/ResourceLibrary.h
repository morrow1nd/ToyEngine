#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Random/UUID.h"
#include "ToyEngine/Resource/ResourceHandle.h"
#include "ToyEngine/Resource/ResourcePath.h"


namespace ToyEngine
{


struct ResourceLibrarySource
{
    enum class ResourceLibrarySoruceType
    {
        FileSystem,
        AssetBundle,

        // More data sources
        //SqliteDataBase,
        //HttpResource,
    };

    ResourceLibrarySoruceType Type;
};

struct ResourceLibraryConfig
{
    ToyUtility::List<ResourceLibrarySource> Sources;
};


class ResourceLibrary
{
public:
    void Init(const ResourceLibraryConfig& config);
    void DeInit();


    HResource Load(const ResourcePath& path);
    HResource Load(const ToyUtility::UUID& uuid);

    bool Exist(const ResourcePath& path) const;
    bool Exist(const ToyUtility::UUID& uuid) const;

    void Delete(const ResourcePath& path);
    void Delete(const ToyUtility::UUID& uuid);
    void Delete(HResource resource);

    void Move(const ResourcePath& from, const ResourcePath& to);

    void Copy(const ResourcePath& from, const ResourcePath& to);
    void Copy(const ToyUtility::UUID& from, const ToyUtility::UUID& to);
    void Copy(HResource from, HResource to);

    HResource Create(/*...*/);

    void Unload(const ResourcePath& path);
    void Unload(const ToyUtility::UUID& uuid);
    void Unload(HResource resource);

    void ReleaseUnusedResource();

    void Find(/*...*/);
};


} // end of namespace ToyEngine