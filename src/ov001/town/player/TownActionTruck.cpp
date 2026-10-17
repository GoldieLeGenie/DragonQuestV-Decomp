#pragma ipa file
#include "ov001/town/player/TownActionTruck.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/global/Global.hpp"
#include "main/sound/SoundManager.hpp"

#pragma thumb on

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline cmn::MENU_ACTION cmn::CommonPartyInfo::getMenuAction()
{
    return menuAction_;
}

inline int cmn::CommonPartyInfo::getWagonUid()
{
    return wagonUid_;
}

inline void cmn::CommonPartyInfo::setWagonUid(int uid)
{
    wagonUid_ = uid;
}

inline void cmn::PartyMoveAction::setSpeed(dss::Fix32 speed)
{
    memberSpeed_ = speed;
}

inline void FldStage::setRotObjectUid(int uId, dss::Fix32Vector3& angle)
{
    m_fld.SetMapUidRotFX32(uId, (VecFx32*)&angle);
}

inline void twn::TownStageManager::setRotObjectUid(int uid, dss::Fix32Vector3& angle)
{
    stage_.setRotObjectUid(uid, angle);
}

inline int twn::TownStageManager::characoterColl(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos, dss::Fix32 rad, dss::Fix32Vector3* retVec, int flag)
{
    return coll_.characterColl(oldPos, newPos, rad, retVec, flag);
}

inline int twn::TownStageManager::eventAnim(int event, int objID)
{
    return stage_.eventAnim(event, objID);
}

inline bool twn::TownTruckRail::checkFlag(unsigned short flag)
{
    return flag_.check(flag);
}

inline short twn::TownTruckRail::getRoot()
{
    return root_;
}

inline short twn::TownTruckRail::getJumpMap()
{
    return jumpMap_;
}

inline short twn::TownTruckRail::getJumpIndex()
{
    return jumpIndex_;
}

inline twn::TownTruckRail& twn::TownTruckSystem::getRailByRailNo(int railNo)
{
    return rail_[railNo];
}

inline int twn::TownTruckSystem::getWagonCount()
{
    return wagonCount_;
}

inline void twn::TownTruckWagon::setMap(short map)
{
    map_ = map;
}

inline void twn::TownTruckWagon::setPos(dss::Fix32Vector3& pos)
{
    pos_ = pos;
}

inline void twn::TownTruckWagon::setIdx(short idx)
{
    idx_ = idx;
}

inline short twn::TownTruckWagon::getUid()
{
    return uid_;
}

const dss::Fix32 twn::TownActionTruck::truckSpeed((fx32)0x200);
const dss::Fix32 twn::TownActionTruck::truckSpeed2((fx32)0x266);
const dss::Fix32 twn::TownActionTruck::trainSpeed2((fx32)0x333);
const dss::Fix32 twn::TownActionTruck::slopeFx((fx32)0xc);
const dss::Fix32 twn::TownActionTruck::slopelen((fx32)0x4000);
const dss::Fix32 twn::TownActionTruck::trainR((fx32)0x168f);

int twn::TownActionTruck::setup()
{
    state_ = NONE;
    counter_ = 0;
    nowRailNo_ = 0;
    prevRailNo_ = 0;
    wagonUid_ = 0;
    scriptFlag_ = 0;
    seesaw_ = 0;
    trainUid_ = 0x1f5;
    scriptWagonUid_ = 0;
    scriptRail_ = 0;
    prevScriptRail_ = 0;
    scriptFlag_ = 0;
    trainRunSe_ = 0;
    waterSe_ = 0;
    wagonSe_ = 0;
    initRunSe_ = 0;
    initWatSe_ = 0;
    system_.initialize();
    if (cmn::g_cmnPartyInfo.getMenuAction() == cmn::TRUCK_LINK) {
        TownPlayerManager::getSingleton().setRemote(true);
        wagonUid_ = cmn::g_cmnPartyInfo.getWagonUid();
        firstMove();
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        initRunSe_ = 1;
        if (system_.getRailByRailNo(nowRailNo_).checkFlag(0x80) == true) {
            int index = getWaterEffectNo();
            dss::Fix32Vector3 pos = position_;
            pos.vy.value += 0x5dc;
            waterNo_ = TownRiseupManager::getSingleton().setupSprite2(index, pos, 2, 0);
            initWatSe_ = 1;
        } else if (system_.rail_[nowRailNo_].checkFlag(0x400) == true) {
            initWatSe_ = 1;
        }
        return 0x13;
    }
    return -1;
}

