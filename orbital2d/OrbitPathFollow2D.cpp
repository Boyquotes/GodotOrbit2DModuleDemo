#include "OrbitPathFollow2D.hpp"
#include "orbits.hpp"
#include "kepler.hpp"

// TODO
void OrbitPathFollow2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_process"), &OrbitPathFollow2D::_process);
    ClassDB::bind_method(D_METHOD("get_time"), &OrbitPathFollow2D::get_time);
    ClassDB::bind_method(D_METHOD("set_standard_gravitational_parameter", "value"), &OrbitPathFollow2D::set_);
    ClassDB::bind_method(D_METHOD("get_standard_gravitational_parameter"), &OrbitPathFollow2D::get_);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "standard_gravitational_parameter"), "set_standard_gravitational_parameter", "get_standard_gravitational_parameter");
    ClassDB::bind_method(D_METHOD("set_true_anomaly_at_epoch", "value"), &OrbitPathFollow2D::set_);
    ClassDB::bind_method(D_METHOD("get_true_anomaly_at_epoch"), &OrbitPathFollow2D::get_);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "true_anomaly_at_epoch"), "set_true_anomaly_at_epoch", "get_true_anomaly_at_epoch");
}

OrbitPathFollow2D::OrbitPathFollow2D() {
    standard_gravitational_parameter = 10.0;
    true_anomaly_at_epoch = 0.0;
    _time = 0.0;
    _orbit_path_2d = get_parent();
}

OrbitPathFollow2D::~OrbitPathFollow2D() {}

void _process(const float delta) {
    _time += delta;
    orbits::PositionVelocity2D pv = get_heliocentric_position_velocity_from_time(
        _time,
        _orbit_path_2d.get_eccentricity(),
        _orbit_path_2d.get_semi_major_axis(),
        _orbit_path_2d.get_argument_of_periapsis(),
        standard_gravitational_parameter
    );
    set_position(pv.position);
    set_linear_velocity(pv.velocity);
}

// Setters
void set_standard_gravitational_parameter(const float value) {
    standard_gravitational_parameter = value;
}

void set_true_anomaly_at_epoch(const float value) {
    true_anomaly_at_epoch = value;
    // TODO set_position()
}

// Getters
float get_standard_gravitational_parameter() {
    return standard_gravitational_parameter;
}

float get_true_anomaly_at_epoch() {
    return true_anomaly_at_epoch;
}

float get_time() {
    return _time;
}
