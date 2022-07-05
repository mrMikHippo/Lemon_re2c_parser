#include "dbbuffer.h"

#include "../../types/dbbuffer.h"

using std::to_string;

LiteralDBBuffer::LiteralDBBuffer(const int _address, const int _size, const std::string& _description)
	: address(_address), size(_size), description(_description)
{
}

void* LiteralDBBuffer::execute() {
    return new DBBuffer(address, size, description);
}

std::string LiteralDBBuffer::toString() const {
	return "DBBuffer(" + to_string(address) + ", " + to_string(size) + ", " + description + ")";
}

std::string LiteralDBBuffer::print(int level) const {
	return std::string(level, '\t') + "DBBuffer(\"" + to_string(address) + ", " + to_string(size) + ", " + description + "\")\n";
}
