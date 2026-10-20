#pragma once
#include <globaldefs.h>
#include "main/dss/TextureBillboard.hpp"
#include "main/data/DataObject.hpp"

namespace twn {
    // billboard texture coordinates given as four corners
    struct UnkBillboardTexCorners : UnkBillboardTexCoord {
        UnkBillboardTexCorners(const dss::Vector2<dss::Fix32>& v0, const dss::Vector2<dss::Fix32>& v1,
                               const dss::Vector2<dss::Fix32>& v2, const dss::Vector2<dss::Fix32>& v3);
    };
}

struct BillboardItem : TextureBillboard {
    DataObject unk_b8;                          // 0xB8 texture file

    BillboardItem();
    ~BillboardItem();
    virtual void draw();
    void unkfunc_0214e840(const char* filename);                   // load a single icon texture
    void unkfunc_0214e8a0(const UnkBillboardVertex* vertex);       // setVertex
    void unkfunc_0214e8a8(const UnkBillboardTexCoord* texCoord);   // setTexCoord
    void unkfunc_0214e8b0(const char* filename, int index);        // load the icon `index` of an icon sheet
    void cleanup();
};
