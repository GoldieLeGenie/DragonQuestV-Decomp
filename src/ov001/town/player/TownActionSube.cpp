#pragma ipa file
#include "ov001/town/player/TownActionSube.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/sound/Sound.hpp"
#include "main/sound/SoundManager.hpp"

#pragma thumb on

inline dss::Fix32Vector3::Fix32Vector3(const Fix32& x, const Fix32& y, const Fix32& z)
{
    vx = x;
    vy = y;
    vz = z;
}

inline void twn::TownPlayerManager::setAnimation(int flag)
{
    partyDraw_.setAnimation(flag);
}

const dss::Fix32 twn::TownActionSube::subeR((fx32)0x59a);
const dss::Fix32 twn::TownActionSube::subeSpeed((fx32)0x19a);

int twn::TownActionSube::setup()
{
    subeDir4_ = 0;
    prev_subeDir4_ = 0;
    vec[0] = dss::Fix32Vector3(0L, 0L, subeSpeed * -1);
    vec[1] = dss::Fix32Vector3(subeSpeed, 0L, 0L);
    vec[2] = dss::Fix32Vector3(0L, 0L, subeSpeed);
    vec[3] = dss::Fix32Vector3(subeSpeed * -1, 0L, 0L);
    count_ = 0;
    return -1;
}

void twn::TownActionSube::execute()
{
    dss::Fix32Vector3 subePos;
    dss::Fix32Vector3 tempPos;
    dss::Fix32 height;
    tempPos = position_;
    tempPos.vy += subeR;
    TownStageManager::getSingleton()->compute(tempPos, tempPos, subeR, subeR, subeR * 2, height);
    subeDir4_ = TownStageManager::getSingleton()->getHitSurfaceIdByType(8);
    if (subeDir4_ != -1) {
        subeDir4_ = (subeDir4_ & 0xf) - 1;
        subePos = TownStageManager::getSingleton()->getHitSurfacePosByType(8);
        if (subeDir4_ == 0 || subeDir4_ == 2) {
            if (subePos.vx != position_.vx) {
                dss::Fix32 len = subePos.vx - position_.vx;
                if (dss::abs<long>(len.value) < subeSpeed.value) {
                    position_.vx += len;
                } else {
                    position_.vx += (len.value >= 0) ? subeSpeed : subeSpeed * -1;
                }
            } else {
                position_ += vec[subeDir4_];
            }
        } else {
            if (subePos.vz != position_.vz) {
                dss::Fix32 len = subePos.vz - position_.vz;
                if (dss::abs<long>(len.value) < subeSpeed.value) {
                    position_.vz += len;
                } else {
                    position_.vz += (len.value >= 0) ? subeSpeed : subeSpeed * -1;
                }
            } else {
                position_ += vec[subeDir4_];
            }
        }
    } else {
        if (count_ <= maxCount) {
            subeDir4_ = prev_subeDir4_;
            position_ += vec[subeDir4_];
        }
        count_++;
    }
    prev_subeDir4_ = subeDir4_;
    if (TownStageManager::getSingleton()->getExitIndex() != -1) {
        SoundManager::stopSeWithIndex(0x14a, 0);
    }
}

int twn::TownActionSube::update()
{
    if (count_ == maxCount) {
        if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0) == -1 || TownStageManager::getSingleton()->getHitSurfaceIdByType(0xb) != -1) {
            TownPlayerManager::getSingleton().player_.townActionFall_.setCollFall();
            TownPlayerManager::getSingleton().player_.townActionFall_.count_ = 3;
            SoundManager::stopSeWithIndex(0x14a, 0);
            return 3;
        }
        TownPlayerManager::getSingleton().setMoveToFirstFlag();
    } else if (count_ > maxCount) {
        if (TownPlayerManager::getSingleton().getMoveToFirstFlag() == false) {
            TownPlayerManager::getSingleton().setRemote(false);
            TownPlayerManager::getSingleton().setAnimation(true);
            SoundManager::stopSeWithIndex(0x14a, 0);
            return 0;
        }
    }
    return -1;
}

int twn::TownActionSube::startCheck()
{
    int ret = -1;
    int surfaceId = TownStageManager::getSingleton()->getHitSurfaceIdByType(8);
    if (surfaceId != -1) {
        count_ = 0;
        subeDir4_ = 0;
        prev_subeDir4_ = 0;
        ret = 2;
        TownPlayerManager::getSingleton().setRemote(true);
        TownPlayerManager::getSingleton().setAnimation(false);
        Sound::sePlayDirect(0x14a);
    }
    return ret;
}
