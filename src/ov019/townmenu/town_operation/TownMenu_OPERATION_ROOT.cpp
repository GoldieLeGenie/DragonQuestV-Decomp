#pragma ipa file
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_ROOT.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_EQUIP.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_SETTING.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_SHIFT_PARTY.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_SORTITEM.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_TACTICS.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/global/Global.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/menu/MessageWindow.hpp"
#include "main/profile/SaveLoad.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline status::UseActionMessage::UseActionMessage()
{
    clear();
}

inline status::UseActionParam::UseActionParam()
{
    clear();
}

inline status::UseActionParam::~UseActionParam()
{
}

inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus()
{
    return actorCharacterStatus_;
}

inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index)
{
    return targetCharacterStatus_[index];
}

inline int status::UseActionParam::getActionIndex()
{
    return actionIndex_;
}

inline status::UseActionMessage& status::UseActionParam::getUseActionMessage(int index)
{
    return message_[index];
}

inline int status::UseActionParam::getTargetCount()
{
    return targetCount_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline int status::UseActionMessage::getExecMessage(int index)
{
    return execMessage_[index];
}

inline int status::UseActionMessage::getResultMessage(int index)
{
    return resultMessage_[index];
}

inline void menu::MenuItem::resetResult()
{
    result_ = 0;
    lastresult_ = 0;
}

inline void menu::MenuItem::setCursor(CURSORTYPE cursor)
{
    ctype_ = cursor;
}

inline unsigned char TownMenuPlayerControl::getActiveTactics()
{
    return activeTactics_;
}

inline void TownMenuPlayerControl::setActiveTactics(unsigned char tactics)
{
    activeTactics_ = tactics;
}

inline void TownMenu_OPERATION_SORTITEM::setSortMode(SORT_MODE mode)
{
    m_mode = mode;
}

THUMB void TownMenu_OPERATION_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    mode_ = MODE_SORT_NONE;
    abortMode_ = 0;
    saveResult_ = 0;
    isMantan_ = 0;
    unk_1e = 0;
    seCount_ = 0;
    navigator_.setupBase();
    menuItem_.active_ = TownMenuPlayerControl::getSingleton()->getActiveTactics();
}

THUMB void TownMenu_OPERATION_ROOT::menuExecute()
{
    if (!gTownMenu_MESSAGE.isOpen()) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_02171338(&menuItem_, menuItem_.active_, OP_EOF);
    }
}

