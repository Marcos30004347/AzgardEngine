#include <GL/glew.h>
#include <GL/gl.h>

class GLES3_Texture {
    private:
    int _height;
    int _width;
    int _n_chanels;
    unsigned int _texture;

    public:
    GLES3_Texture(const char** filepaths, unsigned int n_textures, unsigned int width, unsigned int height);
    void use();
};
