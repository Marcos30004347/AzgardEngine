#include"textbox.h"
#include"nodes/xml.h"
#include<iostream>


TextBox::TextBox(float width) {
  this->_width = width;
  hb_buffer = hb_buffer_create ();
  this->current_font = nullptr;
  this->char_to_positions = std::map<unsigned int, std::vector<std::vector<glm::vec2>>>();
  this->char_to_scales = std::map<unsigned int, std::vector<std::vector<glm::vec2>>>();
  this->shapes_to_positions = std::map<unsigned int, std::vector<std::vector<glm::vec2>>>();
  this->shapes_to_scales = std::map<unsigned int, std::vector<std::vector<glm::vec2>>>();
  this->caret_position = 0;
  this->tt_root = nullptr;
}

TextBox::~TextBox() {

}

void TextBox::add_font(const char* name, Font* font){
  this->fonts.insert({name, font});
}

void TextBox::set_font(const char* font_name) {
  this->current_font = this->fonts[font_name];
}


void TextBox::add_text(std::string text) {
  this->tt_root = text_tree::insert_characters_at(this->tt_root, text.c_str(), this->caret_position);
  this->caret_position += text.length();
}

void TextBox::remove_text(int lenght) {
  this->tt_root = text_tree::remove_characters_between(this->tt_root, this->caret_position  -  lenght, this->caret_position);
  this->caret_position -= lenght;
}


void TextBox::shape() {
  this->char_to_positions = std::map<unsigned int, std::vector<std::vector<glm::vec2>>>();
  hb_font_t *hb_font;
  
  FT_Set_Char_Size (this->current_font->get_face(), 1*64, 1*64, 0, 0);
  
  hb_font = hb_ft_font_create (this->current_font->get_face(), NULL);

  /* Create hb-buffer and populate. */
  // hb_buffer_t *hb_buffer;
  // hb_buffer = hb_buffer_create ();
  hb_buffer_reset(this->hb_buffer);

  hb_buffer_set_direction(this->hb_buffer, HB_DIRECTION_LTR);
  hb_buffer_set_script(this->hb_buffer, HB_SCRIPT_LATIN);
  hb_buffer_set_language(this->hb_buffer, hb_language_from_string("pt", 2));

  size_t lenght = text_tree::lenght(this->tt_root);
  hb_buffer_add_utf8 (this->hb_buffer, text_tree::to_string(this->tt_root, 0, lenght - 1).c_str(), lenght, 0,lenght);

  // hb_buffer_guess_segment_properties (this->hb_buffer);

  /* Shape it! */
  std::vector<hb_feature_t> features;
  // features.push_back(HBFeature::KerningOn);
  // features.push_back(HBFeature::LigatureOn);

  hb_shape (hb_font, this->hb_buffer, &features[0], features.size());

  /* Get glyph information and positions out of the buffer. */
  unsigned int len = hb_buffer_get_length (this->hb_buffer);
  hb_glyph_info_t *info = hb_buffer_get_glyph_infos (this->hb_buffer, NULL);
  hb_glyph_position_t *pos = hb_buffer_get_glyph_positions (this->hb_buffer, NULL);

  float current_x = 0;
  float current_y = 0;

  // First process
  for (unsigned int i = 0; i < len; i++){
    hb_codepoint_t gid   = info[i].codepoint;
    unsigned int cluster = info[i].cluster;

    if(break_line_positions.count(i) || current_x >= this->_width) {
      current_y -= 1.0f;
      current_x = 0.0f;
    }
  
    current_x += pos[i].x_offset / 64.;
    current_y += pos[i].y_offset / 64.;
    char glyphname[32];
    hb_font_get_glyph_name (hb_font, gid, glyphname, sizeof (glyphname));

    auto it = this->char_to_positions.count(gid);

    if(!it) {
      this->char_to_positions[gid] = std::vector<std::vector<glm::vec2>>();
      this->char_to_scales[gid] = std::vector<std::vector<glm::vec2>>();
      this->char_to_positions[gid].push_back(std::vector<glm::vec2>());
      this->char_to_scales[gid].push_back(std::vector<glm::vec2>());
    }

    if(this->char_to_positions[gid][this->char_to_positions[gid].size() - 1].size() >= 512) {
      this->char_to_positions[gid].push_back(std::vector<glm::vec2>());
      this->char_to_scales[gid].push_back(std::vector<glm::vec2>());
    }
  
    this->char_to_positions[gid][this->char_to_positions[gid].size() - 1].push_back(glm::vec2(current_x,current_y));
    this->char_to_scales[gid][this->char_to_scales[gid].size() - 1].push_back(glm::vec2(1.f));
  
    current_x += pos[i].x_advance / 64.;
    current_y += pos[i].y_advance / 64.;
  }

}

