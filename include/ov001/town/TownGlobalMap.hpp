#pragma once
#include <globaldefs.h>
#include "main/window/ImageMap.hpp"
#include "main/dss/UnkSprite2D.hpp"

namespace twn
{
    struct TownGlobalMap : window::ImageMap {
        UnkMenuSprite map_;                     // 0x004
        UnkMenuSprite point_[2];                // 0x054
        int isEnable_;                          // 0x0F4
        int unk_0f8;                            // 0x0F8
        int unk_0fc;                            // 0x0FC
        int frame_;                             // 0x100
        int map2d_;                             // 0x104

        TownGlobalMap();
        ~TownGlobalMap();
        static TownGlobalMap& getSingleton();
        void setup();
        virtual void cleanup();
        void execute();
        void draw();
        void setupPoint(int x, int y, int kind);
        void cleanupPoint();
        virtual int isEnable();
        virtual void open();
        virtual void close();
        virtual bool isOpen();
        virtual bool isClose();
    };
} // namespace twn
