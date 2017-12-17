#include <Ancona/Framework/Serializing/Archive.hpp>
#include <Ancona/System/Log.hpp>

using namespace ild;

Archive::Archive(
        rapidjson::Value * root,
        SerializingContext & context,
        bool loading,
        bool snapshotSave) :
    _loading(loading),
    _snapshotSave(snapshotSave),
    _root(root),
    _context(context)
{
    _jsonBranch.push(_root);
}

rapidjson::Value & Archive::CurrentBranch()
{
    return *_jsonBranch.top();
}

bool Archive::EnterProperty(const std::string & name)
{
    if (!CurrentBranch().HasMember(name)) {
        return false;
    }
    _jsonBranch.push(&(CurrentBranch())[name]);
    return true;
}

bool Archive::EnterProperty(const int & name)
{
    _jsonBranch.push(&(CurrentBranch())[name]);
    return true;
}

void Archive::ExitProperty()
{
    _jsonBranch.pop();
}

bool Archive::HasProperty(const std::string & name)
{
    return CurrentBranch().HasMember(name);
}
