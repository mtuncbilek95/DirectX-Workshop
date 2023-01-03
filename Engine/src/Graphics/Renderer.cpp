#include "Renderer.h"

#include <FileReader/FileReader.h>
#include <Window/Window.h>

#include <Math/Matrix4x4.h>


Engine::Renderer::Renderer() : DevicePtr(nullptr), SwapChainPtr(nullptr), ContextPtr(nullptr), RenderTargetViewPtr(nullptr)
{
    D3D11_VIEWPORT Viewport;
    Viewport.Width = 800;
    Viewport.Height = 600;
    Viewport.MinDepth = 0;
    Viewport.MaxDepth = 1;
    Viewport.TopLeftX = 0;
    Viewport.TopLeftY = 0;
}

Engine::Renderer::~Renderer()
{
    Cleanup();
}

bool Engine::Renderer::Initialize(HWND handle)
{
    if (!CreateDeviceContext())
        return false;
    if (!CreateSwapChain(handle))
        return false;
    if (!CreateRenderTargetView())
        return false;

    //  I have an issue on InputLayout. Idk why but fuck, I will find it someday.
    
    /*
     *  if (!CreateInputLayout())
     *      return false;
     */
    
    if (!CreatePixelShader())
        return false;
    if (!CreateVertexShader())
        return false;

    return true;
}

void Engine::Renderer::RenderFrame()
{
    const float color[] = {100u / 255.f, 149u / 255.f, 237u / 255.f, 255u / 255.f};
    ContextPtr->ClearRenderTargetView(RenderTargetViewPtr.Get(), color);

    SwapChainPtr->Present(1, 0);
}

void Engine::Renderer::Cleanup()
{
    DevicePtr.Reset();
    SwapChainPtr.Reset();
    ContextPtr.Reset();
    InputLayoutPtr.Reset();
    RenderTargetViewPtr.Reset();
    VertexShader.Reset();
    PixelShader.Reset();
}

bool Engine::Renderer::CreateDeviceContext(DriverTypes typeValue)
{
    D3D_DRIVER_TYPE driverType = {};

    switch (typeValue)
    {
    case DriverTypes::Hardware:
        driverType = D3D_DRIVER_TYPE_HARDWARE;
        break;
    case DriverTypes::Warp:
        driverType = D3D_DRIVER_TYPE_WARP;
        break;
    case DriverTypes::Reference:
        driverType = D3D_DRIVER_TYPE_REFERENCE;
        break;
    case DriverTypes::Software:
        driverType = D3D_DRIVER_TYPE_SOFTWARE;
        break;
    default:
        driverType = D3D_DRIVER_TYPE_HARDWARE;
        break;
    }

    HRESULT hr = D3D11CreateDevice(nullptr, driverType, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
                                   DevicePtr.GetAddressOf(), nullptr, ContextPtr.GetAddressOf());
    if (FAILED(hr))
    {
        printf("Failed to create the device");
        return false;
    }

    return true;
}

bool Engine::Renderer::CreateSwapChain(HWND handle)
{
    DXGI_SWAP_CHAIN_DESC SwapChainDesc;

    //  Swap chain figures out the size of the window by checking window handle
    SwapChainDesc.BufferDesc.Width = 0;
    SwapChainDesc.BufferDesc.Height = 0;

    //  Color Format
    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    //  Refresh rate based on fullscreen
    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 0;

    //  Since we don't specify size, scaling is also unspecified.
    SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

    //  Anti-aliasing
    SwapChainDesc.SampleDesc.Count = 1;
    SwapChainDesc.SampleDesc.Quality = 0;

    //  Pipeline is going to be rendering all of stuff.
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferCount = 2;

    SwapChainDesc.OutputWindow = handle;
    SwapChainDesc.Windowed = true;
    SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    SwapChainDesc.Flags = 0;

    ComPtr<IDXGIDevice> dxgiDevice;

    HRESULT hr = DevicePtr.As(&dxgiDevice);
    if (FAILED(hr))
    {
        printf("Failed to get the DXGI device");
        return false;
    }

    ComPtr<IDXGIAdapter> dxgiAdapter;

    hr = dxgiDevice->GetParent(IID_PPV_ARGS(dxgiAdapter.GetAddressOf()));
    if (FAILED(hr))
    {
        printf("Failed to get the DXGI adapter");
        return false;
    }

    ComPtr<IDXGIFactory> dxgiFactory;

    hr = dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf()));
    if (FAILED(hr))
    {
        printf("Failed to get the DXGI factory");
        return false;
    }

    hr = dxgiFactory->CreateSwapChain(DevicePtr.Get(), &SwapChainDesc, &SwapChainPtr);
    if (FAILED(hr))
    {
        printf("Failed to create the swap chain");
        return false;
    }

    return true;
}

bool Engine::Renderer::CreateRenderTargetView()
{
    ComPtr<ID3D11Texture2D> backBuffer;

    HRESULT hr = SwapChainPtr->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
    if (FAILED(hr))
    {
        printf("Failed to get the back buffer");
        return false;
    }

    hr = DevicePtr->CreateRenderTargetView(backBuffer.Get(), nullptr, &RenderTargetViewPtr);
    if (FAILED(hr))
    {
        printf("Failed to create the render target view");
        return false;
    }

    return true;
}

