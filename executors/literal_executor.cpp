#include "literal_executor.h"

#include "../types/dbbuffer.h"

void* DBBufferLiteralExecutor::call(std::vector<Expression*> content_) {
    using std::cout;
    using std::endl;
    using std::string;
    // std::cout << "[ BufferLiteralExecutor ] call (here we execute some method)" << std::endl;

    DBBuffer* dbbuf;

    if (content_.size() == 3) {
        int* ival = static_cast<int*>(content_.at(0)->execute());
        double* dval = static_cast<double*>(content_.at(1)->execute());
        string* sval = static_cast<string*>(content_.at(2)->execute());

        dbbuf = new DBBuffer(*ival, *dval, *sval);
        delete ival;
        delete dval;
        delete sval;
    } else
        dbbuf = new DBBuffer;

    dbbuf->print();

    // TODO casting
    return dbbuf;
}

bool initialize()
{
    std::cout << "[ Initialize] Call to register operators" << std::endl;

    GlobalLiteralTypeMap::getInstance().registerExecutor("DBBuffer", std::make_shared<DBBufferLiteralExecutor>());
    // GlobalLiteralTypeMap::getInstance().registerExecutor("Vector", std::make_shared<VectorLiteralExecutor>());
    return true;
}

static bool success = initialize();
