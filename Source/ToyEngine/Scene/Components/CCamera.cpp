#include "ToyEngine/Scene/Components/CCamera.h"

#include "ToyUtility/Math/Vector3.h"
#include "ToyUtility/Math/Vector4.h"
#include "ToyUtility/Math/Rect2I.h"
#include "ToyEngine/Engine/Engine.h"


namespace ToyEngine
{


using namespace ToyUtility;


const float CCamera::INFINITE_FAR_PLANE_ADJUST = 0.00001f;

CCamera::CCamera()
    :
    // m_Layers(0xFFFFFFFFFFFFFFFF),
    m_ProjType(ProjectionType::PERSPECTIVE),
    m_HorzFOV(Degree(90.0f)),
    m_FarDist(500.0f),
    m_NearDist(0.05f),
    m_Aspect(1.33333333333333f),
    m_OrthoHeight(5),
    m_Priority(0),
    m_CustomViewMatrix(false),
    m_CustomProjMatrix(false),
    m_MSAA(1),
    m_FrustumExtentsManuallySet(false),
    m_ProjMatrixRS(ToyUtility::TuZero),
    m_ProjMatrix(ToyUtility::TuZero),
    m_ViewMatrix(ToyUtility::TuZero),
    m_ProjMatrixRSInv(ToyUtility::TuZero),
    m_ProjMatrixInv(ToyUtility::TuZero),
    m_ViewMatrixInv(ToyUtility::TuZero),
    m_RecalcFrustum(true),
    m_RecalcFrustumPlanes(true),
    m_RecalcView(true),
    m_Active(true)
{}

void CCamera::SetTransform(const TransformPRS & transform)
{
    m_Transform = transform;

    m_RecalcView = true;
}

void CCamera::SetHorzFOV(const Radian & fov)
{
    m_HorzFOV = fov;
    _InvalidateFrustum();
}

void CCamera::SetNearClipDistance(float nearDist)
{
    if (nearDist <= 0)
    {
        TOY_LOG_ERROR(__FUNCTION__ ": nearDist({}) <= 0. Near clip distance must be greater than zero.",
            nearDist);
        return;
    }

    m_NearDist = nearDist;
    _InvalidateFrustum();
}

void CCamera::SetFarClipDistance(float farDist)
{
    m_FarDist = farDist;
    _InvalidateFrustum();
}

void CCamera::SetAspectRatio(float ratio)
{
    m_Aspect = ratio;
    _InvalidateFrustum();
}

void CCamera::SetFrustumExtents(float left, float right, float top, float bottom)
{
    m_FrustumExtentsManuallySet = true;
    m_Left = left;
    m_Right = right;
    m_Top = top;
    m_Bottom = bottom;

    _InvalidateFrustum();
}

void CCamera::ResetFrustumExtents()
{
    m_FrustumExtentsManuallySet = false;

    _InvalidateFrustum();
}

void CCamera::GetFrustumExtents(float & outleft, float & outright, float & outtop, float & outbottom) const
{
    _UpdateFrustum();

    outleft = m_Left;
    outright = m_Right;
    outtop = m_Top;
    outbottom = m_Bottom;
}

const Matrix4 & CCamera::GetProjectionMatrixRS() const
{
    _UpdateFrustum();

    return m_ProjMatrixRS;
}

const Matrix4 & CCamera::GetProjectionMatrixRSInv() const
{
    _UpdateFrustum();

    return m_ProjMatrixRSInv;
}

const Matrix4 & CCamera::GetProjectionMatrix() const
{
    _UpdateFrustum();

    return m_ProjMatrix;
}

const Matrix4 & CCamera::GetProjectionMatrixInv() const
{
    _UpdateFrustum();

    return m_ProjMatrixInv;
}

const Matrix4 & CCamera::GetViewMatrix() const
{
    _UpdateView();

    return m_ViewMatrix;
}

const Matrix4 & CCamera::GetViewMatrixInv() const
{
    _UpdateView();

    return m_ViewMatrixInv;
}

const ConvexVolume & CCamera::GetFrustum() const
{
    // Make any pending updates to the calculated frustum planes
    _UpdateFrustumPlanes();

    return m_Frustum;
}

ConvexVolume CCamera::GetWorldFrustum() const
{
    const List<Plane>& frustumPlanes = GetFrustum().getPlanes();

    Matrix4 worldMatrix;
    worldMatrix.setTRS(m_Transform.GetPosition(), m_Transform.GetRotation(), Vector3::ONE);

    List<Plane> worldPlanes(frustumPlanes.size());
    uint32 i = 0;
    for (auto& plane : frustumPlanes)
    {
        worldPlanes[i] = worldMatrix.multiplyAffine(plane);
        i++;
    }

    return ConvexVolume(worldPlanes);
}

const AABox & CCamera::GetBoundingBox() const
{
    _UpdateFrustum();

    return m_BoundingBox;
}

void CCamera::SetProjectionType(ProjectionType pt)
{
    m_ProjType = pt;
    _InvalidateFrustum();
    // TODO: _markCoreDirty();
}

void CCamera::SetOrthoWindow(float w, float h)
{
    m_OrthoHeight = h;
    m_Aspect = w / h;

    _InvalidateFrustum();
    // TODO: _makeCoreDirty();
}

void CCamera::SetOrthoWindowHeight(float h)
{
    m_OrthoHeight = h;

    _InvalidateFrustum();
    // TODO: _makeCoreDirty();
}

float CCamera::GetOrthoWindowHeight() const
{
    return m_OrthoHeight;
}

void CCamera::SetOrthoWindowWidth(float w)
{
    m_OrthoHeight = w / m_Aspect;

    _InvalidateFrustum();
    // TODO: _makeCoreDirty();
}

float CCamera::GetOrthoWindowWidth() const
{
    return m_OrthoHeight * m_Aspect;
}

Vector2I CCamera::WorldToScreenPoint(const Vector3 & worldPoint) const
{
    Vector2 ndcPoint = WorldToNdcPoint(worldPoint);
    return NdcToScreenPoint(ndcPoint);
}

Vector2 CCamera::WorldToNdcPoint(const Vector3 & worldPoint) const
{
    Vector3 viewPoint = WorldToViewPoint(worldPoint);
    return ViewToNdcPoint(viewPoint);
}

Vector3 CCamera::WorldToViewPoint(const Vector3 & worldPoint) const
{
    return GetViewMatrix().multiplyAffine(worldPoint);
}

Vector3 CCamera::ScreenToWorldPoint(const Vector2I & screenPoint, float depth) const
{
    Vector2 ndcPoint = ScreenToNdcPoint(screenPoint);
    return NdcToWorldPoint(ndcPoint, depth);
}

Vector3 CCamera::ScreenToWorldPointDeviceDepth(const Vector2I & screenPoint, float deviceDepth) const
{
    Vector2 ndcPoint = ScreenToNdcPoint(screenPoint);
    ToyUtility::Vector4 worldPoint(ndcPoint.x, ndcPoint.y, deviceDepth, 1.0f);
    worldPoint = GetProjectionMatrixRS().inverse().multiply(worldPoint);

    Vector3 worldPoint3D;
    if (ToyUtility::Math::Abs(worldPoint.w) > 1e-7f)
    {
        float invW = 1.0f / worldPoint.w;

        worldPoint3D.x = worldPoint.x * invW;
        worldPoint3D.y = worldPoint.y * invW;
        worldPoint3D.z = worldPoint.z * invW;
    }

    return ViewToWorldPoint(worldPoint3D);
}

Vector3 CCamera::ScreenToViewPoint(const Vector2I & screenPoint, float depth) const
{
    Vector2 ndcPoint = ScreenToNdcPoint(screenPoint);
    return NdcToViewPoint(ndcPoint, depth);
}

Vector2 CCamera::ScreenToNdcPoint(const Vector2I & screenPoint) const
{
    Rect2I viewport = GetViewportRect();

    Vector2 ndcPoint;
    ndcPoint.x = (float)(((screenPoint.x - viewport.x) / (float)viewport.width) * 2.0f - 1.0f);

    // TODO:
    //const RenderAPIInfo& info = RenderAPI::getAPIInfo();
    //if (info.isFlagSet(RenderAPIFeatureFlag::NDCYAxisDown))
    //    ndcPoint.y = (float)(((screenPoint.y - viewport.y) / (float)viewport.height) * 2.0f - 1.0f);
    //else
        ndcPoint.y = (float)((1.0f - ((screenPoint.y - viewport.y) / (float)viewport.height)) * 2.0f - 1.0f);

    return ndcPoint;
}

Vector3 CCamera::ViewToWorldPoint(const Vector3 & viewPoint) const
{
    return GetViewMatrix().inverseAffine().multiplyAffine(viewPoint);
}

Vector2I CCamera::ViewToScreenPoint(const Vector3 & viewPoint) const
{
    Vector2 ndcPoint = ViewToNdcPoint(viewPoint);
    return NdcToScreenPoint(ndcPoint);
}

Vector2 CCamera::ViewToNdcPoint(const Vector3 & viewPoint) const
{
    Vector3 projPoint = ProjectPoint(viewPoint);

    return Vector2(projPoint.x, projPoint.y);
}

Vector3 CCamera::NdcToWorldPoint(const Vector2 & ndcPoint, float depth) const
{
    Vector3 viewPoint = NdcToViewPoint(ndcPoint, depth);
    return ViewToWorldPoint(viewPoint);
}

Vector3 CCamera::NdcToViewPoint(const Vector2 & ndcPoint, float depth) const
{
    return UnprojectPoint(Vector3(ndcPoint.x, ndcPoint.y, depth));
}

Vector2I CCamera::NdcToScreenPoint(const Vector2 & ndcPoint) const
{
    Rect2I viewport = GetViewportRect();

    Vector2I screenPoint;
    screenPoint.x = ToyUtility::Math::RoundToInt(viewport.x + ((ndcPoint.x + 1.0f) * 0.5f) * viewport.width);
    screenPoint.y = ToyUtility::Math::RoundToInt(viewport.y + (1.0f - (ndcPoint.y + 1.0f) * 0.5f) * viewport.height);

    return screenPoint;
}

ToyUtility::Ray CCamera::ScreenPointToRay(const Vector2I & screenPoint) const
{
    Vector2 ndcPoint = ScreenToNdcPoint(screenPoint);

#ifdef near
# undef near
#endif
#ifdef far
# undef far
#endif

    Vector3 near = UnprojectPoint(Vector3(ndcPoint.x, ndcPoint.y, m_NearDist));
    Vector3 far = UnprojectPoint(Vector3(ndcPoint.x, ndcPoint.y, m_NearDist + 1.0f));

    Ray ray(near, Vector3::normalize(far - near));
    ray.transformAffine(GetViewMatrix().inverseAffine());

    return ray;
}


Vector3 CCamera::ProjectPoint(const Vector3 & point) const
{
    Vector4 projPoint4(point.x, point.y, point.z, 1.0f);
    projPoint4 = GetProjectionMatrixRS().multiply(projPoint4);

    if (Math::Abs(projPoint4.w) > 1e-7f)
    {
        float invW = 1.0f / projPoint4.w;
        projPoint4.x *= invW;
        projPoint4.y *= invW;
        projPoint4.z *= invW;
    }
    else
    {
        projPoint4.x = 0.0f;
        projPoint4.y = 0.0f;
        projPoint4.z = 0.0f;
    }

    return Vector3(projPoint4.x, projPoint4.y, projPoint4.z);
}

Vector3 CCamera::UnprojectPoint(const Vector3 & point) const
{
    // Point.z is expected to be in view space, so we need to do some extra work to get the proper coordinates
    // (as opposed to if point.z was in device coordinates, in which case we could just inverse project)

    // Get world position for a point near the far plane (0.95f)
    Vector4 farAwayPoint(point.x, point.y, 0.95f, 1.0f);
    farAwayPoint = GetProjectionMatrixRS().inverse().multiply(farAwayPoint);

    // Can't proceed if w is too small
    if (Math::Abs(farAwayPoint.w) > 1e-7f)
    {
        // Perspective divide, to get the values that make sense in 3D space
        float invW = 1.0f / farAwayPoint.w;

        Vector3 farAwayPoint3D;
        farAwayPoint3D.x = farAwayPoint.x * invW;
        farAwayPoint3D.y = farAwayPoint.y * invW;
        farAwayPoint3D.z = farAwayPoint.z * invW;

        // Find the distance to the far point along the camera's viewing axis
        float distAlongZ = farAwayPoint3D.dot(-Vector3::UNIT_Z);

        // Do nothing if point is behind the camera
        if (distAlongZ >= 0.0f)
        {
            if (m_ProjType == ProjectionType::PERSPECTIVE)
            {
                // Direction from origin to our point
                Vector3 dir = farAwayPoint3D; // Camera is at (0, 0, 0) so it's the same vector

                                              // Our view space depth (point.z) is distance along the camera's viewing axis. Since our direction
                                              // vector is not parallel to the viewing axis, instead of normalizing it with its own length, we
                                              // "normalize" with the length projected along the camera's viewing axis.
                dir /= distAlongZ;

                // And now we just find the final position along the direction
                return dir * point.z;
            }
            else // Ortographic
            {
                // Depth difference between our arbitrary point and actual depth
                float depthDiff = distAlongZ - point.z;

                // Depth difference along viewing direction
                Vector3 depthDiffVec = depthDiff * -Vector3::UNIT_Z;

                // Return point that is depthDiff closer than our arbitrary point
                return farAwayPoint3D - depthDiffVec;
            }
        }
    }

    return Vector3(0.0f, 0.0f, 0.0f);
}

void CCamera::_CalcProjectionParameters(float & left, float & right, float & bottom, float & top) const
{
    if (m_CustomProjMatrix)
    {
        // Convert clipspace corners to camera space
        Matrix4 invProj = m_ProjMatrix.inverse();
        Vector3 topLeft(-0.5f, 0.5f, 0.0f);
        Vector3 bottomRight(0.5f, -0.5f, 0.0f);

        topLeft = invProj.multiply(topLeft);
        bottomRight = invProj.multiply(bottomRight);

        left = topLeft.x;
        top = topLeft.y;
        right = bottomRight.x;
        bottom = bottomRight.y;
    }
    else
    {
        if (m_FrustumExtentsManuallySet)
        {
            left = m_Left;
            right = m_Right;
            top = m_Top;
            bottom = m_Bottom;
        }
        else if (m_ProjType == ProjectionType::PERSPECTIVE)
        {
            Radian thetaX(m_HorzFOV * 0.5f);
            float tanThetaX = std::tan(thetaX.ValueRadians());
            float tanThetaY = tanThetaX / m_Aspect;

            float half_w = tanThetaX * m_NearDist;
            float half_h = tanThetaY * m_NearDist;

            left = -half_w;
            right = half_w;
            bottom = -half_h;
            top = half_h;

            m_Left = left;
            m_Right = right;
            m_Top = top;
            m_Bottom = bottom;
        }
        else
        {
            float half_w = GetOrthoWindowWidth() * 0.5f;
            float half_h = GetOrthoWindowHeight() * 0.5f;

            left = -half_w;
            right = half_w;
            bottom = -half_h;
            top = half_h;

            m_Left = left;
            m_Right = right;
            m_Top = top;
            m_Bottom = bottom;
        }
    }
}

void CCamera::_UpdateFrustum() const
{
    if (_IsFrustumOutOfDate())
    {
        float left, right, bottom, top;

        _CalcProjectionParameters(left, right, bottom, top);

        if (!m_CustomProjMatrix)
        {
            float inv_w = 1 / (right - left);
            float inv_h = 1 / (top - bottom);
            float inv_d = 1 / (m_FarDist - m_NearDist);

            if (m_ProjType == ProjectionType::PERSPECTIVE)
            {
                float A = 2 * m_NearDist * inv_w;
                float B = 2 * m_NearDist * inv_h;
                float C = (right + left) * inv_w;
                float D = (top + bottom) * inv_h;
                float q, qn;

                if (m_FarDist == 0)
                {
                    // Infinite far plane
                    q = INFINITE_FAR_PLANE_ADJUST - 1;
                    qn = m_NearDist * (INFINITE_FAR_PLANE_ADJUST - 2);
                }
                else
                {
                    q = -(m_FarDist + m_NearDist) * inv_d;
                    qn = -2 * (m_FarDist * m_NearDist) * inv_d;
                }

                m_ProjMatrix = Matrix4::ZERO;
                m_ProjMatrix[0][0] = A;
                m_ProjMatrix[0][2] = C;
                m_ProjMatrix[1][1] = B;
                m_ProjMatrix[1][2] = D;
                m_ProjMatrix[2][2] = q;
                m_ProjMatrix[2][3] = qn;
                m_ProjMatrix[3][2] = -1;
            }
            else if (m_ProjType == ProjectionType::ORTHOGRAPHIC)
            {
                float A = 2 * inv_w;
                float B = 2 * inv_h;
                float C = -(right + left) * inv_w;
                float D = -(top + bottom) * inv_h;
                float q, qn;

                if (m_FarDist == 0)
                {
                    // Can not do infinite far plane here, avoid divided zero only
                    q = -INFINITE_FAR_PLANE_ADJUST / m_NearDist;
                    qn = -INFINITE_FAR_PLANE_ADJUST - 1;
                }
                else
                {
                    q = -2 * inv_d;
                    qn = -(m_FarDist + m_NearDist)  * inv_d;
                }

                m_ProjMatrix = Matrix4::ZERO;
                m_ProjMatrix[0][0] = A;
                m_ProjMatrix[0][3] = C;
                m_ProjMatrix[1][1] = B;
                m_ProjMatrix[1][3] = D;
                m_ProjMatrix[2][2] = q;
                m_ProjMatrix[2][3] = qn;
                m_ProjMatrix[3][3] = 1;
            }
        }

        RenderAPI& renderAPI = Engine::Instance().GetModule<RendererManager>()->GetRenderAPI();
        renderAPI.ConvertProjectionMatrix(m_ProjMatrix, m_ProjMatrixRS);
        m_ProjMatrixInv = m_ProjMatrix.inverse();
        m_ProjMatrixRSInv = m_ProjMatrixRS.inverse();

        // Calculate bounding box (local)
        // Box is from 0, down -Z, max dimensions as determined from far plane
        // If infinite view frustum just pick a far value
        float farDist = (m_FarDist == 0) ? 100000 : m_FarDist;

        // Near plane bounds
        Vector3 min(left, bottom, -farDist);
        Vector3 max(right, top, 0);

        if (m_CustomProjMatrix)
        {
            // Some custom projection matrices can have unusual inverted settings
            // So make sure the AABB is the right way around to start with
            Vector3 tmp = min;
            min.floor(max);
            max.ceil(tmp);
        }

        if (m_ProjType == ProjectionType::PERSPECTIVE)
        {
            // Merge with far plane bounds
            float radio = farDist / m_NearDist;
            min.floor(Vector3(left * radio, bottom * radio, -farDist));
            max.ceil(Vector3(right * radio, top * radio, 0));
        }

        m_BoundingBox.setExtents(min, max);

        m_RecalcFrustum = false;
        m_RecalcFrustumPlanes = true;
    }
}

void CCamera::_UpdateFrustumPlanes() const
{
    _UpdateFrustum();

    if (m_RecalcFrustumPlanes)
    {
        m_Frustum = ConvexVolume(m_ProjMatrix);
        m_RecalcFrustumPlanes = false;
    }
}

void CCamera::_UpdateView() const
{
    if (!m_CustomViewMatrix && m_RecalcView)
    {
        m_ViewMatrix.makeView(m_Transform.GetPosition(), m_Transform.GetRotation());
        m_ViewMatrixInv = m_ViewMatrix.inverseAffine();
        m_RecalcView = false;
    }
}

bool CCamera::_IsFrustumOutOfDate() const
{
    return m_RecalcFrustum;
}

void CCamera::_InvalidateFrustum() const
{
    m_RecalcFrustum = true;
    m_RecalcFrustumPlanes = true;
}

void CCamera::Serialize(ToyUtility::Serializer& serializer) const
{
    serializer.BeginDictionary("Camera");
    {
        serializer.Push((int32)m_ProjType, "ProjectionType");
        serializer.Push(m_HorzFOV.ValueDegrees(), "HorzFov");
        serializer.Push(m_FarDist, "FarDist");
        serializer.Push(m_NearDist, "NearDist");
        serializer.Push(m_Aspect, "Aspect");
        serializer.Push(m_OrthoHeight, "OrthoHeight");
        serializer.Push(m_Priority, "Priority");
        serializer.Push(m_Active, "Active");
    }
    serializer.EndDictionary();
}

void CCamera::Unserialize(ToyUtility::Serializer& serializer)
{
}

} // end of namespace ToyEngine