THUMB void TownMenu_OPERATION_ROOT::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    unkfunc_021735ec(open);
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenu_OPERATION_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (seCount_ > 30) {
        SoundManager::playSe(0x1f5, 0);
        seCount_ = 0;
        if (actionIndex_ != 0x7d) {
            isMantan_ = 0;
        }
    }
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (s_draw->isFinish()) {
            isMantan_ = 0;
            if (mode_ == MODE_ALL_RECOVERY) {
                status::UseActionParam useActionParam;
                useActionParam.clear();
                if (MenuStatusInfo::isCheckPosonPlayer() == true && MenuStatusInfo::isPoisonPlayer(useActionParam) == true) {
                    gTownMenu_MESSAGE.restartMessage();
                    allRecoveryMessage(useActionParam);
                    isMantan_ = 1;
                    seCount_ = 0;
                    redraw_ = 1;
                    return;
                }
                if (MenuStatusInfo::isCheckRecoveryPlayer() == true) {
                    if (MenuStatusInfo::isRecoveryPlayer(useActionParam) == true) {
                        gTownMenu_MESSAGE.restartMessage();
                        allRecoveryMessage(useActionParam);
                        redraw_ = 1;
                    } else {
                        mode_ = MODE_SORT_NONE;
                    }
                    isMantan_ = 1;
                    seCount_ = 0;
                } else {
                    mode_ = MODE_SORT_NONE;
                }
                MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
                return;
            }
        }
        if (isMantan_ == 1) {
            seCount_++;
        }
        if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
            if (abortMode_ == 2) {
                saveResult_ = profile::SaveLoad::savebank(3, profile::SAVETYPE_RESUME);
                data_0211b27c.state_ = FadeEffector::FADE_NONE;
                data_0211b27c.count_ = 0;
                data_0211b27c.frames_ = 60;
                data_0211b27c.sprite_[0].setColor(0, 0, 0);
                data_0211b27c.sprite_[1].setColor(0, 0, 0);
                data_02101d14.addPart(&data_0211b27c);
                SoundManager::stopBgm(60);
                abortMode_ = 3;
            }
            unkfunc_02175c8c();
            return;
        }
        if (stat == MENUBASE_STAT_OK) {
            if (mode_ == OP_ABORT) {
                unkfunc_02175c8c();
                return;
            }
            gTownMenu_MESSAGE.close();
            return;
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            mode_ = MODE_SORT_NONE;
            menuItem_.setCursor(menu::MenuItem::CURSORTYPE_ACTIVE);
            menuItem_.drawActive();
            redraw_ = 1;
        }
        return;
    }
    navigator_.setup(2, 4, OP_EOF);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        if (result == 2) {
            if (menuItem_.active_ != OP_SETTING && menuItem_.active_ != OP_ABORT && g_AreaFlag.check(0x82) && !g_AreaFlag.check(0x84)) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xc42a8);
                return;
            }
            TownMenuPlayerControl::getSingleton()->setActiveTactics(menuItem_.active_);
            switch (menuItem_.active_) {
                case OP_MANTAN:
                    hpMax();
                    break;
                case OP_EQUIP:
                    close();
                    TownMenuPlayerControl::getSingleton()->activeChara_ = 0;
                    gTownMenu_OPERATION_EQUIP.open();
                    break;
                case OP_ARRAY:
                    boxUpArray();
                    break;
                case OP_TACTICS: {
                    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
                    int count = 0;
                    for (int i = 0; i < partyCount; i++) {
                        if (!MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_BATTLE_NPC) && !MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_NORMAL_NPC)) {
                            count++;
                        }
                    }
                    if (count == 1) {
                        gTownMenu_MESSAGE.openMessageForMENU();
                        gTownMenu_MESSAGE.addMessage(0xc4238);
                    } else {
                        close();
                        gTownMenu_OPERATION_TACTICS.open();
                    }
                    break;
                }
                case OP_SORTITEM:
                    close();
                    gTownMenu_OPERATION_SORTITEM.setSortMode(TownMenu_OPERATION_SORTITEM::SORT_ITEM);
                    gTownMenu_OPERATION_SORTITEM.open();
                    break;
                case OP_SORTFUKURO:
                    close();
                    gTownMenu_OPERATION_SORTITEM.setSortMode(TownMenu_OPERATION_SORTITEM::SORT_SACK);
                    gTownMenu_OPERATION_SORTITEM.open();
                    break;
                case OP_SETTING:
                    close();
                    gTownMenu_OPERATION_SETTING.open();
                    break;
                case OP_ABORT:
                    mode_ = OP_ABORT;
                    gTownMenu_MESSAGE.openMessageForMENU();
                    if (!cmn::g_cmnPartyInfo.isAbortSaveDungeon()) {
                        gTownMenu_MESSAGE.addMessage(0xcba13, 0xcba14);
                    } else if (!cmn::g_cmnPartyInfo.isAbortSaveTown()) {
                        gTownMenu_MESSAGE.addMessage(0xcba16, 0xcba17, 0xcba18);
                    } else {
                        gTownMenu_MESSAGE.addMessage(0xcba03);
                        gTownMenu_MESSAGE.setYesNo();
                        gTownMenu_MESSAGE.setYesNoSuperCancel(false);
                        abortMode_ = 2;
                    }
                    break;
            }
        }
        if (result == 3) {
            close();
            gTownMenu_ROOT.open();
            gTownMenu_ROOT.menuItem_.active_ = TownMenu_ROOT::ROOT_OPERATION;
        }
        redraw_ = 1;
    }
}

