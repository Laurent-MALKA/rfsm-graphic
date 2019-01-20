#ifndef VARIABLE_HPP_INCLUDED
#define VARIABLE_HPP_INCLUDED

#include <string>
#include <vector>

class Variable
{
    public:
        static std::vector<std::string> Types;

    protected:
        int type_index;
        std::string name;

    public:
        Variable(std::string name, int type_index = 0);
        
        std::string getType() const;
        std::string getName() const;
        
        void setType(int type_index);
        void setType(std::string type);

        void setName(const char* name);
        void setName(std::string name);
};

#endif