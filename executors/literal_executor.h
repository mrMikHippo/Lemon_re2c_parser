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

class BufferLiteralExecutor : public LiteralExecutor
{
public:
    BufferLiteralExecutor() {}

    void* call(std::vector<Expression*> content_) override {
        // std::cout << "[ BufferLiteralExecutor ] call (here we execute some method)" << std::endl;
        std::vector<int> vec;
        for (const auto& cnt : content_) {
            // std::cout << "expression toString: " << cnt->toString() << std::endl;
            void *ptr = cnt->execute();
            if (ptr) {
                int n = *((int *) cnt->execute());
                // std::cout << "casted: " << n << std::endl;
                vec.push_back(n);
            }
        }
        return some_action(vec);
    }


    void* some_action(std::vector<int>& vec_) {
        std::cout << "[ BufferLiteralExecutor ] some_action with: ";
        for (const auto& el : vec_) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
        return reinterpret_cast<void*>(1);
    }
};
