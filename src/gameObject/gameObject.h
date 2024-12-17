#ifndef Floor_h
#define Floor_h
#include<godot_cpp/classes/rigid_body2d.hpp>
namespace godot {
    class GameObject : public RigidBody2D {
        GDCLASS(GameObject, RigidBody2D);

        protected:
            static void _bind_methods();

        public:
            GameObject();
            ~GameObject();

            void onCollision(Node* body);

            void _ready() override;
            void _physics_process(double delta) override;
    };
}

#endif