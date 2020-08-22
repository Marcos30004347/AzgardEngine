#ifndef NODES_CORE_DESC_H
#define NODES_CORE_DESC_H

#include "../../gles3/font.h"
#include "../../gles3/shape.h"
#include"rapidxml/rapidxml.hpp"
#include <string>

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ot.h>
#include <harfbuzz/hb-ft.h>
#include FT_FREETYPE_H


#define NULL_GLYPH UINT64_MAX


struct math_shape_params_t {
    uint32_t codepoint = 0;
    float stretch_x = 1.0f;
    float stretch_y = 1.0f;

    float advance_x = 0.0f;
    float advance_y = 0.0f;

    float p0_x = FLT_MAX;
    float p0_y = FLT_MAX;
    float p1_x = FLT_MIN;
    float p1_y = FLT_MIN;

    float x = 0.0f;
    float y = 0.0f;

    Shape* custom_shapes = nullptr;
    unsigned int n_custom_shapes = 0;

    math_shape_params_t* next;
};


struct math_shape_desc_t {
    math_shape_params_t* first_param = nullptr;
    math_shape_params_t* last_param = nullptr;
    size_t n_params = 0;

    unsigned int operations = 0;
    float p0_x = 0.0f;
    float p0_y = 0.0f;
    float p1_x = 0.0f;
    float p1_y = 0.0f;
    float advance_x = 0.0f;
    float advance_y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    float x = 0.0f;
    float y = 0.0f;
};


math_shape_desc_t* init_shape_desc() {
    math_shape_desc_t* desc = (math_shape_desc_t*)malloc(sizeof(math_shape_desc_t));
    
    desc->first_param = nullptr;
    desc->last_param = nullptr;
    desc->n_params = 0;
    desc->operations = 0;
    desc->p0_x = 0.0f;
    desc->p0_y = 0.0f;
    desc->p1_x = 0.0f;
    desc->p1_y = 0.0f;
    desc->advance_x = 0.0f;
    desc->advance_y = 0.0f;
    desc->width = 0.0f;
    desc->height = 0.0f;
    desc->x = 0.0f;
    desc->y = 0.0f;
    desc->first_param = nullptr;
    desc->last_param = nullptr;
    return desc;
}



math_shape_params_t* init_shape_param() {
    math_shape_params_t* param = (math_shape_params_t*)malloc(sizeof(math_shape_params_t));
    
    param->p0_x = 0.0f;
    param->p0_y = 0.0f;
    param->p1_x = 0.0f;
    param->p1_y = 0.0f;
    param->advance_x = 0.0f;
    param->advance_y = 0.0f;
    param->x = 0.0f;
    param->y = 0.0f;
    param->stretch_x = 1.f;
    param->stretch_y = 1.f;
    param->n_custom_shapes = 0;
    param->custom_shapes = nullptr;
    param->codepoint = 0;
    param->next = nullptr;
    return param;
}

void translate_math_shape_params(math_shape_desc_t* &params, float x, float y) {
    if(!params) return;
    float max_x = FLT_MIN;
    float max_y = FLT_MIN;
    float min_x = FLT_MAX;
    float min_y = FLT_MAX;

    math_shape_params_t* p = params->first_param;
    while (p)
    {
        /* code */
        p->x += x;
        p->y += y;

        p->p0_x += x;
        p->p0_y += y;

        p->p1_x += x;
        p->p1_y += y;

        min_y = std::min(min_y, p->p0_y);
        max_y = std::max(max_y, p->p1_y);

        min_x = std::min(min_x, p->p0_x);
        max_x = std::max(max_x, p->p1_x);
        p = p->next;
    }
    
    // for(int i=0; i<params->n_params; i++) {
    // }

    params->x += x;
    params->y += y;

    params->p1_x = max_x;
    params->p0_x = min_x;

    params->p1_y = max_y;
    params->p0_y = min_y;

    params->width = (params->p1_x - params->p0_x);
    params->height = params->p1_y - params->p0_y;
}

