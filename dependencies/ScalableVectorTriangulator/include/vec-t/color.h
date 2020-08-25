
#include"shape.h"

std::array<float, 4> parse_nsvg_color(unsigned int nsvg_color) {
    
    unsigned int r = (nsvg_color & 0x00FF);
    unsigned int g = (nsvg_color >> 8) & 0x00FF;
    unsigned int b = (nsvg_color >> 16) & 0x00FF;
    unsigned int a = (nsvg_color >> 24) & 0xFFFF;
    return { r/255.f, g/255.f, b/255.f, a/255.f};
}

std::array<float, 4> calculate_color(
    float x, float y,
	shape _shape
){
	if (_shape.fill_type == COLOR) {
        return _shape.color;
	} else if (_shape.fill_type == GRADIENT_LINEAR) {
        printf("form: %f %f %f %f %f %f\n", _shape.form[0], _shape.form[1], _shape.form[2], _shape.form[3], _shape.form[4], _shape.form[5]);
        for(gradient_stop s: _shape.stops) printf("stop: offset=%f color=(%f, %f, %f, %f)\n", s.offset, s.color[0], s.color[1], s.color[2], s.color[3]);
        printf("spread=%i\n",_shape.spread);
    
		return _shape.color;
	} else if (_shape.fill_type == GRADIENT_RADIAL) {
        printf("form: %f %f %f %f %f %f\n", _shape.form[0], _shape.form[1], _shape.form[2], _shape.form[3], _shape.form[4], _shape.form[5]);
        printf("fx=%f fy=%f\n", _shape.fx, _shape.fy);
        for(gradient_stop s: _shape.stops) printf("stop: offset=%f color=(%f, %f, %f, %f)\n", s.offset, s.color[0], s.color[1], s.color[2], s.color[3]);
        printf("spread=%i\n",_shape.spread);
    
		return _shape.color;
	}
    return _shape.color;

}