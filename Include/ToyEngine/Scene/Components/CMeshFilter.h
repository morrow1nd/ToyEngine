#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Math/Vector3.h"
#include "ToyEngine/Scene/ComponentBase.h"
#include "ToyEngine/Scene/ComponentManagerHelper.h"


namespace ToyEngine
{


using ToyUtility::Vector3;


class CMeshFilter : public ComponentBase
{
public:
    using ListOfVector3 = ToyUtility::List<ToyUtility::Vector3>;
    
    const int GetSubMeshCount() const { return m_SubMeshTriangleIndices.size(); }
    void GetSubMeshInfo(int index, int& beginIndex, int& size);

    const ListOfVector3& GetVertices() const { return m_Vertices; }
    const bool HasNormals() const { return m_Normals.size() > 0; }
    const ListOfVector3& GetNormals() const { return m_Normals; }
    const bool HasTangents() const { return m_Tangents.size() > 0; }
    const ListOfVector3& GetTangents() const { return m_Tangents; }
    const bool HasUVs() const { return m_UVs.size() > 0; }
    const ListOfVector3& GetUVs() const { return m_UVs; }
    const bool HasUVs2() const { return m_UVs2.size() > 0; }
    const ListOfVector3& GetUVs2() const { return m_UVs2; }
    const bool HasUVs3() const { return m_UVs3.size() > 0; }
    const ListOfVector3& GetUVs3() const { return m_UVs3; }
    const bool HasUVs4() const { return m_UVs4.size() > 0; }
    const ListOfVector3& GetUVs4() const { return m_UVs4; }
    const ToyUtility::List<ToyUtility::uint16>& GetTriangles() const { return m_Triangles; }

    void Clear();
    void ClearTriangle() { m_Triangles.clear(); m_SubMeshTriangleIndices.clear(); };

    void PushVertex(const Vector3& vertex) { m_Vertices.push_back(vertex); }
    void PushNormal(const Vector3& normal) { m_Normals.push_back(normal); }
    // ...

    void PushVertices(const ListOfVector3& vertices);

    // Swap contents: swap the contents of m_Vertices and newVertices, and return m_Vertices
    const ListOfVector3& SwapVertices(ListOfVector3& newVertices);
    const ListOfVector3& SwapNormals(ListOfVector3& newNormals);
    const ListOfVector3& SwapTangents(ListOfVector3& newTangents);
    const ListOfVector3& SwapUVs(ListOfVector3& newUVs);
    const ListOfVector3& SwapUVs2(ListOfVector3& newUVs2);
    const ListOfVector3& SwapUVs3(ListOfVector3& newUVs3);
    const ListOfVector3& SwapUVs4(ListOfVector3& newUVs4);
    const ToyUtility::List<ToyUtility::uint16>& SwapAllTriangles(
        ToyUtility::List<ToyUtility::uint16>& newTriangles);

    // Copy contents
    void SetVertices(const ListOfVector3& newVertices) { m_Vertices = newVertices; }
    // ......

    void PushSubMesh(const ToyUtility::List<ToyUtility::uint16>& triangles);


    // Serializable
public:
    virtual void Serialize(ToyUtility::Serializer& serializer) const override;
    virtual void Unserialize(ToyUtility::Unserializer& serializer) override;


private:
    ListOfVector3 m_Vertices;
    ListOfVector3 m_Normals;
    ListOfVector3 m_Tangents;
    ListOfVector3 m_UVs;
    ListOfVector3 m_UVs2;
    ListOfVector3 m_UVs3;
    ListOfVector3 m_UVs4;

    ToyUtility::List<ToyUtility::uint16> m_Triangles;
    ToyUtility::List<int> m_SubMeshTriangleIndices;
};

TE_USING_COMPONENT_MANAGER_HELPER(CMeshFilter);


} // end of namespace ToyEngine