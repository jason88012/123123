#include <bits/stdc++.h>

#pragma once

template <typename TypeTrait>
struct DfsRecursionTrait {
    using Field = typename TypeTrait::Field;
    using Record = typename TypeTrait::Record;
    using Records = typename TypeTrait::Records;

    static void doDfs(const Field& field, std::ostringstream& output,
                      const Records& records,
                      std::unordered_set<Field>& visited) {
        auto it = records.find(field);
        if (it != std::end(records) && visited.insert(field).second) {
            const auto& record = it->second;
            output << record;
            for (auto& dep : record.dependencies) {
                doDfs(dep, output, records, visited);
            }
        }
    }
};

template <typename TypeTrait>
struct DfsIterationTrait {
    using Field = typename TypeTrait::Field;
    using Record = typename TypeTrait::Record;
    using Records = typename TypeTrait::Records;

    static void doDfs(const Field& startField, std::ostringstream& output,
                      const Records& records,
                      std::unordered_set<Field>& visited) {
        std::stack<Field> stack;
        stack.push(startField);

        while (!stack.empty()) {
            const Field& currentField = stack.top();
            stack.pop();

            if (visited.insert(currentField).second) {
                auto it = records.find(currentField);
                if (it != records.end()) {
                    const Record& record = it->second;
                    output << record;

                    for (const auto& dep : record.dependencies) {
                        stack.push(dep);
                    }
                }
            }
        }
    }
};

struct ErrorTracerTypeTrait {
    using Field = std::string;

    struct RecordType {
        Field field;
        std::string trace;
        std::string message;
        std::unordered_set<Field> dependencies;

        friend std::ostream& operator<<(std::ostream& os,
                                        const RecordType& record) {
            os << "{Field: " << record.field << ", Trace: " << record.trace
               << ", Message: " << record.message << "}";
            return os;
        }
    };

    using Record = RecordType;
    using Records = std::unordered_map<Field, Record>;
};

template <typename Trait>
struct ErrorTracerImpl {
    using Field = typename Trait::Field;
    using Record = typename Trait::Record;
    using Records = typename Trait::Records;

   protected:
    void add(Record& record, const Field& field, const std::string& trace,
             const std::string& message) {
        record.field = field;
        record.trace = trace;
        record.message = message;
    }

   public:
    void add(const Field& field, const std::string& trace,
             const std::string& message) {
        auto& record = records[field];
        add(record, field, trace, message);
    }

    void add(const Field& field, const Field& dependency,
             const std::string& trace, const std::string& message) {
        auto& record = records[field];
        record.dependencies.insert(dependency);
        add(record, field, trace, message);
    }

    std::string getErrorTrace(const Field& field) {
        std::unordered_set<Field> visited;
        std::ostringstream oss;
        Trait::doDfs(field, oss, records, visited);
        return oss.str();
    }

    Records records;
};

using ErrorTracerRecursion =
    ErrorTracerImpl<DfsRecursionTrait<ErrorTracerTypeTrait>>;
using ErrorTracerIteration =
    ErrorTracerImpl<DfsIterationTrait<ErrorTracerTypeTrait>>;
