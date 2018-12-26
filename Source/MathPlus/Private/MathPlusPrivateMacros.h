#pragma once

#define DECLARE_OPERATOR_EQUALITY(ContainerType, ElementType)   \
    bool operator==(const ContainerType<ElementType>& Other) const;   \
    bool operator!=(const ContainerType<ElementType>& Other) const;