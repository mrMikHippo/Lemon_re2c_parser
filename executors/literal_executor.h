#pragma once

#include "../AST/expression.h"
#include "../AST/global_types_map.h"

#include <vector>
#include <iostream>

class LiteralExecutor
{
public:
    LiteralExecutor() {}
    virtual ~LiteralExecutor() = default;

    virtual void* call(std::vector<Expression*> content_) = 0;
};

class DBBufferLiteralExecutor : public LiteralExecutor
{
public:
    DBBufferLiteralExecutor() {}

    void* call(std::vector<Expression*> content_) override;

    void* some_action(std::vector<int>& vec_) {
        std::cout << "[ BufferLiteralExecutor ] some_action with: ";
        for (const auto& el : vec_) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
        return reinterpret_cast<void*>(1);
    }
};

class VectorLiteralExecutor : public LiteralExecutor
{
public:
    VectorLiteralExecutor() {}

    void* call(std::vector<Expression*> content_) override;

// private:
    // std::vector<int> content;
};
