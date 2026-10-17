#include "main/cmn/CommonWalkDamage.hpp"
#include "main/btl/Encount.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StatusChange.hpp"

int cmn::CommonWalkDamage::topStride_;
int cmn::CommonWalkDamage::partyStride_;
int cmn::CommonWalkDamage::walkCount_;
int cmn::CommonWalkDamage::effectFlag_;
int cmn::CommonWalkDamage::damageFlag_;
int cmn::CommonWalkDamage::encountFlag_;
int cmn::CommonWalkDamage::memberDamage_;
cmn::MembaerDamage cmn::CommonWalkDamage::partyDamage_[PARTY_DAMAGE_COUNT];
char cmn::CommonWalkDamage::damage_[82];

THUMB void cmn::CommonWalkDamage::setup()
{
    for (int i = 0; i < 82; i++) {
        damage_[i] = 3;
    }
    for (int j = 0; j < PARTY_DAMAGE_COUNT; j++) {
        partyDamage_[j].type = 3;
    }
    memberDamage_ = 0;
    effectFlag_ = 1;
    damageFlag_ = 1;
    encountFlag_ = 1;
    seCounter_ = -1;
    watCounter_ = -1;
    nextWatSe_ = 0;
}

THUMB void cmn::CommonWalkDamage::clear()
{
    for (int i = 0; i < 82; i++) {
        damage_[i] = 3;
    }
    for (int j = 0; j < PARTY_DAMAGE_COUNT; j++) {
        partyDamage_[j].type = 3;
    }
    memberDamage_ = 0;
    seCounter_ = -1;
}

THUMB bool cmn::CommonWalkDamage::checkWalkStride()
{
    bool ret = false;
    if (partyDamage_[0].frame % getDamageStride(partyDamage_[0].type) == 0) {
        ret = true;
    }
    damage_[0] = partyDamage_[0].type;
    if (partyDamage_[0].type != 3) {
        partyDamage_[0].frame++;
    }
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCarriageOutCount();
    for (int i = 1; i < count; i++) {
        partyDamage_[i].frame++;
        partyDamage_[i].type = damage_[i * partyStride_ - 1];
        if ((damage_[i * partyStride_ - 1] != 3 && damage_[i * partyStride_] == 3) || partyDamage_[i].frame >= getDamageStride(partyDamage_[i].type)) {
            partyDamage_[i].counter = 0;
            partyDamage_[i].frame = 0;
        }
    }
    int total = status::g_Party.getCarriageOutCount() * partyStride_;
    for (int j = 0; j < total; j++) {
        damage_[total - j] = damage_[total - j - 1];
    }
    walkCount_++;
    return ret;
}

THUMB int cmn::CommonWalkDamage::getDamageStride(int type)
{
    switch (type) {
        case 0:
        case 1:
        case 2:
            return topStride_;
    }
    return 8;
}

