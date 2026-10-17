#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/status/ActionDefence.hpp"
#include "main/status/HaveStatus.hpp"
#include "main/status/HaveItem.hpp"
#include "main/status/HaveAction.hpp"
#include "main/status/HaveEquipment.hpp"
#include "main/status/StatusChange.hpp"

namespace status {
    struct HaveBattleStatus;

    struct HaveStatusInfo {
        enum Condition {
            ALIVE = 0x0,
            DEAD = 0x1,
            SLEEP = 0x2,
            CONFUSION = 0x3,
            SPAZZ = 0x4,
            SPELL = 0x5,
            POISON = 0x6,
        };
        enum MenuStatusChange {
            Manusa = 0x0,
            Mahoton = 0x1,
            Sleep = 0x2,
            Confusion = 0x3,
            Spazz = 0x4,
            Venom = 0x6,
            Curse = 0x7,
            MaxStatus = 0x8,
        };
        enum DiffStatus {
            BeforeAction = 0x0,
            ExecuteAction = 0x1,
            ResultAction = 0x2,
            SpecialAction = 0x3,
            MaxAction = 0x4,
        };

        // flag_
        static const unsigned int FLAG_COMMAND_RANDOM = 0x1;
        static const unsigned int FLAG_FUBAHA = 0x2;
        static const unsigned int FLAG_BOSS_DEATH = 0x4;
        static const unsigned int FLAG_DAMAGE_MYSELF = 0x8;
        static const unsigned int FLAG_DISAPPEAR = 0x20;
        static const unsigned int FLAG_REBIRTH_FAILED = 0x40;
        static const unsigned int FLAG_MOSYAS_EVILPRIEST = 0x80;
        static const unsigned int FLAG_ACTION_DISABLE = 0x100;
        static const unsigned int FLAG_SLEEP_ATTACK = 0x200;
        static const unsigned int FLAG_MULTI_ATTACK = 0x400;
        static const unsigned int FLAG_MOSYAS_RELEASE = 0x800;
        static const unsigned int FLAG_CALL_FRIEND = 0x1000;
        static const unsigned int FLAG_SILVER_TAROT = 0x2000;
        static const unsigned int FLAG_WEAPON_ADD_DAMAGE = 0x4000;
        static const unsigned int FLAG_CONFUSE_MISS_ATTACK = 0x8000;
        static const unsigned int FLAG_KILL_MYSELF = 0x10000;
        static const unsigned int FLAG_ADD_EFFECT_SLEEP = 0x20000;
        static const unsigned int FLAG_ADD_EFFECT_SPAZZ = 0x40000;
        static const unsigned int FLAG_ADD_EFFECT_POISON = 0x80000;
        static const unsigned int FLAG_ADD_EFFECT_RECOVERY = 0x100000;
        static const unsigned int FLAG_ADD_EFFECT_MAHOTORA = 0x200000;
        static const unsigned int FLAG_ADD_EFFECT_DAMAGE = 0x400000;
        static const unsigned int FLAG_TARGET_JOUK = 0x800000;
        static const unsigned int FLAG_MONSTER_CHANGE = 0x1000000;
        static const unsigned int FLAG_BAIKIRUTO_DISABLE = 0x2000000;
        static const unsigned int FLAG_FIRST_MOSYAS = 0x4000000;
        static const unsigned int FLAG_MAHOKANTA_COUNTER = 0x8000000;
        static const unsigned int FLAG_COUNTER_DAMAGE = 0x10000000;
        static const unsigned int FLAG_DAMAGE = 0x20000000;
        static const unsigned int FLAG_LAST_ACTOR = 0x40000000;
        static const unsigned int FLAG_ADD_MAHOTORA_EXECUTE = 0x80000000;
        // flag2_
        static const unsigned int FLAG_SELF_IMMOLATION = 0x1;
        static const unsigned int FLAG_FIRST_KAISHIN = 0x2;
        static const unsigned int FLAG_SECOND_KAISHIN = 0x4;
        static const unsigned int FLAG_STATUS_CHANGE_RELEASE = 0x8;
        static const unsigned int FLAG_ASTORON = 0x10;
        static const unsigned int FLAG_MP_FAILURE = 0x20;
        static const unsigned int FLAG_MAHOTONE_FAILURE = 0x40;
        static const unsigned int FLAG_MEGAZARU_REBIRTH = 0x80;
        static const unsigned int FLAG_MEGAZARU_RECOVERY = 0x100;
        static const unsigned int FLAG_ZAORIKU_REBIRTH = 0x200;
        static const unsigned int FLAG_IMMIDIATE_DEATH = 0x400;
        static const unsigned int FLAG_MULTI_FIRST_DEATH = 0x800;
        static const unsigned int FLAG_EXECUTE_MEGANTE_RING = 0x1000;
        static const unsigned int FLAG_VENOM_ACTION = 0x2000;
        static const unsigned int FLAG_MEGAZARU_RING = 0x4000;
        static const unsigned int FLAG_DISABLE_TEXTURE_CACHE = 0x8000;
        static const unsigned int FLAG_SPLIT = 0x10000;
        static const unsigned int FLAG_JOUK = 0x20000;
        static const unsigned int FLAG_KAISHIN = 0x40000;
        static const unsigned int FLAG_TSUKON1 = 0x80000;
        static const unsigned int FLAG_TSUKON2 = 0x100000;
        static const unsigned int FLAG_MISS = 0x200000;
        static const unsigned int FLAG_SLEEP_TURN = 0x400000;
        static const unsigned int FLAG_CURSE2_TARGET_SELECT = 0x800000;
        static const unsigned int FLAG_LIFE_STONE_ENABLE = 0x1000000;
        static const unsigned int FLAG_ZAORARU_FAILED = 0x2000000;
        static const unsigned int FLAG_MANUSA_ALREADY = 0x4000000;
        static const unsigned int FLAG_CURSE1 = 0x8000000;
        static const unsigned int FLAG_DEATH = 0x10000000;
        static const unsigned int FLAG_IMMEDIATE_DEATH_ITEM = 0x20000000;
        static const unsigned int FLAG_MAGIC_DISABLE = 0x40000000;
        static const unsigned int FLAG_MOSYAS_START = 0x80000000;
        // testFlag_
        static const unsigned int FLAG_TEST_TARGET_JOUK = 0x1;
        // battleFlag_
        static const unsigned int FLAG_ALL_KAISHIN = 0x1;
        static const unsigned int FLAG_CLOSE_DOOR = 0x2;
        static const unsigned int FLAG_MOSYAS_TARGET = 0x4;
        static const unsigned int FLAG_MOSYAS_EXEC = 0x8;
        static const unsigned int FLAG_DEATH_LESSLY = 0x10;
        static const unsigned int FLAG_INVOKE_MEGANTE_RING = 0x20;
        static const unsigned int FLAG_REBIRTH_FOR_REBIRTH_STONE = 0x40;
        static const unsigned int FLAG_CHANGE_TACTICS = 0x80;
        static const unsigned int FLAG_ESCAPE = 0x100;
        static const unsigned int FLAG_MEGANTE_RING = 0x200;
        static const unsigned int FLAG_INVOKE_REBRTH_STONE = 0x400;
        // globalFlag_
        static const unsigned int FLAG_GLB_MEGANTE_RING = 0x1;
        static const unsigned int FLAG_GLB_MEGAZARU_RING = 0x2;
        static const unsigned int FLAG_GLB_REBIRTH_STONE = 0x4;