void twn::TownActionTruck::execute()
{
    dss::Fix32 a((fx32)8);
    dss::Fix32Vector3 prevPos = position_;
    dss::Fix32 ret;
    switch (state_) {
        case GET_ON:
            cmn::gMoveToTarget.execute();
            break;
        case MOVE:
            cmn::gMoveToTarget.execute();
            position_.vy += TownPlayerAction::collR;
            TownStageManager::getSingleton()->characoterColl(prevPos, position_, TownPlayerAction::collR, &position_, 2);
            TownStageManager::getSingleton()->setMapUidPosFX32(wagonUid_, position_);
            system_.getWagonByUid(wagonUid_).setPos(position_);
            if (system_.rail_[nowRailNo_].checkFlag(0x80) == true) {
                dss::Fix32Vector3 pos = position_;
                if (TownRiseupManager::getSingleton().isEnable(waterNo_) == false) {
                    int index = getWaterEffectNo();
                    waterNo_ = TownRiseupManager::getSingleton().setupSprite(index, pos, 0, 0);
                }
                if (height_ == 1) {
                    pos.vy.value += 0x7d0;
                }
                TownRiseupManager::getSingleton().setPosition(waterNo_, pos);
            }
            break;
        case GET_DOWN:
            cmn::gMoveToTarget.execute();
            if (counter_ <= jumpCount_) {
                position_.vy += a * -1 * 4 * counter_ * counter_ + a * 4 * jumpCount_ * counter_;
            } else if (counter_ == jumpCount_ + 1) {
                SoundManager::playSe(0x49a, 0);
            }
            break;
        case SLOPE:
            cmn::gMoveToTarget.execute();
            position_ += vec_ * -1 * counter_ * counter_;
            TownStageManager::getSingleton()->setMapUidPosFX32(wagonUid_, position_);
            break;
        case SLOPE_DOWN:
            position_ += vec_ * counter_ * counter_;
            TownStageManager::getSingleton()->setMapUidPosFX32(wagonUid_, position_);
            break;
        case TRAIN_3:
            cmn::gMoveToTarget.execute();
            TownStageManager::getSingleton()->setMapUidPosFX32(wagonUid_, position_);
            system_.getWagonByUid(wagonUid_).setPos(position_);
            {
                dss::Fix32Vector3 ang(0, 0, 0);
                ang.vy.value = TownPlayerManager::getSingleton().party_.getMemberDir(1) + 0x4000;
                TownStageManager::getSingleton()->setRotObjectUid(trainUid_, ang);
                TownPlayerManager& player = TownPlayerManager::getSingleton();
                TownStageManager::getSingleton()->setMapUidPosFX32(trainUid_, (dss::Fix32Vector3&)player.party_.getMemberPos(1));
            }
            break;
    }
}

void twn::TownActionTruck::terminate()
{
    if (waterSe_ == 1) {
        SoundManager::stopSeWithIndex(0x47b, 0);
    }
    if (trainRunSe_ == 1) {
        SoundManager::stopSeWithIndex(0x47d, 0);
    }
    if (wagonSe_ == 1) {
        SoundManager::stopSeWithIndex(0x47a, 0);
    }
}

