#pragma once
#include <globaldefs.h>

namespace btl
{
    struct EncountTile {
        int chapter_;                           // 0x00
        int tileId_;                            // 0x04

        EncountTile();
        ~EncountTile();
        void setupDungeon(int chapter, int floorIndex);
        void setupField(int chapter, int type, int land, int x, int y);
        int getTileId() const;
        static int getTileId(int chapter, int floorIndex);
        static int getTileIdFieldOnYounenki(int x, int y);
        static int getTileIdFieldOnSeinenki(int x, int y);
        static int getTileIdFieldOnSounenki(int x, int y);
        static int getTileIdSeaOnSeinenki(int x, int y);
        static int getTileIdSeaOnSounenki(int x, int y);
        static int getTileIdFairy(int x, int y);
        static int getTileIdDark(int x, int y);
    };
} // namespace btl
