#pragma once
#include <globaldefs.h>
#include "main/window/ImageMap.hpp"
#include "ov005/fld/FieldSmallMap.hpp"
#include "ov005/fld/FieldYamiMap.hpp"
#include "ov005/fld/FieldFairyMap.hpp"

namespace fld
{
    struct FieldLargeMap {
        Render* render_;                        // 0x00
        UnkMenuSprite unk_04;                   // 0x04
        UnkMenuSprite unk_54;                   // 0x54
        int unk_a4;                             // 0xA4 player marker x
        int unk_a8;                             // 0xA8 player marker y

        FieldLargeMap();
        ~FieldLargeMap();
        void setup(Render* render);  // load
        void cleanup();                // cleanup
        void setupSprites();                // setup the sprites
        int loadEventBlock(int x, int y, void* buffer);   // load the map piece changed by the story
        void buildMapTexture(int x, int y);    // build the map texture around the block x, y
        void buildPlayerMap();                // build the map around the player
        void setAlpha(unsigned char alpha);
        void updatePlayerMarker();                // update the player marker
    };

    struct FieldImageMap : window::ImageMap {
        Render* render_;                        // 0x004
        FieldLargeMap largeMap_;                // 0x008
        FieldSmallMap smallMap_;                // 0x0B4
        FieldYamiMap darkMap_;                  // 0x1FC
        FieldFairyMap fairyMap_;                // 0x2F8
        window::WorldMap* worldMap_;            // 0x3F4
        int frame_;                             // 0x3F8
        int map2d_;                             // 0x3FC

        FieldImageMap();
        ~FieldImageMap();
        void setup(Render* render);
        virtual void open();
        virtual void close();
        virtual bool isOpen();
        virtual bool isClose();
        virtual void cleanup();
        void execute();
        void draw();
        void reload();
        void closeLargeMap();
        void closeSmallMap();
    };
} // namespace fld
