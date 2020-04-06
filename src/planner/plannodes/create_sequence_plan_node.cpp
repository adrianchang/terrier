#include "planner/plannodes/create_sequence_plan_node.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "parser/expression/abstract_expression.h"
#include "parser/expression/constant_value_expression.h"
#include "parser/parser_defs.h"

namespace terrier::planner {

    common::hash_t CreateSequencePlanNode::Hash() const {
        common::hash_t hash = AbstractPlanNode::Hash();

        // Hash sequence name
        hash = common::HashUtil::CombineHashes(hash, common::HashUtil::Hash(sequence_name_));

        // Hash sequence start
        hash = common::HashUtil::CombineHashes(hash, common::HashUtil::Hash(sequence_start_));

        // Hash sequence increment
        hash = common::HashUtil::CombineHashes(hash, common::HashUtil::Hash(sequence_increment_));

        // Hash sequence max value
        hash = common::HashUtil::CombineHashes(hash, common::HashUtil::Hash(sequence_max_value_));

        // Hash sequence min value
        hash = common::HashUtil::CombineHashes(hash, common::HashUtil::Hash(sequence_min_value_));

        // Hash sequence cache
        hash = common::HashUtil::CombineHashes(hash, common::HashUtil::Hash(sequence_cache_));

        // Hash sequence cycle
        hash = common::HashUtil::CombineHashes(hash, common::HashUtil::Hash(sequence_cycle_));

        return hash;
    }

    bool CreateSequencePlanNode::operator==(const AbstractPlanNode &rhs) const {
        if (!AbstractPlanNode::operator==(rhs)) return false;

        auto &other = dynamic_cast<const CreateSequencePlanNode &>(rhs);

        // Sequence name
        if (GetSequenceName() != other.GetSequenceName()) return false;

        // Sequence start
        if (GetSequenceStart() != other.GetSequenceStart()) return false;

        // Sequence increment
        if (GetSequenceIncrement() != other.GetSequenceIncrement()) return false;

        // Sequence max value
        if (GetSequenceMaxValue() != other.GetSequenceMaxValue()) return false;

        // Sequence min value
        if (GetSequenceMinValue() != other.GetSequenceMinValue()) return false;

        // Sequence cache
        if (GetSequenceCache() != other.GetSequenceCache()) return false;

        // Sequence cycle
        if (GetSequenceCycle() != other.GetSequenceCycle()) return false;

        return true;
    }

    nlohmann::json CreateSequencePlanNode::ToJson() const {
        nlohmann::json j = AbstractPlanNode::ToJson();
        j["sequence_name"] = sequence_name_;
        j["sequence_start"] = sequence_start_;
        j["sequence_increment"] = sequence_increment_;
        j["sequence_max_value"] = sequence_max_value_;
        j["sequence_min_value"] = sequence_min_value_;
        j["sequence_cache"] = sequence_cache_;
        j["sequence_cycle"] = sequence_cycle_;
        return j;
    }

    std::vector<std::unique_ptr<parser::AbstractExpression>> CreateSequencePlanNode::FromJson(const nlohmann::json &j) {
        std::vector<std::unique_ptr<parser::AbstractExpression>> exprs;
        auto e1 = AbstractPlanNode::FromJson(j);
        exprs.insert(exprs.end(), std::make_move_iterator(e1.begin()), std::make_move_iterator(e1.end()));
        sequence_name_ = j.at("sequence_name").get<std::string>();
        sequence_start_ = j.at("sequence_start").get<in>();
        sequence_increment_ = j.at("sequence_increment").get<std::string>();
        sequence_max_value_ = j.at("sequence_max_value").get<std::string>();
        sequence_min_value_ = j.at("sequence_min_value").get<std::string>();
        sequence_cache_ = j.at("sequence_cache").get<std::string>();
        sequence_cycle_ = j.at("sequence_cycle").get<std::string>();
        return exprs;
    }
}
