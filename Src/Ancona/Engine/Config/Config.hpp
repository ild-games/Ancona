#ifndef ANCONA_ENGINE_CONFIG_CONFIG_H_
#define ANCONA_ENGINE_CONFIG_CONFIG_H_

#include <unordered_map>

namespace ild
{

class Config 
{
    public:

        static void Load(const std::string & configFile);

        static const std::string & GetOption(const std::string & optionName);

    private:
        Config() {};
        static std::unordered_map<std::string,std::string> * options;
};

}

#endif
