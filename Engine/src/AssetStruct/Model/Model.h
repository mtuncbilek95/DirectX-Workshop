#pragma once

#include <Core/CoreAPI.h>
#include <Containers/Array.h>

#include <AssetStruct/Material/Material.h>
#include <AssetStruct/Mesh/MeshData.h>

#include <AssetStruct/Transformation/Transformation.h>
#include <AssetStruct/Transformation/ConstantBuffer.h>

namespace Engine
{
    class Model
    {
    public:
        Model();
        ~Model();

        void InitializeModel(ComPtr<ID3D11Device>& d11Device);
        void UpdateModel();
        
        ID3D11InputLayout* GetInputLayout() { material.InputLayout.Get(); };
        ID3D11VertexShader* GetVertexShader() { material.VertexShader.Get(); };
        ID3D11PixelShader* GetPixelShader() { material.PixelShader.Get(); };
    
    private:
        Array<MeshData> Vertices;
        Material material;
    
        ComPtr<ID3D11Buffer> VertexBufferPtr;
        ComPtr<ID3D11Buffer> IndexBufferPtr;
        ComPtr<ID3D11Buffer> ConstantBufferPtr;
        
        Transformation transformationMatrix;

        ConstantBuffer constantBuffer;
        
        byte indices[]; 
    };

}
