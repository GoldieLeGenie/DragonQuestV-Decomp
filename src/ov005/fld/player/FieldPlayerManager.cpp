#include "ov005/fld/FieldPlayerManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/WorldLocation.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/leveldata/CharacterWidth.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "ov005/fld/FieldActionCalculate.hpp"
#include "ov005/fld/FieldPlayerDoku.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov005/fld/FieldSymbolManager.hpp"
#include "ov005/fld/FieldSystem.hpp"

inline void cmn::PartyMoveAction::setPartyState(PARTY_ACTION_STATE state)
{
    state_ = state;
}

inline cmn::PartyMoveAction::PARTY_ACTION_STATE cmn::PartyMoveAction::getPartyState()
{
    return state_;
}

inline void cmn::PartyMoveAction::setSpeed(dss::Fix32 speed)
{
    memberSpeed_ = speed;
}

inline void cmn::CommonPartyInfo::setPrevPosition()
{
    prev_position_ = position_;
}

inline int cmn::CommonPartyInfo::isPrevLocation()
{
    return prevLocation_;
}

inline void cmn::CommonPartyInfo::setPrevLocation(bool flag)
{
    prevLocation_ = flag;
}

inline cmn::MENU_ACTION cmn::CommonPartyInfo::getMenuAction()
{
    return menuAction_;
}

inline cmn::PARTY_RIDE_ON_TYPE cmn::CommonPartyInfo::getRideOn()
{
    return rideOnType_;
}

inline void cmn::CommonPartyInfo::setPartyTalkEnable(bool flag)
{
    partyTalk = flag;
}

inline int status::StageInfo::getEncountFlag()
{
    return encount_;
}

inline void status::StageInfo::setEncountFlag(bool flag)
{
    encount_ = flag;
}

inline void status::StageInfo::setShipEncount(bool flag)
{
    shipEncount_ = flag;
}

inline void status::StageInfo::setSymbolID(int sy)
{
    symbolID_ = sy;
}

inline void status::StageInfo::setRiremitMapId(int id)
{
    riremitMap_ = id;
}

inline int status::StageInfo::getkimeraSymbol()
{
    return kimeraSymbol_;
}

