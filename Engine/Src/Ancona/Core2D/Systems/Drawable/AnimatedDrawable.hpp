#ifndef Ancona_Engine_Core_Systems_AnimatedDrawable_H_
#define Ancona_Engine_Core_Systems_AnimatedDrawable_H_

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>

namespace ild
{

/**
 * @brief Responsible for drawing an animation that is made up of multiple frames, each frame
 *        is its own drawable.
 *
 * @author Tucker Lein
 */
class AnimatedDrawable : public Drawable
{
    public:
        /**
         * @brief Default constructor, should only be used by the serializer.
         */
        AnimatedDrawable() {}

        /**
         * @brief Constructs an AnimatedDrawable
         *
         * @param priority RenderPriority that determines when the drawable obj is rendered.
         * @param duration Seconds per frame.
         * @param priorityOffset Optional offset to the render priority.
         * @param positionOffset Vector that defines the offset from its parent drawable.
         */
        AnimatedDrawable(
                const int priority,
                const std::string & key,
                float duration,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));


        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc) override;

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity) override;

        /**
         * @brief Adds a frame to the AnimatedDrawable
         *
         * @param Drawable to add as frame.
         */
        void AddFrame(Drawable * frame);

        /**
         * @brief Removes a frame from the AnimatedDrawable
         *
         * @param key Key of drawable to remove.
         */
        void RemoveFrame(const std::string & key);

        /**
         * @copydoc ild::Drawable::FindDrawable
         */
        Drawable * FindDrawable(const std::string & key) override;

        /* getters and setters */
        sf::Vector2f size() override;
        int alpha() override;
        void alpha(int alpha) override;

    private:
        /**
         * Contains the drawables that will be displayed, the order in this list is the order they are displayed in.
         */
        std::vector<std::unique_ptr<Drawable>> _frames;
        /**
         * @brief Seconds per frame.
         */
        float _duration;
        /**
         * @brief time until the frame changes.
         */
        float _timeUntilChange;
        /**
         * @brief The current frame being shown.
         */
        int _curFrame = 0;

        /**
         * @brief Ticks the animation, will switch the frame when it is time to do so.
         */
        void Tick(float delta);
        void AdvanceFrame();
        void OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta) override;
};

}

#endif
