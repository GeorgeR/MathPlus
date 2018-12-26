#pragma once

#include "Point.h"

template <typename TElementType>
struct TPoint<TElementType, 2>
{
public:
#pragma region Data
    TElementType X;
    TElementType Y;
#pragma endregion Data

#pragma region Statics
    MATHPLUS_API static const TPointType Zero;
    MATHPLUS_API static const TPointType One;
    MATHPLUS_API static const TPointType Up;
    MATHPLUS_API static const TPointType Right;
#pragma endregion Statics

#pragma region Constructors
    TPoint(TElementType X, TElementType Y);
#pragma endregion Constructors
};