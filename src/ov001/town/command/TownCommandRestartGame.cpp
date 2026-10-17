#include "ov001/town/command/TownCommandRestartGame.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov019/leveldata/ChurchMessage.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/leveldata/MapChurch.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"

#pragma thumb on

inline dq5::level::MapChurch* dq5::level::MapChurch::getRecord(int index)
{
    return (MapChurch*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline void status::StageInfo::setReliveCheckFlag(bool flag)
{
    reliveCheckFlag_ = flag;
}

inline bool status::StageInfo::isLoadFlag()
{
    return load_;
}

inline void status::StageInfo::setLoadFlag(bool flag)
{
    load_ = flag;
}

inline int status::StageInfo::getLoadChurch()
{
    return loadChurchData_;
}

inline char dq5::level::MapChurch::getChurchman()
{
    return byte_1 & 1;
}

inline unsigned long dq5::level::ChurchMessage::getMessage1()
{
    return message1;
}

inline unsigned long dq5::level::ChurchMessage::getMessage2()
{
    return message2;
}

inline char dq5::level::ChurchMessage::getVocalSound()
{
    return byte_1 & 1;
}

inline dq5::level::ChurchMessage* dq5::level::ChurchMessage::getRecord(int index)
{
    return (ChurchMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

twn::TownCommandRestartGame::TownCommandRestartGame()
{
    wait_ = defaultWait;
}

twn::TownCommandRestartGame::~TownCommandRestartGame()
{
}

int twn::TownCommandRestartGame::isExec()
{
    if (status::g_StageInfo.isLoadFlag()) {
        if (wait_ == defaultWait) {
            TownPlayerManager::getSingleton().setLock(true);
            status::g_Party.setPlayerMode();
            int hero = status::g_Party.getSortIndex(1);
            int hp = 999;
            if (hero != -1) {
                hp = status::g_Party.getPlayerStatus(hero).getHaveStatusInfo().getHp();
            }
            if (hero == -1 || hp == 0) {
                SoundManager::townPlay(TownSystem::getFloorBgmIndex());
            }
            status::g_StageInfo.setReliveCheckFlag(false);
        }
        if (wait_ <= 0) {
            dq5::level::MapChurch::setup();
            dq5::level::ChurchMessage::setup();
            if (dq5::level::MapChurch::getRecord(status::g_StageInfo.getLoadChurch())->getChurchman() == 0) {
                if (dq5::level::ChurchMessage::getRecord(dq5::level::ChurchMessage::CHURCH_MES42)->getVocalSound()) {
                    ui_MsgSndSet(0x32);
                }
                TownWindowSystem::getSingleton().openMessage(dq5::level::ChurchMessage::getRecord(dq5::level::ChurchMessage::CHURCH_MES42)->getMessage1(), 1);
                TownWindowSystem::getSingleton().addCommonMessage(dq5::level::ChurchMessage::getRecord(dq5::level::ChurchMessage::CHURCH_MES43)->getMessage1());
            } else {
                if (dq5::level::ChurchMessage::getRecord(dq5::level::ChurchMessage::CHURCH_MES42)->getVocalSound()) {
                    if (status::g_StageInfo.getLoadChurch() == 0x20) {
                        ui_MsgSndSet(0x31);
                    } else {
                        ui_MsgSndSet(0x32);
                    }
                }
                TownWindowSystem::getSingleton().openMessage(dq5::level::ChurchMessage::getRecord(dq5::level::ChurchMessage::CHURCH_MES42)->getMessage2(), 1);
                TownWindowSystem::getSingleton().addCommonMessage(dq5::level::ChurchMessage::getRecord(dq5::level::ChurchMessage::CHURCH_MES43)->getMessage2());
            }
            TownPlayerManager::getSingleton().setLock(false);
            status::g_StageInfo.setLoadFlag(false);
            wait_ = defaultWait;
            dq5::level::ChurchMessage::cleanup();
            dq5::level::MapChurch::cleanup();
        } else {
            wait_--;
        }
        return true;
    }
    return false;
}

int twn::TownCommandRestartGame::isEnd()
{
    return true;
}

void twn::TownCommandRestartGame::exec()
{
    CommandObjectDefineTownSystem::setLoseReturn();
}
