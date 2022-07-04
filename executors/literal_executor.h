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

    void* some_action(std::vector<int>& vec_) {
        std::cout << "[ BufferLiteralExecutor ] some_action with: ";
        for (const auto& el : vec_) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
        return reinterpret_cast<void*>(1);
    }
};


template<typename T>
T castValue(void* value) {
    auto val = static_cast<T*>(value);
    T ret_val;
    if (val) {
        ret_val = *val;
        delete val;
    }
    return ret_val;
}

template<typename T>
Vector<T>* createAndFillVector(std::vector<Expression*> content_) {
    Vector<T>* vec = new Vector<T>();

    for (const auto& ex : content_) {
        auto val = static_cast<T*>(ex->execute());
        if (val) {
            vec->pushBack(*val);
            delete val;
        }
    }
    vec->print();
    return vec;
}

class VectorLiteralExecutor : public LiteralExecutor
{
public:
    VectorLiteralExecutor() {}

    std::string getName() const override { return "VectorLiteralExecutor"; }

    void* call(VariableType* type, std::vector<Expression*> content_) override;
};