THUMB void cmn::CommonWalkDamage::checkWalk(dss::Fix32Vector3& position, dss::Fix32Vector3& prevPosition)
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCarriageOutCount();
    int type = 3;
    int i;
    if (position != prevPosition) {
        if (checkBarrier() == true) {
            partyDamage_[0].type = 0;
            memberDamage_ = 1;
        } else if (checkPoison() == true) {
            partyDamage_[0].type = 1;
            memberDamage_ = 1;
        } else if (checkYogan() == true) {
            partyDamage_[0].type = 2;
            memberDamage_ = 1;
        } else if (checkPuddle() == true) {
            partyDamage_[0].type = 10;
            memberDamage_ = 1;
        } else {
            partyDamage_[0].type = 3;
            partyDamage_[0].frame = 0;
        }
        if (encountFlag_ == 1) {
            if (status::StatusChange::statusToherosu_.isEnable()) {
                if (status::PartyStatusUtility::getStoryPlayerStatus().haveStatusInfo_.haveStatus_.level_ < btl::Encount::getSingleton()->encountData_.tileLevel_ + 5) {
                    btl::Encount::getSingleton()->execWalk();
                }
            } else if (status::StatusChange::statusSinobiasi_.isEnable()) {
                if (status::StatusChange::statusSinobiasi_.count_ % 4 != 0) {
                    btl::Encount::getSingleton()->execWalk();
                }
            } else if (status::StatusChange::statusMonstersFood_.isEnable()) {
                btl::Encount::getSingleton()->execWalk();
                btl::Encount::getSingleton()->execWalk();
                btl::Encount::getSingleton()->execWalk();
                btl::Encount::getSingleton()->execWalk();
            } else {
                btl::Encount::getSingleton()->execWalk();
            }
            status::g_Party.getPlayerStatus(0).walkEnvioronment();
        }
        if (memberDamage_ == 1 && checkWalkStride() == true && partyDamage_[0].type != 3) {
            partyDamage_[0].counter = 0;
            walkCount_ = 0;
        }
        if (damageFlag_ == 1) {
            for (i = 0; i < count; i++) {
                if (status::g_Party.getPlayerStatus(i).walkNormal() == true && effectFlag_ == 1) {
                    setPartyMemberColor(status::g_Party.getPlayerIndex(i), 1);
                    partyDamage_[i].counter = 0;
                }
            }
        }
    }
    for (i = 0; i < count; i++) {
        if (memberDamage_ == 1 && partyDamage_[i].type != 3) {
            if (partyDamage_[i].counter == 0 && !status::g_Party.getPlayerStatus(i).haveStatusInfo_.isDeath() == true && damageFlag_ == 1) {
                if (status::g_Party.getPlayerStatus(i).walkDamage((StageDamage)partyDamage_[i].type) == true && effectFlag_ == 1) {
                    setPartyMemberColor(status::g_Party.getPlayerIndex(i), partyDamage_[i].type);
                }
                if (partyDamage_[i].type == 10) {
                    setPuddleEffect(i);
                }
            }
            type = partyDamage_[i].type;
        }
        if (partyDamage_[i].counter == 4) {
            status::g_Party.setBattleMode();
            setPartyMemberColor(status::g_Party.getPlayerIndex(i), 3);
        }
        partyDamage_[i].counter++;
    }
    if (memberDamage_ == 1 && type == 3 && walkCount_ > partyStride_ * (count - 1)) {
        memberDamage_ = 0;
        for (i = 0; i < count; i++) {
            setPartyMemberColor(status::g_Party.getPlayerIndex(i), 3);
        }
        for (int j = 0; j < 82; j++) {
            damage_[j] = 3;
        }
        walkCount_ = 0;
    }
    if (seCounter_ != -1) {
        seCounter_++;
        if (seCounter_ >= 12) {
            seCounter_ = -1;
            if (nextSe_ == 1) {
                if (nextSeType_ == 0) {
                    SoundManager::playSe(0x13c, 0);
                } else if (nextSeType_ == 1) {
                    SoundManager::playSe(0x13b, 0);
                } else if (nextSeType_ == 2) {
                    SoundManager::playSe(0x13c, 0);
                } else if (nextSeType_ == 10) {
                    SoundManager::playSe2(0x72, 0);
                }
                nextSe_ = 0;
                seCounter_ = 0;
            }
        }
    }
    if (watCounter_ != -1) {
        watCounter_++;
        if (watCounter_ >= 12) {
            watCounter_ = -1;
            if (nextWatSe_ == 1) {
                SoundManager::playSe2(0x72, 0);
                nextWatSe_ = 0;
                watCounter_ = 0;
            }
        }
    }
}

THUMB bool cmn::CommonWalkDamage::checkPuddle()
{
    return false;
}

THUMB bool cmn::CommonWalkDamage::isPlaySe()
{
    if (seCounter_ == -1) {
        seCounter_ = 0;
        return true;
    }
    return false;
}

THUMB void cmn::CommonWalkDamage::setNextSe(int type)
{
    if (type == 3) {
        return;
    }
    if (seCounter_ > 0) {
        nextSe_ = 1;
        nextSeType_ = type;
    }
}

THUMB bool cmn::CommonWalkDamage::checkYogan()
{
    return false;
}

THUMB void cmn::CommonWalkDamage::setPuddleEffect(int index)
{
}

THUMB void cmn::CommonWalkDamage::resetMemberColor()
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCarriageOutCount();
    for (int i = 0; i < count; i++) {
        setPartyMemberColor(status::g_Party.getPlayerIndex(i), 3);
    }
}