void stretch_math_shape_params(math_shape_desc_t* params, float x, float y) {
    if(!params) return;

    float previous_p1_x = 0;
    float previous_p1_y = 0;

    float max_y = FLT_MIN;
    float min_y = FLT_MAX;
    float max_x = FLT_MIN;
    float min_x = FLT_MAX;
    
    float center_x = (params->p0_x + params->p1_x)/2.f;
    float center_y = (params->p0_y + params->p1_y)/2.f;


    math_shape_params_t* p = params->first_param;
    while (p)
    {

        float p_center_x = (p->p1_x + p->p0_x)/2.f;
        float p_center_y = (p->p1_y + p->p0_y)/2.f;

        float anchor_x = p->x;
        float anchor_y = p->y;
    

        previous_p1_x = p->p1_x;
        previous_p1_y = p->p1_y;
    
        float diff_y = (center_y - p->y) * (1-y);
        
        p->stretch_x *= x;
        p->stretch_y *= y;

        p->p0_x -= anchor_x;
        p->p0_x *= x;
        p->p0_x += anchor_x;

        p->p0_y -= anchor_y;
        p->p0_y *= y;
        p->p0_y += anchor_y + diff_y;

        p->p1_x -= anchor_x;
        p->p1_x *= x;
        p->p1_x += anchor_x;

        p->p1_y -= anchor_y;
        p->p1_y *= y;
        p->p1_y += anchor_y + diff_y;
        p->y += diff_y;

        params->advance_y *= y;
        params->advance_x *= x;

        float diff_x = p_center_x - (p->p1_x + p->p0_x)/2.f;
        p->x     += diff_x;
        p->p1_x  += diff_x;
        p->p0_x  += diff_x;
        p = p->next;
    }


    p = params->first_param;

    while (p)
    {
        float diff_x = ((params->p1_x + params->p0_x)/2.f - (p->p1_x + p->p0_x)/2.f)*(1 - x);
        // float diff_y = ((params->p0_y)/2.f - (p->p1_y + p->p0_y)/2.f)*(1 - y);

        p->x     += diff_x;
        p->p1_x  += diff_x;
        p->p0_x  += diff_x;
        
        // p->y     += diff_y;
        // p->p1_y  += diff_y;
        // p->p0_y  += diff_y;
        min_y = std::min(min_y, p->p0_y);
        max_y = std::max(max_y, p->p1_y);

        min_x = std::min(min_x, p->p0_x);
        max_x = std::max(max_x, p->p1_x);
        p = p->next;
    }


    params->width = max_x - min_x;
    params->height = max_y - min_y;

    params->p1_x = max_x;
    params->p0_x = min_x;

    params->p1_y = max_y;
    params->p0_y = min_y;

    params->advance_x *= x;
    params->advance_y *= y;
    printf("aqui\n");

}

void add_param_to_desc(math_shape_desc_t* &a, math_shape_params_t* &b) {
    if(!a) return;

    if(a->last_param) {
        a->last_param->next = b;
        a->last_param = b;
    } else {
        a->first_param = b;
        a->last_param = b;
    }

    a->p0_x = std::min(a ? a->p0_x : FLT_MAX, b ? b->p0_x : FLT_MAX);
    a->p0_y = std::min(a ? a->p0_y : FLT_MAX, b ? b->p0_y : FLT_MAX);
    a->p1_x = std::max(a ? a->p1_x : FLT_MIN, b ? b->p1_x : FLT_MIN);
    a->p1_y = std::max(a ? a->p1_y : FLT_MIN, b ? b->p1_y : FLT_MIN);

    a->n_params = a->n_params + 1;

    a->advance_x = b->advance_x;
    a->advance_y = b->advance_y;

    a->x = a->x;
    a->y = a->y;

    a->height = a->p1_y - a->p0_y;
    a->width = a->p1_x - a->p0_x;

}


math_shape_desc_t* concat_math_shape_descs(math_shape_desc_t* &a, math_shape_desc_t*&b, float x = 0, float y = 0) {
    // math_shape_desc_t* result = (math_shape_desc_t*)malloc(sizeof(math_shape_desc_t));
    if(!b) return a;
    if(!a) {
        return b;
    }

    // math_shape_params_t* params = (math_shape_params_t*)malloc(sizeof(math_shape_params_t)* ((a? a->n_params : 0) + (b ? b->n_params : 0)));
    translate_math_shape_params(b, x, y);

    if(a->last_param){
        a->last_param->next = b->first_param;
        a->last_param = b->last_param;
    }
    else {
        a->first_param = b->first_param;
        a->last_param = b->last_param;
    }

    // for(int i=0; i < (a ? a->n_params : 0); i++) {
    //     params[i] = a->params[i];
    // }

    // for(int i=0; i < (b ? b->n_params : 0); i++) {
    //     params[i+a->n_params] = b->params[i];
    // }

    a->p0_x = std::min(a ? a->p0_x : FLT_MAX, b ? b->p0_x : FLT_MAX);
    a->p0_y = std::min(a ? a->p0_y : FLT_MAX, b ? b->p0_y : FLT_MAX);
    a->p1_x = std::max(a ? a->p1_x : FLT_MIN, b ? b->p1_x : FLT_MIN);
    a->p1_y = std::max(a ? a->p1_y : FLT_MIN, b ? b->p1_y : FLT_MIN);

    a->n_params = (a? a->n_params : 0) + (b? b->n_params : 0);
    a->advance_x = b->advance_x;
    a->advance_y = 0.0f;

    a->height = a->p1_y - a->p0_y;
    a->width = a->p1_x - a->p0_x;

    a->operations = a->operations + b->operations;

    return a;
}

