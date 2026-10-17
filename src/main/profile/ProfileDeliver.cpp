#include "main/profile/Profile.hpp"
#include "main/global/Global.hpp"
#include "main/btl/Encount.hpp"
#include "main/cmn/CommonCounterInfo.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/sound/Sound.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/GameStatus.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/status/OptionStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StatusChange.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/TouchData.hpp"

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline void btl::Encount::setEnable(int flag) { enable_ = flag; }
inline void status::BattleResult::setMonsterCount(int index, unsigned short count) { result_[index].monsterCount_ = count; }
inline void status::BattleResult::setMonsterItemCount(int index, unsigned short count) { result_[index].itemCount_ = count; }
inline void status::BattleResult::setMonsterLevel(int index, unsigned char level) { result_[index].level_ = level; }
inline void status::StoryStatus::setFlagValue(unsigned int val) { flag_.flag_ = val; }
inline void status::StoryStatus::setHeroEquip(int index, short itemID) { heroEquip_[index] = itemID; }
inline void status::StageAttribute::setTimestopFlag(int flag) { timestop_ = flag; }
inline status::TOUCH_RANKING_DATA& status::TouchData::getRanking(int index) { return ranking_[index]; }
inline status::PlayerData& status::PlayerDataAll::getPlayerData(int index) { return playerData_[index]; }
inline void status::PlayerDataAll::setPlayerNameIndex(int index, unsigned char val) { nameIndex_[index] = val; }
inline void status::PlayerDataAll::setPlayerFlagValue(int index, unsigned char val) { playerFlag_[index].flag_ = val; }
inline void status::PlayerData::setCursedName(int val) { cursedName_ = val; }
inline void status::PlayerData::setCommand(unsigned char val) { command_ = val; }
inline void status::PlayerData::setFlagValue(unsigned char val) { flag_.flag_ = val; }
inline void status::PlayerData::setExp(int exp) { baseStatus_.exp_ = exp; }
inline void status::PlayerData::setLevel(unsigned char lvl) { baseStatus_.level_ = lvl; }
inline void status::MuseumStatus::setSelectTaishiFlag(int index, int flag) { selectTaishiFlag_[index] = flag; }
inline status::MuseumItemStatus& status::MuseumStatus::getMuseumItemStatus(int index) { return museumitem_[index]; }
inline void status::MuseumItemStatus::setIconID(unsigned short id) { iconid_ = id; }
inline void cmn::CommonCounterInfo::setCounter(int index, unsigned char counter) { dayCounter_[index] = counter; }
inline void status::PartyStatusData::setPlayerStatusFlagValue(int idx, unsigned int val) { playerStatusFlag_[idx].flag_ = val; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline void status::BasePartyStatus::setCarriage(int flag) { carriage_ = flag; }
inline void status::HaveItemSack::setCursedName(int flag) { cursedName_ = flag; }
inline void cmn::CommonPartyInfo::setRideOn(PARTY_RIDE_ON_TYPE type) { rideOnType_ = type; }
inline void cmn::CommonPartyInfo::setShipNo(int shipNo) { shipNo_ = shipNo; }
inline void status::StageInfo::setProfileBank(int val) { profileBank_ = val; }
inline void status::StageInfo::setProfileType(int val) { profileType_ = val; }
inline void status::StageInfo::setLoadFlag(bool flag) { load_ = flag; }
inline dss::Fix32Vector3& status::StageInfo::getShipPosition(int index) { return shipPosition_[index]; }
inline dss::Fix32Vector3& status::StageInfo::getFirmamentPosition() { return firmamentPosition_; }
inline dss::Fix32Vector3& status::StageInfo::getOverviewPosition() { return overviewPosition_; }
inline dss::Fix32Vector3& status::StageInfo::getOverviewTempPosition() { return overviewTempPosition_; }
inline void status::StageInfo::setReturnChurch(int church) { returnChurchData_ = church; }
inline void status::StageInfo::setLoadChurch(int church) { loadChurchData_ = church; }
inline void status::StageInfo::setSymbolID(int sy) { symbolID_ = sy; }
inline void status::StageInfo::setRiremitMapId(int id) { riremitMap_ = id; }
inline void status::StageInfo::setRanaMapSurfaceId(int id) { lastFldSurface_ = id; }
inline void status::StageInfo::setKimeraSymbol(int id) { kimeraSymbol_ = id; }
inline void status::StageInfo::setFieldChange(int ch) { fieldChangeIndex_ = ch; }

THUMB bool profile::Profile::deliverProfile(int no)
{
    if (!isValidData()) {
        return false;
    }
    if (!calcCheckSum()) {
        return false;
    }
    g_Global.initialize();
    status::g_Party.clear();
    Sound::unkfunc_0206889c(15);
    deliver_PROFILE_SYSTEM();
    deliver_PROFILE_PARTY();
    deliver_PROFILE_ASSETS();
    deliver_PROFILE_PLAYER();
    deliver_PROFILE_LOCATION();
    unkfunc_0204058c();
    deliver_PROFILE_MONSTER();
    {
        status::PartyStatusData& partystatusdata = status::g_Party.partyStatusData_;
        for (int i = 0; i < 10; i++) {
            if (pASSETS->ALL_MEMBER[i] != 0) {
                partystatusdata.setPlayerStatus(i, pASSETS->ALL_MEMBER[i]);
            }
        }
        for (int i = 0; i < 10; i++) {
            if (pASSETS->ALL_MEMBER[i] != 0) {
                partystatusdata.setPlayerStatusFlagValue(i, pASSETS->ALL_MEMBER_FLAG[i]);
            }
        }
        for (int i = 0; i < 4; i++) {
            partystatusdata.setOutsideOrder(i, pASSETS->OUTSIDE_MEMBER[i]);
        }
        for (int i = 0; i < 7; i++) {
            partystatusdata.setInsideOrder(i, pASSETS->INSIDE_MEMBER[i]);
        }
        for (int i = 0; i < 2; i++) {
            if (pASSETS->BACKSIDE_MEMBER[i] != -1) {
                unsigned short charaIndex = pASSETS->BACKSIDE_MEMBER_CHARINDEX[i];
                status::PlayerStatus& player = partystatusdata.getPlayerStatusForCtrl(pASSETS->BACKSIDE_MEMBER[i]);
                player.getHaveStatusInfo().getHaveStatus().setCharaIndex(charaIndex);
            }
        }
    }
    cmn::PartyTalk::getSingleton().initialize();
    status::g_MuseumStatus.updateMuseum();
    dss::Fix32Vector3 pos;
    pos.vx.value = pLOCATION->PARTY_X;
    pos.vy.value = pLOCATION->PARTY_Y;
    pos.vz.value = pLOCATION->PARTY_Z;
    short dir = pLOCATION->PARTY_D;
    deliverRESTART_MAP(pos, dir);
    return true;
}

THUMB void profile::Profile::deliver_PROFILE_MONSTER()
{
    PROFILE_MONSTER* pm = pMONSTER;
    for (int i = 0; i < 202; i++) {
        status::g_BattleResult.setMonsterCount(i, pm->KILL);
        status::g_BattleResult.setMonsterItemCount(i, pm->ITEMCOUNT);
        status::g_BattleResult.setMonsterLevel(i, pm->LEVEL);
        status::g_BattleResult.setMonsterEncount(i, pm->ENCOUNT);
        pm++;
    }
}

THUMB void profile::Profile::unkfunc_0204058c()
{
    UnkProfileTaishi* pt = pTAISHI;
    status::TaishiBase* tb = status::g_MuseumStatus.othersTaishi_;
    for (int i = 0; i < status::MuseumStatus::OTHERS_TAISHI_MAX; i++) {
        if (pt->IS_TAISHI) {
            tb->isTaishi_ = pt->IS_TAISHI;
            tb->uniqueId_ = pt->UNIQUEID;
            tb->price_ = pt->PRICE;
            tb->objectId_ = pt->OBJECTID;
            tb->production_ = pt->PRODUCTION;
            dss::memcpy(tb->taishiName_, pt->NAME, sizeof(pt->NAME));
            dss::memcpy(tb->producer_, pt->PRODUCER, sizeof(pt->PRODUCER));
            dss::memcpy(tb->message_, pt->MESSAGE, sizeof(pt->MESSAGE));
        }
        pt++;
        tb++;
    }
    tb = &status::g_MuseumStatus.playerTaishi_;
    if (pt->IS_TAISHI) {
        tb->isTaishi_ = pt->IS_TAISHI;
        tb->uniqueId_ = pt->UNIQUEID;
        tb->price_ = pt->PRICE;
        tb->objectId_ = pt->OBJECTID;
        tb->production_ = pt->PRODUCTION;
        dss::memcpy(tb->taishiName_, pt->NAME, sizeof(pt->NAME));
        dss::memcpy(tb->producer_, pt->PRODUCER, sizeof(pt->PRODUCER));
        dss::memcpy(tb->message_, pt->MESSAGE, sizeof(pt->MESSAGE));
    }
}

THUMB void profile::Profile::deliverRESTART_MAP(dss::Fix32Vector3& pos, short dir)
{
    if (pSYSTEM->SAVETYPE == SAVETYPE_CHURCH) {
        status::g_StageInfo.loadChurch();
        status::g_StageInfo.setLoadFlag(true);
        return;
    }
    if (pSYSTEM->SAVETYPE == SAVETYPE_INTERVAL && pSYSTEM->CLEAR) {
        status::g_StageInfo.loadChurch();
        status::g_StageInfo.setLoadFlag(true);
        return;
    }
    if (dss::strcmp((char*)pLOCATION->RESTART, "field") == 0) {
        cmn::g_extraMapLink.setExtraLinkFieldAbsPos(pLOCATION->FIELDTYPE, pos, 4);
        return;
    }
    int mapid = g_Global.getMapNameIdByName((char*)pLOCATION->RESTART);
    cmn::g_extraMapLink.setExtraLinkTown(mapid, pos, dir);
}

THUMB void profile::Profile::deliver_PROFILE_SYSTEM()
{
    status::g_StageInfo.setProfileBank(pSYSTEM->BOOKNO);
    status::g_StageInfo.setProfileType(pSYSTEM->SAVETYPE);
    status::g_Game.setUniqueID(pSYSTEM->UNIQUEID);
}

THUMB void profile::Profile::deliver_PROFILE_PARTY()
{
    g_Option.setSackSort(pPARTY->OPTION_SACK_SORT);
    g_Option.setBgmVolume(pPARTY->OPTION_BGM_VOLUME);
    g_Option.setSeVolume(pPARTY->OPTION_SEVOLUME);
    g_Option.setBattleSpeed(pPARTY->OPTION_BATTLE_SPEED);
    deliverGameFlag(&g_AreaFlag, pPARTY->GLOBALFLAG);
    deliverGameFlag(&g_LocalFlag, pPARTY->AREAFLAG);
    status::g_Story.setFlagValue(pPARTY->STORY_FLAG);
    status::g_Story.setChapter((dq5::CHAPTER_NO)pPARTY->STORY_CHAPTER_NO);
    for (int i = 0; i < 9; i++) {
        status::g_Story.setHeroEquip(i, pPARTY->STORY_HEROEQUIP[i]);
    }
    status::g_Game.setPlayTime(pPARTY->PLAY_TIME);
    status::g_StageInfo.setTimeZone((TIME_ZONE)pPARTY->TIME_ZONE);
    status::g_StageInfo.setWorldTime(pPARTY->WORLD_TIME);
    status::g_StageAttribute.setTimestopFlag(pPARTY->TIME_STOP);
    status::g_StageInfo.deliverMapFlag((SAVETYPE)pSYSTEM->SAVETYPE, pPARTY);
    for (int i = 0; i < 10; i++) {
        status::TOUCH_RANKING_DATA& tr = status::g_TouchData.getRanking(i);
        tr.score = pPARTY->TOUCH_SCORE[i];
        tr.stage = pPARTY->TOUCH_STAGE[i];
    }
    status::StatusChange::setToherosInfo(pPARTY->INFO_TOHEROS);
    status::StatusChange::setSinobiasiInfo(pPARTY->INFO_SINOBIASI);
    status::StatusChange::setMonstersFoodInfo(pPARTY->INFO_MONSTERSFOOD);
    status::StageAttribute::setToramana(pPARTY->ATTR_TORAMANA);
    btl::Encount::getSingleton()->setEnable(pPARTY->NO_ENCOUNT_FLAG);
    for (int i = 0; i < 88; i++) {
        status::PlayerDataAll::setPlayerNameIndex(i, pPARTY->NAME_INDEX[i]);
    }
    for (int i = 0; i < 64; i++) {
        status::g_MuseumStatus.setSelectTaishiFlag(i, pPARTY->SELECTTAISHI_FLAG[i]);
    }
    {
        int num1 = 8;
        for (int i = 0; i < num1; i++) {
            cmn::g_CommonCounterInfo.setCounter(i, pPARTY->DAY_COUNTER[i]);
        }
    }
}

THUMB void profile::Profile::deliver_PROFILE_ASSETS()
{
    {
        status::HaveItemSack& hisack = status::g_Party.haveItemSack_;
        status::g_Party.setGold(pASSETS->HAVING_GOLD);
        status::g_Party.setBankMoney(pASSETS->BANK_GOLD);
        status::g_Party.setCasinoCoin(pASSETS->CASINO_TOKEN);
        status::g_Party.setMedalCoin(pASSETS->KINGS_MEDAL);
        status::g_Party.setCarriage(pASSETS->BASHA);
        hisack.clear();
        for (int i = 0; i < 263; i++) {
            hisack.add(pASSETS->SACKITEM[i], pASSETS->SACKCOUNT[i]);
        }
    }
    {
        status::PartyStatusData& partystatusdata = status::g_Party.partyStatusData_;
        for (int i = 0; i < 4; i++) {
            partystatusdata.setOutsideOrder(i, -1);
        }
        for (int i = 0; i < 7; i++) {
            partystatusdata.setInsideOrder(i, -1);
        }
        for (int i = 0; i < 2; i++) {
            partystatusdata.setBacksideOrder(i, -1);
        }
    }
    for (int i = 0; i < 26; i++) {
        status::MuseumItemStatus& mr = status::g_MuseumStatus.getMuseumItemStatus(i);
        mr.setIconID(pASSETS->MEISAN[i]);
    }
    {
        status::HaveItemSack& hisack = status::g_Party.haveItemSack_;
        hisack.setNameString((char*)pASSETS->SACKNAME);
        hisack.setCursedName(pASSETS->CURSED_SACKNAME);
    }
}

THUMB void profile::Profile::deliver_PROFILE_PLAYER()
{
    PROFILE_PLAYER* pP = pPLAYER;
    for (int i = 0; i < 97; i++, pP++) {
        if (pP->PDA_INDEX == 0) {
            continue;
        }
        status::PlayerData& playerdata = status::PlayerDataAll::getPlayerData(pP->PDA_INDEX);
        status::PlayerDataAll::setPlayerFlagValue(pP->PDA_INDEX, pP->PDA_FLAG);
        status::HaveItem& haveitem = playerdata.haveItem_;
        bool name;
        switch (pP->PDA_INDEX) {
        case 0:
            name = true;
            break;
        case 1:
            name = true;
            break;
        case 2:
            name = false;
            break;
        case 3:
            name = false;
            break;
        case 4:
            name = false;
            break;
        case 5:
            name = false;
            break;
        case 6:
            name = false;
            break;
        case 7:
            name = false;
            break;
        case 8:
            name = false;
            break;
        case 9:
            name = false;
            break;
        case 10:
            name = false;
            break;
        case 11:
            name = false;
            break;
        case 12:
            name = false;
            break;
        case 13:
            name = true;
            break;
        case 14:
            name = true;
            break;
        case 15:
            name = false;
            break;
        case 16:
            name = true;
            break;
        case 19:
            name = true;
            break;
        default:
            name = true;
            break;
        }
        if (name) {
            playerdata.setNameString((char*)pP->NAME);
        }
        playerdata.nameBasedSex_ = (pP->CURSED_NAME & 0x80) == 0 ? (Sex)0 : (Sex)1;
        playerdata.setCursedName(pP->CURSED_NAME & 0x7f);
        playerdata.setCommand(pP->TACTICS);
        playerdata.setFlagValue(pP->STATFLAG);
        playerdata.setExp(pP->EXP);
        playerdata.baseStatus_.setStrength(pP->STRENGTH);
        playerdata.baseStatus_.setProtection(pP->PROTECTION);
        playerdata.baseStatus_.setHp(pP->HP);
        playerdata.baseStatus_.setHpMax(pP->HPMAX);
        playerdata.baseStatus_.setMp(pP->MP);
        playerdata.baseStatus_.setMpMax(pP->MPMAX);
        playerdata.baseStatus_.setAgility(pP->AGILITY);
        playerdata.baseStatus_.setWisdom(pP->WISDAM);
        playerdata.baseStatus_.setLuck(pP->LUCK);
        playerdata.setLevel(pP->LEVEL);
        haveitem.clear();
        for (int j = 0; j < 12; j++) {
            int item = pP->HAVEITEM[j];
            status::ItemData& itemdata = haveitem.itemArray_[j];
            itemdata.index_ = item & 0x7fff;
            itemdata.count_ = 1;
            if (item & 0x8000) {
                itemdata.setEquipment(true);
            }
        }
        switch (pP->INDEX) {
        case 2:
        case 5:
        case 8:
        case 15:
            break;
        default:
            playerdata.haveAction_.loadLevelup(pP->LEVEL, pPARTY->RULA_LEVEL, pPARTY->PARUPUNTE_LEVEL);
            break;
        }
    }
}

THUMB void profile::Profile::deliver_PROFILE_LOCATION()
{
    cmn::g_cmnPartyInfo.setRideOn((cmn::PARTY_RIDE_ON_TYPE)pLOCATION->RIDEON_TYPE);
    cmn::g_cmnPartyInfo.setShipNo(pLOCATION->SHIP_NO);
    {
        dss::Fix32Vector3 pos;
        int id = pLOCATION->SHIP_ID;
        pos.vx.value = pLOCATION->SHIP_X;
        pos.vy.value = pLOCATION->SHIP_Y;
        pos.vz.value = pLOCATION->SHIP_Z;
        short idx = pLOCATION->SHIP_D;
        cmn::g_cmnPartyInfo.setShipInfo(id, pos, idx);
    }
    {
        dss::Fix32Vector3 pos;
        pos.vx.value = pLOCATION->RAFT_X;
        pos.vy.value = pLOCATION->RAFT_Y;
        pos.vz.value = pLOCATION->RAFT_Z;
        int id = pLOCATION->RAFT_ID;
        cmn::g_cmnPartyInfo.setIkadaInfo(id, pos);
    }
    {
        dss::Fix32Vector3& pos0 = status::g_StageInfo.getShipPosition(0);
        dss::Fix32Vector3& pos1 = status::g_StageInfo.getShipPosition(1);
        dss::Fix32Vector3& pos2 = status::g_StageInfo.getFirmamentPosition();
        dss::Fix32Vector3& pos3 = status::g_StageInfo.getOverviewPosition();
        dss::Fix32Vector3& pos4 = status::g_StageInfo.getOverviewTempPosition();
        deliverFx32Vector3(&pos0, pLOCATION->STAGE_INFO_LOCATION_SHIP1);
        deliverFx32Vector3(&pos1, pLOCATION->STAGE_INFO_LOCATION_SHIP2);
        deliverFx32Vector3(&pos2, pLOCATION->STAGE_INFO_LOCATION_TENKUUJYO);
        deliverFx32Vector3(&pos3, pLOCATION->STAGE_INFO_LOCATION_MINIMAP1);
        deliverFx32Vector3(&pos4, pLOCATION->STAGE_INFO_LOCATION_MINIMAP2);
    }
    status::g_StageInfo.setReturnChurch(pLOCATION->RETURN_CHURCH);
    status::g_StageInfo.setLoadChurch(pLOCATION->LOAD_CHURCH);
    for (int i = 0; i < 9; i++) {
        status::g_StageInfo.setPuzzleSection(i % 3, i / 3, pLOCATION->PLATE_MOVE[i]);
    }
    status::g_StageInfo.setSymbolID(pLOCATION->RIREMITO_SYMBOL_ID);
    status::g_StageInfo.setRiremitMapId(pLOCATION->RIREMITO_MAP);
    status::g_StageInfo.setRanaMapSurfaceId(pLOCATION->LAST_FIELD_LINK_SURFACE);
    status::g_StageInfo.setRanaMapNameId(pLOCATION->LAST_RANARUTA_STAGE_ID);
    status::g_StageInfo.setKimeraSymbol(pLOCATION->KIMERA_SYMBOL);
    status::g_StageInfo.setFieldChange(pLOCATION->FIELD_CHANGE);
    status::g_StageInfo.switchDataFlag_ = pLOCATION->TROKKO_SWITCHDATA;
    status::g_StageInfo.switchInitFlag_ = pLOCATION->TROKKO_SWITCHINIT;
    status::g_StageInfo.wagonData1Flag_ = pLOCATION->TROKKO_WAGON1DATA;
    status::g_StageInfo.wagonData2Flag_ = pLOCATION->TROKKO_WAGON2DATA;
    status::g_StageInfo.loadAfterTruckDataSetup();
}
