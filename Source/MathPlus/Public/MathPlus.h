#pragma once

#include "CoreMinimal.h"

class MATHPLUS_API FMathPlus
{
public:
	template <typename TIntegralType>
	static TIntegralType PackFloatToInt(const float Value, const float MinValue, const float MaxValue)
	{
		static_assert(TIsIntegral<TIntegralType>::Value, "TIntegralType must be an integer");

		// clip to min, max (should be anyway!)
		auto InputValue = FMath::Clamp(Value, MinValue, MaxValue);

		const auto InputRange = MaxValue - MinValue;
		const auto OneOverInputRange = 1.0f / InputRange;

		// normalize to -1, +1
		InputValue -= MinValue;
		InputValue *= OneOverInputRange;

		const auto OutputRange = TNumericLimits<TIntegralType>::Max() - TNumericLimits<TIntegralType>::Min();
		const auto OneOverOutputRange = 1.0f / StaticCast<float>(OutputRange);

		auto OutputValue = StaticCast<TIntegralType>(FMath::RoundToInt(InputValue * OutputRange));
		OutputValue += MinValue;
		
		return OutputValue;
	}

	template <typename TIntegralType>
	static float UnpackIntToFloat(const TIntegralType Value, const float MinValue, const float MaxValue)
	{
		static_assert(TIsIntegral<TIntegralType>::Value, "TIntegralType must be an integer");

		auto InputValue = Value;

		const auto InputRange = TNumericLimits<TIntegralType>::Max() - TNumericLimits<TIntegralType>::Min();
		const auto OneOverInputRange = 1.0f / StaticCast<float>(InputRange);

		const auto OutputRange = MaxValue - MinValue;
		const auto OneOverOutputRange = 1.0f / OutputRange;

		auto OutputValue = StaticCast<float>(StaticCast<float>(InputValue) / StaticCast<float>(InputRange));
		OutputValue *= OutputRange;
		OutputValue += MinValue;

		return OutputValue;
	}
};
