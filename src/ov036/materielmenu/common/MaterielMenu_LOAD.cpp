#include "ov036/materielmenu/common/MaterielMenu_LOAD.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/common/MaterielMenu_LoadName.hpp"
#include "main/global/Global.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuCasinoDraw.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/status/GameStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/Status.hpp"

using menu::MenuTemplate_materiel;

inline void status::StageInfo::setReturnGame(dq5::RETURN_GAME_TYPE returnGame)
{
    returnGame_ = returnGame;
}

const int MaterielMenu_LOAD::ROOT_COUNT = 3;
const int MaterielMenu_LOAD::ROOT_RESUME_COUNT = 4;
int MaterielMenu_LOAD::activeDiaryNo_ = -1;

THUMB void MaterielMenu_LOAD::menuSetup()
{
    rootItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    dataItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    resumeItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    status_ = LOAD_MODESELECT;
    country_ = 0;
    messageCounter_ = -1;
    menuMode_ = 0;
    country_ = status::g_Game.language_;
    killResult_ = 0;
    makeResult_ = 0;
    wait_ = 0;
    resumeExist_ = 0;
    if (profile::SaveLoad::checkbank(3) == 1) {
        resumeExist_ = 1;
    }
    frame_ = 0;
    deleteWaitFlag_ = 0;
    deleteWaitCounter_ = 0;
}

THUMB void MaterielMenu_LOAD::menuExecute()
{
    if (resumeExist_ != 0) {
        MenuTemplate_materiel::MATERIEL_DIARY_MENU(&rootItem_, ROOT_RESUME_COUNT);
    } else {
        MenuTemplate_materiel::MATERIEL_DIARY_MENU(&rootItem_, ROOT_COUNT);
    }
    MenuTemplate_materiel::MATERIEL_DIARY_LOAD(&dataItem_);
    MenuTemplate_materiel::unkfunc_0217d0b8(&resumeItem_);
}

THUMB void MaterielMenu_LOAD::menuDraw()
{
    int rootMessage[3] = { 0xe00002ef, 0xe00002f0, 0xe00002f1 };
    int rootResumeMessage[4] = { 0xe00002ef, 0xe00002ee, 0xe00002f0, 0xe00002f1 };
    if (status_ == LOAD_MODESELECT) {
        if (resumeExist_ == 1) {
            unkfunc_02029fec(rootResumeMessage, ROOT_RESUME_COUNT, 0x18, 0x10);
            drawMenuFrame(8, 8, 0xa0, 0x48, -1);
            rootItem_.drawActive();
        } else {
            unkfunc_02029fec(rootMessage, ROOT_COUNT, 0x18, 0x10);
            drawMenuFrame(8, 8, 0xa0, 0x38, -1);
            rootItem_.drawActive();
        }
    }
    if (status_ == LOAD_DATASELECT) {
        int message = rootMessage[0];
        int flag = 1;
        if (menuMode_ == 1) {
            message = rootMessage[1];
            flag = 0;
        } else if (menuMode_ == 2) {
            message = rootMessage[2];
        }
        drawCenteredMessage(&message, 8, 0x38, 0xf0, 0x50);
        for (int i = 0; i < 3; i++) {
            switch (diary_[i].savetype_) {
                case profile::SAVETYPE_NEW:
                    unkfunc_0202a164(i, diary_[i].name_, 0, 1, diary_[i].town_, diary_[i].time_, 0x5a, flag);
                    break;
                case profile::SAVETYPE_INTERVAL:
                    unkfunc_0202a164(i, diary_[i].name_, diary_[i].clear_, diary_[i].level_, diary_[i].town_, diary_[i].time_, 0x5a, flag);
                    break;
                case profile::SAVETYPE_CHURCH:
                    unkfunc_0202a164(i, diary_[i].name_, diary_[i].clear_, diary_[i].level_, diary_[i].town_, diary_[i].time_, 0x5a, flag);
                    break;
                case profile::SAVETYPE_NONE:
                case profile::SAVETYPE_RESUME:
                default:
                    unkfunc_0202a164(i, diary_[i].name_, diary_[i].clear_, diary_[i].level_, -1, diary_[i].time_, 0x5a, flag);
                    break;
            }
        }
        drawMenuFrame(8, 0x38, 0xf0, 0x78, 0x50);
        dataItem_.drawActive();
    }
    if (status_ == LOAD_IS_RESUME) {
        drawCenteredMessage(&rootResumeMessage[1], 8, 0x38, 0xf0, 0x50);
        unkfunc_0202a274(diary_[3].name_, diary_[3].clear_, diary_[3].level_, diary_[3].time_);
        drawMenuFrame(8, 0x38, 0xf0, 0x40, 0x50);
        resumeItem_.drawActive();
    }
}

