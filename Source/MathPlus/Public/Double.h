#pragma once

#include "CoreMinimal.h"

#include "Double.generated.h"

USTRUCT(BlueprintType)
struct MATHPLUS_API FDouble
{
    GENERATED_BODY()

public:
#pragma region Constructors
    FDouble();
    FDouble(const double& Value);
    explicit FDouble(EForceInit) { }
#pragma endregion Constructors

    double GetValue() const;
    void SetValue(const double& Value);

#pragma region Operators
    FDouble operator+(const FDouble& Other) const;
    FDouble operator+(const double& Other) const;
    FDouble operator+=(const FDouble& Other);
    FDouble operator+=(const double& Other);

    FDouble operator-(const FDouble& Other) const;
    FDouble operator-(const double& Other) const;
    FDouble operator-=(const FDouble& Other);
    FDouble operator-=(const double& Other);

    FDouble operator*(const FDouble& Other) const;
    FDouble operator*(const double& Other) const;
    FDouble operator*=(const FDouble& Other);
    FDouble operator*=(const double& Other);

    FDouble operator/(const FDouble& Other) const;
    FDouble operator/(const double& Other) const;
    FDouble operator/=(const FDouble& Other);
    FDouble operator/=(const double& Other);

    /** Negate */
    FDouble& operator-();

    operator double() const { return GetValue(); }

    bool operator==(const FDouble& Other) const;
    bool operator==(const double& Other) const;

    bool operator!=(const FDouble& Other) const;
    bool operator!=(const double& Other) const;

    bool operator>(const FDouble& Other) const;
    bool operator>(const double& Other) const;
    bool operator<(const FDouble& Other) const;
    bool operator<(const double& Other) const;

    friend uint32 GetTypeHash(const FDouble& Value) { return GetTypeHash(Value.GetValue()); }
#pragma endregion Operators

protected:
    UPROPERTY()
    TArray<uint8> Bytes;
};