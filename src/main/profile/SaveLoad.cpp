#include "main/profile/SaveLoad.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkSleep.hpp"
#include "main/dss/UnkTextConvert.hpp"
#include "main/status/StageInfo.hpp"
#include "main/text/TextAPI.hpp"
#include "nitro/card.h"

#define BACKUP_LOCK_ID 0x1234
#define BANK_SIZE 0x3c00
#define BANK_OFFSET(bank) ((bank) * BANK_SIZE + 0x400)
#define PROFILE_MAGIC 0x65747261
#define PROFILE_VERSION 200804302

inline int status::StageInfo::getProfileBank() { return profileBank_; }

int profile::SaveLoad::catalogRecent_;
int profile::SaveLoad::lastSleep_;
profile::Profile* profile::SaveLoad::asyncBuff_;
int profile::SaveLoad::asyncResult_;
int profile::SaveLoad::asyncBank_;
profile::CatalogView profile::SaveLoad::catalogView_[3];

THUMB int profile::SaveLoad::checkbank(int bank)
{
    unsigned char buff[0x200];
    PROFILE_SYSTEM* system = (PROFILE_SYSTEM*)buff;
    if (!memoryload(BANK_OFFSET(bank), buff, 0x200)) {
        return -3;
    }
    if (system->MAGIC == PROFILE_MAGIC && system->VER == PROFILE_VERSION) {
        return 1;
    }
    return -1;
}

THUMB profile::CatalogView* profile::SaveLoad::getCatalogView()
{
    CatalogView* views[4];
    views[0] = &catalogView_[0];
    views[1] = &catalogView_[1];
    views[2] = &catalogView_[2];
    views[3] = &catalogView_[3];
    unsigned int seek = BANK_OFFSET(0);
    for (int i = 0; i < 4; i++) {
        unsigned char* buff = (unsigned char*)dssAlloc(&data_020fd24c, BANK_SIZE, 0x20);
        if (buff == NULL) {
            return NULL;
        }
        if (!memoryload(seek, buff, BANK_SIZE)) {
            if (buff != NULL) {
                dssFree(&data_020fd24c, buff);
            }
            return NULL;
        }
        PROFILE_RECORD* pr = (PROFILE_RECORD*)buff;
        if (pr->system[0].MAGIC == PROFILE_MAGIC && pr->system[0].VER == PROFILE_VERSION) {
            int town;
            views[i]->useFlag_ = 1;
            views[i]->id_ = pr->system[0].BOOKNO;
            switch (pr->system[0].SAVETYPE) {
            case SAVETYPE_CHURCH:
                town = getPlaceNameNo(pr->party[0].STORY_CHAPTER_NO, (char*)pr->location[0].RESTART);
                break;
            case SAVETYPE_INTERVAL:
            case SAVETYPE_NEW:
                town = getPlaceNameByChapter(pr->party[0].STORY_CHAPTER_NO);
                break;
            default:
                town = 0;
                break;
            }
            dss::strcpy_s(views[i]->name_, 0x20, (char*)pr->player[0].NAME);
            views[i]->savetype_ = pr->system[0].SAVETYPE;
            views[i]->chapter_ = pr->party[0].STORY_CHAPTER_NO;
            views[i]->level_ = pr->player[0].LEVEL;
            views[i]->town_ = town;
            views[i]->time_ = pr->party[0].PLAY_TIME;
            views[i]->clear_ = pr->system[0].CLEAR;
        } else {
            views[i]->useFlag_ = 0;
        }
        dssFree(&data_020fd24c, buff);
        seek += BANK_SIZE;
    }
    catalogRecent_ = getSaveBank();
    return catalogView_;
}

THUMB int profile::SaveLoad::getCatalogRecent()
{
    return catalogRecent_;
}

