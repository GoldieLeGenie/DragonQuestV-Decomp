#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "ov000/btl/BattleSelectTargetParam.hpp"

namespace status {
    struct CharacterStatus;
}

namespace btl {
    struct BattleSecondCheck {
        static unsigned char getSecondCheckParam(BattleSelectTargetParam* targetParam);
        static bool secondCheckFirst(BattleSelectTargetParam* targetParam);
        static bool secondCheckLast(unsigned char checkParam, status::CharacterStatus* targetStatus, status::CharacterStatus* actorStatus);
        static bool secondCheckPercent(BattleSelectTargetParam* targetParam, int member, int enable, int mahokanta);
        static bool personalCheckFirst(BattleSelectTargetParam* targetParam);
        static bool personalCheckLast(BattleSelectTargetParam* targetParam, int group, int num);
        static bool myselfCheck(BattleSelectTargetParam* targetParam);
        static bool multipleCheckFirst(BattleSelectTargetParam* targetParam);
        static bool multipleCheckPercent(BattleSelectTargetParam* targetParam, int member, int enable, int mahokanta);
        static bool everyCheckLast(BattleSelectTargetParam* targetParam, int index);
        static bool everyCheckPercent(BattleSelectTargetParam* targetParam, int enable, int mahokanta);
        static int secondCheckTarget(BattleSelectTargetParam* targetParam, int max, int actor);
        static bool checkFizzleZone(BattleSelectTargetParam* battleSelectTargetParam);
        static bool personalCheckMyMahokanta(BattleSelectTargetParam* battleSelectTargetParam);
        static bool personalCheckChargeAttack(BattleSelectTargetParam* battleSelectTargetParam);
        static bool checkPartFourth(BattleSelectTargetParam* battleSelectTargetParam);
        static bool checkPartThree(BattleSelectTargetParam* battleSelectTargetParam);
        static bool checkPartHalf(BattleSelectTargetParam* battleSelectTargetParam);
        static bool checkAnkoku(BattleSelectTargetParam* battleSelectTargetParam);
        static bool personalCheckMahokantaForGod(BattleSelectTargetParam* battleSelectTargetParam);
        static bool checkEscape(BattleSelectTargetParam* battleSelectTargetParam);
        static bool checkBashaModoshi(BattleSelectTargetParam* battleSelectTargetParam);
        static bool checkBashaShime(BattleSelectTargetParam* battleSelectTargetParam);
        static bool checkMyHoimi(BattleSelectTargetParam* battleSelectTargetParam);
        static bool checkMySukara(BattleSelectTargetParam* battleSelectTargetParam);
        static bool personalCheckRandom();
        static int personalCheckMahokanta(status::CharacterStatus* characterStatus);
        static bool checkRarihoma(status::CharacterStatus* characterStatus);
        static bool checkFubaha(status::CharacterStatus* characterStatus);
        static bool checkManusa(status::CharacterStatus* characterStatus);
        static bool checkMahoton(status::CharacterStatus* characterStatus);
        static bool checkMahokite(status::CharacterStatus* characterStatus);
        static bool checkPoison(status::CharacterStatus* characterStatus);
        static bool checkDeepPoison(status::CharacterStatus* characterStatus);
        static bool checkParalyse(status::CharacterStatus* characterStatus);
        static bool checkMedapani(status::CharacterStatus* characterStatus);
        static bool checkMahotora(status::CharacterStatus* characterStatus);
        static bool checkRukani(status::CharacterStatus* characterStatus);
        static bool checkSukara(status::CharacterStatus* characterStatus);
        static bool checkBaikiruto(status::CharacterStatus* characterStatus);
        static bool checkHoimi(status::CharacterStatus* characterStatus);
        static bool checkThereHoimi(status::CharacterStatus* characterStatus);
        static bool checkZaoriku(status::CharacterStatus* characterStatus, CharacterType type);
        static bool checkOthers(status::CharacterStatus* targetStatus, status::CharacterStatus* actorStatus);
        static bool checkOtakebi(status::CharacterStatus* characterStatus);
        static bool checkHadou(status::CharacterStatus* characterStatus);
        static bool checkBashaModoshi(status::CharacterStatus* characterStatus);
        static bool checkBukimi(status::CharacterStatus* characterStatus);
        static bool personalCheckNakamayobi(BattleSelectTargetParam* battleSelectTargetParam);
        static bool personalCheckGattai(BattleSelectTargetParam* battleSelectTargetParam);
        static bool checkMahotonForGod(status::CharacterStatus* characterStatus);
        static bool checkRukaniForGod(status::CharacterStatus* characterStatus);
        static bool checkRukananForGod(status::CharacterStatus* characterStatus);
        static bool checkMosyasu(status::CharacterStatus* characterStatus);
        static bool checkMahokantakeiPercent(int member, int mahokanta);
        static bool checkBehomaraPercent(int member, int enable);
        static bool checkMegazaruPercent(int member, int enable);
        static bool checkNotZeroPercent(int enableCount);
    };
}
