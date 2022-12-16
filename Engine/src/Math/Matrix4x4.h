#pragma once

#include <Core/CoreAPI.h>
#include <Core/Types.h>

#include <Math/Vector3.h>

namespace Engine
{
    template <typename TValue>
    class Matrix4x4
    {
    public:
        FORCEINLINE static Matrix4x4 IdentityMatrix();

        FORCEINLINE static Matrix4x4 TranslationMatrix(Engine::Vector3<TValue>& translationPos);
        FORCEINLINE static Matrix4x4 RotationX(TValue rotationAngle);
        FORCEINLINE static Matrix4x4 RotationY(TValue rotationAngle);
        FORCEINLINE static Matrix4x4 RotationZ(TValue rotationAngle);
        FORCEINLINE static Matrix4x4 Scale(Engine::Vector3<TValue>& scalePos);

        FORCEINLINE static Matrix4x4 TransformationMatrix(Engine::Vector3<TValue>& transformationPos);

        Matrix4x4(
            const TValue a11, const TValue a12, const TValue a13, const TValue a14,
            const TValue a21, const TValue a22, const TValue a23, const TValue a24,
            const TValue a31, const TValue a32, const TValue a33, const TValue a34,
            const TValue a41, const TValue a42, const TValue a43, const TValue a44);

        Matrix4x4(const TValue value);
        Matrix4x4();
        ~Matrix4x4() = default;

    private:
        TValue MatrixArray[16];
    };

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::IdentityMatrix()
    {
        return Matrix4x4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::TranslationMatrix(Engine::Vector3<TValue>& translationPos)
    {
        Matrix4x4 matrix = Matrix4x4::IdentityMatrix();

        matrix[12] = translationPos.X;
        matrix[13] = translationPos.Y;
        matrix[14] = translationPos.Z;

        return matrix;
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::RotationX(TValue rotationAngle)
    {
        Matrix4x4 matrix = Matrix4x4::IdentityMatrix();

        matrix[5] = rotationAngle * Engine::Math::Cos(rotationAngle);
        matrix[6] = rotationAngle * Engine::Math::Sin(rotationAngle);
        matrix[9] = -rotationAngle * Engine::Math::Sin(rotationAngle);
        matrix[10] = rotationAngle * Engine::Math::Cos(rotationAngle);

        return matrix;
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::RotationY(TValue rotationAngle)
    {
        Matrix4x4 matrix = Matrix4x4::IdentityMatrix();

        matrix[0] = rotationAngle * Engine::Math::Cos(rotationAngle);
        matrix[2] = -rotationAngle * Engine::Math::Sin(rotationAngle);
        matrix[8] = rotationAngle * Engine::Math::Sin(rotationAngle);
        matrix[10] = rotationAngle * Engine::Math::Cos(rotationAngle);

        return matrix;
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::RotationZ(TValue rotationAngle)
    {
        Matrix4x4 matrix = Matrix4x4::IdentityMatrix();

        matrix[5] = rotationAngle * Engine::Math::Cos(rotationAngle);
        matrix[6] = rotationAngle * Engine::Math::Sin(rotationAngle);
        matrix[9] = -rotationAngle * Engine::Math::Sin(rotationAngle);
        matrix[10] = rotationAngle * Engine::Math::Cos(rotationAngle);

        return matrix;
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::Scale(Engine::Vector3<TValue>& scalePos)
    {
        Matrix4x4 matrix = Matrix4x4::IdentityMatrix();
        matrix[0] = scalePos.X;
        matrix[5] = scalePos.Y;
        matrix[10] = scalePos.Z;
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::TransformationMatrix(Engine::Vector3<TValue>& transformationPos)
    {
        return Matrix4x4();
    }

    template <typename TValue>
    Matrix4x4<TValue>::Matrix4x4(const TValue a11, const TValue a12, const TValue a13, const TValue a14, const TValue a21, const TValue a22, const TValue a23,
                                 const TValue a24, const TValue a31, const TValue a32, const TValue a33, const TValue a34, const TValue a41, const TValue a42,
                                 const TValue a43,
                                 const TValue a44)
    {
    }

    template <typename TValue>
    Matrix4x4<TValue>::Matrix4x4(const TValue value)
    {
#pragma unroll
        for (unsigned int i = 0; i < 16; i++)
        {
            MatrixArray[i] = value;
        }
    }

    template <typename TValue>
    Matrix4x4<TValue>::Matrix4x4()
    {
#pragma unroll
        for (unsigned int i = 0; i < 16; i++)
        {
            MatrixArray[i] = 0;
        }
    }
}
