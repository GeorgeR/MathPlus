#include "Float64Customization.h"

#include "IDetailsView.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SBoxPanel.h"
#include "Text.h"
#include "UObject/Class.h"
#include "Float64.h"
#include "PlatformApplicationMisc.h"
#include "ScopedTransaction.h"
#include "IDetailChildrenBuilder.h"
#include "Editor.h"
#include "IPropertyUtilities.h"

#define LOCTEXT_NAMESPACE "FFloat64Customization"

TSharedRef<IPropertyTypeCustomization> FFloat64Customization::MakeInstance()
{
    return MakeShareable(new FFloat64Customization);
}

template <typename NumericType>
TSharedRef<SWidget> FFloat64Customization::MakeValueWidget(
    TSharedRef<IPropertyHandle>& StructPropertyHandle,
    TSharedRef<NumericType>& Value,
    const FLinearColor& LabelColor,
    const FLinearColor& LabelBackgroundColor)
{
    TWeakPtr<IPropertyHandle> WeakHandlePtr = StructPropertyHandle;

    return
        SNew(SNumericEntryBox<NumericType>)
        .Value(this, &FFloat64Customization::OnGetValue<NumericType>, WeakHandlePtr, Value)
        .Font(IDetailLayoutBuilder::GetDetailFont())
        .UndeterminedString(NSLOCTEXT("PropertyEditor", "MultipleValues", "Multiple Values"))
        .OnValueCommitted(this, &FFloat64Customization::OnValueCommitted<NumericType>, WeakHandlePtr, Value)
        .OnValueChanged(this, &FFloat64Customization::OnValueChanged<NumericType>, WeakHandlePtr, Value)
        .OnBeginSliderMovement(this, &FFloat64Customization::OnBeginSliderMovement)
        .OnEndSliderMovement(this, &FFloat64Customization::OnEndSliderMovement<NumericType>, WeakHandlePtr, Value)
        .LabelVAlign(VAlign_Fill)
        .LabelPadding(0)
        // Only allow spin on handles with one object.  Otherwise it is not clear what value to spin
        .AllowSpin(StructPropertyHandle->GetNumOuterObjects() == 1)
        .MinValue(TOptional<NumericType>())
        .MaxValue(TOptional<NumericType>())
        .MaxSliderValue(TOptional<NumericType>())
        .MinSliderValue(TOptional<NumericType>());
    //.Label()
    //[
    //    SNumericEntryBox<float>::BuildLabel(Label, LabelColor, LabelBackgroundColor)
    //];
}

void FFloat64Customization::CustomizeChildren(
    TSharedRef<IPropertyHandle> StructPropertyHandle,
    IDetailChildrenBuilder& StructBuilder,
    IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
    PropertyUtilities = StructCustomizationUtils.GetPropertyUtilities();

    TWeakPtr<IPropertyHandle> WeakHandlePtr = StructPropertyHandle;

    //CustomizeRotation(StructPropertyHandle, StructBuilder.AddCustomRow(LOCTEXT("LocationLabel", "Location")));
    auto Row = StructBuilder.AddCustomRow(LOCTEXT("Float64Label", "Value"));
    Row
        //.CopyAction(FUIAction(FExecuteAction::CreateSP(this, &FMatrixStructCustomization::OnCopy, FTransformField::Location, WeakHandlePtr)))
        //.PasteAction(FUIAction(FExecuteAction::CreateSP(this, &FMatrixStructCustomization::OnPaste, FTransformField::Location, WeakHandlePtr)))
        .NameContent()
        [
            StructPropertyHandle->CreatePropertyNameWidget(LOCTEXT("Float64Label", "Value"))
        ]
        .ValueContent()
        .MinDesiredWidth(375.0f)
        .MaxDesiredWidth(375.0f)
        [
            MakeValueWidget<double>(StructPropertyHandle, Value)
        ];
}

