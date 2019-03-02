#include "Variable.hpp"

#include <cctype>
#include <stdexcept>

Variable::Variable(const std::string& name, const std::string& type)
{
    setType(type);
    setName(name);
}

const std::string& Variable::getType() const
{
    return type;
}

const std::string& Variable::getName() const
{
    return name;
}

void Variable::setType(const std::string& type)
{
    this->type = type;
    for(auto& character : this->type)
        character = std::tolower(character);
}

void Variable::setName(const std::string& name)
{
    this->name = name;
    for(auto& character : this->name)
        character = std::tolower(character);
}
