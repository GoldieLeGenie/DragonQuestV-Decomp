#include "ov001/town/player/TownActionIce.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownSugorokuManager.hpp"
#include "ov001/town/TownDamageFloor.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "main/btl/Encount.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/town/TownSugorokuInfo.hpp"

#pragma thumb on

inline void twn::TownPlayerManager::setMapLink(bool flag)
{
    flagMapLink_ = flag;
}

inline void twn::TownSugorokuInfo::decTimer()
{
    timeCount_--;
}

int twn::TownActionIce::setup()
{
    end_ = false;
    if (cmn::g_cmnPartyInfo.iceStart_ == true) {
        count_ = cmn::g_cmnPartyInfo.iceCount_;
        target_ = cmn::g_cmnPartyInfo.iceTarget_;
        TownPlayerManager::getSingleton().setRemote(true);
        cmn::g_cmnPartyInfo.iceStart_ = false;
        return 0x12;
    }
    return -1;
}

void twn::TownActionIce::execute()
{
    dss::Fix32Vector3 nowPos = position_;
    dss::Fix32Vector3 nextPos;
    if (end_ == false) {
        dss::Fix32Vector3 vec;
        TownActionCalculate::getVec4ByIdx(dirIdx_, vec);
        nextPos = position_ + vec * dss::Fix32(TownPlayerAction::walkSpeed);
        nextPos.vy += TownPlayerAction::collR;
        nowPos.vy += TownPlayerAction::collR;
        collActionFlag_ = TownActionCalculate::townStageColl(nowPos, nextPos, TownPlayerAction::collR, TownPlayerAction::surfaceR, TownPlayerAction::townCharaPreR);
        if (nowPos.vx == nextPos.vx && nowPos.vz == nextPos.vz) {
            end_ = true;
            count_ = 5;
        }
        nextPos.vy -= TownPlayerAction::collR;
        position_ = nextPos;
    }
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0xe) == -1) {
        end_ = true;
        count_ = 5;
    }
    if (count_ >= 0x26) {
        end_ = true;
        count_ = 0;
    }
    if (TownSugorokuManager::getSingleton().isTreasuerRoom() == true) {
        if (TownStageManager::getSingleton()->getHitSurfaceIdByType(1) != -1) {
            end_ = true;
            count_ = 5;
        }
        TownStageManager::getSingleton()->coll_.surfaceType_[1] = -1;
        TownPlayerManager::getSingleton().setMapLink(true);
        g_SugorokuInfo.decTimer();
    }
    nextPos = position_;
    if (end_ == false) {
        TownDamageFloor::getSingleton().checkDamageFloor(nowPos, nextPos);
    }
}

int twn::TownActionIce::update()
{
    if (collActionFlag_ != -1) {
        TownPlayerManager::getSingleton().player_.townActionFall_.setCollFall();
        return collActionFlag_;
    }
    int ret = TownPlayerManager::getSingleton().player_.townActionFall_.startCheck();
    if (ret != -1) {
        TownPlayerManager::getSingleton().player_.townActionFall_.setCollFall();
        return ret;
    }
    ret = TownPlayerManager::getSingleton().player_.townActionKaidan_.startCheck();
    if (ret != -1) {
        return ret;
    }
    ret = TownPlayerManager::getSingleton().player_.townActionDoor_.startCheck();
    if (ret != -1) {
        return ret;
    }
    if (end_ == true && count_ >= 5) {
        TownPlayerManager::getSingleton().setRemote(false);
        return 0;
    }
    count_++;
    if (end_ == false) {
        TownDamageFloor::getSingleton().checkEncount();
        if (status::g_StageAttribute.isEncount() == false) {
            return -1;
        }
        if (btl::Encount::getSingleton()->enable_ == false) {
            return -1;
        }
        if (btl::Encount::getSingleton()->isEncounted()) {
            btl::Encount::getSingleton()->execDungeon();
            cmn::g_cmnPartyInfo.iceStart_ = true;
            cmn::g_cmnPartyInfo.iceCount_ = count_;
            cmn::g_cmnPartyInfo.iceTarget_ = target_;
            return -1;
        }
    }
    return -1;
}

int twn::TownActionIce::startCheck()
{
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0xe) != -1 && cmn::g_cmnPartyInfo.position_ != cmn::g_cmnPartyInfo.prev_position_) {
        short dir = dirIdx_;
        dirIdx_ = (dir + (dir < 0 ? -0x2000 : 0x2000)) / 0x4000;
        dirIdx_ = dirIdx_ << 14;
        count_ = 0;
        target_ = position_;
        end_ = false;
        TownPlayerManager::getSingleton().setRemote(true);
        return 0x12;
    }
    return -1;
}
