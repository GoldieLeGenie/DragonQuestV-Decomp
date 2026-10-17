#pragma ipa file
#include "ov001/town/TownSugorokuManager.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/UnkRenderObject.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/leveldata/SugorokuChanceCard.hpp"
#include "main/leveldata/SugorokuChangeMsg.hpp"
#include "main/leveldata/SugorokuData.hpp"
#include "main/leveldata/SugorokuDrop.hpp"
#include "main/leveldata/SugorokuPanelList.hpp"
#include "main/leveldata/SugorokuSpecialMsg.hpp"
#include "main/leveldata/SugorokuStage.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/menu/UnkMenuOverlay.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/ShopList.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/town/TownSugorokuInfo.hpp"

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline void Global::setBattleLoseAfterFlag(bool flag)
{
    battleLoseAfterFlag_ = flag;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline void status::ShopList::setSection(int section)
{
    section_ = section;
}

inline void status::StageAttribute::setShopDataIndex(int index)
{
    shopDataIndex_ = index;
}

inline void status::StageInfo::setReliveCheckFlag(bool flag)
{
    reliveCheckFlag_ = flag;
}

inline void status::BattleResult::setPlayerDemolition(bool flag)
{
    playerDemolition_ = flag;
}

inline int status::BattleResult::isPlayerDemolition()
{
    return playerDemolition_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline void cmn::CommonPartyInfo::setPrevLocation(bool flag)
{
    prevLocation_ = flag;
}

inline void twn::TownCommandInitWait::setWait(bool flag)
{
    flag_ = flag;
}

inline void twn::TownSystemCommand::setWait(bool flag)
{
    townCommandInitWait_.setWait(flag);
}

inline void twn::TownSystem::setWait(bool flag)
{
    townSystemCommand_.setWait(flag);
}

inline bool twn::TownSugorokuDice::isFinish()
{
    return enable_ ? false : true;
}

inline unsigned short twn::PanelData::getUid()
{
    return uid_;
}

inline void twn::PanelData::setReverce(PanelData* panel)
{
    reverce_[0] = panel;
}

inline twn::PanelData* twn::PanelData::getBackPanel1()
{
    return reverce_[1];
}

inline char twn::TownSugorokuInfo::getNowMoveCount()
{
    return nowMoveCount;
}

inline void twn::TownSugorokuInfo::setDiceCount(unsigned short count)
{
    diceCount_ = count;
}

inline twn::PanelData* twn::TownSugorokuInfo::getNowPane()
{
    return nowPanel;
}

inline int twn::TownSugorokuInfo::getPanelNum()
{
    return panelNum_;
}

inline int twn::TownSugorokuInfo::getPanelIDByIndex(int index)
{
    return panel_[index].panelID_;
}

inline dss::Fix32Vector3& twn::PanelData::getPos()
{
    return pos_;
}

inline dss::Fix32Vector3& twn::TownSugorokuInfo::getPanelPosByIndex(int index)
{
    return panel_[index].getPos();
}

inline void twn::TownSugorokuInfo::setContinue(int state)
{
    continueState_ = state;
}

inline int twn::TownSugorokuInfo::getContinueState()
{
    return continueState_;
}

inline void twn::TownSugorokuInfo::setFallPosition(dss::Fix32Vector3& pos)
{
    fallPosition_ = pos;
}

inline void twn::TownSugorokuInfo::setFallMapId(int id)
{
    fallMapId_ = id;
}

inline twn::PanelData* twn::TownSugorokuInfo::getPanelDataByIndex(int index)
{
    return &panel_[index];
}

inline void twn::TownSugorokuInfo::setSugorokuEndMode(int type)
{
    sugorokuEndMode_ = type;
}

inline int twn::TownSugorokuInfo::getSugorokuEndMode()
{
    return sugorokuEndMode_;
}

inline void twn::TownSugorokuInfo::setDngOutMap(int map)
{
    dngMap_ = map;
}

inline void twn::TownSugorokuInfo::setDngOutUid(int uid)
{
    dngUid_ = uid;
}

inline int twn::TownSugorokuInfo::getDngOutMap()
{
    return dngMap_;
}

inline int twn::TownSugorokuInfo::getDngOutUid()
{
    return dngUid_;
}

inline void twn::TownSugorokuInfo::setDngIn(bool flag)
{
    dngIn_ = flag;
}

inline int twn::TownSugorokuInfo::isDngIn()
{
    return dngIn_;
}

inline void twn::TownSugorokuInfo::setMoveStart(bool flag)
{
    moveStart_ = flag;
}

inline int twn::TownSugorokuInfo::getTime()
{
    return timeCount_;
}

inline void twn::TownSugorokuInfo::setGateNextPayOff(bool flag)
{
    nextPayOff_ = flag;
}

inline unsigned int dq5::level::SugorokuStage::getArraySize()
{
    return binary_.record_;
}

inline dq5::level::SugorokuStage* dq5::level::SugorokuStage::getRecord(int index)
{
    return (SugorokuStage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::SugorokuDrop::getArraySize()
{
    return binary_.record_;
}

inline dq5::level::SugorokuDrop* dq5::level::SugorokuDrop::getRecord(int index)
{
    return (SugorokuDrop*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::SugorokuData::getArraySize()
{
    return binary_.record_;
}

inline dq5::level::SugorokuData* dq5::level::SugorokuData::getRecord(int index)
{
    return (SugorokuData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

#pragma thumb on

twn::TownSugorokuManager::TownSugorokuManager()
{
}

void twn::TownSugorokuManager::initialize()
{
    treasureRoom_ = false;
    for (int i = 0; i < SUGOROKU_COMMAND_NUM; i++) {
        sugorokuCommand_[i] = NULL;
    }
    flag_.clear();
    if (isSugorokuStage() == true) {
        flag_.set(STAGE_INIT);
        stageSetup();
    }
    nextState_ = sugoroku::NOT_CHANGE_STATE;
    state_ = sugoroku::NOT_SUGOROKU_MODE;
    if (g_SugorokuInfo.isContinue() == true) {
        if ((g_SugorokuInfo.getContinueState() == TownSugorokuInfo::CONTINUE_BATTLE ||
             g_SugorokuInfo.getContinueState() == TownSugorokuInfo::CONTINUE_TREASURE_ROOM) &&
            status::g_BattleResult.isPlayerDemolition() == true) {
            status::g_Party.getPlayerStatus(0).getHaveStatusInfo().setHp(1);
            g_SugorokuInfo.setSugorokuEndMode(5);
            cmn::g_cmnPartyInfo.setKeep(false, 0, false);
        } else {
            startSugoroku();
        }
        g_Global.setBattleLoseAfterFlag(false);
    }
    g_SugorokuInfo.setGateNextPayOff(false);
    g_SugorokuInfo.setContinue(TownSugorokuInfo::NOT_SUGOROKU);
    drawDiceNo_ = 0;
    sugorokuTime_ = false;
}

void twn::TownSugorokuManager::terminate()
{
    if (flag_.check(STAGE_INIT)) {
        sugorokuDraw_.cleanup();
        for (int i = 0; i < ARROW_NUM; i++) {
            arrow_[i].cleanup();
        }
    }
    if (flag_.check(GAME_INIT)) {
        terminateSugoroku();
        if (!g_SugorokuInfo.isContinue()) {
            switch (g_SugorokuInfo.getSugorokuEndMode()) {
            case 0:
                break;
            case 1:
                g_SugorokuInfo.setSugorokuEndMode(0);
                break;
            case 6:
                cmn::g_cmnPartyInfo.setKeep(false, 0, false);
                status::g_StageInfo.setFallFlag(true);
                break;
            default:
                cmn::g_cmnPartyInfo.setPrevLocation(true);
                cmn::g_cmnPartyInfo.setKeep(false, 0, false);
                break;
            }
        }
    } else {
        g_SugorokuInfo.setSugorokuEndMode(0);
    }
    if (g_SugorokuInfo.isContinue() == true) {
        if (g_Global.isNextPart(5)) {
            g_Global.setBattleLoseAfterMapNameId(g_SugorokuInfo.getEndMapNameId(), g_SugorokuInfo.getEndMapPosition(), g_SugorokuInfo.getEndMapDirIdx());
            g_Global.setBattleLoseAfterFlag(true);
        }
        if (g_SugorokuInfo.getContinueState() != TownSugorokuInfo::CONTINUE_TREASURE_ROOM) {
            cmn::g_cmnPartyInfo.setPrevLocation(true);
        }
    }
    if (isTreasuerRoom() == true) {
        if (g_Global.isNextPart(5)) {
            g_Global.setBattleLoseAfterMapNameId(g_SugorokuInfo.getEndMapNameId(), g_SugorokuInfo.getEndMapPosition(), g_SugorokuInfo.getEndMapDirIdx());
            g_Global.setBattleLoseAfterFlag(true);
            g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_TREASURE_ROOM);
        }
    }
}

void twn::TownSugorokuManager::execute()
{
    if (returnMenuFlag_ == true) {
        unkfunc_02018d64(10);
        returnMenuFlag_ = false;
    }
    if (nextState_ != sugoroku::NOT_CHANGE_STATE) {
        state_ = nextState_;
        nextState_ = sugoroku::NOT_CHANGE_STATE;
        sugorokuCommand_[state_]->setup();
    }
    sugorokuCommand_[state_]->execute();
    nextState_ = sugorokuCommand_[state_]->nextState();
    if (nextState_ != sugoroku::NOT_CHANGE_STATE) {
        sugorokuCommand_[state_]->terminate();
        if (nextState_ == sugoroku::NOT_SUGOROKU_MODE) {
            state_ = sugoroku::NOT_SUGOROKU_MODE;
            if (g_SugorokuInfo.getSugorokuEndMode() == 1) {
                SoundManager::townPlay(TownSystem::getFloorBgmIndex());
                int shopChapter = status::ShopList::SECTION_FIRST;
                switch (status::g_Story.getChapter()) {
                case dq5::CHAPTER_SEINENKI:
                    shopChapter = status::ShopList::SECTION_SECOND;
                    break;
                case dq5::CHAPTER_SOUNENKI:
                    shopChapter = status::ShopList::SECTION_THIRD;
                    break;
                }
                status::ShopList::setSection(shopChapter);
                int index = dq5::level::g_LevelDataUtility.searchShopDataIndex(g_Global.getNowAreaNo(), shopChapter);
                status::g_StageAttribute.setShopDataIndex(index);
            }
        }
    }
}

void twn::TownSugorokuManager::draw()
{
    diceAnim_.draw();
    if (drawDiceNo_ != 0) {
        diceAnim_.drawNumber(drawDiceNo_);
    } else if (flag_.check(DRAW_NUMBER) == true) {
        int num = g_SugorokuInfo.getNowMoveCount();
        num = dss::clamp<int>(1, num, 6);
        diceAnim_.drawNumber(num);
    }
    if (shopSprite_.unkfunc_02051b04()) {
        unkfunc_0204813c();
        shopSprite_.unkfunc_02051b68();
    }
    if (flag_.flag_ & DRAW_ARROW1) {
        arrow_[0].setRotate(arrowIdx_[0]);
        arrow_[0].draw(arrowPos[0]);
    }
    if (flag_.flag_ & DRAW_ARROW2) {
        arrow_[1].setRotate(arrowIdx_[1]);
        arrow_[1].draw(arrowPos[1]);
    }
    if (flag_.flag_ & DRAW_TIMER) {
        drawSugorokuTimer();
    }
    if (flag_.check(STAGE_INIT) == true) {
        int num = g_SugorokuInfo.getPanelNum();
        for (int i = 0; i < num; i++) {
            sugorokuDraw_.unkfunc_0214d568(g_SugorokuInfo.getPanelIDByIndex(i), g_SugorokuInfo.getPanelPosByIndex(i));
        }
    }
}

twn::TownSugorokuManager& twn::TownSugorokuManager::getSingleton()
{
    static TownSugorokuManager townSugorokuManager;
    return townSugorokuManager;
}

void twn::TownSugorokuManager::setupMapObj()
{
    sugorokuObj_[0].uid = 0x755a;
    sugorokuObj_[0].type = 0;
    sugorokuObj_[0].flag.clear();
    sugorokuObj_[1].uid = 0x755b;
    sugorokuObj_[1].type = 0;
    sugorokuObj_[1].flag.clear();
    sugorokuObj_[2].uid = 0x755c;
    sugorokuObj_[2].type = 1;
    sugorokuObj_[2].flag.clear();
    sugorokuObj_[3].uid = 0x755d;
    sugorokuObj_[3].type = 1;
    sugorokuObj_[3].flag.clear();
}

void twn::TownSugorokuManager::stageSetup()
{
    setStageNo();
    setupMapObj();
    g_SugorokuInfo.initialize();
    dss::Vector3<dss::Fix16> p1(-0.9f, 0.0f, 0.9f);
    dss::Vector3<dss::Fix16> p2(0.9f, 0.0f, 0.9f);
    dss::Vector3<dss::Fix16> p3(0.9f, 0.0f, -0.9f);
    dss::Vector3<dss::Fix16> p4(-0.9f, 0.0f, -0.9f);
    UnkPolygonVertex xy;
    xy.v[0] = p1;
    xy.v[1] = p2;
    xy.v[2] = p3;
    xy.v[3] = p4;
    sugorokuDraw_.unkfunc_0214d3ac(&xy);
    p1 = p1 / 2;
    p2 = p2 / 2;
    p3 = p3 / 2;
    p4 = p4 / 2;
    xy.v[0] = p1;
    xy.v[1] = p2;
    xy.v[2] = p3;
    xy.v[3] = p4;
    for (int i = 0; i < ARROW_NUM; i++) {
        arrow_[i].setup(&xy);
    }
    dq5::level::SugorokuStage::setup();
    int mapNo = g_Global.getMapNameId();
    int dataCount = dq5::level::SugorokuStage::getArraySize();
    int count = 0;
    dss::Fix32Vector3 pos;
    dss::Fix32Vector3 minPos;
    dss::Fix32Vector3 maxPos;
    int tMapNo = 0;
    int offset = 0;
    int i;
    for (i = 0; i < dataCount; i++) {
        if (tMapNo != dq5::level::SugorokuStage::getRecord(i)->mapNo) {
            offset = dq5::level::SugorokuStage::getRecord(i)->index;
        }
        tMapNo = dq5::level::SugorokuStage::getRecord(i)->mapNo;
        if (dq5::level::SugorokuStage::getRecord(i)->mapNo == mapNo) {
            unsigned short panelId;
            int loop;
            unsigned short uid;
            unsigned short attr;
            unsigned short warpMapNo;
            unsigned short warpId;
            int link2;
            int link3;
            uid = dq5::level::SugorokuStage::getRecord(i)->placeNo;
            panelId = dq5::level::SugorokuStage::getRecord(i)->panelNo - 1;
            attr = dq5::level::SugorokuStage::getRecord(i)->divergent;
            warpMapNo = dq5::level::SugorokuStage::getRecord(i)->warpMapNo;
            warpId = dq5::level::SugorokuStage::getRecord(i)->warpPlaceNo;
            int polyNo = TownStageManager::getSingleton()->stage_.m_fld.CollGetPolyNoByMapUid(uid, 0);
            TownStageManager::getSingleton()->stage_.collGetPolygonPos(polyNo, &pos);
            if (count == 0) {
                minPos = pos;
                maxPos = pos;
            } else {
                if (minPos.vx > pos.vx) {
                    minPos.vx = pos.vx;
                } else if (maxPos.vx < pos.vx) {
                    maxPos.vx = pos.vx;
                }
                if (minPos.vz > pos.vz) {
                    minPos.vz = pos.vz;
                } else if (maxPos.vz < pos.vz) {
                    maxPos.vz = pos.vz;
                }
            }
            g_SugorokuInfo.pushPanelData(uid, panelId, attr, warpMapNo, warpId, pos);
            int link1 = dq5::level::SugorokuStage::getRecord(i)->link1;
            link2 = dq5::level::SugorokuStage::getRecord(i)->link2;
            link3 = dq5::level::SugorokuStage::getRecord(i)->link3;
            loop = dq5::level::SugorokuStage::getRecord(i)->reverse;
            if (link1 == 0) {
                g_SugorokuInfo.pushPanelLink(count, 0, count + 1);
            }
            if (link1 != 0 && link1 != 999 && link1 != 998) {
                g_SugorokuInfo.pushPanelLink(count, 0, link1 - offset);
            }
            int revCount = 0;
            PanelData* data = g_SugorokuInfo.getPanelDataByIndex(count);
            if (link1 == 999) {
                for (; revCount < 5; revCount++) {
                    data->setReverce(data->getBackPanel1());
                    data = data->getBackPanel1();
                }
            }
            if (link2 != 0) {
                g_SugorokuInfo.pushPanelLink(count, 1, link2 - offset);
            }
            if (link3 != 0) {
                g_SugorokuInfo.pushPanelLink(count, 2, link3 - offset);
            }
            if (loop != 0) {
                g_SugorokuInfo.setLoopLink(count, loop - offset);
            }
            count++;
        }
    }
    minPos.vz.value += 4 * FX32_ONE;
    TownCamera::getSingleton()->setArea(minPos, maxPos);
    dq5::level::SugorokuStage::cleanup();
}

bool twn::TownSugorokuManager::isSugorokuStage()
{
    switch (g_Global.getMapNameId()) {
    case 0x97:
    case 0x20a:
    case 0x20b:
    case 0x21d:
    case 0x222:
    case 0x223:
    case 0x224:
    case 0x225:
    case 0x226:
    case 0x227:
    case 0x228:
    case 0x22a:
    case 0x22b:
    case 0x22c:
    case 0x22d:
    case 0x22e:
    case 0x22f:
    case 0x230:
    case 0x231:
    case 0x232:
        return true;
    }
    return false;
}

void twn::TownSugorokuManager::startSugoroku()
{
    if (g_SugorokuInfo.getContinueState() != TownSugorokuInfo::CONTINUE_TREASURE_ROOM) {
        TownSystem::getSingleton().setWait(false);
    }
    status::g_BattleResult.setPlayerDemolition(false);
    diceAnim_.setup();
    unkfunc_02018d64(10);
    flag_.set(GAME_INIT);
    dss::Fix32Vector3 pos(TownPlayerManager::getSingleton().getPosition());
    dq5::level::SugorokuDrop::setup();
    for (int i = 0; i < (int)dq5::level::SugorokuDrop::getArraySize(); i++) {
        if (dq5::level::SugorokuDrop::getRecord(i)->before == g_Global.getMapNameId()) {
            dss::Fix32Vector3 fallPos;
            fallPos.vx = dq5::level::SugorokuDrop::getRecord(i)->x;
            fallPos.vy = dq5::level::SugorokuDrop::getRecord(i)->y;
            fallPos.vz = dq5::level::SugorokuDrop::getRecord(i)->z;
            g_SugorokuInfo.setFallPosition(fallPos);
            g_SugorokuInfo.setFallMapId(dq5::level::SugorokuDrop::getRecord(i)->after);
        }
    }
    dq5::level::SugorokuDrop::cleanup();
    dq5::level::SugorokuChanceCard::setup();
    dq5::level::SugorokuChangeMsg::setup();
    dq5::level::SugorokuSpecialMsg::setup();
    dq5::level::SugorokuData::setup();
    dq5::level::SugorokuPanelList::setup();
    registCommand();
    state_ = sugoroku::NOT_CHANGE_STATE;
    g_SugorokuInfo.setMoveStart(false);
    switch (g_SugorokuInfo.getContinueState()) {
    case TownSugorokuInfo::CONTINUE_BATTLE:
        nextState_ = sugoroku::SYSTEM_PANEL_START;
        break;
    case TownSugorokuInfo::CONTINUE_INN:
        nextState_ = sugoroku::SYSTEM_PANEL_START;
        flag_.set(START_INN);
        break;
    case TownSugorokuInfo::CONTINUE_TABI:
    case TownSugorokuInfo::CONTINUE_FALL:
    case TownSugorokuInfo::CONTINUE_STRAT:
        nextState_ = sugoroku::SYSTEM_PANEL_START;
        break;
    case TownSugorokuInfo::CONTINUE_MOVE:
        g_SugorokuInfo.setMoveStart(true);
        nextState_ = sugoroku::SYSTEM_PANEL_START;
        break;
    case TownSugorokuInfo::START_SUGOROKU:
        g_SugorokuInfo.setDngIn(false);
        nextState_ = sugoroku::SYSTEM_DEBUG_START;
        break;
    case TownSugorokuInfo::CONTINUE_TREASURE_ROOM:
        treasureRoom_ = true;
        nextState_ = sugoroku::SYSTEM_TREASURE_ROOM_MOVE;
        setDrawTimer(true);
        return;
    case TownSugorokuInfo::CONTINUE_TREASURE_PRE_ROOM:
        treasureRoom_ = true;
        nextState_ = sugoroku::SYSTEM_TREASURE_PRE_ROOM;
        break;
    default:
        g_SugorokuInfo.setDngIn(false);
        nextState_ = sugoroku::SYSTEM_START;
        break;
    }
    int countMax = dq5::level::SugorokuData::getArraySize();
    for (int i = 0; i < countMax; i++) {
        if (stageNO_ == dq5::level::SugorokuData::getRecord(i)->index) {
            stageOffset_ = i;
        }
    }
    if (g_SugorokuInfo.getContinueState() == TownSugorokuInfo::NOT_SUGOROKU ||
        g_SugorokuInfo.getContinueState() == TownSugorokuInfo::START_SUGOROKU) {
        g_SugorokuInfo.setDiceCount(dq5::level::SugorokuData::getRecord(stageOffset_)->times);
    }
    status::ShopList::setSection(status::ShopList::SECTION_SUGOROKU);
    int index = dq5::level::g_LevelDataUtility.searchShopDataIndex(stageNO_, status::ShopList::SECTION_SUGOROKU);
    status::g_StageAttribute.setShopDataIndex(index);
}

bool twn::TownSugorokuManager::isSugorokuMode()
{
    if (state_ != sugoroku::NOT_SUGOROKU_MODE && treasureRoom_ != true) {
        return true;
    }
    return false;
}

bool twn::TownSugorokuManager::isTreasuerRoom()
{
    if (treasureRoom_ == true) {
        return true;
    }
    return false;
}

void twn::TownSugorokuManager::regist(int id, SugorokuCommand& command)
{
    sugorokuCommand_[id] = &command;
}

void twn::TownSugorokuManager::setShopDraw(int type)
{
    char filename[128];
    switch (type) {
    case 0:
        dss::sprintf_s(filename, sizeof(filename), "data/SUGOROKU/yado.tex");
        break;
    case 1:
        dss::sprintf_s(filename, sizeof(filename), "data/SUGOROKU/yorozu.tex");
        break;
    }
    shopSprite_.unkfunc_02051a50(filename, 0);
    shopSprite_.unkfunc_02051b78();
    shopSprite_.unkfunc_02051b90(0x1f);
    shopSprite_.unkfunc_02051ba0(0x3f);
    shopSprite_.unkfunc_02051bb0(0x80);
    shopSprite_.sprite_.unk_32 = 1;
    shopSprite_.unkfunc_02051b14(0, 0);
}

void twn::TownSugorokuManager::clearShopDraw()
{
    if (shopSprite_.unkfunc_02051b04()) {
        shopSprite_.unkfunc_02051ac4();
    }
}

void twn::TownSugorokuManager::terminateSugoroku()
{
    dq5::level::SugorokuChanceCard::cleanup();
    dq5::level::SugorokuChangeMsg::cleanup();
    dq5::level::SugorokuSpecialMsg::cleanup();
    dq5::level::SugorokuData::cleanup();
    dq5::level::SugorokuPanelList::cleanup();
    int shopChapter = status::ShopList::SECTION_FIRST;
    switch (status::g_Story.getChapter()) {
    case dq5::CHAPTER_SEINENKI:
        shopChapter = status::ShopList::SECTION_SECOND;
        break;
    case dq5::CHAPTER_SOUNENKI:
        shopChapter = status::ShopList::SECTION_THIRD;
        break;
    }
    status::ShopList::setSection(shopChapter);
    int index = dq5::level::g_LevelDataUtility.searchShopDataIndex(g_Global.getNowAreaNo(), shopChapter);
    status::g_StageAttribute.setShopDataIndex(index);
    status::g_StageInfo.setReliveCheckFlag(false);
    clearShopDraw();
    diceAnim_.cleanup();
}

void twn::TownSugorokuManager::setArrowDraw(int no, bool flag)
{
    if (no == 0) {
        if (flag == true) {
            flag_.set(DRAW_ARROW1);
        } else {
            flag_.remove(DRAW_ARROW1);
        }
    } else {
        if (flag == true) {
            flag_.set(DRAW_ARROW2);
        } else {
            flag_.remove(DRAW_ARROW2);
        }
    }
}

void twn::TownSugorokuManager::setDrawDiceNum(bool flag)
{
    if (flag == true) {
        flag_.set(DRAW_NUMBER);
    } else {
        flag_.remove(DRAW_NUMBER);
    }
}

void twn::TownSugorokuManager::drawSugorokuTimer()
{
    static UnkMenuParts s_timerFrameParts[] = {
        {0x01, 0x00, (short)0xf000, 0, 0, 0, 88, 32},
        {0xff, 0x00, 0x0000, 0, 0, 0, 0, 0},
    };

    static UnkMenuParts s_timerParts1[] = {
        {0x0f, 0x06, (short)0xf000, 2, 34, 8, 8, 12},
        {0x0d, 0x06, (short)0xf000, 3, 42, 8, 8, 12},
        {0x0f, 0x06, (short)0xf000, 4, 54, 8, 8, 12},
        {0x0f, 0x06, (short)0xf000, 5, 64, 8, 8, 12},
        {0xff, 0x00, 0x0000, 0, 0, 0, 0, 0},
    };

    static UnkMenuParts s_timerParts2[] = {
        {0x0f, 0x06, (short)0xf000, 1, 24, 8, 8, 12},
        {0x0f, 0x06, (short)0xf000, 2, 34, 8, 8, 12},
        {0x0d, 0x06, (short)0xf000, 3, 42, 8, 8, 12},
        {0x0f, 0x06, (short)0xf000, 4, 54, 8, 8, 12},
        {0x0f, 0x06, (short)0xf000, 5, 64, 8, 8, 12},
        {0xff, 0x00, 0x0000, 0, 0, 0, 0, 0},
    };

    static UnkMenuParts s_timerParts3[] = {
        {0x0f, 0x06, (short)0xf000, 0, 14, 8, 8, 12},
        {0x0f, 0x06, (short)0xf000, 1, 24, 8, 8, 12},
        {0x0f, 0x06, (short)0xf000, 2, 34, 8, 8, 12},
        {0x0d, 0x06, (short)0xf000, 3, 42, 8, 8, 12},
        {0x0f, 0x06, (short)0xf000, 4, 54, 8, 8, 12},
        {0x0f, 0x06, (short)0xf000, 5, 64, 8, 8, 12},
        {0xff, 0x00, 0x0000, 0, 0, 0, 0, 0},
    };
    unkfunc_02061c5c(0, 0xc0);
    int sugorokuTime = g_SugorokuInfo.getTime();
    if (sugorokuTime < 0) {
        sugorokuTime = 0;
    }
    int t = sugorokuTime % 216000;
    int m = (t % 3600) / 60 + (t / 3600) * 60;
    int s = (t % 3600) % 60 * 100 / 60;
    int param[6] = {0, 0, 0, (int)"\xff\xfe\xa8\x24", 0, 0};
    param[0] = m / 100;
    param[1] = m / 10;
    param[2] = m % 10;
    param[4] = s / 10;
    param[5] = s % 10;
    unkfunc_0206297c(s_timerFrameParts, NULL);
    if (m / 100 != 0) {
        unkfunc_020629a4(s_timerParts3, param, 1);
    } else if (m / 10 != 0) {
        unkfunc_020629a4(s_timerParts2, param, 1);
    } else {
        unkfunc_020629a4(s_timerParts1, param, 1);
    }
    MenuAPI::menuEnable(1);
}

void twn::TownSugorokuManager::setDrawTimer(bool flag)
{
    if (flag == true) {
        MenuAPI::changeMenuModeNormal();
        flag_.set(DRAW_TIMER);
    } else {
        flag_.remove(DRAW_TIMER);
    }
}

void twn::TownSugorokuManager::setStageNo()
{
    switch (g_Global.getMapNameId()) {
    case 0x97:
        stageNO_ = 1;
        break;
    case 0x20a:
    case 0x20b:
        stageNO_ = 2;
        break;
    case 0x21d:
        stageNO_ = 3;
        break;
    case 0x222:
    case 0x223:
        stageNO_ = 4;
        break;
    case 0x224:
    case 0x225:
    case 0x226:
    case 0x227:
    case 0x228:
        stageNO_ = 5;
        break;
    case 0x22a:
        stageNO_ = 6;
        break;
    case 0x22b:
        stageNO_ = 7;
        break;
    case 0x22c:
        stageNO_ = 8;
        break;
    case 0x22d:
        stageNO_ = 9;
        break;
    case 0x22e:
        stageNO_ = 10;
        break;
    case 0x22f:
        stageNO_ = 11;
        break;
    case 0x230:
        stageNO_ = 12;
        break;
    case 0x231:
        stageNO_ = 13;
        break;
    case 0x232:
        stageNO_ = 14;
        break;
    }
}

int twn::TownSugorokuManager::getSugorokuDungeonUid(int map)
{
    int uid = 0;
    switch (map) {
    case 0x22a:
        uid = 0x7919;
        break;
    case 0x22b:
        uid = 0x792f;
        break;
    case 0x22c:
        uid = 0x7945;
        break;
    case 0x22d:
        uid = 0x797d;
        break;
    case 0x22e:
        uid = 0x79c3;
        break;
    case 0x22f:
        uid = 0x7a09;
        break;
    case 0x230:
        uid = 0x7aa9;
        break;
    case 0x231:
        uid = 0x7b0a;
        break;
    case 0x232:
        uid = 0x7b6b;
        break;
    }
    return uid;
}

void twn::TownSugorokuManager::getSugorokuDungeonData(int& map, int& uid)
{
    if (g_SugorokuInfo.isDngIn() == true) {
        map = g_SugorokuInfo.getDngOutMap();
        uid = g_SugorokuInfo.getDngOutUid();
        g_SugorokuInfo.setDngIn(false);
        g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_MOVE);
        return;
    }
    g_SugorokuInfo.setDngOutMap(g_Global.getMapNameId());
    g_SugorokuInfo.setDngOutUid(g_SugorokuInfo.getNowPane()->getUid());
    g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_FALL);
    g_SugorokuInfo.setDngIn(true);
    int tmap;
    int r = UnkDssRand::rand(3);
    switch (g_Global.getMapNameId()) {
    case 0x21d:
        tmap = r + 0x22a;
        break;
    case 0x222:
    case 0x223:
        tmap = r + 0x22d;
        break;
    case 0x224:
    case 0x225:
    case 0x226:
    case 0x227:
    case 0x228:
        tmap = r + 0x230;
        break;
    }
    map = tmap;
    uid = getSugorokuDungeonUid(tmap);
}

void twn::TownSugorokuManager::registCommand()
{
    regist(sugoroku::SYSTEM_START, sugorokuSystemStart_);
    regist(sugoroku::SYSTEM_OPEN_MENU, sugorokuOpenRootMenu_);
    regist(sugoroku::SYSTEM_DICE, sugorokuSystemDice_);
    regist(sugoroku::SYSTEM_MOVE, sugorokuSystemPlayerMove_);
    regist(sugoroku::SYSTEM_FADE_OUT_END, sugorokuSystemFadeOutEnd_);
    regist(sugoroku::SYSTEM_CAMERA, sugorokuSystemCameraMove_);
    regist(sugoroku::SYSTEM_CAMERA_END, sugorokuSystemCameraMoveEnd_);
    regist(sugoroku::SYSTEM_PANEL_START, sugorokuSystemPanelStart_);
    regist(sugoroku::SYSTEM_PANEL_LINK, sugorokuSystemPanelLink_);
    regist(sugoroku::SYSTEM_FADE_OUT_NEXT_SHOP, sugorokuSystemFadeOutNextShop_);
    regist(sugoroku::SYSTEM_FADE_IN_NEXT_SHOP, sugorokuSystemFadeInNextShop_);
    regist(sugoroku::SYSTEM_SHOP_OPEN, sugorokuSystemShopOpen_);
    regist(sugoroku::SYSTEM_DICE_CONTROL, sugorokuSystemDiceControl_);
    regist(sugoroku::SYSTEM_FADE_OUT_NEXT_MENU, sugorokuSystemFadeOutNextMenu_);
    regist(sugoroku::SYSTEM_FADE_IN_NEXT_MENU, sugorokuSystemFadeInNextMenu_);
    regist(sugoroku::SYSTEM_DEBUG_START, sugorokuSystemDebugStart_);
    regist(sugoroku::SYSTEM_ABORT_END, sugorokuSystemAbortEnd_);
    regist(sugoroku::SYSTEM_TORESURE_ROOM_END_MESSAGE, sugorokuSystemTreasureRoomEndMessage_);
    regist(sugoroku::SYSTEM_TREASURE_ROOM_MOVE, sugorokuSystemTreasureRoomMove_);
    regist(sugoroku::SYSTEM_TREASURE_ROOM_END, sugorokuSystemTreasureRoomEnd_);
    regist(sugoroku::SYSTEM_TORESURE_ROOM_SET_TIME, sugorokuSystemTreasureRoomSetTime_);
    regist(sugoroku::SYSTEM_TREASURE_PRE_ROOM, sugorokuSystemTreasurePreRoom_);
    regist(sugoroku::SYSTEM_BATTLE_END, sugorokuSystemBattleEnd_);
    regist(sugoroku::PANEL_FINISH, sugorokuPanelFinish_);
    regist(sugoroku::PANEL_KAIDAN_UP, sugorokuPanelActionKaidanUp_);
    regist(sugoroku::PANEL_KAIDAN_DOWN, sugorokuPanelActionKaidanDown_);
    regist(sugoroku::PANEL_GOLD_UP_50, sugorokuPanelActionGoldUp50_);
    regist(sugoroku::PANEL_GOLD_UP_100, sugorokuPanelActionGoldUp100_);
    regist(sugoroku::PANEL_GOLD_UP_200, sugorokuPanelActionGoldUp200_);
    regist(sugoroku::PANEL_GOLD_UP_300, sugorokuPanelActionGoldUp300_);
    regist(sugoroku::PANEL_GOLD_UP_500, sugorokuPanelActionGoldUp500_);
    regist(sugoroku::PANEL_GOLD_UP_1000, sugorokuPanelActionGoldUp1000_);
    regist(sugoroku::PANEL_GOLD_UP_2000, sugorokuPanelActionGoldUp2000_);
    regist(sugoroku::PANEL_GOLD_UP_3000, sugorokuPanelActionGoldUp3000_);
    regist(sugoroku::PANEL_GOLD_UP_5000, sugorokuPanelActionGoldUp5000_);
    regist(sugoroku::PANEL_GOLD_DOWN_50, sugorokuPanelActionGoldDown50_);
    regist(sugoroku::PANEL_GOLD_DOWN_100, sugorokuPanelActionGoldDown100_);
    regist(sugoroku::PANEL_GOLD_DOWN_200, sugorokuPanelActionGoldDown200_);
    regist(sugoroku::PANEL_GOLD_DOWN_300, sugorokuPanelActionGoldDown300_);
    regist(sugoroku::PANEL_GOLD_DOWN_500, sugorokuPanelActionGoldDown500_);
    regist(sugoroku::PANEL_GOLD_DOWN_1000, sugorokuPanelActionGoldDown1000_);
    regist(sugoroku::PANEL_GOLD_DOWN_2000, sugorokuPanelActionGoldDown2000_);
    regist(sugoroku::PANEL_GOLD_DOWN_3000, sugorokuPanelActionGoldDown3000_);
    regist(sugoroku::PANEL_GOLD_DOWN_5000, sugorokuPanelActionGoldDown5000_);
    regist(sugoroku::PANEL_DICE_UP_1, sugorokuPanelActionDiceUp1_);
    regist(sugoroku::PANEL_DICE_UP_2, sugorokuPanelActionDiceUp2_);
    regist(sugoroku::PANEL_DICE_UP_3, sugorokuPanelActionDiceUp3_);
    regist(sugoroku::PANEL_DICE_UP_5, sugorokuPanelActionDiceUp5_);
    regist(sugoroku::PANEL_DICE_DOWN_1, sugorokuPanelActionDiceDown1_);
    regist(sugoroku::PANEL_DICE_DOWN_2, sugorokuPanelActionDiceDown2_);
    regist(sugoroku::PANEL_DICE_DOWN_3, sugorokuPanelActionDiceDown3_);
    regist(sugoroku::PANEL_DICE_DOWN_5, sugorokuPanelActionDiceDown5_);
    regist(sugoroku::PANEL_MOVE_NEXT_1, sugorokuPanelActionMoveNext1_);
    regist(sugoroku::PANEL_MOVE_NEXT_2, sugorokuPanelActionMoveNext2_);
    regist(sugoroku::PANEL_MOVE_NEXT_3, sugorokuPanelActionMoveNext3_);
    regist(sugoroku::PANEL_MOVE_NEXT_4, sugorokuPanelActionMoveNext4_);
    regist(sugoroku::PANEL_MOVE_NEXT_5, sugorokuPanelActionMoveNext5_);
    regist(sugoroku::PANEL_MOVE_NEXT_6, sugorokuPanelActionMoveNext6_);
    regist(sugoroku::PANEL_MOVE_BACK_1, sugorokuPanelActionMoveBack1_);
    regist(sugoroku::PANEL_MOVE_BACK_2, sugorokuPanelActionMoveBack2_);
    regist(sugoroku::PANEL_MOVE_BACK_3, sugorokuPanelActionMoveBack3_);
    regist(sugoroku::PANEL_MOVE_BACK_4, sugorokuPanelActionMoveBack4_);
    regist(sugoroku::PANEL_MOVE_BACK_5, sugorokuPanelActionMoveBack5_);
    regist(sugoroku::PANEL_MOVE_BACK_6, sugorokuPanelActionMoveBack6_);
    regist(sugoroku::PANEL_ENCOUNT_NORMAL, sugorokuPanelActionEncountNormal_);
    regist(sugoroku::PANEL_ENCOUNT_METAL, sugorokuPanelActionEncountMetal_);
    regist(sugoroku::PANEL_DAMAGE, sugorokuPanelActionDamage_);
    regist(sugoroku::PANEL_LOST_MP, sugorokuPanelActionLostMp_);
    regist(sugoroku::PANEL_CHANGE_PARAMETER, sugorokuPanelActionChangeParameter_);
    regist(sugoroku::PANEL_CHANCE_CARD, sugorokuPanelActionChanceCard_);
    regist(sugoroku::PANEL_BACK_TO_START, sugorokuPanelActionBackToStart_);
    regist(sugoroku::PANEL_HOLE_TRAP, sugorokuPanelActionHoleTrap_);
    regist(sugoroku::PANEL_TRAVEL_GATE, sugorokuPanelActionTravelGate_);
    regist(sugoroku::PANEL_TANSU, sugorokuPanelActionTansu_);
    regist(sugoroku::PANEL_TUBO, sugorokuPanelActionTubo_);
    regist(sugoroku::PANEL_TREASUER_BOX, sugorokuPanelActionTreasuerBox_);
    regist(sugoroku::PANEL_INN, sugorokuPanelActionInn_);
    regist(sugoroku::PANEL_SHOP, sugorokuPanelActionShop_);
    regist(sugoroku::PANEL_FLAT, sugorokuPanelActionFlat_);
    regist(sugoroku::PANEL_FOREST, sugorokuPanelActionForest_);
    regist(sugoroku::PANEL_MOUNTAIN, sugorokuPanelActionMountain_);
    regist(sugoroku::PANEL_KANBAN_UP, sugorokuPanelActionKanbanUp_);
    regist(sugoroku::PANEL_KANBAN_DOWN, sugorokuPanelActionKanbanDown_);
    regist(sugoroku::PANEL_KANBAN_LEFT, sugorokuPanelActionKanbanLeft_);
    regist(sugoroku::PANEL_KANBAN_RIGHT, sugorokuPanelActionKanbanRight_);
    regist(sugoroku::PANEL_CHARGE_GATE, sugorokuPanelActionChangeGate_);
    regist(sugoroku::PANEL_SUGOROKU_DUNGEON, sugorokuPanelActionSugorokuDungeon_);
    regist(sugoroku::PANEL_TREASUER_ROOM, sugorokuPanelActionTreasuerRoom_);
    regist(sugoroku::PANEL_HEAL_POINT, sugorokuPanelActionHealPoint_);
    regist(sugoroku::PANEL_SELECT_SPOT, sugorokuPanelActionSelectSpot_);
    regist(sugoroku::CHANCE_STRENGTH_UP1, sugorokuPanelChanceCardStrengthUp1_);
    regist(sugoroku::CHANCE_STRENGTH_UP2, sugorokuPanelChanceCardStrengthUp2_);
    regist(sugoroku::CHANCE_AGILITY_UP1, sugorokuPanelChanceCardAgilityUp1_);
    regist(sugoroku::CHANCE_AGILITY_UP2, sugorokuPanelChanceCardAgilityUp2_);
    regist(sugoroku::CHANCE_PROTECTION_UP1, sugorokuPanelChanceCardProtectionUp1_);
    regist(sugoroku::CHANCE_PROTECTION_UP2, sugorokuPanelChanceCardProtectionUp2_);
    regist(sugoroku::CHANCE_WISDOM_UP1, sugorokuPanelChanceCardWisdomUp_);
    regist(sugoroku::CHANCE_WISDOM_DOWN1, sugorokuPanelChanceCardWisdomDown_);
    regist(sugoroku::CHANCE_LUCK_UP1, sugorokuPanelChanceCardLuckUp1_);
    regist(sugoroku::CHANCE_LUCK_UP2, sugorokuPanelChanceCardLuckUp2_);
    regist(sugoroku::CHANCE_STRENGTH_DOWN, sugorokuPanelChanceCardStrengthDown_);
    regist(sugoroku::CHANCE_AGILITY_DOWN, sugorokuPanelChanceCardAgilityDown_);
    regist(sugoroku::CHANCE_PROTECTION_DOWN, sugorokuPanelChanceCardProtectionDown_);
    regist(sugoroku::CHANCE_LUCK_DOWN, sugorokuPanelChanceCardLuckDown_);
    regist(sugoroku::CHANCE_BACK_TO_START, sugorokuPanelChanceCardBackToStart_);
    regist(sugoroku::CHANCE_ENCOUNT_1, sugorokuPanelChanceCardEncount1_);
    regist(sugoroku::CHANCE_ENCOUNT_2, sugorokuPanelChanceCardEncount2_);
    regist(sugoroku::CHANCE_ENCOUNT_3, sugorokuPanelChanceCardEncount3_);
    regist(sugoroku::CHANCE_GOLD_DOWN_100, sugorokuPanelChanceCardGoldDown100_);
    regist(sugoroku::CHANCE_GOLD_UP_100, sugorokuPanelChanceCardGoldUp100_);
    regist(sugoroku::CHANCE_NOT_ENCOUNT, sugorokuPanelChanceCardNotEncount_);
    regist(sugoroku::CHANCE_HOLE_TRAP, sugorokuPanelChanceCardHoleTrap_);
    regist(sugoroku::CHANCE_CHANGE_PARAMETER, sugorokuPanelChanceCardChanceParameter_);
    regist(sugoroku::CHANCE_GET_TREASUER_BOX, sugorokuPanelChanceCardTreasuerBox_);
    regist(sugoroku::CHANCE_DICE_COUNT_UP, sugorokuPanelChanceCardDiceCountUp_);
    regist(sugoroku::CHANCE_ENCOUNT_4, sugorokuPanelChanceCardEncount4_);
    regist(sugoroku::CHANCE_INN, sugorokuPanelChanceCardInn_);
    regist(sugoroku::CHANCE_SELECT_DICE, sugorokuPanelChanceCardSelectDice_);
    regist(sugoroku::CHANCE_MOVE_NEXT_6, sugorokuPanelChanceCardMoveNext6_);
    regist(sugoroku::CHANCE_MOVE_BACK_5, sugorokuPanelChanceCardMoveBack5_);
    regist(sugoroku::CHANCE_DICE_LIMIT_DOWN, sugorokuPanelChanceCardDiceLimitDown_);
    regist(sugoroku::CHANCE_TREASUER_ROOM, sugorokuPanelChanceCardTreasuerRoom_);
    regist(sugoroku::CHANCE_LUCKY_1, sugorokuPanelChanceCardLucky1_);
    regist(sugoroku::CHANCE_LUCKY_2, sugorokuPanelChanceCardLucky2_);
    regist(sugoroku::CHANCE_LUCKY_3, sugorokuPanelChanceCardLucky3_);
    regist(sugoroku::CHANCE_UNLUCKY_1, sugorokuPanelChanceCardUnlucky1_);
    regist(sugoroku::CHANCE_UNLUCKY_2, sugorokuPanelChanceCardUnlucky2_);
    regist(sugoroku::CHANCE_UNLUCKY_3, sugorokuPanelChanceCardUnlucky3_);
}

bool twn::TownSugorokuManager::isDiceAnimEnd()
{
    if (diceAnim_.isFinish() == true) {
        SoundManager::stopSeWithIndex(0x15a, 0);
        return true;
    }
    return false;
}

void twn::TownSugorokuManager::diceThrowIn(int number)
{
    SoundManager::playSe(0x15a, 0);
    diceAnim_.throwIn(number);
}

#include "main/dss/DssVectorDefault.hpp"
