#include "main/cmn/CommonPartyInfo.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/FloorParam.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

inline char dq5::level::FloorParam::getSave()
{
    return byte_6 & 0xf;
}

inline dq5::level::FloorParam* dq5::level::FloorParam::getRecord(int index)
{
    return (FloorParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

cmn::CommonPartyInfo cmn::g_cmnPartyInfo;

THUMB cmn::CommonPartyInfo::CommonPartyInfo()
{
    prevLocation_ = 0;
    mapNameIdAtIkada_ = 0;
    mapNameIdShip_ = 0;
    keepMap_ = 0;
    shipIkadaArea_ = 0;
    iceStart_ = 0;
    iceCount_ = 0;
    cancelColl_ = 0;
    prev_dispMapName_ = NULL;
    dispMapName_ = NULL;
    linkDisp_ = 0;
    cameraRot_ = 1;
    mapLinkFlag_ = 0;
}

THUMB void cmn::CommonPartyInfo::getPartyInfo(dss::Fix32Vector3& position, short& dirIdx)
{
    position = position_;
    dirIdx = dirIdx_;
}

THUMB void cmn::CommonPartyInfo::setDirIdx(short dirIdx)
{
    dirIdx_ = dirIdx;
}

THUMB void cmn::CommonPartyInfo::setStartPosition()
{
    position_ = startPos_;
}

THUMB void cmn::CommonPartyInfo::setShipInfo(int mapNameId, dss::Fix32Vector3& position, short direction)
{
    mapNameIdShip_ = mapNameId;
    townShipPos_ = position;
    shipDirection_ = direction;
}

THUMB short cmn::CommonPartyInfo::getShipMapName()
{
    return mapNameIdShip_;
}

THUMB void cmn::CommonPartyInfo::getShipInfo(dss::Fix32Vector3& position, short& direction)
{
    position = townShipPos_;
    direction = shipDirection_;
}

THUMB void cmn::CommonPartyInfo::setIkadaInfo(int mapNameId, dss::Fix32Vector3& position)
{
    mapNameIdAtIkada_ = mapNameId;
    townIkadaPos_ = position;
}

THUMB int cmn::CommonPartyInfo::getIkadaMapNameId()
{
    return mapNameIdAtIkada_;
}

THUMB dss::Fix32Vector3 cmn::CommonPartyInfo::getIkadaPos()
{
    return townIkadaPos_;
}

THUMB void cmn::CommonPartyInfo::resetShipIkadaMapName()
{
    switch (status::g_StageInfo.returnGame_) {
        case dq5::RETURN_GAME_CHURCH:
        case dq5::RETURN_GAME_ABORT:
            return;
    }
    if (shipIkadaArea_ == 0) {
        mapNameIdAtIkada_ = 0;
        mapNameIdShip_ = 0;
    }
    shipIkadaArea_ = 0;
}

THUMB void cmn::CommonPartyInfo::callCarriage()
{
    status::g_Party.carriage_ = 1;
    status::g_StageAttribute.setCarriageEnable(true);
    status::g_StageAttribute.setCarriageEnter(true);
    barron_ = 1;
    if (data_02101c88.isCurrentPart(6)) {
        fld::FieldPlayerManager::getSingleton().resetParty();
    } else {
        twn::TownPlayerManager::getSingleton().resetParty();
    }
}

THUMB void cmn::CommonPartyInfo::setMenuAction(MENU_ACTION action)
{
    menuAction_ = action;
}

THUMB void cmn::CommonPartyInfo::setKeep(int flag, int map, bool reset)
{
    if (flag == true) {
        twn::TownPlayerManager::getSingleton().partyDraw_.separatePos();
        keepMap_ = map;
        status::PartyStatusUtility::separateParty(reset);
    } else {
        status::PartyStatusUtility::resetSeparateParty(reset);
    }
}

THUMB int cmn::CommonPartyInfo::isAbortSaveTown()
{
    if (data_02101c88.isCurrentPart(6) == 1) {
        return 1;
    }
    if (data_02101c88.isCurrentPart(4) == 1) {
        if (twn::TownPlayerManager::getSingleton().isSaveAndBattleOK() == false) {
            return 0;
        }
    }
    return dq5::level::FloorParam::getRecord(dq5::level::g_LevelDataUtility.getFloorDataIndex())->getSave();
}

THUMB int cmn::CommonPartyInfo::isAbortSaveDungeon()
{
    if (data_02101c88.isCurrentPart(6) == 1) {
        return 1;
    }
    if (g_Global.areaNo_ >= 0x1e && g_Global.areaNo_ <= 0x2c) {
        if (data_02101c88.isCurrentPart(4) == 1) {
            if (twn::TownPlayerManager::getSingleton().isSaveAndBattleOK() == false) {
                return 0;
            }
        }
        return dq5::level::FloorParam::getRecord(dq5::level::g_LevelDataUtility.getFloorDataIndex())->getSave();
    }
    return 1;
}
