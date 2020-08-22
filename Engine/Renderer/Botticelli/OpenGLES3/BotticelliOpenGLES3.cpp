#include <iostream>
#include "definitions.hpp"
#include "BotticelliOpenGLES3.hpp"

#ifdef OPENGLES3_API

BotticelliOpenGLES3::BotticelliOpenGLES3() {}
BotticelliOpenGLES3::~BotticelliOpenGLES3() {}

void BotticelliOpenGLES3::FrameBegin() {
    std::cout << "frame beggin" << std::endl;
}
void BotticelliOpenGLES3::FrameEnd() {
    std::cout << "frame end" << std::endl;
}
void BotticelliOpenGLES3::RenderCmd() {
    std::cout << "render cmd" << std::endl;
}

void BotticelliOpenGLES3::StartUp() {

}

void BotticelliOpenGLES3::ShutDown() {

}

void BotticelliOpenGLES3::EnableFeature(RendererFeature feat, void* feat_params) {

}

std::vector<RendererFeature> BotticelliOpenGLES3::GetFeatures() {
    return std::vector<RendererFeature>();
}

#endif