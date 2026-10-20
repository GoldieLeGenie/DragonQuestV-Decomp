#include "ov001/town/TownStageEffectManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownFurnitureControl.hpp"
#include "main/status/StageInfo.hpp"
#include "main/sound/SoundManager.hpp"

#pragma thumb on

inline void twn::TownStageManager::addCollisionPosByMapUid(int uid_id, dss::Fix32Vector3& add)
{
    stage_.m_fld.CollAddPolyPosByMapUid(uid_id, (VecFx32*)&add);
}

const unsigned char twn::TownStageNinePuzzle::defaultSection[3][3] = {
    {1, 4, 7},
    {2, 5, 0},
    {3, 6, 8},
};

twn::TownStageNinePuzzle::TownStageNinePuzzle()
{
    enable_ = false;
}

twn::TownStageNinePuzzle::~TownStageNinePuzzle()
{
}

void twn::TownStageNinePuzzle::initPuzzle()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            status::g_StageInfo.setPuzzleSection(defaultSection[i][j], i, j);
        }
    }
    setup();
}

void twn::TownStageNinePuzzle::setup()
{
    moveFrame_ = 90;
    phase_ = 0;
    moveId_ = -1;
    enable_ = true;
    moveDirect_ = 0;
    moveSection_ = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            relocation(status::g_StageInfo.getPuzzleSection(i, j), i, j);
        }
    }
}

void twn::TownStageNinePuzzle::relocation(int id, int x, int z)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (id == defaultSection[i][j]) {
                int diffX = x - i;
                dss::Fix32Vector3 pos = TownStageManager::getSingleton()->getMapUidPos(id + modelOffset);
                dss::Fix32Vector3 coll(0, 0, 0);
                diffX *= distance_;
                pos.vx.value += diffX;
                int diffZ = (z - j) * distance_;
                pos.vz.value += diffZ;
                coll.vx.value += diffX;
                coll.vz.value += diffZ;
                TownStageManager::getSingleton()->addCollisionPosByMapUid(id + collisionOffset, coll);
                TownStageManager::getSingleton()->addMapUidPosFX32(id + modelOffset, coll);
            }
        }
    }
}

void twn::TownStageNinePuzzle::cleanup()
{
}

void twn::TownStageNinePuzzle::execute()
{
    if (enable_ == false) {
        return;
    }
    switch (phase_) {
    case 0:
        break;
    case 1: {
        dss::Fix32Vector3 start(TownPlayerManager::getSingleton().getPosition());
        dss::Fix32Vector3 target = TownStageManager::getSingleton()->getHitSurfacePosByType(18);
        TownPlayerManager::getSingleton().setSimpleMove(start, target, 5);
        phase_ = 2;
        break;
    }
    case 2:
        if (TownPlayerManager::getSingleton().isFinish()) {
            TownPlayerManager::getSingleton().setMoveToFirstFlag();
            phase_ = 3;
        }
        break;
    case 3:
        if (TownPlayerManager::getSingleton().getMoveToFirstFlag() == false) {
            setSlideMove();
            phase_ = 4;
        }
        break;
    case 4:
        if (TownFurnitureControlManager::getSingleton().isEnd(moveId_)) {
            TownFurnitureControlManager::getSingleton().cleanup(moveId_);
            dss::Fix32Vector3& playerPos = TownPlayerManager::getSingleton().getPosition();
            TownPlayerManager::getSingleton().setPartyToFirst(playerPos);
            TownPlayerManager::getSingleton().setLock(false);
            SoundManager::stopSe(ctrl_, 0);
            SoundManager::playSe(0x456, 0);
            phase_ = 5;
        }
        break;
    case 5:
        if (TownStageManager::getSingleton()->getHitSurfaceIdByType(18) < 0) {
            phase_ = 0;
        }
        break;
    }
}

bool twn::TownStageNinePuzzle::checkMovable()
{
    if (phase_ == 5) {
        return false;
    }
    int id = TownStageManager::getSingleton()->getHitSurfaceIdByType(18);
    if (id < 0) {
        return false;
    }
    moveSection_ = (unsigned short)id;
    int x, y;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (moveSection_ == status::g_StageInfo.getPuzzleSection(i, j)) {
                x = i;
                y = j;
                break;
            }
        }
    }
    int work;
    int current = status::g_StageInfo.getPuzzleSection(x, y);
    if (x - 1 >= 0) {
        work = status::g_StageInfo.getPuzzleSection(x - 1, y);
        if (work == 0) {
            status::g_StageInfo.setPuzzleSection(current, x - 1, y);
            status::g_StageInfo.setPuzzleSection(work, x, y);
            phase_ = 1;
            moveDirect_ = 1;
            return true;
        }
    }
    if (x + 1 < 3) {
        work = status::g_StageInfo.getPuzzleSection(x + 1, y);
        if (work == 0) {
            status::g_StageInfo.setPuzzleSection(current, x + 1, y);
            status::g_StageInfo.setPuzzleSection(work, x, y);
            phase_ = 1;
            moveDirect_ = 2;
            return true;
        }
    }
    if (y - 1 >= 0) {
        work = status::g_StageInfo.getPuzzleSection(x, y - 1);
        if (work == 0) {
            status::g_StageInfo.setPuzzleSection(current, x, y - 1);
            status::g_StageInfo.setPuzzleSection(work, x, y);
            phase_ = 1;
            moveDirect_ = 3;
            return true;
        }
    }
    if (y + 1 < 3) {
        work = status::g_StageInfo.getPuzzleSection(x, y + 1);
        if (work == 0) {
            status::g_StageInfo.setPuzzleSection(current, x, y + 1);
            status::g_StageInfo.setPuzzleSection(work, x, y);
            phase_ = 1;
            moveDirect_ = 4;
            return true;
        }
    }
    moveDirect_ = 0;
    return false;
}

void twn::TownStageNinePuzzle::setSlideMove()
{
    if (moveDirect_ == 0) {
        return;
    }
    dss::Fix32Vector3 pos = TownStageManager::getSingleton()->getMapUidPos(moveSection_ + modelOffset);
    dss::Fix32Vector3 coll(0, 0, 0);
    dss::Fix32Vector3 playerPos(TownPlayerManager::getSingleton().getPosition());
    switch (moveDirect_) {
    case 1:
        pos.vx.value -= distance_;
        coll.vx.value -= distance_;
        playerPos.vx.value -= distance_;
        break;
    case 2:
        pos.vx.value += distance_;
        coll.vx.value += distance_;
        playerPos.vx.value += distance_;
        break;
    case 3:
        pos.vz.value -= distance_;
        coll.vz.value -= distance_;
        playerPos.vz.value -= distance_;
        break;
    case 4:
        pos.vz.value += distance_;
        coll.vz.value += distance_;
        playerPos.vz.value += distance_;
        break;
    }
    TownStageManager::getSingleton()->addCollisionPosByMapUid(moveSection_ + collisionOffset, coll);
    moveId_ = TownFurnitureControlManager::getSingleton().setFurnitureMove(moveSection_ + modelOffset, moveFrame_, pos);
    TownFurnitureControlManager::getSingleton().setGarbageCorrect(moveId_, false);
    TownPlayerManager::getSingleton().party_.setParallelMove(playerPos, moveFrame_);
    SoundManager::stopSe(ctrl_, 0);
    ctrl_ = SoundManager::playSe(0x471, 0);
}

bool twn::TownStageNinePuzzle::checkPuzzleMove()
{
    if (phase_ == 0 || phase_ == 5) {
        return false;
    }
    return true;
}
