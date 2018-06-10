#include "ToyEngine/Resource/FileSystemResourceSource/FileSystemResourceFactory.h"

#include "ToyEngine/Debug/Logger.h"

#include "ToyEngine/Resource/RBinary.h"
#include "ToyEngine/Resource/RDirectory.h"
#include "ToyEngine/Resource/RMaterial.h"
#include "ToyEngine/Resource/RMesh.h"
#include "ToyEngine/Resource/RShader.h"
#include "ToyEngine/Resource/RText.h"
#include "ToyEngine/Resource/RTexture2D.h"
#include "ToyEngine/Resource/RScene.h"


namespace ToyEngine
{


HResource FileSystemResourceFactory::CreateResource(ResourceType resourceType)
{
    Resource* resource = nullptr;
    switch (resourceType)
    {
    case kResourceBinary:
        resource = new RBinary(false);
        break;
    case kResourceDirectory:
        resource = new RDirectory(false);
        break;
    case kResourceText:
        resource = new RText(false);
        break;
    case kResourceMaterial:
        resource = new RMaterial(false);
        break;
    //case kResourceMesh:
    //    resource = new (false);
    //    break;
    case kResourceScene:
        resource = new RScene(false);
        break;
    case kResourceShader:
        resource = new RShader(false);
        break;
    //case kResourceTexture2D:
    //    resource = new RTexture2D(false);
    //    break;

    default:
        TOY_LOG_ERROR("FileSystemResourceFactory::CreateResource: unknown resource type: {}", resourceType);
        break;
    }

    return HResource(resource);
}


} // end of namespace ToyEngine