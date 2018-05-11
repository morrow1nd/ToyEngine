#include "ToyEngine/Scene/Components/CTransform.h"
#include "ToyUtility/Serialization/Serializer.h"
#include "ToyUtility/Serialization/Unserializer.h"
#include "ToyEngineConfig.h"
#include "ToyEngine/Debug/Logger.h"


namespace ToyEngine
{


const TransformPRS & CTransform::GetWorldTransform() const
{
    //if (!IsCachedWorldTfrmUpToDate())
    if(true)
    {
        _UpdateWorldTrfm();
    }

    return m_CachedWorldTrfm;
}

void CTransform::SetPosition(const Vector3 & position)
{
    m_LocalTrfm.SetPosition(position);
    // TODO: notifyTransformChanged
}

void CTransform::SetWorldPosition(const Vector3 & position)
{
    if(m_Parent != nullptr)
        m_LocalTrfm.SetWorldPosition(position, m_Parent->GetWorldTransform());
    else
        m_LocalTrfm.SetPosition(position);

    // TODO: notifyTransformChanged
}

void CTransform::SetRotation(const Quaternion & rotation)
{
    m_LocalTrfm.SetRotation(rotation);
    // TODO: notifyTransformChanged
}

void CTransform::SetWorldRotation(const Quaternion & rotation)
{
    if(m_Parent != nullptr)
        m_LocalTrfm.SetWorldRotation(rotation, m_Parent->GetWorldTransform());
    else
        m_LocalTrfm.SetRotation(rotation);

    // TODO: notifyTransformChanged
}

void CTransform::SetScale(const Vector3 & scale)
{
    m_LocalTrfm.SetScale(scale);

    // TODO: notifyTransformChanged
}

void CTransform::SetWorldScale(const Vector3 & scale)
{
    if(m_Parent != nullptr)
        m_LocalTrfm.SetWorldScale(scale, m_Parent->GetWorldTransform());
    else
        m_LocalTrfm.SetScale(scale);
    // TODO: notifyTransformChanged
}

void CTransform::LookAt(const Vector3 & location, const Vector3 & up)
{
    const TransformPRS& worldTrfm = GetWorldTransform();

    Vector3 forward = location - worldTrfm.GetPosition();

    Quaternion rotation = worldTrfm.GetRotation();
    rotation.lookRotation(forward, up);

    SetWorldRotation(rotation);
}

const Matrix4 & CTransform::GetWorldMatrix() const
{
    //if (!IsCachedWorldTfrmUpToDate())
    if (true)
    {
        _UpdateWorldTrfm();
    }

    return m_CachedWorldTrfmMatrix;
}

Matrix4 CTransform::GetInverseWorldMatrix() const
{
    //if (!IsCachedWorldTfrmUpToDate())
    if (true)
    {
        _UpdateWorldTrfm();
    }

    Matrix4 worldToLocal = m_CachedWorldTrfm.GetInverseMatrix();
    return worldToLocal;
}

const Matrix4 & CTransform::GetLocalMatrix() const
{
    //if (!IsCachedLocalTfrmUpToDate())
    if (true)
    {
        _UpdateLocalTrfm();
    }

    return m_CachedLocalTrfmMatrix;
}

void CTransform::Move(const Vector3 & vec)
{
    m_LocalTrfm.Move(vec);
    // TODO: notifyTransformChanged
}

void CTransform::MoveRelative(const Vector3 & vec)
{
    m_LocalTrfm.MoveRelative(vec);

    // TODO: notifyTransformChanged
}

void CTransform::SetForward(const Vector3 & forwardDir)
{
    const TransformPRS& worldTrfm = GetWorldTransform();

    Quaternion currRotation = worldTrfm.GetRotation();
    currRotation.lookRotation(forwardDir);
    SetWorldRotation(currRotation);
}

void CTransform::Rotate(const Vector3 & axis, const Radian & angle)
{
    m_LocalTrfm.Rotate(axis, angle);
    // TODO: notifyTransformChanged
}

void CTransform::Rotate(const Quaternion & q)
{
    m_LocalTrfm.Rotate(q);
    // TODO: notifyTransformChanged
}

void CTransform::Roll(const Radian & angle)
{
    m_LocalTrfm.Roll(angle);
    // TODO: notifyTransformChanged
}

void CTransform::Yaw(const Radian & angle)
{
    m_LocalTrfm.Yaw(angle);
    // TODO: notifyTransformChanged
}

void CTransform::Pitch(const Radian & angle)
{
    m_LocalTrfm.Pitch(angle);
    // TODO: notifyTransformChanged
}

void CTransform::SetParent(CTransform & parent, bool keepWorldTransform)
{
    //if (parent.IsDestoryed())
    //{
    //    return;
    //}

    if(SO() == parent.SO())
        return;

    if (m_Parent == nullptr || m_Parent != nullptr)
    {
        TransformPRS worldTrfm;

        if(keepWorldTransform)
            worldTrfm = GetWorldTransform();

        if(m_Parent != nullptr)
            m_Parent->_RemoveChild(*this);

        parent._AddChild(*this);

        m_Parent = &parent;

        if (keepWorldTransform)
        {
            m_LocalTrfm = worldTrfm;

            if (m_Parent != nullptr)
            {
                m_LocalTrfm.MakeLocal(m_Parent->GetWorldTransform());
            }
        }

        // TODO: notifyTransformChanged((TransformChangedFlags)(TCF_Parent | TCF_Transform));
    }
}

CTransform * CTransform::GetChild(ToyUtility::uint32 index) const
{
    if (index >= m_Children.size())
    {
        TOY_LOG_ERROR("CTransform::GetChild argument index({}) >= m_Children.size()({})",
            index, m_Children.size());

        return nullptr;
    }

    return m_Children[index];
}

CTransform* CTransform::findPath(const ToyUtility::String & path) const
{
    if(path.empty())
        return nullptr;

    TOY_LOG_ERROR("Function CTransform::findPath is not impled");

    // TODO:

    return nullptr;
}

CTransform * CTransform::FindChild(const ToyUtility::String & name, bool recursive)
{
    for (auto& child : m_Children)
    {
        if (child->GetName() == name)
        {
            return child;
        }
    }

    if (recursive)
    {
        for (auto& child : m_Children)
        {
            auto res = child->FindChild(name, true);
            if(res != nullptr)
                return res;
        }
    }

    return nullptr;
}

ToyUtility::List<CTransform*> CTransform::FindChildren(const ToyUtility::String & name, bool recursive)
{
    std::function<void(const CTransform*, ToyUtility::List<CTransform*>&)> findChildrenInternal =
        [&] (const CTransform* root, ToyUtility::List<CTransform*>& output)
    {
        for (auto& child : root->m_Children)
        {
            if (child->GetName() == name)
                output.push_back(child);
        }

        if (recursive)
        {
            for (auto& child : root->m_Children)
                findChildrenInternal(child, output);
        }
    };

    ToyUtility::List<CTransform*> output;
    findChildrenInternal(this, output);

    return output;
}

void CTransform::_RemoveChild(CTransform& object)
{
    auto res = std::find(m_Children.begin(), m_Children.end(), &object);

    if (res != m_Children.end())
    {
        m_Children.erase(res);
    }
    else
    {
        TOY_LOG_ERROR("CTransform::_RemoveChild: Trying to remove a child but it's not a child of this "
            "transform");
    }
}

void CTransform::_AddChild(CTransform& object)
{
    m_Children.push_back(&object);
    // TODO: object->_SetFlags(mFlags);
}

void CTransform::_UpdateWorldTrfm() const
{
    m_CachedWorldTrfm = m_LocalTrfm;

    if (m_Parent != nullptr)
    {
        m_CachedWorldTrfm.MakeWorld(m_Parent->GetWorldTransform());

        m_CachedWorldTrfmMatrix = m_CachedWorldTrfm.GetMatrix();
    }
    else
    {
        m_CachedWorldTrfmMatrix = GetLocalMatrix();
    }

    // TODO: Set Dirty flag
}

void CTransform::_UpdateLocalTrfm() const
{
    m_CachedLocalTrfmMatrix = m_LocalTrfm.GetMatrix();
    // TODO: Set Dirty flag
}

void CTransform::Serialize(ToyUtility::Serializer & serializer) const
{
    serializer.BeginDictionary("Transform");
    {
        serializer.Push(SO().GetId(), "Id");

        m_LocalTrfm.Serialize(serializer);

        ToyUtility::uint32 parentId = 0;
        if (m_Parent != nullptr)
        {
            parentId = m_Parent->SO().GetId();
        }
        serializer.Push(parentId, "parent");

        serializer.BeginDictionary("children");
        {
            serializer.Push((ToyUtility::uint32)m_Children.size(), "size");

            for (int i = 0; i < m_Children.size(); ++i)
            {
                //if (m_Children[i] != nullptr)
                //{
                    serializer.Push(m_Children[i]->SO().GetId());
                //}
            }
        }
        serializer.EndDictionary();

        serializer.Push(m_ActiveSelf, "activeSelf");
        serializer.Push(m_ActiveHierarchy, "activeHierarchy");
    }
    serializer.EndDictionary();
}

void CTransform::Unserialize(ToyUtility::Unserializer & unserializer)
{
    unserializer.BeginDictionary("Transform");
    {
        SceneObject::IdType id;
        unserializer.Pop("Id", id); // We don't use it here

        m_LocalTrfm.Unserialize(unserializer);

        SceneObject::IdType parentId = 0;
        unserializer.Pop("parent", parentId); // We don't use it here

        unserializer.BeginDictionary("children");
        {
            ToyUtility::uint32 childrenSize = 0;
            unserializer.Pop("size", childrenSize);

            ToyUtility::uint32 id = 0;
            for (int i = 0; i < childrenSize; ++i)
            {
                unserializer.Pop("", id); // We don't use it here
            }
        }
        unserializer.EndDictionary();

        unserializer.Pop("activeSelf", m_ActiveSelf);
        unserializer.Pop("activeHierarchy", m_ActiveHierarchy);
    }
    unserializer.EndDictionary();
}


} // end of namespace ToyEngine