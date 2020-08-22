#include "renderer.h"
#include<iostream>

GLES3_Renderer::GLES3_Renderer() {
    // glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte *version;
    version = glGetString(GL_VERSION);
    std::cout << "version: " << version << std::endl;
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    #if __EMSCRIPTEN__
    #else
    #endif
}

GLES3_Renderer::~GLES3_Renderer() {}

void GLES3_Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLES3_Renderer::set_clear_color(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
}