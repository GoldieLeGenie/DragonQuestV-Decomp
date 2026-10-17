#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct ActionParam {
        enum ACTIONTYPE {
            ACTIONTYPE_NONE = 0,
            ACTIONTYPE_DAMAGE = 1,
            ACTIONTYPE_KAIFUKU = 2,
            ACTIONTYPE_SOKUSHI = 3,
            ACTIONTYPE_FUKKATSU = 4,
            ACTIONTYPE_MP_ADD = 5,
            ACTIONTYPE_MP_SUB = 6,
            ACTIONTYPE_ST_CLR = 7,
            ACTIONTYPE_NAKAMAYOBI = 8,
            ACTIONTYPE_PARTY_CHANGE = 9,
            ACTIONTYPE_SAKUSENHENKOU = 10,
            ACTIONTYPE_DISAPPEAR = 11,
            ACTIONTYPE_STR_PLUS = 12,
            ACTIONTYPE_SPD_PLUS = 13,
            ACTIONTYPE_DEF_PLUS = 14,
            ACTIONTYPE_INT_PLUS = 15,
            ACTIONTYPE_MAXHP_PLUS = 16,
            ACTIONTYPE_MAXMP_PLUS = 17,
            ACTIONTYPE_ASTORON = 18,
            ACTIONTYPE_MAHI = 19,
            ACTIONTYPE_NEMURI = 20,
            ACTIONTYPE_MANUSA = 21,
            ACTIONTYPE_BAIKIRUTO = 22,
            ACTIONTYPE_DF_HENKA = 23,
            ACTIONTYPE_BUKIMINAHIKARI = 24,
            ACTIONTYPE_FUBAHA = 25,
            ACTIONTYPE_MAHOKANTA = 26,
            ACTIONTYPE_MOSYASU = 27,
            ACTIONTYPE_TAMEKEI = 28,
            ACTIONTYPE_MAHOTON = 29,
            ACTIONTYPE_DORAGORAM = 30,
            ACTIONTYPE_KONRAN = 31,
            ACTIONTYPE_PATH_1 = 32,
            ACTIONTYPE_DOKU = 33,
            ACTIONTYPE_MOUDOKU = 34,
            ACTIONTYPE_CLOSEDOOR = 35,
            ACTIONTYPE_CURSE1 = 36,
            ACTIONTYPE_CURSE2 = 37,
            ACTIONTYPE_CURSE3 = 38,
            ACTIONTYPE_MAHOKITE = 39,
            ACTIONTYPE_DEFENCE = 40,
            ACTIONTYPE_FIZZLEZONE = 41,
            ACTIONTYPE_TIMESTOP = 42,
            ACTIONTYPE_TOHEROSU = 43,
            ACTIONTYPE_SINOBIASI = 44,
            ACTIONTYPE_CURSE4 = 45,
            ACTIONTYPE_CURSE5 = 46,
            ACTIONTYPE_NORMAL_MAMONONOESA = 47,
            ACTIONTYPE_MSG_ONLY = 48,
            ACTIONTYPE_MSG_SUCCESS = 49,
            ACTIONTYPE_MSG_FAILED = 50,
            ACTIONTYPE_MAX = 51,
        };
        enum DEFENCE {
            DEFENCE_MERA = 0,
            DEFENCE_GIRA = 1,
            DEFENCE_IO = 2,
            DEFENCE_HYADO = 3,
            DEFENCE_BAGI = 4,
            DEFENCE_DEIN = 5,
            DEFENCE_ZAKI = 6,
            DEFENCE_MEGANTE = 7,
            DEFENCE_NIFRAM = 8,
            DEFENCE_MANUSA = 9,
            DEFENCE_MEDAPANI = 10,
            DEFENCE_RARIHO = 11,
            DEFENCE_MAHOTOON = 12,
            DEFENCE_MAHOTORA = 13,
            DEFENCE_RUKANI = 14,
            DEFENCE_SUKARA = 15,
            DEFENCE_FIRE = 16,
            DEFENCE_BLIZZARD = 17,
            DEFENCE_POISON = 18,
            DEFENCE_VENOM = 19,
            DEFENCE_PARALYSIS = 20,
            DEFENCE_REST = 21,
            DEFENCE_ALL = 22,
            DEFENCE_HALF = 23,
            DEFENCE_SUCCESS_4TH = 24,
            DEFENCE_SUCCESS_6TH = 25,
            DEFENCE_SUCCESS_8TH = 26,
            DEFENCE_SUCCESS_3_4 = 27,
            DEFENCE_SUCCESS_3_8 = 28,
            DEFENCE_SUCCESS_5_8 = 29,
            DEFENCE_ENCOUNT = 30,
            DEFENCE_RARIHOMA = 31,
            DEFENCE_RUKANAN = 32,
            DEFENCE_MAX = 33,
        };
        enum DEFENCETYPE {
            DEFENCETYPE_TYPE_A = 0,
            DEFENCETYPE_TYPE_B = 1,
            DEFENCETYPE_TYPE_C = 2,
            DEFENCETYPE_TYPE_D = 3,
            DEFENCETYPE_TYPE_E = 4,
            DEFENCETYPE_TYPE_F = 5,
            DEFENCETYPE_TYPE_Z = 6,
            DEFENCETYPE_MAX = 7,
        };
        enum KIND {
            KIND_NONE = 0,
            KIND_BATTLE_MAGIC = 1,
            KIND_BATTLE_SKILL = 2,
            KIND_NORMAL_MAGIC = 3,
            KIND_NORMAL_SKILL = 4,
            KIND_ENEMY_ACTION = 5,
            KIND_BATTLE_ITEM = 6,
            KIND_NORMAL_ITEM = 7,
            KIND_COFUSE = 8,
            KIND_PARUPUNTE = 9,
            KIND_ADD_ACTION = 10,
            KIND_ADD_EFFECT = 11,
            KIND_MAX = 12,
        };
        enum DIRECT {
            DIRECT_NONE = 0,
            DIRECT_ME = 1,
            DIRECT_FRIEND = 2,
            DIRECT_ENEMY = 3,
            DIRECT_BOTH = 4,
            DIRECT_MAX = 5,
        };
        enum DEAD {
            DEAD_DEAD = 0,
            DEAD_ALIVE = 1,
            DEAD_MAX = 2,
        };

        unsigned long actionMes;                    // 0x00
        unsigned long playerSuccess;                // 0x04
        unsigned long monsterSuccess;               // 0x08
        unsigned long playerFailed;                 // 0x0C
        unsigned long monsterFailed;                // 0x10
        unsigned long endMes;                       // 0x14
        unsigned long menuMes;                      // 0x18
        unsigned short index;                       // 0x1C
        unsigned short effectFriend;                // 0x1E
        unsigned short effectEnemy;                 // 0x20
        unsigned short effectLap;                   // 0x22
        unsigned short MonsterMin;                  // 0x24
        unsigned short MonsterMax;                  // 0x26
        unsigned short PlayerMin;                   // 0x28
        unsigned short PlayerMax;                   // 0x2A
        unsigned short actionSE;                    // 0x2C
        unsigned short startSE;                     // 0x2E
        unsigned char type;                         // 0x30
        unsigned char magictype2;                   // 0x31
        unsigned char useMP;                        // 0x32
        unsigned char fool;                         // 0x33
        unsigned char human;                        // 0x34
        unsigned char god;                          // 0x35
        unsigned char typeID;                       // 0x36
        unsigned char magictype;                    // 0x37
        char byte_1;                                // 0x38
        char byte_2;                                // 0x39
        char byte_3;                                // 0x3A
        char byte_4;                                // 0x3B
        char byte_5;                                // 0x3C
        char byte_6;                                // 0x3D
        char byte_7;                                // 0x3E
        unsigned char dummy0;                       // 0x3F

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[32000];

        unsigned long getActionMes();
        unsigned long getPlayerSuccess();
        unsigned long getMonsterSuccess();
        unsigned long getPlayerFailed();
        unsigned long getMonsterFailed();
        unsigned long getEndMes();
        unsigned long getMenuMes();
        unsigned short getIndex();
        unsigned short getEffectFriend();
        unsigned short getEffectEnemy();
        unsigned short getEffectLap();
        unsigned short getMonsterMin();
        unsigned short getMonsterMax();
        unsigned short getPlayerMin();
        unsigned short getPlayerMax();
        unsigned short getActionSE();
        unsigned short getStartSE();
        unsigned char getType();
        unsigned char getMagictype2();
        unsigned char getUseMP();
        unsigned char getFool();
        unsigned char getHuman();
        unsigned char getGod();
        unsigned char getTypeID();
        unsigned char getMagictype();
        char getYaiba();
        char getFubaha();
        char getManusa();
        char getMikawasi();
        char getTikaratame();
        char getBaikiru();
        char getKaisin();
        char getSyuutyuu();
        char getAstron();
        char getMahokanta();
        char getMohokite();
        char getKaijo();
        char getTokusyu();
        char getMissA();
        char getMuchi();
        char getDMC();
        char getSaseru();
        char getFukusuu();
        char getHP();
        char getSeisi();
        char getMahotoon();
        char getBattleID();
        char getNormalID();
        char getDefencetype();
        char getDirect();
        char getRange();
        char getAI();
        char getDaibougyo();
        char getMane();
        char getDMD();
        char getOmake();
        char getMP();
        char getOmiyage();
        char getMosyasu();
        char getKakutou();
        char getEventBattle();
        char getDefencetypePlayer();
        static void setup();
        static void cleanup();
        static ActionParam* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
