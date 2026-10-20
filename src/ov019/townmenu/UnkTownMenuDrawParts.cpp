#pragma ipa file
#include "ov019/townmenu/UnkTownMenuDrawParts.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/town_item/TownMenuItemUseManager.hpp"
#include "ov019/townmenu/town_status/TownMenu_STATUS.hpp"
#include "ov019/commonmenu/UnkMenuDrawText.hpp"
#include "main/cmn/CommonRuraData.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/global/Global.hpp"
#include "main/menu/MenuDataCommon.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/ShopList.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseItem.hpp"

using menu::MenuDataCommon;
using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

#define PARTS_END {0xff, 0x00, 0x0000, 0, 0x00, 0x00, 0x00, 0x00}

static UnkMenuParts s_parts_0217f7e0[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x50, 0x18, 0x18, 0x08},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f7fc[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x14, 0x54, 0x60, 0x0e},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f674[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x00, 0x00, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f8a4[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x08, 0x2c, 0xf8, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f690[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x80, 0xa0, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f850[] = {
    {0x11, 0x00, 0x0000, 0, 0x00, 0x00, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f6c8[] = {
    {0x15, 0xb5, 0x0000, 0, 0x00, 0x00, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fa2c[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x76, 0x00, 0x20, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0xd4, 0x00, 0x20, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f8dc[] = {
    {0x0e, 0x08, (short)0xf000, 0, 0x08, 0x78, 0xf0, 0x1c},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f888[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x02, 0x40, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f620[] = {
    {0x0e, 0x08, (short)0xf000, 0, 0x08, 0x78, 0xc0, 0x1c},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fa80[] = {
    {0x0e, 0x08, (short)0xf000, 0, 0x04, 0x08, 0x40, 0x18},
    {0x0c, 0xf0, 0x0000, 1, 0x48, 0x00, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f8c0[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x02, 0x60, 0x0e},
    PARTS_END,
};

static const int s_tactics_0217dd60[6] = {
    (int)0x90000001, (int)0x90000002, (int)0x90000005, (int)0x90000003, (int)0x90000004, (int)0x90000006,
};

static int s_titles_0217f5d8[4] = {(int)0xe000015f, (int)0xe0000161, (int)0xe0000162, (int)0xe0000163};

static UnkMenuParts s_parts_0217f6e4[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x30, 0x08},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f930[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x10, 0x00, 0x78, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x80, 0x00, 0x70, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f5e8[] = {
    {0x11, 0x00, 0x0000, 0, 0x00, 0x00, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f6ac[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x02, 0x4c, 0x0e},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fad4[] = {
    {0x14, 0xc0, 0x0000, -1, 0x00, 0x08, 0x68, 0x18},
    {0x0e, 0x08, (short)0xf000, 0, 0x04, 0x08, 0x48, 0x18},
    {0x0c, 0xf0, 0x0000, 1, 0x48, 0x00, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f770[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x38, 0x28, 0x98, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f604[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x14, 0x54, 0x60, 0x0e},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f8f8[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x94, 0x52, 0x48, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f63c[] = {
    {0x0e, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x38, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f71c[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x30, 0x08},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f658[] = {
    {0x07, 0x00, (short)0xf000, 17, 0x08, 0x00, 0x30, 0x08},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f914[] = {
    {0x14, 0xc0, 0x0000, -1, 0x00, 0x08, 0x68, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f95a[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x80, 0xa0, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x98, 0xa0, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fc08[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x80, 0xa0, 0x0c},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x98, 0x48, 0x0c},
    {0x0d, 0x08, (short)0xf000, 2, 0x08, 0xa8, 0x28, 0x0c},
    {0x0f, 0x0a, (short)0xf000, 3, 0x30, 0xa8, 0x20, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f700[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x0c, 0x54, 0x00, 0x0e},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f738[] = {
    {0x07, 0x00, (short)0xf000, 17, 0x08, 0x00, 0x30, 0x08},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f984[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x10, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f9ae[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x80, 0xa0, 0x0c},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x98, 0x48, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f754[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x50, 0xaa, 0x48, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f834[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x08, 0x00, 0xe8, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f78c[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x18, 0x72, 0x50, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f9d8[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x02, 0x58, 0x10},
    {0x0d, 0x0a, (short)0xf000, 1, 0x60, 0x02, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f7c4[] = {
    {0x0f, 0x09, (short)0xf000, 0, 0x00, 0x03, 0x20, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fa02[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x00, 0x58, 0x20},
    {0x07, 0x00, (short)0xf000, 25, 0x50, 0x08, 0x08, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fe8c[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x0a, 0x80, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x0c, 0x1a, 0x10, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x18, 0x1a, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x08, 0x32, 0x80, 0x10},
    {0x0d, 0x0a, (short)0xf000, 4, 0xc8, 0x32, 0x0c, 0x10},
    {0x0f, 0x0a, (short)0xf000, 5, 0xb0, 0x32, 0x44, 0x10},
    {0x0c, 0xf0, 0x0000, 6, 0xd8, 0x04, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f818[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x38, 0x18, 0x0e, 0x0e},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f86c[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x18, 0x00, 0x80, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fc94[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x0a, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 1, 0x10, 0x0a, 0x20, 0x0a},
    {0x0d, 0x08, (short)0xf000, 2, 0x30, 0x0a, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 3, 0x30, 0x0a, 0x20, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fa56[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x3c, 0x22, 0x68, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0xa8, 0x22, 0x28, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217faaa[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0xaa, 0x80, 0x10},
    {0x0d, 0x0a, (short)0xf000, 1, 0x88, 0xaa, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fb44[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x1f, 0x27, 0x18, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x10, 0x10},
    {0x0f, 0x0a, (short)0xf000, 2, 0x28, 0x27, 0x18, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fb7c[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x0c, 0x00, 0x0a, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x0a, 0x10},
    {0x0f, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x0a, 0x10},
    {0x0c, 0xf4, 0x0000, 3, 0x10, 0x08, 0x18, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fbc2[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x10, 0x98, 0x90, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0xa8, 0x98, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x10, 0xa8, 0x90, 0x10},
    {0x0f, 0x0a, (short)0xf000, 3, 0xa8, 0xa8, 0x40, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fcda[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x12, 0x00, 0x12, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x12, 0x10},
    {0x0f, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x12, 0x10},
    {0x0c, 0xf4, 0x0000, 3, 0x28, 0x08, 0x18, 0x18},
    {0x0c, 0xf4, 0x0000, 4, 0x08, 0x08, 0x18, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fefc[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x0a, 0x80, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x0c, 0x1a, 0x10, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x18, 0x1a, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x08, 0x32, 0x80, 0x10},
    {0x0f, 0x0a, (short)0xf000, 4, 0xa8, 0x32, 0x1c, 0x10},
    {0x0d, 0x0a, (short)0xf000, 5, 0xc8, 0x32, 0x0c, 0x10},
    {0x0f, 0x0a, (short)0xf000, 6, 0xb0, 0x32, 0x44, 0x10},
    {0x0c, 0xf0, 0x0000, 7, 0xd8, 0x04, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fe2a[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x10, 0x00, 0x50, 0x10},
    {0x0f, 0x09, (short)0xf000, 1, 0x70, 0x00, 0x10, 0x10},
    {0x0f, 0x09, (short)0xf000, 2, 0x88, 0x00, 0x10, 0x10},
    {0x0f, 0x09, (short)0xf000, 3, 0xa0, 0x00, 0x10, 0x10},
    {0x0f, 0x09, (short)0xf000, 4, 0xb8, 0x00, 0x10, 0x10},
    {0x0f, 0x09, (short)0xf000, 5, 0xd0, 0x00, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fd2e[] = {
    {0x0c, 0xf4, 0x0000, 0, 0x08, 0x08, 0x18, 0x18},
    {0x0f, 0x08, (short)0xf000, 1, 0x24, 0x12, 0x08, 0x08},
    {0x0d, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x08, 0x08},
    {0x0f, 0x0b, (short)0xf000, 3, 0x00, 0x00, 0x08, 0x08},
    {0x0c, 0xf4, 0x0000, 4, 0x40, 0x08, 0x18, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fb0c[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x80, 0xa0, 0x0c},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x98, 0xa0, 0x0c},
    {0x0d, 0x08, (short)0xf000, 2, 0x08, 0xa8, 0xa0, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fd82[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x0a, 0x80, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x0c, 0x1a, 0x10, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x18, 0x1a, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x08, 0x32, 0x80, 0x10},
    {0x0c, 0xf0, 0x0000, 4, 0xd8, 0x04, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_0217ff7a[] = {
    {0x14, 0xc0, 0x0000, -1, 0x00, 0x00, 0x70, 0x38},
    {0x0c, 0xf1, 0x0000, 0, -4, 0x10, 0x20, 0x20},
    {0x0d, 0x08, (short)0xf000, 1, 0x1c, 0x03, 0x50, 0x10},
    {0x0d, 0x09, (short)0xf000, 2, 0x1c, 0x10, 0x10, 0x10},
    {0x0d, 0x09, (short)0xf000, 3, 0x44, 0x10, 0x10, 0x10},
    {0x0d, 0x09, (short)0xf000, 4, 0x1c, 0x1a, 0x10, 0x10},
    {0x0d, 0x09, (short)0xf000, 5, 0x44, 0x1a, 0x10, 0x10},
    {0x0f, 0x0a, (short)0xf000, 6, 0x30, 0x10, 0x18, 0x10},
    {0x0f, 0x0a, (short)0xf000, 7, 0x50, 0x10, 0x18, 0x10},
    {0x0f, 0x0a, (short)0xf000, 8, 0x30, 0x1a, 0x18, 0x10},
    {0x0f, 0x0a, (short)0xf000, 9, 0x50, 0x1a, 0x18, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fc4e[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x30, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x00, 0x10, 0x10, 0x10},
    {0x0d, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x10, 0x10},
    {0x0f, 0x0b, (short)0xf000, 3, 0x00, 0x00, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217f7a8[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x1f, 0x27, 0x30, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0217fdd6[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x80, 0xa0, 0x0c},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x98, 0x48, 0x0c},
    {0x0f, 0x0a, (short)0xf000, 2, 0x08, 0xa8, 0x18, 0x0c},
    {0x0d, 0x08, (short)0xf000, 3, 0x28, 0xa8, 0x10, 0x0c},
    {0x0f, 0x0a, (short)0xf000, 4, 0x30, 0xa8, 0x20, 0x0c},
    PARTS_END,
};

THUMB void drawRootMenuButtonFrames(int x, int y, int flag)
{
    if (flag != 0) {
        for (int i = 0; i < 6; i++) {
            drawMenuFrame((i % 2) * 0x48 + 0x40, (i / 2) * 0x20 + 0x60, 0x48, 0x20, -1);
        }
    } else {
        drawMenuFrame(x, y, 0x48, 0x20, -1);
    }
}

THUMB void drawRootMenuCommands(int type, int sub)
{
    UnkMenuParts kindPart = {0x0c, 0xf4, 0x0000, 0, 0x00, 0x00, 0x18, 0x18};
    UnkMenuParts namePart = {0x0d, 0x08, (short)0xf100, 0, 0x04, 0x00, 0x30, 0x0c};
    int name = 0;
    int kind = 0;
    if (type == -1) {
        for (int i = 0; i < 6; i++) {
            kind = getRootMenuKind(i);
            name = getRootMenuName(i);
            drawMenuPartAt(&kindPart, &kind, (i % 2) * 0x48 + 0x68, (i / 2) * 0x20 + 0x60);
            drawMenuPartAt(&namePart, &name, (i % 2) * 0x48 + 0x44, (i / 2) * 0x20 + 0x6a);
        }
        return;
    }
    TownMenuPlayerControl::getSingleton();
    kind = getRootMenuKind(type);
    name = getRootMenuName(type);
    if (sub != -1) {
        drawMenuPartAt(&kindPart, &kind, sub + 0x28, 0xa0);
        drawMenuPartAt(&namePart, &name, sub + 4, 0xaa);
        return;
    }
    drawMenuPartAt(&kindPart, &kind, 0x68, 0xa0);
    drawMenuPartAt(&namePart, &name, 0x44, 0xaa);
    drawTownCommandCursor(0x40, 0xb0);
}

THUMB void drawPartyMemberIcon(int chara, int x, int y)
{
    drawCharaIconWithCondition(chara, x, y);
}

THUMB void drawCharaItemNameList(int chara)
{
    setMenuDrawOffset(0, 0);
    int count = MenuStatusInfo::getPlayerItemCount(chara);
    int x;
    int y;
    for (int i = 0; i < count; i++) {
        x = (i % 2) * 0x78;
        y = (i / 2) * 16;
        int param = MenuStatusInfo::getPlayerItemID(chara, i) + 0x40000000;
        if (MenuStatusInfo::isPlayerEquipItemIndex(chara, i) == true) {
            int equip = (int)0xe000003c;
            drawMenuParts(s_parts_0217f700, &equip, x, y + 6, data_02094dd4[0]);
        }
        drawMenuParts(s_parts_0217f604, &param, x, y + 6, data_02094dd4[0]);
    }
}

THUMB void drawBagItemNameList()
{
    setMenuDrawOffset(0, 0);
    int pageCount = 1;
    int page = 0;
    if (MenuStatusInfo::getFukuroItemCount() > 6) {
        pageCount = 2;
    }
    for (int n = 0; n < pageCount; n++) {
        int count = MenuStatusInfo::getFukuroItemCountInPage(page);
        for (int i = 0; i < count; i++) {
            int param = MenuStatusInfo::getFukuroItemID(i, page) + 0x40000000;
            drawMenuParts(s_parts_0217f7fc, &param, (i % 2) * 0x78, (i / 2 + n * 3) * 16 + 6, data_02094dd4[0]);
        }
        page++;
    }
}

THUMB void drawActiveCharaNameBar(int chara, int a, int b, int c)
{
    int x = 0;
    int y = 0xaa;
    int name = 0;
    int color = 0;
    if (a == 1) {
        x = c + 0x88;
    }
    if (chara == -2) {
        name = 0x5000024d;
    } else if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1 && b == 0) {
        name = 0x5000024e;
    } else {
        int hp = MenuDataCommon::getStatus(chara, MenuDataCommon::NOWHP, false);
        int hpMax = MenuDataCommon::getStatus(chara, MenuDataCommon::MAXHP, false);
        int percent = hp * 100 / hpMax;
        if (percent <= 0 && hp > 0) {
            percent = 1;
        }
        if (hp != 0 && hp > hpMax / 4 - 1 && percent < 0x1a) {
            percent = 0x1a;
        }
        name = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
        y = 0xa6;
        color = getCharaTextColorIndex(chara);
        drawMenuParts(s_parts_0217f850, &percent, x, 0xb6, data_02094dd4[color]);
        drawMenuParts(s_parts_0217f658, 0, x, y, data_02094dd4[color]);
    }
    drawMenuParts(s_parts_0217f71c, &name, x, y, data_02094dd4[color]);
}

THUMB void drawTargetCharaNameBar(int chara)
{
    int y = 0xaa;
    int name = 0;
    int color = 0;
    if (TownMenuPlayerControl::getSingleton()->targetFukuro_ == 1) {
        name = 0x5000024e;
    } else {
        int hp = MenuDataCommon::getStatus(chara, MenuDataCommon::NOWHP, false);
        int hpMax = MenuDataCommon::getStatus(chara, MenuDataCommon::MAXHP, false);
        int percent = hp * 100 / hpMax;
        if (percent <= 0 && hp > 0) {
            percent = 1;
        }
        if (hp > hpMax / 4 - 1 && percent < 0x1a) {
            percent = 0x1a;
        }
        name = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
        y = 0xa6;
        color = getCharaTextColorIndex(chara);
        drawMenuParts(s_parts_0217f5e8, &percent, 0x88, 0xb6, data_02094dd4[color]);
        drawMenuParts(s_parts_0217f738, 0, 0x88, y, data_02094dd4[color]);
    }
    drawMenuParts(s_parts_0217f6e4, &name, 0x90, y, data_02094dd4[color]);
}

THUMB void drawItemSlot(int itemID, int x, int y)
{
    int param[2];
    if (itemID != -1) {
        param[0] = itemID + 0x40000000;
        param[1] = itemID;
        drawMenuParts(s_parts_0217fa80, param, x, y, data_02094dd4[0]);
    }
    drawMenuParts(s_parts_0217f914, 0, x, y, data_02094dd4[0]);
}

THUMB void drawBagItemSlot(int itemID, int index, int x, int y)
{
    int param[2];
    int count;
    param[0] = itemID + 0x40000000;
    param[1] = itemID;
    drawMenuParts(s_parts_0217fad4, param, x, y, data_02094dd4[0]);
    if (MenuStatusInfo::getFukuroItemCount(index) > 1) {
        count = MenuStatusInfo::getFukuroItemCount(index);
        drawMenuParts(s_parts_0217f7e0, &count, x, y, data_02094dd4[0]);
    }
}

THUMB void drawItemEquippedMark(int index)
{
    int param = (int)0xe000003c;
    drawMenuParts(s_parts_0217f818, &param, (index % 2 + 1) * 32 + (index % 2) * 0x58, (index / 2) * 8 + (index / 2) * 0x18, data_02094dd4[0]);
}

THUMB void drawPageIndicator(int x, int max, int page, int flag)
{
    UnkMenuParts* parts = s_parts_0217fb7c;
    int param[5] = {page + 1, (int)"\xff\xfe\xa7\x24", max + 1, 0xd, 0xc};
    if (flag == 1) {
        parts = s_parts_0217fcda;
    }
    drawMenuParts(parts, param, x, 0x78, data_02094dd4[0]);
}

THUMB void drawPageIndicatorWide(int x, int max, int page)
{
    int param[5] = {0xc, page + 1, (int)"\xff\xfe\xa7\x24", max + 1, 0xd};
    drawMenuParts(s_parts_0217fd2e, param, x, 0x78, data_02094dd4[0]);
}

THUMB void drawMenuDescription(int index, int isAction, int mode)
{
    int param = 0;
    if (isAction) {
        param = status::UseAction::getMenuMessage(index) + 0x30000000;
    } else {
        param = status::UseItem::getMenuMessage(index) + 0x20000000;
    }
    if (mode) {
        if (TownMenuPlayerControl::getSingleton()->targetItem_ == -1) {
            param = 0xcc3cf;
        } else {
            param = 0xcc3d1;
        }
    }
    drawMenuPartsColored(s_parts_0217f620, &param, data_02094dd4[0]);
}

THUMB void drawItemUsageInfo(int itemID)
{
    if (itemID != 0) {
        setMenuDrawOffset(0, 0);
        int param[2];
        param[0] = MenuDataCommon::getItemTypeMessageNo(itemID);
        param[1] = MenuDataCommon::getItemMessageNo(itemID);
        drawMenuPartsColored(s_parts_0217f95a, param, data_02094dd4[0]);
    }
}

THUMB void drawEquipCompareWindow(int chara, int itemID, int equipIndex, int fukuro, int flag, int mode)
{
    setMenuDrawOffset(0, 0);
    UnkMenuParts* parts = 0;
    int param[6] = {-1};
    for (int i = 0; i < 6; i++) {
        param[i] = -1;
    }
    if (itemID == -1) {
        UnkMenuParts* equipParts = s_parts_0217fdd6;
        int equip = getEquipSlotCompareValues(chara, equipIndex, param);
        param[0] = MenuDataCommon::getEquipKind(equipIndex);
        if (equip == 0) {
            if (equipIndex == 0) {
                param[1] = (int)0xe0000019;
            } else {
                param[1] = (int)0xe000001a;
            }
        } else {
            param[1] = MenuDataCommon::getItemMessageNo(equip);
            if (status::UseItem::getCommentType(equip) == 0xb) {
                equipParts = s_parts_0217f9ae;
            }
        }
        if (equipIndex == 4 && mode == 1) {
            param[0] = (int)0xe00000cc;
            param[1] = (int)0xe000001a;
            param[2] = (int)0xe000003c;
            equipParts = s_parts_0217fc08;
            param[3] = MenuDataCommon::getStatus(chara, MenuDataCommon::DEFENCE, false);
        }
        drawMenuPartsColored(equipParts, param, data_02094dd4[getCharaTextColorIndex(chara)]);
        return;
    }
    if (status::UseItem::getItemType(itemID) == ITEM_SPECIALTY && flag == 0) {
        param[0] = (int)0xe00000d0;
    } else {
        param[0] = MenuDataCommon::getEquipKind(status::UseItem::getEquipItemType(itemID));
    }
    param[1] = MenuDataCommon::getItemMessageNo(itemID);
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1 && fukuro == 0) {
        param[2] = 0;
        drawMenuPartsColored(s_parts_0217fb0c, param, data_02094dd4[0]);
        return;
    }
    switch (getEquipCompareValues(chara, itemID, param)) {
        case 0:
            parts = s_parts_0217fb0c;
            break;
        case 1:
            parts = s_parts_0217fdd6;
            if (status::UseItem::getCommentType(itemID) == 0xb) {
                parts = s_parts_0217f9ae;
            }
            break;
        case 2:
            parts = s_parts_0217fc08;
            if (status::UseItem::getCommentType(itemID) == 0xb) {
                parts = s_parts_0217f9ae;
            }
            break;
    }
    drawMenuPartsColored(parts, param, data_02094dd4[getCharaTextColorIndex(chara)]);
}

THUMB void drawItemUseCommands(int commandFlag)
{
    int text[6] = {-1};
    for (int i = 0; i < 6; i++) {
        text[i] = -1;
    }
    TownMenuPlayerControl::getSingleton();
    int count = 6;
    switch (commandFlag) {
        case 0:
            text[0] = unkfunc_02178c28(0);
            text[1] = unkfunc_02178c28(1);
            text[2] = unkfunc_02178c28(2);
            text[3] = unkfunc_02178c28(5);
            count = 4;
            break;
        case 1:
            text[0] = unkfunc_02178c28(0);
            text[1] = unkfunc_02178c28(1);
            text[2] = unkfunc_02178c28(2);
            text[3] = unkfunc_02178c28(3);
            text[4] = unkfunc_02178c28(5);
            count = 5;
            break;
        case 2:
            text[0] = unkfunc_02178c28(0);
            text[1] = unkfunc_02178c28(1);
            text[2] = unkfunc_02178c28(2);
            text[3] = unkfunc_02178c28(4);
            text[4] = unkfunc_02178c28(5);
            count = 5;
            break;
        case 3:
            for (int i = 0; i < 6; i++) {
                text[i] = unkfunc_02178c28(i);
            }
            break;
    }
    for (int i = 0; i < count; i++) {
        drawMenuParts(s_parts_0217f888, &text[i], (i % 3) * 0x40 + 0x10 + (i % 3) * 16, (i / 3) * 0x18 + 0x70, data_02094dd4[0]);
    }
}

THUMB void drawPartyIconRow(int mode, int flag)
{
    int w4;
    int x4;
    int w3;
    int x3;
    int w2;
    int x2;
    int w1;
    int x1;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (mode == 1) {
        int n = 0;
        int i;
        for (i = 0; i < count; i++) {
            x1 = (n % 5) * 32 + 0x10;
            w1 = (n % 5) * 8;
            int y;
            if (count < 5) {
                y = 0x70;
            } else {
                y = (n / 5) * 0x28 + 0x48;
            }
            if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_PLAYER) == true) {
                drawPartyMemberIcon(i, x1 + w1, y);
                n++;
            }
        }
        n = 0;
        for (i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT); i++) {
            x2 = (n % 5) * 32 + 0x10;
            w2 = (n % 5) * 8;
            int y;
            if (count < 5) {
                y = 0x70;
            } else {
                y = (n / 5) * 0x28 + 0x48;
            }
            if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_PLAYER) == true) {
                drawCarriageOrderNumber(i + 1, x2 + w2 - 8, y + 8, i);
                n++;
            }
        }
        if (!g_AreaFlag.check(0x82) || g_AreaFlag.check(0x84)) {
            drawPartyMemberIcon(-1, (count % 5) * 32 + 0x10 + (count % 5) * 8, 0x70);
        }
    } else {
        int i;
        for (i = 0; i < count; i++) {
            x3 = (i % 5) * 32 + 0x10;
            w3 = (i % 5) * 8;
            int y;
            if (count < 6) {
                y = 0x70;
            } else {
                y = (i / 5) * 0x28 + 0x48;
            }
            drawPartyMemberIcon(i, x3 + w3, y);
            if (flag == 0 && i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT)) {
                drawCarriageOrderNumber(i + 1, x3 + w3 - 8, y + 8, i);
            }
        }
        if (flag == 1) {
            int n = 0;
            for (i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT); i++) {
                x4 = (n % 5) * 32 + 0x10;
                w4 = (n % 5) * 8;
                int y;
                if (count < 6) {
                    y = 0x70;
                } else {
                    y = (i / 5) * 0x28 + 0x48;
                }
                if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_PLAYER) == true) {
                    drawCarriageOrderNumber(i + 1, x4 + w4 - 8, y + 8, i);
                    n++;
                }
            }
        }
    }
}

THUMB void drawCharaSummaryPanel(int chara, int index, int page)
{
    if (index == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        return;
    }
    UnkMenuParts* parts = s_parts_0217fb44;
    int param[10] = {0, 0, (int)0xe0000017, (int)"\xff\xfe\xa7\x24", (int)0xe0000018, (int)"\xff\xfe\xa7\x24", 0, 0, 0, 0};
    param[0] = MenuStatusInfo::getPlayerIconIndex(chara);
    param[1] = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
    param[6] = MenuDataCommon::getStatus(chara, MenuDataCommon::NOWHP, false);
    param[7] = MenuDataCommon::getStatus(chara, MenuDataCommon::MAXHP, false);
    param[8] = MenuDataCommon::getStatus(chara, MenuDataCommon::NOWMP, false);
    param[9] = MenuDataCommon::getStatus(chara, MenuDataCommon::MAXMP, false);
    int level[3] = {(int)0xe0000016, (int)"\xff\xfe\xa8\x24", 0};
    level[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::LEVEL, false);
    int x = (index % 2) * 0x78 + 0xc;
    int y = (index / 2) * 0x40 + 0xc;
    int condition = MenuDataCommon::getPlayerCondition(chara);
    if (condition != 0) {
        level[0] = condition;
        parts = s_parts_0217f7a8;
    }
    drawMenuParts(parts, level, x, y, data_02094dd4[getCharaTextColorIndex(chara)]);
    if (page == 0 && MenuStatusInfo::isCarriagePosition(chara, MenuStatusInfo::POSITION_CARRIAGE_OUT) == true) {
        int number = index + 1;
        drawMenuParts(s_parts_0217f7c4, &number, x, y, data_02094dd4[getCharaTextColorIndex(chara)]);
    }
    drawMenuParts(s_parts_0217ff7a, param, x, y, data_02094dd4[getCharaTextColorIndex(chara)]);
}

THUMB void drawCasterMpBar(int chara, int mp, int useMp)
{
    drawMenuPartsAt(s_parts_0217fa02, 0, 0x88, 0xa0);
    int param[4] = {(int)0xe0000018, useMp, (int)"\xff\xfe\xa7\x24", mp};
    drawMenuParts(s_parts_0217fc94, param, 0x88, 0xa0, data_02094dd4[getCharaTextColorIndex(chara)]);
}

THUMB void drawTownSpellList(int chara)
{
    setMenuDrawOffset(0, 0);
    int count = MenuStatusInfo::getPlayerActionCount(chara, MenuStatusInfo::USE_TOWN);
    int n = 0;
    for (int i = 0; i < count; i++) {
        int magicID = MenuStatusInfo::getPlayerActionID(chara, i);
        if (MenuStatusInfo::isPlayerActionUseType(magicID, MenuStatusInfo::USE_TOWN) == true) {
            int word = MenuStatusInfo::getWordDBIndex(magicID);
            drawSpellName((n % 2) * 0x80, (n / 2) * 16 + 0x74, word + 0x70000000, chara);
            n++;
        }
    }
    drawMenuFrame(0, 0x68, 0x100, 0x58, -1);
}

THUMB void drawSpellName(int x, int y, int text, int chara)
{
    int param = text;
    drawMenuParts(s_parts_0217f86c, &param, x, y, data_02094dd4[getCharaTextColorIndex(chara)]);
}

THUMB void drawRuraTownList(int page)
{
    int n = 0;
    int index = 0;
    for (int i = 1; i < cmn::CommonRuraData::maxRuraFlag; i++) {
        if (cmn::CommonRuraData::getSingleton().isEnableRura(i) == true) {
            index++;
            if (index > page * 8) {
                int name = MenuDataCommon::getRuraName(i - 1);
                drawMenuParts(s_parts_0217f8c0, &name, (n % 2) * 0x78 + 0x14, (n / 2) * 16 + 0xc + (n / 2) * 8, data_02094dd4[0]);
                n++;
                if (n > 7) {
                    break;
                }
            }
        }
    }
    int count = cmn::CommonRuraData::getSingleton().getRuraCount();
    if (count > 8) {
        drawPageIndicator(0xb8, (count - 1) / 8, page, 1);
    }
    int param = status::UseAction::getMenuMessage(0x81) + 0x30000000;
    drawMenuPartsColored(s_parts_0217f8dc, &param, data_02094dd4[0]);
}

THUMB void drawCarriageOrderNumber(int number, int x, int y, int chara)
{
    if (chara < 0) {
        drawMenuParts(s_parts_0217f674, &number, x, y, data_02094dd4[0]);
        return;
    }
    drawMenuParts(s_parts_0217f674, &number, x, y, data_02094dd4[getCharaTextColorIndex(chara)]);
}

THUMB void drawMenuHeaderText(int x, int y, int text)
{
    setMenuDrawOffset(0, 0);
    int param = text;
    drawMenuParts(s_parts_0217f834, &param, x, y, data_02094dd4[0]);
}

THUMB void drawCommandLabel(int x, int y, int text)
{
    int param = text;
    drawMenuParts(s_parts_0217f6ac, &param, x, y, data_02094dd4[0]);
}

THUMB void drawCharaTacticsRow(int chara, int x, int y)
{
    setMenuDrawOffset(0, 0);
    int tactics = MenuStatusInfo::getPlayerTactics(chara);
    int param[2];
    param[0] = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
    param[1] = s_tactics_0217dd60[tactics];
    drawMenuParts(s_parts_0217f930, param, x, y, data_02094dd4[getCharaTextColorIndex(chara)]);
}

THUMB void drawTacticsOptions()
{
    for (int i = 0; i < 6; i++) {
        int param = s_tactics_0217dd60[i];
        drawMenuParts(s_parts_0217f63c, &param, (i % 3) * 0x38 + 0x1c + (i % 3) * 8, (i / 3) * 0x18 + 8 + (i / 3) * 8, data_02094dd4[0]);
    }
}

THUMB void drawShiftPartyIconList(char* allocation, char* list, int count)
{
    int outCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        int x = (i % 5) * 32 + 0x10;
        int x2 = (i % 5) * 8;
        int y = (i / 5) * 32 + 0x68;
        int y2 = (i / 5) * 8;
        int posX = x + x2;
        int posY = y + y2;
        drawPartyMemberIcon(list[i], posX, posY);
        if (list[i] < outCount) {
            drawCarriageOrderNumber(list[i] + 1, posX - 8, posY + 8, list[i]);
        }
    }
    if (allocation[0] != -1 && MenuStatusInfo::isCarriageEnable() == true) {
        drawPartyMemberIcon(-3, (count % 5) * 32 + 0x10 + (count % 5) * 8, (count / 5) * 32 + 0x68 + (count / 5) * 8);
        return;
    }
    if (count == 0 && MenuStatusInfo::isCarriageEnable() == false) {
        drawPartyMemberIcon(-3, 0x10, 0x68);
    }
}

THUMB void unkfunc_unused_0217dd00()
{
    int param[4] = {(int)"@\x82\xd0\x82\xe5\x82\xa4\x82\xa9\x83\x7c\x83\x43\x83\x93\x83\x67", 0, (int)0xe0000145, 0};
    drawMenuPartsColored(s_parts_0217f78c, param, data_02094dd4[0]);
}

THUMB void drawShiftPartyFrontSlots(char* allocation)
{
    int param[4] = {-1};
    for (int i = 0; i < 4; i++) {
        param[i] = -1;
    }
    param[1] = (int)"\xff\xfe\xa8\x24";
    for (int i = 0; i < 4; i++) {
        param[0] = i + 1;
        drawMenuParts(s_parts_0217f984, param, (i % 2) * 64 + 8, (i / 2) * 0x30 + 8, data_02094dd4[0]);
    }
    int i = 0;
    char* p;
    for (; (p = &allocation[i], allocation[i] != -1) && i < 4; i++) {
        param[0] = MenuStatusInfo::getPlayerIndex(allocation[i]) + 0x50000000;
        param[1] = (int)0xe0000016;
        param[2] = (int)"\xff\xfe\xa8\x24";
        param[3] = MenuDataCommon::getStatus(*p, MenuDataCommon::LEVEL, false);
        drawMenuParts(s_parts_0217fc4e, param, (i % 2) * 64 + 0x18, (i / 2) * 0x30 + 8, data_02094dd4[getCharaTextColorIndex(*p)]);
    }
}

THUMB void drawOperationTitle(int type)
{
    drawMenuPartsColored(s_parts_0217f754, &s_titles_0217f5d8[type], data_02094dd4[0]);
    drawMenuFrame(0x48, 0xa0, 0x50, 0x20, -1);
}

THUMB void drawEquipListCaption(int itemType)
{
    if (itemType == 4) {
        int text[2] = {(int)0xe0000181, (int)0xe0000182};
        drawMenuPartsColored(s_parts_0217f78c, &text[0], data_02094dd4[0]);
        drawMenuParts(s_parts_0217f78c, &text[1], 0x78, 0, data_02094dd4[0]);
        return;
    }
    int param = (int)0xe0000181;
    drawMenuPartsColored(s_parts_0217f78c, &param, data_02094dd4[0]);
}

THUMB void drawSettingScreenLabels()
{
    int values[32];
    int param[32];
    int text[32];
    values[1] = 1;
    values[2] = 2;
    values[3] = 3;
    values[4] = 4;
    values[5] = 5;
    values[0] = (int)0xe00001b5;
    drawMenuParts(s_parts_0217fe2a, values, 0, 0x59, data_02094dd4[0]);
    values[0] = (int)0xe00001b3;
    drawMenuParts(s_parts_0217fe2a, values, 0, 0x76, data_02094dd4[0]);
    values[0] = (int)0xe00001b4;
    drawMenuParts(s_parts_0217fe2a, values, 0, 0x88, data_02094dd4[0]);
    param[0] = (int)0xe00001b7;
    param[1] = param[0] + 1;
    drawMenuParts(s_parts_0217fa2c, param, 0, 0x4d, data_02094dd4[0]);
    param[0] = (int)0xe00001b9;
    param[1] = param[0] + 1;
    drawMenuParts(s_parts_0217fa2c, param, 0, 0x6a, data_02094dd4[0]);
    text[0] = (int)0xe00001b6;
    drawMenuPartsColored(s_parts_0217f8a4, text, data_02094dd4[0]);
    drawMenuFrame(0, 0x20, 0x100, 0x80, 0x40);
}

THUMB void unkfunc_02172804()
{
    int param = (int)0xe000019a;
    drawMenuPartsColored(s_parts_0217f8f8, &param, data_02094dd4[0]);
    drawMenuFrame(0x90, 0x48, 0x50, 0x20, -1);
}

THUMB void drawTownCommandCursor(int x, int y)
{
    drawMenuPartsAt(s_parts_0217f6c8, 0, x, y);
}

THUMB void drawItemTargetInfo(int chara, int itemID, int flag)
{
    UnkMenuParts* parts = 0;
    int param[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 8; i++) {
        param[i] = 0;
    }
    int values[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        values[i] = 0;
    }
    param[0] = itemID + 0x40000000;
    param[1] = (int)"\xff\xfe\xaf\x24";
    if (TownMenuPlayerControl::getSingleton()->targetFukuro_ != 0) {
        param[2] = 0x5000024e;
    } else {
        param[2] = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
    }
    if ((status::UseItem::getEquipItemType(itemID) <= ITEM_ACCESSORY || menu::TownMenuItemUseManager::isEquipSpecialItem(itemID) == true)
        && TownMenuPlayerControl::getSingleton()->targetFukuro_ == 0) {
        param[3] = MenuDataCommon::getItemMessageNo(itemID);
        switch (getEquipCompareValues(chara, itemID, values)) {
            case 0:
                param[3] = values[2];
                if (flag == 0) {
                    param[4] = itemID;
                }
                parts = s_parts_0217fd82;
                break;
            case 1:
                param[4] = values[2];
                param[5] = values[3];
                param[6] = values[4];
                if (status::UseItem::getCommentType(itemID) == 0xb) {
                    if (flag == 0) {
                        param[4] = itemID;
                    }
                    parts = s_parts_0217fd82;
                } else {
                    if (flag == 0) {
                        param[7] = itemID;
                    }
                    parts = s_parts_0217fefc;
                }
                break;
            case 2:
                param[4] = values[2];
                param[5] = values[3];
                if (status::UseItem::getCommentType(itemID) == 0xb) {
                    if (flag == 0) {
                        param[4] = itemID;
                    }
                    parts = s_parts_0217fd82;
                } else {
                    if (flag == 0) {
                        param[6] = itemID;
                    }
                    parts = s_parts_0217fe8c;
                }
                break;
        }
    } else {
        if (TownMenuPlayerControl::getSingleton()->targetFukuro_ != 0) {
            if (MenuStatusInfo::isFukuroHaveItem(itemID)) {
                param[3] = (int)0xe00000e3;
            } else {
                param[3] = (int)0xe00000e4;
            }
        } else {
            if (MenuStatusInfo::isPlayerHaveItem(chara, itemID) == true) {
                param[3] = (int)0xe00000e1;
            } else {
                param[3] = (int)0xe00000e2;
            }
        }
        parts = s_parts_0217fd82;
        if (flag == 0) {
            param[4] = itemID;
        }
    }
    int y = 0;
    if (flag == 1) {
        setMenuDrawOffset(0, 0);
        y = 8;
    }
    drawMenuParts(parts, param, 0, y, data_02094dd4[0]);
}

THUMB void drawChooseCharaPrompt(int mode)
{
    int text[2] = {(int)0xe0000082, (int)"\xff\xfe\xac\x24"};
    int y = 0x58;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (mode == 1) {
        if (count + 1 > 5) {
            y = 0x30;
        }
        text[0] = (int)0xe00000a0;
    } else {
        if (count > 5) {
            y = 0x30;
        }
        if (MenuStatusInfo::isPlayerType(TownMenuPlayerControl::getSingleton()->activeChara_, MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
            text[0] = (int)0xe0000083;
        }
    }
    drawMenuParts(s_parts_0217f9d8, text, 0, y, data_02094dd4[0]);
    drawMenuFrame(0, y - 8, 0x78, 0x20, -1);
}

THUMB void drawSpellOrTownSelectPrompt(int mode)
{
    setMenuDrawOffset(0, 0);
    int text[2] = {(int)0xe0000084, (int)"\xff\xfe\xad\x24"};
    int chara = TownMenuPlayerControl::getSingleton()->activeChara_;
    if (mode == 1) {
        text[0] = (int)0xe0000086;
    } else if (MenuStatusInfo::isPlayerType(chara, MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
        text[0] = (int)0xe0000085;
    }
    drawMenuPartsColored(s_parts_0217faaa, text, data_02094dd4[0]);
    drawMenuFrame(0, 0xa0, 0xa0, 0x20, -1);
}

THUMB void drawTownShopGoods(int type)
{
    setMenuDrawOffset(0, 0);
    int shop = 2;
    int title = 0;
    int param[2] = {0, 0};
    for (int i = 0; i < 2; i++) {
        param[i] = 0;
    }
    switch (type) {
        case 0:
            title = (int)0xe00001c4;
            shop = 2;
            break;
        case 1:
            title = (int)0xe00001c5;
            shop = 3;
            break;
        case 2:
            title = (int)0xe00001c6;
            shop = 4;
            break;
        case 3:
            title = (int)0xe00001c6;
            shop = 5;
            break;
        case 4:
            title = (int)0xe00001c4;
            shop = 9;
            break;
        case 5:
            title = (int)0xe00001c5;
            shop = 0xa;
            break;
        case 6:
            title = (int)0xe00001c6;
            shop = 0xb;
            break;
        case 7:
            title = (int)0xe00001c6;
            shop = 0xc;
            break;
    }
    int count = status::g_Shop.getShopCount(shop);
    for (int i = 0; i < count; i++) {
        int item = status::g_Shop.getShopItem(shop, i);
        param[0] = item + 0x40000000;
        param[1] = status::UseItem::getBuyPrice(item);
        if (g_Global.areaNo_ == 10 && status::g_Story.getChapter() == 1 && type == 2) {
            if (i == 0) {
                param[1] = 6;
            } else {
                param[1] = 8;
            }
        }
        drawMenuParts(s_parts_0217fa56, param, 0, i * 16 + 0x20, data_02094dd4[0]);
    }
    drawMenuPartsColored(s_parts_0217f770, &title, data_02094dd4[0]);
    drawMenuFrame(0x30, 0x20, 0xa8, 0x88, 0x38);
}

THUMB int getCharaTextColorIndex(int chara)
{
    return getActorConditionColor(chara);
}

THUMB int getEquipCompareValues(int chara, int itemID, int* values)
{
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    int result = 1;
    if (!info.isEquipEnable(itemID)) {
        values[2] = (int)0xe00000de;
        return 0;
    }
    bool equip = MenuStatusInfo::isPlayerEquipItem(chara, itemID);
    values[3] = (int)"\xff\xfe\xaf\x24";
    switch (status::UseItem::getEquipType(itemID)) {
        case Strength:
            if (equip == true) {
                values[2] = (int)0xe000003c;
                values[3] = MenuDataCommon::getStatus(chara, MenuDataCommon::STRENGTH, false);
                result = 2;
            } else {
                values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::STRENGTH, false);
                values[4] = info.getChangeStrength(itemID);
            }
            break;
        case Attack:
            if (equip == true) {
                values[2] = (int)0xe000003c;
                values[3] = MenuDataCommon::getStatus(chara, MenuDataCommon::ATTACK, false);
                result = 2;
            } else {
                values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::ATTACK, false);
                values[4] = info.getChangeAttack(itemID);
            }
            break;
        case Defence:
            if (equip == true) {
                values[2] = (int)0xe000003c;
                values[3] = MenuDataCommon::getStatus(chara, MenuDataCommon::DEFENCE, false);
                result = 2;
            } else {
                values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::DEFENCE, false);
                values[4] = info.getChangeDefence(itemID);
            }
            break;
        case Agility:
            if (equip == true) {
                values[2] = (int)0xe000003c;
                values[3] = MenuDataCommon::getStatus(chara, MenuDataCommon::AGILITY, false);
                result = 2;
            } else {
                values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::AGILITY, false);
                values[4] = info.getChangeAgility(itemID);
            }
            break;
        case Wisdom:
            if (equip == true) {
                values[2] = (int)0xe000003c;
                values[3] = MenuDataCommon::getStatus(chara, MenuDataCommon::WISDOM, false);
                result = 2;
            } else {
                values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::WISDOM, false);
                values[4] = info.getChangeWisdom(itemID);
            }
            break;
        case Luck:
            if (equip == true) {
                values[2] = (int)0xe000003c;
                values[3] = MenuDataCommon::getStatus(chara, MenuDataCommon::LUCK, false);
                result = 2;
            } else {
                values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::LUCK, false);
                values[4] = info.getChangeLuck(itemID);
            }
            break;
    }
    return result;
}

THUMB int getEquipSlotCompareValues(int chara, int equipIndex, int* values)
{
    MenuStatusInfo::getHaveStatusInfo(chara);
    int equip = MenuStatusInfo::getPlayerEquipItemID(chara, (ItemType)equipIndex, 0);
    int value = status::UseItem::getEquipValue(equip);
    switch (equipIndex) {
        case 0: {
            int attack = MenuDataCommon::getStatus(chara, MenuDataCommon::ATTACK, false);
            if (equip == 0) {
                values[2] = values[4] = attack;
            } else {
                values[2] = attack;
                values[4] = attack - value;
            }
            break;
        }
        case 1:
        case 2:
        case 3: {
            int defence = MenuDataCommon::getStatus(chara, MenuDataCommon::DEFENCE, false);
            if (equip == 0) {
                values[2] = values[4] = defence;
            } else {
                values[2] = defence;
                values[4] = defence - value;
            }
            break;
        }
        case 4:
            if (equip == 0) {
                values[2] = values[4] = MenuDataCommon::getStatus(chara, MenuDataCommon::DEFENCE, false);
                break;
            }
            switch (status::UseItem::getEquipType(equip)) {
                case Strength:
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::STRENGTH, false);
                    values[4] = MenuDataCommon::getStatus(chara, MenuDataCommon::STRENGTH, true);
                    break;
                case Attack:
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::ATTACK, false);
                    values[4] = values[2] - value;
                    break;
                case Defence:
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::DEFENCE, false);
                    values[4] = values[2] - value;
                    break;
                case Wisdom:
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::WISDOM, false);
                    values[4] = MenuDataCommon::getStatus(chara, MenuDataCommon::WISDOM, true);
                    break;
                case Agility:
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::AGILITY, false);
                    values[4] = MenuDataCommon::getStatus(chara, MenuDataCommon::AGILITY, true);
                    break;
                case Luck:
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::LUCK, false);
                    values[4] = MenuDataCommon::getStatus(chara, MenuDataCommon::LUCK, true);
                    break;
            }
            break;
    }
    values[4] = dss::clamp<int>(values[4], 0, 999);
    values[3] = (int)"\xff\xfe\xaf\x24";
    return equip;
}

// not in the ROM (dead-stripped), its parts lists are still in .data
THUMB void unkfunc_unused_0217f690()
{
    drawMenuPartsPlain(s_parts_0217f690, 0);
    drawMenuPartsPlain(s_parts_0217fbc2, 0);
}
