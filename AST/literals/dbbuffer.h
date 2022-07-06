#pragma once

#include "../literal.h"
#include "../../types/dbbuffer.h"

class LiteralDBBuffer : public Literal
{
public:

	template<typename ...Args>
	static DBBuffer* create(Args && ... _args) {
		return new DBBuffer(std::forward<Args>...);
	}

	void* execute() override;

	std::string toString() const override;
	std::string print(int level = 0) const override;

protected:
	LiteralDBBuffer(const int _address, const int _size, const std::string& _description = "");


private:
    int address;
    int size;
    std::string description;
};
