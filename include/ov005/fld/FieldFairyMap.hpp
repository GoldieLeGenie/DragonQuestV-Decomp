#pragma once
#include <globaldefs.h>
#include "ov005/fld/FieldRegionMap.hpp"

namespace fld
{
    struct FieldFairyMap : FieldRegionMap {
        FieldFairyMap();
        ~FieldFairyMap();
        virtual void setup();
    };
} // namespace fld
