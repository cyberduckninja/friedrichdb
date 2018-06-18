#pragma once

#include <rapidjson/document.h>
#include <rapidjson/>
#include <friedrichdb/transaction.hpp>

#include <string>

/**
 * {
 *  "database":"",
 *  "" : [
 *      {
 *          "operation":""
 *          "document_key":""
 *          "table":"",
 *          "field":"",
 *          "value":""
 *      }
 *  ]
 * }
 */

namespace friedrichdb { namespace ql {


        bool parser_transactions(rapidjson::Value::Array &array, std::vector<transaction> transactions) {
            bool error = true;
            for (auto &i:array) {
                if (i.IsObject()) {

                    operation_type operation;

                    if (i["operation"].IsString() && i["operation"].IsString()) {
                        operation = friedrichdb::from_string(i["operation"].GetString());

                    } else {
                        return error;
                    }

                    std::string table;
                    if (i["in_memory_table"].IsString() && i["in_memory_table"].IsString()) {
                        table = i["in_memory_table"].GetString();

                    } else {
                        return error;
                    }


                    std::string document_id;
                    if (i["document_id"].IsString() && i["document_id"].IsString()) {
                        document_id = i["document_id"].GetString();

                    } else {
                        return error;
                    }

                    std::string field;
                    if (i["field"].IsString() && i["field"].IsString()) {
                        field = i["field"].GetString();

                    } else {
                        return error;
                    }

                    std::string value;
                    if (i["value"].IsString() && i["value"].IsString()) {
                        value = i["value"].GetString();

                    } else {
                        return true;
                    }

                    transactions.emplace_back({operation, table, field, value});
                } else {
                    return error;
                }


            }
            error = false;
            return error;
        }


        auto parser(const std::string &json_string) -> query {
            query query_;

            rapidjson::Document document;
            document.Parse(json_string);
            if (!document.HasParseError()) {
                if (document.IsObject()) {
                    query_.database = document["database"].GetString();
                    if (document["transactions"].IsArray()) {
                        parser_transactions(document["transactions"].GetArray(), query_.transactions);
                    }
                }
            } else {

            }


        }
    }
}