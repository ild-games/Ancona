#ifndef Ancona_Engine_Core_Systems_DrawableSystem_H_
#define Ancona_Engine_Core_Systems_DrawableSystem_H_

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/ShapeComponent.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/SpriteComponent.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/TextComponent.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>

namespace ild
{



/**
 * @brief Manages all DrawableComponents for a screen.
 *
 * @author Tucker Lein
 */
class DrawableSystem : public UnorderedSystem<DrawableComponent>
{
    public:
        /**
         * @brief Construct the DrawableSystem.
         *
         * @param window RenderWindow for game.
         * @param systemManager SystemManager for the screen.
         * @param positionSystem PositionSystem for the screen.
         */
        DrawableSystem(
                sf::RenderWindow & window,
                SystemManager & systemManager,
                PositionSystem & positionSystem);

        /**
         * @brief Create a sprite component for the entity.
         *
         * @param entity Entity that the component should be attached to.
         * @param textureKey Key that describes the texture the sprite should use.
         * @param priority RenderPriority that handles when the sprite is drawn.
         * @param priorityOffset offset of priority, defaults to 0.
         *
         * @return A pointer to the SpriteComponent.
         */
        SpriteComponent * CreateSpriteComponent(
                const Entity & entity, 
                const std::string & textureKey,
                const RenderPriorityEnum priority,
                int priorityOffset = 0);

        /**
         * @brief Create a text component for the entity.
         *
         * @param entity Entity that the component should be attached to.
         * @param text Text shown on the window.
         * @param fontKey Name of font to use.
         * @param color Color of font.
         * @param characterSize Size of font in pixels.
         * @param priority RenderPriority that handles when the text is drawn.
         * @param priorityOffset offset of priority, defaults to 0.
         * @param smooth Determines if the font is smooth or not, defaults to true.
         *
         * @return Pointer to the TextComponent.
         */
        TextComponent * CreateTextComponent(
                const Entity & entity,
                const std::string text,
                const std::string fontKey,
                const sf::Color color,
                const int characterSize,
                const RenderPriorityEnum priority,
                int priorityOffset = 0,
                bool smooth = true);

        /**
         * @brief Create a shape component for the entity.
         *
         * @param entity Entity that the component should be attached to.
         * @param shape Shape to be drawn.
         * @param priority RenderPriority that handles when the text is drawn.
         * @param priorityOffset Offset of priority, defaults to 0.
         *
         * @return Pointer to the ShapeComponent.
         */
        ShapeComponent * CreateShapeComponent(
                const Entity & entity,
                sf::Shape & shape,
                const RenderPriorityEnum priority,
                int priorityOffset = 0);


        /**
         * @brief Draw all drawable elements to the screen.
         *
         * @param delta Ignored by the drawable system.
         */
        void Update(float delta);

    protected:
        /**
         * @see ild::SystemManager::OnComponentRemove(Entity, ComponentType*)
         */
        void OnComponentRemove(Entity entity, DrawableComponent * component);

    private:
        /**
         * @brief The window the sprite system will draw to.
         */
        sf::RenderWindow & _window;
        /**
         * @brief The system used to determine where an entity should be drawn.
         */
        PositionSystem & _positionSystem;
        /**
         * @brief Holds pointers to the sprite components sorted by priority + priorityOffset.
         */
        std::vector<DrawableComponent * > _renderQueue;

        /**
         * @brief Attaches a drawable component and places it in the render queue.
         *
         * @param entity Entity that the component should be attached to.
         * @param component DrawableComponent to attach.
         * @param textureKey Key that describes the texture the sprite should use.
         * @param priority RenderPriority that handles when the sprite is drawn.
         *
         * @return A pointer to the newly created sprite.
         */
        void AttachComponent(
                const Entity & entity,
                DrawableComponent & component,
                const RenderPriorityEnum priority,
                int priorityOffset = 0);
};

}

#endif
