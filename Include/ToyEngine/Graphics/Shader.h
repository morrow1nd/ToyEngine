#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/List.h"
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

class ShaderPropertie
{
public:
    enum class ShaderPropertieDataType
    {
        NONE = 0,

        Color,
        Texture2D,
        Raw,
    };

public:
    ShaderPropertie()
        :
        m_InitDataLength(0),
        m_InitData(nullptr),
        m_ArrayLength(1)
    {}


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
    void PushPass(Pass& pass) { m_Passes.push_back(pass); }

private:
    ToyUtility::String m_Name;
    ToyUtility::List<Pass> m_Passes;
};


class Shader
{
public:
    Shader(ShaderName& name,
        const ToyUtility::List<ShaderPropertie>& properties,
        const ToyUtility::List<SubShader>& subShaders,
        ShaderName& fallback)
        :
        m_Name(name),
        m_Properties(properties),
        m_SubShaders(subShaders),
        m_Fallback(fallback)
    {}


public:
    const ShaderName& GetName() const { return m_Name; }
    const ShaderName& GetFallback() const { return m_Fallback; }
    const ToyUtility::List<ShaderPropertie>& GetProperties() const { return m_Properties; }
    const ToyUtility::List<SubShader>& GetSubShaders() const { return m_SubShaders; }


private:
    ShaderName m_Name;
    ToyUtility::List<ShaderPropertie> m_Properties;
    ToyUtility::List<SubShader> m_SubShaders;
    ShaderName m_Fallback;
};


} // end of namespace ToyEngine