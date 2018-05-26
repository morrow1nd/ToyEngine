#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/List.h"
#include "ToyEngine/Resource/ResourceHandle.h"


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


    HResource Load(/*Path*/);
    HResource Load(/*UUID*/);

    bool Exist(/*Path*/) const;
    bool Exist(/*UUID*/) const;

    void Delete(/*Path*/);
    void Delete(/*UUID*/);
    void Delete(/*HResource*/);

    void Move(/*Path from, Path to*/);

    void Copy(/*Path from, Path to*/);
    void Copy(/*UUID from, UUID to*/);
    void Copy(/*HResource from, HResource to*/);

    HResource Create(/*...*/);

    void Unload(/*Path*/);
    void Unload(/*UUID*/);
    void Unload(/*HResource*/);

    void ReleaseUnusedResource();

    void Find(/*...*/);
};


} // end of namespace ToyEngine