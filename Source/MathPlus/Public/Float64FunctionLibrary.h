#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Float64.h"

#include "Float64FunctionLibrary.generated.h"

UCLASS(meta = (BlueprintThreadSafe))
class MATHPLUS_API UFloat64FunctionLibrary
    : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
#pragma region Arithmetic Operators
    /** Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Float64 + Float64", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|Float64")
    static FFloat64 Add_Float64Float64(FFloat64 A, FFloat64 B);

    /** Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Float64 + float", CompactNodeTitle = "+", Keywords = "+ add plus"), Category = "Math|Float64")
    static FFloat64 Add_Float64Float(FFloat64 A, float B = 1.0) { return A + FFloat64(B); }

    /** Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Float64 - Float64", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Math|Float64")
    static FFloat64 Subtract_Float64Float64(FFloat64 A, FFloat64 B);

    /** Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Float64 - float", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Math|Float64")
    static FFloat64 Subtract_Float64Float(FFloat64 A, float B = 1.0) { return A - FFloat64(B); }

    /** Multiplication (A * B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Float64 * Float64", CompactNodeTitle = "*", Keywords = "* multiply", CommutativeAssociativeBinaryOperator = "true"), Category="Math|Float64")
	static FFloat64 Multiply_Float64Float64(FFloat64 A, FFloat64 B);

    /** Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Float64 * float", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Math|Float64")
    static FFloat64 Multiply_Float64Float(FFloat64 A, float B = 1.0) { return A * FFloat64(B); }

	/** Division (A / B) */
	UFUNCTION(BlueprintPure, CustomThunk, meta=(DisplayName = "Float64 / Float64", CompactNodeTitle = "/", Keywords = "/ divide division"), Category="Math|Float64")
	static FFloat64 Divide_Float64Float64(FFloat64 A, FFloat64 B);
    static FFloat64 GenericDivide_Float64Float64(FFloat64 A, FFloat64 B);
    DECLARE_FUNCTION(execDivide_Float64Float64)
    {
        P_GET_PROPERTY(UDoubleProperty, A);
        P_GET_PROPERTY(UDoubleProperty, B);
        P_FINISH;

        if(B == 0.0)
        {
            FFrame::KismetExecutionMessage(*FString::Printf(TEXT("Divide by zero detected: %f / 0\n%s"), A, *Stack.GetStackTrace()), ELogVerbosity::Warning);
            *(double*)RESULT_PARAM = 0;
            return;
        }

        *(double*)RESULT_PARAM = GenericDivide_Float64Float64(FFloat64(A), FFloat64(B));
    }

	/** Division (A / B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Float64 / float", CompactNodeTitle = "/", Keywords = "/ divide division"), Category="Math|Float64")
	static FFloat64 Divide_Float64Float(FFloat64 A, float B = 1.0) { return A / FFloat64(B); }
#pragma endregion Arithmetic Operators

#pragma region Comparison Operators
	/** Returns true if A is equal to B (A == B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal (Float64)", CompactNodeTitle = "==", Keywords = "== equal"), Category="Math|Float64")
	static bool EqualEqual_Float64Float64(FFloat64 A, FFloat64 B);

    /** Returns true if A is equal to B (A == B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal (float)", CompactNodeTitle = "==", Keywords = "== equal"), Category="Math|Float64")
    static bool EqualEqual_Float64Float(FFloat64 A, float B) { return (float)A == B; }

    /** Returns true if A is equal to B (A == B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal (Float64)", CompactNodeTitle = "==", Keywords = "== equal"), Category="Math|Float64")
    static bool EqualEqual_FloatFloat64(float A, FFloat64 B) { return A == (float)B; }

	/** Returns true if A is not equal to B (A != B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "NotEqual (Float64)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category="Math|Float64")
	static bool NotEqual_Float64Float64(FFloat64 A, FFloat64 B);

	/** Returns true if A is not equal to B (A != B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "NotEqual (float)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category="Math|Float64")
    static bool NotEqual_Float64Float(FFloat64 A, float B) { return (float)A != B; }

	/** Returns true if A is not equal to B (A != B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "NotEqual (Float64)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category="Math|Float64")
    static bool NotEqual_FloatFloat64(float A, FFloat64 B) { return A != (float)B; }

	/** Returns true if A is greater than B (A > B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Float64 > Float64", CompactNodeTitle = ">", Keywords = "> greater"), Category="Math|Float64")
	static bool Greater_Float64Float64(FFloat64 A, FFloat64 B);

	/** Returns true if A is greater than B (A > B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Float64 > float", CompactNodeTitle = ">", Keywords = "> greater"), Category = "Math|Float64")
    static bool Greater_Float64Float(FFloat64 A, float B) { return (float)A > B; }

	/** Returns true if A is greater than B (A > B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "float > Float64", CompactNodeTitle = ">", Keywords = "> greater"), Category = "Math|Float64")
    static bool Greater_FloatFloat64(float A, FFloat64 B) { return A > (float)B; }

	/** Returns true if A is greater than or equal to B (A >= B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Float64 >= Float64", CompactNodeTitle = ">=", Keywords = ">= greater"), Category="Math|Float64")
	static bool GreaterEqual_Float64Float64(FFloat64 A, FFloat64 B);

	/** Returns true if A is greater than or equal to B (A >= B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Float64 >= float", CompactNodeTitle = ">=", Keywords = ">= greater"), Category="Math|Float64")
    static bool GreaterEqual_Float64Float(FFloat64 A, float B) { return (float)A >= B; }

    /** Returns true if A is greater than or equal to B (A >= B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "float >= Float64", CompactNodeTitle = ">=", Keywords = ">= greater"), Category="Math|Float64")
	static bool GreaterEqual_FloatFloat64(float A, FFloat64 B) { return A >= (float)B; }

	/** Returns true if A is less than B (A < B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Float64 < Float64", CompactNodeTitle = "<", Keywords = "< less"), Category="Math|Float64")
	static bool Less_Float64Float64(FFloat64 A, FFloat64 B);

	/** Returns true if A is less than B (A < B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Float64 < float", CompactNodeTitle = "<", Keywords = "< less"), Category="Math|Float64")
	static bool Less_Float64Float(FFloat64 A, float B) { return (float)A < B; }

	/** Returns true if A is less than B (A < B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "float < Float64", CompactNodeTitle = "<", Keywords = "< less"), Category="Math|Float64")
	static bool Less_FloatFloat64(float A, FFloat64 B) { return A < (float)B; }

	/** Returns true if A is less than or equal to B (A <= B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Float64 <= Float64", CompactNodeTitle = "<=", Keywords = "<= less"), Category="Math|Float64")
	static bool LessEqual_Float64Float64(FFloat64 A, FFloat64 B);

	/** Returns true if A is less than or equal to B (A <= B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Float64 <= float", CompactNodeTitle = "<=", Keywords = "<= less"), Category="Math|Float64")
	static bool LessEqual_Float64Float(FFloat64 A, float B) { return (float)A <= B; }

	/** Returns true if A is less than or equal to B (A <= B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "float <= Float64", CompactNodeTitle = "<=", Keywords = "<= less"), Category="Math|Float64")
	static bool LessEqual_FloatFloat64(float A, FFloat64 B) { return A <= (float)B; }
#pragma endregion Comparison Operators
};

FORCEINLINE_DEBUGGABLE FFloat64 UFloat64FunctionLibrary::GenericDivide_Float64Float64(FFloat64 A, FFloat64 B)
{
    return A / B;
}