void twn::TownActionTruck::checkAction()
{
    if (system_.rail_[nowRailNo_].checkFlag(1) == true) {
        state_ = TRAIN_1;
        TownCamera::getSingleton()->setCameraLock(true);
        TownCamera::getSingleton()->setShake(2, 4);
        SoundManager::playSe(0x47c, 0);
        counter_ = 0;
    }
    if (system_.getRailByRailNo(nowRailNo_).checkFlag(0x80) == true) {
        int index = getWaterEffectNo();
        dss::Fix32Vector3 pos = position_;
        pos.vy.value += 0x5dc;
        waterNo_ = TownRiseupManager::getSingleton().setupSprite2(index, pos, 2, 0);
        if (waterSe_ == 0) {
            SoundManager::playSe(0x47b, 0);
            waterSe_ = 1;
        }
    } else if (system_.rail_[nowRailNo_].checkFlag(0x400) == true) {
        if (waterSe_ == 0) {
            SoundManager::playSe(0x47b, 0);
            waterSe_ = 1;
        }
    } else if (waterSe_ == 1) {
        SoundManager::stopSeWithIndex(0x47b, 0);
        waterSe_ = 0;
    }
    if (system_.rail_[prevRailNo_].checkFlag(2) == true) {
        slope_ = 1;
    }
    switch (seesaw_) {
        case 0:
            if (system_.getRailByRailNo(prevRailNo_).checkFlag(4) == true) {
                if (twn::seesaw_.isSeesawIndex(system_.getRailByRailNo(prevRailNo_).index_)) {
                    system_.getRailByRailNo(prevRailNo_).changeSwitch();
                    seesaw_ = 1;
                }
            }
            break;
        case 1:
            twn::seesaw_.seesawSwitch(true);
            seesaw_ = 2;
            break;
        case 2:
            if (system_.getRailByRailNo(prevRailNo_).checkFlag(4) == true) {
                system_.getRailByRailNo(prevRailNo_).changeSwitch();
                seesaw_ = 0;
            }
            break;
    }
    if (system_.rail_[nowRailNo_].checkFlag(8) == true) {
        sparkIndex_++;
        if (sparkIndex_ >= 2) {
            short idxNum = (dirIdx_ + (dirIdx_ > 0 ? 0x1000 : -0x1000)) / 0x2000;
            switch (idxNum) {
                case 0:
                    sparkIndex_ = 0x3a0;
                    break;
                case 2:
                    sparkIndex_ = 0x3a1;
                    break;
                case -4:
                case 4:
                    sparkIndex_ = 0x39f;
                    break;
                case -2:
                    sparkIndex_ = 0x3a2;
                    break;
                case 3:
                    sparkIndex_ = 0x3a4;
                    break;
                case -1:
                    sparkIndex_ = 0x3a3;
                    break;
            }
            TownRiseupManager::getSingleton().setupSprite(sparkIndex_, position_, 0, 0);
            sparkIndex_ = 0;
        }
    }
}

int twn::TownActionTruck::getWaterEffectNo()
{
    int index = 0x39f;
    height_ = 0;
    short idxNum = (dirIdx_ + (dirIdx_ > 0 ? 0x1000 : -0x1000)) / 0x2000;
    switch (idxNum) {
        case -4:
        case 4:
            index = 0x3a0;
            height_ = 1;
            break;
        case -2:
            index = 0x3a1;
            break;
        case 0:
            index = 0x39f;
            break;
        case 2:
            index = 0x3a2;
            break;
        case -3:
            index = 0x3a3;
            height_ = 1;
            break;
        case 1:
            index = 0x3a4;
            break;
    }
    return index + 0xd;
}

bool twn::TownActionTruck::preActionCheck()
{
    if (slope_ == 1) {
        dss::Fix32Vector3 target;
        int temp = system_.getNextRailNo(nowRailNo_, prevRailNo_);
        system_.nextPos(temp, position_, target);
        vec_ = target - position_;
        vec_.normalize();
        target = position_ + vec_ * slopelen;
        cmn::gMoveToTarget.setAction(position_, target, truckSpeed, 0, 1, 9);
        vec_ *= slopeFx;
        state_ = SLOPE;
        slope_ = 0;
        counter_ = 0;
        return true;
    }
    return false;
}

void twn::TownActionTruck::scriptStart(int wagonUid, int nowRail, int prevRail)
{
    int temp = system_.getNextRailNo(nowRail, prevRail);
    dss::Fix32Vector3 start;
    dss::Fix32Vector3 target;
    start = system_.getWagonByUid(wagonUid).pos_;
    system_.nextPos(temp, start, target);
    prevScriptRail_ = nowRail;
    scriptRail_ = temp;
    scriptWagonUid_ = wagonUid;
    scriptMove_.setActionMove(start, target);
    scriptMove_.setMoveSpeed(truckSpeed);
    scriptPos_ = start;
    scriptFlag_ = 1;
}

void twn::TownActionTruck::scriptMove()
{
    scriptMove_.execMove(scriptPos_);
    TownStageManager::getSingleton()->setMapUidPosFX32(scriptWagonUid_, scriptPos_);
    system_.getWagonByUid(scriptWagonUid_).setPos(scriptPos_);
    if (scriptMove_.moveUpdate() == true) {
        if (system_.getNextRailNo(scriptRail_, prevScriptRail_) != 999) {
            scriptStart(scriptWagonUid_, scriptRail_, prevScriptRail_);
        } else {
            scriptFlag_ = 0;
            scriptWagonUid_ = 0;
            SoundManager::stopSeWithIndex(0x47a, 0);
        }
    }
}

