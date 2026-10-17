#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace twn {
    struct PanelData {
        static const int PANEL_LINK_MAX_NUM = 3;

        unsigned short uid_;                        // 0x00
        unsigned short panelID_;                    // 0x02
        dss::Fix32Vector3 pos_;                     // 0x04
        PanelData* link_[PANEL_LINK_MAX_NUM];       // 0x10
        PanelData* reverce_[PANEL_LINK_MAX_NUM];    // 0x1C
        PanelData* loopPanel_;                      // 0x28
        unsigned short warpMapNo_;                  // 0x2C
        unsigned short warpUid_;                    // 0x2E
        unsigned short attr_;                       // 0x30

        unsigned short getUid();
        unsigned short getPanelID();
        void setPanelID(unsigned short id);
        PanelData* getLinkPanel(int no);
        PanelData* getRevercePanel();
        PanelData* getBackPanel2();
        PanelData* getLoopPanel();
        unsigned short getPanelAttr();
        unsigned short getWarpMapNo();
        unsigned short getWarpPanelUid();
        void setReverce(PanelData* panel);
        PanelData* getBackPanel1();
        dss::Fix32Vector3& getPos();
        void setPos(dss::Fix32Vector3& pos);
        void setRoopData(PanelData* panel);
        void setData(unsigned short uid, unsigned short panelID, unsigned short attr, unsigned short warpMapNo, unsigned short warpUid);
        void pushLinkPanel(int no, PanelData* panel);
        void setBack(PanelData* panel);
        void clear();
    };
}
