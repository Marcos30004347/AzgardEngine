#include "Parser.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace tinyobj;

ModelData ParseObj(const char* obj) {
    tinyobj::ObjReader reader = tinyobj::ObjReader();
    std::istringstream obgStream = std::istringstream(obj);


    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;

    tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &obgStream);

    std::vector<MeshData> objmeshes = std::vector<MeshData>(shapes.size());
    float x = 0;
    float y = 0;

    for (size_t s = 0; s < shapes.size(); s++) {
        objmeshes[s] = MeshData();

        objmeshes[s].name = shapes[s].name.c_str();
        objmeshes[s].vertices = std::vector<VerticeData>(shapes[s].mesh.indices.size());
        objmeshes[s].indices = std::vector<unsigned int>(shapes[s].mesh.indices.size());
    
        size_t index_offset = 0;

        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            for (size_t v = 0; v < fv; v++) {
                VerticeData obj_vertice;
            
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
            
                tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
                tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
                tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
                tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
                tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
                tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
                x+= vx;
                y+= vy;
                obj_vertice.posX = vx;
                obj_vertice.posY = vy;
                obj_vertice.posZ = vz;

                obj_vertice.normX = nx;
                obj_vertice.normY = ny;
                obj_vertice.normZ = nz;
            
                obj_vertice.uvX = tx;
                obj_vertice.uvY = ty;

                objmeshes[s].indices[index_offset + v] = index_offset + v;
                objmeshes[s].vertices[index_offset + v] = obj_vertice;
            }
        
            index_offset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];
        }
    }

    ModelData model;
    model.meshes = objmeshes;
    x = x/attrib.vertices.size();
    y = y/attrib.vertices.size();

    printf("center %f %f\n", x, y);

    // ??
    model.name = "Model";

    return model;
}