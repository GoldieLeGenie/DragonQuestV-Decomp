#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

// The original TU also emitted ScriptCommand's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "ov001/script/ScriptMessageCommandTown.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/window/ShopMenuControl.hpp"
#include "main/script/CommandParam.hpp"

#pragma thumb on

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
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

inline void MaterielMenu_WINDOW_MANAGER::setExtraInnType(int type)
{
    extraInnType_ = type;
}

inline void MaterielMenu_WINDOW_MANAGER::setNameType(int type)
{
    nameType_ = type;
}

inline void MaterielMenu_WINDOW_MANAGER::setOpenMenuForScript(bool flag)
{
    editMessageForScript_ = flag;
}

inline void cmn::CommonPartyInfo::setTalkCharaCtrlID(int ctrl)
{
    ctrlID_ = ctrl;
}

inline int status::MenuStatus::getEventInnStart()
{
    return eventInnStart_;
}

inline void status::MenuStatus::setAddMonsterIndex(char index)
{
    addMonsterIndex_ = index;
}

inline void status::StageInfo::setChapterLoadFlag(bool flag)
{
    chapterLoad_ = flag;
}

inline void ScriptCommandWeakVtable::initialize(char* scriptParam)
{
}

inline int ScriptCommandWeakVtable::isEnd()
{
    return 0;
}

inline void CmdSpeakToPlayer::execute()
{
}

inline void CmdSpeakToPlayer2::execute()
{
}

inline void CmdSpeakToPlayerWaitClosing::execute()
{
}

inline void CmdSpeakToPlayer2WaitClosing::execute()
{
}

inline void MenuShop::execute()
{
}

inline void MenuShop::terminate()
{
}

inline void EventInn::execute()
{
}

inline void EventInn::terminate()
{
}

inline void NameSetMenu::execute()
{
}

inline void NameSetMenu::terminate()
{
}

inline void FriendMonsterAzuke::execute()
{
}

inline void FriendMonsterAzuke::terminate()
{
}

bool cmdIsSpeaked(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    int index = getPlacementIndex(ctrl);
    int charaNo = TownCharacterManager::getSingleton()->getCharaIndex(ctrl);
    if (TownCharacterManager::getSingleton()->isTalked(ctrl)) {
        cmn::g_talkSound.setVoice(charaNo);
        cmn::PartyTalk::getSingleton().resetPartyTalk();
        return true;
    }
    return false;
}

void Speak_to_player_self_closing::initialize(char* scriptParam)
{
    PARAM_SPEAK_TO_PLAYER_SELF_CLOSING* param = (PARAM_SPEAK_TO_PLAYER_SELF_CLOSING*)scriptParam;
    count_ = 0;
    frame_ = param->frame;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setPlayerDirection(ctrl);
    if (getObjectCount() > ctrl) {
        if (data_02101c88.unkfunc_02051818(4)) {
            cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
        }
    } else {
        cmn::g_talkSound.setVoice(0);
        ctrl = -1;
    }
    cmn::g_talkSound.setMessageSound(1, ctrl);
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(param->message);
    cmn::PartyTalk::getSingleton().setPreMessageNo(param->message);
    cmn::GameManager::getSingleton().getPlayerManager()->setLock(true);
}

void Speak_to_player_self_closing::execute()
{
    count_++;
}

int Speak_to_player_self_closing::isEnd()
{
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK || stat == menu::MenuBase::MENUBASE_STAT_CANCEL || count_ >= frame_) {
        gTownMenu_MESSAGE.setStat(menu::MenuBase::MENUBASE_STAT_OK);
        gTownMenu_MESSAGE.close();
        cmn::GameManager::getSingleton().getPlayerManager()->setLock(false);
        return true;
    }
    return false;
}

Speak_to_player_self_closing gSpeak_to_player_self_closing;

