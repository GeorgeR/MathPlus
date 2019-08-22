#pragma once

#include "CoreMinimal.h"
#include "Customizations/MathStructCustomizations.h"
#include "Float64.h"

class FDetailWidgetRow;
class IDetailLayoutBuilder;
class IPropertyUtilities;

class FFloat64Customization
    : public FMathStructCustomization
{
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance();

    ///** IPropertyTypeCustomization interface */
    void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

    /** FMathStructCustomization interface */
    void MakeHeaderRow(TSharedRef<class IPropertyHandle>& InStructPropertyHandle, FDetailWidgetRow& Row) override;

protected:
    TSharedRef<double> Value;

    void OnCopy(TWeakPtr<IPropertyHandle> PropertyHandlePtr) { }
    void OnPaste(TWeakPtr<IPropertyHandle> PropertyHandlePtr) { }

    template<typename NumericType>
    TSharedRef<SWidget> MakeValueWidget(TSharedRef<IPropertyHandle>& StructPropertyHandle, TSharedRef<NumericType>& Value, const FLinearColor& LabelColor = FCoreStyle::Get().GetColor("DefaultForeground"), const FLinearColor& LabelBackgroundColor = FCoreStyle::Get().GetColor("InvertedForeground"));

private:
    template<typename NumericType>
    TOptional<NumericType> OnGetValue(TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef<NumericType> Value) const;

    template<typename NumericType>
    void OnValueCommitted(NumericType NewValue, ETextCommit::Type CommitType, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef<NumericType> Value);

    template<typename NumericType>
    void OnValueChanged(NumericType NewValue, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef<NumericType> Value);

    void OnBeginSliderMovement();

    template<typename NumericType>
    void OnEndSliderMovement(NumericType NewValue, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef<NumericType> Value);

protected:
    TSharedPtr<IPropertyUtilities> PropertyUtilities;

    bool UpdateValue(TWeakPtr<IPropertyHandle> WeakHandlePtr) const;
};