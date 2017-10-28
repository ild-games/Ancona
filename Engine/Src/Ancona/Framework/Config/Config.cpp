#include <iostream>
#include <fstream>

#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Util/StrUtil.hpp>
#include <Ancona/Util/Assert.hpp>

using namespace ild;

std::unordered_map<std::string,std::string> * Config::_options = NULL;
static const std::string EMPTY_OPTION = "";

void Config::Load(const std::string & configFile)
{
    std::ifstream file(configFile, std::ios::out);
    Load(file);
}

void Config::Load(std::istream & file)
{
    if(_options != NULL)
    {
        return;
    }

    _options = new std::unordered_map<std::string,std::string>();

    std::vector<std::string> pieces;
    std::string line;

    if(file.fail())
    {
        //If the file did not open then throw an exception.
        throw new AssertException("Failed to open configuration file.");
    }
    
    while(!file.eof())
    {
        std::getline(file, line);
        pieces.clear();

        //Remove comments from the string
        size_t comment_pos = line.find("#");
        if(comment_pos != std::string::npos)
        {
            line.erase(line.begin() + line.find("#"), line.end());
        }

        //Split the line along the assignment operator
        pieces = StrUtil::Split(line, '=', 2);

        if(pieces.size() == 2)
        {
            //Trim whitespace from both pieces
            StrUtil::Trim(pieces[0]);
            StrUtil::Trim(pieces[1]);

            (*_options)[pieces[0]] = pieces[1];
        }
    }

}

void Config::Add(const std::string & optionName, const std::string & value)
{
    (*_options)[optionName] = value;
}

const std::string & Config::GetOption(const std::string & optionName)
{
    //Test if the option is in the map
    if(_options->find(optionName) != _options->end())
    {
        return _options->at(optionName);
    }
    else
    {
        return EMPTY_OPTION;
    }
}

void Config::_initAssert()
{
    const std::string & assertFile = GetOption("Assert_ErrorFile");
    const std::string & throwException = GetOption("Assert_ThrowException");

    if(assertFile != "")
    {
        std::ostream * logFile = new std::ofstream(assertFile);
        AssertControls::SetErrorStream(logFile);
    }

    if(throwException != "false")
    {
        //Default to throw an exception
        AssertControls::SetThrowException(true);
    }
}
