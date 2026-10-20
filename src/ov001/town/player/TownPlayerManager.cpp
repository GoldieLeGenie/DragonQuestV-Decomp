#pragma ipa file
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownDamageFloor.hpp"
#include "ov001/town/TownExtraMapObjManager.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownSugorokuManager.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/leveldata/CharacterWidth.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/town/TownSugorokuInfo.hpp"

inline cmn::PartyMoveAction::PartyMoveAction()
{
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline void twn::TownStageManager::setBoxtestFlag(int flag)
{
    stage_.m_fld.m_box_test = flag;
}

inline int twn::TownStageManager::characoterColl(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos, dss::Fix32 rad, dss::Fix32Vector3* retVec, int flag)
{
    return coll_.characterColl(oldPos, newPos, rad, retVec, flag);
}

inline int twn::TownStageManager::getMapObjUid(int obj_id)
{
    return stage_.m_fld.GetMapObjUid(obj_id);
}

inline int twn::TownStageManager::getCommonID(int objectID)
{
    if (objectID == -1) {
        return -1;
    }
    return stage_.m_fld.GetMapObjCommonId(objectID);
}

inline void twn::TownSugorokuInfo::decTimer()
{
    timeCount_--;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline int status::PlayerStatus::getPlayerIndex()
{
    return getHaveStatusInfo().getHaveStatus().getPlayerIndex();
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::CharacterWidth* dq5::level::CharacterWidth::getRecord(int index)
{
    return (CharacterWidth*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

THUMB inline bool twn::TownPlayerManager::isEqalNextPos(int index)
{
    return party_.isEqalNextPos(index);
}

THUMB inline void twn::TownPlayerManager::addPartyDrawAlpha(int index, char a)
{
    partyDraw_.addAlpha(index, a);
}

THUMB inline char twn::TownPlayerManager::getPartyDrawAlpha(int index)
{
    return partyDraw_.partyDispAlpha_[index];
}

THUMB inline short cmn::PartyMoveAction::getMemberDir(int index)
{
    return partyData_[index].direction;
}

THUMB inline const dss::Fix32Vector3& cmn::PartyMoveAction::getMemberPos(int index)
{
    return partyData_[index].position;
}

static dss::Fix32Vector3 unk_02153bd8(0, 0, 0);

THUMB twn::TownPlayerManager::TownPlayerManager()
{
}

THUMB twn::TownPlayerManager& twn::TownPlayerManager::getSingleton()
{
    static TownPlayerManager m_singleton;
    return m_singleton;
}

THUMB void twn::TownPlayerManager::initialize()
{
    for (int i = 0; i < SCRIPT_SEARCH_OBJECT_NUM; i++) {
        scriptSearchUid_[i] = 0;
    }
    flagMapLink_ = 0;
    effectPosFlag_ = 0;
    charaColl_ = 1;
    locked_ = 0;
    remoteFlag_ = 0;
    execFlag_ = 0;
    link_ = 0;
    scriptPlayer_ = 0;
    uid1_ = 0;
    uid2_ = 0;
    partyDraw_.setup();
    exitLock_ = 0;
    cameraLot_ = ROT_NONE;
    prev_cameraLot_ = ROT_NONE;
    txCounter_ = 0;
    scriptColl_ = 0;
    defaultClip_ = 2;
    if (g_Global.getMapNameId() == 0x1c2) {
        defaultClip_ = 0;
    }
    TownStageManager::getSingleton()->setBoxtestFlag(defaultClip_);
    if (g_Global.areaNo_ != g_Global.prevAreaNo_) {
        cmn::g_cmnPartyInfo.resetShipIkadaMapName();
    }
}

THUMB void twn::TownPlayerManager::terminate()
{
    if (g_Global.isNextPart(5) == false) {
        g_Global.isAreaChange();
        if (playExitSE_ != 0 && defaultSELock_ == 0) {
            SoundManager::playSe(0x131, 0);
        }
    } else {
        cmn::g_cmnPartyInfo.mapLinkFlag_ = flagMapLink_;
    }
    if (g_Global.isNextPart(6)) {
        status::g_StageInfo.setFallFlag(false);
    }
    partyDraw_.cleanup();
}

THUMB void twn::TownPlayerManager::execute()
{
    execFlag_ = 1;
    cmn::g_cmnPartyInfo.playerTalk = 0;
    searchMapUid_ = 0;
    cmn::g_cmnPartyInfo.prev_position_ = cmn::g_cmnPartyInfo.position_;
    if (prev_cameraLot_ != ROT_NONE || cameraLot_ != ROT_NONE) {
        setCameraRot();
    }
    normalExec();
    unkfunc_0213d450();
    scriptTruckAction();
}

THUMB void twn::TownPlayerManager::update()
{
    if (execFlag_ == 1) {
        if (locked_ == 0 || scriptPlayer_ == 1) {
            player_.update();
        }
    }
}

THUMB void twn::TownPlayerManager::draw()
{
    setShadow();
    if (effectPosFlag_ == 0) {
        partyDraw_.setPosition(0, cmn::g_cmnPartyInfo.position_);
        partyDraw_.setRotate(0, cmn::g_cmnPartyInfo.dirIdx_);
        party_.setPosition();
    } else {
        partyDraw_.setPosition(0, effectPos_);
        dss::Fix32Vector3 tempPos(cmn::g_cmnPartyInfo.position_);
        cmn::g_cmnPartyInfo.position_ = effectPos_;
        partyDraw_.setRotate(0, cmn::g_cmnPartyInfo.dirIdx_);
        party_.setPosition();
        cmn::g_cmnPartyInfo.position_ = tempPos;
    }
    for (int i = 1; i < partyDraw_.countReal_; i++) {
        partyDraw_.setPosition(i, party_.getMemberPos(i));
        partyDraw_.setRotate(i, party_.getMemberDir(i));
    }
    party_.resetFixPos();
    partyDraw_.execute();
    partyDraw_.draw();
}

THUMB void twn::TownPlayerManager::setup()
{
    partyDraw_.setExcute(true);
    scriptType_ = 0;
    allShadowReset_ = 1;
    shadowSet_ = 0;
    mapChangeSE_ = 1;
    int exitIndex = util::StageLink::getTownExitIndex();
    dss::Fix32Vector3 pos;
    if (exitIndex != -1 && status::g_StageInfo.encount_ == 0 && cmn::g_cmnPartyInfo.prevLocation_ == 0) {
        TownStageManager::getSingleton()->setExitPosition(&pos, exitIndex);
        dss::abs<int>(exitIndex);
        setPosition(pos);
        cmn::g_cmnPartyInfo.startPos_ = pos;
        flagMapLink_ = 1;
        dss::Fix32Vector3 dirVec = TownStageManager::getSingleton()->getSurfaceDir(exitIndex);
        if (dirVec.vy <= dss::Fix32(0x333)) {
            short idx = 0;
            TownActionCalculate::getIdxByVec(idx, dirVec);
            cmn::g_cmnPartyInfo.setDirIdx(idx);
            flIdx = idx;
        }
        flPos = pos;
    }
    player_.setup();
    party_.setup();
    setDistance();
    if (status::g_BattleResult.playerDemolitionMessage_ == 2 && status::g_StageInfo.encount_ == 1) {
        flagMapLink_ = cmn::g_cmnPartyInfo.mapLinkFlag_;
    } else {
        flagMapLink_ = 1;
    }
    TownStageManager::getSingleton()->coll_.searchClear();
    cmn::g_cmnPartyInfo.prevLocation_ = 0;
    status::g_StageInfo.encount_ = 0;
    status::g_StageInfo.menuTalk_ = 0;
    status::g_StageInfo.menuSearch_ = 0;
    status::g_StageInfo.ropeLink_ = 0;
    partyDraw_.setAnimation(1);
    idoMess_ = 0;
    tabiLink_ = 0;
    walkCounter_ = 0;
    searchAction_ = 0;
    BillboardCharacter::setAllCharaAnim(true);
    if (player_.actionType_ != ACTION_TYPE_FALL) {
        TownCamera::getSingleton()->camera_.m_camera0.setTarget(cmn::g_cmnPartyInfo.position_);
        dss::Fix32Vector3 povPos(TownCamera::getSingleton()->camera_.m_camera0.getPosition());
        dss::Fix32Vector3 target(TownCamera::getSingleton()->camera_.m_camera0.getTarget());
        dss::Vector3<short>& now = TownCamera::getSingleton()->camera_.m_camera0.getAngle();
        dss::Vector3<short> angle(now.vx, now.vy, now.vz);
        TownCamera::getSingleton()->calcPositionFromAngle(angle, povPos, target);
        TownCamera::getSingleton()->camera_.m_camera0.setPosition(povPos);
    }
}

THUMB void twn::TownPlayerManager::cleanup()
{
    player_.cleanup();
    party_.cleanup();
}

THUMB void twn::TownPlayerManager::unkfunc_0213d450()
{
}

THUMB void twn::TownPlayerManager::normalExec()
{
    if (cmn::PlayerManager::isLock() == false || scriptPlayer_ == 1) {
        cmn::g_cmnPartyInfo.partyTalk = 1;
        player_.execute();
        dss::Fix32Vector3 prevPos(cmn::g_cmnPartyInfo.prev_position_);
        dss::Fix32Vector3 nextPos(cmn::g_cmnPartyInfo.position_);
        if (prevPos != nextPos) {
            switch (player_.actionType_) {
            case ACTION_TYPE_WALK:
            case ACTION_TYPE_ROPE:
            case ACTION_TYPE_KAIDAN:
            case ACTION_TYPE_FRAME_MOVE:
                partyDraw_.setWriggleCharaAll(1);
                break;
            default:
                partyDraw_.setWriggleCharaAll(0);
                break;
            }
            if (isLock() == false) {
                walkCounter_++;
                talkRefresh_++;
                if (talkRefresh_ >= 240) {
                    talkRefresh_ = 0;
                    cmn::PartyTalk::getSingleton().resetWalkPartyTalk();
                }
            }
        } else {
            partyDraw_.setWriggleCharaAll(0);
        }
        return;
    }
    dss::Fix32Vector3 pos(getPosition());
    dss::Vector3<short> angle;
    angle.set(0, getDirection(), 0);
    switch (scriptType_) {
    case 8: {
        dss::Fix32Vector3 tpos = TownStageManager::getSingleton()->getMapUidPos(objMoveUid_);
        tpos += objMovePos_;
        dss::Fix32Vector3 vec = tpos - pos;
        setPosition(tpos);
        TownActionCalculate::getIdxByVec(angle.vy, vec);
        setDirection(angle.vy);
        return;
    }
    case 6:
        if (getMoveToFirstFlag() == false) {
            setLock(false);
            scriptType_ = 7;
        }
        return;
    case 7:
        return;
    default:
        if (scriptType_ != 0) {
            scriptExecute();
        }
        break;
    }
    if (scriptRotFlag_ == 1) {
        scriptMove_.execRot(angle);
        setDirection(angle.vy);
        if (scriptMove_.rotUpdate() == true) {
            scriptRotFlag_ = 0;
        }
    }
    if (player_.actionType_ == ACTION_TYPE_FALL) {
        player_.townActionFall_.exitFall();
    }
}

THUMB bool twn::TownPlayerManager::normalMapLink()
{
    int nameId = TownStageManager::getSingleton()->getLinkMapNameId();
    if (nameId == 0) {
        flagIdoLink_ = 0;
        return false;
    }
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(5) != -1 &&
        TownStageManager::getSingleton()->getHitSurfaceIdByType(6) == -1 && flagIdoLink_ == 0) {
        return false;
    }
    if (flagMapLink_ == 0) {
        flagMapLink_ = 1;
        if (mapChangeSE_ == 1) {
            playExitSE_ = 1;
        }
        if (nameId == 999) {
            int id = util::StageLink::getSymbolIndex();
            util::StageLink::setFieldSymbolIndex(id);
            g_Global.nextFieldType_ = cmn::g_extraMapLink.getFieldTypeBySurface(id);
            g_Global.startField();
            setLock(true);
            status::g_StageInfo.idoLinkInFlag_ = 0;
            status::g_StageInfo.idoLinkOutFlag_ = 0;
            link_ = 1;
            return true;
        }
        char name[10];
        g_Global.getMapNameById(name, nameId);
        if (TownStageManager::getSingleton()->isStageExist(name)) {
            util::StageLink::setTownExitIndex(TownStageManager::getSingleton()->getExitIndex());
            g_Global.startTown(nameId);
            setLock(true);
            link_ = 1;
            return true;
        }
    }
    return false;
}

THUMB bool twn::TownPlayerManager::execMapLink()
{
    link_ = 0;
    if (execFlag_ == 0) {
        return false;
    }
    int exitIndex = TownStageManager::getSingleton()->getExitIndex();
    if (exitIndex == -1 || exitLock_ != 0) {
        flagMapLink_ = 0;
        flagIdoLink_ = 0;
        return false;
    }
    if (flagMapLink_ == 0) {
        if ((exitIndex & 0xffff0000) == 0x70000 && (exitIndex & 0xfff) >= 300) {
            player_.townActionTabi_.start(exitIndex, false);
            player_.actionType_ = ACTION_TYPE_TABI;
            return true;
        }
        if ((exitIndex & 0xfff) >= 200) {
            if (cmn::g_cmnPartyInfo.position_ != cmn::g_cmnPartyInfo.prev_position_) {
                player_.townActionTabi_.start(exitIndex, false);
                player_.actionType_ = ACTION_TYPE_TABI;
                return true;
            }
            return false;
        }
        if (TownStageManager::getSingleton()->getHitSurfaceIdByType(16) != -1 && cmn::g_extraMapLink.checkWarp(exitIndex)) {
            SoundManager::playSe(0x470, 0);
            flagMapLink_ = 1;
            link_ = 1;
            return true;
        }
        if (g_Global.getMapNameId() == 0x51 && (exitIndex & 0xffff0000) == 0x70000) {
            flagMapLink_ = 1;
            cmn::g_extraMapLink.setExtraLinkFieldAbsPos(0, status::g_StageInfo.firmamentPosition_, 4);
            if (mapChangeSE_ == 1) {
                playExitSE_ = 1;
            }
            return true;
        }
        int ret = cmn::g_extraMapLink.checkTownMapLink(exitIndex);
        if (ret == 4) {
            return false;
        }
        if (ret != 0) {
            if (mapChangeSE_ == 1) {
                playExitSE_ = 1;
            }
            setLock(true);
            flagMapLink_ = 1;
            link_ = 1;
            return true;
        }
    }
    return normalMapLink();
}

THUMB void twn::TownPlayerManager::inputPad(int padDir)
{
    player_.inputPad(padDir);
}

THUMB void twn::TownPlayerManager::inputClear()
{
    player_.inputClear();
}

THUMB void twn::TownPlayerManager::resetParty()
{
    int taimatsu = partyDraw_.taimatsuFlag_;
    status::g_Party.setDisplayMode();
    if (partyDraw_.countReal_ != 0) {
        partyDraw_.cleanup();
        partyDraw_.setup();
        int count = partyDraw_.countReal_;
        for (int i = 0; i < count; i++) {
            partyDraw_.setPosition(i, party_.getMemberPos(i));
            partyDraw_.setRotate(i, party_.getMemberDir(i));
        }
    }
    setDistance();
    resetAlpha();
    partyDraw_.taimatsuFlag_ = taimatsu;
    switch (player_.actionType_) {
    case ACTION_TYPE_SHIP:
        setDrawPartyNone();
        break;
    case ACTION_TYPE_IKADA:
        setPartyDrawOne();
        break;
    }
}

THUMB void twn::TownPlayerManager::lockMapLink(EXIT_LOCK_TYPE type)
{
    exitLock_ |= type;
}

THUMB void twn::TownPlayerManager::resetMapLink(RESET_EXIT_LOCK_TYPE type)
{
    exitLock_ &= ~type;
}

THUMB void twn::TownPlayerManager::setPosition(dss::Fix32Vector3& pos)
{
    cmn::g_cmnPartyInfo.position_ = pos;
}

THUMB dss::Fix32Vector3& twn::TownPlayerManager::getPosition()
{
    return cmn::g_cmnPartyInfo.position_;
}

THUMB void twn::TownPlayerManager::setPartyToFirst(dss::Fix32Vector3& pos)
{
    cmn::g_cmnPartyInfo.position_ = pos;
    party_.setAllPotition(pos);
}

THUMB void twn::TownPlayerManager::setDirection(short idx)
{
    cmn::g_cmnPartyInfo.setDirIdx(idx);
}

THUMB short twn::TownPlayerManager::getDirection()
{
    return cmn::g_cmnPartyInfo.dirIdx_;
}

THUMB void twn::TownPlayerManager::setFormation(int frmDir, int charaDir, dss::Fix32 speed)
{
    dss::Fix32Vector3 frmVec;
    short dirIdx = TownActionCalculate::getIdxByParam(charaDir);
    frmVec = TownActionCalculate::getParamVec(frmDir);
    frmVec.normalize();
    frmVec *= TownPlayerAction::walkSpeed;
    setDirection(dirIdx);
    party_.setFormation(frmVec, dirIdx, speed);
    frmVec *= -1;
    TownActionCalculate::getIdxByVec(dirIdx, frmVec);
    party_.formationDir_ = dirIdx;
    frmDirIdx_ = dirIdx;
}

THUMB void twn::TownPlayerManager::setRemote(bool flag)
{
    remoteFlag_ = flag;
    if (flag == true) {
        TownDamageFloor::getSingleton().check_ = 0;
        TownDamageFloor::getSingleton().resetMemberColor();
    }
}

THUMB bool twn::TownPlayerManager::isLock()
{
    if (remoteFlag_ == 1 || cmn::PlayerManager::isLock() == true) {
        return true;
    }
    return false;
}

THUMB void twn::TownPlayerManager::setLock(bool lock)
{
    if (locked_ == 0) {
        partyDraw_.setExcute(false);
        TownCharacterManager::getSingleton()->setAllEventLock(true);
        TownCharacterManager::getSingleton()->eventLockAllChraraAnim();
        partyDraw_.setAnimation(2);
        partyDraw_.setWriggleCharaAll(0);
        TownStageManager::getSingleton()->setBoxtestFlag(0);
        TownDamageFloor::getSingleton().check_ = 0;
        TownDamageFloor::getSingleton().resetMemberColor();
    }
    cmn::PlayerManager::setLock(lock);
    player_.inputClear();
    if (locked_ == 0) {
        partyDraw_.setExcute(true);
        charaColl_ = 1;
        TownCharacterManager::getSingleton()->setAllEventLock(false);
        TownCharacterManager::getSingleton()->restoreCharacterAnim();
        partyDraw_.setAnimation(1);
        TownStageManager::getSingleton()->setBoxtestFlag(defaultClip_);
    }
}

THUMB void twn::TownPlayerManager::setCameraRotToNorth()
{
    switch (cameraLot_) {
    case ROT_TO_NORTH:
    case ROT_TO_NORTH_END:
    case ROT_TO_NORTH_FREE:
        return;
    }
    cameraLot_ = ROT_TO_NORTH;
    setLock(true);
}

THUMB void twn::TownPlayerManager::setCameraRot()
{
    bool ret;
    short dirIdx = getDirection();
    short prevIdx = dirIdx;
    switch (cameraLot_) {
    case ROT_NONE:
    case ROT_TO_NORTH_END:
    case ROT_TO_NORTH_FREE:
        break;
    case ROT_TO_NORTH: {
        short addAngle = 0;
        if (TownCamera::getSingleton()->setAngleNorth(addAngle) == true) {
            cameraLot_ = ROT_TO_NORTH_END;
            setLock(false);
        } else if (TownSugorokuManager::getSingleton().isTreasuerRoom() == true) {
            g_SugorokuInfo.decTimer();
        }
        if (player_.actionType_ != ACTION_TYPE_ROPE) {
            setDirection(addAngle + dirIdx);
        }
        flagMapLink_ = 1;
        break;
    }
    case ROT_TO_R:
        ret = TownCamera::getSingleton()->rotateR();
        if (TownCamera::getSingleton()->flagRotateR == 1 && player_.actionType_ != ACTION_TYPE_ROPE && ret == true) {
            dirIdx = (unsigned short)(short)(dirIdx - 0x100);
            setDirection(dirIdx);
        }
        break;
    case ROT_TO_L:
        ret = TownCamera::getSingleton()->rotateL();
        if (TownCamera::getSingleton()->flagRotateL == 1 && player_.actionType_ != ACTION_TYPE_ROPE && ret == true) {
            dirIdx = (unsigned short)(short)(dirIdx + 0x100);
            setDirection(dirIdx);
        }
        break;
    }
    prev_cameraLot_ = cameraLot_;
    if (cameraLot_ != ROT_TO_NORTH && cameraLot_ != ROT_TO_NORTH_END) {
        cameraLot_ = ROT_NONE;
    }
    if (dirIdx != prevIdx) {
        player_.townActionWalk_.clearActionInfo();
    }
}

THUMB void twn::TownPlayerManager::setSimpleMove(dss::Fix32Vector3& prev, dss::Fix32Vector3& next, int frame)
{
    setLock(true);
    scriptMove_.setActionMove(prev, next);
    scriptMove_.setMoveFrame(frame);
    scriptType_ = 1;
    party_.script_ = 1;
    party_.fixFlag_ = 0;
}

THUMB void twn::TownPlayerManager::setSpeedMove(dss::Fix32Vector3& prev, dss::Fix32Vector3& next, dss::Fix32 speed)
{
    setLock(true);
    static const dss::Fix32 defaultSpeed(0x66);
    speed = defaultSpeed * speed;
    scriptMove_.setActionMove(prev, next);
    scriptMove_.setMoveSpeed(speed);
    scriptType_ = 1;
    party_.script_ = 1;
    party_.fixFlag_ = 0;
}

THUMB void twn::TownPlayerManager::setJumpMove(dss::Fix32Vector3& endPos, int frame)
{
    dss::Fix32Vector3 pos = getPosition();
    scriptMove_.setJumpMove(pos, endPos, frame);
    scriptType_ = 2;
    for (int i = 0; i < partyDraw_.countReal_; i++) {
        partyDraw_.partyCharacter_[i].setShadowFlag(0);
    }
    setLock(true);
}

THUMB int twn::TownPlayerManager::isFinish()
{
    return scriptType_ == 0;
}

THUMB void twn::TownPlayerManager::setMapObjMove(int flag, int mapUid, dss::Fix32Vector3& pos)
{
    if (flag == true) {
        scriptType_ = 8;
        objMoveUid_ = mapUid;
        objMovePos_ = pos;
    } else {
        scriptType_ = 0;
    }
}

THUMB void twn::TownPlayerManager::setCameraRotType(int type)
{
    if (prev_cameraLot_ != ROT_TO_NORTH && prev_cameraLot_ != ROT_TO_NORTH_END) {
        cameraLot_ = (CAMERA_ROT_TYPE)type;
        return;
    }
    if (prev_cameraLot_ == ROT_TO_NORTH_END && type == ROT_NONE) {
        cameraLot_ = ROT_NONE;
    }
}

THUMB bool twn::TownPlayerManager::isIdoLinkPos()
{
    dss::Fix32Vector3 pos = TownStageManager::getSingleton()->getHitSurfacePosByType(5);
    dss::Fix32Vector3 vec = pos - cmn::g_cmnPartyInfo.position_;
    vec.vy = 0L;
    vec.normalize();
    dss::Fix32Vector3 dir;
    TownActionCalculate::getDirByIdx(cmn::g_cmnPartyInfo.dirIdx_, dir);
    dss::Fix32 dot = vec * dir;
    return dot.value >= 0x424;
}

THUMB unsigned short twn::TownPlayerManager::getDamageColor(int type)
{
    switch (type) {
    case 1:
        return TownPartyDraw::colorDoku;
    case 0:
        return TownPartyDraw::colorBarrier;
    case 2:
        return TownPartyDraw::colorYogan;
    }
    return 0x7fff;
}

THUMB void twn::TownPlayerManager::setShadow()
{
    static const dss::Fix32 unk_021517b0(0x2cd);
    static const dss::Fix32 fixMax(0x5000);
    if (shadowSet_ == 1) {
        int floorPoly = TownStageManager::getSingleton()->coll_.floorPolygonNo_;
        dss::Fix32Vector3 floorPos;
        TownStageManager::getSingleton()->stage_.collGetPolygonPos(floorPoly, &floorPos);
        allShadowReset_ = 0;
        dss::Fix32Vector3 position(cmn::g_cmnPartyInfo.position_);
        for (int i = 0; i < getPartyDrawCount(); i++) {
            dss::Fix32Vector3 pos(party_.getMemberPos(i));
            if (position.vx == pos.vx && position.vz == pos.vz) {
                if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0) == -1 || floorPoly == -1) {
                    partyDraw_.partyCharacter_[i].setShadowAlpha(0);
                } else {
                    floorPos.vx = pos.vx;
                    floorPos.vz = pos.vz;
                    partyDraw_.partyCharacter_[i].setShadowPos(floorPos);
                    dss::Fix32 vol = (fixMax - (pos.vy - floorPos.vy)) / fixMax * 12;
                    if (vol < dss::Fix32(0L)) {
                        vol = 0L;
                    }
                    int alpha = (unsigned char)(vol.value / 4096);
                    alpha = dss::clamp<unsigned int>(0, alpha, 12);
                    partyDraw_.partyCharacter_[i].setShadowAlpha(alpha);
                    partyDraw_.partyCharacter_[i].setShadowStay(0);
                }
            }
        }
    } else if (allShadowReset_ == 0) {
        partyDraw_.partyCharacter_[0].setShadowStay(1);
        partyDraw_.partyCharacter_[0].setShadowAlpha(12);
        int floorPoly = TownStageManager::getSingleton()->coll_.floorPolygonNo_;
        dss::Fix32Vector3 floorPos;
        TownStageManager::getSingleton()->stage_.collGetPolygonPos(floorPoly, &floorPos);
        allShadowReset_ = 1;
        dss::Fix32Vector3 position(cmn::g_cmnPartyInfo.position_);
        for (int i = 1; i < getPartyDrawCount(); i++) {
            dss::Fix32Vector3 pos(party_.getMemberPos(i));
            int value = pos.vy.value - floorPos.vy.value;
            if (value >= 0 && value < 0x3c) {
                partyDraw_.partyCharacter_[i].setShadowStay(1);
                partyDraw_.partyCharacter_[i].setShadowAlpha(12);
            } else {
                allShadowReset_ = 0;
            }
        }
    }
}

THUMB void twn::TownPlayerManager::setMenuAction(int type)
{
    setRemote(true);
    switch (type) {
    case cmn::MENU_RURA_SUCCESS:
        player_.actionType_ = ACTION_TYPE_RURA;
        partyDraw_.setExcute(false);
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        player_.townActionRura_.startCheck();
        break;
    case cmn::MENU_RURA_FAILED:
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        player_.townActionRuraFailed_.startCheck();
        player_.actionType_ = ACTION_TYPE_RURA_FAILED;
        break;
    case cmn::MENU_RIREMIT:
        player_.actionType_ = ACTION_TYPE_RIREMITO;
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        player_.townActionRiremito_.start();
        break;
    case cmn::MENU_RANARUTA:
        player_.actionType_ = ACTION_TYPE_RANARUTA;
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        player_.townActionRanaruta_.start();
        break;
    case cmn::MENU_KIMERA:
        status::g_StageInfo.setRuraTownID(status::g_StageInfo.kimeraSymbol_);
        player_.actionType_ = ACTION_TYPE_RURA;
        partyDraw_.setExcute(false);
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        player_.townActionRura_.startCheck();
        break;
    case cmn::MENU_SORATOBU_START:
        cmn::g_extraMapLink.soratobu_ = 1;
        player_.actionType_ = ACTION_TYPE_RURA;
        partyDraw_.setExcute(false);
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        player_.townActionRura_.startCheck();
        break;
    case cmn::TABI_LINK:
        setRemote(true);
        player_.actionType_ = ACTION_TYPE_TABI;
        player_.townActionTabi_.start(0, true);
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        break;
    }
}

THUMB void twn::TownPlayerManager::scriptExecute()
{
    dss::Fix32Vector3 nowPos = getPosition();
    dss::Fix32Vector3 nextPos = nowPos;
    short dirIdx = getDirection();
    scriptMove_.execMove(nextPos);
    if (rotLock_ == 1) {
        setDirection(dirIdx);
    } else if (nextPos != nowPos) {
        dss::Fix32Vector3 vec = nextPos - nowPos;
        short idx = getDirection();
        TownActionCalculate::getIdxByVec(idx, vec);
        setDirection(idx);
    }
    int coll = scriptColl_;
    if ((coll & 2) || (coll & 1)) {
        TownStageManager::getSingleton()->characoterColl(nowPos, nextPos, TownPlayerAction::collR, &nextPos, coll);
    }
    if (scriptColl_ & 4) {
        dss::Fix32Vector3 pos = nextPos;
        TownCharacterManager::getSingleton()->characterColl(nowPos, nextPos, TownPlayerAction::townCharaR);
        if (nextPos != pos) {
            nextPos = nowPos;
            scriptMove_.setup();
            scriptType_ = 6;
            setMoveToFirstFlag();
        }
    }
    setPosition(nextPos);
    if (player_.actionType_ == ACTION_TYPE_IKADA) {
        player_.townActionIkada_.setIkadaPosition(nextPos);
    }
    if (scriptType_ == 4) {
        player_.townActionIkada_.setIkadaPosition(nextPos);
    }
    if (scriptMove_.moveUpdate() == true) {
        party_.script_ = 0;
        party_.fixFlag_ = 0;
        switch (scriptType_) {
        case 2:
            partyDraw_.partyCharacter_[0].setShadowFlag(1);
            setMoveToFirstFlag();
            scriptType_ = 3;
            break;
        case 3:
            if (getMoveToFirstFlag() == false) {
                scriptType_ = 0;
                setLock(false);
                for (int i = 0; i < partyDraw_.countReal_; i++) {
                    partyDraw_.partyCharacter_[i].setShadowFlag(1);
                }
            }
            break;
        default:
            scriptType_ = 0;
            shadowSet_ = 0;
            setLock(false);
            break;
        }
    }
}

THUMB void twn::TownPlayerManager::setScriptRot(int frame, short idx, int flag)
{
    scriptRotFlag_ = 1;
    dss::Vector3<short> start(0, getDirection(), 0);
    if (flag == 0) {
        idx = -idx;
    }
    dss::Vector3<short> rot(0, idx, 0);
    scriptMove_.setSimpleRot(start, rot, frame);
}

THUMB void twn::TownPlayerManager::setStartEraseParty()
{
    party_.changeAlpha_ = 1;
    for (int i = 1; i < getPartyDrawCount(); i++) {
        partyDraw_.setAlpha(i, 0);
    }
}

THUMB void twn::TownPlayerManager::rizeupSet(int icon)
{
    riseupIndex_ = TownRiseupManager::getSingleton().setup(icon, getPosition());
}

THUMB bool twn::TownPlayerManager::rizeupEnd()
{
    return TownRiseupManager::getSingleton().isFinish(riseupIndex_);
}

THUMB int twn::TownPlayerManager::getInpasMapObj()
{
    return player_.townActionWalk_.getMapUid();
}

THUMB bool twn::TownPlayerManager::getPlayerCopyInfo(int playerNo, dss::Fix32Vector3& pos, short& idx, int& charNo)
{
    status::g_Party.setDisplayMode();
    int count = status::g_Party.getCarriageOutCount();
    for (int i = 0; i < count; i++) {
        if (playerNo == status::g_Party.getPlayerStatus(i).getPlayerIndex()) {
            charNo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getCharaIndex();
            pos = party_.getMemberPos(i);
            idx = party_.getMemberDir(i);
            partyDraw_.setAlpha(i, 0);
            return true;
        }
    }
    return false;
}

THUMB void twn::TownPlayerManager::setIkadaSpeedMove(dss::Fix32Vector3& prev, dss::Fix32Vector3& next, dss::Fix32 speed)
{
    setSpeedMove(prev, next, speed);
    scriptType_ = 4;
}

THUMB void twn::TownPlayerManager::setIkadaFrameMove(dss::Fix32Vector3& prev, dss::Fix32Vector3& next, int frame)
{
    setSimpleMove(prev, next, frame);
    scriptType_ = 4;
}

THUMB void twn::TownPlayerManager::setIkadaMove()
{
    scriptType_ = 4;
    player_.actionType_ = ACTION_TYPE_IKADA;
    player_.townActionIkada_.moveMode_ = 0;
}

THUMB void twn::TownPlayerManager::rizeupSetParty(int charaNo, int markNo)
{
    status::g_Party.setDisplayMode();
    int count = status::g_Party.getCarriageOutCount();
    for (int i = 0; i < count; i++) {
        if (charaNo == status::g_Party.getPlayerStatus(i).getPlayerIndex()) {
            TownRiseupManager::getSingleton().setup(markNo, party_.getMemberPos(i));
        }
    }
}

THUMB void twn::TownPlayerManager::setVanAndBasha()
{
    partyDraw_.setVanAndBasha();
}

THUMB bool twn::TownPlayerManager::isSaveAndBattleOK()
{
    bool ret = true;
    if (player_.actionType_ == ACTION_TYPE_ROPE || player_.actionType_ == ACTION_TYPE_FALL) {
        ret = false;
    }
    if (player_.townActionKaidan_.isSaveOK() == false) {
        ret = false;
    }
    return ret;
}

THUMB void twn::TownPlayerManager::scriptColl(dss::Fix32Vector3& nextPos, short& dirIdx)
{
}

THUMB bool twn::TownPlayerManager::checkSearchMapObj(bool searchFlag)
{
    bool floor;
    int floorMapUid = TownExtraMapObjManager::getSingleton().checkFloorMapUid(cmn::g_cmnPartyInfo.position_);
    floor = false;
    if (floorMapUid != 0) {
        floor = true;
        searchMapUid_ = floorMapUid;
        TownFurnitureManager::getSingleton()->checkObject(floorMapUid, false, floor, floor);
        if (TownFurnitureManager::getSingleton()->prevCheck_ == 2 || TownFurnitureManager::getSingleton()->prevCheck_ == 3) {
            cmn::PartyTalk::getSingleton().resetPartyTalk();
            return true;
        }
    }
    int searchObjectId = player_.townActionWalk_.searchObjectId_;
    int mapUid = TownStageManager::getSingleton()->getMapObjUid(searchObjectId);
    if (mapUid == 0) {
        floor = true;
        mapUid = TownStageManager::getSingleton()->coll_.floorMapUid_;
    }
    if (mapUid != 0) {
        searchMapUid_ = mapUid;
        bool searchObjectSide;
        if (floor == false && isMapObjBackSide(mapUid) == true) {
            searchObjectSide = true;
        } else {
            searchObjectSide = false;
        }
        if (TownFurnitureManager::getSingleton()->checkObject(mapUid, searchObjectSide, searchFlag, 0)) {
            int commonId = TownStageManager::getSingleton()->getCommonID(searchObjectId);
            if (commonId == 0xc1c || commonId == 0xd48) {
                player_.townActionWalk_.searchObjectId_ = -1;
            }
            return true;
        }
    }
    if (player_.townActionWalk_.isIdoMonster(mapUid) == true) {
        setLock(true);
        status::g_StageInfo.encountMapUid_ = mapUid;
        return true;
    }
    return false;
}

THUMB bool twn::TownPlayerManager::checkIdo()
{
    if (player_.actionType_ == ACTION_TYPE_ROPE) {
        return false;
    }
    int idoSurfaceid = player_.townActionWalk_.idoSurfaceid_;
    if (idoSurfaceid != -1 && TownStageManager::getSingleton()->getHitSurfaceIdByType(6) == -1) {
        TownStageManager::getSingleton()->coll_.surfaceType_[5] = idoSurfaceid;
        if (isIdoLinkPos() == true) {
            flagIdoLink_ = 1;
            status::g_StageInfo.idoLinkInFlag_ = 1;
            status::g_StageInfo.idoLinkDirIdx_ = getDirection();
            dss::Fix32Vector3 pos = getPosition();
            status::g_StageInfo.idoLinkPos_ = pos;
            flagMapLink_ = 0;
            return true;
        }
    }
    return false;
}

THUMB bool twn::TownPlayerManager::checkTalkToCharacter()
{
    int ctrSurfaceId;
    int searchPolyNo;
    int searchObjectId;
    searchObjectId = player_.townActionWalk_.searchObjectId_;
    ctrSurfaceId = player_.townActionWalk_.ctrSurfaceId_;
    searchPolyNo = player_.townActionWalk_.searchPolyNo_;
    dss::Fix32 len;
    len = TownPlayerAction::walkCtrLen;
    TownActionCalculate::checkFarTalk(cmn::g_cmnPartyInfo.position_, ctrSurfaceId, searchObjectId, searchPolyNo, len);
    if (TownActionCalculate::checkTalking(cmn::g_cmnPartyInfo.position_, cmn::g_cmnPartyInfo.dirIdx_, searchObjectId) == true) {
        return true;
    }
    return false;
}

THUMB bool twn::TownPlayerManager::isMapObjBackSide(int uid)
{
    dss::Fix32Vector3 vec = getPosition() - TownStageManager::getSingleton()->getMapUidPos(uid);
    vec.vy = 0L;
    vec.normalize();
    dss::Fix32Vector3 dir = TownStageManager::getSingleton()->getMapUidRot(uid);
    TownActionCalculate::getDirByIdx(dir.vy.value, dir);
    dss::Fix32 dot = vec * dir;
    if (dot.value <= -0x6c3) {
        return true;
    }
    return false;
}

THUMB bool twn::TownPlayerManager::checkScriptSearch()
{
    bool backSide = false;
    int MapUid = TownExtraMapObjManager::getSingleton().checkFloorMapUid(cmn::g_cmnPartyInfo.position_);
    if (MapUid <= 0) {
        int searchObjectId = player_.townActionWalk_.searchObjectId_;
        MapUid = TownStageManager::getSingleton()->getMapObjUid(searchObjectId);
        if (MapUid == 0) {
            MapUid = TownStageManager::getSingleton()->coll_.floorMapUid_;
        } else if (isMapObjBackSide(MapUid) == true) {
            backSide = true;
        }
    }
    if (MapUid > 0) {
        if (TownFurnitureManager::getSingleton()->checkCoffer(MapUid) == 1) {
            return false;
        }
        if (backSide == true) {
            int index = TownFurnitureManager::getSingleton()->getFurnitureIndex(MapUid);
            if (index != -1 && TownFurnitureManager::getSingleton()->checkRevMessage(index) == true) {
                return false;
            }
        }
        for (int i = 0; i < SCRIPT_SEARCH_OBJECT_NUM; i++) {
            if (MapUid == scriptSearchUid_[i]) {
                searchMapUid_ = MapUid;
                return true;
            }
        }
        if (uid1_ <= MapUid && uid2_ >= MapUid) {
            searchMapUid_ = MapUid;
            return true;
        }
    }
    return false;
}

THUMB void twn::TownPlayerManager::scriptTruckAction()
{
    if (player_.townActionTruck_.scriptFlag_ != 0) {
        player_.townActionTruck_.scriptMove();
        int max = TownCharacterManager::getSingleton()->townCharacterCount_;
        for (int i = 0; i < max; i++) {
            if (TownCharacterManager::getSingleton()->character_[i]->moveType_ == 12) {
                TownCharacterManager::getSingleton()->character_[i]->mapObjMove();
            }
        }
    }
}

THUMB void twn::TownPlayerManager::setDistance()
{
    dss::Fix32 distance(0x666);
    dq5::level::CharacterWidth::setup();
    int dstMax = dq5::level::CharacterWidth::binary_.getRecordCount();
    dss::Fix32 disF;
    dss::Fix32 disB;
    dss::Fix32 disR;
    dss::Fix32 disL;
    for (int i = 0; i < partyDraw_.countReal_; i++) {
        int charaIndex = partyDraw_.charaIndex_[i];
        for (int j = 0; j < dstMax; j++) {
            if (charaIndex == dq5::level::CharacterWidth::getRecord(j)->index) {
                disF = dq5::level::CharacterWidth::getRecord(j)->townFront;
                disB = dq5::level::CharacterWidth::getRecord(j)->townBack;
                if (disF == dss::Fix32(0L)) {
                    disF = distance;
                }
                if (disB == dss::Fix32(0L)) {
                    disB = distance;
                }
                if (disR == dss::Fix32(0L)) {
                    disR = distance;
                }
                if (disL == dss::Fix32(0L)) {
                    disL = distance;
                }
                party_.setCharaDistance(i, disF, disB, disR, disL);
                break;
            }
        }
    }
    dq5::level::CharacterWidth::cleanup();
}
