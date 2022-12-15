// Copyright Metehan Tuncbilek, All Rights Reserved.

/*****************************************************************************************************
 *
 *  This is a standart 3 Color and 1 Alpha RGBA library which is created to use for Shader and Color calculations.
 *
 *  Current capabilities:
 *  -   All the operator functions including bool check which is defined as ==.
 *  -   Initialization without defining the elements. (Returns Non-Transparent Black)
 *  -   Length, Normalize, Distance, DotProduct, CrossProduct.
 *  -   Num. (Returns the count of element which is 4 for RGBA)
 *
 *  W.I.P Features:
 *  -   RGBA
 *  -   More Mathematical calculations.
 *  
 *****************************************************************************************************/

#pragma once

#include "Core/CoreAPI.h"
#include "Core/Types.h"

namespace Engine
{
    template <typename TValue>
    class ColorRGBA
    {
    public:
        //	If it is not initialized, it is zero vector.
        ColorRGBA();

        //	Initialization constructor.
        ColorRGBA(TValue RedValue, TValue GreenValue, TValue BlueValue, TValue AlphaValue);

        TValue Red, Green, Blue, Alpha;
        
        //	Gives the distance from origin.
        FORCEINLINE float Length();

        //	Rates the current vector's each element in between 0 and 1.
        FORCEINLINE ColorRGBA<float> Normalize();

        //	Gives the distance of 2 vector points.
        FORCEINLINE static TValue Distance(ColorRGBA& Vec1, ColorRGBA& Vec2);

        //	Scalar multiplication method called Dot Product. Returns TValue.
        FORCEINLINE static TValue DotProduct(ColorRGBA& Vec1, ColorRGBA& Vec2);

        //	Gives the size of the ColorRGBA which is always equals 4.
        FORCEINLINE static constexpr byte Num();

        //	ColorRGBA + ColorRGBA. Each element sums with the other vector's related element.
        FORCEINLINE ColorRGBA operator+(ColorRGBA& Other) const;

        //	ColorRGBA + TValue. Add each element the TValue parameter.
        FORCEINLINE ColorRGBA operator+(TValue& Other) const;

        //	ColorRGBA - ColorRGBA. Each element subtracts with the other vector's related element.
        FORCEINLINE ColorRGBA operator-(ColorRGBA& Other) const;

        //	ColorRGBA - TValue. Subtract the TValue parameter from each element.
        FORCEINLINE ColorRGBA operator-(TValue& Other) const;

        //	ColorRGBA * TValue. Multiplies each element with the TValue parameter.
        FORCEINLINE ColorRGBA operator*(TValue& Other) const;

        //	ColorRGBA * TValue. Divides each element with the TValue parameter.
        FORCEINLINE ColorRGBA operator/(TValue& Other) const;

        //	ColorRGBA + ColorRGBA. Each element sums with the other vector's related element and overwrites on related ColorRGBA.
        FORCEINLINE ColorRGBA operator+=(ColorRGBA Other);

        //	ColorRGBA + TValue. Each element sums with the other vector's related element and overwrites on related ColorRGBA.
        FORCEINLINE ColorRGBA operator+=(TValue Other);

        //	ColorRGBA - ColorRGBA. Each element sums with the other vector's related element and overwrites on related ColorRGBA.
        FORCEINLINE ColorRGBA operator-=(ColorRGBA Other);

        //	ColorRGBA - TValue. Each element subtract with the other vector's related element and overwrites on related ColorRGBA.
        FORCEINLINE ColorRGBA operator-=(TValue Other);

        //	ColorRGBA * TValue. Each element multiplies with the other vector's related element and overwrites on related ColorRGBA.
        FORCEINLINE ColorRGBA operator*=(TValue Other);

        //	ColorRGBA / TValue. Each element multiplies with the other vector's related element and overwrites on related ColorRGBA.
        FORCEINLINE ColorRGBA operator/=(TValue Other);

        //	Boolean that checks if both 4 dimensional Vectors are equal.
        FORCEINLINE bool operator==(ColorRGBA Other);
    };

    template <typename TValue>
    constexpr byte ColorRGBA<TValue>::Num()
    {
        return 4;
    }

