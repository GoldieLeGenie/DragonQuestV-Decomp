#pragma once
#include <globaldefs.h>
#include "main/dss/UnkPolygonObject.hpp"

// shadow volume: quad (draw) or 8 quads (unkfunc_0204748c) drawn as shadow polygons
/* vtable 0x020c447c */
struct UnkShadowPolygon : UnkPolygonObject {
    virtual void draw();                        // 0x020839bc
    virtual void unkfunc_0204748c();            // draw unk_84

    UnkPolygonVertex unk_84[8];                    // 0x84

    void unkfunc_02047670(int index, const UnkPolygonVertex* vertex);
};
