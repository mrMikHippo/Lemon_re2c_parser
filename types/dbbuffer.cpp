#include "dbbuffer.h"

#include <iostream>
#include <iomanip>

// DBBuffer::DBBuffer()
//     : address(0), size(0)
// {
// }

DBBuffer::DBBuffer(int _address, int _size, const std::string& _description)
    : address(_address), size(_size), description(_description)
{}

void DBBuffer::print() const
{
    std::cout << "DBBuffer:" << std::endl;
    std::cout << "\t    address=0x" << std::hex << std::setw(10) << std::setfill('0') << address << std::endl;
    std::cout << std::resetiosflags(std::ios_base::basefield);
    std::cout << "\t       size=" << size << std::endl;
    std::cout << "\tdescription=" << description << std::endl;
}
