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
    dss::Vector3<char> color_;                  // 0x80 color (r, g, b)

    void setVertex(const UnkPolygonVertex* vertex);         // setVertex
    void setTexCoord(const UnkBillboardTexCoord* texCoord);   // setTexCoord
    void drawQuad();                                    // draw the textured quad
};