THUMB void TownMenu_OPERATION_ROOT::hpMax()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    bool noRecovery = true;
    status::UseActionParam useActionParam;
    useActionParam.clear();
    gTownMenu_MESSAGE.openMessageForMENU();
    if (MenuStatusInfo::isCheckPosonPlayer()) {
        if (MenuStatusInfo::isPoisonPlayer(useActionParam)) {
            allRecoveryMessage(useActionParam);
            noRecovery = false;
        }
        mode_ = MODE_ALL_RECOVERY;
        isMantan_ = 1;
    }
    if (MenuStatusInfo::isCheckRecoveryPlayer() && noRecovery) {
        if (MenuStatusInfo::isRecoveryPlayer(useActionParam)) {
            allRecoveryMessage(useActionParam);
            noRecovery = false;
        }
        mode_ = MODE_ALL_RECOVERY;
        isMantan_ = 1;
    }
    if (noRecovery) {
        isMantan_ = 0;
        gTownMenu_MESSAGE.addMessage(0xc424c);
    }
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
}

THUMB void TownMenu_OPERATION_ROOT::boxUpArray()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) == 1) {
        menuItem_.resetResult();
        gTownMenu_MESSAGE.openMessageForMENU();
        gTownMenu_MESSAGE.addMessage(0xc423a);
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    } else {
        close();
        gTownMenu_OPERATION_SHIFT_PARTY.open();
    }
}

THUMB void TownMenu_OPERATION_ROOT::allRecoveryMessage(status::UseActionParam& useActionParam)
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int message[4] = {0};
    for (int i = 0; i < 4; i++) {
        message[i] = 0;
    }
    int messageCount;
    status::UseActionMessage& useActionMessage = useActionParam.getUseActionMessage(0);
    status::CharacterStatus* actorStatus = useActionParam.getActorCharacterStatus();
    {
        int targetCount = useActionParam.getTargetCount();
        TextAPI::setMACRO0(1, 0x50000000, actorStatus->getHaveStatusInfo().getPlayerIndex());
        TextAPI::setMACRO0(0x11, 0x70000000, MenuStatusInfo::getWordDBIndex(useActionParam.getActionIndex()));
        messageCount = 0;
        message[messageCount] = useActionMessage.getExecMessage(messageCount);
        while (message[messageCount] != 0) {
            gTownMenu_MESSAGE.addMessageNOWAIT(message[messageCount]);
            messageCount++;
            message[messageCount] = useActionMessage.getExecMessage(messageCount);
            SoundManager::playSe(0x132, 0);
        }
        for (int i = 0; i < targetCount; i++) {
            status::CharacterStatus* targetStatus = useActionParam.getTargetCharacterStatus(i);
            TextAPI::setMACRO0(0x12, 0x50000000, targetStatus->getHaveStatusInfo().getPlayerIndex());
            messageCount = 0;
            message[messageCount] = useActionMessage.getResultMessage(messageCount);
            while (message[messageCount] != 0) {
                if (!MenuStatusInfo::isCheckRecoveryPlayer()) {
                    if (i != targetCount) {
                        gTownMenu_MESSAGE.addMessageNOWAIT(message[messageCount]);
                    } else {
                        gTownMenu_MESSAGE.addMessage(message[messageCount]);
                    }
                } else {
                    gTownMenu_MESSAGE.addMessageNOWAIT(message[messageCount]);
                }
                messageCount++;
                message[messageCount] = useActionMessage.getResultMessage(messageCount);
            }
        }
    }
    actionIndex_ = useActionParam.getActionIndex();
}

THUMB void TownMenu_OPERATION_ROOT::unkfunc_02175c8c()
{
    switch (abortMode_) {
        case 0:
            gTownMenu_MESSAGE.close();
            break;
        case 1:
            break;
        case 2:
            gTownMenu_MESSAGE.close();
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessageNOWAIT(0xcba06);
            gTownMenu_MESSAGE.addMessageWAITKEY();
            break;
        case 3:
            gTownMenu_MESSAGE.close();
            gTownMenu_MESSAGE.openMessageForMENU();
            if (saveResult_ == 0) {
                gTownMenu_MESSAGE.addMessage(0xcba0d);
                abortMode_ = 1;
            } else {
                gTownMenu_MESSAGE.addMessage(0xcba09, 0xcba0a);
                abortMode_ = 1;
            }
            break;
    }
}
