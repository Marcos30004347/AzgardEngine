#include <rapidjson/rapidjson.h>
#include <string>

struct Matrix {
    float values[4][4];
};

struct Translation {
    float x,y,z;
};

struct Rotation {
    float x,y,z;
};

struct Scale {
    float x,y,z;
};

struct Mesh {

};

struct Node {
    Mesh* meshes;
    size_t n_meshes;

    Matrix matrix;

    Translation translation;
    Rotation rotation;
    Scale scale;
};

struct Scene {
    Node* node;
    Scene* children;
};



class GLTF2Parser {
    public:
    GLTF2Parser();
    ~GLTF2Parser();
    Scene Load(std::string src);
};

int PeadJSON();