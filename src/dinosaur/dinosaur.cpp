#include "dinosaur.h"
#include "../env/env.h"
#include<godot_cpp/classes/input.hpp>
#include<godot_cpp/core/class_db.hpp>
using namespace godot;

Dinosaur::Dinosaur() {
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
    if(!isRunble || isRunble == 2) return;
    int isDown = false;
    Input& i = *Input::get_singleton();
    Vector2 vec = get_position();
    if(i.is_action_just_pressed("ui_up") && isUP) {
        isDown = true;
        vec.y -= 90;
        isUP = 0;
    }else if(i.is_action_just_pressed("ui_down") && !isUP) {
        isDown = true;
        vec.y += 90;
        isUP = 1;
    }

    if(isDown) ws->send_text("{ \"type\":\"move\", \"x\":"+String::num(vec.x)+", \"y\":"+String::num(vec.y)+" }");

    set_position(vec);
}