#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Math/Radian.h"
#include "ToyUtility/Math/Matrix4.h"
#include "ToyUtility/Math/Vector2I.h"
#include "ToyUtility/Math/Vector2.h"
#include "ToyUtility/Math/Vector3.h"
#include "ToyUtility/Math/TransformPRS.h"
#include "ToyUtility/Math/Ray.h"
#include "ToyUtility/Math/AABox.h"
#include "ToyUtility/Math/Rect2I.h"
#include "ToyUtility/Math/ConvexVolume.h"
#include "ToyEngine/Scene/ComponentBase.h"
#include "ToyEngine/Scene/ComponentManagerHelper.h"


namespace ToyEngine
{


using ToyUtility::Vector2;
using ToyUtility::Vector2I;
using ToyUtility::Vector3;
using ToyUtility::Matrix4;
using ToyUtility::Radian;
using ToyUtility::int32;
using ToyUtility::uint8;
using ToyUtility::TransformPRS;


class CCamera : public ComponentBase
{
public:
    CCamera();


public:
    void SetTransform(const TransformPRS& transform);

    /**
    * Determines the camera horizontal field of view. This determines how wide the camera viewing angle is along the
    * horizontal axis. Vertical FOV is calculated from the horizontal FOV and the aspect ratio.
    */
    void SetHorzFOV(const Radian& fov);

    const Radian& GetHorzFOV() const { return m_HorzFOV; }

    /**
    * Determines the distance from the frustum to the near clipping plane. Anything closer than the near clipping plane will
    * not be rendered. Decreasing this value decreases depth buffer precision.
    */
    void SetNearClipDistance(float nearDist);

    float GetNearClipDistance() const { return m_NearDist; }

    /**
    * Determines the distance from the frustum to the far clipping plane. Anything farther than the far clipping plane will
    * not be rendered. Increasing this value decreases depth buffer precision.
    */
    void SetFarClipDistance(float farDist);

    float GetFarClipDistance() const { return m_FarDist; }

    /**	Determines the current viewport aspect ratio (width / height). */
    void SetAspectRatio(float ratio);

    float GetAspectRatio() const { return m_Aspect; }

    /** Manually set the extents of the frustum that will be used when calculating the projection matrix. This will
    * prevents extents for being automatically calculated from aspect and near plane so it is up to the caller to keep
    * these values accurate.
    *
    * @param[in] left		The position where the left clip plane intersect the near clip plane, in view space.
    * @param[in] right		The position where the right clip plane intersect the near clip plane, in view space.
    * @param[in] top		The position where the top clip plane intersect the near clip plane, in view space.
    * @param[in] bottom	The position where the bottom clip plane intersect the near clip plane, in view space.
    */
    void SetFrustumExtents(float left, float right, float top, float bottom);

    /**
    * Resets frustum extents so they are automatically derived from other values. This is only relevant if you have
    * previously set custom extents.
    */
    void ResetFrustumExtents();

    /** Returns the extents of the frustum in view space at the near plane. */
    void GetFrustumExtents(float& outleft, float& outright, float& outtop, float& outbottom) const;

    /**
    * Returns the standard projection matrix that determines how are 3D points projected to two dimensions. The layout
    * of this matrix depends on currently used render system.
    *
    * @note
    * You should use this matrix when sending the matrix to the render system to make sure everything works
    * consistently when other render systems are used.
    */
    const Matrix4& GetProjectionMatrixRS() const;

    /** Returns the inverse of the render-system specific projection matrix. See getProjectionMatrixRS(). */
    const Matrix4& GetProjectionMatrixRSInv() const;

    /**
    * Returns the standard projection matrix that determines how are 3D points projected to two dimensions. Returned
    * matrix is standard following right-hand rules and depth range of [-1, 1]. In case you need a render-system specific
    * projection matrix call getProjectionMatrixRS().
    */
    const Matrix4& GetProjectionMatrix() const;

