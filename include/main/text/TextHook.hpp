#pragma once
#include "globaldefs.h"
#include "GameInfo.hpp"
#include "main/text/TextAPI.hpp"

struct UnkTextHookBase {
    virtual int extractDefaultText(char* text, int size, int id, int param) = 0;
    virtual int getMacroStat(int id, int param) = 0;
};

struct TextHook : UnkTextHookBase {
    static const int EQUIPABLE_PC_MAXCOUNT = 10;

    virtual int extractDefaultText(char* text, int size, int id, int param);
    virtual int getMacroStat(int id, int param);

    int equipable_pc_list_[EQUIPABLE_PC_MAXCOUNT]; /* 0x04 */
    int equipable_pc_count_;                    /* 0x2C */
    const char* equipable_pc_delimiter1_;       /* 0x30 */
    const char* equipable_pc_delimiter2_;       /* 0x34 */
    int humanPC_;                               /* 0x38 */
    int humanNPC_;                              /* 0x3C */
    int monsterPC_;                             /* 0x40 */
    int deadleadpc_;                            /* 0x44 */
    int deadleader_;                            /* 0x48 */
    int topchar_;                               /* 0x4C */
    int leader_;                                /* 0x50 */
    int leaderpc_;                              /* 0x54 */
    int mostheroic_;                            /* 0x58 */
    int sister_;                                /* 0x5C */
    int male_;                                  /* 0x60 */
    int female_;                                /* 0x64 */
    int monster_;                               /* 0x68 */
    int corpse_;                                /* 0x6C */
    Sex leaderSex_;                             /* 0x70 */
    Sex leadPcSex_;                             /* 0x74 */
    int raceResultA_;                           /* 0x78 */
    int raceResultB_;                           /* 0x7C */

    int extractDefaultTextTest(char* text, int size, int id, int param);
    int extractDefaultTextString(char* text, int size, int id, int param);
    int extractDefaultTextNumber(char* text, int size, int id, int param);
    void resetEQUIPABLE_PC();
    void setEQUIPABLE_PC(int playerIndex);
    void checkPlayer();
    void extractParty(char* text, int size, int value);
    void extractNumber(char* text, int size, int value);
};

struct UserExtractWordHook : UnkTextExtractorHook {
    virtual int extract(char* dst, int size, int type, int no);
    static int getOriginalWordSEX(int playerIndex);
};

extern UserExtractWordHook data_020ef2e0;

extern TextHook gTextHook;
