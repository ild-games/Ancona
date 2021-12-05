#include <Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Core2D/Systems/PositionSystem.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ShapeDrawable);

using namespace ild;

ShapeDrawable::ShapeDrawable(ildhal::Shape *shape, const float priorty, const std::string &key, float priorityOffset,
                             Vector2f anchor)
    : Drawable(priorty, key, priorityOffset, anchor), _shape(shape)
{
}

Drawable *ShapeDrawable::Copy()
{
    ILD_Assert(false, "ShapeDrawable copy not implemented.");
    auto drawable = new ShapeDrawable();
    Drawable::CopyProperties(drawable);
    return drawable;
}

void ShapeDrawable::OnDraw(ildhal::RenderTarget &target, Transform drawableTransform, float delta)
{
    ildhal::RenderStates states(drawableTransform);
    target.Draw(*_shape, states);
}

void ShapeDrawable::FetchDependencies(const Entity &entity)
{
    Drawable::FetchDependencies(entity);
    _shape->origin(_shape->localBounds().width * _anchor.x, _shape->localBounds().height * _anchor.y);
}

void ShapeDrawable::Serialize(Archive &archive)
{
    Drawable::Serialize(archive);
    archive(_shape, "shape");
}

/* getters and setters */
Vector2f ShapeDrawable::size()
{
    Vector2f size(_shape->localBounds().width, _shape->localBounds().height);
    return VectorMath::ComponentMultiplication(size, _scale);
}

int ShapeDrawable::alpha()
{
    return _shape->fillColor().a;
}

void ShapeDrawable::alpha(int alpha)
{
    Color outlineCol(_shape->outlineColor());
    outlineCol.a = alpha;
    _shape->outlineColor(outlineCol);

    Color fillCol(_shape->fillColor());
    fillCol.a = alpha;
    _shape->fillColor(fillCol);
}
