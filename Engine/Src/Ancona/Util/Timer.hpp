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
    static void SetMilliseconds(float millis);

  private:
    static float _elapsedTime;
    static float _startTime;
};

} // namespace ild

#endif