void twn::TownActionTruck::firstMove()
{
    state_ = MOVE;
    dss::Fix32Vector3 target;
    nowRailNo_ = system_.getRailNo(position_);
    int temp = system_.getNextRailNo(nowRailNo_, 999);
    system_.nextPos(temp, position_, target);
    cmn::gMoveToTarget.setAction(position_, target, truckSpeed, 0, 1, 3);
    prevRailNo_ = nowRailNo_;
    nowRailNo_ = temp;
    if (system_.rail_[nowRailNo_].checkFlag(8) == true) {
        sparkIndex_++;
    }
}

void twn::TownActionTruck::moveNext(int next, dss::Fix32 speed)
{
    prevRailNo_ = nowRailNo_;
    dss::Fix32Vector3 target;
    dss::Fix32Vector3 ang;
    system_.nextPos(next, position_, target);
    nowRailNo_ = next;
    cmn::gMoveToTarget.setAction(position_, target, speed, 0, 1, 3);
    if (system_.rail_[nowRailNo_].getRoot() == 999) {
        ang.vy.value = dirIdx_;
        TownStageManager::getSingleton()->setRotObjectUid(wagonUid_, ang);
        system_.getWagonByUid(wagonUid_).setIdx(dirIdx_);
    }
}

void twn::TownActionTruck::moveEnd()
{
    dss::Fix32Vector3 ang;
    dirIdx_ = (dirIdx_ + (dirIdx_ < 0 ? -0x1000 : 0x1000)) / 0x2000;
    dirIdx_ = dirIdx_ << 13;
    ang.vy.value = dirIdx_;
    TownStageManager::getSingleton()->setRotObjectUid(wagonUid_, ang);
    system_.getWagonByUid(wagonUid_).setIdx(dirIdx_);
    if (system_.rail_[nowRailNo_].getJumpMap() != 0) {
        cmn::g_extraMapLink.setExtraExitTown(system_.rail_[nowRailNo_].getJumpMap(), system_.rail_[nowRailNo_].getJumpIndex() + 0x130000);
        cmn::g_cmnPartyInfo.setMenuAction(cmn::TRUCK_LINK);
        cmn::g_cmnPartyInfo.setWagonUid(wagonUid_);
        TownPlayerManager::getSingleton().setRemote(false);
        system_.getWagonByUid(wagonUid_).setMap(system_.rail_[nowRailNo_].getJumpMap());
    } else {
        dss::Fix32Vector3 pos = system_.getWagonByUid(wagonUid_).pos_;
        setGetDown();
        state_ = GET_DOWN;
        counter_ = 0;
    }
}

