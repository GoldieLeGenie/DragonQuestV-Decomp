#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

// The original TU also emitted ScriptCommand's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "main/script/ScriptSystemCommand.hpp"
#include "main/script/CommandParam.hpp"
#include "main/ceremony/CeremonySetting.hpp"
#include "main/ceremony/UnkCeremonyEndingFin.hpp"
#include "main/cmn/CommonCounterInfo.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/dss/UnkDssMath.hpp"
#include "main/dss/UnkLanguage.hpp"
#include "main/dss/UnkModelMember.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/leveldata/PartytalkMonster.hpp"
#include "main/object/DisplayCharacter.hpp"
#include "main/sound/Sound.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/ShopList.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StatusChange.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/text/TextAPI.hpp"
#include "main/town/TownSugorokuInfo.hpp"
#include "main/window/ShopMenuControl.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageEffectManager.hpp"
#include "ov001/town/TownSugorokuManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov001/town/character/TownCharacterBase.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "ov004/ceremony/CeremonyEndingFin.hpp"
#include "ov004/ceremony/CeremonyEndingSystem.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov005/fld/FieldSystem.hpp"
#include "ov012/materielmenu/MaterielMenu_SLOT.hpp"

#pragma thumb on

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

inline void GameWait::terminate()
{
}

inline void CmdFriendMonsterMessage::execute()
{
}

inline void CmdRiseupPlayerEquip::execute()
{
}

inline void cmn::PlayerManager::setTownCharaColl(bool charaColl)
{
    charaColl_ = charaColl;
}

inline void twn::TownPlayerManager::setMapLink(bool flag)
{
    flagMapLink_ = flag;
}

inline twn::TownSystemScript& twn::TownSystem::getScriptSystem()
{
    return townSystemScript_;
}

