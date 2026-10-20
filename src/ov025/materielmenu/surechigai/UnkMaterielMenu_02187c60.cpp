#pragma ipa file
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c60.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c7c.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187cb4.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/leveldata/SurechigaiData.hpp"
#include "main/menu/MaterielMenu_NameEdit.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void UnkMaterielMenu_02187c60::menuExecute()
{
}

inline dq5::level::SurechigaiData* dq5::level::SurechigaiData::getRecord(int index)
{
    return (SurechigaiData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

THUMB void UnkMaterielMenu_02187c60::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    status::g_Menu.drawFlag_ = 0;
    unk_1c = MaterielMenu_WINDOW_MANAGER::getSingleton()->editMessageForScript_;
    unk_24 = dq5::level::SurechigaiData::getRecord(status::g_MuseumStatus.playerTaishi_.objectId_)->cgicon;
    for (int i = 0; i < 0x88; i++) {
        unk_26[i] = 0;
    }
    unk_20 = 0;
    mode_ = 0;
    gMaterielMenu_NameEdit.open();
    gMaterielMenu_NameEdit.clearName();
    if (unk_af == 0) {
        gMaterielMenu_NameEdit.setTaishiNameMode();
        gMaterielMenu_NameEdit.setDefaultName(status::g_MuseumStatus.playerTaishi_.taishiName_);
        return;
    }
    gMaterielMenu_NameEdit.setMessageMode();
    gMaterielMenu_NameEdit.setDefaultName(status::g_MuseumStatus.playerTaishi_.message_);
    dss::strcpy_s(unk_26, 0x88, status::g_MuseumStatus.playerTaishi_.message_);
}

THUMB void UnkMaterielMenu_02187c60::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (unk_20 == 0) {
        unkfunc_0217c4e4(gTownMenu_MESSAGE.isOpen(), unk_af, unk_24);
    }
}

THUMB void UnkMaterielMenu_02187c60::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            unkfunc_02186c38();
        } else if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            unkfunc_02186d58();
        }
        unk_20 = 0;
        return;
    }
    switch (MaterielMenu_NameEdit::status_) {
        case MaterielMenu_NameEdit::ERROR_S:
            unk_20 = 1;
            if (unk_1c == 1) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xcc5b4);
                return;
            }
            cmn::g_talkSound.setOrderMessage(0x30);
            cmn::g_talkSound.setMessageSound(1, -1);
            gTownMenu_MESSAGE.openMessageForTALK();
            if (unk_af == 0) {
                gTownMenu_MESSAGE.addMessage(0xcc5ab);
            } else {
                gTownMenu_MESSAGE.addMessage(0xcc5b4);
            }
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(cmn::g_cmnPartyInfo.ctrlID_));
            return;
        case MaterielMenu_NameEdit::COMPLETE:
            if (unk_af == 0) {
                status::g_MuseumStatus.playerTaishi_.setTaishiName(gMaterielMenu_NameEdit.getNameUTF8());
                close();
                data_ov019_02185900.open();
                if (unk_1c == 0 && MaterielMenu_WINDOW_MANAGER::getSingleton()->menuType_ != MaterielMenu_WINDOW_MANAGER::MENU_SURECHIGAI_MAKE_TAISHI) {
                    data_ov019_02185900.unk_24 = 1;
                }
            } else if (unk_af == 1) {
                status::g_MuseumStatus.playerTaishi_.setTaishiMessage(gMaterielMenu_NameEdit.getNameUTF8());
                TextAPI::setUserString(0, status::g_MuseumStatus.playerTaishi_.taishiName_);
                TextAPI::setMACRO0(0x8f, 0xd0000000, 0);
                if (unk_1c == 1) {
                    gTownMenu_MESSAGE.openMessageForMENU();
                    gTownMenu_MESSAGE.addMessage(0xcc5cd);
                } else {
                    gTownMenu_MESSAGE.openMessageForTALK();
                    gTownMenu_MESSAGE.addMessage(0xcc5b6);
                }
                gTownMenu_MESSAGE.setYesNo();
                mode_ = 6;
            }
            break;
        case MaterielMenu_NameEdit::CANCEL:
            if (unk_1c == 1) {
                gTownMenu_MESSAGE.openMessageForMENU();
                TextAPI::setUserString(0, status::g_MuseumStatus.playerTaishi_.taishiName_);
                TextAPI::setMACRO0(0x8f, 0xd0000000, 0);
                gTownMenu_MESSAGE.addMessage(0xcc5d0);
                unk_af = 2;
                mode_ = 9;
                return;
            }
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xcc5b1);
            unk_af = 0;
            mode_ = 2;
            break;
        case MaterielMenu_NameEdit::EDIT_INIT:
        case MaterielMenu_NameEdit::EXEC:
            break;
    }
}

THUMB void UnkMaterielMenu_02187c60::unkfunc_02186c38()
{
    switch (mode_) {
        case 0:
            gMaterielMenu_NameEdit.open();
            gMaterielMenu_NameEdit.clearName();
            if (unk_af == 0) {
                gMaterielMenu_NameEdit.setTaishiNameMode();
                gMaterielMenu_NameEdit.setDefaultName(status::g_MuseumStatus.playerTaishi_.taishiName_);
                return;
            }
            gMaterielMenu_NameEdit.setMessageMode();
            status::g_MuseumStatus.playerTaishi_.setTaishiMessage(unk_26);
            gMaterielMenu_NameEdit.setDefaultName(status::g_MuseumStatus.playerTaishi_.message_);
            break;
        case 2:
            status::g_MuseumStatus.recoveryTaishi();
            close();
            data_ov019_021854d4.open();
            if (unk_1c == 0 && MaterielMenu_WINDOW_MANAGER::getSingleton()->menuType_ != MaterielMenu_WINDOW_MANAGER::MENU_SURECHIGAI_MAKE_TAISHI) {
                data_ov019_021854d4.unk_24 = 1;
            }
            break;
        case 6:
            if (unk_1c == 1) {
                TextAPI::setUserString(0, status::g_MuseumStatus.playerTaishi_.taishiName_);
                TextAPI::setMACRO0(0x8f, 0xd0000000, 0);
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xcc5ce);
            } else {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xcc5b7);
                status::g_MuseumStatus.playerTaishi_.isTaishi_ = 1;
            }
            unk_af = 2;
            mode_ = 9;
            break;
        case 9:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->changeTaishi_ = unk_1c == 0 ? 1 : 0;
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void UnkMaterielMenu_02187c60::unkfunc_02186d58()
{
    if (mode_ == 6) {
        if (unk_1c == 1) {
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xcc5c8);
        } else {
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xcc5ba);
        }
        mode_ = 0;
    }
}
