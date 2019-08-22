#pragma once

#include "CoreMinimal.h"
#include "Scalar.h"

#include "Float64.generated.h"

USTRUCT(BlueprintType)
struct MATHPLUS_API FFloat64
{
    GENERATED_BODY()

protected:
    typedef double TElementType;
    typedef FFloat64 TScalarType;

protected:
    union
    {
        struct
        {
#if PLATFORM_LITTLE_ENDIAN
            uint64	Mantissa : 52;
            uint64	Exponent : 11;
            uint64	Sign : 1;
#else
            uint64	Sign : 1;
            uint64	Exponent : 11;
            uint64	Mantissa : 52;
#endif
        } Components;

        double	DoubleValue;
    };

public:
#pragma region Constructors
    FFloat64();
    FFloat64(const TScalarType& Value);
    explicit FFloat64(TElementType Value);
#pragma endregion Constructors

#pragma region Assignment
    FFloat64& operator=(const TScalarType& Value);
    FFloat64& operator=(TElementType Value);
    operator TElementType() const { return GetValue(); }
#pragma endregion Assignment

#pragma region Accessors
    const TElementType& GetValue() const;
    void SetValue(TElementType Value);
#pragma endregion Accessors

#pragma region Operators
    DEFINE_SCALAR_OPERATOR_STACK()

    /** Negate */
    FFloat64& operator-();

    DEFINE_SCALAR_CMP_STACK()

    friend uint32 GetTypeHash(const TScalarType& Value) { return GetTypeHash(Value.GetValue()); }
#pragma endregion Operators

#pragma region Serialization
    friend FArchive& operator<<(FArchive& Ar, TScalarType& Value);
    friend void operator<<(FStructuredArchive::FSlot Slot, TScalarType& Value);
    bool Serialize(FArchive& Ar);
    bool Serialize(FStructuredArchive::FSlot Slot);
#pragma endregion Serialization
};

template <> struct TIsPODType<FFloat64> { enum { Value = true }; };