#pragma once
#include <globaldefs.h>
#include "main/cmn/ResourceStorage.hpp"
#include "ov001/town/riseup/BillboardItem.hpp"

namespace twn {
    struct BillbordItemResource : cmn::ResourceStorage {
        static const unsigned int RESOURCE_ITEM_MAX = 32;

        BillboardItem m_item[RESOURCE_ITEM_MAX];    // 0x80C

        BillbordItemResource();
        ~BillbordItemResource();
        virtual void initialize();
        virtual void terminate();
        BillboardItem* getResource(int id);
        virtual int loadResource(int id);
        virtual void releaseResource(int id);
    };
}
