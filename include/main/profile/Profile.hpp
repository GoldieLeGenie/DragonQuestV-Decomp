#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace status {
    struct GameFlag;
}

namespace profile {
    enum SAVETYPE {
        SAVETYPE_NONE = 0,
        SAVETYPE_CHURCH = 1,
        SAVETYPE_INTERVAL = 2,
        SAVETYPE_RESUME = 3,
        SAVETYPE_NEW = 4,
        SAVETYPE_INVALID = 255,
    };

    struct PROFILE_SYSTEM {
        unsigned int MAGIC;                     // 0x00
        unsigned int VER;                       // 0x04
        unsigned int CHECKSUM;                  // 0x08
        unsigned int UNIQUEID;                  // 0x0C
        unsigned char BOOKNO;                   // 0x10
        unsigned char SAVETYPE;                 // 0x11
        unsigned char CLEAR;                    // 0x12
        unsigned char padPosSize;               // 0x13
    };

    struct PROFILE_ASSETS {
        unsigned int HAVING_GOLD;               // 0x000
        unsigned int BANK_GOLD;                 // 0x004
        unsigned int CASINO_TOKEN;              // 0x008
        unsigned int HAVING_MEDAL;              // 0x00C
        unsigned int KINGS_MEDAL;               // 0x010
        unsigned int BASHA;                     // 0x014
        unsigned int SHIP;                      // 0x018
        unsigned int TENKUUJYO;                 // 0x01C
        unsigned short SACKITEM[263];           // 0x020
        unsigned char SACKCOUNT[263];           // 0x22E
        unsigned short ALL_MEMBER[10];          // 0x336
        unsigned int ALL_MEMBER_FLAG[10];       // 0x34C
        int OUTSIDE_MEMBER[4];                  // 0x374
        int INSIDE_MEMBER[7];                   // 0x384
        int BACKSIDE_MEMBER[2];                 // 0x3A0
        unsigned short BACKSIDE_MEMBER_CHARINDEX[2];    // 0x3A8
        unsigned short MEISAN[26];              // 0x3AC
        unsigned char SACKNAME[26];             // 0x3E0
        int CURSED_SACKNAME;                    // 0x3FC
        unsigned char __reserve[28];            // 0x400
    };

    struct PROFILE_PLAYER {
        unsigned int EXP;                       // 0x00
        unsigned short HP;                      // 0x04
        unsigned short HPMAX;                   // 0x06
        unsigned short MP;                      // 0x08
        unsigned short MPMAX;                   // 0x0A
        unsigned short PDA_INDEX;               // 0x0C
        unsigned short HAVEITEM[12];            // 0x0E
        unsigned char PDA_FLAG;                 // 0x26
        unsigned char INDEX;                    // 0x27
        unsigned char NAME[18];                 // 0x28
        unsigned char TACTICS;                  // 0x3A
        unsigned char STATFLAG;                 // 0x3B
        unsigned char STRENGTH;                 // 0x3C
        unsigned char PROTECTION;               // 0x3D
        unsigned char AGILITY;                  // 0x3E
        unsigned char WISDAM;                   // 0x3F
        unsigned char LUCK;                     // 0x40
        unsigned char LEVEL;                    // 0x41
        unsigned char CURSED_NAME;              // 0x42
    };

    struct PROFILE_LOCATION {
        unsigned short PARTY_D;                 // 0x00
        unsigned int PARTY_X;                   // 0x04
        unsigned int PARTY_Y;                   // 0x08
        unsigned int PARTY_Z;                   // 0x0C
        unsigned int SHIP_X;                    // 0x10
        unsigned int SHIP_Y;                    // 0x14
        unsigned int SHIP_Z;                    // 0x18
        short SHIP_D;                           // 0x1C
        short SHIP_ID;                          // 0x1E
        unsigned int RAFT_X;                    // 0x20
        unsigned int RAFT_Y;                    // 0x24
        unsigned int RAFT_Z;                    // 0x28
        int RAFT_ID;                            // 0x2C
        unsigned int RIDEON_TYPE;               // 0x30
        int SHIP_NO;                            // 0x34
        unsigned int BALLOON_X;                 // 0x38
        unsigned int BALLOON_Y;                 // 0x3C
        unsigned int BALLOON_Z;                 // 0x40
        unsigned int OVERVIEW_X;                // 0x44
        unsigned int OVERVIEW_Y;                // 0x48
        unsigned int OVERVIEW_Z;                // 0x4C
        unsigned char RESTART[16];              // 0x50
        unsigned char CHURCH[16];               // 0x60
        unsigned char FIELDTYPE;                // 0x70
        int STAGE_INFO_LOCATION_SHIP1[3];       // 0x74
        int STAGE_INFO_LOCATION_SHIP2[3];       // 0x80
        int STAGE_INFO_LOCATION_TENKUUJYO[3];   // 0x8C
        int STAGE_INFO_LOCATION_MINIMAP1[3];    // 0x98
        int STAGE_INFO_LOCATION_MINIMAP2[3];    // 0xA4
        int RETURN_CHURCH;                      // 0xB0
        int LOAD_CHURCH;                        // 0xB4
        unsigned char PLATE_MOVE[9];            // 0xB8
        int RIREMITO_SYMBOL_ID;                 // 0xC4
        int RIREMITO_MAP;                       // 0xC8
        int LAST_FIELD_LINK_SURFACE;            // 0xCC
        int LAST_RANARUTA_STAGE_ID;             // 0xD0
        int KIMERA_SYMBOL;                      // 0xD4
        int FIELD_CHANGE;                       // 0xD8
        unsigned int TROKKO_SWITCHDATA;         // 0xDC
        unsigned int TROKKO_SWITCHINIT;         // 0xE0
        unsigned int TROKKO_WAGON1DATA;         // 0xE4
        unsigned int TROKKO_WAGON2DATA;         // 0xE8
        unsigned char __reserve[16];            // 0xEC
    };

