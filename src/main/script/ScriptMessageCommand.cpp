#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

// The original TU also emitted ScriptCommand's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "main/script/ScriptMessageCommand.hpp"
#include "main/script/CommandParam.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/leveldata/SugorokuData.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/menu/MessageWindow.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/ShopList.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"
#include "main/window/ShopMenuControl.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov005/fld/FieldWindowSystem.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"

inline void ScriptCommandWeakVtable::initialize(char* scriptParam)
{
}

inline int ScriptCommandWeakVtable::isEnd()
{
    return 0;
}

#pragma thumb on

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline bool fld::FieldWindowSystem::isMessageOpen()
{
    return message_open_;
}

inline cmn::PlayerManager* cmn::GameManager::getPlayerManager()
{
    return playerManager_;
}

inline menu::MenuBase::MENUBASE_STAT menu::MenuBase::getStat()
{
    return stat_;
}

inline void menu::MenuBase::setStat(MENUBASE_STAT s)
{
    stat_ = s;
}

inline void window::ShopMenuControl::startMenu(int menuType)
{
    menuType_ = menuType;
    state_ = 7;
}

inline bool window::ShopMenuControl::isMenuEnd()
{
    return state_ == 8;
}

inline void MaterielMenu_WINDOW_MANAGER::setSaveMenuType(int type)
{
    type_ = type;
}

inline int MaterielMenu_WINDOW_MANAGER::getCloseMaterielMenu()
{
    return endWindow_;
}

inline void cmn::CommonPartyInfo::setTalkCharaCtrlID(int ctrl)
{
    ctrlID_ = ctrl;
}

inline short status::MenuStatus::getActorIndex()
{
    return actorIndex_;
}

inline short status::MenuStatus::getTargetIndex()
{
    return targetIndex_;
}

inline void status::MenuStatus::setTargetIndex(short target)
{
    targetIndex_ = target;
}

inline short status::MenuStatus::getItemIndex()
{
    return itemIndex_;
}

