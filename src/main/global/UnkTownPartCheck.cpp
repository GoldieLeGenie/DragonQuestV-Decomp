#pragma ipa file
#include "main/global/UnkTownPartCheck.hpp"
#include "main/global/UnkGlobalSystem.hpp"

THUMB UnkTownPartCheck::UnkTownPartCheck()
{
}

THUMB UnkTownPartCheck::~UnkTownPartCheck()
{
}

THUMB bool UnkTownPartCheck::isTownPart()
{
    if (data_02101c88.isCurrentPart(4)) {
        return true;
    }
    return false;
}

UnkTownPartCheck data_020efb48;
