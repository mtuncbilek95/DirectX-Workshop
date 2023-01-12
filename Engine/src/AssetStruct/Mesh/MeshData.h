#pragma once

#include <Math/Vector3.h>
#include <Math/ColorRGBA.h>

namespace Engine
{
    struct MeshData
    {
        Vector3<float> Position;
        ColorRGBA<byte> Color;
    };
}
