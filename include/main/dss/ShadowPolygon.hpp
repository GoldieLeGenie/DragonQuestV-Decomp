#pragma once
#include <globaldefs.h>
#include "main/dss/PolygonObject.hpp"

// shadow volume: quad (draw) or 8 quads (drawVolume) drawn as shadow polygons
/* vtable 0x020c447c */
struct ShadowPolygon : PolygonObject {
    virtual void draw();                        // 0x020839bc
    virtual void drawVolume();            // draw volumeVertex_

    UnkPolygonVertex volumeVertex_[8];                    // 0x84

    void setVolumeVertex(int index, const UnkPolygonVertex* vertex);
};
