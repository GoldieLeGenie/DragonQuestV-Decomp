#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace cmn
{
    enum PARTY_RIDE_ON_TYPE {
        RIDE_ON_NONE = 0,
        RIDE_ON_TOWN_BALLOON = 1,
        RIDE_ON_SHIP_IKADA = 2,
        RIDE_ON_CARPET = 3,
        RIDE_ON_CASTLE = 4,
        RIDE_DRAGON = 5,
    };

    enum MENU_ACTION {
        MENU_ACTION_NONE = 0,
        MENU_RURA_SUCCESS = 1,
        MENU_RURA_FAILED = 2,
        MENU_RURA_AFTER = 3,
        MENU_RIREMIT = 4,
        MENU_RANARUTA = 5,
        MENU_TALK = 6,
        MENU_SEARCH = 7,
        MENU_KIMERA = 8,
        MENU_SORATOBU_START = 9,
        MENU_SORATOBU_SWITCH = 10,
        MENU_SORATOBU_END = 11,
        TABI_LINK = 12,
        RANA_START = 13,
        MAGIC_CARPET = 14,
        MASTER_DRAGON = 15,
        MASTER_DRAGON_DIRECT = 16,
        TENKU_CASTLE = 17,
        TRUCK_LINK = 18,
        SCOPE = 19,
        BALLON_HORN = 20,
    };

    struct CommonPartyInfo {
        dss::Fix32Vector3 prev_position_;       // 0x000
        dss::Fix32Vector3 startPos_;            // 0x00C
        dss::Fix32Vector3 separatePos_[5];      // 0x018
        short separateDir_[5];                  // 0x054
        dss::Fix32Vector3 position_;            // 0x060
        short dirIdx_;                          // 0x06C
        PARTY_RIDE_ON_TYPE rideOnType_;         // 0x070
        dss::Fix32Vector3 townShipPos_;         // 0x074
        short shipDirection_;                   // 0x080
        short mapNameIdShip_;                   // 0x082
        dss::Fix32Vector3 townIkadaPos_;        // 0x084
        int mapNameIdAtIkada_;                  // 0x090
        int shipNo_;                            // 0x094
        int roadFlag_;                          // 0x098
        int prevLocation_;                      // 0x09C
        MENU_ACTION menuAction_;                // 0x0A0
        int keepMap_;                           // 0x0A4
        int barron_;                            // 0x0A8
        int prevFrameBattle_;                   // 0x0AC
        dss::Fix32Vector3 collVec_;             // 0x0B0
        int collFlag_;                          // 0x0BC
        int ctrlID_;                            // 0x0C0
        int partyTalk;                          // 0x0C4
        dss::Fix32Vector3 tempFirmamentPos_;    // 0x0C8
        int tempFirmamentFieldType_;            // 0x0D4
        dss::Fix32Vector3 tempShipPos_;         // 0x0D8
        int playerTalk;                         // 0x0E4
        int wagonUid_;                          // 0x0E8
        dss::Fix32Vector3 backupPos_;           // 0x0EC
        short backupDirIdx_;                    // 0x0F8
        int iceCount_;                          // 0x0FC
        int iceStart_;                          // 0x100
        dss::Fix32Vector3 iceTarget_;           // 0x104
        int dispPos_;                           // 0x110
        int cancelColl_;                        // 0x114
        int dispMapUid_;                        // 0x118
        int cameraRot_;                         // 0x11C
        char* prev_dispMapName_;                // 0x120
        char* dispMapName_;                     // 0x124
        int linkDisp_;                          // 0x128
        int shipIkadaArea_;                     // 0x12C
        int mapLinkFlag_;                       // 0x130

        CommonPartyInfo();
        void getPartyInfo(dss::Fix32Vector3& position, short& dirIdx);
        void setDirIdx(short dirIdx);
        short& getDirIdx2();
        void setStartPosition();
        void setShipInfo(int mapNameId, dss::Fix32Vector3& position, short direction);
        short getShipMapName();
        void getShipInfo(dss::Fix32Vector3& position, short& direction);
        void setIkadaInfo(int mapNameId, dss::Fix32Vector3& position);
        int getIkadaMapNameId();
        int isPrevLocation();
        dss::Fix32Vector3 getIkadaPos();
        void resetShipIkadaMapName();
        void callCarriage();
        void setMenuAction(MENU_ACTION action);
        void setBackupPos(dss::Fix32Vector3& pos);
        void setBackupDirIdx(short idx);
        void setNotResetShipIkada(bool flag);
        void setKeep(int flag, int map, bool reset);
        int isAbortSaveTown();
        int isAbortSaveDungeon();
        PARTY_RIDE_ON_TYPE getRideOn();
        MENU_ACTION getMenuAction();
        void setRideOn(PARTY_RIDE_ON_TYPE type);
        int getShipNo();
        void setShipNo(int shipNo);
        void setSetupIceAction(bool flag);
        int getKeepMap();
        short getCarriageOutDir(int index);
        void setPrevLocation(bool flag);
        void setPrevPosition();
        void setPartyTalkEnable(bool flag);
        void setTalkCharaCtrlID(int ctrl);
        short getBackupDirIdx();
        int getCollFlag();
        dss::Fix32Vector3 getCharaColl();
        void setStartPos(dss::Fix32Vector3& pos);
        void setPosition(dss::Fix32Vector3& pos);
        int getWagonUid();
        void setWagonUid(int uid);
    };

    extern CommonPartyInfo g_cmnPartyInfo;
} // namespace cmn
