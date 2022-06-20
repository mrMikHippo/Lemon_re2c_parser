#pragma once

#include "token.h"
#include "expression.h"
#include <vector>

class OneParamContent : public Token
{
public:
    using Elements = std::vector<Expression*>;
    OneParamContent(Expression* expr);

    void addElement(Expression* el_);
    const Elements& getElements() const;


private:
    Elements elements;
};

class TwoParamContent : public Token
{
public:
    using ElementPair = std::pair<Token*, Expression*>;
    using Elements = std::vector<ElementPair>;
    TwoParamContent(std::pair<Token*, Expression*> el_);

    void addElement(ElementPair el_);
    const Elements& getElements() const;

public:
    Elements elements;
};

template<typename T>
class ParamsContent : public Token
{
public:
    ParamsContent() {};

    void addElement(T el_) {
        elements.push_back(el_);
    }
private:
    std::vector<T> elements;
};
