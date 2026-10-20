#pragma ipa file
#include "main/menu/MaterielMenu_NameEdit.hpp"
#include "main/data/ExcelBinaryData.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkLanguage.hpp"
#include "main/dss/UnkTextConvert.hpp"
#include "main/dss/UnkUtf8Iterator.hpp"
#include "main/leveldata/KeyDataArpha.hpp"
#include "main/leveldata/KeyDataDire.hpp"
#include "main/leveldata/KeyDataJH.hpp"
#include "main/leveldata/KeyDataJK.hpp"
#include "main/leveldata/KeyTableArpha.hpp"
#include "main/leveldata/KeyTableDire.hpp"
#include "main/leveldata/KeyTableJH.hpp"
#include "main/leveldata/KeyTableJK.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuCasinoDraw.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/status/GameStatus.hpp"
#include "main/text/TextAPI.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::KeyDataJH* dq5::level::KeyDataJH::getRecord(int index)
{
    return (KeyDataJH*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::KeyDataJK* dq5::level::KeyDataJK::getRecord(int index)
{
    return (KeyDataJK*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::KeyDataArpha* dq5::level::KeyDataArpha::getRecord(int index)
{
    return (KeyDataArpha*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::KeyDataDire* dq5::level::KeyDataDire::getRecord(int index)
{
    return (KeyDataDire*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::KeyTableJH* dq5::level::KeyTableJH::getRecord(int index)
{
    return (KeyTableJH*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::KeyTableJK* dq5::level::KeyTableJK::getRecord(int index)
{
    return (KeyTableJK*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::KeyTableArpha* dq5::level::KeyTableArpha::getRecord(int index)
{
    return (KeyTableArpha*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::KeyTableDire* dq5::level::KeyTableDire::getRecord(int index)
{
    return (KeyTableDire*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::KeyDataJH::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::KeyDataJK::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::KeyDataArpha::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::KeyDataDire::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int UnkNameKeyboard::getSpace()
{
    return space_;
}








static int s_index[45];
static int s_keyText[66];
static unsigned int s_nameText[45];
MaterielMenu_NameEdit::EDIT_STATUS MaterielMenu_NameEdit::status_;
static int s_count;
static unsigned int s_code[45];
static int s_maxCount;

THUMB void MaterielMenu_NameEdit::menuSetup()
{
    status_ = EDIT_INIT;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    keyboard_.unkfunc_0202acd4();
    unk_88 = 0;
    language_ = status::g_Game.language_;
    inputType_ = TYPE_NAME_EDIT;
    s_maxCount = unkfunc_0202acc0();
    closeFlag_ = 0;
    cancelLock_ = 0;
}

THUMB void MaterielMenu_NameEdit::setTaishiNameMode()
{
    inputType_ = TYPE_TAISHI_NAME;
    s_maxCount = 9;
}

THUMB void MaterielMenu_NameEdit::unkfunc_0202a528()
{
    inputType_ = TYPE_MESSAGE;
    s_maxCount = 0x2d;
}

THUMB void MaterielMenu_NameEdit::menuExecute()
{
    if (closeFlag_ == 0) {
        if (inputType_ == TYPE_MESSAGE) {
            menu::MenuTemplate_materiel::MATERIEL_KEYBOARD_JAP_MESSAGE(&menuItem_);
        }
        else {
            menu::MenuTemplate_materiel::MATERIEL_KEYBOARD_JAP(&menuItem_);
        }
    }
}

THUMB void MaterielMenu_NameEdit::menuDraw()
{
    if (closeFlag_ == 0 && !gTownMenu_MESSAGE.isOpen()) {
        getNamePointer(s_nameText);
        int message = unkfunc_0202a670();
        int isMessage;
        if (inputType_ == TYPE_MESSAGE) {
            isMessage = 1;
        }
        else {
            isMessage = 0;
        }
        if (isMessage) {
            drawMenuFrame(0, 0x48, 0x100, 0x78, 0x60);
            drawMessageInput(message);
        }
        else {
            drawMenuFrame(0x38, 0x10, 0xa0, 0x20, -1);
            unkfunc_0202a6e0(message);
        }
        if (redraw_) {
            for (int i = 0; i < 0x42; i++) {
                s_keyText[i] = 0;
            }
            unkfunc_0202a610();
            drawNameEditCharTable(s_keyText, isMessage);
        }
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_NameEdit::unkfunc_0202a610()
{
    static char s_keyChar[0x14a];
    int pos = 0;
    for (int i = 0; i < 0x42; i++) {
        char* text = &s_keyChar[pos];
        s_keyText[i] = (int)text;
        if (keyboard_.unkfunc_0202b098(i)) {
            pos += unpackCharCode(keyboard_.unkfunc_0202b850(i), text);
            s_keyChar[pos] = 0;
            pos++;
        }
        else {
            s_keyText[i] = keyboard_.unkfunc_0202b850(i);
        }
    }
}

THUMB int MaterielMenu_NameEdit::unkfunc_0202a670()
{
    switch (inputType_) {
        case TYPE_MESSAGE:
            return 0xe00003c4;
        case TYPE_NAME_EDIT:
            return 0xe00002d0;
        case TYPE_TAISHI_NAME:
            return 0xe00003c1;
    }
    return 0;
}

THUMB void MaterielMenu_NameEdit::drawMessageInput(int message)
{
    unkfunc_0202a428(s_nameText, s_count);
    drawMenuFrame(0, 0, 0x100, 0x48, -1);
    drawCenteredMessage(&message, 8, 0x4a, 0xf0, 0x58);
}

THUMB void MaterielMenu_NameEdit::unkfunc_0202a6e0(int message)
{
    int blink = 0;
    if (cursorTimer_ > 30) {
        cursorTimer_ = 0;
    }
    if (cursorTimer_ >= 15) {
        blink = 1;
    }
    cursorTimer_++;
    unkfunc_0202a374(language_, s_nameText, s_count, s_maxCount, blink, 0);
    drawMenuFrame(0, 0x30, 0x100, 0x78, 0x48);
    drawCenteredMessage(&message, 8, 0x4a, 0xf0, 0x2c);
}

THUMB void MaterielMenu_NameEdit::menuUpdate()
{
    if (closeFlag_) {
        close();
        return;
    }
    if (status_ == EDIT_INIT) {
        status_ = EXEC;
    }
    if (status_ == EXEC && !gTownMenu_MESSAGE.isOpen()) {
        commandUpdate();
    }
}

THUMB void MaterielMenu_NameEdit::commandUpdate()
{
    int active = menuItem_.active_;
    int result = menuItem_.execInput();
    if (result != menu::MenuItem::MENUITEM_RESULT_NONE) {
        if (result == menu::MenuItem::MENUITEM_RESULT_OK) {
            menuItem_.result_ = 0;
            menuItem_.lastresult_ = 0;
            unsigned int code = keyboard_.unkfunc_0202ad54();
            int index = keyboard_.index_;
            if (code & 0x80000000) {
                unkfunc_0202a9fc();
            }
            else {
                unkfunc_0202a8a4(index, code);
            }
            redraw_ = 1;
        }
        if (result == menu::MenuItem::MENUITEM_RESULT_CANCEL || result == menu::MenuItem::MENUITEM_RESULT_SUPERCANCEL) {
            menuItem_.result_ = 0;
            menuItem_.lastresult_ = 0;
            if (s_count == 0) {
                if (cancelLock_ == 0) {
                    endMenu(CANCEL);
                }
            }
            else {
                deleteLastChar();
                redraw_ = 1;
            }
        }
        if (result == menu::MenuItem::MENUITEM_RESULT_CHANGE) {
            int move = active - menuItem_.active_;
            if (move == -1) {
                result = menu::MenuItem::MENUITEM_RESULT_RIGHT;
            }
            if (move == 1) {
                result = menu::MenuItem::MENUITEM_RESULT_LEFT;
            }
            if (move < -1) {
                result = menu::MenuItem::MENUITEM_RESULT_DOWN;
            }
            if (move > 1) {
                result = menu::MenuItem::MENUITEM_RESULT_UP;
            }
        }
        if (result == menu::MenuItem::MENUITEM_RESULT_UP) {
            menuItem_.active_ = keyboard_.unkfunc_0202b200();
        }
        if (result == menu::MenuItem::MENUITEM_RESULT_DOWN) {
            menuItem_.active_ = keyboard_.unkfunc_0202b20c();
        }
        if (result == menu::MenuItem::MENUITEM_RESULT_LEFT) {
            menuItem_.active_ = keyboard_.unkfunc_0202b218();
        }
        if (result == menu::MenuItem::MENUITEM_RESULT_RIGHT) {
            menuItem_.active_ = keyboard_.unkfunc_0202b224();
        }
    }
    else if ((dss::g_Pad.edge() & 8) && s_count > 0) {
        menuItem_.active_ = keyboard_.unkfunc_0202b82c(0x41);
    }
}

THUMB void MaterielMenu_NameEdit::unkfunc_0202a8a4(int index, unsigned int code)
{
    int max = s_maxCount;
    if (s_count < max) {
        s_count++;
    }
    s_code[s_count - 1] = code;
    s_index[s_count - 1] = index;
    if (s_count == max) {
        menuItem_.active_ = keyboard_.unkfunc_0202b82c(0x41);
    }
}

THUMB void MaterielMenu_NameEdit::unkfunc_0202a8e4(int index, unsigned int code)
{
    int count = s_count;
    if (count > 0) {
        s_code[count - 1] = code;
        s_index[count - 1] = index;
    }
    else {
        s_code[0] = code;
        s_index[0] = index;
    }
    if (count == s_maxCount) {
        menuItem_.active_ = keyboard_.unkfunc_0202b82c(0x41);
    }
}

THUMB void MaterielMenu_NameEdit::deleteLastChar()
{
    if (s_count > 0) {
        s_count--;
        s_code[s_count] = 0;
        s_index[s_count] = 0;
    }
}

THUMB bool MaterielMenu_NameEdit::judgeNameEnable()
{
    bool space = true;
    int badWord = 0;
    for (int i = 0; i < s_count; i++) {
        getNameUTF8();
        unsigned int code = s_code[i];
        if (code != keyboard_.space_) {
            space = false;
        }
    }
    if (space) {
        clearName();
        menuItem_.active_ = 0;
        keyboard_.unkfunc_0202b82c(0);
        return false;
    }
    if (CheckBadWord(getNameUTF8())) {
        badWord = true;
    }
    if (inputType_ == TYPE_NAME_EDIT) {
        if (unkfunc_0206cea4(getNameUTF8())) {
            badWord = 1;
        }
    }
    if (badWord) {
        endMenu(ERROR_S);
        return false;
    }
    if (s_count > 0) {
        return true;
    }
    return false;
}

THUMB void MaterielMenu_NameEdit::unkfunc_0202a9fc()
{
    unsigned int code = s_code[0];
    int index = s_index[0];
    if (s_count > 0) {
        code = s_code[s_count - 1];
        index = s_index[s_count - 1];
    }
    switch (keyboard_.unkfunc_0202b74c()) {
        case 1:
            deleteLastChar();
            break;
        case 5:
            if (judgeNameEnable()) {
                endMenu(COMPLETE);
            }
            break;
        case 2:
        case 3:
            if (s_count > 0) {
                code = keyboard_.unkfunc_0202b0f4(index, code);
                index = keyboard_.unkfunc_0202b1c4(index);
                if (code != -1) {
                    unkfunc_0202a8e4(index, code);
                }
            }
            break;
    }
}

THUMB void MaterielMenu_NameEdit::endMenu(EDIT_STATUS status)
{
    keyboard_.unkfunc_0202ad28();
    close();
    status_ = status;
}

THUMB void MaterielMenu_NameEdit::clearName()
{
    for (int i = 0; i < 0x2d; i++) {
        s_code[i] = (unsigned int)"@\x81@";
        s_index[i] = 0;
        s_nameText[i] = 0;
    }
    s_count = 0;
}

THUMB char* MaterielMenu_NameEdit::getNameUTF8()
{
    static char s_name[0x89];
    static char s_nameUTF8[0x89];
    int length = 0;
    for (int i = 0; i < s_count; i++) {
        length += unpackCharCode(s_code[i], &s_nameUTF8[length]);
    }
    s_nameUTF8[length] = 0;
    unkfunc_0204afa8(s_nameUTF8);
    UnkUtf8Iterator src;
    src.unkfunc_0204a800(s_nameUTF8);
    UnkUtf8Iterator dst;
    dst.unkfunc_0204a828(s_name, 0x89);
    while (true) {
        int c = src.unkfunc_0204a990();
        src.unkfunc_0204a9ec();
        if (c == 0) {
            break;
        }
        switch (c) {
            case 0x24d5:
                c = 0x80;
                break;
            case 0x24d6:
                c = 0x81;
                break;
            case 0x24d7:
                c = 0x82;
                break;
            case 0x24d8:
                c = 0x83;
                break;
            case 0x24d9:
                c = 0x84;
                break;
            case 0x24c6:
                c = 0x85;
                break;
        }
        dst.unkfunc_0204a9a0(c);
    }
    return s_name;
}

THUMB void MaterielMenu_NameEdit::getNamePointer(unsigned int* pointer)
{
    static char s_nameChar[0xb5];
    int pos = 0;
    for (int i = 0; i < s_count; i++) {
        pointer[i] = (unsigned int)&s_nameChar[pos];
        pos += unpackCharCode(s_code[i], &s_nameChar[pos]);
        s_nameChar[pos] = 0;
        pos++;
    }
}

THUMB int MaterielMenu_NameEdit::unpackCharCode(unsigned int code, char* buf)
{
    int size = 0;
    for (int i = 3; i >= 0; i--) {
        unsigned char c = code >> (i * 8);
        if (c) {
            buf[size++] = c;
        }
    }
    return size;
}

THUMB void MaterielMenu_NameEdit::setDefaultName(const char* str)
{
    unsigned int code = 0;
    int rest = 0;
    for (int i = 0; (unsigned char)str[i] != 0; i++) {
        unsigned int c = (unsigned char)str[i];
        if ((c | 0x3f) == 0x3f) {
            rest = 0;
        }
        if ((c | 0x1f) == 0xdf) {
            rest = 1;
        }
        if ((c | 0x0f) == 0xef) {
            rest = 2;
        }
        if (rest == 0) {
            code |= c;
        }
        else {
            code |= c << (rest * 8);
        }
        if (--rest < 0) {
            unkfunc_0202ac90(code);
            code = 0;
            rest = 0;
        }
    }
    keyboard_.page_ = 0;
}

THUMB void MaterielMenu_NameEdit::unkfunc_0202ac90(unsigned int code)
{
    s_code[s_count] = code;
    s_index[s_count] = keyboard_.unkfunc_0202b040(code);
    s_count++;
}

THUMB int MaterielMenu_NameEdit::unkfunc_0202acc0()
{
    if (unkfunc_020464e8() == 1) {
        return 4;
    }
    return 8;
}

THUMB void UnkNameKeyboard::unkfunc_0202acd4()
{
    index_ = 0;
    keyCount_ = 0x42;
    page_ = 0;
    japanese_ = unkfunc_020464e8() == 1;
    if (japanese_) {
        dq5::level::KeyDataJH::setup();
        dq5::level::KeyDataJK::setup();
        dq5::level::KeyTableJH::setup();
        dq5::level::KeyTableJK::setup();
        space_ = 0xe38080;
    }
    else {
        dq5::level::KeyDataArpha::setup();
        dq5::level::KeyDataDire::setup();
        dq5::level::KeyTableArpha::setup();
        dq5::level::KeyTableDire::setup();
        space_ = 0x20;
    }
}

THUMB void UnkNameKeyboard::unkfunc_0202ad28()
{
    if (japanese_) {
        dq5::level::KeyDataJH::cleanup();
        dq5::level::KeyDataJK::cleanup();
        dq5::level::KeyTableJH::cleanup();
        dq5::level::KeyTableJK::cleanup();
    }
    else {
        dq5::level::KeyDataArpha::cleanup();
        dq5::level::KeyDataDire::cleanup();
        dq5::level::KeyTableArpha::cleanup();
        dq5::level::KeyTableDire::cleanup();
    }
}

THUMB unsigned int UnkNameKeyboard::unkfunc_0202ad54()
{
    switch (unkfunc_0202b758(index_)) {
        case 0:
            return unkfunc_0202ad80();
        case 4:
            return unkfunc_0202b1ec();
    }
    return 0x80000000;
}

THUMB unsigned int UnkNameKeyboard::unkfunc_0202ad80()
{
    if (japanese_) {
        if (page_ == 0) {
            return dq5::level::KeyDataJH::getRecord(index_)->Data;
        }
        else {
            return dq5::level::KeyDataJK::getRecord(index_)->Data;
        }
    }
    else {
        if (page_ == 0) {
            return dq5::level::KeyDataArpha::getRecord(index_)->Data;
        }
        else {
            return dq5::level::KeyDataDire::getRecord(index_)->Data;
        }
    }
}

THUMB unsigned int UnkNameKeyboard::unkfunc_0202ae3c(int index)
{
    if (japanese_) {
        if (page_ == 0) {
            return dq5::level::KeyDataJH::getRecord(index)->Data;
        }
        else {
            return dq5::level::KeyDataJK::getRecord(index)->Data;
        }
    }
    else {
        if (page_ == 0) {
            return dq5::level::KeyDataArpha::getRecord(index)->Data;
        }
        else {
            return dq5::level::KeyDataDire::getRecord(index)->Data;
        }
    }
}

THUMB unsigned short UnkNameKeyboard::unkfunc_0202aef0(int index)
{
    if (japanese_) {
        if (page_ == 0) {
            return dq5::level::KeyDataJH::getRecord(index)->No;
        }
        else {
            return dq5::level::KeyDataJK::getRecord(index)->No;
        }
    }
    else {
        if (page_ == 0) {
            return dq5::level::KeyDataArpha::getRecord(index)->No;
        }
        else {
            return dq5::level::KeyDataDire::getRecord(index)->No;
        }
    }
}

THUMB unsigned int UnkNameKeyboard::unkfunc_0202afa4()
{
    if (japanese_) {
        if (page_ != 0) {
            return dq5::level::KeyDataJK::getArraySize();
        }
        else {
            return dq5::level::KeyDataJH::getArraySize();
        }
    }
    else {
        if (page_ != 0) {
            return dq5::level::KeyDataDire::getArraySize();
        }
        else {
            return dq5::level::KeyDataArpha::getArraySize();
        }
    }
}

THUMB unsigned int UnkNameKeyboard::unkfunc_0202afdc(int no)
{
    int count = unkfunc_0202afa4();
    for (int i = 0; i < count; i++) {
        if (no == unkfunc_0202aef0(i)) {
            return unkfunc_0202ae3c(i);
        }
    }
    return -1;
}

THUMB int UnkNameKeyboard::unkfunc_0202b010(int no)
{
    unsigned int count = unkfunc_0202afa4();
    for (unsigned int i = 0; i < count; i++) {
        if (no == unkfunc_0202aef0(i)) {
            return i;
        }
    }
    return -1;
}

THUMB int UnkNameKeyboard::unkfunc_0202b040(unsigned int code)
{
    unsigned int count = unkfunc_0202afa4();
    for (unsigned int i = 0; i < count; i++) {
        if (code == unkfunc_0202ae3c(i)) {
            return i;
        }
    }
    unkfunc_0202b1ec();
    count = unkfunc_0202afa4();
    for (unsigned int i = 0; i < count; i++) {
        if (code == unkfunc_0202ae3c(i)) {
            return i;
        }
    }
    return -1;
}

THUMB int UnkNameKeyboard::unkfunc_0202b098(int position)
{
    int result = 0;
    if (unkfunc_0202b880(position) == 0 || unkfunc_0202b850(position) == getSpace() || unkfunc_0202b880(position) == 2
        || unkfunc_0202b880(position) == 3) {
        result = 1;
    }
    return result;
}

THUMB int UnkNameKeyboard::unkfunc_0202b0d4(int no)
{
    if (unkfunc_0202b74c() == 2) {
        no += 100;
    }
    if (unkfunc_0202b74c() == 3) {
        no += 200;
    }
    return no;
}

THUMB unsigned int UnkNameKeyboard::unkfunc_0202b0f4(int index, unsigned int code)
{
    if (!japanese_) {
        return -1;
    }
    int switched = 0;
    if (code != unkfunc_0202ae3c(index)) {
        switched = 1;
        unkfunc_0202b1ec();
    }
    int no = unkfunc_0202b15c(index);
    if (no == -1) {
        if (switched) {
            unkfunc_0202b1ec();
        }
        return no;
    }
    unsigned int result = unkfunc_0202afdc(unkfunc_0202b0d4(no));
    if (switched) {
        unkfunc_0202b1ec();
    }
    return result;
}

THUMB int UnkNameKeyboard::unkfunc_0202b15c(int index)
{
    int no = unkfunc_0202aef0(index);
    if (!japanese_) {
        return no;
    }
    switch (unkfunc_0202b74c()) {
        case 2:
            if (unkfunc_0202aef0(index) > 200) {
                no -= 200;
            }
            else if (unkfunc_0202aef0(index) > 100) {
                return -1;
            }
            break;
        case 3:
            if (unkfunc_0202aef0(index) > 200) {
                return -1;
            }
            if (unkfunc_0202aef0(index) > 100) {
                no -= 100;
            }
            break;
    }
    return no;
}

THUMB int UnkNameKeyboard::unkfunc_0202b1c4(int index)
{
    if (!japanese_) {
        return -1;
    }
    int no = unkfunc_0202b15c(index);
    return unkfunc_0202b010(unkfunc_0202b0d4(no));
}

THUMB unsigned int UnkNameKeyboard::unkfunc_0202b1ec()
{
    if (page_) {
        page_ = 0;
    }
    else {
        page_ = 1;
    }
    return 0x80000000;
}

THUMB int UnkNameKeyboard::unkfunc_0202b200()
{
    return unkfunc_0202b230(0);
}

THUMB int UnkNameKeyboard::unkfunc_0202b20c()
{
    return unkfunc_0202b230(1);
}

THUMB int UnkNameKeyboard::unkfunc_0202b218()
{
    return unkfunc_0202b230(2);
}

THUMB int UnkNameKeyboard::unkfunc_0202b224()
{
    return unkfunc_0202b230(3);
}

THUMB int UnkNameKeyboard::unkfunc_0202b230(int dir)
{
    int i = 0;
    while (!unkfunc_0202b798(dir, i)) {
        i++;
    }
    index_ = i;
    return unkfunc_0202b698(i);
}

THUMB unsigned char UnkNameKeyboard::unkfunc_0202b260(int index)
{
    if (japanese_) {
        if (page_ == 0) {
            return dq5::level::KeyTableJH::getRecord(index)->No;
        }
        else {
            return dq5::level::KeyTableJK::getRecord(index)->No;
        }
    }
    else {
        if (page_ == 0) {
            return dq5::level::KeyTableArpha::getRecord(index)->No;
        }
        else {
            return dq5::level::KeyTableDire::getRecord(index)->No;
        }
    }
}

THUMB unsigned char UnkNameKeyboard::unkfunc_0202b314(int index)
{
    if (japanese_) {
        if (page_ == 0) {
            return dq5::level::KeyTableJH::getRecord(index)->Up;
        }
        else {
            return dq5::level::KeyTableJK::getRecord(index)->Up;
        }
    }
    else {
        if (page_ == 0) {
            return dq5::level::KeyTableArpha::getRecord(index)->Up;
        }
        else {
            return dq5::level::KeyTableDire::getRecord(index)->Up;
        }
    }
}

THUMB unsigned char UnkNameKeyboard::unkfunc_0202b3c8(int index)
{
    if (japanese_) {
        if (page_ == 0) {
            return dq5::level::KeyTableJH::getRecord(index)->down;
        }
        else {
            return dq5::level::KeyTableJK::getRecord(index)->down;
        }
    }
    else {
        if (page_ == 0) {
            return dq5::level::KeyTableArpha::getRecord(index)->down;
        }
        else {
            return dq5::level::KeyTableDire::getRecord(index)->down;
        }
    }
}

THUMB unsigned char UnkNameKeyboard::unkfunc_0202b47c(int index)
{
    if (japanese_) {
        if (page_ == 0) {
            return dq5::level::KeyTableJH::getRecord(index)->left;
        }
        else {
            return dq5::level::KeyTableJK::getRecord(index)->left;
        }
    }
    else {
        if (page_ == 0) {
            return dq5::level::KeyTableArpha::getRecord(index)->left;
        }
        else {
            return dq5::level::KeyTableDire::getRecord(index)->left;
        }
    }
}

THUMB unsigned char UnkNameKeyboard::unkfunc_0202b530(int index)
{
    if (japanese_) {
        if (page_ == 0) {
            return dq5::level::KeyTableJH::getRecord(index)->right;
        }
        else {
            return dq5::level::KeyTableJK::getRecord(index)->right;
        }
    }
    else {
        if (page_ == 0) {
            return dq5::level::KeyTableArpha::getRecord(index)->right;
        }
        else {
            return dq5::level::KeyTableDire::getRecord(index)->right;
        }
    }
}

THUMB unsigned char UnkNameKeyboard::unkfunc_0202b5e4(int index)
{
    if (japanese_) {
        if (page_ == 0) {
            return dq5::level::KeyTableJH::getRecord(index)->command;
        }
        else {
            return dq5::level::KeyTableJK::getRecord(index)->command;
        }
    }
    else {
        if (page_ == 0) {
            return dq5::level::KeyTableArpha::getRecord(index)->command;
        }
        else {
            return dq5::level::KeyTableDire::getRecord(index)->command;
        }
    }
}

THUMB unsigned char UnkNameKeyboard::unkfunc_0202b698(int index)
{
    if (japanese_) {
        if (page_ == 0) {
            return dq5::level::KeyTableJH::getRecord(index)->position;
        }
        else {
            return dq5::level::KeyTableJK::getRecord(index)->position;
        }
    }
    else {
        if (page_ == 0) {
            return dq5::level::KeyTableArpha::getRecord(index)->position;
        }
        else {
            return dq5::level::KeyTableDire::getRecord(index)->position;
        }
    }
}

THUMB int UnkNameKeyboard::unkfunc_0202b74c()
{
    return unkfunc_0202b758(index_);
}

THUMB int UnkNameKeyboard::unkfunc_0202b758(int index)
{
    switch (unkfunc_0202b5e4(index)) {
        case 1:
            return 0;
        case 5:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 6:
            return 5;
        case 4:
            return 4;
    }
    return 6;
}

THUMB int UnkNameKeyboard::unkfunc_0202b798(int dir, int index)
{
    switch (dir) {
        case 0:
            return unkfunc_0202b314(index_) == unkfunc_0202b260(index);
        case 1:
            return unkfunc_0202b3c8(index_) == unkfunc_0202b260(index);
        case 2:
            return unkfunc_0202b47c(index_) == unkfunc_0202b260(index);
        case 3:
            return unkfunc_0202b530(index_) == unkfunc_0202b260(index);
    }
    return 0;
}

THUMB int UnkNameKeyboard::unkfunc_0202b82c(int position)
{
    for (int i = 0; i < 0x42; i++) {
        if (position == unkfunc_0202b698(i)) {
            index_ = i;
            return position;
        }
    }
    return 0;
}

THUMB unsigned int UnkNameKeyboard::unkfunc_0202b850(int position)
{
    for (int i = 0; i < keyCount_; i++) {
        if (position == unkfunc_0202b698(i)) {
            return unkfunc_0202ae3c(i);
        }
    }
    return 0;
}

THUMB int UnkNameKeyboard::unkfunc_0202b880(int position)
{
    for (int i = 0; i < keyCount_; i++) {
        if (position == unkfunc_0202b698(i)) {
            return unkfunc_0202b758(i);
        }
    }
    return 6;
}
