#include "ToyEngine/Resource/FileSystemResourceSource/FileSystemResourceSource.h"

#include "ToyUtility/FileSystem/FileSystem.h"
#include "ToyEngine/Debug/Logger.h"
#include "ToyEngine/Debug/Assert.h"

#include "ToyEngine/Resource/RDirectory.h"
#include "ToyEngine/Resource/RText.h"


namespace ToyEngine
{


FileSystemResourceSource::FileSystemResourceSource(const ToyUtility::String & path)
    :
    m_RootPath(path),
    m_RootFilePath(m_RootPath)
{
}

void FileSystemResourceSource::Init()
{
    m_CachedInfo.Init(m_RootPath);
    //m_CachedInfo.Rescan("/");
}

void FileSystemResourceSource::DeInit()
{
}

bool FileSystemResourceSource::Exist(const ResourcePath & path) const
{
    return m_CachedInfo.Exist(path);
}

bool FileSystemResourceSource::Exist(const ToyUtility::UUID & uuid) const
{
    return m_CachedInfo.Exist(uuid);
}

HResource FileSystemResourceSource::Create(const ResourcePath & path, ResourceType type)
{
    return HResource();
}

HResource FileSystemResourceSource::Load(const ResourcePath & path, ResourceType type)
{
    // Check if it's already loaded
    auto res = m_LoadedResources.Find(path);
    if (res.Empty() == false)
    {
        return res;
    }

    // Check if this resource exists
    if (Exist(path) == false)
    {
        return HResource();
    }

    return _LoadResourceFromFileSystem(path, type);
}

HResource FileSystemResourceSource::Load(const ToyUtility::UUID & uuid, ResourceType type)
{
    // Check if it's already loaded
    auto res = m_LoadedResources.Find(uuid);
    if (res.Empty() == false)
    {
        return res;
    }

    // Check if it exists
    auto path = m_CachedInfo.GetPathByUUID(uuid);
    if (path.Empty())
    {
        return HResource();
    }

    return _LoadResourceFromFileSystem(path, type);
}

bool FileSystemResourceSource::Copy(const ResourcePath & from, const ResourcePath & to)
{
    return false;
}

bool FileSystemResourceSource::Copy(const ToyUtility::UUID & from, const ToyUtility::UUID & to)
{
    return false;
}

bool FileSystemResourceSource::Copy(HResource from, HResource to)
{
    return false;
}

bool FileSystemResourceSource::Delete(const ResourcePath & path)
{
    return false;
}

bool FileSystemResourceSource::Delete(const ToyUtility::UUID & uuid)
{
    return false;
}

bool FileSystemResourceSource::Delete(HResource resource)
{
    return false;
}

bool FileSystemResourceSource::Move(const ResourcePath & from, const ResourcePath & to)
{
    return false;
}

bool FileSystemResourceSource::Persistent(HResource resource)
{
    return false;
}

void FileSystemResourceSource::RescanResourceInfo(const ResourcePath & path)
{
}

void FileSystemResourceSource::ReleaseUnusedResource()
{
}

void FileSystemResourceSource::Find()
{
}

HResource FileSystemResourceSource::_LoadResourceFromFileSystem(const ResourcePath & path, ResourceType type)
{
    ToyUtility::FilePath filePath = m_RootFilePath.Resolve(path.FullPath());
    auto fileHandle = ToyUtility::FileSystem::Open(filePath.Path());

    // Check the resource type
    if (type == ResourceType::kResourceNone)
    {
        if (fileHandle->IsDirectory())
        {
            type = kResourceDirectory;
        }
        else
        {
            type = ResourcePath::GetTypeByExtension(filePath.Extension());
        }
    }

    HResource res = m_ResourceFactory.CreateResource(type);
    if (res.Empty() == false)
    {
        res->SetPath(path);

        m_ResourceLoader.Load(res, filePath);
    }

    return res;
}


} // end of namespace ToyEngine