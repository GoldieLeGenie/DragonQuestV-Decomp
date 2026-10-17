#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"

// one entry per excel table: how the table is loaded
struct ExcelBinaryInfo {
    int uic_;                                   // 0x0
};

namespace dq5 {
namespace level {
    struct EncountSeaTile1 {
        unsigned char* tile_;                   // 0x0

        static const int ID_;
        static const unsigned int width_;
        static const unsigned int height_;
        static DataObject data_;

        unsigned char getTile(unsigned int x, unsigned int y);
    };
    struct EncountSeaTile2 {
        unsigned char* tile_;                   // 0x0

        static const int ID_;
        static const unsigned int width_;
        static const unsigned int height_;
        static DataObject data_;

        unsigned char getTile(unsigned int x, unsigned int y);
    };
    struct EncountTile1 {
        unsigned char* tile_;                   // 0x0

        static const int ID_;
        static const unsigned int width_;
        static const unsigned int height_;
        static DataObject data_;

        unsigned char getTile(unsigned int x, unsigned int y);
    };
    struct EncountTile2 {
        unsigned char* tile_;                   // 0x0

        static const int ID_;
        static const unsigned int width_;
        static const unsigned int height_;
        static DataObject data_;

        unsigned char getTile(unsigned int x, unsigned int y);
    };
    struct EncountTile3 {
        unsigned char* tile_;                   // 0x0

        static const int ID_;
        static const unsigned int width_;
        static const unsigned int height_;
        static DataObject data_;

        unsigned char getTile(unsigned int x, unsigned int y);
    };
    struct EncountFairyTile {
        unsigned char* tile_;                   // 0x0

        static const int ID_;
        static const unsigned int width_;
        static const unsigned int height_;
        static DataObject data_;

        unsigned char getTile(unsigned int x, unsigned int y);
    };
    struct EncountDarkTile {
        unsigned char* tile_;                   // 0x0

        static const int ID_;
        static const unsigned int width_;
        static const unsigned int height_;
        static DataObject data_;

        unsigned char getTile(unsigned int x, unsigned int y);
    };

    struct LevelData {
        DataObject info_;                       // 0x00
        EncountSeaTile1 encountSeaTile1_;       // 0x10
        EncountSeaTile2 encountSeaTile2_;       // 0x14
        EncountTile1 encountTile1_;             // 0x18
        EncountTile2 encountTile2_;             // 0x1C
        EncountTile3 encountTile3_;             // 0x20
        EncountFairyTile encountFairyTile_;     // 0x24
        EncountDarkTile encountDarkTile_;       // 0x28

        LevelData();
        ~LevelData();
        void setup();
        int getLoadType(int index);
        void setupBattle();
        void cleanupBattle();
        void setupField();
        void cleanupField();
        void setupTown();
        void cleanupTown();
    };

    extern LevelData levelData;

    extern const unsigned char EncountTile1_array[260];
    extern const unsigned char EncountTile2_array[260];
    extern const unsigned char EncountTile3_array[260];
    extern const unsigned char EncountSeaTile1_array[260];
    extern const unsigned char EncountSeaTile2_array[260];
    extern const unsigned char EncountDarkTile_array[20];
    extern const unsigned char EncountFairyTile_array[20];
}
}
