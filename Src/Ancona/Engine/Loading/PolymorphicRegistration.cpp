#include <Ancona/Engine/Loading/Loading.hpp>

using namespace ild;

PolymorphicSerializerAbstractBase::PolymorphicSerializerAbstractBase(
        std::string className) : 
    _className(className)
{
}

void PolymorphicSerializerAbstractBase::Serialize(void *&property, Archive &arc)
{
    Assert(false, "Unable to serialize abstract base class " + _className);
}
