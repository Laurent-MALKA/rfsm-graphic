#include <stdexcept>
#include "Variable.hpp"

std::vector<std::string> Variable::Types = {"bool", "int", "float"};

Variable::Variable(const std::string& name, int type_index):type_index(0), name(name)
{
}

std::string Variable::getType() const
{
    return getTypes()[type_index];
}

std::string Variable::getName() const
{
    return name;    
}

std::vector<std::string> Variable::getTypes() const
{
    return Types;
}

void Variable::setType(int type_index)
{
    if(0 > type_index || (unsigned)type_index >= getTypes().size())
        throw std::invalid_argument("Invalid type index");

    this->type_index = type_index;
}

void Variable::setType(const std::string& type)
{
    unsigned int index = 0;
    while(index < getTypes().size() && getTypes()[index] != type)
        index++;

    if(index == getTypes().size())
        throw std::invalid_argument("Invalid type name");

    setType(index);
}

void Variable::setName(const char* name)
{
    this->name = name;
}

void Variable::setName(const std::string& name)
{
    this->name = name;
}