inline fld::FieldSystemScript& fld::FieldSystem::getScriptSystem()
{
    return fieldSystemScript_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline unsigned int status::BasePartyStatus::getGold()
{
    return gold_;
}

inline unsigned int status::BasePartyStatus::getCasinoCoin()
{
    return casinoCoin_;
}

inline unsigned int status::BasePartyStatus::getMedalCoin()
{
    return medalCoin_;
}

inline int status::BasePartyStatus::isFukuro()
{
    return fukuro_;
}

inline void status::BasePartyStatus::setCarriage(int flag)
{
    carriage_ = flag;
}

inline dq5::RETURN_GAME_TYPE status::StageInfo::getReturnGame()
{
    return returnGame_;
}

inline void status::StageInfo::setLastParty(int num, int index)
{
    lastParty_[num] = index;
}

inline void status::StageAttribute::setTimestopFlag(int flag)
{
    timestop_ = flag;
}

inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment()
{
    return haveEquipment_;
}

inline int status::HaveStatus::getLevel() const
{
    return level_;
}

inline unsigned char status::PlayerData::getLevel()
{
    return baseStatus_.level_;
}

inline char* status::PlayerData::getNameString()
{
    return name_;
}

inline status::PlayerData& status::PlayerDataAll::getPlayerData(int index)
{
    return playerData_[index];
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline void cmn::CommonPartyInfo::setPrevLocation(bool flag)
{
    prevLocation_ = flag;
}

inline void cmn::CommonPartyInfo::setTalkCharaCtrlID(int ctrl)
{
    ctrlID_ = ctrl;
}

inline void window::ShopMenuControl::startMenu(int menuType)
{
    menuType_ = menuType;
    state_ = 7;
}

inline void twn::TownSugorokuInfo::setEndMapNameId(int id)
{
    endMapId_ = id;
}

inline void twn::TownSugorokuInfo::setEndMapPosition(dss::Fix32Vector3& pos)
{
    endMapPos_ = pos;
}

inline void twn::TownSugorokuInfo::setEndMapDirIdx(short idx)
{
    endMapIdx_ = idx;
}

inline void twn::TownSugorokuInfo::setContinue(int state)
{
    continueState_ = state;
}

inline void ceremony::CeremonySetting::setOpening(int index)
{
    opening_ = index;
}

inline void ceremony::CeremonySetting::setNextActMap(int index)
{
    nextActMap_ = index;
}

inline void ceremony::CeremonySetting::setNextActPos(dss::Fix32Vector3& pos)
{
    nextActPosition_ = pos;
}

inline int status::MenuStatus::getMenuEventFlag()
{
    return menuEventFlag_;
}

inline void status::MenuStatus::setMenuEventFlag(bool flag)
{
    menuEventFlag_ = flag;
}

inline void status::MenuStatus::setMenuEventNo(short no)
{
    menuEventNo_[0] = no;
}

inline short status::MenuStatus::getItemIndex()
{
    return itemIndex_;
}

inline void status::MenuStatus::setLuraDisableMessage(int mes)
{
    messageNo_[0] = mes;
}

inline void status::MenuStatus::setLuraDisableMessage(int index, int mes)
{
    messageNo_[index] = mes;
}

inline void status::MenuStatus::setLuraDisableMessageVoice(int index, int voice)
{
    messageVoice_[index] = voice;
}

inline void twn::TownSugorokuManager::setTreasuerRoom(bool flag)
{
    treasureRoom_ = flag;
}

inline void twn::TownSugorokuManager::setNextState(int state)
{
    nextState_ = state;
}

inline int twn::TownSugorokuManager::getSugorokuTimeEnd()
{
    return sugorokuTime_;
}

inline void twn::TownSugorokuInfo::setSugorokuEndMode(int type)
{
    sugorokuEndMode_ = type;
}

inline int twn::TownSugorokuInfo::getTime()
{
    return timeCount_;
}

inline void twn::TownPlayerAction::setActionType(TOWN_PLAYER_ACTION_TYPE type)
{
    actionType_ = type;
}

inline void twn::TownPlayerManager::setActionType(int type)
{
    player_.setActionType((TOWN_PLAYER_ACTION_TYPE)type);
}

inline void twn::TownPlayerManager::resetDrawPartyCount()
{
    partyDraw_.resetDrawPartyCount();
}

inline bool status::HaveStatus::isFriendMonster() const
{
    return playerType_ == TYPE_FRIENDMONSTER;
}

inline int status::HaveStatus::getPlayerKindIndex() const
{
    return playerKindIndex_;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline short status::StoryStatus::getClearFriendMonster(int index)
{
    return clearFriendMonster_[index];
}

inline void status::StoryStatus::setClearFriendMonster(int index, short ctrlID)
{
    clearFriendMonster_[index] = ctrlID;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

inline void TownCharacterManager::changePose(int index, int pose)
{
    character_[index]->changePose(pose);
}

inline dq5::level::PartytalkMonster* dq5::level::PartytalkMonster::getRecord(int index)
{
    return (PartytalkMonster*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline char dq5::level::PartytalkMonster::getConduct()
{
    return conduct;
}

inline unsigned long dq5::level::PartytalkMonster::getMessage()
{
    return message;
}

inline void status::ShopList::setSection(int section)
{
    section_ = section;
}

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline void status::StageAttribute::setShopDataIndex(int index)
{
    shopDataIndex_ = index;
}

inline void status::StageInfo::setRiremitMapId(int id)
{
    riremitMap_ = id;
}

inline void FadeEffector::setFadeDisable(bool flag)
{
    fadeDisable_ = flag;
}


bool cmdSetup(void* scriptParam)
{
    PARAM_SETUP param = *(PARAM_SETUP*)scriptParam;
    setScriptObjectEnable(param.index, true);
    return true;
}

bool cmdPlayerLock(void* scriptParam)
{
    static int lockNum = 0;
    PARAM_PLAYER_LOCK* param = (PARAM_PLAYER_LOCK*)scriptParam;
    if (param->flag) {
        lockNum++;
        if (data_02101c88.unkfunc_02051818(4)) {
            twn::TownPlayerManager::getSingleton().setLock(true);
            twn::TownPlayerManager::getSingleton().setTownCharaColl(false);
            twn::TownSystem::getSingleton().getScriptSystem().setEventLock(true);
        } else {
            fld::FieldPlayerManager::getSingleton().setLock(true);
            fld::FieldSystem::getSingleton()->getScriptSystem().setEventLock(true);
        }
        cmn::PartyTalk::getSingleton().resetPartyTalk();
    } else {
        lockNum--;
        if (data_02101c88.unkfunc_02051818(4)) {
            twn::TownPlayerManager::getSingleton().setLock(false);
            if (!cmn::PlayerManager::isLock()) {
                twn::TownPlayerManager::getSingleton().setTownCharaColl(true);
                twn::TownPlayerManager::getSingleton().setMapLink(true);
            }
            twn::TownSystem::getSingleton().getScriptSystem().setEventLock(false);
        } else {
            fld::FieldPlayerManager::getSingleton().setLock(false);
            fld::FieldSystem::getSingleton()->getScriptSystem().setEventLock(false);
        }
    }
    return true;
}

bool cmd_check_search_action(void* scriptParam)
{
    return false;
}

bool cmdSetItem(void* scriptParam)
{
    PARAM_SET_ITEM* paramSetItem = (PARAM_SET_ITEM*)scriptParam;
    status::g_Party.setPlayerMode();
    if (paramSetItem->item == 0xD1) {
        if (paramSetItem->flag == 0) {
            status::g_Party.addMedalCoin(paramSetItem->value);
            status::g_Story.setMedalFlag(true);
        } else {
            status::g_Party.setMedalCoin(status::g_Party.getMedalCoin() - paramSetItem->value);
        }
        return true;
    }
    if (paramSetItem->flag == 0) {
        cmn::PartyTalk::getSingleton().setPreItem(paramSetItem->item);
    }
    if (paramSetItem->flag == 0 && paramSetItem->index != 0) {
        int active = status::g_Party.getSortIndex(paramSetItem->index);
        if (active != -1 && !status::g_Party.getPlayerStatus(active).getHaveStatusInfo().isDeath()) {
            int addCount = 0;
            status::HaveItem& item = status::g_Party.getPlayerStatus(active).getHaveStatusInfo().getHaveItem();
            for (int i = 0; i < paramSetItem->value; i++) {
                item.add(paramSetItem->item);
                addCount++;
                if (item.getCount() == status::HaveItem::ITEM_MAX) {
                    break;
                }
            }
            unsigned int rest = paramSetItem->value;
            if (rest > addCount) {
                rest -= addCount;
                status::g_Party.haveItemSack_.add(paramSetItem->item, rest);
            }
            return true;
        }
    }
    int partyCount = status::g_Party.getCount();
    if (paramSetItem->flag == 0) {
        bool fukuro = true;
        if (paramSetItem->index == 0) {
            for (int i = 0; i < partyCount; i++) {
                status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
                if (statusInfo.isDeath() == true) {
                    continue;
                }
                int itemCount = statusInfo.getHaveItem().getCount();
                if (itemCount + (int)paramSetItem->value <= status::HaveItem::ITEM_MAX) {
                    for (int count = 0; count < paramSetItem->value; count++) {
                        statusInfo.getHaveItem().add(paramSetItem->item);
                    }
                    fukuro = false;
                    break;
                }
            }
        }
        if (fukuro == true) {
            status::g_Party.haveItemSack_.add(paramSetItem->item, paramSetItem->value);
        }
        TextAPI::setMACRO0(10, 0x40000000, paramSetItem->item);
    } else {
        unsigned int itemCount = paramSetItem->value;
        for (int i = 0; i < partyCount; i++) {
            status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
            if (statusInfo.getHaveItem().isItem(paramSetItem->item)) {
                for (int j = 0; j < statusInfo.getHaveItem().getCount(); j++) {
                    if (paramSetItem->item == statusInfo.getHaveItem().getItem(j)) {
                        statusInfo.execThrow(j);
                        itemCount--;
                        j--;
                        if (itemCount == 0) {
                            return true;
                        }
                    }
                }
            }
        }
        if (status::g_Party.isFukuro()) {
            if (status::g_Party.haveItemSack_.isItem(paramSetItem->item)) {
                for (int i = 0; i < status::g_Party.haveItemSack_.getCount(); i++) {
                    if (paramSetItem->item == status::g_Party.haveItemSack_.getItem(i)) {
                        int count = status::g_Party.haveItemSack_.getItemCount(i);
                        for (int j = 0; j < count; j++) {
                            status::g_Party.haveItemSack_.execThrow(i);
                            if (--itemCount == 0) {
                                return true;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    return true;
}

bool cmdSetGold(void* scriptParam)
{
    PARAM_SET_GOLD* param = (PARAM_SET_GOLD*)scriptParam;
    if (param->flag == 0) {
        status::g_Party.setGold(param->value + status::g_Party.getGold());
    } else {
        int gold = status::g_Party.getGold() - param->value;
        if (gold < 0) {
            gold = 0;
        }
        status::g_Party.setGold(gold);
    }
    return true;
}

bool cmdSetCoin(void* scriptParam)
{
    PARAM_SET_COIN* param = (PARAM_SET_COIN*)scriptParam;
    if (param->flag == 0) {
        status::g_Party.setCasinoCoin(param->value + status::g_Party.getCasinoCoin());
    } else {
        int coin = status::g_Party.getCasinoCoin() - param->value;
        if (coin < 0) {
            coin = 0;
        }
        status::g_Party.setCasinoCoin(coin);
    }
    return true;
}

bool cmd_set_random(void* scriptParam)
{
    PARAM_SET_RANDOM* param = (PARAM_SET_RANDOM*)scriptParam;
    int value = UnkDssRand::rand(param->value) % (int)param->value;
    if (value == 0) {
        g_GlobalFlag.set(param->index);
    } else {
        g_GlobalFlag.remove(param->index);
    }
    return true;
}

bool cmd_set_random2(void* scriptParam)
{
    PARAM_SET_RANDOM2* param = (PARAM_SET_RANDOM2*)scriptParam;
    int value = UnkDssRand::rand(param->value2) % (int)param->value2;
    if (value < param->value1) {
        g_GlobalFlag.set(param->index);
    } else {
        g_GlobalFlag.remove(param->index);
    }
    return true;
}

bool cmdSetRulaLook(void* scriptParam)
{
    PARAM_SET_RUURA_LOCK* param = (PARAM_SET_RUURA_LOCK*)scriptParam;
    status::g_StageAttribute.setRulaDisable(param->rulaDisable);
    status::g_StageAttribute.setRiremitoDisable(param->riremitoDisable);
    return true;
}

bool cmd_set_ranaruta(void* scriptParam)
{
    PARAM_SET_RANARUTA* param = (PARAM_SET_RANARUTA*)scriptParam;
    status::g_StageAttribute.setLanarutaDisable(param->flag);
    return true;
}

bool cmdCheckMoney(void* scriptParam)
{
    PARAM_CHECK_MONEY* param = (PARAM_CHECK_MONEY*)scriptParam;
    bool ret = false;
    if (param->flag == 0) {
        if (status::g_Party.getGold() >= param->value) {
            ret = true;
        }
    } else if (status::g_Party.getGold() < param->value) {
        ret = true;
    }
    return ret;
}

bool cmd_set_wait_counter(void* scriptParam)
{
    PARAM_SET_WAIT_COUNTER* param = (PARAM_SET_WAIT_COUNTER*)scriptParam;
    cmn::g_CommonCounterInfo.setWaitZero(param->frame);
    return true;
}

bool isWaitCounter(void* scriptParam)
{
    return cmn::g_CommonCounterInfo.isEndWaitCounter();
}

bool waitOperation(void* scriptParam)
{
    return cmn::g_CommonCounterInfo.checkBottun();
}

bool cmd_set_day_count(void* scriptParam)
{
    PARAM_SET_DAY_COUNT* param = (PARAM_SET_DAY_COUNT*)scriptParam;
    cmn::g_CommonCounterInfo.setDayCounter(param->counter, param->days);
    return true;
}

bool isDayCount(void* scriptParam)
{
    PARAM_IS_DAY_COUNT* param = (PARAM_IS_DAY_COUNT*)scriptParam;
    return cmn::g_CommonCounterInfo.isEndDayCounter(param->counter);
}

bool cmd_set_forward_counter(void* scriptParam)
{
    cmn::g_CommonCounterInfo.setChangeDay();
    return true;
}

bool cmd_set_chapter(void* scriptParam)
{
    PARAM_SET_CHAPTER* param = (PARAM_SET_CHAPTER*)scriptParam;
    if (param->chapter == dq5::CHAPTER_SEINENKI) {
        status::g_StageAttribute.setMapName("xbb1b2a");
        {
            status::g_Party.add(3, true);
            status::g_Party.add(4, true);
            status::g_Party.setPlayerMode();
            int younen = status::g_Party.getSortIndex(3);
            int seinen = status::g_Party.getSortIndex(4);
            status::HaveStatusInfo& biankaStatus_y = status::g_Party.getPlayerStatus(younen).getHaveStatusInfo();
            status::HaveStatusInfo& biankaStatus_s = status::g_Party.getPlayerStatus(seinen).getHaveStatusInfo();
            int tempEquip[4];
            tempEquip[0] = biankaStatus_s.getHaveEquipment().getEquipment(ITEM_WEAPON, 0);
            tempEquip[1] = biankaStatus_s.getHaveEquipment().getEquipment(ITEM_ARMOR, 0);
            tempEquip[2] = biankaStatus_s.getHaveEquipment().getEquipment(ITEM_SHIELD, 0);
            tempEquip[3] = biankaStatus_s.getHaveEquipment().getEquipment(ITEM_HELMET, 0);
            int levelUp = biankaStatus_y.haveStatus_.getLevel() + 10;
            biankaStatus_s.levelup(levelUp);
            int itemCount = biankaStatus_s.getHaveItem().getCount();
            for (int i = 0; i < itemCount; i++) {
                biankaStatus_s.execThrow(0);
            }
            for (int i = 0; i < 4; i++) {
                biankaStatus_s.getHaveItem().add(tempEquip[i]);
            }
            for (int i = 0; i < 4; i++) {
                biankaStatus_s.setEquipment(3);
            }
            status::g_Party.del(seinen);
            status::g_Party.setPlayerMode();
            status::g_Party.del(status::g_Party.getSortIndex(3));
        }
        {
            int kirapanIndex = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(17);
            if (status::g_Party.getSortIndex(16) == -1) {
                status::g_Party.add(16, true);
            }
            status::g_Party.add(kirapanIndex, true);
            status::g_Party.setPlayerMode();
            int younen = status::g_Party.getSortIndex(16);
            int seinen = status::g_Party.getSortIndex(kirapanIndex);
            status::HaveStatusInfo& kirapanStatus_y = status::g_Party.getPlayerStatus(younen).getHaveStatusInfo();
            status::HaveStatusInfo& kirapanStatus_s = status::g_Party.getPlayerStatus(seinen).getHaveStatusInfo();
            status::PlayerDataAll::getPlayerData(kirapanIndex).setNameString(status::PlayerDataAll::getPlayerData(16).getNameString());
            int bebiLevel = kirapanStatus_y.haveStatus_.getLevel();
            if (bebiLevel > status::PlayerDataAll::getPlayerData(kirapanIndex).getLevel()) {
                kirapanStatus_s.levelup(bebiLevel);
            }
            status::g_Party.del(seinen);
            status::g_Party.setPlayerMode();
            status::g_Party.del(status::g_Party.getSortIndex(16));
        }
    }
    status::StatusChange::statusToherosu_.clear();
    status::StatusChange::statusSinobiasi_.clear();
    status::StatusChange::statusMonstersFood_.clear();
    status::g_Story.setChapter((dq5::CHAPTER_NO)param->chapter);
    return true;
}

bool cmdCheckHeroLevel(void* scriptParam)
{
    PARAM_CHECK_HERO_LEVEL* param = (PARAM_CHECK_HERO_LEVEL*)scriptParam;
    int hero = status::g_Party.getSortIndex(1);
    if (hero == -1) {
        return false;
    }
    int level = status::g_Party.getPlayerStatus(hero).getHaveStatusInfo().haveStatus_.getLevel();
    if (level >= param->minlevel && level <= param->maxlevel) {
        return true;
    }
    return false;
}

bool cmd_chpater_store(void* scriptParam)
{
    return true;
}

bool cmd_chpater_restore(void* scriptParam)
{
    return true;
}

bool cmd_set_basha_go_into(void* scriptParam)
{
    PARAM_SET_BASHA_GO_INTO* param = (PARAM_SET_BASHA_GO_INTO*)scriptParam;
    status::g_StageAttribute.setCarriageEnter(param->flag == 0);
    if (data_02101c88.unkfunc_02051818(4)) {
        twn::TownPlayerManager::getSingleton().resetParty();
    }
    return true;
}

bool cmd_is_load_init(void* scriptParam)
{
    PARAM_IS_LOAD_INIT* param = (PARAM_IS_LOAD_INIT*)scriptParam;
    int index = status::g_StageInfo.getReturnGame();
    bool ret;
    switch (index) {
    case dq5::RETURN_GAME_NONE:
        ret = false;
        break;
    case dq5::RETURN_GAME_CHURCH:
    case dq5::RETURN_GAME_ABORT:
    case dq5::RETURN_GAME_LOSE:
        ret = true;
        break;
    default:
        ret = false;
        break;
    }
    if (param->flag == 1) {
        ret = !ret;
    }
    return ret;
}

bool cmd_save_last_party()
{
    status::g_StageAttribute.setCarriageEnable(true);
    status::g_Party.setCarriage(true);
    status::g_Party.setNormalMode();
    for (int i = 0; i < 9; i++) {
        if (status::g_Party.getCount() > i) {
            status::g_StageInfo.setLastParty(i, status::g_Party.getPlayerIndex(i));
        } else {
            status::g_StageInfo.setLastParty(i, 0);
        }
    }
    return true;
}

bool cmd_map_black(void* scriptParam)
{
    NNSG3dResTex* tex = getLastModelTexture();
    dss::Fix32Vector3 rate(0, 0, 0);
    applyModelPaletteRgbRate(tex, rate);
    return true;
}

bool cmdIsTimezone(void* scriptParam)
{
    PARAM_IS_TIMEZONE* param = (PARAM_IS_TIMEZONE*)scriptParam;
    if (param->timezone + 1 == TIME_ZONE_MORNING || param->timezone + 1 == TIME_ZONE_DAYTIME) {
        if (status::g_StageInfo.getDayNight() == dq5::DAY_NIGHT_DAY) {
            return true;
        }
        return false;
    }
    if (status::g_StageInfo.getDayNight() == dq5::DAY_NIGHT_NIGHT) {
        return true;
    }
    return false;
}

bool cmdIsTimezone2(void* scriptParam)
{
    PARAM_IS_TIMEZONE2* param = (PARAM_IS_TIMEZONE2*)scriptParam;
    if (status::g_StageInfo.getTimeZone() == TIME_ZONE_MORNING && param->timeZone == TIME_ZONE_MORNING) {
        return true;
    }
    if (status::g_StageInfo.getTimeZone() == TIME_ZONE_DAYTIME && param->timeZone == TIME_ZONE_DAYTIME) {
        return true;
    }
    if (status::g_StageInfo.getTimeZone() == TIME_ZONE_EVENING && param->timeZone == TIME_ZONE_EVENING) {
        return true;
    }
    if (status::g_StageInfo.getTimeZone() == TIME_ZONE_NIGHT && param->timeZone == TIME_ZONE_NIGHT) {
        return true;
    }
    return false;
}

bool cmdSetTimezone(void* scriptParam)
{
    PARAM_SET_TIMEZONE* param = (PARAM_SET_TIMEZONE*)scriptParam;
    status::g_StageInfo.setTimeZone((TIME_ZONE)(param->timezone + 1));
    if (data_02101c88.unkfunc_02051818(6) == true) {
        fld::FieldStage::getSingleton()->ChangeTime(1);
    } else {
        twn::TownStageEffectManager::getSingleton()->loadStage();
    }
    return true;
}

bool cmdSetTimezonePause(void* scriptParam)
{
    PARAM_SET_TIMEZONE_PAUSE* param = (PARAM_SET_TIMEZONE_PAUSE*)scriptParam;
    status::g_StageAttribute.setTimestopFlag(param->flag);
    return true;
}

void Cmd_key_wait_typeB::initialize(char* scriptParam)
{
}

void Cmd_key_wait_typeB::execute()
{
}

int Cmd_key_wait_typeB::isEnd()
{
    return cmn::g_CommonCounterInfo.checkBottun();
}

Cmd_key_wait_typeB gCmd_key_wait_typeB;

bool cmdCharcter3DRotate(void* scriptParam)
{
    PARAM_CHARCTER_3D_ROTATE* param = (PARAM_CHARCTER_3D_ROTATE*)scriptParam;
    dss::Vector3<short> rot;
    dss::Fix32 rotX, rotY, rotZ;
    rotX.value = param->rotX;
    rotY.value = param->rotY;
    rotZ.value = param->rotZ;
    rot.vx = degreeToAngle(rotX);
    rot.vy = degreeToAngle(rotY);
    rot.vz = degreeToAngle(rotZ);
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setRotate(ctrl, rot);
    return true;
}

bool cmd_set_sleep_near(void* scriptParam)
{
    PARAM_SET_SLEEP_NEAR* param = (PARAM_SET_SLEEP_NEAR*)scriptParam;
    dss::Fix32 defNear(0L);
    defNear.value = param->defNear;
    dss::Fix32 phtmNear(0L);
    phtmNear.value = param->phtmNear;
    dss::Fix32 offset(0L);
    offset.value = param->offset;
    if (param->def == 0) {
        if (defNear == dss::Fix32(0L)) {
            defNear = dss::Fix32(0.27f);
        }
        if (phtmNear == dss::Fix32(0L)) {
            phtmNear = dss::Fix32(0.173f);
        }
        if (offset == dss::Fix32(0L)) {
            offset = dss::Fix32(0.194f);
        }
    } else if (param->def == 1) {
        if (defNear == dss::Fix32(0L)) {
            defNear = dss::Fix32(0.254f);
        }
        if (phtmNear == dss::Fix32(0L)) {
            phtmNear = dss::Fix32(0.169f);
        }
        if (offset == dss::Fix32(0L)) {
            offset = dss::Fix32(0.455f);
        }
    }
    DisplayCharacter::sleepBodyOffset_ = dss::Fix32(defNear);
    DisplayCharacter::sleepHeadOffset_ = dss::Fix32(phtmNear);
    DisplayCharacter::sleepHeight_ = dss::Fix32(offset);
    return true;
}

bool cmdMiniGame(void* scriptParam)
{
    PARAM_MINI_GAME* param = (PARAM_MINI_GAME*)scriptParam;
    switch (param->category) {
    case 0:
    case 1:
        twn::TownPlayerManager::getSingleton().setLock(true);
        cmn::g_cmnPartyInfo.setPrevLocation(true);
        g_Global.setMinigame(param->category);
        gMaterielMenu_SLOT.slotType_ = param->index;
        g_Global.startCasino();
        break;
    case 3: {
        int ctrl = getPlacementCtrlId();
        TownCharacterManager::getSingleton()->setPlayerDirection(ctrl);
        int type = 0x24;
        window::gShopMenuControl.startMenu(type);
        cmn::g_cmnPartyInfo.setTalkCharaCtrlID(ctrl);
        break;
    }
    case 4: {
        int ctrl = getPlacementCtrlId();
        TownCharacterManager::getSingleton()->setPlayerDirection(ctrl);
        int type = 0x27;
        window::gShopMenuControl.startMenu(type);
        cmn::g_cmnPartyInfo.setTalkCharaCtrlID(ctrl);
        break;
    }
    case 2: {
        int ctrl = getPlacementCtrlId();
        TownCharacterManager::getSingleton()->setPlayerDirection(ctrl);
        int type = 0x1A;
        window::gShopMenuControl.startMenu(type);
        cmn::g_cmnPartyInfo.setTalkCharaCtrlID(ctrl);
        break;
    }
    case 5: {
        cmn::g_cmnPartyInfo.setKeep(true, g_Global.getMapNameId(), false);
        dss::Fix32Vector3 pos(twn::TownPlayerManager::getSingleton().getPosition());
        twn::g_SugorokuInfo.setEndMapNameId(g_Global.getMapNameId());
        twn::g_SugorokuInfo.setEndMapPosition(pos);
        twn::g_SugorokuInfo.setEndMapDirIdx(twn::TownPlayerManager::getSingleton().getDirection());
        twn::g_SugorokuInfo.setContinue(twn::TownSugorokuInfo::START_SUGOROKU);
        g_Global.startTown(g_Global.getMapNameId());
        break;
    }
    }
    return true;
}

bool cmd_check_shoplist(void* scriptParam)
{
    return true;
}

bool cmd_start_opening(void* scriptParam)
{
    PARAM_START_OPENING* param = (PARAM_START_OPENING*)scriptParam;
    g_Global.startTitle();
    ceremony::CeremonySetting::getSingleton()->setOpening(1);
    ceremony::CeremonySetting::getSingleton()->setNextActMap(param->floor);
    dss::Fix32Vector3 pos;
    pos.vx.value = param->exitX;
    pos.vy.value = param->exitY;
    pos.vz.value = param->exitZ;
    ceremony::CeremonySetting::getSingleton()->setNextActPos(pos);
    Sound::strmStop(0xF);
    return true;
}

bool cmd_the_end(void* scriptParam)
{
    g_Global.startFin();
    return true;
}

bool cmd_check_the_end(void* scriptParam)
{
    if (getGameRegion() == 1) {
        return ceremony::CeremonyEndingFin::getSingleton()->isEnd();
    }
    return ceremony::UnkCeremonyEndingFin::getSingleton()->isEnd();
}

bool cmd_check_endroll(void* scriptParam)
{
    return ceremony::CeremonyEndingSystem::getSingleton()->isEnd();
}

bool cmd_map_change_timezone(void* scriptParam)
{
    PARAM_MAP_CHANGE_TIMEZONE* param = (PARAM_MAP_CHANGE_TIMEZONE*)scriptParam;
    status::g_StageAttribute.setTimeZoneEnable(true);
    status::g_StageInfo.setTimeZone((TIME_ZONE)param->timezone);
    return true;
}

bool cmdIsTrigger(void* scriptParam)
{
    PARAM_IS_TRIGGER* param = (PARAM_IS_TRIGGER*)scriptParam;
    dss::Fix32Vector3 pos(twn::TownPlayerManager::getSingleton().getPosition());
    if (param->startX < pos.vx.value && param->endX > pos.vx.value && param->startY < pos.vy.value && param->endY > pos.vy.value && param->startZ < pos.vz.value && param->endZ > pos.vz.value) {
        return true;
    }
    return false;
}

bool cmd_set_lura_message(void* scriptParam)
{
    PARAM_SET_LURA_MESSAGE* param = (PARAM_SET_LURA_MESSAGE*)scriptParam;
    int setMes = 0;
    if (param->flag == 0) {
        setMes = param->message;
    }
    status::g_Menu.setLuraDisableMessage(setMes);
    return true;
}

bool cmd_set_lura_message2(void* scriptParam)
{
    PARAM_SET_LURA_MESSAGE2* param = (PARAM_SET_LURA_MESSAGE2*)scriptParam;
    int message[3] = {param->message1, param->message2, param->message3};
    char charaVoice[3] = {param->voice1, param->voice2, param->voice3};
    for (int i = 0; i < 3; i++) {
        status::g_Menu.setLuraDisableMessage(i, message[i]);
        int voice = 0x30;
        switch (charaVoice[i]) {
        case 1:
            voice = 0x31;
            break;
        case 2:
            voice = 0x32;
            break;
        case 3:
            voice = 0x33;
            break;
        case 4:
            voice = 0x39;
            break;
        }
        status::g_Menu.setLuraDisableMessageVoice(i, voice);
    }
    return true;
}

bool cmd_check_event_item(void* scriptParam)
{
    PARAM_CHECK_EVENT_ITEM* param = (PARAM_CHECK_EVENT_ITEM*)scriptParam;
    if (status::g_Menu.getMenuEventFlag() == true) {
        if (data_02101c88.unkfunc_02051818(4)) {
            twn::TownPlayerManager::getSingleton().setLock(false);
        } else {
            fld::FieldPlayerManager::getSingleton().setLock(false);
        }
        status::g_Menu.resetMenuEventNo();
        status::g_Menu.setMenuEventFlag(false);
        return true;
    }
    status::g_Menu.setMenuEventNo(param->item);
    return false;
}

bool cmd_check_event_item2(void* scriptParam)
{
    PARAM_CHECK_EVENT_ITEM2* param = (PARAM_CHECK_EVENT_ITEM2*)scriptParam;
    short item[8] = {param->item1, param->item2, param->item3, param->item4, param->item5, param->item6, param->item7, param->item8};
    if (status::g_Menu.getMenuEventFlag() == true) {
        twn::TownPlayerManager::getSingleton().setLock(false);
        status::g_Menu.resetMenuEventNo();
        status::g_Menu.setMenuEventFlag(false);
        return true;
    }
    status::g_Menu.setMenuEventNo(item, 8);
    return false;
}

bool cmdCheckUseEventItem(void* scriptParam)
{
    PARAM_CHECK_EVENT_MAGIC* param = (PARAM_CHECK_EVENT_MAGIC*)scriptParam;
    if (param->magic == status::g_Menu.getItemIndex()) {
        return true;
    }
    return false;
}

bool cmd_check_event_magic(void* scriptParam)
{
    PARAM_CHECK_USE_EVENT_ITEM* param = (PARAM_CHECK_USE_EVENT_ITEM*)scriptParam;
    if (status::g_Menu.getMenuEventFlag() == true) {
        twn::TownPlayerManager::getSingleton().setLock(false);
        status::g_Menu.resetMenuEventNo();
        status::g_Menu.setMenuEventFlag(false);
        return true;
    }
    status::g_Menu.setMenuEventNo(param->item);
    return false;
}

void SugorokuTime::initialize(char* scriptParam)
{
    cmn::g_cmnPartyInfo.setTalkCharaCtrlID(getPlacementCtrlId());
    twn::TownSugorokuManager::getSingleton().setTreasuerRoom(false);
    twn::TownSugorokuManager::getSingleton().setNextState(0x19);
}

void SugorokuTime::execute()
{
}

int SugorokuTime::isEnd()
{
    return twn::TownSugorokuManager::getSingleton().getSugorokuTimeEnd();
}

SugorokuTime g_SugorokuTime;

bool cmd_set_sugoroku_treasure(void* scriptParam)
{
    twn::g_SugorokuInfo.setContinue(twn::TownSugorokuInfo::CONTINUE_TREASURE_ROOM);
    return true;
}

bool cmdSetSugorokuEnd(void* scriptParam)
{
    dss::Fix32Vector3 pos(twn::TownPlayerManager::getSingleton().getPosition());
    twn::TownPlayerManager::getSingleton().setPartyToFirst(pos);
    twn::TownPlayerManager::getSingleton().resetDrawPartyCount();
    cmn::g_cmnPartyInfo.setKeep(false, 0, true);
    twn::g_SugorokuInfo.setSugorokuEndMode(0);
    twn::TownPlayerManager::getSingleton().setLock(false);
    if (g_Global.getMapNameId() == 0x223) {
        twn::TownPlayerManager::getSingleton().setActionType(twn::ACTION_TYPE_FALL);
        twn::TownPlayerManager::getSingleton().player_.townActionFall_.setCollFall();
        twn::TownPlayerManager::getSingleton().player_.townActionFall_.count_ = 3;
    }
    return true;
}

bool cmdSetSackItem(void* scriptParam)
{
    PARAM_SET_SACK_ITEM* param = (PARAM_SET_SACK_ITEM*)scriptParam;
    status::HaveItemSack& sack = status::g_Party.haveItemSack_;
    if (param->flag == 0) {
        if (param->item == 0xD1) {
            status::g_Party.addMedalCoin(param->count);
            status::g_Story.setMedalFlag(true);
            return true;
        }
        sack.add(param->item, param->count);
        cmn::PartyTalk::getSingleton().setPreItem(param->item);
    } else {
        if (param->item == 0xD1) {
            status::g_Party.setMedalCoin(status::g_Party.getMedalCoin() - param->count);
            return true;
        }
        if (!sack.isItem(param->item)) {
            return true;
        }
        int itemCount = sack.getCount();
        int delItemPos = 0;
        for (int i = 0; i < itemCount; i++) {
            if (param->item == sack.getItem(i)) {
                delItemPos = i;
                break;
            }
        }
        for (int i = 0; i < param->count; i++) {
            sack.execThrow(delItemPos);
            if (!sack.isItem(param->item)) {
                break;
            }
        }
    }
    return true;
}

void GameWait::initialize(char* scriptParam)
{
    PARAM_SYSTEM_WAIT* param = (PARAM_SYSTEM_WAIT*)scriptParam;
    count_ = 0;
    countFrame_ = param->frame;
}

void GameWait::execute()
{
    count_++;
}

int GameWait::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

GameWait g_GameWait;

bool cmdSetPlayerTownVehicle(void* scriptParam)
{
    PARAM_SET_PLAYER_TOWN_VEHICLE* param = (PARAM_SET_PLAYER_TOWN_VEHICLE*)scriptParam;
    if (param->vehicle == 0) {
        twn::TownPlayerManager::getSingleton().setIkadaMove();
    }
    return true;
}

bool cmdCheckSpaceItemChara(void* scriptParam)
{
    PARAM_CHECK_SPACE_ITEM_CHARA* param = (PARAM_CHECK_SPACE_ITEM_CHARA*)scriptParam;
    status::g_Party.setPlayerMode();
    bool haveFukuro = true;
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveItem().getCount() != status::HaveItem::ITEM_MAX) {
            haveFukuro = false;
            break;
        }
    }
    if ((param->flag == 0 && haveFukuro == false) || (param->flag == 1 && haveFukuro == true)) {
        return true;
    }
    return false;
}

bool cmdSetMacroBaby(void* scriptParam)
{
    char name_a[512];
    char name_b[512];
    TextAPI::extractText(name_a, sizeof(name_a), 0xE0000000, 0x3DB);
    TextAPI::extractText(name_b, sizeof(name_b), 0xE0000000, 0x3DC);
    if (dss::strcmp(status::PlayerDataAll::getPlayerData(1).getNameString(), name_a) == 0) {
        TextAPI::setUserString(0, name_b);
    } else {
        TextAPI::setUserString(0, name_a);
    }
    TextAPI::setMACRO0(0x78, 0xD0000000, 0);
    return true;
}

bool cmdExecRuraLink(void* scriptParam)
{
    cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_RURA_AFTER);
    cmn::g_extraMapLink.setRuraLink();
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatusForPlayerIndex(1).getHaveStatusInfo();
    int mp = statusInfo.getMp() - 8;
    statusInfo.setMp(dss::clamp<int>(0, mp, 999));
    return true;
}

bool cmdCoercionSort(void* scriptParam)
{
    PARAM_COERCTION_SORT* param = (PARAM_COERCTION_SORT*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    int count = status::g_Party.getCount();
    int posCount = 0;
    int index[4] = {-1};
    for (int i = 0; i < 4; i++) {
        index[i] = -1;
    }
    int pos[4] = {param->index1, param->index2, param->index3, param->index4};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < count; j++) {
            if (pos[i] == status::g_Party.getPlayerStatus(j).getHaveStatusInfo().haveStatus_.getPlayerKindIndex()) {
                index[posCount] = j;
                posCount++;
                break;
            }
        }
    }
    status::g_Party.reorder(index[0], index[1], index[2], index[3]);
    cmn::GameManager::getSingleton().resetParty();
    status::g_StageAttribute.setCoercionSort(false);
    return true;
}

bool cmdSetCoercionSortEnable(void* scriptParam)
{
    PARAM_SET_COERCION_SORT_ENABLE* param = (PARAM_SET_COERCION_SORT_ENABLE*)scriptParam;
    status::g_StageAttribute.setCoercionSort(param->flag);
    return true;
}

bool cmdSaveClearMonsterParty(void* scriptParam)
{
    status::g_Party.setBattleMode();
    for (int i = 0; i < 3; i++) {
        status::g_Story.setClearFriendMonster(i, -1);
    }
    int FriendCount = 0;
    int partyCount = status::g_Party.getCount();
    for (int i = 0; i < partyCount; i++) {
        status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
        if (statusInfo.haveStatus_.isFriendMonster() && statusInfo.haveStatus_.getPlayerKindIndex() != 0x11) {
            status::g_Story.setClearFriendMonster(FriendCount, statusInfo.getPlayerIndex());
            FriendCount++;
        }
        if (FriendCount == 3) {
            break;
        }
    }
    return true;
}

bool cmdCheckSaveMonster(void* scriptParam)
{
    PARAM_CHECK_SAVE_MONSTER* param = (PARAM_CHECK_SAVE_MONSTER*)scriptParam;
    if (status::g_Story.getClearFriendMonster(param->index) != -1) {
        return true;
    }
    return false;
}

bool cmdCopySaveMonster(void* scriptParam)
{
    PARAM_COPY_SAVE_MONSTER* param = (PARAM_COPY_SAVE_MONSTER*)scriptParam;
    int charaIndex = status::g_Story.getClearFriendMonster(param->index);
    if (charaIndex != -1) {
        int ctrl = getPlacementCtrlId();
        TownCharacterManager::getSingleton()->changePose(ctrl, status::PlayerDataAll::getPlayerData(charaIndex).getCgIndex());
    }
    return true;
}

bool cmdSetMacroPMName(void* scriptParam)
{
    PARAM_SET_MACRO_P_M_NAME* param = (PARAM_SET_MACRO_P_M_NAME*)scriptParam;
    TextAPI::setMACRO0(0x7E, 0x50000000, status::g_Story.getClearFriendMonster(param->index));
    return true;
}

bool cmdSetMacroSecond(void* scriptParam)
{
    int second = twn::g_SugorokuInfo.getTime() / 60;
    TextAPI::setMACRO0(0x71, 0xF0000000, second);
    return true;
}

void CmdFriendMonsterMessage::initialize(char* scriptParam)
{
    dq5::level::PartytalkMonster::setup();
    int ctrlID = status::g_Story.getClearFriendMonster(2);
    int playerIndex = status::PlayerDataAll::getPlayerData(ctrlID).getKindIndex();
    int record = playerIndex + 0x36;
    if (playerIndex == 0x56) {
        record = 0x8E;
    }
    if (playerIndex == 0x57) {
        record = 0x8F;
    }
    dq5::level::PartytalkMonster* data = dq5::level::PartytalkMonster::getRecord(record);
    int voice = 0x30;
    switch (data->getConduct()) {
    case 0:
        break;
    case 0x13:
        voice = 0x33;
        break;
    case 0x14:
        voice = 0x32;
        break;
    case 0x15:
        voice = 0x31;
        break;
    }
    cmn::g_talkSound.setOrderMessage(voice);
    cmn::g_talkSound.setMessageSound(1, -1);
    twn::TownWindowSystem::getSingleton().openTalkMessage(data->getMessage(), 1);
    dq5::level::PartytalkMonster::cleanup();
}

int CmdFriendMonsterMessage::isEnd()
{
    if (!twn::TownWindowSystem::getSingleton().isMessageStart() && !twn::TownWindowSystem::getSingleton().isMessageOpen()) {
        return true;
    }
    return false;
}

CmdFriendMonsterMessage gCmdFriendMonsterMessage;

bool cmdSetShopList(void* scriptParam)
{
    PARAM_SET_SHOP_LIST* param = (PARAM_SET_SHOP_LIST*)scriptParam;
    status::g_StageAttribute.setShopListDisable(param->flag);
    return true;
}

bool cmdChengeShopChater(void* scriptParam)
{
    PARAM_CHANGE_SHOP_CHAPTER* param = (PARAM_CHANGE_SHOP_CHAPTER*)scriptParam;
    status::ShopList::SECTION section = status::ShopList::SECTION_FIRST;
    switch (param->chapter) {
    case 0:
        if (status::g_Story.getChapter() == dq5::CHAPTER_SEINENKI) {
            section = status::ShopList::SECTION_SECOND;
        } else {
            section = status::ShopList::SECTION_THIRD;
        }
        break;
    case 1:
        section = status::ShopList::SECTION_FIRST;
        break;
    case 2:
        section = status::ShopList::SECTION_SECOND;
        break;
    case 3:
        section = status::ShopList::SECTION_THIRD;
        break;
    }
    status::ShopList::setSection(section);
    int index = dq5::level::g_LevelDataUtility.searchShopDataIndex(g_Global.getNowAreaNo(), section);
    status::g_StageAttribute.setShopDataIndex(index);
    return true;
}

bool cmdResetReorderFlag(void* scriptParam)
{
    status::PartyStatusUtility::resetForceReorderMember();
    return true;
}

bool cmdSetMagicMove(void* scriptParam)
{
    PARAM_SET_MAGIC_MOVE* param = (PARAM_SET_MAGIC_MOVE*)scriptParam;
    switch (param->attr) {
    case 0:
        status::g_StageInfo.setRiremitMapId(param->map);
        status::g_StageInfo.symbolID_ = param->next;
        break;
    case 1:
        status::g_StageInfo.setRanaMapNameId(param->map);
        status::g_StageInfo.lastFldSurface_ = param->next;
        break;
    case 2:
        status::g_StageInfo.kimeraSymbol_ = param->next;
        break;
    }
    return true;
}

bool cmdSetMagicMoveSetDisable(void* scriptParam)
{
    status::g_StageAttribute.setKimeraSetDisable(true);
    return true;
}

void CmdRiseupPlayerEquip::initialize(char* scriptParam)
{
    PARAM_RISEUP_PLAYER_EQUIP* param = (PARAM_RISEUP_PLAYER_EQUIP*)scriptParam;
    status::g_Party.setAllPlayerMode();
    int playerPos;
    if (param->playerFlag == 0) {
        playerPos = param->index - 1;
        if (playerPos >= status::g_Party.getCarriageOutCount()) {
            return;
        }
    } else {
        playerPos = status::g_Party.getSortIndex(param->index);
        if (playerPos == -1) {
            return;
        }
    }
    status::HaveEquipment& equip = status::g_Party.getPlayerStatus(playerPos).getHaveStatusInfo().getHaveEquipment();
    int itemID = 0;
    switch (param->equip) {
    case 0:
        itemID = equip.getEquipment(ITEM_WEAPON, 0);
        break;
    case 1:
        itemID = equip.getEquipment(ITEM_ARMOR, 0);
        break;
    case 2:
        itemID = equip.getEquipment(ITEM_SHIELD, 0);
        break;
    case 3:
        itemID = equip.getEquipment(ITEM_HELMET, 0);
        break;
    case 4:
        itemID = equip.getEquipment(ITEM_ACCESSORY, 0);
        break;
    case 5:
        itemID = equip.getEquipment(ITEM_ACCESSORY, 1);
        break;
    case 6:
        itemID = equip.getEquipment(ITEM_ACCESSORY, 2);
        break;
    case 7:
        itemID = equip.getEquipment(ITEM_ACCESSORY, 3);
        break;
    case 8:
        itemID = equip.getEquipment(ITEM_ACCESSORY, 4);
        break;
    }
    if (itemID == 0) {
        return;
    }
    dss::Fix32Vector3 startPos;
    if (param->flag == 0) {
        startPos = twn::TownPlayerManager::getSingleton().getPosition();
    } else {
        startPos.vx.value = param->startX;
        startPos.vy.value = param->startY;
        startPos.vz.value = param->startZ;
    }
    ctrlID_ = twn::TownRiseupManager::getSingleton().setup(itemID, startPos);
}

int CmdRiseupPlayerEquip::isEnd()
{
    if (!twn::TownRiseupManager::getSingleton().isEnable(ctrlID_)) {
        return true;
    }
    return false;
}

CmdRiseupPlayerEquip g_CmdRiseupPlayerEquip;

bool cmdSetFadeDisable(void* scriptParam)
{
    fadeEffector.setFadeDisable(true);
    return true;
}

bool cmdReorderFormerMember(void* scriptParam)
{
    status::PartyStatusUtility::reorderFormerMember();
    return true;
}

void ScriptSystemCommand_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
