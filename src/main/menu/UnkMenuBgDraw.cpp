#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkBgText.hpp"
#include "main/dss/UnkTextConvert.hpp"
#include "main/dss/UnkVramRequest.hpp"
#include "main/menu/UnkMenuDisplays.hpp"
#include "main/menu/UnkMenuBg.hpp"
#include "main/menu/UnkMenuSystem.hpp"
#include "main/menu/BattleMenu.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/text/TextAPI.hpp"
#include "nitro/gx.h"
#include <string.h>

int data_02105f34;
int data_02105f2c;
int data_02105f30;
UnkCharBuffer* data_02105f40;
UnkScreenBuffer* data_02105f3c;
UnkScreenBuffer* data_02105f38;

// HP gauge rows: 0-8 filled pixels, middle row and top/bottom rows, normal and low HP
static unsigned int s_gaugeOuter[9] = {0, 0x6, 0x66, 0x666, 0x6666, 0x66666, 0x666666, 0x6666666, 0x66666666};
static unsigned int s_gaugeInner[9] = {0, 0x5, 0x55, 0x555, 0x5555, 0x55555, 0x555555, 0x5555555, 0x55555555};
static unsigned int s_gaugeLowOuter[9] = {0, 0x8, 0x88, 0x888, 0x8888, 0x88888, 0x888888, 0x8888888, 0x88888888};
static unsigned int s_gaugeLowInner[9] = {0, 0x7, 0x77, 0x777, 0x7777, 0x77777, 0x777777, 0x7777777, 0x77777777};

THUMB void unkfunc_02061bd0()
{
    ui_MsgSystemInit();
}

THUMB void unkfunc_02061bd8(int redraw)
{
    UnkMenuWindowBg* window = &data_02106178.window_;
    data_02105f40 = window->unkfunc_02063708();
    data_02105f3c = window->unkfunc_0206370c();
    data_02105f38 = data_02106178.back_.getScreenBuffer();
    data_02105f34 = redraw;
    if (redraw) {
        unkfunc_0204e574(data_02105f40, 0);
        fillScreenBufferRect(data_02105f3c, 0, 0, 32, 48, 0xf000);
        fillScreenBufferRect(data_02105f38, 0, 0, 32, 48, 0xf000);
        data_02106178.icon_.unkfunc_020637f8();
        unkfunc_02064154();
    }
}

THUMB void unkfunc_02061c5c(int x, int y)
{
    data_02105f2c = x;
    data_02105f30 = y;
}

THUMB void fillMenuBackRect(int x, int y, int w, int h, int palette)
{
    if (data_02105f34 == 1) {
        fillWindowBackRect(data_02105f38, x / 8, y / 8, w / 8, h / 8, palette);
    }
}

THUMB void drawMenuWindowBack(int x, int y, int w, int h, int palette)
{
    if (data_02105f34 == 1) {
        drawWindowBack(data_02105f38, x / 8, y / 8, w / 8, h / 8, palette);
    }
}

THUMB void drawMenuWindowBorder(int x, int y, int w, int h, int palette)
{
    if (data_02105f34 == 1) {
        drawWindowBorder(data_02105f3c, x / 8, y / 8, w / 8, h / 8, palette);
    }
}

THUMB void drawMenuObjFrame(int x, int y, int w, int h, int xlu)
{
    MenuFrameDisplay* frames = &data_02114dd4.frames_;
    if (xlu) {
        frames->addRoundedFrame(x, y, w, h, 3, 15);
    } else {
        frames->addFrame(x, y, w, h, 3, 15);
    }
}

THUMB void drawMenuItemFrame(int x, int y, int w, int h, int priority, int flag)
{
    MenuFrameDisplay* frames = &data_02114dd4.frames_;
    frames->addFrame(x, y, w, h, priority, flag ? 9 : 6);
}

