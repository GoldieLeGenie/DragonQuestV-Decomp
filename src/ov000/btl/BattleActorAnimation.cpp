#include "ov000/btl/BattleActorAnimation.hpp"
#include "ov000/btl/BattleActorSound.hpp"
#include "ov000/btl/BattleMonster.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/btl/Encount.hpp"
#include "main/btl/MonsterData.hpp"
#include "main/window/UnkMapPoint.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/menu/BattleMenu.hpp"
#include "main/object/GameMonster.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionParam.hpp"

int btl::BattleActorAnimation::airMaxHeight = 0x10;
int btl::BattleActorAnimation::groundMaxHeight = 0x20;

inline int status::HaveStatus::getMonsterKind() const { return monsterId_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline int status::UseActionParam::getTargetCount() { return targetCount_; }
inline bool status::UseActionParam::isResult() { return result_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline bool status::CharacterStatus::isTsukonSound() { return damageSound_ == TsukonSe; }
inline void status::CharacterStatus::setCharacterIndex(int index) { characterIndex_ = index; }
inline int status::CharacterStatus::getCharacterIndex() { return characterIndex_; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline int status::HaveStatusInfo::getUseActionEffectValue() { return effectValue_; }
inline int status::MonsterStatus::getMonsterGroup() { return characterGroup_; }
inline int status::MonsterStatus::getMosyasMonsterIndex() { return mosyasMonsterIndex_; }
inline dss::Fix32Vector3 btl::BattleMonster::getPosition() { return *monsterDraw_.getPosition(); }
inline bool btl::BattleMonster::isAirMonster() { return flag_.check(FLAG_AIR_MONSTER); }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }
inline void btl::Encount::setMonsterIndex(int group, int index) { monsterIndex_[group] = index; }
inline void btl::Encount::setMonsterCount(int group, int count) { monsterCount_[group] = count; }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned char dq5::level::ActionParam::getUseMP() { return useMP; }

THUMB int btl::BattleActorAnimation::setExecAnimation(status::UseActionParam& useActionParam)
{
    int actionIndex = useActionParam.getActionIndex();
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    if (!checkExecAnimation(useActionParam)) {
        return 0;
    }
    setMosyasSetup(&useActionParam);
    if (checkNormalAnimation(useActionParam)) {
        int drawCtrlId = useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getDrawCtrlId();
        int animation = useActionParam.getActorCharacterStatus()->getHaveBattleStatus().getActionAnimation();
        if (status::isNormalAttackForSE(actionIndex) && actionIndex != 0x47) {
            actionIndex = 0x47;
            animation = 0;
        }
        if ((actionIndex == 0x9F || actionIndex == 0xA0) && !useActionParam.getActorCharacterStatus()->isTsukonSound()) {
            actionIndex = 0x47;
            animation = 0;
        }
        if (useActionParam.getActorCharacterStatus()->getHaveStatusInfo().isMosyasExec()) {
            int mosyasId = ((status::MonsterStatus*)useActionParam.getActorCharacterStatus())->getMosyasMonsterIndex();
            switch (actionIndex) {
            case 0x33:
            case 0x36:
            case 0x39:
                actionIndex -= 1;
                break;
            case 0x34:
            case 0x37:
            case 0x3A:
                actionIndex -= 2;
                break;
            }
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startMosyasAnimation(mosyasId, actionIndex);
        }
        else {
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(actionIndex, animation);
        }
        return BattleAutoFeed::getMessageSpeed();
    }
    int actionIndex2 = useActionParam.getActionIndex();
    if (useActionParam.isResult() && actor->isEscapeAnimation()) {
        useActionParam.getActorCharacterStatus()->clearEscapeAnimation();
        int drawCtrlId = useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getDrawCtrlId();
        int animation = useActionParam.getActorCharacterStatus()->getHaveBattleStatus().getActionAnimation();
        BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(actionIndex2, animation);
        SoundManager::playSe(0x198, 0);
    }
    if (actor->isDisappearAnimation()) {
        actor->clearDisappearAnimation();
        int drawCtrlId = actor->getHaveStatusInfo().getDrawCtrlId();
        BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x1F);
    }
    if (actor->getHaveStatusInfo().isKillMyself()) {
        int drawCtrlId = useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getDrawCtrlId();
        int animation = useActionParam.getActorCharacterStatus()->getHaveBattleStatus().getActionAnimation();
        BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(actionIndex2, animation);
        BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setTransOfEnd();
    }
    if (actor->getHaveStatusInfo().isCurse1()) {
        return BattleAutoFeed::getMessageSpeed();
    }
    return 0;
}

THUMB bool btl::BattleActorAnimation::checkExecAnimation(status::UseActionParam& useActionParam)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    if (actor->getHaveStatusInfo().isStatusChangeRelease()) {
        return false;
    }
    if (actor->getCharacterType() != MONSTER) {
        return false;
    }
    if (actor->getHaveStatusInfo().getActionDisable()) {
        return false;
    }
    if (useActionParam.getActionIndex() == 0x1DE) {
        return false;
    }
    if (useActionParam.getActionIndex() == 0x3F || useActionParam.getActionIndex() == 0x18) {
        int monster = actor->getHaveStatusInfo().isMosyasExec() ? ((status::MonsterStatus*)actor)->getMosyasMonsterIndex() : actor->getCharacterIndex();
        if (monster == 0x2A) {
            return true;
        }
        if (actor->getHaveStatusInfo().isMagicDisable()) {
            return false;
        }
    }
    return true;
}

