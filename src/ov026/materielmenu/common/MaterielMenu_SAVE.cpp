#include "ov026/materielmenu/common/MaterielMenu_SAVE.hpp"
#include "ov026/materielmenu/church/MaterielMenu_CHURCH_ROOT.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/global/Global.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/menu/UnkMenuCasinoDraw.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/GameStatus.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline void status::MenuStatus::setBooking(menu::BOOKING_FLAG flag)
{
    bookingFlag_ = flag;
}

inline void status::StageInfo::setOverviewPosition(dss::Fix32Vector3& pos)
{
    overviewPosition_ = pos;
    overviewTempPosition_ = pos;
}

THUMB void MaterielMenu_SAVE::menuSetup()
{
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.enableSE_ = 1;
    selectList_ = 0;
    isSave_ = 0;
    messageCounter_ = 0;
    startSurechigai_ = 0;
    status_ = MENU_IS_SAVE;
    saveWaitFlag_ = 0;
    saveWaitCounter_ = 0;
}

THUMB void MaterielMenu_SAVE::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_DIARY_SELECT(&menuItem_);
}

THUMB void MaterielMenu_SAVE::menuDraw()
{
    if (status_ != MENU_SELECT || messageCounter_ == 0) {
        if (saveType_ == TYPE_CHURCH) {
            drawMoneyAndPartyWindows();
        }
        return;
    }
    for (int i = 0; i < 3; i++) {
        switch (diary_[i].savetype_) {
            case profile::SAVETYPE_NEW:
                drawJournalSlot(i, diary_[i].name_, 0, 1, diary_[i].town_, diary_[i].time_, 0x22, diary_[i].name_ != 0);
                break;
            case profile::SAVETYPE_INTERVAL:
                drawJournalSlot(i, diary_[i].name_, diary_[i].clear_, diary_[i].level_, diary_[i].town_, diary_[i].time_, 0x22, diary_[i].name_ != 0);
                break;
            case profile::SAVETYPE_CHURCH:
                drawJournalSlot(i, diary_[i].name_, diary_[i].clear_, diary_[i].level_, diary_[i].town_, diary_[i].time_, 0x22, diary_[i].name_ != 0);
                break;
            case profile::SAVETYPE_NONE:
            case profile::SAVETYPE_RESUME:
            default:
                drawJournalSlot(i, diary_[i].name_, diary_[i].clear_, diary_[i].level_, -1, diary_[i].time_, 0x22, diary_[i].name_ != 0);
                break;
        }
    }
    drawMenuFrame(0, 0x10, 0x100, 0x68, 0);
    if (saveType_ == TYPE_CHURCH) {
        drawMoneyAndPartyWindows();
    }
    menuItem_.drawActive();
}

THUMB void MaterielMenu_SAVE::menuUpdate()
{
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
    }
    if (!messageUpdate()) {
        commandUpdate();
    }
}

