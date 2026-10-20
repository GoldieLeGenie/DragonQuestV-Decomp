#pragma ipa file
#include "main/global/Global.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/btl/Encount.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkOverlaySlot.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/sound/Sound.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/Status.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/window/ScreenEffectManager.hpp"

inline void cmn::CommonPartyInfo::setSetupIceAction(bool flag)
{
    iceStart_ = flag;
}

inline void status::BattleResult::setDisableChurchMessage(int flag)
{
    playerDemolitionMessage_ = flag;
}

inline bool FadeEffector::isFadeDisable()
{
    if (fadeDisable_) {
        fadeDisable_ = false;
        return true;
    }
    return false;
}

static int s_fieldMapNameId = 999;
static int s_debugTownMapNameId = 723;
static int s_firstTownMapNameId = 72;
static char s_firstMapName[] = "mbout";

Global g_Global;
static GlobalChangePart data_0209d690;
FadeEffector fadeEffector;
static UnkGlobalWaitPart data_0209d698;

static char s_battleMapName[] = "btlda1";

THUMB Global::Global()
{
    nextMapNameId = s_firstTownMapNameId;
    dss::strcpy_s(nextMapName, 32, s_firstMapName);
    dss::strcpy_s(battleMapName, 32, s_battleMapName);
    battleLoseAfterFlag_ = 0;
    partChangeFlag_ = 0;
    battleLoseAfterMapNameId_ = 722;
}

THUMB Global::~Global()
{
}

THUMB void Global::initialize()
{
    status::PlayerDataAll::initialize(false);
    status::Status::initialize();
}

