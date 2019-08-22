#include "MathStructProxyCustomizations.h"

#include "Editor.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailLayoutBuilder.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "HAL/PlatformApplicationMisc.h"

void FMathStructProxyCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
    PropertyUtilities = StructCustomizationUtils.GetPropertyUtilities();
}

void FMathStructProxyCustomization::MakeHeaderRow(TSharedRef<class IPropertyHandle>& StructPropertyHandle, FDetailWidgetRow& Row)
{
}

template<typename ProxyType, typename NumericType>
TSharedRef<SWidget> FMathStructProxyCustomization::MakeNumericProxyWidget(TSharedRef<IPropertyHandle>& StructPropertyHandle, TSharedRef< TProxyProperty<ProxyType, NumericType> >& ProxyValue, const FText& Label, bool bRotationInDegrees, const FLinearColor& LabelColor, const FLinearColor& LabelBackgroundColor)
{
    TWeakPtr<IPropertyHandle> WeakHandlePtr = StructPropertyHandle;

    return
        SNew(SNumericEntryBox<NumericType>)
        .Value(this, &FMathStructProxyCustomization::OnGetValue<ProxyType, NumericType>, WeakHandlePtr, ProxyValue)
        .Font(IDetailLayoutBuilder::GetDetailFont())
        .UndeterminedString(NSLOCTEXT("PropertyEditor", "MultipleValues", "Multiple Values"))
        .OnValueCommitted(this, &FMathStructProxyCustomization::OnValueCommitted<ProxyType, NumericType>, WeakHandlePtr, ProxyValue)
        .OnValueChanged(this, &FMathStructProxyCustomization::OnValueChanged<ProxyType, NumericType>, WeakHandlePtr, ProxyValue)
        .OnBeginSliderMovement(this, &FMathStructProxyCustomization::OnBeginSliderMovement)
        .OnEndSliderMovement(this, &FMathStructProxyCustomization::OnEndSliderMovement<ProxyType, NumericType>, WeakHandlePtr, ProxyValue)
        .LabelVAlign(VAlign_Fill)
        .LabelPadding(0)
        // Only allow spin on handles with one object.  Otherwise it is not clear what value to spin
        .AllowSpin(StructPropertyHandle->GetNumOuterObjects() == 1)
        .MinValue(TOptional<NumericType>())
        .MaxValue(TOptional<NumericType>())
        .MaxSliderValue(bRotationInDegrees ? 360.0f : TOptional<NumericType>())
        .MinSliderValue(bRotationInDegrees ? 0.0f : TOptional<NumericType>())
        .Label()
        [
            SNumericEntryBox<float>::BuildLabel(Label, LabelColor, LabelBackgroundColor)
        ];
}


template<typename ProxyType, typename NumericType>
TOptional<NumericType> FMathStructProxyCustomization::OnGetValue(TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue) const
{
    if (CacheValues(WeakHandlePtr))
        return ProxyValue->Get();

    return TOptional<NumericType>();
}

template<typename ProxyType, typename NumericType>
void FMathStructProxyCustomization::OnValueCommitted(NumericType NewValue, ETextCommit::Type CommitType, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue)
{
    if (!bIsUsingSlider && !GIsTransacting)
    {
        ProxyValue->Set(NewValue);
        FlushValues(WeakHandlePtr);
    }
}

template<typename ProxyType, typename NumericType>
void FMathStructProxyCustomization::OnValueChanged(NumericType NewValue, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue)
{
    if (bIsUsingSlider)
    {
        ProxyValue->Set(NewValue);
        FlushValues(WeakHandlePtr);
    }
}

void FMathStructProxyCustomization::OnBeginSliderMovement()
{
    bIsUsingSlider = true;
}

template<typename ProxyType, typename NumericType>
void FMathStructProxyCustomization::OnEndSliderMovement(NumericType NewValue, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue)
{
    bIsUsingSlider = false;

    ProxyValue->Set(NewValue);
    FlushValues(WeakHandlePtr);
}