THUMB void MaterielMenu_LOAD::menuUpdate()
{
    if (wait_ > 0) {
        wait_--;
        return;
    }
    if (frame_ < 30) {
        frame_++;
        return;
    }
    if (messageUpdate()) {
        return;
    }
    switch (status_) {
        case LOAD_MODESELECT:
            rootUpdate();
            break;
        case LOAD_DATACHECK:
            if (getSaveData()) {
                if (menuMode_ == 3) {
                    changeStatus(LOAD_IS_RESUME);
                    redraw_ = 1;
                    break;
                }
                changeStatus(LOAD_DATASELECT);
                activeDiaryNo_ = 0;
                redraw_ = 1;
            } else {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessageNOWAIT(0xcb60b);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                changeStatus(LOAD_ERROR);
            }
            break;
        case LOAD_DATASELECT:
            dataSelectUpdate();
            break;
        case LOAD_WRITECHECK: {
            int result = profile::SaveLoad::isCardOK();
            status::g_StageInfo.setReturnGame(dq5::RETURN_GAME_CHURCH);
            if (result) {
                result = makeDiary();
            }
            if (result) {
                changeStatus(LOAD_END);
            } else {
                gTownMenu_MESSAGE.close();
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessageNOWAIT(0xcb5fa);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                changeStatus(LOAD_ERROR);
            }
            break;
        }
        case LOAD_DELETECHECK:
            if (gTownMenu_MESSAGE.isOpen() && gTownMenu_MESSAGE.isMessageWAITPROG()) {
                deleteResult_ = deleteDiary();
                changeStatus(LOAD_DELETEWAIT);
            }
            break;
        case LOAD_DELETEWAIT:
            if (deleteWaitFlag_) {
                deleteWaitCounter_--;
                if (deleteWaitCounter_ <= 0) {
                    deleteWaitFlag_ = 0;
                }
            } else if (deleteResult_) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xcb605);
                messageCounter_++;
            } else {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessageNOWAIT(0xcb608);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                changeStatus(LOAD_ERROR);
            }
            break;
        case LOAD_LOADCHECK: {
            int result = profile::SaveLoad::loadbank(activeDiaryNo_);
            status::g_StageInfo.setReturnGame(dq5::RETURN_GAME_CHURCH);
            if (result) {
                changeStatus(LOAD_END);
            } else {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessageNOWAIT(0xcb60b);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                changeStatus(LOAD_ERROR);
            }
            break;
        }
        case LOAD_ERROR:
            if (gTownMenu_MESSAGE.isOpen()) {
                gTownMenu_MESSAGE.isMessageWAITPROG();
            }
            break;
        case LOAD_END:
            close();
            break;
        case LOAD_IS_RESUME:
            resumeUpdate();
            break;
        case LOAD_RESUME: {
            int result = profile::SaveLoad::loadbank(3);
            status::g_StageInfo.setReturnGame(dq5::RETURN_GAME_ABORT);
            if (result) {
                changeStatus(LOAD_END);
            } else {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessageNOWAIT(0xcba10);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                changeStatus(LOAD_ERROR);
            }
            break;
        }
    }
}

