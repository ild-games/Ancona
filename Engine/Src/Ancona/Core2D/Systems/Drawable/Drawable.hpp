#ifndef Ancona_Engine_Core_Systems_Drawable_H_
#define Ancona_Engine_Core_Systems_Drawable_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

namespace RenderPriority
{

    /**
     * @brief Determines when the drawable objects are rendered, the lower the priority the sooner they are rendered.
     *
     * @author Tucker Lein
     */
    enum RenderPriority
    {
        Background = -1000,
        Player = 0,
        Foreground = 1000,
    };
}

/**
 * @brief Defines when the sprite should be rendered
 *
 * @author Tucker Lein
 */
typedef RenderPriority::RenderPriority RenderPriorityEnum;

class DrawableSystem;
class DrawableComponent;

/**
 * @brief Defines a drawable element used in the DrawableSystem
 *
 * @author Tucker Lein
 */
class Drawable
{

    public:
        /**
         * @brief Default constructor, should only be used by the serializer.
         */
        Drawable () {}

        virtual ~Drawable() {};

        /**
         * @brief Constructs a Drawable.
         *
         * @param priority RenderPriority that determines when the drawable obj is rendered.
         * @param key Key of the drawable.
         * @param priorityOffset Optional offset to the render priority.
         * @param anchor Vector that defines the offset from its parent drawable.
         */
        Drawable(
                const float priority,
                const std::string & key,
                float priorityOffset = 0,
                sf::Vector2f anchor = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Draws the object to the window.
         *
         * @param window RenderWindow for the game.
         * @param parentTransform Transform of the parent drawable.
         */
        void Draw(
                sf::RenderTarget & target,
                sf::Transform parentTransform,
                float delta);

        virtual void PostDrawUpdate(float delta) { }

        virtual Drawable * Copy() = 0;
        void CopyProperties(Drawable * drawable);

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        virtual void FetchDependencies(const Entity & entity);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        virtual void Serialize(Archive & arc);

        /**
         * Sets the direction of the drawable in the x axis.
         * @param leftOrRightSignum -1 if the drawable should be facing left, 1 if right.
         */
        void SetXDirection(int leftOrRightSignum);

        /**
         * Sets the direction of the drawable in the y axis.
         * @param upOrDownSignum -1 if the drawable should be facing up, 1 if down.
         */
        void SetYDirection(int upOrDownSignum);

        /**
         * @brief Finds a drawable contained within this drawable. The default
         *        implementation simply returns itself if the keys match. Container
         *        and Animation drawables will walk their children to try and find
         *        the drawable if the keys do not match.
         *
         * @param key Key of the drawable to find
         *
         * @returns Pointer to the drawable, nullptr if no such drawable exists.
         */
        virtual Drawable * FindDrawable(const std::string & key);

        /* getters and setters */
        float renderPriority() const { return _renderPriority + _priorityOffset; }
        void renderPriority(const float renderPriority) { _renderPriority = renderPriority; }
        void priorityOffset(const float priorityOffset) { _priorityOffset = priorityOffset; }
        sf::Vector2f anchor() { return _anchor; }
        void anchor(sf::Vector2f anchor) { _anchor = anchor; }
        float rotation() { return _rotation; }
        sf::Vector2f scale() { return _scale; }
        void rotation(float rotation) { _rotation = rotation; }
        void scale(sf::Vector2f scale) { _scale = scale; };
        /**
         * @brief The actual position of a drawable takes in the position from the position component
         *        and also takes into account the anchor of the drawable which might change it's true
         *        position.
         *
         * @param entityPosition The position from the entity's position component
         *
         * @returns The actual position the drawable is drawn at
         */
        virtual sf::Vector2f position(sf::Vector2f entityPosition);
        virtual sf::Vector2f size() = 0;
        virtual int alpha() = 0;
        virtual void alpha(int alpha) = 0;
        std::string key() { return _key; }
        void key(const std::string & key) { _key = key; }
        bool inactive() { return _inactive; }
        void inactive(bool inactive) { _inactive = inactive; }


    protected:
        /**
         * @brief Key that describes the Drawable.
         */
        std::string _key;
        /**
         * @brief Offset coordinate for this drawable element.
         */
        sf::Vector2f _anchor;
        /**
         * @brief Amount to scale the drawable element.
         */
        sf::Vector2f _scale = sf::Vector2f(1.0f, 1.0f);
        /**
         * @brief priority of rendering this obj.
         */
        float _renderPriority;
        /**
         * @brief Offsets the render priority.
         */
        float _priorityOffset;
        /**
         * @brief Amount to rotate the drawable element.
         */
        float _rotation = 0;
        /**
         * @brief True if the drawable is actively drawn/updated. Otherwise false.
         */
        bool _inactive = false;
    private:

        sf::Transform CalculateTransforms();
        virtual void OnDraw(
                sf::RenderTarget & target,
                sf::Transform drawableTransform,
                float delta) = 0;
};

}

GENERATE_ABSTRACT_CLASS_CONSTRUCTOR(ild::Drawable)

#endif
