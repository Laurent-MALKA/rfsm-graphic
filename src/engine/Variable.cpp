#include "Variable.hpp"

#include <stdexcept>

Variable::Variable(const std::string& name, const std::string& type)
    : type(type), name(name)
{}

const std::string& Variable::getType() const
{
    return type;
}

const std::string& Variable::getName() const
{
    return name;
}

void Variable::setType(const char* type)
{
    this->type = type;
}

void Variable::setType(const std::string& type)
{
    this->type = type;
}

void Variable::setName(const char* name)
{
    this->name = name;
}

void Variable::setName(const std::string& name)
{
    this->name = name;
}
