#include <Ancona/Engine/Loading/InflaterMap.hpp>

using namespace ild;

void InflaterMap::AddAbstract(std::string key, AbstractInflater * inflater)
{
    _typeMap.emplace(key, std::unique_ptr<AbstractInflater>(inflater));
}

AbstractInflater * InflaterMap::GetInflater(std::string key)
{
    return _typeMap[key].get();
}