THUMB void drawMenuIcon(int x, int y, int w, int h, int type, int index)
{
    if (unkfunc_0204d03c()) {
        data_02106178.icon_.unkfunc_02063aac(x / 8, y / 8, w, h, type, index);
    }
}

THUMB void unkfunc_02061df8(int x, int y, int w, int h, int palette, int flip, int bank, int chr)
{
    if (data_02105f34 == 1) {
        x /= 8;
        y /= 8;
        w /= 8;
        h /= 8;
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                unkfunc_0204e60c(data_02105f40, x + i, y + j, flip, bank, chr);
            }
        }
        mapCharBufferToScreen(data_02105f3c, x, y, w, h, palette);
    }
}

THUMB int unkfunc_02061e98(int x, int y, int w, int h, int palette, int color, int align, int font, int value, int wrap,
                           int autoReturn)
{
    char buf[0x200];
    char buf2[0x200];
    char work[0x400];
    char lines[0x400];
    if (data_02105f34 == 1 && value != 0) {
        const char* text = (const char*)value;
        unsigned int type = value & 0xf0000000;
        unsigned int id = value;
        int msgId = value;
        id &= 0x0fffffff;
        if (type != 0 || id < 0x00ffffff) {
            if (type == 0) {
                type = 0x10000000;
            }
            int ex = 0;
            if (type == 0x60000000 && TextAPI::isGermanMonsterException(id)) {
                ex = 2;
            }
            g_text_extractor.extract_text(buf, sizeof(buf), type, id, ex, 0);
            if (type == 0x40000000 || type == 0x60000000) {
                translateTextPrefix(data_02099e94[0], data_02099e94[1], buf2, sizeof(buf2), buf, 1);
                dss::strcpy_s(buf, sizeof(buf), buf2);
            }
            text = buf;
        } else {
            msgId = -1;
        }
        if (msgId == -1) {
            if (text[0] == '@') {
                convertSjisToUtf8(work, sizeof(work), text + 1);
                text = work;
            }
            if ((unsigned char)text[0] == 0xff && (unsigned char)text[1] == 0xfe) {
                convertUtf16ToUtf8(work, sizeof(work), text);
                text = work;
            }
        }
        int x8;
        int right = x + w;
        int bottom = y + h;
        x8 = x / 8;
        int y8 = y / 8;
        int right8 = right / 8 + (right % 8 ? 1 : 0);
        int bottom8 = bottom / 8 + (bottom % 8 ? 1 : 0);
        mapCharBufferToScreen(data_02105f3c, x8, y8, right8 - x8, bottom8 - y8, palette);
        int size;
        if (font == 12) {
            size = 12;
        } else {
            size = 10;
        }
        if (autoReturn) {
            lines[0] = 0;
            unkfunc_020627f8(lines, text, w, 4, size);
            text = lines;
        }
        unkfunc_0204e478(size);
        unkfunc_0204dfbc(NULL, 0, 0, 0, text, wrap);
        int width = unkfunc_0204e540();
        int offsetX = 0;
        int offsetY = 0;
        if (wrap && !strchr(text, ';') && !strchr(text, '$') && width > w) {
            UnkUtf8Iterator src;
            src.setText(text);
            int breakPos = -1;
            int lineWidth = 0;
            int count = 0;
            if (src.getChar()) {
                unsigned short ch;
                do {
                    ch = src.getChar();
                    src.nextChar();
                    count++;
                    if (ch == ' ' || ch == '-' || ch == 0x3220) {
                        breakPos = count;
                    }
                    lineWidth += unkfunc_0204e1a0(NULL, 0, 0, 0, ch);
                    if (lineWidth > w) {
                        if (breakPos == -1) {
                            breakPos = count;
                        }
                        break;
                    }
                } while (ch != 0);
            }
            UnkUtf8Iterator dst;
            dst.initBuffer(buf2, sizeof(buf2));
            src.pos_ = 0;
            for (int i = 0;; i++) {
                if (i == breakPos) {
                    dst.putChar(';');
                }
                int ch = src.getChar();
                src.nextChar();
                dst.putChar(ch);
                if (ch == 0) {
                    break;
                }
            }
            text = buf2;
            unkfunc_0204dfbc(NULL, 0, 0, 0, text, wrap);
            width = unkfunc_0204e540();
            offsetX = 0;
            offsetY = 0;
        }
        switch (align) {
        case 0:
            offsetX = 0;
            break;
        case 1:
            offsetX = (w - width) / 2;
            break;
        case 2:
            offsetX = w - width;
            break;
        }
        if (wrap && !dss::strchr(text, ';') && !dss::strchr(text, '$') && !dss::strchr(text, '\n')) {
            offsetY += font / 2 + 2;
        }
        unkfunc_0204e478(size);
        int left = x + offsetX;
        if (left < 0 || y + offsetY < 0) {
            convertUtf8ToSjisWork(text);
        }
        unkfunc_0204dfbc(data_02105f40, left, y + offsetY, color, text, wrap);
        return left + unkfunc_0204e540();
    }
}

