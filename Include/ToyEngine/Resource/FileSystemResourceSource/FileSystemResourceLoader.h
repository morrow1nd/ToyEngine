#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Encode/Base64.h"
#include "ToyUtility/FileSystem/FileSystem.h"
#include "ToyUtility/FileSystem/FilePath.h"
#include "ToyUtility/Serialization/Serializer.h"
#include "ToyUtility/Serialization/Unserializer.h"
#include "ToyUtility/Serialization/JsonUnserializer.h"
#include "ToyUtility/DataStream/FileDataStream.h"
#include "TRL/CommonType.h"
#include "ToyEngine/Resource/Resource.h"
#include "ToyEngine/Resource/ResourcePath.h"
#include "ToyEngine/Debug/Logger.h"

#include "ToyEngine/Resource/RBinary.h"
#include "ToyEngine/Resource/RDirectory.h"
#include "ToyEngine/Resource/RMaterial.h"
#include "ToyEngine/Resource/RMesh.h"
#include "ToyEngine/Resource/RShader.h"
#include "ToyEngine/Resource/RText.h"
#include "ToyEngine/Resource/RTexture2D.h"
#include "ToyEngine/Resource/RScene.h"


namespace ToyEngine
{


class FileSystemResourceLoader
{
public:
    void Load(HResource res, ToyUtility::FilePath filePath)
    {
        switch (res->ResourceType())
        {
        case kResourceDirectory:
            LoadRDirectory(res, filePath);
            break;
        case kResourceBinary:
            LoadRBinary(res, filePath);
            break;
        case kResourceText:
            LoadRText(res, filePath);
            break;
        case kResourceMaterial:
            LoadRMaterial(res, filePath);
            break;
        case kResourceMesh:
            LoadRMesh(res, filePath);
            break;
        case kResourceScene:
            LoadRScene(res, filePath);
            break;
        case kResourceShader:
            LoadRShader(res, filePath);
            break;
        case kResourceTexture2D:
            LoadTexture2D(res, filePath);
            break;
        default:
            TOY_LOG_ERROR("unknown ResourceType{}", res->ResourceType());
            break;
        }
    }

    void LoadRDirectory(HResource res, ToyUtility::FilePath filePath)
    {
        auto fh = ToyUtility::FileSystem::Open(filePath.FullPath());
        auto metaFh = ToyUtility::FileSystem::Open(filePath.FullPath() + ".meta");
        if (fh)
        {
            if (metaFh == nullptr)
            {
                // TODOH: regenerate meta file, and log warnning info
            }

            auto metaReader = ToyUtility::FileDataStream(metaFh->CreateInputStream());
            ToyUtility::JsonUnserializer unserializer(metaReader);
            ResourceBasicInfo bisicInfo;
            bisicInfo.Unserialize(unserializer);

            res->SetUUID(bisicInfo.GetUUID());
        }
        else
        {
            TOY_LOG_ERROR("can't find file:{}", filePath.FullPath());
        }
    }

    void LoadRBinary(HResource res, ToyUtility::FilePath filePath)
    {
        auto fh = ToyUtility::FileSystem::Open(filePath.FullPath());
        auto metaFh = ToyUtility::FileSystem::Open(filePath.FullPath() + ".meta");
        if (fh)
        {
            if (metaFh == nullptr)
            {
                // TODOH: regenerate meta file, and log warnning info
            }

            {
                auto metaReader = ToyUtility::FileDataStream(metaFh->CreateInputStream());
                ToyUtility::JsonUnserializer unserializer(metaReader);
                ResourceBasicInfo bisicInfo;
                bisicInfo.Unserialize(unserializer);

                res->SetUUID(bisicInfo.GetUUID());
            }

            {
                auto reader = ToyUtility::FileDataStream(fh->CreateInputStream());
                HResourceCase<RBinary>(res)->SetBinaryData(reader);
            }
        }
        else
        {
            TOY_LOG_ERROR("can't find file:{}", filePath.FullPath());
        }
    }
    void LoadRText(HResource res, ToyUtility::FilePath filePath)
    {
        auto fh = ToyUtility::FileSystem::Open(filePath.FullPath());
        auto metaFh = ToyUtility::FileSystem::Open(filePath.FullPath() + ".meta");
        if (fh)
        {
            if (metaFh == nullptr)
            {
                // TODOH: regenerate meta file, and log warnning info
            }

            {
                auto metaReader = ToyUtility::FileDataStream(metaFh->CreateInputStream());
                ToyUtility::JsonUnserializer unserializer(metaReader);
                ResourceBasicInfo bisicInfo;
                bisicInfo.Unserialize(unserializer);

                res->SetUUID(bisicInfo.GetUUID());
            }

            {
                auto reader = ToyUtility::FileDataStream(fh->CreateInputStream());
                HResourceCase<RText>(res)->SetText(reader.GetAsString());
            }
        }
        else
        {
            TOY_LOG_ERROR("can't find file:{}", filePath.FullPath());
        }
    }

