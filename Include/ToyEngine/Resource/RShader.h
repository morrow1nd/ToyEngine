#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyEngine/Resource/RText.h"
#include "ToyEngine/Graphics/Shader.h"


namespace ToyEngine
{


class RShader : public RText
{
public:
    RShader(bool readOnly)
        :
        RText(readOnly)
    { }


public:
    virtual ToyEngine::ResourceType ResourceType() const override { return kResourceShader; }

    ToyUtility::SPtr<const Shader> GetShader();


private:
    mutable ToyUtility::SPtr<const Shader> m_Shader;
};


} // end of namespace ToyEngine