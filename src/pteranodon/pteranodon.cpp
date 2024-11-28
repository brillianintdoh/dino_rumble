#include "pteranodon.h"
#include<godot_cpp/core/class_db.hpp>
using namespace godot;

Pteranodon::Pteranodon() {
}

Pteranodon::~Pteranodon() {}

void Pteranodon::_bind_methods() {}

void Pteranodon::_ready() {
    animated = Object::cast_to<AnimatedSprite2D>(get_node_internal("Animated"));
    animated->play();
}

void Pteranodon::_physics_process(double delta) {
    if(is_Web) {
        // int w = js->get_meta("", 0);
    }
}