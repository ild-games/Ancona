#include <Ancona/Core2D/Systems/Drawable/Image.hpp>

REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(ild::Image);

using namespace ild;

void Image::Serialize(Archive & arc)
{
    arc(_textureKey, "texture-key");
}
