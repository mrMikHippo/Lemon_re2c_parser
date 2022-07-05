#include "literal_executor.h"

#include "../AST/variable_type.h"
#include "../types/dbbuffer.h"

void* DBBufferLiteralExecutor::call(VariableType* type, std::vector<Expression*> content_)
{
    using std::cout;
    using std::endl;
    using std::string;
    // std::cout << "[ BufferLiteralExecutor ] call " << std::endl;

    DBBuffer* dbbuf;

    if (content_.size() == 3) {
        int* address = static_cast<int*>(content_.at(0)->execute());
        int* size = static_cast<int*>(content_.at(1)->execute());
        string* description = static_cast<string*>(content_.at(2)->execute());

        dbbuf = new DBBuffer(*address, *size, *description);
        delete address;
        delete size;
        delete description;
    } else
        dbbuf = new DBBuffer;

    dbbuf->print();

    return dbbuf;
}

void* VectorLiteralExecutor::call(VariableType* type, std::vector<Expression*> content_)
{
    auto sub_type = type->getSubTypes().at(0);

    if (sub_type->getType()->value == "Integer") {
        return createAndFillVector<int>(content_);
    } else if (sub_type->getType()->value == "Float") {
        return createAndFillVector<double>(content_);
    } else if (sub_type->getType()->value == "String") {
        return createAndFillVector<std::string>(content_);
    }

    return nullptr;
}

bool initialize()
{
    std::cout << "[ Initialize] Call to register operators" << std::endl;

    GlobalLiteralTypeMap::getInstance().registerExecutor("DBBuffer", std::make_shared<DBBufferLiteralExecutor>());
    GlobalLiteralTypeMap::getInstance().registerExecutor("Vector", std::make_shared<VectorLiteralExecutor>());
    return true;
}

static bool success = initialize();
