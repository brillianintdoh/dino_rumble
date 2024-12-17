#include "dinosaur.h"
#include "../env/env.h"
#include<godot_cpp/classes/input.hpp>
#include<godot_cpp/core/class_db.hpp>
using namespace godot;

Dinosaur::Dinosaur() {}

Dinosaur::~Dinosaur() {}

void Dinosaur::_bind_methods() {}

void Dinosaur::_ready() {
    animated = Object::cast_to<AnimatedSprite2D>(get_node_internal("Animated"));
    dinoCollision = Object::cast_to<CollisionShape2D>(get_node_internal("CollisionShape2D"));
    animated->play();
}

void Dinosaur::_physics_process(double delta) {
    if(!isRunble || isRunble == 2) return;
    int isDown = false;
    Input& i = *Input::get_singleton();
    Vector2 vec = get_position();
    if(i.is_action_just_pressed("ui_up") && isUPdino) {
        isDown = true;
        vec.y -= 90;
        isUPdino = 0;
    }else if(i.is_action_just_pressed("ui_down") && !isUPdino) {
        isDown = true;
        vec.y += 90;
        isUPdino = 1;
    }

    if(isDown) ws->send_text("{ \"type\":\"move\", \"x\":"+String::num(vec.x)+", \"y\":"+String::num(vec.y)+", \"isUP\":"+String::num(isUPdino)+" }");

    set_position(vec);
}