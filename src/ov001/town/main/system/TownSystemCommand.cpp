#pragma ipa file
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageEffectManager.hpp"
#include "ov001/town/TownSugorokuManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/window/MenuControl.hpp"
#include "main/window/MessageControl.hpp"
#include "main/window/ShopMenuControl.hpp"

#pragma thumb on

inline void args::CommandObjectManager::setCommandState(int state)
{
    state_ = state;
}

inline bool window::MenuControl::isMenuEnd()
{
    return state_ == MENU_END;
}

inline bool window::MessageControl::isMessageEnd()
{
    return state_ == END_MESSAGE;
}

inline bool window::ShopMenuControl::isMenuStart()
{
    return state_ == 7;
}

inline bool window::ShopMenuControl::isMenuEnd()
{
    return state_ == 8;
}

inline int status::StageInfo::getReliveMessageFlag()
{
    return reliveMessageFlag_;
}

inline void status::StageInfo::setReliveMessageFlag(bool flag)
{
    reliveMessageFlag_ = flag;
}

inline cmn::MENU_ACTION cmn::CommonPartyInfo::getMenuAction()
{
    return menuAction_;
}

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline bool twn::TownStageEffectManager::isTrap()
{
    return wire_.isTrap();
}

inline bool twn::TownStageEffectManager::isPuzzleMove()
{
    return puzzle_.checkPuzzleMove();
}

inline bool twn::TownStageEffectManager::isMovable()
{
    return puzzle_.checkMovable();
}

inline int twn::TownPlayerManager::isRemote()
{
    return remoteFlag_;
}

twn::TownSystemCommand::TownSystemCommand()
{
}

twn::TownSystemCommand::~TownSystemCommand()
{
}

void twn::TownSystemCommand::initialize()
{
    commandObjectManager_.initialize();
    commandObjectManager_.enRegister(townCommandScreenEffect_, 1);
    commandObjectManager_.enRegister(townMessageCommand_, 4);
    commandObjectManager_.enRegister(townMenuCommand_, 27);
    commandObjectManager_.enRegister(townMapDrawCommand_, 28);
    commandObjectManager_.enRegister(townSugorokuCommand_, 18);
    commandObjectManager_.enRegister(townMaterielMenuCommand, 15);
    commandObjectManager_.enRegister(townPlayerMoveCommand_, 16);
    commandObjectManager_.enRegister(townNormalCommand_, 30);
    commandObjectManager_.enRegister(townCommandEncount_, 23);
    commandObjectManager_.enRegister(townShopListDrawCommand, 8);
    commandObjectManager_.enRegister(townCommandButtonTalk_, 24);
    commandObjectManager_.enRegister(townCommandButtonSearch_, 25);
    commandObjectManager_.enRegister(townCommandPartChange_, 0);
    commandObjectManager_.enRegister(townCommandInitWait_, 20);
    commandObjectManager_.enRegister(townCommandMenuSearch_, 13);
    commandObjectManager_.enRegister(townCommandMenuTalk_, 12);
    commandObjectManager_.enRegister(townCommandEvent_, 19);
    commandObjectManager_.enRegister(townCommandPartyTalk_, 29);
    commandObjectManager_.enRegister(townCommandWalkCount_, 22);
    commandObjectManager_.enRegister(townCommandLink_, 17);
    commandObjectManager_.enRegister(townCommandBookingMenu_, 11);
    commandObjectManager_.enRegister(townCommandFukubikiDraw_, 9);
    commandObjectManager_.enRegister(townTreasureRoomCommand_, 26);
    commandObjectManager_.enRegister(townCommandBookingTownMenu_, 10);
    commandObjectManager_.enRegister(townCommandComebackChurch_, 6);
    commandObjectManager_.enRegister(townCommandRestartGame_, 5);
    commandObjectManager_.enRegister(townCommandScope_, 2);
    commandObjectManager_.enRegister(townCommandCoercionSort_, 7);
    commandObjectManager_.enRegister(townPlayerLockCommand_, 21);
    commandObjectManager_.enRegister(townCommandPlaySound_, 3);
    commandObjectManager_.setCommandState(30);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::ScreenEffectPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::CommandPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::MenuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::MessagePriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::MaterielMenuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::DrawTownMapPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::SugorokuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::CameraPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::StagePriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::FurniturePriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::RiseupPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::PlayerPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::CharacterPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::ScriptPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::DrawTownMapPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::DrawTownShopListPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::GlobalMapPriority, false);
}

void twn::TownSystemCommand::terminate()
{
}

void twn::TownSystemCommand::execute()
{
    commandObjectManager_.execute();
}

void twn::TownSystemCommand::draw()
{
}

