#pragma ipa file
#include "ov005/fld/FieldPartyDraw.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/leveldata/CharaData.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/status/PartyStatus.hpp"

THUMB inline int status::PartyStatus::isCarriage()
{
    return carriage_;
}

THUMB inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline dq5::level::CharaData* dq5::level::CharaData::getRecord(int index)
{
    return (CharaData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline short status::PlayerStatus::getIndex()
{
    return index_;
}

THUMB fld::FieldPartyDraw::FieldPartyDraw()
{
}

THUMB fld::FieldPartyDraw::~FieldPartyDraw()
{
}

// setup calls its inline helpers out of line (their copies follow it in .text)
#pragma dont_inline on
THUMB void fld::FieldPartyDraw::setup()
{
    status::PlayerStatus playerStatus;
    int charaIndex;
    status::g_Party.setDisplayMode();
    countReal_ = count_ = status::g_Party.getCount();
    if (status::g_Party.isCarriage()) {
        count_ += 2;
        countReal_ = count_;
        for (int i = 0; i < count_; i++) {
            switch (i) {
            case 0:
                playerStatus = status::g_Party.getPlayerStatus(i);
                charaIndex = playerStatus.getHaveStatusInfo().getCharaIndex();
                break;
            case 1:
                charaIndex = 0x12d;
                break;
            case 2:
                charaIndex = 0x12c;
                break;
            default:
                playerStatus = status::g_Party.getPlayerStatus(i - 2);
                charaIndex = playerStatus.getHaveStatusInfo().getCharaIndex();
                break;
            }
            if (charaIndex != 0x12d && charaIndex != 0x12d) {
                if (playerStatus.getHaveStatusInfo().isDeath()) {
                    charaIndex = 0x59;
                }
            }
            setupChara(i, charaIndex);
        }
    } else {
        for (int i = 0; i < count_; i++) {
            playerStatus = status::g_Party.getPlayerStatus(i);
            charaIndex = playerStatus.getHaveStatusInfo().getCharaIndex();
            if (playerStatus.getHaveStatusInfo().isDeath()) {
                charaIndex = 0x59;
            }
            setupChara(i, charaIndex);
        }
    }
}
#pragma dont_inline reset

THUMB void fld::FieldPartyDraw::reload()
{
    for (int i = 0; i < count_; i++) {
        partyCharacter_[i].reload();
    }
    SpriteCharacter::unkfunc_02058754();
}

THUMB void fld::FieldPartyDraw::setupChara(int index, int charaNo)
{
    char name[0x80];
    charaIndex_[index] = charaNo;
    int charaparam = dq5::level::g_LevelDataUtility.getCharaParamIndex(charaNo);
    if (dq5::level::CharaData::getRecord(charaparam)->width < 0x20) {
        dq5::level::CharaData::getRecord(charaparam)->width = 0x20;
    }
    int height;
    unsigned char width = dq5::level::CharaData::getRecord(charaparam)->width;
    height = dq5::level::CharaData::getRecord(charaparam)->height;
    dss::sprintf_s(name, sizeof(name), "data/chr/h%03d.pack", charaNo);
    partyCharacter_[index].setup(name, width, height, dq5::level::CharaData::loadSwitch_);
    partyCharacter_[index].depth_ = index - 6;
    partyCharacter_[index].setDirection(4);
}

THUMB void fld::FieldPartyDraw::cleanup()
{
    for (int i = 0; i < countReal_; i++) {
        partyCharacter_[i].cleanup();
    }
}

THUMB void fld::FieldPartyDraw::draw()
{
    SpriteCharacter* tempDraw[PARTY_DRAW_MAX];
    int temp;
    int no;
    int count;
    for (int i = 0; i < countReal_; i++) {
        tempDraw[i] = &partyCharacter_[i];
    }
    no = 0;
    for (int i = 0; i < countReal_; i++) {
        temp = -1000000;
        for (count = 0; count < countReal_; count++) {
            if (tempDraw[count] != NULL && temp < valueY_[count]) {
                no = count;
                temp = valueY_[count];
            }
        }
        partyCharacter_[no].depth_ = 10 - i;
        partyCharacter_[no].draw();
        tempDraw[no] = NULL;
    }
}

THUMB void fld::FieldPartyDraw::setPosition(int index, dss::Vector2<int> pos)
{
    partyCharacter_[index].setPosition(pos);
}

THUMB void fld::FieldPartyDraw::setDepth(int index, int value)
{
    valueY_[index] = value;
}

THUMB void fld::FieldPartyDraw::setRotate(int index, unsigned int dirIdx)
{
    partyCharacter_[index].setDirection(dirIdx);
}

THUMB void fld::FieldPartyDraw::setDrawNone()
{
    for (int i = 0; i < countReal_; i++) {
        partyCharacter_[i].setDisplayEnable(0);
    }
}

THUMB void fld::FieldPartyDraw::resetDrawCount()
{
    for (int i = 0; i < countReal_; i++) {
        partyCharacter_[i].setDisplayEnable(1);
        partyCharacter_[i].setAlpha(0x1f);
    }
}

THUMB void fld::FieldPartyDraw::setDrawPartyOne()
{
    for (int i = 1; i < count_; i++) {
        partyCharacter_[i].setDisplayEnable(0);
    }
}

THUMB void fld::FieldPartyDraw::changePlayerPose(int charaId, int charaIndex)
{
    int index = -1;
    for (int i = 0; i < count_; i++) {
        if (charaId == status::g_Party.getPlayerStatus(i).getIndex()) {
            index = i;
            break;
        }
    }
    if (index >= 0) {
        partyCharacter_[index].cleanup();
        setupChara(index, charaIndex);
    }
}
