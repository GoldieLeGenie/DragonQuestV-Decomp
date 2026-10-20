#pragma ipa file
#include "ov028/sugoroku/TownSugorokuCommand.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownSugorokuManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkMatrix43.hpp"
#include "main/dss/UnkModelMember.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/global/Global.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/text/TextAPI.hpp"
#include "main/town/TownSugorokuInfo.hpp"
#include "main/window/NormalControl.hpp"
#include "main/window/ShopMenuControl.hpp"

#pragma thumb on

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline unsigned int status::BasePartyStatus::getGold()
{
    return gold_;
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

inline menu::MenuBase::MENUBASE_STAT menu::MenuBase::getStat()
{
    return stat_;
}

inline void MaterielMenu_WINDOW_MANAGER::setExtraInnType(int type)
{
    extraInnType_ = type;
}

inline void TownCamera::setPrevChange(bool flag)
{
    notEqualPreAngle_ = flag;
}

inline void TownCamera::setAreaTarget(dss::Fix32Vector3& pos)
{
    target_ = pos;
}

inline bool TownCamera::isEndMotion()
{
    return cameraMove_.isEnd();
}

inline void TownCamera::setCameraRemote(int mode)
{
    remote_ = mode;
}

inline void twn::TownPlayerManager::setAnimation(int flag)
{
    partyDraw_.setAnimation(flag);
}

inline void twn::TownPlayerManager::setMapLink(bool flag)
{
    flagMapLink_ = flag;
}

inline int twn::TownPlayerAction::getPadInput()
{
    return padInput_;
}

inline int twn::TownPlayerAction::getDirInput()
{
    return dirInput_;
}

inline int twn::TownPlayerManager::getPadInput()
{
    return player_.getPadInput();
}

inline int twn::TownPlayerManager::getDirInput()
{
    return player_.getDirInput();
}

inline unsigned short twn::PanelData::getUid()
{
    return uid_;
}

inline unsigned short twn::PanelData::getPanelID()
{
    return panelID_;
}

inline dss::Fix32Vector3& twn::PanelData::getPos()
{
    return pos_;
}

inline twn::PanelData* twn::PanelData::getLinkPanel(int no)
{
    return link_[no];
}

inline twn::PanelData* twn::PanelData::getRevercePanel()
{
    return reverce_[0];
}

inline twn::PanelData* twn::PanelData::getBackPanel1()
{
    return reverce_[1];
}

inline twn::PanelData* twn::PanelData::getBackPanel2()
{
    return reverce_[2];
}

inline twn::PanelData* twn::PanelData::getLoopPanel()
{
    return loopPanel_;
}

inline unsigned short twn::PanelData::getPanelAttr()
{
    return attr_;
}

inline unsigned short twn::PanelData::getWarpMapNo()
{
    return warpMapNo_;
}

inline unsigned short twn::PanelData::getWarpPanelUid()
{
    return warpUid_;
}

inline twn::PanelData* twn::TownSugorokuInfo::getNowPane()
{
    return nowPanel;
}

inline int twn::TownSugorokuInfo::getPanelNum()
{
    return panelNum_;
}

inline int twn::TownSugorokuInfo::getPanelUidByIndex(int index)
{
    return panel_[index].getUid();
}

inline int twn::TownSugorokuInfo::getPanelIDByIndex(int index)
{
    return panel_[index].getPanelID();
}

inline dss::Fix32Vector3& twn::TownSugorokuInfo::getPanelPosByIndex(int index)
{
    return panel_[index].getPos();
}

inline void twn::TownSugorokuInfo::setNowPanel(int index)
{
    nowPanel = &panel_[index];
}

inline void twn::TownSugorokuInfo::setNowPanel(PanelData* data)
{
    nowPanel = data;
}

inline twn::PanelData* twn::TownSugorokuInfo::getLastMovePanel()
{
    return diceMovePanel_[count_ - 1];
}

inline char twn::TownSugorokuInfo::getNowMoveCount()
{
    return nowMoveCount;
}

inline void twn::TownSugorokuInfo::setNowMoveCount(char count)
{
    nowMoveCount = count;
}

inline void twn::TownSugorokuInfo::setOrgMoveCount(char count)
{
    orgMoveCount_ = count;
}

inline char twn::TownSugorokuInfo::getDebugOrgMoveCount()
{
    return debugOrgMoveCount_;
}

inline void twn::TownSugorokuInfo::setDebugOrgMoveCount(char count)
{
    debugOrgMoveCount_ = count;
}

inline int twn::TownSugorokuInfo::getDiceCount()
{
    return diceCount_;
}

inline unsigned short twn::TownSugorokuInfo::getChanceCardID()
{
    return chanceCardID_;
}

inline void twn::TownSugorokuInfo::setChanceCardID(unsigned short id)
{
    chanceCardID_ = id;
}

inline int twn::TownSugorokuInfo::getDiceLimit()
{
    return diceLimit_;
}

inline char twn::TownSugorokuInfo::downDiceLimitCount()
{
    diceLimitCount_--;
    return diceLimitCount_;
}

inline void twn::TownSugorokuInfo::setDiceLimit(bool flag)
{
    diceLimit_ = flag;
    if (flag == true) {
        diceLimitCount_ = 3;
    }
}

inline int twn::TownSugorokuInfo::getDiceControlFlag()
{
    return diceControlFlag_;
}

inline void twn::TownSugorokuInfo::setDiceControlFlag(bool flag)
{
    diceControlFlag_ = flag;
}

inline int twn::TownSugorokuInfo::isReverce()
{
    return reverce_;
}

inline void twn::TownSugorokuInfo::setRevece(bool flag)
{
    reverce_ = flag;
}

inline int twn::TownSugorokuInfo::isBack()
{
    return back_;
}

inline void twn::TownSugorokuInfo::setBack(bool flag)
{
    back_ = flag;
}

inline int twn::TownSugorokuInfo::isBackReverce()
{
    return backReverce_;
}

inline void twn::TownSugorokuInfo::setBackReverce(bool flag)
{
    backReverce_ = flag;
}

inline int twn::TownSugorokuInfo::getMenuState()
{
    return menuState_;
}

inline void twn::TownSugorokuInfo::setContinue(int state)
{
    continueState_ = state;
}

inline void twn::TownSugorokuInfo::setNextMapPanelUid(unsigned short uid)
{
    nextPanelUid_ = uid;
}

inline void twn::TownSugorokuInfo::setStartPanelMapId(int id)
{
    startPanelMapId_ = id;
}

inline int twn::TownSugorokuInfo::getStartPanelMapId()
{
    return startPanelMapId_;
}

inline void twn::TownSugorokuInfo::setStartPanelUid(int uid)
{
    startPanelUid_ = uid;
}

inline int twn::TownSugorokuInfo::getStartPanelUid()
{
    return startPanelUid_;
}

inline dss::Fix32Vector3 twn::TownSugorokuInfo::getFallPosition()
{
    return fallPosition_;
}

inline int twn::TownSugorokuInfo::getFallMapId()
{
    return fallMapId_;
}

inline twn::PanelData& twn::TownSugorokuInfo::getLastPanel()
{
    return lastPanel_;
}

inline void twn::TownSugorokuInfo::setSugorokuEndMode(int type)
{
    sugorokuEndMode_ = type;
}

inline void twn::TownSugorokuInfo::setTrgMap(int map)
{
    trgMap_ = map;
}

inline int twn::TownSugorokuInfo::getTrgMap()
{
    return trgMap_;
}

inline void twn::TownSugorokuInfo::setTrgUid(int uid)
{
    trgUid_ = uid;
}

inline int twn::TownSugorokuInfo::getTrgUid()
{
    return trgUid_;
}

inline int twn::TownSugorokuInfo::isMoveStart()
{
    return moveStart_;
}

inline void twn::TownSugorokuInfo::setPrevMapNameId(int id)
{
    prevMapNameId_ = id;
}

inline void twn::TownSugorokuInfo::setPrevMapLastUid(int id)
{
    prevMapLastUid_ = id;
}

inline int twn::TownSugorokuInfo::getPrevMapNameId()
{
    return prevMapNameId_;
}

inline int twn::TownSugorokuInfo::getPrevMapLastUid()
{
    return prevMapLastUid_;
}

inline void twn::TownSugorokuInfo::setTime(int time)
{
    timeCount_ = time;
}

inline int twn::TownSugorokuInfo::getTime()
{
    return timeCount_;
}

inline void twn::TownSugorokuInfo::decTimer()
{
    timeCount_--;
}

inline void twn::TownSugorokuInfo::setGateNextPayOff(bool flag)
{
    nextPayOff_ = flag;
}

inline int twn::TownSugorokuInfo::isGateNextPayOff()
{
    return nextPayOff_;
}

inline int twn::TownSugorokuManager::getStageNo()
{
    return stageNO_;
}

inline int twn::TownSugorokuManager::getStageOffset()
{
    return stageOffset_;
}

inline void twn::TownSugorokuManager::setDrawDiceFreeOneFrame(int dice)
{
    drawDiceNo_ = dice;
}

inline int twn::TownSugorokuManager::getTurnEnd()
{
    return turnEnd_;
}

inline void twn::TownSugorokuManager::setTurnEnd(bool flag)
{
    turnEnd_ = flag;
}

inline void twn::TownSugorokuManager::setArrowIdx(int index, unsigned short idx)
{
    arrowIdx_[index] = idx;
}

inline void twn::TownSugorokuManager::setArrowPos(int index, dss::Fix32Vector3& pos)
{
    arrowPos[index] = pos;
}

inline void twn::TownSugorokuManager::setSugorokuTimeEnd(bool flag)
{
    sugorokuTime_ = flag;
}

inline void twn::TownSugorokuManager::setTreasuerRoom(bool flag)
{
    treasureRoom_ = flag;
}

void twn::SugorokuSystemDebugStart::setup()
{
    dss::Fix32Vector3 pos;
    TownPlayerManager::getSingleton().setLock(true);
    int max = g_SugorokuInfo.getPanelNum();
    for (int i = 0; i < max; i++) {
        int id = g_SugorokuInfo.getPanelIDByIndex(i);
        if (id == 0) {
            pos = g_SugorokuInfo.getPanelPosByIndex(i);
            g_SugorokuInfo.setNowPanel(i);
            g_SugorokuInfo.setStartPanelUid(g_SugorokuInfo.getNowPane()->getUid());
            g_SugorokuInfo.setStartPanelMapId(g_Global.getMapNameId());
            TownCamera::getSingleton()->resetAngle();
        }
    }
    dss::Fix32Vector3 vec = g_SugorokuInfo.getNowPane()->getLinkPanel(0)->getPos() - g_SugorokuInfo.getNowPane()->getPos();
    short dir;
    cmn::CommonCalculate::getIdxByVec(dir, vec);
    TownPlayerManager::getSingleton().setPosition(pos);
    TownPlayerManager::getSingleton().setDirection(dir);
    TownCamera::getSingleton()->resetAngle();
}

void twn::SugorokuSystemDebugStart::execute()
{
    TownCamera::getSingleton()->setPrevChange(true);
}

int twn::SugorokuSystemDebugStart::nextState()
{
    if (fadeEffector.isFadeEnd()) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemStart::setup()
{
    g_Global.fadeOutBlack(30, true);
    TownPlayerManager::getSingleton().setLock(true);
    cmn::g_cmnPartyInfo.setKeep(1, g_Global.getMapNameId(), true);
    state_ = 0;
}

void twn::SugorokuSystemStart::execute()
{
    if (state_ == 0 && fadeEffector.isFadeEnd()) {
        dss::Fix32Vector3 pos;
        g_Global.fadeInBlack(30);
        TownCamera::getSingleton()->resetAngle();
        int max = g_SugorokuInfo.getPanelNum();
        for (int i = 0; i < max; i++) {
            int id = g_SugorokuInfo.getPanelIDByIndex(i);
            if (id == 0) {
                pos = g_SugorokuInfo.getPanelPosByIndex(i);
                g_SugorokuInfo.setNowPanel(i);
                g_SugorokuInfo.setStartPanelUid(g_SugorokuInfo.getNowPane()->getUid());
                g_SugorokuInfo.setStartPanelMapId(g_Global.getMapNameId());
            }
        }
        TownPlayerManager::getSingleton().setPosition(pos);
        dss::Fix32Vector3 vec = g_SugorokuInfo.getNowPane()->getLinkPanel(0)->getPos() - g_SugorokuInfo.getNowPane()->getPos();
        short dir;
        cmn::CommonCalculate::getIdxByVec(dir, vec);
        TownPlayerManager::getSingleton().setDirection(dir);
        state_ = 1;
    }
}

int twn::SugorokuSystemStart::nextState()
{
    if (fadeEffector.isFadeEnd() && state_ == 1) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemPanelStart::setup()
{
    TownCamera::getSingleton()->resetAngle();
    int max = g_SugorokuInfo.getPanelNum();
    dss::Fix32Vector3 pos;
    int target = g_SugorokuInfo.nextPanelUid_;
    bool flag = false;
    for (int i = 0; i < max; i++) {
        int id = g_SugorokuInfo.getPanelUidByIndex(i);
        if (id == target) {
            pos = g_SugorokuInfo.getPanelPosByIndex(i);
            g_SugorokuInfo.setNowPanel(i);
            flag = true;
        }
    }
    if (flag == false) {
        pos = g_SugorokuInfo.getPanelPosByIndex(0);
        g_SugorokuInfo.setNowPanel(0);
    }
    dss::Fix32Vector3 vec;
    if (g_SugorokuInfo.getNowPane()->getPanelAttr() == 3) {
        if (g_SugorokuInfo.getLastPanel().getUid() == g_SugorokuInfo.getNowPane()->getLoopPanel()->getUid()) {
            vec = g_SugorokuInfo.getNowPane()->getLinkPanel(2)->getPos() - g_SugorokuInfo.getNowPane()->getPos();
        } else {
            vec = g_SugorokuInfo.getNowPane()->getLinkPanel(0)->getPos() - g_SugorokuInfo.getNowPane()->getPos();
        }
    } else {
        vec = g_SugorokuInfo.getNowPane()->getLinkPanel(0)->getPos() - g_SugorokuInfo.getNowPane()->getPos();
    }
    short dir;
    cmn::CommonCalculate::getIdxByVec(dir, vec);
    TownPlayerManager::getSingleton().setDirection(dir);
    TownPlayerManager::getSingleton().setLock(true);
    TownPlayerManager::getSingleton().setPosition(pos);
    switch (g_Global.getMapNameId()) {
    case 0x97:
    case 0x20a:
    case 0x21d:
    case 0x222:
    case 0x224:
        TownPlayerManager::getSingleton().resetDrawPartyCount();
        break;
    default:
        TownPlayerManager::getSingleton().setPartyDrawOne();
        break;
    }
    TownPlayerManager::getSingleton().setPartyDrawOne();
}

void twn::SugorokuSystemPanelStart::execute()
{
    TownCamera::getSingleton()->setPrevChange(true);
}

int twn::SugorokuSystemPanelStart::nextState()
{
    if (fadeEffector.isFadeEnd()) {
        if (g_SugorokuInfo.isMoveStart() == true && g_SugorokuInfo.getNowMoveCount() > 0) {
            return sugoroku::SYSTEM_MOVE;
        }
        if (TownSugorokuManager::getSingleton().flag_.check(TownSugorokuManager::START_INN) == true) {
            return sugoroku::PANEL_INN;
        }
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuOpenRootMenu::setup()
{
    next_ = 0;
    g_SugorokuInfo.setBackReverce(false);
    TownSugorokuManager::getSingleton().setDrawDiceNum(false);
    if (TownSugorokuManager::getSingleton().getTurnEnd() == true) {
        short idx = TownPlayerManager::getSingleton().getDirection();
        TownPlayerManager::getSingleton().setDirection(idx - 0x8000);
    }
    TownSugorokuManager::getSingleton().setTurnEnd(false);
    if (g_SugorokuInfo.getDiceCount() > 0 && status::g_Party.getGold() != 0 &&
        status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getHp() != 0) {
        g_SugorokuInfo.setChanceCardID(0);
        window::gShopMenuControl.startMenu(0x1f);
    }
}

void twn::SugorokuOpenRootMenu::execute()
{
}

int twn::SugorokuOpenRootMenu::nextState()
{
    if (next_ == 0) {
        if (status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getHp() == 0) {
            return sugoroku::SYSTEM_ABORT_END;
        }
        if (g_SugorokuInfo.getDiceCount() <= 0) {
            return sugoroku::SYSTEM_ABORT_END;
        }
        if (status::g_Party.getGold() == 0) {
            return sugoroku::SYSTEM_ABORT_END;
        }
        next_ = 1;
        return sugoroku::NOT_CHANGE_STATE;
    }
    switch (g_SugorokuInfo.getMenuState()) {
    case SUGOROKU_DICE:
        if (g_SugorokuInfo.getDiceControlFlag() == true) {
            return sugoroku::SYSTEM_DICE_CONTROL;
        }
        return sugoroku::SYSTEM_DICE;
    case SUGOROKU_CAMERA:
        return sugoroku::SYSTEM_CAMERA;
    case SUGOROKU_END:
        g_SugorokuInfo.setSugorokuEndMode(2);
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemDice::setup()
{
    int dice = g_SugorokuInfo.getDebugOrgMoveCount();
    if (dice == 0) {
        if (g_SugorokuInfo.getDiceLimit() == true) {
            dice = UnkDssRand::rand(3) + 1;
            if (g_SugorokuInfo.downDiceLimitCount() == 0) {
                g_SugorokuInfo.setDiceLimit(false);
            }
        } else {
            dice = UnkDssRand::rand(6) + 1;
        }
    }
    g_SugorokuInfo.setDebugOrgMoveCount(0);
    g_SugorokuInfo.setOrgMoveCount(dice);
    g_SugorokuInfo.setNowMoveCount(dice);
    TownSugorokuManager::getSingleton().diceThrowIn(dice);
}

void twn::SugorokuSystemDice::execute()
{
}

int twn::SugorokuSystemDice::nextState()
{
    if (TownSugorokuManager::getSingleton().isDiceAnimEnd() == true) {
        TownSugorokuManager::getSingleton().setDrawDiceNum(true);
        return sugoroku::SYSTEM_MOVE;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemPlayerMove::setup()
{
    move_ = false;
    end_ = false;
    count_ = 0;
    sinR_ = 0;
    return_ = false;
    g_SugorokuInfo.clearDiceMove();
    TownSugorokuManager::getSingleton().setDrawDiceNum(true);
    TownPlayerManager::getSingleton().setAnimation(1);
}

void twn::SugorokuSystemPlayerMove::execute()
{
    change_ = false;
    if (g_SugorokuInfo.getNowMoveCount() == 0) {
        if (TownPlayerManager::getSingleton().isFinish() == true) {
            TownSugorokuManager::getSingleton().setArrowDraw(0, false);
            TownSugorokuManager::getSingleton().setArrowDraw(1, false);
            end_ = true;
        }
        count_++;
    } else if (move_ == false) {
        count_ = 0;
        return_ = false;
        sugorokuArrowSet();
        window::gNormalControl.executePlayer();
        if (sugorokuMoveSet() == true) {
            move_ = true;
        }
    } else {
        if (TownPlayerManager::getSingleton().isFinish() == true) {
            int panel = g_SugorokuInfo.getNowPane()->getPanelID() + sugoroku::PANEL_STRAT;
            int num = g_SugorokuInfo.getNowMoveCount();
            if (g_SugorokuInfo.getNowPane()->getLinkPanel(0) == NULL) {
                if (panel == sugoroku::PANEL_KAIDAN_UP || panel == sugoroku::PANEL_KAIDAN_DOWN || panel == sugoroku::PANEL_SUGOROKU_DUNGEON) {
                    g_SugorokuInfo.setOrgMoveCount(num);
                    change_ = true;
                } else {
                    g_SugorokuInfo.setRevece(true);
                    g_SugorokuInfo.setOrgMoveCount(num);
                }
            }
            if (panel == sugoroku::PANEL_CHARGE_GATE && return_ == false) {
                gate_ = true;
            }
            move_ = false;
            sinR_ = 0;
        }
        count_++;
    }
    if (count_ >= 2) {
        TownSugorokuManager::getSingleton().setArrowDraw(0, false);
        TownSugorokuManager::getSingleton().setArrowDraw(1, false);
    }
}

bool twn::SugorokuSystemPlayerMove::sugorokuMoveSet()
{
    bool ret;
    int padInput = TownPlayerManager::getSingleton().getPadInput();
    if (padInput != 0) {
        unsigned short dirInput = TownPlayerManager::getSingleton().getDirInput();
        dss::Fix32Vector3 direction = TownCamera::getSingleton()->camera_.unk_004.getDirection();
        direction.vy = 0L;
        direction.normalize();
        dss::UnkMatrix43 mat;
        mat.unkfunc_0204f4ec(-dirInput);
        direction = mat * direction;
        direction.vy = 0L;
        dss::Vector3<short>& angle = TownCamera::getSingleton()->camera_.unk_004.getAngle();
        int idx = (short)(0x8000 - dirInput + angle.vy);
        short dirIdx = TownActionCalculate::getParamDir4ByIdx(idx);
        PanelData* data = g_SugorokuInfo.getNowPane();
        if (g_SugorokuInfo.isReverce() == true) {
            ret = sugorokuMove(data, data->getRevercePanel(), dirIdx, true);
            if (ret == true) {
                return ret;
            }
            if (g_SugorokuInfo.getPushCount() > 0) {
                PanelData* linkData = g_SugorokuInfo.getLastMovePanel();
                ret = sugorokuMove(data, linkData, dirIdx, false);
                if (ret == true) {
                    return ret;
                }
            }
            return false;
        }
        if (g_SugorokuInfo.getPushCount() > 0) {
            PanelData* linkData = g_SugorokuInfo.getLastMovePanel();
            ret = sugorokuMove(data, linkData, dirIdx, false);
            if (ret == true) {
                return ret;
            }
        }
        if (g_SugorokuInfo.isBack() && g_SugorokuInfo.isBackReverce() == false) {
            PanelData* linkData = data->getBackPanel1();
            if (data->getBackPanel2() != NULL) {
                if (g_SugorokuInfo.isExtraBackLink(data->getBackPanel2()->getUid()) == true) {
                    PanelData* temp = g_SugorokuInfo.getExtraBackLink(data->getBackPanel2()->getUid());
                    if (temp == data->getBackPanel2()) {
                        linkData = data->getBackPanel2();
                    }
                }
            }
            if (data->getPanelAttr() == 3 && data->getLoopPanel()->getUid() == g_SugorokuInfo.getLastPanel().getUid()) {
                if (g_SugorokuInfo.getPushCount() == 0) {
                    if (linkData->getUid() == data->getLinkPanel(2)->getUid()) {
                        linkData = data->getLinkPanel(0);
                    }
                } else {
                    if (linkData->getUid() == data->getLinkPanel(0)->getUid()) {
                        linkData = data->getLinkPanel(0);
                    }
                }
            }
            ret = sugorokuMove(data, linkData, dirIdx, true);
            if (g_SugorokuInfo.getNowPane()->getPanelAttr() == 3 && g_SugorokuInfo.getNowMoveCount() == 0 && ret == true) {
                if (g_SugorokuInfo.getNowPane()->getLoopPanel()->getUid() == data->getUid()) {
                    g_SugorokuInfo.pushDiceMovePanel(g_SugorokuInfo.getNowPane()->getLinkPanel(2));
                } else {
                    g_SugorokuInfo.pushDiceMovePanel(g_SugorokuInfo.getNowPane()->getLinkPanel(0));
                }
            }
            return ret;
        }
        if (data->getPanelAttr() == 3) {
            if (data->getLoopPanel() != NULL) {
                if (data->getLoopPanel()->getUid() == g_SugorokuInfo.getLastPanel().getUid()) {
                    ret = sugorokuMove(data, data->getLinkPanel(2), dirIdx, true);
                    if (ret == true) {
                        return ret;
                    }
                } else {
                    for (int i = 0; i < 2; i++) {
                        if (data->getLinkPanel(i) != NULL && data->getLinkPanel(i)->getUid() != g_SugorokuInfo.getLastPanel().getUid()) {
                            ret = sugorokuMove(data, data->getLinkPanel(i), dirIdx, true);
                            if (ret == true) {
                                return ret;
                            }
                        }
                    }
                }
            }
            return false;
        }
        for (int i = 0; i < 2; i++) {
            ret = sugorokuMove(data, data->getLinkPanel(i), dirIdx, true);
            if (ret == true) {
                return ret;
            }
        }
    }
    return false;
}

bool twn::SugorokuSystemPlayerMove::sugorokuMove(PanelData* data, PanelData* linkData, short dirIdx, int flag)
{
    if (linkData != NULL) {
        dss::Fix32Vector3 ppos = TownPlayerManager::getSingleton().getPosition();
        dss::Fix32Vector3 pos = linkData->getPos();
        dss::Fix32Vector3 vec = pos - ppos;
        short idx;
        cmn::CommonCalculate::getIdxByVec(idx, vec);
        idx = TownActionCalculate::getParamDir4ByIdx(idx);
        int nowPane = g_SugorokuInfo.getNowPane()->getPanelID();
        if (idx == dirIdx) {
            TownPlayerManager::getSingleton().setSimpleMove(ppos, pos, 20);
            g_SugorokuInfo.setNowPanel(linkData);
            if (flag == true) {
                g_SugorokuInfo.pushDiceMovePanel(data);
                SoundManager::playSe(0x15b, 0);
            } else {
                return_ = true;
                if (nowPane + sugoroku::PANEL_STRAT == sugoroku::PANEL_CHARGE_GATE) {
                    gate_ = false;
                }
                g_SugorokuInfo.popDiceMovePanel();
                SoundManager::playSe(0x15c, 0);
            }
            return true;
        }
    }
    return false;
}

void twn::SugorokuSystemPlayerMove::sugorokuArrowSet()
{
    static fx32 sin[12] = {0x0, 0x424, 0x800, 0xb50, 0xddb, 0xf74, 0x1000, 0xf74, 0xddb, 0xb50, 0x800, 0x424};
    dss::Fix32 fix;
    PanelData* nextPanel[2] = {NULL, NULL};
    for (int i = 0; i < 2; i++) {
        nextPanel[i] = NULL;
    }
    dss::Fix32Vector3 nextPos, nowPos;
    PanelData* panel = g_SugorokuInfo.getNowPane();
    nowPos = panel->getPos();
    if (g_SugorokuInfo.isReverce()) {
        nextPanel[0] = panel->getRevercePanel();
    } else if (g_SugorokuInfo.isBack() && g_SugorokuInfo.isBackReverce() == false) {
        nextPanel[0] = panel->getBackPanel1();
        if (panel->getBackPanel2() != NULL && g_SugorokuInfo.isExtraBackLink(panel->getBackPanel2()->getUid()) == true) {
            PanelData* temp = g_SugorokuInfo.getExtraBackLink(panel->getBackPanel2()->getUid());
            if (temp == panel->getBackPanel2()) {
                nextPanel[0] = panel->getBackPanel2();
            }
        }
        if (panel->getPanelAttr() == 3 && panel->getLoopPanel()->getUid() == g_SugorokuInfo.getLastPanel().getUid() &&
            g_SugorokuInfo.getPushCount() == 0 && nextPanel[0]->getUid() == panel->getLinkPanel(2)->getUid()) {
            nextPanel[0] = panel->getLinkPanel(0);
        }
    } else if (panel->getPanelAttr() == 3) {
        if (panel->getLoopPanel() != NULL) {
            if (panel->getLoopPanel()->getUid() == g_SugorokuInfo.getLastPanel().getUid()) {
                nextPanel[0] = panel->getLinkPanel(2);
            } else {
                for (int i = 0; i < 2; i++) {
                    if (panel->getLinkPanel(i) != NULL && g_SugorokuInfo.getLastPanel().getUid() != panel->getLinkPanel(i)->getUid()) {
                        nextPanel[i] = panel->getLinkPanel(i);
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < 2; i++) {
            nextPanel[i] = panel->getLinkPanel(i);
        }
    }
    for (int i = 0; i < 2; i++) {
        if (nextPanel[i] != NULL) {
            short idx;
            nextPos = nextPanel[i]->getPos();
            dss::Fix32Vector3 vec = nowPos - nextPos;
            cmn::CommonCalculate::getIdxByVec(idx, vec);
            nextPos.vy.value += 0x555;
            fix.value = sin[(sinR_ / 8) % 12] / 4;
            nextPos += vec / 3 - vec * fix;
            TownSugorokuManager::getSingleton().setArrowIdx(i, idx);
            TownSugorokuManager::getSingleton().setArrowPos(i, nextPos);
            TownSugorokuManager::getSingleton().setArrowDraw(i, true);
        } else {
            TownSugorokuManager::getSingleton().setArrowDraw(i, false);
        }
    }
    sinR_++;
}

int twn::SugorokuSystemPlayerMove::nextState()
{
    int panel = g_SugorokuInfo.getNowPane()->getPanelID();
    if (g_SugorokuInfo.isBack() == true && move_ == false && g_SugorokuInfo.getNowPane()->getBackPanel1() == NULL) {
        return sugoroku::SYSTEM_PANEL_LINK;
    }
    if (gate_ == 1) {
        TextAPI::setMACRO0(0x69, 0xf0000000, 500);
        TownWindowSystem::getSingleton().openSystemMessage(0xca684, 1);
        MaterielMenu_WINDOW_MANAGER::getSingleton()->openBasicMenu(0);
        gate_ = 2;
        return sugoroku::NOT_CHANGE_STATE;
    }
    if (end_ == true && gate_ != 4 && panel + sugoroku::PANEL_STRAT == sugoroku::PANEL_CHARGE_GATE) {
        TextAPI::setMACRO0(0x69, 0xf0000000, 500);
        TownWindowSystem::getSingleton().openSystemMessage(0xca684, 1);
        MaterielMenu_WINDOW_MANAGER::getSingleton()->openBasicMenu(0);
        g_SugorokuInfo.setGateNextPayOff(true);
        gate_ = 4;
        return sugoroku::NOT_CHANGE_STATE;
    }
    if (gate_ == 2) {
        gate_ = 3;
    }
    if (change_ == true) {
        SoundManager::playSe(0x131, 0);
        return sugoroku::SYSTEM_PANEL_LINK;
    }
    if (end_ == true) {
        if (g_SugorokuInfo.isReverce() == true) {
            TownSugorokuManager::getSingleton().setTurnEnd(true);
            g_SugorokuInfo.setBackReverce(true);
        }
        if (g_SugorokuInfo.isBack()) {
            TownSugorokuManager::getSingleton().setTurnEnd(true);
        }
        g_SugorokuInfo.setRevece(false);
        if (gate_ == 3 || (gate_ != 4 && g_SugorokuInfo.isGateNextPayOff())) {
            g_SugorokuInfo.setGateNextPayOff(false);
            TextAPI::setMACRO0(0x69, 0xf0000000, 500);
            TownWindowSystem::getSingleton().openSystemMessage(0xca687, 1);
            MaterielMenu_WINDOW_MANAGER::getSingleton()->openBasicMenu(0);
            int gold = status::g_Party.getGold() - 500;
            if (gold < 0) {
                gold = 0;
            }
            status::g_Party.setGold(gold);
            gate_ = 4;
            if (gold == 0) {
                return sugoroku::SYSTEM_ABORT_END;
            }
            return sugoroku::NOT_CHANGE_STATE;
        }
        if (gate_ == 4) {
            gate_ = 0;
        }
        g_SugorokuInfo.moveBackup();
        TownSugorokuManager::getSingleton().setDrawDiceNum(false);
        g_SugorokuInfo.setBack(false);
        return panel + sugoroku::PANEL_STRAT;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelFinish::setup()
{
    g_SugorokuInfo.setSugorokuEndMode(1);
    cmn::g_cmnSoundManager.setPlaySound(9, false);
    counter_ = 0;
}

void twn::SugorokuPanelFinish::execute()
{
    counter_++;
}

int twn::SugorokuPanelFinish::nextState()
{
    return -(counter_ >= 10);
}

void twn::SugorokuSystemCameraMove::setup()
{
    TownPlayerManager::getSingleton().setLock(true);
    TownCamera::getSingleton()->setCameraAreaMove(true);
    dss::Fix32Vector3 pos = TownPlayerManager::getSingleton().getPosition();
    TownCamera::getSingleton()->setAreaTarget(pos);
}

void twn::SugorokuSystemCameraMove::execute()
{
    window::gNormalControl.executePlayer();
    short idx;
    dss::Fix32Vector3 target = TownCamera::getSingleton()->target_;
    TownActionCalculate::normalMove(target, idx, TownPlayerAction::walkSpeed);
    TownCamera::getSingleton()->setAreaTarget(target);
}

int twn::SugorokuSystemCameraMove::nextState()
{
    if (dss::g_Pad.edge() & 2) {
        return sugoroku::SYSTEM_CAMERA_END;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemCameraEnd::setup()
{
    TownCamera::getSingleton()->setMoveTargetPlayer(60);
}

void twn::SugorokuSystemCameraEnd::execute()
{
}

int twn::SugorokuSystemCameraEnd::nextState()
{
    if (TownCamera::getSingleton()->isEndMotion() == true) {
        TownPlayerManager::getSingleton().setLock(false);
        TownCamera::getSingleton()->setCameraLock(0);
        TownCamera::getSingleton()->setCameraRemote(0);
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemFadeOutEnd::setup()
{
    cmn::g_extraMapLink.setExtraLinkTown(g_SugorokuInfo.getEndMapNameId(), g_SugorokuInfo.getEndMapPosition(), g_SugorokuInfo.getEndMapDirIdx());
}

void twn::SugorokuSystemFadeOutEnd::execute()
{
}

int twn::SugorokuSystemFadeOutEnd::nextState()
{
    return sugoroku::NOT_SUGOROKU_MODE;
}

void twn::SugorokuSystemPanelLink::setup()
{
    int map;
    int uid;
    int panel = g_SugorokuInfo.getNowPane()->getPanelID() + sugoroku::PANEL_STRAT;
    dss::Fix32Vector3 pos = g_SugorokuInfo.getFallPosition();
    switch (panel) {
    case sugoroku::PANEL_FALL_OUT:
        map = g_SugorokuInfo.getNowPane()->getWarpMapNo();
        uid = g_SugorokuInfo.getNowPane()->getWarpPanelUid();
        if (uid != 0) {
            g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_FALL);
        } else {
            g_SugorokuInfo.setContinue(TownSugorokuInfo::NOT_SUGOROKU);
            pos = g_SugorokuInfo.getFallPosition();
            g_SugorokuInfo.setSugorokuEndMode(6);
        }
        SoundManager::playSe(0x138, 0);
        break;
    case sugoroku::PANEL_SUGOROKU_DUNGEON:
        TownSugorokuManager::getSingleton().getSugorokuDungeonData(map, uid);
        break;
    case sugoroku::PANEL_BACK_TO_START:
        map = g_SugorokuInfo.getStartPanelMapId();
        uid = g_SugorokuInfo.getStartPanelUid();
        g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_STRAT);
        break;
    case sugoroku::PANEL_CHANCE_CARD: {
        int chance = g_SugorokuInfo.getChanceCardID() + sugoroku::PANEL_TREASUER_BOX_OPEN;
        switch (chance) {
        case sugoroku::CHANCE_HOLE_TRAP:
            map = g_SugorokuInfo.getFallMapId();
            pos = g_SugorokuInfo.getFallPosition();
            g_SugorokuInfo.setSugorokuEndMode(6);
            SoundManager::playSe(0x138, 0);
            break;
        case sugoroku::CHANCE_BACK_TO_START:
            map = g_SugorokuInfo.getStartPanelMapId();
            uid = g_SugorokuInfo.getStartPanelUid();
            g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_STRAT);
            break;
        case sugoroku::CHANCE_INN:
            changeInn(map, uid);
            g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_INN);
            break;
        case sugoroku::CHANCE_TREASUER_ROOM:
            setTreasuerRoom();
            return;
        }
        break;
    }
    case sugoroku::PANEL_FLAT:
    case sugoroku::PANEL_FOREST:
    case sugoroku::PANEL_MOUNTAIN:
        map = g_SugorokuInfo.getFallMapId();
        pos = g_SugorokuInfo.getFallPosition();
        g_SugorokuInfo.setSugorokuEndMode(6);
        SoundManager::playSe(0x138, 0);
        break;
    case sugoroku::PANEL_KAIDAN_UP:
    case sugoroku::PANEL_KAIDAN_DOWN:
        map = g_SugorokuInfo.getNowPane()->getWarpMapNo();
        uid = g_SugorokuInfo.getNowPane()->getWarpPanelUid();
        g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_MOVE);
        break;
    case sugoroku::PANEL_TREASUER_ROOM:
        setTreasuerRoom();
        return;
    default:
        map = g_SugorokuInfo.getNowPane()->getWarpMapNo();
        uid = g_SugorokuInfo.getNowPane()->getWarpPanelUid();
        if (uid != 0) {
            g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_FALL);
        } else {
            g_SugorokuInfo.setSugorokuEndMode(6);
        }
        break;
    }
    if (g_SugorokuInfo.isBack() == true && g_SugorokuInfo.getNowPane()->getWarpMapNo() == 0) {
        map = g_SugorokuInfo.getPrevMapNameId();
        uid = g_SugorokuInfo.getPrevMapLastUid();
        g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_MOVE);
    }
    g_SugorokuInfo.setPrevMapNameId(g_Global.getMapNameId());
    g_SugorokuInfo.setPrevMapLastUid(g_SugorokuInfo.getNowPane()->getUid());
    cmn::g_extraMapLink.setExtraLinkTown(map, pos, 0);
    g_SugorokuInfo.setNextMapPanelUid(uid);
}

void twn::SugorokuSystemPanelLink::setTreasuerRoom()
{
    dss::Fix32Vector3 pos;
    int map;
    g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_TREASURE_PRE_ROOM);
    g_SugorokuInfo.setTrgMap(g_Global.getMapNameId());
    g_SugorokuInfo.setTrgUid(g_SugorokuInfo.getNowPane()->getUid());
    TownPlayerManager::getSingleton().getDirection();
    switch (TownSugorokuManager::getSingleton().getStageNo()) {
    case 3:
        map = 0x20e;
        break;
    case 4:
        map = 0x212;
        break;
    case 5:
        map = 0x217;
        break;
    default:
        map = 0x20e;
        break;
    }
    pos.vx.value = 0x1800;
    pos.vy.value = 0;
    pos.vz.value = 0x1000;
    cmn::g_extraMapLink.setExtraLinkTown(map, pos, 0);
}

void twn::SugorokuSystemPanelLink::changeInn(int& map, int& uid)
{
    int count = g_SugorokuInfo.getPanelNum();
    int tuid = 0;
    for (int i = 0; i < count; i++) {
        PanelData* panel = &g_SugorokuInfo.panel_[i];
        if (panel->getPanelID() + sugoroku::PANEL_STRAT == sugoroku::PANEL_INN) {
            if (tuid == 0 || dss::abs(g_SugorokuInfo.getNowPane()->getUid() - tuid) > dss::abs(panel->getUid() - g_SugorokuInfo.getNowPane()->getUid())) {
                tuid = panel->getUid();
            }
        }
    }

    if (tuid != 0) {
        uid = tuid;
        map = g_Global.getMapNameId();
        return;
    }
    switch (g_Global.getMapNameId()) {
    case 0x20a:
    case 0x20b:
        map = 0x20b;
        uid = 0x7577;
        break;
    case 0x222:
    case 0x223:
        map = 0x223;
        uid = 0x7696;
        break;
    default:
        map = g_Global.getMapNameId();
        break;
    }
}

void twn::SugorokuSystemPanelLink::execute()
{
}

int twn::SugorokuSystemPanelLink::nextState()
{
    return sugoroku::NOT_SUGOROKU_MODE;
}

void twn::SugorokuSystemFadeOutNextShop::setup()
{
    g_Global.fadeOutBlack(30, true);
}

void twn::SugorokuSystemFadeOutNextShop::execute()
{
}

int twn::SugorokuSystemFadeOutNextShop::nextState()
{
    if (fadeEffector.isFadeEnd() == true) {
        return sugoroku::SYSTEM_FADE_IN_NEXT_SHOP;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemFadeInNextShop::setup()
{
    g_Global.fadeInBlack(30);
    int no = g_SugorokuInfo.getNowPane()->getPanelID() + sugoroku::PANEL_STRAT;
    switch (no) {
    case sugoroku::PANEL_INN:
        TownSugorokuManager::getSingleton().setShopDraw(0);
        break;
    case sugoroku::PANEL_SHOP:
        TownSugorokuManager::getSingleton().setShopDraw(1);
        break;
    }
}

void twn::SugorokuSystemFadeInNextShop::execute()
{
}

int twn::SugorokuSystemFadeInNextShop::nextState()
{
    if (fadeEffector.isFadeEnd() == true) {
        return sugoroku::SYSTEM_SHOP_OPEN;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemShopOpen::setup()
{
    int no = g_SugorokuInfo.getNowPane()->getPanelID() + sugoroku::PANEL_STRAT;
    switch (no) {
    case sugoroku::PANEL_INN:
        window::gShopMenuControl.startMenu(0x20);
        MaterielMenu_WINDOW_MANAGER::getSingleton()->setExtraInnType(2);
        break;
    case sugoroku::PANEL_SHOP:
        window::gShopMenuControl.startMenu(0x21);
        break;
    }
}

void twn::SugorokuSystemShopOpen::execute()
{
}

int twn::SugorokuSystemShopOpen::nextState()
{
    if (window::gShopMenuControl.isMenuEnd()) {
        return sugoroku::SYSTEM_FADE_OUT_NEXT_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemFadeOutNextMenu::setup()
{
    g_Global.fadeOutBlack(30, true);
}

void twn::SugorokuSystemFadeOutNextMenu::execute()
{
}

int twn::SugorokuSystemFadeOutNextMenu::nextState()
{
    if (fadeEffector.isFadeEnd() == true) {
        TownSugorokuManager::getSingleton().clearShopDraw();
        return sugoroku::SYSTEM_FADE_IN_NEXT_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemFadeInNextMenu::setup()
{
    g_Global.fadeInBlack(30);
}

void twn::SugorokuSystemFadeInNextMenu::execute()
{
}

int twn::SugorokuSystemFadeInNextMenu::nextState()
{
    if (fadeEffector.isFadeEnd() == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemAbortEnd::setup()
{
    start_ = false;
    if (status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getHp() == 0) {
        g_SugorokuInfo.setSugorokuEndMode(5);
        status::g_Party.getPlayerStatus(0).getHaveStatusInfo().setHp(1);
        start_ = true;
    } else if (g_SugorokuInfo.getDiceCount() <= 0) {
        g_SugorokuInfo.setSugorokuEndMode(3);
        TownWindowSystem::getSingleton().openSystemMessage(0xc9e9e, 1);
    } else if (status::g_Party.getGold() == 0) {
        g_SugorokuInfo.setSugorokuEndMode(4);
        TownWindowSystem::getSingleton().openSystemMessage(0xc9ea4, 1);
    }
}

void twn::SugorokuSystemAbortEnd::execute()
{
}

int twn::SugorokuSystemAbortEnd::nextState()
{
    if (start_ == true) {
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    start_ = true;
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemDiceControl::setup()
{
    count_ = 0;
    dice_ = 1;
    isEnd_ = false;
    TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(dice_);
    g_SugorokuInfo.setDiceControlFlag(false);
    SoundManager::playSe(0x15a, 0);
}

void twn::SugorokuSystemDiceControl::execute()
{
    if ((dss::g_Pad.edge() & 1) || (dss::g_Pad.edge() & 0x400)) {
        isEnd_ = true;
        g_SugorokuInfo.setDebugOrgMoveCount(0);
        g_SugorokuInfo.setOrgMoveCount(dice_);
        g_SugorokuInfo.setNowMoveCount(dice_);
    }
    if (count_ > 30) {
        count_ = 0;
        dice_++;
        if (dice_ > 6) {
            dice_ = 1;
        }
        TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(dice_);
    }
    count_++;
}

int twn::SugorokuSystemDiceControl::nextState()
{
    if (isEnd_ == true) {
        TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(0);
        SoundManager::stopSeWithIndex(0x15a, 0);
        return sugoroku::SYSTEM_MOVE;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemTreasureRoomLink::setup()
{
}

void twn::SugorokuSystemTreasureRoomLink::execute()
{
}

int twn::SugorokuSystemTreasureRoomLink::nextState()
{
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemTreasureRoomMove::setup()
{
}

void twn::SugorokuSystemTreasureRoomMove::execute()
{
    TownPlayerManager::getSingleton().setMapLink(true);
    g_SugorokuInfo.decTimer();
}

int twn::SugorokuSystemTreasureRoomMove::nextState()
{
    int surface = TownStageManager::getSingleton()->getHitSurfaceIdByType(1);
    if (surface != -1) {
        if (flag_ == false) {
            flag_ = true;
            return sugoroku::SYSTEM_TORESURE_ROOM_END_MESSAGE;
        }
    } else {
        flag_ = false;
    }
    if (g_SugorokuInfo.getTime() <= 0) {
        TownWindowSystem::getSingleton().openSystemMessage(0xc9eb9, 1);
        return sugoroku::SYSTEM_TREASURE_ROOM_END;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemTreasureRoomEnd::setup()
{
    int map = g_SugorokuInfo.getTrgMap();
    int uid = g_SugorokuInfo.getTrgUid();
    short idx = TownPlayerManager::getSingleton().getDirection();
    dss::Fix32Vector3 pos(0, 0, 0);
    cmn::g_extraMapLink.setExtraLinkTown(map, pos, idx);
    g_SugorokuInfo.setNextMapPanelUid(uid);
    g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_FALL);
    TownSugorokuManager::getSingleton().setDrawTimer(false);
    SoundManager::playSe(0x131, 0);
}

void twn::SugorokuSystemTreasureRoomEnd::execute()
{
}

int twn::SugorokuSystemTreasureRoomEnd::nextState()
{
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemTreasureRoomEndMessage::setup()
{
    TownSugorokuManager::getSingleton().setDrawTimer(false);
    TownWindowSystem::getSingleton().openSystemMessage(0xc9eb6, 1);
    gTownMenu_MESSAGE.setYesNo();
    mode_ = MODE_MESSAGE;
}

void twn::SugorokuSystemTreasureRoomEndMessage::execute()
{
    TownPlayerManager::getSingleton().setMapLink(true);
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        mode_ = MODE_YES;
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        mode_ = MODE_NO;
        TownSugorokuManager::getSingleton().setDrawTimer(true);
    }
}

int twn::SugorokuSystemTreasureRoomEndMessage::nextState()
{
    if (mode_ == MODE_YES) {
        return sugoroku::SYSTEM_TREASURE_ROOM_END;
    }
    if (mode_ == MODE_NO) {
        return sugoroku::SYSTEM_TREASURE_ROOM_MOVE;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemTreasureRoomSetTime::setup()
{
    TownPlayerManager::getSingleton().setLock(true);
    g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_TREASURE_ROOM);
    int ctrlID = cmn::g_cmnPartyInfo.ctrlID_;
    if (ctrlID != -1) {
        ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
    } else {
        ui_MsgSndSet(0x32);
    }
    int mes = 0;
    switch (g_Global.getMapNameId()) {
    case 0x20e:
        mes = 0xc9ec5;
        break;
    case 0x212:
        mes = 0xc9ec0;
        break;
    case 0x217:
        mes = 0xc9eb1;
        break;
    }
    TownWindowSystem::getSingleton().openTalkMessage(mes, 3);
    mode_ = MODE_FIRST_DICE;
    time_ = 0;
    isEnd_ = false;
}

void twn::SugorokuSystemTreasureRoomSetTime::execute()
{
    if (TownWindowSystem::getSingleton().isMessageStart() == true) {
        return;
    }
    if (TownSugorokuManager::getSingleton().isDiceAnimEnd() == true) {
        switch (mode_) {
        case MODE_FIRST_DICE:
            drawDice_ = UnkDssRand::rand(6) + 1;
            time_ = drawDice_ * 10;
            TownSugorokuManager::getSingleton().diceThrowIn(drawDice_);
            mode_ = MODE_SECOND_DICE;
            break;
        case MODE_SECOND_DICE:
            TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(drawDice_);
            if ((dss::g_Pad.edge() & 1) || (dss::g_Pad.edge() & 0x400)) {
                TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(0);
                drawDice_ = UnkDssRand::rand(6) + 1;
                time_ += drawDice_;
                TownSugorokuManager::getSingleton().diceThrowIn(drawDice_);
                mode_ = MODE_MESSAGE;
            }
            break;
        case MODE_MESSAGE:
            TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(drawDice_);
            if ((dss::g_Pad.edge() & 1) || (dss::g_Pad.edge() & 0x400)) {
                TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(0);
                TextAPI::setMACRO0(0x71, 0xf0000000, time_);
                int mes = 0;
                switch (g_Global.getMapNameId()) {
                case 0x20e:
                    mes = 0xc9ec8;
                    break;
                case 0x212:
                    mes = 0xc9ec3;
                    break;
                case 0x217:
                    mes = 0xc9eb4;
                    break;
                }
                TownWindowSystem::getSingleton().openTalkMessage(mes, 1);
                mode_ = MODE_END;
            }
            break;
        case MODE_END:
            g_SugorokuInfo.setTime(time_ * 60);
            isEnd_ = true;
            break;
        }
    }
}

int twn::SugorokuSystemTreasureRoomSetTime::nextState()
{
    if (isEnd_ == true) {
        TownSugorokuManager::getSingleton().setSugorokuTimeEnd(true);
        TownPlayerManager::getSingleton().setLock(false);
        TownSugorokuManager::getSingleton().setTreasuerRoom(true);
        return sugoroku::SYSTEM_TREASURE_PRE_ROOM;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemTreasurePreRoom::setup()
{
}

void twn::SugorokuSystemTreasurePreRoom::execute()
{
}

int twn::SugorokuSystemTreasurePreRoom::nextState()
{
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuSystemBattleEnd::setup()
{
    NNSG3dResTex* tex = getLastModelTexture();
    dss::Fix32Vector3 rate(0, 0, 0);
    applyModelPaletteRgbRate(tex, rate);
    TownPlayerManager::getSingleton().setLock(true);
    cmn::g_extraMapLink.setExtraLinkTown(g_SugorokuInfo.getEndMapNameId(), g_SugorokuInfo.getEndMapPosition(), g_SugorokuInfo.getEndMapDirIdx());
}

void twn::SugorokuSystemBattleEnd::execute()
{
}

int twn::SugorokuSystemBattleEnd::nextState()
{
    return sugoroku::NOT_SUGOROKU_MODE;
}