THUMB bool MaterielMenu_SAVE::messageUpdate()
{
    if (!gTownMenu_MESSAGE.isOpen()) {
        return false;
    }
    int stat = gTownMenu_MESSAGE.stat_;
    switch (status_) {
        case MENU_IS_SAVE:
            if (stat == MENUBASE_STAT_OK) {
                gTownMenu_MESSAGE.close();
                setMode(MENU_READING);
            } else if (stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                firstCancelMessage();
            }
            break;
        case MENU_SELECT:
            if (messageCounter_ == 0) {
                switch (saveType_) {
                    case TYPE_CHURCH:
                    case TYPE_LASTDUNGEON:
                    case TYPE_SURECHIGAI:
                        gTownMenu_MESSAGE.setMessageLastCursor(false);
                        messageCounter_++;
                        redraw_ = 1;
                        break;
                    case TYPE_CHAPTER:
                    case TYPE_CLEAR:
                        messageCounter_++;
                        redraw_ = 1;
                        break;
                }
            } else {
                return false;
            }
            break;
        case MENU_IS_OVERWRITE:
            if (stat == MENUBASE_STAT_OK) {
                gTownMenu_MESSAGE.close();
                setMode(MENU_WRITING);
            }
            if (stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                setMode(MENU_SELECT);
            }
            break;
        case MENU_WRITING:
            if (messageCounter_ == 1) {
                return false;
            }
            break;
        case MENU_WRITINGEXEC:
            return false;
        case MENU_WRITINGWAIT:
            return false;
        case MENU_SOUNDWAIT:
            return false;
        case MENU_IS_END:
            if (messageCounter_ == 0) {
                if (stat == MENUBASE_STAT_OK) {
                    gTownMenu_MESSAGE.close();
                    switch (saveType_) {
                        case TYPE_CHURCH:
                            setTalkMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(0x27));
                            break;
                        case TYPE_CHAPTER:
                        case TYPE_LASTDUNGEON:
                        case TYPE_CLEAR:
                        case TYPE_SURECHIGAI:
                            break;
                    }
                    setMode(MENU_END);
                }
                if (stat == MENUBASE_STAT_CANCEL) {
                    gTownMenu_MESSAGE.close();
                    switch (saveType_) {
                        case TYPE_CHURCH:
                            if (isSave_ != 0) {
                                setTalkMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(0xe));
                                setMode(MENU_GAME_END);
                            } else {
                                int mes1 = MaterielMenu_CHURCH_ROOT::getMessageNo(0xc);
                                setTalkYesNoMessage2(mes1, MaterielMenu_CHURCH_ROOT::getMessageNo(0xd), false);
                                messageCounter_++;
                            }
                            break;
                        case TYPE_CHAPTER:
                            setMode(MENU_IS_SAVE);
                            break;
                        case TYPE_LASTDUNGEON:
                            break;
                        case TYPE_CLEAR:
                            setMode(MENU_IS_SAVE);
                            break;
                        case TYPE_SURECHIGAI:
                            setMode(MENU_READING);
                            break;
                    }
                }
            } else {
                if (stat == MENUBASE_STAT_OK) {
                    gTownMenu_MESSAGE.close();
                    setTalkMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(0xe));
                    setMode(MENU_GAME_END);
                }
                if (stat == MENUBASE_STAT_CANCEL) {
                    gTownMenu_MESSAGE.close();
                    setMode(MENU_READING);
                }
            }
            break;
        case MENU_GAME_END:
            if (messageCounter_ == 0 && (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL)) {
                gTownMenu_MESSAGE.close();
            }
            break;
        case MENU_BLANK:
            if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
            }
            return false;
        case MENU_READING:
        case MENU_FAILED:
        case MENU_SUCCESS:
        case MENU_END:
            if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
            }
            break;
        case MENU_SURECHIGAI_START:
            if (stat == MENUBASE_STAT_OK) {
                gTownMenu_MESSAGE.close();
                ui_MsgSndSet(0x31);
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xcc602);
                setMode(MENU_END);
                MaterielMenu_WINDOW_MANAGER::getSingleton()->surechigaiStart_ = 1;
                startSurechigai_ = 1;
            }
            if (stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                ui_MsgSndSet(0x31);
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xcc631);
                setMode(MENU_END);
                MaterielMenu_WINDOW_MANAGER::getSingleton()->surechigaiStart_ = 0;
                startSurechigai_ = 0;
            }
            break;
    }
    return true;
}

