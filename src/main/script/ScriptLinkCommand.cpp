#include "main/script/ScriptLinkCommand.hpp"
#include "main/script/CommandParam.hpp"
#include "main/script/ScriptSystem.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/ceremony/CeremonySetting.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/character/TownCharacterBase.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov005/fld/FieldSystem.hpp"

inline void ScriptSystem::setEnableExecute(bool flag)
{
    executeEnable_ = flag;
}

inline void twn::TownCharacterBase::setAllEventLock(bool flag)
{
    allEventLock_ = flag;
}

inline void twn::TownPlayerManager::setAnimation(int flag)
{
    partyDraw_.setAnimation(flag);
}

inline void twn::TownPlayerManager::setPlayExitSE(bool flag)
{
    playExitSE_ = flag;
}

inline void fld::FieldSystem::setExitSound(int flag)
{
    exitSound_ = flag;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline void fld::FieldStage::setSymbolDisp(int uid, int disp)
{
    fieldData.setDispSymbol(uid, disp);
}

inline void ceremony::CeremonySetting::setStaffrollIndex(int index)
{
    staffrollIndex_ = index;
}

inline void ceremony::CeremonySetting::setNextActMap(int index)
{
    nextActMap_ = index;
}

inline void ceremony::CeremonySetting::setNextActPos(dss::Fix32Vector3& pos)
{
    nextActPosition_ = pos;
}

THUMB bool cmd_floor_change(void* scriptParam)
{
    PARAM_FLOOR_CHANGE* param = (PARAM_FLOOR_CHANGE*)scriptParam;
    dss::Fix32Vector3 pos = cmn::CommonCalculate::setVecByParam(param->exitX, param->exitY, param->exitZ);
    short dir = cmn::CommonCalculate::getIdxByParam(param->direction);
    cmn::g_extraMapLink.setExtraLinkTown(param->floor, pos, dir);
    ScriptSystem::getSingleton()->setEnableExecute(false);
    if (data_02101c88.unkfunc_02051818(4)) {
        twn::TownCharacterBase::setAllEventLock(false);
        BillboardCharacter::setAllCharaAnim(true);
        TownCharacterManager::getSingleton()->restoreCharacterAnim();
        twn::TownPlayerManager::getSingleton().setAnimation(2);
        if (param->flag == 1) {
            twn::TownPlayerManager::getSingleton().setPlayExitSE(true);
        }
    } else if (param->flag == 1) {
        fld::FieldSystem::getSingleton()->setExitSound(true);
    }
    return true;
}

THUMB bool cmd_floor_exit(void* scriptParam)
{
    PARAM_FLOOR_EXIT* param = (PARAM_FLOOR_EXIT*)scriptParam;
    cmn::g_extraMapLink.setExtraExitTown(param->floor, param->exitNo);
    ScriptSystem::getSingleton()->setEnableExecute(false);
    if (data_02101c88.unkfunc_02051818(4)) {
        twn::TownCharacterBase::setAllEventLock(false);
        BillboardCharacter::setAllCharaAnim(true);
        TownCharacterManager::getSingleton()->restoreCharacterAnim();
        twn::TownPlayerManager::getSingleton().setAnimation(2);
        if (param->flag == 1) {
            twn::TownPlayerManager::getSingleton().setPlayExitSE(true);
        }
    } else if (param->flag == 1) {
        fld::FieldSystem::getSingleton()->setExitSound(true);
    }
    return true;
}

THUMB bool cmd_set_map_link_on_off(void* scriptParam)
{
    PARAM_SET_MAP_LINK_ON_OFF* param = (PARAM_SET_MAP_LINK_ON_OFF*)scriptParam;
    cmn::LINK_TYPE type;
    if (param->on_off == 0) {
        type = cmn::NOT_LINK_THIS_TOWN;
    } else {
        type = cmn::LINK_DEFAULT;
    }
    if (data_02101c88.unkfunc_02051818(6)) {
        cmn::g_extraMapLink.setLinkData(param->surfaceNo, -1, type, 0, 0);
    }
    if (data_02101c88.unkfunc_02051818(4)) {
        cmn::g_extraMapLink.setLinkData(param->surfaceNo, -1, type, g_Global.getMapNameId(), 0);
    }
    return true;
}

THUMB bool cmd_change_map_link(void* scriptParam)
{
    PARAM_CHANGE_MAP_LINK* param = (PARAM_CHANGE_MAP_LINK*)scriptParam;
    int nextId = param->nextMapName;
    cmn::g_extraMapLink.setLinkData(param->nowId, param->nextId, cmn::LINK_TOWN_TO_TOWN, g_Global.getMapNameId(), nextId);
    return true;
}

THUMB bool cmd_map_link_field_direct(void* scriptParam)
{
    PARAM_MAP_LINK_FIELD_DIRECT* param = (PARAM_MAP_LINK_FIELD_DIRECT*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz = 0L;
    cmn::g_extraMapLink.setExtraExitField(param->symbol, pos);
    if (data_02101c88.unkfunc_02051818(4)) {
        twn::TownCharacterBase::setAllEventLock(false);
        BillboardCharacter::setAllCharaAnim(true);
        TownCharacterManager::getSingleton()->restoreCharacterAnim();
        twn::TownPlayerManager::getSingleton().setAnimation(2);
        if (param->flag == 1) {
            twn::TownPlayerManager::getSingleton().setPlayExitSE(true);
        }
    } else if (param->flag == 1) {
        fld::FieldSystem::getSingleton()->setExitSound(true);
    }
    return true;
}

THUMB bool cmd_is_doorway(void* scriptParam)
{
    PARAM_IS_DOORWAY* param = (PARAM_IS_DOORWAY*)scriptParam;
    int exitId = util::StageLink::getTownExitIndex();
    if (exitId == param->doorway) {
        return true;
    }
    return false;
}

THUMB bool cmd_set_town_to_field_link(void* scriptParam)
{
    PARAM_SET_TOWN_TO_FIELD_LINK* param = (PARAM_SET_TOWN_TO_FIELD_LINK*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.set(param->posX, param->posY, 0);
    cmn::g_extraMapLink.setLinkData(param->surfaceId, param->symbolNo, cmn::LINK_TOWN_TO_FIELD, g_Global.getMapNameId(), 0, pos);
    return true;
}

THUMB bool cmn_set_field_to_town_link(void* scriptParam)
{
    PARAM_SET_FIELD_TO_TOWN_LINK* param = (PARAM_SET_FIELD_TO_TOWN_LINK*)scriptParam;
    cmn::g_extraMapLink.setLinkData(param->symbolNo, param->surfaceId, cmn::LINK_FIELD_TO_TOWN, 0, param->townNameID);
    return true;
}

THUMB bool cmd_field_erase_symbol(void* scriptParam)
{
    PARAM_FIELD_ERASE_SYMBOL* param = (PARAM_FIELD_ERASE_SYMBOL*)scriptParam;
    fld::FieldStage::getSingleton()->eraseSymbol(param->uid);
    return true;
}

THUMB bool cmd_field_symbol_disp(void* scriptParam)
{
    PARAM_FIELD_SYMBOL_DISP* param = (PARAM_FIELD_SYMBOL_DISP*)scriptParam;
    fld::FieldStage::getSingleton()->setSymbolDisp(param->uid, param->disp);
    return true;
}

THUMB bool cmd_floor_change_ending(void* scriptParam)
{
    PARAM_FLOOR_CHANGE_ENDING* param = (PARAM_FLOOR_CHANGE_ENDING*)scriptParam;
    ceremony::CeremonySetting::getSingleton()->setNextActMap(param->floor);
    dss::Fix32Vector3 pos;
    pos.set(param->exitX, param->exitY, param->exitZ);
    ceremony::CeremonySetting::getSingleton()->setNextActPos(pos);
    ceremony::CeremonySetting::getSingleton()->setStaffrollIndex(param->index);
    g_Global.startStaffroll();
    return true;
}
