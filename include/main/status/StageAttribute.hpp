#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace dq5 {
    enum LandType {
        Sea = 0,
        Desert = 1,
        Mountain = 2,
        Lock = 3,
        Pond = 4,
        Bush = 5,
        Field = 6,
        Forest = 7,
        Floor = 8,
        Island = 9,
    };

    namespace level {
        struct FloorParam;
        struct BattleMap;
    }
}

namespace status {
    struct StageAttribute {
        static const int FLAG_TIMEZONE = 0x1;
        static const int FLAG_MAPICON = 0x2;
        static const int FLAG_SHOPICON = 0x4;
        static const int FLAG_CAMERAICON = 0x8;
        static const int FLAG_RULA = 0x10;
        static const int FLAG_RIREMITO = 0x20;
        static const int FLAG_LANARUTA = 0x40;
        static const int FLAG_BASHA_ENTER = 0x80;
        static const int FLAG_BASHA_ENABLE = 0x100;
        static const int FLAG_ENCOUNT = 0x200;
        static const int FLAG_EVENT_ENCOUNT = 0x400;
        static const int FLAG_RULA_DISABLE = 0x800;
        static const int FLAG_RIREMITO_DISABLE = 0x1000;
        static const int FLAG_ABORT_SAVE = 0x20000;
        static const int FLAG_LANARUTA_DISABLE = 0x40000;
        static const int FLAG_SHOP_LIST_DISABLE = 0x80000;
        static const int FLAG_COERCION_SORT = 0x100000;
        static const int FLAG_YAMI = 0x200000;
        static const int FLAG_KIMERA_SET_DISABLE = 0x400000;

        dss::Flag flag_;                        // 0x00
        char mapName_[32];                      // 0x04
        int floorIndex_;                        // 0x24
        int normalBtlMapIndex_;                 // 0x28
        int eventBtlMapIndex_;                  // 0x2C
        char* map_;                             // 0x30
        char btlMapName_[32];                   // 0x34
        unsigned short battleBackColor_;        // 0x54
        char* btlMap_;                          // 0x58
        char evBtlMapName_[32];                 // 0x5C
        char* evBtlMap_;                        // 0x7C
        char evChapelMapName_[32];              // 0x80
        int mapCorrectIndex_;                   // 0xA0
        int shopDataIndex_;                     // 0xA4
        int furnitureIndex_;                    // 0xA8
        int timestop_;                          // 0xAC

        static int toramana_;

        StageAttribute();
        ~StageAttribute();
        void initialize();
        void setup(const char* mapname, int floorIndex, int areaIndex);
        void setupField();
        void cleanup();
        void setTimeZoneEnable(int flag);
        bool isTimeZoneEnable() const;
        int getMapCorrectIndex();
        void setMapIcon(int flag);
        bool isMapIcon() const;
        void setShopIcon(int flag);
        bool isShopIcon() const;
        void setCameraIcon(int flag);
        bool isCameraIcon() const;
        void setRula(int flag);
        bool isRula() const;
        void setRulaDisable(int flag);
        bool isRulaDisable() const;
        void setRiremito(int flag);
        bool isRiremito() const;
        void setRiremitoDisable(int flag);
        bool isRiremitoDisable() const;
        void setLanaruta(int flag);
        bool isLanaruta() const;
        void setLanarutaDisable(int flag);
        bool isLanarutaDisable() const;
        void setYami(int flag);
        bool getYami() const;
        void setShopListDisable(int flag);
        bool isShopListDisable();
        bool isKimeraSetDisable();
        void setKimeraSetDisable(int flag);
        static void setToramana(int flag);
        static int isToramana();
        void setCarriageEnter(int flag);
        int getTimestopFlag();
        void setTimestopFlag(int flag);
        bool isCarriageEnter() const;
        void setCarriageEnable(int flag);
        bool isCarriageEnable() const;
        void setEncount(int flag);
        bool isEncount() const;
        void setEventEncount(int flag);
        void setAbortSave(int flag);
        void setCoercionSort(int flag);
        bool isCoercionSort() const;
        void setBtlMapName(const char* name);
        void setBtlMapNameOnField(dq5::LandType land);
        char* getBtlMapName();
        void setEvBtlMapName(const char* name);
        char* getEvBtlMapName();
        void setEvBtlMapToBtlMap();
        void setMapName(const char* name);
        char* getMapName() const;
        unsigned short getBattleMapBackColor();
        void partyWipeOut();
        int getShopDataIndex();
        void setShopDataIndex(int index);
        static dq5::level::FloorParam* getFloorParam(int floorIndex);
        static dq5::level::BattleMap* getBattleMap(int battleIndex);
    };

    extern StageAttribute g_StageAttribute;
}