THUMB void MaterielMenu_SAVE::commandUpdate()
{
    saveSoundCounter_++;
    switch (status_) {
        case MENU_IS_SAVE:
            if (messageCounter_ == 0) {
                if (!profile::SaveLoad::isCardOK()) {
                    setMode(MENU_BLANK);
                    switch (saveType_) {
                        case TYPE_CHURCH:
                            setWaitMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(0x28));
                            break;
                        case TYPE_CHAPTER:
                        case TYPE_CLEAR:
                            setWaitMessage(0xcb9fe);
                            break;
                        case TYPE_SURECHIGAI:
                            setTalkWaitMessage(0xcb9fe);
                            break;
                    }
                    return;
                }
                switch (saveType_) {
                    case TYPE_CHURCH: {
                        int mes1 = MaterielMenu_CHURCH_ROOT::getMessageNo(3);
                        setTalkYesNoMessage2(mes1, MaterielMenu_CHURCH_ROOT::getMessageNo(4), true);
                        break;
                    }
                    case TYPE_CHAPTER:
                        setYesNoMessage(0xcb9d3, true);
                        break;
                    case TYPE_CLEAR:
                        setYesNoMessage(0xcb9e9, true);
                        break;
                    case TYPE_SURECHIGAI:
                        setTalkYesNoMessage2(0xcc5eb, 0xcc5ec, true);
                        break;
                }
            }
            break;
        case MENU_READING:
            if (getSaveData()) {
                setMode(MENU_SELECT);
                redraw_ = 1;
                int active = status::g_StageInfo.profileBank_;
                if (active == 3) {
                    active = 0;
                }
                menuItem_.active_ = active;
            } else {
                setMode(MENU_BLANK);
                switch (saveType_) {
                    case TYPE_CHURCH:
                        setWaitMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(0x28));
                        break;
                    case TYPE_CHAPTER:
                        setWaitMessage(0xcb9fe);
                        break;
                    case TYPE_CLEAR:
                        setWaitMessage(0xcb9fe);
                        break;
                    case TYPE_SURECHIGAI:
                        setTalkWaitMessage(0xcb9fe);
                        break;
                }
            }
            break;
        case MENU_SELECT:
            if (messageCounter_ == 0) {
                switch (saveType_) {
                    case TYPE_CHURCH:
                        setTalkWaitMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(5));
                        break;
                    case TYPE_CLEAR:
                        setTalkWaitMessage(0xcb9ef);
                        break;
                    case TYPE_CHAPTER:
                        setTalkWaitMessage(0xcb9d9);
                        redraw_ = 1;
                        break;
                    case TYPE_SURECHIGAI:
                        setTalkWaitMessage(0xcc5ef);
                        break;
                }
            } else {
                if (saveType_ == TYPE_CLEAR || saveType_ == TYPE_CHAPTER) {
                    selectDiary();
                } else if (gTownMenu_MESSAGE.isOpen() && gTownMenu_MESSAGE.isMessageWAITPROG()) {
                    selectDiary();
                }
            }
            break;
        case MENU_IS_OVERWRITE:
            profile::SaveLoad::setCatalogMacro(&catalogview_[menuItem_.active_]);
            switch (saveType_) {
                case TYPE_CHURCH:
                    setTalkYesNoMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(6), true);
                    break;
                case TYPE_CHAPTER:
                case TYPE_CLEAR:
                    if (catalogview_[menuItem_.active_].clear_ != 0) {
                        setYesNoMessage(0xcb9df, true);
                    } else {
                        setYesNoMessage(0xcb9dc, true);
                    }
                    break;
                case TYPE_SURECHIGAI:
                    setTalkYesNoMessage(0xcc5f2, true);
                    break;
            }
            break;
        case MENU_WRITING:
            if (!profile::SaveLoad::isCardOK()) {
                setMode(MENU_BLANK);
                switch (saveType_) {
                    case TYPE_CHURCH:
                        setWaitMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(0x28));
                        break;
                    case TYPE_CHAPTER:
                    case TYPE_CLEAR:
                        setWaitMessage(0xcb9fe);
                        break;
                    case TYPE_SURECHIGAI:
                        setTalkWaitMessage(0xcb9fe);
                        break;
                }
                return;
            }
            if (messageCounter_ == 0) {
                saveSoundCounter_ = 999;
                switch (saveType_) {
                    case TYPE_CHURCH:
                        cmn::g_cmnSoundManager.setFadeOut(5);
                        cmn::g_cmnSoundManager.setPlaySound(2, false);
                        setWaitMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(7));
                        saveSoundCounter_ = 0;
                        break;
                    case TYPE_CHAPTER:
                        setWaitMessage(0xcb9e2);
                        break;
                    case TYPE_LASTDUNGEON:
                        cmn::g_cmnSoundManager.setPlaySound(2, false);
                        setWaitMessage(0xcb9f8);
                        saveSoundCounter_ = 0;
                        break;
                    case TYPE_CLEAR:
                        setWaitMessage(0xcb9f8);
                        break;
                    case TYPE_SURECHIGAI:
                        setWaitMessage(0xcc5f5);
                        if (status::g_Game.language_ == 3) {
                            saveWaitFlag_ = 1;
                            saveWaitCounter_ = 60;
                        }
                        break;
                }
                messageCounter_++;
            }
            gTownMenu_MESSAGE.setBusyIcon(true);
            setMode(MENU_WRITINGEXEC);
            break;
        case MENU_WRITINGEXEC:
            if (gTownMenu_MESSAGE.isOpen() && gTownMenu_MESSAGE.isMessageWAITPROG()) {
                saveResult_ = 0;
                dss::Fix32Vector3 pos;
                switch (saveType_) {
                    case TYPE_CHURCH:
                        status::g_StageInfo.setChurchMapNameId(g_Global.getMapNameId());
                        profile::SaveLoad::savebankAsync(menuItem_.active_, profile::SAVETYPE_CHURCH);
                        break;
                    case TYPE_CLEAR:
                        status::g_StageInfo.setChurchMapNameId(0x42);
                        static float z = 12.0f;
                        static float y = 0.2f;
                        pos.vx = dss::Fix32(0.0f);
                        pos.vy = dss::Fix32(y);
                        pos.vz = dss::Fix32(z);
                        status::g_StageInfo.setOverviewPosition(pos);
                        status::g_StageAttribute.setMapName("cdf1a");
                        status::g_StageInfo.setTimeZone(TIME_ZONE_DAYTIME);
                        status::g_StageInfo.lastFldSurface_ = -1;
                        status::g_StageInfo.setRanaMapNameId(0);
                        profile::SaveLoad::savebankAsync(menuItem_.active_, profile::SAVETYPE_INTERVAL);
                        break;
                    case TYPE_SURECHIGAI:
                        status::g_StageInfo.setChurchMapNameId(0x27c);
                        profile::SaveLoad::savebankAsync(menuItem_.active_, profile::SAVETYPE_CHURCH);
                        break;
                    case TYPE_CHAPTER:
                        status::g_StageInfo.lastFldSurface_ = -1;
                        status::g_StageInfo.setRanaMapNameId(0);
                        profile::SaveLoad::savebankAsync(menuItem_.active_, profile::SAVETYPE_INTERVAL);
                        break;
                }
                setMode(MENU_WRITINGWAIT);
            }
            break;
        case MENU_WRITINGWAIT:
            if (profile::SaveLoad::savebankAsyncWait()) {
                saveResult_ = profile::SaveLoad::savebankAsyncResult();
                setMode(MENU_SOUNDWAIT);
            }
            break;
        case MENU_SOUNDWAIT:
            if (cmn::g_cmnSoundManager.isPlaySound() != true) {
                if (saveWaitFlag_) {
                    saveWaitCounter_--;
                    if (saveWaitCounter_ <= 0) {
                        saveWaitFlag_ = 0;
                        return;
                    }
                    break;
                }
                gTownMenu_MESSAGE.setBusyIcon(false);
                if (saveResult_ == 1) {
                    setMode(MENU_SUCCESS);
                    gTownMenu_MESSAGE.clearMessageWAITPROG();
                    gTownMenu_MESSAGE.close();
                } else if (saveResult_ == 0) {
                    setMode(MENU_FAILED);
                    gTownMenu_MESSAGE.clearMessageWAITPROG();
                    gTownMenu_MESSAGE.close();
                }
            }
            break;
        case MENU_FAILED:
            gTownMenu_MESSAGE.openMessageForMENU();
            switch (saveType_) {
                case TYPE_CHURCH:
                    setWaitMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(8));
                    setMode(MENU_SELECT);
                    break;
                case TYPE_CHAPTER:
                    setWaitMessage(0xcb9e5);
                    setMode(MENU_BLANK);
                    break;
                case TYPE_CLEAR:
                    setWaitMessage(0xcb9fb);
                    setMode(MENU_BLANK);
                    break;
                case TYPE_SURECHIGAI:
                    setTalkWaitMessage(0xcb9e5);
                    setMode(MENU_BLANK);
                    break;
            }
            break;
        case MENU_SUCCESS:
            switch (saveType_) {
                case TYPE_CHURCH:
                    setTalkYesNoMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(9), true);
                    setMode(MENU_IS_END);
                    isSave_ = 1;
                    break;
                case TYPE_CHAPTER:
                    setMode(MENU_END);
                    break;
                case TYPE_CLEAR:
                    setMode(MENU_END);
                    break;
                case TYPE_SURECHIGAI:
                    gTownMenu_MESSAGE.close();
                    ui_MsgSndSet(0x31);
                    gTownMenu_MESSAGE.openMessageForTALK();
                    gTownMenu_MESSAGE.addMessage(0xcc5fb);
                    gTownMenu_MESSAGE.setYesNo();
                    setMode(MENU_SURECHIGAI_START);
                    break;
            }
            break;
        case MENU_GAME_END:
            if (messageCounter_ == 0) {
                data_0211b27c.state_ = FadeEffector::FADE_NONE;
                data_0211b27c.count_ = 0;
                data_0211b27c.frames_ = 120;
                data_0211b27c.sprite_[0].setColor(0, 0, 0);
                data_0211b27c.sprite_[1].setColor(0, 0, 0);
                data_02101d14.addPart(&data_0211b27c);
                messageCounter_++;
                status::g_Menu.setBooking(menu::BOOKING_GAMESET);
                SoundManager::stopBgm(120);
                cmn::GameManager::getSingleton().playerManager_->setLock(true);
                cmn::GameManager::getSingleton().playerManager_->charaColl_ = 0;
                BillboardCharacter::setAllCharaAnim(false);
                close();
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            } else if (messageCounter_ == 1) {
                if (data_0211b27c.count_ == data_0211b27c.frames_) {
                    ui_MsgSndSet(0x30);
                    setMessage(MaterielMenu_CHURCH_ROOT::getMessageNo(0xf));
                    messageCounter_++;
                }
            }
            break;
        case MENU_END:
            close();
            switch (saveType_) {
                case TYPE_CHAPTER:
                    if (gTownMenu_MESSAGE.isOpen()) {
                        gTownMenu_MESSAGE.close();
                    }
                    break;
                case TYPE_SURECHIGAI:
                    if (startSurechigai_ == 0) {
                        status::g_Menu.setBooking(menu::BOOKING_SURECHIGAI_ROOT);
                    }
                    break;
                case TYPE_CHURCH:
                case TYPE_LASTDUNGEON:
                case TYPE_CLEAR:
                    break;
            }
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
        case MENU_BLANK:
            break;
    }
}

