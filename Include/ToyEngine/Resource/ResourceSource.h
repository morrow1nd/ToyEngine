#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Random/UUID.h"
#include "ToyEngine/Resource/ResourceHandle.h"
#include "ToyEngine/Resource/ResourcePath.h"
#include "ToyEngine/Resource/Resource.h"


namespace ToyEngine
{


enum class ResourceSoruceType
{
    FileSystem,
    AssetBundle,

    // More data sources
    //SqliteDataBase,
    //Http(s)Resource,
};


class ResourceSource
{
public:
    virtual ~ResourceSource() = default;


public:
    virtual ResourceSoruceType ResourceSourceType() const = 0;
    
    virtual void Init() = 0;

    virtual void DeInit() = 0;


    /////////////////////////////////////////////////////////////////////////////
    // Resource Operate

    // Check if resource exists
    virtual bool Exist(const ResourcePath& path) const = 0;
    virtual bool Exist(const ToyUtility::UUID& uuid) const = 0;

    // Create new resource, resource must not exist.
    // @return nullptr if error
    virtual HResource Create(const ResourcePath& path, ResourceType type = kResourceNone) = 0;

    // Load resource referenced by @path, and use resource loader specified by @type
    // if @type is @kResourceNone, then loader will be choosed by the postfix of name.
    // @return nullptr if fail
    virtual HResource Load(const ResourcePath& path, ResourceType type = kResourceNone) = 0;
    virtual HResource Load(const ToyUtility::UUID& uuid, ResourceType type = kResourceNone) = 0;

    // Copy resource, override or create dest resource
    virtual bool Copy(const ResourcePath& from, const ResourcePath& to) = 0;
    virtual bool Copy(const ToyUtility::UUID& from, const ToyUtility::UUID& to) = 0;
    virtual bool Copy(HResource from, HResource to) = 0;

    // Delete resource
    virtual bool Delete(const ResourcePath& path) = 0;
    virtual bool Delete(const ToyUtility::UUID& uuid) = 0;
    virtual bool Delete(HResource resource) = 0;

    // Move resource, and keep the UUID unchanged.
    virtual bool Move(const ResourcePath& from, const ResourcePath& to) = 0;

    // Make data persistent. Save contents to file system or other ResourceSource
    virtual bool Persistent(HResource resource) = 0;

    virtual void RescanResourceInfo(const ResourcePath& path) = 0;




    virtual void ReleaseUnusedResource() = 0;

    virtual void/*...*/ Find(/*...*/) = 0;
};


} // end of namespace ToyEngine