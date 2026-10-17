#include "ov005/fld/FieldSystem.hpp"

inline void args::CommandObjectManager::setCommandState(int state)
{
    state_ = state;
}

THUMB fld::FieldSystemCommand::FieldSystemCommand()
{
}

THUMB fld::FieldSystemCommand::~FieldSystemCommand()
{
}

THUMB void fld::FieldSystemCommand::initialize()
{
    commandObjectManager_.initialize();
    commandObjectManager_.enRegister(fieldCommandScreenEffect_, CScreenEffectPriority);
    commandObjectManager_.enRegister(fieldCommandEncount_, CEncountPriority);
    commandObjectManager_.enRegister(fieldCommandPartChange_, CPartChangePriority);
    commandObjectManager_.enRegister(fieldCommandMessage_, CMessagePriority);
    commandObjectManager_.enRegister(fieldCommandPlayer_, CPlayerPriority);
    commandObjectManager_.enRegister(fieldCommandEvent_, CEventPriority);
    commandObjectManager_.enRegister(fieldCommandMaterielMenu_, CMaterielMenuPriority);
    commandObjectManager_.enRegister(fieldCommandMenu_, CMenuPriority);
    commandObjectManager_.enRegister(fieldCommandBookingMenu_, CBookingMenuPriority);
    commandObjectManager_.enRegister(rieldCommandPartyTalk_, CPartyTalkPriority);
    commandObjectManager_.enRegister(fieldCommandNormal_, CNormalPriority);
    commandObjectManager_.enRegister(fieldCommandMenuSearch_, CMenuSearchPriority);
    commandObjectManager_.enRegister(fieldCommandButtonSearch_, CButtonSearch);
    commandObjectManager_.enRegister(fieldCommandWalkCount_, CWalkCountPriority);
    commandObjectManager_.enRegister(fieldCommandAreaMap_, CButtonAreaMap);
    commandObjectManager_.enRegister(fieldCommandVehicle_, CFieldVehicle);
    commandObjectManager_.enRegister(fieldCommandBookingTownMenu_, CBookingTownMenuPriority);
    commandObjectManager_.enRegister(fieldCommandMapLink_, CMapLinkPriority);
    commandObjectManager_.setCommandState(CNormalPriority);
    args::GameSystemManager::getSingleton().setExclusion(FieldSystem::CommandPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(FieldSystem::MenuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(FieldSystem::MaterielMenuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(FieldSystem::MessagePriority, false);
    args::GameSystemManager::getSingleton().setExclusion(FieldSystem::StagePriority, false);
    args::GameSystemManager::getSingleton().setExclusion(FieldSystem::PlayerPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(FieldSystem::ScriptPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(FieldSystem::MapDrawPriority, true);
}

THUMB void fld::FieldSystemCommand::terminate()
{
}

THUMB void fld::FieldSystemCommand::execute()
{
    commandObjectManager_.execute();
}

THUMB void fld::FieldSystemCommand::draw()
{
}
