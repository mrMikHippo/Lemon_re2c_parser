#include "literal_executor.h"

#include "../AST/variable_type.h"
#include "../types/dbbuffer.h"
#include "../types/vector.h"
#include "../types/integer.h"
#include "../types/float.h"

void* DBBufferLiteralExecutor::call(VariableType* type, std::vector<Expression*> content_)
{
    using std::cout;
    using std::endl;
    // std::cout << "[ BufferLiteralExecutor ] call " << std::endl;

    if (content_.size() != 3) {
        return new DBBuffer(0, 0, "");
    }

    int* address = static_cast<int*>(content_.at(0)->execute());
    int* size = static_cast<int*>(content_.at(1)->execute());
    std::string* description = static_cast<std::string*>(content_.at(2)->execute());

    DBBuffer* dbbuf = new DBBuffer(*address, *size, *description);

    delete address;
    delete size;
    delete description;

    dbbuf->print();

    return dbbuf;
}

void* VectorLiteralExecutor::call(VariableType* type, std::vector<Expression*> content_)
{
    auto sub_type = type->getSubTypes().at(0);
    auto sub_type_name = sub_type->getType()->value;

    Vector* vec = Vector::create();

    if (sub_type_name == "Integer") {
        fillVector<Integer, int>(vec, content_);
    } else if (sub_type_name == "Float") {
        fillVector<Float, double>(vec, content_);
    } else if (sub_type_name == "String") {
        // fillVector<String, std::string>(vec, content_);
    } else if (sub_type_name == "Vector") {
        std::cout << "Vector ";
        return call(sub_type, content_);
    }

    std::cout << "Vector content: ";
    vec->print();
    std::cout << std::endl;

    return vec;
}

bool initialize()
{
    std::cout << "[ Initialize] Call to register operators" << std::endl;

    GlobalLiteralTypeMap::getInstance().registerExecutor("DBBuffer", std::make_shared<DBBufferLiteralExecutor>());
    GlobalLiteralTypeMap::getInstance().registerExecutor("Vector", std::make_shared<VectorLiteralExecutor>());
    return true;
}

static bool success = initialize();
