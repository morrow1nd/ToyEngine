#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Resource/Resource.h"


namespace ToyEngine
{


class RTexture2D : public Resource
{
public:
    RTexture2D(bool readOnly)
        :
        Resource(readOnly)
    {
    }


public:
    virtual ToyEngine::ResourceType ResourceType() const override { return kResourceTexture2D; }

    virtual void Copy(HResource dest) override;


private:
    void* m_RawTextureData;
    ToyUtility::uint32 m_RawTextureDataLength;
    // wrap mode
    // minmap
    // filter mode
    //...
};


} // end of namespace ToyEngine