    /** Returns the inverse of the projection matrix. See getProjectionMatrix(). */
    const Matrix4& GetProjectionMatrixInv() const;

    /** Gets the camera view matrix. Used for positioning/orienting the camera. */
    const Matrix4& GetViewMatrix() const;

    /** Returns the inverse of the view matrix. See getViewMatrix(). */
    const Matrix4& GetViewMatrixInv() const;

    // ... CustomViewMatrix

    /** Returns a convex volume representing the visible area of the camera, in local space. */
    const ToyUtility::ConvexVolume& GetFrustum() const;

    /** Returns a convex volume representing the visible area of the camera, in world space. */
    ToyUtility::ConvexVolume GetWorldFrustum() const;

    /**	Returns the bounding of the frustum. */
    const ToyUtility::AABox& GetBoundingBox() const;
    
    /**	Projection type to use by the camera. */
    enum class ProjectionType
    {
        /** Projection type where object size remains constant and parallel lines remain parallel. */
        ORTHOGRAPHIC,
        /** Projection type that emulates human vision. Objects farther away appear smaller. */
        PERSPECTIVE,
    };

    /**
    * Determines the type of projection used by the camera. Projection type controls how is 3D geometry projected onto a
    * 2D plane.
    */
    void SetProjectionType(ProjectionType pt);

    ProjectionType GetProjectionType() const { return m_ProjType; }

    /**
    * Sets the orthographic window height, for use with orthographic rendering only.
    *
    * @param[in]	w	Width of the window in world units.
    * @param[in]	h	Height of the window in world units.
    *
    * @note
    * Calling this method will recalculate the aspect ratio, use setOrthoWindowHeight() or setOrthoWindowWidth() alone
    * if you wish to preserve the aspect ratio but just fit one or other dimension to a particular size.
    */
    void SetOrthoWindow(float w, float h);

    /**
    * Determines the orthographic window height, for use with orthographic rendering only. The width of the window
    * will be calculated from the aspect ratio. Value is specified in world units.
    */
    void SetOrthoWindowHeight(float h);

    float GetOrthoWindowHeight() const;

    /**
    * Determines the orthographic window width, for use with orthographic rendering only. The height of the window
    * will be calculated from the aspect ratio. Value is specified in world units.
    */
    void SetOrthoWindowWidth(float w);

    float GetOrthoWindowWidth() const;

    // ... Priority, Layer, MSAA, RenderSetting

    /**
    * Converts a point in world space to screen coordinates.
    *
    * @param[in]	worldPoint		3D point in world space.
    * @return						2D point on the render target attached to the camera's viewport, in pixels.
    */
    Vector2I WorldToScreenPoint(const Vector3& worldPoint) const;

    /**
    * Converts a point in world space to normalized device coordinates.
    *
    * @param[in]	worldPoint		3D point in world space.
    * @return						2D point in normalized device coordinates ([-1, 1] range), relative to the camera's viewport.
    */
    Vector2 WorldToNdcPoint(const Vector3& worldPoint) const;

    /**
    * Converts a point in world space to view space coordinates.
    *
    * @param[in]	worldPoint		3D point in world space.
    * @return						3D point relative to the camera's coordinate system.
    */
    Vector3 WorldToViewPoint(const Vector3& worldPoint) const;

    /**
    * Converts a point in screen space to a point in world space.
    *
    * @param[in]	screenPoint	2D point on the render target attached to the camera's viewport, in pixels.
    * @param[in]	depth		Depth to place the world point at, in world coordinates. The depth is applied to the
    *							vector going from camera origin to the point on the near plane.
    * @return					3D point in world space.
    */
    Vector3 ScreenToWorldPoint(const Vector2I& screenPoint, float depth = 0.5f) const;

    /**
    * Converts a point in screen space (pixels corresponding to render target attached to the camera) to a point in
    * world space.
    *
    * @param[in]	screenPoint	Point to transform.
    * @param[in]	deviceDepth	Depth to place the world point at, in normalized device coordinates.
    * @return					3D point in world space.
    */
    Vector3 ScreenToWorldPointDeviceDepth(const Vector2I& screenPoint, float deviceDepth = 0.5f) const;