THUMB bool MaterielMenu_SAVE::getSaveData()
{
    if (!profile::SaveLoad::isCardOK()) {
        return false;
    }
    catalogview_ = profile::SaveLoad::getCatalogView();
    profile::CatalogView* view = catalogview_;
    UnkDiaryInfo* diary = diary_;
    for (int i = 0; i < 3; i++, view++, diary++) {
        if (view->useFlag_ != 0) {
            diary->name_ = view->name_;
            diary->clear_ = view->clear_;
            diary->level_ = view->level_;
            diary->town_ = view->town_;
            diary->time_ = view->time_;
            diary->savetype_ = view->savetype_;
        } else {
            diary->name_ = 0;
            diary->clear_ = 0;
            diary->level_ = 0;
            diary->town_ = 0;
            diary->time_ = 0;
            diary->savetype_ = 0;
        }
    }
    return true;
}

THUMB void MaterielMenu_SAVE::setMode(SAVEMENU_MODE mode)
{
    status_ = mode;
    messageCounter_ = 0;
}

THUMB void MaterielMenu_SAVE::selectDiary()
{
    menuItem_.execInput();
    switch (menuItem_.result_) {
        case menu::MenuItem::MENUITEM_RESULT_OK:
            menuItem_.result_ = 0;
            menuItem_.lastresult_ = 0;
            if (diary_[selectList_].name_ == 0) {
                setMode(MENU_WRITING);
            } else {
                setMode(MENU_IS_OVERWRITE);
            }
            if (gTownMenu_MESSAGE.isOpen()) {
                gTownMenu_MESSAGE.close();
            }
            redraw_ = 1;
            break;
        case menu::MenuItem::MENUITEM_RESULT_CANCEL:
            menuItem_.result_ = 0;
            menuItem_.lastresult_ = 0;
            if (gTownMenu_MESSAGE.isOpen()) {
                gTownMenu_MESSAGE.close();
            }
            firstCancelMessage();
            redraw_ = 1;
            break;
        case menu::MenuItem::MENUITEM_RESULT_UP:
            menuItem_.active_ = 2;
            break;
        case menu::MenuItem::MENUITEM_RESULT_DOWN:
            menuItem_.active_ = 0;
            break;
    }
    selectList_ = menuItem_.active_;
}

