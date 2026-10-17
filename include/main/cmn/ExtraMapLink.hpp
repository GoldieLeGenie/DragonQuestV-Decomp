#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace cmn
{
    enum LINK_TYPE {
        LINK_DEFAULT = 0,
        LINK_TOWN_TO_TOWN = 1,
        LINK_TOWN_TO_FIELD = 2,
        LINK_FIELD_TO_TOWN = 3,
        NOT_LINK_THIS_TOWN = 4,
        LINK_EXTRA_TOWN = 5,
        EXIT_TOWN = 6,
        RECT_FIELD_TO_TOWN = 7,
        RECT_FIELD_TO_WORLD = 8,
        RECT_FIELD_TO_YAMI = 9,
        RECT_FIELD_TO_GOT = 10,
        LINK_FIELD_ABS_POS = 11,
        BLOCK_FIELD_SYMBOL = 12,
        LINK_TOWN_OFFSET = 13,
        LINK_TOWN_TO_TOWN_OFFSET = 14,
    };

    struct MAP_LINK_DATA {
        int nowId;                              // 0x00
        int nextId;                             // 0x04
        dss::Fix32Vector3 offsetData;           // 0x08
        int fieldType;                          // 0x14
        LINK_TYPE type;                         // 0x18
        int nowMapNameId;                       // 0x1C
        int nextMapNameId;                      // 0x20
    };

    struct RECT_LINK_DATA {
        int type;                               // 0x00
        int nowId;                              // 0x04
        int nextId;                             // 0x08
        int nextMapNameId;                      // 0x0C
        dss::Fix32Vector3 pos[3];               // 0x10
    };

    struct WAP_LINK_DATA {
        int surface;                            // 0x00
        int nextId;                             // 0x04
        int nextMapNameId;                      // 0x08
    };

    struct ExtraMapLink {
        static const int LINK_DATA_COUNT = 10;
        static const int RECT_LINK_COUNT = 5;
        static const int WARP_COUNT = 8;

        int mapLinkDataCount_;                  // 0x000
        int rectLinkCount_;                     // 0x004
        MAP_LINK_DATA mapLinkData_[LINK_DATA_COUNT]; // 0x008
        RECT_LINK_DATA rectLinkData_[RECT_LINK_COUNT]; // 0x170
        WAP_LINK_DATA warp_[WARP_COUNT];        // 0x274
        int extraLinkNo_;                       // 0x2D4
        int extraLink_;                         // 0x2D8
        int nextId_;                            // 0x2DC
        dss::Fix32Vector3 offset_;              // 0x2E0
        dss::Fix32Vector3 extraPos_;            // 0x2EC
        short extraIdx_;                        // 0x2F8
        int offsetFlag_;                        // 0x2FC
        int soratobu_;                          // 0x300
        dss::Fix32Vector3 posTopLeft_;          // 0x304
        dss::Fix32Vector3 posBottomRight_;      // 0x310

        void setup();
        void setExtraFieldPos(dss::Fix32Vector3& pos, short& idx);
        int checkFieldLink(int id);
        bool checkExtraTownPos(dss::Fix32Vector3& pos, short& idx);
        void setExtraExitTown(int mapNameId, int id);
        void setExtraLinkTown(int mapNameId, dss::Fix32Vector3& pos, short dir);
        void setLinkData(int nowId, int nextId, LINK_TYPE type, int nowMapNameId, int nextMapNameId, dss::Fix32Vector3& offset);
        void setLinkData(int nowId, int nextId, LINK_TYPE type, int nowMapNameId, int nextMapNameId);
        int checkTownMapLink(int id);
        void setExtraExitField(int id, dss::Fix32Vector3& pos);
        void setTownINN();
        void setMonstarBookLink();
        int getFieldTypeBySurface(int surface);
        void eraseSurface(int surface, LINK_TYPE type, int mapNameId);
        int getFieldTypeBySymbol(int symbol);
        int checkFieldRectLinkNo(dss::Fix32Vector3& pos);
        int checkFieldRectLinkByType(dss::Fix32Vector3& pos, int type);
        bool checkEraseSymbolNo(int id);
        void setExtraLinkFieldAbsPos(int fieldType, dss::Fix32Vector3& pos, short dir);
        void setRuraLink();
        void setRanaLink();
        void setData(int index, int nowId, int nextId, LINK_TYPE type, int nowMapNameId, int nextMapNameId, dss::Fix32Vector3& offset);
        bool checkWarp(int surface);
        void setFieldTabi(int id);
        bool checkFieldToTownTabi(int id);
        void setSoratobu();
    };

    extern ExtraMapLink g_extraMapLink;
} // namespace cmn
