#include "main/debug/UnkDebugTurnTask.hpp"
#include "main/global/Global.hpp"
#include "ov001/town/TownPlayerManager.hpp"

#pragma thumb on

UnkDebugTurnTask::UnkDebugTurnTask()
{
    active_ = 0;
}

void UnkDebugTurnTask::vf0c()
{
    if (active_ != 0 && fadeEffector.isFadeEnd()) {
        if (wait_ == 0) {
            int count = count_;
            dss::Fix32Vector3 pos;
            pos.vx.value = ((count % 5) * 4 - 10) << 12;
            pos.vy.value = 1 << 12;
            pos.vz.value = ((count / 5) * 4 - 10) << 12;
            twn::TownPlayerManager::getSingleton().setPosition(pos);
        }
        if (wait_ == 10) {
            if (++count_ == 25) {
                count_ = 0;
                requestState_ = 1;
                state_ = 0;
                return;
            }
            wait_ = 0;
            requestState_ = 2;
            state_ = 0;
        } else {
            wait_++;
        }
    }
}

void UnkDebugTurnTask::vf04()
{
    active_ = 1;
    wait_ = 0;
    count_ = 0;
    requestState_ = 2;
    state_ = 0;
}

UnkDebugTurnTask data_020f3520;