THUMB void MaterielMenu_SAVE::setMessage(int mes)
{
    if (saveType_ == TYPE_CHURCH) {
        mes += sexType_;
    }
    gTownMenu_MESSAGE.openMessageForMENU();
    gTownMenu_MESSAGE.addMessage(mes);
}

THUMB void MaterielMenu_SAVE::setWaitMessage(int mes)
{
    gTownMenu_MESSAGE.openMessageForMENU();
    gTownMenu_MESSAGE.addMessageNOWAIT(mes);
    gTownMenu_MESSAGE.addMessageWAITKEY();
}

THUMB void MaterielMenu_SAVE::setYesNoMessage(int mes, bool yes)
{
    gTownMenu_MESSAGE.openMessageForMENU();
    gTownMenu_MESSAGE.addMessage(mes);
    gTownMenu_MESSAGE.setYesNo(yes ? 0 : 1);
}

THUMB void MaterielMenu_SAVE::setTalkMessage(int mes)
{
    if (saveType_ == TYPE_CHURCH) {
        MaterielMenu_CHURCH_ROOT::setTalkSound();
    }
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes);
}

THUMB void MaterielMenu_SAVE::setTalkWaitMessage(int mes)
{
    if (saveType_ == TYPE_CHURCH) {
        MaterielMenu_CHURCH_ROOT::setTalkSound();
    }
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessageNOWAIT(mes);
    gTownMenu_MESSAGE.addMessageWAITKEY();
}

