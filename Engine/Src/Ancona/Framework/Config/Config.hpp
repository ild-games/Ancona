#pragma once

#include <istream>
#include <string>
#include <unordered_map>

namespace ild
{

/**
 * @brief Used to load and store configuration options.  Load should be the first method called in
 * the ancona engine.
 * @author Jeff Swenson
 */
class Config
{
  public:
    /**
     * @brief Load the setting file and store the options.
     *
     * @param configFile A string containing the configuration file name.
     */
    static void Load(const std::string &configFile);

    /**
     * @brief Load settings from the input stream.
     *
     * @param configStream A string containing the configuration file name.
     */
    static void Load(std::istream &configStream);

    static void Add(const std::string &optionName, const std::string &value);

    /**
     * @brief Get option from the configuration settings.
     *
     * @param optionName Name of the option.
     *
     * @return value of the option.  If the value was not set the "" is returned.
     */
    static const std::string &GetOption(const std::string &optionName);

  private:
    Config(){};
    static std::unordered_map<std::string, std::string> *_options;
    static void _initAssert();
};

} // namespace ild
