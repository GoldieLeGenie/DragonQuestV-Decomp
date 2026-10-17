#include "main/btl/EncountScreenOver.hpp"
#include "main/btl/MonsterData.hpp"

THUMB btl::EncountScreenOver::EncountScreenOver()
{
    count_ = 0;
}

THUMB btl::EncountScreenOver::~EncountScreenOver()
{
}

THUMB void btl::EncountScreenOver::setup(int* monsterIndex, int* monsterCount)
{
    monsterIndex_ = monsterIndex;
    monsterCount_ = monsterCount;
}

THUMB void btl::EncountScreenOver::execThinning()
{
    int count = 0;
    while (true) {
        if (!checkScreenOver()) {
            break;
        }
        setThinning(count);
        count++;
    }
}

THUMB bool btl::EncountScreenOver::checkScreenOver()
{
    int allWidth = 0;
    int width;
    for (int i = 0; i < 4; i++) {
        monsterGroupWidth_[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        if (monsterCount_[i] != 0) {
            width = getMonsterWidthInt(monsterIndex_[i]);
            allWidth += width * monsterCount_[i];
            monsterGroupWidth_[i] += width;
        }
    }
    if (allWidth >= 256) {
        return true;
    }
    return false;
}

THUMB void btl::EncountScreenOver::setThinning(int count)
{
    int maxIndex = -1;
    int maxCount = 0;
    for (int i = 0; i < 4; i++) {
        if (monsterCount_[i] >= maxCount) {
            maxCount = monsterCount_[i];
            maxIndex = i;
        }
    }
    if (monsterCount_[maxIndex] >= 2) {
        monsterCount_[maxIndex]--;
        count_++;
    }
    else if (count >= 5 && monsterCount_[maxIndex] >= 1) {
        monsterCount_[maxIndex]--;
        count_++;
    }
}
