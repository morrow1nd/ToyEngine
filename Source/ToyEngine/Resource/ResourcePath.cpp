#include "ToyEngine/Resource/ResourcePath.h"

#include "ToyEngine/Resource/Resource.h"


namespace ToyEngine
{
ResourceType ResourcePath::GetTypeByExtension(const ToyUtility::String & extension)
{
    if (extension == "toy_mat")
    {
        return kResourceMaterial;
    }
    else if (extension == "toy_shader")
    {
        return kResourceShader;
    }
    else if (extension == "toy_scene")
    {
        return kResourceScene;
    }
    else if (extension == "toy_mesh")
    {
        return kResourceMesh;
    }

    return kResourceBinary;
}
} // end of namespace ToyEngine