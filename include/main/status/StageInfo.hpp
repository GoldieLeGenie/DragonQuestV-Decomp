#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/cmn/WorldLocation.hpp"
#include "main/profile/Profile.hpp"

namespace dq5 {
    enum RETURN_GAME_TYPE {
        RETURN_GAME_NONE = 0,
        RETURN_GAME_CHURCH = 1,
        RETURN_GAME_ABORT = 2,
        RETURN_GAME_LOSE = 3,
    };
}

namespace status {
    struct StageInfo {
        dss::BitFlag<unsigned char> symbolFlag_[16];        // 0x000
        dss::BitFlag<unsigned short> mapVeil_[16];          // 0x010
        dss::BitFlag<unsigned char> furnFlag_[128];         // 0x030
        dss::BitFlag<unsigned char> doorFlag_[32];          // 0x0B0
        dss::BitFlag<unsigned char> breakFlag_[32];         // 0x0D0
        dss::Fix32Vector3 rock_[10];                        // 0x0F0
        int rockFlag_[10];                                  // 0x168
        dss::Fix32Vector3 shipPosition_[2];                 // 0x190
        dss::Fix32Vector3 firmamentPosition_;               // 0x1A8
        dss::Fix32Vector3 overviewPosition_;                // 0x1B4
        dss::Fix32Vector3 overviewTempPosition_;            // 0x1C0
        TIME_ZONE timeZone_;                                // 0x1CC
        unsigned short worldTime_;                          // 0x1D0
        int returnChurchData_;                              // 0x1D4
        int loadChurchData_;                                // 0x1D8
        int fieldChangeIndex_;                              // 0x1DC
        unsigned char section_[3][3];                       // 0x1E0
        int symbolID_;                                      // 0x1EC
        int riremitMap_;                                    // 0x1F0
        int lastFldSurface_;                                // 0x1F4
        int lastRanaStageNameId_;                           // 0x1F8
        int kimeraSymbol_;                                  // 0x1FC
        unsigned int switchDataFlag_;                       // 0x200
        unsigned int switchInitFlag_;                       // 0x204
        unsigned int wagonData1Flag_;                       // 0x208
        unsigned int wagonData2Flag_;                       // 0x20C
        dss::Fix32Vector3 idoLinkPos_;                      // 0x210
        int returnChurchReOrder_;                           // 0x21C
        short idoLinkDirIdx_;                               // 0x220
        int idoLinkInFlag_;                                 // 0x224
        int idoLinkOutFlag_;                                // 0x228
        int ruraFlag_;                                      // 0x22C
        int ruraSymbol_;                                    // 0x230
        int fallFlag_;                                      // 0x234
        int menuTalk_;                                      // 0x238
        int menuSearch_;                                    // 0x23C
        int shipEncount_;                                   // 0x240
        int encount_;                                       // 0x244
        int encountMapUid_;                                 // 0x248
        int ropeLink_;                                      // 0x24C
        int returnBookFlag_;                                // 0x250
        int load_;                                          // 0x254
        int chapterLoad_;                                   // 0x258
        int profileBank_;                                   // 0x25C
        int profileType_;                                   // 0x260
        short lastParty_[9];                                // 0x264
        int flagMapChange_;                                 // 0x278
        int reliveCheckFlag_;                               // 0x27C
        int reliveMessageFlag_;                             // 0x280
        int sepiaFlag_;                                     // 0x284
        dq5::RETURN_GAME_TYPE returnGame_;                  // 0x288
        dss::Vector3<short> backupCameraAngle_;             // 0x28C

        StageInfo();
        ~StageInfo();
        void initialize();
        void collectMapFlag(profile::SAVETYPE savetype, profile::PROFILE_PARTY* pparty);
        void deliverMapFlag(profile::SAVETYPE savetype, profile::PROFILE_PARTY* pparty);
        void resetVeil(bool flag);
        void setMapVeil(int x, int y, int flag);
        bool getMapVeil(int x, int y);
        void setSymbolFlag(int index);
        bool getSymbolFlag(int index);
        void initSymbolFlag();
        void setFurnFlag(int index);
        bool getFurnFlag(int index);
        void removeFurnFlag(int index);
        void initFurnFlag();
        void setDoorOpenFlag(int index);
        void removeDoorOpenFlag(int index);
        bool getDoorOpenFlag(int index);
        void initDoorOpenFlag();
        int getReliveCheckFlag();
        void setReliveCheckFlag(bool flag);
        int getReliveMessageFlag();
        void setReliveMessageFlag(bool flag);
        void setFurnBreakFlag(int index);
        bool getFurnBreakFlag(int index);
        void initFurnBreakFlag();
        void setTimeZone(TIME_ZONE time);
        void setShipPosition(int index, dss::Fix32Vector3& pos);
        void setFirmamentPosition(dss::Fix32Vector3& pos);
        void setFieldChange(int ch);
        int getFieldChange();
        int getProfileBank();
        void setProfileBank(int val);
        void setProfileType(int val);
        int getReturnChurch();
        void setReturnChurch(int church);
        int getLoadChurch();
        void setLoadChurch(int church);
        int getSymbolID();
        void setSymbolID(int sy);
        void setRiremitMapId(int id);
        void setRanaMapSurfaceId(int id);
        void setKimeraSymbol(int id);
        void setReturnGame(dq5::RETURN_GAME_TYPE returnGame);
        dq5::RETURN_GAME_TYPE getReturnGame();
        void setLastParty(int num, int index);
        short getLastParty(int num);
        void setLoadFlag(bool flag);
        void setChapterLoadFlag(bool flag);
        dss::Fix32Vector3& getShipPosition(int index);
        dss::Fix32Vector3& getFirmamentPosition();
        dss::Fix32Vector3& getOverviewPosition();
        void setOverviewPosition(dss::Fix32Vector3& pos);
        void setOverviewTempPosition(dss::Fix32Vector3& pos);
        dss::Fix32Vector3& getOverviewTempPosition();
        int getRiremitMapId();
        int getRanaMapSurfaceId();
        int getRanaMapNameId();
        int getkimeraSymbol();
        dq5::DAY_NIGHT getDayNight();
        TIME_ZONE getTimeZone();
        void setWorldTime(unsigned short wt);
        int getWorldTime() const;
        void setCurrentTimeZone(TIME_ZONE time);
        void setChurchMapNameId(unsigned short nameId);
        void returnChurch();
        void loadChurch();
        void initPuzzle();
        int getPuzzleSection(int x, int y);
        void setPuzzleSection(int num, int x, int y);
        void setRanaMap(int id);
        void setRanaMapNameId(int nameId);
        void setRuraFlag(int rura);
        int getRuraFlag();
        void setEncountFlag(bool flag);
        int getEncountFlag();
        void setShipEncount(bool flag);
        void setRuraTownID(int id);
        int getRuraTownID();
        void setIdoLinkInFlag(bool flag);
        int getIdoLinkInFlag();
        void setIdoLinkOutFlag(bool flag);
        void setRopeLink(int flag);
        int getReturnBookFlag();
        void setReturnBookFlag(bool flag);
        void setFallFlag(bool flag);
        void setRockFlag(int index, bool flag);
        int getRockFlag(int index);
        dss::Fix32Vector3& getRockLocation(int index);
        bool isLoadFlag();
        void setStageSepia(bool sep);
        int getFallFlag();
        void pushCameraAngle(dss::Vector3<short> pos);
        dss::Vector3<short>& popCameraAngle();
        void playerFlagClear();
        void saveBeforTruckDataSetup();
        void loadAfterTruckDataSetup();
    };

    extern StageInfo g_StageInfo;
}
