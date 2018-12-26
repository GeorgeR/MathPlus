#pragma once

#include "CoreTypes.h"
#include "Templates/IsArithmetic.h"
#include "Templates/UnrealTypeTraits.h"
#include "Math/NumericLimits.h"
#include "Math/UnrealMathUtility.h"

template <typename TElementType>
struct TElementTypeTraits
{
    static_assert(TIsArithmetic<TElementType>::Value, "Invalid TElementType.");
    static_assert(THasGetTypeHash<TElementType>::Value, "TElementType must by hashable (GetTypeHash).")

    static TElementType Min()
    {
        return TNumericLimits<TElementType>::Min();
    }

    static TElementType Max()
    {
        return TNumericLimits<TElementType>::Max();
    }
};