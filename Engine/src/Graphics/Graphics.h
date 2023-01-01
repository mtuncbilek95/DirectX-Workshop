#pragma once

#include <Core/CoreApi.h>

#include <Math/ColorRGBA.h>
#include <Math/Vector2.h>

using namespace Engine;
using namespace Microsoft::WRL;

class Graphics
{
public:
    Graphics(HWND handle);
    Graphics(const Graphics&) = delete;
    Graphics& operator =(const Graphics&) = delete;
    ~Graphics() = default;

    void Update(float angle);
    void EndFrame() const;

    void ClearBuffer(ColorRGBA<byte> bufferColor);

protected:
    void CreateSwapChain(HWND handle);
    void CreateBackBuffer();
    void InitializeShaders();
    void CreateViewport();
    void CreateInputAssembler(ComPtr<ID3D11Buffer>& VertexBuffer, ComPtr<ID3D11Buffer>& IndexBuffer, ComPtr<ID3D11InputLayout>& InputBuffer);
    void CompileShaders(ComPtr<ID3DBlob>& Blob, ComPtr<ID3DBlob>& ErrorBlob);
    void InitConstantBuffer();

    void CreateBuffer();

    void InitializeBuffer(ComPtr<ID3D11Buffer>& Buffer, int sizeByte, D3D11_BIND_FLAG flag, D3D11_USAGE usage, int sizeStruct, void* data);
private:
    ComPtr<ID3D11Device> DirectDevice;
    ComPtr<IDXGISwapChain> SwapChain;
    ComPtr<ID3D11DeviceContext> DirectContext;
    
    ComPtr<ID3D11RenderTargetView> TargetBuffer;
    
    ComPtr<ID3D11VertexShader> VertexShader;
    ComPtr<ID3D11PixelShader> PixelShader;

    ComPtr<ID3D11Buffer> ConstantBuffer;
    ComPtr<ID3D11Buffer> VertexBuffer;
    ComPtr<ID3D11Buffer> IndexBuffer;

};

struct Vertex
{
    Vector2<float> vec;
    ColorRGBA<byte> color;
};
