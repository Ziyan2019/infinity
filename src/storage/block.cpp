//
// Created by JinHai on 2022/7/31.
//

#include "block.h"
#include "common/utility/infinity_assert.h"

#include <sstream>

namespace infinity {

Block::Block(const std::shared_ptr<TableDefinition>& table_def, TableType type, uint64_t limit)
    : type_(type), block_limit_(limit), column_defs_(table_def->columns()) {
    for(const auto& column_def: table_def->columns()) {
        auto logical_type = column_def.logical_type();
        switch(logical_type.GetTypeId()) {
            case LogicalTypeId::kBoolean: {
                columns_.emplace_back(std::make_shared<Chunk<BooleanT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kTinyInt: {
                columns_.emplace_back(std::make_shared<Chunk<TinyIntT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kSmallInt: {
                columns_.emplace_back(std::make_shared<Chunk<SmallIntT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kInteger: {
                columns_.emplace_back(std::make_shared<Chunk<IntegerT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kBigInt: {
                columns_.emplace_back(std::make_shared<Chunk<BigIntT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kFloat: {
                columns_.emplace_back(std::make_shared<Chunk<FloatT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kDouble: {
                columns_.emplace_back(std::make_shared<Chunk<DoubleT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kDecimal: {
                columns_.emplace_back(std::make_shared<Chunk<DecimalT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kDate: {
                columns_.emplace_back(std::make_shared<Chunk<DateT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kTime: {
                columns_.emplace_back(std::make_shared<Chunk<TimeT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kDateTime: {
                columns_.emplace_back(std::make_shared<Chunk<DateTimeT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kInterval: {
                columns_.emplace_back(std::make_shared<Chunk<IntervalT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kVarchar: {
                columns_.emplace_back(std::make_shared<Chunk<VarcharT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            case LogicalTypeId::kText: {
                columns_.emplace_back(std::make_shared<Chunk<TextT>>(TableType::kFixedRowCount, logical_type, limit));
                break;
            }
            default:
                StorageError("Wrong column type");
        }
    }
}


void
Block::Append(const std::vector<std::any>& values, uint64_t start_idx) {
    uint64_t column_count = columns_.size();
    StorageAssert(values.size() == column_count, "Wrong column data are appended to the row group");

    for(uint64_t i = 0; i < column_count; ++ i) {
        switch(column_defs_[i].logical_type().GetTypeId()) {
            case LogicalTypeId::kBoolean: {
                auto column = std::any_cast<std::shared_ptr<Chunk<BooleanT>>>(columns_[i]);
                auto value = std::any_cast<BooleanT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kTinyInt: {
                auto column = std::any_cast<std::shared_ptr<Chunk<TinyIntT>>>(columns_[i]);
                auto value = std::any_cast<TinyIntT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kSmallInt: {
                auto column = std::any_cast<std::shared_ptr<Chunk<SmallIntT>>>(columns_[i]);
                auto value = std::any_cast<SmallIntT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kInteger: {
                auto column = std::any_cast<std::shared_ptr<Chunk<IntegerT>>>(columns_[i]);
                auto value = std::any_cast<IntegerT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kBigInt: {
                auto column = std::any_cast<std::shared_ptr<Chunk<BigIntT>>>(columns_[i]);
                auto value = std::any_cast<BigIntT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kFloat: {
                auto column = std::any_cast<std::shared_ptr<Chunk<FloatT>>>(columns_[i]);
                auto value = std::any_cast<FloatT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kDouble: {
                auto column = std::any_cast<std::shared_ptr<Chunk<DoubleT>>>(columns_[i]);
                auto value = std::any_cast<DoubleT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kDecimal: {
                auto column = std::any_cast<std::shared_ptr<Chunk<DecimalT>>>(columns_[i]);
                auto value = std::any_cast<DecimalT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kDate: {
                auto column = std::any_cast<std::shared_ptr<Chunk<DateT>>>(columns_[i]);
                auto value = std::any_cast<DateT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kTime: {
                auto column = std::any_cast<std::shared_ptr<Chunk<TimeT>>>(columns_[i]);
                auto value = std::any_cast<TimeT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kDateTime: {
                auto column = std::any_cast<std::shared_ptr<Chunk<DateTimeT>>>(columns_[i]);
                auto value = std::any_cast<DateTimeT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kInterval: {
                auto column = std::any_cast<std::shared_ptr<Chunk<IntervalT>>>(columns_[i]);
                auto value = std::any_cast<IntervalT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kVarchar: {
                auto column = std::any_cast<std::shared_ptr<Chunk<VarcharT>>>(columns_[i]);
                auto value = std::any_cast<VarcharT>(values[i]);
                column->Append(value);
                break;
            }
            case LogicalTypeId::kText: {
                auto column = std::any_cast<std::shared_ptr<Chunk<TextT>>>(columns_[i]);
                auto value = std::any_cast<TextT>(values[i]);
                column->Append(value);
                break;
            }
            default:
                StorageError("Wrong column type");
        }
    }

    ++ row_count_;
}

std::string
Block::AsStringRow() const {
    std::stringstream ss;

    uint64_t column_count = column_defs_.size();

    // Iterator all row of the blocks
    for(int64_t row_id = 0; row_id < row_count_; ++ row_id) {

        // Iterate all column of this block
        for(uint64_t column_id = 0; column_id < column_count; ++ column_id) {

            // Get the chunk type
            const LogicalType& chunk_type = column_defs_[column_id].logical_type();


            switch(chunk_type.GetTypeId()) {
                case LogicalTypeId::kBoolean: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<BooleanT>>>(columns_[column_id]);
                    bool value = chunk->data()[row_id];
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kTinyInt: {

                    auto chunk = std::any_cast<std::shared_ptr<Chunk<TinyIntT>>>(columns_[column_id]);
                    int8_t value = chunk->data()[row_id];
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kSmallInt: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<SmallIntT>>>(columns_[column_id]);
                    int16_t value = chunk->data()[row_id];
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kInteger: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<IntegerT>>>(columns_[column_id]);
                    int32_t value = chunk->data()[row_id];
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kBigInt: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<BigIntT>>>(columns_[column_id]);
                    int64_t value = chunk->data()[row_id];
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kFloat: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<FloatT>>>(columns_[column_id]);
                    float value = chunk->data()[row_id];
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kDouble: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<DoubleT>>>(columns_[column_id]);
                    double value = chunk->data()[row_id];
                    break;
                }
                case LogicalTypeId::kDecimal: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<DecimalT>>>(columns_[column_id]);
                    DecimalT value = chunk->data()[row_id];

                    // TODO: Decimal type to string
                    ss << "Decimal Value" << " ";
                    break;
                }
                case LogicalTypeId::kDate: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<DateT>>>(columns_[column_id]);
                    int32_t value = chunk->data()[row_id]; // DateT is int32_t
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kTime: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<TimeT>>>(columns_[column_id]);
                    int32_t value = chunk->data()[row_id]; // TimeT is int32_t
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kDateTime: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<DateTimeT>>>(columns_[column_id]);
                    int64_t value = chunk->data()[row_id]; // DateTimeT is int64_t
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kInterval: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<IntervalT>>>(columns_[column_id]);
                    int64_t value = chunk->data()[row_id]; // IntervalT is int64_t
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kVarchar: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<VarcharT>>>(columns_[column_id]);
                    std::string value = chunk->data()[row_id]; // VarcharT is string
                    ss << value << " ";
                    break;
                }
                case LogicalTypeId::kText: {
                    auto chunk = std::any_cast<std::shared_ptr<Chunk<TextT>>>(columns_[column_id]);
                    std::string value = chunk->data()[row_id]; // TextT is string
                    ss << value << " ";
                    break;
                }
                default: {
                    StorageError("Wrong column type");
                }
            }
        }

        ss << std::endl;
    }

    return ss.str();
}
}