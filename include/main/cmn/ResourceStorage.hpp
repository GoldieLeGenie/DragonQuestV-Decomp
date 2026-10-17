#pragma once
#include "globaldefs.h"

namespace cmn {
    struct ResourceStorage {
        static const unsigned int RESOURCE_MAX = 256;

        unsigned int maxStorage_;                   // 0x004
        int refCounter_[RESOURCE_MAX];              // 0x008
        int index_[RESOURCE_MAX];                   // 0x408
        int counter_;                               // 0x808

        ResourceStorage();
        ~ResourceStorage();
        virtual void initialize();
        virtual void terminate();
        void restoreResource(int id);
        int getRefCounter(int id);
        int getResource(int id);
        virtual int loadResource(int id) = 0;
        virtual void releaseResource(int id) = 0;
        int getEmptyArea();
        int getResourceArea(int id);
    };
}
