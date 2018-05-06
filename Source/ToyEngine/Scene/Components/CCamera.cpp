#include <cmath>
#include "ToyEngine/Scene/Components/CCamera.h"
#include "ToyEngine/Debug/Logger.h"
#include "ToyEngine/Engine/Engine.h"


namespace ToyEngine
{


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
    // TODO: insert return statement here
}

void CCamera::SetProjectionType(ProjectionType pt)
{
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

        // TODO: m_BoundingBox.setExtents(min, max);

        m_RecalcFrustum = false;
        m_RecalcFrustumPlanes = true;
    }
}

void CCamera::_UpdateView() const
{
    if (!m_CustomViewMatrix && m_RecalcView)
    {
        m_ViewMatrix.makeView()
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

} // end of namespace ToyEngine