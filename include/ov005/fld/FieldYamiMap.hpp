#pragma once
#include <globaldefs.h>
#include "ov005/fld/FieldRegionMap.hpp"

namespace fld
{
    struct FieldYamiMap : FieldRegionMap {
        FieldYamiMap();
        ~FieldYamiMap();
        virtual void setup();
    };
} // namespace fld
