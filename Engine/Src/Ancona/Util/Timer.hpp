#ifndef Ancona_Util_Timer_H_
#define Ancona_Util_Timer_H_

namespace ild
{

class Timer
{
    public:
        static void Update(float delta);
        static void Restart();
        static float AsMilliseconds();

    private:
        static float _elapsedTime;
        static float _startTime;
};

}

#endif

