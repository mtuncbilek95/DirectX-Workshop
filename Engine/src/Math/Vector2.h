// Copyright Metehan Tuncbilek, All Rights Reserved.

/*****************************************************************************************************
 *
 *  This is a standart 2 Dimensional Vector library which is created to use for mathematical, geometric calculations.
 *
 *  Current capabilities:
 *  -   All the operator functions including bool check which is defined as ==.
 *  -   Initialization without defining the elements. (Returns Zero Vector)
 *  -   Length, Normalize, Distance, DotProduct, CrossProduct.
 *  -   Num. (Returns the count of element which is 2 for Vector2)
 *  
 *****************************************************************************************************/

#pragma once

#include "Core/CoreAPI.h"
#include "Core/Types.h"

namespace Engine
{
    template <typename TValue>
    class Vector2
    {
    public:
        //	If it is not initialized, it is zero vector.
        Vector2();
        //	Initialization constructor.
        Vector2(TValue XValue, TValue YValue);

        TValue X;
        TValue Y;

        //	Gives the Distance from origin.
        FORCEINLINE TValue Length() const;

        //	Rates the current vector's each element in between 0 and 1.
        FORCEINLINE Vector2 Normalize();

        //	Gives the Distance of 2 vector points.
        FORCEINLINE static TValue Distance(Vector2& Vec1, Vector2& Vec2);

        //	Scalar multiplication method called Dot Product. Returns TValue.
        FORCEINLINE static TValue DotProduct(Vector2& Vec1, Vector2& Vec2);

        //	2 Dimensional CrossProduct returns the Z value.
        FORCEINLINE static TValue CrossProduct(Vector2& Vec1, Vector2& Vec2);

        //	Gives the Length of the Vector2 which is always equals 2.
        FORCEINLINE static constexpr byte Num();

        //	Vector2 + Vector2. Each element sums with the other vector's related element.
        FORCEINLINE Vector2 operator+(Vector2 Other) const;

        //	Vector2 + TValue. Add each element the TValue parameter.
        FORCEINLINE Vector2 operator+(TValue Other) const;

        //	Vector2 + Vector2. Each element subtracts with the other vector's related element.
        FORCEINLINE Vector2 operator-(Vector2 Other) const;

        //	Vector2 + TValue. Subtract the TValue parameter from each element.
        FORCEINLINE Vector2 operator-(TValue Other) const;

        //	Vector2 * TValue. Multiplies each element with the TValue parameter.
        FORCEINLINE Vector2 operator*(TValue Other) const;

        //	Vector2 * TValue. Divides each element with the TValue parameter.
        FORCEINLINE Vector2 operator/(TValue Other) const;

        //	Vector2 + Vector2. Each element sums with the other vector's related element and overwrites on related Vector2.
        FORCEINLINE Vector2 operator+=(Vector2 Other);

        //	Vector + TValue. Each element sums with the other vector's related element and overwrites on related Vector2.
        FORCEINLINE Vector2 operator+=(TValue Other);

        //	Vector2 - Vector2. Each element sums with the other vector's related element and overwrites on related Vector2.
        FORCEINLINE Vector2 operator-=(Vector2 Other);

        //	Vector - TValue. Each element subtract with the other vector's related element and overwrites on related Vector2.
        FORCEINLINE Vector2 operator-=(TValue Other);

        //	Vector + TValue. Each element multiplies with the other vector's related element and overwrites on related Vector2.
        FORCEINLINE Vector2 operator*=(TValue Other);

        //	Vector / TValue. Each element multiplies with the other vector's related element and overwrites on related Vector2.
        FORCEINLINE Vector2 operator/=(TValue Other);

        //	Boolean that checks if both 2 dimensional Vector
        bool operator ==(Vector2 Other);
    };

    template <typename TValue>
    constexpr byte Vector2<TValue>::Num()
    {
        return 2;
    }

    template <typename TValue>
    Vector2<TValue>::Vector2()
    {
        X = 0;
        Y = 0;
    }

    template <typename TValue>
    Vector2<TValue>::Vector2(TValue XValue, TValue YValue)
    {
        X = XValue;
        Y = YValue;
    }

    template <typename TValue>
    TValue Vector2<TValue>::Length() const
    {
        return sqrt(pow(X, 2) + pow(Y, 2));
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::Normalize()
    {
        return Vector2(X / Length(), Y / Length());
    }

    template <typename TValue>
    TValue Vector2<TValue>::Distance(Vector2& Vec1, Vector2& Vec2)
    {
        return sqrt(pow((Vec2.X - Vec1.X), 2) + pow((Vec2.Y - Vec1.Y), 2));
    }

    template <typename TValue>
    TValue Vector2<TValue>::DotProduct(Vector2& Vec1, Vector2& Vec2)
    {
        return Vec1.X * Vec2.X + Vec1.Y * Vec2.Y;
    }

    template <typename TValue>
    TValue Vector2<TValue>::CrossProduct(Vector2& Vec1, Vector2& Vec2)
    {
        return Vec1.X * Vec2.Y - Vec1.Y * Vec2.X;
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator+(Vector2 Other) const
    {
        return Vector2((X + Other.X), (Y + Other.Y));
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator+(TValue Other) const
    {
        return Vector2((X + Other), (Y + Other));
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator-(Vector2 Other) const
    {
        return Vector2((X - Other.X), (Y - Other.Y));
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator-(TValue Other) const
    {
        return Vector2((X - Other), (Y - Other));
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator*(TValue Other) const
    {
        return Vector2((X * Other), (Y * Other));
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator/(TValue Other) const
    {
        return Vector2((X / Other), (Y / Other));
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator+=(Vector2 Other)
    {
        X += Other.X;
        Y += Other.Y;
        return Vector2(X, Y);
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator+=(TValue Other)
    {
        X += Other;
        Y += Other;
        return Vector2(X, Y);
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator-=(Vector2 Other)
    {
        X -= Other.X;
        Y -= Other.Y;
        return Vector2(X, Y);
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator-=(TValue Other)
    {
        X -= Other;
        Y -= Other;
        return Vector2(X, Y);
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator*=(TValue Other)
    {
        X *= Other;
        Y *= Other;
        return Vector2(X, Y);
    }

    template <typename TValue>
    Vector2<TValue> Vector2<TValue>::operator/=(TValue Other)
    {
        X /= Other;
        Y /= Other;
        return Vector2(X, Y);
    }

    template <typename TValue>
    bool Vector2<TValue>::operator==(Vector2 Other)
    {
        return Other.X == X && Other.Y == Y ? true : false;
    }
}
