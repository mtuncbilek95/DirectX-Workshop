#pragma once

#include <Core/CoreApi.h>

#include <Math/ColorRGBA.h>
#include <Math/Vector2.h>

namespace Engine
{
    struct Vertex
    {
        Vector2<float> vec;
        ColorRGBA<byte> color;
    };
}
