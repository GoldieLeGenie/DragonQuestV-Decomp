#include "main/status/MenuStatus.hpp"

inline status::MenuStatus::MenuStatus()
{
}

status::MenuStatus status::g_Menu;

ARM void status::MenuStatus::initialize()
{
    ownerVoice_ = 0x30;
    drawFlag_ = 0;
    bookingFlag_ = 0;
    returnMenuType_ = 0;
    surechigaiMode_ = 0;
    menuEventFlag_ = 0;
    eventInnStart_ = 0;
    playerItemFlag_ = 0;
    addMessageFlag_ = 0;
    curseEffectStart_ = 0;
    fukubikiPrize_ = 0;
    innCount_ = 0;
    actorIndex_ = 0;
    targetIndex_ = 0;
    itemIndex_ = 0;
    sackActive_ = 0;
    sackActivePage_ = 0;
    meisanSackActive_ = 0;
    meisanSackActivePage_ = 0;
    pantherNo_ = 0;
    addMonsterIndex_ = 0;
    for (int i = 0; i < 3; i++) {
        messageNo_[i] = 0;
        messageVoice_[i] = 0x30;
    }
    for (int i = 0; i < 8; i++) {
        menuEventNo_[i] = 0;
    }
}

ARM void status::MenuStatus::setMenuEventNo(short* item, int count)
{
    for (int i = 0; i < count; i++) {
        menuEventNo_[i] = item[i];
    }
}

ARM bool status::MenuStatus::checkMenuEventNo(int checkNo)
{
    for (int i = 0; i < 8; i++) {
        if (checkNo == menuEventNo_[i]) {
            itemIndex_ = menuEventNo_[i];
            return true;
        }
    }
    return false;
}

ARM void status::MenuStatus::resetMenuEventNo()
{
    for (int i = 0; i < 8; i++) {
        menuEventNo_[i] = 0;
    }
}

ARM status::MenuStatus::~MenuStatus()
{
}
