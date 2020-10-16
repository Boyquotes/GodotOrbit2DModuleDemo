#ifndef __ORBITPATH2D_H_
#define __ORBITPATH2D_H_

#include <core/math/vector2.h>
#include <scene/2d/path_2d.h>
#include <scene/2d/area_2d.h>
#include <scene/resources/curve.h>
#include <scene/2d/sprite_2d.h>
#include <scene/2d/physics_body_2d.h>

class OrbitPath2D : public Path2D {
    GDCLASS(OrbitPath2D, Path2D);

private:
    // User Defined
    float semi_major_axis;
    float eccentricity;
    float draw_points_per_perimeter_unit;
    Color draw_color;
    float draw_width;

    // Memoizations
    float _semi_minor_axis;

public:
    static void _bind_methods();

    OrbitPath2D();
    ~OrbitPath2D();

    void _draw();

    // Important Functions
    void generate_path();

    void draw_ellipse();

    // Setters
    void set_semi_major_axis(const float value);

    void set_eccentricity(const float value);

    void set_draw_points_per_perimeter_unit(const float value);

    void set_draw_color(const Color value);

    void set_draw_width(const float value);

    // Getters
    float get_semi_major_axis();

    float get_eccentricity();

    float get_argument_of_periapsis();

    int get_draw_resolution();

    float get_draw_points_per_perimeter_unit();

    Color get_draw_color();

    float get_draw_width();

    // Memoized Getters
    float get_semi_minor_axis();

    Vector2 get_focus_point();

    Vector2 get_centroid();

    float get_perimeter();

};

#endif
