#include "gameObject.h"
#include "../env/env.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/variant/utility_functions.hpp>
#include<godot_cpp/classes/input.hpp>
using namespace godot;

GameObject::GameObject() {}

GameObject::~GameObject() {}

void GameObject::_bind_methods() {
    ClassDB::bind_method(D_METHOD("onCollision", "body"), &GameObject::onCollision);
}

void GameObject::_ready() {
    connect("body_entered", Callable(this , "onCollision"));
    set_linear_velocity(Vector2(0,0));
    set_lock_rotation_enabled(true);
    set_collision_layer(1);
}

void GameObject::onCollision(Node* body) {
    String name = body->get_name().to_utf8_buffer().get_string_from_utf8();
    if(name == "Floor") {
        queue_free();
        ws->send_text("{ \"type\":\"o1_delete\" }");
    }else if(name == "dinosaur") {
        if(isUPdino && get_z_index() == 4) {
            set_collision_layer(0);
        }else {
            heart.back()->queue_free();
            heart.pop_back();
            ws->send_text("{ \"type\":\"heart\" }");
        }
    }
}

void GameObject::_physics_process(double delta) {
    if(get_gravity_scale() && !isRunble) {
        Vector2 vec = get_linear_velocity();
        vec.x -= 45;
        set_linear_velocity(vec);
        
        Vector2 v = get_position();
        ws->send_text("{ \"type\":\"o1\", \"x\":"+String::num(v.x)+", \"y\":"+String::num(v.y)+" }");
    }
}