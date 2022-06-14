#pragma once

#include "token.h"
#include "expression.h"
#include <vector>


class OneParamContent : public Token
{
public:
    using Elements = std::vector<Expression*>;
    OneParamContent();

    void addElement(Expression* el_);
    const Elements& getElements() const;


private:
    Elements elements;
};
