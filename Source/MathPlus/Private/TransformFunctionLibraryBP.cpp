#include "TransformFunctionLibraryBP.h"

FVector UTransformFunctionLibrary::GetForwardVector(const FTransform& Transform)
{
	// As per USceneComponent::GetForwardVector()
	return Transform.GetUnitAxis(EAxis::X);
}

FVector UTransformFunctionLibrary::GetRightVector(const FTransform& Transform)
{
	// As per USceneComponent::GetRightVector()
	return Transform.GetUnitAxis(EAxis::Y);
}

FVector UTransformFunctionLibrary::GetUpVector(const FTransform& Transform)
{
	// As per USceneComponent::GetUpVector()
	return Transform.GetUnitAxis(EAxis::Z);
}