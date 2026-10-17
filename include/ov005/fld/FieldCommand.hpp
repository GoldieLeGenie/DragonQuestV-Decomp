#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"
#include "main/dss/GameSystemManager.hpp"

namespace fld
{
    struct FieldCommandAreaMap : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandBookingMenu : args::CommandObject {
        int fadeCount_;                         // 0x04

        FieldCommandBookingMenu();
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandBookingTownMenu : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandButtonSearch : args::CommandObject {
        int script_;                            // 0x04

        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandEncount : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandEvent : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandMaterielMenu : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandMenu : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandMenuSearch : args::CommandObject {
        int script_;                            // 0x04

        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandMessage : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandNormal : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandPartChange : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandPartyTalk : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandPlayer : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandScreenEffect : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandVehicle : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldCommandWalkCount : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    struct FieldSystemCommand : args::GameSystem {
        enum {
            CPartChangePriority = 0,
            CScreenEffectPriority = 1,
            CMessagePriority = 2,
            CBookingTownMenuPriority = 3,
            CBookingMenuPriority = 4,
            CMenuSearchPriority = 5,
            CMaterielMenuPriority = 6,
            CPlayerPriority = 7,
            CMapLinkPriority = 8,
            CEventPriority = 9,
            CButtonAreaMap = 10,
            CFieldVehicle = 11,
            CWalkCountPriority = 12,
            CEncountPriority = 13,
            CMenuPriority = 14,
            CButtonSearch = 15,
            CPartyTalkPriority = 16,
            CNormalPriority = 17,
        };

        args::CommandObjectManager commandObjectManager_;       // 0x004
        FieldCommandScreenEffect fieldCommandScreenEffect_;     // 0x108
        FieldCommandMessage fieldCommandMessage_;               // 0x10C
        FieldCommandEncount fieldCommandEncount_;               // 0x110
        FieldCommandPartChange fieldCommandPartChange_;         // 0x114
        FieldCommandMenu fieldCommandMenu_;                     // 0x118
        FieldCommandPartyTalk rieldCommandPartyTalk_;           // 0x11C
        FieldCommandMaterielMenu fieldCommandMaterielMenu_;     // 0x120
        FieldCommandEvent fieldCommandEvent_;                   // 0x124
        FieldCommandPlayer fieldCommandPlayer_;                 // 0x128
        FieldCommandNormal fieldCommandNormal_;                 // 0x12C
        FieldCommandMenuSearch fieldCommandMenuSearch_;         // 0x130
        FieldCommandButtonSearch fieldCommandButtonSearch_;     // 0x138
        FieldCommandWalkCount fieldCommandWalkCount_;           // 0x140
        FieldCommandAreaMap fieldCommandAreaMap_;               // 0x144
        FieldCommandBookingMenu fieldCommandBookingMenu_;       // 0x148
        FieldCommandVehicle fieldCommandVehicle_;               // 0x150
        FieldCommandBookingTownMenu fieldCommandBookingTownMenu_; // 0x154
        FieldCommandPartChange fieldCommandMapLink_;            // 0x158

        FieldSystemCommand();
        ~FieldSystemCommand();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };
} // namespace fld
