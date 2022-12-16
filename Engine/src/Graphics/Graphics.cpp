#include "Graphics.h"

#include <FileReader/FileReader.h>
#include <Window/Window.h>

const Vertex vertices[] =
{
    {{0.0f, 0.5f}, {0, 255, 0, 0}},
    {{0.5f, -0.5f}, {0, 0, 255, 0}},
    {{-0.5f, -0.5f}, {255, 0, 0, 0}},
    {{0.0f, -0.8f}, {0, 255, 0, 0}},
    {{-0.6f, -0.3f}, {0, 0, 255, 0}},
    {{0.6f, -0.3f}, {255, 0, 0, 0}},
};

const uint16 indices[] = {
    0, 1, 2,
    1, 3, 2,
    2, 4, 0,
    5, 1, 0,
};

Graphics::Graphics(HWND handle)
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

    D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
                                  D3D11_SDK_VERSION, &SwapChainDesc, &SwapChain,
                                  &DirectDevice, nullptr, &DirectContext);
    InitBuffers();
    InitializeShaders();
}

void Graphics::EndFrame() const
{
    SwapChain->Present(1, 0);
}

void Graphics::InitializeViewport()
{
    D3D11_VIEWPORT Viewport;
    Viewport.Width = 800;
    Viewport.Height = 600;
    Viewport.MinDepth = 0;
    Viewport.MaxDepth = 1;
    Viewport.TopLeftX = 0;
    Viewport.TopLeftY = 0;
    DirectContext->RSSetViewports(1u, &Viewport);
}

void Graphics::InitializeInputAssembler(ComPtr<ID3D11Buffer>& VertexBuffer, ComPtr<ID3D11Buffer>& IndexBuffer, ComPtr<ID3D11InputLayout>& InputBuffer)
{
    const uint32 stride = sizeof(Vertex);
    const uint32 offset = 0u;
    DirectContext->IASetVertexBuffers(0u, 1u, VertexBuffer.GetAddressOf(), &stride, &offset);
    DirectContext->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    DirectContext->IASetInputLayout(InputBuffer.Get());
    DirectContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Graphics::InitializeShaders()
{
#pragma region "Vertex Buffer"

    ComPtr<ID3D11Buffer> VertexBuffer;

    D3D11_BUFFER_DESC VertexBufferDesc = {};
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    VertexBufferDesc.CPUAccessFlags = 0;
    VertexBufferDesc.MiscFlags = 0;
    VertexBufferDesc.ByteWidth = sizeof(vertices);
    VertexBufferDesc.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA VertexResourceData = {};
    VertexResourceData.pSysMem = vertices;

    DirectDevice->CreateBuffer(&VertexBufferDesc, &VertexResourceData, &VertexBuffer);

#pragma endregion

#pragma region "Index Buffer"

    ComPtr<ID3D11Buffer> IndexBuffer;

    D3D11_BUFFER_DESC IndexBufferDesc = {};
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.ByteWidth = sizeof(indices);
    IndexBufferDesc.StructureByteStride = sizeof(uint16);

    D3D11_SUBRESOURCE_DATA IndexResourceData = {};
    IndexResourceData.pSysMem = indices;

    DirectDevice->CreateBuffer(&IndexBufferDesc, &IndexResourceData, &IndexBuffer);


#pragma endregion

#pragma region "Shaders Compilation"

    ComPtr<ID3D11VertexShader> VertexShader;
    ComPtr<ID3D11PixelShader> PixelShader;
    ComPtr<ID3DBlob> Blob;
    ComPtr<ID3DBlob> ErrorBlob;


    const string infoPixelShader = FileReader::GetDataFromCurrentDir("src\\HLSL", "PixelShader.hlsl");
    const string infoVertexShader = FileReader::GetDataFromCurrentDir("src\\HLSL", "VertexShader.hlsl");

    D3DCompile(infoPixelShader.c_str(), infoPixelShader.length(), nullptr, nullptr, nullptr, "main", "ps_4_0",
               D3DCOMPILE_ENABLE_STRICTNESS, 0, &Blob, &ErrorBlob);

    if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
        printf("%s", (char*)ErrorBlob->GetBufferPointer());

    DirectDevice->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &PixelShader);
    DirectContext->PSSetShader(PixelShader.Get(), nullptr, 0u);

    D3DCompile(infoVertexShader.c_str(), infoVertexShader.length(), nullptr, nullptr, nullptr, "main", "vs_4_0",
               D3DCOMPILE_ENABLE_STRICTNESS, 0, &Blob, &ErrorBlob);

    if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
        printf("%s", (char*)ErrorBlob->GetBufferPointer());

    DirectDevice->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &VertexShader);
    DirectContext->VSSetShader(VertexShader.Get(), nullptr, 0u);

#pragma endregion

    ComPtr<ID3D11InputLayout> InputBuffer;
    const D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
    {
        {"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 8u, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    DirectDevice->CreateInputLayout(InputElementDesc, (uint32)std::size(InputElementDesc), Blob->GetBufferPointer(),
                                    Blob->GetBufferSize(), &InputBuffer);

    InitializeViewport();
    InitializeInputAssembler(VertexBuffer, IndexBuffer, InputBuffer);
}

void Graphics::Update()
{
    DirectContext->OMSetRenderTargets(1u, TargetBuffer.GetAddressOf(), nullptr);
    ClearBuffer({100u, 149u, 237u, 255u});
    DirectContext->DrawIndexed(sizeof(indices) / sizeof(uint16), 0u, 0u);
}

void Graphics::ClearBuffer(const ColorRGBA<byte> bufferColor)
{
    const float color[] = {bufferColor.Red / 255.f, bufferColor.Green / 255.f, bufferColor.Blue / 255.f, bufferColor.Alpha / 255.f};
    DirectContext->ClearRenderTargetView(TargetBuffer.Get(), color);
}

void Graphics::InitBuffers()
{
    ComPtr<ID3D11Resource> BackBuffer = nullptr;
    SwapChain->GetBuffer(0, IID_PPV_ARGS(BackBuffer.GetAddressOf()));
    DirectDevice->CreateRenderTargetView(BackBuffer.Get(), nullptr, TargetBuffer.GetAddressOf());
    BackBuffer->Release();
}
