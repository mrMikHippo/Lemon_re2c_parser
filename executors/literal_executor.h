#pragma once

#include "../AST/expression.h"
#include "../AST/global_types_map.h"
#include "../types/vector.h"

#include <vector>
#include <iostream>


class LiteralExecutor
{
public:
    LiteralExecutor() {}
    virtual ~LiteralExecutor() = default;

    virtual std::string getName() const = 0;

    virtual void* call(VariableType* type, std::vector<Expression*> content_) = 0;
};

class DBBufferLiteralExecutor : public LiteralExecutor
{
public:
    DBBufferLiteralExecutor() {}

    void* call(VariableType* type, std::vector<Expression*> content_) override;

    std::string getName() const override { return "DBBufferLiteralExecutor"; }
};


// template<typename T>
// T castValue(void* value) {
//     auto val = static_cast<T*>(value);
//     T ret_val;
//     if (val) {
//         ret_val = *val;
//         delete val;
//     }
//     return ret_val;
// }
//
// template<typename T>
// Vector<T>* createAndFillVector(std::vector<Expression*> content_) {
//     Vector<T>* vec = new Vector<T>();
//
//     for (const auto& ex : content_) {
//         auto val = static_cast<T*>(ex->execute());
//         if (val) {
//             vec->pushBack(*val);
//             delete val;
//         }
//     }
//     vec->print();
//     return vec;
// }

template<typename VT, typename T>
void fillVector(Vector* vec, std::vector<Expression*> content_)
{
    for (auto& expression_literal : content_) {
        T* p = static_cast<T*>(expression_literal->execute());
        if (p) {
            VT* ret_middle = new VT(*p);
            vec->pushBack(ret_middle);
            delete p;
        }
    }
}

class VectorLiteralExecutor : public LiteralExecutor
{
public:
    VectorLiteralExecutor() {}

    std::string getName() const override { return "VectorLiteralExecutor"; }

    void* call(VariableType* type, std::vector<Expression*> content_) override;
};
