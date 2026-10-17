#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/fld/MapLink.hpp"

namespace util {
    struct StageLink {
        static DataObject mapLinkData_;
        static CMapLink mapLink_;
        static int townExitIndex_;
        static int fieldSymbolIndex_;

        static void initialize();
        static int getNameId(int id, int exit);
        static int getSymbolIndex();
        static void setTownExitIndex(int index);
        static void resetTownExitIndex();
        static int getTownExitIndex();
        static void setFieldSymbolIndex(int index);
        static int getFieldSymbolIndex();
    };
}