THUMB bool profile::SaveLoad::loadbank(int bank)
{
    if (!isCardOK()) {
        return false;
    }
    Profile* padr = (Profile*)dssAlloc(&data_020fd24c, sizeof(Profile), 0x20);
    if (padr == NULL) {
        return false;
    }
    padr->setup();
    memoryload(BANK_OFFSET(bank), &padr->profiledata_, BANK_SIZE);
    bool result = padr->deliverProfile(bank);
    dssFree(&data_020fd24c, padr);
    return result;
}

THUMB bool profile::SaveLoad::savebank(int bank, SAVETYPE type)
{
    if (!isCardOK()) {
        return false;
    }
    Profile* padr = (Profile*)dssAlloc(&data_020fd24c, sizeof(Profile), 0x20);
    if (padr == NULL) {
        return false;
    }
    padr->setup();
    padr->collectProfile(bank, type);
    bool result = memorysave(BANK_OFFSET(bank), &padr->profiledata_, BANK_SIZE);
    dssFree(&data_020fd24c, padr);
    if (bank < 3) {
        setSaveBank(bank);
    } else {
        setSaveBank(status::g_StageInfo.getProfileBank());
    }
    return result;
}

THUMB void profile::SaveLoad::savebankAsync(int bank, SAVETYPE type)
{
    asyncResult_ = 1;
    asyncBuff_ = NULL;
    asyncBank_ = bank;
    if (!isCardOK()) {
        asyncResult_ = 0;
        return;
    }
    asyncBuff_ = (Profile*)dssAlloc(&data_020fd24c, sizeof(Profile), 0x20);
    if (asyncBuff_ == NULL) {
        asyncResult_ = 0;
        return;
    }
    asyncBuff_->setup();
    asyncBuff_->collectProfile(bank, type);
    memorysaveAsync(BANK_OFFSET(bank), &asyncBuff_->profiledata_, BANK_SIZE);
}

THUMB int profile::SaveLoad::savebankAsyncWait()
{
    if (asyncResult_ == 0) {
        return true;
    }
    return memorysaveAsyncWait();
}

THUMB int profile::SaveLoad::savebankAsyncResult()
{
    if (asyncBuff_ != NULL) {
        dssFree(&data_020fd24c, asyncBuff_);
        asyncBuff_ = NULL;
    }
    if (asyncResult_ == 0) {
        return false;
    }
    asyncResult_ = memorysaveAsyncResult();
    if (asyncBank_ < 3) {
        setSaveBank(asyncBank_);
    } else {
        setSaveBank(status::g_StageInfo.getProfileBank());
    }
    return asyncResult_;
}

THUMB bool profile::SaveLoad::killbank(int bank)
{
    unsigned char* addr = (unsigned char*)dssAlloc(&data_020fd24c, BANK_SIZE, 0x20);
    dss::memset(addr, 0xe5, BANK_SIZE);
    bool result = memorysave(BANK_OFFSET(bank), addr, 0x200);
    dssFree(&data_020fd24c, addr);
    return result;
}

THUMB bool profile::SaveLoad::verifybank(int bank)
{
    if (!isCardOK()) {
        return false;
    }
    Profile* padr = (Profile*)dssAlloc(&data_020fd24c, sizeof(Profile), 0x20);
    if (padr == NULL) {
        return false;
    }
    bool result = memoryload(BANK_OFFSET(bank), &padr->profiledata_, BANK_SIZE);
    if (padr->isValidData()) {
        result = padr->calcCheckSum();
    }
    dssFree(&data_020fd24c, padr);
    return result;
}

THUMB bool profile::SaveLoad::memorysave(unsigned int seek, void* buff, unsigned int size)
{
    int sleep = isSleepEnabled();
    setSleepEnabled(0);
    CARD_LockBackup(BACKUP_LOCK_ID);
    CARD_IdentifyBackup(CARD_BACKUP_TYPE_EEPROM_512KBITS);
    CARD_ReadWriteBackupAsync((u32)buff, (void*)seek, size, NULL, NULL, 0, 8, 10, 2);
    int result = CARD_GetResultCode();
    CARD_UnlockBackup(BACKUP_LOCK_ID);
    setSleepEnabled(sleep);
    if (result == 0) {
        return true;
    }
    return false;
}

