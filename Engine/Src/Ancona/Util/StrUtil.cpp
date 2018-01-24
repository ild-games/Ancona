#include <string>

#include <Ancona/Util/StrUtil.hpp>

using namespace ild;

std::string & StrUtil::Trim(std::string & str, const std::string & delimiters)
{
    return LTrim(RTrim(str));
}

std::string & StrUtil::LTrim(std::string & str, const std::string & delimiters)
{
    size_t pos = str.find_first_not_of(delimiters);
    str.erase(str.begin(),str.begin() + pos);
    return str;
}

std::string & StrUtil::RTrim(std::string & str, const std::string & delimiters)
{
    size_t pos = str.find_last_not_of(delimiters);
    str.erase(str.begin() + pos + 1, str.end());
    return str;
}

std::vector<std::string> StrUtil::Split(const std::string & str, char splitVal, size_t max)
{
    size_t position = 0;
    size_t newPosition;
    std::vector<std::string> result;

    //Loop until the max number of splits are made or the end of the string is reached
    for(size_t i = 0; i < max && position < str.size(); i++)
    {
        if(i == max - 1)
        {
            //If there is only one remaining string then it should the string should not be split
            newPosition = std::string::npos;
        }
        else
        {
            //Find the next split position.  If no split then newPosition will be std::strin::npos
            newPosition = str.find(splitVal,position);
        }

        if(newPosition == std::string::npos)
        {
            //If there is no remaining splitter then add the rest of the string
            result.push_back(str.substr(position));
            break;
        }
        else
        {
            //Add the string up to the next splitter
            result.push_back(str.substr(position,newPosition - position));
        }

        position = newPosition + 1;
    }

    return result;
}

bool StrUtil::BeginsWith(const std::string & str, const std::string & stringItBeginsWith)
{
    return str.compare(0, stringItBeginsWith.length(), stringItBeginsWith) == 0;
}
