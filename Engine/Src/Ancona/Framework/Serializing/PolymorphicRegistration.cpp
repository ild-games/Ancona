#include <Ancona/Framework/Serializing/Serializing.hpp>

using namespace ild;

PolymorphicSerializerAbstractBase::PolymorphicSerializerAbstractBase(
        std::string className) : 
    _className(className)
{
}

void PolymorphicSerializerAbstractBase::Serialize(void *&property, Archive &arc)
{
    ILD_Assert(false, "Unable to serialize abstract base class " + _className);
}
