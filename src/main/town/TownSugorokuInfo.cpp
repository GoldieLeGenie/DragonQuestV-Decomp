#include "main/town/TownSugorokuInfo.hpp"

#pragma thumb on

inline void twn::PanelData::setPos(dss::Fix32Vector3& pos)
{
    pos_ = pos;
}

inline void twn::PanelData::setRoopData(PanelData* panel)
{
    loopPanel_ = panel;
}

inline unsigned short twn::PanelData::getUid()
{
    return uid_;
}

inline int twn::TownSugorokuInfo::isBack()
{
    return back_;
}

inline void twn::TownSugorokuInfo::setLastPanel(PanelData* panel)
{
    if (panel != NULL) {
        lastPanel_ = *panel;
    }
}

twn::TownSugorokuInfo::TownSugorokuInfo()
{
    nowPanel = NULL;
    nextPanel = NULL;
    panelNum_ = 0;
    chanceCardID_ = 0;
    nextPayOff_ = 0;
    back_ = 0;
    backReverce_ = 0;
    stageDataOffset_ = 0;
    for (int i = 0; i < SUGOROKU_PANEL_MAX_NUM; i++) {
        panel_[i].clear();
    }
    count_ = 0;
    for (int i = 0; i < DICE_MOVE_MAX_NUM; i++) {
        diceMovePanel_[i] = NULL;
    }
    continueState_ = NOT_SUGOROKU;
    nowMoveCount = 0;
    orgMoveCount_ = 0;
    debugOrgMoveCount_ = 0;
    diceCount_ = 0;
    endMapId_ = 0;
    endMapPos_.set(0, 0, 0);
    endMapIdx_ = 0;
    menuState_ = 0;
    randomEcountFlag_ = 0;
    diceLimit_ = 0;
    diceLimitCount_ = 0;
    sugorokuEndMode_ = 0;
    lastPanel_.clear();
    diceControlFlag_ = 0;
    timeCount_ = 0x8ca0;
}

void twn::TownSugorokuInfo::initialize()
{
    nowPanel = NULL;
    nextPanel = NULL;
    panelNum_ = 0;
    chanceCardID_ = 0;
    diceControlFlag_ = 0;
    for (int i = 0; i < EXTRA_BACK_COUNT; i++) {
        extraBack_[i] = NULL;
        extraUid_[i] = 0;
    }
    extraUid_[0] = 0x7603;
    extraUid_[1] = 0x77ba;
    extraUid_[2] = 0x778b;
    extraUid_[3] = 0x78fc;
    stageDataOffset_ = 0;
    for (int i = 0; i < SUGOROKU_PANEL_MAX_NUM; i++) {
        panel_[i].clear();
    }
    count_ = 0;
    for (int i = 0; i < DICE_MOVE_MAX_NUM; i++) {
        diceMovePanel_[i] = NULL;
    }
    if (continueState_ == NOT_SUGOROKU || continueState_ == START_SUGOROKU) {
        nowMoveCount = 0;
        orgMoveCount_ = 0;
        debugOrgMoveCount_ = 0;
        diceCount_ = 0;
        lastPanel_.clear();
        back_ = 0;
    }
    if (!isContinue()) {
        randomEcountFlag_ = 0;
    }
}

void twn::TownSugorokuInfo::pushPanelData(unsigned short uid, unsigned short panelID, unsigned short attr, unsigned short warpMapNo, unsigned short warpUid, dss::Fix32Vector3& pos)
{
    panel_[panelNum_].setData(uid, panelID, attr, warpMapNo, warpUid);
    panel_[panelNum_].setPos(pos);
    panelNum_++;
}

void twn::TownSugorokuInfo::pushPanelLink(int index, int no, int link)
{
    panel_[index].pushLinkPanel(no, &panel_[link]);
}

void twn::TownSugorokuInfo::setLoopLink(int index, int loop)
{
    panel_[index].setRoopData(&panel_[loop]);
}

int twn::TownSugorokuInfo::getPushCount()
{
    return count_;
}

void twn::TownSugorokuInfo::pushDiceMovePanel(PanelData* data)
{
    diceMovePanel_[count_] = data;
    if (nowMoveCount > 0) {
        nowMoveCount--;
        count_++;
    }
    pushBackup(data);
}

void twn::TownSugorokuInfo::popDiceMovePanel()
{
    nowMoveCount++;
    count_--;
    popBackup();
}

int twn::TownSugorokuInfo::getEndMapNameId()
{
    return endMapId_;
}

dss::Fix32Vector3& twn::TownSugorokuInfo::getEndMapPosition()
{
    return endMapPos_;
}

short twn::TownSugorokuInfo::getEndMapDirIdx()
{
    return endMapIdx_;
}

void twn::TownSugorokuInfo::clearDiceMove()
{
    count_ = 0;
}

void twn::TownSugorokuInfo::moveBackup()
{
}

void twn::TownSugorokuInfo::pushBackup(PanelData* data)
{
    for (int i = MOVE_BACKUP_NUM - 1; i > 0; i--) {
        moveBackup_[i] = moveBackup_[i - 1];
    }
    moveBackup_[0] = data;
    setLastPanel(moveBackup_[0]);
    for (int i = 0; i < EXTRA_BACK_COUNT; i++) {
        if (extraUid_[i] == data->getUid()) {
            extraBack_[i] = data;
        }
    }
}

void twn::TownSugorokuInfo::popBackup()
{
    if (!isBack() && moveBackup_[0] != NULL) {
        for (int i = 0; i < EXTRA_BACK_COUNT; i++) {
            if (extraUid_[i] == moveBackup_[0]->getUid()) {
                extraBack_[i] = NULL;
            }
        }
    }
    for (int i = 0; i < MOVE_BACKUP_NUM - 1; i++) {
        moveBackup_[i] = moveBackup_[i + 1];
    }
    setLastPanel(moveBackup_[0]);
}

bool twn::TownSugorokuInfo::isContinue()
{
    return continueState_ != NOT_SUGOROKU;
}

bool twn::TownSugorokuInfo::isExtraBackLink(unsigned short uid)
{
    for (int i = 0; i < EXTRA_BACK_COUNT; i++) {
        if (uid == extraUid_[i]) {
            return true;
        }
    }
    return false;
}

twn::PanelData* twn::TownSugorokuInfo::getExtraBackLink(unsigned short uid)
{
    for (int i = 0; i < EXTRA_BACK_COUNT; i++) {
        if (uid == extraUid_[i]) {
            return extraBack_[i];
        }
    }
    return NULL;
}

twn::TownSugorokuInfo twn::g_SugorokuInfo;
