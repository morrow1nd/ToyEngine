#pragma once

#include "ToyUtility/Prerequisites/Predefine.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Container/UnorderedMap.h"
#include "ToyEngine/Scene/IComponentManager.h"


namespace ToyEngine
{


#define TE_USING_COMPONENT_MANAGER_HELPER(ComponentTypeName) \
class ComponentTypeName##ComponentManager : public ComponentManagerHelper<ComponentTypeName> { }

#define TE_ICOMPONENT_TO_DERIVED_WITH_CHECK(iterator, DerivedComponentName, VarName)                        \
DerivedComponentName* VarName = nullptr;                                                                    \
{                                                                                                           \
    if(iterator->second == nullptr)                                                                         \
    {                                                                                                       \
        TOY_LOG_ERROR("Component(" #DerivedComponentName ") Manager contains a nullptr item. SO({}).",      \
            iterator->first.GetId());                                                                       \
    }                                                                                                       \
    else                                                                                                    \
    {                                                                                                       \
        VarName = dynamic_cast<DerivedComponentName*>(iterator->second);                                    \
        if (VarName == nullptr)                                                                             \
        {                                                                                                   \
            TOY_LOG_ERROR("dynamic_cast<" #DerivedComponentName "*>(iterator->second) == nullptr. SO({})",  \
                iterator->first.GetId());                                                                   \
        }                                                                                                   \
    }                                                                                                       \
}


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

    virtual bool HasComponent(SceneObject so) const override
    {
        return m_Components.find(so) != m_Components.end();
    }

    virtual int GetComponentCount() const override
    {
        return m_Components.size();
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


public:
    // TODO: maybe we should use List<ComponentType> to contain components, and sorted by SceneObject's id.
    using ContainerType = ToyUtility::UnorderedMap<SceneObject, IComponent*, SceneObjectHasher>;
    

public:
    ContainerType::iterator GetIterator() { return m_Components.begin(); }
    ContainerType::iterator GetIteratorEnd() { return m_Components.end(); }


private:
    ContainerType m_Components;
};


} // end of namespace ToyEngine