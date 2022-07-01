#include "dbbuffer.h"

#include <iostream>

using std::cout;
using std::endl;

DBBuffer::DBBuffer(int ival_, float fval_, const std::string& sval_)
    : ival(ival_), fval(fval_), sval(sval_)
{}

void DBBuffer::print() const
{
    cout << "DBBuffer content:" << endl;
    cout << "\tival=" << ival << endl;
    cout << "\tfval=" << fval << endl;
    cout << "\tsval=" << sval << endl;
}
