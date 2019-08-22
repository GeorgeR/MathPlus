#include "Float64.h"

FFloat64::FFloat64()
{
    SetValue(0.0);
}

FFloat64::FFloat64(const TScalarType& Value)
{
    DoubleValue = Value.DoubleValue;
}

FFloat64::FFloat64(FFloat64::TElementType Value)
{
    SetValue(Value);
}

FFloat64& FFloat64::operator=(const TScalarType& Value)
{
    DoubleValue = Value.DoubleValue;
    return *this;
}

FFloat64& FFloat64::operator=(TElementType Value)
{
    SetValue(Value);
    return *this;
}

const FFloat64::TElementType& FFloat64::GetValue() const
{
    return DoubleValue;
}

void FFloat64::SetValue(TElementType Value)
{
    DoubleValue = Value;
}

IMPL_SCALAR_OPERATOR_STACK(FFloat64)

FFloat64& FFloat64::operator-()
{
    SetValue(GetValue() * -1.0);
    return *this;
}

IMPL_SCALAR_CMP_STACK(FFloat64)

FArchive& operator<<(FArchive& Ar, FFloat64::TScalarType& Value)
{
    return Ar << Value.DoubleValue;
}

void operator<<(FStructuredArchive::FSlot Slot, FFloat64::TScalarType& Value)
{
    auto Record = Slot.EnterRecord();
    Record << NAMED_ITEM("Value", Value.DoubleValue);
}

bool FFloat64::Serialize(FArchive& Ar)
{
    Ar << *this;
    return true;
}

bool FFloat64::Serialize(FStructuredArchive::FSlot Slot)
{
    Slot << *this;
    return true;
}