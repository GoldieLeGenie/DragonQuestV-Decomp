#include "ov001/town/player/TownActionTruck.hpp"

THUMB void twn::TownTruckRail::initialize()
{
    for (int i = 0; i < 3; i++) {
        link_[i] = 999;
    }
    flag_.clear();
    index_ = 0;
    jumpIndex_ = 0;
    jumpMap_ = 0;
    linkCount_ = 0;
    cutlink_ = 999;
    root_ = 999;
}

THUMB void twn::TownTruckRail::setData(short index, short flag, short jumpIndex, short jumpMap)
{
    index_ = index;
    flag_.flag_ |= flag;
    jumpIndex_ = jumpIndex;
    jumpMap_ = jumpMap;
}

THUMB void twn::TownTruckRail::pushLink(short link)
{
    for (int i = 0; i < linkCount_; i++) {
        if (link_[i] == link) {
            return;
        }
    }
    link_[linkCount_] = link;
    linkCount_++;
}

THUMB void twn::TownTruckRail::setupSwitch(int linkIndex)
{
    for (int i = 0; i < 3; i++) {
        if (link_[i] != root_ && link_[i] != linkIndex) {
            cutlink_ = link_[i];
            return;
        }
    }
}

THUMB void twn::TownTruckRail::changeSwitch()
{
    for (int i = 0; i < 3; i++) {
        if (link_[i] != 999 && link_[i] != root_ && link_[i] != cutlink_) {
            cutlink_ = link_[i];
            return;
        }
    }
}
