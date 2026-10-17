#include "ov019/materielmenu/common/MaterielMenu_LoadName.hpp"
#include "ov036/materielmenu/common/MaterielMenu_LOAD.hpp"
#include "main/menu/MaterielMenu_NameEdit.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/status/PlayerData.hpp"

inline void MaterielMenu_NameEdit::setInputType(INPUT_TYPE type)
{
    inputType_ = type;
}

THUMB void MaterielMenu_LoadName::menuSetup()
{
    if (!gMaterielMenu_NameEdit.isOpen()) {
        gMaterielMenu_NameEdit.open();
        gMaterielMenu_NameEdit.clearName();
    }
    gMaterielMenu_NameEdit.setInputType(MaterielMenu_NameEdit::TYPE_NAME_EDIT);
}

THUMB void MaterielMenu_LoadName::menuExecute()
{
}

THUMB void MaterielMenu_LoadName::menuDraw()
{
}

THUMB void MaterielMenu_LoadName::menuUpdate()
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
                || MenuAPI::judgeRepeatWord((unsigned char*)gMaterielMenu_NameEdit.getNameUTF8()) == true) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xcb5f3);
                break;
            }
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessageNOWAIT(0xcb5f7);
            gTownMenu_MESSAGE.addMessageWAITKEY();
            status::PlayerDataAll::playerData_[1].setNameString(gMaterielMenu_NameEdit.getNameUTF8());
            gMaterielMenu_LOAD.open();
            gMaterielMenu_LOAD.changeStatus(MaterielMenu_LOAD::LOAD_WRITECHECK);
            close();
            break;
        case MaterielMenu_NameEdit::CANCEL:
            gMaterielMenu_LOAD.open();
            gMaterielMenu_LOAD.changeStatus(MaterielMenu_LOAD::LOAD_MODESELECT);
            close();
            break;
    }
}
