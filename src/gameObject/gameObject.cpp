#include "gameObject.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/variant/utility_functions.hpp>
#include<godot_cpp/classes/input.hpp>
using namespace godot;

GameObject::GameObject() {
}

GameObject::~GameObject() {}

void GameObject::_bind_methods() {
    ClassDB::bind_method(D_METHOD("onCollision", "body"), &GameObject::onCollision);
}

void GameObject::_ready() {
    connect("body_entered", Callable(this , "onCollision"));
    set_linear_velocity(Vector2(0,0));
}

void GameObject::onCollision(Node* body) {
    String name = body->get_name().to_utf8_buffer().get_string_from_utf8();
    if(name == "Floor") {
        queue_free();
    }
}

void GameObject::_physics_process(double delta) {
    Vector2 vec = get_linear_velocity();
    vec.x -= 45;
    set_linear_velocity(vec);
}