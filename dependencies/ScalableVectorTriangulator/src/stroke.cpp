#include "vec-t/stroke.h"
#include <set>
#include "stdio.h"


// void remove_segments_from_to(path &contour, int i, int j) {
//     for(int k=i; k<=j; j--) {
//         std::vector<bezier> to_remove = contour.beziers[k];
//         bezier_point_coordinates bez_coord = find_quadratic_bezier(to_remove[0], contour, 0);
//         if(bez_coord.bezier != -1) {
//             std::vector<quadratic_bezier>::iterator it = contour.quadratic_bezier_curves.begin();
//             it += k;
//             contour.quadratic_bezier_curves.erase(it);
//         }
//         std::vector<std::vector<bezier>>::iterator it = contour.beziers.begin();
//         it += k;
//         contour.beziers.erase(it);
//     }
// }

// void remove_intersecting_paths(path &contour) {
//     for(int i=0; i<contour.beziers.size(); i++) {
//         for(int k=i+2; k<contour.beziers.size(); k++) {
//             if(
//                 contour.beziers[i][0] == contour.beziers[k][0]
//                 && contour.beziers[i][1] == contour.beziers[k][1]
//             ) {
//                 continue;
//             }
//             point A = contour.beziers[i][0];
//             point B = contour.beziers[i][1];
//             point C = contour.beziers[k][0];
//             point D = contour.beziers[k][1];
//             line_intercection_params params = line_intercept_params(A, B, C, D);

//             if(params.t >0 && params.t <1 && params.u>0 && params.u < 1) {
//                 point intersection = ((C - D)*params.t)+ D;

//                 int next_bez = k == contour.beziers.size() - 1 ? 0: k + 1;

//                 std::vector<bezier> segA = { contour.beziers[i][0], intersection };
//                 std::vector<bezier> seg2 = { intersection, contour.beziers[k][1] };
 
//                 remove_segments_from_to(contour, i, k);
    
//                 std::vector<std::vector<bezier>>::iterator it = contour.beziers.begin();
//                 it += i;

//                 contour.beziers.insert(it, seg2);
//                 contour.beziers.insert(it, segA);
//             }
//         }
//     }
// }

std::vector<path> build_stroke_segment(
    point A,
    point B,
    point C,
    point D,

    path original_path,
    float width,
    bool is_quadratic,
    bezier_t bez,
    stroke_linejoin join
) {
    std::vector<path> paths;
    path segment;

    point N0 = normal(A, B, -1.f*original_path.orientation);
    N0 = N0 - ((A+B)*0.5f);

    point N1 = normal(C, D, -1.f*original_path.orientation);
    N1 = N1 - ((C+D)*0.5f);

    /**
     * cA===cB Cc===cD
     * cE===cF cG===cH
    **/

    point cA = (N0*1*width) + A;
    point cB = (N0*1*width) + B;
    point cC = (N1*1*width) + C;
    point cD = (N1*1*width) + D;

    point cE = (N1*-1*width) + D;
    point cF = (N1*-1*width) + C;
    point cG = (N0*-1*width) + B;
    point cH = (N0*-1*width) + A;

    segment.beziers.push_back(bezier_t(cA, cB));
    segment.beziers.push_back(bezier_t(cB, cG));
    segment.beziers.push_back(bezier_t(cG, cH));
    segment.beziers.push_back(bezier_t(cH, cA));

    if(is_quadratic) {

        point control = (N0*1*width) + bez.control;
        segment.beziers.push_back(bezier_t(
            cA, control, cB
        ));
    
        control = (N0*-1*width) + bez.control;
    
        segment.beziers.push_back(bezier_t(
            cG, control, cH
        ));
    }

    if(cB != cC) {
        path line_join;

        // Line dont intersect
        /**
         * cA===cB==Cc====cD
        **/
        line_join.beziers.push_back({cB, cC});
        line_join.beziers.push_back({cC, C});
        line_join.beziers.push_back({C, cB});

        // This is given weird results, take a look at it later.
        line_intercection_params params = line_intercept_params(cA, cB, cC, cD);
        point intersection = ((cB - cA)*params.t)+ cA;
    
        if(join == JOIN_MITER) {
            path mitter;

            mitter.beziers.push_back({cB, cC});
            mitter.beziers.push_back({cC, intersection});
            mitter.beziers.push_back({intersection, cB});
            paths.push_back(mitter);

        } else if(join == JOIN_ROUND) {
            line_join.beziers.push_back(bezier_t(cB, intersection, cC));
        }

        paths.push_back(line_join);
    }

    if(cF != cG) {
        path line_join;

        // Line dont intersect
        /**
         * cA===cB==Cc====cD
        **/
        line_join.beziers.push_back({cF, cG});
        line_join.beziers.push_back({cG, B});
        line_join.beziers.push_back({B, cF});

        // This is given weird results, take a look at it later.
        line_intercection_params params = line_intercept_params(cE, cF, cG, cH);
        point intersection = ((cF - cE)*params.t)+ cE;

        if(join == JOIN_MITER) {
            path mitter;

            mitter.beziers.push_back({cF, cG});
            mitter.beziers.push_back({cG, intersection});
            mitter.beziers.push_back({intersection, cF});
            paths.push_back(mitter);

        } else if(join == JOIN_ROUND) {
            line_join.beziers.push_back(bezier_t(cF, intersection, cG));
        }
        paths.push_back(line_join);
    }
    
    paths.push_back(segment);
    return paths;
}


