#pragma once
#include <globaldefs.h>

namespace window {
    /* vtable 0x02094328 */
    class ImageMap {
    public:
        ImageMap();
        ~ImageMap();
        virtual void open() = 0;
        virtual void close() = 0;
        virtual bool isOpen() = 0;
        virtual bool isClose() = 0;
        virtual int isEnable();
        virtual void openBlack();
        virtual void closeBlack();
        virtual void cleanup();
    };
}
