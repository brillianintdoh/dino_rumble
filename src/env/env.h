#ifndef Env_H
#define Env_H
#include "../gameObject/gameObject.h"
#include<godot_cpp/classes/java_script_bridge.hpp>
#include<godot_cpp/classes/web_socket_peer.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
#include<godot_cpp/classes/collision_shape2d.hpp>
using namespace godot;

extern JavaScriptBridge* js;
extern std::vector<TextureRect*> heart;
extern GameObject* store1;
extern Ref<WebSocketPeer> ws;
extern CollisionShape2D* dinoCollision;
extern int is_Web, isRunble, isUPdino;

#endif