#include "Hash.h"

/* 1D */
float UHashFunctionLibrary::Hash_1D_F(const float X)
{
    return FHash::Hash1D<float, float>(X);
}

float UHashFunctionLibrary::Hash_1D_I(const int32 X)
{
    return FHash::Hash1D<int32, float>(X);
}

/* 2D */
float UHashFunctionLibrary::Hash_2D_Point_F(const FVector2D Point)
{
    return FHash::Hash2D<FVector2D, float>(Point);
}

float UHashFunctionLibrary::Hash_2D_F(const float X, const float Y)
{
    return FHash::Hash2D<float, float>(X, Y);
}

float UHashFunctionLibrary::Hash_2D_Point_I(const FIntPoint Point)
{
    return FHash::Hash2D<FIntPoint, float>(Point);
}

float UHashFunctionLibrary::Hash_2D_I(const int32 X, const int32 Y)
{
    return FHash::Hash2D<int32, float>(X, Y);
}

/* 3D */
float UHashFunctionLibrary::Hash_3D_Point_F(const FVector Point)
{
    return FHash::Hash3D<FVector, float>(Point);
}

float UHashFunctionLibrary::Hash_3D_F(const float X, const float Y, const float Z)
{
    return FHash::Hash3D<float, float>(X, Y, Z);
}

float UHashFunctionLibrary::Hash_3D_Point_I(const FIntVector Point)
{
    return FHash::Hash3D<FIntVector, float>(Point);
}

float UHashFunctionLibrary::Hash_3D_I(const int32 X, const int32 Y, const int32 Z)
{
    return FHash::Hash3D<int32, float>(X, Y, Z);
}