#pragma once
#include <globaldefs.h>

namespace btl {
    struct BattleArray {
        static const int INDEX_ARRAY_MAX = 12;
        static const int INVALID_CODE = 0xFF;

        struct MonsterInfo {
            unsigned char count_;                   // 0x000
            unsigned char posCount_;                // 0x001
            unsigned char ctrlArray_[12];           // 0x002
            unsigned char indexArray_[12];          // 0x00E
            unsigned char groupArray_[12];          // 0x01A
            short monsterPosition_[12];             // 0x026
            char positionArray_[256];               // 0x03E
        };

        MonsterInfo monsterGround_;                 // 0x000
        MonsterInfo monsterAir_;                    // 0x13E
        MonsterInfo monsterAll_;                    // 0x27C

        BattleArray();
        ~BattleArray();
        void clear();
        void setup(int* monsterIndex, int* monsterCount);
        void setup();
        int getCtrlMonsterGround(int ctrl);
        int getCtrlMonsterAir(int ctrl);
        int getMonsterPositionGround(int ctrl);
        int getMonsterPositionAir(int ctrl);
        void add(const int ctrl, const int monsterGroup, const int monsterIndex);
        void del(int ctrl);
        bool isAdd(int monsterIndex);
        void changeCtrlId(int oldCtrl, int newCtrl);
        static int searchRightPosition(char* ar, int width);
        static int searchLeftPosition(char* ar, int width);
        static void putCtrlInArray(char* ar, int pos, int width, int ctrl);
    };
}