        int hp_[MaxAction];
        int mp_[MaxAction];
        dss::BitFlag<unsigned int> status_[8];
        CharacterType characterType_;
        int index_;
        HaveBattleStatus* haveBattleStatus_;
        ActionDefence actionDefence_;
        int effectValue_;
        int effectValueMax_;
        int effectValueMin_;
        int effectValueCount_;
        int specialTargetDamage_;
        int specialTargetCount_;
        int addDamage_;
        int drawCtrlId_;
        int noDamage_;
        int allEquipment_;
        int rebirthFlag_;
        short defenceChange_;
        short agilityChange_;
        short attackChange_;
        dss::BitFlag<unsigned int> flag_;
        dss::BitFlag<unsigned int> flag2_;
        dss::BitFlag<unsigned int> testFlag_;
        dss::BitFlag<unsigned int> battleFlag_;
        HaveStatus haveStatus_;
        HaveItem haveItem_;
        HaveAction haveAction_;
        HaveEquipment haveEquipment_;
        StatusChange statusChange_;
        int commandTypeDebug_;

        static dss::BitFlag<unsigned int> globalFlag_;    // data_020a1030

        HaveStatusInfo();
        ~HaveStatusInfo();
        void setup(int index, bool flag);
        void setupMonster(int index);
        void cleanup();
        void setupStatus(int index, bool flag);
        void setupActionDefence();
        void setupActionDefence(int index, bool flag);
        int getPlayerIndex() const;
        int getPlayerKindIndex() const;
        bool isPlayer() const;
        int getCharaIndex();
        int getIconIndex();
        static int getSonIconIndex();
        static int getDaughterIconIndex();
        static int getSonCharaIndex();
        static int getDaughterCharaIndex();
        void levelup(int level);
        unsigned short getStrength(int effect);
        unsigned char getAgility(int effect);
        short getAgilityChange();
        void clearAgilityChange();
        unsigned short getProtection(int effect);
        unsigned char getWisdom(int effect);
        unsigned char getLuck(int effect);
        int getExp() const;
        void addExp(int exp);
        int getLevelupExp() const;
        int getGold() const;
        void setHp(unsigned short hp);
        short getHp() const;
        void addHp(int hp);
        void execDeath();
        void setHpMax(unsigned short hp);
        unsigned short getHpMax() const;
        void addHpMax(unsigned short hp);
        void setMp(unsigned short mp);
        unsigned short getMp() const;
        void addMp(int mp);
        void setMpMax(unsigned short mp);
        unsigned short getMpMax() const;
        void clearHpInBattle();
        void addHpInBattle(DiffStatus status, int hp);
        void clearMpInBattle();
        void addMpInBattle(DiffStatus status, int mp);
        void clearStatusChangeInBattle();
        void setStatusChangeInBattle(DiffStatus status);
        unsigned short getAttack(int effect);
        unsigned short getBaseAttack();
        short setAttackChange();
        short getAttackChange();
        unsigned short getBaseDefence();
        unsigned short getDefence(int effect);
        short setDefenceChange(int actionIndex);
        short getDefenceChange();
        void clearDefenceChange();
        unsigned char getChangeStrength(int itemIndex) const;
        unsigned char getChangeAgility(int itemIndex);
        unsigned char getChangeWisdom(int itemIndex) const;
        unsigned char getChangeLuck(int itemIndex) const;
        short getChangeAttack(int itemIndex) const;
        short getChangeDefence(int itemIndex) const;
        bool isNearDeath() const;
        bool isDeath() const;
        void setDeath();
        void rebirth();
        bool isPoison();
        void setPoison();
        void detoxPoison();
        bool isSpell();
        void breakSpell();
        CharacterType getCharacterType();
        StatusChange& getStatusChange();
        int getCommandType() const;
        int getCommandTypeDebug();
        void setCommandType(CommandType cmd);
        HaveStatus& getHaveStatus();
        HaveItem& getHaveItem();
        HaveAction& getHaveAction();
        HaveEquipment& getHaveEquipment();
        ActionDefence& getActionDefence();
        void setEquipment(int index);
        void resetEquipment(int index);
        void resetEquipment(ItemType itemType);
        void clearAllItem();
        int setItemEquipment(int itemIndex);
        bool isEquipEnable(int itemIndex) const;
        void execThrow(int index);
        void recovery();
        void revival();
        void setUseActionEffectValue(int value);
        void setSpecialTargetDamage(int value);
        int getSpecialTargetDamage();
        void addSpecialTargetCount();
        int getSpecialTargetCount();
        void setFubahaFlag(bool flag);
        bool isFubahaFlag();
        void setDisappearFlag(bool flag);
        bool isDisappearFlag();
        void setRebirthFailed(bool flag);
        bool isRebirthFailed();
        void setMosyasRelease(bool flag);
        bool isMosyasRelease();
        void setActionDisable(bool flag);
        bool getActionDisable();
        void setSleepAttack(bool flag);
        bool isSleepAttack();
        void setMultiAttack(bool flag);
        bool isMultiAttack();
        void setCallFriend(bool flag);
        bool isCallFriend();
        void setWeaponAddDamage(bool flag);
        bool isWeaponAddDamage();
        void setConfuseMissAttack(bool flag);
        bool isConfuseMissAttack();
        void setAddEffectSleep(bool flag);
        void setAddEffectSpazz(bool flag);
        void setAddEffectPoison(bool flag);
        void setAddEffectRecovery(bool flag);
        bool isAddEffectRecovery();
        void setAddEffectMahotora(bool flag);
        bool isAddEffectMahotora();
        void setAddEffectDamage(bool flag);
        bool isAddEffectDamage();
        void setTargetJouk(bool flag);
        bool isTargetJouk();
        void setTargetJoukForTest(bool flag);
        void setKillMyself(bool flag);
        bool isKillMyself();
        void setMonsterChange(bool flag);
        bool isMonsterChange();
        void setBaikirutoDisable(bool flag);
        void setFirstMosyas(bool flag);
        bool isFirstMosyas();
        void setMahokantaCounter(bool flag);
        bool isMahokantaCounter();
        void setCounterDamage(bool flag);
        void setDamage(bool flag);
        bool isDamage();
        void setLastActor(bool flag);
        void setAddMahotoraExecute(bool flag);
        bool isAddMahotoraExecute();
        void setDamageMyself(bool flag);
        void setAddDamage(int dm);
        int getUseActionEffectValue();
        bool isDamageMyself();
        void setSelfImmolation(bool flag);
        bool isSelfImmolation();
        void setFirstKaishin(bool flag);
        void setSecondKaishin(bool flag);
        bool isSecondKaishin();
        void setStatusChangeRelease(bool flag);
        bool isStatusChangeRelease();
        void setAstoron(bool flag);
        bool isAstoron();
        void setMpFailure(bool flag);
        bool isMpFailure();
        void setMahotoneFailure(bool flag);
        void setMegazaruRebirth(bool flag);
        bool isMegazaruRebirth();
        void setMegazaruRecovery(bool flag);
        void setZaorikuRebirth(bool flag);
        void setImmidiateDeath(bool flag);
        bool isImmidiateDeath();
        void setExecuteMeganteRing(bool flag);
        bool isExecuteMeganteRing();
        void setVenomAction(bool flag);
        void setDisableTextureCache(bool flag);
        bool isDisableTextureCache();
        bool isSplit();
        bool isJouk();
        void setKaishin(bool flag);
        bool isKaishin();
        void setTsukon1(bool flag);
        bool isTsukon1();
        void setTsukon2(bool flag);
        bool isTsukon2();
        void setMiss(bool flag);
        bool isMiss();
        void setSleepTurn(bool flag);
        bool isSleepTurn();
        void setCurse2(bool flag);
        bool isCurse2();
        void setLifeStoneEnable(bool flag);
        bool isLifeStoneEnable();
        void setManusaAlready(bool flag);
        bool isManusaAlready();
        void setCurse1(bool flag);
        bool isCurse1();
        void setDeathFlag(bool flag);
        bool isDeathFlag();
        void setImmediateDeathItem(bool flag);
        bool isImmediateDeathItem();
        void setCommandRandom(bool flag);
        bool isCommandRandom();
        void setZaoraruFailed(bool flag);
        void setMagicDisable(bool flag);
        bool isMagicDisable();
        void setMosyasStart(bool flag);
        bool isMosyasStart();
        void setAllKaishin(bool flag);
        bool isAllKaishin();
        void setCloseDoor(bool flag);
        bool isCloseDoor();
        void setMosyasTarget(bool flag);
        bool isMosyasTarget();
        void setDeathLessly(bool flag);
        bool isDeathLessly();
        void setMosyasExec(bool flag);
        bool isMosyasExec();
        void setInvokeMeganteRing(bool flag);
        void setInvokeRebirthStone(bool flag);
        bool isInvokeRebirthStone();
        void setRebirthForRebirthStone(bool flag);
        bool isRebirthForRebirthStone();
        void setEscapeFlag(bool flag);
        bool isEscapeFlag();
        void setMeganteRing(bool flag);
        bool isMeganteRing();
        static void setGlbMeganteRing(bool flag);
        static bool isGlbMeganteRing();
        static void setGlbRebirthStone(bool flag);
        static bool isGlbRebirthStone();
        void setDrawCtrlId(int ctrl);
        int getDrawCtrlId();
        int getAddDamage();
        void setNoDamageEnable(int flag);
        void releaseMosyas();
        void allFlagClear();
        void execStartOfBattle();
        bool isActionEnable();
        bool isActionEnableWithoutDragoram();
        bool isActionEnableForMacro();
        bool isAttackEnable();
    };
}
