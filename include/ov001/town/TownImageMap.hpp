#pragma once
#include <globaldefs.h>
#include "main/window/ImageMap.hpp"
#include "main/dss/Sprite2D.hpp"
#include "main/dss/Camera.hpp"

namespace twn
{
    struct TownImageMap : window::ImageMap {
        dss::Vector2<int> targetPos_;           // 0x004
        UnkMenuSprite map_;                     // 0x00C
        UnkMenuSprite point_;                   // 0x05C
        UnkMenuSprite black_;                   // 0x0AC
        char fileName_[0x80];                   // 0x0FC
        dss::Camera camera_;                    // 0x17C
        dss::Fix32Vector3 playerPos_;           // 0x1EC
        int isEnable_;                          // 0x1F8
        int frame_;                             // 0x1FC
        int map2d_;                             // 0x200
        int m_index;                            // 0x204

        TownImageMap();
        ~TownImageMap();
        void setup();
        virtual void cleanup();
        void execute();
        void exitFloor();
        void checkData();
        void draw();
        virtual int isEnable();
        virtual void open();
        virtual void close();
        virtual void closeBlack();
        virtual bool isOpen();
        virtual bool isClose();
        void calcTargetPos();
        void getTargetPos();
        void setOverview();
    };

    extern TownImageMap imageMap;
} // namespace twn
