#pragma once
#include <globaldefs.h>
#include "main/dss/Render.hpp"
#include "main/dss/Sprite2D.hpp"

namespace book
{
    // monster book part: camera, monster and the encyclopedia background
    struct BookSystem {
        Render render_;                         // 0x000
        UnkMenuSprite sprite_;                  // 0x608
        int monsterNo_;                         // 0x658

        BookSystem();
        ~BookSystem();
        static BookSystem& getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
    };
} // namespace book
