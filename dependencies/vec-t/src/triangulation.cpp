#include "vec-t/triangulation.h"
#include "stdio.h"

#define CDT_DONT_USE_BOOST_RTREE
#include "CDT.h"

std::vector<float> build_paths_vertices(shape &shape) {


	CDT::Triangulation<float> cdt = CDT::Triangulation<float>(CDT::FindingClosestPoint::ClosestRandom, 10);

	std::vector<float> vertex_array_buffer;

	std::vector<CDT::V2d<float>> points = std::vector<CDT::V2d<float>>();
	std::vector<CDT::Edge> edges = std::vector<CDT::Edge>();
	// printf("triangulating %lu paths...\n", shape.paths.size());
	
	for(int c = 0; c < shape.paths.size(); c++) {
		
		unsigned int previous_size = points.size();

		for(int p=0; p<shape.paths[c].beziers.size(); p++) {
			point segFirst = shape.paths[c].beziers[p].off0;

			// printf("(%f, %f)\n", segFirst.x, segFirst.y);
			// bezier_point_coordinates coord = find_quadratic_bezier(segFirst, shape, 0);
			if(shape.paths[c].beziers[p].is_quadratic) { // point found.
				int winding_number = shape.paths[c].beziers[p].control.winding_number;	
				// printf("kkkkkkk\n");
				// printf("===Bezier===\n");

				if(
					(winding_number) % 2 
					&& triangle_area(
						shape.paths[c].beziers[p].off0,
						shape.paths[c].beziers[p].control,
						shape.paths[c].beziers[p].off1
					) > 0.0f
				) { //should include control point of bezier in polygon.
					// printf("incluiu=%i\n", winding_number);
					// printf("(%f, %f)\n", shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][0].x, shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][0].y);
					// printf("(%f, %f)\n", shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][1].x, shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][1].y);
					// printf("(%f, %f)\n", shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][2].x, shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][2].y);
					// printf("=======\n");

					CDT::V2d<float> _point0 = CDT::V2d<float>();
					CDT::V2d<float> _point1 = CDT::V2d<float>();
					CDT::V2d<float> _point2 = CDT::V2d<float>();

					_point0.x = shape.paths[c].beziers[p].off0.x;
					_point0.y = shape.paths[c].beziers[p].off0.y;
				
					
					_point1.x = shape.paths[c].beziers[p].control.x;
					_point1.y = shape.paths[c].beziers[p].control.y;

					_point2.x = shape.paths[c].beziers[p].off1.x;
					_point2.y = shape.paths[c].beziers[p].off1.y;

					point k = (shape.paths[c].beziers[p].off0 + shape.paths[c].beziers[p].control + shape.paths[c].beziers[p].off1)/3.f;
					k = k - shape.paths[c].beziers[p].control;
					k = k*0.00001f;
					k = k + shape.paths[c].beziers[p].control;

					for(bezier_t l :shape.paths[c].beziers) {
						if(triangle_area(l.off0, shape.paths[c].beziers[p].control, l.off1)) {
							_point1.x = k.x;
							_point1.y = k.y;
						}
					}


					// printf("including:%f\n", triangle_area(
					// 	shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][0],
					// 	shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][1],
					// 	shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][2]
					// ));
					// printf("(%f, %f)\n", _point0.x,_point0.y);
					// printf("(%f, %f)\n", _point1.x,_point1.y);
					// printf("(%f, %f)\n", _point2.x,_point2.y);

					points.push_back(_point0);
					CDT::Edge _edge0 = CDT::Edge(
						points.size() - 1,
						points.size()
					);
					edges.push_back(_edge0);
		
					points.push_back(_point1);
					CDT::Edge _edge1 = CDT::Edge(
						points.size() - 1,
						points.size()
					);
					edges.push_back(_edge1);

					points.push_back(_point2);
					CDT::Edge _edge2 = CDT::Edge(
						points.size() - 1,
						((unsigned int)p == (shape.paths[c].beziers.size() - 1) ? previous_size : points.size())
					);
					edges.push_back(_edge2);

				} 
				else { // should include just the base of the bezier triangle
					// printf("nao incluiu=%i\n", winding_number);
					// printf("(%f, %f)\n", shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][0].x, shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][0].y);
					// printf("(%f, %f)\n", shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][1].x, shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][1].y);
					// printf("(%f, %f)\n", shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][2].x, shape.paths[coord.path].quadratic_bezier_curves[coord.bezier][2].y);
					// printf("=======\n");
					CDT::V2d<float> _point0 = CDT::V2d<float>();
					CDT::V2d<float> _point1 = CDT::V2d<float>();
					CDT::V2d<float> _point2 = CDT::V2d<float>();

					_point0.x =  shape.paths[c].beziers[p].off0.x;
					_point0.y =  shape.paths[c].beziers[p].off0.y;
										

					_point2.x =  shape.paths[c].beziers[p].off1.x;
					_point2.y =  shape.paths[c].beziers[p].off1.y;

					_point1.x = (_point0.x+_point2.x)*0.5f;
					_point1.y = (_point0.y+_point2.y)*0.5f;

					points.push_back(_point0);

					CDT::Edge _edge0 = CDT::Edge(
						points.size() - 1,
						points.size()
					);

					edges.push_back(_edge0);
				
					// points.push_back(_point1);

					// CDT::Edge _edge1 = CDT::Edge(
					// 	points.size() - 1,
					// 	points.size()
					// );

					// edges.push_back(_edge1);

					points.push_back(_point2);

					CDT::Edge _edge2 = CDT::Edge(
						points.size() - 1,
						((unsigned int)p == (shape.paths[c].beziers.size() - 1) ? previous_size : points.size())
					);
					edges.push_back(_edge2);

				}
			}
			else { 
				// printf("===Segment===\n");
				// printf("(%f, %f)\n", shape.paths[c].linear_bezier_curves[p][0].x, shape.paths[c].linear_bezier_curves[p][0].y);
				// printf("(%f, %f)\n", shape.paths[c].linear_bezier_curves[p][1].x, shape.paths[c].linear_bezier_curves[p][1].y);
				// printf("===Segment===\n");

				CDT::V2d<float> _point = CDT::V2d<float>();
				_point.x = shape.paths[c].beziers[p].off0.x;
				_point.y = shape.paths[c].beziers[p].off0.y;
				points.push_back(_point);
				CDT::Edge edge = CDT::Edge(
					points.size() - 1,
					((unsigned int)p == (shape.paths[c].beziers.size() - 1) ? previous_size : points.size())
				);
				edges.push_back(edge);
			}
		}
	}

	// printf("calling CDT!\n");
	// printf("%li points and %li edges...\n", points.size(), edges.size());
	
	// if(points[edges[0].v1()].x != points[edges[edges.size() - 1].v2()].x && points[edges[0].v1()].y != points[edges[edges.size() - 1].v2()].y) {
	// 	CDT::Edge _edge0 = CDT::Edge(
	// 		points.size() - 1,
	// 		0
	// 	);
	// 	edges.push_back(_edge0);
	// }

	const std::vector<std::size_t> mapping = CDT::RemoveDuplicates(points);
	CDT::RemapEdges(edges, mapping);

	// printf("CDT......	\n");
	// for(int e =0; e< edges.size(); e++) {
	// 	// printf("(%f, %f)\n", points[edges[e].v1()].x, points[edges[e].v1()].y);
	// 	// printf("(%f, %f)\n", points[edges[e].v2()].x, points[edges[e].v2()].y);
	// 	if(points[edges[e].v1()] == points[edges[e].v2()]) {
	// 		edges.erase(edges.begin() + e);
	// 		e--;
	// 	}
	// }

	// for(int e =0; e< edges.size(); e++) {
	// 	printf("(%f, %f)\n", points[edges[e].v1()].x, points[edges[e].v1()].y);
	// 	printf("(%f, %f)\n", points[edges[e].v2()].x, points[edges[e].v2()].y);
	// }
	// printf("triangulating...\n");

	cdt.insertVertices(points);	
	cdt.insertEdges(edges);
	cdt.eraseOuterTrianglesAndHoles();

	// printf("path triangles count: (%lu)\n", cdt.triangles.size());
	// if(!cdt.triangles.size()) throw 20;

	for(int i =0; i< cdt.triangles.size(); i++) {
		for(int v=0; v<3; v++) {
			vertex_array_buffer.push_back(cdt.vertices[cdt.triangles[i].vertices[v]].pos.x);
			vertex_array_buffer.push_back(cdt.vertices[cdt.triangles[i].vertices[v]].pos.y);
			vertex_array_buffer.push_back(0.0f);

			vertex_array_buffer.push_back(0.0f);
			vertex_array_buffer.push_back(0.0f);
			vertex_array_buffer.push_back(0.0f);
		}

	}

	return vertex_array_buffer;
}