THUMB int unkfunc_02062244(int x, int y, int w, int h, int palette, int color, int align, int font, int value)
{
    char buf[0x400];
    char number[0x400];
    if (data_02105f34 == 1) {
        dss::sprintf_s(buf, sizeof(buf), "%d", value);
        translateText(data_0209a0b8[0], data_0209a0b8[1], number, sizeof(number), buf);
        return unkfunc_02061e98(x, y, w, h, palette, color, align, font, (int)number, 0, 0);
    }
}

THUMB void unkfunc_020622d8(int x, int y, int percent)
{
    if (data_02105f34 == 1) {
        if (percent <= 0) {
            percent = 0;
        } else if (percent <= 3) {
            percent = 3;
        }
        if (percent > 100) {
            percent = 100;
        }
        int length = percent * 48 / 100;
        int full = length / 8;
        int rest = length % 8;
        unkfunc_02061df8(x, y, 8, 8, 15, 0, 0, 0x1e);
        unkfunc_02061df8(x + 8, y, 48, 8, 15, 0, 0, 0x1f);
        unkfunc_02061df8(x + 56, y, 8, 8, 15, 0, 0, 0x1d);
        unsigned int* outer;
        unsigned int* inner;
        if (percent >= 25) {
            outer = s_gaugeOuter;
        } else {
            outer = s_gaugeLowOuter;
        }
        if (percent >= 25) {
            inner = s_gaugeInner;
        } else {
            inner = s_gaugeLowInner;
        }
        for (int i = 0; i < 6; i++) {
            unsigned int* tile = (unsigned int*)unkfunc_0204e564(data_02105f40, (x + 8) / 8, y / 8);
            int n = 0;
            if (i < full) {
                n = 8;
            }
            if (i == full) {
                n = rest;
            }
            tile[4] = outer[n];
            tile[5] = inner[n];
            tile[6] = outer[n];
            x += 8;
        }
    }
}

THUMB int unkfunc_020623f8(int index, const char* text)
{
    return data_02114dd4.texts_[index].unkfunc_020670f4(10, text, 0, 0);
}

THUMB void unkfunc_0206241c(int index, int x, int y, int priority, int flag)
{
    UnkMenuTextDisplay* plate = &data_02114dd4.texts_[index];
    plate->setPosition(x, y);
    plate->priority_ = priority;
    plate->frame_ = 1;
    plate->palette_ = flag ? 15 : 14;
    plate->setEnable(1);
}

THUMB void menu::BattleMenu_setHoppingNumber(int x, int y, int value, int delay)
{
    data_02114dd4.hopping_.startNumber(x, y, value, delay);
}

extern "C" THUMB void func_02062480(int index, int r, int g, int b)
{
    getBgPaletteBuffer(0)->setColor(15, index, GX_RGB(r, g, b));
}
