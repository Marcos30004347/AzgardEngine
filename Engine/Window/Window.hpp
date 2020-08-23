#ifndef WINDOW_H
#define WINDOW_H

enum WindowContext{
    NullContext = 0,
    OpenGLES3Context,
};

class Window {
    public:

    virtual void Swap() = 0;
    virtual void SetContext(WindowContext context) = 0;
    virtual void SetVsync(bool vsync) = 0;

};

#endif