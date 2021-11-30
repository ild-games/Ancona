#ifndef Ancona_Engine_Core_Systems_CameraSystem_H_
#define Ancona_Engine_Core_Systems_CameraSystem_H_

#include <vector>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Graphics/View.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Util/Vector2.hpp>

namespace ild {

class DrawableSystem;

/**
 * @brief Used to manage a camera's attributes.
 *
 * @author Tucker Lein
 */
class CameraComponent {
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
     * @param lowerBounds The min position the camera can be in for the x and y axis
     * @param upperBounds The max position the camera can be in for the x and y axis
     */
    CameraComponent(
        const View& originalView,
        float renderPriority,
        DrawableSystem* drawableSystem,
        float scale = 1.0f,
        Vector2f offset = Vector2f(0, 0),
        Vector2f lowerBounds = Vector2f(std::numeric_limits<float>::min(), std::numeric_limits<float>::min()),
        Vector2f upperBounds = Vector2f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()));

    /**
     * @brief Overridable destructor.
     */
    virtual ~CameraComponent() {}

    /**
     * @brief Updates the position of the camera.
     */
    void Update(float delta);

    /**
     * @brief Draws the camera and all renderables on it.
     */
    void Draw(ildhal::RenderTarget& target, ildhal::Window & window, float delta);

    /**
     * @brief Adds a DrawableComponent to the camera's render queue.
     *
     * @param drawable DrawableComponent to add.
     */
    void AddDrawableComponent(DrawableComponent* drawable);

    /**
     * @brief Remove a DrawableComponent from the camera's render queue.
     *
     * @param drawable DrawableComponent to remove.
     */
    void RemoveDrawableComponent(DrawableComponent* drawable);

    /**
     * @brief Called before the component is used to gather any dependcies necessary for it to operate.
     *
     * @param entity Entity the component is associated with.
     */
    void FetchDependencies(const Entity& entity);

    /**
     * @brief Responsible for saving and loading the object.
     *
     * @param arc Archive instance during the save/load process.
     */
    void Serialize(Archive& arc);

    /* getters and setters */
    float renderPriority() { return _renderPriority; }
    void follows(Entity follows);
    void scale(float scale);
    float scale() { return _scale; }
    void lowerBounds(const Vector2f& lowerBounds) { _lowerBounds = lowerBounds; }
    const Vector2f& lowerBounds() { return _lowerBounds; }
    void upperBounds(const Vector2f& upperBounds) { _upperBounds = upperBounds; }
    const Vector2f& upperBounds() { return _upperBounds; }
    const View& view() { return _view; }
    const Vector2f& offset() { return _offset; }
    void offset(const Vector2f& offset) { _offset = offset; }

protected:
    /**
     * @brief Position component for what the camera is following.
     */
    PositionComponent* _followPosition = nullptr;

    /**
     * @brief Gets the true center position for the camera that will determine the location of the camera
     *        each frame. By default this will handle such things as:
     *          * following the follows entity
     *          * applying offset
     *          * applying bounds
     * @returns Vector for the true position of the camera
     */
    virtual Vector2f GetEffectiveCenter();

private:
    /**
     * @brief View for actually applying the camera's position on the window.
     */
    View _view;
    /**
     * @brief priority in which the camera is rendered, lower priority means  it will be rendered sooner.
     */
    float _renderPriority;
    /**
     * @brief Queue for the drawables on the camera, sorted by the drawable's render priority + render offset.
     */
    std::vector<DrawableComponent*> _renderQueue;
    float _scale = 1;
    float _originalScale = 1;
    Vector2f _offset;
    Entity _follows = nullentity;
    Vector2f _size;
    Vector2f _lowerBounds;
    Vector2f _upperBounds;
    PositionSystem* _positionSystem;
    DrawableSystem* _drawableSystem;
    bool _default = false;
    bool _sorted = false;
    Vector2f _startingCenter;

    void ApplyLetterboxView(int windowWidth, int windowHeight);
};

/**
 * @brief System for managing CameraComponents
 *
 * @author Tucker Lein
 */
class CameraSystem : public UnorderedSystem<CameraComponent> {
public:
    /**
     * @brief Constructs the CameraSystem.
     *
     * @param name Name of the system.
     * @param manager SystemManager instance for the current screen.
     */
    CameraSystem(
        std::string name,
        SystemManager& manager);

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
    CameraComponent* CreateComponent(
        const Entity& entity,
        const View& originalView,
        float renderPriority,
        DrawableSystem* drawableSystem,
        float scale = 1.0f);
};
}

#endif
