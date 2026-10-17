#pragma ipa file
#include "ov005/fld/FieldAction.hpp"
#include "main/dss/DssVectorDefault.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov005/fld/FieldWindowSystem.hpp"

inline int cmn::PlayerAction::getPadInput()
{
    return padInput_;
}

inline int cmn::PlayerAction::getDirInput()
{
    return dirInput_;
}

inline int fld::FieldPlayerManager::getPadInput()
{
    return player_.getPadInput();
}

inline int fld::FieldPlayerManager::getDirInput()
{
    return player_.getDirInput();
}

inline int fld::FieldStage::searchKanban(int x, int y, dss::Vector2<dss::Fix32>* pos)
{
    return fieldData.searchKanban(x, y, pos);
}

inline CWorldMap& fld::FieldData::getWorldMap()
{
    return worldData_;
}

inline CNK_TEX* CWorldMap::getTextureData(int num)
{
    return &m_tex[num];
}

inline dss::Fix32Vector3::Fix32Vector3(const Fix32& x, const Fix32& y, const Fix32& z)
{
    vx = x;
    vy = y;
    vz = z;
}

const dss::Fix32 fld::FieldActionBase::Speed = 0x1800;
const dss::Fix32 fld::FieldActionBase::xSpeed = 0x1000;
const dss::Fix32 fld::FieldActionBase::ySpeed = 0x1000;
const dss::Fix32 fld::FieldActionBase::shipSearchR = 0x14000;
const dss::Fix32 fld::FieldActionBase::shipGetDownR = 0x10000;
const dss::Fix32 fld::FieldActionBase::Speed2 = 0x3000;
const dss::Fix32 fld::FieldActionBase::xSpeed2 = 0x2000;
const dss::Fix32 fld::FieldActionBase::ySpeed2 = 0x2000;
const dss::Fix32 fld::FieldActionBase::balSpeed = 0x2000;
const dss::Fix32 fld::FieldActionBase::balXSpeed = 0x1800;
const dss::Fix32 fld::FieldActionBase::balYSpeed = 0x1800;
fld::FieldCollInfo fld::FieldActionBase::fieldCollInfo_;
int fld::FieldActionBase::blockType_[9];
dss::Fix32Vector3 fld::FieldActionBase::positionN_;
dss::Fix32Vector3 fld::FieldActionBase::speed_;
int fld::FieldActionBase::collSE_;
int fld::FieldActionBase::move_;

THUMB void fld::FieldActionBase::moveNormal(dss::Fix32 speed, dss::Fix32 xspeed, dss::Fix32 yspeed)
{
    int padInput = FieldPlayerManager::getSingleton().getPadInput();
    int dirInput = FieldPlayerManager::getSingleton().getDirInput();
    speed_.vx = 0L;
    speed_.vy = 0L;
    prevInputDir_ = inputDir_;
    if (padInput) {
        dirIdx_ = dirInput / 0x2000;
        move_ = true;
        switch (dirIdx_) {
        case 0:
            speed_.vx = 0L;
            speed_.vy = speed * -1;
            break;
        case 1:
            speed_.vx = xspeed;
            speed_.vy = yspeed * -1;
            break;
        case 2:
            speed_.vx = speed;
            speed_.vy = 0L;
            break;
        case 3:
            speed_.vx = xspeed;
            speed_.vy = yspeed;
            break;
        case 4:
            speed_.vx = 0L;
            speed_.vy = speed;
            break;
        case 5:
            speed_.vx = xspeed * -1;
            speed_.vy = yspeed;
            break;
        case 6:
            speed_.vx = speed * -1;
            speed_.vy = 0L;
            break;
        case 7:
            speed_.vx = xspeed * -1;
            speed_.vy = yspeed * -1;
            break;
        }
        positionN_ = position_ + speed_;
        inputDir_ = dirIdx_;
    } else {
        positionN_ = position_;
        inputDir_ = -1;
    }
    speed_.normalize();
    speed_ *= dss::Fix32(1.2f);
}