bool Engine::Renderer::CreateInputLayout()
{
    ComPtr<ID3DBlob> Blob;
    const D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
    {
        {"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 8u, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    HRESULT hr = DevicePtr->CreateInputLayout(InputElementDesc, _countof(InputElementDesc), Blob->GetBufferPointer(),
                                              Blob->GetBufferSize(), &InputLayoutPtr);
    if (FAILED(hr))
    {
        printf("Failed to create the input layout");
        return false;
    }
    return true;
}

bool Engine::Renderer::CreatePixelShader()
{
    ComPtr<ID3DBlob> Blob;
    ComPtr<ID3DBlob> ErrorBlob;

    const string infoPixelShader = FileReader::GetDataFromCurrentDir("src\\HLSL", "PixelShader.hlsl");
    D3DCompile(infoPixelShader.c_str(), infoPixelShader.length(), nullptr, nullptr, nullptr, "main", "ps_4_0",
               D3DCOMPILE_ENABLE_STRICTNESS, 0, &Blob, &ErrorBlob);

    if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
        printf("%s", (char*)ErrorBlob->GetBufferPointer());

    HRESULT hr = DevicePtr->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &PixelShader);

    if (FAILED(hr))
    {
        printf("Failed to create pixel shader");
        return false;
    }

    ContextPtr->PSSetShader(PixelShader.Get(), nullptr, 0u);

    return true;
}

bool Engine::Renderer::CreateVertexShader()
{
    ComPtr<ID3DBlob> Blob;
    ComPtr<ID3DBlob> ErrorBlob;

    const string infoVertexShader = FileReader::GetDataFromCurrentDir("src\\HLSL", "VertexShader.hlsl");
    D3DCompile(infoVertexShader.c_str(), infoVertexShader.length(), nullptr, nullptr, nullptr, "main", "vs_4_0",
               D3DCOMPILE_ENABLE_STRICTNESS, 0, &Blob, &ErrorBlob);

    if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
        printf("%s", (char*)ErrorBlob->GetBufferPointer());

    HRESULT hr = DevicePtr->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &VertexShader);

    if (FAILED(hr))
    {
        printf("Failed to create vertex shader");
        return false;
    }

    ContextPtr->VSSetShader(VertexShader.Get(), nullptr, 0u);

    return true;
}

/*
 *void Engine::Renderer::CreateInputAssembler(ComPtr<ID3D11Buffer>& VertexBuffer, ComPtr<ID3D11Buffer>& IndexBuffer, ComPtr<ID3D11InputLayout>& InputBuffer)
{
    const uint32 stride = sizeof(Vertex);
    const uint32 offset = 0u;
    ContextPtr->IASetVertexBuffers(0u, 1u, VertexBuffer.GetAddressOf(), &stride, &offset);
    ContextPtr->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    ContextPtr->IASetInputLayout(InputBuffer.Get());
    ContextPtr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Engine::Renderer::InitializeShaders()
{
#pragma region "Vertex Buffer"

    D3D11_BUFFER_DESC VertexBufferDesc = {};
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    VertexBufferDesc.CPUAccessFlags = 0;
    VertexBufferDesc.MiscFlags = 0;
    VertexBufferDesc.ByteWidth = sizeof(vertices);
    VertexBufferDesc.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA VertexResourceData = {};
    VertexResourceData.pSysMem = vertices;

    DevicePtr->CreateBuffer(&VertexBufferDesc, &VertexResourceData, &VertexBuffer);

#pragma endregion

#pragma region "Index Buffer"

    D3D11_BUFFER_DESC IndexBufferDesc = {};
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.ByteWidth = sizeof(indices);
    IndexBufferDesc.StructureByteStride = sizeof(uint16);

    D3D11_SUBRESOURCE_DATA IndexResourceData = {};
    IndexResourceData.pSysMem = indices;

    DevicePtr->CreateBuffer(&IndexBufferDesc, &IndexResourceData, &IndexBuffer);

#pragma endregion

#pragma region "Constant Buffer"

    D3D11_BUFFER_DESC ConstantBufferDesc = {};
    ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ConstantBufferDesc.MiscFlags = 0;
    ConstantBufferDesc.ByteWidth = sizeof(cbMatrix);
    ConstantBufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA ConstantResourceData = {};
    ConstantResourceData.pSysMem = &cbMatrix;

    DevicePtr->CreateBuffer(&ConstantBufferDesc, &ConstantResourceData, &ConstantBuffer);
    ContextPtr->VSSetConstantBuffers(0, 1u, ConstantBuffer.GetAddressOf());

#pragma endregion
    
}

void Engine::Renderer::Update(float angle)
{
    cbMatrix = Matrix4x4<float>::RotationZ(angle);

    D3D11_MAPPED_SUBRESOURCE deneme;
    ContextPtr->Map(ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &deneme);
    memcpy(deneme.pData, &cbMatrix, sizeof(cbMatrix));
    ContextPtr->Unmap(ConstantBuffer.Get(), 0);

    ContextPtr->OMSetRenderTargets(1u, RenderTargetViewPtr.GetAddressOf(), nullptr);

    ContextPtr->DrawIndexed(sizeof(indices) / sizeof(uint16), 0u, 0u);
}
 *
 *
 * 
* const Engine::Vertex vertices[] =
{
    {{0.0f, 0.5f}, {0, 255, 0, 0}},
    {{0.5f, -0.5f}, {0, 0, 255, 0}},
    {{-0.5f, -0.5f}, {255, 0, 0, 0}},
    {{0.0f, -1.0f}, {0, 255, 0, 0}},
    {{-0.6f, -0.3f}, {0, 0, 255, 0}},
    {{0.6f, -0.3f}, {255, 0, 0, 0}},
};

const uint16 indices[] = {
    0, 1, 2,
    1, 3, 2,
    2, 4, 0,
    5, 1, 0,
};

Engine::Matrix4x4<float> cbMatrix = Engine::Matrix4x4<float>::RotationZ(0);
 */
