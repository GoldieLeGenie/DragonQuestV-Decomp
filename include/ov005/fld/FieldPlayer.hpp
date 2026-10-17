#pragma once
#include <globaldefs.h>
#include "main/cmn/PlayerAction.hpp"
#include "ov005/fld/FieldAction.hpp"

namespace fld {
    enum {
        FIELD_ACTION_WALK = 0,
        FIELD_ACTION_SHIP = 1,
        FIELD_ACTION_RURA = 2,
        FIELD_ACTION_RANA = 3,
        FIELD_ACTION_TABI = 4,
        FIELD_ACTION_CASTLE = 5,
        FIELD_ACTION_CARPET = 6,
        FIELD_ACTION_DRAGON = 7,
        FIELD_ACTION_LAST = 7,
    };

    struct FieldPlayer : cmn::PlayerAction {
        enum FIELD_MOVE_TYPE {
            MOVE_WALK = 0,
            MOVE_SHIP = 1,
            MOVE_RURA = 2,
            MOVE_WAIT = 3,
        };

        int actionIndex_;                               // 0x00C
        FieldActionBase* fieldAction_[8];               // 0x010
        FieldActionWalk fieldActionWalk_;               // 0x030
        FieldActionShip fieldActionShip_;               // 0x044
        FieldActionRura fieldActionRura_;               // 0x060
        FieldActionCarpet fieldActionCarpet_;           // 0x088
        FieldActionCastle fieldActionCastle_;           // 0x0A8
        FieldActionDragon fieldActionDragon_;           // 0x0C8
        FieldActionRana fieldActionRana_;               // 0x0F8
        FieldActionTabi fieldActionTabi_;               // 0x114

        FieldPlayer();
        ~FieldPlayer();
        void setup();
        void cleanup();
        void execute();
        bool update();
        virtual void execMove();
        virtual void execCollision();
        bool search();
        void setMoveType(int type);
        FieldActionShip& getActionShip();
        int getMoveType();
        FieldActionCarpet& getActionCarpet();
    };
}
