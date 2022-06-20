#include "content.h"

OneParamContent::OneParamContent(Expression* expr)
    : elements({expr})
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

TwoParamContent::TwoParamContent(std::pair<Token*, Expression*> el_)
    : elements({el_})
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