    template <typename TValue>
    ColorRGBA<TValue>::ColorRGBA()
    {
        Red = Green = Blue = 0;
    }

    template <typename TValue>
    ColorRGBA<TValue>::ColorRGBA(TValue RedValue, TValue GreenValue, TValue BlueValue, TValue AlphaValue)
    {
        Red = RedValue;
        Green = GreenValue;
        Blue = BlueValue;
        Alpha = AlphaValue;
    }

    template <typename TValue>
    float ColorRGBA<TValue>::Length()
    {
        return sqrt(pow(Red, 2) + pow(Green, 2) + pow(Blue, 2) + pow(Alpha, 2));
    }

    template <typename TValue>
    ColorRGBA<float> ColorRGBA<TValue>::Normalize()
    {
        return ColorRGBA(Red / Length(), Green / Length(), Blue / Length(), Alpha / Length());
    }

    template <typename TValue>
    TValue ColorRGBA<TValue>::Distance(ColorRGBA& Vec1, ColorRGBA& Vec2)
    {
        return sqrt(pow((Vec2.Red - Vec1.Red), 2) + pow((Vec2.Green - Vec1.Green), 2) + pow((Vec2.Blue - Vec1.Blue), 2) + pow((Vec2.Alpha - Vec1.Alpha), 2));
    }

    template <typename TValue>
    TValue ColorRGBA<TValue>::DotProduct(ColorRGBA& Vec1, ColorRGBA& Vec2)
    {
        return Vec1.Red * Vec2.Red + Vec1.Green * Vec2.Green + Vec1.Blue * Vec2.Blue;
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator+(ColorRGBA& Other) const
    {
        return ColorRGBA((Red + Other.Red), (Green + Other.Green), (Blue + Other.Blue), (Alpha + Other.Alpha));
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator+(TValue& Other) const
    {
        return ColorRGBA((Red + Other), (Green + Other), (Blue + Other), (Alpha + Other));
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator-(ColorRGBA& Other) const
    {
        return ColorRGBA((Red - Other.Red), (Green - Other.Green), (Blue - Other.Blue), (Alpha - Other.Alpha));
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator-(TValue& Other) const
    {
        return ColorRGBA((Red - Other), (Green - Other), (Blue - Other), (Alpha - Other));
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator*(TValue& Other) const
    {
        return ColorRGBA((Red * Other), (Green * Other), (Blue * Other), (Alpha * Other));
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator/(TValue& Other) const
    {
        return ColorRGBA((Red / Other), (Green / Other), (Blue / Other), (Alpha / Other));
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator+=(ColorRGBA Other)
    {
        Red += Other.Red;
        Green += Other.Green;
        Blue += Other.Blue;
        Alpha += Other.Alpha;
        return ColorRGBA(Red, Green, Blue, Alpha);
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator+=(TValue Other)
    {
        Red += Other;
        Green += Other;
        Blue += Other;
        Alpha += Other;
        return ColorRGBA(Red, Green, Blue, Alpha);
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator-=(ColorRGBA Other)
    {
        Red -= Other.Red;
        Green -= Other.Green;
        Blue -= Other.Blue;
        Alpha -= Other.Alpha;
        return ColorRGBA(Red, Green, Blue, Alpha);
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator-=(TValue Other)
    {
        Red -= Other;
        Green -= Other;
        Blue -= Other;
        Alpha -= Other;
        return ColorRGBA(Red, Green, Blue, Alpha);
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator*=(TValue Other)
    {
        Red *= Other;
        Green *= Other;
        Blue *= Other;
        Alpha *= Other;
        return ColorRGBA(Red, Green, Blue, Alpha);
    }

    template <typename TValue>
    ColorRGBA<TValue> ColorRGBA<TValue>::operator/=(TValue Other)
    {
        Red /= Other;
        Green /= Other;
        Blue /= Other;
        Alpha /= Other;
        return ColorRGBA(Red, Green, Blue, Alpha);
    }

    template <typename TValue>
    bool ColorRGBA<TValue>::operator==(ColorRGBA Other)
    {
        return Other.Red == Red && Other.Green == Green && Other.Blue == Blue && Other.Alpha == Alpha ? true : false;
    }
}
