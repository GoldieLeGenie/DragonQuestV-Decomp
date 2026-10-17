#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"
#include "main/cmn/MoveBase.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/town/TownTruckData.hpp"

namespace twn {
    struct TownTruckRail {
        short index_;                           // 0x00
        short link_[3];                         // 0x02
        short root_;                            // 0x08
        short cutlink_;                         // 0x0A
        short linkCount_;                       // 0x0C
        dss::BitFlag<unsigned short> flag_;     // 0x0E
        short jumpIndex_;                       // 0x10
        short jumpMap_;                         // 0x12

        void initialize();
        void setData(short index, short flag, short jumpIndex, short jumpMap);
        void pushLink(short link);
        void setupSwitch(int linkIndex);
        void changeSwitch();
        bool checkFlag(unsigned short flag);
        short getRoot();
        short getJumpMap();
        short getJumpIndex();
    };

    struct TownTruckSystem {
        int startOffset_;                       // 0x000
        int railCount_;                         // 0x004
        int delWagonUid_;                       // 0x008
        TownTruckRail rail_[160];               // 0x00C

        void initialize();
        int getRailNoByIndex(int index);
        int getNextRailNo(int nowNo, int prevNo);
        int checkWagon(dss::Fix32Vector3& pos);
        void nextPos(int nowRailNo, dss::Fix32Vector3& nowPos, dss::Fix32Vector3& target);
        TownTruckWagon& getWagonByUid(int uid);
        int getRailNo(dss::Fix32Vector3& nowPos);
        void registWagon(int uid, int map);
        void setupWagon();
        void wagonCrear();
        void saveBeforSetup();
        void setupSwitch(int rootIndex, int setIndex, int switchUid, int startSwitchAnim, int railUid, int startRailAnim);
        void switchRail(int uid);
        static void setDelWagonUid(int uid);
        TownTruckRail& getRailByRailNo(int railNo);
        int getWagonCount();
    };

    struct TownActionTruck : cmn::ActionBase {
        enum {
            NONE = 0,
            GET_ON = 1,
            MOVE = 2,
            GET_DOWN = 3,
            SLOPE = 4,
            SLOPE_DOWN = 5,
            TRAIN_1 = 6,
            TRAIN_2 = 7,
            TRAIN_3 = 8,
            END = 9,
        };

        static const dss::Fix32 slopeFx;
        static const dss::Fix32 truckSpeed;
        static const dss::Fix32 truckSpeed2;
        static const dss::Fix32 trainSpeed2;
        static const dss::Fix32 slopelen;
        static const dss::Fix32 trainR;

        TownTruckSystem system_;                // 0x004
        dss::Fix32Vector3 vec_;                 // 0xC90
        int state_;                             // 0xC9C
        int counter_;                           // 0xCA0
        int nowRailNo_;                         // 0xCA4
        int prevRailNo_;                        // 0xCA8
        int wagonUid_;                          // 0xCAC
        int seesaw_;                            // 0xCB0
        int slope_;                             // 0xCB4
        int height_;                            // 0xCB8
        int sparkIndex_;                        // 0xCBC
        int jumpCount_;                         // 0xCC0
        cmn::MoveBase trainMove_;               // 0xCC4
        int trainRailNo_;                       // 0xD14
        int prevTrainRailNo_;                   // 0xD18
        dss::Fix32Vector3 trainPos_;            // 0xD1C
        int trainUid_;                          // 0xD28
        int scriptWagonUid_;                    // 0xD2C
        int scriptRail_;                        // 0xD30
        int prevScriptRail_;                    // 0xD34
        int scriptFlag_;                        // 0xD38
        cmn::MoveBase scriptMove_;              // 0xD3C
        dss::Fix32Vector3 scriptPos_;           // 0xD8C
        int waterNo_;                           // 0xD98
        int waterSe_;                           // 0xD9C
        int trainRunSe_;                        // 0xDA0
        int wagonSe_;                           // 0xDA4
        int initRunSe_;                         // 0xDA8
        int initWatSe_;                         // 0xDAC

        virtual int setup();
        virtual void execute();
        virtual int update();
        virtual void terminate();
        int check();
        void set();
        void scriptStart(int wagonUid, int nowRail, int prevRail);
        void scriptMove();
        static int isScriptMove();
        bool preActionCheck();
        void checkAction();
        void firstMove();
        void moveNext(int next, dss::Fix32 speed);
        void setGetDown();
        int getWaterEffectNo();
        void moveEnd();
    };
}
