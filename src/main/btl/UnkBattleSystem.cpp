#pragma ipa file
#include "main/btl/UnkBattleSystem.hpp"

THUMB btl::UnkBattleSystem::UnkBattleSystem()
{
    static int unk;
}

THUMB btl::UnkBattleSystem* btl::UnkBattleSystem::getSingleton()
{
    static UnkBattleSystem m_singleton;
    return &m_singleton;
}

THUMB void btl::UnkBattleSystem::initialize()
{
}

THUMB void btl::UnkBattleSystem::terminate()
{
}

THUMB void btl::UnkBattleSystem::execute()
{
}

THUMB void btl::UnkBattleSystem::draw()
{
}
