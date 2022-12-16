#pragma once

#include <Core/CoreAPI.h>
#include <Core/Types.h>

namespace Engine
{
    
#define PI 3.14159265359
#define DEG_TO_RAD 0.01745329252f
#define RAD_TO_DEG 357.295779513f

    class Math
    {
    public:
        Math() = delete;
        ~Math() = delete;
        
        FORCEINLINE static float Sqrt(const float value);

        FORCEINLINE static float Pow(const float value, const float power);

        FORCEINLINE static float Sin(const float deg);

        FORCEINLINE static float Cos(const float deg);

        FORCEINLINE static float Tan(const float deg);

        FORCEINLINE static float Cotan(const float deg);

        FORCEINLINE static float Asin(const float value);

        FORCEINLINE static float Acos(const float value);

        FORCEINLINE static float Atan(const float value);

        FORCEINLINE static float Acotan(const float value);
    };


    inline float Math::Sqrt(const float value)
    {
        return sqrtf(value);
    }

    inline float Math::Pow(const float value, const float power)
    {
        return powf(value, power);
    }

    inline float Math::Sin(const float deg)
    {
        return sinf(deg * DEG_TO_RAD);
    }

    inline float Math::Cos(const float deg)
    {
        return cosf(deg * DEG_TO_RAD);
    }

    inline float Math::Tan(const float deg)
    {
        return tanf(deg * DEG_TO_RAD);
    }

    inline float Math::Cotan(const float deg)
    {
        return 1 / tanf(deg * DEG_TO_RAD);
    }

    inline float Math::Asin(const float value)
    {
        return asinf(value * DEG_TO_RAD);
    }

    inline float Math::Acos(const float value)
    {
        return acosf(value * DEG_TO_RAD);
    }

    inline float Math::Atan(const float value)
    {
        return atanf(value * DEG_TO_RAD);
    }

    inline float Math::Acotan(const float value)
    {
        return 1 / atanf(value * DEG_TO_RAD);
    }
}
