#pragma once
#include <globaldefs.h>
#include "main/status/TaishiBase.hpp"
#include "main/leveldata/MeisanhinData.hpp"

namespace status {
    enum MUSEUMFLOOR {
        MUSEUMFLOOR_F1 = 0x276,
        MUSEUMFLOOR_F2 = 0x279,
        MUSEUMFLOOR_F3 = 0x27A,
        MUSEUMFLOOR_B1 = 0x27B,
        MUSEUMFLOOR_S1 = 0x27C,
        MUSEUMFLOOR_S2 = 0x27D,
    };

    enum MUSEUMTREND {
        MUSEUMTREND_FEAR = 0,
        MUSEUMTREND_FUNNY = 1,
        MUSEUMTREND_BEAUTIFUL = 2,
    };

    struct TAISHI_DATA {
        int isTaishi_;                              // 0x00
        unsigned int uniqueId_;                     // 0x04
        unsigned int price_;                        // 0x08
        unsigned char objectId_;                    // 0x0C
        unsigned char production_;                  // 0x0D
        char taishiName_[28];                       // 0x0E
        char producer_[26];                         // 0x2A
        char message_[136];                         // 0x44
    };

    struct MuseumItemStatus {
        unsigned short mapid_;                      // 0x00
        unsigned short mapobjectid_;                // 0x02
        unsigned short iconid_;                     // 0x04
        dq5::level::MeisanhinData meisan_;          // 0x08

        void setup(unsigned short mapid, unsigned short mapobjectid);
        unsigned short getMapID();
        unsigned short getMapObjectID();
        unsigned short getIconID();
        void setIconID(unsigned short id);
        dq5::level::MeisanhinData* getMeisanhinData();
        void setIconIDandRedraw(unsigned short id);
    };

    struct MuseumStatus {
        static const int OTHERS_TAISHI_MAX = 24;
        static const int SELECT_TAISHI_MAX = 64;
        static const int MUSEUM_ITEM_MAX = 51;

        TaishiBase playerTaishi_;                           // 0x0000
        TaishiBase othersTaishi_[OTHERS_TAISHI_MAX];        // 0x00CC
        TaishiBase keepTaishi_;                             // 0x13EC
        int selectTaishiFlag_[SELECT_TAISHI_MAX];           // 0x14B8
        MuseumItemStatus museumitem_[MUSEUM_ITEM_MAX];      // 0x15B8
        int museumLevel_;                                   // 0x1F48
        int museumPoint_;                                   // 0x1F4C
        int fearPoint_;                                     // 0x1F50
        int funnyPoint_;                                    // 0x1F54
        int beautifulPoint_;                                // 0x1F58
        int penaltyPoint_;                                  // 0x1F5C
        int successConnect_;                                // 0x1F60
        TAISHI_DATA successTaishi_;                         // 0x1F64

        MuseumStatus();
        ~MuseumStatus();
        void initialize();
        TaishiBase& getPlayerTaishi();
        TaishiBase& getOthersTaishi(int index);
        void deleteOthersTaishi(int index);
        int findExistTaishi(unsigned int uid);
        int getTaishiCount();
        int getBlankTaishiNo();
        void saveTaishi();
        void recoveryTaishi();
        void resetSaveTaishi();
        MuseumItemStatus& getMuseumItemStatus(int index);
        void setSelectTaishiFlag(int index, int flag);
        int getSelectTaishiFlag(int index);
        int findMuseumItemStatus(int objid);
        int findMuseumItemStatusForItemID(int itemID);
        int getMuseumLevel();
        int getPenaltyPoint();
        void updateTaishi();
        void updateMuseum();
        void updateLevel();
        dq5::level::MeisanhinData* __findMeisanhinData(int no);
        void computeLevel();
        MUSEUMTREND getMuseumTrend();
        int setIconByMapObjectID(int mid, int item);
        void setSuccessTaishi(TAISHI_DATA* taishiData, bool successFlag);
        int getFloorItemCount(MUSEUMFLOOR floor);
        int getFloorItemCount(MUSEUMFLOOR floor, int item);
        bool isFloorItemSame(int item);
        void resetingTaishiFlag();
    };

    extern unsigned short museum_status_data[102];
    extern MuseumStatus g_MuseumStatus;
}
