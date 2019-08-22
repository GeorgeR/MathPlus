#pragma once

#include "CoreTypes.h"
#include "Templates/IsArithmetic.h"
#include "Templates/UnrealTypeTraits.h"
#include "Math/NumericLimits.h"
#include "Math/UnrealMathUtility.h"

/**
 * Adds to this value.
 *
 * @param Other The value to add to this value.
 * @return Reference to this value after addition.
 */
// +=

 /**
  * Gets the result of addition on this value.
  *
  * @param Other The other value to add to this.
  * @return A new combined value.
  */
// +

#pragma region Macros
#define __DEFINE_SCALAR_CMP_STACK(Type, BaseType, Op)           \
        bool operator##Op##(const Type##& Other) const;         \
        bool operator##Op##(const BaseType##& Other) const;

#define _DEFINE_SCALAR_CMP_STACK(Type, BaseType)         \
        __DEFINE_SCALAR_CMP_STACK(Type, BaseType, ==)    \
        __DEFINE_SCALAR_CMP_STACK(Type, BaseType, !=)    \
        __DEFINE_SCALAR_CMP_STACK(Type, BaseType, >)     \
        __DEFINE_SCALAR_CMP_STACK(Type, BaseType, >=)    \
        __DEFINE_SCALAR_CMP_STACK(Type, BaseType, <)     \
        __DEFINE_SCALAR_CMP_STACK(Type, BaseType, <=)

#define DEFINE_SCALAR_CMP_STACK() _DEFINE_SCALAR_CMP_STACK(TScalarType, TElementType)

#define __IMPL_SCALAR_CMP_STACK(DeclType, Type, BaseType, Op)               \
        bool DeclType##::operator##Op##(const Type##& Other) const          \
        {                                                                   \
            return GetValue() Op Other.GetValue();                          \
        }                                                                   \
                                                                            \
        bool DeclType##::operator##Op##(const BaseType##& Other) const      \
        {                                                                   \
            return GetValue() Op Other;                                     \
        }

#define _IMPL_SCALAR_CMP_STACK(DeclType, Type, BaseType)         \
        __IMPL_SCALAR_CMP_STACK(DeclType, Type, BaseType, ==)    \
        __IMPL_SCALAR_CMP_STACK(DeclType, Type, BaseType, !=)    \
        __IMPL_SCALAR_CMP_STACK(DeclType, Type, BaseType, >)     \
        __IMPL_SCALAR_CMP_STACK(DeclType, Type, BaseType, >=)    \
        __IMPL_SCALAR_CMP_STACK(DeclType, Type, BaseType, <)     \
        __IMPL_SCALAR_CMP_STACK(DeclType, Type, BaseType, <=)

#define IMPL_SCALAR_CMP_STACK(DeclType) _IMPL_SCALAR_CMP_STACK(DeclType, DeclType::TScalarType, DeclType::TElementType)

#define __DEFINE_SCALAR_OPERATOR_STACK(Type, BaseType, Op)      \
        Type& operator##Op##=(const Type##& Other);             \
        Type& operator##Op##=(const BaseType##& Other);         \
        Type operator##Op##(Type Other) const;                  \
        Type operator##Op##(BaseType Other) const;

#define _DEFINE_SCALAR_OPERATOR_STACK(Type, BaseType)      \
        __DEFINE_SCALAR_OPERATOR_STACK(Type, BaseType, +)  \
        __DEFINE_SCALAR_OPERATOR_STACK(Type, BaseType, -)  \
        __DEFINE_SCALAR_OPERATOR_STACK(Type, BaseType, *)  \
        __DEFINE_SCALAR_OPERATOR_STACK(Type, BaseType, /)

#define DEFINE_SCALAR_OPERATOR_STACK() _DEFINE_SCALAR_OPERATOR_STACK(TScalarType, TElementType)

#define __IMPL_SCALAR_OPERATOR_STACK(DeclType, Type, BaseType, Op)      \
        Type& DeclType##::operator##Op##=(const Type##& Other)          \
        {                                                               \
            SetValue(GetValue() Op Other.GetValue());                   \
            return *this;                                               \
        }                                                               \
                                                                        \
        Type& DeclType##::operator##Op##=(const BaseType##& Other)      \
        {                                                               \
            SetValue(GetValue() Op Other);                              \
            return *this;                                               \
        }                                                               \
                                                                        \
        Type DeclType##::operator##Op##(Type Other) const               \
        {                                                               \
            return Type(*this) += Other;                                \
        }                                                               \
                                                                        \
        Type DeclType##::operator##Op##(BaseType Other) const           \
        {                                                               \
            return Type(*this) += Other;                                \
        }

#define _IMPL_SCALAR_OPERATOR_STACK(DeclType, Type, BaseType)         \
        __IMPL_SCALAR_OPERATOR_STACK(DeclType, Type, BaseType, +)     \
        __IMPL_SCALAR_OPERATOR_STACK(DeclType, Type, BaseType, -)     \
        __IMPL_SCALAR_OPERATOR_STACK(DeclType, Type, BaseType, *)     \
        __IMPL_SCALAR_OPERATOR_STACK(DeclType, Type, BaseType, /)

#define IMPL_SCALAR_OPERATOR_STACK(DeclType) _IMPL_SCALAR_OPERATOR_STACK(DeclType, DeclType::TScalarType, DeclType::TElementType)

#pragma endregion Macros