#include "mainNode.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/classes/os.hpp>
#include<godot_cpp/classes/json.hpp>
using namespace godot;

MainNode::MainNode() {
    store = nullptr;
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
    store1 = Object::cast_to<GameObject>(get_node_internal("store1"));
    js = JavaScriptBridge::get_singleton();
    is_Web = OS::get_singleton()->get_name() == "Web";

    for(int i=1; i <= 3; i++) {
        heart.push_back(Object::cast_to<TextureRect>(get_node_internal("camera/heart"+String::num(i))));
    }

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
                String player = isRunble ? "true" : "false";
                js->eval("setPlayer("+player+")");
                js->eval("loadOk()");
            }else if(type == "move") {
                if(isRunble) {
                    pteranodon->set_position(Vector2(json.get("x"), json.get("y")));
                }else {
                    dinosaur->set_position(Vector2(json.get("x"), json.get("y")));
                    isUPdino = json.get("isUP");
                }
            }else if(type == "o1_create") {
                Node* store_copy = store1->duplicate();
                add_child(store_copy);

                store = Object::cast_to<GameObject>(store_copy);
                Vector2 vec = pteranodon->get_global_position();
                vec.x -= 100;
                vec.y += 100;
                store->set_global_position(vec);
                if(json.get("isUP")) store->set_z_index(2);
                else store->set_z_index(3);
            }else if(type == "o1_delete") {
                store->queue_free();
                store = nullptr;
            }else if(type == "o1" && store != nullptr) {
                store->set_position(Vector2(json.get("x"), json.get("y")));
            }else if(type == "heart") {
                heart.back()->queue_free();
                heart.pop_back();
            }else if(type == "gameOver") {
                gameOver = true;
                String over = isRunble ? "true" : "false";
                js->eval("gameOver("+over+")");
            }
        }
    }else if (ws->get_ready_state() == WebSocketPeer::STATE_CLOSED || ws->get_ready_state() == WebSocketPeer::STATE_CLOSING) {
        printf("연결 끊김 재연결 시도중..\n");
        ws->connect_to_url("wss://game.ourgram.co.kr/ws");
    }
}

void MainNode::_process(double delta) {
    if(gameOver) return;
    Vector2 vec = background->get_position();
    vec.x -= 2;
    if(vec.x >= -2550) {
        background->set_position(vec);
    }else {
        background->set_position(Vector2(-300,0));
    }

    time+=delta;
    js->eval("setTime("+String::num(time)+")");
    webSocket();
}