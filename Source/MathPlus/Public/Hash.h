#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Hash.generated.h"

#define _HASH_1D(X) FMath::Frac(1.0e4 * FMath::Sin(17.0f * X) * (0.1f + FMath::Abs(FMath::Sin(13.0f * X))))
#define _HASH_2D(X, Y) FMath::Frac(1.0e4 * FMath::Sin(17.0f * X + 0.1f * Y) * (0.1f + FMath::Abs(FMath::Sin(13.0f * Y + X))))

struct MATHPLUS_API FHash
{
public:
#pragma region 1D
    template <typename TElementType, typename TReturnType>
    static TReturnType Hash1D(const TElementType X);
#pragma endregion 1D

#pragma region 2D
    template <typename TElementType, typename TReturnType>
    static TReturnType Hash2D(const TElementType X, const TElementType Y);
    
    template <typename TContainerType, typename TReturnType>
    static TReturnType Hash2D(const TContainerType Point);
#pragma endregion 2D

#pragma region 3D
    template <typename TElementType, typename TReturnType>
    static TReturnType Hash3D(const TElementType X, const TElementType Y, const TElementType Z);

    template <typename TContainerType, typename TReturnType>
    static TReturnType Hash3D(const TContainerType Point);
#pragma endregion 3D
};

template <typename TElementType, typename TReturnType>
TReturnType FHash::Hash1D(const TElementType X)
{
    return _HASH_1D(X);
}

template <typename TElementType, typename TReturnType>
TReturnType FHash::Hash2D(const TElementType X, const TElementType Y)
{
    return _HASH_2D(X, Y);
}

template <typename TContainerType, typename TReturnType>
TReturnType FHash::Hash2D(const TContainerType Point)
{
    return _HASH_2D(Point.X, Point.Y);
}

template <typename TElementType, typename TReturnType>
TReturnType FHash::Hash3D(const TElementType X, const TElementType Y, const TElementType Z)
{
    auto XY = _HASH_2D(X, Y);
    return _HASH_2D(XY, Z);    
}

template <typename TContainerType, typename TReturnType>
TReturnType FHash::Hash3D(const TContainerType Point)
{
    auto XY = _HASH_2D(Point.X, Point.Y);
    return _HASH_2D(XY, Point.Z);
}

#undef _HASH_1D
#undef _HASH_2D
#undef _HASH_3D

UCLASS(BlueprintType)
class MATHPLUS_API UHashFunctionLibrary
    : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
#pragma region 1D
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash1D"))
    static float Hash_1D_F(const float X);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash1D"))
    static float Hash_1D_I(const int32 X);
#pragma endregion 1D

#pragma region 2D
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash2D"))
    static float Hash_2D_Point_F(const FVector2D Point);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash2D"))
    static float Hash_2D_F(const float X, const float Y);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash2D"))
    static float Hash_2D_Point_I(const FIntPoint Point);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash2D"))
    static float Hash_2D_I(const int32 X, const int32 Y);
#pragma endregion 2D

#pragma region 3D
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash3D"))
    static float Hash_3D_Point_F(const FVector Point);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash3D"))
    static float Hash_3D_F(const float X, const float Y, const float Z);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash3D"))
    static float Hash_3D_Point_I(const FIntVector Point);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash3D"))
    static float Hash_3D_I(const int32 X, const int32 Y, const int32 Z);
#pragma endregion 3D
};