std::vector<path> build_stroke_path(path contour, float width, stroke_linejoin join) {
    std::vector<path> paths;
    printf("Generating stroke of Path...\n");

    point last_point_up = point(-10000.f, -10000.f);
    point last_point_bottom = point(-10000.f, -10000.f);
    
    path up_path;
    up_path.orientation = contour.orientation;
    path bottom_path;
    up_path.orientation = -1*contour.orientation;
    for(int bez=0; bez < contour.beziers.size(); bez++) {
    
        int next_bez = bez == contour.beziers.size() - 1 ? 0 : bez + 1;
        int previous_bez = bez == contour.beziers.size() - 1 ? 0 : bez + 1;

        point A = contour.beziers[bez].off0;
        point B = contour.beziers[bez].off1;

        point C = contour.beziers[next_bez].off0;
        point D = contour.beziers[next_bez].off1;
    
        if(bez == 0) {
            point E = contour.beziers[contour.beziers.size() - 1].off0;
            point F = contour.beziers[contour.beziers.size() - 1].off1;

            point N0 = normal(E, F, -1.f*contour.orientation);
            N0 = N0 - ((E+F)*0.5f);

            point N1 = normal(A, B, -1.f*contour.orientation);
            N1 = N1 - ((A+B)*0.5f);
        
            point _cA = (N0*1*width) + E;
            point _cB = (N0*1*width) + F;
            point _cC = (N1*1*width) + A;
            point _cD = (N1*1*width) + B;

            line_intercection_params params = line_intercept_params(_cA, _cB, _cC, _cD);
            if(params.t >=0 && params.t <=1 && params.u>=0 && params.u <= 1) {
                last_point_up = ((_cB - _cA)*params.t)+ _cA;
            }

            _cA = (N0*-1*width) + E;
            _cB = (N0*-1*width) + F;
            _cC = (N1*-1*width) + A;
            _cD = (N1*-1*width) + B;

            params = line_intercept_params(_cA, _cB, _cC, _cD);
            if(params.t >=0 && params.t <=1 && params.u>=0 && params.u <= 1) {
                last_point_bottom = ((_cB - _cA)*params.t)+ _cA;
            }

        }

        
        bezier_t _bez = bezier_t(point(0,0), point(0,0), point(0,0));
        if(A == B || C == D) continue;

        std::vector<path> stoke_segments = build_stroke_segment(
            A,
            B,
            C,
            D,
            contour,
            width,
            contour.beziers[bez].is_quadratic,
            contour.beziers[bez],
            join
        );
    
        for(path p: stoke_segments) paths.push_back(p);
    }

    printf("done creating stroke paths!\n");

    return paths;
}






