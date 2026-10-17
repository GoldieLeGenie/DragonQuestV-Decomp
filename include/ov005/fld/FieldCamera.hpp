#pragma once
#include <globaldefs.h>
#include "main/dss/Camera.hpp"

namespace fld
{
    struct FieldCamera {
        dss::UnkDualCamera camera_;             // 0x000

        FieldCamera();
        ~FieldCamera();
        static FieldCamera& getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
    };
} // namespace fld
