# Orbits2D for Godot

A GodotNative module for adding orbits, collisions, etc in 2D

# Installation

1. Initialize all submodules
2. `make` from the root directory

# TODO

* [X] Create OrbitPath2D object. This will handle the path drawing code.
    * [ ] Unit Test the code
    * [ ] Provide a demo
* [ ] Create OrbitPathFollow2D object. This will handle the path following code.
    * [ ] Unit Test the code
    * [ ] Provide a demo
* [ ] Create a custom integrator for KinematicBody2D objects following Area2D nodes.
* [ ] Create a function for the following
    * [ ] Calculate the intercept points for two overlapping orbits
    * [ ] Calculate the next time to intercept
    * [ ] Calculate the next time two circles of size r1 and r2 would overlap
* [ ] Handle hyperbolic orbits
