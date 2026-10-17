#pragma once
#include <globaldefs.h>
#include "ov001/town/SugorokuCommand.hpp"
#include "main/town/SugorokuPanelData.hpp"

namespace twn {
    enum SUGOROKU_MENU_STATE {
        SUGOROKU_DICE = 0,
        SUGOROKU_CAMERA = 1,
        SUGOROKU_END = 2,
    };

    // vtable 0x0218bf2c
    struct SugorokuSystemStart : SugorokuCommand {
        int state_;                             // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bf14
    struct SugorokuOpenRootMenu : SugorokuCommand {
        int next_;                              // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bf74
    struct SugorokuSystemDice : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bf44
    struct SugorokuSystemPlayerMove : SugorokuCommand {
        int end_;                               // 0x04
        int move_;                              // 0x08
        int gate_;                              // 0x0C
        int change_;                            // 0x10
        int return_;                            // 0x14
        int count_;                             // 0x18
        int sinR_;                              // 0x1C

        virtual void setup();
        virtual void execute();
        virtual int nextState();
        bool sugorokuMove(PanelData* data, PanelData* linkData, short dirIdx, int flag);
        bool sugorokuMoveSet();
        void sugorokuArrowSet();
    };

    // vtable 0x0218bf5c
    struct SugorokuSystemCameraMove : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c01c
    struct SugorokuSystemCameraEnd : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bf8c
    struct SugorokuPanelFinish : SugorokuCommand {
        int counter_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bfa4
    struct SugorokuSystemFadeOutEnd : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bfbc
    struct SugorokuSystemPanelStart : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bfd4
    struct SugorokuSystemPanelLink : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
        void changeInn(int& map, int& uid);
        void setTreasuerRoom();
    };

    // vtable 0x0218bfec
    struct SugorokuSystemFadeOutNextShop : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c004
    struct SugorokuSystemFadeInNextShop : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c13c
    struct SugorokuSystemFadeOutNextMenu : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c034
    struct SugorokuSystemFadeInNextMenu : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c04c
    struct SugorokuSystemShopOpen : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c064
    struct SugorokuSystemDebugStart : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c07c
    struct SugorokuSystemAbortEnd : SugorokuCommand {
        int start_;                             // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c094
    struct SugorokuSystemDiceControl : SugorokuCommand {
        int dice_;                              // 0x04
        int count_;                             // 0x08
        int isEnd_;                             // 0x0C

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c0ac
    struct SugorokuSystemTreasurePreRoom : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // not linked: its vtable is part of the TU's data layout, the linker drops it
    struct SugorokuSystemTreasureRoomLink : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c0c4
    struct SugorokuSystemTreasureRoomEnd : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c0dc
    struct SugorokuSystemTreasureRoomMove : SugorokuCommand {
        int start_;                             // 0x04
        int flag_;                              // 0x08

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c0f4
    struct SugorokuSystemTreasureRoomEndMessage : SugorokuCommand {
        enum MODE {
            MODE_MESSAGE = 0,
            MODE_YES = 1,
            MODE_NO = 2,
        };

        MODE mode_;                             // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c10c
    struct SugorokuSystemTreasureRoomSetTime : SugorokuCommand {
        enum MODE {
            MODE_FIRST_DICE = 0,
            MODE_SECOND_DICE = 1,
            MODE_MESSAGE = 2,
            MODE_END = 3,
        };

        MODE mode_;                             // 0x04
        int time_;                              // 0x08
        int drawDice_;                          // 0x0C
        int isEnd_;                             // 0x10
        int ctrlID_;                            // 0x14

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218c124
    struct SugorokuSystemBattleEnd : SugorokuCommand {
        int start_;                             // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };
}
