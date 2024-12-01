#ifndef MainNode_h
#define MainNode_h
#include "../env/env.h"
#include "../pteranodon/pteranodon.h"
#include "../dinosaur/dinosaur.h"
#include<godot_cpp/classes/node2d.hpp>
#include<godot_cpp/classes/texture_rect.hpp>

namespace godot {
    class MainNode : public Node2D {
        GDCLASS(MainNode, Node2D);

        protected:
            static void _bind_methods();

        private:
            TextureRect* background;
            Pteranodon* pteranodon;
            Dinosaur* dinosaur;

        public:
            MainNode();
            ~MainNode();

            void webSocket();

            void _ready() override;
            void _process(double delta) override;
    };
}

#endif