THUMB bool btl::BattleActorAnimation::checkNormalAnimation(status::UseActionParam& useActionParam)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    status::CharacterStatus* target = useActionParam.getTargetCharacterStatus(0);
    if (actor->getHaveStatusInfo().isDeath()) {
        if (useActionParam.getActionIndex() == 0x1B9) {
            return true;
        }
        if (actor->getHaveStatusInfo().isSelfImmolation()) {
            return true;
        }
        if (actor->getHaveStatusInfo().isSelfImmolation()) {
            return true;
        }
        if (actor->getHaveStatusInfo().isDamageMyself()) {
            return true;
        }
        if (actor->getHaveStatusInfo().isMahokantaCounter()) {
            return true;
        }
        if (actor->getHaveStatusInfo().isExecuteMeganteRing()) {
            return true;
        }
        if (actor->isDisappearAnimation()) {
            return true;
        }
    }
    if (actor->getHaveStatusInfo().isKillMyself()) {
        return false;
    }
    if (actor->getHaveStatusInfo().isCurse1()) {
        return false;
    }
    if (actor->getHaveStatusInfo().isCurse2() && actor->getCharacterType() != target->getCharacterType()) {
        return false;
    }
    if (actor->getHaveStatusInfo().isAttackEnable() == true) {
        return true;
    }
    if (actor->getHaveStatusInfo().isAstoron()) {
        for (int i = 0; i < useActionParam.getTargetCount(); i++) {
            useActionParam.getTargetCharacterStatus(i)->getHaveStatusInfo().setAstoron(false);
        }
        return true;
    }
    if (useActionParam.getActionIndex() == 0x195 || useActionParam.getActionIndex() == 0x1AD) {
        return true;
    }
    return false;
}

THUMB void btl::BattleActorAnimation::setResultAnimation(status::UseActionParam& useActionParam, int currentTarget)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    status::CharacterStatus* target = useActionParam.getTargetCharacterStatus(currentTarget);
    int actionIndex = useActionParam.getActionIndex();
    if (!checkResultAnimation(useActionParam, currentTarget)) {
        return;
    }
    if (!checkNormalAnimation(useActionParam)) {
        if (actor->getHaveStatusInfo().isSleepAttack()) {
            if (target->getHaveStatusInfo().getUseActionEffectValue() > 0) {
                int drawCtrlId = target->getHaveStatusInfo().getDrawCtrlId();
                SoundManager::playSe(0x192, 0);
                if (target->getHaveStatusInfo().isDeath()) {
                    BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x22);
                    if (target->isDeathDisable()) {
                        BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x23);
                    }
                }
                else {
                    BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x23);
                }
                setDamangeDraw(target);
            }
            else {
                SoundManager::playSe(0x195, 0);
            }
        }
        if (!actor->getHaveStatusInfo().isKillMyself()) {
            return;
        }
    }
    if (status::UseAction::getDamageType(useActionParam.getActionIndex()) == 1 && target->isDamageAnimation() && target->getCharacterType() == MONSTER) {
        setDamangeDraw(target);
    }
    BattleActorSound::playActionResultSound(useActionParam, currentTarget);
    bool flag = true;
    if (useActionParam.getActionIndex() == 0x1B9) {
        flag = false;
    }
    setResultAnimationMonster(actor, target, currentTarget, flag);
    setMosyasChange(actor);
    gattaiSlime(actor, actionIndex);
}

