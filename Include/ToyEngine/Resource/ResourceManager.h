#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyEngine/Engine/EngineModule.h"


namespace ToyEngine
{


class ResourceManager : public EngineModule
{
public:
    ResourceManager(EngineModuleId moduleId)
        :
        EngineModule(moduleId, "ResourceManager")
    {}



    /************************************************************************/
    /*                             Functions                                */
    /************************************************************************/
public:
    void AddAssetsFindingPath(const ToyUtility::String& path);
    void RemoveAssetsFindingPath(const ToyUtility::String& path);
    void ClearAssetsFindingPath();


    void Load(const ToyUtility::String& path);
    void Unload(const ToyUtility::String& path);


public:
    virtual void StartUp() override
    {
        EngineModule::StartUp();

    }

    virtual void ShutDown() override
    {

        EngineModule::ShutDown();
    }
};


} // end of namespace ToyEngine