THUMB bool MaterielMenu_LOAD::messageUpdate()
{
    if (!gTownMenu_MESSAGE.isOpen()) {
        return false;
    }
    int stat = gTownMenu_MESSAGE.stat_;
    switch (status_) {
        case LOAD_DATASELECT:
            switch (menuMode_) {
                case 0:
                    if (stat == MENUBASE_STAT_OK) {
                        gTownMenu_MESSAGE.close();
                        changeStatus(LOAD_NAMEEDIT);
                        redraw_ = 1;
                    } else if (stat == MENUBASE_STAT_CANCEL) {
                        gTownMenu_MESSAGE.close();
                    }
                    break;
                case 1:
                    if (stat == MENUBASE_STAT_OK) {
                        gTownMenu_MESSAGE.close();
                        changeStatus(LOAD_NAMEEDIT);
                        redraw_ = 1;
                    } else if (stat == MENUBASE_STAT_CANCEL) {
                        gTownMenu_MESSAGE.close();
                    }
                    break;
                case 2:
                    if (stat == MENUBASE_STAT_OK) {
                        gTownMenu_MESSAGE.close();
                        gTownMenu_MESSAGE.openMessageForMENU();
                        gTownMenu_MESSAGE.addMessageNOWAIT(0xcb604);
                        gTownMenu_MESSAGE.addMessageWAITKEY();
                        changeStatus(LOAD_DELETECHECK);
                        deleteWaitFlag_ = 1;
                        deleteWaitCounter_ = 60;
                    } else if (stat == MENUBASE_STAT_CANCEL) {
                        gTownMenu_MESSAGE.close();
                    }
                    break;
            }
            break;
        case LOAD_DELETECHECK:
        case LOAD_DELETEWAIT:
            if (messageCounter_ > 0) {
                if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
                    redraw_ = 1;
                    gTownMenu_MESSAGE.close();
                    changeStatus(LOAD_MODESELECT);
                }
            } else {
                return false;
            }
            break;
        case LOAD_WRITECHECK:
        case LOAD_LOADCHECK:
            if (messageCounter_ > 0) {
                if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
                    redraw_ = 1;
                    gTownMenu_MESSAGE.close();
                    changeStatus(LOAD_MODESELECT);
                }
            } else if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
                gTownMenu_MESSAGE.close();
                return false;
            }
            break;
        case LOAD_ERROR:
            if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
            }
            return false;
        case LOAD_END:
            closeMessage();
            break;
    }
    return true;
}

THUMB void MaterielMenu_LOAD::rootUpdate()
{
    rootItem_.execInput();
    switch (rootItem_.result_) {
        case menu::MenuItem::MENUITEM_RESULT_OK: {
            rootItem_.result_ = 0;
            rootItem_.lastresult_ = 0;
            dataItem_.active_ = 0;
            if (!profile::SaveLoad::isCardOK()) {
                stat_ = MENUBASE_STAT_OK;
                changeStatus(LOAD_END);
                break;
            }
            if (resumeExist_ != 0) {
                int active = rootItem_.active_;
                if (active == 0) {
                    menuMode_ = 0;
                } else if (active == 1) {
                    menuMode_ = 3;
                } else if (active == 2) {
                    menuMode_ = 1;
                } else if (active == 3) {
                    menuMode_ = 2;
                }
                changeStatus(LOAD_DATACHECK);
            } else {
                int active = rootItem_.active_;
                if (active == 0) {
                    menuMode_ = 0;
                } else if (active == 1) {
                    menuMode_ = 1;
                } else if (active == 2) {
                    menuMode_ = 2;
                }
                changeStatus(LOAD_DATACHECK);
            }
            break;
        }
        case menu::MenuItem::MENUITEM_RESULT_CANCEL:
            rootItem_.result_ = 0;
            rootItem_.lastresult_ = 0;
            break;
        case menu::MenuItem::MENUITEM_RESULT_UP:
            if (resumeExist_ != 0) {
                rootItem_.active_ = 3;
            } else {
                rootItem_.active_ = 2;
            }
            break;
        case menu::MenuItem::MENUITEM_RESULT_DOWN:
            rootItem_.active_ = 0;
            break;
    }
}

THUMB void MaterielMenu_LOAD::resumeUpdate()
{
    resumeItem_.execInput();
    if (resumeItem_.result_ == menu::MenuItem::MENUITEM_RESULT_OK) {
        changeStatus(LOAD_RESUME);
        wait_ = 2;
        redraw_ = 1;
    } else if (resumeItem_.result_ == menu::MenuItem::MENUITEM_RESULT_CANCEL || resumeItem_.result_ == menu::MenuItem::MENUITEM_RESULT_SUPERCANCEL) {
        changeStatus(LOAD_MODESELECT);
        redraw_ = 1;
    }
    resumeItem_.result_ = 0;
    resumeItem_.lastresult_ = 0;
}

