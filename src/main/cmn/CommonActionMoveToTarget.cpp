#pragma ipa file
#pragma thumb on
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/cmn/GameManager.hpp"

inline void cmn::ActionBase::terminate()
{
}

inline cmn::PlayerManager* cmn::GameManager::getPlayerManager()
{
    return playerManager_;
}

cmn::CommonActionMoveToTarget cmn::gMoveToTarget;

int cmn::CommonActionMoveToTarget::setup()
{
    speed_.value = 0;
    target_.set(0, 0, 0);
    moveMode_ = MOVE_TO_TARGET;
    return -1;
}

void cmn::CommonActionMoveToTarget::execute()
{
    static const dss::Fix32 drawLen2(0xa3d);
    dss::Fix32Vector3 vec;
    if (moveMode_ == MOVE_TO_TARGET) {
        nowPos_ = nowPos_ + moveVec_;
        vec = target_ - nowPos_;
        if (vec.lengthsq() < speed_ * speed_) {
            if (partyMoveFlag_ == 1) {
                moveMode_ = MOVE_TO_FIRST;
                playerManager_->setMoveToFirstFlag();
                partyMoveFlag_ = 0;
            } else {
                moveMode_ = MOVE_END;
            }
            nowPos_ = target_;
        } else if (vec.lengthsq() < drawLen2 && !eraseFlag_) {
            eraseFlag_ = 1;
            count_ = 0;
        }
    }
    switch (drawType_) {
        case 0:
            drawAllExec();
            break;
        case 1:
            drawEraseExec(1);
            break;
        case 2:
            drawEraseExec(0);
            break;
    }
    position_ = nowPos_;
}

void cmn::CommonActionMoveToTarget::setAction(dss::Fix32Vector3& startPos, dss::Fix32Vector3& target, dss::Fix32 speed, int moveFlag, int drawFlag, int nextAction)
{
    playerManager_ = GameManager::getSingleton().getPlayerManager();
    target_ = target;
    nowPos_ = startPos;
    startPos_ = startPos;
    speed_ = speed;
    moveVec_ = target_ - position_;
    moveVec_.normalize();
    moveVec_ = moveVec_ * speed;
    moveType_ = moveFlag;
    partyMoveFlag_ = moveFlag == 1;
    drawType_ = drawFlag;
    nextAction_ = nextAction;
    dss::Fix32Vector3 dir = target_ - position_;
    CommonCalculate::getIdxByVec(dirIdx_, dir);
    moveMode_ = MOVE_TO_TARGET;
    eraseFlag_ = 0;
    count_ = 0;
}

int cmn::CommonActionMoveToTarget::update()
{
    int ret = -1;
    if (moveMode_ == MOVE_END) {
        ret = nextAction_;
    } else if (moveMode_ == MOVE_TO_FIRST) {
        if (!playerManager_->getMoveToFirstFlag()) {
            ret = nextAction_;
            moveMode_ = MOVE_END;
        }
    }
    if (ret != -1) {
        switch (drawType_) {
            case 0:
                playerManager_->resetDrawPartyCount();
                playerManager_->resetAlpha();
                break;
            case 1:
                playerManager_->setPartyDrawOne();
                break;
            case 2:
                playerManager_->setDrawPartyNone();
                break;
        }
    }
    count_++;
    return ret;
}

void cmn::CommonActionMoveToTarget::drawAllExec()
{
    int drawCount = playerManager_->getPartyDrawCount();
    for (int i = 0; i < drawCount; i++) {
        if (!playerManager_->isEqalNextPos(i) && playerManager_->getPartyDrawAlpha(i) < 0x1f) {
            playerManager_->addPartyDrawAlpha(i, 4);
        }
    }
}

void cmn::CommonActionMoveToTarget::drawEraseExec(int start)
{
    int drawCount = playerManager_->getPartyDrawCount();
    if (eraseFlag_ == 1) {
        for (int i = start; i < drawCount; i++) {
            if (count_ - i * 8 >= 0) {
                playerManager_->addPartyDrawAlpha(i, -4);
            }
        }
    }
}
