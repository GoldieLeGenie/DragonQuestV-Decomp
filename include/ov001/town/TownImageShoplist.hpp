#pragma once
#include <globaldefs.h>
#include "main/window/ImageMap.hpp"
#include "main/dss/UnkSprite2D.hpp"

namespace twn
{
    struct TownImageShoplist : window::ImageMap {
        UnkMenuSprite shop_;                    // 0x04
        UnkMenuSprite black_;                   // 0x54
        int isEnable_;                          // 0xA4
        int frame_;                             // 0xA8
        int map2d_;                             // 0xAC

        TownImageShoplist();
        ~TownImageShoplist();
        void setup();
        virtual void cleanup();
        void execute();
        void checkData();
        void draw();
        virtual int isEnable();
        virtual void open();
        virtual void openBlack();
        virtual void close();
        virtual bool isOpen();
        virtual bool isClose();
    };

    extern TownImageShoplist gTownImageShoplist;
} // namespace twn
