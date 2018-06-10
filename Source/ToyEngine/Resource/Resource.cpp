#include "ToyEngine/Resource/Resource.h"
#include "ToyUtility/Serialization/Serializer.h"
#include "ToyUtility/Serialization/Unserializer.h"


namespace ToyEngine
{


bool Resource::IsSameType(HResource resource) const
{
    if (resource.Empty() == false)
    {
        return resource->ResourceType() == ResourceType();
    }

    return false;
}


void ResourceBasicInfo::Serialize(ToyUtility::Serializer & serializer) const
{
    serializer.Push(m_UUID.Pretty(), "uuid");
}

void ResourceBasicInfo::Unserialize(ToyUtility::Unserializer & unserializer)
{
    ToyUtility::String str;
    unserializer.Pop("uuid", str);

    m_UUID = ToyUtility::UUID::Rebuild(str);
}

} // end of namespace ToyEngine