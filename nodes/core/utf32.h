#ifndef NODES_CORE_UTF32_H
#define NODES_CORE_UTF32_H

#include "desc.h"

math_shape_desc_t* parse_utf32(uint32_t * text, unsigned int lenght, Font* font, const char* features = nullptr) {

    FT_Set_Char_Size (font->get_face(), 1*64, 1*64, 0, 0);
    
    hb_font_t* hb_font = hb_ft_font_create (font->get_face(), NULL);

    /* Create hb-buffer and populate. */
    hb_buffer_t *hb_buffer;
    hb_buffer = hb_buffer_create ();
    hb_buffer_reset(hb_buffer);

    hb_buffer_set_direction(hb_buffer, HB_DIRECTION_LTR);
    hb_buffer_set_script(hb_buffer, HB_SCRIPT_LATIN);
    hb_buffer_set_language(hb_buffer, hb_language_from_string("en", -1));    hb_buffer_set_content_type(hb_buffer, HB_BUFFER_CONTENT_TYPE_UNICODE);
    hb_buffer_add_utf32 (hb_buffer, text, lenght, 0, lenght);
    // hb_buffer_add_utf32(hb_buffer, text.c_str(), text.size(), 0,text.size());
    // hb_buffer_guess_segment_properties (this->hb_buffer);

    /* Shape it! */
    std::vector<hb_feature_t> feats = std::vector<hb_feature_t>();

    if(features) {
        feats = parse_features(std::string(features));
    }

    const char *shaperprefs[3] = { "ot", "default", "aat" };


    hb_shape_full (hb_font, hb_buffer, &feats[0], feats.size(), shaperprefs);

    /* Get glyph information and positions out of the buffer. */
    unsigned int len = hb_buffer_get_length (hb_buffer);
    hb_glyph_info_t *info = hb_buffer_get_glyph_infos (hb_buffer, NULL);
    hb_glyph_position_t *pos = hb_buffer_get_glyph_positions (hb_buffer, NULL);

    float current_x = 0;
    float current_y = 0;

    
    float height = 0;
    float width = 0;
    float p0_x = FLT_MAX, p0_y = FLT_MAX, p1_x = FLT_MIN, p1_y = FLT_MIN;

    float advance_x;
    hb_face_t* harf_face = hb_ft_face_create(font->get_face(), nullptr);

    unsigned lookup_count = hb_ot_layout_table_get_lookup_count (harf_face, HB_OT_TAG_GSUB);
    unsigned int variants_count = 30;
    hb_codepoint_t variants[30];        

    math_shape_desc_t* desc = init_shape_desc();

    for (unsigned int i = 0; i < len; i++){
        math_shape_params_t* param = init_shape_param();
    
        unsigned int cluster = info[i].cluster;

        Glyph* g = font->get_glyph(info[i].codepoint);

        current_x += pos[i].x_offset / 64.f;
        current_y += pos[i].y_offset / 64.f;

        param->codepoint = info[i].codepoint;
        param->x = current_x;
        param->y = current_y;
        param->p0_x = current_x + g->get_bounding_box().p0.x;
        param->p0_y = current_y + g->get_bounding_box().p0.y;
        param->p1_x = current_x + g->get_bounding_box().p1.x;
        param->p1_y = current_y + g->get_bounding_box().p1.y;
        param->n_custom_shapes = 0;
        param->custom_shapes = nullptr;
    
        if(g->get_bounding_box().p1.x == 0.f) {
            param->p1_x += pos[i].x_advance / 64.f;
        }
    
        param->stretch_x = 1.f;
        param->stretch_y = 1.f;

        param->advance_x = pos[i].x_advance / 64.f;
        param->advance_y = pos[i].y_advance / 64.f;


        p0_x = std::min(p0_x, param->p0_x);
        p0_y = std::min(p0_y, param->p0_y);

        p1_x = std::max(p1_x, param->p1_x);
        p1_y = std::max(p1_y, param->p1_y);

        current_x += pos[i].x_advance / 64.f;
        current_y += pos[i].y_advance / 64.f;
        advance_x = pos[i].x_advance / 64.f;
        width = current_x;
        height = std::max(g->get_height(), height);

        add_param_to_desc(desc, param);
    }

    desc->x = 0.f;
    desc->y = 0.f;
    desc->operations = 1;
    desc->p0_x = p0_x;
    desc->p0_y = p0_y;
    desc->p1_x = p1_x;
    desc->p1_y = p1_y;
    desc->width = desc->p1_x - desc->p0_x;
    desc->height = desc->p1_y - desc->p0_y;
    desc->n_params = len;

    desc->advance_x = 0.1f;
    desc->advance_y = 0.0f;

    return desc;
}


#endif