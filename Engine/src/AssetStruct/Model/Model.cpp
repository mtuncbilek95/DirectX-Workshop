#include "Model.h"

Engine::Model::Model()
{
}

Engine::Model::~Model()
{
}

void Engine::Model::InitializeModel(ComPtr<ID3D11Device>& d11Device)
{
    D3D11_BUFFER_DESC VertexBufferDesc = {};
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    VertexBufferDesc.CPUAccessFlags = 0;
    VertexBufferDesc.MiscFlags = 0;
    VertexBufferDesc.ByteWidth = Vertices.Size();
    VertexBufferDesc.StructureByteStride = sizeof(MeshData);

    D3D11_SUBRESOURCE_DATA VertexResourceData = {};
    VertexResourceData.pSysMem = Vertices.GetSource();

    d11Device->CreateBuffer(&VertexBufferDesc, &VertexResourceData, &VertexBufferPtr);
}

void Engine::Model::UpdateModel()
{
}