void CmdSpeakToPlayer::initialize(char* scriptParam)
{
    PARAM_SPEAK_TO_PLAYER* param = (PARAM_SPEAK_TO_PLAYER*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setPlayerDirection(ctrl);
    cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
    cmn::g_talkSound.setMessageSound(param->count, ctrl);
    if (twn::TownWindowSystem::getSingleton().isMessageStart()) {
        for (int i = 0; i < param->count; i++) {
            twn::TownWindowSystem::getSingleton().addCommonMessage(param->message + i);
        }
    } else {
        twn::TownWindowSystem::getSingleton().openMessage(param->message, param->count);
    }
    cmn::PartyTalk::getSingleton().setPreMessageNo(param->message + param->count - 1);
}

int CmdSpeakToPlayer::isEnd()
{
    return true;
}

CmdSpeakToPlayer gCmdSpeakToPlayer;

void CmdSpeakToPlayer2::initialize(char* scriptParam)
{
    PARAM_SPEAK_TO_PLAYER2* param = (PARAM_SPEAK_TO_PLAYER2*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setPlayerDirection(ctrl);
    cmn::g_talkSound.setVoice(TownCharacterManager::getSingleton()->getCharaIndex(ctrl));
    unsigned int tmess[8];
    tmess[0] = param->message0;
    tmess[1] = param->message1;
    tmess[2] = param->message2;
    tmess[3] = param->message3;
    tmess[4] = param->message4;
    tmess[5] = param->message5;
    tmess[6] = param->message6;
    tmess[7] = param->message7;
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (tmess[i] == 0) {
            break;
        }
        count++;
    }
    cmn::g_talkSound.setMessageSound(count, ctrl);
    if (param->message0 != 0) {
        if (!twn::TownWindowSystem::getSingleton().isMessageStart()) {
            twn::TownWindowSystem::getSingleton().openCommonMessage();
        }
        twn::TownWindowSystem::getSingleton().addCommonMessage(param->message0);
    }
    for (int i = 1; i < 8; i++) {
        if (tmess[i] != 0) {
            twn::TownWindowSystem::getSingleton().addCommonMessage(tmess[i]);
        }
    }
    cmn::PartyTalk::getSingleton().setPreMessageNo(tmess[count - 1]);
}

int CmdSpeakToPlayer2::isEnd()
{
    return true;
}

CmdSpeakToPlayer2 gCmdSpeakToPlayer2;

bool cmd_not_use_load_message()
{
    status::g_StageInfo.setChapterLoadFlag(true);
    return true;
}

void CmdSpeakToPlayerWaitClosing::initialize(char* scriptParam)
{
    gCmdSpeakToPlayer.initialize(scriptParam);
}

int CmdSpeakToPlayerWaitClosing::isEnd()
{
    if (!twn::TownWindowSystem::getSingleton().isMessageStart() && !twn::TownWindowSystem::getSingleton().isMessageOpen()) {
        return true;
    }
    return false;
}

CmdSpeakToPlayerWaitClosing gCmdSpeakToPlayerWaitClosing;

void CmdSpeakToPlayer2WaitClosing::initialize(char* scriptParam)
{
    gCmdSpeakToPlayer2.initialize(scriptParam);
}

int CmdSpeakToPlayer2WaitClosing::isEnd()
{
    if (!twn::TownWindowSystem::getSingleton().isMessageStart() && !twn::TownWindowSystem::getSingleton().isMessageOpen()) {
        return true;
    }
    return false;
}

CmdSpeakToPlayer2WaitClosing gCmdSpeakToPlayer2WaitClosing;

void MenuShop::initialize(char* scriptParam)
{
    PARAM_MENU_SHOP* param = (PARAM_MENU_SHOP*)scriptParam;
    type_ = param->shop - 1;
    int ctrl = -1;
    if (data_02101c88.unkfunc_02051818(4)) {
        ctrl = getPlacementCtrlId();
        TownCharacterManager::getSingleton()->setPlayerDirection(ctrl);
    }
    window::gShopMenuControl.startMenu(type_);
    MaterielMenu_WINDOW_MANAGER::getSingleton()->setExtraInnType(0);
    cmn::g_cmnPartyInfo.setTalkCharaCtrlID(ctrl);
}

int MenuShop::isEnd()
{
    if (window::gShopMenuControl.isMenuEnd()) {
        return true;
    }
    return false;
}

MenuShop g_MenuShop;

void EventInn::initialize(char* scriptParam)
{
    PARAM_EVENT_INN* param = (PARAM_EVENT_INN*)scriptParam;
    int ctrl = getPlacementCtrlId();
    type_ = param->type;
    index_ = param->index;
    TownCharacterManager::getSingleton()->setPlayerDirection(ctrl);
    window::gShopMenuControl.startMenu(0x1e);
    MaterielMenu_WINDOW_MANAGER::getSingleton()->setExtraInnType(1);
    cmn::g_cmnPartyInfo.setTalkCharaCtrlID(ctrl);
}

int EventInn::isEnd()
{
    if (window::gShopMenuControl.isMenuEnd()) {
        int flag = status::g_Menu.getEventInnStart();
        switch (type_) {
        case 0:
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
        case 2:
            if (flag) {
                g_GlobalFlag.set(index_);
            } else {
                g_GlobalFlag.remove(index_);
            }
            break;
        }
        return true;
    }
    return false;
}

EventInn gEventInn;

void NameSetMenu::initialize(char* scriptParam)
{
    PARAM_SET_SON_DAUGHTER_NAME* param = (PARAM_SET_SON_DAUGHTER_NAME*)scriptParam;
    int nameType;
    if (param->type == 0) {
        nameType = 1;
    } else {
        nameType = 2;
    }
    MaterielMenu_WINDOW_MANAGER::getSingleton()->setNameType(nameType);
    window::gShopMenuControl.startMenu(0x23);
    cmn::g_cmnPartyInfo.setTalkCharaCtrlID(getPlacementCtrlId());
}

int NameSetMenu::isEnd()
{
    if (window::gShopMenuControl.isMenuEnd()) {
        return true;
    }
    return false;
}

NameSetMenu g_NameSetMenu;

void FriendMonsterAzuke::initialize(char* scriptParam)
{
    PARAM_FRIEND_MONSTER_AZUKE* param = (PARAM_FRIEND_MONSTER_AZUKE*)scriptParam;
    status::g_Menu.setAddMonsterIndex(param->index);
    MaterielMenu_WINDOW_MANAGER::getSingleton()->setOpenMenuForScript(true);
    window::gShopMenuControl.startMenu(0x2b);
}

int FriendMonsterAzuke::isEnd()
{
    if (window::gShopMenuControl.isMenuEnd()) {
        return true;
    }
    return false;
}

FriendMonsterAzuke g_FriendMonsterAzuke;

void ScriptMessageCommandTown_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
