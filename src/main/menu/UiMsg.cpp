#include "main/menu/UiMsg.hpp"
#include "main/menu/UnkMenuDisplays.hpp"
#include "main/dss/UnkBgText.hpp"
#include "main/dss/UnkTextConvert.hpp"
#include "main/dss/UnkUtf8Iterator.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/text/TextAPI.hpp"

static unsigned char s_msgSndLast;
static int s_windowType;
static int s_lang;
static int s_msgCur;
int s_msgCount;
MessageWindow* s_draw;
static int s_msgSndCur;
static int s_msgQue[16];
static unsigned char s_msgSndQue[33];

THUMB void ui_MsgSystemInit()
{
    s_draw = &data_02114dd4.message_;
    ui_MsgSndSet(0x39);
}

THUMB void ui_MsgSetup(eMessageWindow type, int lang)
{
    if (type != TALK_MESSAGE_WINDOW) {
        ui_MsgSndSet(0x39);
    }
    s_windowType = type;
    s_lang = lang;
    s_msgCur = 0;
    s_msgCount = 0;
    for (int i = 0; i < 16; i++) {
        s_msgQue[i] = 0;
    }
}

THUMB void ui_MsgAdd(int strNo)
{
    unkfunc_0206266c(strNo);
}

THUMB int ui_MsgAddSerial(int no)
{
    int count = 0;
    if (unkfunc_02062748(no) != 0) {
        return count;
    }
    unkfunc_0206266c(no);
    ui_MsgAddWaitTrigger();
    no++;
    count++;
    while (1) {
        if (TextAPI::isExistMessage(no) == 0) {
            break;
        }
        if (unkfunc_02062748(no) == 0) {
            unkfunc_0206266c(no);
            ui_MsgAddWaitTrigger();
        }
        no++;
        count++;
    }
    return count;
}

THUMB void ui_MsgAdd(const char* str)
{
    char buf[0x400];
    char name[0x80];
    s_msgQue[s_msgCount++] = 99999999;
    int snd = ui_MsgSndGet();
    buf[0] = 0x1b;
    buf[1] = '0';
    name[0] = 0;
    if (*(const unsigned char*)str == '@') {
        convertSjisToUtf8(buf + 2, 0x3fe, str + 1);
    } else {
        dss::strcpy_s(buf + 2, 0x3fe, str);
    }
    TextAPI::getMessageSound();
    if (snd == 0x39) {
        snd = '0';
    }
    buf[1] = snd;
    if (s_msgCur == 0) {
        s_draw->openWindow(s_windowType, name, buf);
    } else {
        s_draw->addText(buf);
    }
    s_msgCur++;
}

THUMB void ui_MsgAddWaitTrigger()
{
    ui_MsgOpenIfFirst();
    s_draw->addWaitKey();
}

THUMB void ui_MsgAddWait()
{
    ui_MsgOpenIfFirst();
    s_draw->unkfunc_020669f0();
}

THUMB void unkfunc_0206264c()
{
    data_02114dd4.yesNo_.setEnable(1);
}

THUMB void ui_MsgSetYesNoCursor(int cursor)
{
    data_02114dd4.yesNo_.unkfunc_020675ec(cursor);
}

THUMB void unkfunc_0206266c(int strNo)
{
    char buf[0x400];
    char name[0x80];
    s_msgQue[s_msgCount++] = strNo;
    int snd = ui_MsgSndGet();
    buf[0] = 0x1b;
    buf[1] = '0';
    TextAPI::getMessage(buf + 2, 0x400, name, 0x80, strNo);
    TextAPI::getMessageSound();
    if (snd == 0x39) {
        snd = '0';
    }
    buf[1] = snd;
    if (s_msgCur == 0) {
        s_draw->openWindow(s_windowType, "", "");
        s_draw->addText("\x1b" "A");
        s_draw->addText(buf);
        s_draw->unkfunc_02066a7c();
    } else {
        s_draw->addText("\x1b" "A");
        s_draw->addText(buf);
    }
    s_draw->unkfunc_02066aa4(name);
    s_msgCur++;
}

THUMB void ui_MsgOpenIfFirst()
{
    if (s_msgCur == 0) {
        s_draw->openWindow(s_windowType, "", "");
        s_msgCur++;
    }
}

THUMB int unkfunc_02062748(int no)
{
    for (int i = 0; i < s_msgCount; i++) {
        if (no == s_msgQue[i]) {
            return 1;
        }
    }
    return 0;
}

THUMB void ui_MsgSndSet(int no)
{
    s_msgSndCur = 0;
    for (int i = 0; i < 32; i++) {
        s_msgSndQue[i] = no;
    }
    s_msgSndQue[32] = 0x39;
    s_msgSndLast = no;
}

THUMB void ui_MsgSndSet(int* pms)
{
    int i = 0;
    while (*pms != 0x39) {
        s_msgSndQue[i++] = *pms++;
    }
    s_msgSndQue[i] = 0x39;
    s_msgSndCur = 0;
}

THUMB int ui_MsgSndGet()
{
    int snd = s_msgSndQue[s_msgSndCur];
    if (snd != 0x39) {
        s_msgSndCur++;
        return snd;
    }
    return s_msgSndLast;
}

THUMB void unkfunc_020627f8(char* dst, const char* src, int width, int lines, int font)
{
    int length = dss::strlen(src);
    int x = 0;
    setBgTextFontSize(font);
    UnkUtf8Iterator in;
    in.setText(src);
    UnkUtf8Iterator out;
    out.setBuffer(dst, 0x400);
    unsigned short c = in.getChar();
    int breakPos = -1;
    int breakLength = -1;
    int line = 0;
    while (c != 0) {
        c = in.getChar();
        in.nextChar();
        if (c == 0x1b) {
            out.putChar(c);
            c = in.getChar();
            in.nextChar();
            out.putChar(c);
            c = in.getChar();
            in.nextChar();
        }
        if (c == '\r') {
            out.putChar(c);
            c = in.getChar();
            in.nextChar();
        }
        if (c == 0x3221) {
            in.nextChar();
            int n = lines - line;
            if (line == 0 && x == 0) {
                n = 0;
            }
            for (; n != 0; n--) {
                out.putChar('\n');
                line++;
            }
            x = 0;
        } else if (c != '\n') {
            int w = drawBgChar(NULL, 0, 0, 0, c);
            out.putChar(c);
            if (c == ' ' || c == '-' || c == 0x3220) {
                breakPos = in.pos_;
                breakLength = out.getLength();
            }
            x += w;
            if (x > width) {
                if (breakPos != -1) {
                    in.pos_ = breakPos;
                    breakPos = -1;
                    out.truncate(breakLength);
                    breakLength = -1;
                }
                out.putChar('\n');
                x = 0;
                line++;
            }
        } else {
            out.putChar(c);
            x = 0;
            line++;
        }
        if (line == lines && in.getChar()) {
            out.putChar(0x328a);
            line = 0;
        }
    }
    out.putChar(0);
}