inline void status::MenuStatus::setItemIndex(short index)
{
    itemIndex_ = index;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline bool status::HaveStatusInfo::isPlayer() const
{
    int flag = false;
    unsigned char type = (unsigned char)haveStatus_.playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline bool status::HaveStatus::isFriendMonster() const
{
    return playerType_ == TYPE_FRIENDMONSTER;
}

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline short status::StageInfo::getLastParty(int num)
{
    return lastParty_[num];
}

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

inline void status::ShopList::setSection(int section)
{
    section_ = section;
}

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline unsigned int dq5::level::SugorokuData::getArraySize()
{
    return binary_.record_;
}

inline dq5::level::SugorokuData* dq5::level::SugorokuData::getRecord(int index)
{
    return (SugorokuData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int SoundManager::getBgmIndex()
{
    return bgmIndex_;
}

inline void SoundManager::setInterrupt(int flag)
{
    interrupt_ = flag;
}

inline void CmdMessage::execute()
{
}

inline void CmdMessage2::execute()
{
}

inline void CmdMessageWaitClosing::execute()
{
}

inline void CmdMessage2WaitClosing::execute()
{
}

inline void MenuYesNo::execute()
{
}

inline void MenuYesNo::terminate()
{
}

inline void Menu_save::execute()
{
}

inline void Message1SelfClosing::terminate()
{
}

inline void ShakeMessage::execute()
{
}

inline void DelayMessage::execute()
{
}

inline void NarrationMessage::execute()
{
}

inline void NarrationMessage2::execute()
{
}

bool cmd_set_no_search_message(void* scriptParam)
{
    return true;
}

void CmdMessage::initialize(char* scriptParam)
{
    PARAM_MESSAGE1* param = (PARAM_MESSAGE1*)scriptParam;
    int ctrl = getPlacementCtrlId();
    if (getObjectCount() > ctrl) {
        if (data_02101c88.isCurrentPart(4)) {
            cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
        }
    } else {
        cmn::g_talkSound.setVoice(0);
        ctrl = -1;
    }
    cmn::g_talkSound.setMessageSound(param->count, ctrl);
    if (data_02101c88.isCurrentPart(6)) {
        fld::FieldWindowSystem::getSingleton()->openMessage(param->message, param->count);
    } else if (twn::TownWindowSystem::getSingleton().isMessageStart()) {
        for (int i = 0; i < param->count; i++) {
            twn::TownWindowSystem::getSingleton().addCommonMessage(param->message + i);
        }
    } else {
        twn::TownWindowSystem::getSingleton().openMessage(param->message, param->count);
    }
    cmn::PartyTalk::getSingleton().setPreMessageNo(param->message + param->count - 1);
}

int CmdMessage::isEnd()
{
    return true;
}

CmdMessage gCmdMessage;

void CmdMessage2::initialize(char* scriptParam)
{
    PARAM_MESSAGE2* param = (PARAM_MESSAGE2*)scriptParam;
    int ctrl = getPlacementCtrlId();
    if (getObjectCount() > ctrl) {
        if (data_02101c88.isCurrentPart(4)) {
            cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
        }
    } else {
        cmn::g_talkSound.setVoice(0);
        ctrl = -1;
    }
    unsigned int mess[8];
    mess[0] = param->message0;
    mess[1] = param->message1;
    mess[2] = param->message2;
    mess[3] = param->message3;
    mess[4] = param->message4;
    mess[5] = param->message5;
    mess[6] = param->message6;
    mess[7] = param->message7;
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (mess[i] == 0) {
            break;
        }
        count++;
    }
    cmn::g_talkSound.setMessageSound(count, ctrl);
    if (data_02101c88.isCurrentPart(6)) {
        fld::FieldWindowSystem::getSingleton()->openCommonMessage();
        for (int i = 0; i < 8; i++) {
            if (mess[i] != 0) {
                fld::FieldWindowSystem::getSingleton()->addCommonMessage(mess[i]);
            }
        }
    } else {
        if (!twn::TownWindowSystem::getSingleton().isMessageStart()) {
            twn::TownWindowSystem::getSingleton().openCommonMessage();
        }
        for (int i = 0; i < 8; i++) {
            if (mess[i] != 0) {
                twn::TownWindowSystem::getSingleton().addCommonMessage(mess[i]);
            }
        }
    }
    cmn::PartyTalk::getSingleton().setPreMessageNo(mess[count - 1]);
}

int CmdMessage2::isEnd()
{
    return true;
}

CmdMessage2 gCmdMessage2;

void CmdMessageWaitClosing::initialize(char* scriptParam)
{
    gCmdMessage.initialize(scriptParam);
}

int CmdMessageWaitClosing::isEnd()
{
    if (data_02101c88.isCurrentPart(6)) {
        if (!fld::FieldWindowSystem::getSingleton()->isMessageOpen()) {
            return true;
        }
    } else if (!twn::TownWindowSystem::getSingleton().isMessageStart() && !twn::TownWindowSystem::getSingleton().isMessageOpen()) {
        return true;
    }
    return false;
}

CmdMessageWaitClosing gCmdMessageWaitClosing;

void CmdMessage2WaitClosing::initialize(char* scriptParam)
{
    gCmdMessage2.initialize(scriptParam);
}

int CmdMessage2WaitClosing::isEnd()
{
    if (data_02101c88.isCurrentPart(6)) {
        if (!fld::FieldWindowSystem::getSingleton()->isMessageOpen()) {
            return true;
        }
    } else if (!twn::TownWindowSystem::getSingleton().isMessageStart() && !twn::TownWindowSystem::getSingleton().isMessageOpen()) {
        return true;
    }
    return false;
}

CmdMessage2WaitClosing gCmdMessage2WaitClosing;

bool cmd_set_macro_actor()
{
    TextAPI::setMACRO0(1, 0x50000000, status::g_Menu.getActorIndex());
    return true;
}

bool cmd_set_macro_target()
{
    if (status::g_Menu.getTargetIndex() != 0) {
        TextAPI::setMACRO0(0x12, 0x50000000, status::g_Menu.getTargetIndex());
        status::g_Menu.setTargetIndex(0);
        return true;
    }
    status::g_Party.setPlayerMode();
    int count = 0;
    int player = 0;
    int target = 0;
    for (; count < status::g_Party.getCount(); count++) {
        status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(count).getHaveStatusInfo();
        if (!statusInfo.isDeath()) {
            if (statusInfo.isPlayer() == true && target == 0) {
                target = statusInfo.getPlayerIndex();
            }
            if (statusInfo.getHaveItem().getCount() != 12) {
                player = statusInfo.getPlayerIndex();
                TextAPI::setMACRO0(0x12, 0x50000000, player);
                break;
            }
        }
    }
    if (player == 0) {
        TextAPI::setMACRO0(0x12, 0x50000000, target);
    }
    return true;
}

bool cmd_set_macro_target_index(void* scriptParam)
{
    PARAM_SET_MACRO_TARGET_INDEX* param = (PARAM_SET_MACRO_TARGET_INDEX*)scriptParam;
    TextAPI::setMACRO0(0x12, 0x50000000, param->index);
    return true;
}

bool cmdSetMacroTargetForPosition(void* scriptParam)
{
    PARAM_SET_MACRO_TARGET_FOR_POSITION* param = (PARAM_SET_MACRO_TARGET_FOR_POSITION*)scriptParam;
    status::g_Party.setPlayerMode();
    int playerIndex[4] = { -1 };
    for (int i = 0; i < 4; i++) {
        playerIndex[i] = -1;
    }
    int carriageOutCount = status::g_Party.getCarriageOutCount();
    int count = 0;
    for (int i = 0; i < carriageOutCount; i++) {
        status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
        if (!statusInfo.isDeath()) {
            playerIndex[count] = statusInfo.getPlayerIndex();
            count++;
        }
    }
    TextAPI::setMACRO0(0x12, 0x50000000, playerIndex[param->index - 1]);
    return true;
}

bool cmdSetMacroTargetForIndex(void* scriptParam)
{
    PARAM_SET_MACRO_TARGET_FOR_POSITION* param = (PARAM_SET_MACRO_TARGET_FOR_POSITION*)scriptParam;
    unsigned int targetIndex = param->index;
    if (targetIndex > 15) {
        targetIndex = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(targetIndex);
    }
    TextAPI::setMACRO0(0x12, 0x50000000, targetIndex);
    return true;
}

bool cmdSetMacroTargetWithDeath(void* scriptParam)
{
    PARAM_SET_MACRO_TARGET_WITH_DEATH* param = (PARAM_SET_MACRO_TARGET_WITH_DEATH*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    int alive[4] = { -1 };
    for (int i = 0; i < 4; i++) {
        alive[i] = -1;
    }
    int death[4] = { -1 };
    for (int i = 0; i < 4; i++) {
        death[i] = -1;
    }
    int aliveCount = 0;
    int deathCount = 0;
    int memberCount = status::g_Party.getCarriageOutCount();
    for (int i = 0; i < memberCount; i++) {
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() == true) {
            death[deathCount] = i;
            deathCount++;
        } else {
            alive[aliveCount] = i;
            aliveCount++;
        }
    }
    for (int i = 0; i < deathCount; i++) {
        alive[aliveCount + i] = death[i];
    }
    if (alive[param->index - 1] == -1) {
        TextAPI::setMACRO0(0x12, 0x50000000, status::g_Party.getPlayerStatus(alive[0]).getHaveStatusInfo().getPlayerIndex());
    } else {
        TextAPI::setMACRO0(0x12, 0x50000000, status::g_Party.getPlayerStatus(alive[param->index - 1]).getHaveStatusInfo().getPlayerIndex());
    }
    return true;
}

bool cmdSetMacroMName(void* scriptParam)
{
    PARAM_SET_MACRO_M_NAME* param = (PARAM_SET_MACRO_M_NAME*)scriptParam;
    if (data_02101c88.isCurrentPart(5)) {
        TextAPI::setMACRO0(0xd, 0x60000000, param->index);
    } else {
        TextAPI::setMACRO0(0xd, 0x60000000, status::PlayerDataAll::getCtrlFromFriendMonsterIndex(param->index));
    }
    return true;
}

bool cmdSetMacroSpell(void* scriptParam)
{
    PARAM_SET_MACRO_SPELL* param = (PARAM_SET_MACRO_SPELL*)scriptParam;
    TextAPI::setMACRO0(0x11, 0x70000000, param->magicID);
    return true;
}

bool cmd_set_macro_i_name(void* scriptParam)
{
    PARAM_SET_MACRO_I_NAME* param = (PARAM_SET_MACRO_I_NAME*)scriptParam;
    if (param->item == 0) {
        TextAPI::setMACRO0(0xa, 0x40000000, status::g_Menu.getItemIndex());
        status::g_Menu.setItemIndex(0);
    } else {
        TextAPI::setMACRO0(0xa, 0x40000000, param->item);
    }
    return true;
}

bool cmd_set_macro_x_times_can_cast()
{
    int stageNo = 0;
    int offset = 0;
    switch (g_Global.getNowAreaNo()) {
    case 0x0d:
        stageNo = 1;
        break;
    case 0x4b:
        stageNo = 2;
        break;
    case 0x4f:
        stageNo = 3;
        break;
    case 0x50:
        stageNo = 4;
        break;
    case 0x51:
        stageNo = 5;
        break;
    }
    dq5::level::SugorokuData::setup();
    int countMax = dq5::level::SugorokuData::getArraySize();
    for (int i = 0; i < countMax; i++) {
        if (stageNo == dq5::level::SugorokuData::getRecord(i)->index) {
            offset = i;
        }
    }
    TextAPI::setMACRO0(0x70, 0xf0000000, dq5::level::SugorokuData::getRecord(offset)->times);
    dq5::level::SugorokuData::cleanup();
    return true;
}

bool cmdSetBasicMenu(void* scriptParam)
{
    PARAM_SET_BASIC_MENU* param = (PARAM_SET_BASIC_MENU*)scriptParam;
    MaterielMenu_WINDOW_MANAGER::getSingleton()->openBasicMenu(param->menu);
    return true;
}

void MenuYesNo::initialize(char* scriptParam)
{
    PARAM_MENU_YES_NO* param = (PARAM_MENU_YES_NO*)scriptParam;
    gTownMenu_MESSAGE.setYesNo(param->position);
    type_ = param->type;
    index_ = param->index;
    position_ = param->position;
}

int MenuYesNo::isEnd()
{
    if (data_02101c88.isCurrentPart(4)) {
        if (twn::TownWindowSystem::getSingleton().isMessageStart() || twn::TownWindowSystem::getSingleton().isMessageOpen()) {
            return false;
        }
    } else if (fld::FieldWindowSystem::getSingleton()->isMessageOpen()) {
        return false;
    }
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        setFlag(true);
        return true;
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        setFlag(false);
        return true;
    }
    return false;
}

void MenuYesNo::setFlag(bool flag)
{
    switch (type_) {
    case 2:
        if (flag) {
            g_AreaFlag.set(index_);
        } else {
            g_AreaFlag.remove(index_);
        }
        break;
    case 1:
        if (flag) {
            g_LocalFlag.set(index_);
        } else {
            g_LocalFlag.remove(index_);
        }
        break;
    case 0:
        if (flag) {
            g_GlobalFlag.set(index_);
        } else {
            g_GlobalFlag.remove(index_);
        }
        break;
    }
}

MenuYesNo g_MenuYesNo;

void Menu_save::initialize(char* scriptParam)
{
    PARAM_MENU_SAVE* param = (PARAM_MENU_SAVE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    MaterielMenu_WINDOW_MANAGER::getSingleton()->setSaveMenuType(param->type);
    if (data_02101c88.isCurrentPart(4) == true) {
        window::gShopMenuControl.startMenu(0x11);
    } else {
        MaterielMenu_WINDOW_MANAGER::getSingleton()->openMaterielWindow(0x11);
    }
    cmn::g_cmnPartyInfo.setTalkCharaCtrlID(ctrl);
    type_ = param->type;
    if (param->type == 1) {
        status::g_Party.setNormalMode();
        int partyMax = status::g_Party.getCount();
        for (int i = 0; i < partyMax; i++) {
            bool itemMove = true;
            int playerID = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getPlayerIndex();
            for (int j = 0; j < 9; j++) {
                if (playerID == status::g_StageInfo.getLastParty(j)) {
                    itemMove = false;
                }
            }
            if (itemMove) {
                itemMoveToSack(i);
            }
            partyOut(i);
        }
        for (int i = 0; i < 9; i++) {
            int index = status::g_StageInfo.getLastParty(i);
            status::g_Party.add(index, true);
            if (index != 1) {
                if (status::PlayerDataAll::playerData_[index].getKindIndex() > 15) {
                    status::PlayerDataAll::setMonsterOldManFlag(index, false);
                } else {
                    status::PlayerDataAll::setRuidaFlag(index, false);
                }
            }
        }
        status::g_Story.setChapter(dq5::CHAPTER_SOUNENKI);
        status::ShopList::setSection(status::ShopList::SECTION_THIRD);
    }
}

void Menu_save::itemMoveToSack(int index)
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(index).getHaveStatusInfo();
    status::HaveItem& item = statusInfo.getHaveItem();
    int itemCount = item.getCount();
    int equipCount = 0;
    for (int i = 0; i < itemCount; i++) {
        if (item.isEquipment(i)) {
            equipCount++;
        }
    }
    for (int i = equipCount; i < itemCount; i++) {
        status::UseItem::give2(statusInfo, equipCount, status::g_Party.haveItemSack_, -1);
    }
}

void Menu_save::partyOut(int index)
{
    int playerID = status::g_Party.getPlayerStatus(index).getHaveStatusInfo().getPlayerIndex();
    if (status::g_Party.getPlayerStatus(index).getHaveStatusInfo().getHaveStatus().isFriendMonster()) {
        status::g_Party.del(0);
        status::PlayerDataAll::setMonsterOldManFlag(playerID, true);
    } else {
        status::g_Party.del(0);
        if (playerID != 1) {
            status::PlayerDataAll::setRuidaFlag(playerID, true);
        }
    }
}

int Menu_save::isEnd()
{
    if (data_02101c88.isCurrentPart(4) == true) {
        if (window::gShopMenuControl.isMenuEnd()) {
            return true;
        }
        return false;
    }
    if (MaterielMenu_WINDOW_MANAGER::getSingleton()->getCloseMaterielMenu()) {
        if (type_ == 0) {
            const char* defaultName = "zaout";
            status::g_StageAttribute.setMapName(defaultName);
        }
        return true;
    }
    return false;
}

Menu_save gMenu_save;

bool cmd_random_message(void* scriptParam)
{
    PARAM_RANDOM_MESSAGE* param = (PARAM_RANDOM_MESSAGE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    if (getObjectCount() > ctrl) {
        if (data_02101c88.isCurrentPart(4)) {
            cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
        }
    } else {
        cmn::g_talkSound.setVoice(0);
        ctrl = -1;
    }
    unsigned int message[7];
    message[0] = param->message1;
    message[1] = param->message2;
    message[2] = param->message3;
    message[3] = param->message4;
    message[4] = param->message5;
    message[5] = param->message6;
    message[6] = param->message7;
    int randomMessage = UnkDssRand::rand(param->count);
    cmn::g_talkSound.setMessageSound(param->count, ctrl);
    twn::TownWindowSystem::getSingleton().openCommonMessage();
    twn::TownWindowSystem::getSingleton().addCommonMessage(message[randomMessage]);
    cmn::PartyTalk::getSingleton().setPreMessageNo(message[randomMessage]);
    return true;
}

void MessageWithSound::initialize(char* scriptParam)
{
    PARAM_MESSAGE_WITH_SOUND* param = (PARAM_MESSAGE_WITH_SOUND*)scriptParam;
    preMusicNo_ = SoundManager::getBgmIndex();
    musicNo_ = param->soundNo;
    playTime_ = param->frame + 30;
    lastMessage_ = 0;
    flag_ = param->flag;
    wait_ = param->automes;
    soundCount_ = 0;
    stopSound_ = 0;
    playEnd_ = 0;
    int ctrl = getPlacementCtrlId();
    if (getObjectCount() > ctrl) {
        if (data_02101c88.isCurrentPart(4)) {
            cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
        }
    } else {
        ctrl = -1;
    }
    cmn::g_talkSound.setMessageSound(param->count, ctrl);
    gTownMenu_MESSAGE.openMessageForTALK();
    if (param->count == 1) {
        gTownMenu_MESSAGE.addMessageNOWAIT(param->message);
        cmn::PartyTalk::getSingleton().setPreMessageNo(param->message);
    } else if (param->count == 2) {
        lastMessage_ = param->message + 1;
        gTownMenu_MESSAGE.addMessageNOWAIT(param->message);
        cmn::PartyTalk::getSingleton().setPreMessageNo(lastMessage_);
    } else if (param->count >= 3) {
        lastMessage_ = param->message + param->count - 1;
        gTownMenu_MESSAGE.addMessageCount(param->message, param->count - 2);
        gTownMenu_MESSAGE.addMessageNOWAIT(param->message + param->count - 2);
        cmn::PartyTalk::getSingleton().setPreMessageNo(lastMessage_);
    }
    gTownMenu_MESSAGE.addMessageWAITKEY();
}

void MessageWithSound::execute()
{
    if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
        if (stopSound_ == 0 && lastMessage_ != 0) {
            stopSound_ = 1;
            gTownMenu_MESSAGE.close();
            gTownMenu_MESSAGE.clearMessageWAITPROG();
            return;
        }
        if (soundCount_ == -1) {
            gTownMenu_MESSAGE.clearMessageWAITPROG();
            if (wait_ == 0) {
                playEnd_ = 1;
            }
        } else if (soundCount_ == 30) {
            SoundManager::setInterrupt(1);
            SoundManager::play(musicNo_, 5);
            soundCount_++;
        } else if (soundCount_ <= playTime_) {
            soundCount_++;
        } else if (soundCount_ > playTime_) {
            if (flag_ == 0) {
                SoundManager::play(preMusicNo_, 5);
            }
            soundCount_ = -1;
        }
    } else if (stopSound_ == 1 && !gTownMenu_MESSAGE.isOpen()) {
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessageNOWAIT(lastMessage_);
        gTownMenu_MESSAGE.addMessageWAITKEY();
    }
}

int MessageWithSound::isEnd()
{
    if (wait_ == 1) {
        int stat = gTownMenu_MESSAGE.getStat();
        if (stat == menu::MenuBase::MENUBASE_STAT_OK || stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.setStat(menu::MenuBase::MENUBASE_STAT_OK);
            gTownMenu_MESSAGE.close();
            playEnd_ = 1;
            wait_ = 0;
        }
        return false;
    }
    if (playEnd_ == 1 && wait_ == 0) {
        gTownMenu_MESSAGE.setStat(menu::MenuBase::MENUBASE_STAT_OK);
        gTownMenu_MESSAGE.close();
        return true;
    }
    return false;
}

MessageWithSound g_MessageWithSound;

bool cmd_set_message_sound(void* scriptParam)
{
    PARAM_SET_MESSAGE_SOUND* param = (PARAM_SET_MESSAGE_SOUND*)scriptParam;
    int temp[7];
    temp[0] = param->voice1;
    temp[1] = param->voice2;
    temp[2] = param->voice3;
    temp[3] = param->voice4;
    temp[4] = param->voice5;
    temp[5] = param->voice6;
    temp[6] = param->voice7;
    for (int i = 0; i < param->count; i++) {
        int type;
        switch (temp[i]) {
        case 0:
            type = 0x30;
            break;
        case 1:
            type = 0x31;
            break;
        case 2:
            type = 0x32;
            break;
        case 3:
            type = 0x33;
            break;
        case 4:
            type = cmn::g_talkSound.getPlayerVoice();
            break;
        case 5:
            type = cmn::g_talkSound.getMostHeroicVoice();
            break;
        }
        cmn::g_talkSound.setOrderMessage(type);
    }
    return true;
}

void Message1SelfClosing::initialize(char* scriptParam)
{
    PARAM_MESSAGE1_SELF_CLOSING* param = (PARAM_MESSAGE1_SELF_CLOSING*)scriptParam;
    count_ = 0;
    frame_ = param->frame;
    cmn::g_talkSound.setMessageSound(1, -1);
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(param->message);
    cmn::PartyTalk::getSingleton().setPreMessageNo(param->message);
    cmn::GameManager::getSingleton().getPlayerManager()->setLock(true);
}

void Message1SelfClosing::execute()
{
    count_++;
}

int Message1SelfClosing::isEnd()
{
    if (count_ >= frame_) {
        gTownMenu_MESSAGE.setStat(menu::MenuBase::MENUBASE_STAT_OK);
        gTownMenu_MESSAGE.close();
        cmn::GameManager::getSingleton().getPlayerManager()->setLock(false);
        return true;
    }
    return false;
}

Message1SelfClosing gMessage1SelfClosing;

void ShakeMessage::initialize(char* scriptParam)
{
    PARAM_SHAKE_MESSAGE* param = (PARAM_SHAKE_MESSAGE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    if (getObjectCount() > ctrl) {
        if (data_02101c88.isCurrentPart(4)) {
            cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
        }
    } else {
        cmn::g_talkSound.setVoice(0);
        ctrl = -1;
    }
    cmn::g_talkSound.setMessageSound(1, ctrl);
    s_draw->shakeRequest_ = param->count;
    if (data_02101c88.isCurrentPart(6)) {
        fld::FieldWindowSystem::getSingleton()->openCommonMessage();
        fld::FieldWindowSystem::getSingleton()->addCommonMessage(param->message);
    } else {
        twn::TownWindowSystem::getSingleton().openCommonMessage();
        twn::TownWindowSystem::getSingleton().addCommonMessage(param->message);
    }
    cmn::PartyTalk::getSingleton().setPreMessageNo(param->message);
}

int ShakeMessage::isEnd()
{
    return true;
}

ShakeMessage gShakeMessage;

void DelayMessage::initialize(char* scriptParam)
{
    PARAM_DELAY_MESSAGE* param = (PARAM_DELAY_MESSAGE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    if (getObjectCount() > ctrl) {
        if (data_02101c88.isCurrentPart(4)) {
            cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
        }
    } else {
        cmn::g_talkSound.setVoice(0);
        ctrl = -1;
    }
    cmn::g_talkSound.setMessageSound(1, ctrl);
    s_draw->printDelayRequest_ = param->frame;
    if (data_02101c88.isCurrentPart(6)) {
        fld::FieldWindowSystem::getSingleton()->openCommonMessage();
        fld::FieldWindowSystem::getSingleton()->addCommonMessage(param->message);
    } else {
        twn::TownWindowSystem::getSingleton().openTalkMessage();
        twn::TownWindowSystem::getSingleton().addCommonMessage(param->message);
    }
    cmn::PartyTalk::getSingleton().setPreMessageNo(param->message);
}

int DelayMessage::isEnd()
{
    if (data_02101c88.isCurrentPart(6)) {
        if (!fld::FieldWindowSystem::getSingleton()->isMessageOpen()) {
            return true;
        }
    } else if (!twn::TownWindowSystem::getSingleton().isMessageStart() && !twn::TownWindowSystem::getSingleton().isMessageOpen()) {
        return true;
    }
    return false;
}

DelayMessage gDelayMessage;

void NarrationMessage::initialize(char* scriptParam)
{
    PARAM_NARRATION_MESSAGE* param = (PARAM_NARRATION_MESSAGE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    if (getObjectCount() > ctrl) {
        if (data_02101c88.isCurrentPart(4)) {
            cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
        }
    } else {
        cmn::g_talkSound.setVoice(0);
        ctrl = -1;
    }
    cmn::g_talkSound.setMessageSound(param->count, ctrl);
    gTownMenu_MESSAGE.openMessageForBATTLESHOP();
    gTownMenu_MESSAGE.addMessageCount(param->message, param->count);
    cmn::PartyTalk::getSingleton().setPreMessageNo(param->message + param->count - 1);
}

int NarrationMessage::isEnd()
{
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK || stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        gTownMenu_MESSAGE.setStat(menu::MenuBase::MENUBASE_STAT_OK);
        gTownMenu_MESSAGE.close();
        return true;
    }
    return false;
}

NarrationMessage g_NarrationMessage;

void NarrationMessage2::initialize(char* scriptParam)
{
    PARAM_NARRATION_MESSAGE2* param = (PARAM_NARRATION_MESSAGE2*)scriptParam;
    int ctrl = getPlacementCtrlId();
    if (getObjectCount() > ctrl) {
        if (data_02101c88.isCurrentPart(4)) {
            cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
        }
    } else {
        cmn::g_talkSound.setVoice(0);
        ctrl = -1;
    }
    unsigned int mess[8];
    mess[0] = param->message0;
    mess[1] = param->message1;
    mess[2] = param->message2;
    mess[3] = param->message3;
    mess[4] = param->message4;
    mess[5] = param->message5;
    mess[6] = param->message6;
    mess[7] = param->message7;
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (mess[i] == 0) {
            break;
        }
        count++;
    }
    cmn::g_talkSound.setMessageSound(count, ctrl);
    gTownMenu_MESSAGE.openMessageForBATTLESHOP();
    for (int i = 0; i < count; i++) {
        gTownMenu_MESSAGE.addMessage(mess[i]);
    }
    cmn::PartyTalk::getSingleton().setPreMessageNo(mess[count]);
}

int NarrationMessage2::isEnd()
{
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK || stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        gTownMenu_MESSAGE.setStat(menu::MenuBase::MENUBASE_STAT_OK);
        gTownMenu_MESSAGE.close();
        return true;
    }
    return false;
}

NarrationMessage2 g_NarrationMessage2;

void ScriptMessageCommand_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
