#include "ov001/town/command/TownCommandCoercionSort.hpp"
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/global/Global.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/leveldata/PlayerCarriage.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"

inline int twn::TownCommandCoercionSort::isEnd()
{
    return true;
}

#pragma thumb on

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline int status::StageInfo::getReliveCheckFlag()
{
    return reliveCheckFlag_;
}

inline void status::StageInfo::setReliveCheckFlag(bool flag)
{
    reliveCheckFlag_ = flag;
}

inline void status::StageInfo::setReliveMessageFlag(bool flag)
{
    reliveMessageFlag_ = flag;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline unsigned short dq5::level::PlayerCarriage::getFloor()
{
    return floor;
}

inline char dq5::level::PlayerCarriage::getMostRelive()
{
    return (byte_1 & 2) >> 1;
}

inline char dq5::level::PlayerCarriage::getRelive()
{
    return (byte_1 & 4) >> 2;
}

inline dq5::level::PlayerCarriage* dq5::level::PlayerCarriage::getRecord(int index)
{
    return (PlayerCarriage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::PlayerCarriage::getArraySize()
{
    return binary_.getRecordCount();
}

int twn::TownCommandCoercionSort::isExec()
{
    if (status::g_StageInfo.getReliveCheckFlag() == true) {
        status::g_StageInfo.setReliveCheckFlag(false);
        status::g_StageInfo.setReliveMessageFlag(false);
        status::g_Party.setPlayerMode();
        if (status::g_Story.getChapter() <= dq5::CHAPTER_YOUNENKI) {
            return false;
        }
        if (status::g_Party.getSortIndex(1) == -1) {
            return false;
        }
        if (status::g_Party.getPlayerStatusForPlayerIndex(1).getHaveStatusInfo().getHp() > 0) {
            return false;
        }
        int carriageOutCount = status::g_Party.getCarriageOutCount();
        bool aliveHuman = false, rebirthHero = false, rebirthFlag = true;
        dq5::level::PlayerCarriage::setup();
        unsigned int max = dq5::level::PlayerCarriage::getArraySize();
        int mapID = g_Global.getMapNameId();
        dq5::level::PlayerCarriage* data = 0;
        for (int i = 0; i < max; i++) {
            data = dq5::level::PlayerCarriage::getRecord(i);
            if (mapID != data->getFloor()) {
                continue;
            }
            rebirthHero = true;
            break;
        }
        if (rebirthHero == false || data->getRelive() == 0) {
            rebirthFlag = false;
        }
        if (rebirthFlag == true) {
            for (int i = 0; i < carriageOutCount; i++) {
                if (i == status::g_Party.getSortIndex(1)) {
                    continue;
                }
                status::HaveStatus& haveStatus = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus();
                if (haveStatus.playerType_ == status::HaveStatus::TYPE_BATTLENPC || haveStatus.playerType_ == status::HaveStatus::TYPE_NOBATTLENPC ||
                    haveStatus.playerType_ == status::HaveStatus::TYPE_FRIENDMONSTER) {
                    continue;
                }
                if (haveStatus.getHp() != 0) {
                    aliveHuman = true;
                    break;
                }
            }
            if (data->getMostRelive() == 0 && aliveHuman == true) {
                rebirthFlag = false;
            }
        }
        dq5::level::PlayerCarriage::cleanup();
        if (rebirthFlag == false) {
            return false;
        }
        status::g_Party.setAllPlayerMode();
        int hero = status::g_Party.getSortIndex(1);
        int hp = status::g_Party.getPlayerStatus(hero).getHaveStatusInfo().getHp();
        status::g_Party.setPlayerMode();
        status::g_StageInfo.setReliveMessageFlag(true);
        TownWindowSystem::getSingleton().openSystemMessage();
        if (carriageOutCount == 2) {
            TownWindowSystem::getSingleton().addCommonMessage(0xc42a1);
        } else {
            TownWindowSystem::getSingleton().addCommonMessage(0xc42a3);
        }
        status::g_Party.getPlayerStatus(hero).getHaveStatusInfo().revival();
        status::PartyStatusUtility::forceReorderTown(false);
        status::PartyStatusUtility::resetForceReorderMember();
        data_0211b27c.state_ = FadeEffector::FADE_NONE;
        data_0211b27c.count_ = 0;
        data_0211b27c.frames_ = 1;
        data_0211b27c.sprite_[0].setColor(0, 0, 0);
        data_0211b27c.sprite_[1].setColor(0, 0, 0);
        data_02101d14.unkfunc_020519a8(&data_0211b27c);
        cmn::g_cmnSoundManager.setPlaySound(0x13, true);
        return true;
    }
    return false;
}

void twn::TownCommandCoercionSort::exec()
{
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::CommandPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::MenuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::MessagePriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::MaterielMenuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::DrawTownShopListPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::DrawTownMapPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::SugorokuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::CameraPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::StagePriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::FurniturePriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::RiseupPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::PlayerPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::CharacterPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::ScriptPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::GlobalMapPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::ScreenEffectPriority, false);
}
