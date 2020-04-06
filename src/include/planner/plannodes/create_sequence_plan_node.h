#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "parser/create_statement.h"
#include "parser/select_statement.h"
#include "planner/plannodes/abstract_plan_node.h"
#include "planner/plannodes/plan_visitor.h"

namespace terrier::planner {

/**
 * Plan node for creating sequences
 */
    class CreateSequencePlanNode : public AbstractPlanNode {
    public:
        class Builder : public AbstractPlanNode::Builder<Builder> {
        public:
            Builder() = default;

            /**
             * @param index_name the name of the index
             * @return builder object
             */
            Builder &SetSequenceName(std::string sequence_name) {
                sequence_name_ = std::move(sequence_name);
                return *this;
            }

            Builder &SetSequenceStart(int32_t sequence_start) {
                sequence_start_ = sequence_start;
                return *this;
            }

            Builder &SetSequenceIncrement(int32_t sequence_increment) {
                sequence_increment_ = sequence_increment;
                return *this;
            }

            Builder &SetSequenceMaxValue(int32_t sequence_max_value) {
                sequence_max_value_ = sequence_max_value;
                return *this;
            }

            Builder &SetSequenceMinValue(int32_t sequence_min_value) {
                sequence_min_value_ = sequence_min_value;
                return *this;
            }

            Builder &SetSequenceCache(int32_t sequence_cache) {
                sequence_cache_ = sequence_cache;
                return *this;
            }

            Builder &SetSequenceCycle(bool sequence_cycle) {
                sequence_cycle_ = sequence_cycle;
                return *this;
            }

            std::unique_ptr<CreateSequencePlanNode> Build() {
                return std::unique_ptr<CreateSequencePlanNode>(
                        new CreateSequencePlanNode(std::move(children_), std::move(output_schema_),
                                                std::move(sequence_name_), sequence_start_, sequence_start_,
                                                sequence_max_value_, sequence_min_value_, sequence_cache_,
                                                sequence_cycle_));
            }


        protected:
            /**
             * Name of the sequence
             */
            std::string sequence_name_;

            int32_t sequence_start_;

            int32_t sequence_increment_;

            int32_t sequence_max_value_;

            int32_t sequence_min_value_;

            int32_t sequence_cache_;

            bool sequence_cycle_;
        };

    private:
        CreateSequencePlanNode(std::vector<std::unique_ptr<AbstractPlanNode>> &&children,
                               std::unique_ptr<OutputSchema> output_schema,
                               std::string sequence_name, int32_t sequence_start,
                               int32_t sequence_increment, int32_t sequence_max_value,
                               int32_t sequence_min_value, int32_t sequence_cache,
                               bool sequence_cycle)
                : AbstractPlanNode(std::move(children), std::move(output_schema)),
                  sequence_name_(std::move(sequence_name)),
                  sequence_increment_(sequence_increment),
                  sequence_max_value_(sequence_max_value),
                  sequence_min_value_(sequence_min_value),
                  sequence_cache_(sequence_cache),
                  sequence_cycle_(sequence_cycle){}

    public:
        /**
         * @return the type of this plan node
         */
        PlanNodeType GetPlanNodeType() const override { return PlanNodeType::CREATE_SEQUENCE; }


        /**
         * @return name of the sequence
         */
        std::string GetSequenceName() const { return sequence_name_; }

        /**
         * @return start of the sequence
         */
        int32_t GetSequenceStart() const { return sequence_start_; }

        /**
         * @return increment of the sequence
         */
        int32_t GetSequenceIncrement() const { return sequence_increment_; }

        /**
         * @return max_value of the sequence
         */
        int32_t GetSequenceMaxValue() const { return sequence_max_value_; }

        /**
         * @return min_value of the sequence
         */
        int32_t GetSequenceMinValue() const { return sequence_min_value_; }

        /**
         * @return cache size of the sequence
         */
        int32_t GetSequenceCache() const { return sequence_cache_; }

        /**
         * @return cycle of the sequence
         */
        bool GetSequenceCycle() const { return sequence_cycle_; }

        /**
         * @return the hashed value of this plan node
         */
        common::hash_t Hash() const override;

        bool operator==(const AbstractPlanNode &rhs) const override;

        void Accept(common::ManagedPointer<PlanVisitor> v) const override { v->Visit(this); }

        nlohmann::json ToJson() const override;
        std::vector<std::unique_ptr<parser::AbstractExpression>> FromJson(const nlohmann::json &j) override;

    private:
        std::string sequence_name_;
        int32_t sequence_start_;
        int32_t sequence_increment_;
        int32_t sequence_max_value_;
        int32_t sequence_min_value_;
        int32_t sequence_cache_;
        bool sequence_cycle_;
    };
    DEFINE_JSON_DECLARATIONS(CreateSequencePlanNode);

}  // namespace terrier::planner