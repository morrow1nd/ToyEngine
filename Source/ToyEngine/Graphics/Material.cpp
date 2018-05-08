#include "ToyEngine/Graphics/Material.h"
#include "ToyEngine/Debug/Logger.h"


namespace ToyEngine
{


int Material::GetShaderPropertieCount() const
{
    if(m_Shader == nullptr)
        return 0;

    return m_Shader->GetProperties().size();
}

const ShaderPropertie* Material::GetShaderPropertieInfo(int index) const
{
    if(m_Shader == nullptr)
        return nullptr;

    auto properties = m_Shader->GetProperties();
    int size = properties.size();
    if (index >= 0 && index < size)
    {
        return &m_Shader->GetProperties()[index];
    }

    return nullptr;
}

void Material::SetShaderPropertieValue(int index, const void* data, int copyLength)
{
#if (TOY_ENGINE_MORE_RUNTIME_CHECK)
    if (index < 0 || index >= (int)m_Offsets.size())
    {
        TOY_LOG_ERROR("Argument index({}) out of range({}, {}).", index, 0, m_Offsets.size());
        return;
    }

    if (data == nullptr)
    {
        TOY_LOG_ERROR("data == nullptr");
        return;
    }

#endif

    ToyUtility::uint8* to = ((ToyUtility::uint8*)m_ShaderPropertieValues) + m_Offsets[index];
    ToyUtility::uint8* from = (ToyUtility::uint8*)data;

#if (TOY_ENGINE_MORE_RUNTIME_CHECK)
    int valueLength = GetShaderPropertieValueLength(index);
    if (copyLength > valueLength)
    {
        TOY_LOG_ERROR("Argument error: copyLength({}) > valueLength({})", copyLength, valueLength);

        copyLength = valueLength;
    }
#endif

    // TODO: use memcpy
    for (int i = 0; i < copyLength; ++i)
    {
        to[i] = from[i];
    }
}

const void* Material::GetShaderPropertieValue(int index) const
{
    if (index < 0 || index >= (int)m_Offsets.size())
    {
        return nullptr;
    }

    return ((ToyUtility::uint8*)m_ShaderPropertieValues) + m_Offsets[index];
}

int Material::GetShaderPropertieValueLength(int index) const
{
    int size = m_Offsets.size();

    if (index < 0 || index >= size)
    {
        return 0;
    }

    if (index < size - 1)
    {
        return m_Offsets[index + 1] - m_Offsets[index];
    }
    else
    {
        return m_AllValueLength - m_Offsets.back();
    }
}

void Material::SetShader(ToyUtility::SPtr<Shader> shader)
{
    m_Shader = shader;

    _RecalcShaderPropertieValueOffsets();
}

void Material::_RecalcShaderPropertieValueOffsets()
{
    if (m_Shader == nullptr)
    {
        m_Offsets.clear();
        return;
    }

    auto properties = m_Shader->GetProperties();
    int size = properties.size();
    if (size == 0)
    {
        m_Offsets.clear();
        return;
    }

    m_Offsets.resize(size);
    m_Offsets[0] = 0;
    for (int i = 1; i < size; ++i)
    {
        m_Offsets[i] = m_Offsets[i - 1] + properties[i - 1].GetValueSize();
    }
}


} // end of namespace ToyEngine