THUMB bool fld::FieldActionBase::searchObject(dss::Fix32Vector3& searchPos, dss::Fix32 dr)
{
    bool ret = false;
    dss::Fix32Vector3 vec;
    int pblkX = positionN_.vx.value / 0x10000;
    int pblkY = positionN_.vy.value / 0x10000;
    int sblkX = searchPos.vx.value / 0x10000;
    int sblkY = searchPos.vy.value / 0x10000;
    int dx = pblkX - sblkX;
    int dy = pblkY - sblkY;
    if (dss::abs(dx) < 3 && dss::abs(dy) < 3) {
        vec = searchPos - positionN_;
        vec.vz = 0L;
        if (vec.lengthsq() < dr * dr) {
            ret = true;
        }
    }
    return ret;
}

THUMB void fld::FieldActionBase::coll(int blkX, int blkY)
{
    dss::Fix32Vector3 pvec = FieldActionCalculate::getVector3ByDir8(dirIdx_);
    dss::Fix32Vector3 searchPos = position_ + pvec * 8;
    dss::Vector2<dss::Fix32> kpos;
    dss::Vector2<dss::Fix32> pos;
    if (FieldStage::getSingleton()->searchKanban(searchPos.vx.value, searchPos.vy.value, &kpos) != -1) {
        pos.vx = searchPos.vx;
        pos.vy = searchPos.vy;
        dss::Vector2<dss::Fix32> vec = kpos - pos;
        vec.normalize();
        dss::Vector2<dss::Fix32> pvec2(pvec.vx, pvec.vy);
        if (vec * pvec2 < dss::Fix32(0xf09)) {
            positionN_ = position_;
        }
    }
    setColl(blkX, blkY, 1, 1);
    FieldPlayerInfo fldPlayerInfo = { position_, positionN_, dirIdx_ };
    FieldActionCalculate::playerFixMove(&fldPlayerInfo, &fieldCollInfo_, blkX, blkY, Speed);
    positionN_ = fldPlayerInfo.nextPos;
}

THUMB void fld::FieldActionBase::walkColl(int blkX, int blkY)
{
    dss::Fix32Vector3 pvec = FieldActionCalculate::getVector3ByDir8(dirIdx_);
    dss::Fix32Vector3 searchPos = position_ + pvec * 8;
    dss::Vector2<dss::Fix32> kpos;
    dss::Vector2<dss::Fix32> pos;
    if (FieldStage::getSingleton()->searchKanban(searchPos.vx.value, searchPos.vy.value, &kpos) != -1) {
        pos.vx = searchPos.vx;
        pos.vy = searchPos.vy;
        dss::Vector2<dss::Fix32> vec = kpos - pos;
        vec.normalize();
        dss::Vector2<dss::Fix32> pvec2(pvec.vx, pvec.vy);
        if (vec * pvec2 < dss::Fix32(0xf09)) {
            positionN_ = position_;
        }
    }
    setWalkColl(blkX, blkY, 6, 6);
    FieldPlayerInfo fldPlayerInfo = { position_, positionN_, dirIdx_ };
    FieldActionCalculate::playerFixMove(&fldPlayerInfo, &fieldCollInfo_, blkX, blkY, Speed);
    positionN_ = fldPlayerInfo.nextPos;
}

THUMB void fld::FieldActionBase::setColl(int blkX, int blkY, int collLength, int fixLength)
{
    int vecI[4] = { 1, -1, -1, 1 };
    dss::Fix32 fx[4];
    fx[0].value = blkY << 16;
    fx[1].value = (blkX + 1) << 16;
    fx[2].value = (blkY + 1) << 16;
    fx[3].value = blkX << 16;
    for (int i = 0; i < 4; i++) {
        if (fieldCollInfo_.blockColl[i * 2] == 0) {
            fieldCollInfo_.collLine[i].value = fx[i].value + ((vecI[i] * 6) << 12);
            getOn_[i] = 0;
        } else {
            fieldCollInfo_.collLine[i].value = fx[i].value + ((vecI[i] * collLength) << 12);
            getOn_[i] = 1;
        }
        if (fieldCollInfo_.blockColl[FieldActionCalculate::getDir8RotIdx(i * 2, -1)] == 0 || fieldCollInfo_.blockColl[FieldActionCalculate::getDir8RotIdx(i * 2, -2)] == 0 ||
            fieldCollInfo_.blockColl[FieldActionCalculate::getDir8RotIdx(i * 2, 1)] == 0 || fieldCollInfo_.blockColl[FieldActionCalculate::getDir8RotIdx(i * 2, 2)] == 0) {
            fieldCollInfo_.fixLine[i].value = fx[i].value + ((vecI[i] * 6) << 12);
            getOn_[i] = 0;
        } else {
            fieldCollInfo_.fixLine[i].value = fx[i].value + ((vecI[i] * fixLength) << 12);
            getOn_[i] = 1;
        }
    }
}

