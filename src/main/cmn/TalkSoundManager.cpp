#include "main/cmn/TalkSoundManager.hpp"
#include "main/leveldata/CharaData.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/PartyStatus.hpp"
#include "ov001/town/TownCharacterManager.hpp"

inline unsigned short dq5::level::CharaData::getIndex()
{
    return index;
}

inline dq5::level::CharaData* dq5::level::CharaData::getRecord(int index)
{
    return (CharaData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline unsigned int dq5::level::CharaData::getArraySize()
{
    return binary_.getRecordCount();
}

inline bool TownCharacterManager::checkVoice(int index)
{
    return character_[index]->checkVoice();
}

inline int TownCharacterManager::getVoice(int index)
{
    return character_[index]->getVoice();
}

inline char dq5::level::CharaData::getVoice()
{
    return byte_1 & 3;
}

cmn::TalkSoundManager cmn::g_talkSound;

THUMB void cmn::TalkSoundManager::setup()
{
    index_ = 0;
    orderDataCount_ = 0;
    charaNo_ = 0;
    for (int i = 0; i < MESSAGE_COUNT; i++) {
        orderSound_[i] = 0x39;
    }
}

THUMB void cmn::TalkSoundManager::setVoice(int charaNo)
{
    charaNo_ = charaNo;
}

THUMB void cmn::TalkSoundManager::setMessageSound(int count, int character)
{
    int sound[MESSAGE_COUNT];

    ui_MsgSndSet(getDefaultMessageSound());
    if (orderDataCount_ > 0) {
        for (int i = 0; i < count; i++) {
            int order = getOrderMessageSound();
            if (order != 0x39) {
                sound[i] = order;
            } else {
                sound[i] = 0x39;
                ui_MsgSndSet(sound);
                return;
            }
        }
        sound[count] = 0x39;
        ui_MsgSndSet(sound);
    } else if (character != -1) {
        if (TownCharacterManager::getSingleton()->checkVoice(character) == true) {
            ui_MsgSndSet(TownCharacterManager::getSingleton()->getVoice(character));
        }
    }
}

THUMB int cmn::TalkSoundManager::getOrderMessageSound()
{
    int sound = 0x39;
    if (index_ < orderDataCount_) {
        sound = orderSound_[index_];
        index_++;
        if (index_ >= orderDataCount_) {
            index_ = 0;
            orderDataCount_ = 0;
        }
    }
    return sound;
}

THUMB int cmn::TalkSoundManager::getDefaultMessageSound()
{
    int sound = 0x30;
    for (unsigned int i = 0; i < dq5::level::CharaData::getArraySize(); i++) {
        if (charaNo_ == dq5::level::CharaData::getRecord(i)->getIndex()) {
            switch (dq5::level::CharaData::getRecord(i)->getVoice()) {
                case 1:
                    sound = 0x31;
                    break;
                case 2:
                    sound = 0x32;
                    break;
                case 3:
                    sound = 0x33;
                    break;
            }
            break;
        }
    }
    return sound;
}

THUMB void cmn::TalkSoundManager::setOrderMessage(int sound)
{
    orderSound_[orderDataCount_] = sound;
    orderDataCount_++;
}

THUMB int cmn::TalkSoundManager::getCharacterVoice(int character)
{
    int charaNo = charaNo_;
    charaNo_ = TownCharacterManager::getSingleton()->getCharaIndex(character);
    int sound = getDefaultMessageSound();
    charaNo_ = charaNo;
    return sound;
}

THUMB int cmn::TalkSoundManager::getPlayerVoice()
{
    status::g_Party.setDisplayMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!status::g_Party.getPlayerStatus(i).haveStatusInfo_.isDeath() == true) {
            int index = status::g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.getCharaIndex();
            int charaNo = charaNo_;
            charaNo_ = index;
            int sound = getDefaultMessageSound();
            charaNo_ = charaNo;
            return sound;
        }
    }
    return 0x32;
}

THUMB int cmn::TalkSoundManager::getPlayerVoice(int index)
{
    status::g_Party.setDisplayMode();
    int charaNo = charaNo_;
    charaNo_ = index;
    int sound = getDefaultMessageSound();
    charaNo_ = charaNo;
    return sound;
}

THUMB int cmn::TalkSoundManager::getMostHeroicVoice()
{
    status::g_Party.setDisplayMode();
    int count = status::g_Party.getCarriageOutCount();
    for (int i = 0; i < count; i++) {
        if (!status::g_Party.getPlayerStatus(i).haveStatusInfo_.isDeath() == true &&
            status::g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.getPlayerIndex() == 1) {
            int index = status::g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.getCharaIndex();
            int charaNo = charaNo_;
            charaNo_ = index;
            int sound = getDefaultMessageSound();
            charaNo_ = charaNo;
            return sound;
        }
    }
    status::g_Party.setPlayerMode();
    count = status::g_Party.getCarriageOutCount();
    for (int j = 0; j < count; j++) {
        if (!status::g_Party.getPlayerStatus(j).haveStatusInfo_.isDeath() == true) {
            int index = status::g_Party.getPlayerStatus(j).haveStatusInfo_.haveStatus_.getCharaIndex();
            int charaNo = charaNo_;
            charaNo_ = index;
            int sound = getDefaultMessageSound();
            charaNo_ = charaNo;
            return sound;
        }
    }
    return getPlayerVoice();
}
