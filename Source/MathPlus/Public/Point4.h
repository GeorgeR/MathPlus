#pragma once

#include "Point.h"

#pragma region Declaration
template <typename TElementType>
struct TPoint<TElementType, 4>
{
private:
    typedef TPoint<TElementType, 4> TPointType;

public:
#pragma region Data
    TElementType X;
    TElementType Y;
    TElementType Z;
    TElementType W;
#pragma endregion Data

#pragma region Statics
    MATHPLUS_API static const TPointType Zero;
    MATHPLUS_API static const TPointType One;
    MATHPLUS_API static const TPointType Up;
    MATHPLUS_API static const TPointType Right;
    MATHPLUS_API static const TPointType Forward;
#pragma endregion Statics

#pragma region Constructors
    TPoint() = default;
    TPoint(TElementType Value);
    TPoint(TElementType X, TElementType Y, TElementType Z, TElementType W);
    explicit FORCEINLINE TPoint(EForceInit);
#pragma endregion Constructors

#pragma region Accessors
    TElementType operator[](uint8 Index) const;
    TElementType& operator[](uint8 Index);
#pragma endregion Accessors

#pragma region Operators
    bool operator==(const TPointType& Other) const;
    bool operator!=(const TPointType& Other) const;

    friend uint32 GetTypeHash(const TPointType& Value)
    {
        return GetTypeHash(Value.X) ^ GetTypeHash(Value.Y) ^ GetTypeHash(Value.Z) ^ GetTypeHash(Value.W);
    }

    TPointType& operator+=(const TElementType& Other);
    TPointType& operator+=(const TPointType& Other);

    TPointType& operator-=(const TElementType& Other);
    TPointType& operator-=(const TPointType& Other);

    TPointType& operator*=(TElementType Scale);
    TPointType& operator*=(const TPointType& Other);

    TPointType& operator/=(TElementType Divisor);
    TPointType& operator/=(const TPointType& Other);
#pragma endregion Operators

    FORCEINLINE TPointType ComponentMin(const TPointType& Other) const;
    FORCEINLINE TPointType ComponentMax(const TPointType& Other) const;

    TElementType GetMin() const;
    TElementType GetMax() const;

    TElementType Size() const;
    TElementType SizeSquared() const;

    FString ToString() const;

#pragma region Serialization
    friend FArchive& operator<<(FArchive& Ar, TPointType& Value)
    {
        return A << Value.X << Value.Y << Value.Z << Value.W;
    }

    friend void operator<<(FStructuredArchive::FSlot Slot, TPointType& Value)
    {
        FStructuredArchive::FRecord Record = Slot.EnterRecord();
        Record << NAMED_ITEM("X", Value.X) << NAMED_ITEM("Y", Value.Y) << NAMED_ITEM("Z", Value.Z) << NAMED_ITEM("W", Value.W);
    }
#pragma endregion Serialization
};
#pragma endregion Declaration

#pragma region Definition
#define TPointType TPoint<TElementType, 4>
#define TemplateDeclaration template <typename TElementType>
#pragma region Constructors
TemplateDeclaration
FORCEINLINE TPointType::TPoint(TElementType Value)
    : X(Value),
    Y(Value),
    Z(Value),
    W(Value)
{ }

TemplateDeclaration
FORCEINLINE TPointType::TPoint(TElementType X, TElementType Y, TElementType Z, TElementType W)
    : X(X),
    Y(Y),
    Z(Z),
    W(W)
{ }

TemplateDeclaration
FORCEINLINE TPointType::TPoint(EForceInit)
    : X(0),
    Y(0),
    Z(0),
    W(0)
{ }
#pragma endregion Constructors

#pragma region Accessors
TemplateDeclaration
FORCEINLINE TElementType TPointType::operator[](uint8 Index) const
{
    check(Index >= 0 && Index < 4);
    if (Index == 0)
        return X;
    else if (Index == 1)
        return Y;
    else if (Index == 2)
        return Z;
    else if (Index == 3)
        return W;
}

TemplateDeclaration
FORCEINLINE TElementType& TPointType::operator[](uint8 Index)
{
    check(Index >= 0 && Index < 4);
    if (Index == 0)
        return X;
    else if (Index == 1)
        return Y;
    else if (Index == 2)
        return Z;

	return W;
}
#pragma endregion Accessors

#pragma region Operators

