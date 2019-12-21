#pragma once

#include "CoreTypes.h"
#include "Templates/IsArithmetic.h"
#include "Templates/UnrealTypeTraits.h"
#include "Math/NumericLimits.h"
#include "Math/UnrealMathUtility.h"

template <uint8 Dimension>
struct TDimensionTraits
{
    static_assert(Dimension >= 2 && Dimension <= 4, "Dimension must be between 2 and 4.");
};
