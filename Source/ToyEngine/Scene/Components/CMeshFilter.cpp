#include "ToyEngine/Scene/Components/CMeshFilter.h"
#include "ToyEngineConfig.h"


namespace ToyEngine
{


void CMeshFilter::GetSubMeshInfo(int index, int& beginIndex, int& size)
{
#if (TOY_ENGINE_MORE_RUNTIME_CHECK)
    if (index < 0 || index >= GetSubMeshCount())
    {
        // LogError(...
        beginIndex = 0;
        size = 0;
        return;
    }
#endif

    beginIndex = m_SubMeshTriangleIndices[index];
    int nextSubMeshIndex = beginIndex == m_SubMeshTriangleIndices.size() - 1
        ? m_Triangles.size()
        : m_SubMeshTriangleIndices[index + 1];
    size = nextSubMeshIndex - beginIndex;
}

void CMeshFilter::Clear()
{
    m_Vertices.clear();
    m_Normals.clear();
    m_Tangents.clear();
    m_UVs.clear();
    m_UVs2.clear();
    m_UVs3.clear();
    m_UVs4.clear();
    m_Triangles.clear();
    m_SubMeshTriangleIndices.clear();
}

const CMeshFilter::ListOfVector3& CMeshFilter::SwapVertices(ListOfVector3& newVertices)
{
    m_Vertices.swap(newVertices);
    return m_Vertices;
}

const CMeshFilter::ListOfVector3 & CMeshFilter::SwapNormals(ListOfVector3 & newNormals)
{
    m_Normals.swap(newNormals);
    return m_Normals;
}

const CMeshFilter::ListOfVector3 & CMeshFilter::SwapTangents(ListOfVector3 & newTangents)
{
    m_Tangents.swap(newTangents);
    return m_Tangents;
}

const CMeshFilter::ListOfVector3 & CMeshFilter::SwapUVs(ListOfVector3 & newUVs)
{
    m_UVs.swap(newUVs);
    return m_UVs;
}

const CMeshFilter::ListOfVector3 & CMeshFilter::SwapUVs2(ListOfVector3 & newUVs2)
{
    m_UVs2.swap(newUVs2);
    return m_UVs2;
}

const CMeshFilter::ListOfVector3 & CMeshFilter::SwapUVs3(ListOfVector3 & newUVs3)
{
    m_UVs3.swap(newUVs3);
    return m_UVs3;
}

const CMeshFilter::ListOfVector3 & CMeshFilter::SwapUVs4(ListOfVector3 & newUVs4)
{
    m_UVs4.swap(newUVs4);
    return m_UVs4;
}

const ToyUtility::List<ToyUtility::uint16>& CMeshFilter::SwapAllTriangles(ToyUtility::List<ToyUtility::uint16>& newTriangles)
{
    m_Triangles.swap(newTriangles);
    return m_Triangles;
}

void CMeshFilter::PushSubMesh(const ToyUtility::List<ToyUtility::uint16>& triangles)
{
    m_SubMeshTriangleIndices.push_back(m_Triangles.size());

    auto begin = triangles.cbegin();
    auto end = triangles.cend();
    for (; begin != end; ++begin)
    {
        m_Triangles.push_back(*begin);
    }
}

void CMeshFilter::Serialize(ToyUtility::Serializer & serializer) const
{
}

void CMeshFilter::Unserialize(ToyUtility::Serializer & serializer)
{
}


} // end of namespace ToyEngine