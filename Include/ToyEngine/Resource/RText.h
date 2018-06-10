#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyEngine/Resource/Resource.h"
#include "ToyUtility/String/String.h"


namespace ToyEngine
{


class RText : public Resource
{
public:
    RText(bool readOnly)
        :
        Resource(readOnly)
    {}


public:
    virtual ToyEngine::ResourceType ResourceType() const override { return kResourceText; }

    virtual void Copy(HResource dest) override;

    const ToyUtility::String& GetText() const;

    void SetText(const ToyUtility::String& text);


private:
    ToyUtility::String m_Text;
};


} // end of namespace ToyEngine