#pragma once
#include <globaldefs.h>
#include "main/dss/PolygonObject.hpp"
#include "main/data/DataObject.hpp"
#include "main/object/DSSAObject.hpp"

namespace twn {
    // sugoroku board panels
    struct TownSugorokuDraw {
        static const int PANEL_TYPE_MAX = 70;

        PolygonObject polygon_;                  // 0x000
        DataObject data_;                           // 0x084
        void* texture_;                             // 0x094
        UnkPolygonVertex xy_;                       // 0x098
        UnkBillboardTexCoord uv_[PANEL_TYPE_MAX];   // 0x0B0

        TownSugorokuDraw();
        ~TownSugorokuDraw();
        void unkfunc_0214d3ac(const UnkPolygonVertex* xy);              // load the panel texture
        void unkfunc_0214d568(int type, dss::Fix32Vector3& pos);        // draw one panel
        void cleanup();
    };

    // dice animation
    struct TownSugorokuDice {
        static const int DICE_ANIM_MAX = 12;

        DataObject diceData_;                       // 0x000
        void* texture_;                             // 0x010
        DSSAObject2D diceAnim_[DICE_ANIM_MAX];      // 0x014
        int enable_;                                // 0x764
        int number_;                                // 0x768

        TownSugorokuDice();
        ~TownSugorokuDice();
        void setup();
        void throwIn(int number);
        bool isFinish();
        void draw();
        void drawNumber(int number);
        void cleanup();
    };

    // direction arrow
    struct TownSugorokuArrow {
        static const int ARROW_ANIM_MAX = 6;

        int counter_;                               // 0x000
        dss::Vector3<unsigned short> rot_;          // 0x004
        int animFrame_;                             // 0x00C
        PolygonObject polygon_;                  // 0x010
        DataObject arrowData_;                      // 0x094
        void* texture_;                             // 0x0A4
        UnkPolygonVertex xy_;                       // 0x0A8
        UnkBillboardTexCoord uv_[ARROW_ANIM_MAX];   // 0x0C0

        TownSugorokuArrow();
        ~TownSugorokuArrow();
        void setup(const UnkPolygonVertex* xy);
        void draw(dss::Fix32Vector3& pos);
        void cleanup();
        void setRotate(unsigned short rot);
    };
}