struct glyph_metrics {
  float advance_x;
  float bearing_y;
  float bearing_x;
  float heigth;
  float width;
};

glyph_metrics get_glyph_metrics(FT_Face face, unsigned int glyph_id) {
    FT_Load_Glyph(face, glyph_id, 0);
    return {
      face->glyph->metrics.horiAdvance/64.f,
      face->glyph->metrics.horiBearingY/64.f,
      face->glyph->metrics.horiBearingX/64.f,
      face->glyph->metrics.height/64.f,
      face->glyph->metrics.width/64.f,
    };
}




void TextBox::shape_equation(const char* equation) {
    FT_Set_Char_Size (this->current_font->get_face(), 1*64, 1*64, 0, 0);

    hb_font_t* harf_font = hb_ft_font_create (this->current_font->get_face(), NULL);
    hb_face_t* harf_face = hb_ft_face_create(this->current_font->get_face(), nullptr);

    if(!hb_ot_math_has_data(harf_face)) {
        printf("font does no support math!\n");
        return;
    }
    printf("font support math\n");
  
    math_shape_desc_t* desc = open_xml(this->current_font);
    this->char_to_positions = std::map<unsigned int, std::vector<std::vector<glm::vec2>>>();
    this->char_to_scales = std::map<unsigned int, std::vector<std::vector<glm::vec2>>>();

    math_shape_params_t* p = desc->first_param;

    while(p) {
      if(!this->char_to_positions.count(p->codepoint) && p->codepoint != NULL_GLYPH) {
        this->char_to_positions[p->codepoint] = std::vector<std::vector<glm::vec2>>();
        this->char_to_scales[p->codepoint] = std::vector<std::vector<glm::vec2>>();
        this->char_to_positions[p->codepoint].push_back(std::vector<glm::vec2>());
        this->char_to_scales[p->codepoint].push_back(std::vector<glm::vec2>());
      }
      p = p->next;
    }


    p = desc->first_param;

    while(p) {
      if(p->codepoint != NULL_GLYPH) {
        this->char_to_positions[p->codepoint][0].push_back(glm::vec2(p->x, p->y));
        this->char_to_scales[p->codepoint][0].push_back(glm::vec2(p->stretch_x, p->stretch_y));
        for(int j=0; j<p->n_custom_shapes; j++) {
          shapes.push_back(&p->custom_shapes[j]);
          this->shapes_to_positions[shapes.size() - 1] = std::vector<std::vector<glm::vec2>>();
          this->shapes_to_scales[shapes.size() - 1] = std::vector<std::vector<glm::vec2>>();
          this->shapes_to_positions[shapes.size() - 1].push_back(std::vector<glm::vec2>());
          this->shapes_to_scales[shapes.size() - 1].push_back(std::vector<glm::vec2>());
          this->shapes_to_positions[shapes.size() - 1][0].push_back(glm::vec2(p->x, p->y));
          this->shapes_to_scales[shapes.size() - 1][0].push_back(glm::vec2(p->stretch_x, p->stretch_y));
        }
      }
      p = p->next;

    }


    free(desc);
  
}

void TextBox::draw(GLES3_Camera* camera, glm::mat4 model) {
  // printf("KKKKKKKKKKKKK %lu\n", this->current_font->get_glyphs()[1]->get_glyph_id());
  // printf("KKKKKKKKKKKKK %lu\n", this->current_font->get_glyphs()[2]->get_glyph_id());
  // printf("KKKKKKKKKKKKK %lu\n", this->current_font->get_glyphs()[3]->get_glyph_id());
  // printf("KKKKKKKKKKKKK %lu\n", this->current_font->get_glyphs()[4]->get_glyph_id());
  // for(auto i = this->current_font->get_glyphs().begin();  i != this->current_font->get_glyphs().end(); i++) {
  //   // i->second->draw(camera, model, {{ pos }}, {{1.f}});
  //   pos = pos + glm::vec2(1.0f, 0.0f);

  // }
  // this->current_font->get_glyphs()[752]->draw(camera, model, {{ pos }}, {{1.f}});
  for(auto i= this->char_to_positions.begin(); i != this->char_to_positions.end(); i++) {
    this->current_font->get_glyph(i->first)->draw(camera, model, i->second, this->char_to_scales[i->first]);
  }

  for(auto i= this->shapes_to_positions.begin(); i != this->shapes_to_positions.end(); i++) {
    this->shapes[i->first]->draw(camera, model, i->second, this->shapes_to_scales[i->first]);
  }
}

void TextBox::break_line() {
  this->break_line_positions.insert(this->caret_position);
}

void TextBox::set_caret_position(unsigned int pos) {
  size_t lenght = text_tree::lenght(this->tt_root);

  if(pos > lenght) {
    this->caret_position = lenght;
    return;
  }

  this->caret_position = pos;
}