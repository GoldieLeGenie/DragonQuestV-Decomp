#pragma ipa file
#include "main/menu/UnkMenuCasinoDraw.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/text/TextAPI.hpp"

#define PARTS_END {0xff, 0x00, 0x0000, 0, 0x00, 0x00, 0x00, 0x00}

extern UnkMenuParts s_unusedParts[];

static UnkMenuParts s_resumeNameParts[] = {
    {0x0d, 0x0a, (short)0xf000, 1, 0x78, 0x00, 0x10, 0x0a},
    {0x0d, 0x08, (short)0xf000, 2, 0x8a, 0x00, 0x0e, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 3, 0x00, 0x00, 0x18, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_resumeTimeParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x50, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 4, 0x98, 0x00, 0x18, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 8, 0x00, 0x00, 0x0a, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 9, 0x00, 0x00, 0x0a, 0x0a},
    {0x0d, 0x0b, (short)0xf000, 5, 0x00, 0x00, 0x08, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 6, 0x00, 0x00, 0x0a, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 7, 0x00, 0x00, 0x0a, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_betTitleParts[] = {
    {0x15, 0xb0, 0x0000, 0, 0xdd, 0x26, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_monsterTitleActiveParts[] = {
    {0x05, 0x00, (short)0xf000, 5, 0xb0, 0x00, 0x08, 0x08},
    {0x03, 0xd0, (short)0xf000, 0, 0xb0, 0x08, 0x08, 0x38},
    {0x05, 0x00, (short)0xf000, 11, 0xb0, 0x40, 0x08, 0x08},
    PARTS_END,
};

static UnkMenuParts s_messageCharParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x18, 0x00, 0x0c, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_betTitleActiveParts[] = {
    {0x15, 0xb1, 0x0000, 0, 0xdd, 0x26, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_keyLineParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf000, 1, 0x10, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf000, 2, 0x20, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf000, 3, 0x30, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf000, 4, 0x40, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf000, 5, 0x58, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf000, 6, 0x68, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf000, 7, 0x78, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf000, 8, 0x88, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf000, 9, 0x98, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf000, 10, 0xb0, 0x00, 0x28, 0x0c},
    PARTS_END,
};

// not in the ROM (dead-stripped), its parts list and its rodata are still in the unit
THUMB void unkfunc_unused_020962e4()
{
    int param[] = {0x58, 0x10};
    int pos[] = {0x0e, 0x90};
    unkfunc_020629b4(s_unusedParts, param, pos[0], pos[1], 1);
}

static UnkMenuParts s_logNameParts[] = {
    {0x0d, 0x0a, (short)0xf000, 3, 0x78, 0x00, 0x10, 0x0a},
    {0x0d, 0x08, (short)0xf000, 4, 0x8a, 0x00, 0x0e, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 5, 0x00, 0x00, 0x18, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_nameCharParts[] = {
    {0x0d, 0x05, (short)0xf000, 0, 0x00, 0x00, 0x0c, 0x0e},
    PARTS_END,
};

static UnkMenuParts s_monsterCursorParts[] = {
    {0x15, 0xb5, 0x0000, 0, 0x00, 0x00, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_messageCursorParts[] = {
    {0x15, 0xb0, 0x0000, 0, 0x00, 0x00, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_titleParts[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x00, 0x00, 0x00, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_monsterLineParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x10, 0x00, 0x64, 0x10},
    {0x0d, 0x0b, (short)0xf000, 6, 0x00, 0x00, 0x0a, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x74, 0x00, 0x0a, 0x10},
    {0x0f, 0x0a, (short)0xf000, 2, 0x7e, 0x00, 0x18, 0x24},
    {0x0d, 0x0b, (short)0xf000, 3, 0x00, 0x00, 0x0a, 0x10},
    {0x0f, 0x0b, (short)0xf000, 4, 0x00, 0x00, 0x08, 0x0e},
    {0x0d, 0x0b, (short)0xf000, 5, 0x00, 0x00, 0x0c, 0x0e},
    PARTS_END,
};

static UnkMenuParts s_monsterTitleParts[] = {
    {0x05, 0x00, (short)0xf000, 5, 0xb0, 0x00, 0x08, 0x08},
    {0x03, 0xd0, (short)0xf000, 0, 0xb0, 0x08, 0x08, 0x10},
    {0x05, 0x00, (short)0xf000, 11, 0xb0, 0x18, 0x08, 0x08},
    PARTS_END,
};

static UnkMenuParts s_cursorParts[] = {
    {0x15, 0xb0, 0x0000, 0, 0x00, 0x00, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_coinParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x38, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0x00, 0x0c, 0x38, 0x10},
    PARTS_END,
};

static UnkMenuParts s_commandParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x90, 0x0e},
    PARTS_END,
};

static UnkMenuParts s_logEmptyParts[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x0a, 0x0a},
    {0x0d, 0x0b, (short)0xf000, 7, 0x00, 0x00, 0x0e, 0x0a},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x50, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_unusedParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x58, 0x10},
    PARTS_END,
};

static UnkMenuParts s_logParts[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x0e, 0x0a},
    {0x0d, 0x0b, (short)0xf000, 7, 0x00, 0x00, 0x0e, 0x0a},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x50, 0x0c},
    {0x0f, 0x0a, (short)0xf000, 6, 0x98, 0x00, 0x18, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 11, 0x00, 0x00, 0x0a, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 12, 0x00, 0x00, 0x0a, 0x0a},
    {0x0d, 0x0b, (short)0xf000, 7, 0x00, 0x00, 0x08, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 8, 0x00, 0x00, 0x0a, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 9, 0x00, 0x00, 0x0a, 0x0a},
    {0x0d, 0x08, (short)0xf000, 10, 0x74, 0x0c, 0x70, 0x0a},
    PARTS_END,
};

THUMB void unkfunc_02029fa4(int flag)
{
    if (flag) {
        unkfunc_0206297c(s_monsterTitleActiveParts, 0);
    }
    else {
        unkfunc_0206297c(s_monsterTitleParts, 0);
    }
}

THUMB void unkfunc_02029fc8(int flag)
{
    if (flag) {
        unkfunc_0206297c(s_betTitleActiveParts, 0);
    }
    else {
        unkfunc_0206297c(s_betTitleParts, 0);
    }
}

THUMB void unkfunc_02029fec(int* message, int count, int x, int y)
{
    int param = 0;
    s_commandParts[0].x_ = x;
    s_commandParts[0].y_ = y;
    for (int i = 0; i < count; i++) {
        param = message[i];
        unkfunc_020629b4(s_commandParts, &param, 0, i * 0xe, 1);
    }
}

THUMB void unkfunc_0202a034(int monster, int diameter, int index, int order)
{
    if (monster >= 0) {
        const char* orderText[] = {"", "\xff\xfe\x21\xff", "\xff\xfe\x22\xff", "\xff\xfe\x23\xff", "\xff\xfe\x24\xff"};
        int param[7];
        param[0] = monster + 0x60000000;
        param[1] = (int)"\xff\xfe\xa9\x24";
        param[2] = diameter / 10;
        param[3] = (int)"@.";
        param[4] = diameter % 10;
        param[5] = 0xe0000353;
        param[6] = (int)orderText[order + 1];
        unkfunc_020629b4(s_monsterLineParts, param, 0, index * 0x18 + 0x10, 1);
    }
}

THUMB void unkfunc_0202a0b4(int index)
{
    unkfunc_02062990(s_monsterCursorParts, 0, 0xc, index * 0x18 + 0x16);
}

THUMB void unkfunc_0202a0d0(int coin, int x, int y, int flag)
{
    int param[] = {0xe0000352, coin};
    if (flag) {
        param[0] = (int)"@";
    }
    unkfunc_020629b4(s_coinParts, param, x + 0xc0, y + 8, 1);
    if (flag && coin < 10) {
        param[0] = (int)"@";
        param[1] = 0;
        unkfunc_020629b4(s_coinParts, param, x + 0xb8, y + 8, 1);
    }
}

THUMB void unkfunc_0202a138(int* message, int x, int y, int w, int h)
{
    s_titleParts[0].x_ = x;
    s_titleParts[0].y_ = y + ((h - y) >> 1);
    s_titleParts[0].w_ = w;
    s_titleParts[0].h_ = 10;
    unkfunc_020629a4(s_titleParts, message, 1);
}

THUMB void unkfunc_0202a164(int index, const char* name, int clear, int level, int town, int time, int x, int flag)
{
    UnkMenuParts* parts = s_logParts;
    int color;
    if (flag) {
        color = 1;
    }
    else {
        color = 2;
    }
    unsigned int hour = time / 216000;
    unsigned int minute = time % 216000 / 3600;
    int param[13];
    param[0] = index + 1;
    param[1] = (int)name;
    param[3] = (int)"\xff\xfe\xb9\x24";
    param[4] = 0xe0000016;
    param[5] = level;
    param[6] = hour / 100;
    param[7] = (int)"\xff\xfe\xa8\x24";
    param[8] = minute / 10;
    param[9] = minute % 10;
    param[10] = town;
    param[11] = hour % 100 / 10;
    param[12] = hour % 10;
    if (clear == 0) {
        param[3] = (int)"";
    }
    if (town == -1) {
        param[10] = (int)"";
    }
    if (name == 0) {
        param[1] = 0xe0000262;
        parts = s_logEmptyParts;
        if (flag) {
            color = 2;
        }
        else {
            color = 1;
        }
    }
    else {
        unkfunc_020629b4(s_logNameParts, &param[0], 0x10, x + index * 0x1a, color);
    }
    unkfunc_020629b4(parts, &param[0], 0x10, x + index * 0x1a, color);
}

THUMB void unkfunc_0202a274(const char* name, int clear, int level, int time)
{
    unsigned int hour = time / 216000;
    unsigned int minute = time % 216000 / 3600;
    int param[10];
    param[0] = (int)name;
    param[1] = (int)"\xff\xfe\xb9\x24";
    param[2] = 0xe0000016;
    param[3] = level;
    param[4] = hour / 100;
    param[5] = (int)"\xff\xfe\xa8\x24";
    param[6] = minute / 10;
    param[7] = minute % 10;
    param[8] = hour % 100 / 10;
    param[9] = hour % 10;
    if (clear == 0) {
        param[1] = (int)"";
    }
    unkfunc_020629b4(s_resumeNameParts, param, 0x10, 0x5a, 1);
    unkfunc_020629b4(s_resumeTimeParts, param, 0x10, 0x5a, 1);
}

// keyboard lines
THUMB void unkfunc_0202a330(int* text, int flag)
{
    int y = 0x10;
    if (flag == 1) {
        y += 0x18;
    }
    for (int i = 0, lineY = 0x44; i < 6; i++, lineY += 0xc) {
        int param[11];
        for (int j = 0; j < 11; j++) {
            param[j] = *text++;
        }
        unkfunc_020629b4(s_keyLineParts, param, 0x18, y + lineY, 1);
    }
}

// name chars
THUMB void unkfunc_0202a374(int language, unsigned int* text, int count, int max, int blink, int type)
{
    int i;
    int x = 0x8c - (max >> 1) * 0xe - (max % 2) * 7;
    int y = 0x18;
    if (type == 1) {
        x -= 8;
        y += 4;
    }
    for (i = 0; i < max; i++) {
        int param = 0;
        if (count < i) {
            param = (int)"@\x81Q";
            if (blink == 2) {
                param = (int)"@ ";
            }
        }
        else {
            param = *text;
        }
        if (count != i) {
            unkfunc_020629b4(s_nameCharParts, &param, x, y, 1);
        }
        else if (blink == 0) {
            unkfunc_020629b4(s_cursorParts, 0, x + 6, 0x28, 1);
        }
        text++;
        x += 0xc;
    }
}

// message chars
THUMB void unkfunc_0202a428(unsigned int* text, int count)
{
    for (int i = 0; i < 0x2d; i++) {
        int param = text[i];
        int x = 0;
        if (count < i) {
            param = (int)"@*";
            x = 2;
        }
        if (count != i) {
            unkfunc_020629b4(s_messageCharParts, &param, x + (i % 15) * 0xe, (i / 15) * 0x10 + 0xe, 1);
        }
        else {
            unkfunc_020629b4(s_messageCursorParts, 0, (i % 15) * 0xe + 0x1e, (i / 15) * 0x10 + 0x1c, 1);
        }
    }
}
