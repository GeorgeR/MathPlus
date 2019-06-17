#include "Double.h"

FDouble::FDouble()
{
    Bytes.SetNumZeroed(8);
}

FDouble::FDouble(const double& Value)
{
    SetValue(Value);
}

double FDouble::GetValue() const
{
    auto LongValue = 
    (((int64)Bytes[0]) << 56) 
    | (((int64)Bytes[1]) << 48) 
    | (((int64)Bytes[2]) << 40) 
    | (((int64)Bytes[3]) << 32) 
    | (((int64)Bytes[4]) << 24) 
    | (((int64)Bytes[5]) << 16) 
    | (((int64)Bytes[6]) << 8) 
    | ((int64)Bytes[7]);

    return *((double*)(&LongValue));
}

void FDouble::SetValue(const double& Value)
{
    const int64 LongValue = *((int64*)(&Value));

    Bytes[0] = (LongValue >> 56);
    Bytes[1] = (LongValue >> 48);
    Bytes[2] = (LongValue >> 40);
    Bytes[3] = (LongValue >> 32);
    Bytes[4] = (LongValue >> 24);
    Bytes[5] = (LongValue >> 16);
    Bytes[6] = (LongValue >> 8);
    Bytes[7] = (LongValue);
}

#define IMPL_SIMPLE_OPERATOR_STACK(Type, BaseType, Op)                  \
        Type Type##::operator##Op(const Type##& Other) const            \
        {                                                               \
            return Type##(GetValue() Op Other.GetValue());              \
        }                                                               \
                                                                        \
        Type Type##::operator##Op##(const BaseType##& Other) const      \
        {                                                               \
            return Type##(GetValue() Op Other);                         \
        }                                                               \
                                                                        \
        Type Type##::operator##Op##=(const Type##& Other)               \
        {                                                               \
            return this->operator##Op##(Other);                         \
        }                                                               \
                                                                        \
        Type Type##::operator##Op##=(const BaseType##& Other)           \
        {                                                               \
            return this->operator##Op##(Other);                         \
        }

IMPL_SIMPLE_OPERATOR_STACK(FDouble, double, +)
IMPL_SIMPLE_OPERATOR_STACK(FDouble, double, -)
IMPL_SIMPLE_OPERATOR_STACK(FDouble, double, *)
IMPL_SIMPLE_OPERATOR_STACK(FDouble, double, /)

#undef IMPL_SIMPLE_OPERATOR_STACK

FDouble& FDouble::operator-()
{
    SetValue(GetValue() * -1.0);
    return *this;
}

#define IMPL_CMP_OPERATOR_STACK(Type, BaseType, Op)                     \
        bool Type##::operator##Op##(const Type##& Other) const          \
        {                                                               \
            return GetValue() Op Other.GetValue();                      \
        }                                                               \
                                                                        \
        bool Type##::operator##Op##(const BaseType##& Other) const      \
        {                                                               \
            return GetValue() Op Other;                                 \
        }

IMPL_CMP_OPERATOR_STACK(FDouble, double, ==)
IMPL_CMP_OPERATOR_STACK(FDouble, double, !=)
IMPL_CMP_OPERATOR_STACK(FDouble, double, >)
IMPL_CMP_OPERATOR_STACK(FDouble, double, <)

#undef IMPL_CMP_OPERATOR_STACK