THUMB void profile::SaveLoad::memorysaveAsync(unsigned int seek, void* buff, unsigned int size)
{
    lastSleep_ = isSleepEnabled();
    setSleepEnabled(0);
    CARD_LockBackup(BACKUP_LOCK_ID);
    CARD_IdentifyBackup(CARD_BACKUP_TYPE_EEPROM_512KBITS);
    CARD_ReadWriteBackupAsync((u32)buff, (void*)seek, size, NULL, NULL, 1, 8, 10, 2);
}

THUMB int profile::SaveLoad::memorysaveAsyncWait()
{
    return CARD_TryWaitBackupAsync();
}

THUMB bool profile::SaveLoad::memorysaveAsyncResult()
{
    int result = CARD_GetResultCode();
    CARD_UnlockBackup(BACKUP_LOCK_ID);
    setSleepEnabled(lastSleep_);
    if (result == 0) {
        return true;
    }
    return false;
}

THUMB bool profile::SaveLoad::memoryload(unsigned int seek, void* buff, unsigned int size)
{
    CARD_LockBackup(BACKUP_LOCK_ID);
    CARD_IdentifyBackup(CARD_BACKUP_TYPE_EEPROM_512KBITS);
    CARD_ReadWriteBackupAsync(seek, buff, size, NULL, NULL, 0, 6, 1, 0);
    int result = CARD_GetResultCode();
    CARD_UnlockBackup(BACKUP_LOCK_ID);
    if (result == 0) {
        return true;
    }
    return false;
}

THUMB void profile::SaveLoad::setCatalogMacro(CatalogView* view)
{
    char text[0x40];
    char time[0x40];
    int chapter = view->chapter_;
    unsigned int playTime = view->time_;
    int town = view->town_;
    int level = view->level_;
    TextAPI::setMACRO0(0x42, 0xf0000000, view->id_ + 1);
    TextAPI::setMACRO0(9, 0xd0000000, 0);
    TextAPI::setMACRO0(0x5f, 0xc0000000, town & 0x0fffffff);
    TextAPI::setMACRO0(0x5d, 0xf0000000, chapter);
    TextAPI::setMACRO0(0x18, 0xd0000000, 1);
    TextAPI::setMACRO0(0x5e, 0xf0000000, level);
    dss::sprintf_s(text, sizeof(text), "%4d:%02d", playTime / (60 * 60 * 60), playTime % (60 * 60 * 60) / (60 * 60));
    translateText(data_0209a0b8[0], data_0209a0b8[1], time, sizeof(time), text);
    TextAPI::setUserString(0, view->name_);
    TextAPI::setUserString(1, time);
}

