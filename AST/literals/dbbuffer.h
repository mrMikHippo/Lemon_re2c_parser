#pragma once

#include "../literal.h"

class LiteralDBBuffer : public Literal
{
public:
	LiteralDBBuffer(const int _address, const int _size, const std::string& _description);

	void* execute();

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
    int address;
    int size;
    std::string description;
};
