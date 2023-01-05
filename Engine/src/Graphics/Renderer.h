#pragma once

#include <Core/CoreApi.h>

#include <Math/ColorRGBA.h>
#include <Math/Vector2.h>
#include <Containers/Array.h>

#include <Graphics/Data/VertexData.h>
#include <Graphics/DriverTypes.h>

namespace Engine
{
    class Renderer
    {
    public:
        Renderer();
        Renderer(const Renderer&) = delete;
        Renderer& operator =(const Renderer&) = delete;
        ~Renderer();

        //  Initializes create functions in the renderer.
        bool Initialize(HWND handle);
        void RenderFrame();
        void Cleanup();

    protected:
        //  Creates device context.
        bool CreateDeviceContext(DriverTypes typeValue = DriverTypes::Hardware);
        //  Creates swapchain.
        bool CreateSwapChain(HWND handle);
        //  Creates render target view.
        bool CreateRenderTargetView();
        //  Creates input layout.
        bool CreateInputLayout(ComPtr<ID3DBlob>& Blob);
        //  Creates pixel shader.
        bool CreatePixelShader(ComPtr<ID3DBlob>& Blob);
        //  Creates vertex shader.
        bool CreateVertexShader(ComPtr<ID3DBlob>& Blob);

        void InitBuffers();

    private:
        ComPtr<ID3D11Device> DevicePtr;
        ComPtr<IDXGISwapChain> SwapChainPtr;
        ComPtr<ID3D11DeviceContext> ContextPtr;

        ComPtr<ID3D11InputLayout> InputLayoutPtr;
        ComPtr<ID3D11RenderTargetView> RenderTargetViewPtr;

        ComPtr<ID3D11VertexShader> VertexShader;
        ComPtr<ID3D11PixelShader> PixelShader;

        ComPtr<ID3D11Buffer> ConstantBuffer;
        ComPtr<ID3D11Buffer> VertexBuffer;
        ComPtr<ID3D11Buffer> IndexBuffer;

        D3D11_VIEWPORT Viewport;
    };
}
