#include "content.h"

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

TwoParamContent::TwoParamContent()
    : elements({})
{
}
const TwoParamContent::Elements& TwoParamContent::getElements() const
{
    return elements;
}

void TwoParamContent::addElement(TwoParamContent::ElementPair el_)
{
    elements.push_back(el_);
}
