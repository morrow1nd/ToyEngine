#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Random/UUID.h"
#include "ToyEngine/Resource/ResourcePath.h"


namespace ToyEngine
{


class FileSystemCachedInfo
{
public:
    void Init(const ToyUtility::String& rootPath);
    bool Exist(const ResourcePath& path) const;
    bool Exist(const ToyUtility::UUID& uuid) const;
    ToyUtility::UUID GetUUIDByPath(const ResourcePath& path) const;
    ResourcePath GetPathByUUID(const ToyUtility::UUID& uuid) const;
    void Rescan(const ResourcePath& path);


private:

};


} // end of namespace ToyEngine