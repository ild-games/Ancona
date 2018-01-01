#include <Ancona/Framework/Serializing/Archive.hpp>
#include <Ancona/System/Log.hpp>

using namespace ild;

Archive::Archive(
        rapidjson::Value * root,
        std::shared_ptr<SerializingContext> context,
        bool loading,
        rapidjson::MemoryPoolAllocator<> & allocator,
        bool snapshotSave) :
    _loading(loading),
    _snapshotSave(snapshotSave),
    _root(root),
    _context(context),
    _allocator(allocator)
{
    _jsonBranch.push(_root);
}

rapidjson::Value & Archive::CurrentBranch()
{
    return *_jsonBranch.top();
}

bool Archive::EnterProperty(const std::string & name, bool createIfMissing, const rapidjson::Type typeToCreate)
{
    if (!CurrentBranch().HasMember(name)) {
        if (createIfMissing) {
            rapidjson::Value key(name, _allocator);
            CurrentBranch().AddMember(key, rapidjson::Value(typeToCreate), _allocator);
        } else {
            return false;
        }
    }
    _jsonBranch.push(&(CurrentBranch())[name]);
    return true;
}

bool Archive::EnterProperty(const int & index, bool createIfMissing, const rapidjson::Type typeToCreate)
{
    if (index >= CurrentBranch().Size()) {
        if (createIfMissing) {
            Assert(index == CurrentBranch().Size(), "Cannot add a new value to a json array beyond the size");
            CurrentBranch().PushBack(rapidjson::Value(typeToCreate), _allocator);
        } else {
            return false;
        }
    }

    _jsonBranch.push(&(CurrentBranch())[index]);
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