THUMB int profile::SaveLoad::getPlaceNameNo(int chap, char* name)
{
    if (isThisMap(name, "cb")) {
        return 0xc00002bd;
    }
    if (isThisMap(name, "md")) {
        return 0xc00002be;
    }
    if (isThisMap(name, "sb")) {
        return 0xc00002bf;
    }
    if (isThisMap(name, "me")) {
        return 0xc00002c0;
    }
    if (isThisMap(name, "mg")) {
        return 0xc00002c1;
    }
    if (isThisMap(name, "mf")) {
        return 0xc00002c2;
    }
    if (isThisMap(name, "mh")) {
        return 0xc00002c3;
    }
    if (isThisMap(name, "cc")) {
        return 0xc00002c4;
    }
    if (isThisMap(name, "si")) {
        return 0xc00002c5;
    }
    if (isThisMap(name, "sj")) {
        return 0xc00002c6;
    }
    if (isThisMap(name, "cd")) {
        return 0xc00002c7;
    }
    if (isThisMap(name, "sk")) {
        return 0xc00002c8;
    }
    if (isThisMap(name, "mk")) {
        return 0xc00002c9;
    }
    if (isThisMap(name, "ma")) {
        return 0xc00002ca;
    }
    if (isThisMap(name, "mb")) {
        return 0xc00002cb;
    }
    if (isThisMap(name, "mc")) {
        return 0xc00002cc;
    }
    if (isThisMap(name, "ce")) {
        return 0xc00002cd;
    }
    if (isThisMap(name, "ml")) {
        return 0xc00002ce;
    }
    if (isThisMap(name, "dn")) {
        return 0xc00002cf;
    }
    if (isThisMap(name, "xd")) {
        return 0xc00002d0;
    }
    if (isThisMap(name, "cf")) {
        return 0xc00002d1;
    }
    if (isThisMap(name, "mi")) {
        return 0xc00002d2;
    }
    if (isThisMap(name, "mj")) {
        return 0xc00002d3;
    }
    if (isThisMap(name, "dk")) {
        return 0xc00002d4;
    }
    if (isThisMap(name, "se")) {
        return 0xc00002d5;
    }
    if (isThisMap(name, "sp")) {
        return 0xc00002d6;
    }
    if (isThisMap(name, "tb")) {
        return 0xc00002d7;
    }
    return 0;
}

THUMB int profile::SaveLoad::getPlaceNameByChapter(int chap)
{
    if (chap == 1) {
        return 0xc00002d8;
    }
    if (chap == 2) {
        return 0xc00002d9;
    }
    return 0xc00002c7;
}

THUMB bool profile::SaveLoad::isThisMap(char* now, char* name)
{
    if (now[0] != name[0]) {
        return false;
    }
    if (now[1] != name[1]) {
        return false;
    }
    return true;
}

THUMB bool profile::SaveLoad::isCardOK()
{
    unsigned char buff[0x200];
    return memoryload(0, buff, sizeof(buff));
}

THUMB int profile::SaveLoad::checkBackup()
{
    int result = 1;
    unsigned char buff[0x200];
    if (!memoryload(0, buff, sizeof(buff))) {
        return -3;
    }
    unsigned int* header = (unsigned int*)buff;
    if (header[0] != 0x2f355144 || header[1] != 0x45545241) {
        dss::memset(buff, 0, sizeof(buff));
        header[0] = 0x2f355144;
        header[1] = 0x45545241;
        if (!memorysave(0, buff, sizeof(buff))) {
            return -4;
        }
        if (!setSaveBank(0)) {
            return -4;
        }
        for (int i = 0; i < 4; i++) {
            if (!killbank(i)) {
                return -5;
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            if (!verifybank(i)) {
                result = -2;
                if (!killbank(i)) {
                    return -5;
                }
            }
        }
    }
    return result;
}

THUMB bool profile::SaveLoad::setSaveBank(int bank)
{
    unsigned char buff[0x200];
    dss::memset(buff, 0, sizeof(buff));
    BANKINFO* pC = (BANKINFO*)buff;
    pC->MAGIC = 0x2f355144;
    pC->TAG = 0x65766173;
    pC->BANK = bank;
    pC->CHECKSUM = bank + (pC->MAGIC + pC->TAG);
    return memorysave(0x200, buff, sizeof(buff));
}

THUMB int profile::SaveLoad::getSaveBank()
{
    unsigned char buff[0x200];
    if (!memoryload(0x200, buff, sizeof(buff))) {
        return -1;
    }
    BANKINFO* pC = (BANKINFO*)buff;
    unsigned int sum = pC->BANK + (pC->MAGIC + pC->TAG);
    if (pC->MAGIC != 0x2f355144 || pC->TAG != 0x65766173 || sum != pC->CHECKSUM) {
        pC->BANK = 0;
    }
    return pC->BANK;
}
