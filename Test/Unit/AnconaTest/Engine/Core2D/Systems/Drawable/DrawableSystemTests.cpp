#include <gtest/gtest.h>

#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/ImageDrawable.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/AnimatedDrawable.hpp>

using namespace ild;

TEST(DrawableSystem, ShapeDrawableSize)
{
    sf::RectangleShape * sfRectShape = new sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
    ShapeDrawable shape(sfRectShape, 0, "shape");

    ASSERT_EQ(shape.size(), sf::Vector2f(50.0f, 50.0f));

    shape.scale(sf::Vector2f(2.0f, 2.0f));
    ASSERT_EQ(shape.size(), sf::Vector2f(100.0f, 100.0f));

    shape.scale(sf::Vector2f(1.3f, 1.0f));
    ASSERT_EQ(shape.size(), sf::Vector2f(65.0f, 50.0f));
}

TEST(DrawableSystem, ImageDrawableSize)
{
    SystemManager manager;
    sf::RenderWindow renderWindow;
    Entity entity = manager.CreateEntity();

    DrawableSystem & drawable = *(new DrawableSystem("drawable", renderWindow, manager));
    CameraSystem & camera = *(new CameraSystem("camera", manager));
    PlatformPhysicsSystem & physics = *(new PlatformPhysicsSystem("physics", manager));

    sf::View view;
    drawable.defaultCamera(camera.CreateComponent(manager.CreateEntity(), view, 0, &drawable, 1.0f));

    sf::Texture * texture = new sf::Texture();
    texture->create(50, 50);
    ImageDrawable * image = new ImageDrawable(texture, 0, "image");
    physics.CreateComponent(entity);
    drawable.CreateComponent(entity, image, &physics);

    manager.Update(1, UpdateStep::Draw);

    ASSERT_EQ(image->size(), sf::Vector2f(50.0f, 50.0f));

    image->scale(sf::Vector2f(2.0f, 2.0f));
    ASSERT_EQ(image->size(), sf::Vector2f(100.0f, 100.0f));

    image->scale(sf::Vector2f(1.3f, 1.0f));
    ASSERT_EQ(image->size(), sf::Vector2f(65.0f, 50.0f));
}

TEST(DrawableSystem, ContainerDrawable)
{
    ContainerDrawable containerDrawable(0, "container");
    ShapeDrawable * shape1 = new ShapeDrawable(new sf::RectangleShape(sf::Vector2f(50.0f, 50.0f)), 0, "shape1");
    containerDrawable.AddDrawable(shape1);

    ASSERT_EQ(containerDrawable.size(), sf::Vector2f(50.0f, 50.0f));

    shape1->positionOffset(sf::Vector2f(-50.0f, 0.0f));
    ShapeDrawable * shape2 = new ShapeDrawable(new sf::RectangleShape(sf::Vector2f(50.0f, 50.0f)), 0, "shape2");
    containerDrawable.AddDrawable(shape2);

    ASSERT_EQ(containerDrawable.size(), sf::Vector2f(100.0f, 50.0f));

    shape2->scale(sf::Vector2f(2.0f, 2.0f));

    ASSERT_EQ(containerDrawable.size(), sf::Vector2f(125.0f, 100.0f));

    ASSERT_EQ(containerDrawable.FindDrawable("shape2"), shape2);
    containerDrawable.RemoveDrawable("shape2");
    ASSERT_EQ(containerDrawable.FindDrawable("shape2"), nullptr);

    ASSERT_EQ(containerDrawable.size(), sf::Vector2f(50.0f, 50.0f));

    shape1->scale(sf::Vector2f(0.5f, 0.5f));

    ASSERT_EQ(containerDrawable.size(), sf::Vector2f(25.0f, 25.0f));

}

TEST(DrawableSystem, AnimatedDrawable)
{
    AnimatedDrawable animatedDrawable(0, "animatedDrawable", 1);
    ShapeDrawable * shape1 = new ShapeDrawable(new sf::RectangleShape(sf::Vector2f(50.0f, 50.0f)), 0, "shape1");
    animatedDrawable.AddFrame(shape1);

    ASSERT_EQ(animatedDrawable.size(), sf::Vector2f(50.0f, 50.0f));

    shape1->scale(sf::Vector2f(2.0f, 2.0f));

    ASSERT_EQ(animatedDrawable.size(), sf::Vector2f(100.0f, 100.0f));

    ASSERT_EQ(animatedDrawable.FindDrawable("shape1"), shape1);
    animatedDrawable.RemoveFrame("shape1");
    ASSERT_EQ(animatedDrawable.FindDrawable("shape1"), nullptr);
}