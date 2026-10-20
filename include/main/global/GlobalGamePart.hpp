#pragma once
#include <globaldefs.h>
#include "main/global/UnkGlobalSystem.hpp"

enum GAME_PART {
    MENU_PART = 0,
    TITLE_PART = 1,
    LOGO_PART = 2,
    GAME_START_PART = 3,
    TOWN_PART = 4,
    BATTLE_PART = 5,
    FIELD_PART = 6,
    CASINO_PART = 7,
    BOOK_PART = 8,
    SLIME_RACE_PART = 9,
    SLIME_TOUCH_PART = 10,
    CEREMONY_PART = 11,
    MAP_VIEWER_PART = 12,
    CHARACTER_VIEWER_PART = 13,
    FLD_VIEWER_PART = 14,
    SSA_VIEWER_PART = 15,
    CHR_VIEWER_PART = 16,
    FIELD_VIEWER_PART = 17,
    CARDCHECK_PART = 18,
    GAME_END_PART = 19,
    BATTLE_MENU_PART = 20,
    MACADDRESS_PART = 21,
    MPEXCHANGE_PART = 22,
    IMATEST_PART = 23,
    FUKAYATEST_PART = 24,
    SHIKATATEST_PART = 25,
    NONE_PART = 26,
    END_PART = 27,
};

namespace args {
    // Base of the game parts (BattlePart, FieldPart, TownPart...): the UnkGlobalSystem task, the UnkGameTask slots call
    // the part virtuals
    struct GamePart : UnkGameTask {
        virtual void vf00();
        virtual void vf04();
        virtual void vf08();
        virtual void vf0c();
        virtual void vf10();
        virtual void initialize();
        virtual void terminate();
        virtual void onExecutePart();
        virtual void onDrawPart();
        virtual void onWindowPart();
        virtual void onDebugPart();
        virtual void onSwapBuffersPart();

        int unkfunc_02067ac0();                 // execute the part (no extra menu)
    };
}

// Parts run every frame on top of the current game part (fade, wait, debug menu...)
struct UnkGlobalPart {
    virtual void update();
    virtual void draw();
    virtual int isEnd();
};

struct GlobalGamePartManager {
    UnkGlobalPart* part_[8];                    // 0x00

    GlobalGamePartManager();
    ~GlobalGamePartManager();
    void unkfunc_02051908();                    //
    void unkfunc_02051958();                    //
    void unkfunc_020519a8(UnkGlobalPart* part);    // add
    void unkfunc_020519cc(UnkGlobalPart* part);    // remove
};

extern GlobalGamePartManager data_02101d14;
extern int data_0209aea0;

void unkfunc_02067b00(void (*callback)());       // set the per-frame callback

extern "C" {
    void ov000_entry(void);                     // called by the parts right after loading the overlay
    void ov001_entry(void);                     // idem ov001
    void ov004_entry(void);                     // idem ov004
    void ov005_entry(void);                     // idem ov005
    void ov006_entry(void);                     // idem ov006
    void ov009_entry(void);                     // idem ov009
    void ov012_entry(void);                     // idem ov012
    void ov018_entry(void);                     // idem ov018
    void ov019_entry(void);                     // idem ov019
}