THUMB void btl::BattleActorAnimation::setDamangeDraw(status::CharacterStatus* target)
{
    int damage = target->getHaveStatusInfo().getUseActionEffectValue();
    if (damage <= 0) {
        return;
    }
    int monster = target->getHaveStatusInfo().isMosyasExec() ? ((status::MonsterStatus*)target)->getMosyasMonsterIndex() : target->getCharacterIndex();
    short* rect = MonsterTaiData[monster];
    int actorIndex;
    for (int i = 0; i < status::g_Monster.getCount(); i++) {
        if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getDrawCtrlId() == target->getHaveStatusInfo().getDrawCtrlId()) {
            actorIndex = i;
            break;
        }
    }
    dss::Vector2<int>* position = unkfunc_02052164(actorIndex);
    int x = position->vx;
    int y = position->vy;
    y -= dss::abs(rect[1] - rect[3]);
    if (BattleMonsterDraw2::getSingleton().getMonster(target->getHaveStatusInfo().getDrawCtrlId()).isAirMonster()) {
        if (y <= airMaxHeight) {
            y = airMaxHeight;
        }
    }
    else {
        if (y <= groundMaxHeight) {
            y = groundMaxHeight;
        }
    }
    menu::BattleMenu_setHoppingNumber(x, y, damage, 0);
}

THUMB bool btl::BattleActorAnimation::checkResultAnimation(status::UseActionParam& useActionParam, int currentTarget)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    if (useActionParam.getTargetCharacterStatus(currentTarget) == NULL) {
        return false;
    }
    if (actor->getHaveStatusInfo().isStatusChangeRelease()) {
        return false;
    }
    if ((status::UseAction::getActionType(useActionParam.getActionIndex()) == 1 || useActionParam.getActionIndex() == 0x19D) && actor->getHaveStatusInfo().isMagicDisable()) {
        return false;
    }
    if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getUseMP() && actor->getHaveStatusInfo().isMagicDisable()) {
        return false;
    }
    if (actor->getHaveStatusInfo().getActionDisable()) {
        return false;
    }
    if (useActionParam.getActionIndex() != 0x1DE) {
        return true;
    }
    return false;
}

THUMB void btl::BattleActorAnimation::setResultAnimationMonster(status::CharacterStatus* actor, status::CharacterStatus* target, int currentTarget, bool flag)
{
    setCallFriend(actor);
    setCallFriend(target);
    if (!actor->getHaveStatusInfo().isAttackEnable() && flag && !actor->getHaveStatusInfo().isSelfImmolation() && !actor->getHaveStatusInfo().isDamageMyself() && !actor->getHaveStatusInfo().isMahokantaCounter() && !actor->getHaveStatusInfo().isExecuteMeganteRing()) {
        if (actor->isDisappearAnimation()) {
            actor->clearDisappearAnimation();
            int drawCtrlId = actor->getHaveStatusInfo().getDrawCtrlId();
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x1F);
            return;
        }
    }
    else {
        if (target->getCharacterType() != MONSTER) {
            return;
        }
        int drawCtrlId = target->getHaveStatusInfo().getDrawCtrlId();
        if (target->isDamageAnimation()) {
            target->clearDamageAnimation();
            if (target->getHaveStatusInfo().isDeath()) {
                BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x22);
                if (target->isDeathDisable()) {
                    BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x23);
                }
            }
            else {
                BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x23);
            }
        }
        if (target->isDeathAnimation()) {
            target->clearDeathAnimation();
            if (target->getHaveStatusInfo().isImmidiateDeath()) {
                target->getHaveStatusInfo().setImmidiateDeath(false);
            }
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x22);
            if (target->isDeathDisable()) {
                BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x23);
            }
        }
        if (target->isDisappearAnimation()) {
            target->clearDisappearAnimation();
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x1F);
        }
        if (target->isRebirthAnimation()) {
            target->clearRebirthAnimation();
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x20);
        }
        if (target->isEscapeAnimation()) {
            SoundManager::playSe(0x198, 0);
        }
    }
}

