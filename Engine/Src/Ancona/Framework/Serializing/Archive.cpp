#include <Ancona/Framework/Serializing/Archive.hpp>

using namespace ild;

Archive::Archive(
        Json::Value root,
        SerializingContext & context,
        bool loading,
        const std::string & mapKey,
        bool snapshotSave) :
    _mapKey(mapKey),
    _loading(loading),
    _snapshotSave(snapshotSave),
    _root(root),
    _context(context)
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
