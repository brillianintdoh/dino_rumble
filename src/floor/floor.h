#ifndef Floor_h
#define Floor_h
#include<godot_cpp/classes/area2d.hpp>
namespace godot {
    class Floor : public Area2D {
        GDCLASS(Floor, Area2D);

        protected:
            static void _bind_methods();

        private:
            int isUP;

        public:
            Floor();
            ~Floor();

            void onCollision(Node* body);

            void _ready() override;
            void _physics_process(double delta) override;
    };
}

#endif