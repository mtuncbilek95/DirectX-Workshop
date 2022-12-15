// Copyright Metehan Tuncbilek, All Rights Reserved.

/*****************************************************************************************************
 *
 *  This is a standart 4 Dimensional Vector library which is created to use for mathematical, geometric calculations.
 *
 *  Current capabilities:
 *  -   All the operator functions including bool check which is defined as ==.
 *  -   Initialization without defining the elements. (Returns Zero Vector)
 *  -   Length, Normalize, Distance, DotProduct, CrossProduct.
 *  -   Num. (Returns the count of element which is 4 for Vector4)
 *  
 *****************************************************************************************************/

#pragma once

#include "Core/CoreAPI.h"
#include "Core/Types.h"

namespace Engine
{
    template <typename TValue>
    class Vector4
    {
    public:
        //	If it is not initialized, it is zero vector.
        Vector4();

        //	Initialization constructor.
        Vector4(TValue XValue, TValue YValue, TValue ZValue, TValue WValue);

        TValue X, Y, Z, W;
        //	Gives the distance from origin.
        FORCEINLINE TValue Length();

        //	Rates the current vector's each element in between 0 and 1.
        FORCEINLINE Vector4 Normalize();

        //	Gives the distance of 2 vector points.
        FORCEINLINE static TValue Distance(Vector4& Vec1, Vector4& Vec2);

        //	Scalar multiplication method called Dot Product. Returns TValue.
        FORCEINLINE static TValue DotProduct(Vector4& Vec1, Vector4& Vec2);

        //	Gives the size of the Vector4 which is always equals 4.
        FORCEINLINE static constexpr byte Num();

        //	Vector4 + Vector4. Each element sums with the other vector's related element.
        FORCEINLINE Vector4 operator+(Vector4& Other) const;

        //	Vector4 + TValue. Add each element the TValue parameter.
        FORCEINLINE Vector4 operator+(TValue& Other) const;

        //	Vector4 - Vector4. Each element subtracts with the other vector's related element.
        FORCEINLINE Vector4 operator-(Vector4& Other) const;

        //	Vector4 - TValue. Subtract the TValue parameter from each element.
        FORCEINLINE Vector4 operator-(TValue& Other) const;

        //	Vector4 * TValue. Multiplies each element with the TValue parameter.
        FORCEINLINE Vector4 operator*(TValue& Other) const;

        //	Vector4 * TValue. Divides each element with the TValue parameter.
        FORCEINLINE Vector4 operator/(TValue& Other) const;

        //	Vector4 + Vector4. Each element sums with the other vector's related element and overwrites on related Vector4.
        FORCEINLINE Vector4 operator+=(Vector4 Other);

        //	Vector4 + TValue. Each element sums with the other vector's related element and overwrites on related Vector4.
        FORCEINLINE Vector4 operator+=(TValue Other);

        //	Vector4 - Vector4. Each element sums with the other vector's related element and overwrites on related Vector4.
        FORCEINLINE Vector4 operator-=(Vector4 Other);

        //	Vector4 - TValue. Each element subtract with the other vector's related element and overwrites on related Vector4.
        FORCEINLINE Vector4 operator-=(TValue Other);

        //	Vector4 * TValue. Each element multiplies with the other vector's related element and overwrites on related Vector4.
        FORCEINLINE Vector4 operator*=(TValue Other);

        //	Vector4 / TValue. Each element multiplies with the other vector's related element and overwrites on related Vector4.
        FORCEINLINE Vector4 operator/=(TValue Other);

        //	Boolean that checks if both 4 dimensional Vectors are equal.
        FORCEINLINE bool operator==(Vector4 Other);
    };

    template <typename TValue>
    constexpr byte Vector4<TValue>::Num()
    {
        return 3;
    }

    template <typename TValue>
    Vector4<TValue>::Vector4()
    {
        X = Y = Z = 0;
    }

    template <typename TValue>
    Vector4<TValue>::Vector4(TValue XValue, TValue YValue, TValue ZValue, TValue WValue)
    {
        X = XValue;
        Y = YValue;
        Z = ZValue;
        W = WValue;
    }

    template <typename TValue>
    TValue Vector4<TValue>::Length()
    {
        return sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2) + pow(W, 2));
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::Normalize()
    {
        return Vector4(X / Length(), Y / Length(), Z / Length(), W / Length());
    }

    template <typename TValue>
    TValue Vector4<TValue>::Distance(Vector4& Vec1, Vector4& Vec2)
    {
        return sqrt(pow((Vec2.X - Vec1.X), 2) + pow((Vec2.Y - Vec1.Y), 2) + pow((Vec2.Z - Vec1.Z), 2) + pow((Vec2.W - Vec1.W), 2));
    }

    template <typename TValue>
    TValue Vector4<TValue>::DotProduct(Vector4& Vec1, Vector4& Vec2)
    {
        return Vec1.X * Vec2.X + Vec1.Y * Vec2.Y + Vec1.Z * Vec2.Z;
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator+(Vector4& Other) const
    {
        return Vector4((X + Other.X), (Y + Other.Y), (Z + Other.Z), (W + Other.W));
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator+(TValue& Other) const
    {
        return Vector4((X + Other), (Y + Other), (Z + Other), (W + Other));
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator-(Vector4& Other) const
    {
        return Vector4((X - Other.X), (Y - Other.Y), (Z - Other.Z), (W - Other.W));
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator-(TValue& Other) const
    {
        return Vector4((X - Other), (Y - Other), (Z - Other), (W - Other));
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator*(TValue& Other) const
    {
        return Vector4((X * Other), (Y * Other), (Z * Other), (W * Other));
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator/(TValue& Other) const
    {
        return Vector4((X / Other), (Y / Other), (Z / Other), (W / Other));
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator+=(Vector4 Other)
    {
        X += Other.X;
        Y += Other.Y;
        Z += Other.Z;
        W += Other.W;
        return Vector4(X, Y, Z, W);
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator+=(TValue Other)
    {
        X += Other;
        Y += Other;
        Z += Other;
        W += Other;
        return Vector4(X, Y, Z, W);
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator-=(Vector4 Other)
    {
        X -= Other.X;
        Y -= Other.Y;
        Z -= Other.Z;
        W -= Other.W;
        return Vector4(X, Y, Z, W);
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator-=(TValue Other)
    {
        X -= Other;
        Y -= Other;
        Z -= Other;
        W -= Other;
        return Vector4(X, Y, Z, W);
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator*=(TValue Other)
    {
        X *= Other;
        Y *= Other;
        Z *= Other;
        W *= Other;
        return Vector4(X, Y, Z, W);
    }

    template <typename TValue>
    Vector4<TValue> Vector4<TValue>::operator/=(TValue Other)
    {
        X /= Other;
        Y /= Other;
        Z /= Other;
        W /= Other;
        return Vector4(X, Y, Z, W);
    }

    template <typename TValue>
    bool Vector4<TValue>::operator==(Vector4 Other)
    {
        return Other.X == X && Other.Y == Y && Other.Z == Z && Other.W == W ? true : false;
    }
}