THUMB void MaterielMenu_SAVE::setTalkYesNoMessage(int mes, bool yes)
{
    if (saveType_ == TYPE_CHURCH) {
        MaterielMenu_CHURCH_ROOT::setTalkSound();
    }
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes);
    gTownMenu_MESSAGE.setYesNo(yes ? 0 : 1);
}

THUMB void MaterielMenu_SAVE::setTalkYesNoMessage2(int mes1, int mes2, bool yes)
{
    if (saveType_ == TYPE_CHURCH) {
        MaterielMenu_CHURCH_ROOT::setTalkSound();
    }
    int cursor = yes ? 0 : 1;
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes1, mes2);
    gTownMenu_MESSAGE.setYesNo(cursor);
}

THUMB void MaterielMenu_SAVE::firstCancelMessage()
{
    switch (saveType_) {
        case TYPE_CHURCH: {
            int mes1 = MaterielMenu_CHURCH_ROOT::getMessageNo(0xa);
            setTalkYesNoMessage2(mes1, MaterielMenu_CHURCH_ROOT::getMessageNo(0xb), true);
            setMode(MENU_IS_END);
            break;
        }
        case TYPE_CHAPTER:
            setYesNoMessage(0xcb9d6, false);
            setMode(MENU_IS_END);
            break;
        case TYPE_CLEAR:
            setYesNoMessage(0xcb9ec, false);
            setMode(MENU_IS_END);
            break;
        case TYPE_SURECHIGAI:
            setTalkYesNoMessage2(0xcc5fe, 0xcc5ff, false);
            setMode(MENU_IS_END);
            break;
    }
}
