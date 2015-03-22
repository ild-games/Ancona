#include <Ancona/Engine/Loading/Archive.hpp>

using namespace ild;

Archive::Archive(Json::Value root, LoadingContext & context) :
    _root(root), _context(context)
{
    _jsonBranch.push(&_root);
}
