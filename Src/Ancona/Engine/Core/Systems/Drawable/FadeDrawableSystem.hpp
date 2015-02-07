#ifndef Ancona_Engine_Core_Systems_Drawable_FadeDrawableSystem_H_
#define Ancona_Engine_Core_Systems_Drawable_FadeDrawableSystem_H_

#include <memory>

#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>

#include <SFML/System.hpp>

namespace ild
{

class FadeDrawableSystem;

/**
 * @brief Fades a DrawableComponent either in or out.
 *
 * @author Tucker Lein
 */
class FadeDrawableComponent 
{
    public:
        /**
         * @brief Constructs a new FadeDrawableComponent
         *
         * @param drawableComponent DrawableComponent being faded.
         * @param fadeDrawableSys FadeDrawableSystem for the screen.
         * @param fadeIn True if the graphics are fading in, false if they are fading out.
         * @param fadeSpeed Speed at which the fade occurs, defaults to 650.0f
         */
        FadeDrawableComponent(
                DrawableComponent & drawableComponent,
                float fadeIn,
                float fadeSpeed = 650.0f);

        /**
         * @brief Updates the fade of the DrawableComponent.
         *
         * @param delta Seconds since the last update.
         */
        void Update(float delta);

        /* getters and setters */
        bool GetFadeIn() { return _fadeIn; }
        void SetFadeIn(bool fadeIn) { _fadeIn = fadeIn; }
    private:
        /**
         * @brief The drawable component being faded.
         */
        DrawableComponent & _drawableComponent;

        /**
         * @brief Speed the fade occurs at.
         */
        float const FADE_SPEED;

        /**
         * @brief True if the drawable is fading in, false if it is fading out.
         */
        bool _fadeIn;
};

/**
 * @brief System for managing FadeDrawableComponents
 *
 * @author Tucker Lein
 */
class FadeDrawableSystem : public UnorderedSystem<FadeDrawableComponent>
{
    public:
        /**
         * @brief Default constructor
         *
         * @param manager SystemManager instance for the current screen.
         */
        FadeDrawableSystem(SystemManager & manager);

        /**
         * @brief Updates the components managed by the system.
         *
         * @param delta Seconds since last update
         */
        void Update(float delta);

        /**
         * @brief Constructs a FadeDrawableComponent and attachs it to the system.
         *
         * @param entity Entity to associate the component with.
         * @param drawableComponent DrawableComponent for the entity.
         * @param fadeIn True if the graphics are fading in, false if they are fading out.
         * @param fadeSpeed Speed at which the fade occurs, defaults to 650.0f
         *
         * @return Pointer to the FadeDrawableComponent being created.
         */
        FadeDrawableComponent * CreateComponent(
                const Entity & entity,
                DrawableComponent & drawableComponent,
                bool fadeIn,
                float fadeSpeed = 650.0f);
};


}

#endif