    /**
    * Converts a point in screen space to a point in view space.
    *
    * @param[in]	screenPoint	2D point on the render target attached to the camera's viewport, in pixels.
    * @param[in]	depth		Depth to place the world point at, in device depth. The depth is applied to the
    *							vector going from camera origin to the point on the near plane.
    * @return					3D point relative to the camera's coordinate system.
    */
    Vector3 ScreenToViewPoint(const Vector2I& screenPoint, float depth = 0.5f) const;

    /**
    * Converts a point in screen space to normalized device coordinates.
    *
    * @param[in]	screenPoint		2D point on the render target attached to the camera's viewport, in pixels.
    * @return						2D point in normalized device coordinates ([-1, 1] range), relative to
    *								the camera's viewport.
    */
    Vector2 ScreenToNdcPoint(const Vector2I& screenPoint) const;

    /**
    * Converts a point in view space to world space.
    *
    * @param[in]	viewPoint		3D point relative to the camera's coordinate system.
    * @return						3D point in world space.
    */
    Vector3 ViewToWorldPoint(const Vector3& viewPoint) const;

    /**
    * Converts a point in view space to screen space.
    *
    * @param[in]	viewPoint		3D point relative to the camera's coordinate system.
    * @return						2D point on the render target attached to the camera's viewport, in pixels.
    */
    Vector2I ViewToScreenPoint(const Vector3& viewPoint) const;

    /**
    * Converts a point in view space to normalized device coordinates.
    *
    * @param[in]	viewPoint		3D point relative to the camera's coordinate system.
    * @return						2D point in normalized device coordinates ([-1, 1] range), relative to
    *								the camera's viewport.
    */
    Vector2 ViewToNdcPoint(const Vector3& viewPoint) const;

    /**
    * Converts a point in normalized device coordinates to world space.
    *
    * @param[in]	ndcPoint	2D point in normalized device coordinates ([-1, 1] range), relative to
    *							the camera's viewport.
    * @param[in]	depth		Depth to place the world point at. The depth is applied to the
    *							vector going from camera origin to the point on the near plane.
    * @return					3D point in world space.
    */
    Vector3 NdcToWorldPoint(const Vector2& ndcPoint, float depth = 0.5f) const;

    /**
    * Converts a point in normalized device coordinates to view space.
    *
    * @param[in]	ndcPoint	2D point in normalized device coordinates ([-1, 1] range), relative to
    *							the camera's viewport.
    * @param[in]	depth		Depth to place the world point at. The depth is applied to the
    *							vector going from camera origin to the point on the near plane.
    * @return					3D point relative to the camera's coordinate system.
    */
    Vector3 NdcToViewPoint(const Vector2& ndcPoint, float depth = 0.5f) const;

    /**
    * Converts a point in normalized device coordinates to screen space.
    *
    * @param[in]	ndcPoint	2D point in normalized device coordinates ([-1, 1] range), relative to
    *							the camera's viewport.
    * @return					2D point on the render target attached to the camera's viewport, in pixels.
    */
    Vector2I NdcToScreenPoint(const Vector2& ndcPoint) const;

    /**
    * Converts a point in screen space to a ray in world space.
    *
    * @param[in]	screenPoint		2D point on the render target attached to the camera's viewport, in pixels.
    * @return						Ray in world space, originating at the selected point on the camera near plane.
    */
    ToyUtility::Ray ScreenPointToRay(const Vector2I& screenPoint) const;

    /**
    * Projects a point in view space to normalized device coordinates. Similar to viewToNdcPoint() but preserves
    * the depth component.
    *
    * @param[in]	point			3D point relative to the camera's coordinate system.
    * @return						3D point in normalized device coordinates ([-1, 1] range), relative to the
    *								camera's viewport. Z value range depends on active render API.
    */
    Vector3 ProjectPoint(const Vector3& point) const;

