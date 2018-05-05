#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/DesignPattern/IModule.h"
#include "ToyUtility/Event/EventListener.h"


namespace ToyEngine
{


using EngineModuleId = ToyUtility::uint16;


class EngineModule : public ToyUtility::IModule, ToyUtility::EventListener
{
public:
    EngineModule() = delete;

    EngineModule(EngineModuleId id, const ToyUtility::String& name)
        :
        m_ModuleName(name),
        m_Id(id),
        m_HasStartUp(false)
    {}

    virtual ToyUtility::EventListenerType GetListenerType() const override
    {
        return static_cast<ToyUtility::EventListenerType>(m_Id);
    }

    virtual void StartUp() override
    {
        m_HasStartUp = true;
    }

    virtual void ShutDown() override
    {
        m_HasStartUp = false;
    }

    bool IsStarted() const { return m_HasStartUp; }


public:
    const ToyUtility::String& GetName() const { return m_ModuleName; }
    EngineModuleId GetModuleId() const { return m_Id; }


private:
    ToyUtility::String m_ModuleName;
    EngineModuleId m_Id;
    bool m_HasStartUp;
};


} // end of namespace ToyEngine