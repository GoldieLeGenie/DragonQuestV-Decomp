#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_CHANGE_NAME.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_CHECK_NAME.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ROOT.hpp"
#include "ov032/leveldata/JisanMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline dq5::level::JisanMessage* dq5::level::JisanMessage::getRecord(int index)
{
    return (JisanMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::JisanMessage::getMessage1()
{
    return message1;
}

inline void MaterielMenu_JISAN_ROOT::setActiveMenu(char select)
{
    active_ = select;
}

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

inline void status::PlayerData::setCursedName(int val)
{
    cursedName_ = val;
}

inline void status::HaveItemSack::setCursedName(int flag)
{
    cursedName_ = flag;
}

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

inline void menu::MenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

inline void menu::MaterielMenuPlayerControl::setActiveItemPage(int active)
{
    activeItemPage_ = active;
}

THUMB void MaterielMenu_JISAN_CHANGE_NAME::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    status::g_Menu.drawFlag_ = 1;
    for (int i = 0; i < 0x51; i++) {
        unk_90[i] = 0;
    }
    unk_90[0] = -1;
    short count = 1;
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (short i = 0; i < partyCount; i++) {
        int index = MenuStatusInfo::getPlayerData(i).getKindIndex();
        if (index != 0x10 && index != 0x11 && index != 0x3b && index != 0x3a && index != 0x52) {
            unk_90[count] = i;
            count++;
        }
    }
    unk_1c = count;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    navigator_.setupBase();
    navigator_.setup(6, 2, unk_1c);
    navigator_.setPageNo(menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_);
    menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(unk_90[navigator_.getIndex(menuItem_.active_)]);
    cmn::g_cmnSoundManager.initialize();
    mode_ = MODE_SELECT;
}

THUMB void MaterielMenu_JISAN_CHANGE_NAME::menuExecute()
{
    int count = unk_1c - navigator_.getPageNo() * 12;
    menu::MenuTemplate_materiel::surechigaiSelectObject(&menuItem_, menuItem_.active_, dss::clamp<int>(1, count, 12));
}

THUMB void MaterielMenu_JISAN_CHANGE_NAME::menuDraw()
{
    if (mode_ == MODE_CANCEL || mode_ == MODE_END) {
        return;
    }
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    if (cmn::g_cmnSoundManager.isPlaySound() == 1) {
        int active = menuItem_.active_;
        drawCommandCursor(active % 6 * 40 + 12, active / 6 * 40 + 60);
    }
    else if (open == 0) {
        menuItem_.drawActive();
    }
    int page = navigator_.getPageNo();
    int pageMax = navigator_.getPageMaxCount() - 1;
    drawChangeNameScreen(open, page, pageMax, 4, unk_90, unk_1c);
}

THUMB void MaterielMenu_JISAN_CHANGE_NAME::menuUpdate()
{
    if (cmn::g_cmnSoundManager.isPlaySound() == 1) {
        cmn::g_cmnSoundManager.execSound();
        return;
    }
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            selectYes();
            return;
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            selectNo();
            return;
        }
        return;
    }
    if (mode_ == MODE_CURSE) {
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessage(getMessageNo(0x2d), getMessageNo(0x2e), getMessageNo(0x2f));
        gTownMenu_MESSAGE.setYesNo();
        return;
    }
    navigator_.setup(6, 2, unk_1c);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        int active = navigator_.getIndex(menuItem_.active_);
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(unk_90[active]);
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(menuItem_.active_);
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(navigator_.getPageNo());
        if (result == 3) {
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x47));
            mode_ = MODE_CANCEL;
        }
        if (result == 2) {
            if (active == 0) {
                if (MenuStatusInfo::getHaveItemSack().cursedName_ == 1) {
                    mode_ = MODE_CURSE;
                    cmn::g_cmnSoundManager.setPlaySound(1, false);
                }
                else {
                    gTownMenu_MESSAGE.openMessageForTALK();
                    gTownMenu_MESSAGE.addMessage(getMessageNo(0x35), getMessageNo(0x36), getMessageNo(0x37));
                    mode_ = MODE_NEXT;
                }
            }
            else if (MenuStatusInfo::getPlayerData(unk_90[active]).cursedName_ == 1) {
                mode_ = MODE_CURSE;
                cmn::g_cmnSoundManager.setPlaySound(1, false);
            }
            else {
                TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(unk_90[active]));
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x34));
                mode_ = MODE_NEXT;
            }
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_JISAN_CHANGE_NAME::selectYes()
{
    switch (mode_) {
        case MODE_SELECT:
            break;
        case MODE_NEXT:
            close();
            gMaterielMenu_JISAN_CHECK_NAME.open();
            break;
        case MODE_CURSE: {
            gTownMenu_MESSAGE.openMessageForTALK();
            if (MenuStatusInfo::getGold() < 5000) {
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x30), getMessageNo(0x46));
                gTownMenu_MESSAGE.setYesNo();
                mode_ = MODE_END;
                return;
            }
            int active = navigator_.getIndex(menuItem_.active_);
            MenuStatusInfo::setGold(MenuStatusInfo::getGold() - 5000);
            int ctrl = cmn::g_cmnPartyInfo.ctrlID_;
            cmn::g_talkSound.setOrderMessage(0x30);
            cmn::g_talkSound.setOrderMessage(cmn::g_talkSound.getCharacterVoice(ctrl));
            cmn::g_talkSound.setMessageSound(2, -1);
            if (active == 0) {
                TextAPI::setMACRO0(0x12, 0x50000000, 0x24e);
                MenuStatusInfo::getHaveItemSack().setCursedName(0);
            }
            else {
                TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(unk_90[active]));
                MenuStatusInfo::getPlayerData(unk_90[active]).setCursedName(0);
            }
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x31), getMessageNo(0x32));
            mode_ = MODE_NEXT;
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(cmn::g_cmnPartyInfo.ctrlID_));
            break;
        }
        case MODE_CURSE_NEXT:
            break;
        case MODE_CANCEL:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0x48));
            gTownMenu_MESSAGE.addMessageWAITKEY();
            close();
            gMaterielMenu_JISAN_ROOT.setActiveMenu(4);
            gMaterielMenu_JISAN_ROOT.open();
            break;
        case MODE_END:
            mode_ = MODE_SELECT;
            break;
    }
}

THUMB void MaterielMenu_JISAN_CHANGE_NAME::selectNo()
{
    switch (mode_) {
        case MODE_SELECT:
        case MODE_NEXT:
            break;
        case MODE_CURSE:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x33), getMessageNo(0x46));
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_SELECT;
            break;
        case MODE_CURSE_NEXT:
        case MODE_CANCEL:
            break;
        case MODE_END:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0x48));
            gTownMenu_MESSAGE.addMessageWAITKEY();
            close();
            gMaterielMenu_JISAN_ROOT.setActiveMenu(4);
            gMaterielMenu_JISAN_ROOT.open();
            break;
    }
}

THUMB int MaterielMenu_JISAN_CHANGE_NAME::getMessageNo(int index)
{
    return dq5::level::JisanMessage::getRecord(index)->getMessage1();
}
