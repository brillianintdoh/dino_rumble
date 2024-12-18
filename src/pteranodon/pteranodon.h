#ifndef Pteranodon_H
#define Pteranodon_H
#include "../env/env.h"
#include<godot_cpp/classes/character_body2d.hpp>
#include<godot_cpp/classes/animated_sprite2d.hpp>
namespace godot {
    class Pteranodon : public CharacterBody2D {
        GDCLASS(Pteranodon, CharacterBody2D);

        protected:
            static void _bind_methods();

        private:
            AnimatedSprite2D* animated;
            int isUP;
            double cooling_time;

        public:
            Pteranodon();
            ~Pteranodon();

            void _physics_process(double delta) override;
            void _ready() override;
    };
}

#endif