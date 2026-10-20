#include "ov026/materielmenu/church/MaterielMenu_CHURCH_ROOT.hpp"
#include "ov026/materielmenu/church/MaterielMenu_CHURCH_MIRACLE.hpp"
#include "ov026/materielmenu/church/MaterielMenu_CHURCH_OMEN.hpp"
#include "ov026/materielmenu/common/MaterielMenu_SAVE.hpp"
#include "ov019/leveldata/ChurchMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/MapChurch.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"

int MaterielMenu_CHURCH_ROOT::sexType_ = 1;
int MaterielMenu_CHURCH_ROOT::voiceType_;

inline int status::MenuStatus::getBooking()
{
    return bookingFlag_;
}

inline void status::MenuStatus::clearBooking()
{
    bookingFlag_ = 0;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline unsigned short dq5::level::MapChurch::getFloor()
{
    return floor;
}

inline char dq5::level::MapChurch::getChurchman()
{
    return byte_1 & 1;
}

inline char dq5::level::MapChurch::getMapTime()
{
    return (byte_1 & 0x1c) >> 2;
}

inline char dq5::level::MapChurch::getChapter()
{
    return (byte_1 & 0xe0) >> 5;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline unsigned int dq5::level::MapChurch::getArraySize()
{
    return binary_.getRecordCount();
}

inline dq5::level::MapChurch* dq5::level::MapChurch::getRecord(int index)
{
    return (MapChurch*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::ChurchMessage::getMessage1()
{
    return message1;
}

inline unsigned long dq5::level::ChurchMessage::getMessage2()
{
    return message2;
}

inline dq5::level::ChurchMessage* dq5::level::ChurchMessage::getRecord(int index)
{
    return (ChurchMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline bool MaterielMenu_CHURCH_ROOT::getSexType()
{
    return sexType_ == 1;
}

THUMB void MaterielMenu_CHURCH_ROOT::menuSetup()
{
    status::g_Party.setBattleMode();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menu::MaterielMenuPlayerControl::getSingleton()->initialize();
    activeCommand_ = -1;
    firstFlag_ = 1;
    m_bOpen = 1;
    churchType_ = status::g_Shop.getChurchType(false);
    navigator_.setupBase();
    menuItem_.active_ = 0;
    setupSexType();
    timeType_ = status::g_StageInfo.getTimeZone();
    if (status::g_Menu.getBooking() == menu::BOOKING_RETURN) {
        activeCommand_ = 7;
    }
}

THUMB void MaterielMenu_CHURCH_ROOT::setupSexType()
{
    int sex = 0;
    voiceType_ = 0;
    dq5::level::MapChurch::setup();
    for (int i = 0; i < dq5::level::MapChurch::getArraySize(); i++) {
        if (dq5::level::MapChurch::getRecord(i)->getFloor() == g_Global.getMapNameId()) {
            int chapter = dq5::level::MapChurch::getRecord(i)->getChapter();
            if (chapter == 0 || chapter == status::g_Story.getChapter()) {
                int time = dq5::level::MapChurch::getRecord(i)->getMapTime();
                if (time != 0) {
                    if (time == 4) {
                        time = dq5::DAY_NIGHT_NIGHT;
                    } else {
                        time = dq5::DAY_NIGHT_DAY;
                    }
                }
                if (time == 0 || time == status::g_StageInfo.getDayNight()) {
                    sex = dq5::level::MapChurch::getRecord(i)->getChurchman();
                    break;
                }
            }
        }
    }
    dq5::level::MapChurch::cleanup();
    sexType_ = sex == 0 ? 1 : 0;
    if (g_Global.getMapNameId() == 0x27c) {
        voiceType_ = 1;
    }
    setTalkSound();
}

THUMB void MaterielMenu_CHURCH_ROOT::menuExecute()
{
    commandNum_ = churchType_ == status::ShopList::Exist ? 6 : 5;
    int commandNum = commandNum_;
    menu::MaterielMenuPlayerControl::getSingleton()->churchCommandNum_ = commandNum;
    menu::MenuTemplate_materiel::MATERIEL_CHURCH_ROOT(&menuItem_, commandNum_, menuItem_.active_);
}

THUMB void MaterielMenu_CHURCH_ROOT::menuDraw()
{
    if (activeCommand_ != 7) {
        drawChurchScreen(activeCommand_, firstFlag_);
        if (activeCommand_ == -1 && firstFlag_ == 0 && gTownMenu_MESSAGE.isMessageWAITPROG()) {
            menuItem_.drawActive();
        }
    }
}

THUMB void MaterielMenu_CHURCH_ROOT::menuUpdate()
{
    if (firstFlag_) {
        firstFlag_ = 0;
        firstMessage();
    }
    if (rootUpdate() == false) {
        commandUpdate();
    }
}

THUMB bool MaterielMenu_CHURCH_ROOT::rootUpdate()
{
    int stat = gTownMenu_MESSAGE.stat_;
    switch (activeCommand_) {
        case -1:
            if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                redraw_ = 1;
                return true;
            }
            break;
        case 7:
            return true;
        case 6:
            if (stat == MENUBASE_STAT_OK) {
                gTownMenu_MESSAGE.close();
                activeCommand_ = -1;
                redraw_ = 1;
            } else if (stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                selectEnd();
            }
            break;
        case 5:
            if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                activeCommand_ = -1;
                status::g_Menu.clearBooking();
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            }
            break;
    }
    return false;
}

THUMB bool MaterielMenu_CHURCH_ROOT::commandUpdate()
{
    if (gTownMenu_MESSAGE.isOpen() && gTownMenu_MESSAGE.isMessageWAITPROG()) {
        if (m_bOpen) {
            m_bOpen = 0;
            redraw_ = 1;
            return false;
        }
        int offset = 6 - commandNum_;
        navigator_.setup(2, 3, commandNum_);
        int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
        if (result != 0) {
            if (result == 2) {
                switch (offset + menuItem_.active_) {
                    case 0:
                        close();
                        gTownMenu_MESSAGE.close();
                        gMaterielMenu_SAVE.open();
                        gMaterielMenu_SAVE.saveType_ = MaterielMenu_SAVE::TYPE_CHURCH;
                        redraw_ = 1;
                        break;
                    case 1:
                        close();
                        gTownMenu_MESSAGE.clearMessageWAITPROG();
                        gTownMenu_MESSAGE.close();
                        gMaterielMenu_CHURCH_OMEN.open();
                        break;
                    case 2:
                        gTownMenu_MESSAGE.openMessageForTALK();
                        gTownMenu_MESSAGE.addMessage(getMessageNo(0x13));
                        gTownMenu_MESSAGE.addMessageWAITKEY();
                        close();
                        gMaterielMenu_CHURCH_MIRACLE.open();
                        gMaterielMenu_CHURCH_MIRACLE.menuItem_.active_ = 0;
                        gMaterielMenu_CHURCH_MIRACLE.miracle_ = MIRACLE_ORDER_REVIVAL;
                        break;
                    case 3:
                        gTownMenu_MESSAGE.openMessageForTALK();
                        gTownMenu_MESSAGE.addMessage(getMessageNo(0x19));
                        gTownMenu_MESSAGE.addMessageWAITKEY();
                        close();
                        gMaterielMenu_CHURCH_MIRACLE.open();
                        gMaterielMenu_CHURCH_MIRACLE.menuItem_.active_ = 0;
                        gMaterielMenu_CHURCH_MIRACLE.miracle_ = MIRACLE_ORDER_ANTIDOTE;
                        break;
                    case 4:
                        gTownMenu_MESSAGE.openMessageForTALK();
                        gTownMenu_MESSAGE.addMessage(getMessageNo(0x1d));
                        gTownMenu_MESSAGE.addMessageWAITKEY();
                        close();
                        gMaterielMenu_CHURCH_MIRACLE.open();
                        gMaterielMenu_CHURCH_MIRACLE.menuItem_.active_ = 0;
                        gMaterielMenu_CHURCH_MIRACLE.miracle_ = MIRACLE_ORDER_ANTICURSE;
                        break;
                    case 5:
                        redraw_ = 1;
                        activeCommand_ = 5;
                        selectEnd();
                        return true;
                }
                redraw_ = 1;
                return true;
            }
            if (result == 3) {
                redraw_ = 1;
                if (activeCommand_ == -1) {
                    selectEnd();
                    return true;
                }
            }
        }
    }
    return false;
}

THUMB void MaterielMenu_CHURCH_ROOT::selectEnd()
{
    oneMessage(0x27);
    activeCommand_ = 5;
}

THUMB void MaterielMenu_CHURCH_ROOT::firstMessage()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (activeCommand_ != 7) {
        if (status::g_StageInfo.getDayNight() == dq5::DAY_NIGHT_NIGHT) {
            gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(2));
            gTownMenu_MESSAGE.addMessageWAITKEY();
            return;
        }
        gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(1));
        gTownMenu_MESSAGE.addMessageWAITKEY();
        return;
    }
    ui_MsgSndSet(0x30);
    gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0xf));
    gTownMenu_MESSAGE.addMessageWAITKEY();
}

THUMB void MaterielMenu_CHURCH_ROOT::oneMessage(int mes)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(getMessageNo(mes));
}

THUMB int MaterielMenu_CHURCH_ROOT::getMessageNo(int index)
{
    unsigned long mes;
    if (getSexType()) {
        mes = dq5::level::ChurchMessage::getRecord(index)->getMessage1();
    } else {
        mes = dq5::level::ChurchMessage::getRecord(index)->getMessage2();
    }
    return mes;
}

THUMB void MaterielMenu_CHURCH_ROOT::setTalkSound()
{
    int type = 0x32;
    if (voiceType_ == 1) {
        type = 0x31;
    }
    ui_MsgSndSet(type);
}
