#vec-T
vec-t is a library capable of triangulating scalable vector grapgics with Constrained Delaunay Triangulation.

it uses CDT(https://github.com/artem-ogre/CDT) for the Constrained Delaunay Triangulation and FreeType for font parsing.


### Dependencies:
* FreeType2(https://www.freetype.org/)
###Compiling:

This library uses CMake(https://cmake.org/) as build system.

To compile on linux and macOS just type the following commands on the terminal from the root of the repository:
    ```mkdir build```
    ```cd build```
    ```cmake ..```
    ```make```

### Exposed methods:

This library exposes tree methods.

including "svg.h" you have access to the following methods:
```std::vector<shape_triangulation_data> parse_svg(const char* svg_path);```
This function receives the file path of the svg file and return a vector of shape_triangulation_data.


including "glyph.h" you have access to the following methods:
```shape_triangulation_data parse_glyph(FT_Face face, char glyph_id);```
This function receives a FT_Face and a glyph id and return a shape_triangulation_data of the glyph with id parsed to the function.

```shape_triangulation_data parse_glyph(const char* font_file, char glyph_id);```
This function receives a font path and a glyph id and return a shape_triangulation_data of the glyph with id parsed to the function.

### shape_triangulation_data:

This struct has:

    // Vertex array buffer of the shape.
	std::vector<float> path_vertex_array_data;

    // Vertex array buffer of the quadratic bezier curves of the shape.
	std::vector<float> curves_vertex_array_data;

    // Vertex array buffer of the stroke of the shape.
	std::vector<float> stroke_path_vertex_array_data;

    // Vertex array buffer of the quadratic bezier curves of the stroke.
	std::vector<float> stroke_curves_vertex_array_data;

each one of them can be interpreted as a Vertex Buffer, the first two related to the main shape and the next two are related to the stroke.

the layout of the VAO's are:
3 floats for posisitions, 3 floats for curve parameters, and 4 floats for colors.

so each vertex as the total of 10 floats.