#include "literal_executor.h"


bool initialize()
{
    std::cout << "[ Initialize] Call to register operators" << std::endl;

    GlobalLiteralTypeMap::getInstance().registerExecutor("Buffer", std::make_shared<BufferLiteralExecutor>());
    return true;
}

static bool success = initialize();
