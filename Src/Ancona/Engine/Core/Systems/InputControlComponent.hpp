#ifndef Ancona_Engine_Config_Systems_InputControlComponent_H_
#define Ancona_Engine_Config_Systems_InputControlComponent_H_

namespace ild
{

/**
 * @brief  A component used to control the player using a device 
 *         (keyboard, mouse, ...) should inherit from this class
 *
 * @author Jeff Swenson
 */
class InputControlComponent 
{
    public:
        void Update(float delta);
};

}

#endif