int twn::TownMenuCommand::isExec()
{
    if (dss::g_Pad.edge() & 0x400) {
        if (!fadeEffector.isFadeEnd()) {
            return false;
        }
        window::gMenuControl.openSetup();
        return true;
    }
    return false;
}

int twn::TownMenuCommand::isEnd()
{
    return window::gMenuControl.isMenuEnd();
}

void twn::TownMenuCommand::exec()
{
    CommandObjectDefineTownSystem::setXmenu();
}

int twn::TownMessageCommand::isExec()
{
    if (TownWindowSystem::getSingleton().isMessageStart()) {
        window::gMessageControl.startMessage();
        TownWindowSystem::getSingleton().setMessageFlag(false);
        return true;
    }
    return false;
}

int twn::TownMessageCommand::isEnd()
{
    if (window::gMessageControl.isMessageEnd()) {
        if (status::g_StageInfo.getReliveMessageFlag() == true) {
            switch (data_0211b27c.state_) {
            case FadeEffector::FADE_NONE:
                data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
                break;
            case FadeEffector::FADE_IN_BLACK:
                data_0211b27c.state_ = FadeEffector::FADE_OUT_WHITE;
                break;
            default:
                data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
                break;
            }
            data_0211b27c.count_ = 0;
            data_0211b27c.frames_ = 30;
            data_02101d14.addPart(&data_0211b27c);
            status::g_StageInfo.setReliveMessageFlag(false);
            SoundManager::townPlay(TownSystem::getFloorBgmIndex());
        }
        return true;
    }
    return false;
}

void twn::TownMessageCommand::exec()
{
    CommandObjectDefineTownSystem::setMessage();
}

int twn::TownMaterielMenuCommand::isExec()
{
    if (window::gShopMenuControl.isMenuStart()) {
        window::gShopMenuControl.setup();
        return true;
    }
    return false;
}

int twn::TownMaterielMenuCommand::isEnd()
{
    return window::gShopMenuControl.isMenuEnd();
}

void twn::TownMaterielMenuCommand::exec()
{
    CommandObjectDefineTownSystem::setMateriel();
}

int twn::TownPlayerLockCommand::isExec()
{
    if (TownPlayerManager::getSingleton().isLock() == true) {
        return true;
    }
    return false;
}

int twn::TownPlayerLockCommand::isEnd()
{
    return true;
}

void twn::TownPlayerLockCommand::exec()
{
    CommandObjectDefineTownSystem::setplayerLock();
}

int twn::TownSugorokuCommand::isExec()
{
    return TownSugorokuManager::getSingleton().isSugorokuMode();
}

int twn::TownSugorokuCommand::isEnd()
{
    return true;
}

void twn::TownSugorokuCommand::exec()
{
    CommandObjectDefineTownSystem::setSugoroku();
}

int twn::TownTreasureRoomCommand::isExec()
{
    return TownSugorokuManager::getSingleton().isTreasuerRoom();
}

int twn::TownTreasureRoomCommand::isEnd()
{
    return true;
}

void twn::TownTreasureRoomCommand::exec()
{
    CommandObjectDefineTownSystem::setTreasuerRoom();
}

int twn::TownPlayerMoveCommand::isExec()
{
    cmn::MENU_ACTION action = cmn::g_cmnPartyInfo.getMenuAction();
    if (action != cmn::MENU_ACTION_NONE) {
        TownPlayerManager::getSingleton().setMenuAction(action);
        return true;
    }
    if (g_Global.getNowAreaNo() == 0x33) {
        if (TownStageEffectManager::getSingleton()->isTrap() == true) {
            return true;
        }
    }
    if (g_Global.getMapNameId() == 0x16c) {
        if (TownStageEffectManager::getSingleton()->isPuzzleMove() == true) {
            return true;
        }
        if (TownStageEffectManager::getSingleton()->isMovable()) {
            TownPlayerManager::getSingleton().setLock(true);
            return true;
        }
    }
    TownPlayerManager::getSingleton().update();
    TownPlayerManager::getSingleton().execMapLink();
    if (TownPlayerManager::getSingleton().isRemote() == true) {
        return true;
    }
    if (TownWindowSystem::getSingleton().isMessageStart()) {
        return true;
    }
    return false;
}

int twn::TownPlayerMoveCommand::isEnd()
{
    return true;
}

void twn::TownPlayerMoveCommand::exec()
{
    if (TownWindowSystem::getSingleton().isMessageStart()) {
        CommandObjectDefineTownSystem::setMessage();
    } else {
        CommandObjectDefineTownSystem::setPlayer();
    }
}

int twn::TownNormalCommand::isExec()
{
    status::g_Menu.resetMenuEventNo();
    return true;
}

int twn::TownNormalCommand::isEnd()
{
    return true;
}

void twn::TownNormalCommand::exec()
{
    CommandObjectDefineTownSystem::setNormal();
}
