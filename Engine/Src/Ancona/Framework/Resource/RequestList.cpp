#include <string>
#include <fstream>

#include <Ancona/Framework/Resource/RequestList.hpp>
#include <Ancona/Util/StrUtil.hpp>
#include <Ancona/Util/Algorithm/ContainerWrappers.hpp>

using namespace ild;

RequestList::RequestList() { }

RequestList::RequestList(std::istream & openStream)
{
    LoadFromFile(openStream);
    _next = begin();
    Start();
}

RequestList::RequestList(const std::string & requestFile)
{
    std::ifstream openStream(requestFile, std::ios::out);
    LoadFromFile(openStream);
    Start();
}

void RequestList::Start()
{
    _next = begin();
}

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
    if(_next == end())
    {
        return end();
    }
    return _next++;
}

bool RequestList::Contains(const std::string & resourceType, const std::string & resourceKey)
{
    return alg::find_if(_requestList, [resourceType, resourceKey](const std::pair<std::string, std::string> & entry) {
        return entry.first == resourceType && entry.second == resourceKey;
    }) != _requestList.end();
}

float RequestList::PercentLoaded()
{
    return 1 - ((float) std::distance(_next, end()) /
            _requestList.size());
}

void RequestList::LoadFromFile(std::istream & openStream)
{
    std::vector<std::string> pieces;
    std::string line;

    while(!openStream.eof())
    {
        std::getline(openStream, line);
        pieces.clear();

        pieces = StrUtil::Split(line, ',', 2);

        if(pieces.size() == 2)
        {
            StrUtil::Trim(pieces[0]);
            StrUtil::Trim(pieces[1]);
            Add(pieces[0], pieces[1]);
        }
    }
}
