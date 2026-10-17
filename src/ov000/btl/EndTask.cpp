#include "ov000/btl/BattleActorExec2.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/UseActionParam.hpp"

inline status::HaveItem& status::HaveStatusInfo::getHaveItem() { return haveItem_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }

status::UseActionParam* btl::EndTask::useActionParam_;

THUMB void btl::EndTask::initialize()
{
    status::CharacterStatus* actor = useActionParam_->getActorCharacterStatus();
    if (actor) {
        status::g_Party.setBattleMode();
        int count = status::g_Party.getCount();
        {
            bool megante = false;
            if (status::g_Monster.getAliveCount()) {
                for (int i = 0; i < count; i++) {
                    if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isMeganteRing()) {
                        if (megante) {
                            status::g_Party.getPlayerStatus(i).getHaveStatusInfo().setMeganteRing(false);
                        }
                        status::HaveStatusInfo::setGlbMeganteRing(true);
                        megante = true;
                    }
                }
            }
            for (int i = 0; i < count; i++) {
                if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveItem().isItem(0xB8) && status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isInvokeRebirthStone()) {
                    status::HaveStatusInfo::setGlbRebirthStone(true);
                }
            }
        }
    }
}

THUMB void btl::EndTask::terminate()
{
}

THUMB void btl::EndTask::execute()
{
}