std::vector<float> build_curves_vertices(shape _shape) {
	std::vector<float> vertex_buffer_array;

	for(int c=0; c<_shape.paths.size(); c++) {
		for(int s=0; s<_shape.paths[c].beziers.size(); s++) {

			int winding_number = _shape.paths[c].beziers[s].control.winding_number;
			int size = (winding_number % 2) ? 1.0f : -1.0f;

			// x y z r g b
			vertex_buffer_array.push_back(_shape.paths[c].beziers[s].off0.x);
			vertex_buffer_array.push_back(_shape.paths[c].beziers[s].off0.y);
			vertex_buffer_array.push_back(0.0f);
			vertex_buffer_array.push_back(0.0f);
			vertex_buffer_array.push_back(0.0f);
			vertex_buffer_array.push_back(size);


			vertex_buffer_array.push_back(_shape.paths[c].beziers[s].control.x);
			vertex_buffer_array.push_back(_shape.paths[c].beziers[s].control.y);
			vertex_buffer_array.push_back(0.0f);
			vertex_buffer_array.push_back(0.5f);
			vertex_buffer_array.push_back(0.0f);
			vertex_buffer_array.push_back(size);
		

			vertex_buffer_array.push_back(_shape.paths[c].beziers[s].off1.x);
			vertex_buffer_array.push_back(_shape.paths[c].beziers[s].off1.y);
			vertex_buffer_array.push_back(0.0f);
			vertex_buffer_array.push_back(1.0f);
			vertex_buffer_array.push_back(1.0f);
			vertex_buffer_array.push_back(size);
		}
	}
	// printf("curves triangles count: (%lu)\n", vertex_buffer_array.size()/6);
	return vertex_buffer_array;
}
