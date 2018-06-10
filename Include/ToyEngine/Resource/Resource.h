#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DesignPattern/IUncopyable.h"
#include "ToyUtility/Random/UUID.h"
#include "ToyUtility/Serialization/Serializable.h"
#include "ToyUtility/DesignPattern/RefCounted.h"
#include "ToyEngine/Resource/ResourcePath.h"
#include "ToyEngine/Resource/ResourceHandle.h"


namespace ToyEngine
{


enum ResourceType
{
    kResourceNone,

    kResourceDirectory,

    kResourceBinary,
    kResourceText,
    kResourceScene,
    kResourceMaterial,
    kResourceMesh,
    kResourceShader,
    kResourceTexture2D,
};


class ResourceBasicInfo : public ToyUtility::Serializable
{
public:
    const ToyUtility::UUID& GetUUID() const { return m_UUID; }

    void SetUUID(const ToyUtility::UUID& uuid) { m_UUID = uuid; }

    virtual void Serialize(ToyUtility::Serializer & serializer) const override;
    virtual void Unserialize(ToyUtility::Unserializer & unserializer) override;


private:
    ToyUtility::UUID m_UUID;
};


class Resource :
    public ToyUtility::RefCounted,
    private ToyUtility::IUncopyable
{
public:
    Resource(bool readOnly)
        :
        ToyUtility::IUncopyable(),
        m_Path(""),
        m_Exist(true),
        m_ReadOnly(readOnly),
        m_LoadFinished(false),
        m_Dirty(false)
    {}


public:
    virtual ToyEngine::ResourceType ResourceType() const = 0;

    bool IsSameType(HResource resource) const;

    const ToyUtility::UUID& UUID() const { return m_BasicInfo.GetUUID(); }
    void SetUUID(const ToyUtility::UUID& newUUID) { m_BasicInfo.SetUUID(newUUID); _MarkAsDirty(); }

    const ResourcePath& Path() const { return m_Path; }
    void SetPath(const ResourcePath& path) { m_Path = path; _MarkAsDirty(); }

    bool Exist() const { return m_Exist; }
    void SetExist(bool exist) { m_Exist = exist; _MarkAsDirty(); }

    bool IsWriteable() const { return !m_ReadOnly; }
    bool IsReadOnly() const { return m_ReadOnly; }

    bool IsLoadFinished() const { return m_LoadFinished; }
    void SetLoadFinished(bool loadFinished) { m_LoadFinished = loadFinished; }

    bool IsDirty() const { return m_Dirty; }

    virtual void Copy(HResource dest) = 0;


protected:
    void _MarkAsDirty() { m_Dirty = true; OnDirty(); }
    void _MarkAsUnDirty() { m_Dirty = false; }

    // Called when it's dirty
    virtual void OnDirty() { }


private:
    ResourceBasicInfo m_BasicInfo;
    ResourcePath m_Path;
    bool m_Exist; // TODOM: use a bitset
    bool m_ReadOnly;
    bool m_LoadFinished;
    bool m_Dirty;
};


} // end of namespace ToyEngine