THUMB void fld::FieldActionBase::setWalkColl(int blkX, int blkY, int collLength, int fixLength)
{
    if (blockType_[8] == 0xe) {
        fieldCollInfo_.collLine[0] = dss::Fix32((long)(blkY * 16 + collLength));
        fieldCollInfo_.collLine[1] = dss::Fix32((long)(blkX * 16 + 7));
        fieldCollInfo_.collLine[2] = dss::Fix32((long)(blkY * 16 + 16 - collLength));
        fieldCollInfo_.collLine[3] = dss::Fix32((long)(blkX * 16 + 9));
        fieldCollInfo_.fixLine[0] = dss::Fix32((long)(blkY * 16 + fixLength));
        fieldCollInfo_.fixLine[1] = dss::Fix32((long)(blkX * 16 + 7));
        fieldCollInfo_.fixLine[2] = dss::Fix32((long)(blkY * 16 + 16 - fixLength));
        fieldCollInfo_.fixLine[3] = dss::Fix32((long)(blkX * 16 + 9));
    } else {
        int vecI[4] = { 1, -1, -1, 1 };
        dss::Fix32 fx[4];
        fx[0].value = blkY << 16;
        fx[1].value = (blkX + 1) << 16;
        fx[2].value = (blkY + 1) << 16;
        fx[3].value = blkX << 16;
        int num = FieldStage::getSingleton()->getFieldData().getWorldMap().getWorldNo(blkX, blkY);
        for (int i = 0; i < 4; i++) {
            if (blockType_[i * 2] == 8 || blockType_[i * 2] == 9) {
                fieldCollInfo_.collLine[i].value = fx[i].value + ((vecI[i] * 9) << 12);
            } else {
                fieldCollInfo_.collLine[i].value = fx[i].value + ((vecI[i] * collLength) << 12);
            }
            if (isKaigFix(i, num) == true) {
                fieldCollInfo_.collLine[i].value = fx[i].value + ((vecI[i] * 9) << 12);
                fieldCollInfo_.fixLine[i].value = fx[i].value + ((vecI[i] * 9) << 12);
            } else {
                fieldCollInfo_.fixLine[i].value = fx[i].value + ((vecI[i] * fixLength) << 12);
            }
        }
    }
}

THUMB bool fld::FieldActionBase::isKaigFix(int dir4, int num)
{
    if (blockType_[8] != 7) {
        return false;
    }
    int ptNo = FieldStage::getSingleton()->getFieldData().getWorldMap().getTextureData(num)->ano;
    int ret = false;
    switch (g_Global.getFieldType()) {
    case 3:
        switch (ptNo) {
        case 6:
        case 7:
        case 8:
        case 9:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
            ret = true;
            break;
        }
        break;
    case 1:
    case 2:
        switch (ptNo) {
        case 6:
        case 7:
        case 8:
        case 9:
        case 0x20:
        case 0x21:
        case 0x22:
            ret = true;
            break;
        }
    default:
        switch (ptNo) {
        case 6:
        case 7:
        case 8:
        case 0xb:
            ret = true;
            break;
        }
        break;
    }
    if (ret == true) {
        if (blockType_[FieldActionCalculate::getDir8RotIdx(dir4 * 2, -1)] == 8 || blockType_[FieldActionCalculate::getDir8RotIdx(dir4 * 2, 1)] == 8) {
            return true;
        }
    }
    if (blockType_[dir4 * 2] == 0xe) {
        return true;
    }
    return false;
}