    void LoadRMaterial(HResource res, ToyUtility::FilePath filePath)
    {
        LoadRBinary(res, filePath);

        _GenerateMaterialFromBinaryData(res);
    }
    void LoadRMesh(HResource res, ToyUtility::FilePath filePath);
    void LoadRScene(HResource res, ToyUtility::FilePath filePath)
    {
        LoadRBinary(res, filePath);
    }
    void LoadRShader(HResource res, ToyUtility::FilePath filePath)
    {
        LoadRText(res, filePath);

        _ParserShaderText(res);
    }
    void LoadTexture2D(HResource res, ToyUtility::FilePath filePath)
    {

    }


    void _GenerateMaterialFromBinaryData(HResource resource)
    {
        auto res = HResourceCase<RMaterial>(resource);

        auto material = res->GetMaterial();
        auto reader = res->GetBinaryData();

        ToyUtility::JsonUnserializer unserializer(reader);
        
        ToyUtility::String shaderName;
        unserializer.Pop("Shader", shaderName);

        // TODOH: serach in ResourceLibrary to find this shader, than load this shader

        ToyUtility::String properties;
        unserializer.Pop("Properties", properties);    
        ToyUtility::List<ToyUtility::uint8> propertiesBinaryData;
        ToyUtility::Base64::Decode(properties, propertiesBinaryData);
        material->SetAllShaderPropertieValues(propertiesBinaryData);
    }

    void _ParserShaderText(HResource res)
    {
        // TODOH: 
    }

    void _SerializerHelper(ToyUtility::Serializer& serializer,
        TRL::GpuDataType dataType,
        const void* data,
        const ToyUtility::String& fieldName) const
    {
        switch (dataType)
        {
        case TRL::GpuDataType::GPU_BYTE:
            serializer.Push(*static_cast<const TRL::GpuByte*>(data), fieldName);
            break;
        case TRL::GpuDataType::GPU_UNSIGNED_BYTE:
            serializer.Push(*static_cast<const TRL::GpuUByte*>(data), fieldName);
            break;
        case TRL::GpuDataType::GPU_SHORT:
            serializer.Push(*static_cast<const TRL::GpuShort*>(data), fieldName);
            break;
        case TRL::GpuDataType::GPU_UNSIGNED_SHORT:
            serializer.Push(*static_cast<const TRL::GpuUShort*>(data), fieldName);
            break;
        case TRL::GpuDataType::GPU_INT:
            serializer.Push(*static_cast<const TRL::GpuInt*>(data), fieldName);
            break;
        case TRL::GpuDataType::GPU_UNSIGNED_INT:
            serializer.Push(*static_cast<const TRL::GpuUInt*>(data), fieldName);
            break;
        case TRL::GpuDataType::GPU_HALF_FLOAT:
            serializer.Push(*static_cast<const TRL::GpuHalf*>(data), fieldName);
            break;
        case TRL::GpuDataType::GPU_FLOAT:
            serializer.Push(*static_cast<const TRL::GpuFloat*>(data), fieldName);
            break;
        case TRL::GpuDataType::GPU_FIXED:
            serializer.Push(*static_cast<const TRL::GpuFixed*>(data), fieldName);
            break;
        case TRL::GpuDataType::GPU_FLOAT_VEC2:
            const TRL::GpuFloat* floatVec2 = static_cast<const TRL::GpuFloat*>(data);
            serializer.Push(floatVec2[0], fieldName);
            serializer.Push(floatVec2[1], fieldName);
            break;
            // todo...
        }
    }

    void _UnserializerHelper(ToyUtility::Unserializer& unserializer,
        TRL::GpuDataType dataType,
        void* data,
        const ToyUtility::String& fieldName) const
    {

    }
};


} // end of namespace ToyEngine