#pragma region Equality
TemplateDeclaration
FORCEINLINE bool TPointType::operator==(const TPointType& Other) const
{
    return X == Other.X && Y == Other.Y && Z == Other.Z && W == Other.W;
}

TemplateDeclaration
FORCEINLINE bool TPointType::operator!=(const TPointType& Other) const
{
    return (X != Other.X) || (Y != Other.Y) || (Z != Other.Z) || (W != Other.W);
}
#pragma endregion Equality

#pragma region Add
TemplateDeclaration
FORCEINLINE TPointType& TPointType::operator+=(const TElementType& Other)
{
    X += Other;
    Y += Other;
    Z += Other;
    W += Other;

    return *this;
}

TemplateDeclaration
FORCEINLINE TPointType& TPointType::operator+=(const TPointType& Other)
{
    X += Other.X;
    Y += Other.Y;
    Z += Other.Z;
    W += Other.W;

    return *this;
}
#pragma endregion Add

#pragma region Subtract
TemplateDeclaration
FORCEINLINE TPointType& TPointType::operator-=(const TElementType& Other)
{
    X -= Other;
    Y -= Other;
    Z -= Other;
    W -= Other;

    return *this;
}

TemplateDeclaration
FORCEINLINE TPointType& TPointType::operator-=(const TPointType& Other)
{
    X -= Other.X;
    Y -= Other.X;
    Z -= Other.Z;
    W -= Other.W;

    return *this;
}
#pragma endregion Subtract

#pragma region Multiply
TemplateDeclaration
FORCEINLINE TPointType& TPointType::operator*=(TElementType Scale)
{
    X *= Scale;
    Y *= Scale;
    Z *= Scale;
    W *= Scale;

    return *this;
}

TemplateDeclaration
FORCEINLINE TPointType& TPointType::operator*=(const TPointType& Other)
{
    X *= Other.X;
    Y *= Other.Y;
    Z *= Other.Z;
    W *= Other.W;

    return *this;
}
#pragma endregion Multiply

#pragma region Divide
TemplateDeclaration
TPointType& TPointType::operator/=(TElementType Divisor)
{
    X /= Divisor;
    Y /= Divisor;
    Z /= Divisor;
    W /= Divisor;

    return *this;
}

TemplateDeclaration
TPointType& TPointType::operator/=(const TPointType& Other)
{
    X /= Other.X;
    Y /= Other.Y;
    Z /= Other.Z;
    W /= Other.W;

    return *this;
}
#pragma endregion Divide
#pragma endregion Operators

TemplateDeclaration
FORCEINLINE TPointType TPointType::ComponentMin(const TPointType& Other) const
{
    return TPointType(FMath::Min(X, Other.X), FMath::Min(Y, Other.Y), FMath::Min(Z, Other.Z), FMath::Min(W, Other.W));
}

TemplateDeclaration
FORCEINLINE TPointType TPointType::ComponentMax(const TPointType& Other) const
{
    return TPointType(FMath::Max(X, Other.X), FMath::Max(Y, Other.Y), FMath::Max(Z, Other.Z), FMath::Max(W, Other.W));
}

TemplateDeclaration
FORCEINLINE TElementType TPointType::GetMin() const
{
    return FMath::Min(FMath::Min(FMath::Min(X, Y), Z), W);
}

TemplateDeclaration
FORCEINLINE TElementType TPointType::GetMax() const
{
    return FMath::Max(FMath::Max(FMath::Max(X, Y), Z), W);
}

TemplateDeclaration
FORCEINLINE TElementType TPointType::Size() const
{
    return TElementType(FMath::Sqrt(X * X + Y * Y + Z * Z + W * W));
}

TemplateDeclaration
FORCEINLINE TElementType TPointType::SizeSquared() const
{
    return X * X + Y * Y + Z * Z + W * W;
}

TemplateDeclaration
FORCEINLINE FString TPointType::ToString() const
{
    return FString::Printf(TEXT("X=%d Y=%d Z=%d W=%d"), X, Y, Z, W);
}

TemplateDeclaration
struct TIsPODType<TPointType> { enum { Value = true }; };

#undef TPointType
#undef TemplateDeclaration
#pragma endregion Definition

typedef TPoint<int8, 4> FPoint4B;
typedef TPoint<int16, 4> FPoint4S;
typedef TPoint<int32, 4> FPoint4I;
typedef TPoint<FFloat16, 4> FPoint4H;
typedef TPoint<float, 4> FPoint4F;
typedef TPoint<double, 4> FPoint4D;
