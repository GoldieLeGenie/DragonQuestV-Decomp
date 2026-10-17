#include "ov019/materielmenu/meisanhin/MaterielMenuMeisanhinUtil.hpp"

THUMB short getMeisanhinFlagNo(int itemId)
{
    short flagNo = 0;
    if (itemId == 0xd6) {
        flagNo = 0x16e;
    }
    if (itemId == 0xd7) {
        flagNo = 0x94;
    }
    if (itemId == 0xdb) {
        flagNo = 0x52;
    }
    if (itemId == 0xdc) {
        flagNo = 0x2c5;
    }
    if (itemId == 0xdd) {
        flagNo = 0x188;
    }
    if (itemId == 0xde) {
        flagNo = 0x2c3;
    }
    if (itemId == 0xdf) {
        flagNo = 0x2d6;
    }
    if (itemId == 0xe0) {
        flagNo = 0x2c6;
    }
    if (itemId == 0xe1) {
        flagNo = 0x87;
    }
    if (itemId == 0xe2) {
        flagNo = 0xd0;
    }
    if (itemId == 0xe3) {
        flagNo = 0x2c4;
    }
    if (itemId == 0xe4) {
        flagNo = 0xc2;
    }
    if (itemId == 0xe5) {
        flagNo = 0xc9;
    }
    if (itemId == 0xe6) {
        flagNo = 0x12c;
    }
    if (itemId == 0xe7) {
        flagNo = 0x12c;
    }
    if (itemId == 0xe8) {
        flagNo = 0x12c;
    }
    if (itemId == 0xe9) {
        flagNo = 0x2d7;
    }
    if (itemId == 0xea) {
        flagNo = 0x131;
    }
    if (itemId == 0xeb) {
        flagNo = 0x134;
    }
    if (itemId == 0xec) {
        flagNo = 0x100;
    }
    if (itemId == 0xed) {
        flagNo = 0x2d5;
    }
    if (itemId == 0xee) {
        flagNo = 0x116;
    }
    if (itemId == 0xef) {
        flagNo = 0x170;
    }
    if (itemId == 0xf0) {
        flagNo = 0x19c;
    }
    if (itemId == 0xf1) {
        flagNo = 0x2c7;
    }
    if (itemId == 0xf2) {
        flagNo = 0x233;
    }
    if (itemId == 0xf3) {
        flagNo = 0x1e5;
    }
    if (itemId == 0xf4) {
        flagNo = 0xd2;
    }
    if (itemId == 0xf6) {
        flagNo = 0x173;
    }
    if (itemId == 0xf5) {
        flagNo = 0x108;
    }
    if (itemId == 0xf7) {
        flagNo = 0x1ec;
    }
    if (itemId == 0xf8) {
        flagNo = 0x15f;
    }
    if (itemId == 0xf9) {
        flagNo = 0x237;
    }
    if (itemId == 0xfa) {
        flagNo = 0x228;
    }
    return flagNo;
}
