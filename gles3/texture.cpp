#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

GLES3_Texture::GLES3_Texture(const char** filepaths, unsigned int n_textures, unsigned int width, unsigned int height) {
    glGenTextures(1, &(this->_texture));

    glBindTexture(GL_TEXTURE_2D_ARRAY, this->_texture);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexImage3D(GL_TEXTURE_2D_ARRAY,1, GL_RGBA8, width, height, n_textures, 0.0f, GL_RGBA, GL_UNSIGNED_BYTE, DA );
    // glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, n_textures);
    this->_height = height;
    this->_width = width;

    for(int i=0; i<n_textures; i++) {
        unsigned char *data = stbi_load(filepaths[i], &(this->_width), &(this->_height), &(this->_n_chanels), 0);
        if (data){
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Failed to load texture: "<< i << std::endl;
        }
        stbi_image_free(data);
    }

    glGenerateMipmap(GL_TEXTURE_2D);

}

void GLES3_Texture::use() {
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->_texture);
}