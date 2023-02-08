//
// Created by JinHai on 2022/9/14.
//

#include "count.h"
#include "function/aggregate_function.h"
#include "function/aggregate_function_set.h"

namespace infinity {

struct CountState {
public:
    u64 count;

    void Initialize() {
        this->count = 0;
    }

    void Update() {

    }

    void Finalize() {
    }
};

void
RegisterCountFunction(const UniquePtr<Catalog> &catalog_ptr) {
    String func_name = "COUNT";

    SharedPtr<AggregateFunctionSet> function_set_ptr = MakeShared<AggregateFunctionSet>(func_name);

    AggregateFunction count_boolean
            = AggregateFunction::UnaryAggregate<CountState, BooleanT, BigIntT>(func_name,
                                                                               DataType(LogicalType::kBoolean),
                                                                               DataType(LogicalType::kBigInt));
    function_set_ptr->AddFunction(count_boolean);
    AggregateFunction count_tinyint
            = AggregateFunction::UnaryAggregate<CountState, TinyIntT, BigIntT>(func_name,
                                                                               DataType(LogicalType::kTinyInt),
                                                                               DataType(LogicalType::kBigInt));
    function_set_ptr->AddFunction(count_tinyint);
    catalog_ptr->AddFunctionSet(function_set_ptr);
}

}
