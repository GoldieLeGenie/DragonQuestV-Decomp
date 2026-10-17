#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkSprite2D.hpp"
#include "main/script/ScriptBaseCommand.hpp"
#include "ov005/fld/FieldSymbolAnimation.hpp"

struct PARAM_FIELD_PARTY_MOVE2_FORMATION {
    unsigned int frmDir;
    unsigned int charaDir;
};

struct PARAM_FIELD_TRRIGER {
    int startX;
    int startY;
    int endX;
    int endY;
    unsigned int flag;
};

struct PARAM_DRAW_GOLD_ORB {
    unsigned int endY;
    int speed;
    unsigned int high;
};

struct PARAM_FIELD_GET_DOWN_SHIP {
    unsigned int direction;
};

struct PARAM_FIELD_MOVE_LINE {
    unsigned int direction;
    int target;
};

struct PARAM_FIELD_PLAYER_MOVE_TO {
    int endX;
    int endY;
    int endZ;
    int rate;
    unsigned int absFlag;
};

struct PARAM_SET_FIELD_PLAYER_POS {
    int posX;
    int posY;
    int posZ;
};

struct FieldGetDownShip : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FieldPlayerMoveTo : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FieldMoveLine : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FieldSymbolAnim : ScriptCommand {
    fld::FieldSymbolAnimation anim_;    // 0x04

    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FieldGoldOrbEvent : ScriptCommand {
    dss::Fix32 orbPosX_;                // 0x04
    dss::Fix32 orbPosY_;                // 0x08
    dss::Fix32 orbSpeed_;               // 0x0C
    int orbEndPosY_;                    // 0x10
    UnkMenuSprite unk_14;               // 0x14 orb
    UnkMenuSprite unk_64;               // 0x64 orb glow

    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

bool cmd_field_player_set_ship(void* scriptParam);
bool cmd_set_field_player_pos(void* scriptParam);
bool cmd_field_trriger(void* scriptParam);
bool cmd_field_set_formation(void* scriptParam);

extern FieldPlayerMoveTo gFieldPlayerMoveTo;
extern FieldMoveLine gFieldMoveLine;
extern FieldGetDownShip gFieldGetDownShip;
extern FieldSymbolAnim gFieldSymbolAnim;
extern FieldGoldOrbEvent gFieldGoldOrbEvent;
