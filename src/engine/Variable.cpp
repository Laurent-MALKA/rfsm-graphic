#include <stdexcept>
#include "Variable.hpp"

std::vector<std::string> Variable::Type = {"bool", "int", "float", "event"};

Variable::Variable():type_index(0), name("var")
{
}

std::string Variable::getType() const
{
    return Type[type_index];
}

std::string Variable::getName() const
{
    return name;    
}

void Variable::setType(int type_index)
{
    if(0 > type_index || (unsigned)type_index >= Type.size())
        throw std::invalid_argument("Invalid type index");

    this->type_index = type_index;
}

void Variable::setType(std::string type)
{
    unsigned int index = 0;
    while(index < Type.size() && Type[index] != type)
        index++;

    if(index == Type.size())
        throw std::invalid_argument("Invalid type name");

    setType(index);
}

void Variable::setName(const char* name)
{
    this->name = name;
}

void Variable::setName(std::string name)
{
    this->name = name;
}
