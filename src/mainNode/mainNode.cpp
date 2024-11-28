#include "mainNode.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/classes/os.hpp>
using namespace godot;

MainNode::MainNode() {
}

MainNode::~MainNode() {
}

void MainNode::_bind_methods() {}

void MainNode::_ready() {
    background = Object::cast_to<TextureRect>(get_node_internal("background"));
    js = JavaScriptBridge::get_singleton();
    is_Web = OS::get_singleton()->get_name() == "Web";

    if(is_Web) {
        js->get_interface("console")->call("log", "wow sans");
    }
}

void MainNode::_process(double delta) {
    Vector2 vec = background->get_position();
    vec.x -= 2;
    if(vec.x >= -2250) {
        background->set_position(vec);
    }else {
        background->set_position(Vector2(0,0));
    }
}