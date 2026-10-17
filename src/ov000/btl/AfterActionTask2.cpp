#include "ov000/btl/BattleActorExec2.hpp"
#include "ov000/btl/BattleActorAnimation.hpp"
#include "ov000/btl/BattleActorMacro.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "ov000/btl/BattleMonster.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseActionMacro.hpp"
#include "main/status/UseActionParam.hpp"

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }

status::UseActionParam* btl::AfterActionTask2::useActionParam_;

THUMB bool btl::AfterActionTask2::isEnableStatusChange()
{
    return true;
}

THUMB void btl::AfterActionTask2::initialize()
{
    if (useActionParam_->getActionIndex() == 0x1D2 || useActionParam_->getActionIndex() == 0x103 || useActionParam_->getActionIndex() == 0x1DE) {
        return;
    }
    if (!isEnableStatusChange()) {
        return;
    }
    status::StatusChange& statusChange = useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange();
    statusChange.printAll();
    statusChange.execEndOfTurn();
    if (useActionParam_->getActorCharacterStatus()) {
        useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().setStatusChangeRelease(false);
    }
    mess_ = isMessageStatusChangeRelease();
}

THUMB void btl::AfterActionTask2::terminate()
{
}

THUMB void btl::AfterActionTask2::execute()
{
}

THUMB bool btl::AfterActionTask2::isMessageStatusChangeRelease()
{
    bool ret = false;
    status::StatusChange& statusChange = useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange();
    status::CharacterStatus* actor = useActionParam_->getActorCharacterStatus();
    dq5::level::ActionParam::ACTIONTYPE release = statusChange.isRelease();
    bool death = useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().isDeath();
    int monsterCount = status::g_Monster.getBattleCount();
    if (release && !death && monsterCount) {
        BattleActorMacro::setMacroActor(useActionParam_->getActorCharacterStatus(), 0);
        status::UseActionMacro::setStatusChangeMacro(useActionParam_->getActorCharacterStatus());
        if (release == dq5::level::ActionParam::ACTIONTYPE_DORAGORAM) {
            BattleActorMacro::setMacroTarget(useActionParam_->getActorCharacterStatus(), 0, 0);
            useActionParam_->getActorCharacterStatus()->getHaveBattleStatus().changeMonsterReverse();
        }
        if (release == dq5::level::ActionParam::ACTIONTYPE_MOSYASU) {
            useActionParam_->getActorCharacterStatus()->setMosyasRelease();
            BattleActorMacro::setMacroTarget(useActionParam_->getActorCharacterStatus(), 0, 0);
            BattleActorAnimation::setMosyasReverse(useActionParam_->getActorCharacterStatus());
        }
        if (release == dq5::level::ActionParam::ACTIONTYPE_TIMESTOP) {
            status::g_Party.setBattleMode();
            int count = status::g_Party.getCount();
            for (int i = 0; i < count; i++) {
                status::StatusChange& tmpStatusChange = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange();
                if (tmpStatusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_TIMESTOP)) {
                    tmpStatusChange.release(dq5::level::ActionParam::ACTIONTYPE_TIMESTOP);
                }
            }
            count = status::g_Monster.getCount();
            for (int i = 0; i < count; i++) {
                status::StatusChange& tmpStatusChange = status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange();
                if (tmpStatusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_TIMESTOP)) {
                    tmpStatusChange.release(dq5::level::ActionParam::ACTIONTYPE_TIMESTOP);
                }
            }
        }
        if (release == dq5::level::ActionParam::ACTIONTYPE_ASTORON) {
            int drawCtrlId = actor->getHaveStatusInfo().getDrawCtrlId();
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setPaletteAstoron(0);
        }
        status::UseActionMacro::setStatusChangeMacro(useActionParam_->getActorCharacterStatus());
        int mess = statusChange.getReleaseMessage();
        BattleMessage::setMessage(mess, 0, 0, 0);
        if (mess) {
            ret = true;
        }
    }
    return ret;
}

THUMB int btl::AfterActionTask2::isEnd()
{
    if (!mess_) {
        return true;
    }
    if (BattleAutoFeed::isEndMessage()) {
        mess_ = isMessageStatusChangeRelease();
        if (!mess_) {
            return true;
        }
    }
    return false;
}
