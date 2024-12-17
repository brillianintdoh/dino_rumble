#include "env.h"
JavaScriptBridge* js = nullptr;
GameObject* store1 = nullptr;
CollisionShape2D* dinoCollision = nullptr;
std::vector<TextureRect*> heart;
Ref<WebSocketPeer> ws;
int is_Web = false, isRunble = 2, isUPdino = 1;