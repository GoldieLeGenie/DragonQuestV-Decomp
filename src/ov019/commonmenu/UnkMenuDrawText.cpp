#include "ov019/commonmenu/UnkMenuDrawText.hpp"
#include "main/status/GameFlag.hpp"

THUMB int unkfunc_02178c28(int index)
{
    int table[6] = {(int)0xe00000a1, (int)0xe00000a2, (int)0xe00000a3, (int)0xe00000a4, (int)0xe00000a5, (int)0xe00000a6};
    return table[index];
}

THUMB int unkfunc_02178c50(int type, int index)
{
    int text = 0;
    switch (type) {
        case 0:
            if (index == 0) {
                text = 0xe0000212;
            }
            if (index == 1) {
                text = 0xe0000213;
            }
            if (index == 2) {
                text = 0xe0000214;
            }
            break;
        case 1:
            if (index == 0) {
                text = 0xe000028a;
            }
            if (index == 1) {
                text = 0xe000028b;
            }
            if (index == 2) {
                text = 0xe0000214;
            }
            break;
        case 2:
            if (index == 0) {
                text = 0xe00002a8;
            }
            if (index == 1) {
                text = 0xe00002a9;
            }
            if (index == 2) {
                text = 0xe00002aa;
            }
            if (index == 3) {
                text = 0xe00002ab;
            }
            if (index == 4) {
                text = 0xe00002ac;
            }
            if (index == 5) {
                text = 0xe0000214;
            }
            if (index == 6) {
                text = 0xe000028a;
            }
            break;
        case 3:
            if (index == 0) {
                text = 0xe00002ad;
            }
            if (index == 1) {
                text = 0xe00002ae;
            }
            if (index == 2) {
                text = 0xe00002af;
            }
            if (index == 3) {
                text = 0xe0000214;
            }
            break;
    }
    return text;
}

THUMB void unkfunc_02178d10(int* text, int flag)
{
    if (flag) {
        text[0] = 0xe00000aa;
        text[1] = 0xe00000ab;
    } else {
        text[0] = 0xe000035f;
        text[1] = 0xe0000360;
    }
}

THUMB void unkfunc_02178d30(int* text, int flag)
{
    if (flag) {
        text[0] = 0xe0000259;
        text[1] = 0xe000025a;
        text[2] = 0xe000025b;
        text[3] = 0xe000025c;
        text[4] = 0xe0000214;
    } else {
        text[0] = 0xe0000258;
        text[1] = 0xe0000259;
        text[2] = 0xe000025a;
        text[3] = 0xe000025b;
        text[4] = 0xe000025c;
        text[5] = 0xe0000214;
    }
}

THUMB int unkfunc_02178d6c(int index)
{
    int table[5] = {(int)0xe00003b6, (int)0xe00003b7, (int)0xe00003b8, (int)0xe00003b9, (int)0xe0000214};
    return table[index];
}

THUMB char unkfunc_02178d94(int index)
{
    char table[28] = {3, 6, 9, 2, 12, 13, 7, 10, 28, 14, 11, 18, 17, 19, 20, 29, 21, 22, 32, 30, 23, 1, 5, 26, 24, 27, 31, 34};
    char count = table[index];
    if (index == 0 && g_AreaFlag.check(0x2c5) == true) {
        count++;
    }
    if (index == 6 && g_AreaFlag.check(0x2c6) == true) {
        count++;
    }
    if (index == 9) {
        if (g_AreaFlag.check(0xec) == true) {
            count++;
        }
        if (g_AreaFlag.check(0x259) == true) {
            count += 2;
        }
    }
    if (index == 18 && g_AreaFlag.check(0x237) == true) {
        count++;
    }
    if (index == 24 && g_AreaFlag.check(0x2c7) == true) {
        count++;
    }
    return count;
}
