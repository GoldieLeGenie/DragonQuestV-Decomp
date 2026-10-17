#include "ov001/town/MapObjGridMove.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownActionCalculate.hpp"

inline void twn::TownStageManager::addCollisionPosByMapUid(int uid_id, dss::Fix32Vector3& add)
{
    stage_.m_fld.CollAddPolyPosByMapUid(uid_id, (VecFx32*)&add);
}

THUMB void twn::MapObjGridMove::initialize()
{
    uid_ = 0;
    moveLength_ = 0L;
}

THUMB void twn::MapObjGridMove::setup(int uid, int flag, dss::Fix32 length)
{
    counter_ = 0;
    endCount_ = 0;
    if (uid_ == uid) {
        end_ = basePosition_;
        end_.vx += moveLength_ * countMoveX_;
        end_.vz += moveLength_ * countMoveZ_;
        dss::Fix32Vector3 vec = end_ - basePosition_;
        TownStageManager::getSingleton()->addCollisionPosByMapUid(uid_, vec);
        TownStageManager::getSingleton()->setMapUidPosFX32(uid_, end_);
    } else {
        countMoveX_ = 0;
        countMoveZ_ = 0;
        uid_ = uid;
        moveLength_ = length;
        if (flag == false) {
            basePosition_.set(0, 0, 0);
        } else {
            basePosition_ = TownStageManager::getSingleton()->getMapUidPos(uid);
        }
    }
}

THUMB void twn::MapObjGridMove::execute()
{
    if (endCount_ != 0) {
        dss::Fix32Vector3 pos;
        if (counter_ <= endCount_) {
            pos = (start_ * (endCount_ - counter_) + end_ * counter_) / endCount_;
        } else {
            pos = end_;
            dss::Fix32Vector3 vec = end_ - start_;
            TownStageManager::getSingleton()->addCollisionPosByMapUid(uid_, vec);
            endCount_ = 0;
        }
        TownStageManager::getSingleton()->setMapUidPosFX32(uid_, pos);
        counter_++;
    }
}

THUMB void twn::MapObjGridMove::setMove(int direction, dss::Fix32 speed)
{
    int polyNo = 0;
    dss::Fix32Vector3 start(basePosition_);
    start.vx += moveLength_ * countMoveX_;
    start.vz += moveLength_ * countMoveZ_;
    start.vy.value += 0x199;
    dss::Fix32Vector3 vec = TownActionCalculate::getParamVec(direction);
    dss::Fix32Vector3 target(start);
    target += vec * moveLength_;
    if (TownStageManager::getSingleton()->checkCrossNumEraseSurface(start, target, 0xc0000, false, polyNo) <= 1) {
        start_ = basePosition_;
        start_.vx += moveLength_ * countMoveX_;
        start_.vz += moveLength_ * countMoveZ_;
        speed *= baseSpeed;
        endCount_ = (moveLength_ / speed).value / 0x1000;
        counter_ = 0;
        switch (direction) {
        case 0:
            countMoveZ_++;
            break;
        case 1:
            countMoveX_++;
            break;
        case 2:
            countMoveZ_--;
            break;
        case 3:
            countMoveX_--;
            break;
        }
        end_ = basePosition_;
        end_.vx += moveLength_ * countMoveX_;
        end_.vz += moveLength_ * countMoveZ_;
    }
}

const dss::Fix32 twn::MapObjGridMove::baseSpeed((fx32)0x66);
