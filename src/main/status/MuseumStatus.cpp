#include "main/status/MuseumStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/leveldata/SurechigaiData.hpp"
#include "main/dss/DssUtils.hpp"
#include "ov019/materielmenu/meisanhin/MaterielMenuMeisanhinUtil.hpp"

inline dq5::level::MeisanhinData* dq5::level::MeisanhinData::getRecord(int index)
{
    return (MeisanhinData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline void status::TaishiBase::setTaishiFlag(bool flag) { isTaishi_ = flag; }
inline int status::TaishiBase::getTaishiFlag() { return isTaishi_; }
inline void status::TaishiBase::setTaishiUniqueId(unsigned int id) { uniqueId_ = id; }
inline unsigned int status::TaishiBase::getTaishiUniqueId() { return uniqueId_; }
inline void status::TaishiBase::setTaishiPrice(unsigned int price) { price_ = price; }
inline void status::TaishiBase::setTaishiObjectId(unsigned char object) { objectId_ = object; }
inline unsigned char status::TaishiBase::getTaishiObjectId() { return objectId_; }
inline void status::TaishiBase::setTaishiProduction(unsigned char production) { production_ = production; }
inline void status::MuseumItemStatus::setup(unsigned short mapid, unsigned short mapobjectid)
{
    mapid_ = mapid;
    mapobjectid_ = mapobjectid;
}
inline unsigned short status::MuseumItemStatus::getMapID() { return mapid_; }
inline unsigned short status::MuseumItemStatus::getMapObjectID() { return mapobjectid_; }
inline unsigned short status::MuseumItemStatus::getIconID() { return iconid_; }
inline void status::MuseumItemStatus::setIconID(unsigned short id) { iconid_ = id; }
inline dq5::level::MeisanhinData* status::MuseumItemStatus::getMeisanhinData() { return &meisan_; }
inline status::MuseumItemStatus& status::MuseumStatus::getMuseumItemStatus(int index) { return museumitem_[index]; }
inline unsigned short dq5::level::MeisanhinData::getItemid() { return itemid; }
inline char dq5::level::MeisanhinData::getPoint1() { return byte_2 & 0xf; }
inline char dq5::level::MeisanhinData::getPoint2() { return (byte_1 & 0x70) >> 4; }
inline unsigned char dq5::level::MeisanhinData::getPoint3() { return point3; }
inline unsigned char dq5::level::MeisanhinData::getPoint4() { return point4; }
inline unsigned char dq5::level::MeisanhinData::getPoint5() { return point5; }
inline unsigned char dq5::level::MeisanhinData::getPoint6() { return point6; }
inline char dq5::level::MeisanhinData::getLevel() { return (byte_1 & 0xc) >> 2; }
inline dq5::level::SurechigaiData* dq5::level::SurechigaiData::getRecord(int index) { return (SurechigaiData*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned short dq5::level::SurechigaiData::getCgicon() { return cgicon; }
inline char dq5::level::SurechigaiData::getLevel() { return (byte_1 & 0x1c) >> 2; }
inline char dq5::level::SurechigaiData::getType() { return byte_1 & 0x3; }

unsigned short status::museum_status_data[102] = {
    0x276, 0x37ab, 0x276, 0x37ac, 0x276, 0x37ad,
    0x276, 0x37ae, 0x276, 0x37af, 0x276, 0x37b0,
    0x276, 0x37b1, 0x276, 0x37b2, 0x276, 0x37b3,
    0x276, 0x37b4, 0x276, 0x37b5, 0x276, 0x37b6,
    0x279, 0x37e3, 0x279, 0x37e4, 0x279, 0x37e5,
    0x279, 0x37e6, 0x279, 0x37e7, 0x279, 0x37e8,
    0x279, 0x37e9, 0x279, 0x37ea, 0x27a, 0x37fe,
    0x27b, 0x380e, 0x27b, 0x380f, 0x27b, 0x3810,
    0x27b, 0x3811, 0x27b, 0x3812, 0x27c, 0x381f,
    0x27d, 0x3829, 0x27d, 0x382a, 0x27d, 0x382b,
    0x27d, 0x382c, 0x27d, 0x382d, 0x27d, 0x382e,
    0x27d, 0x382f, 0x27d, 0x3830, 0x27d, 0x3831,
    0x27d, 0x3832, 0x27d, 0x3833, 0x27d, 0x3834,
    0x27d, 0x3835, 0x27d, 0x3836, 0x27d, 0x3837,
    0x27d, 0x3838, 0x27d, 0x3839, 0x27d, 0x383a,
    0x27d, 0x383b, 0x27d, 0x383c, 0x27d, 0x383d,
    0x27d, 0x383e, 0x27d, 0x383f, 0x27d, 0x3840,
};

status::MuseumStatus status::g_MuseumStatus;

THUMB status::MuseumStatus::MuseumStatus()
{
}

THUMB status::MuseumStatus::~MuseumStatus()
{
}

THUMB void status::MuseumStatus::initialize()
{
    playerTaishi_.clearTaishi();
    for (int i = 0; i < OTHERS_TAISHI_MAX; i++) {
        othersTaishi_[i].clearTaishi();
    }
    unsigned short* pm = museum_status_data;
    for (int i = 0; i < MUSEUM_ITEM_MAX; i++) {
        unsigned short mid = *pm++;
        unsigned short pid = *pm++;
        museumitem_[i].setup(mid, pid);
        museumitem_[i].setIconID(0);
    }
    museumLevel_ = 0;
    museumPoint_ = 0;
    fearPoint_ = 0;
    funnyPoint_ = 0;
    beautifulPoint_ = 0;
    penaltyPoint_ = 0;
}

THUMB void status::MuseumStatus::deleteOthersTaishi(int index)
{
    othersTaishi_[index].clearTaishi();
    for (int i = 0; i < OTHERS_TAISHI_MAX - 1; i++) {
        if (othersTaishi_[i].getTaishiFlag() == false) {
            for (int j = i; j < OTHERS_TAISHI_MAX - 1; j++) {
                othersTaishi_[j] = othersTaishi_[j + 1];
            }
            othersTaishi_[OTHERS_TAISHI_MAX - 1].clearTaishi();
            break;
        }
    }
    updateTaishi();
}

THUMB int status::MuseumStatus::findExistTaishi(unsigned int uid)
{
    for (int i = 0; i < OTHERS_TAISHI_MAX; i++) {
        if (othersTaishi_[i].getTaishiFlag() == true && uid == othersTaishi_[i].getTaishiUniqueId()) {
            return i;
        }
    }
    return -1;
}

THUMB int status::MuseumStatus::getTaishiCount()
{
    int count = 0;
    for (int i = 0; i < OTHERS_TAISHI_MAX; i++) {
        if (othersTaishi_[i].getTaishiFlag() == true) {
            count++;
        }
    }
    return count;
}

THUMB int status::MuseumStatus::getBlankTaishiNo()
{
    for (int i = 0; i < OTHERS_TAISHI_MAX; i++) {
        if (othersTaishi_[i].getTaishiFlag() == false) {
            return i;
        }
    }
    return -1;
}

THUMB void status::MuseumStatus::saveTaishi()
{
    keepTaishi_ = playerTaishi_;
}

THUMB void status::MuseumStatus::recoveryTaishi()
{
    playerTaishi_ = keepTaishi_;
}

THUMB void status::MuseumStatus::resetSaveTaishi()
{
    keepTaishi_.clearTaishi();
}

THUMB int status::MuseumStatus::findMuseumItemStatus(int objid)
{
    for (int i = 0; i < MUSEUM_ITEM_MAX; i++) {
        if (objid == museumitem_[i].getMapObjectID()) {
            return i;
        }
    }
    return -1;
}

THUMB int status::MuseumStatus::findMuseumItemStatusForItemID(int itemID)
{
    for (int i = 0; i < 26; i++) {
        if (itemID == museumitem_[i].getIconID()) {
            return i;
        }
    }
    return -1;
}

THUMB int status::MuseumStatus::getMuseumLevel()
{
    if (museumLevel_ == 0) {
        updateMuseum();
    }
    return museumLevel_;
}

THUMB void status::MuseumStatus::updateTaishi()
{
    dq5::level::SurechigaiData::setup();
    {
        TaishiBase& tb = playerTaishi_;
        MuseumItemStatus& mi = museumitem_[26];
        dq5::level::SurechigaiData* sure = dq5::level::SurechigaiData::getRecord(tb.getTaishiObjectId());
        mi.setIconID(sure->getCgicon());
    }
    int i;
    TaishiBase* ptb;
    for (i = 0, ptb = othersTaishi_; i < OTHERS_TAISHI_MAX; i++, ptb++) {
        TaishiBase& tb = *ptb;
        dq5::level::SurechigaiData* sure = dq5::level::SurechigaiData::getRecord(tb.getTaishiObjectId());
        MuseumItemStatus& mi = getMuseumItemStatus(i + 27);
        mi.setIconID(sure->getCgicon());
    }
    dq5::level::SurechigaiData::cleanup();
}

THUMB void status::MuseumStatus::updateMuseum()
{
    updateTaishi();
    updateLevel();
}

THUMB void status::MuseumStatus::updateLevel()
{
    dq5::level::MeisanhinData::setup();
    for (int i = 0; i < MUSEUM_ITEM_MAX; i++) {
        dq5::level::MeisanhinData* pd = museumitem_[i].getMeisanhinData();
        dq5::level::MeisanhinData* ps = __findMeisanhinData(museumitem_[i].getIconID());
        dss::memcpy(pd, ps, sizeof(dq5::level::MeisanhinData));
    }
    computeLevel();
    dq5::level::MeisanhinData::cleanup();
}

THUMB dq5::level::MeisanhinData* status::MuseumStatus::__findMeisanhinData(int no)
{
    dq5::level::MeisanhinData* meisan = dq5::level::MeisanhinData::getRecord(0);
    unsigned int max = dq5::level::MeisanhinData::binary_.record_;
    for (int i = 1; i < max; i++) {
        dq5::level::MeisanhinData* pm = &meisan[i];
        if (no == pm->getItemid()) {
            return pm;
        }
    }
    return meisan;
}

THUMB void status::MuseumStatus::computeLevel()
{
    museumLevel_ = 0;
    museumPoint_ = 0;
    fearPoint_ = 0;
    funnyPoint_ = 0;
    beautifulPoint_ = 0;
    penaltyPoint_ = 0;
    MuseumItemStatus* pi = museumitem_;
    char itemnum[264];
    for (int i = 0; i < 264; i++) {
        itemnum[i] = 0;
    }
    for (int i = 0; i < MUSEUM_ITEM_MAX; i++, pi++) {
        int lv;
        dq5::level::MeisanhinData* pd = &pi->meisan_;
        switch (pi->getMapID()) {
        case MUSEUMFLOOR_F1:
            lv = 1;
            break;
        case MUSEUMFLOOR_F2:
            lv = 2;
            break;
        case MUSEUMFLOOR_F3:
            lv = 3;
            break;
        default:
            lv = -1;
            break;
        }
        if (pi->getIconID() == 0) {
            lv = -1;
        }
        if (lv != -1) {
            int no = pi->getIconID();
            if (itemnum[no] == 0) {
                museumPoint_ += pd->getPoint1();
            } else {
                museumPoint_ += pd->getPoint2();
            }
            museumPoint_ += pd->getPoint3();
            int pn = pd->getLevel() - lv;
            if (pn > 0) {
                pn = 0;
            }
            penaltyPoint_ += pn;
            beautifulPoint_ += pd->getPoint4();
            funnyPoint_ += pd->getPoint5();
            fearPoint_ += pd->getPoint6();
            itemnum[no]++;
        }
    }
    museumPoint_ += penaltyPoint_;
    if (museumPoint_ >= 400) {
        museumLevel_ = 5;
    }
    if (museumPoint_ >= 350 && museumPoint_ <= 399) {
        museumLevel_ = 4;
    }
    if (museumPoint_ >= 220 && museumPoint_ <= 349) {
        museumLevel_ = 3;
    }
    if (museumPoint_ >= 80 && museumPoint_ <= 219) {
        museumLevel_ = 2;
    }
    if (museumPoint_ <= 79) {
        museumLevel_ = 1;
    }
    resetingTaishiFlag();
}

THUMB status::MUSEUMTREND status::MuseumStatus::getMuseumTrend()
{
    if (fearPoint_ >= funnyPoint_ && fearPoint_ >= beautifulPoint_) {
        return MUSEUMTREND_FEAR;
    }
    if (funnyPoint_ >= fearPoint_ && funnyPoint_ >= beautifulPoint_) {
        return MUSEUMTREND_FUNNY;
    }
    return MUSEUMTREND_BEAUTIFUL;
}

THUMB int status::MuseumStatus::setIconByMapObjectID(int mid, int item)
{
    int mno = findMuseumItemStatus(mid);
    if (mno == -1) {
        return -1;
    }
    MuseumItemStatus& mi = museumitem_[mno];
    int old = mi.getIconID();
    mi.setIconIDandRedraw(item);
    return old;
}

THUMB void status::MuseumStatus::setSuccessTaishi(TAISHI_DATA* taishiData, bool successFlag)
{
    successConnect_ = successFlag;
    if (taishiData != NULL) {
        dss::memcpy(&successTaishi_, taishiData, sizeof(TAISHI_DATA));
        int bank = findExistTaishi(successTaishi_.uniqueId_);
        if (bank == -1) {
            bank = getBlankTaishiNo();
            if (bank == -1) {
                return;
            }
        }
        TaishiBase* pt = &othersTaishi_[bank];
        pt->setTaishiFlag(true);
        pt->setTaishiUniqueId(successTaishi_.uniqueId_);
        pt->setTaishiPrice(successTaishi_.price_);
        pt->setTaishiObjectId(successTaishi_.objectId_);
        pt->setTaishiProduction(successTaishi_.production_);
        pt->setTaishiName(successTaishi_.taishiName_);
        pt->setTaishiProducer(successTaishi_.producer_);
        pt->setTaishiMessage(successTaishi_.message_);
        selectTaishiFlag_[successTaishi_.objectId_ - 1] = 1;
    }
}

THUMB int status::MuseumStatus::getFloorItemCount(MUSEUMFLOOR floor)
{
    int ret = 0;
    MuseumItemStatus* pi = museumitem_;
    for (int i = 0; i < MUSEUM_ITEM_MAX; i++, pi++) {
        if (floor == pi->getMapID() && pi->getIconID() != 0) {
            ret++;
        }
    }
    return ret;
}

THUMB int status::MuseumStatus::getFloorItemCount(MUSEUMFLOOR floor, int item)
{
    int ret = 0;
    MuseumItemStatus* pi = museumitem_;
    for (int i = 0; i < MUSEUM_ITEM_MAX; i++, pi++) {
        if (floor == pi->getMapID() && item == pi->getIconID()) {
            ret++;
        }
    }
    return ret;
}

THUMB bool status::MuseumStatus::isFloorItemSame(int item)
{
    if (getFloorItemCount(MUSEUMFLOOR_F1, item) != 12) {
        return false;
    }
    if (getFloorItemCount(MUSEUMFLOOR_F2, item) != 8) {
        return false;
    }
    if (getFloorItemCount(MUSEUMFLOOR_F3, item) == 1) {
        return true;
    }
    return false;
}

THUMB void status::MuseumStatus::resetingTaishiFlag()
{
    dq5::level::SurechigaiData::setup();
    for (int i = 1; i < SELECT_TAISHI_MAX; i++) {
        if (selectTaishiFlag_[i - 1] == true) {
            continue;
        }
        dq5::level::SurechigaiData* data = dq5::level::SurechigaiData::getRecord(i);
        if (data->getLevel() > museumLevel_) {
            continue;
        }
        switch (data->getType()) {
        case 0:
            selectTaishiFlag_[i - 1] = true;
            break;
        case 1:
        case 2:
            if (g_AreaFlag.check(getMeisanhinFlagNo(data->itemid)) == true) {
                selectTaishiFlag_[i - 1] = true;
            }
            break;
        case 3:
            break;
        }
    }
    dq5::level::SurechigaiData::cleanup();
}
