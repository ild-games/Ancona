#include <Ancona/Engine/Resource/RequestList.hpp>

using namespace ild;

void RequestList::Add(const std::string & resourceType, const std::string & resourceKey)
{
    _requestList.push_back(
            std::pair<std::string,std::string>(resourceType,resourceKey)); 
}

RequestList::iterator RequestList::begin() const
{
    return _requestList.cbegin();
}

RequestList::iterator RequestList::end() const
{
    return _requestList.cend();
}

RequestList::iterator RequestList::Next()
{
    return _next++;
}
