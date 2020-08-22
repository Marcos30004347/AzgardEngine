#ifndef CANVAS_H
#define CANVAS_H

enum CanvasContext{
    NullContext = 0,
    OpenGLES3Context,
};

class Window {
    public:

    virtual void Swap() = 0;
    virtual void SetContext(CanvasContext context) = 0;
    virtual void SetVsync(bool vsync) = 0;

};

#endif