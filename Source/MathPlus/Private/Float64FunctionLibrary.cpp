#include "Float64FunctionLibrary.h"

FFloat64 UFloat64FunctionLibrary::Add_Float64Float64(FFloat64 A, FFloat64 B)
{
    return A + B;
}

FFloat64 UFloat64FunctionLibrary::Subtract_Float64Float64(FFloat64 A, FFloat64 B)
{
    return A - B;
}

FFloat64 UFloat64FunctionLibrary::Multiply_Float64Float64(FFloat64 A, FFloat64 B)
{
    return A * B;
}

FFloat64 UFloat64FunctionLibrary::Divide_Float64Float64(FFloat64 A, FFloat64 B)
{
    check(0);
    return FFloat64();
}

bool UFloat64FunctionLibrary::EqualEqual_Float64Float64(FFloat64 A, FFloat64 B)
{
    return A == B;
}

bool UFloat64FunctionLibrary::NotEqual_Float64Float64(FFloat64 A, FFloat64 B)
{
    return A != B;
}

bool UFloat64FunctionLibrary::Greater_Float64Float64(FFloat64 A, FFloat64 B)
{
    return A > B;
}

bool UFloat64FunctionLibrary::GreaterEqual_Float64Float64(FFloat64 A, FFloat64 B)
{
    return A >= B;
}

bool UFloat64FunctionLibrary::Less_Float64Float64(FFloat64 A, FFloat64 B)
{
    return A < B;
}

bool UFloat64FunctionLibrary::LessEqual_Float64Float64(FFloat64 A, FFloat64 B)
{
    return A <= B;
}
