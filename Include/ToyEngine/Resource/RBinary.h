#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Resource/Resource.h"
#include "ToyUtility/DataStream/MemoryDataStream.h"


namespace ToyEngine
{


class RBinary : public Resource
{
public:
    RBinary(bool readOnly)
        :
        Resource(readOnly),
        m_Capacity(0),
        m_BinaryDataSize(0),
        m_BinaryData(nullptr)
    {}

    ~RBinary();


public:
    virtual ToyEngine::ResourceType ResourceType() const override { return kResourceBinary; }

    virtual void Copy(HResource dest) override;

    ToyUtility::MemoryDataStream GetBinaryData() const;

    void SetBinaryData(ToyUtility::DataStream& data);


private:
    void _CheckCapacity(ToyUtility::uint32 needed);


private:
    ToyUtility::uint32 m_Capacity;

protected:
    ToyUtility::uint32 m_BinaryDataSize;
    void* m_BinaryData;
};


} // end of namespace ToyEngine