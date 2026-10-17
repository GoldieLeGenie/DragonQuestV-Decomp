#pragma ipa file
#include "ov019/commonmenu/CommonMenu_Dummy.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"

static UnkMenuParts s_parts[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x40, 0x48, 0x78, 0x28 },
    { 0x0d, 0x09, (short)0xf100, 0, 0x53, 0x50, 0x58, 0x10 },
    { 0x0d, 0x09, (short)0xf100, 1, 0x50, 0x5a, 0x58, 0x0e },
    { 0xff, 0, 0, 0, 0, 0, 0, 0 },
};

THUMB void CommonMenu_Dummy::menuSetup()
{
    mapInfo_ = 0;
}

THUMB void CommonMenu_Dummy::menuExecute()
{
}

THUMB void CommonMenu_Dummy::menuDraw()
{
    if (mapInfo_ != 0) {
        int param[2] = {0};
        for (int i = 0; i < 2; i++) {
            param[i] = 0;
        }
        param[0] = (int)"\xff\xfe\xac\x24";
        if (mapInfo_ == 1) {
            param[1] = 0xe00001c2;
        }
        if (mapInfo_ == 2) {
            param[1] = 0xe00001c3;
        }
        unkfunc_0206297c(s_parts, param);
    }
}

THUMB void CommonMenu_Dummy::menuUpdate()
{
}

THUMB void CommonMenu_Dummy::setMapInfo(int mapInfo)
{
    if (mapInfo == 0) {
        close();
    } else {
        open();
        redraw_ = 1;
    }
    mapInfo_ = mapInfo;
}
