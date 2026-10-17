#include "ov019/materielmenu/common/MaterielMenu_ChildName.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/menu/MaterielMenu_NameEdit.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/status/PlayerData.hpp"

inline void MaterielMenu_NameEdit::setNonCancelMode()
{
    cancelLock_ = 1;
}

inline void MaterielMenu_NameEdit::setInputType(INPUT_TYPE type)
{
    inputType_ = type;
}

inline char* status::PlayerData::getNameString()
{
    return name_;
}

THUMB void MaterielMenu_ChildName::menuSetup()
{
    if (!gMaterielMenu_NameEdit.isOpen()) {
        gMaterielMenu_NameEdit.open();
        gMaterielMenu_NameEdit.clearName();
        gMaterielMenu_NameEdit.setNonCancelMode();
    }
    gMaterielMenu_NameEdit.setInputType(MaterielMenu_NameEdit::TYPE_NAME_EDIT);
    childType_ = 13;
}

THUMB void MaterielMenu_ChildName::menuExecute()
{
}

THUMB void MaterielMenu_ChildName::menuDraw()
{
}

THUMB void MaterielMenu_ChildName::menuUpdate()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (!gMaterielMenu_NameEdit.isOpen()) {
                gMaterielMenu_NameEdit.open();
            }
        }
        return;
    }
    switch (MaterielMenu_NameEdit::status_) {
        case MaterielMenu_NameEdit::EDIT_INIT:
        case MaterielMenu_NameEdit::EXEC:
            break;
        case MaterielMenu_NameEdit::ERROR_S:
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xcb5f3);
            break;
        case MaterielMenu_NameEdit::COMPLETE:
            if (MenuAPI::judgeReserveWord(gMaterielMenu_NameEdit.getNameUTF8()) == true
                || MenuAPI::judgeRepeatWord((unsigned char*)gMaterielMenu_NameEdit.getNameUTF8()) == true
                || MenuAPI::judgeOverlapWord((unsigned char*)gMaterielMenu_NameEdit.getNameUTF8()) == true) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xcb5f3);
                break;
            }
            if (childType_ == 13) {
                status::PlayerDataAll::playerData_[13].setNameString(gMaterielMenu_NameEdit.getNameUTF8());
            } else {
                status::PlayerDataAll::playerData_[14].setNameString(gMaterielMenu_NameEdit.getNameUTF8());
            }
            close();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
        case MaterielMenu_NameEdit::CANCEL:
            gMaterielMenu_NameEdit.open();
            break;
    }
}

THUMB void MaterielMenu_ChildName::setChildType(int type)
{
    childType_ = type;
    gMaterielMenu_NameEdit.setDefaultName(status::PlayerDataAll::playerData_[type].getNameString());
}
