#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

// The original TU also emitted ScriptCommand's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "ov001/script/ScriptSurechigaiCommand.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/window/ShopMenuControl.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/leveldata/SurechigaiData.hpp"
#include "main/text/TextAPI.hpp"

#pragma thumb on

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline void window::ShopMenuControl::startMenu(int menuType)
{
    menuType_ = menuType;
    state_ = 7;
}

inline bool window::ShopMenuControl::isMenuEnd()
{
    return state_ == 8;
}

inline int MaterielMenu_WINDOW_MANAGER::getSurechigaiFlag()
{
    return surechigaiStart_;
}

inline void MaterielMenu_WINDOW_MANAGER::setSurechigaiFlag(bool flag)
{
    surechigaiStart_ = flag;
}

inline int MaterielMenu_WINDOW_MANAGER::getChangeTaishiFlag()
{
    return changeTaishi_;
}

inline void MaterielMenu_WINDOW_MANAGER::setChangeTaishiFlag(bool flag)
{
    changeTaishi_ = flag;
}

inline void MaterielMenu_WINDOW_MANAGER::setOpenMenuForScript(bool flag)
{
    editMessageForScript_ = flag;
}

inline void cmn::CommonPartyInfo::setTalkCharaCtrlID(int ctrl)
{
    ctrlID_ = ctrl;
}

inline unsigned char status::TaishiBase::getTaishiObjectId()
{
    return objectId_;
}

inline dq5::level::SurechigaiData* dq5::level::SurechigaiData::getRecord(int index)
{
    return (SurechigaiData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned short dq5::level::SurechigaiData::getCgicon()
{
    return cgicon;
}

inline void ScriptCommandWeakVtable::initialize(char* scriptParam)
{
}

inline int ScriptCommandWeakVtable::isEnd()
{
    return 0;
}

inline void SurechigaiRoot::execute()
{
}

inline void MakeTaishi::execute()
{
}

inline void SurechigaiTaishiMessage::execute()
{
}

inline void SurechigaiTaishiInfo::execute()
{
}

void SurechigaiRoot::initialize(char* scriptParam)
{
    unsigned int* param = (unsigned int*)scriptParam;
    connectFlag_ = param[0];
    connectIndex_ = param[1];
    makeFlag_ = param[2];
    makeIndex_ = param[3];
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setPlayerDirection(ctrl);
    window::gShopMenuControl.startMenu(0x13);
    cmn::g_cmnPartyInfo.setTalkCharaCtrlID(ctrl);
}

int SurechigaiRoot::isEnd()
{
    if (window::gShopMenuControl.isMenuEnd()) {
        if (MaterielMenu_WINDOW_MANAGER::getSingleton()->getSurechigaiFlag() == true) {
            unkfunc_021288f8(connectFlag_, connectIndex_, true);
        } else {
            unkfunc_021288f8(connectFlag_, connectIndex_, false);
        }
        if (MaterielMenu_WINDOW_MANAGER::getSingleton()->getChangeTaishiFlag() == true) {
            unkfunc_021288f8(makeFlag_, makeIndex_, true);
        } else {
            unkfunc_021288f8(makeFlag_, makeIndex_, false);
        }
        MaterielMenu_WINDOW_MANAGER::getSingleton()->setSurechigaiFlag(false);
        MaterielMenu_WINDOW_MANAGER::getSingleton()->setChangeTaishiFlag(false);
        return true;
    }
    return false;
}

SurechigaiRoot gSurechigaiRoot;

void MakeTaishi::initialize(char* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setPlayerDirection(ctrl);
    window::gShopMenuControl.startMenu(0x12);
    cmn::g_cmnPartyInfo.setTalkCharaCtrlID(ctrl);
}

int MakeTaishi::isEnd()
{
    if (window::gShopMenuControl.isMenuEnd()) {
        return true;
    }
    return false;
}

MakeTaishi gMakeTaishi;

void SurechigaiTaishiMessage::initialize(char* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    window::gShopMenuControl.startMenu(0x14);
    MaterielMenu_WINDOW_MANAGER::getSingleton()->setOpenMenuForScript(true);
    cmn::g_cmnPartyInfo.setTalkCharaCtrlID(ctrl);
}

int SurechigaiTaishiMessage::isEnd()
{
    if (window::gShopMenuControl.isMenuEnd()) {
        MaterielMenu_WINDOW_MANAGER::getSingleton()->setOpenMenuForScript(false);
        return true;
    }
    return false;
}

SurechigaiTaishiMessage gSurechigaiTaishiMessage;

void unkfunc_021288f8(unsigned int type, unsigned int index, bool flag)
{
    switch (type) {
    case 0:
        if (flag) {
            g_AreaFlag.set(index);
        } else {
            g_AreaFlag.remove(index);
        }
        break;
    case 1:
        if (flag) {
            g_LocalFlag.set(index);
        } else {
            g_LocalFlag.remove(index);
        }
        break;
    case 2:
        if (flag) {
            g_GlobalFlag.set(index);
        } else {
            g_GlobalFlag.remove(index);
        }
        break;
    }
}

void SurechigaiTaishiInfo::initialize(char* scriptParam)
{
    window::gShopMenuControl.startMenu(0x2a);
}

int SurechigaiTaishiInfo::isEnd()
{
    if (window::gShopMenuControl.isMenuEnd()) {
        MaterielMenu_WINDOW_MANAGER::getSingleton()->setOpenMenuForScript(false);
        return true;
    }
    return false;
}

SurechigaiTaishiInfo gSurechigaiTaishiInfo;

bool cmdRedrawSurechigaiTaishi(void* scriptParam)
{
    dq5::level::SurechigaiData::setup();
    int objectID = status::g_MuseumStatus.playerTaishi_.getTaishiObjectId();
    int itemID = dq5::level::SurechigaiData::getRecord(objectID)->getCgicon();
    int result = status::g_MuseumStatus.setIconByMapObjectID(0x381f, itemID);
    dq5::level::SurechigaiData::cleanup();
    return true;
}

bool cmdSetMacroSpecialty(void* scriptParam)
{
    TextAPI::setUserString(0, status::g_MuseumStatus.playerTaishi_.taishiName_);
    TextAPI::setMACRO0(0x8f, 0xd0000000, 0);
    return true;
}

void ScriptSurechigaiCommand_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
