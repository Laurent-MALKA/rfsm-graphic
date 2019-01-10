#include <fstream>
#include "../includes/Config.hpp"

/**
 * Construct config
 */
Config::Config(std::string path)
{
    std::ifstream config_file(path.c_str());

    if(config_file.good() == 0)
        throw FileNotFoundException(path);

    config_file >> this->parsed_config;
}

/**
 * Explode a string with a delimiter into a vector of string
 */
const std::vector<std::string> Config::split(const std::string &s, const char &c)
{
    std::string buff{""};
    std::vector<std::string> v;

    for (auto n : s)
    {
        if (n != c)
            buff += n;
        else if (n == c && buff != "")
        {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "")
        v.push_back(buff);

    return v;
}