    struct PROFILE_PARTY {
        unsigned char OPTION_SACK_SORT;         // 0x000
        unsigned char OPTION_BGM_VOLUME;        // 0x001
        unsigned char OPTION_SEVOLUME;          // 0x002
        unsigned char OPTION_BATTLE_SPEED;      // 0x003
        unsigned char GLOBALFLAG[128];          // 0x004
        unsigned char AREAFLAG[128];            // 0x084
        unsigned int STORY_FLAG;                // 0x104
        unsigned char STORY_CHAPTER_NO;         // 0x108
        short STORY_HEROEQUIP[9];               // 0x10A
        unsigned int PLAY_TIME;                 // 0x11C
        unsigned short WORLD_TIME;              // 0x120
        unsigned char TIME_ZONE;                // 0x122
        unsigned char TIME_STOP;                // 0x123
        unsigned char MAPSYMBOL_FLAG[16];       // 0x124
        unsigned short MAPVEIL_FLAG[16];        // 0x134
        unsigned char FURN_FLAG[128];           // 0x154
        unsigned char DOOR_FLAG[32];            // 0x1D4
        unsigned char BREAK_FLAG[32];           // 0x1F4
        int ROCK_VX[10];                        // 0x214
        int ROCK_VY[10];                        // 0x23C
        int ROCK_VZ[10];                        // 0x264
        unsigned char unk_28C[16];              // 0x28C
        unsigned char DAY_COUNTER[8];           // 0x29C
        unsigned char unk_2A4[48];              // 0x2A4
        unsigned char SELECTTAISHI_FLAG[64];    // 0x2D4
        int TOUCH_SCORE[10];                    // 0x314
        unsigned char TOUCH_STAGE[10];          // 0x33C
        unsigned short INFO_TOHEROS;            // 0x346
        unsigned short INFO_SINOBIASI;          // 0x348
        unsigned short INFO_MONSTERSFOOD;       // 0x34A
        unsigned short ATTR_TORAMANA;           // 0x34C
        unsigned short RULA_LEVEL;              // 0x34E
        unsigned short PARUPUNTE_LEVEL;         // 0x350
        unsigned short NO_ENCOUNT_FLAG;         // 0x352
        unsigned char NAME_INDEX[88];           // 0x354
        unsigned char unk_3AC[12];              // 0x3AC
    };

    struct PROFILE_MONSTER {
        unsigned short KILL;                    // 0x0
        unsigned short ITEMCOUNT;               // 0x2
        unsigned char LEVEL;                    // 0x4
        bool ENCOUNT;                           // 0x5
    };

    struct UnkProfileTaishi {
        int IS_TAISHI;                          // 0x00
        unsigned int UNIQUEID;                  // 0x04
        unsigned int PRICE;                     // 0x08
        unsigned char OBJECTID;                 // 0x0C
        unsigned char PRODUCTION;               // 0x0D
        char NAME[28];                          // 0x0E
        char PRODUCER[26];                      // 0x2A
        char MESSAGE[136];                      // 0x44
    };

    struct PROFILE_RECORD {
        PROFILE_SYSTEM system[1];               // 0x0000
        PROFILE_ASSETS assets[1];               // 0x0014
        PROFILE_PLAYER player[97];              // 0x0430
        PROFILE_LOCATION location[1];           // 0x1DF4
        PROFILE_PARTY party[1];                 // 0x1EF0
        PROFILE_MONSTER monster[202];           // 0x22A8
        UnkProfileTaishi taishi[25];              // 0x2764
    };

    struct Profile {
        PROFILE_SYSTEM* pSYSTEM;                // 0x0000
        PROFILE_ASSETS* pASSETS;                // 0x0004
        PROFILE_PLAYER* pPLAYER;                // 0x0008
        PROFILE_LOCATION* pLOCATION;            // 0x000C
        PROFILE_PARTY* pPARTY;                  // 0x0010
        PROFILE_MONSTER* pMONSTER;              // 0x0014
        UnkProfileTaishi* pTAISHI;                // 0x0018
        PROFILE_RECORD profiledata_;            // 0x001C
        unsigned char profiledummy_[176];       // 0x3B6C

        void setup();
        void collectGameFlag(unsigned char* WRITE, status::GameFlag* flag);
        void deliverGameFlag(status::GameFlag* flag, unsigned char* WRITE);
        bool calcCheckSum();
        bool isValidData();
        void nameCopy(unsigned char* dst, int size, unsigned char* src);
        void collectFx32Vector3(int* prof, dss::Fix32Vector3* vec);
        void deliverFx32Vector3(dss::Fix32Vector3* vec, int* prof);
        bool collectProfile(int no, int type);
        void collect_PROFILE_MONSTER();
        void unkfunc_0203fb84();
        void collect_PROFILE_SYSTEM(int no, int type);
        void collect_PROFILE_PARTY();
        void collect_PROFILE_ASSETS();
        void collect_PROFILE_PLAYER();
        void collect_PROFILE_LOCATION();
        bool deliverProfile(int no);
        void deliver_PROFILE_MONSTER();
        void unkfunc_0204058c();
        void deliverRESTART_MAP(dss::Fix32Vector3& pos, short dir);
        void deliver_PROFILE_SYSTEM();
        void deliver_PROFILE_PARTY();
        void deliver_PROFILE_ASSETS();
        void deliver_PROFILE_PLAYER();
        void deliver_PROFILE_LOCATION();
    };
}
