#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Memory/FrameAllocator.h"
#include "TRL/CommonType.h"


namespace ToyEngine
{


class ShaderName
{
public:
    ShaderName()
    {}

    ShaderName(const ToyUtility::String& name)
    {
        // TODO
        m_Paths.push_back(name);
    }

public:
    const ToyUtility::String& GetFullName() const { return m_Paths[0]; /* TODO */}
    const ToyUtility::List<ToyUtility::String>& GetPaths() const { return m_Paths; }


private:
    ToyUtility::List<ToyUtility::String> m_Paths;
};


enum class ShaderPropertieDataType
{
    NONE = 0,

    Color,
    Texture2D,
    Raw,
};

template<typename AllocatorType>
class ShaderPropertie
{
public:
    ShaderPropertie(AllocatorType& allocator)
        :
        m_InitDataLength(0),
        m_InitData(nullptr),
        m_ArrayLength(1),
        m_Allocator(allocator)
    {}

    ~ShaderPropertie()
    {
        if (m_InitData != nullptr)
        {
            m_Allocator.Free(m_InitData);
            m_InitData = nullptr;
        }
    }

    ShaderPropertie(const ShaderPropertie& sp)
        :
        m_InitDataLength(0), // TODOH
        m_InitData(nullptr),
        m_ArrayLength(sp.m_ArrayLength),
        m_Allocator(sp.m_Allocator)
    {
        // TODO
    }

    ShaderPropertie(ShaderPropertie&& sp)
        :
        m_InitDataLength(0), // TODOH
        m_InitData(nullptr),
        m_ArrayLength(sp.m_ArrayLength),
        m_Allocator(sp.m_Allocator)
    {
        std::swap(m_Name, sp.m_Name);
        std::swap(m_MatName, sp.m_MatName);
        std::swap(m_InitData, sp.m_InitData);
        std::swap(m_InitDataLength, sp.m_InitDataLength);
    }


public:
    const ToyUtility::String& GetName() const { return m_Name; }
    void SetName(const ToyUtility::String& name) { m_Name = name; }
    TRL::GpuDataType GetDataType() const { return m_DataType; }
    void SetDataType(TRL::GpuDataType dataType) { m_DataType = dataType; }
    int GetArrayLength() const { return m_ArrayLength; }
    void SetArrayLength(int arrayLen) { m_ArrayLength = arrayLen; }
    const ToyUtility::String& GetMatName() const { return m_MatName; }
    void SetMatName(const ToyUtility::String& matName) { m_MatName = matName; }
    ShaderPropertieDataType GetMatDataType() const { return m_MatDataType; }
    void SetMatDataType(ShaderPropertieDataType matDataType) { m_MatDataType = matDataType; }
    const void* GetInitData() const { return m_InitData; }
    void SetInitData(const void* initData, int dataLength);

    int GetValueSize() const;


private:
    ToyUtility::String m_Name;
    TRL::GpuDataType m_DataType;
    int m_ArrayLength;
    ToyUtility::String m_MatName;
    ShaderPropertieDataType m_MatDataType;
    void* m_InitData;

    mutable int m_InitDataLength;
    AllocatorType& m_Allocator;
};

class Pass
{
public:
    const ToyUtility::String& GetName() const { return m_Name; }
    void SetName(const ToyUtility::String& name) { m_Name = name; }
    const ToyUtility::String& GetVertexShaderCode() const { return m_VertexShaderCode; }
    void SetVertexShaderCode(const ToyUtility::String& vertexShaderCode) { m_VertexShaderCode = vertexShaderCode; }
    const ToyUtility::String& GetFragShaderCode() const { return m_FragShaderCode; }
    void SetFragShaderCode(const ToyUtility::String& fragShaderCode) { m_FragShaderCode = fragShaderCode; }


private:
    ToyUtility::String m_Name;
    ToyUtility::String m_VertexShaderCode;
    ToyUtility::String m_FragShaderCode;
};

class SubShader
{
public:
    const ToyUtility::String& GetName() const { return m_Name; }
    void SetName(const ToyUtility::String& name) { m_Name = name; }

    const ToyUtility::List<Pass>& GetPasses() const { return m_Passes; } // TODO: remove this
    ToyUtility::List<Pass>& Passes() { return m_Passes; }
    void PushPass(Pass& pass) { m_Passes.push_back(pass); }

private:
    ToyUtility::String m_Name;
    ToyUtility::List<Pass> m_Passes;
};


class Shader
{
public:
    Shader()
        :
        m_FrameAllocator(m_NormalAllocator)
    {}

    ~Shader()
    {
        m_FrameAllocator.Clear();
    }


public:
    using ShaderPropertieType = ShaderPropertie<ToyUtility::FrameAllocator<ToyUtility::NormalAllocator>>;

    const ShaderName& GetName() const { return m_Name; }
    const ShaderName& GetFallback() const { return m_Fallback; }
    const ToyUtility::List<ShaderPropertieType>& GetProperties() const { return m_Properties; }
    const ToyUtility::List<SubShader>& GetSubShaders() const { return m_SubShaders; }

    void SetName(const ShaderName& name) { m_Name = name; }
    void PushPropertie(TRL::GpuDataType dataType, ToyUtility::uint16 arrayLength,
        const ToyUtility::String& variableName,
        const ToyUtility::String& materialName,
        ShaderPropertieDataType materialDataType,
        const void* initValue);
    void PushSubShader(const SubShader& subShader) { m_SubShaders.push_back(subShader); }
    void SetFallback(const ShaderName& name) { m_Fallback = name; }


private:
    ShaderName m_Name;
    ToyUtility::List<ShaderPropertieType> m_Properties;
    ToyUtility::List<SubShader> m_SubShaders;
    ShaderName m_Fallback;

    ToyUtility::NormalAllocator m_NormalAllocator;
    ToyUtility::FrameAllocator<ToyUtility::NormalAllocator> m_FrameAllocator;
};


} // end of namespace ToyEngine