# Sequences

## Overview

Implement the sequence feature which work as global counters that can be used as auto-increment keys for tables.
The sequence feature works similarly like the one implemented by postgres.

* Support functionalities:
  * nextval function
  * currval function
  * SERIAL attribute type
* Example usage:
  * CREATE SEQUENCE my_sequence;
  * CREATE TABLE my_table_1 (id INTEGER NOT NULL DEFAULT nextval(‘my_sequence’));
  * CREATE TABLE my_table_2 (id SERIAL);


## Scope

Currently, we have establish the end-to-end CREATE SEQUENCE and DROP SEQUENCE pipeline.
Sequences can now be created and removed in database catalog pg_class.

File modified:

* Parser (postgresparser.cpp)
* Binder (bind_node_visitor.cpp)
* Optimizer (logical_operators.cpp, physical_operators.cpp, query_to_operator_transformer.cpp, plan_generator.cpp)
* Planner (create_sequence_plan_node.cpp, drop_sequence_plan_node.cpp)
* TrafficCop (traffic_cop.cpp)
* Execution (ddl_executors.cpp)
* Catalog (catalog_accessor.cpp, database_catalog.cpp)
* Unit tests (parser_test, binder_test, logical_operator_test, physical_operator_test, operator_transformer_test, catalog_test, ddl_executors_test)

## Glossary (Optional)

## Architectural Design

* Create pg_sequence in database catalog to store sequence metadata.
  https://www.postgresql.org/docs/12/catalog-pg-sequence.html
* Implement basic nextval and currval function with the newly added builtin function feature.
  https://github.com/cmu-db/terrier/pull/803
* Implement the expected behavior for nextval and currval.
  https://www.postgresql.org/docs/12/functions-sequence.html
* Implement minvalue, maxvalue, increment …
  https://www.postgresql.org/docs/12/sql-createsequence.html

## Design Rationale

## Testing Plan

* First of all, we will add the sequence unittest for each part of the pipeline, namely, parser_test, logical_operator_test, physical_operator_test and operator_transformer_test for now.

* Then, after adding the nextval and curval feature, we will add unittest for them too.

* Lastly, after full functionality is set, we will add in more general tests to test for more general tests such as cross session tests and benchmarks.

## Trade-offs and Potential Problems

## Future Work

