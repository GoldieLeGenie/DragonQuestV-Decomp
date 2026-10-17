#pragma once
#include <globaldefs.h>
#include "ov001/town/SugorokuCommand.hpp"

namespace twn {
    struct SugorokuPanelAction {
        struct RISEUP_ITEM {
            int index;                          // 0x00
            int itemID[2];                      // 0x04
            int messageNo[2];                   // 0x0C
        };

        enum {
            TYPE_TANSU = 2,
            TYPE_TUBO = 3,
            TYPE_BOX = 4,
        };

        static void goldUp(int gold);
        static bool goldDown(int gold);
        static void diceUp(int dice);
        static void diceDown(int dice);
        static void moveNext(char count);
        static void moveBack(char count);
        static char isSelectChanceCard(int chanceNo);
        static void openPanelActionMessage();
        static bool addTreasuerMessage(int type, RISEUP_ITEM& riseup);
        static int selectNormalPanelAction(RISEUP_ITEM& riseup);
        static void startSugorokuEncount(sugoroku::SUGOROKU_ENCOUNT_TYPE type);
        static int isMessageOpen(sugoroku::NEXT_ACTION nextAction);
    };

    // vtable 0x0218bb6c
    struct SugorokuPanelActionKaidanUp : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b554
    struct SugorokuPanelActionKaidanDown : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b56c
    struct SugorokuPanelActionGoldUp50 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b584
    struct SugorokuPanelActionGoldUp100 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b59c
    struct SugorokuPanelActionGoldUp200 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b5b4
    struct SugorokuPanelActionGoldUp300 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b5cc
    struct SugorokuPanelActionGoldUp500 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b5e4
    struct SugorokuPanelActionGoldUp1000 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b5fc
    struct SugorokuPanelActionGoldUp2000 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b614
    struct SugorokuPanelActionGoldUp3000 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b62c
    struct SugorokuPanelActionGoldUp5000 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b644
    struct SugorokuPanelActionGoldDown50 : SugorokuCommand {
        int endFlag_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b65c
    struct SugorokuPanelActionGoldDown100 : SugorokuCommand {
        int endFlag_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b674
    struct SugorokuPanelActionGoldDown200 : SugorokuCommand {
        int endFlag_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b68c
    struct SugorokuPanelActionGoldDown300 : SugorokuCommand {
        int endFlag_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b6a4
    struct SugorokuPanelActionGoldDown500 : SugorokuCommand {
        int endFlag_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b6bc
    struct SugorokuPanelActionGoldDown1000 : SugorokuCommand {
        int endFlag_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b6d4
    struct SugorokuPanelActionGoldDown2000 : SugorokuCommand {
        int endFlag_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b6ec
    struct SugorokuPanelActionGoldDown3000 : SugorokuCommand {
        int endFlag_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b704
    struct SugorokuPanelActionGoldDown5000 : SugorokuCommand {
        int endFlag_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b71c
    struct SugorokuPanelActionDiceUp1 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b734
    struct SugorokuPanelActionDiceUp2 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b74c
    struct SugorokuPanelActionDiceUp3 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b764
    struct SugorokuPanelActionDiceUp5 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b77c
    struct SugorokuPanelActionDiceDown1 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b794
    struct SugorokuPanelActionDiceDown2 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b7ac
    struct SugorokuPanelActionDiceDown3 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b7c4
    struct SugorokuPanelActionDiceDown5 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b7dc
    struct SugorokuPanelActionMoveNext1 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b7f4
    struct SugorokuPanelActionMoveNext2 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b80c
    struct SugorokuPanelActionMoveNext3 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b824
    struct SugorokuPanelActionMoveNext4 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b83c
    struct SugorokuPanelActionMoveNext5 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b854
    struct SugorokuPanelActionMoveNext6 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b86c
    struct SugorokuPanelActionMoveBack1 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b884
    struct SugorokuPanelActionMoveBack2 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b89c
    struct SugorokuPanelActionMoveBack3 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b8b4
    struct SugorokuPanelActionMoveBack4 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b8cc
    struct SugorokuPanelActionMoveBack5 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b8e4
    struct SugorokuPanelActionMoveBack6 : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b8fc
    struct SugorokuPanelActionEncountNormal : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b914
    struct SugorokuPanelActionEncountMetal : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b92c
    struct SugorokuPanelActionDamage : SugorokuCommand {
        int endFlag_;                           // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b944
    struct SugorokuPanelActionLostMp : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b95c
    struct SugorokuPanelActionChangeParameter : SugorokuCommand {
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
        bool isParamLimitValue(bool max);
        void changeParam();
    };

    // vtable 0x0218b974
    struct SugorokuPanelActionChanceCard : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b98c
    struct SugorokuPanelActionBackToStart : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b9a4
    struct SugorokuPanelActionHoleTrap : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b9bc
    struct SugorokuPanelActionTravelGate : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b9d4
    struct SugorokuPanelActionTansu : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08
        int openMenu_;                          // 0x0C
        SugorokuPanelAction::RISEUP_ITEM item_; // 0x10

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218b9ec
    struct SugorokuPanelActionTubo : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08
        int openMenu_;                          // 0x0C
        SugorokuPanelAction::RISEUP_ITEM item_; // 0x10

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218ba04
    struct SugorokuPanelActionTreasuerBox : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08
        int openMenu_;                          // 0x0C
        SugorokuPanelAction::RISEUP_ITEM item_; // 0x10

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218ba1c
    struct SugorokuPanelActionInn : SugorokuCommand {
        int count_;                             // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218ba34
    struct SugorokuPanelActionShop : SugorokuCommand {
        int count_;                             // 0x04

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218ba4c
    struct SugorokuPanelActionFlat : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08
        int actionNo_;                          // 0x0C
        int encountFlag_;                       // 0x10
        SugorokuPanelAction::RISEUP_ITEM item_; // 0x14

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218ba64
    struct SugorokuPanelActionForest : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08
        int actionNo_;                          // 0x0C
        int encountFlag_;                       // 0x10
        SugorokuPanelAction::RISEUP_ITEM item_; // 0x14

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218ba7c
    struct SugorokuPanelActionMountain : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08
        int actionNo_;                          // 0x0C
        int encountFlag_;                       // 0x10
        SugorokuPanelAction::RISEUP_ITEM item_; // 0x14

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218ba94
    struct SugorokuPanelActionKanbanUp : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218baac
    struct SugorokuPanelActionKanbanDown : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bac4
    struct SugorokuPanelActionKanbanLeft : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218badc
    struct SugorokuPanelActionKanbanRight : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218baf4
    struct SugorokuPanelActionChangeGate : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bb0c
    struct SugorokuPanelActionSugorokuDungeon : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08
        int yes_;                               // 0x0C

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bb24
    struct SugorokuPanelActionTreasuerRoom : SugorokuCommand {
        int endFlag_;                           // 0x04
        int yesnoFlag_;                         // 0x08
        int yes_;                               // 0x0C

        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bb3c
    struct SugorokuPanelActionHealPoint : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };

    // vtable 0x0218bb54
    struct SugorokuPanelActionSelectSpot : SugorokuCommand {
        virtual void setup();
        virtual void execute();
        virtual int nextState();
    };
}