void FFloat64Customization::MakeHeaderRow(
    TSharedRef<IPropertyHandle>& InStructPropertyHandle,
    FDetailWidgetRow& Row)
{
    Row
        .NameContent()
        [
            InStructPropertyHandle->CreatePropertyNameWidget()
        ]
        .ValueContent()
        .MinDesiredWidth(0.0f)
        .MaxDesiredWidth(0.0f)
        [
            SNullWidget::NullWidget
        ];
}

template <typename NumericType>
TOptional<NumericType> FFloat64Customization::OnGetValue(
    TWeakPtr<IPropertyHandle> WeakHandlePtr,
    TSharedRef<NumericType> Value) const
{
    return Value.Get();
}

template <typename NumericType>
void FFloat64Customization::OnValueCommitted(
    NumericType NewValue, 
    ETextCommit::Type CommitType,
    TWeakPtr<IPropertyHandle> WeakHandlePtr, 
    TSharedRef<NumericType> Value)
{
    if(!bIsUsingSlider && !GIsTransacting)
    {
        //Value = MakeShareable(NewValue);
        UpdateValue(WeakHandlePtr);
    }
}

template <typename NumericType>
void FFloat64Customization::OnValueChanged(
    NumericType NewValue, 
    TWeakPtr<IPropertyHandle> WeakHandlePtr,
    TSharedRef<NumericType> Value)
{
    if(bIsUsingSlider)
    {
        //Value = MakeShareable(NewValue);
        UpdateValue(WeakHandlePtr);
    }
}

void FFloat64Customization::OnBeginSliderMovement()
{
    bIsUsingSlider = true;
}

template <typename NumericType>
void FFloat64Customization::OnEndSliderMovement(
    NumericType NewValue, 
    TWeakPtr<IPropertyHandle> WeakHandlePtr,
    TSharedRef<NumericType> Value)
{
    bIsUsingSlider = false;

    //Value = MakeShareable(NewValue);
    UpdateValue(WeakHandlePtr);
}

