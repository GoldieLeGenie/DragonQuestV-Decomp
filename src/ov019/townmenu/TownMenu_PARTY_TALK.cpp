#pragma ipa file
#include "ov019/townmenu/TownMenu_PARTY_TALK.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void TownMenu_PARTY_TALK::menuDraw()
{
}

inline void TownMenu_PARTY_TALK::menuExecute()
{
}

inline int cmn::PartyTalk::getPartyTalkMessCount()
{
    return partyTalk_[partyTalkNo_].mesCount_;
}

inline int cmn::PartyTalk::getTalkMonsterIndex()
{
    return partyTalk_[partyTalkNo_].talkMonster_;
}

inline int cmn::PartyTalk::getPartyTalkFirstMessage(int index)
{
    return partyTalk_[partyTalkNo_].message_[index];
}

inline int cmn::PartyTalk::getPartyTalkSoundChara(int index)
{
    return partyTalk_[partyTalkNo_].mesSoundIndex_[index];
}

inline int cmn::PartyTalk::getPartyTalkMessageType()
{
    return partyTalk_[partyTalkNo_].messageType_;
}

inline int cmn::PartyTalk::getPartyTalkYesNoCount(int index)
{
    return partyTalk_[partyTalkNo_].yesnoCount_[index];
}

THUMB void TownMenu_PARTY_TALK::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::NORMAL_MODE);
    cmn::g_talkSound.setup();
    cmn::PartyTalk::getSingleton().setPartyTalkMessage();
    cmn::PartyTalk& talk = cmn::PartyTalk::getSingleton();
    int count = 0;
    int playerActor = 0;
    int playerCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    int mesCount = talk.getPartyTalkMessCount();
    int playerList[8] = {-1};
    for (int i = 0; i < 8; i++) {
        playerList[i] = -1;
    }
    for (int i = 0; i < playerCount; i++) {
        if (MenuStatusInfo::isCarriagePosition(i, MenuStatusInfo::POSITION_CARRIAGE_OUT) == true && MenuStatusInfo::getPlayerIndex(i) != 1) {
            if (!MenuStatusInfo::isPlayerCondition(i, MenuStatusInfo::CONDITION_DEATH) && !MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_FRIEND_MONSTER)) {
                playerList[count] = i;
                count++;
            }
        } else if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_NORMAL_NPC) == true) {
            if (status::g_Party.getNpcPlayerIndex() != 0x10 || g_AreaFlag.check(0x35f)) {
                playerList[count] = i;
                count++;
            }
        }
    }
    mode_ = 2;
    if (count != 0) {
        playerActor = UnkDssRand::rand(count);
    }
    if (mesCount != 0) {
        if (playerCount > 1) {
            if (playerList[playerActor] != -1) {
                if (MenuStatusInfo::isPlayerType(playerList[playerActor], MenuStatusInfo::TYPE_NORMAL_NPC) == true) {
                    TextAPI::setMACRO0(1, 0x50000000, status::g_Party.getNpcPlayerIndex());
                } else {
                    TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(playerList[playerActor]));
                }
            }
            TextAPI::setMACRO0(0x7e, 0x50000000, talk.getTalkMonsterIndex());
            if (talk.getPartyTalkFirstMessage(0) == 0x7a223) {
                setMacroTeaSet();
            }
        }
        if (talk.getPartyTalkMessageType() == cmn::PartyTalk::TYPE_SHAKE) {
            s_draw->shakeRequest_ = 2;
        }
        if (talk.getPartyTalkFirstMessage(0) == 0xc4292) {
            int charaIndex = MenuStatusInfo::getPlayerCharaIndex(playerList[playerActor]);
            cmn::g_talkSound.setOrderMessage(cmn::g_talkSound.getPlayerVoice(charaIndex));
            cmn::g_talkSound.setMessageSound(1, -1);
        } else {
            if (talk.getPartyTalkMessageType() == cmn::PartyTalk::TYPE_YESNO) {
                mesCount = talk.getPartyTalkYesNoCount(0);
            }
            for (int i = 0; i < mesCount; i++) {
                cmn::g_talkSound.setOrderMessage(talk.getPartyTalkSoundChara(i));
            }
            cmn::g_talkSound.setMessageSound(mesCount, -1);
        }
        gTownMenu_MESSAGE.openMessageForTALK();
        for (int i = 0; i < mesCount; i++) {
            gTownMenu_MESSAGE.addMessage(talk.getPartyTalkFirstMessage(i));
        }
        if (talk.getPartyTalkMessageType() == cmn::PartyTalk::TYPE_YESNO) {
            gTownMenu_MESSAGE.setYesNo();
            mode_ = 1;
        }
    } else {
        close();
        gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
    }
}

