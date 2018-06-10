#include "ToyEngine/Graphics/Shader.h"
#include "TRL/RenderAPI.h"


namespace ToyEngine
{


template<typename AllocatorType>
void ShaderPropertie<AllocatorType>::SetInitData(const void * initData, int dataLength)
{
    // TODOH: use memcpy

    if (m_InitDataLength < dataLength)
    {
        if (m_InitData != nullptr)
        {
            m_Allocator.Free(m_InitData);
        }

        m_InitData = m_Allocator.Alloc(dataLength + 1);
        m_InitDataLength = dataLength;
    }

    for (int i = 0; i < dataLength; ++i)
    {
        ((char*)m_InitData)[i] = ((char*)initData)[i];
    }
}

template<typename AllocatorType>
int ShaderPropertie<AllocatorType>::GetValueSize() const
{
    int dataSize = TRL::RenderAPI::GetGpuDataTypeSize(m_DataType);
    return dataSize * m_ArrayLength;
}

void ToyEngine::Shader::PushPropertie(TRL::GpuDataType dataType, ToyUtility::uint16 arrayLength,
    const ToyUtility::String & variableName,
    const ToyUtility::String & materialName,
    ShaderPropertieDataType materialDataType,
    const void * initValue)
{
    ShaderPropertieType propertie(m_FrameAllocator);
    propertie.SetArrayLength(arrayLength);
    propertie.SetDataType(dataType);
    propertie.SetName(variableName);
    propertie.SetInitData(initValue, TRL::RenderAPI::GetGpuDataTypeSize(dataType));
    propertie.SetMatName(materialName);
    propertie.SetMatDataType(materialDataType);

    m_Properties.push_back(propertie);
}


} // end of namespace ToyEngine