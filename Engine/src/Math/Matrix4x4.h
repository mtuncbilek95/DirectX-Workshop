#pragma once

#include <Core/CoreAPI.h>
#include <Core/Types.h>

#include <Math/Math.h>
#include <Math/Vector3.h>

namespace Engine
{
    template <typename TValue>
    class Matrix4x4
    {
    public:
        FORCEINLINE static constexpr Matrix4x4 IdentityMatrix();

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

        FORCEINLINE TValue& operator[](const byte index);

        Matrix4x4(const TValue value);
        Matrix4x4();
        ~Matrix4x4() = default;

    private:
        TValue MatrixArray[16];
    };

    template <typename TValue>
    constexpr Matrix4x4<TValue> Matrix4x4<TValue>::IdentityMatrix()
    {
        return Matrix4x4<TValue>(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::TranslationMatrix(Engine::Vector3<TValue>& translationPos)
    {
        Matrix4x4<TValue> matrix = Matrix4x4<TValue>::IdentityMatrix();

        matrix[12] = translationPos.X;
        matrix[13] = translationPos.Y;
        matrix[14] = translationPos.Z;

        return matrix;
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::RotationX(TValue rotationAngle)
    {
        Matrix4x4<TValue> matrix = Matrix4x4<TValue>::IdentityMatrix();

        matrix[5] = Engine::Math::Cos(rotationAngle);
        matrix[6] = Engine::Math::Sin(rotationAngle);
        matrix[9] = -Engine::Math::Sin(rotationAngle);
        matrix[10] = Engine::Math::Cos(rotationAngle);

        return matrix;
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::RotationY(TValue rotationAngle)
    {
        Matrix4x4<TValue> matrix = Matrix4x4<TValue>::IdentityMatrix();

        matrix[0] = Engine::Math::Cos(rotationAngle);
        matrix[2] = -Engine::Math::Sin(rotationAngle);
        matrix[8] = Engine::Math::Sin(rotationAngle);
        matrix[10] = Engine::Math::Cos(rotationAngle);

        return matrix;
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::RotationZ(TValue rotationAngle)
    {
        Matrix4x4 matrix = Matrix4x4::IdentityMatrix();

        matrix[0] = (3.0f/4.0f) * Engine::Math::Cos(rotationAngle);
        matrix[1] = (3.0f/4.0f) * Engine::Math::Sin(rotationAngle);
        matrix[4] = -Engine::Math::Sin(rotationAngle);
        matrix[5] = Engine::Math::Cos(rotationAngle);

        return matrix;
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::Scale(Engine::Vector3<TValue>& scalePos)
    {
        Matrix4x4<TValue> matrix = Matrix4x4<TValue>::IdentityMatrix();
        matrix[0] = scalePos.X;
        matrix[5] = scalePos.Y;
        matrix[10] = scalePos.Z;
    }

    template <typename TValue>
    Matrix4x4<TValue> Matrix4x4<TValue>::TransformationMatrix(Engine::Vector3<TValue>& transformationPos)
    {
        return Matrix4x4<TValue>();
    }

    template <typename TValue>
    Matrix4x4<TValue>::Matrix4x4(const TValue a11, const TValue a12, const TValue a13, const TValue a14, const TValue a21, const TValue a22, const TValue a23,
                                 const TValue a24, const TValue a31, const TValue a32, const TValue a33, const TValue a34, const TValue a41, const TValue a42,
                                 const TValue a43,
                                 const TValue a44)
    {
        MatrixArray[0] = a11;
        MatrixArray[1] = a12;
        MatrixArray[2] = a13;
        MatrixArray[3] = a14;

        MatrixArray[4] = a21;
        MatrixArray[5] = a22;
        MatrixArray[6] = a23;
        MatrixArray[7] = a24;

        MatrixArray[8] = a31;
        MatrixArray[9] = a32;
        MatrixArray[10] = a33;
        MatrixArray[11] = a34;

        MatrixArray[12] = a41;
        MatrixArray[13] = a42;
        MatrixArray[14] = a43;
        MatrixArray[15] = a44;
    }

    template <typename TValue>
    TValue& Matrix4x4<TValue>::operator[](const byte index)
    {
        return MatrixArray[index];
    }

    template <typename TValue>
    Matrix4x4<TValue>::Matrix4x4(const TValue value)
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            MatrixArray[i] = value;
        }
    }

    template <typename TValue>
    Matrix4x4<TValue>::Matrix4x4()
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            MatrixArray[i] = 0;
        }
    }
}
