#include "literal_executor.h"

#include "../AST/variable_type.h"
#include "../types/dbbuffer.h"
#include "../types/vector.h"
#include "../types/map.h"
#include "../types/integer.h"
#include "../types/float.h"
#include "../types/string.h"

LiteralExecutor::LiteralExecutor()
{}

LiteralExecutor::LiteralExecutor(VariableType* _type)
    : type(_type)
{}

void* DBBufferLiteralExecutor::call(VariableType* _type, std::vector<Expression*> _content)
{
    using std::cout;
    using std::endl;
    // std::cout << "[ BufferLiteralExecutor ] call " << std::endl;

    DBBuffer* dbbuf = new DBBuffer;

    if (_content.size() == 3) {
        int address = *(int*)_content.at(0)->execute();
        int size = *(int*)_content.at(1)->execute();
        std::string description = *(std::string*)_content.at(2)->execute();

        dbbuf->setParameters(address, size, description);
    }

    dbbuf->print();

    return dbbuf;
}

void* VectorLiteralExecutor::call(VariableType* _type, std::vector<Expression*> _content)
{
    auto sub_type = _type->getSubTypes().at(0)->getTokenType();
    // auto sub_type_name = sub_type->getType();

    // std::vector<void*>* vec = new std::vector<void *>;
    // for (auto& el : _content) {
    //     vec->push_back(el->execute());
    // }

    Vector* vec = Vector::create();

    if (sub_type == "Integer") {
        fillVector<Integer, int>(vec, _content);
    } else if (sub_type == "Float") {
        fillVector<Float, double>(vec, _content);
    } else if (sub_type == "String") {
        fillVector<String, std::string>(vec, _content);
    } else if (sub_type == "Vector") {
        for (auto & e : _content) {
            Vector* v1 = (Vector*)e->execute();
            vec->pushBack(v1);
        }
    }

    std::cout << "Vector content: ";
    vec->print();
    std::cout << std::endl;

    return static_cast<void*>(vec);
}

void* MapLiteralExecutor::call(VariableType* _type, std::vector<Expression*> _content)
{
    return nullptr;
}
void* MapLiteralExecutor::call(VariableType* _type, std::vector<std::pair<Token*, Expression*>> _content)
{
    auto first_type = _type->getSubTypes().at(0)->getTokenType();
    auto sec_type = _type->getSubTypes().at(1)->getTokenType();

    Map* mp = Map::create();

    if (first_type == "Integer" && sec_type == "Integer") {
        std::cout << "Map: " << _type->toString() << std::endl;

        for (auto & el : _content) {
            auto first = el.first;
            auto second = el.second;
            ExpressionId* expr = (ExpressionId*)first;
            // FIXME this shouldn't be a simple name value
            auto key = *(std::string*)expr->execute();
            auto middle_val = *(int*)second->execute();

            mp->insert({new String(key), new Integer(middle_val)});
        }
    }

    std::cout << "Map content: ";
    mp->print();
    std::cout << std::endl;

    return static_cast<void*>(mp);
}

bool initialize()
{
    std::cout << "[ Initialize] Call to register operators" << std::endl;

    GlobalLiteralTypeMap::getInstance().registerExecutor("DBBuffer", std::make_shared<DBBufferLiteralExecutor>());
    GlobalLiteralTypeMap::getInstance().registerExecutor("Vector", std::make_shared<VectorLiteralExecutor>());
    GlobalLiteralTypeMap::getInstance().registerExecutor("Map", std::make_shared<MapLiteralExecutor>());
    return true;
}

static bool success = initialize();
