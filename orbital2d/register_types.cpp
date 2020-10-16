/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "OrbitPath2D.hpp"
#include "OrbitPathFollow2D.hpp"

void register_orbital2d_types() {
	ClassDB::register_class<OrbitPath2D>();
	ClassDB::register_class<OrbitPathFollow2D>();
}

void unregister_orbital2d_types() {
	// Nothing to do here in this example.
}
