#ifndef Ancona_Util_StrUtil_H_
#define Ancona_Util_StrUtil_H_

#include <string>
#include <vector>

namespace ild
{

/**
 * @brief The built in c++ string lacks many modern features.  This class is
 *  to make up for some of that. Note that because of they way the c++ memory
 *  model works most functions in this class will mutate the argument string.
 *
 * @author Jeff Swenson
 */
class StrUtil
{
  public:
    /**
     * @brief Trim the whitespace from a string.  NOTE: this will mutate the string.
     *
     * @param str String that should have its whitespace trimmed.
     * @param delimiters (Optional) A string containing all characters that should be trimmed.
     *
     * @return A reference to the string
     */
    static std::string &Trim(std::string &str, const std::string &delimiters = " \n\r");
    /**
     * @brief Trim the leading whitespace from a string.  NOTE: this will mutate the string.
     *
     * @param str String that should have its whitespace trimmed.
     * @param delimiters (Optional) A string containing all characters that should be trimmed.
     *
     * @return A reference to the string.
     */
    static std::string &LTrim(std::string &str, const std::string &delimiters = " \n\r");
    /**
     * @brief Trim the trailing whitespace from a string.  NOTE: this will mutate the string.
     *
     * @param str String that should have its whitespace trimmed.
     * @param delimiters (Optional) A string containing all characters that should be trimmed.
     *
     * @return A reference to the string.
     */
    static std::string &RTrim(std::string &str, const std::string &delimiters = " \n\r");
    /**
     * @brief Split the string on the character and append the result to the end of the result vector.
     *
     * @param str String to be split.
     * @param splitVal Character that the string should be split on.
     * @param max Maximum number of splits that will occur.  Defaults to max_size_t.
     *
     * @return A vector of the results.
     */
    static std::vector<std::string> Split(const std::string &str, char splitVal, size_t max = (size_t)-1);

    static bool BeginsWith(const std::string &str, const std::string &stringItBeginsWith);
};

} // namespace ild
#endif
