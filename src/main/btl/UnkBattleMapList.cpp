#include "main/btl/UnkBattleMapList.hpp"
#include "main/dss/DssUtils.hpp"

THUMB UnkBattleMapList::UnkBattleMapList()
{
    group_ = 0;
    map_ = 0;
    mapIndex_ = 0;
    loaded_ = 0;
}

THUMB UnkBattleMapList::~UnkBattleMapList()
{
}

THUMB void UnkBattleMapList::unkfunc_0206da18(const char* filename)
{
    load(filename, 1);
    group_ = 0;
    map_ = 0;
    mapIndex_ = 0;
    loaded_ = 1;
}

THUMB int UnkBattleMapList::isLoaded()
{
    return loaded_;
}

THUMB char* UnkBattleMapList::getGroupName()
{
    return getText(group_ + map_, 1);
}

THUMB void UnkBattleMapList::nextGroup()
{
    int i = 0;
    char* name = getText(group_ + map_, 1);
    while (true) {
        if (getText(group_ + map_ + i, 1) == NULL) {
            return;
        }
        if (dss::strcmp(name, getText(group_ + map_ + i, 1)) != 0) {
            map_ += i;
            mapIndex_ = 0;
            return;
        }
        i++;
        char* first = getText(group_, 0);
        char* text = getText(group_ + map_ + i, 0);
        if (text == NULL) {
            return;
        }
        if (first[0] != text[0]) {
            return;
        }
    }
}

THUMB void UnkBattleMapList::prevGroup()
{
    int i = 0;
    int offset = 0;
    if (map_ == 0) {
        return;
    }
    char* prev = getText(group_ + map_, 1);
    char* name = getText(group_, 1);
    while (true) {
        char* text = getText(group_ + offset + i, 1);
        if (dss::strcmp(name, text) != 0) {
            if (dss::strcmp(prev, text) == 0) {
                map_ = offset;
                mapIndex_ = 0;
                return;
            }
            offset += i;
            name = getText(group_ + offset, 1);
            i = 0;
        } else {
            i++;
        }
        char* first = getText(group_, 0);
        char* cur = getText(group_ + offset + i, 0);
        if (cur == NULL) {
            return;
        }
        if (first[0] != cur[0]) {
            return;
        }
    }
}

THUMB char* UnkBattleMapList::getMapName()
{
    return getText(group_ + map_ + mapIndex_, 2);
}

THUMB void UnkBattleMapList::nextMap()
{
    getText(group_, 0);
    char* name = getText(group_ + map_, 1);
    if (getText(group_ + map_ + mapIndex_ + 1, 2) == NULL) {
        return;
    }
    char* next = getText(group_ + map_ + mapIndex_ + 1, 2);
    if (dss::strncmp(name, next, dss::strlen(name)) == 0) {
        mapIndex_++;
    }
}

THUMB void UnkBattleMapList::prevMap()
{
    getText(group_, 0);
    char* name = getText(group_ + map_, 1);
    int row = group_ + map_ + mapIndex_ - 1;
    if (row < 0) {
        return;
    }
    char* prev = getText(row, 2);
    if (dss::strncmp(name, prev, dss::strlen(name)) == 0) {
        mapIndex_--;
    }
}
