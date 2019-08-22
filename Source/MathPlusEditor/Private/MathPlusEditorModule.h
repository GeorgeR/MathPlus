#pragma once

#include "IMathPlusEditorModuleInterface.h"

#include "CoreMinimal.h"
#include "Stats/Stats.h"
#include "Stats/Stats2.h"
#include "DetailCustomizations.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMathPlusEditor, VeryVerbose, All);

DECLARE_STATS_GROUP(TEXT("MathPlusEditor"), STATGROUP_MathPlusEditor, STATCAT_Advanced);

class FMathPlusEditorModule
    : public IMathPlusEditorModuleInterface
{
public:
    void StartupModule() override;
    void ShutdownModule() override;

    FORCEINLINE bool SupportsDynamicReloading() override { return true; }

private:
    void RegisterPropertyTypeCustomizations();
    void RegisterObjectCustomizations();
    
    void RegisterCustomClassLayout(FName ClassName, FOnGetDetailCustomizationInstance DetailLayoutDelegate);
    void RegisterCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate);

private:
    TSet<FName> RegisteredClassNames;
    TSet<FName> RegisteredPropertyTypes;
};