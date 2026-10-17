#pragma once
#include <globaldefs.h>
#include "ov001/town/SugorokuCommand.hpp"

namespace twn {
    struct SugorokuPanelChanceCard {
        enum CHANCE_STATUS {
            CHANCE_STRENGTH = 1,
            CHANCE_AGILITY = 2,
            CHANCE_PROTECTION = 3,
            CHANCE_WISDOM = 4,
            CHANCE_LUCK = 5,
            CHANCE_MAXHP = 6,
        };

        enum ENCOUNT_TYPE {
            TYPE_BEAST = 0,
            TYPE_SEA = 1,
            TYPE_BIRD = 2,
            TYPE_ZOMBIE = 3,
        };

        static void openMessage();
        static void statusChange(int paramIndex, char value, bool statusUpFlag);
        static bool isStatusLimit(int paramIndex, bool statusUpFlag);
        static int getSugorokuEncountTileID(ENCOUNT_TYPE type);
        static bool sugorokuEncount(int tileID);
        static void goldUp(int gold);
        static bool goldDown(int gold);
        static void setParameterMacro(int paramIndex);
    };

    // vtable 0x0218befc
    struct SugorokuPanelChanceCardStrengthUp1 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bb84
    struct SugorokuPanelChanceCardStrengthUp2 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bb9c
    struct SugorokuPanelChanceCardAgilityUp1 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bbb4
    struct SugorokuPanelChanceCardAgilityUp2 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bbcc
    struct SugorokuPanelChanceCardProtectionUp1 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bbe4
    struct SugorokuPanelChanceCardProtectionUp2 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bbfc
    struct SugorokuPanelChanceCardWisdomUp : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bc14
    struct SugorokuPanelChanceCardWisdomDown : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bc2c
    struct SugorokuPanelChanceCardLuckUp1 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bc44
    struct SugorokuPanelChanceCardLuckUp2 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bc5c
    struct SugorokuPanelChanceCardStrengthDown : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bc74
    struct SugorokuPanelChanceCardAgilityDown : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bc8c
    struct SugorokuPanelChanceCardProtectionDown : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bca4
    struct SugorokuPanelChanceCardLuckDown : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bcbc
    struct SugorokuPanelChanceCardBackToStart : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bcd4
    struct SugorokuPanelChanceCardEncount1 : SugorokuCommand {
        int tileID_;                            // 0x04
        int encountEnd_;                        // 0x08

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bcec
    struct SugorokuPanelChanceCardEncount2 : SugorokuCommand {
        int tileID_;                            // 0x04
        int encountEnd_;                        // 0x08

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bd04
    struct SugorokuPanelChanceCardEncount3 : SugorokuCommand {
        int tileID_;                            // 0x04
        int encountEnd_;                        // 0x08

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bd1c
    struct SugorokuPanelChanceCardEncount4 : SugorokuCommand {
        int tileID_;                            // 0x04
        int encountEnd_;                        // 0x08

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bd34
    struct SugorokuPanelChanceCardGoldDown100 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bd4c
    struct SugorokuPanelChanceCardGoldUp100 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bd64
    struct SugorokuPanelChanceCardNotEncount : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bd7c
    struct SugorokuPanelChanceCardHoleTrap : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bd94
    struct SugorokuPanelChanceCardChanceParameter : SugorokuCommand {
        enum {
            DICE_START = 0,
            DICE_PARAM = 1,
            DICE_UP_DOWN = 2,
            DICE_CLOSE = 3,
            DICE_END = 4,
        };

        int endFlag_;                           // 0x04
        int chanceParam_;                       // 0x08
        int updownParam_;                       // 0x0C
        int mode_;                              // 0x10

        virtual void setup();
        virtual void execute();
        virtual int nextState();
        void changeParam();
    };

    // vtable 0x0218bdac
    struct SugorokuPanelChanceCardTreasuerBox : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08
        int getItem_;                           // 0x0C
        int riseUpIndex_;                       // 0x10

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bdc4
    struct SugorokuPanelChanceCardDiceCountUp : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bddc
    struct SugorokuPanelChanceCardInn : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bdf4
    struct SugorokuPanelChanceCardSelectDice : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218be0c
    struct SugorokuPanelChanceCardMoveNext6 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218be24
    struct SugorokuPanelChanceCardMoveBack5 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218be3c
    struct SugorokuPanelChanceCardDiceLimitDown : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218be54
    struct SugorokuPanelChanceCardTreasuerRoom : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218be6c
    struct SugorokuPanelChanceCardLucky1 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218be84
    struct SugorokuPanelChanceCardLucky2 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218be9c
    struct SugorokuPanelChanceCardLucky3 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218beb4
    struct SugorokuPanelChanceCardUnlucky1 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218becc
    struct SugorokuPanelChanceCardUnlucky2 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bee4
    struct SugorokuPanelChanceCardUnlucky3 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };
}
