cmake_minimum_required(VERSION 3.15)

include(CMakePackageConfigHelpers)

# Generate version from the version.h header file
set(Ancona_VERSION_MAJOR 1)
set(Ancona_VERSION_MINOR 0)
set(Ancona_VERSION_PATCH 0)
set(Ancona_VERSION ${Ancona_VERSION_MAJOR}.${Ancona_VERSION_MINOR}.${Ancona_VERSION_PATCH})

# Define the library's project
project(
  Ancona
    LANGUAGES C CXX
    VERSION ${Ancona_VERSION}
    DESCRIPTION "Ancona game engine"
)

# General compile_commands.json for clangd lsp, has to be above target creation
set(
  CMAKE_EXPORT_COMPILE_COMMANDS ON
  CACHE
    BOOL
    "Generate compile commands database for clang tooling"
    FORCE
)

# Define the library and its alias
add_library(Ancona SHARED)
add_library(Ancona::Ancona ALIAS Ancona)

# Link dependencies
find_package(rapidjson CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
target_link_libraries(
  Ancona
    PRIVATE
      SDL2::SDL2
      SDL2_image::SDL2_image
      SDL2_ttf::SDL2_ttf
      SDL2_mixer::SDL2_mixer
)
if (APPLE)
  enable_language(OBJC)
  enable_language(OBJCXX)
  target_link_libraries(
    Ancona
      PRIVATE
        "-framework Foundation"
  )
endif()
if (ANDROID)
  find_library(android-lib android)
  find_library(log-lib log)
  target_link_libraries(
    Ancona
      PRIVATE
        android
        log
  )
endif()

# Set the library's version
set_target_properties(
  Ancona
    PROPERTIES
      SOVERSION ${Ancona_VERSION_MAJOR}
      VERSION ${Ancona_VERSION}
      DEBUG_POSTFIX "-d"
)

# We need this directory, and users of our library will need it too
target_include_directories(
  Ancona
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Engine/Src>
      $<INSTALL_INTERFACE:include>
)

# Enumerate headers
set(
  Ancona_PUBLIC_HEADERS
    Engine/Src/Ancona/Core.hpp
    Engine/Src/Ancona/Core2D.hpp
    Engine/Src/Ancona/Framework.hpp
    Engine/Src/Ancona/Graphics.hpp
    Engine/Src/Ancona/HAL.hpp
    Engine/Src/Ancona/Menu.hpp
    Engine/Src/Ancona/Platformer.hpp
    Engine/Src/Ancona/System.hpp
    Engine/Src/Ancona/Util.hpp
    Engine/Src/Ancona/Util2D.hpp
)


target_sources(
  Ancona
    PRIVATE
      Engine/Src/Ancona/Core/Game.cpp
      Engine/Src/Ancona/Core2D/Systems/CameraSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/InputControlComponent.cpp
      Engine/Src/Ancona/Core2D/Systems/InputControlSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/PathFollowerSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/PathSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/PositionSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/RotateSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/TriggerDeathSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/Audio/AutoStartMusicSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/Audio/Music.cpp
      Engine/Src/Ancona/Core2D/Systems/Audio/MusicSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/Audio/Sound.cpp
      Engine/Src/Ancona/Core2D/Systems/Audio/SoundSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/Collision/CollisionComponent.cpp
      Engine/Src/Ancona/Core2D/Systems/Collision/CollisionSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/AnimatedDrawable.cpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/ContainerDrawable.cpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/Drawable.cpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/DrawableComponent.cpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/DrawableSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/FadeDrawableSystem.cpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/ImageDrawable.cpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/ShapeDrawable.cpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/TextDrawable.cpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/TileBlockDrawable.cpp
      Engine/Src/Ancona/Framework/Audio/Jukebox.cpp
      Engine/Src/Ancona/Framework/Audio/JukeboxSounds.cpp
      Engine/Src/Ancona/Framework/Config/Config.cpp
      Engine/Src/Ancona/Framework/EntityFramework/AbstractSystem.cpp
      Engine/Src/Ancona/Framework/EntityFramework/SystemManager.cpp
      Engine/Src/Ancona/Framework/Resource/AbstractLoader.cpp
      Engine/Src/Ancona/Framework/Resource/FontLoader.cpp
      Engine/Src/Ancona/Framework/Resource/RequestList.cpp
      Engine/Src/Ancona/Framework/Resource/ResourceLibrary.cpp
      Engine/Src/Ancona/Framework/Resource/ResourceLoaderInit.cpp
      Engine/Src/Ancona/Framework/Resource/SoundBufferLoader.cpp
      Engine/Src/Ancona/Framework/Resource/TextureLoader.cpp
      Engine/Src/Ancona/Framework/Screens/AbstractScreen.cpp
      Engine/Src/Ancona/Framework/Screens/LoadingScreen.cpp
      Engine/Src/Ancona/Framework/Screens/ScreenManager.cpp
      Engine/Src/Ancona/Framework/Serializing/HalSerializer.cpp
      Engine/Src/Ancona/Framework/Serializing/MapSerializer.cpp
      Engine/Src/Ancona/Framework/Serializing/PolymorphicMap.cpp
      Engine/Src/Ancona/Framework/Serializing/PolymorphicRegistration.cpp
      Engine/Src/Ancona/Framework/Serializing/SerializingContext.cpp
      Engine/Src/Ancona/Framework/Systems/ScreenSystemsContainer.cpp
      Engine/Src/Ancona/Graphics/Color.cpp
      Engine/Src/Ancona/Graphics/MatrixTransform.cpp
      Engine/Src/Ancona/Graphics/Transform.cpp
      Engine/Src/Ancona/Graphics/Rect.inl
      Engine/Src/Ancona/Graphics/View.cpp
      Engine/Src/Ancona/HAL/SDL/BlendModeImpl.cpp
      Engine/Src/Ancona/HAL/SDL/CircleShapeImpl.cpp
      Engine/Src/Ancona/HAL/SDL/ClockImpl.cpp
      Engine/Src/Ancona/HAL/SDL/EventImpl.cpp
      Engine/Src/Ancona/HAL/SDL/FontImpl.cpp
      Engine/Src/Ancona/HAL/SDL/JoystickImpl.cpp
      Engine/Src/Ancona/HAL/SDL/KeyboardImpl.cpp
      Engine/Src/Ancona/HAL/SDL/MouseImpl.cpp
      Engine/Src/Ancona/HAL/SDL/MusicImpl.cpp
      $<$<PLATFORM_ID:Android>:Engine/Src/Ancona/HAL/SDL/OSImpl.Android.cpp>
      $<$<PLATFORM_ID:Darwin>:Engine/Src/Ancona/HAL/SDL/OSImpl.Desktop.cpp>
      $<$<PLATFORM_ID:Windows>:Engine/Src/Ancona/HAL/SDL/OSImpl.Desktop.cpp>
      $<$<PLATFORM_ID:Linux>:Engine/Src/Ancona/HAL/SDL/OSImpl.Desktop.cpp>
      Engine/Src/Ancona/HAL/SDL/RectangleShapeImpl.cpp
      Engine/Src/Ancona/HAL/SDL/RenderStatesImpl.cpp
      Engine/Src/Ancona/HAL/SDL/RenderTargetImpl.cpp
      Engine/Src/Ancona/HAL/SDL/RenderTextureImpl.cpp
      Engine/Src/Ancona/HAL/SDL/ShapeImpl.cpp
      Engine/Src/Ancona/HAL/SDL/SleepImpl.cpp
      Engine/Src/Ancona/HAL/SDL/SoundBufferImpl.cpp
      Engine/Src/Ancona/HAL/SDL/SoundImpl.cpp
      Engine/Src/Ancona/HAL/SDL/SoundSourceImpl.cpp
      Engine/Src/Ancona/HAL/SDL/SpriteImpl.cpp
      Engine/Src/Ancona/HAL/SDL/TextImpl.cpp
      Engine/Src/Ancona/HAL/SDL/TextureImpl.cpp
      Engine/Src/Ancona/HAL/SDL/TimeImpl.cpp
      Engine/Src/Ancona/HAL/SDL/TouchImpl.cpp
      Engine/Src/Ancona/HAL/SDL/VertexArrayImpl.cpp
      Engine/Src/Ancona/HAL/SDL/WindowImpl.cpp
      Engine/Src/Ancona/Menu/Screens/MenuGameSystems.cpp
      Engine/Src/Ancona/Menu/Screens/MenuInputHandler.cpp
      Engine/Src/Ancona/Menu/Screens/MenuKeyboardAndMouse.cpp
      Engine/Src/Ancona/Menu/Screens/MenuScreen.cpp
      Engine/Src/Ancona/Menu/Screens/MenuTouch.cpp
      Engine/Src/Ancona/Menu/Systems/ButtonSystem.cpp
      Engine/Src/Ancona/Platformer/Actions/Actions.cpp
      Engine/Src/Ancona/Platformer/Actions/ActionSystem.cpp
      $<$<PLATFORM_ID:Android>:Engine/Src/Ancona/System/Android/EventHandling.cpp>
      $<$<PLATFORM_ID:Android>:Engine/Src/Ancona/System/Android/FileOperations.cpp>
      $<$<PLATFORM_ID:Android>:Engine/Src/Ancona/System/Android/Log.cpp>
      $<$<PLATFORM_ID:Windows>:Engine/Src/Ancona/System/Desktop/EventHandling.cpp>
      $<$<PLATFORM_ID:Windows>:Engine/Src/Ancona/System/Desktop/FileOperations.cpp>
      $<$<PLATFORM_ID:Windows>:Engine/Src/Ancona/System/Desktop/Log.cpp>
      $<$<PLATFORM_ID:Linux>:Engine/Src/Ancona/System/Desktop/EventHandling.cpp>
      $<$<PLATFORM_ID:Linux>:Engine/Src/Ancona/System/Desktop/FileOperations.cpp>
      $<$<PLATFORM_ID:Linux>:Engine/Src/Ancona/System/Desktop/Log.cpp>
      $<$<PLATFORM_ID:iOS>:Engine/Src/Ancona/System/macOS/EventHandling.cpp>
      $<$<PLATFORM_ID:iOS>:Engine/Src/Ancona/System/macOS/FileOperations.mm>
      $<$<PLATFORM_ID:iOS>:Engine/Src/Ancona/System/macOS/Log.mm>
      $<$<PLATFORM_ID:Darwin>:Engine/Src/Ancona/System/macOS/EventHandling.cpp>
      $<$<PLATFORM_ID:Darwin>:Engine/Src/Ancona/System/macOS/FileOperations.mm>
      $<$<PLATFORM_ID:Darwin>:Engine/Src/Ancona/System/macOS/Log.cpp>
      Engine/Src/Ancona/Util/Assert.cpp
      Engine/Src/Ancona/Util/Math.cpp
      Engine/Src/Ancona/Util/StrUtil.cpp
      Engine/Src/Ancona/Util/Timer.cpp
      Engine/Src/Ancona/Util/Vector2.inl
      Engine/Src/Ancona/Util/Vector3.inl
      Engine/Src/Ancona/Util2D/VectorMath.cpp
      Engine/Src/Ancona/Util2D/Collision/Box2.cpp
      Engine/Src/Ancona/Util2D/Collision/Box3.cpp
      Engine/Src/Ancona/Util2D/Collision/Math.cpp
      Engine/Src/Ancona/Core.hpp
      Engine/Src/Ancona/Core2D.hpp
      Engine/Src/Ancona/Framework.hpp
      Engine/Src/Ancona/Graphics.hpp
      Engine/Src/Ancona/HAL.hpp
      Engine/Src/Ancona/Menu.hpp
      Engine/Src/Ancona/Platformer.hpp
      Engine/Src/Ancona/System.hpp
      Engine/Src/Ancona/Util.hpp
      Engine/Src/Ancona/Util2D.hpp
      Engine/Src/Ancona/Core/Game.hpp
      Engine/Src/Ancona/Core2D/InputDevices/InputHandler.hpp
      Engine/Src/Ancona/Core2D/Systems/CameraSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/InputControlComponent.hpp
      Engine/Src/Ancona/Core2D/Systems/InputControlSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/PathFollowerSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/PathSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/PositionSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/RotateSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/TriggerDeathSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/Audio/AutoStartMusicSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/Audio/Music.hpp
      Engine/Src/Ancona/Core2D/Systems/Audio/MusicSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/Audio/Sound.hpp
      Engine/Src/Ancona/Core2D/Systems/Audio/SoundSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/Collision/Collision.hpp
      Engine/Src/Ancona/Core2D/Systems/Collision/CollisionComponent.hpp
      Engine/Src/Ancona/Core2D/Systems/Collision/CollisionSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/AnimatedDrawable.hpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/ContainerDrawable.hpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/Drawable.hpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/DrawableComponent.hpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/FadeDrawableSystem.hpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/ImageDrawable.hpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/TextDrawable.hpp
      Engine/Src/Ancona/Core2D/Systems/Drawable/TileBlockDrawable.hpp
      Engine/Src/Ancona/Framework/Audio/Jukebox.hpp
      Engine/Src/Ancona/Framework/Audio/JukeboxSounds.hpp
      Engine/Src/Ancona/Framework/Config/Config.hpp
      Engine/Src/Ancona/Framework/EntityFramework/AbstractSystem.hpp
      Engine/Src/Ancona/Framework/EntityFramework/Entity.hpp
      Engine/Src/Ancona/Framework/EntityFramework/SystemManager.hpp
      Engine/Src/Ancona/Framework/EntityFramework/UnorderedSystem.hpp
      Engine/Src/Ancona/Framework/EntityFramework/UpdateStep.hpp
      Engine/Src/Ancona/Framework/Resource/AbstractLoader.hpp
      Engine/Src/Ancona/Framework/Resource/FontLoader.hpp
      Engine/Src/Ancona/Framework/Resource/HalResourceLoader.hpp
      Engine/Src/Ancona/Framework/Resource/RequestList.hpp
      Engine/Src/Ancona/Framework/Resource/ResourceLibrary.hpp
      Engine/Src/Ancona/Framework/Resource/ResourceLoaderInit.hpp
      Engine/Src/Ancona/Framework/Resource/SoundBufferLoader.hpp
      Engine/Src/Ancona/Framework/Resource/TextureLoader.hpp
      Engine/Src/Ancona/Framework/Screens/AbstractScreen.hpp
      Engine/Src/Ancona/Framework/Screens/LoadingScreen.hpp
      Engine/Src/Ancona/Framework/Screens/ScreenManager.hpp
      Engine/Src/Ancona/Framework/Serializing/Archive.cpp
      Engine/Src/Ancona/Framework/Serializing/Archive.hpp
      Engine/Src/Ancona/Framework/Serializing/ClassConstructor.hpp
      Engine/Src/Ancona/Framework/Serializing/HalSerializer.hpp
      Engine/Src/Ancona/Framework/Serializing/MapSerializer.hpp
      Engine/Src/Ancona/Framework/Serializing/PolymorphicMap.hpp
      Engine/Src/Ancona/Framework/Serializing/PolymorphicRegistration.hpp
      Engine/Src/Ancona/Framework/Serializing/PolymorphicSerializer.hpp
      Engine/Src/Ancona/Framework/Serializing/Serializer.hpp
      Engine/Src/Ancona/Framework/Serializing/Serializing.hpp
      Engine/Src/Ancona/Framework/Serializing/SerializingContext.hpp
      Engine/Src/Ancona/Framework/Serializing/StdSerializer.hpp
      Engine/Src/Ancona/Framework/Serializing/UtilSerializer.hpp
      Engine/Src/Ancona/Framework/Systems/ScreenSystemsContainer.hpp
      Engine/Src/Ancona/Graphics/Color.hpp
      Engine/Src/Ancona/Graphics/MatrixTransform.hpp
      Engine/Src/Ancona/Graphics/Rect.hpp
      Engine/Src/Ancona/Graphics/Rect.inl
      Engine/Src/Ancona/Graphics/Transform.hpp
      Engine/Src/Ancona/Graphics/View.hpp
      Engine/Src/Ancona/HAL/BlendMode.hpp
      Engine/Src/Ancona/HAL/CircleShape.hpp
      Engine/Src/Ancona/HAL/Clock.hpp
      Engine/Src/Ancona/HAL/Drawable.hpp
      Engine/Src/Ancona/HAL/Event.hpp
      Engine/Src/Ancona/HAL/Font.hpp
      Engine/Src/Ancona/HAL/Joystick.hpp
      Engine/Src/Ancona/HAL/Keyboard.hpp
      Engine/Src/Ancona/HAL/Mouse.hpp
      Engine/Src/Ancona/HAL/Music.hpp
      Engine/Src/Ancona/HAL/OS.hpp
      Engine/Src/Ancona/HAL/PrimitiveRenderType.hpp
      Engine/Src/Ancona/HAL/RectangleShape.hpp
      Engine/Src/Ancona/HAL/RenderStates.hpp
      Engine/Src/Ancona/HAL/RenderTarget.hpp
      Engine/Src/Ancona/HAL/RenderTexture.hpp
      Engine/Src/Ancona/HAL/SDL.hpp
      Engine/Src/Ancona/HAL/Sensor.hpp
      Engine/Src/Ancona/HAL/Shape.hpp
      Engine/Src/Ancona/HAL/Sleep.hpp
      Engine/Src/Ancona/HAL/Sound.hpp
      Engine/Src/Ancona/HAL/SoundBuffer.hpp
      Engine/Src/Ancona/HAL/SoundSource.hpp
      Engine/Src/Ancona/HAL/Sprite.hpp
      Engine/Src/Ancona/HAL/Text.hpp
      Engine/Src/Ancona/HAL/Texture.hpp
      Engine/Src/Ancona/HAL/Time.hpp
      Engine/Src/Ancona/HAL/Touch.hpp
      Engine/Src/Ancona/HAL/Vertex.hpp
      Engine/Src/Ancona/HAL/VertexArray.hpp
      Engine/Src/Ancona/HAL/Window.hpp
      Engine/Src/Ancona/HAL/SDL/BlendModeImpl.hpp
      Engine/Src/Ancona/HAL/SDL/CircleShapeImpl.hpp
      Engine/Src/Ancona/HAL/SDL/ClockImpl.hpp
      Engine/Src/Ancona/HAL/SDL/DrawableImpl.hpp
      Engine/Src/Ancona/HAL/SDL/EventImpl.hpp
      Engine/Src/Ancona/HAL/SDL/FontImpl.hpp
      Engine/Src/Ancona/HAL/SDL/MusicImpl.hpp
      Engine/Src/Ancona/HAL/SDL/RectangleShapeImpl.hpp
      Engine/Src/Ancona/HAL/SDL/RenderStatesImpl.hpp
      Engine/Src/Ancona/HAL/SDL/RenderTargetImpl.hpp
      Engine/Src/Ancona/HAL/SDL/RenderTextureImpl.hpp
      Engine/Src/Ancona/HAL/SDL/ShapeImpl.hpp
      Engine/Src/Ancona/HAL/SDL/SoundBufferImpl.hpp
      Engine/Src/Ancona/HAL/SDL/SoundImpl.hpp
      Engine/Src/Ancona/HAL/SDL/SoundSourceImpl.hpp
      Engine/Src/Ancona/HAL/SDL/SpriteImpl.hpp
      Engine/Src/Ancona/HAL/SDL/TextImpl.hpp
      Engine/Src/Ancona/HAL/SDL/TextureImpl.hpp
      Engine/Src/Ancona/HAL/SDL/VertexArrayImpl.hpp
      Engine/Src/Ancona/HAL/SDL/WindowImpl.hpp
      Engine/Src/Ancona/Menu/Screens/MenuGameSystems.hpp
      Engine/Src/Ancona/Menu/Screens/MenuInputHandler.hpp
      Engine/Src/Ancona/Menu/Screens/MenuKeyboardAndMouse.hpp
      Engine/Src/Ancona/Menu/Screens/MenuScreen.hpp
      Engine/Src/Ancona/Menu/Screens/MenuTouch.hpp
      Engine/Src/Ancona/Menu/Systems/ButtonSystem.hpp
      Engine/Src/Ancona/Platformer/Actions/Action.hpp
      Engine/Src/Ancona/Platformer/Actions/Actions.hpp
      Engine/Src/Ancona/Platformer/Actions/ActionSystem.hpp
      Engine/Src/Ancona/Platformer/Actions/ScaleAction.hpp
      Engine/Src/Ancona/Platformer/Actions/ValueAction.hpp
      Engine/Src/Ancona/System/EventHandling.hpp
      Engine/Src/Ancona/System/FileOperations.hpp
      Engine/Src/Ancona/System/Log.hpp
      $<$<PLATFORM_ID:Android>:Engine/Src/Ancona/System/Android/AndroidFileOperations.hpp>
      $<$<PLATFORM_ID:iOS>:Engine/Src/Ancona/System/iOS/iOSFileOperations.hpp>
      Engine/Src/Ancona/Util/Algorithm.hpp
      Engine/Src/Ancona/Util/Assert.hpp
      Engine/Src/Ancona/Util/Data.hpp
      Engine/Src/Ancona/Util/Json.hpp
      Engine/Src/Ancona/Util/Math.hpp
      Engine/Src/Ancona/Util/StateMachine.hpp
      Engine/Src/Ancona/Util/StrUtil.hpp
      Engine/Src/Ancona/Util/Timer.hpp
      Engine/Src/Ancona/Util/Vector2.hpp
      Engine/Src/Ancona/Util/Vector2.inl
      Engine/Src/Ancona/Util/Vector3.hpp
      Engine/Src/Ancona/Util/Vector3.inl
      Engine/Src/Ancona/Util/Algorithm/ContainerExtensions.hpp
      Engine/Src/Ancona/Util/Algorithm/ContainerWrappers.hpp
      Engine/Src/Ancona/Util/Algorithm/Types.hpp
      Engine/Src/Ancona/Util/Data/DualMap.hpp
      Engine/Src/Ancona/Util/Data/Table.hpp
      Engine/Src/Ancona/Util/StateMachine/SharedMachine.hpp
      Engine/Src/Ancona/Util2D/VectorMath.hpp
      Engine/Src/Ancona/Util2D/Collision/Box2.hpp
      Engine/Src/Ancona/Util2D/Collision/Box3.hpp
      Engine/Src/Ancona/Util2D/Collision/Math.hpp
)

set_target_properties(
  Ancona
    PROPERTIES
      CXX_STANDARD 17
      PUBLIC_HEADER "${Ancona_PUBLIC_HEADERS}"
)

# compiler options
target_compile_options(
  Ancona
    PRIVATE
      $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wshadow
        -Wall
        -Wpadded
        -Wextra
        -Wpedantic>
)

# Configure config package file pased on .in file
configure_package_config_file(
  AnconaConfig.cmake.in
  ${CMAKE_BINARY_DIR}/cmake/Ancona/AnconaConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

write_basic_package_version_file(
  ${CMAKE_BINARY_DIR}/cmake/Ancona/AnconaConfigVersion.cmake
  VERSION ${Ancona_VERSION}
  COMPATIBILITY SameMajorVersion
)

# install library targets
install(
  TARGETS Ancona
  EXPORT AnconaTargets
  LIBRARY 
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Ancona
)

# install the AnconaConfig.cmake and AnconaConfigVersion.cmake
install(
  FILES
    ${CMAKE_BINARY_DIR}/cmake/Ancona/AnconaConfig.cmake
    ${CMAKE_BINARY_DIR}/cmake/Ancona/AnconaConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Ancona
  COMPONENT Ancona_DEVELOPMENT
)

# install the AnconaTargets.cmake file
install(
  EXPORT AnconaTargets
  FILE AnconaTargets.cmake
  NAMESPACE Ancona::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Ancona
  COMPONENT devel
)

