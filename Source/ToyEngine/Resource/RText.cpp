#include "ToyEngine/Resource/RText.h"


namespace ToyEngine
{


void RText::Copy(HResource dest)
{
    if (IsSameType(dest))
    {
        HResourceCase<RText>(dest)->SetText(GetText());
    }
}

const ToyUtility::String& RText::GetText() const
{
    return m_Text;
}

void RText::SetText(const ToyUtility::String & text)
{
    m_Text = text;

    _MarkAsDirty();
}


} // end of namespace ToyEngine