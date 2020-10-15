#include "OrbitPath2D.hpp"
#include "orbits.hpp"

// TODO
void OrbitPath2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_draw"), &OrbitPath2D::_draw);
    ClassDB::bind_method(D_METHOD("get_semi_minor_axis"), &OrbitPath2D::get_semi_minor_axis);
    ClassDB::bind_method(D_METHOD("get_focus_point"), &OrbitPath2D::get_focus_point);
    ClassDB::bind_method(D_METHOD("get_centroid"), &OrbitPath2D::get_centroid);
    ClassDB::bind_method(D_METHOD("get_argument_of_periapsis"), &OrbitPath2D::get_argument_of_periapsis);

    ClassDB::bind_method(D_METHOD("set_semi_major_axis", "value"), &OrbitPath2D::set_semi_major_axis);
    ClassDB::bind_method(D_METHOD("get_semi_major_axis"), &OrbitPath2D::get_semi_major_axis);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "semi_major_axis"), "set_semi_major_axis", "get_semi_major_axis");
    ClassDB::bind_method(D_METHOD("set_eccentricity", "value"), &OrbitPath2D::set_eccentricity);
    ClassDB::bind_method(D_METHOD("get_eccentricity"), &OrbitPath2D::get_eccentricity);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "eccentricity"), "set_eccentricity", "get_eccentricity");
    ClassDB::bind_method(D_METHOD("set_draw_points_per_perimeter_unit", "value"), &OrbitPath2D::set_draw_points_per_perimeter_unit);
    ClassDB::bind_method(D_METHOD("get_draw_points_per_perimeter_unit"), &OrbitPath2D::get_draw_points_per_perimeter_unit);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "draw_points_per_perimeter_unit"), "set_draw_points_per_perimeter_unit", "get_draw_points_per_perimeter_unit");
    ClassDB::bind_method(D_METHOD("set_draw_color", "value"), &OrbitPath2D::set_draw_color);
    ClassDB::bind_method(D_METHOD("get_draw_color"), &OrbitPath2D::get_draw_color);
    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "draw_color"), "set_draw_color", "get_draw_color");
    ClassDB::bind_method(D_METHOD("set_draw_width", "value"), &OrbitPath2D::set_draw_width);
    ClassDB::bind_method(D_METHOD("get_draw_width"), &OrbitPath2D::get_draw_width);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "draw_width"), "set_draw_width", "get_draw_width");
}

OrbitPath2D::OrbitPath2D() {
    semi_major_axis = 10.0;
    _semi_minor_axis = 10.0;
    eccentricity = 0.0;  // Starts as a circle
    draw_points_per_perimeter_unit = 1.0;
    draw_color = Color(0,0,0);
    draw_width = 1.0;
}
OrbitPath2D::~OrbitPath2D() {}
//void OrbitPath2D::_ready() {}

//void OrbitPath2D::_physics_process(float delta) {
//	_path_follow->set_offset(_path_follow->get_offset() + get_velocity() * delta);
//}

void OrbitPath2D::_draw() {draw_ellipse();}

void OrbitPath2D::draw_ellipse() {
	// REF: https://www.mathopenref.com/coordcirclealgorithm.html
	const int nb_points = get_draw_resolution();
	float theta = 0.0;  // angle that will be increased each loop
	const float step = 2.0*M_PI / (float) nb_points;  // amount to add to theta each time (radians)
    const auto centroid = get_centroid();
    const auto semi_minor_axis = get_semi_minor_axis();
	PackedVector2Array points;

	int i = 0;
	while (theta < 2.0*M_PI) {
		const real_t x = semi_minor_axis*Math::cos(theta) + centroid.x;
		const real_t y = semi_major_axis*Math::sin(theta) + centroid.y;
		points.push_back(Vector2{x, y});
		theta += step;
		i++;
	}
	for (int i = 0; i < nb_points-1; i++) {
		draw_line(points[i], points[i+1], draw_color, draw_width);
	}
    draw_line(points[nb_points-1], points[0], draw_color, draw_width);
}