THUMB void TownMenu_PARTY_TALK::menuUpdate()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            cmn::PartyTalk& talk = cmn::PartyTalk::getSingleton();
            gTownMenu_MESSAGE.close();
            if (mode_ == 2) {
                close();
                gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
                return;
            }
            int start = talk.getPartyTalkYesNoCount(0);
            int end = start + talk.getPartyTalkYesNoCount(1);
            if (start == 0) {
                start = end;
                end = talk.getPartyTalkYesNoCount(2);
            }
            for (int i = start; i < end; i++) {
                cmn::g_talkSound.setOrderMessage(talk.getPartyTalkSoundChara(i));
            }
            cmn::g_talkSound.setMessageSound(end - start, -1);
            gTownMenu_MESSAGE.openMessageForTALK();
            for (int i = start; i < end; i++) {
                gTownMenu_MESSAGE.addMessage(talk.getPartyTalkFirstMessage(i));
            }
            mode_ = 2;
        } else if (stat == MENUBASE_STAT_CANCEL) {
            cmn::PartyTalk& talk = cmn::PartyTalk::getSingleton();
            gTownMenu_MESSAGE.close();
            int start = talk.getPartyTalkYesNoCount(0) + talk.getPartyTalkYesNoCount(1);
            int end = start + talk.getPartyTalkYesNoCount(2);
            if (talk.getPartyTalkYesNoCount(2) == 0) {
                start = talk.getPartyTalkYesNoCount(0);
                end = start + talk.getPartyTalkYesNoCount(1);
            }
            for (int i = start; i < end; i++) {
                cmn::g_talkSound.setOrderMessage(talk.getPartyTalkSoundChara(i));
            }
            cmn::g_talkSound.setMessageSound(end - start, -1);
            gTownMenu_MESSAGE.openMessageForTALK();
            for (int i = start; i < end; i++) {
                gTownMenu_MESSAGE.addMessage(talk.getPartyTalkFirstMessage(i));
            }
            mode_ = 2;
        }
    }
}

THUMB void TownMenu_PARTY_TALK::setMacroTeaSet()
{
    unsigned int teaset[3] = {0};
    for (int i = 0; i < 3; i++) {
        teaset[i] = 0;
    }
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < partyCount; i++) {
        if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_PLAYER) == true) {
            if (MenuStatusInfo::isPlayerHaveItem(i, 0xd8) == true) {
                teaset[0] = 0xd8;
            }
            if (MenuStatusInfo::isPlayerHaveItem(i, 0xd9) == true) {
                teaset[1] = 0xd9;
            }
            if (MenuStatusInfo::isPlayerHaveItem(i, 0xda) == true) {
                teaset[2] = 0xda;
            }
        }
    }
    if (teaset[0] == 0 && MenuStatusInfo::isFukuroHaveItem(0xd8) == 1) {
        teaset[0] = 0xd8;
    }
    if (teaset[1] == 0 && MenuStatusInfo::isFukuroHaveItem(0xd9) == 1) {
        teaset[1] = 0xd9;
    }
    if (teaset[2] == 0 && MenuStatusInfo::isFukuroHaveItem(0xda) == 1) {
        teaset[2] = 0xda;
    }
    for (int i = 0; i < 3; i++) {
        if (teaset[i] != 0) {
            TextAPI::setMACRO0(10, 0x40000000, teaset[i]);
            return;
        }
    }
}
