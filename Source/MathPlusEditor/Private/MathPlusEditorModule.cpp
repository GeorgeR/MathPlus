#include "MathPlusEditorModule.h"

#include "ModuleManager.h"
#include "PropertyEditorModule.h"

#include "Customizations/Float64Customization.h"

DEFINE_LOG_CATEGORY(LogMathPlusEditor);

#define LOCTEXT_NAMESPACE "FMathPlusEditorModule"

void FMathPlusEditorModule::StartupModule()
{
    auto& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

    RegisterPropertyTypeCustomizations();
    RegisterObjectCustomizations();

    //TSharedPtr<FMotionControllerPinFactory> MotionControllerPinFactory = MakeShareable(new FMotionControllerPinFactory());
    //FEdGraphUtilities::RegisterVisualPinFactory(MotionControllerPinFactory);

    PropertyModule.NotifyCustomizationModuleChanged();
}

void FMathPlusEditorModule::ShutdownModule()
{
    if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
    {
        auto& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

        // Unregister all classes customized by name
        for (auto It = RegisteredClassNames.CreateConstIterator(); It; ++It)
        {
            if (It->IsValid())
                PropertyModule.UnregisterCustomClassLayout(*It);
        }

        // Unregister all structures
        for (auto It = RegisteredPropertyTypes.CreateConstIterator(); It; ++It)
        {
            if (It->IsValid())
                PropertyModule.UnregisterCustomPropertyTypeLayout(*It);
        }

        PropertyModule.NotifyCustomizationModuleChanged();
    }
}

void FMathPlusEditorModule::RegisterPropertyTypeCustomizations()
{
    RegisterCustomPropertyTypeLayout(TEXT("Float64"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FFloat64Customization::MakeInstance));
}

void FMathPlusEditorModule::RegisterObjectCustomizations()
{
}

void FMathPlusEditorModule::RegisterCustomClassLayout(const FName ClassName, const FOnGetDetailCustomizationInstance DetailLayoutDelegate)
{
    check(ClassName != NAME_None);

    RegisteredClassNames.Add(ClassName);

    static FName PropertyEditor(TEXT("PropertyEditor"));
    auto& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);
    PropertyModule.RegisterCustomClassLayout(ClassName, DetailLayoutDelegate);
}

void FMathPlusEditorModule::RegisterCustomPropertyTypeLayout(const FName PropertyTypeName, const FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate)
{
    check(PropertyTypeName != NAME_None);

    RegisteredPropertyTypes.Add(PropertyTypeName);

    static FName PropertyEditor("PropertyEditor");
    auto& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);
    PropertyModule.RegisterCustomPropertyTypeLayout(PropertyTypeName, PropertyTypeLayoutDelegate);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMathPlusEditorModule, MathPlusEditor)