THUMB void btl::BattleActorAnimation::setAfterAnimation(status::CharacterStatus* actor, status::CharacterStatus* target, int targetCount, int currentIndex)
{
    if (actor == NULL) {
        return;
    }
    if (currentIndex != targetCount - 1) {
        return;
    }
    if (!actor->getHaveStatusInfo().isSelfImmolation()) {
        return;
    }
    actor->getHaveStatusInfo().setSelfImmolation(false);
    if (actor->getCharacterType() == MONSTER) {
        int drawCtrlId = actor->getHaveStatusInfo().getDrawCtrlId();
        BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x1F);
    }
}

THUMB void btl::BattleActorAnimation::setMosyasSetup(status::UseActionParam* useActionParam)
{
    status::CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    status::CharacterStatus* target = useActionParam->getTargetCharacterStatus(0);
    int actionIndex = useActionParam->getActionIndex();
    if (actor && target && actor->getCharacterType() == MONSTER && actionIndex == 0x2F) {
        int monsterIndex = target->getHaveStatusInfo().haveStatus_.getMonsterKind();
        GameMonster::setupTexture(monsterIndex);
    }
}

THUMB void btl::BattleActorAnimation::setMosyasChange(status::CharacterStatus* actor)
{
    if (actor == NULL) {
        return;
    }
    if (actor->getCharacterType() != MONSTER) {
        return;
    }
    if (!actor->getHaveStatusInfo().isMosyasStart()) {
        return;
    }
    actor->getHaveStatusInfo().setMosyasStart(false);
    int ctrlIdDraw = actor->getHaveStatusInfo().getDrawCtrlId();
    int monsterGroup = ((status::MonsterStatus*)actor)->getMonsterGroup();
    dss::Fix32Vector3 pos = BattleMonsterDraw2::getSingleton().getMonster(ctrlIdDraw).getPosition();
    BattleMonsterDraw2::getSingleton().cleanup(ctrlIdDraw);
    int ctrlIdDraw2 = BattleMonsterDraw2::getSingleton().setup(monsterGroup, ((status::MonsterStatus*)actor)->getMosyasMonsterIndex(), true);
    actor->getHaveStatusInfo().setDrawCtrlId(ctrlIdDraw2);
    BattleMonsterDraw2::getSingleton().changeArrayCtrl(ctrlIdDraw, ctrlIdDraw2);
    BattleMonsterDraw2::getSingleton().setupBattleArray(ctrlIdDraw2, false);
    actor->getHaveStatusInfo().setDisableTextureCache(false);
}

THUMB void btl::BattleActorAnimation::setMosyasReverse(status::CharacterStatus* actor)
{
    if (!actor->getHaveStatusInfo().isMosyasRelease()) {
        return;
    }
    int ctrlIdDraw = actor->getHaveStatusInfo().getDrawCtrlId();
    int monsterGroup = ((status::MonsterStatus*)actor)->getMonsterGroup();
    dss::Fix32Vector3 pos = BattleMonsterDraw2::getSingleton().getMonster(ctrlIdDraw).getPosition();
    BattleMonsterDraw2::getSingleton().cleanup(ctrlIdDraw);
    int ctrlIdDraw2 = BattleMonsterDraw2::getSingleton().setup(monsterGroup, actor->getCharacterIndex(), true);
    actor->getHaveStatusInfo().setDrawCtrlId(ctrlIdDraw2);
    BattleMonsterDraw2::getSingleton().changeArrayCtrl(ctrlIdDraw, ctrlIdDraw2);
    BattleMonsterDraw2::getSingleton().setupBattleArray(ctrlIdDraw2, false);
    actor->getHaveStatusInfo().setMosyasRelease(false);
    if (!actor->getHaveStatusInfo().isDisableTextureCache()) {
        GameMonster::cleanupTexture(((status::MonsterStatus*)actor)->getMosyasMonsterIndex());
    }
    actor->getHaveStatusInfo().setDisableTextureCache(false);
}