int twn::TownActionTruck::update()
{
    dss::Fix32Vector3 target;
    dss::Fix32Vector3 ang;
    switch (state_) {
        case GET_ON:
            if (cmn::gMoveToTarget.update() == 2) {
                firstMove();
                if (wagonSe_ == 0) {
                    SoundManager::playSe(0x47a, 0);
                    wagonSe_ = 1;
                }
            }
            break;
        case MOVE:
            if (initRunSe_ == 1) {
                if (wagonSe_ == 0) {
                    SoundManager::playSe(0x47a, 0);
                    wagonSe_ = 1;
                }
                initRunSe_ = 0;
            }
            if (initWatSe_ == 1) {
                if (waterSe_ == 0) {
                    SoundManager::playSe(0x47b, 0);
                    waterSe_ = 1;
                }
                initWatSe_ = 0;
            }
            if (cmn::gMoveToTarget.update() == 3 && preActionCheck() != true) {
                int temp = system_.getNextRailNo(nowRailNo_, prevRailNo_);
                if (temp != 999) {
                    moveNext(temp, truckSpeed);
                    if (wagonSe_ == 0) {
                        SoundManager::playSe(0x47a, 0);
                        wagonSe_ = 1;
                    }
                    checkAction();
                } else {
                    moveEnd();
                }
            }
            break;
        case GET_DOWN:
            if (cmn::gMoveToTarget.update() == 9) {
                TownPlayerManager::getSingleton().setMoveToFirstFlag();
                state_ = END;
            }
            break;
        case SLOPE:
            if (cmn::gMoveToTarget.update() == 9) {
                int temp = nowRailNo_;
                nowRailNo_ = prevRailNo_;
                prevRailNo_ = temp;
                temp = system_.getNextRailNo(nowRailNo_, prevRailNo_);
                if (temp != 999) {
                    moveNext(temp, truckSpeed);
                }
                state_ = MOVE;
            }
            break;
        case TRAIN_1:
            if (counter_ > 0x18) {
                TownCamera::getSingleton()->setCameraLock(false);
                SoundManager::playSe(0x47d, 0);
                trainRunSe_ = 1;
                state_ = TRAIN_2;
                TownPlayerManager::getSingleton().party_.setSpeed(truckSpeed);
                dss::Fix32 fix((fx32)0x19a);
                TownPlayerManager::getSingleton().party_.setCharaDistance(0, fix, fix, fix, fix);
                fix.value = 0x1000;
                TownPlayerManager::getSingleton().party_.setCharaDistance(1, fix, fix, fix, fix);
                TownPlayerManager::getSingleton().setFormation(1, 3, dss::Fix32(0L));
            }
            break;
        case TRAIN_2: {
            int temp = nowRailNo_;
            nowRailNo_ = prevRailNo_;
            prevRailNo_ = temp;
            temp = system_.getNextRailNo(nowRailNo_, prevRailNo_);
            if (temp != 999) {
                moveNext(temp, truckSpeed / 2);
            }
            state_ = TRAIN_3;
            TownStageManager::getSingleton()->eventAnim(1, 0);
            break;
        }
        case TRAIN_3:
            if (cmn::gMoveToTarget.update() == 3) {
                int temp = system_.getNextRailNo(nowRailNo_, prevRailNo_);
                if (temp != 999) {
                    moveNext(temp, truckSpeed2);
                    if (system_.rail_[nowRailNo_].getJumpMap() != 0) {
                        cmn::g_extraMapLink.setExtraExitTown(system_.rail_[nowRailNo_].getJumpMap(), system_.rail_[nowRailNo_].getJumpIndex() + 0x130000);
                        cmn::g_cmnPartyInfo.setWagonUid(wagonUid_);
                        TownPlayerManager::getSingleton().setRemote(false);
                        system_.getWagonByUid(wagonUid_).setMap(system_.rail_[nowRailNo_].getJumpMap());
                    }
                } else {
                    SoundManager::stopSeWithIndex(0x47d, 0);
                }
            }
            break;
        case END:
            if (TownPlayerManager::getSingleton().getMoveToFirstFlag() == false) {
                wagonUid_ = 0;
                TownPlayerManager::getSingleton().setRemote(false);
                return 0;
            }
            break;
    }
    counter_++;
    return -1;
}

void twn::TownPlayerManager::setMoveToFirstFlag()
{
    party_.setMoveFirstFlag(true);
}

bool twn::TownPlayerManager::getMoveToFirstFlag()
{
    return party_.getMoveFirstFlag();
}

void twn::TownActionTruck::setGetDown()
{
    dss::Fix32 fix((fx32)0x2000);
    jumpCount_ = 0x14;
    if (system_.getRailByRailNo(nowRailNo_).checkFlag(0x100)) {
        dss::Fix32 a((fx32)0x1c00);
        fix *= a;
        jumpCount_ = jumpCount_ * a.value / 0x1000;
    } else if (system_.getRailByRailNo(nowRailNo_).checkFlag(0x200)) {
        dss::Fix32 a((fx32)0x2000);
        fix *= a;
        jumpCount_ = jumpCount_ * a.value / 0x1000;
    }
    SoundManager::stopSeWithIndex(0x47a, 0);
    SoundManager::playSe(0x499, 0);
    wagonSe_ = 0;
    dss::Fix32Vector3 vec;
    TownActionCalculate::getDirByIdx(dirIdx_, vec);
    dss::Fix32Vector3 target = position_ + vec * fix;
    TownPlayerManager::getSingleton().setPartyToFirst(position_);
    TownPlayerManager::getSingleton().resetDrawPartyCount();
    cmn::gMoveToTarget.setAction(position_, target, TownPlayerAction::walkSpeed, 1, 0, 9);
}

int twn::TownActionTruck::check()
{
    if (g_Global.getNowAreaNo() != 0x28) {
        return false;
    }
    wagonUid_ = system_.checkWagon(position_);
    if (wagonUid_ != 0 && wagonUid_ != scriptWagonUid_) {
        return true;
    }
    return false;
}

void twn::TownActionTruck::set()
{
    dss::Fix32Vector3 target;
    int count = system_.getWagonCount();
    for (int i = 0; i < count; i++) {
        if (wagonUid_ == wagon_[i].getUid()) {
            target = wagon_[i].pos_;
        }
    }
    TownPlayerManager::getSingleton().setRemote(true);
    target.vy += TownPlayerAction::collR;
    cmn::gMoveToTarget.setAction(position_, target, TownPlayerAction::walkSpeed, 1, 1, 2);
    state_ = GET_ON;
}
