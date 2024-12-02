#ifndef Dinosaur_h
#define Dinosaur_h
#include<godot_cpp/classes/character_body2d.hpp>
#include<godot_cpp/classes/animated_sprite2d.hpp>
namespace godot {
    class Dinosaur : public CharacterBody2D {
        GDCLASS(Dinosaur, CharacterBody2D);

        protected:
            static void _bind_methods();

        private:
            int isUP;
            AnimatedSprite2D* animated;

        public:
            Dinosaur();
            ~Dinosaur();

            void _physics_process(double delta) override;
            void _ready() override;
    };
}

#endif