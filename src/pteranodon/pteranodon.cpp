#include "pteranodon.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/classes/input.hpp>
using namespace godot;

Pteranodon::Pteranodon() {
    isUP = 0;
    cooling_time = 0;  
}

Pteranodon::~Pteranodon() {}

void Pteranodon::_bind_methods() {}

void Pteranodon::_ready() {
    animated = Object::cast_to<AnimatedSprite2D>(get_node_internal("Animated"));
    animated->play();
}

void Pteranodon::_physics_process(double delta) {
    if(isRunble || isRunble == 2 || gameOver) return;
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
    if(cooling_time != 0) {
        cooling_time += delta;
        if(cooling_time >= 1.5) cooling_time = 0;
    }

    if(i.is_action_just_pressed("ui_select") && cooling_time == 0) {
        cooling_time += delta;
        Node* store_copy = store1->duplicate();
        Object::cast_to<Node2D>(get_node_internal("../../MainNode"))->add_child(store_copy);

        if(auto* store = Object::cast_to<GameObject>(store_copy)) {
            Vector2 vec = get_global_position();
            vec.x -= 100;
            vec.y += 100;
            store->set_global_position(vec);
            if(isUP) store->set_z_index(2);
            else store->set_z_index(3);
            store->set_gravity_scale(1);
            ws->send_text("{ \"type\":\"o1_create\", \"isUP\": "+String::num(isUP)+" }");
        }
    }

    set_position(vec);
}