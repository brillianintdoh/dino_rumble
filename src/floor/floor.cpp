#include "floor.h"
#include "../env/env.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/variant/utility_functions.hpp>
#include<godot_cpp/classes/input.hpp>
using namespace godot;

Floor::Floor() {
    isUP = 1;
}

Floor::~Floor() {}

void Floor::_bind_methods() {
    ClassDB::bind_method(D_METHOD("onCollision", "body"), &Floor::onCollision);
}

void Floor::_ready() {
    connect("body_entered", Callable(this , "onCollision"));
}

void Floor::onCollision(Node* body) {
    std::cout << body->get_name().to_utf8_buffer().get_string_from_utf8().utf8().get_data() << std::endl;
}

void Floor::_physics_process(double delta) {
    if(isRunble == 2) return;

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