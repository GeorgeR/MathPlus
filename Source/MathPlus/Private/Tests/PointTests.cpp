#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#if WITH_EDITOR

/* TEST_NAME doesn't work for some reason */
#define PRETTY_NAME(ElementType, Dimensions, Operation) FString::Printf(TEXT("MathPlus.Point<%s,%i>.%s"), #ElementType, Dimensions, #Operation)

#include "Tests/AutomationCommon.h"
#include "Point.h"
#include "Point4.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPoint_Double_4_Construct_Test, PRETTY_NAME(Double, 4, Construct), EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPoint_Double_4_Construct_Test::RunTest(const FString& Parameters)
{
    auto Point4 = FPoint4D();
    TestEqual(TEXT("Value should be zero"), Point4.X, 0.0);
    TestEqual(TEXT("Value should be zero"), Point4.Y, 0.0);
    TestEqual(TEXT("Value should be zero"), Point4.Z, 0.0);
    TestEqual(TEXT("Value should be zero"), Point4.W, 0.0);
    
    Point4 = FPoint4D(55.0);
    TestEqual(TEXT("Value should be 55.0"), Point4.X, 55.0);
    TestEqual(TEXT("Value should be 55.0"), Point4.Y, 55.0);
    TestEqual(TEXT("Value should be 55.0"), Point4.Z, 55.0);
    TestEqual(TEXT("Value should be 55.0"), Point4.W, 55.0);

    Point4 = FPoint4D(55.0, 45.0, 40.0, 30.0);
    TestEqual(TEXT("Value should be 55.0"), Point4.X, 55.0);
    TestEqual(TEXT("Value should be 45.0"), Point4.Y, 45.0);
    TestEqual(TEXT("Value should be 40.0"), Point4.Z, 40.0);
    TestEqual(TEXT("Value should be 30.0"), Point4.W, 30.0);

    Point4 = FPoint4D(EForceInit::ForceInit);
    TestEqual(TEXT("Value should be zero"), Point4.X, 0.0);
    TestEqual(TEXT("Value should be zero"), Point4.Y, 0.0);
    TestEqual(TEXT("Value should be zero"), Point4.Z, 0.0);
    TestEqual(TEXT("Value should be zero"), Point4.W, 0.0);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPoint_Double_4_Accessor_Test, PRETTY_NAME(Double, 4, Accessor), EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPoint_Double_4_Accessor_Test::RunTest(const FString& Parameters)
{
    auto Point4 = FPoint4D(55.0, 45.0, 35.0, 25.0);
    
    auto X = Point4[0];
    TestEqual(TEXT("Value should be 55.0"), X, 55.0);

    auto Y = Point4[1];
    TestEqual(TEXT("Value should be 55.0"), X, 45.0);

    auto Z = Point4[2];
    TestEqual(TEXT("Value should be 55.0"), X, 35.0);

    auto W = Point4[3];
    TestEqual(TEXT("Value should be 55.0"), X, 25.0);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPoint_Double_4_Equality_Test, PRETTY_NAME(Double, 4, Equality), EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPoint_Double_4_Equality_Test::RunTest(const FString& Parameters)
{
    auto Left = FPoint4D(55.0, 45.0, 35.0, 25.0);
    auto Right = FPoint4D(50.0, 45.0, 35.0, 25.0);
    TestTrue(TEXT("Values aren't equal"), Left != Right);
    
    Right = FPoint4D(55.0, 45.0, 35.0, 25.0);
    TestTrue(TEXT("Values should be equal"), Left == Right);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPoint_Double_4_Addition_Test, PRETTY_NAME(Double, 4, Addition), EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPoint_Double_4_Addition_Test::RunTest(const FString& Parameters)
{
    auto Left = FPoint4D(55.0, 45.0, 35.0, 25.0);
    auto Right = FPoint4D(5.0, 10.0, 15.0, 20.0);
    //auto Result = Left + Right;
    //TestEqual(TEXT("Values should be not this"), Result, FPoint4D(60.0f, 55.0, 50.0, 45.0));

    return true;
}

#endif