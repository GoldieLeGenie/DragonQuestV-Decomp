#include "ov005/fld/FieldAction.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "ov005/fld/FieldPlayerDoku.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov005/fld/FieldSymbolManager.hpp"

inline dss::Fix32Vector3& fld::FieldPlayerManager::getShipPos(int index)
{
    return shipDraw_[index].getPosition();
}

inline void cmn::CommonPartyInfo::setShipNo(int shipNo)
{
    shipNo_ = shipNo;
}

inline void fld::FieldData::pause(int flag)
{
    pause_ = flag;
}

inline void cmn::CommonParticleEmitter::pause(bool flag)
{
    stop_ = flag;
}

inline void fld::FieldStage::pause(int flag)
{
    fieldData.pause(flag);
    cmn::CommonParticleEmitter::getSingleton()->pause(flag);
}

inline int fld::FieldStage::searchKanban(int x, int y, dss::Vector2<dss::Fix32>* pos)
{
    return fieldData.searchKanban(x, y, pos);
}

THUMB int fld::FieldActionWalk::setup()
{
    firstMove_ = false;
    return -1;
}

THUMB void fld::FieldActionWalk::execute()
{
    move_ = false;
    dss::Fix32Vector3 oldPos = position_;
    moveNormal(Speed, xSpeed, ySpeed);
    walkCollision();
    dss::Fix32Vector3 vec = positionN_ - oldPos;
    if (move_ == true) {
        firstMove_ = true;
    }
    if (oldPos != positionN_) {
        dirIdx_ = FieldActionCalculate::getDir8ByVector3(vec);
        collSE_ = true;
    } else if (move_ == true && collSE_ == true) {
        collSE_ = false;
    }
    FieldPlayerDoku::getSingleton().checkDokuDamage(position_, positionN_);
    position_ = positionN_;
}

THUMB void fld::FieldActionWalk::walkCollision()
{
    int blkX = position_.vx.value / 0x10000;
    int blkY = position_.vy.value / 0x10000;
    blockType_[8] = FieldStage::getSingleton()->getBlockAttr2(blkX, blkY);
    FieldStage::getSingleton()->setWalkColl(blkX, blkY, fieldCollInfo_);
    FieldStage::getSingleton()->setChipAttr(blkX, blkY, blockType_);
    walkColl(blkX, blkY);
    FieldPlayerDoku::getSingleton().setBlockAttr(blockType_[8]);
}

THUMB int fld::FieldActionWalk::update()
{
    if (checkShipAction() == true) {
        FieldPlayerManager::getSingleton().player_.fieldActionShip_.startAction();
        return 1;
    }
    return -1;
}

THUMB bool fld::FieldActionWalk::search()
{
    dss::Fix32Vector3 balPos;
    dss::Fix32Vector3 shipPos;
    dss::Fix32Vector3 searchPos;
    searchPos = position_ + FieldActionCalculate::getVector3ByDir8(dirIdx_) * 20;
    int kanbanId = FieldStage::getSingleton()->searchKanban(searchPos.vx.value, searchPos.vy.value, NULL);
    if (kanbanId != -1) {
        bool flag = false;
        if (position_.vy < searchPos.vy) {
            flag = true;
        }
        if (FieldSymbolManager::getSingleton().checkSymbol(kanbanId, flag) == true) {
            return true;
        }
    }
    return false;
}

THUMB bool fld::FieldActionWalk::checkShipAction()
{
    int ship[2] = { 0, 1 };
    if (firstMove_ == false) {
        return false;
    }
    for (int i = 0; i < 2; i++) {
        if (status::g_Story.isVehicleEnable(ship[i])) {
            dss::Fix32Vector3 vec;
            dss::Fix32Vector3 tvec;
            dss::Fix32Vector3 shipPos = FieldPlayerManager::getSingleton().getShipPos(i);
            dss::Fix32 length[4];
            int blkX = shipPos.vx.value / 0x10000;
            int blkY = shipPos.vy.value / 0x10000;
            vec = shipPos - positionN_;
            if (searchObject(shipPos, shipSearchR) == true) {
                vec.vz = 0L;
                vec.normalize();
                dss::Fix32Vector3 playerDir = FieldActionCalculate::getVector3ByDir8(dirIdx_);
                if (vec * playerDir <= dss::Fix32(0xb50)) {
                    return false;
                }
                if (FieldStage::getSingleton()->getBlockAttr2(blkX, blkY) == 7) {
                    length[0] = shipPos.vy.value - (blkY << 16);
                    length[1] = ((blkX + 1) << 16) - shipPos.vx.value;
                    length[2] = ((blkY + 1) << 16) - shipPos.vy.value;
                    length[3] = shipPos.vx.value - (blkX << 16);
                    int temp = 0;
                    for (int i = 0; i < 4; i++) {
                        if (length[temp] > length[i]) {
                            temp = i;
                        }
                    }
                    switch (temp) {
                    case 0:
                        shipPos.vy.value = (blkY << 16) - 1000;
                        break;
                    case 1:
                        shipPos.vx.value = ((blkX + 1) << 16) + 1000;
                        break;
                    case 2:
                        shipPos.vy.value = ((blkY + 1) << 16) + 1000;
                        break;
                    case 3:
                        shipPos.vx.value = (blkX << 16) - 1000;
                        break;
                    }
                }
                cmn::g_cmnPartyInfo.setShipNo(i);
                FieldPlayerDoku::getSingleton().clear();
                FieldStage::getSingleton()->pause(1);
                return true;
            }
        }
    }
    return false;
}
