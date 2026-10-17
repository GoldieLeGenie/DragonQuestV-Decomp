#include "main/debug/UnkBattleTest.hpp"
#include "main/btl/Encount.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "ov000/btl/BattleTaskManager.hpp"
#include "ov000/status/MonsterParty.hpp"

inline void btl::Encount::setTileId(int id)
{
    tileId_ = id;
    encountData_.setTileId(id);
}

UnkBattleTest data_020c2c40;

THUMB UnkBattleTest::UnkBattleTest()
{
    mode_ = 0;
    unk_04 = 0;
    firstTile_ = 1;
    lastTile_ = 1;
    playCount_ = 1;
    noDamage_ = 0;
    hpRate_ = 100;
    noDamageTurn_ = 5;
    endTurn_ = 30;
    unk_3c = 0;
    unk_40 = 0;
    act_ = 0;
    state_ = 0;
    counter_ = -1;
}

THUMB void UnkBattleTest::unkfunc_02026b68()
{
    switch (state_) {
    case 0:
        break;
    case 1:
        if (counter_ == 30) {
            status::g_Story.setChapter(dq5::CHAPTER_SOUNENKI);
            status::g_StageInfo.setTimeZone(TIME_ZONE_DAYTIME);
            if (mode_ == 1) {
                firstTile_ = 0;
                lastTile_ = 0;
            }
            if (tile_ > 0x55 && tile_ < 0x64) {
                tile_ = 0x64;
            }
            if (tile_ > 0x81 && tile_ < 0x8c) {
                tile_ = 0x8c;
            }
            btl::Encount::getSingleton()->setTileId(tile_);
            btl::Encount::getSingleton()->setTimeZone(TIME_ZONE_DAYTIME);
            status::g_Party.setAllPlayerMode();
            int count = status::g_Party.getCount();
            for (int i = 0; i < count; i++) {
                status::HaveStatusInfo& info = status::g_Party.getPlayerStatus(i).haveStatusInfo_;
                info.revival();
                int hpMax = info.getHpMax();
                int hp = hpMax * hpRate_ / 100;
                if (hp == 0) {
                    hp = 1;
                }
                if (hp > hpMax) {
                    hp = hpMax;
                }
                info.setHp(hp);
                if (info.haveStatus_.playerIndex_ == 1) {
                    if (command_ < COMMAND_DEBUG) {
                        info.haveStatus_.command_ = command_;
                    }
                    if (command_ == 7) {
                        info.haveStatus_.command_ = COMMAND_DEBUG;
                        info.commandTypeDebug_ = 0;
                    }
                    if (command_ == 8) {
                        info.haveStatus_.command_ = COMMAND_DEBUG;
                        info.commandTypeDebug_ = 1;
                    }
                    if (command_ == 9) {
                        info.haveStatus_.command_ = COMMAND_DEBUG;
                        info.commandTypeDebug_ = 2;
                    }
                    if (command_ == 10) {
                        info.haveStatus_.command_ = COMMAND_DEBUG;
                        info.commandTypeDebug_ = 3;
                    }
                    if (command_ == 11) {
                        info.haveStatus_.command_ = COMMAND_DEBUG;
                        info.commandTypeDebug_ = 4;
                    }
                } else {
                    if (command2_ < COMMAND_DEBUG) {
                        info.haveStatus_.command_ = command2_;
                    }
                    if (command_ == 7) {
                        info.haveStatus_.command_ = COMMAND_DEBUG;
                        info.commandTypeDebug_ = 0;
                    }
                    if (command_ == 8) {
                        info.haveStatus_.command_ = COMMAND_DEBUG;
                        info.commandTypeDebug_ = 1;
                    }
                    if (command_ == 9) {
                        info.haveStatus_.command_ = COMMAND_DEBUG;
                        info.commandTypeDebug_ = 2;
                    }
                    if (command_ == 10) {
                        info.haveStatus_.command_ = COMMAND_DEBUG;
                        info.commandTypeDebug_ = 3;
                    }
                    if (command_ == 11) {
                        info.haveStatus_.command_ = COMMAND_DEBUG;
                        info.commandTypeDebug_ = 4;
                    }
                }
            }
            status::PartyStatusUtility::setNoDamageEnableForMonster(true);
            if (noDamage_ != 0) {
                status::PartyStatusUtility::setNoDamageEnable(noDamage_);
            } else {
                status::g_BattleResult.setDisablePlayerDemolition(true);
            }
            if (mode_ == 0) {
                if (btl::Encount::getSingleton()->brew()) {
                    g_Global.startBattle();
                    state_ = 2;
                    counter_ = -1;
                    dss::g_Pad.unkfunc_0204be8c();
                    dss::g_Pad.unkfunc_0204bef0(1, 4);
                    dss::g_Pad.unkfunc_0204bd50(0x300);
                } else {
                    state_ = 4;
                    counter_ = -1;
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    int monsterIndex = monsterIndex_[i];
                    btl::Encount::getSingleton()->monsterIndex_[i] = monsterIndex;
                    int monsterCount = monsterCount_[i];
                    btl::Encount::getSingleton()->monsterCount_[i] = monsterCount;
                }
                btl::Encount::getSingleton()->encountData_.tileLevel_ = 99;
                g_Global.directStartBattle();
                state_ = 2;
                counter_ = -1;
                dss::g_Pad.unkfunc_0204be8c();
                dss::g_Pad.unkfunc_0204bef0(1, 4);
                dss::g_Pad.unkfunc_0204bd50(0x300);
            }
        }
        break;
    case 2:
        if (data_02101c88.unkfunc_02051810() == 5) {
            state_ = 3;
            counter_ = -1;
        }
        break;
    case 3:
        if (data_02101c88.unkfunc_02051810() != 5) {
            state_ = 4;
            counter_ = -1;
            dss::g_Pad.unkfunc_0204be48();
        } else {
            int turn = status::g_BattleResult.battleTurnCount_ + 1;
            data_020f6f9c.unkfunc_0204b04c(0, 0x16, "TURN%2d/%2d/%2d  ACT=%d", turn, noDamageTurn_, endTurn_, act_);
            data_020f6f9c.unkfunc_0204b04c(0xc, 0x17, "PLAY%2d/%2d", play_, playCount_);
            data_020f6f9c.unkfunc_0204b04c(0, 0x17, "TILE%3d/%3d", tile_, lastTile_);
            if (turn > noDamageTurn_) {
                status::PartyStatusUtility::setNoDamageEnableForMonster(false);
                int count = status::g_Monster.getCount();
                for (int i = 0; i < count; i++) {
                    int noDamage = status::PartyStatusUtility::noDamageForMonster_;
                    status::g_Monster.getMonsterStatus(i).haveStatusInfo_.noDamage_ = noDamage;
                }
            }
            if (turn > endTurn_ && play_ != 0xb7 && play_ != 0xb9) {
                if (!btl::taskManager_.checkTask(7) && !btl::taskManager_.checkTask(8)) {
                    g_Global.endBattle(false);
                    btl::taskManager_.setNextTask(8);
                }
                state_ = 4;
                counter_ = -1;
                dss::g_Pad.unkfunc_0204be48();
            }
        }
        break;
    case 4:
        if (dss::g_Pad.pad()) {
            state_ = 5;
            counter_ = -1;
        } else {
            tile_++;
            if (tile_ > 0x55 && tile_ < 0x64) {
                tile_ = 0x64;
            }
            if (tile_ > 0x81 && tile_ < 0x8c) {
                tile_ = 0x8c;
            }
            if (tile_ > lastTile_) {
                tile_ = firstTile_;
                play_++;
                if (play_ == playCount_) {
                    state_ = 5;
                    counter_ = -1;
                    dss::g_Pad.unkfunc_0204be48();
                } else {
                    state_ = 1;
                    counter_ = -1;
                }
            } else {
                state_ = 1;
                counter_ = -1;
            }
        }
        break;
    case 5: {
        unk_3c = 0;
        act_ = 0;
        status::g_Party.setAllPlayerMode();
        int count = status::g_Party.getCount();
        for (int i = 0; i < count; i++) {
            status::HaveStatusInfo& info = status::g_Party.getPlayerStatus(i).haveStatusInfo_;
            if (info.haveStatus_.playerIndex_ == 1) {
                info.haveStatus_.command_ = COMMAND_MEIREISASERO;
            } else if (info.haveStatus_.command_ == COMMAND_DEBUG) {
                info.haveStatus_.command_ = COMMAND_MEIREISASERO;
            }
        }
        state_ = 0;
        counter_ = -1;
        break;
    }
    }
    counter_++;
}
