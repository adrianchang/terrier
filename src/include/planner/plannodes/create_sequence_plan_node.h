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
         * @param database_oid  OID of the database
         * @return builder object
         */
        Builder &SetDatabaseOid(catalog::db_oid_t database_oid) {
            database_oid_ = database_oid;
            return *this;
        }

        /**
         * @param index_name the name of the index
         * @return builder object
         */
        Builder &SetSequenceName(std::string sequence_name) {
            sequence_name_ = std::move(sequence_name);
            return *this;
        }

        std::unique_ptr<CreateSequencePlanNode> Build() {
            return std::unique_ptr<CreateSequencePlanNode>(
                    new CreateIndexPlanNode(std::move(children_), std::move(output_schema_), database_oid_,
                                            std::move(sequence_name_)));
        }


    protected:
        /**
         * OID of database
         */
        catalog::database_oid_t database_oid_;

        /**
         * Name of the sequence
         */
        std::string sequence_name_;
    };

private:
    CreateSequencePlanNode(std::vector<std::unique_ptr<AbstractPlanNode>> &&children,
    std::unique_ptr<OutputSchema> output_schema, catalog::database_oid_t database_oid,
    std::string sequence_name)
    : AbstractPlanNode(std::move(children), std::move(output_schema)),
    database_oid_(database_oid),
    sequence_name_(std::move(sequence_name)){}

public:
    /**
     * @return the type of this plan node
     */
    PlanNodeType GetPlanNodeType() const override { return PlanNodeType::CREATE_SEQUENCE; }


    /**
     * @return OID of the database to create index on
     */
    catalog::table_oid_t GetDatabaseOid() const { return database_oid_; }

    /**
     * @return name of the index
     */
    const std::string &GetSequenceName() const { return sequence_name_; }

    /**
     * @return the hashed value of this plan node
     */
    common::hash_t Hash() const override;

private:
    catalog::database_oid_t database_oid_;
    std::string sequence_name_;
};