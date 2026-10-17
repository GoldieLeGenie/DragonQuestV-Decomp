#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace casino {
    enum CARD_ACTION {
        CARD_ACTION_TABULATE,
        CARD_ACTION_REVERSE,
        CARD_ACTION_MOVE,
        CARD_ACTION_FADE,
        CARD_ACTION_MAX,
    };

    struct PokerActionBase {
        // vtable                               // 0x00
        int isEnd_;                             // 0x04
        dss::Fix32 distance_;                   // 0x08
        int doubleUp_;                          // 0x0C
        unsigned short ang_[5];                 // 0x10
        char gyre_[5];                          // 0x1A
        char index_;                            // 0x1F
        char moveDirection_;                    // 0x20

        virtual void setup() = 0;
        virtual void execute() = 0;
        bool isEnd();
        void setCardIndex(char index);
        void hopCard(int cardIndex);
    };

    struct PokerActionFade : PokerActionBase {
        int fadeIn_;                            // 0x24
        unsigned char alpha_[5];                // 0x28

        virtual void setup();
        virtual void execute();
    };

    struct PokerActionMove : PokerActionBase {
        char direction_;                        // 0x21
        dss::Fix32Vector3 endPos_;              // 0x24

        virtual void setup();
        virtual void execute();
        void setMoveDirection(char direction);
        void setEndPos(dss::Fix32Vector3 pos);
    };

    struct PokerActionReverse : PokerActionBase {
        virtual void setup();
        virtual void execute();
    };

    struct PokerActionTabulate : PokerActionBase {
        virtual void setup();
        virtual void execute();
    };

    struct PokerAction {
        PokerActionBase* cardAction_[4];            // 0x00
        CARD_ACTION action_;                        // 0x10
        PokerActionTabulate pokerActionTabulate_;   // 0x14
        PokerActionReverse pokerActionReverse_;     // 0x38
        PokerActionMove pokerActionMove_;           // 0x5C
        PokerActionFade pokerActionFade_;           // 0x8C

        static PokerAction* getSingleton();
        void initialize();
        void execute();
        bool isEnd();
        void setCardAction(CARD_ACTION action);
        void setCardIndex(int index);
        PokerActionMove& getActionMove();
    };
}
