#include "literal_executor.h"

#include "../AST/variable_type.h"
#include "../types/dbbuffer.h"
#include "../types/vector.h"
#include "../types/integer.h"
#include "../types/float.h"
#include "../types/string.h"

void* DBBufferLiteralExecutor::call(VariableType* type, std::vector<Expression*> content_)
{
    using std::cout;
    using std::endl;
    // std::cout << "[ BufferLiteralExecutor ] call " << std::endl;

    DBBuffer* dbbuf = new DBBuffer;

    if (content_.size() == 3) {
        int address = *(int*)content_.at(0)->execute();
        int size = *(int*)content_.at(1)->execute();
        std::string description = *(std::string*)content_.at(2)->execute();

        dbbuf->setParameters(address, size, description);
    }

    dbbuf->print();

    return dbbuf;
}

void* VectorLiteralExecutor::call(VariableType* type, std::vector<Expression*> content_)
{
    auto sub_type = type->getSubTypes().at(0)->getTokenType();
    // auto sub_type_name = sub_type->getType();

    // std::vector<void*>* vec = new std::vector<void *>;
    // for (auto& el : content_) {
    //     vec->push_back(el->execute());
    // }

    Vector* vec = Vector::create();

    if (sub_type == "Integer") {
        fillVector<Integer, int>(vec, content_);
    } else if (sub_type == "Float") {
        fillVector<Float, double>(vec, content_);
    } else if (sub_type == "String") {
        fillVector<String, std::string>(vec, content_);
    } else if (sub_type == "Vector") {
        for (auto & e : content_) {
            Vector* v1 = (Vector*)e->execute();
            vec->pushBack(v1);
        }
    }

    std::cout << "Vector content: ";
    vec->print();
    std::cout << std::endl;

    return static_cast<void*>(vec);
}

bool initialize()
{
    std::cout << "[ Initialize] Call to register operators" << std::endl;

    GlobalLiteralTypeMap::getInstance().registerExecutor("DBBuffer", std::make_shared<DBBufferLiteralExecutor>());
    GlobalLiteralTypeMap::getInstance().registerExecutor("Vector", std::make_shared<VectorLiteralExecutor>());
    return true;
}

static bool success = initialize();
