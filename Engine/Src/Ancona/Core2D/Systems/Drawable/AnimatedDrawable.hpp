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

        /**
         * Reset the Animation to the first frame.
         */
        void ResetAnimation();

        /**
         * Check if the animation should only run once and the last frame has played.
         * @return True if the animation is no longer playing, false otherwise.
         */
        bool IsFinished();

        /* getters and setters */
        sf::Vector2f size() override;
        int alpha() override;
        void alpha(int alpha) override;
        void duration(float duration) { _duration = duration; }
        float duration() { return _duration; }
        void loopOnce(bool loopOnce) { _loopOnce = loopOnce; }

    private:
        std::vector<std::unique_ptr<Drawable>> _frames;
        float _duration;
        float _timeUntilChange;
        int _curFrame = 0;
        bool _loopOnce = false;


        void Tick(float delta);
        void AdvanceFrame();
        void OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta) override;
};

}

#endif
