#pragma once

#include <Math/Matrix4x4.h>

namespace Engine
{
    struct Transformation
    {
        Matrix4x4<float> WorldMatrix;
        Matrix4x4<float> TranslationMatrix;
        Matrix4x4<float> ScaleMatrix;
        Matrix4x4<float> RotationMatrix;
    };

}
