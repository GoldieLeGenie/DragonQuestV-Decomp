#pragma ipa file
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/BattleMonsterNamePlate.hpp"
#include "ov000/btl/BattleMenuFace.hpp"
#include "main/menu/MenuDataCommon.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/UseItem.hpp"

using menu::MenuStatusInfo;

// parts lists (their definition order sets the .data layout)
static UnkMenuParts s_parts_02176b9c[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x40, 0x48 },
    { 0x17, 0x00, (short)0xf000, 1, 0x0, 0x10, 0x40, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021769a4[] = {
    { 0x0c, 0xf4, 0, 0, 0xe0, 0xa0, 0x18, 0x18 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176f70[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x8, 0x8, 0x30, 0xa },
    { 0x0d, 0x08, (short)0xf000, 1, 0x8, 0x1a, 0x18, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 2, 0x8, 0x26, 0x18, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 3, 0x8, 0x34, 0x30, 0xa },
    { 0x0f, 0x0a, (short)0xf000, 5, 0x18, 0x1a, 0x20, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 6, 0x18, 0x26, 0x20, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176bc6[] = {
    { 0x14, 0xc2, 0, 0, 0x4, 0xe, 0x20, 0x18 },
    { 0x0c, 0xf1, 0, 0, 0x0, 0x0, 0x20, 0x20 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176abc[] = {
    { 0x09, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176e12[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x40, 0x20 },
    { 0x0d, 0x08, (short)0xf000, 0, 0x8, 0x6, 0x30, 0x10 },
    { 0x07, 0x00, (short)0xf000, 17, 0x8, 0x0, 0x30, 0x8 },
    { 0x11, 0x00, 0, 1, 0x0, 0x10, 0x0, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176a84[] = {
    { 0x15, 0xb5, 0, 0, 0x0, 0x10, 0x0, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176bf0[] = {
    { 0x0d, 0x08, (short)0xf000, 4, 0x14, 0x34, 0x10, 0xa },
    { 0x0f, 0x0a, (short)0xf000, 7, 0x18, 0x34, 0x20, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021769f8[] = {
    { 0x0a, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177034[] = {
    { 0x0d, 0x09, (short)0xf000, 0, 0x8, 0xa, 0x30, 0xa },
    { 0x0d, 0x08, (short)0xf000, 1, 0x3c, 0xa, 0x18, 0xa },
    { 0x0d, 0x08, (short)0xf000, 2, 0xc, 0x24, 0x18, 0xa },
    { 0x0f, 0x0a, (short)0xf000, 3, 0x1c, 0x24, 0x20, 0xa },
    { 0x0d, 0x08, (short)0xf000, 8, 0x3c, 0x24, 0xa, 0xa },
    { 0x0f, 0x0a, (short)0xf000, 4, 0x3c, 0x24, 0x20, 0xa },
    { 0x0d, 0x08, (short)0xf000, 5, 0xc, 0x34, 0x18, 0xa },
    { 0x0f, 0x0a, (short)0xf000, 6, 0x1c, 0x34, 0x20, 0xa },
    { 0x0d, 0x08, (short)0xf000, 8, 0x3c, 0x34, 0xa, 0xa },
    { 0x0f, 0x0a, (short)0xf000, 7, 0x3c, 0x34, 0x20, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176da2[] = {
    { 0x0e, 0x09, (short)0xf000, 0, 0x2, 0x0, 0x3e, 0x14 },
    { 0x0d, 0x09, (short)0xf000, 1, 0x2, 0x14, 0x3e, 0xa },
    { 0x0e, 0x09, (short)0xf000, 2, 0x2, 0x20, 0x3e, 0x20 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176a14[] = {
    { 0x0a, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176c1a[] = {
    { 0x0d, 0x08, (short)0xf000, 4, 0x14, 0x34, 0x10, 0xa },
    { 0x0d, 0x0a, (short)0xf000, 7, 0x18, 0x34, 0x20, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021770ce[] = {
    { 0x14, 0xc0, 0, -1, 0x0, 0x0, 0x70, 0x38 },
    { 0x0c, 0xf1, 0, 0, -4, 0x10, 0x20, 0x20 },
    { 0x0d, 0x08, (short)0xf000, 1, 0x1c, 0x3, 0x50, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 2, 0x20, 0x27, 0x30, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 3, 0x20, 0x10, 0x10, 0x10 },
    { 0x0d, 0x09, (short)0xf000, 4, 0x44, 0x10, 0x10, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 5, 0x20, 0x1a, 0x10, 0x10 },
    { 0x0d, 0x09, (short)0xf000, 6, 0x44, 0x1a, 0x10, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 8, 0x30, 0x10, 0x18, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 9, 0x50, 0x10, 0x18, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 10, 0x30, 0x1a, 0x18, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 11, 0x50, 0x1a, 0x18, 0x10 },
    { 0x0f, 0x09, (short)0xf000, 12, 0x0, 0x3, 0x20, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176ad8[] = {
    { 0x15, 0xb4, 0, 0, 0x0, 0x0, 0x0, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176f2a[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x8, 0xa, 0x10, 0xa },
    { 0x0f, 0x0a, (short)0xf000, 1, 0x10, 0xa, 0x20, 0xa },
    { 0x0d, 0x08, (short)0xf000, 2, 0x30, 0xa, 0x10, 0xa },
    { 0x0f, 0x0b, (short)0xf000, 3, 0x0, 0x0, 0x1e, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176a68[] = {
    { 0x0f, 0x0a, (short)0xf000, 0, 0x60, 0x42, 0x18, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176a4c[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x14, 0x8, 0x60, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176dda[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0xa0, 0x8, 0x30, 0x10 },
    { 0x0d, 0x0a, (short)0xf000, 1, 0xd8, 0x8, 0x8, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 2, 0xe0, 0x8, 0x18, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176c98[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x48, 0xa, 0xe, 0xa },
    { 0x0f, 0x0a, (short)0xf000, 1, 0x46, 0xa, 0x18, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176cc2[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x48, 0xa, 0xe, 0xa },
    { 0x0d, 0x0a, (short)0xf000, 1, 0x46, 0xa, 0x18, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176aa0[] = {
    { 0x09, 0x00, 0x2, 0, 0x0, 0x0, 0x0, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021769dc[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0xc, 0x8, 0x10, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176b10[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x6, 0x7, 0x60, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176fd2[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0xa, 0x44, 0x38, 0xa },
    { 0x0d, 0x08, (short)0xf000, 4, 0x3c, 0x44, 0xa, 0xa },
    { 0x0f, 0x0b, (short)0xf000, 1, 0x0, 0x0, 0x1a, 0xa },
    { 0x0d, 0x08, (short)0xf000, 2, 0xa, 0x54, 0x38, 0xa },
    { 0x0d, 0x08, (short)0xf000, 4, 0x3c, 0x54, 0xa, 0xa },
    { 0x0f, 0x0b, (short)0xf000, 3, 0x0, 0x0, 0x1a, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176b2c[] = {
    { 0x0c, 0xf4, 0, 0, 0x0, 0x0, 0x18, 0x18 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176b48[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0xc, 0x68, 0x48, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176b64[] = {
    { 0x09, 0x00, 0x3, 0, 0x0, 0x0, 0x0, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176d16[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x58, 0x20 },
    { 0x07, 0x00, (short)0xf000, 25, 0x50, 0x8, 0x8, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176d40[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x1c, 0x8, 0xa, 0xa },
    { 0x0d, 0x08, (short)0xf000, 1, 0x1c, 0x13, 0xa, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177192[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x8, 0xa, 0x28, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 1, 0x58, 0xa, 0x10, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 2, 0x68, 0xa, 0x28, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 3, 0x38, 0x24, 0x58, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 4, 0x38, 0x34, 0x28, 0x10 },
    { 0x0d, 0x0b, (short)0xf000, 5, 0x0, 0x0, 0x8, 0x10 },
    { 0x0d, 0x0b, (short)0xf000, 6, 0x0, 0x0, 0x28, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 7, 0x38, 0x42, 0x28, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 8, 0x60, 0x42, 0x8, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 9, 0x38, 0x4f, 0x18, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 10, 0x48, 0x4f, 0x20, 0x10 },
    { 0x0d, 0x0b, (short)0xf000, 11, 0x0, 0x0, 0x8, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 12, 0x68, 0x4f, 0x20, 0x10 },
    { 0x0d, 0x08, (short)0xf000, 13, 0x38, 0x5c, 0x18, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 14, 0x48, 0x5c, 0x20, 0x10 },
    { 0x0d, 0x0b, (short)0xf000, 15, 0x0, 0x0, 0x8, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 16, 0x68, 0x5c, 0x20, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176a30[] = {
    { 0x0e, 0x08, (short)0xf000, 0, 0x0, 0x0, 0xc8, 0x18 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176af4[] = {
    { 0x0e, 0x09, (short)0xf000, 0, 0x2, 0x8, 0x3e, 0x30 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021769c0[] = {
    { 0x09, 0x00, 0x1, 0, 0x0, 0x0, 0x0, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176e58[] = {
    { 0x0f, 0x08, (short)0xf000, 0, 0xc, 0x0, 0xa, 0x10 },
    { 0x0d, 0x0b, (short)0xf000, 1, 0x0, 0x0, 0xa, 0x10 },
    { 0x0f, 0x0b, (short)0xf000, 2, 0x0, 0x0, 0xa, 0x10 },
    { 0x0c, 0xf4, 0, 3, 0x10, 0x8, 0x18, 0x18 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176d6a[] = {
    { 0x0c, 0xf4, 0, 0, 0x28, 0x0, 0x18, 0x18 },
    { 0x0d, 0x08, (short)0xf000, 1, 0x8, 0xa, 0x28, 0x10 },
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x48, 0x20 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176e9e[] = {
    { 0x0f, 0x08, (short)0xf000, 0, 0x6, 0x4, 0xa, 0x10 },
    { 0x0d, 0x0b, (short)0xf000, 1, 0x0, 0x0, 0xa, 0x10 },
    { 0x0f, 0x0b, (short)0xf000, 2, 0x0, 0x0, 0xa, 0x10 },
    { 0x0c, 0xf4, 0, 3, 0x8, 0x10, 0x18, 0x18 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176ee4[] = {
    { 0x14, 0xc0, 0, -1, 0x0, 0xc, 0x68, 0x18 },
    { 0x0e, 0x08, (short)0xf000, 0, 0x8, 0xc, 0x40, 0x18 },
    { 0x0c, 0xf0, 0, 1, 0x48, 0x0, 0x20, 0x20 },
    { 0x0d, 0x0a, (short)0xf000, 2, 0x3e, 0x18, 0x10, 0xc },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176c44[] = {
    { 0x0d, 0x08, (short)0xf000, 13, 0x2c, 0x27, 0x10, 0x10 },
    { 0x0d, 0x0a, (short)0xf000, 7, 0x30, 0x27, 0x18, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176c6e[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x68, 0x68 },
    { 0x16, 0x00, (short)0xf000, 0, 0x0, 0x18, 0x68, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176b80[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x70, 0xe0, 0x30 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02176cec[] = {
    { 0x0d, 0x08, (short)0xf000, 13, 0x2c, 0x27, 0x10, 0x10 },
    { 0x0f, 0x0a, (short)0xf000, 7, 0x30, 0x27, 0x18, 0x10 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};

inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline int BattleMenuPlayerControl::getPartyHP(int memberNum) { return statusData_[memberNum].hp; }
inline int BattleMenuPlayerControl::getHPColor(int memberNum)
{
    if (memberNum < 0) {
        return 0;
    }
    return statusData_[memberNum].color;
}
inline int BattleMenuPlayerControl::getCondition(int memberNum) { return statusData_[memberNum].condition; }
inline bool BattleMenuPlayerControl::isConditionChange(int memberNum) { return statusData_[memberNum].conditionFlag; }

THUMB void drawBattleCommandIcons(int command0, int command1, int command2, int command3)
{
    drawBattleCommandIcon(command0, 0x40, 0x80, 1);
    drawBattleCommandIcon(command1, 0x88, 0x80, 1);
    drawBattleCommandIcon(command2, 0x40, 0xa0, 1);
    drawBattleCommandIcon(command3, 0x88, 0xa0, 1);
}

THUMB void drawBattleMemberHpPercent(int x, int y, int hp, status::HaveStatusInfo* info)
{
    int index = info->haveStatus_.playerIndex_;
    MenuStatusInfo::getPlayerSortIndex(index);
    int hpMax = info->getHpMax();
    int param[2];
    param[0] = index + 0x50000000;
    param[1] = hp * 100 / hpMax;
    if (param[1] <= 0 && hp > 0) {
        param[1] = 1;
    }
    if (hp > hpMax / 4 - 1 && param[1] < 26) {
        param[1] = 26;
    }
    if (hp == 0) {
        param[1] = 0;
    }
    drawMenuParts(s_parts_02176e12, param, x, y, data_02094dd4[unkfunc_0216ff50(info->getHpMax(), hp)]);
}

THUMB void drawBattleActiveMember(status::HaveStatusInfo* info, int hp, int flag)
{
    drawBattleMemberHpPercent(0, 0xa0, hp, info);
    drawBattleMemberFace(8, 0x72, info, flag);
}

THUMB void unkfunc_0216f2ec(int group)
{
    int plateGroup;
    int count = BattleMonsterNamePlate::getSingleton().addCount_;
    if (count == 0) {
        return;
    }
    for (int i = 0; i < count; i++) {
        BattleMonsterNamePlate::Monster_DATA& data = BattleMonsterNamePlate::getSingleton().getMonsterData(i);
        int drawID = data.drawID;
        int y = data.height;
        plateGroup = data.group;
        int x = data.center - (data.leng >> 1);
        if (group == plateGroup || group == -1) {
            showNamePlate(i, x, y, drawID, 1);
            if (group == plateGroup) {
                drawMenuPartsAt(s_parts_02176ad8, 0, x, y + 8);
            }
        } else {
            showNamePlate(i, x, y, drawID, 0);
        }
    }
}

THUMB void drawBattleCommandIcon(int command, int x, int y, int flag)
{
    int param[2] = { -1, 0 };
    switch (command) {
    case 0x01:
        param[0] = 6;
        param[1] = 0xe0000001;
        break;
    case 0x02:
        param[0] = 1;
        param[1] = 0xe0000002;
        break;
    case 0x04:
        param[0] = 9;
        param[1] = 0xe0000003;
        break;
    case 0x08:
        param[0] = 10;
        param[1] = 0xe0000004;
        break;
    case 0x10:
        param[0] = 6;
        param[1] = 0xe0000005;
        break;
    case 0x20:
        param[0] = 2;
        param[1] = 0xe0000006;
        break;
    case 0x100:
        param[0] = 2;
        param[1] = 0xe000000d;
        break;
    case 0x40:
        param[0] = 3;
        param[1] = 0xe0000007;
        break;
    case 0x80:
        param[0] = 7;
        param[1] = 0xe0000008;
        break;
    default:
        return;
    }
    if (flag == 0 && param[0] != -1) {
        drawMenuParts(s_parts_02176d6a, param, x, y, data_02094dd4[0]);
        drawMenuPartsAt(s_parts_02176a84, 0, x, y);
    } else {
        drawMenuParts(s_parts_02176d6a, param, x, y, data_02094dd4[0]);
    }
}

THUMB void drawBattleHelpMessage(int x, int y, int message)
{
    drawMenuParts(s_parts_02176a30, &message, x, y, data_02094dd4[0]);
}

THUMB void drawBattlePageNumber(int x, int y, int max, int page)
{
    if (max != 0) {
        int param[4] = { 0, (int)"\xff\xfe\xa7\x24", 0, 0xd };
        param[0] = page + 1;
        param[2] = max + 1;
        drawMenuParts(s_parts_02176e9e, param, x, y - 8, data_02094dd4[0]);
    }
}

THUMB void drawBattleItemEntry(int x, int y, int item, int flag)
{
    int param[3] = { 0, 0, (int)"\xff\xfe\xa6\x24" };
    param[0] = item + 0x40000000;
    param[1] = item;
    if (flag) {
        param[2] = 0xe000003c;
    }
    drawMenuParts(s_parts_02176ee4, param, x, y, data_02094dd4[0]);
}

THUMB void unkfunc_0216f570(int x, int y, int action)
{
    int param = MenuStatusInfo::getWordDBIndex(action) + 0x70000000;
    drawMenuParts(s_parts_02176b10, &param, x, y, data_02094dd4[0]);
}

THUMB void unkfunc_0216f5a4(status::HaveStatusInfo* info, int index)
{
    int playerIndex = info->haveStatus_.playerIndex_;
    int param[14];
    param[0] = info->getIconIndex();
    param[1] = playerIndex + 0x50000000;
    param[2] = 0xe0000016;
    param[3] = 0xe0000017;
    param[4] = (int)"\xff\xfe\xa7\x24";
    param[5] = 0xe0000018;
    param[6] = (int)"\xff\xfe\xa7\x24";
    param[7] = info->haveStatus_.level_;
    param[8] = info->haveStatus_.getHp();
    param[9] = info->haveStatus_.getHpMax();
    param[10] = info->haveStatus_.getMp();
    param[11] = info->haveStatus_.getMpMax();
    param[12] = index + 1;
    param[13] = (int)"\xff\xfe\xa8\x24";
    param[2] = BattleMenuPlayerControl::getSingleton()->getCondition(index);
    int color = BattleMenuPlayerControl::getSingleton()->getHPColor(index);
    int x = (index % 2) * 120 + 12;
    int y = (index / 2) * 64 + 20;
    drawMenuParts(s_parts_021770ce, param, x, y, data_02094dd4[color]);
    if (!BattleMenuPlayerControl::getSingleton()->isConditionChange(index)) {
        drawMenuParts(s_parts_02176cec, param, x, y, data_02094dd4[color]);
    }
}

THUMB void unkfunc_0216f694(int x, int y, status::HaveStatusInfo* info)
{
    MenuStatusInfo::getPlayerSortIndex(info->haveStatus_.playerIndex_);
    int color = BattleDrawParts_getStatusColor(*info);
    drawMenuPartsAt(s_parts_02176c6e, 0, x, y);
    int level[2] = { (int)"\xff\xfe\xa8\x24", 0 };
    level[1] = info->haveStatus_.level_;
    int status[9] = { 0, 0xe0000016, 0xe0000014, 0, 0, 0xe0000015, 0, 0, (int)"\xff\xfe\xa7\x24" };
    status[0] = info->haveStatus_.playerIndex_ + 0x50000000;
    status[3] = info->getHp();
    status[4] = info->getHpMax();
    status[6] = info->getMp();
    status[7] = info->getMpMax();
    int power[5] = { 0xe0000019, 0, 0xe000001a, 0, (int)"\xff\xfe\xa8\x24" };
    power[1] = info->getAttack(0);
    power[3] = info->getDefence(0);
    drawMenuParts(s_parts_02176c98, level, x, y, data_02094dd4[color]);
    drawMenuParts(s_parts_02177034, status, x, y, data_02094dd4[color]);
    drawMenuParts(s_parts_02176fd2, power, x, y, data_02094dd4[color]);
}

THUMB void unkfunc_0216f78c(int* list, int count, int page)
{
    drawMenuPartsPlain(s_parts_02176b80, 0);
    int pageMax = (count - 1) / 4;
    int num = (count - 1) % 4 + 1;
    if (pageMax != page) {
        num = 4;
    }
    for (int i = 0; i < num; i++) {
        int x = i * 40 + 16;
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(list[page * 4 + i]);
        drawBattleMemberIcon(x, 0x70, info.getIconIndex());
        unkfunc_0216f82c(&info, x, 0x70);
    }
    int param = 0xd;
    if (pageMax > 0) {
        drawMenuParts(s_parts_02176b2c, &param, 0xc4, 0x80, data_02094dd4[0]);
    }
}

THUMB void unkfunc_0216f82c(status::HaveStatusInfo* info, int x, int y)
{
    int param[3] = { (int)" ", (int)" ", (int)" " };
    MenuStatusInfo::getPlayerSortIndex(info->haveStatus_.playerIndex_);
    int curse = false;
    int count = info->haveItem_.getMaxCount();
    for (int i = 0; i < count; i++) {
        if (info->haveItem_.isEquipment(i) == true && status::UseItem::isCurse(info->haveItem_.getItem(i))) {
            curse = true;
        }
    }
    if (info->isDeath()) {
        param[0] = 0xe0000037;
    } else {
        if (info->getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU) || info->getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
            param[0] = 0xe0000038;
        }
        if (info->isSpell() || curse) {
            param[1] = 0xe0000039;
        }
    }
    drawMenuParts(s_parts_02176d40, param, x, y, data_02094dd4[BattleDrawParts_getStatusColor(*info)]);
}

THUMB void drawBattleCancelButton()
{
    int param = 5;
    drawMenuPartsPlain(s_parts_021769a4, &param);
}

THUMB void unkfunc_0216f91c(status::HaveStatusInfo* info, int a, int b, int c, int index)
{
    setMenuDrawOffset(0, 0);
    int x = index * 64;
    drawMenuPartsAt(s_parts_02176b9c, 0, x, 0x78);
    int param[8] = { 0 };
    for (int i = 0; i < 8; i++) param[i] = 0;
    int color = BattleMenuPlayerControl::getSingleton()->getHPColor(index);
    param[0] = info->haveStatus_.playerIndex_ + 0x50000000;
    param[1] = 0xe0000014;
    param[2] = 0xe0000015;
    param[3] = 0xe0000016;
    param[4] = (int)"\xff\xfe\xa8\x24";
    param[5] = a;
    param[6] = b;
    param[7] = c;
    param[3] = BattleMenuPlayerControl::getSingleton()->getCondition(index);
    if (!BattleMenuPlayerControl::getSingleton()->isConditionChange(index)) {
        drawMenuParts(s_parts_02176bf0, param, x, 0x78, data_02094dd4[color]);
    }
    drawMenuParts(s_parts_02176f70, param, x, 0x78, data_02094dd4[color]);
}

THUMB void drawBattleActionHistory(int index, int value, int message, int color)
{
    setMenuDrawOffset(0, 0);
    int x = index * 64;
    if (message != -1) {
        int param[3] = { 0, (int)"\xff\xfe\xbe\x24", 0 };
        param[2] = message;
        param[0] = value;
        drawMenuParts(s_parts_02176da2, param, x, 0x10, data_02094dd4[color]);
    } else if (value != -1) {
        drawMenuParts(s_parts_02176af4, &value, x, 0x10, data_02094dd4[color]);
    }
}

THUMB void drawBattleMemberIconInSlot(int x, int y, int value, int type)
{
    switch (type) {
    case 0:
        drawMenuPartsAt(s_parts_02176abc, &value, x, y);
        break;
    case 1:
        drawMenuPartsAt(s_parts_021769c0, &value, x, y);
        break;
    case 2:
        drawMenuPartsAt(s_parts_02176aa0, &value, x, y);
        break;
    case 3:
        drawMenuPartsAt(s_parts_02176b64, &value, x, y);
        break;
    }
}

THUMB void drawBattleMpCost(int mp, int useMp)
{
    drawMenuPartsAt(s_parts_02176d16, 0, 0x88, 0xa0);
    int param[4] = { 0xe0000018, 0, (int)"\xff\xfe\xa7\x24", 0 };
    param[1] = useMp;
    param[3] = mp;
    drawMenuParts(s_parts_02176f2a, param, 0x88, 0xa0, data_02094dd4[0]);
}

THUMB void unkfunc_0216fb38(int page, int max)
{
    int param[5] = { 0, (int)"\xff\xfe\xa7\x24", 0, 0xd, 0 };
    param[0] = page + 1;
    param[2] = max + 1;
    if (max != 0) {
        drawMenuParts(s_parts_02176e58, param, 0xd0, 0x78, data_02094dd4[0]);
    }
    drawMenuFrame(0, 0x70, 0x100, 0x30, -1);
}

THUMB void unkfunc_0216fb94(int hp, int mp, int hpMax, int mpMax, int sex, int level, int ctrl, int monster)
{
    status::PlayerData& data = status::PlayerDataAll::playerData_[ctrl];
    int param[18];
    param[0] = data.index_ + 0x50000000;
    param[1] = (int)"\xff\xfe\xac\x24";
    param[2] = 0xe0000066;
    param[3] = monster + 0x60000000;
    param[4] = 0xe0000113;
    param[5] = (int)"\xff\xfe\xa8\x24";
    if (sex == 2) {
        param[6] = (int)"???";
    } else if (sex == 0) {
        param[6] = 0xe0000114;
    } else if (sex == 1) {
        param[6] = 0xe0000115;
    }
    param[7] = 0xe0000118;
    param[8] = (int)"\xff\xfe\xa8\x24";
    param[9] = 0xe0000014;
    param[10] = hp;
    param[11] = (int)"\xff\xfe\xa7\x24";
    param[12] = hpMax;
    param[13] = 0xe0000015;
    param[14] = mp;
    param[15] = (int)"\xff\xfe\xa7\x24";
    param[16] = mpMax;
    switch (data.kindIndex_) {
    case 0x3a:
        param[3] = 0xe000010b;
        break;
    case 0x3b:
        param[3] = 0xe000010b;
        break;
    case 0x52:
        param[3] = 0xe000010c;
        break;
    }
    int icon = data.getIconIndex();
    int lv = level;
    drawMenuPartsColored(s_parts_02177192, param, data_02094dd4[unkfunc_0216ff50(hpMax, hp)]);
    drawMenuPartsAt(s_parts_02176a14, &icon, 6, 0x28);
    drawMenuPartsColored(s_parts_02176a68, &lv, data_02094dd4[unkfunc_0216ff50(hpMax, hp)]);
    drawMenuFrame(0, 0, 0x98, 0x70, 0x18);
}

THUMB void unkfunc_0216fcb8(short hp, unsigned short hpMax, unsigned short strength, unsigned short agility, unsigned short protection, unsigned short wisdom, unsigned short luck, unsigned short attack, unsigned short defence)
{
    int kind[7] = { 2, 3, 4, 5, 6, 0, 1 };
    unsigned short value[7] = { strength, agility, protection, wisdom, luck, attack, defence };
    for (int i = 0; i < 7; i++) {
        int param[3] = { 0, (int)"\xff\xfe\xa8\x24", 0 };
        param[0] = menu::MenuDataCommon::getAbilityKind((menu::MenuDataCommon::STATUS_INDEX)kind[i]);
        param[2] = value[i];
        drawMenuParts(s_parts_02176dda, param, 0, i * 14, data_02094dd4[unkfunc_0216ff50(hpMax, hp)]);
    }
    drawMenuFrame(0x98, 0, 0x68, 0x70, -1);
}

THUMB void drawBattleMemberIcon(int x, int y, int icon)
{
    drawMenuPartsAt(s_parts_02176bc6, &icon, x, y);
}

THUMB void unkfunc_0216fd88(status::BaseHaveItem* items, int hp, int hpMax)
{
    setMenuDrawOffset(0, 0);
    int x;
    int y;
    int count = items->getCount();
    int item = 0;
    for (int i = 0; i < count; i++) {
        item = items->getItem(i) + 0x40000000;
        x = (i % 2) * 120;
        y = (i / 2) * 16;
        if (items->isEquipment(i) == true) {
            int equip = 0xe000003c;
            drawMenuParts(s_parts_021769dc, &equip, x, y, data_02094dd4[unkfunc_0216ff50(hpMax, hp)]);
        }
        drawMenuParts(s_parts_02176a4c, &item, x, y, data_02094dd4[unkfunc_0216ff50(hpMax, hp)]);
    }
    drawMenuFrame(0, 0, 0xf0, 0x60, -1);
}

THUMB void unkfunc_0216fe48(status::HaveAction* actions, int hp, int hpMax)
{
    setMenuDrawOffset(0, 0);
    int action = 0;
    int count = actions->getCount();
    for (int i = 0; i < count; i++) {
        action = actions->getAction(i) + 0x70000000;
        int color = unkfunc_0216ff50(hpMax, hp);
        drawMenuParts(s_parts_02176b48, &action, (i % 3) * 80, (i / 3) * 12, data_02094dd4[color]);
    }
    drawMenuFrame(0, 0x60, 0x100, 0x60, -1);
}

THUMB void drawBattleMemberFace(int x, int y, status::HaveStatusInfo* info, int flag)
{
    int index = info->haveStatus_.playerIndex_;
    if (flag == 1) {
        int icon = info->getIconIndex();
        drawMenuPartsAt(s_parts_021769f8, &icon, x, y);
        BattleMenuFace::getSingleton()->setDisplayOn(index, x, y);
    } else {
        BattleMenuFace::getSingleton()->setDisplayOff(index);
    }
}

THUMB int BattleDrawParts_getStatusColor(status::HaveStatusInfo& statusInfo)
{
    statusInfo.getHp();
    if (statusInfo.isDeath()) {
        return 2;
    }
    if (statusInfo.isNearDeath() != false) {
        return 1;
    }
    return 0;
}

THUMB int unkfunc_0216ff50(int hpMax, int hp)
{
    if (hp == 0) {
        return 2;
    }
    if (hp <= hpMax / 4 - 1) {
        return 1;
    }
    return 0;
}

THUMB void unkfunc_0216ff70()
{
    drawBattleCommandIcons(1, 2, 4, 8);
}

THUMB void unkfunc_0216ff80(int flag)
{
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    drawBattleActiveMember(&info, BattleMenuPlayerControl::getSingleton()->getPartyHP(chara), 1);
    int command0 = (flag & 0x10) ? 0x10 : 0;
    int command1 = (flag & 0x20) ? 0x20 : 0;
    if (flag & 0x100) {
        command1 = 0x100;
    }
    int command2 = (flag & 0x40) ? 0x40 : 0;
    int command3 = (flag & 0x80) ? 0x80 : 0;
    drawBattleCommandIcons(command0, command1, command2, command3);
    unkfunc_0216f2ec(-1);
    drawBattleCancelButton();
}

// not in the ROM (dead-stripped), keeps the unused parts lists and condition tables
THUMB void unkfunc_unused_0216ff80(int index, int flag)
{
    int conditionName[10] = { 0xe0000027, 0xe000002b, 0xe0000029, 0xe0000028, 0xe000002a, 0xe0000026, 0xe0000025, 0xe0000024, 0xe0000023, 0 };
    int conditionNameFemale[10] = { 0xe0000031, 0xe0000035, 0xe0000033, 0xe0000032, 0xe0000034, 0xe0000030, 0xe000002f, 0xe000002e, 0xe000002d, 0 };
    int param = flag ? conditionNameFemale[index] : conditionName[index];
    drawMenuParts(s_parts_02176c1a, &param, 0, 0, data_02094dd4[0]);
    drawMenuParts(s_parts_02176c44, &param, 0, 0, data_02094dd4[0]);
    drawMenuParts(s_parts_02176cc2, &param, 0, 0, data_02094dd4[0]);
}
