#include "main/btl/BattleScriptManager.hpp"
#include "main/script/CommandParam.hpp"
#include "main/script/ScriptFlagCommand.hpp"
#include "main/status/BattleResult.hpp"

#pragma thumb on

inline int status::BattleResult::isPlayerVictory()
{
    return playerVictory_;
}

btl::BattleScriptManager btl::gBattleScriptManager;

btl::BattleScriptManager::BattleScriptManager()
{
    checkBattle_ = 0;
    setDataInit_ = 0;
}

void btl::BattleScriptManager::setScriptBattleResult(int flagType, int flagNo, int victory)
{
    checkBattle_ = 1;
    flagInfo_[victory].flagNo = flagNo;
    flagInfo_[victory].flagType = flagType;
    flagInfo_[victory].victory = victory;
    switch (victory) {
    case 0:
        setDataInit_ |= 1;
        break;
    case 1:
        setDataInit_ |= 2;
        break;
    }
}

void btl::BattleScriptManager::checkScriptBattleResult()
{
    if (checkBattle_ == 1) {
        for (int i = 0; i < SET_BATTLE_END_FLAG_COUNT; i++) {
            unsigned int type;
            if (flagInfo_[i].victory == 0) {
                type = 1;
            } else {
                type = 2;
            }
            if (setDataInit_ & type) {
                PARAM_SET_FLAG param;
                param.type = flagInfo_[i].flagType;
                param.index = flagInfo_[i].flagNo;
                param.flag = 0;
                if (status::g_BattleResult.isPlayerVictory() == 1) {
                    param.flag = flagInfo_[i].victory == 0 ? 1 : 0;
                } else {
                    param.flag = flagInfo_[i].victory == 1 ? 1 : 0;
                }
                cmdSetFlag(&param);
            }
        }
    }
    setDataInit_ = 0;
    checkBattle_ = 0;
}