THUMB void MaterielMenu_LOAD::dataSelectUpdate()
{
    dataItem_.execInput();
    switch (dataItem_.result_) {
        case menu::MenuItem::MENUITEM_RESULT_OK: {
            dataItem_.result_ = 0;
            dataItem_.lastresult_ = 0;
            int active = dataItem_.active_;
            activeDiaryNo_ = active;
            switch (menuMode_) {
                case 0:
                    if (diary_[active].name_ == 0) {
                        gTownMenu_MESSAGE.openMessageForMENU();
                        gTownMenu_MESSAGE.addMessage(0xcb5eb);
                        gTownMenu_MESSAGE.setYesNo();
                    } else {
                        changeStatus(LOAD_LOADCHECK);
                        wait_ = 2;
                    }
                    break;
                case 1:
                    if (diary_[active].name_ != 0) {
                        gTownMenu_MESSAGE.openMessageForMENU();
                        gTownMenu_MESSAGE.addMessage(0xcb5ef);
                        gTownMenu_MESSAGE.setYesNo();
                    } else {
                        changeStatus(LOAD_NAMEEDIT);
                    }
                    break;
                case 2:
                    if (diary_[active].name_ != 0) {
                        gTownMenu_MESSAGE.openMessageForMENU();
                        profile::SaveLoad::setCatalogMacro(&catalogview_[activeDiaryNo_]);
                        profile::CatalogView* view = &catalogview_[activeDiaryNo_];
                        if (view->clear_ != 0) {
                            gTownMenu_MESSAGE.addMessage(0xcb601);
                        } else if (view->savetype_ == profile::SAVETYPE_NEW) {
                            gTownMenu_MESSAGE.addMessage(0xcb610);
                        } else {
                            gTownMenu_MESSAGE.addMessage(0xcb5fe);
                        }
                        gTownMenu_MESSAGE.setYesNo(1);
                    }
                    break;
            }
            redraw_ = 1;
            break;
        }
        case menu::MenuItem::MENUITEM_RESULT_CANCEL:
            dataItem_.result_ = 0;
            dataItem_.lastresult_ = 0;
            changeStatus(LOAD_MODESELECT);
            redraw_ = 1;
            break;
        case menu::MenuItem::MENUITEM_RESULT_CHANGE:
            activeDiaryNo_ = dataItem_.active_;
            break;
        case menu::MenuItem::MENUITEM_RESULT_UP:
            dataItem_.active_ = 2;
            activeDiaryNo_ = dataItem_.active_;
            break;
        case menu::MenuItem::MENUITEM_RESULT_DOWN:
            dataItem_.active_ = 0;
            activeDiaryNo_ = dataItem_.active_;
            break;
    }
}

THUMB bool MaterielMenu_LOAD::getSaveData()
{
    catalogview_ = profile::SaveLoad::getCatalogView();
    firstDiary_ = profile::SaveLoad::getCatalogRecent();
    freeDiary_ = 3;
    profile::CatalogView* view = catalogview_;
    UnkDiaryInfo* diary = diary_;
    int useFlag[3] = { 0, 0, 0 };
    int i;
    int* use = useFlag;
    for (i = 0; i < 3; i++, view++, diary++, use++) {
        *use = view->useFlag_;
        if (*use != 0) {
            diary->name_ = view->name_;
            diary->clear_ = view->clear_;
            diary->level_ = view->level_;
            diary->town_ = view->town_;
            diary->time_ = view->time_;
            diary->savetype_ = view->savetype_;
        } else {
            if (freeDiary_ > i) {
                freeDiary_ = i;
            }
            diary->name_ = 0;
            diary->clear_ = 0;
            diary->level_ = 0;
            diary->town_ = 0;
            diary->time_ = 0;
            diary->savetype_ = 0;
        }
    }
    diary_[3].name_ = view->name_;
    diary_[3].clear_ = view->clear_;
    diary_[3].level_ = view->level_;
    diary_[3].time_ = view->time_;
    if (freeDiary_ == 3) {
        freeDiary_ = 0;
    }
    if (useFlag[firstDiary_] == 0) {
        firstDiary_ = 0;
        for (int k = 0; k < 3; k++) {
            if (useFlag[k] != 0) {
                firstDiary_ = k;
                break;
            }
        }
    }
    dataItem_.active_ = firstDiary_;
    if (menuMode_ == 1) {
        dataItem_.active_ = freeDiary_;
    }
    return true;
}

THUMB bool MaterielMenu_LOAD::deleteDiary()
{
    return profile::SaveLoad::killbank(activeDiaryNo_);
}

THUMB bool MaterielMenu_LOAD::makeDiary()
{
    status::g_Party.setNormalMode();
    status::Status::setEventParty(1);
    status::g_Game.setPlayTime(0);
    status::g_Game.resetUniqueID();
    g_Global.startFirstTown();
    return profile::SaveLoad::savebank(activeDiaryNo_, profile::SAVETYPE_NEW);
}

THUMB void MaterielMenu_LOAD::changeStatus(LOAD_STATUS status)
{
    if (status == LOAD_NAMEEDIT) {
        close();
        gMaterielMenu_LoadName.open();
    }
    status_ = status;
    messageCounter_ = 0;
}

THUMB void MaterielMenu_LOAD::closeMessage()
{
    int stat = gTownMenu_MESSAGE.stat_;
    redraw_ = 1;
    if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
        gTownMenu_MESSAGE.close();
    }
}