bool FFloat64Customization::UpdateValue(TWeakPtr<IPropertyHandle> WeakHandlePtr) const
{
    const auto PropertyHandle = WeakHandlePtr.Pin();
    if (!PropertyHandle.IsValid())
        return false;

    TArray<void*> RawData;
    PropertyHandle->AccessRawData(RawData);

    TArray<UObject*> OuterObjects;
    PropertyHandle->GetOuterObjects(OuterObjects);

    // The object array should either be empty or the same size as the raw data array.
    check(!OuterObjects.Num() || OuterObjects.Num() == RawData.Num());

    // Persistent flag that's set when we're in the middle of an interactive change (note: assumes multiple interactive changes do not occur in parallel).
    static auto bIsInteractiveChangeInProgress = false;

    auto bNotifiedPreChange = false;
    for (auto ValueIndex = 0; ValueIndex < RawData.Num(); ValueIndex++)
    {
        const auto DoubleValue = reinterpret_cast<double*>(RawData[0]);
        if (DoubleValue != nullptr)
        {
            const double PreviousValue = *DoubleValue;

            //FRotator Rotation(
            //    CachedRotationPitch->IsSet() ? CachedRotationPitch->Get() : CurrentRotation.Pitch,
            //    CachedRotationYaw->IsSet() ? CachedRotationYaw->Get() : CurrentRotation.Yaw,
            //    CachedRotationRoll->IsSet() ? CachedRotationRoll->Get() : CurrentRotation.Roll
            //);
            //FVector Translation(
            //    CachedTranslationX->IsSet() ? CachedTranslationX->Get() : CurrentTranslation.X,
            //    CachedTranslationY->IsSet() ? CachedTranslationY->Get() : CurrentTranslation.Y,
            //    CachedTranslationZ->IsSet() ? CachedTranslationZ->Get() : CurrentTranslation.Z
            //);
            //FVector Scale(
            //    CachedScaleX->IsSet() ? CachedScaleX->Get() : CurrentScale.X,
            //    CachedScaleY->IsSet() ? CachedScaleY->Get() : CurrentScale.Y,
            //    CachedScaleZ->IsSet() ? CachedScaleZ->Get() : CurrentScale.Z
            //);

            const auto NewValue = PreviousValue;            
            if (!bNotifiedPreChange && (!FMath::IsNearlyEqual(*DoubleValue, NewValue, 0.0) || (!bIsUsingSlider && bIsInteractiveChangeInProgress)))
            {
                if (!bIsInteractiveChangeInProgress)
                    GEditor->BeginTransaction(FText::Format(NSLOCTEXT("FTransformStructCustomization", "SetPropertyValue", "Set {0}"), PropertyHandle->GetPropertyDisplayName()));

                PropertyHandle->NotifyPreChange();
                bNotifiedPreChange = true;

                bIsInteractiveChangeInProgress = bIsUsingSlider;
            }

            // Set the new value.
            *DoubleValue = NewValue;

            // Propagate default value changes after updating, for archetypes. As per usual, we only propagate the change if the instance matches the archetype's value.
            // Note: We cannot use the "normal" PropertyNode propagation logic here, because that is string-based and the decision to propagate relies on an exact value match.
            // Here, we're dealing with conversions between FTransform and FVector/FRotator values, so there is some precision loss that requires a tolerance when comparing values.
            if (ValueIndex < OuterObjects.Num() && OuterObjects[ValueIndex]->IsTemplate())
            {
                TArray<UObject*> ArchetypeInstances;
                OuterObjects[ValueIndex]->GetArchetypeInstances(ArchetypeInstances);
                for (auto ArchetypeInstance : ArchetypeInstances)
                {
                    auto* CurrentValue = reinterpret_cast<double*>(PropertyHandle->GetValueBaseAddress(reinterpret_cast<uint8*>(ArchetypeInstance)));
                    if (CurrentValue && FMath::IsNearlyEqual(*CurrentValue, PreviousValue, 0.0))
                        *CurrentValue = NewValue;
                }
            }
        }
    }

    if (bNotifiedPreChange)
    {
        PropertyHandle->NotifyPostChange(bIsUsingSlider ? EPropertyChangeType::Interactive : EPropertyChangeType::ValueSet);

        if (!bIsUsingSlider)
        {
            GEditor->EndTransaction();
            bIsInteractiveChangeInProgress = false;
        }
    }

    if (PropertyUtilities.IsValid() && !bIsInteractiveChangeInProgress)
    {
        const FPropertyChangedEvent ChangeEvent(PropertyHandle->GetProperty(), EPropertyChangeType::ValueSet);
        PropertyUtilities->NotifyFinishedChangingProperties(ChangeEvent);
    }

    return true;
}


/*
void FFloat64Customization::OnCopy(TWeakPtr<IPropertyHandle> PropertyHandlePtr)
{
    const auto PropertyHandle = PropertyHandlePtr.Pin();
    if (!PropertyHandle.IsValid())
        return;

    CacheValues(PropertyHandle);

    const auto Value = CachedInnerValue->Get();
    const auto CopyStr = FString::Printf(TEXT("(%f)"), Value);

    if (!CopyStr.IsEmpty())
        FPlatformApplicationMisc::ClipboardCopy(*CopyStr);
}

void FFloat64Customization::OnPaste(TWeakPtr<IPropertyHandle> PropertyHandlePtr)
{
    const auto PropertyHandle = PropertyHandlePtr.Pin();
    if (!PropertyHandle.IsValid())
        return;

    FString PastedText;
    FPlatformApplicationMisc::ClipboardPaste(PastedText);

    FFloat64 Value;
    if(Value.InitFromString(PastedText))
    {
        FScopedTransaction Transaction(LOCTEXT("PasteFloat64", "Paste Float64"));
        CachedInnerValue->Set(Value);
        FlushValues(PropertyHandle);
    }
}*/

#undef LOCTEXT_NAMESPACE
