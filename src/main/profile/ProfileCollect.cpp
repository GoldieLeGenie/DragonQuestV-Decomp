#include "main/profile/Profile.hpp"
#include "main/global/Global.hpp"
#include "main/btl/Encount.hpp"
#include "main/cmn/CommonCounterInfo.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/dss/UnkTextConvert.hpp"
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
#include "string.h"

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}


inline unsigned short status::BattleResult::getMonsterCount(int index) { return result_[index].monsterCount_; }
inline unsigned short status::BattleResult::getMonsterItemCount(int index) { return result_[index].itemCount_; }
inline unsigned char status::BattleResult::getMonsterLevel(int index) { return result_[index].level_; }
inline int status::TaishiBase::getTaishiFlag() { return isTaishi_; }
inline unsigned int status::StoryStatus::getFlagValue() { return flag_.flag_; }
inline short status::StoryStatus::getHeroEquip(int index) { return heroEquip_[index]; }
inline int status::StageAttribute::getTimestopFlag() { return timestop_; }
inline status::TOUCH_RANKING_DATA& status::TouchData::getRanking(int index) { return ranking_[index]; }
inline status::PlayerData& status::PlayerDataAll::getPlayerData(int index) { return playerData_[index]; }
inline unsigned char status::PlayerDataAll::getPlayerNameIndex(int index) { return nameIndex_[index]; }
inline int status::MuseumStatus::getSelectTaishiFlag(int index) { return selectTaishiFlag_[index]; }
inline unsigned char cmn::CommonCounterInfo::getCounter(int index) { return dayCounter_[index]; }
inline unsigned int status::PartyStatusData::getPlayerStatusFlagValue(int idx) { return playerStatusFlag_[idx].flag_; }
inline short status::PlayerStatus::getIndex() { return index_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline unsigned short status::MuseumItemStatus::getIconID() { return iconid_; }
inline status::MuseumItemStatus& status::MuseumStatus::getMuseumItemStatus(int index) { return museumitem_[index]; }
inline int status::HaveItemSack::getCursedName() { return cursedName_; }
inline cmn::PARTY_RIDE_ON_TYPE cmn::CommonPartyInfo::getRideOn() { return rideOnType_; }
inline int cmn::CommonPartyInfo::getShipNo() { return shipNo_; }
inline int status::StageInfo::getProfileBank() { return profileBank_; }
inline void status::StageInfo::setProfileBank(int val) { profileBank_ = val; }
inline dss::Fix32Vector3& status::StageInfo::getShipPosition(int index) { return shipPosition_[index]; }
inline dss::Fix32Vector3& status::StageInfo::getFirmamentPosition() { return firmamentPosition_; }
inline dss::Fix32Vector3& status::StageInfo::getOverviewPosition() { return overviewPosition_; }
inline dss::Fix32Vector3& status::StageInfo::getOverviewTempPosition() { return overviewTempPosition_; }
inline int status::StageInfo::getReturnChurch() { return returnChurchData_; }
inline int status::StageInfo::getLoadChurch() { return loadChurchData_; }
inline int status::StageInfo::getSymbolID() { return symbolID_; }
inline int status::StageInfo::getRiremitMapId() { return riremitMap_; }
inline int status::StageInfo::getRanaMapSurfaceId() { return lastFldSurface_; }
inline int status::StageInfo::getRanaMapNameId() { return lastRanaStageNameId_; }
inline int status::StageInfo::getkimeraSymbol() { return kimeraSymbol_; }
inline int status::StageInfo::getFieldChange() { return fieldChangeIndex_; }

THUMB bool profile::Profile::collectProfile(int no, int type)
{
    g_Global.checkSave1();
    collect_PROFILE_SYSTEM(no, type);
    collect_PROFILE_PARTY();
    collect_PROFILE_ASSETS();
    collect_PROFILE_PLAYER();
    collect_PROFILE_LOCATION();
    unkfunc_0203fb84();
    collect_PROFILE_MONSTER();
    if (type != SAVETYPE_NEW && g_Global.checkSave2()) {
        dss::strcpy_s((char*)pLOCATION->RESTART, 16, "cdf3b");
        pSYSTEM->SAVETYPE = SAVETYPE_NEW;
    }
    if (type == SAVETYPE_NEW) {
        dss::strcpy_s((char*)pLOCATION->RESTART, 16, "cdf3b");
    }
    calcCheckSum();
    return true;
}

THUMB void profile::Profile::collect_PROFILE_MONSTER()
{
    PROFILE_MONSTER* pm = pMONSTER;
    for (int i = 0; i < 202; i++) {
        pm->KILL = status::g_BattleResult.getMonsterCount(i);
        pm->ITEMCOUNT = status::g_BattleResult.getMonsterItemCount(i);
        pm->LEVEL = status::g_BattleResult.getMonsterLevel(i);
        pm->ENCOUNT = status::g_BattleResult.isMonsterEncount(i);
        pm++;
    }
}

THUMB void profile::Profile::unkfunc_0203fb84()
{
    UnkProfileTaishi* pt = pTAISHI;
    status::TaishiBase* tb = status::g_MuseumStatus.othersTaishi_;
    for (int i = 0; i < status::MuseumStatus::OTHERS_TAISHI_MAX; i++) {
        dss::memset(pt, 0, sizeof(UnkProfileTaishi));
        if (tb->getTaishiFlag()) {
            pt->IS_TAISHI = tb->getTaishiFlag();
            pt->UNIQUEID = tb->uniqueId_;
            pt->PRICE = tb->price_;
            pt->OBJECTID = tb->objectId_;
            pt->PRODUCTION = tb->production_;
            dss::memcpy(pt->NAME, tb->taishiName_, sizeof(pt->NAME));
            dss::memcpy(pt->PRODUCER, tb->producer_, sizeof(pt->PRODUCER));
            dss::memcpy(pt->MESSAGE, tb->message_, sizeof(pt->MESSAGE));
        }
        pt++;
        tb++;
    }
    tb = &status::g_MuseumStatus.playerTaishi_;
    dss::memset(pt, 0, sizeof(UnkProfileTaishi));
    if (tb->getTaishiFlag()) {
        pt->IS_TAISHI = tb->getTaishiFlag();
        pt->UNIQUEID = tb->uniqueId_;
        pt->PRICE = tb->price_;
        pt->OBJECTID = tb->objectId_;
        pt->PRODUCTION = tb->production_;
        dss::memcpy(pt->NAME, tb->taishiName_, sizeof(pt->NAME));
        dss::memcpy(pt->PRODUCER, tb->producer_, sizeof(pt->PRODUCER));
        dss::memcpy(pt->MESSAGE, tb->message_, sizeof(pt->MESSAGE));
    }
}

THUMB void profile::Profile::collect_PROFILE_SYSTEM(int no, int type)
{
    pSYSTEM->MAGIC = 0x65747261;
    pSYSTEM->VER = 200804302;
    pSYSTEM->CHECKSUM = 0;
    pSYSTEM->UNIQUEID = status::g_Game.getUniqueID();
    if (no != 3) {
        status::g_StageInfo.setProfileBank(no);
        pSYSTEM->BOOKNO = no;
    } else {
        pSYSTEM->BOOKNO = status::g_StageInfo.getProfileBank();
    }
    pSYSTEM->SAVETYPE = type;
    if (g_AreaFlag.check(0x226)) {
        pSYSTEM->CLEAR = 1;
    } else {
        pSYSTEM->CLEAR = 0;
    }
}

THUMB void profile::Profile::collect_PROFILE_PARTY()
{
    pPARTY->OPTION_SACK_SORT = g_Option.getSackSort();
    pPARTY->OPTION_BGM_VOLUME = g_Option.getBgmVolume();
    pPARTY->OPTION_SEVOLUME = g_Option.getSeVolume();
    pPARTY->OPTION_BATTLE_SPEED = g_Option.getBattleSpeed();
    collectGameFlag(pPARTY->GLOBALFLAG, &g_AreaFlag);
    if (pSYSTEM->SAVETYPE == SAVETYPE_INTERVAL) {
        for (int i = 0; i < 128; i++) {
            pPARTY->AREAFLAG[i] = 0;
        }
    } else {
        collectGameFlag(pPARTY->AREAFLAG, &g_LocalFlag);
    }
    pPARTY->STORY_FLAG = status::g_Story.getFlagValue();
    pPARTY->STORY_CHAPTER_NO = status::g_Story.chapter_;
    for (int i = 0; i < 9; i++) {
        pPARTY->STORY_HEROEQUIP[i] = status::g_Story.getHeroEquip(i);
    }
    pPARTY->PLAY_TIME = status::g_Game.getPlayTime();
    pPARTY->WORLD_TIME = status::g_StageInfo.getWorldTime();
    pPARTY->TIME_ZONE = status::g_StageInfo.getTimeZone();
    pPARTY->TIME_STOP = status::g_StageAttribute.getTimestopFlag();
    status::g_StageInfo.collectMapFlag((SAVETYPE)pSYSTEM->SAVETYPE, pPARTY);
    for (int i = 0; i < 10; i++) {
        status::TOUCH_RANKING_DATA& tr = status::g_TouchData.getRanking(i);
        pPARTY->TOUCH_SCORE[i] = tr.score;
        pPARTY->TOUCH_STAGE[i] = tr.stage;
    }
    pPARTY->INFO_TOHEROS = status::StatusChange::getToherosInfo();
    pPARTY->INFO_SINOBIASI = status::StatusChange::getSinobiasiInfo();
    pPARTY->INFO_MONSTERSFOOD = status::StatusChange::getMonstersFoodInfo();
    pPARTY->ATTR_TORAMANA = status::StageAttribute::isToramana();
    {
        status::PlayerData& playerdata = status::PlayerDataAll::getPlayerData(0);
        pPARTY->RULA_LEVEL = playerdata.haveAction_.getRulaLevel();
        pPARTY->PARUPUNTE_LEVEL = playerdata.haveAction_.getParupunteLevel();
    }
    pPARTY->NO_ENCOUNT_FLAG = btl::Encount::getSingleton()->enable_;
    for (int i = 0; i < 88; i++) {
        pPARTY->NAME_INDEX[i] = status::PlayerDataAll::getPlayerNameIndex(i);
    }
    for (int i = 0; i < 64; i++) {
        pPARTY->SELECTTAISHI_FLAG[i] = status::g_MuseumStatus.getSelectTaishiFlag(i);
    }
    {
        int num1 = 8;
        for (int i = 0; i < num1; i++) {
            pPARTY->DAY_COUNTER[i] = cmn::g_CommonCounterInfo.getCounter(i);
        }
    }
}

ARM unsigned char status::HaveAction::getRulaLevel()
{
    return addRulaLevel_;
}

ARM unsigned char status::HaveAction::getParupunteLevel()
{
    return addParupunteLevel_;
}

THUMB void profile::Profile::collect_PROFILE_ASSETS()
{
    {
        status::HaveItemSack& hisack = status::g_Party.haveItemSack_;
        pASSETS->HAVING_GOLD = status::g_Party.gold_;
        pASSETS->BANK_GOLD = status::g_Party.bankMoney_;
        pASSETS->CASINO_TOKEN = status::g_Party.casinoCoin_;
        pASSETS->KINGS_MEDAL = status::g_Party.medalCoin_;
        pASSETS->BASHA = status::g_Party.carriage_;
        for (int i = 0; i < 263; i++) {
            int NO = hisack.getItem(i);
            int NUM = hisack.getItemCount(i);
            if (NUM > 99) {
                NUM = 99;
            }
            pASSETS->SACKITEM[i] = NO;
            pASSETS->SACKCOUNT[i] = NUM;
        }
    }
    {
        status::PartyStatusData& partystatusdata = status::g_Party.partyStatusData_;
        for (int i = 0; i < 10; i++) {
            status::PlayerStatus& playerstatus = partystatusdata.getPlayerStatusForCtrl(i);
            if (partystatusdata.getPlayerStatusFlagValue(i)) {
                pASSETS->ALL_MEMBER[i] = playerstatus.getIndex();
                pASSETS->ALL_MEMBER_FLAG[i] = partystatusdata.getPlayerStatusFlagValue(i);
            } else {
                pASSETS->ALL_MEMBER[i] = 0;
                pASSETS->ALL_MEMBER_FLAG[i] = 0;
            }
        }
        for (int i = 0; i < 4; i++) {
            pASSETS->OUTSIDE_MEMBER[i] = partystatusdata.getOutsideOrder(i);
        }
        for (int i = 0; i < 7; i++) {
            pASSETS->INSIDE_MEMBER[i] = partystatusdata.getInsideOrder(i);
        }
        for (int i = 0; i < 2; i++) {
            pASSETS->BACKSIDE_MEMBER[i] = partystatusdata.getBacksideOrder(i);
            unsigned short charaIndex = 0;
            if (partystatusdata.getBacksideOrder(i) != -1) {
                status::PlayerStatus& player = partystatusdata.getPlayerStatusForCtrl(partystatusdata.getBacksideOrder(i));
                charaIndex = player.getHaveStatusInfo().getHaveStatus().getCharaIndex();
            }
            pASSETS->BACKSIDE_MEMBER_CHARINDEX[i] = charaIndex;
        }
    }
    for (int i = 0; i < 26; i++) {
        status::MuseumItemStatus& mr = status::g_MuseumStatus.getMuseumItemStatus(i);
        pASSETS->MEISAN[i] = mr.getIconID();
    }
    {
        status::HaveItemSack& hisack = status::g_Party.haveItemSack_;
        dss::strcpy_s((char*)pASSETS->SACKNAME, 26, hisack.name_);
        pASSETS->CURSED_SACKNAME = hisack.getCursedName();
    }
}

THUMB void profile::Profile::collect_PROFILE_PLAYER()
{
    status::g_Party.store();
    PROFILE_PLAYER* pP = pPLAYER;
    for (int k = 0; k < 97; k++) {
        pP[k].PDA_INDEX = 0;
    }
    for (int i = 0; i < status::PlayerDataAll::PLAYER_ALL_MAX; i++) {
        status::PlayerData& playerdata = status::PlayerDataAll::playerData_[i];
        unsigned char flg = status::PlayerDataAll::playerFlag_[i].flag_;
        bool SAVE = false;
        if (i >= 1 && i <= 15) {
            SAVE = true;
        }
        if (i == 16) {
            SAVE = true;
        }
        if (i == 19) {
            SAVE = true;
        }
        if (flg != 0) {
            SAVE = true;
        }
        if (SAVE) {
            unkfunc_0204afa8(playerdata.name_);
            pP->PDA_INDEX = i;
            pP->PDA_FLAG = flg;
            pP->INDEX = playerdata.index_;
            nameCopy(pP->NAME, 18, (unsigned char*)playerdata.name_);
            pP->CURSED_NAME = playerdata.cursedName_;
            if (playerdata.nameBasedSex_ == 1) {
                pP->CURSED_NAME |= 0x80;
            }
            pP->TACTICS = playerdata.command_;
            pP->STATFLAG = playerdata.flag_.flag_;
            pP->EXP = playerdata.baseStatus_.exp_;
            pP->STRENGTH = playerdata.baseStatus_.strength_;
            pP->PROTECTION = playerdata.baseStatus_.protection_;
            pP->HP = playerdata.baseStatus_.hp_;
            pP->HPMAX = playerdata.baseStatus_.hpMax_;
            pP->MP = playerdata.baseStatus_.mp_;
            pP->MPMAX = playerdata.baseStatus_.mpMax_;
            pP->AGILITY = playerdata.baseStatus_.agility_;
            pP->WISDAM = playerdata.baseStatus_.wisdom_;
            pP->LUCK = playerdata.baseStatus_.luck_;
            pP->LEVEL = playerdata.baseStatus_.level_;
            for (int j = 0; j < 12; j++) {
                status::ItemData& itemdata = playerdata.haveItem_.itemArray_[j];
                pP->HAVEITEM[j] = itemdata.index_;
                if (itemdata.isEquipment()) {
                    pP->HAVEITEM[j] |= 0x8000;
                }
            }
            pP++;
        }
    }
}

THUMB void profile::Profile::collect_PROFILE_LOCATION()
{
    {
        dss::Fix32Vector3 pos;
        short dir;
        cmn::g_cmnPartyInfo.getPartyInfo(pos, dir);
        pLOCATION->PARTY_X = pos.vx.value;
        pLOCATION->PARTY_Y = pos.vy.value;
        pLOCATION->PARTY_Z = pos.vz.value;
        pLOCATION->PARTY_D = dir;
    }
    pLOCATION->RIDEON_TYPE = cmn::g_cmnPartyInfo.getRideOn();
    pLOCATION->SHIP_NO = cmn::g_cmnPartyInfo.getShipNo();
    {
        dss::Fix32Vector3 pos;
        short dir;
        cmn::g_cmnPartyInfo.getShipInfo(pos, dir);
        pLOCATION->SHIP_X = pos.vx.value;
        pLOCATION->SHIP_Y = pos.vy.value;
        pLOCATION->SHIP_Z = pos.vz.value;
        pLOCATION->SHIP_D = dir;
        pLOCATION->SHIP_ID = cmn::g_cmnPartyInfo.getShipMapName();
    }
    {
        dss::Fix32Vector3 pos = cmn::g_cmnPartyInfo.getIkadaPos();
        pLOCATION->RAFT_X = pos.vx.value;
        pLOCATION->RAFT_Y = pos.vy.value;
        pLOCATION->RAFT_Z = pos.vz.value;
        pLOCATION->RAFT_ID = cmn::g_cmnPartyInfo.getIkadaMapNameId();
    }
    dss::memset(pLOCATION->RESTART, 0, sizeof(pLOCATION->RESTART));
    dss::memset(pLOCATION->CHURCH, 0, sizeof(pLOCATION->CHURCH));
    {
        char* rmap = NULL;
        char* cmap = status::g_StageAttribute.getMapName();
        int ftype = 0;
        if (cmap == NULL) {
            cmap = "";
        }
        if (rmap == NULL) {
            rmap = cmap;
        }
        if (pSYSTEM->SAVETYPE == SAVETYPE_CHURCH) {
            cmap = rmap;
        }
        if (strcmp(cmap, "field") == 0) {
            ftype = g_Global.getFieldType();
        }
        dss::strcpy_s((char*)pLOCATION->CHURCH, 16, rmap);
        dss::strcpy_s((char*)pLOCATION->RESTART, 16, cmap);
        pLOCATION->FIELDTYPE = ftype;
    }
    {
        dss::Fix32Vector3& pos0 = status::g_StageInfo.getShipPosition(0);
        dss::Fix32Vector3& pos1 = status::g_StageInfo.getShipPosition(1);
        dss::Fix32Vector3& pos2 = status::g_StageInfo.getFirmamentPosition();
        dss::Fix32Vector3& pos3 = status::g_StageInfo.getOverviewPosition();
        dss::Fix32Vector3& pos4 = status::g_StageInfo.getOverviewTempPosition();
        collectFx32Vector3(pLOCATION->STAGE_INFO_LOCATION_SHIP1, &pos0);
        collectFx32Vector3(pLOCATION->STAGE_INFO_LOCATION_SHIP2, &pos1);
        collectFx32Vector3(pLOCATION->STAGE_INFO_LOCATION_TENKUUJYO, &pos2);
        collectFx32Vector3(pLOCATION->STAGE_INFO_LOCATION_MINIMAP1, &pos3);
        collectFx32Vector3(pLOCATION->STAGE_INFO_LOCATION_MINIMAP2, &pos4);
    }
    pLOCATION->RETURN_CHURCH = status::g_StageInfo.getReturnChurch();
    pLOCATION->LOAD_CHURCH = status::g_StageInfo.getLoadChurch();
    for (int i = 0; i < 9; i++) {
        pLOCATION->PLATE_MOVE[i] = status::g_StageInfo.getPuzzleSection(i % 3, i / 3);
    }
    pLOCATION->RIREMITO_SYMBOL_ID = status::g_StageInfo.getSymbolID();
    pLOCATION->RIREMITO_MAP = status::g_StageInfo.getRiremitMapId();
    pLOCATION->LAST_FIELD_LINK_SURFACE = status::g_StageInfo.getRanaMapSurfaceId();
    pLOCATION->LAST_RANARUTA_STAGE_ID = status::g_StageInfo.getRanaMapNameId();
    pLOCATION->KIMERA_SYMBOL = status::g_StageInfo.getkimeraSymbol();
    pLOCATION->FIELD_CHANGE = status::g_StageInfo.getFieldChange();
    status::g_StageInfo.saveBeforTruckDataSetup();
    pLOCATION->TROKKO_SWITCHDATA = status::g_StageInfo.switchDataFlag_;
    pLOCATION->TROKKO_SWITCHINIT = status::g_StageInfo.switchInitFlag_;
    pLOCATION->TROKKO_WAGON1DATA = status::g_StageInfo.wagonData1Flag_;
    pLOCATION->TROKKO_WAGON2DATA = status::g_StageInfo.wagonData2Flag_;
}
