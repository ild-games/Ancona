#ifndef Ancona_Engine_Core_Systems_CameraSystem_H_
#define Ancona_Engine_Core_Systems_CameraSystem_H_

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Core2D/Systems/Physics/BasePhysicsSystem.hpp>
#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

class DrawableSystem;

/**
 * @brief Used to manage a camera's attributes.
 *
 * @author Tucker Lein
 */
class CameraComponent
{
    public:
        /**
         * @brief Default constructor, should only be used by the serializer.
         */
        CameraComponent();

        /**
         * @brief Constructs a new CameraComponent.
         *
         * @param originalView Default view of the window.
         * @param renderPriority priority to render the camera by.
         * @param scale The scale the camera will zoom to, defaults to 1.0f.
         * @param offset The offset the camera will center on, defaults to {0, 0}
         */
        CameraComponent(
                const sf::View & originalView,
                int renderPriority,
                float scale = 1.0f,
                sf::Vector2f offset = sf::Vector2f(0, 0));

        /**
         * @brief Overridable destructor.
         */
        virtual ~CameraComponent() { }

        /**
         * @brief Updates the position of the camera.
         */
        void Update(float delta);

        /**
         * @brief Draws the camera and all renderables on it.
         *
         * @param window RenderWindow for the game.
         */
        void Draw(sf::RenderWindow & window, float delta);

        /**
         * @brief Moves the camera, the default behavior is to lock onto the _followPhysics.
         */
        virtual void MoveCamera();

        /**
         * @brief Adds a DrawableComponent to the camera's render queue.
         *
         * @param drawable DrawableComponent to add.
         */
        void AddDrawableComponent(DrawableComponent * drawable);

        /**
         * @brief Remove a DrawableComponent from the camera's render queue.
         *
         * @param drawable DrawableComponent to remove.
         */
        void RemoveDrawableComponent(DrawableComponent * drawable);

        /**
         * @brief Called before the component is used to gather any dependcies necessary for it to operate.
         *
         * @param entity Entity the component is associated with.
         */
        void FetchDependencies(const Entity & entity);

        /**
         * @brief Responsible for saving and loading the object.
         *
         * @param arc Archive instance during the save/load process.
         */
        void Serialize(Archive & arc);

        /* getters and setters */
        int renderPriority() { return _renderPriority; }
        void follows(Entity follows);
        void scale(float scale);
        float scale() { return _scale; }

    protected:
        /**
         * @brief Position component for what the camera is following.
         */
        BasePhysicsComponent * _followPhysics = nullptr;

    private:
        /**
         * @brief SFML view for actually applying the camera's position on the window.
         */
        sf::View _view;
        /**
         * @brief priority in which the camera is rendered, lower priority means  it will be rendered sooner.
         */
        int _renderPriority;
        /**
         * @brief Queue for the drawables on the camera, sorted by the drawable's render priority + render offset.
         */
        std::vector<DrawableComponent *> _renderQueue;
        float _scale = 1;
        float _originalScale = 1;
        sf::Vector2f _offset;
        Entity _follows;
        sf::Vector2f _size;
        BasePhysicsSystem * _physicsSystem;
        DrawableSystem * _drawableSystem;
        bool _default = false;

};

/**
 * @brief System for managing CameraComponents
 *
 * @author Tucker Lein
 */
class CameraSystem : public UnorderedSystem<CameraComponent>
{
    public:
        /**
         * @brief Constructs the CameraSystem.
         *
         * @param name Name of the system.
         * @param manager SystemManager instance for the current screen.
         */
        CameraSystem(
                std::string name,
                SystemManager & manager);

        /**
         * @brief Updates the components managed by the system.
         */
        void Update(float delta);

        /**
         * @brief Constructs a CameraComponent and attaches it to the system.
         *
         * @param entity Entity to associate the component with.
         * @param originalView Default view of the window.
         * @param renderPriority The render priority of the camera.
         * @param scale The scale the camera will zoom to, defaults to 1.0f.
         *
         * @return Pointer to the CameraComponent being created.
         */
        CameraComponent * CreateComponent(
                const Entity & entity,
                const sf::View & originalView,
                int renderPriority,
                float scale = 1.0f);

};

}

#endif
