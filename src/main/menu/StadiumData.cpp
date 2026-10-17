#include "main/menu/StadiumData.hpp"

inline StadiumData::StadiumData()
{
    cleanUp();
}

THUMB void StadiumData::cleanUp()
{
    stadiumFlag_ = 0;
    monsterDeath_ = 0;
    odds_ = 0;
    monsterID_ = 0;
    monsterArray_ = 0;
    monsterNumber_ = 0;
    result_ = 0;
    retire_ = 0;
}

StadiumData g_StadiumData;