THUMB void Global::startGame()
{
    data_0209d690.setNextPart(GAME_START_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
}

THUMB void Global::startFirstTown()
{
    setMapNameId(s_firstTownMapNameId);
    data_0209d690.setNextPart(TOWN_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
}

THUMB void Global::startDebugTown()
{
    setMapNameId(s_debugTownMapNameId);
    data_0209d690.setNextPart(TOWN_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
}

THUMB void Global::startTown(int mapNameId)
{
    setMapNameId(mapNameId);
    data_0209d690.setNextPart(TOWN_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
    partChangeFlag_ = true;
    checkFlag();
}

THUMB void Global::startTown(const char* name)
{
    startTown(getMapNameIdByName(name));
}

THUMB void Global::startCasino()
{
    setMapNameId(0);
    data_0209d690.setNextPart(CASINO_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
    partChangeFlag_ = true;
}

THUMB void Global::startSlimeRace()
{
    setMapNameId(0);
    data_0209d690.setNextPart(SLIME_RACE_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
    partChangeFlag_ = true;
    prevPartTown_ = true;
    cmn::g_cmnPartyInfo.prevLocation_ = true;
}

THUMB void Global::startSlimeTouch()
{
    setMapNameId(0);
    data_0209d690.setNextPart(SLIME_TOUCH_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
    partChangeFlag_ = true;
    prevPartTown_ = true;
    cmn::g_cmnPartyInfo.prevLocation_ = true;
}

THUMB void Global::startBook()
{
    setMapNameId(0);
    data_0209d690.setNextPart(BOOK_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
    partChangeFlag_ = true;
}

THUMB void Global::startSurechigai()
{
    setMapNameId(0);
    data_0209d690.setNextPart(MPEXCHANGE_PART);
    data_02101d14.addPart(&data_0209d690);
    cmn::g_cmnPartyInfo.prevLocation_ = true;
    fadeOutBlack(30, true);
}

THUMB void Global::setMinigame(int type)
{
    minigameType_ = type;
}

THUMB int Global::getMinigame()
{
    return minigameType_;
}

THUMB void Global::setCeremonyType(int type)
{
    ceremonyType_ = type;
}

THUMB int Global::getCeremonyType()
{
    return ceremonyType_;
}

THUMB void Global::setGameStatus(int status)
{
    minigameStatus_ = status;
}

THUMB int Global::getGameStatus()
{
    return minigameStatus_;
}

THUMB void Global::setRanarutaFlag(bool flag)
{
    ranarutaFlag_ = flag;
}

THUMB int Global::getRanarutaFlag()
{
    return ranarutaFlag_;
}

THUMB const char* Global::getMapName()
{
    return nextMapName;
}

THUMB void Global::setMapNameId(int id)
{
    char buff[32];
    prevMapNameId = nextMapNameId;
    nextMapNameId = id;
    getMapNameById(buff, id);
    dss::strcpy_s(prevMapName, 32, nextMapName);
    dss::strcpy_s(nextMapName, 32, buff);
}

THUMB void Global::getMapNameById(char* buff, int id)
{
    dss::strcpy_s(buff, 32, dq5::level::g_LevelDataUtility.getMapNameById(id));
}

THUMB int Global::getMapNameIdByName(const char* name)
{
    char buff[10] = {0};
    dss::strcpy(buff, name);
    return dq5::level::g_LevelDataUtility.getMapNameIdByName(buff);
}

THUMB bool Global::isAreaChange()
{
    if (prevMapName[0] == nextMapName[0] && prevMapName[1] == nextMapName[1]) {
        return false;
    }
    return true;
}

THUMB int Global::getFieldType()
{
    return fieldType_;
}

THUMB void Global::startField()
{
    setMapNameId(s_fieldMapNameId);
    data_0209d690.setNextPart(FIELD_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
    partChangeFlag_ = true;
}

THUMB void Global::startBattle()
{
    SoundManager::battlePlay(btl::Encount::getSingleton()->encountData_.sound_);
    cmn::PlayerManager::setLock(true);
    currentGamePart_ = data_02101c88.getCurrentPart();
    data_0209d690.setNextPart(BATTLE_PART);
    data_02101d14.addPart(&data_0209d690);
    partChangeFlag_ = true;
    SoundManager::stopSeWithIndex(0x44c, 10);
    window::gScreenEffect.effectStart(window::ScreenEffectManager::PLAY_BACK_BATTLE);
    fadeOutBlack(125, true);
}

THUMB void Global::directStartBattle()
{
    cmn::PlayerManager::setLock(true);
    SoundManager::battlePlay(10);
    currentGamePart_ = data_02101c88.getCurrentPart();
    data_0209d690.setNextPart(BATTLE_PART);
    data_02101d14.addPart(&data_0209d690);
    partChangeFlag_ = true;
    fadeOutBlack(15, true);
}

THUMB void Global::endBattle(bool demolition)
{
    cmn::PlayerManager::setLock(false);
    if (battleLoseAfterFlag_ && demolition == true) {
        g_GlobalFlag.clear();
        battleLoseAfterFlag_ = false;
        cmn::g_extraMapLink.setExtraLinkTown(battleLoseAfterMapNameId_, battleLoseAfterPosition_, battleLoseAfterIdx_);
        cmn::g_cmnPartyInfo.setSetupIceAction(false);
        status::g_StageInfo.initDoorOpenFlag();
    } else if (!demolition) {
        data_0209d690.setNextPart(currentGamePart_);
        data_02101d14.addPart(&data_0209d690);
    } else {
        status::g_BattleResult.setDisableChurchMessage(false);
        g_GlobalFlag.clear();
        if (!g_AreaFlag.check(0x140)) {
            g_LocalFlag.clear();
        }
        status::g_StageInfo.returnChurch();
        status::g_StageAttribute.partyWipeOut();
        status::g_StageInfo.playerFlagClear();
        status::g_Party.setGold(status::g_Party.gold_ / 2);
        status::g_Party.battleExp_ = 0;
        status::g_Party.battleGold_ = 0;
        status::g_Party.battleMonsterCount_ = 0;
        cmn::g_cmnPartyInfo.resetShipIkadaMapName();
        cmn::g_cmnPartyInfo.setSetupIceAction(false);
    }
    fadeOutBlack(30, true);
}

THUMB void Global::setBattleLoseAfterMapNameId(int id, dss::Fix32Vector3& pos, short idx)
{
    battleLoseAfterMapNameId_ = id;
    battleLoseAfterPosition_ = pos;
    battleLoseAfterIdx_ = idx;
    battleLoseAfterFlag_ = true;
}

THUMB void Global::startTitle()
{
    setMapNameId(0x2cd);
    status::g_Story.setChapter((dq5::CHAPTER_NO)4);
    data_0209d690.setNextPart(CEREMONY_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
    Sound::seStopAll(10);
    partChangeFlag_ = true;
    setCeremonyType(1);
}

THUMB void Global::startOpeningStaff()
{
    setMapNameId(0);
    status::g_Story.setChapter((dq5::CHAPTER_NO)4);
    data_0209d690.setNextPart(CEREMONY_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
    Sound::seStopAll(10);
    partChangeFlag_ = true;
    setCeremonyType(0);
}

THUMB void Global::startStaffroll()
{
    setMapNameId(0);
    status::g_Story.setChapter((dq5::CHAPTER_NO)5);
    data_0209d690.setNextPart(CEREMONY_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
    Sound::seStopAll(10);
    partChangeFlag_ = true;
    setCeremonyType(2);
}

THUMB void Global::startFin()
{
    setMapNameId(0);
    status::g_Story.setChapter((dq5::CHAPTER_NO)5);
    data_0209d690.setNextPart(CEREMONY_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
    Sound::seStopAll(10);
    partChangeFlag_ = true;
    setCeremonyType(3);
}

THUMB void Global::startLogo()
{
    data_0209d690.setNextPart(MENU_PART);
    data_02101d14.addPart(&data_0209d690);
    fadeOutBlack(30, true);
}

THUMB bool Global::isNextPart(int part)
{
    if (part == data_02101c88.getNextPart()) {
        return true;
    }
    return false;
}

THUMB void Global::fadeOutBlack(int frame, bool flag)
{
    if (!fadeEffector.isFadeOutBlack() && !fadeEffector.isFadeOutWhite()) {
        if (fadeEffector.isFadeInBlack()) {
            data_02101d14.removePart(&fadeEffector);
        }
        fadeEffector.setFadeOutBlack(frame, flag);
        data_02101d14.addPart(&fadeEffector);
    }
}

THUMB void Global::fadeOutWhite(int frame, bool flag)
{
    if (!fadeEffector.isFadeOutWhite()) {
        fadeEffector.setFadeOutWhite(frame, flag);
        data_02101d14.addPart(&fadeEffector);
    }
}

THUMB void Global::fadeInBlack(int frame)
{
    fadeEffector.setFadeInBlack(frame);
    data_02101d14.addPart(&fadeEffector);
}

THUMB void Global::fadeInWhite(int frame)
{
    fadeEffector.setFadeInWhite(frame);
    data_02101d14.addPart(&fadeEffector);
}

THUMB void Global::fadeIn(int frame)
{
    fadeEffector.setFadeIn(frame);
    data_02101d14.addPart(&fadeEffector);
}

THUMB void Global::updateArea()
{
    prevAreaNo_ = areaNo_;
    areaNo_ = dq5::level::g_LevelDataUtility.getAreaNoByMapId(nextMapNameId);
}

THUMB void Global::checkFlag()
{
    if (isProtectCheckTriggered()) {
        g_LocalFlag.remove(5);
        g_AreaFlag.remove(0x70);
        g_AreaFlag.remove(0x3d);
    }
}

THUMB void Global::checkSave1()
{
    if (isProtectCheckTriggered()) {
        g_AreaFlag.clear();
    }
}

THUMB bool Global::checkSave2()
{
    if (isProtectCheckTriggered()) {
        setPadLock(1);
        return true;
    }
    return false;
}

THUMB void GlobalChangePart::update()
{
    if (fadeEffector.isFadeEnd()) {
        data_02101c88.setNextPart(nextPart_);
        nextPart_ = NONE_PART;
    }
}

THUMB int GlobalChangePart::isEnd()
{
    if (nextPart_ == NONE_PART) {
        return true;
    }
    return false;
}

THUMB void GlobalChangePart::setNextPart(int part)
{
    nextPart_ = part;
}

THUMB FadeEffector::FadeEffector()
{
    state_ = FADE_NONE;
    brightness_ = 0;
    count_ = 0;
    frames_ = 0;
    applyBrightness_ = 1;
    fadeDisable_ = 0;
}

THUMB void FadeEffector::update()
{
}

THUMB void FadeEffector::draw()
{
    count_++;
    count_ = dss::clamp<int>(count_, 0, frames_);
    brightness_ = (count_ << 4) / frames_;
    switch (state_) {
        case FADE_NONE:
            break;
        case FADE_OUT_BLACK:
            brightness_ = -brightness_;
            brightness_ = dss::clamp<int>(brightness_, -16, 0);
            break;
        case FADE_IN_BLACK:
            brightness_ -= 16;
            brightness_ = dss::clamp<int>(brightness_, -16, 0);
            break;
        case FADE_OUT_WHITE:
            break;
        case FADE_IN_WHITE:
            brightness_ = 16 - brightness_;
            break;
    }
    if (applyBrightness_) {
        setMainBrightness(brightness_);
        setSubBrightness(brightness_);
    }
}

THUMB int FadeEffector::isEnd()
{
    if (isFadeEnd()) {
        return true;
    }
    return false;
}

THUMB void FadeEffector::setFadeOutBlack(int frame, bool flag)
{
    if (!isFadeDisable()) {
        applyBrightness_ = flag;
        state_ = FADE_OUT_BLACK;
        count_ = 0;
        frames_ = frame;
        count_ = (-brightness_ * frame) / 16;
        count_ = dss::clamp<int>(count_, 0, frames_);
    }
}

THUMB void FadeEffector::setFadeOutWhite(int frame, bool flag)
{
    if (!isFadeDisable()) {
        applyBrightness_ = flag;
        state_ = FADE_OUT_WHITE;
        count_ = 0;
        frames_ = frame;
    }
}

THUMB void FadeEffector::setFadeInBlack(int frame)
{
    if (!isFadeDisable()) {
        if (state_ == FADE_OUT_BLACK) {
            state_ = FADE_IN_BLACK;
        } else if (state_ == FADE_OUT_WHITE) {
            state_ = FADE_IN_WHITE;
        } else {
            state_ = FADE_IN_BLACK;
        }
        count_ = 0;
        frames_ = frame;
    }
}

THUMB void FadeEffector::setFadeInWhite(int frame)
{
    if (!isFadeDisable()) {
        state_ = (state_ == FADE_OUT_BLACK) ? FADE_IN_BLACK : FADE_IN_WHITE;
        count_ = 0;
        frames_ = frame;
    }
}

THUMB void FadeEffector::setFadeIn(int frame)
{
    if (!isFadeDisable()) {
        switch (state_) {
            case FADE_OUT_BLACK:
                state_ = FADE_IN_BLACK;
                break;
            case FADE_OUT_WHITE:
                state_ = FADE_IN_WHITE;
                break;
            default:
                state_ = FADE_IN_BLACK;
                break;
        }
        count_ = 0;
        frames_ = frame;
    }
}

THUMB int FadeEffector::isFadeEnd()
{
    if (count_ == frames_) {
        return true;
    }
    return false;
}

THUMB int FadeEffector::isFadeOutBlack()
{
    if (state_ == FADE_OUT_BLACK && brightness_ < 0) {
        return true;
    }
    return false;
}

THUMB int FadeEffector::isFadeInBlack()
{
    if (state_ == FADE_IN_BLACK && brightness_ < 0) {
        return true;
    }
    return false;
}

THUMB int FadeEffector::isFadeOutWhite()
{
    if (state_ == FADE_OUT_WHITE && brightness_ > 0) {
        return true;
    }
    return false;
}

THUMB void UnkGlobalWaitPart::update()
{
}

THUMB void UnkGlobalWaitPart::draw()
{
    count_++;
    count_ = dss::clamp<int>(count_, 0, frames_);
}

THUMB int UnkGlobalWaitPart::isEnd()
{
    if (!isRunning()) {
        return true;
    }
    return false;
}

THUMB int UnkGlobalWaitPart::isRunning()
{
    if (count_ == frames_) {
        dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(8, 8);
        return false;
    }
    return true;
}

THUMB void UnkGlobalPart::draw()
{
}
