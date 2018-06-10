#include "ToyEngine/Resource/RBinary.h"


namespace ToyEngine
{


RBinary::~RBinary()
{
    if (m_BinaryData != nullptr)
    {
        delete[] m_BinaryData;
        m_BinaryData = nullptr;
    }
}

void RBinary::Copy(HResource dest)
{
    if (IsSameType(dest))
    {
        HResourceCase<RBinary>(dest)->SetBinaryData(GetBinaryData());
    }
}

ToyUtility::MemoryDataStream RBinary::GetBinaryData() const
{
    return ToyUtility::MemoryDataStream(m_BinaryData, m_BinaryDataSize, false, ToyUtility::DataStream::AccessMode::READ);
}

void RBinary::SetBinaryData(ToyUtility::DataStream& data)
{
    auto size = data.Size();

    _CheckCapacity(size);

    if (size <= m_Capacity)
    {
        data.Seek(0);
        ToyUtility::uint32 readed = 0;
        do
        {
            auto res = data.Read((ToyUtility::uint8*)m_BinaryData + readed, size - readed);
            readed += res;
        } while(readed < size);
    }

    m_BinaryDataSize = size;

    _MarkAsDirty();
}

void RBinary::_CheckCapacity(ToyUtility::uint32 needed)
{
    if (needed > m_Capacity)
    {
        if (m_BinaryData != nullptr)
        {
            delete[] m_BinaryData;
        }

        m_BinaryData = new char[needed];
        m_Capacity = needed;
    }
}


} // end of namespace ToyEngine