THUMB void fld::FieldActionBase::endlessMove(dss::Fix32 rate1, dss::Fix32 rate2, short no)
{
    dss::Fix32Vector3 balVec[8] = {
        dss::Fix32Vector3(balSpeed * 0, balSpeed * -1, 0L),
        dss::Fix32Vector3(balXSpeed * 1, balYSpeed * -1, 0L),
        dss::Fix32Vector3(balSpeed * 1, balSpeed * 0, 0L),
        dss::Fix32Vector3(balXSpeed * 1, balYSpeed * 1, 0L),
        dss::Fix32Vector3(balSpeed * 0, balSpeed * 1, 0L),
        dss::Fix32Vector3(balXSpeed * -1, balYSpeed * 1, 0L),
        dss::Fix32Vector3(balSpeed * -1, balSpeed * 0, 0L),
        dss::Fix32Vector3(balXSpeed * -1, balYSpeed * -1, 0L),
    };
    int padInput = FieldPlayerManager::getSingleton().getPadInput();
    int dirInput = FieldPlayerManager::getSingleton().getDirInput();
    if (no != -1) {
        dirIdx_ = no;
        speed_ = balVec[no] * rate1;
    } else if (padInput) {
        dirIdx_ = (dirInput / 0x2000) & 7;
        if (dirIdx_ % 2 == 0) {
            speed_ = balVec[dirIdx_] * rate1;
        } else {
            speed_ = balVec[dirIdx_] * rate2;
        }
    }
    positionN_ = position_ + speed_;
}

THUMB bool fld::FieldActionBase::checkGetOut()
{
    if (dss::g_Pad.edge() & 0x403) {
        if (isGetOffAttr() == true) {
            return true;
        }
        FieldWindowSystem::getSingleton()->openCommonMessage();
        FieldWindowSystem::getSingleton()->addCommonMessage(0xc4290);
    }
    return false;
}

THUMB bool fld::FieldActionBase::isGetOffAttr()
{
    int id;
    int index = FieldStage::getSingleton()->getSearchSymbolAttach(position_, &id);
    if (index >= 0 && id != 0) {
        return false;
    }
    int blkX = position_.vx.value / 0x10000;
    int blkY = position_.vy.value / 0x10000;
    int attr = FieldStage::getSingleton()->getBlockAttr2(blkX, blkY);
    switch (attr) {
    case 1:
    case 2:
    case 3:
    case 0xe:
        return true;
    case 7: {
        index = FieldStage::getSingleton()->getFieldData().getWorldMap().getWorldNo(blkX, blkY);
        if (FieldStage::getSingleton()->getBlockAttr2(blkX, blkY - 1) == 8 || FieldStage::getSingleton()->getBlockAttr2(blkX, blkY - 1) == 9 || isKaigFix(0, index) == true) {
            if (position_.vy.value < (((blkY << 4) + 9) << 12)) {
                return false;
            }
        }
        if (FieldStage::getSingleton()->getBlockAttr2(blkX, blkY + 1) == 8 || FieldStage::getSingleton()->getBlockAttr2(blkX, blkY + 1) == 9 || isKaigFix(2, index) == true) {
            if (position_.vy.value > ((((blkY + 1) << 4) - 9) << 12)) {
                return false;
            }
        }
        if (FieldStage::getSingleton()->getBlockAttr2(blkX + 1, blkY) == 8 || FieldStage::getSingleton()->getBlockAttr2(blkX + 1, blkY) == 9 || isKaigFix(1, index) == true) {
            if (position_.vx.value > ((((blkX + 1) << 4) - 9) << 12)) {
                return false;
            }
        }
        if (FieldStage::getSingleton()->getBlockAttr2(blkX - 1, blkY) == 8 || FieldStage::getSingleton()->getBlockAttr2(blkX - 1, blkY) == 9 || isKaigFix(3, index) == true) {
            if (position_.vx.value < (((blkX << 4) + 9) << 12)) {
                return false;
            }
        }
        return true;
    }
    }
    return false;
}
