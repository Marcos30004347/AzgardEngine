#include "shape.h"

Shape::Shape(shape_triangulation_data* triangulation_data) {

	this->num_beziers = triangulation_data->curves_vertex_array_data.size()/10;
	// this->num_indices = vertice_data.indices.size();
	this->num_triangles = triangulation_data->path_vertex_array_data.size()/10;

	this->stroke_num_beziers = triangulation_data->stroke_curves_vertex_array_data.size()/10;
	// this->num_indices = vertice_data.indices.size();
	this->stroke_num_triangles = triangulation_data->stroke_path_vertex_array_data.size()/10;

    this->base_path_sh = new GLES3_Shader("assets/shaders/svg/svg-path.vert.glsl","assets/shaders/svg/svg-path.frag.glsl");
	this->base_curve_sh = new GLES3_Shader("assets/shaders/svg/svg-curve.vert.glsl","assets/shaders/svg/svg-curve.frag.glsl");

    this->stroke_path_sh = new GLES3_Shader("assets/shaders/svg/svg-stroke-path.vert.glsl","assets/shaders/svg/svg-stroke-path.frag.glsl");
	this->stroke_curve_sh = new GLES3_Shader("assets/shaders/svg/svg-stroke-curve.vert.glsl","assets/shaders/svg/svg-stroke-curve.frag.glsl");

    glGenBuffers(1, &this->base_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->base_vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangulation_data->path_vertex_array_data.size(), &triangulation_data->path_vertex_array_data[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->stroke_base_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->stroke_base_vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangulation_data->stroke_path_vertex_array_data.size(), &triangulation_data->stroke_path_vertex_array_data[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->bezier_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->bezier_vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangulation_data->curves_vertex_array_data.size(), &triangulation_data->curves_vertex_array_data[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->stroke_bezier_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->stroke_bezier_vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangulation_data->stroke_curves_vertex_array_data.size(), &triangulation_data->stroke_curves_vertex_array_data[0], GL_STATIC_DRAW);

}

void Shape::draw(GLES3_Camera *camera, glm::mat4 model, std::vector<std::vector<glm::vec2>> positions, std::vector<std::vector<glm::vec2>> scales_packs) {
    // glm::mat4 _model = glm::rotate(model, glm::radians(180.f), glm::vec3(1.f,0.0f,0.0f));
    for(int i =0; i<positions.size(); i++) {


        //Draw triangles
        //Base
        this->base_path_sh->use();

        this->base_path_sh->set_uniform_vector2_array("positions", &positions[i][0], positions.size());
        // printf("first pos: (%f, %f)\n", positions[0].x, positions[0].y);
        this->base_path_sh->set_uniform_matrix4("model", &model[0][0]);
        this->base_path_sh->set_uniform_matrix4("view", &camera->getView()[0][0]);
        this->base_path_sh->set_uniform_matrix4("projection", &camera->getProjection()[0][0]);
        this->base_path_sh->set_uniform_vector2_array("scales", &scales_packs[i][0], scales_packs[i].size());

        glBindBuffer(GL_ARRAY_BUFFER, this->base_vao);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  this->base_ibo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glDrawArraysInstanced(GL_TRIANGLES, 0, this->num_triangles, positions.size());

        //Draw beziers
        this->base_curve_sh->use();

        this->base_curve_sh->set_uniform_vector2_array("positions", &positions[i][0], positions.size());
        this->base_curve_sh->set_uniform_matrix4("model", &model[0][0]);
        this->base_curve_sh->set_uniform_matrix4("view", &camera->getView()[0][0]);
        this->base_curve_sh->set_uniform_matrix4("projection", &camera->getProjection()[0][0]);
        this->base_curve_sh->set_uniform_vector2_array("scales", &scales_packs[i][0], scales_packs[i].size());

        glBindBuffer(GL_ARRAY_BUFFER, this->bezier_vao);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    
        glDrawArraysInstanced(GL_TRIANGLES, 0, this->num_beziers, positions.size());

        // Strokes
        //Draw triangles
        this->stroke_path_sh->use();
        this->stroke_path_sh->set_uniform_vector2_array("positions", &positions[i][0], positions.size());
        this->stroke_path_sh->set_uniform_matrix4("model", &model[0][0]);
        this->stroke_path_sh->set_uniform_matrix4("view", &camera->getView()[0][0]);
        this->stroke_path_sh->set_uniform_matrix4("projection", &camera->getProjection()[0][0]);
        this->stroke_path_sh->set_uniform_vector2_array("scales", &scales_packs[i][0], scales_packs[i].size());

        glBindBuffer(GL_ARRAY_BUFFER, this->stroke_base_vao);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  this->base_ibo);
    
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    

        glDrawArraysInstanced(GL_TRIANGLES, 0, this->stroke_num_triangles, positions.size());

        //Draw beziers
        this->stroke_curve_sh->use();

        this->stroke_curve_sh->set_uniform_vector2_array("positions", &positions[i][0], positions.size());
        this->stroke_curve_sh->set_uniform_matrix4("model", &model[0][0]);
        this->stroke_curve_sh->set_uniform_matrix4("view", &camera->getView()[0][0]);
        this->stroke_curve_sh->set_uniform_matrix4("projection", &camera->getProjection()[0][0]);
        this->stroke_curve_sh->set_uniform_vector2_array("scales", &scales_packs[i][0], scales_packs[i].size());

        glBindBuffer(GL_ARRAY_BUFFER, this->stroke_bezier_vao);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    

        glDrawArraysInstanced(GL_TRIANGLES, 0, this->stroke_num_beziers, positions.size());

    }
}