//
// Created by JinHai on 2022/11/20.
//

#pragma once

namespace infinity {

struct BaseMixedType {

// static member variable
public:
    static constexpr i64 ELEMENT_SIZE = 16;
    static constexpr i64 TUPLE_SIZE = ELEMENT_SIZE * 2;
    static constexpr i64 SHORT_STR_LIMIT = 14;
    static constexpr i64 SHORT_NESTED_STR_LIMIT = 12;
    static constexpr i64 LONG_STR_HEADER = 5;
    static constexpr i64 LONG_NESTED_STR_HEADER = 3;

public:

    BaseMixedType() = default;

    explicit
    BaseMixedType(MixedValueType value_type): type(value_type) {}

    MixedValueType type;
};

}