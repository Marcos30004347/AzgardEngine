#include <GL/glew.h>

class GLES3_Renderer {
    private:

    public:
    GLES3_Renderer();
    ~GLES3_Renderer();

    void set_clear_color(float r, float g, float b, float a);
    void clear();
};