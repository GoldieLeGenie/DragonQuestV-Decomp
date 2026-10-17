#include "main/status/GameStatus.hpp"
#include "main/text/TextAPI.hpp"

status::GameStatus status::g_Game;

THUMB status::GameStatus::GameStatus()
{
    playTime_ = 0;
}

THUMB status::GameStatus::~GameStatus()
{
}

THUMB void status::GameStatus::initialize()
{
    playTime_ = 0;
}

THUMB void status::GameStatus::setPlayTime(unsigned int time)
{
    playTime_ = time;
    if (playTime_ > 0xcdfd7f0) {
        playTime_ = 0xcdfd7f0;
    }
}

THUMB void status::GameStatus::addPlayTime(unsigned int time)
{
    playTime_ += time;
    if (playTime_ > 0xcdfd7f0) {
        playTime_ = 0xcdfd7f0;
    }
}

THUMB unsigned int status::GameStatus::getPlayTime()
{
    return playTime_;
}

THUMB void status::GameStatus::resetUniqueID()
{
    unsigned char macAddr[6];
    func_020887b4(macAddr);
    unsigned int A = macAddr[3];
    unsigned int B = macAddr[4];
    unsigned int C = macAddr[5];
    unsigned int D = UnkDssRand::rand(0x100);
    uniqueID_ = (A << 24) + (B << 16) + (C << 8) + D;
}

THUMB unsigned int status::GameStatus::getUniqueID()
{
    if (uniqueID_ == 0) {
        resetUniqueID();
    }
    return uniqueID_;
}

THUMB void status::GameStatus::setUniqueID(unsigned int id)
{
    uniqueID_ = id;
}

THUMB void status::GameStatus::setLanguage(Language language)
{
    language_ = language;
    if (language == Japanese) {
        func_0204e54c(1);
    }
    else {
        func_0204e54c(2);
    }
    switch (language_) {
    case Japanese:
        TextAPI::setLanguage(0);
        break;
    case English:
        TextAPI::setLanguage(1);
        break;
    case French:
        TextAPI::setLanguage(2);
        break;
    case German:
        TextAPI::setLanguage(3);
        break;
    case Italian:
        TextAPI::setLanguage(4);
        break;
    case Spanish:
        TextAPI::setLanguage(5);
        break;
    }
}
