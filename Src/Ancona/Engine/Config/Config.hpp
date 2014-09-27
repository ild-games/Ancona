#ifndef ANCONA_ENGINE_CONFIG_CONFIG_H_
#define ANCONA_ENGINE_CONFIG_CONFIG_H_

#include <unordered_map>
#include <string>

namespace ild
{

/**
 * @brief Used to load and store configuration options.  Load should be the first method called in
 * the ancona engine.
 * @owner Jeff Swenson
 */
class Config 
{
    public:

        /**
         * @brief Load the setting file and store the options.
         *
         * @param configFile A string containing the configuration file name.
         */
        static void Load(const std::string & configFile);

        /**
         * @brief Get option from the configuration settings.
         *
         * @param optionName Name of the option.
         *
         * @return Value of the option.  If the value was not set the "" is returned.
         */
        static const std::string & GetOption(const std::string & optionName);
    private:
        Config() {};
        static std::unordered_map<std::string,std::string> * options;
        static void _initAssert();
};

}

#endif
