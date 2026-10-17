#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/town/TownCommandPlaySound.hpp"
#include "ov001/town/command/TownCommandBookingMenu.hpp"
#include "ov001/town/command/TownCommandBookingTownMenu.hpp"
#include "ov001/town/command/TownCommandButtonSearch.hpp"
#include "ov001/town/command/TownCommandButtonTalk.hpp"
#include "ov001/town/command/TownCommandCoercionSort.hpp"
#include "ov001/town/command/TownCommandComebackChurch.hpp"
#include "ov001/town/command/TownCommandEvent.hpp"
#include "ov001/town/command/TownCommandFukubikiDraw.hpp"
#include "ov001/town/command/TownCommandInitWait.hpp"
#include "ov001/town/command/TownCommandLink.hpp"
#include "ov001/town/command/TownCommandPartChange.hpp"
#include "ov001/town/command/TownCommandPartyTalk.hpp"
#include "ov001/town/command/TownCommandRestartGame.hpp"
#include "ov001/town/command/TownCommandScope.hpp"
#include "ov001/town/command/TownCommandScreenEffect.hpp"
#include "ov001/town/command/TownCommandWalkCount.hpp"
#include "ov001/town/command/TownMapDrawCommand.hpp"
#include "ov001/town/command/TownShopListDrawCommand.hpp"
#include "ov001/town/command/UnkTownCommandMenuSearch.hpp"
#include "ov001/town/command/UnkTownCommandMenuTalk.hpp"

namespace twn {
    struct TownPlayerMoveCommand : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct TownNormalCommand : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct TownMenuCommand : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct TownMessageCommand : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct TownMaterielMenuCommand : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct TownSugorokuCommand : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct TownPlayerLockCommand : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct TownTreasureRoomCommand : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct TownSystemCommand : args::GameSystem {
        args::CommandObjectManager commandObjectManager_;       // 0x004
        TownCommandScreenEffect townCommandScreenEffect_;       // 0x108
        TownMessageCommand townMessageCommand_;                 // 0x10C
        TownMenuCommand townMenuCommand_;                       // 0x110
        TownMapDrawCommand townMapDrawCommand_;                 // 0x114
        TownShopListDrawCommand townShopListDrawCommand;        // 0x120
        TownMaterielMenuCommand townMaterielMenuCommand;        // 0x124
        TownSugorokuCommand townSugorokuCommand_;               // 0x128
        TownPlayerMoveCommand townPlayerMoveCommand_;           // 0x12C
        TownNormalCommand townNormalCommand_;                   // 0x130
        TownCommandEncount townCommandEncount_;                 // 0x134
        TownCommandButtonTalk townCommandButtonTalk_;           // 0x138
        TownCommandButtonSearch townCommandButtonSearch_;       // 0x13C
        TownCommandPartChange townCommandPartChange_;           // 0x14C
        TownCommandInitWait townCommandInitWait_;               // 0x150
        UnkTownCommandMenuTalk unk_15c;                         // 0x15C
        UnkTownCommandMenuSearch unk_160;                       // 0x160
        TownCommandEvent townCommandEvent_;                     // 0x170
        TownCommandPartyTalk townCommandPartyTalk_;             // 0x174
        TownCommandWalkCount townCommandWalkCount_;             // 0x178
        TownCommandLink townCommandLink_;                       // 0x17C
        TownCommandBookingMenu townCommandBookingMenu_;         // 0x180
        TownCommandFukubikiDraw townCommandFukubikiDraw_;       // 0x190
        TownTreasureRoomCommand townTreasureRoomCommand_;       // 0x194
        TownCommandBookingTownMenu townCommandBookingTownMenu_; // 0x198
        TownCommandComebackChurch townCommandComebackChurch_;   // 0x19C
        TownCommandRestartGame townCommandRestartGame_;         // 0x1A4
        TownCommandScope townCommandScope_;                     // 0x1AC
        TownCommandCoercionSort townCommandCoercionSort_;       // 0x1B0
        TownPlayerLockCommand townPlayerLockCommand_;           // 0x1B4
        TownCommandPlaySound townCommandPlaySound_;             // 0x1B8

        TownSystemCommand();
        ~TownSystemCommand();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        void setWait(bool flag);
    };
}
