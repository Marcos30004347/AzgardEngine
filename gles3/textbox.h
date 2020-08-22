#include "font.h"
#include "glyph.h"
#include "shape.h"
#include "camera.h"
#include <vector>
#include <map>
#include <string>
#include <set>
#include "glm/glm.hpp"

#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ot.h>
#include <harfbuzz/hb-ft.h>
#include FT_FREETYPE_H

#include "text_tree.h"

struct special_glyph_maps {
    
};

class TextBox {
    private:

    Font* current_font;
    std::map<const char*, Font*> fonts;

    float _width;

    hb_buffer_t *hb_buffer;

    std::map<unsigned int, std::vector<std::vector<glm::vec2>>> char_to_positions;
    std::map<unsigned int, std::vector<std::vector<glm::vec2>>> char_to_scales;
    std::set<unsigned int> break_line_positions;

    std::vector<Shape*> shapes;
    unsigned int n_shapes;
    std::map<unsigned int, std::vector<std::vector<glm::vec2>>> shapes_to_positions;
    std::map<unsigned int, std::vector<std::vector<glm::vec2>>> shapes_to_scales;

    text_tree::node_t* tt_root;

    unsigned int caret_position;

    public:
    TextBox(float width);
    ~TextBox();

    void add_font(const char* name,Font* font);
    void set_font(const char* font_name);

    void add_text(std::string text);
    void remove_text(int lenght);

    void set_caret_position(unsigned int pos);

    void break_line();

    void shape();
    void draw(GLES3_Camera* camera, glm::mat4 model);
    void shape_equation(const char* equation);
    std::string to_string() { return text_tree::to_string(this->tt_root, 0, text_tree::lenght(tt_root) - 1); }
    inline unsigned int get_caret_position() { return this->caret_position; }
};
