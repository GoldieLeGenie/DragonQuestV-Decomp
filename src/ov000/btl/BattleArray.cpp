#include "ov000/btl/BattleArray.hpp"
#include "main/btl/MonsterData.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/leveldata/MonsterData.hpp"

inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index) { return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline char dq5::level::MonsterData::getPosition() { return byte_1 & 0x1; }

THUMB btl::BattleArray::BattleArray()
{
}

THUMB btl::BattleArray::~BattleArray()
{
}

THUMB void btl::BattleArray::clear()
{
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        monsterAir_.ctrlArray_[i] = INVALID_CODE;
    }
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        monsterGround_.ctrlArray_[i] = INVALID_CODE;
    }
}

THUMB void btl::BattleArray::setup(int* monsterIndex, int* monsterCount)
{
    clear();
    monsterGround_.count_ = 0;
    monsterAir_.count_ = 0;
    monsterAll_.count_ = 0;
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        monsterGround_.indexArray_[i] = 0;
    }
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        monsterAir_.indexArray_[i] = 0;
    }
    int ctrl = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < monsterCount[i]; j++) {
            dq5::level::MonsterData* monsterData = dq5::level::MonsterData::getRecord(monsterIndex[i]);
            if (!monsterData->getPosition()) {
                monsterGround_.ctrlArray_[monsterGround_.count_] = ctrl;
                monsterGround_.groupArray_[monsterGround_.count_] = i;
                monsterGround_.indexArray_[monsterGround_.count_] = monsterIndex[i];
                monsterGround_.count_++;
                monsterAll_.ctrlArray_[monsterAll_.count_] = ctrl;
            }
            else {
                monsterAir_.ctrlArray_[monsterAir_.count_] = ctrl;
                monsterAir_.groupArray_[monsterAir_.count_] = i;
                monsterAir_.indexArray_[monsterAir_.count_] = monsterIndex[i];
                monsterAir_.count_++;
                monsterAll_.ctrlArray_[monsterAll_.count_] = ctrl;
            }
            monsterAll_.indexArray_[monsterAll_.count_] = monsterIndex[i];
            monsterAll_.groupArray_[monsterAll_.count_] = i;
            monsterAll_.count_++;
            ctrl++;
        }
    }
    setup();
}

THUMB void btl::BattleArray::setup()
{
    monsterGround_.posCount_ = 0;
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        monsterGround_.monsterPosition_[i] = 0;
    }
    for (int i = 0; i < 256; i++) {
        monsterGround_.positionArray_[i] = -1;
    }
    for (int i = 0; i < monsterGround_.count_; i++) {
        int width = getMonsterWidthInt(monsterGround_.indexArray_[i]);
        monsterGround_.monsterPosition_[i] = monsterGround_.posCount_ + width / 2;
        for (int j = 0; j < width; j++) {
            monsterGround_.positionArray_[monsterGround_.posCount_++] = monsterGround_.ctrlArray_[i];
        }
    }
    monsterAir_.posCount_ = 0;
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        monsterAir_.monsterPosition_[i] = 0;
    }
    for (int i = 0; i < 256; i++) {
        monsterAir_.positionArray_[i] = -1;
    }
    for (int i = 0; i < monsterAir_.count_; i++) {
        int width = getMonsterWidthInt(monsterAir_.indexArray_[i]);
        monsterAir_.monsterPosition_[i] = monsterAir_.posCount_ + width / 2;
        for (int j = 0; j < width; j++) {
            monsterAir_.positionArray_[monsterAir_.posCount_++] = monsterAir_.ctrlArray_[i];
        }
    }
    for (int i = 0; i < monsterGround_.count_; i++) {
        int offset = 256 - monsterGround_.posCount_;
        monsterGround_.monsterPosition_[i] += (offset + 1) / 2;
        monsterGround_.monsterPosition_[i] -= 0x80;
    }
    for (int i = 0; i < monsterAir_.count_; i++) {
        int offset = 256 - monsterAir_.posCount_;
        monsterAir_.monsterPosition_[i] += (offset + 1) / 2;
        monsterAir_.monsterPosition_[i] -= 0x80;
    }
    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (monsterGround_.positionArray_[i] == -1) {
            count++;
        }
    }
    char temp[256];
    for (int i = 0; i < 256; i++) {
        temp[i] = -1;
    }
    for (int i = 0; i < 256; i++) {
        if (count / 2 + i >= 256) {
            break;
        }
        temp[count / 2 + i] = monsterGround_.positionArray_[i];
    }
    for (int i = 0; i < 256; i++) {
        monsterGround_.positionArray_[i] = temp[i];
    }
    count = 0;
    for (int i = 0; i < 256; i++) {
        if (monsterAir_.positionArray_[i] == -1) {
            count++;
        }
    }
    for (int i = 0; i < 256; i++) {
        temp[i] = -1;
    }
    for (int i = 0; i < 256; i++) {
        if (count / 2 + i >= 256) {
            break;
        }
        temp[count / 2 + i] = monsterAir_.positionArray_[i];
    }
    for (int i = 0; i < 256; i++) {
        monsterAir_.positionArray_[i] = temp[i];
    }
}

