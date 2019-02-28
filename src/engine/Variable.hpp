#ifndef VARIABLE_HPP_INCLUDED
#define VARIABLE_HPP_INCLUDED

#include <string>
#include <vector>

class Variable
{
  protected:
    std::string type;
    std::string name;

  public:
    Variable(const std::string& name, const std::string& type_index = "int");

    const std::string& getType() const;
    const std::string& getName() const;

    void setType(const std::string& type);

    void setName(const std::string& name);
};

#endif