    /**	Un-projects a point in normalized device space to view space.
    *
    * @param[in]	point			3D point in normalized device coordinates ([-1, 1] range), relative to the
    *								camera's viewport. Z value range depends on active render API.
    * @return						3D point relative to the camera's coordinate system.
    */
    Vector3 UnprojectPoint(const Vector3& point) const;

    static const float INFINITE_FAR_PLANE_ADJUST; /**< Small constant used to reduce far plane projection to avoid inaccuracies. */


private:
    /**	Calculate projection parameters that are used when constructing the projection matrix. */
    void _CalcProjectionParameters(float& left, float& right, float& bottom, float& top) const;

    /**	Recalculate frustum if dirty. */
    void _UpdateFrustum() const;

    /**	Recalculate frustum planes if dirty. */
    void _UpdateFrustumPlanes() const;

    /**
    * Update view matrix from parent position/orientation.
    *
    * @note	Does nothing when custom view matrix is set.
    */
    void _UpdateView() const;

    bool _IsFrustumOutOfDate() const;
    void _InvalidateFrustum() const;

    // TODO
    ToyUtility::Rect2I GetViewportRect() const { return ToyUtility::Rect2I(0, 0, 800, 600); }


    // Serializable
public:
    virtual void Serialize(ToyUtility::Serializer& serializer) const override;
    virtual void UnSerialize(ToyUtility::Serializer& serializer) override;


private:
    // uint64 m_Layers; // Bitfield that can be used for filtering what objects the camera sees

    ProjectionType m_ProjType; /**< Type of camera projection. */
    Radian m_HorzFOV; /**< Horizontal field of view represents how wide is the camera angle. */
    float m_FarDist; /**< Clip any objects further than this. Larger value decreases depth precision at smaller depths. */
    float m_NearDist; /**< Clip any objects close than this. Smaller value decreases depth precision at larger depths. */
    float m_Aspect; /**< Width/height viewport ratio. */
    float m_OrthoHeight; /**< Height in world units used for orthographic cameras. */
    int32 m_Priority; /**< Determines in what order will the camera be rendered. Higher priority means the camera will be rendered sooner. */

    bool m_CustomViewMatrix; /**< Is custom view matrix set. */
    bool m_CustomProjMatrix; /**< Is custom projection matrix set. */
    uint8 m_MSAA; /**< Number of samples to render the scene with. */

    //SPtr<RenderSettings> mRenderSettings; /**< Settings used to control rendering for this camera. */

    bool m_FrustumExtentsManuallySet; /**< Are frustum extents manually set. */

    mutable Matrix4 m_ProjMatrixRS; /**< Cached render-system specific projection matrix. */
    mutable Matrix4 m_ProjMatrix; /**< Cached projection matrix that determines how are 3D points projected to a 2D viewport. */
    mutable Matrix4 m_ViewMatrix; /**< Cached view matrix that determines camera position/orientation. */
    mutable Matrix4 m_ProjMatrixRSInv;
    mutable Matrix4 m_ProjMatrixInv;
    mutable Matrix4 m_ViewMatrixInv;

    mutable ToyUtility::ConvexVolume m_Frustum; /**< Main clipping planes describing cameras visible area. */
    mutable bool m_RecalcFrustum : 1; /**< Should frustum be recalculated. */
    mutable bool m_RecalcFrustumPlanes : 1; /**< Should frustum planes be recalculated. */
    mutable bool m_RecalcView : 1; /**< Should view matrix be recalculated. */
    mutable float m_Left, m_Right, m_Top, m_Bottom; /**< Frustum extents. */
    mutable ToyUtility::AABox m_BoundingBox; /**< Frustum bounding box. */

    // TODO: SceneActor
    TransformPRS m_Transform;
    bool m_Active;
};

TE_USING_COMPONENT_MANAGER_HELPER(CCamera);


} // end of namespace ToyEngine