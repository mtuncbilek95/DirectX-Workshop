// Copyright Metehan Tuncbilek, All Rights Reserved.

/*****************************************************************************************************
 *
 *  This is a standart 3 Dimensional Vector library which is created to use for mathematical, geometric calculations.
 *
 *  Current capabilities:
 *  -   All the operator functions including bool check which is defined as ==.
 *  -   Initialization without defining the elements. (Returns Zero Vector)
 *  -   Length, Normalize, Distance, DotProduct, CrossProduct.
 *  -   Num. (Returns the count of element which is 3 for Vector3)
 *  
 *****************************************************************************************************/

#pragma once

#include "Core/CoreAPI.h"
#include "Core/Types.h"

namespace Engine
{
    template <typename TValue>
    class Vector3
    {
    public:
        //	If it is not initialized, it is zero vector.
        Vector3();

        //	Initialization constructor.
        Vector3(TValue XValue, TValue YValue, TValue ZValue);

        TValue X, Y, Z;

        //	Gives the distance from origin.
        FORCEINLINE TValue Length();

        //	Rates the current vector's each element in between 0 and 1.
        FORCEINLINE Vector3 Normalize();

        //	Gives the distance of 2 vector points.
        FORCEINLINE static TValue Distance(Vector3& Vec1, Vector3& Vec2);

        //	Scalar multiplication method called Dot Product. Returns TValue.
        FORCEINLINE static TValue DotProduct(Vector3& Vec1, Vector3& Vec2);

        //	3 Dimensional CrossProduct returns normal vector of given two vectors.
        FORCEINLINE static Vector3 CrossProduct(Vector3& Vec1, Vector3& Vec2);

        //	Gives the size of the Vector3 which is always equals 3.
        FORCEINLINE static constexpr byte Num();

        //	Vector3 + Vector3. Each element sums with the other vector's related element.
        FORCEINLINE Vector3 operator+(Vector3& Other) const;

        //	Vector3 + TValue. Add each element the TValue parameter.
        FORCEINLINE Vector3 operator+(TValue& Other) const;

        //	Vector3 - Vector3. Each element subtracts with the other vector's related element.
        FORCEINLINE Vector3 operator-(Vector3& Other) const;

        //	Vector3 - TValue. Subtract the TValue parameter from each element.
        FORCEINLINE Vector3 operator-(TValue& Other) const;

        //	Vector3 * TValue. Multiplies each element with the TValue parameter.
        FORCEINLINE Vector3 operator*(TValue& Other) const;

        //	Vector3 * TValue. Divides each element with the TValue parameter.
        FORCEINLINE Vector3 operator/(TValue& Other) const;

        //	Vector3 + Vector3. Each element sums with the other vector's related element and overwrites on related Vector3.
        FORCEINLINE Vector3 operator+=(Vector3 Other);

        //	Vector3 + TValue. Each element sums with the other vector's related element and overwrites on related Vector3.
        FORCEINLINE Vector3 operator+=(TValue Other);

        //	Vector3 - Vector3. Each element sums with the other vector's related element and overwrites on related Vector3.
        FORCEINLINE Vector3 operator-=(Vector3 Other);

        //	Vector3 - TValue. Each element subtract with the other vector's related element and overwrites on related Vector3.
        FORCEINLINE Vector3 operator-=(TValue Other);

        //	Vector3 * TValue. Each element multiplies with the other vector's related element and overwrites on related Vector3.
        FORCEINLINE Vector3 operator*=(TValue Other);

        //	Vector3 / TValue. Each element multiplies with the other vector's related element and overwrites on related Vector3.
        FORCEINLINE Vector3 operator/=(TValue Other);

        //	Boolean that checks if both 3 dimensional Vectors are equal.
        FORCEINLINE bool operator==(Vector3 Other);
    };

    template <typename TValue>
    constexpr byte Vector3<TValue>::Num()
    {
        return 3;
    }

    template <typename TValue>
    Vector3<TValue>::Vector3()
    {
        X = Y = Z = 0;
    }

    template <typename TValue>
    Vector3<TValue>::Vector3(TValue XValue, TValue YValue, TValue ZValue)
    {
        X = XValue;
        Y = YValue;
        Z = ZValue;
    }

    template <typename TValue>
    TValue Vector3<TValue>::Length()
    {
        return sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::Normalize()
    {
        return Vector3(X / Length(), Y / Length(), Z / Length());
    }

    template <typename TValue>
    TValue Vector3<TValue>::Distance(Vector3& Vec1, Vector3& Vec2)
    {
        return sqrt(pow((Vec2.X - Vec1.X), 2) + pow((Vec2.Y - Vec1.Y), 2) + pow((Vec2.Z - Vec1.Z), 2));
    }

    template <typename TValue>
    TValue Vector3<TValue>::DotProduct(Vector3& Vec1, Vector3& Vec2)
    {
        return Vec1.X * Vec2.X + Vec1.Y * Vec2.Y + Vec1.Z * Vec2.Z;
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::CrossProduct(Vector3& Vec1, Vector3& Vec2)
    {
        return Vector3((Vec1.Y * Vec2.Z - Vec1.Z * Vec2.Y), (Vec1.X * Vec2.Z - Vec1.Z * Vec2.X),
                       (Vec1.X * Vec2.Y - Vec1.Y * Vec2.X));
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator+(Vector3& Other) const
    {
        return Vector3((X + Other.X), (Y + Other.Y), (Z + Other.Z));
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator+(TValue& Other) const
    {
        return Vector3((X + Other), (Y + Other), (Z + Other));
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator-(Vector3& Other) const
    {
        return Vector3((X - Other.X), (Y - Other.Y), (Z - Other.Z));
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator-(TValue& Other) const
    {
        return Vector3((X - Other), (Y - Other), (Z - Other));
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator*(TValue& Other) const
    {
        return Vector3((X * Other), (Y * Other), (Z * Other));
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator/(TValue& Other) const
    {
        return Vector3((X / Other), (Y / Other), (Z / Other));
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator+=(Vector3 Other)
    {
        X += Other.X;
        Y += Other.Y;
        Z += Other.Z;
        return Vector3(X, Y, Z);
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator+=(TValue Other)
    {
        X += Other;
        Y += Other;
        Z += Other;
        return Vector3(X, Y, Z);
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator-=(Vector3 Other)
    {
        X -= Other.X;
        Y -= Other.Y;
        Z -= Other.Z;
        return Vector3(X, Y, Z);
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator-=(TValue Other)
    {
        X -= Other;
        Y -= Other;
        Z -= Other;
        return Vector3(X, Y, Z);
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator*=(TValue Other)
    {
        X *= Other;
        Y *= Other;
        Z *= Other;
        return Vector3(X, Y, Z);
    }

    template <typename TValue>
    Vector3<TValue> Vector3<TValue>::operator/=(TValue Other)
    {
        X /= Other;
        Y /= Other;
        Z /= Other;
        return Vector3(X, Y, Z);
    }

    template <typename TValue>
    bool Vector3<TValue>::operator==(Vector3 Other)
    {
        return Other.X == X && Other.Y == Y && Other.Z ? true : false;
    }
}
