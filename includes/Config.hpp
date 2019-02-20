#ifndef CONFIG_HEADER
#define CONFIG_HEADER

#include <string>
#include <vector>
#include <exception>

#include "../includes/nlohmann_json.hpp"

class Config
{
    private:
        nlohmann::json parsed_config;

    public:
        Config(const std::string& path = "config/config.json");

        /**
         * Return the value of the key
         */
        template<typename T>
        T get(const std::string& key)
        {
            std::vector<std::string> splited_string = split(key, '.');
            nlohmann::json current_json = parsed_config;

            for (int i = 0, size = splited_string.size(); i < size; i ++)
            {
                if(current_json.find(splited_string[i]) == current_json.end())
                    throw KeyNotFoundException(splited_string[i]);

                current_json = current_json[splited_string[i]];
            }

            return current_json.get<T>();
        };

    private:
        const std::vector<std::string> split(const std::string &s, const char &c);

    /**
     * Exceptions
     */
    public:
        class FileNotFoundException : public std::exception
        {
            private:
                std::string error_message;
            public:
                FileNotFoundException(const std::string& path)
                {
                    error_message = std::string("Could not open '") + path + std::string("' file");
                }

                const char* what() const noexcept
                {
                    return error_message.c_str();
                }
        };

        class KeyNotFoundException : public std::exception
        {
            private:
                std::string error_message;
            public:
                KeyNotFoundException(const std::string& key)
                {
                    error_message = std::string("Key '") + key + std::string("' not found in config");
                }

                const char* what() const noexcept
                {
                    return error_message.c_str();
                }
        };
};

#endif
