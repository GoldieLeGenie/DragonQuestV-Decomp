#pragma once
#include <globaldefs.h>
#include "main/dss/Camera.hpp"

namespace book
{
    struct BookCamera {
        static const short DIR_OFFSET;
        static const short FOV;

        UnkCamera camera_;                      // 0x00

        BookCamera();
        ~BookCamera();
        static BookCamera& getSingleton();
        void initialize();
        void terminate();
        void draw();
        void setInitTarget();
        dss::Camera& getCamera();
    };
} // namespace book
