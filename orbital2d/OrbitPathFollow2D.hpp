#ifndef __ORBITPATHFOLLOW2D_H_
#define __ORBITPATHFOLLOW2D_H_

#include "OrbitPath2D.hpp"
#include <core/math/vector2.h>
#include <scene/2d/path_follow_2d.h>
#include <scene/2d/area_2d.h>
#include <scene/resources/curve.h>
#include <scene/2d/sprite_2d.h>
#include <scene/2d/physics_body_2d.h>

class OrbitPathFollow2D : public PathFollow2D {
    GDCLASS(OrbitPathFollow2D, PathFollow2D);

private:
    float standard_gravitational_parameter;
    float true_anomaly_at_epoch;

    float _time;
    OrbitPath2D _orbit_path_2d;

public:
    static void _bind_methods();

    OrbitPathFollow2D();
    ~OrbitPathFollow2D();

    void _process(const float delta);

    // Setters
    void set_standard_gravitational_parameter(const float value);
    void set_true_anomaly_at_epoch(const float value);

    // Getters
    float get_standard_gravitational_parameter();
    float get_true_anomaly_at_epoch();
    float get_time();
};

#endif
