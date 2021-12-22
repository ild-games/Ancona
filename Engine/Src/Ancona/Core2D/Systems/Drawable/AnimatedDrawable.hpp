#pragma once

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Graphics/Transform.hpp>
#include <Ancona/Util/Vector2.hpp>

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
     * @param anchor Vector that defines the offset from its parent drawable.
     */
    AnimatedDrawable(
        const float priority,
        const std::string & key,
        float duration,
        float priorityOffset = 0,
        Vector2f anchor = Vector2f(0.0f, 0.0f));

    Drawable * Copy() override;
    void PostDrawUpdate(float delta) override;

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

    /**
     * @brief Returns the number of frames in this animation
     *
     * @return number of frames in the animation
     */
    int NumberOfFrames();

    void SetCurrentFrame(unsigned int frame);

    /* getters and setters */
    Vector2f size() override;
    Vector2f position(Vector2f entityPosition) override;
    int alpha() override;
    void alpha(int alpha) override;
    void duration(float duration) { _duration = duration; }
    float duration() { return _duration; }
    void loopOnce(bool loopOnce) { _loopOnce = loopOnce; }
    unsigned int curFrame() { return _curFrame; }

  private:
    std::vector<std::unique_ptr<Drawable>> _frames;
    float _duration;
    float _timeUntilChange = 0;
    unsigned int _curFrame = 0;
    bool _loopOnce = false;

    void Tick(float delta);
    void AdvanceFrame();
    void OnDraw(ildhal::RenderTarget & target, Transform drawableTransform, float delta) override;
};

} // namespace ild
