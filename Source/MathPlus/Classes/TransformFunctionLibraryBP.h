#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "TransformFunctionLibraryBP.generated.h"

UCLASS(BlueprintType)
class MATHPLUS_API UTransformFunctionLibrary
    : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MathPlus|Transform")
	static FVector GetForwardVector(const FTransform& Transform);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MathPlus|Transform")
	static FVector GetRightVector(const FTransform& Transform);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MathPlus|Transform")
	static FVector GetUpVector(const FTransform& Transform);
};