math_shape_desc_t* get_math_shape_desc_stretchy(hb_codepoint_t glyph_index, hb_direction_t direction, float desired_size, Font* font, float extra_width = 0.0f) {

    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    Glyph* g = font->get_glyph(glyph_index);
    unsigned int variants = 30;
    hb_ot_math_glyph_variant_t variant[30];

    hb_ot_math_get_glyph_variants (
        harf_font,
        glyph_index,
        direction,
        0,
        &variants,
        variant
    );

    unsigned int parts = 30;
    hb_ot_math_glyph_part_t part[30];

    hb_codepoint_t best = glyph_index;


    for(int i=0; i<variants; i++) {

        if((std::abs(font->get_glyph(variant[i].glyph)->get_height() - desired_size) <= std::abs(font->get_glyph(best)->get_height() - desired_size))) {
            best = variant[i].glyph;
        }

    }


    math_shape_desc_t* desc = init_shape_desc();
    math_shape_params_t* param = init_shape_param();

    Glyph* gs = font->get_glyph(best);

    param->advance_x = 0.1f;
    param->advance_y = 0.1f;
    param->x = 0.0f;
    param->y = 0.0f;
    param->codepoint = best;
    param->stretch_x = 1.0f;
    param->stretch_y = 1.0f;
    param->p0_x = gs->get_bounding_box().p0.x;
    param->p0_y = gs->get_bounding_box().p0.y;
    param->p1_x = gs->get_bounding_box().p1.x;
    param->p1_y = gs->get_bounding_box().p1.y;
    param->n_custom_shapes = 0;
    param->custom_shapes = nullptr;

    add_param_to_desc(desc, param);

    desc->n_params = 1;
    desc->p0_x = param->p0_x;
    desc->p0_y = param->p0_y;
    desc->p1_x = param->p1_x;
    desc->p1_y = param->p1_y; 
    desc->advance_x = 0.0f;
    desc->advance_y = 0.0f;
    desc->height = desc->p1_y - desc->p0_y;
    desc->width = desc->p1_x - desc->p0_x;
    desc->x = param->x;
    desc->y = param->y;
    desc->operations = 0;
    
    stretch_math_shape_params(
        desc,
        HB_DIRECTION_IS_HORIZONTAL(direction) ?  extra_width + desired_size/gs->get_width() : 1.0f,
        HB_DIRECTION_IS_HORIZONTAL(direction) ?  1.0f : extra_width + desired_size/gs->get_height()
    );

    return desc;
}


void surround_shape_desc_horizontal(unsigned int left_codepoint, unsigned int right_codepoint, math_shape_desc_t* &desc, Font* font, float extra_width = 0.4f) {
    math_shape_desc_t* ldesc = get_math_shape_desc_stretchy(left_codepoint, HB_DIRECTION_TTB, (desc->p1_y - desc->p0_y), font, extra_width);
    math_shape_desc_t* rdesc = get_math_shape_desc_stretchy(right_codepoint, HB_DIRECTION_TTB, (desc->p1_y - desc->p0_y), font, extra_width);

    concat_math_shape_descs(
        ldesc,
        desc,
        ldesc->p1_x - desc->p0_x,
        ldesc->y
        // (ldesc->p1_y + ldesc->p0_y)/2.f - (desc->p1_y + desc->p0_y)/2.f + extra_width/2.f
    );
    concat_math_shape_descs(
        ldesc,
        rdesc,
        ldesc->p1_x - rdesc->p0_x,
        ldesc->y
        // (ldesc->p1_y + ldesc->p0_y)/2.f - (rdesc->p1_y + rdesc->p0_y)/2.f
    );
    desc = ldesc;
    // return ldesc;
}



