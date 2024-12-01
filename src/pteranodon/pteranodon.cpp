#include "pteranodon.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/classes/input.hpp>
using namespace godot;

Pteranodon::Pteranodon() {
    isUP = 0;
}

Pteranodon::~Pteranodon() {}

void Pteranodon::_bind_methods() {}

void Pteranodon::_ready() {
    animated = Object::cast_to<AnimatedSprite2D>(get_node_internal("Animated"));
    animated->play();
}

void Pteranodon::_physics_process(double delta) {
    if(isRunble) return;
    Input& i = *Input::get_singleton();
    Vector2 vec = get_position();
    if(i.is_action_just_pressed("ui_up") && isUP) {
        vec.y -= 90;
        isUP = 0;
    }else if(i.is_action_just_pressed("ui_down") && !isUP) {
        vec.y += 90;
        isUP = 1;
    }
    String data = "{ \"y\":\""+String::num(vec.y)+"\" }";
    ws->send_text(data);

    set_position(vec);
}