THUMB void btl::BattleActorAnimation::setCallFriend(status::CharacterStatus* target)
{
    if (target == NULL) {
        return;
    }
    if (!target->getHaveStatusInfo().isCallFriend()) {
        return;
    }
    target->getHaveStatusInfo().setCallFriend(false);
    BattleMonsterDraw2::getSingleton().startAnimationWithLoop(target->getHaveStatusInfo().getDrawCtrlId(), 0x20, true);
}

THUMB void btl::BattleActorAnimation::gattaiSlimeStart(status::CharacterStatus* actor, int actionIndex)
{
    if (actor == NULL) {
        return;
    }
    if (!actor->getHaveStatusInfo().isAttackEnable()) {
        return;
    }
    if (actionIndex != 0x9E) {
        return;
    }
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        int drawCtrlId = status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getDrawCtrlId();
        if (actor == &status::g_Monster.getMonsterStatus(i)) {
            actor->getHaveStatusInfo().setMonsterChange(true);
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startGattai();
            dss::Fix32Vector3 pos(0, 0, 0);
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setPosition(pos);
            SoundManager::playSe(0x2C1, 0);
            GameMonster::setupTexture(0x6B);
            int bookIndex = status::g_BattleResult.getMonsterBookIndex(0x6B);
            if (bookIndex != -1) {
                status::g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
        else {
            dss::Fix32Vector3 pos(0, -0x30, 0);
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setPosition(pos);
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).disappearGattaiSlime();
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setTransOfEnd();
            actor->getHaveStatusInfo().setMonsterChange(true);
        }
    }
}

THUMB void btl::BattleActorAnimation::gattaiSlime(status::CharacterStatus* actor, int actionIndex)
{
    if (actor != NULL && actor->getHaveStatusInfo().isAttackEnable() && actionIndex == 0x9E) {
        if (!actor->getHaveStatusInfo().isMonsterChange()) {
            return;
        }
        actor->getHaveBattleStatus().newBaseChangeMonster(0x6B);
        actor->getHaveStatusInfo().setMonsterChange(false);
        int ctrlIdDraw = actor->getHaveStatusInfo().getDrawCtrlId();
        int monsterGroup = ((status::MonsterStatus*)actor)->getMonsterGroup();
        dss::Fix32Vector3 pos = BattleMonsterDraw2::getSingleton().getMonster(ctrlIdDraw).getPosition();
        BattleMonsterDraw2::getSingleton().cleanup(ctrlIdDraw);
        for (int i = 0; i < status::g_Monster.getCount(); i++) {
            if (status::g_Monster.getMonsterStatus(i).isBattleEnable() && &status::g_Monster.getMonsterStatus(i) != actor) {
                status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().setDisappearFlag(true);
                status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().setDeath();
                status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().setDrawCtrlId(-1);
            }
        }
        actor->setCharacterIndex(0x6B);
        unsigned short hpMax = actor->getHaveStatusInfo().getHpMax();
        unsigned short rate = UnkDssRand::rand(25) + 76;
        unsigned short hp = hpMax * rate / 100;
        if (hp == 0) {
            hp = 1;
        }
        actor->getHaveStatusInfo().setHp(hp);
        actor->getHaveStatusInfo().getStatusChange().clear();
        Encount::getSingleton()->setMonsterIndex(0, 0x6B);
        Encount::getSingleton()->setMonsterIndex(1, 0);
        Encount::getSingleton()->setMonsterIndex(2, 0);
        Encount::getSingleton()->setMonsterIndex(3, 0);
        Encount::getSingleton()->setMonsterCount(0, 1);
        Encount::getSingleton()->setMonsterCount(1, 0);
        Encount::getSingleton()->setMonsterCount(2, 0);
        Encount::getSingleton()->setMonsterCount(3, 0);
        int ctrlIdDraw2 = BattleMonsterDraw2::getSingleton().setup(monsterGroup, actor->getHaveBattleStatus().index_, true);
        BattleMonsterDraw2::getSingleton().getMonster(ctrlIdDraw2).setPosition(pos);
        actor->getHaveStatusInfo().setDrawCtrlId(ctrlIdDraw2);
        GameMonster::cleanupTexture(0x6B);
    }
}
