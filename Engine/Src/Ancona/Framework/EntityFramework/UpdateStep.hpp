#ifndef Ancona_Engine_EntityFramework_UpdateStep_H_
#define Ancona_Engine_EntityFramework_UpdateStep_H_

namespace ild
{

namespace UpdateStep
{
    //The namespace is used to prevent the enum values from leaking into
    //the ild namespace.  In order to use a enum value you type
    //UpdateStep::Update or UpdateStep::Draw.  Without the namespace you
    //could have typed UpdateStep


    /**
     * @brief Defines when a system should be updated
     * @author Jeff Swenson
     */
    enum UpdateStep
    {
        Input,
        Update,
        Physics,
        Draw,
        LAST_FOR_ITERATION
    };
}

/**
 * @brief Defines when a system should be updated.
 * @author Jeff Swenson
 */
typedef UpdateStep::UpdateStep UpdateStepEnum;

}

#endif
