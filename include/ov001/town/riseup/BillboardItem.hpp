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
    DataObject data_;                          // 0xB8 texture file

    BillboardItem();
    ~BillboardItem();
    virtual void draw();
    void loadIconTexture(const char* filename);                   // load a single icon texture
    void setItemVertex(const UnkBillboardVertex* vertex);       // setVertex
    void setItemTexCoord(const UnkBillboardTexCoord* texCoord);   // setTexCoord
    void loadSheetIcon(const char* filename, int index);        // load the icon `index` of an icon sheet
    void cleanup();
};