THUMB int btl::BattleArray::getCtrlMonsterGround(int ctrl)
{
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        if (ctrl == monsterGround_.ctrlArray_[i]) {
            return i;
        }
    }
    return -1;
}

THUMB int btl::BattleArray::getCtrlMonsterAir(int ctrl)
{
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        if (ctrl == monsterAir_.ctrlArray_[i]) {
            return i;
        }
    }
    return -1;
}

THUMB int btl::BattleArray::getMonsterPositionGround(int ctrl)
{
    return monsterGround_.monsterPosition_[getCtrlMonsterGround(ctrl)];
}

THUMB int btl::BattleArray::getMonsterPositionAir(int ctrl)
{
    return monsterAir_.monsterPosition_[getCtrlMonsterAir(ctrl)];
}

THUMB void btl::BattleArray::add(const int ctrl, const int monsterGroup, const int monsterIndex)
{
    dq5::level::MonsterData* monsterData = dq5::level::MonsterData::getRecord(monsterIndex);
    if (!monsterData->getPosition()) {
        int index = 0;
        for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
            if (monsterGround_.ctrlArray_[i] == INVALID_CODE) {
                index = i;
                break;
            }
        }
        monsterGround_.ctrlArray_[index] = ctrl;
        monsterGround_.groupArray_[index] = monsterGroup;
        monsterGround_.indexArray_[index] = monsterIndex;
        int width = getMonsterWidthInt(monsterIndex);
        int right = searchRightPosition(monsterGround_.positionArray_, width);
        int left = searchLeftPosition(monsterGround_.positionArray_, width);
        if (dss::abs(right + width / 2 - 0x80) < dss::abs(left - width / 2 - 0x80)) {
            putCtrlInArray(monsterGround_.positionArray_, right, width, ctrl);
            monsterGround_.monsterPosition_[index] = right + width / 2 - 0x80;
        }
        else {
            putCtrlInArray(monsterGround_.positionArray_, left - width, width, ctrl);
            monsterGround_.monsterPosition_[index] = left - width / 2 - 0x80;
        }
    }
    else {
        int index = 0;
        for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
            if (monsterAir_.ctrlArray_[i] == INVALID_CODE) {
                index = i;
                break;
            }
        }
        monsterAir_.ctrlArray_[index] = ctrl;
        monsterAir_.groupArray_[index] = monsterGroup;
        monsterAir_.indexArray_[index] = monsterIndex;
        int width = getMonsterWidthInt(monsterIndex);
        int right = searchRightPosition(monsterAir_.positionArray_, width);
        int left = searchLeftPosition(monsterAir_.positionArray_, width);
        if (dss::abs(right + width / 2 - 0x80) < dss::abs(left - width / 2 - 0x80)) {
            putCtrlInArray(monsterAir_.positionArray_, right, width, ctrl);
            monsterAir_.monsterPosition_[index] = right + width / 2 - 0x80;
        }
        else {
            putCtrlInArray(monsterAir_.positionArray_, left - width, width, ctrl);
            monsterAir_.monsterPosition_[index] = left - width / 2 - 0x80;
        }
    }
}

