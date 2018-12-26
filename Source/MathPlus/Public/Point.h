#pragma once

#include "CoreMinimal.h"

#pragma region Declaration
template <typename TElementType, uint8 Dimensions>
struct TPoint
{
    static_assert(Dimensions >= 2 && Dimensions <= 4, "Dimensions must range from 2-4.");

protected:
    typedef TPoint<TElementType, Dimensions> TPointType;

public:
#pragma region Data
    TElementType X;
#pragma endregion Data

#pragma region Constructors
    TPoint();
    TPoint(TElementType Value) { }
    explicit FORCEINLINE TPoint(EForceInit) { }
#pragma endregion Constructors

#pragma region Accessors
    const TElementType& operator()(uint8 Index) const;
    TElementType& operator()(uint8 Index);

    TElementType operator[](uint8 Index) const { return X; }
    TElementType& operator[](uint8 Index) { return X; }
#pragma endregion Accessors

#pragma region Operators
    bool operator==(const TPointType& Other) const { return false; }
    bool operator!=(const TPointType& Other) const { return false; }

    friend uint32 GetTypeHash(const TPointType& Value) { return 0; }

    TPointType operator+=(const TElementType& Other) const;
    TPointType& operator+=(const TElementType& Other) { return *this; }

    TPointType operator+=(const TPointType& Other) const;
    TPointType& operator+=(const TPointType& Other) { return *this; }

    TPointType operator-=(const TElementType& Other) const;
    TPointType& operator-=(const TElementType& Other) { return *this; }

    TPointType operator-=(const TPointType& Other) const;
    TPointType& operator-=(const TPointType& Other) { return *this; }

    TPointType operator*=(TElementType Scale) const;
    TPointType& operator*=(TElementType Scale) { return *this; }

    TPointType operator*=(const TPointType& Other) const;
    TPointType& operator*=(const TPointType& Other) { return *this; }

    TPointType operator/=(TElementType Divisor) const;
    TPointType& operator/=(TElementType Divisor) { return *this; }

    TPointType operator/=(const TPointType& Other) const;
    TPointType& operator/=(const TPointType& Other) { return *this; }
#pragma endregion Operators

    FORCEINLINE TPointType ComponentMin(const TPointType& Other) const { return *this; }
    FORCEINLINE TPointType ComponentMax(const TPointType& Other) const { return *this; }

    TElementType GetMin() const { return X; }
    TElementType GetMax() const { return X; }

    TElementType Size() const { return X; }
    TElementType SizeSquared() const { return X * X; }

    FString ToString() const { return FString::Printf(TEXT("X=%d"), X); }

    static int32 NumComponents() { return Dimensions; }

#pragma region Serialization
    friend FArchive& operator<<(FArchive& Ar, TPointType& Value) { return Ar; }
    friend void operator<<(FStructuredArchive::FSlot Slot, TPointType& Value) { }
    bool Serialize(FArchive& Ar);
    bool Serialize(FStructuredArchive::FSlot Slot);
#pragma endregion Serialization
};
#pragma endregion Declaration

#pragma region Definition
#define TPointType TPoint<TElementType, Dimensions>
#define TemplateDeclaration template <typename TElementType, uint8 Dimensions>
#pragma region Constructors
TemplateDeclaration
FORCEINLINE TPointType::TPoint() { }
#pragma endregion Constructors

#pragma region Accessors
TemplateDeclaration
FORCEINLINE const TElementType& TPointType::operator()(uint8 Index) const
{
    return (&X)[Index];
}

TemplateDeclaration
FORCEINLINE TElementType& TPointType::operator()(uint8 Index)
{
    return (&X)[Index];
}
#pragma endregion Accessors

#pragma region Operators

#pragma region Add
TemplateDeclaration
FORCEINLINE TPointType TPointType::operator+=(const TElementType& Other) const
{
    return TPointType(*this) += Other;
}

TemplateDeclaration
FORCEINLINE TPointType TPointType::operator+=(const TPointType& Other) const
{
    return TPointType(*this) += Other;
}
#pragma endregion Add

#pragma region Subtract
TemplateDeclaration
FORCEINLINE TPointType TPointType::operator-=(const TElementType& Other) const
{
    return TPointType(*this) -= Other;
}

TemplateDeclaration
FORCEINLINE TPointType TPointType::operator-=(const TPointType& Other) const
{
    return TPointType(*this) -= Other;
}
#pragma endregion Subtract

#pragma region Multiply
TemplateDeclaration
FORCEINLINE TPointType TPointType::operator*=(TElementType Scale) const
{
    return TPointType(*this) *= Other;
}

TemplateDeclaration
FORCEINLINE TPointType TPointType::operator*=(const TPointType& Other) const
{
    return TPointType(*this) *= Other;
}
#pragma endregion Multiply

#pragma region Divide
TemplateDeclaration
TPointType TPointType::operator/=(TElementType Divisor) const
{
    return TPointType(*this) /= Other;
}

TemplateDeclaration
TPointType TPointType::operator/=(const TPointType& Other) const
{
    return TPointType(*this) /= Other;
}
#pragma endregion Divide
#pragma endregion Operators

#pragma region Serialization
TemplateDeclaration
FORCEINLINE bool TPointType::Serialize(FArchive& Ar)
{
    Ar << *this;
    return true;
}

TemplateDeclaration
FORCEINLINE bool TPointType::Serialize(FStructuredArchive::FSlot Slot)
{
    Slot << *this;
    return true;
}
#pragma endregion Serialization

TemplateDeclaration
struct TIsPODType<TPointType> { enum { Value = true }; };

#undef TPointType
#undef TemplateDeclaration
#pragma endregion Definition