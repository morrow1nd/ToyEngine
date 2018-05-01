#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/UnorderedMap.h"
#include "ToyUtility/Container/Vector.h"
#include "ToyUtility/Math/Matrix4.h"
#include "ToyUtility/Math/TransformPRS.h"
#include "ToyEngine/Scene/ComponentBase.h"
#include "ToyEngine/Scene/ComponentManagerHelper.h"


namespace ToyEngine
{


using ToyUtility::TransformPRS;
using ToyUtility::Vector3;
using ToyUtility::Quaternion;
using ToyUtility::Matrix4;
using ToyUtility::Radian;


class CTransform : public ComponentBase
{
    /************************************************************************/
    /*                             Transform                                */
    /************************************************************************/
public:
    // Get the TransformPRS object representing object's position/rotation/scale in world space
    const TransformPRS& GetWorldTransform() const;

    const TransformPRS& GetLocalTransform() const { return m_LocalTrfm; }

    // Set the local position of the object
    void SetPosition(const Vector3& position);

    // Set the world position
    void SetWorldPosition(const Vector3& position);

    void SetRotation(const Quaternion& rotation);

    void SetWorldRotation(const Quaternion& rotation);

    void SetScale(const Vector3& scale);

    // Sets the world scale of the object
    // @note    This will not work properly if this object or any of its parents have non-affine transform matrices.
    void SetWorldScale(const Vector3& scale);

    // Orients the object so it is looking at the provided @p location(world space) where @p up is used for
    // determining the location of the object's Y axis.
    void LookAt(const Vector3& location, const Vector3& up = Vector3::UNIT_Y);

    // Gets the objects world transform matrix.
    // @note	Performance warning : This might involve updating the transforms if the transform is dirty.
    const Matrix4& GetWorldMatrix() const;

    // Gets the objects inverse world transform matrix.
    // @note	Performance warning : This might involve updating the transforms if the transform is dirty.
    Matrix4 GetInvWorldMatrix() const;

    // Get the object's local transform matrix
    const Matrix4& GetLocalMatrix() const;

    /**	Moves the object's position by the vector offset provided along world axes. */
    void Move(const Vector3& vec);

    /**	Moves the object's position by the vector offset provided along it's own axes (relative to orientation). */
    void MoveRelative(const Vector3& vec);

    // Rotates the game object so it's forward axis faces the provided direction.
    // @param[in]	forwardDir	The forward direction to face, in world space.
    // @note	Local forward axis is considered to be negative Z.
    void SetForward(const Vector3& forwardDir);

    /**	Rotate the object around an arbitrary axis. */
    void Rotate(const Vector3& axis, const Radian& angle);

    /**	Rotate the object around an arbitrary axis using a Quaternion. */
    void Rotate(const Quaternion& q);

    // Rotates around local Z axis.
    // @param[in]	angle	Angle to rotate by.
    void Roll(const Radian& angle);

    // Rotates around Y axis.
    // @param[in]	angle	Angle to rotate by.
    void Yaw(const Radian& angle);

    // Rotates around X axis
    // @param[in]	angle	Angle to rotate by.
    void Pitch(const Radian& angle);

private:
    TransformPRS                m_LocalTrfm;
    //mutable TransformPRS        m_CachedWorldTrfm;
    //mutable Matrix4             m_CachedLocalTrfmMatrix;
    //mutable Matrix4             m_CachedWorldTrfmMatrix;


    /************************************************************************/
    /* 								Hierarchy	                     		*/
    /************************************************************************/
public:
    // Changes the parent of this object. Also removes the object from the current parent
    // and attach it to the new parent.
    void SetParent(const SceneObject& parent, bool keepWorldTransform = true);

    CTransform* GetParent() const { return m_Parent; }

    CTransform* GetChild(ToyUtility::uint32 index) const;

    ToyUtility::uint32 GetChildrenCount() const { return static_cast<ToyUtility::uint32>(m_Children.size()); }

    CTransform findPath(const ToyUtility::String& path) const;

    CTransform* FindChild(const ToyUtility::String& name, bool recursive = true);

    ToyUtility::List<CTransform*> FindChildren(const ToyUtility::String& name, bool recursive = true);

    //void SetActive(bool active);

    //void GetActive(bool self = false) const;

private:
    CTransform* m_Parent;
    ToyUtility::List<CTransform*> m_Children;
    bool m_ActiveSelf;
    bool m_ActiveHierarchy;
};

USING_COMPONENT_MANAGER_HELPER(CTransform);


} // end of namespace ToyEngine