THUMB void btl::BattleArray::del(int ctrl)
{
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        if (ctrl == monsterGround_.ctrlArray_[i]) {
            monsterGround_.ctrlArray_[i] = INVALID_CODE;
            monsterGround_.groupArray_[i] = INVALID_CODE;
            monsterGround_.indexArray_[i] = INVALID_CODE;
            monsterGround_.monsterPosition_[i] = 0;
            for (int j = 0; j < 256; j++) {
                if (ctrl == monsterGround_.positionArray_[j]) {
                    monsterGround_.positionArray_[j] = -1;
                }
            }
            return;
        }
    }
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        if (ctrl == monsterAir_.ctrlArray_[i]) {
            monsterAir_.ctrlArray_[i] = INVALID_CODE;
            monsterAir_.groupArray_[i] = INVALID_CODE;
            monsterAir_.indexArray_[i] = INVALID_CODE;
            monsterAir_.monsterPosition_[i] = 0;
            for (int j = 0; j < 256; j++) {
                if (ctrl == monsterAir_.positionArray_[j]) {
                    monsterAir_.positionArray_[j] = -1;
                }
            }
            return;
        }
    }
}

THUMB bool btl::BattleArray::isAdd(int monsterIndex)
{
    dq5::level::MonsterData* monsterData = dq5::level::MonsterData::getRecord(monsterIndex);
    if (!monsterData->getPosition()) {
        int width = getMonsterWidthInt(monsterIndex);
        int right = searchRightPosition(monsterGround_.positionArray_, width);
        int left = searchLeftPosition(monsterGround_.positionArray_, width);
        if (right == -1 && left == -1) {
            return false;
        }
    }
    else {
        int width = getMonsterWidthInt(monsterIndex);
        int right = searchRightPosition(monsterAir_.positionArray_, width);
        int left = searchLeftPosition(monsterAir_.positionArray_, width);
        if (right == -1 && left == -1) {
            return false;
        }
    }
    return true;
}

THUMB void btl::BattleArray::changeCtrlId(int oldCtrl, int newCtrl)
{
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        if (oldCtrl == monsterGround_.ctrlArray_[i]) {
            monsterGround_.ctrlArray_[i] = newCtrl;
            for (int i = 0; i < 256; i++) {
                if (oldCtrl == monsterGround_.positionArray_[i]) {
                    monsterGround_.positionArray_[i] = newCtrl;
                }
            }
            return;
        }
    }
    for (int i = 0; i < INDEX_ARRAY_MAX; i++) {
        if (oldCtrl == monsterAir_.ctrlArray_[i]) {
            monsterAir_.ctrlArray_[i] = newCtrl;
            for (int i = 0; i < 256; i++) {
                if (oldCtrl == monsterAir_.positionArray_[i]) {
                    monsterAir_.positionArray_[i] = newCtrl;
                }
            }
            return;
        }
    }
}

THUMB int btl::BattleArray::searchRightPosition(char* ar, int width)
{
    int start = 0x80 - width / 2;
    for (int i = start; i < 256; i++) {
        if ((unsigned char)ar[i] == INVALID_CODE) {
            bool flag = true;
            for (int j = 0; j < width; j++) {
                if (ar[i + j] != -1) {
                    flag = false;
                }
            }
            if (flag) {
                return i;
            }
        }
    }
    return -1;
}

THUMB int btl::BattleArray::searchLeftPosition(char* ar, int width)
{
    int start = width / 2 + 0x80;
    for (int i = start; i > 0; i--) {
        if ((unsigned char)ar[i] == INVALID_CODE) {
            bool flag = true;
            for (int j = 0; j < width; j++) {
                if (ar[i - j] != -1) {
                    flag = false;
                }
            }
            if (flag) {
                return i;
            }
        }
    }
    return -1;
}

THUMB void btl::BattleArray::putCtrlInArray(char* ar, int pos, int width, int ctrl)
{
    for (int i = 0; i < width; i++) {
        ar[pos + i] = ctrl;
    }
}
