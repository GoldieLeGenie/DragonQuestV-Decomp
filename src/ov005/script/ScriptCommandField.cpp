#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

// The original TU also emitted ScriptCommand's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "ov005/script/ScriptCommandField.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/dss/RenderObject.hpp"
#include "ov005/fld/FieldActionCalculate.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline void ScriptCommandWeakVtable::initialize(char* scriptParam)
{
}

inline int ScriptCommandWeakVtable::isEnd()
{
    return 0;
}

inline void fld::FieldPlayerManager::setShipPos(int index, dss::Fix32Vector3& pos)
{
    shipDraw_[index].setPosition(pos);
}

inline cmn::PlayerManager* cmn::GameManager::getPlayerManager()
{
    return playerManager_;
}

inline void FieldGetDownShip::execute()
{
}

inline void FieldGetDownShip::terminate()
{
}

inline void FieldPlayerMoveTo::execute()
{
}

inline void FieldPlayerMoveTo::terminate()
{
}

inline void FieldMoveLine::execute()
{
}

inline void FieldMoveLine::terminate()
{
}

inline void FieldSymbolAnim::terminate()
{
}

inline void FieldGoldOrbEvent::terminate()
{
}

THUMB bool cmd_field_player_set_ship(void* scriptParam)
{
    dss::Fix32Vector3 pos = fld::FieldPlayerManager::getSingleton().getPosition();
    fld::FieldPlayerManager::getSingleton().player_.setMoveType(1);
    fld::FieldPlayerManager::getSingleton().setShipPos(1, pos);
    fld::FieldPlayerManager::getSingleton().partyDraw_.setDrawNone();
    fld::FieldPlayerManager::getSingleton().shipDraw_[1].ride_ = 1;
    fld::FieldStage::getSingleton()->scriptShip_ = 1;
    cmn::g_cmnPartyInfo.rideOnType_ = cmn::RIDE_ON_SHIP_IKADA;
    return true;
}

THUMB bool cmd_set_field_player_pos(void* scriptParam)
{
    PARAM_SET_FIELD_PLAYER_POS* param = (PARAM_SET_FIELD_PLAYER_POS*)scriptParam;
    dss::Fix32Vector3 pos = cmn::CommonCalculate::setVecByParam(param->posX, param->posY, param->posZ);
    fld::FieldPlayerManager::getSingleton().setPosition(pos);
    fld::FieldPlayerManager::getSingleton().party_.setAllPlayerAtFirst();
    return true;
}

THUMB void FieldPlayerMoveTo::initialize(char* scriptParam)
{
    PARAM_FIELD_PLAYER_MOVE_TO* param = (PARAM_FIELD_PLAYER_MOVE_TO*)scriptParam;
    dss::Fix32Vector3 target;
    target.vx.value = param->endX;
    target.vy.value = param->endY;
    target.vz.value = param->endZ;
    dss::Fix32 rate;
    rate.value = param->rate;
    fld::FieldPlayerManager::getSingleton().setSimpleMove(target, rate, param->absFlag);
}

THUMB int FieldPlayerMoveTo::isEnd()
{
    return fld::FieldPlayerManager::getSingleton().scriptMoveFlag_ == 0;
}

FieldPlayerMoveTo gFieldPlayerMoveTo;

THUMB void FieldMoveLine::initialize(char* scriptParam)
{
    PARAM_FIELD_MOVE_LINE* param = (PARAM_FIELD_MOVE_LINE*)scriptParam;
    dss::Fix32 target;
    target.value = param->target;
    fld::FieldPlayerManager::getSingleton().setDirectionMove(target, param->direction);
}

THUMB int FieldMoveLine::isEnd()
{
    return fld::FieldPlayerManager::getSingleton().scriptMoveFlag_ == 0;
}

FieldMoveLine gFieldMoveLine;

