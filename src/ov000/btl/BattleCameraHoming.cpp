#include "ov000/btl/BattleCameraHoming.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "nitro/fx.hpp"
#include "nitro/fx/fx_atan.h"

inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }

THUMB btl::BattleCameraHoming::BattleCameraHoming()
{
    startTime_ = 30;
    waitTime_ = 60;
    restoreTime_ = 30;
    step_ = STEP_NONE;
}

THUMB btl::BattleCameraHoming::~BattleCameraHoming()
{
}

THUMB void btl::BattleCameraHoming::setup(dss::Fix32Vector3 target, int drawCtrlId)
{
    dss::Fix32Vector3 position;
    position = dss::Fix32Vector3(*BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).monsterDraw_.getPosition());
    VecFx32 dir;
    dir.x = position.vx.value - target.vx.value;
    dir.y = 0;
    dir.z = position.vz.value - target.vz.value;
    func_0208a330(&dir, &dir);
    rotAngle_ = FX_AtanIdx(FX_Divide(dir.x / 2, dir.z));
    count_ = 0;
    step_ = STEP_NONE;
}

THUMB void btl::BattleCameraHoming::calcHomingTarget(dss::Vector3<short>& angle)
{
    angle.vy = count_ * rotAngle_ / startTime_;
    count_++;
    if (count_ == startTime_) {
        step_ = STEP_WAIT;
        count_ = 0;
    }
}

THUMB void btl::BattleCameraHoming::waitHomingTarget(dss::Vector3<short>& angle)
{
    angle.vy = rotAngle_;
    count_++;
    if (count_ == waitTime_) {
        step_ = STEP_RESTORE;
        count_ = 0;
    }
}

THUMB void btl::BattleCameraHoming::restoreHomingTarget(dss::Vector3<short>& angle)
{
    angle.vy = rotAngle_ * (restoreTime_ - count_) / restoreTime_;
    count_++;
    if (count_ == restoreTime_) {
        step_ = STEP_NONE;
    }
}

THUMB void btl::BattleCameraHoming::calculation(dss::Vector3<short>& angle)
{
    switch (step_) {
    case STEP_NONE:
        break;
    case STEP_START:
        calcHomingTarget(angle);
        break;
    case STEP_WAIT:
        waitHomingTarget(angle);
        break;
    case STEP_RESTORE:
        restoreHomingTarget(angle);
        break;
    }
}

THUMB void btl::BattleCameraHoming::setRotateTime(int time)
{
    startTime_ = time;
    restoreTime_ = time;
}

THUMB void btl::BattleCameraHoming::setWaitTime(int time)
{
    waitTime_ = time;
}