// Important Functions
void OrbitPath2D::generate_path() {
	// REF: https://www.mathopenref.com/coordcirclealgorithm.html
	const int nb_points = get_draw_resolution();
	float theta = 0.0;  // angle that will be increased each loop
	const float step = 2.0*M_PI / (float) nb_points;  // amount to add to theta each time (radians)
    const auto centroid = get_centroid();
    const auto semi_minor_axis = get_semi_minor_axis();
    auto curve = get_curve();
    curve->clear_points();

	while (theta < 2.0*M_PI) {
		const real_t x = semi_minor_axis*Math::cos(theta) + centroid.x;
		const real_t y = semi_major_axis*Math::sin(theta) + centroid.y;
        curve->add_point(Vector2(x, y));
		theta += step;
	}
}


// Setters
void OrbitPath2D::set_semi_major_axis(const float value) {
    semi_major_axis = value;
    _semi_minor_axis = orbits::get_semi_minor_axis(eccentricity, semi_major_axis);
    // _cached_angular_velocity = 0.0;
    generate_path();
    update();
}
void OrbitPath2D::set_eccentricity(const float value) {
    eccentricity = value;
    _semi_minor_axis = orbits::get_semi_minor_axis(eccentricity, semi_major_axis);
    // _cached_angular_velocity = 0.0;
    generate_path();
    update();
}

void OrbitPath2D::set_draw_points_per_perimeter_unit(const float value) {
    draw_points_per_perimeter_unit = value;
    generate_path();
    update();
}
void OrbitPath2D::set_draw_color(const Color value) {
    draw_color = value;
    generate_path();
    update();
}
void OrbitPath2D::set_draw_width(const float value) {
    draw_width = value;
    generate_path();
    update();
}

// Getters
float OrbitPath2D::get_semi_major_axis() {return semi_major_axis;}
float OrbitPath2D::get_eccentricity() {return eccentricity;}
float OrbitPath2D::get_argument_of_periapsis() {return get_rotation();}
//float OrbitPath2D::get_gravity() {return gravity;}
float OrbitPath2D::get_draw_points_per_perimeter_unit() {return draw_points_per_perimeter_unit;}
int OrbitPath2D::get_draw_resolution() {return (int) (get_perimeter() * fmax(1.0, draw_points_per_perimeter_unit));}

// Memoized Getters
float OrbitPath2D::get_semi_minor_axis() {
  return _semi_minor_axis;
}
//Vector2 OrbitPath2D::get_velocity() {
//    // TODO: Handle circular obits with a cached velocity
//    Vector2 v = get_heliocentric_velocity_from_eccentric_anomaly(
//        get_eccentric_anomaly_from_position(position, focus_point),
//        eccentricity,
//        semi_major_axis,
//        argument_of_periapsis,
//        get_standard_gravitational_parameter()
//    );
//}
//PhysicsBody2D* OrbitPath2D::get_body() {
//    return _body;
//}
//PathFollow2D* OrbitPath2D::get_path_follow() {
//    return _path_follow;
//}
//Area2D* OrbitPath2D::get_area() {
//    return _area;
//}
//float OrbitPath2D::get_standard_gravitational_parameter() {
//    return _standard_gravitational_area;
//}
Vector2 OrbitPath2D::get_focus_point() {
    return get_position();
}
Vector2 OrbitPath2D::get_centroid() {
    return orbits::get_centroid_from_focus_point(eccentricity, semi_major_axis, get_argument_of_periapsis(), get_focus_point());
}
Color OrbitPath2D::get_draw_color() {
    return draw_color;
}
float OrbitPath2D::get_draw_width() {
    return draw_width;
}
float OrbitPath2D::get_perimeter() {
    const float a = get_semi_major_axis();
    const float b = get_semi_minor_axis();
    // REF: https://www.mathsisfun.com/geometry/ellipse-perimeter.html
    // Using Ramanujan's method
    const float h = (a - b) * (a - b) / ((a + b) * (a + b));
    return M_PI * (a + b) * (1.0 + ((3.0 * h)/(10.0 + Math::sqrt(4.0 - (3.0 * h)))));
}
