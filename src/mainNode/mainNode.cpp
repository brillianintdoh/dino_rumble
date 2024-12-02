#include "mainNode.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/classes/os.hpp>
#include<godot_cpp/classes/json.hpp>
using namespace godot;

MainNode::MainNode() {
    ws.instantiate();
}

MainNode::~MainNode() {
    ws->close();
    ws.unref();
}

void MainNode::_bind_methods() {}

void MainNode::_ready() {
    background = Object::cast_to<TextureRect>(get_node_internal("background"));
    dinosaur = Object::cast_to<Dinosaur>(get_node_internal("dinosaur"));
    pteranodon = Object::cast_to<Pteranodon>(get_node_internal("Pteranodon"));
    js = JavaScriptBridge::get_singleton();
    is_Web = OS::get_singleton()->get_name() == "Web";

    if(is_Web) {
        ws->connect_to_url("wss://game.ourgram.co.kr/ws");
    }
}

void MainNode::webSocket() {
    if(!is_Web) return;
    ws->poll();

    if(ws->get_ready_state() == WebSocketPeer::STATE_OPEN) {
        if(ws->get_available_packet_count() > 0) {
            String packet = ws->get_packet().get_string_from_utf8();
            Variant json = JSON::parse_string(packet);
            Variant type = json.get("type");
            if(type == "okLink") {
                isRunble = json.get("p1");
                js->eval("loadOk()");
            }else if(type == "move") {
                if(isRunble) {
                    Vector2 vec = pteranodon->get_position();
                    vec.x = json.get("x");
                    vec.y = json.get("y");
                    pteranodon->set_position(vec);
                }else {
                    Vector2 vec = dinosaur->get_position();
                    vec.x = json.get("x");
                    vec.y = json.get("y");
                    dinosaur->set_position(vec);
                }
            }
        }
    }
}

void MainNode::_process(double delta) {
    Vector2 vec = background->get_position();
    vec.x -= 2;
    if(vec.x >= -2550) {
        background->set_position(vec);
    }else {
        background->set_position(Vector2(-300,0));
    }

    webSocket();
}