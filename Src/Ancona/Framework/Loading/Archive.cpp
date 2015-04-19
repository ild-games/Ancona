#include <Ancona/Framework/Loading/Archive.hpp>

using namespace ild;

Archive::Archive(Json::Value root, LoadingContext & context) :
    _root(root), _context(context)
{
    _jsonBranch.push(&_root);
}

Json::Value & Archive::CurrentBranch()
{
    return *_jsonBranch.top();
}

void Archive::EnterProperty(const std::string & name)
{
    _jsonBranch.push(&(CurrentBranch())[name]);
}

void Archive::EnterProperty(const int & name)
{
    _jsonBranch.push(&(CurrentBranch())[name]);
}

void Archive::ExitProperty()
{
    _jsonBranch.pop();
}

bool Archive::HasProperty(const std::string & name)
{
    return CurrentBranch().isMember(name);
}
