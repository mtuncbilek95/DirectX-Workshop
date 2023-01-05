#pragma once

#include <Core/CoreApi.h>

#include <Math/ColorRGBA.h>
#include <Math/Vector3.h>

namespace Engine
{
    struct Vertex
    {
        Vector3<float> vec;
        ColorRGBA<byte> color;
    };
}
