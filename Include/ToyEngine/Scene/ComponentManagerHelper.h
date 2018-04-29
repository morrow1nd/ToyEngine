#pragma once

#include "ToyUtility/Prerequisites/Types.h"
#include "ToyUtility/Container/Vector.h"
#include "ToyEngine/Scene/IComponentManager.h"


namespace ToyEngine
{


#define USING_COMPONENT_MANAGER_HELPER(ComponentTypeName) \
class ComponentTypeName##ComponentManager : public ComponentManagerHelper<ComponentTypeName> { }


template<typename ComponentType>
class ComponentManagerHelper : public IComponentManager
{
public:
    virtual IComponent* GetComponent(SceneObject so) override
    {
        auto iter = m_Components.find(so);

        if (iter == m_Components.end())
        {
            return nullptr;
        }

        return iter->second;
    }

    virtual IComponent& AddComponent(SceneObject so) override
    {
        auto component = GetComponent(so);
        if (component != nullptr)
            return *component;

        component = _NewComponent();
        component->Init(so);

        m_Components[so] = component;

        return *component;
    }

    virtual void DestoryComponent(SceneObject so) override
    {
        auto component = GetComponent(so);
        if (component == nullptr)
            return;

        m_Components.erase(so);

        _DeleteComponent(component);
    }

    virtual bool HasComponent(SceneObject so) override
    {
        return m_Components.find(so) != m_Components.end();
    }


private:
    IComponent * _NewComponent()
    {
        return new ComponentType();
    }

    void _DeleteComponent(IComponent* component)
    {
        if (component != nullptr)
        {
            delete component;
        }
    }


private:
    ToyUtility::UnorderedMap<SceneObject, IComponent*, SceneObjectHasher> m_Components;
};


} // end of namespace ToyEngine