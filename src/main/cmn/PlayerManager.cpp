#include "main/cmn/PlayerManager.hpp"

int cmn::PlayerManager::locked_;

inline void cmn::PlayerManager::resetParty()
{
}

THUMB cmn::PlayerManager::PlayerManager()
    : flagMapLink_(0), charaColl_(1)
{
    scriptMove_.setup();
    talkRefresh_ = 0;
}

THUMB cmn::PlayerManager::~PlayerManager()
{
}

THUMB void cmn::PlayerManager::setLock(bool flag)
{
    if (flag) {
        locked_++;
        return;
    }
    locked_--;
}

THUMB bool cmn::PlayerManager::isLock()
{
    return locked_ != 0;
}

THUMB void cmn::PlayerManager::setScriptSearchObject(int uid)
{
    int index = -1;
    for (int i = 0; i < SCRIPT_SEARCH_OBJECT_NUM; i++) {
        if (uid == scriptSearchUid_[i]) {
            return;
        }
        if (scriptSearchUid_[i] == 0 && index == -1) {
            index = i;
        }
    }
    if (index != -1) {
        scriptSearchUid_[index] = uid;
    }
}

THUMB void cmn::PlayerManager::delScriptSearchObject(int uid)
{
    for (int i = 0; i < SCRIPT_SEARCH_OBJECT_NUM; i++) {
        if (scriptSearchUid_[i] == uid) {
            scriptSearchUid_[i] = 0;
            return;
        }
    }
}

THUMB void cmn::PlayerManager::resetAlpha()
{
}