void script_shape_desc(
    math_shape_desc_t* &desc,
    math_shape_desc_t* superscript,
    math_shape_desc_t* subscript,
    Font* font,
    float scale = 0.5f,
    float delta_y_super_script = 0.0f,
    float delta_y_subs_script = 0.0f,
    float delta_x_super_script = 0.0f,
    float delta_x_subs_script = 0.0f
) {

    // math_shape_desc_t* result = desc;

    math_shape_params_t* param = desc->first_param;
    float p1y = param->p1_y;
    float p0y = param->p0_y;
    float p1x = param->p1_x;
    hb_codepoint_t codepoint = param->codepoint;

    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);
    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);
    float italic_correction = hb_ot_math_get_glyph_italics_correction (harf_font, codepoint)/64.f;

    if(superscript) {
        stretch_math_shape_params(superscript, scale, scale);

        float base_line_y = p1y + delta_y_super_script;
        float y = base_line_y - superscript->p1_y;
        float x = p1x - superscript->p0_x  + delta_x_super_script;

        concat_math_shape_descs(desc, superscript, x, y);
    }
    if(subscript) {
        stretch_math_shape_params(subscript, scale, scale);

        float base_line_y = p0y + delta_y_subs_script;
        float y = base_line_y - subscript->p0_y;
        float x = p1x - subscript->p0_x - italic_correction + delta_x_subs_script;
        concat_math_shape_descs(desc, subscript, x, y);
    }

}


struct word_desc {
    int lenght;
    int begin_text_pos;
    int end_text_pos;

    float p0_x;
    float p1_x;
};


word_desc* get_words_descs(math_shape_desc_t* d, hb_codepoint_t space_codepoint, int *n) {
    math_shape_params_t* p = d->first_param;

    int n_words = 0;//get_n_words(d, space_codepoint);
    while(p) {

        if(p->codepoint != space_codepoint) {
            while (p && p->codepoint != space_codepoint)
            {
                p = p->next;
            }
            n_words++;
        }

        if(p) p = p->next;
    }


    word_desc* descs = (word_desc*)malloc(sizeof(word_desc)*n_words);

    p = d->first_param;

    int word = 0;
    int l = 0;
    int pos = 0;

    float p1_x = 0.0f;

    while(p) {

        if(p->codepoint != space_codepoint) {
            descs[word].p0_x = p->p0_x; 
            while (p && p->codepoint != space_codepoint)
            {
                l++;
                p1_x = p->p1_x;
                if(p) {
                    pos++;
    
                    p = p->next;
                }
            }
            descs[word].p1_x = p1_x; 

            descs[word].lenght = l;
            descs[word].end_text_pos = pos;
            descs[word].begin_text_pos = descs[word].end_text_pos - l;
            printf("%i %i %i\n", l ,pos, pos - l);
            word++;
            l = 0;
        }
    
        if(p) {
            pos++;
            p = p->next;
        }
    }

    *n = n_words;

    return descs;
}



int* text_wrap(word_desc* words, float width, Font* font, int n) {
    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);
    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    hb_codepoint_t space_codepoint;
    std::string s("0020");
    int num = std::stoi(s, 0, 16);
    hb_font_get_nominal_glyph(harf_font, num, &space_codepoint);
    hb_position_t x, y;
    hb_font_get_glyph_advance_for_direction(harf_font, space_codepoint, HB_DIRECTION_LTR, &x, &y);
    float space_width = x/64.f;

    int i, j; 

    float currlen; 


    float cost; 


    float* dp = (float*)malloc(sizeof(float)*n); 


    int* ans = (int*)malloc(sizeof(int)*n); 


    dp[n - 1] = 0.f; 
    ans[n - 1] = n - 1; 

    for (i = n - 2; i >= 0; i--) { 
        currlen = 0.f; 
        dp[i] = FLT_MAX; 
  

        for (j = i; j < n; j++) { 
            currlen += ((words[j].p1_x - words[j].p0_x)+ space_width);
 
            if(currlen > width) break;

            if(j==n - 1) cost = 0;
            else {
                cost = currlen > width ? FLT_MAX : (width - currlen) * (width - currlen) + dp[j + 1];
            }      
            if (cost < dp[i]) { 
                dp[i] = cost; 
                ans[i] = j; 
            } 
        }   
    }


    // i = 0;

    // while (i < n) { 
    //     std:: cout << "t: " <<i << " " << ans[i] << "\n";
    //     i = ans[i] + 1; 
    // } 


    /*
    Teste testando aqui é um teste demais palavra teste teste teste palavra teste.
    */


    
    return ans;
}



