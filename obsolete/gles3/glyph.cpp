#include "glyph.h"
#include "vec-t/glyph.h"

Glyph::Glyph(FT_Face face, FT_UInt glyph_id) {
    this->_glyph = glyph_id;

    shape_triangulation_data vertice_data = parse_glyph(face, glyph_id);

    this->advance_x = vertice_data.advance_x;
    this->advance_y = vertice_data.advance_y;

    this->hori_bearing_x = vertice_data.hori_bearing_x;
    this->hori_bearing_y = vertice_data.hori_bearing_y;

    this->vert_bearing_x = vertice_data.vert_bearing_x;
    this->vert_bearing_y = vertice_data.vert_bearing_y;

    this->bounding_box.p0 = glm::vec2(vertice_data.boundings.p0.x, vertice_data.boundings.p0.y);
    this->bounding_box.p1 = glm::vec2(vertice_data.boundings.p1.x, vertice_data.boundings.p1.y);
    // this->advance_x = vertice_data.advance_x;
    // this->advance_y = vertice_data.advance_y;
    
    // this->_vao_data = vertice_data.path_vertex_array_data;
    // this->_vao_indices = vertice_data.indices;
    // this->_vao_bezier_data = vertice_data.curves_vertex_array_data;

	this->num_beziers = vertice_data.curves_vertex_array_data.size()/6;
	// this->num_indices = vertice_data.indices.size();
	this->num_triangles = vertice_data.path_vertex_array_data.size()/6;;

    this->program0 = new GLES3_Shader("assets/shaders/loop-blinn/mesh.vert.glsl","assets/shaders/loop-blinn/mesh-solid.frag2.glsl");
	this->program1 = new GLES3_Shader("assets/shaders/loop-blinn/mesh.vert.glsl","assets/shaders/loop-blinn/mesh.frag.glsl");



    glGenBuffers(1, &this->base_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->base_vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertice_data.path_vertex_array_data.size(), &vertice_data.path_vertex_array_data[0], GL_STATIC_DRAW);

    // glGenBuffers(1, &this->base_ibo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->base_ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * vertice_data.indices.size() , &vertice_data.indices[0], GL_STATIC_DRAW);


    glGenBuffers(1, &this->bezier_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->bezier_vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertice_data.curves_vertex_array_data.size(), &vertice_data.curves_vertex_array_data[0], GL_STATIC_DRAW);

}

void Glyph::draw(GLES3_Camera *camera, glm::mat4 model, std::vector<std::vector<glm::vec2>> positions_packs, std::vector<std::vector<glm::vec2>> scales_packs) {
    for(int i =0; i<positions_packs.size(); i++) {
        //Draw triangles
        this->program0->use();
        this->program0->set_uniform_vector2_array("positions", &positions_packs[i][0], positions_packs[i].size());
        this->program0->set_uniform_vector2_array("scales", &scales_packs[i][0], scales_packs[i].size());
        this->program0->set_uniform_matrix4("model", &model[0][0]);
        this->program0->set_uniform_matrix4("view", &camera->getView()[0][0]);
        this->program0->set_uniform_matrix4("projection", &camera->getProjection()[0][0]);

        glBindBuffer(GL_ARRAY_BUFFER, this->base_vao);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  this->base_ibo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // glDrawElementsInstanced(GL_TRIANGLES, this->num_indices, GL_UNSIGNED_INT, nullptr, positions.size());
        glDrawArraysInstanced(GL_TRIANGLES, 0, this->num_triangles, positions_packs[i].size());

        // glDrawElements(GL_TRIANGLES, this->num_indices, GL_UNSIGNED_INT, nullptr);

        //Draw beziers
        this->program1->use();

        this->program1->set_uniform_vector2_array("positions", &positions_packs[i][0], positions_packs[i].size());
        this->program0->set_uniform_vector2_array("scales", &scales_packs[i][0], scales_packs[i].size());

        this->program1->set_uniform_matrix4("model", &model[0][0]);
        this->program1->set_uniform_matrix4("view", &camera->getView()[0][0]);
        this->program1->set_uniform_matrix4("projection", &camera->getProjection()[0][0]);

        glBindBuffer(GL_ARRAY_BUFFER, this->bezier_vao);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // glDrawArrays(GL_TRIANGLES, 0, this->num_beziers);
        glDrawArraysInstanced(GL_TRIANGLES, 0, this->num_beziers, positions_packs[i].size());
    }
}