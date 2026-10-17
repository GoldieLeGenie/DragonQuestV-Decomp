#include "main/cmn/GameManager.hpp"

inline void cmn::PlayerManager::resetParty()
{
}

THUMB cmn::GameManager::GameManager()
{
}

THUMB cmn::GameManager& cmn::GameManager::getSingleton()
{
    static GameManager gameManager;
    return gameManager;
}

THUMB void cmn::GameManager::initialize()
{
    playerManager_ = 0;
}

THUMB void cmn::GameManager::terminate()
{
}

THUMB void cmn::GameManager::execute()
{
}

THUMB void cmn::GameManager::resetParty()
{
    playerManager_->resetParty();
}
