#include "svg.h"
#include "vec-t/svg.h"

SVG::SVG(const char* path) {
    std::vector<shape_triangulation_data> vertices_datas = parse_svg(path);
    for(shape_triangulation_data td : vertices_datas) {
        shapes.push_back(new Shape(&td));
    }

}

void SVG::draw(GLES3_Camera *camera, glm::mat4 model, std::vector<std::vector<glm::vec2>> positions_packs, std::vector<std::vector<glm::vec2>> scales_packs) {
    for(Shape* shape: this->shapes) {
        shape->draw(camera, model, positions_packs, scales_packs);
    }
}