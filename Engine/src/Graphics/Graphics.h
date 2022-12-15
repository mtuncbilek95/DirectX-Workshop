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

    void EndFrame() const;
    void ClearBuffer(ColorRGBA<byte> bufferColor);

    void InitializeShaders();
    void Update();
protected:
    void InitBuffers();
    
private:
    ComPtr<ID3D11Device> DirectDevice = nullptr;
    ComPtr<IDXGISwapChain> SwapChain = nullptr;
    ComPtr<ID3D11DeviceContext> DirectContext = nullptr;
    ComPtr<ID3D11RenderTargetView> TargetBuffer = nullptr;
    D3D11_VIEWPORT Viewport;
};

struct Vertex
{
    Vector2<float> vec;
    ColorRGBA<byte> color;
};