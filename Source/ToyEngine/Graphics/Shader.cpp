#include "ToyEngine/Graphics/Shader.h"
#include "TRL/RenderAPI.h"


namespace ToyEngine
{

void ShaderPropertie::SetInitData(const void * initData, int dataLength)
{
    // TODO: use memcpy. remove new and delete
    
    if (m_InitDataLength < dataLength)
    {
        if (m_InitData != nullptr)
        {
            delete[] m_InitData;
        }

        m_InitData = new char[dataLength + 1];
        m_InitDataLength = dataLength;
    }

    for (int i = 0; i < dataLength; ++i)
    {
        ((char*)m_InitData)[i] = ((char*)initData)[i];
    }
}

int ShaderPropertie::GetValueSize() const
{
    int dataSize = TRL::RenderAPI::GetGpuDataTypeSize(m_DataType);
    return dataSize * m_ArrayLength;
}


} // end of namespace ToyEngine