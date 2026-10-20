#pragma once
#include <globaldefs.h>
#include "main/dss/RenderObject.hpp"

struct UnkPolygonVertex {
    dss::Vector3<dss::Fix16> v[4];
};

/* vtable 0x020c4440 */
struct PolygonObject : UnkRenderObject3D {
    virtual void draw();                        // 0x0208383c

    UnkPolygonVertex vertex_;                      // 0x48
    UnkBillboardTexCoord texCoord_;                // 0x60
    dss::Vector3<char> unk_80;                  // 0x80 color (r, g, b)

    void unkfunc_0204709c(const UnkPolygonVertex* vertex);         // setVertex
    void unkfunc_02047138(const UnkBillboardTexCoord* texCoord);   // setTexCoord
    void unkfunc_020471b0();                                    // draw the textured quad
};
