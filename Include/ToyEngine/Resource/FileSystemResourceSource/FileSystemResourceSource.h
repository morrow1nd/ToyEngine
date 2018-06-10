#pragma once

#include <sstream>
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/FileSystem/FilePath.h"
#include "ToyUtility/Container/UnorderedMap.h"
#include "ToyUtility/Container/List.h"
#include "ToyEngine/Resource/ResourceSource.h"
#include "ToyEngine/Resource/FileSystemResourceSource/FileSystemCachedInfo.h"
#include "ToyEngine/Resource/FileSystemResourceSource/FileSystemResourceFactory.h"
#include "ToyEngine/Resource/FileSystemResourceSource/FileSystemResourceLoader.h"
#include "ToyEngine/Resource/FileSystemResourceSource/FileSystemResourceUnloader.h"


namespace ToyEngine
{


class LoadedResourceMgr
{
public:
    HResource Find(const ResourcePath& path) const
    {
        auto res = m_PathToIndex.find(path);
        if (res == m_PathToIndex.end())
        {
            return HResource();
        }
        else
        {
            return m_Resources[res->second];
        }
    }

    HResource Find(const ToyUtility::UUID& uuid) const
    {
        auto res = m_UUIDToIndex.find(uuid);
        if (res == m_UUIDToIndex.end())
        {
            return HResource();
        }
        else
        {
            return m_Resources[res->second];
        }
    }

    void PushResource(HResource resource)
    {
        if (m_PathToIndex.find(resource->Path()) == m_PathToIndex.end()
            && m_UUIDToIndex.find(resource->UUID()) == m_UUIDToIndex.end())
        {
            m_Resources.push_back(resource);
            m_PathToIndex[resource->Path()] = m_Resources.size() - 1;
            m_UUIDToIndex[resource->UUID()] = m_Resources.size() - 1;
        }
    }

    void RemoveResource(const ResourcePath& path)
    {
        auto res = m_PathToIndex.find(path);
        if (res != m_PathToIndex.end())
        {
            m_UUIDToIndex.erase(m_Resources[res->second]->UUID());
            m_Resources[res->second] = HResource();
            m_PathToIndex.erase(path);
        }
    }
    void RemoveResource(const ToyUtility::UUID& uuid)
    {
        auto res = m_UUIDToIndex.find(uuid);
        if (res != m_UUIDToIndex.end())
        {
            m_PathToIndex.erase(m_Resources[res->second]->Path());
            m_Resources[res->second] = HResource();
            m_UUIDToIndex.erase(uuid);
        }
    }


private:
    ToyUtility::List<HResource> m_Resources;
    ToyUtility::UnorderedMap<ResourcePath, int, ResourcePathHasher, ResourcePathEqualTo> m_PathToIndex;
    ToyUtility::UnorderedMap<ToyUtility::UUID, int, ToyUtility::UUIDHasher, ToyUtility::UUIDEqualTo> m_UUIDToIndex;
};


class FileSystemResourceSource : public ResourceSource
{
public:
    // @path: Resource source root directory path
    FileSystemResourceSource(const ToyUtility::String& path);

    virtual ~FileSystemResourceSource() = default;


public:
    virtual ResourceSoruceType ResourceSourceType() const override { return ResourceSoruceType::FileSystem; }

    virtual void Init() override;
    virtual void DeInit() override;
    virtual bool Exist(const ResourcePath & path) const override;
    virtual bool Exist(const ToyUtility::UUID & uuid) const override;
    virtual HResource Create(const ResourcePath & path, ResourceType type = kResourceNone) override;
    virtual HResource Load(const ResourcePath & path, ResourceType type = kResourceNone) override;
    virtual HResource Load(const ToyUtility::UUID & uuid, ResourceType type = kResourceNone) override;
    virtual bool Copy(const ResourcePath & from, const ResourcePath & to) override;
    virtual bool Copy(const ToyUtility::UUID & from, const ToyUtility::UUID & to) override;
    virtual bool Copy(HResource from, HResource to) override;
    virtual bool Delete(const ResourcePath & path) override;
    virtual bool Delete(const ToyUtility::UUID & uuid) override;
    virtual bool Delete(HResource resource) override;
    virtual bool Move(const ResourcePath & from, const ResourcePath & to) override;
    virtual bool Persistent(HResource resource) override;
    virtual void RescanResourceInfo(const ResourcePath& path) override;
    virtual void ReleaseUnusedResource() override;
    virtual void Find() override;


private:
    HResource _LoadResourceFromFileSystem(const ResourcePath& path, ResourceType type);


private:
    const ToyUtility::String m_RootPath;
    const ToyUtility::FilePath m_RootFilePath;

    FileSystemCachedInfo m_CachedInfo;
    LoadedResourceMgr m_LoadedResources;
    FileSystemResourceFactory m_ResourceFactory;
    FileSystemResourceLoader m_ResourceLoader;
    FileSystemResourceUnloader m_ResourceUnloader;
};


} // end of namespace ToyEngine