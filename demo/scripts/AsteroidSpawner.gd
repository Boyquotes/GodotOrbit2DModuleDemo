extends Node
class_name AsteroidSpawner

@export var nb_asteroids = 100
@export var min_distance_from_center = 30.0
@export var max_distance_from_center = 90.0
@export var min_speed = 10.0
@export var max_speed = 20.0

var rng = RandomNumberGenerator.new()
	
# Called when the node enters the scene tree for the first time.
func _ready():
	rng.randomize()
	for i in range(nb_asteroids):
		spawn_asteroid()

func spawn_asteroid():
	var radius_from_center = rng.randf_range(min_distance_from_center, max_distance_from_center)
	var angle = rng.randf_range(0.0, 2.0*PI)
	var speed = rng.randf_range(min_speed, max_speed)
	var angular_velocity = rng.randf_range(-1.0, 1.0)
	
	var location = Vector2(0, 1).rotated(angle) * radius_from_center
	var velocity = Vector2(1, 0).rotated(angle) * speed
	
	var nodeInstance: RigidBody2D = RigidBody2D.new()
	var spriteInstance: Sprite2D = Sprite2D.new()
	var collisionInstance: CollisionShape2D = CollisionShape2D.new()
	spriteInstance.set_texture(load("res://assets/Moon/moon.png"))
	spriteInstance.set_scale(Vector2(.05, .05))
	collisionInstance.set_shape(CircleShape2D.new())
	nodeInstance.set_position(location)
	nodeInstance.set_linear_velocity(velocity)
	nodeInstance.set_angular_velocity(angular_velocity)
	nodeInstance.add_child(spriteInstance)
	nodeInstance.add_child(collisionInstance)
	add_child(nodeInstance)
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
# func _process(delta):
# 	pass
