#include "main/town/TownTruckData.hpp"
#include "main/global/Global.hpp"
#include "ov001/town/TownStageManager.hpp"

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int twn::TownStageManager::eventAnim(int event, int objID)
{
    return stage_.eventAnim(event, objID);
}

THUMB void twn::TownTruckSeesaw::setup()
{
    switchIndex_[0] = 0x3de;
    switchIndex_[1] = 0x3df;
    link_ = 0x3de;
    switchAnim_ = 1;
    uid_ = 0x1f5;
}

THUMB bool twn::TownTruckSeesaw::setupAnim()
{
    if (g_Global.getMapNameId() != 0x149) {
        return false;
    }
    if (switchAnim_ == 3) {
        TownStageManager::getSingleton()->eventAnim(0, 0);
        TownStageManager::getSingleton()->eventAnim(3, 0);
        return true;
    }
    return false;
}

THUMB bool twn::TownTruckSeesaw::isSeesawIndex(int index)
{
    if (index == link_) {
        return true;
    }
    return false;
}

THUMB void twn::TownTruckSeesaw::seesawSwitch(bool anim)
{
    for (int i = 0; i < 2; i++) {
        if (link_ != switchIndex_[i]) {
            link_ = switchIndex_[i];
            if (switchAnim_ == 1) {
                if (g_Global.getMapNameId() == 0x149) {
                    if (anim == true) {
                        TownStageManager::getSingleton()->eventAnim(0, 0);
                        TownStageManager::getSingleton()->eventAnim(2, 0);
                    } else {
                        TownStageManager::getSingleton()->eventAnim(0, 0);
                        TownStageManager::getSingleton()->eventAnim(3, 0);
                    }
                }
                switchAnim_ = 3;
            } else {
                if (g_Global.getMapNameId() == 0x149 && anim == true) {
                    TownStageManager::getSingleton()->eventAnim(0, 0);
                    TownStageManager::getSingleton()->eventAnim(4, 0);
                }
                switchAnim_ = 1;
            }
            return;
        }
    }
}