inline int status::StageAttribute::getTimestopFlag()
{
    return timestop_;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline void cmn::ExtraMapLink::setSoratobu()
{
    soratobu_ = true;
}

inline void fld::FieldSystem::setExitSound(int flag)
{
    exitSound_ = flag;
}

inline void fld::FieldSymbolManager::setResetFlag(bool flag)
{
    resetFlag_ = flag;
}

inline void fld::FieldStage::drawRuramoon()
{
    fieldData.drawRuramonn();
}

inline void fld::FieldPartyDraw::setShadowFlag(int index, int flag)
{
    partyCharacter_[index].setShadowFlag(flag);
}

inline unsigned short fld::FieldPartyDraw::colorDokuParty()
{
    return colorDoku;
}

inline unsigned short fld::FieldPartyDraw::colorBarrierParty()
{
    return colorBarrier;
}

inline void fld::FieldPlayerManager::setDrawNone()
{
    partyDraw_.setDrawNone();
}

inline dq5::level::CharacterWidth* dq5::level::CharacterWidth::getRecord(int index)
{
    return (CharacterWidth*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::CharacterWidth::getArraySize()
{
    return binary_.record_;
}

inline unsigned short dq5::level::CharacterWidth::getIndex()
{
    return index;
}

inline fx32 dq5::level::CharacterWidth::getFieldFront()
{
    return fieldFront;
}

inline fx32 dq5::level::CharacterWidth::getFieldBack()
{
    return fieldBack;
}

inline fx32 dq5::level::CharacterWidth::getFieldRight()
{
    return fieldRight;
}

inline fx32 dq5::level::CharacterWidth::getFieldLeft()
{
    return fieldLeft;
}

THUMB inline void fld::FieldPlayerManager::setDirection(short idx)
{
    dirIdx_ = idx;
}

THUMB inline short fld::FieldPlayerManager::getDirection()
{
    return dirIdx_;
}

THUMB fld::FieldPlayerManager::FieldPlayerManager()
    : position_(cmn::g_cmnPartyInfo.position_), dirIdx_(cmn::g_cmnPartyInfo.dirIdx_)
{
}

THUMB fld::FieldPlayerManager& fld::FieldPlayerManager::getSingleton()
{
    static FieldPlayerManager fieldPlayerManager;
    return fieldPlayerManager;
}

THUMB void fld::FieldPlayerManager::initialize()
{
    locked_ = false;
    dummyPosFlag_ = false;
    eventEncount_ = false;
    int index = util::StageLink::getFieldSymbolIndex();
    dss::Fix32Vector3 pos;
    if (index != -1) {
        pos = FieldStage::getSingleton()->getSymbolPosition(index);
    }
    if (dirIdx_ > 7 || dirIdx_ < 0) {
        dirIdx_ = 0;
        position_.set(0, 0, 0);
    }
    partyDraw_.setup();
    carpetDraw_.setup();
    FieldShipDraw::initialize();
    shipDraw_[0].setup();
    shipDraw_[1].setup();
    firmamentDraw_.setup();
    fieldDragonDraw_.setup();
    fieldDragonDraw_.setDisplayEnable(0);
    shipDraw_[0].setPosition(status::g_StageInfo.shipPosition_[0]);
    shipDraw_[1].setPosition(status::g_StageInfo.shipPosition_[1]);
    firmamentDraw_.setPosition(status::g_StageInfo.firmamentPosition_);
    scriptMoveFlag_ = false;
    SpriteCharacter::setAllCharaAnim(1);
    cmn::g_cmnPartyInfo.setPartyTalkEnable(true);
    status::g_StageInfo.setRiremitMapId(999);
    height_ = 0;
}

THUMB void fld::FieldPlayerManager::terminate()
{
    switch (cmn::g_cmnPartyInfo.getMenuAction()) {
    case cmn::MENU_RURA_AFTER:
    case cmn::MENU_SORATOBU_SWITCH:
        break;
    default:
        status::g_StageInfo.shipPosition_[0] = shipDraw_[0].getPosition();
        status::g_StageInfo.shipPosition_[1] = shipDraw_[1].getPosition();
        status::g_StageInfo.firmamentPosition_ = firmamentDraw_.getPosition();
        break;
    }
    partyDraw_.cleanup();
    shipDraw_[0].cleanup();
    shipDraw_[1].cleanup();
    firmamentDraw_.cleanup();
    fieldDragonDraw_.cleanup();
    FieldShipDraw::terminate();
    carpetDraw_.cleanup();
}

THUMB void fld::FieldPlayerManager::execute()
{
    cmn::g_cmnPartyInfo.setPrevPosition();
    searchMapUid_ = 0;
    dss::Fix32Vector3 prevPos = position_;
    normalExec();
    everyExec();
    cmn::WorldLocation::calcWorldPos(position_.vx.value, position_.vy.value);
    party_.execute();
    if (dummyPosFlag_ == true) {
        position_ = dummyPos_;
    }
}

THUMB void fld::FieldPlayerManager::draw()
{
    for (int i = 0; i < partyDraw_.countReal_; i++) {
        dss::Vector2<int> pos = FieldStage::getSingleton()->calcDrawPosition((dss::Fix32Vector3&)party_.getMemberPos(i));
        if (i > 0) {
            if (party_.getMemberPos(0).vx.value < party_.getMemberPos(i).vx.value) {
                if (party_.getMemberPos(i).vx.value % 0x1000 + (0x1000 - party_.getMemberPos(0).vx.value % 0x1000) >= 0x1000) {
                    pos.vx++;
                }
            } else if (party_.getMemberPos(i).vx.value < party_.getMemberPos(0).vx.value) {
                if (party_.getMemberPos(0).vx.value % 0x1000 + (0x1000 - party_.getMemberPos(i).vx.value % 0x1000) >= 0x1000) {
                    pos.vx--;
                }
            }
            if (party_.getMemberPos(0).vy.value < party_.getMemberPos(i).vy.value) {
                if (party_.getMemberPos(i).vy.value % 0x1000 + (0x1000 - party_.getMemberPos(0).vy.value % 0x1000) >= 0x1000) {
                    pos.vy++;
                }
            } else if (party_.getMemberPos(i).vy.value < party_.getMemberPos(0).vy.value) {
                if (party_.getMemberPos(0).vy.value % 0x1000 + (0x1000 - party_.getMemberPos(i).vy.value % 0x1000) >= 0x1000) {
                    pos.vy--;
                }
            }
        }
        pos.vy -= height_;
        partyDraw_.setPosition(i, pos);
        partyDraw_.setDepth(i, party_.getMemberPos(i).vy.value);
        partyDraw_.setRotate(i, (unsigned short)party_.getMemberDir(i));
    }
    partyDraw_.draw();
    FieldStage::getSingleton()->drawRuramoon();
}

THUMB void fld::FieldPlayerManager::setup()
{
    flagMapLink_ = false;
    int index = util::StageLink::getFieldSymbolIndex();
    if (index != -1 && status::g_StageInfo.getEncountFlag() == false && cmn::g_cmnPartyInfo.isPrevLocation() == false) {
        dss::Fix32Vector3 pos;
        pos = FieldStage::getSingleton()->getSymbolPosition(index);
        index &= 0xfff;
        FieldStage::getSingleton()->setSymbolFlag(index);
        switch (index) {
        case 0x1a:
            pos.vy += 0x20;
            break;
        case 0x2e:
        case 0x2f:
            pos.vy.value += 0x9000;
            break;
        case 0x5c:
            pos.vx.value += 0x7000;
            pos.vy.value += 0x10000;
            break;
        }
        dirIdx_ = 4;
        position_.vx = pos.vx;
        position_.vy = pos.vy;
    }
    flagMapLink_ = true;
    cmn::g_extraMapLink.setExtraFieldPos(position_, dirIdx_);
    dss::Fix32Vector3 target;
    player_.setup();
    party_.setup();
    setDistance();
    if (cmn::g_cmnPartyInfo.getRideOn() == cmn::RIDE_ON_SHIP_IKADA) {
        FieldPlayerManager::getSingleton().setDrawNone();
    }
    if (status::g_StageInfo.getEncountFlag() != true) {
        FieldPlayerDoku::getSingleton().setup();
    }
    status::g_StageInfo.setShipEncount(false);
    status::g_StageInfo.setEncountFlag(false);
    cmn::g_cmnPartyInfo.setPrevLocation(false);
    if (g_Global.isAreaChange() == true) {
        cmn::g_cmnPartyInfo.resetShipIkadaMapName();
    }
}

THUMB void fld::FieldPlayerManager::cleanup()
{
    player_.cleanup();
    party_.cleanup();
}

THUMB void fld::FieldPlayerManager::everyExec()
{
}

THUMB void fld::FieldPlayerManager::normalExec()
{
    int x;
    int y;
    if (isLock()) {
        if (scriptMoveFlag_ == true) {
            dss::Fix32Vector3 nextPos = position_;
            scriptMove_.execMove(nextPos);
            if (scriptMove_.moveUpdate() == true) {
                scriptMoveFlag_ = false;
                party_.setSpeed(FieldActionBase::Speed);
            }
            if (position_ != nextPos) {
                dss::Fix32Vector3 vec = nextPos - position_;
                dirIdx_ = FieldActionCalculate::getDir8ByVector3(vec);
                if (status::g_StageAttribute.getTimestopFlag() != true && status::g_Story.getChapter() != dq5::CHAPTER_YOUNENKI && g_Global.getFieldType() == 0) {
                    FieldStage::getSingleton()->ChangeTime(0);
                }
            }
            position_ = nextPos;
            cmn::WorldLocation::calcWorldPos(position_.vx.value, position_.vy.value);
            status::g_StageInfo.setMapVeil(position_.vx.value / 16 / 0x1000, position_.vy.value / 16 / 0x1000, 0);
        }
        switch (player_.getMoveType()) {
        case 1:
        case 5:
        case 7:
            player_.execute();
            break;
        }
    } else {
        dss::Fix32Vector3 nowPos = position_;
        player_.execute();
        cmn::WorldLocation::calcWorldPos(position_.vx.value, position_.vy.value);
        if (nowPos != position_) {
            FieldSymbolManager::getSingleton().setResetFlag(true);
        }
        if (g_Global.getFieldType() == 0) {
            x = position_.vx.value / 16 / 0x1000;
            y = position_.vy.value / 16 / 0x1000;
            if (player_.getMoveType() != 2) {
                status::g_StageInfo.setMapVeil(x, y, 0);
            }
        }
        if (nowPos != position_ && remote_ == false) {
            talkRefresh_++;
            if (talkRefresh_ >= 0xf0) {
                talkRefresh_ = 0;
                cmn::PartyTalk::getSingleton().resetWalkPartyTalk();
            }
            if (status::g_StageAttribute.getTimestopFlag() != true && status::g_Story.getChapter() != dq5::CHAPTER_YOUNENKI && g_Global.getFieldType() == 0) {
                FieldStage::getSingleton()->ChangeTime(0);
            }
            player_.getMoveType();
        }
    }
}

THUMB bool fld::FieldPlayerManager::isTenkuNearAreaGetOn()
{
    if (g_Global.getFieldType() != 0) {
        return false;
    }
    if (status::g_Story.isVehicleEnable(3) == false) {
        return false;
    }
    dss::Fix32Vector3 vec = cmn::g_cmnPartyInfo.position_ - firmamentDraw_.getPosition();
    vec.vz = 0L;
    if (dss::abs<long>(vec.vx.value) <= 0x30000 && dss::abs<long>(vec.vy.value) <= 0x30000) {
        if (vec.lengthsq() <= dss::Fix32(0x100L)) {
            return true;
        }
    }
    return false;
}

THUMB bool fld::FieldPlayerManager::isTenkuNearArea()
{
    if (g_Global.getFieldType() != 0) {
        return false;
    }
    if (status::g_Story.isVehicleEnable(3) == false) {
        return false;
    }
    dss::Fix32Vector3 vec = cmn::g_cmnPartyInfo.prev_position_ - firmamentDraw_.getPosition();
    vec.vz = 0L;
    if (dss::abs<long>(vec.vx.value) <= 0x30000 && dss::abs<long>(vec.vy.value) <= 0x30000) {
        if (vec.lengthsq() > dss::Fix32(0x100L)) {
            vec = cmn::g_cmnPartyInfo.position_ - firmamentDraw_.getPosition();
            vec.vz = 0L;
            if (dss::abs<long>(vec.vx.value) <= 0x30000 && dss::abs<long>(vec.vy.value) <= 0x30000) {
                if (vec.lengthsq() <= dss::Fix32(0x100L)) {
                    return true;
                }
            }
        }
    }
    return false;
}

THUMB void fld::FieldPlayerManager::execMapLink()
{
    dss::Fix32Vector3 pos = getPosition();
    int index = FieldStage::getSingleton()->getSearchSymbolAttach(pos, NULL);
    if (index == -1) {
        if (flagMapLink_ == true) {
            if (cmn::g_extraMapLink.checkFieldRectLinkNo(pos) == -1) {
                flagMapLink_ = false;
            }
        } else {
            int ret = cmn::g_extraMapLink.checkFieldRectLinkByType(pos, 7);
            if (ret != 0) {
                FieldSystem::getSingleton()->setExitSound(true);
                status::g_StageInfo.setSymbolID(ret);
                flagMapLink_ = true;
            }
        }
        if (player_.getMoveType() == 0 && isTenkuNearArea() == true) {
            FieldSystem::getSingleton()->setExitSound(true);
            cmn::g_extraMapLink.setExtraExitTown(0x51, 0x70001);
        }
        return;
    }
    if (flagMapLink_ != false) {
        return;
    }
    if (player_.getMoveType() == 5) {
        return;
    }
    if (player_.getMoveType() == 6) {
        return;
    }
    if (player_.getMoveType() == 7 && index != 0x27) {
        return;
    }
    if (player_.getMoveType() == 1 && index != 0x1a && index != 0x2e && index != 0x2f) {
        flagMapLink_ = true;
        return;
    }
    if (cmn::g_extraMapLink.checkFieldToTownTabi(index)) {
        flagMapLink_ = true;
        player_.setMoveType(4);
        player_.fieldActionTabi_.start(index, 0);
        status::g_StageInfo.setRiremitMapId(999);
        status::g_StageInfo.setSymbolID(index);
        return;
    }
    int ret = cmn::g_extraMapLink.checkFieldLink(index);
    if (ret == 4) {
        return;
    }
    if (ret == 3) {
        FieldSystem::getSingleton()->setExitSound(true);
        util::StageLink::setTownExitIndex(util::StageLink::getSymbolIndex());
        status::g_StageInfo.setSymbolID(index);
        flagMapLink_ = true;
        return;
    }
    int nextId = util::StageLink::getNameId(999, index);
    if (nextId != 0) {
        FieldStage::getSingleton()->setSymbolFlag(index);
        util::StageLink::setTownExitIndex(util::StageLink::getSymbolIndex());
        status::g_StageInfo.setSymbolID(index);
        g_Global.startTown(nextId);
        setLock(true);
        FieldSystem::getSingleton()->setExitSound(true);
        flagMapLink_ = true;
    }
}

THUMB void fld::FieldPlayerManager::setPosition(dss::Fix32Vector3& pos)
{
    position_ = pos;
}

THUMB void fld::FieldPlayerManager::inputPad(int dir)
{
    player_.inputPad(dir);
}

THUMB void fld::FieldPlayerManager::inputClear()
{
    player_.inputClear();
}

THUMB void fld::FieldPlayerManager::resetParty()
{
    if (partyDraw_.countReal_ != 0) {
        partyDraw_.cleanup();
        partyDraw_.setup();
        int count = partyDraw_.countReal_;
        for (int i = 0; i < count; i++) {
            dss::Fix32Vector3 pos = party_.getMemberPos(i);
            FieldStage::getSingleton()->calcDrawPosition(pos);
            partyDraw_.setDepth(0, pos.vy.value);
            partyDraw_.setPosition(0, FieldStage::getSingleton()->calcDrawPosition(pos));
            partyDraw_.setRotate(0, party_.getMemberDir(i));
        }
    }
    setDistance();
    if (player_.getMoveType() == 1) {
        setDrawNone();
    }
}

THUMB dq5::LandType fld::FieldPlayerManager::getLandType()
{
    switch (getAttr()) {
    case WMAP_ATTR_NOT:
        return dq5::Floor;
    case WMAP_ATTR_SOUG:
        return dq5::Field;
    case WMAP_ATTR_SIGE:
        return dq5::Bush;
    case WMAP_ATTR_SUNA:
        return dq5::Desert;
    case WMAP_ATTR_MORI:
        return dq5::Forest;
    case WMAP_ATTR_YAMA1:
        return dq5::Mountain;
    case WMAP_ATTR_YAMA2:
        return dq5::Lock;
    case WMAP_ATTR_KAIG:
        return dq5::Field;
    case WMAP_ATTR_UMI:
        return dq5::Sea;
    case WMAP_ATTR_ASAS:
        return dq5::Sea;
    case WMAP_ATTR_DOKU:
        return dq5::Pond;
    }
    return dq5::Floor;
}

THUMB int fld::FieldPlayerManager::getAttr()
{
    int blkX = position_.vx.value / 0x10000;
    int blkY = position_.vy.value / 0x10000;
    return FieldStage::getSingleton()->getBlockAttr2(blkX, blkY);
}

THUMB fld::FieldCarrirerDraw* fld::FieldPlayerManager::getCarrierDraw(int type)
{
    switch (type) {
    case 0:
        return &shipDraw_[0];
    case 1:
        return &shipDraw_[1];
    case 2:
        return &carpetDraw_;
    case 3:
        return &firmamentDraw_;
    case 4:
        return &fieldDragonDraw_;
    }
    return NULL;
}

THUMB void fld::FieldPlayerManager::unkfunc_02131c70()
{
}

THUMB void fld::FieldPlayerManager::setRemote(bool flag)
{
    if (flag == true) {
        FieldPlayerDoku::getSingleton().resetMemberColor();
    }
    remote_ = flag;
}

THUMB unsigned short fld::FieldPlayerManager::getDamageColor(int type)
{
    switch (type) {
    case 1:
        return partyDraw_.colorDokuParty();
    case 0:
        return partyDraw_.colorBarrierParty();
    case 3:
        return 0x7fff;
    }
    return 0x7fff;
}

THUMB void fld::FieldPlayerManager::setSimpleMove(dss::Fix32Vector3 target, dss::Fix32 rate, int absFlag)
{
    target = absFlag == true ? target + position_ : target;
    scriptMove_.setActionMove(position_, target);
    dss::Fix32 speed = rate * FieldActionBase::Speed;
    party_.setSpeed(speed);
    scriptMove_.setMoveSpeed(speed);
    scriptMove_.setRough(true);
    scriptMoveFlag_ = true;
}

THUMB void fld::FieldPlayerManager::setDirectionMove(dss::Fix32 target, int dir)
{
    scriptMoveFlag_ = true;
    dss::Fix32 speed(0x1800);
    scriptMove_.setDirMove(target, dir, FieldActionBase::balSpeed * speed);
}

THUMB void fld::FieldPlayerManager::setScriptGetDownShip(int dir)
{
}

THUMB int fld::FieldPlayerManager::isEndScriptGetDownShip()
{
    if (player_.getMoveType() == 0) {
        return true;
    }
    return false;
}

THUMB void fld::FieldPlayerManager::resetLockByEventEncount()
{
    if (eventEncount_ == true) {
        setLock(false);
        eventEncount_ = false;
    }
}

THUMB void fld::FieldPlayerManager::setMoveToFirstFlag()
{
    party_.setPartyState(cmn::PartyMoveAction::MOVE_TO_FIRST);
}

THUMB bool fld::FieldPlayerManager::getMoveToFirstFlag()
{
    return party_.getPartyState() == cmn::PartyMoveAction::MOVE_TO_FIRST;
}

THUMB void fld::FieldPlayerManager::resetDrawPartyCount()
{
    partyDraw_.resetDrawCount();
}

THUMB void fld::FieldPlayerManager::setPartyDrawOne()
{
    partyDraw_.setDrawPartyOne();
}

THUMB void fld::FieldPlayerManager::setDrawPartyNone()
{
    partyDraw_.setDrawNone();
}

THUMB int fld::FieldPlayerManager::getPartyDrawCount()
{
    return partyDraw_.countReal_;
}

THUMB bool fld::FieldPlayerManager::isEqalNextPos(int index)
{
    return true;
}

THUMB char fld::FieldPlayerManager::getPartyDrawAlpha(int index)
{
    return 0x1f;
}

THUMB void fld::FieldPlayerManager::addPartyDrawAlpha(int index, char add)
{
}

THUMB void fld::FieldPlayerManager::scriptColl(dss::Fix32Vector3& nextPos, short& dirIdx)
{
}

THUMB void fld::FieldPlayerManager::setAllShadow(bool flag)
{
    int count = partyDraw_.countReal_;
    for (int i = 0; i < count; i++) {
        dss::Fix32Vector3 pos = party_.getMemberPos(i);
        if (position_.vx == pos.vx) {
            partyDraw_.setShadowFlag(i, flag);
        }
    }
}

THUMB void fld::FieldPlayerManager::checkMenuAction(int type)
{
    switch (type) {
    case cmn::MENU_RURA_SUCCESS:
        player_.fieldActionRura_.start(0);
        break;
    case cmn::MENU_RURA_AFTER:
        player_.fieldActionRura_.start(1);
        break;
    case cmn::MENU_RANARUTA:
        player_.fieldActionRana_.start(player_.getMoveType());
        break;
    case cmn::MAGIC_CARPET:
        player_.fieldActionCarpet_.setStart();
        break;
    case cmn::TENKU_CASTLE:
        player_.fieldActionCastle_.setStart();
        break;
    case cmn::MENU_KIMERA:
        status::g_StageInfo.setRuraTownID(status::g_StageInfo.getkimeraSymbol());
        player_.fieldActionRura_.start(0);
        break;
    case cmn::MENU_SORATOBU_START:
        cmn::g_extraMapLink.setSoratobu();
        player_.fieldActionRura_.start(0);
        break;
    case cmn::MENU_SORATOBU_SWITCH:
        player_.fieldActionRura_.start(2);
        break;
    case cmn::MASTER_DRAGON:
        player_.setMoveType(7);
        player_.fieldActionDragon_.setStart();
        break;
    case cmn::MASTER_DRAGON_DIRECT:
        player_.fieldActionDragon_.directStart();
        player_.setMoveType(7);
        break;
    case cmn::TABI_LINK:
        setRemote(true);
        player_.setMoveType(4);
        player_.fieldActionTabi_.start(0, 1);
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        break;
    default:
        return;
    }
    cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
}

THUMB bool fld::FieldPlayerManager::checkScriptSearch()
{
    for (int i = 0; i < SCRIPT_SEARCH_OBJECT_NUM; i++) {
        if (scriptSearchUid_[i] != 0 && FieldStage::getSingleton()->getFieldData().isSymbolAttachByUid(scriptSearchUid_[i], position_)) {
            searchMapUid_ = scriptSearchUid_[i];
            return true;
        }
    }
    return false;
}

THUMB void fld::FieldPlayerManager::setDistance()
{
    dss::Fix32 distance = FieldActionBase::Speed * 7;
    dq5::level::CharacterWidth::setup();
    int dstMax = dq5::level::CharacterWidth::getArraySize();
    dss::Fix32 disF;
    dss::Fix32 disB;
    dss::Fix32 disR;
    dss::Fix32 disL;
    for (int i = 0; i < partyDraw_.countReal_; i++) {
        int charaIndex = partyDraw_.charaIndex_[i];
        for (int j = 0; j < dstMax; j++) {
            if (charaIndex == dq5::level::CharacterWidth::getRecord(j)->getIndex()) {
                disF = dq5::level::CharacterWidth::getRecord(j)->getFieldFront();
                disB = dq5::level::CharacterWidth::getRecord(j)->getFieldBack();
                disR = dq5::level::CharacterWidth::getRecord(j)->getFieldRight();
                disL = dq5::level::CharacterWidth::getRecord(j)->getFieldLeft();
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

const unsigned short fld::FieldPartyDraw::colorDoku = 0x48f2;
const unsigned short fld::FieldPartyDraw::colorBarrier = 0x1e52;
