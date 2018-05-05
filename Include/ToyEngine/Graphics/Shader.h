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
    }

public:
    const ToyUtility::String& GetFullName() const;
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


private:
    ToyUtility::String m_Name;
    TRL::GpuDataType m_DataType;
    ToyUtility::String m_MatName;
    ShaderPropertieDataType m_MatDataType;
    void* m_InitData;
};

class Pass
{
public:


private:
    ToyUtility::String m_Name;
    ToyUtility::String m_VertexShaderCode;
    ToyUtility::String m_FragShaderCode;
};

class SubShader
{
public:

private:
    ToyUtility::String m_Name;
    ToyUtility::List<Pass> m_Passes;
};


class Shader
{
public:
    Shader(ShaderName& name,
        ToyUtility::List<ShaderPropertie>& properties,
        ToyUtility::List<SubShader>& subShaders,
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