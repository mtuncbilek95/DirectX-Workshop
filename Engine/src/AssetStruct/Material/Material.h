#pragma once

#include <Core/CoreAPI.h>
#include <Core/Types.h>

using namespace Microsoft::WRL;

namespace Engine
{
    struct Material
    {
        ComPtr<ID3D11PixelShader> PixelShader;
        ComPtr<ID3D11VertexShader> VertexShader;
        ComPtr<ID3D11InputLayout> InputLayout;
    };
}
