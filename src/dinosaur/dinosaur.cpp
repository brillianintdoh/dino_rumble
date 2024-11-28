#include "dinosaur.h"
#include "../env/env.h"
#include<godot_cpp/classes/input.hpp>
#include<godot_cpp/core/class_db.hpp>
using namespace godot;

Dinosaur::Dinosaur() {
    speed = 100.0f;
    isUP = 1;
}

Dinosaur::~Dinosaur() {
}

void Dinosaur::_bind_methods() {}

void Dinosaur::_ready() {
    animated = Object::cast_to<AnimatedSprite2D>(get_node_internal("Animated"));
    animated->play();
}

void Dinosaur::_physics_process(double delta) {
    if(!isRunble) return;
    Input& i = *Input::get_singleton(); 
    Vector2 vec = get_position();
    if(i.is_action_just_pressed("ui_up") && isUP) {
        vec.y -= 90;
        isUP = 0;
    }else if(i.is_action_just_pressed("ui_down") && !isUP) {
        vec.y += 90;
        isUP = 1;
    }

    set_position(vec);
}