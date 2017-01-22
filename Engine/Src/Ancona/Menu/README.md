# Ancona Menu Library
The Menu Library makes it easy to add simple menu screens and buttons to Ancona. The two classes meant to be re-used are the MenuScreen and ButtonSystem.

## MenuScreen
The MenuScreen should be created by your Game if you have a screen that is just used as a menu.

## ButtonSystem
In most cases you should let the MenuScreen handle the ButtonSystem. The ButtonSystem is standalone and can be used to add buttons to your custom game screens. In order to use the ButtonSystem you need to proxy input to it using the ButtonSystem::Pointer method. You should pull for button clicks using
the ButtonSystem::WasEntityPressed() and ButtonSystem::GetPressedKey() methods.