THUMB void FieldGetDownShip::initialize(char* scriptParam)
{
    PARAM_FIELD_GET_DOWN_SHIP* param = (PARAM_FIELD_GET_DOWN_SHIP*)scriptParam;
    fld::FieldPlayerManager::getSingleton().setScriptGetDownShip(param->direction);
}

THUMB int FieldGetDownShip::isEnd()
{
    return fld::FieldPlayerManager::getSingleton().isEndScriptGetDownShip();
}

FieldGetDownShip gFieldGetDownShip;

THUMB void FieldSymbolAnim::initialize(char* scriptParam)
{
    anim_.setup("data/field/symbol/watergate.pack");
}

THUMB void FieldSymbolAnim::execute()
{
    anim_.calcAnim(fld::FieldStage::getSingleton()->fieldData.symbolTexture_[21]);
}

THUMB int FieldSymbolAnim::isEnd()
{
    return anim_.enable_ == 0;
}

FieldSymbolAnim gFieldSymbolAnim;

THUMB void FieldGoldOrbEvent::initialize(char* scriptParam)
{
    PARAM_DRAW_GOLD_ORB* param = (PARAM_DRAW_GOLD_ORB*)scriptParam;
    orbPosX_ = 0x78L;
    orbPosY_ = (long)(param->endY - param->high);
    orbSprite_.loadFile("data/field/symbol/glob.tex", 1);
    orbSprite_.setPositionFix32(orbPosX_, orbPosY_);
    orbSprite_.setDepth(0x10);
    orbSprite_.setMainScreen();
    orbGlowSprite_.loadFile("data/field/symbol/glob2.tex", 1);
    orbGlowSprite_.setPositionFix32(orbPosX_, orbPosY_);
    orbGlowSprite_.setDepth(0x12);
    orbGlowSprite_.setMainScreen();
    orbEndPosY_ = param->endY;
    orbSpeed_.value = param->speed;
}

THUMB void FieldGoldOrbEvent::execute()
{
    setupOrtho2DBackground();
    orbSprite_.setPositionFix32(orbPosX_, orbPosY_);
    orbSprite_.draw();
    orbGlowSprite_.setPositionFix32(orbPosX_, orbPosY_);
    orbGlowSprite_.draw();
    orbPosY_.value += orbSpeed_.value;
}

THUMB int FieldGoldOrbEvent::isEnd()
{
    if (orbPosY_.value == orbEndPosY_ << 12) {
        orbSprite_.unload();
        orbGlowSprite_.unload();
        return true;
    }
    return false;
}

FieldGoldOrbEvent gFieldGoldOrbEvent;

THUMB bool cmd_field_trriger(void* scriptParam)
{
    PARAM_FIELD_TRRIGER* param = (PARAM_FIELD_TRRIGER*)scriptParam;
    dss::Fix32Vector3 pos = cmn::GameManager::getSingleton().getPlayerManager()->getPosition();
    short idx = cmn::GameManager::getSingleton().getPlayerManager()->getDirection();
    dss::Fix32Vector3 start;
    dss::Fix32Vector3 end;
    start.set(param->startX, param->startY, -1);
    end.set(param->endX, param->endY, 1);
    pos.vz = 0L;
    dss::Fix32Vector3 center = (start + end) / 2 - pos;
    int checkDir = 0;
    int checkArea = param->flag == 0 ? 7 : 6;
    return cmn::CommonCalculate::areaCheck(pos, idx, start, end, checkDir, checkArea);
}

THUMB bool cmd_field_set_formation(void* scriptParam)
{
    PARAM_FIELD_PARTY_MOVE2_FORMATION* param = (PARAM_FIELD_PARTY_MOVE2_FORMATION*)scriptParam;
    int charDir = fld::FieldActionCalculate::getIdxByParam4(param->charaDir);
    dss::Fix32Vector3 fmDir = fld::FieldActionCalculate::getVector3ByDir8(fld::FieldActionCalculate::getIdxByParam4(param->frmDir));
    fld::FieldPlayerManager::getSingleton().party_.setFormation(fmDir, charDir);
    return true;
}

void ScriptCommandField_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
