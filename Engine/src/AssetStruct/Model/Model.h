#pragma once

#include <Core/CoreAPI.h>
#include <Containers/Array.h>

#include <AssetStruct/Material/Material.h>
#include <AssetStruct/Mesh/MeshVertex.h>
#include <AssetStruct/Transformation/Transformation.h>

namespace Engine
{
    class Model
    {
    public:
        Model();
        ~Model();
        
    private:
        Array<MeshVertex> meshVertexData;
        Material material;
    
        ComPtr<ID3D11Buffer> VertexBuffer;
        ComPtr<ID3D11Buffer> IndexBuffer;
        ComPtr<ID3D11Buffer> ConstantBuffer;
        Transformation transformationMatrix;
    };

}
