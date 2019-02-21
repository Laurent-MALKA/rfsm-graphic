#ifndef VARIABLE_HPP_INCLUDED
#define VARIABLE_HPP_INCLUDED

#include <string>
#include <vector>

class Variable
{
  private:
    static std::vector<std::string> Types;

  protected:
    int type_index;
    std::string name;

  public:
    Variable(const std::string& name, int type_index = 0);

    std::string getType() const;
    std::string getName() const;

    virtual std::vector<std::string> getTypes() const;

    void setType(int type_index);
    void setType(const std::string& type);

    void setName(const char* name);
    void setName(const std::string& name);
};

#endif