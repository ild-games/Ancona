#ifndef Ancona_Engine_Core_Systems_ShapeDrawable_H_
#define Ancona_Engine_Core_Systems_ShapeDrawable_H_

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Graphics/Transform.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/Framework/Serializing/SerializingContext.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ild
{

/**
 * @brief Responsible for drawing a shape to the window
 *
 * @author Tucker Lein
 */
class ShapeDrawable : public Drawable
{
    public:
        /**
         * @brief Default constructor, should only be used by the serializer.
         */
        ShapeDrawable() {}

        ShapeDrawable(
                ildhal::Shape * shape,
                const float priority,
                const std::string & key,
                float priorityOffset = 0,
                Vector2f anchor = Vector2f(0.0f, 0.0f));

        Drawable * Copy() override;

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc) override;

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity) override;

        /* getters and setters */
        Vector2f size() override;
        int alpha() override;
        void alpha(int alpha) override;

    private:
        /**
         * @brief Shape used for the drawing.
         */
        std::unique_ptr<ildhal::Shape> _shape;

        void OnDraw(ildhal::RenderTarget & target, Transform drawableTransform, float delta) override;

};

}

#endif
