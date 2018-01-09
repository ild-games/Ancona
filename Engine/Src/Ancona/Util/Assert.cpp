#include <sstream>

#include <Ancona/Util/Assert.hpp>

using namespace ild;

AssertException::AssertException(const std::string & message) : std::runtime_error(message)
{

}

bool AssertControls::_throwException = true;
std::ostream * AssertControls::_errorStream = NULL;

void AssertControls::SetThrowException(bool value)
{
    _throwException = value;
}

void AssertControls::SetErrorStream(std::ostream * errorStream)
{
    _errorStream = errorStream;
}

void AssertControls::_ild_assert(bool condition, const std::string & message, const char * fileName, int lineNumber)
{
    if(!condition)
    {
        std::stringstream errMsg;
        errMsg << "Assert Failed In File: " << fileName << " Line: " << lineNumber <<
            std::endl << "    Message: " << message;
        if(_throwException)
        {
            throw AssertException(errMsg.str());
        }
        if(_errorStream != NULL)
        {
            *_errorStream << errMsg.str();
        }
    }
}
