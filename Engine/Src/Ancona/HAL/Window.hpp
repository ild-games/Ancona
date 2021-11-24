#ifndef Ancona_HAL_Window_H_
#define Ancona_HAL_Window_H_

namespace ild
{

namespace WindowStyle
{
    enum
    {
        None       = 0,
        Titlebar   = 1 << 0,
        Resize     = 1 << 1,
        Close      = 1 << 2,
        Fullscreen = 1 << 3,

        Default = Titlebar | Resize | Close
    };
}

class Window
{
    public:
        Window(
            const std::string& title,
            int width,
            int height,
            unsigned int style = WindowStyle::Default);

        ~Window();

        void sayHello();

    private:
        class WindowImpl;

        std::unique_ptr<WindowImpl> _pimpl;
};

}

#endif