void left_justify(math_shape_desc_t* desc, Font* font, float line_lenght, float line_height = 1.0f) {

    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    hb_codepoint_t space_codepoint;
    std::string s("0020");
    int num = std::stoi(s, 0, 16);
    hb_font_get_nominal_glyph(harf_font, num, &space_codepoint);


    int n = 0;
    word_desc* words = get_words_descs(desc, space_codepoint, &n);

    int* ans = text_wrap(words, line_lenght, font, n);

    int i = 0;


    float y_c = 0.0f;
    float x_c = 0.0f;
    math_shape_params_t* p = desc->first_param;

    while (i < n) { 
    

        for(int w=words[i].begin_text_pos; w < words[ans[i]].end_text_pos; w++) {
            p->x -= x_c;
            p->y -= y_c;
            p = p->next;
        }

        if(p) {
            p = p->next; // space
            if(p) {
                x_c = p->x;
                y_c += line_height;
            }
        }

        i = ans[i] + 1; 
    } 

    hb_font_destroy(harf_font);
}


void right_justify(math_shape_desc_t* desc, Font* font, float line_lenght, float line_height = 1.0f) {
    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);

    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    hb_codepoint_t space_codepoint;
    std::string s("0020");
    int num = std::stoi(s, 0, 16);
    hb_font_get_nominal_glyph(harf_font, num, &space_codepoint);

    int n = 0;
    word_desc* words = get_words_descs(desc, space_codepoint, &n);

    int* ans = text_wrap(words, line_lenght, font, n);

    int i = 0;

    float y_c = 0.0f;
    float x_c = 0.0f;
    math_shape_params_t* p = desc->first_param;

    while (i < n) { 
        float advance = words[i].p0_x + line_lenght - words[ans[i]].p1_x;

        for(int w=words[i].begin_text_pos; w < words[ans[i]].end_text_pos; w++) {
            p->x -= x_c;
            p->x += advance;
            p->y -= y_c;
            p = p->next;
        }


        if(p) {
            p = p->next; // space
            if(p) {
                x_c = p->x;
                y_c += line_height;
            }
        }

        i = ans[i] + 1; 
    } 

    hb_font_destroy(harf_font);
}

void midle_justify(math_shape_desc_t* desc, Font* font, float line_lenght, float line_height = 1.0f) {
    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);

    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    hb_codepoint_t space_codepoint;
    std::string s("0020");
    int num = std::stoi(s, 0, 16);
    hb_font_get_nominal_glyph(harf_font, num, &space_codepoint);

    int n = 0;
    word_desc* words = get_words_descs(desc, space_codepoint, &n);

    int* ans = text_wrap(words, line_lenght, font, n);

    int i = 0;

    float y_c = 0.0f;
    float x_c = 0.0f;
    math_shape_params_t* p = desc->first_param;

    while (i < n) { 
        float advance = words[i].p0_x + line_lenght - words[ans[i]].p1_x;

        for(int w=words[i].begin_text_pos; w < words[ans[i]].end_text_pos; w++) {
            p->x -= x_c;
            p->x += advance/2.f;
            p->y -= y_c;
            p = p->next;
        }


        if(p) {
            p = p->next; // space
            if(p) {
                x_c = p->x;
                y_c += line_height;
            }
        }

        i = ans[i] + 1; 
    } 

    hb_font_destroy(harf_font);
}




void justify(math_shape_desc_t* desc, Font* font, float line_lenght, float line_height = 1.0f) {
    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);

    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    hb_codepoint_t space_codepoint;
    std::string s("0020");
    int num = std::stoi(s, 0, 16);
    hb_font_get_nominal_glyph(harf_font, num, &space_codepoint);

    int n = 0;
    word_desc* words = get_words_descs(desc, space_codepoint, &n);

    int* ans = text_wrap(words, line_lenght, font, n);

    int i = 0;

    float y_c = 0.0f;
    float x_c = 0.0f;
    float remaining;
    math_shape_params_t* p = desc->first_param;
    math_shape_params_t* tmp = nullptr;

    while (i < n) { 


        tmp = p;
        for(int w=words[i].begin_text_pos; w < words[ans[i]].end_text_pos; w++) {
            p->x -= x_c;
            p->p0_x -=x_c;
            p->p1_x -=x_c;
            p->y -= y_c;
            p->p0_y -= y_c;
            p->p1_y -= y_c;
            p = p->next;
        }

        int h = 0;

        remaining = line_lenght - (words[ans[i]].p1_x - words[i].p0_x);
        float adv = (ans[i] - i) > 0 ? remaining/(ans[i] - i) : 0;
    


        for(int w=words[i].begin_text_pos; w < words[ans[i]].end_text_pos && (ans[i] + 1) < n; w++) {
            if(tmp->codepoint == space_codepoint) h++;
            tmp->x += h*adv;
            tmp = tmp->next;
        }

        if(p) {
            p = p->next; // space
            if(p) {
                x_c = p->x;
                y_c += line_height;
            }
        }

        i = ans[i] + 1; 
    } 

    hb_font_destroy(harf_font);
}



#endif