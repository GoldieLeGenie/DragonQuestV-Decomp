#include "ov000/btl/BattleTurn.hpp"
#include "ov000/btl/BattleActor.hpp"
#include "ov000/btl/BattleActorManager.hpp"

THUMB btl::BattleTurn::BattleTurn()
{
}

THUMB btl::BattleTurn::~BattleTurn()
{
}

THUMB void btl::BattleTurn::setBattleActor(BattleActor* actor)
{
    battleActor_ = actor;
    flag_.clear();
}

THUMB void btl::BattleTurn::execute()
{
    if (!flag_.check(FLAG_INITIALIZED)) {
        setup();
        flag_.set(FLAG_INITIALIZED);
    }
    if (!flag_.check(FLAG_TERMINATED)) {
        exec();
        if (checkEnd()) {
            cleanup();
            flag_.set(FLAG_TERMINATED);
        }
    }
}

THUMB bool btl::BattleTurn::isEnd()
{
    return flag_.check(FLAG_TERMINATED);
}

THUMB bool btl::BattleTurn::checkEnd()
{
    if (battleActor_->isEnd() && isBattleActorEnd()) {
        return true;
    }
    return false;
}

THUMB void btl::BattleTurn::setup()
{
    battleActor_->setup();
}

THUMB void btl::BattleTurn::cleanup()
{
    flag_.clear();
    BattleActorManager::getSingleton()->execEndOfTurn();
}

THUMB void btl::BattleTurn::exec()
{
    battleActor_->execute();
}

THUMB bool btl::BattleTurn::isBattleActorEnd()
{
    if (battleActor_->isEnd()) {
        return true;
    }
    if (!battleActor_->isActionEnable()) {
        return true;
    }
    return false;
}

THUMB void btl::BattleTurn::reattack()
{
    flag_.clear();
    battleActor_->reattack();
}
