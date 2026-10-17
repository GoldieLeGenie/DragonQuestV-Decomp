#include "ov012/casino/Casino_SlotReel.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/sound/SoundManager.hpp"

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::SlotDrum* dq5::level::SlotDrum::getRecord(int index)
{
    return (SlotDrum*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::SlotDrum::getArraySize()
{
    return binary_.getRecordCount();
}

inline int dq5::level::SlotDrum::getName()
{
    return name;
}

THUMB casino::Casino_SlotReel::Casino_SlotReel()
{
    rollCount_ = 0;
    rollPosition_ = 0;
    rollFirstPosition_ = 0;
    rollStopPosition_ = -1;
    rollState_ = ROLLING;
    rollSpeed_ = 0;
    deBoostPosition_ = 0;
    deBoostFlag_ = false;
}

THUMB casino::Casino_SlotReel::~Casino_SlotReel()
{
}

THUMB void casino::Casino_SlotReel::setReel(int table)
{
    rollCount_ = 0;
    rollSpeed_ = 0;
    rollState_ = ROLLING;
    tableNo_ = table;
    rollStopPosition_ = -1;
    rollFirstPosition_ = 0x10000;
    rollPosition_ = 0x10000;
    drumPos_ = 0;
    unsigned int maxDrum = dq5::level::SlotDrum::getArraySize();
    int i = 0;
    while (i < maxDrum) {
        int drumName = dq5::level::SlotDrum::getRecord(i)->getName();
        if (drumName - 1 == table) {
            drumPos_ = i;
            return;
        }
        i++;
    }
}

THUMB void casino::Casino_SlotReel::setStopImageNum(int num)
{
    num += (num >= MAX_REEL_SIZE) ? -MAX_REEL_SIZE : 0;
    num += (num < 0) ? MAX_REEL_SIZE : 0;
    setStopPosition(num * IMAGE_SIZE);
}

THUMB void casino::Casino_SlotReel::setStopPosition(int position)
{
    rollStopPosition_ = position;
    int count = searchDeBoost(REEL_UNDER_SPEED);
    deBoostPosition_ = rollStopPosition_ - count * IMAGE_SIZE;
    if (deBoostPosition_ < 0) {
        deBoostPosition_ += 0x10000;
    }
    deBoostFlag_ = false;
}

THUMB void casino::Casino_SlotReel::resetReel()
{
    rollSpeed_ = 0;
    rollState_ = ROLLING;
    rollCount_ = 0;
    subRollCount_ = 0;
    rollFirstPosition_ = rollPosition_;
    rollStopPosition_ = -1;
    deBoostPosition_ = 0;
    deBoostFlag_ = false;
}

THUMB casino::Casino_SlotReel::SLOT_ROLL_STATE casino::Casino_SlotReel::scrollReel()
{
    if (rollState_ == ROLLING) {
        rollSpeedUp();
        reelRolling();
        if (deBoostFlag_ && rollCount_ >= MIN_ROLL_COUNT) {
            if (checkPassingPoint(deBoostPosition_)) {
                if (subRollCount_ + 1 <= rollCount_) {
                    rollState_ = BRAKE;
                }
            }
        } else {
            subRollCount_ = rollCount_;
        }
    } else if (rollState_ == BRAKE) {
        rollSpeedDown();
        reelRolling();
        if (checkPassingPoint(rollStopPosition_) && rollSpeed_ == REEL_UNDER_SPEED) {
            SoundManager::playSe(0x159, 0);
            rollState_ = STOP;
            rollPosition_ = rollStopPosition_;
        }
    } else if (rollState_ == STOP) {
        return rollState_;
    }
    if (checkPassingPoint(rollFirstPosition_)) {
        rollCount_++;
    }
    return rollState_;
}

THUMB void casino::Casino_SlotReel::rollSpeedUp()
{
    if (rollSpeed_ >= REEL_TOP_SPEED) {
        return;
    }
    int speed = rollSpeed_ + REEL_UNDER_SPEED;
    rollSpeed_ = speed + (speed >> 4);
    if (rollSpeed_ > REEL_TOP_SPEED) {
        rollSpeed_ = REEL_TOP_SPEED;
    }
}

THUMB void casino::Casino_SlotReel::rollSpeedDown()
{
    if (rollSpeed_ <= REEL_UNDER_SPEED) {
        return;
    }
    rollSpeed_ -= rollSpeed_ >> 5;
    if (rollSpeed_ < REEL_UNDER_SPEED) {
        rollSpeed_ = REEL_UNDER_SPEED;
    }
}

THUMB void casino::Casino_SlotReel::reelRolling()
{
    rollPosition_ += rollSpeed_;
    if (rollPosition_ > 0x10000) {
        rollPosition_ -= 0x10000;
    }
}

THUMB bool casino::Casino_SlotReel::checkPassingPoint(int point)
{
    int prev = rollPosition_ - rollSpeed_;
    if (prev < 0) {
        if (rollPosition_ >= point || prev + 0x10000 <= point) {
            return true;
        }
    } else if (rollPosition_ >= point && prev <= point) {
        return true;
    }
    return false;
}

THUMB int casino::Casino_SlotReel::getImageNum(REEL_POS pos)
{
    int num = rollPosition_ / IMAGE_SIZE;
    if (rollPosition_ % IMAGE_SIZE > IMAGE_SIZE / 2) {
        num++;
    }
    switch (pos) {
    case REEL_POS_BOTTOM:
        num--;
        if (num < 0) {
            num += MAX_REEL_SIZE;
        }
        break;
    case REEL_POS_TOP:
        num++;
        if (num > MAX_REEL_SIZE) {
            num -= MAX_REEL_SIZE;
        }
        break;
    }
    return num;
}

THUMB int casino::Casino_SlotReel::searchDeBoost(int speed)
{
    int current = REEL_TOP_SPEED;
    int distance = 0;
    for (;;) {
        if (current <= speed) {
            break;
        }
        current -= current >> 5;
        distance += current;
    }
    return (distance + REEL_TOP_SPEED) / IMAGE_SIZE + 1;
}

THUMB dq5::level::SlotDrum* casino::Casino_SlotReel::getDrumData(int num)
{
    return dq5::level::SlotDrum::getRecord(drumPos_ + num);
}

THUMB unsigned char casino::Casino_SlotReel::getDrumImage(int num)
{
    if (num != 0) {
        num -= MAX_REEL_SIZE;
    }
    num = dss::abs<int>(num);
    switch (reelNumber_) {
    case 0:
        return getDrumData(num)->drum1;
    case 1:
        return getDrumData(num)->drum2;
    case 2:
        return getDrumData(num)->drum3;
    case 3:
        return getDrumData(num)->drum4;
    case 4:
        return getDrumData(num)->drum5;
    }
    return 0;
}
