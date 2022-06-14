#include "content.h"

#include <iostream>
#include <exception>

OneParamContent::OneParamContent()
    : elements({})
{
}
const OneParamContent::Elements& OneParamContent::getElements() const
{
    return elements;
}

void OneParamContent::addElement(Expression* el_)
{
    elements.push_back(el_);
}
