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
    store1 = Object::cast_to<GameObject>(get_node_internal("../store1"));
    animated->play();
}

void Pteranodon::_physics_process(double delta) {
    if(isRunble || isRunble == 2) return;
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

    if(i.is_action_just_pressed("ui_select")) {
        Node* store_copy = store1->duplicate();
        Object::cast_to<Node2D>(get_node_internal("../../MainNode"))->add_child(store_copy);

        if(auto* store = Object::cast_to<GameObject>(store_copy)) {
            Vector2 vec = get_global_position();
            vec.x -= 100;
            vec.y += 100;
            store->set_global_position(vec);
            store->set_gravity_scale(1);
        }
    }

    if(isDown) ws->send_text("{ \"type\":\"move\", \"x\":"+String::num(vec.x)+", \"y\":"+String::num(vec.y)+" }");

    set_position(vec);
}