#pragma once

#include <Math/Vector2.h>
#include <Math/Vector3.h>

namespace Engine
{
    struct MeshVertex
    {
        Vector3<float> Position;
        Vector2<float> TextureCoords;
        Vector3<float> Normals;
    };
}
