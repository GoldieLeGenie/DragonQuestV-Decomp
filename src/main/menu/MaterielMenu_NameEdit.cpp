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
    keyboard_.setup();
    unk_88 = 0;
    language_ = status::g_Game.language_;
    inputType_ = TYPE_NAME_EDIT;
    s_maxCount = getNameMaxCount();
    closeFlag_ = 0;
    cancelLock_ = 0;
}

THUMB void MaterielMenu_NameEdit::setTaishiNameMode()
{
    inputType_ = TYPE_TAISHI_NAME;
    s_maxCount = 9;
}

THUMB void MaterielMenu_NameEdit::setMessageMode()
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
        int message = getPromptMessage();
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
            drawNameInput(message);
        }
        if (redraw_) {
            for (int i = 0; i < 0x42; i++) {
                s_keyText[i] = 0;
            }
            buildKeyLabels();
            drawNameEditCharTable(s_keyText, isMessage);
        }
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_NameEdit::buildKeyLabels()
{
    static char s_keyChar[0x14a];
    int pos = 0;
    for (int i = 0; i < 0x42; i++) {
        char* text = &s_keyChar[pos];
        s_keyText[i] = (int)text;
        if (keyboard_.isTextKey(i)) {
            pos += unpackCharCode(keyboard_.getCodeAtPosition(i), text);
            s_keyChar[pos] = 0;
            pos++;
        }
        else {
            s_keyText[i] = keyboard_.getCodeAtPosition(i);
        }
    }
}

THUMB int MaterielMenu_NameEdit::getPromptMessage()
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
    drawNameEditCommentField(s_nameText, s_count);
    drawMenuFrame(0, 0, 0x100, 0x48, -1);
    drawCenteredMessage(&message, 8, 0x4a, 0xf0, 0x58);
}

THUMB void MaterielMenu_NameEdit::drawNameInput(int message)
{
    int blink = 0;
    if (cursorTimer_ > 30) {
        cursorTimer_ = 0;
    }
    if (cursorTimer_ >= 15) {
        blink = 1;
    }
    cursorTimer_++;
    drawNameEditField(language_, s_nameText, s_count, s_maxCount, blink, 0);
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
            unsigned int code = keyboard_.getPressedCode();
            int index = keyboard_.index_;
            if (code & 0x80000000) {
                onSpecialKey();
            }
            else {
                appendChar(index, code);
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
            menuItem_.active_ = keyboard_.moveCursorUp();
        }
        if (result == menu::MenuItem::MENUITEM_RESULT_DOWN) {
            menuItem_.active_ = keyboard_.moveCursorDown();
        }
        if (result == menu::MenuItem::MENUITEM_RESULT_LEFT) {
            menuItem_.active_ = keyboard_.moveCursorLeft();
        }
        if (result == menu::MenuItem::MENUITEM_RESULT_RIGHT) {
            menuItem_.active_ = keyboard_.moveCursorRight();
        }
    }
    else if ((dss::g_Pad.edge() & 8) && s_count > 0) {
        menuItem_.active_ = keyboard_.setCursorPosition(0x41);
    }
}

THUMB void MaterielMenu_NameEdit::appendChar(int index, unsigned int code)
{
    int max = s_maxCount;
    if (s_count < max) {
        s_count++;
    }
    s_code[s_count - 1] = code;
    s_index[s_count - 1] = index;
    if (s_count == max) {
        menuItem_.active_ = keyboard_.setCursorPosition(0x41);
    }
}

THUMB void MaterielMenu_NameEdit::replaceLastChar(int index, unsigned int code)
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
        menuItem_.active_ = keyboard_.setCursorPosition(0x41);
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
        keyboard_.setCursorPosition(0);
        return false;
    }
    if (CheckBadWord(getNameUTF8())) {
        badWord = true;
    }
    if (inputType_ == TYPE_NAME_EDIT) {
        if (isNameTooWide(getNameUTF8())) {
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

THUMB void MaterielMenu_NameEdit::onSpecialKey()
{
    unsigned int code = s_code[0];
    int index = s_index[0];
    if (s_count > 0) {
        code = s_code[s_count - 1];
        index = s_index[s_count - 1];
    }
    switch (keyboard_.getCursorKeyType()) {
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
                code = keyboard_.getDakutenCode(index, code);
                index = keyboard_.getDakutenKey(index);
                if (code != -1) {
                    replaceLastChar(index, code);
                }
            }
            break;
    }
}

THUMB void MaterielMenu_NameEdit::endMenu(EDIT_STATUS status)
{
    keyboard_.cleanup();
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
    convertUtf8ToSjisWork(s_nameUTF8);
    UnkUtf8Iterator src;
    src.setText(s_nameUTF8);
    UnkUtf8Iterator dst;
    dst.initBuffer(s_name, 0x89);
    while (true) {
        int c = src.getChar();
        src.nextChar();
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
        dst.putChar(c);
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
            appendDefaultChar(code);
            code = 0;
            rest = 0;
        }
    }
    keyboard_.page_ = 0;
}

THUMB void MaterielMenu_NameEdit::appendDefaultChar(unsigned int code)
{
    s_code[s_count] = code;
    s_index[s_count] = keyboard_.getKeyOfCode(code);
    s_count++;
}

THUMB int MaterielMenu_NameEdit::getNameMaxCount()
{
    if (getGameRegion() == 1) {
        return 4;
    }
    return 8;
}

THUMB void UnkNameKeyboard::setup()
{
    index_ = 0;
    keyCount_ = 0x42;
    page_ = 0;
    japanese_ = getGameRegion() == 1;
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

THUMB void UnkNameKeyboard::cleanup()
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

THUMB unsigned int UnkNameKeyboard::getPressedCode()
{
    switch (getKeyType(index_)) {
        case 0:
            return getCursorCode();
        case 4:
            return switchPage();
    }
    return 0x80000000;
}

THUMB unsigned int UnkNameKeyboard::getCursorCode()
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

THUMB unsigned int UnkNameKeyboard::getCode(int index)
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

THUMB unsigned short UnkNameKeyboard::getCharNo(int index)
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

THUMB unsigned int UnkNameKeyboard::getKeyDataCount()
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

THUMB unsigned int UnkNameKeyboard::getCodeOfCharNo(int no)
{
    int count = getKeyDataCount();
    for (int i = 0; i < count; i++) {
        if (no == getCharNo(i)) {
            return getCode(i);
        }
    }
    return -1;
}

THUMB int UnkNameKeyboard::getKeyOfCharNo(int no)
{
    unsigned int count = getKeyDataCount();
    for (unsigned int i = 0; i < count; i++) {
        if (no == getCharNo(i)) {
            return i;
        }
    }
    return -1;
}

THUMB int UnkNameKeyboard::getKeyOfCode(unsigned int code)
{
    unsigned int count = getKeyDataCount();
    for (unsigned int i = 0; i < count; i++) {
        if (code == getCode(i)) {
            return i;
        }
    }
    switchPage();
    count = getKeyDataCount();
    for (unsigned int i = 0; i < count; i++) {
        if (code == getCode(i)) {
            return i;
        }
    }
    return -1;
}

THUMB int UnkNameKeyboard::isTextKey(int position)
{
    int result = 0;
    if (getKeyTypeAtPosition(position) == 0 || getCodeAtPosition(position) == getSpace() || getKeyTypeAtPosition(position) == 2
        || getKeyTypeAtPosition(position) == 3) {
        result = 1;
    }
    return result;
}

THUMB int UnkNameKeyboard::getDakutenCharNo(int no)
{
    if (getCursorKeyType() == 2) {
        no += 100;
    }
    if (getCursorKeyType() == 3) {
        no += 200;
    }
    return no;
}

THUMB unsigned int UnkNameKeyboard::getDakutenCode(int index, unsigned int code)
{
    if (!japanese_) {
        return -1;
    }
    int switched = 0;
    if (code != getCode(index)) {
        switched = 1;
        switchPage();
    }
    int no = getBaseCharNo(index);
    if (no == -1) {
        if (switched) {
            switchPage();
        }
        return no;
    }
    unsigned int result = getCodeOfCharNo(getDakutenCharNo(no));
    if (switched) {
        switchPage();
    }
    return result;
}

THUMB int UnkNameKeyboard::getBaseCharNo(int index)
{
    int no = getCharNo(index);
    if (!japanese_) {
        return no;
    }
    switch (getCursorKeyType()) {
        case 2:
            if (getCharNo(index) > 200) {
                no -= 200;
            }
            else if (getCharNo(index) > 100) {
                return -1;
            }
            break;
        case 3:
            if (getCharNo(index) > 200) {
                return -1;
            }
            if (getCharNo(index) > 100) {
                no -= 100;
            }
            break;
    }
    return no;
}

THUMB int UnkNameKeyboard::getDakutenKey(int index)
{
    if (!japanese_) {
        return -1;
    }
    int no = getBaseCharNo(index);
    return getKeyOfCharNo(getDakutenCharNo(no));
}

THUMB unsigned int UnkNameKeyboard::switchPage()
{
    if (page_) {
        page_ = 0;
    }
    else {
        page_ = 1;
    }
    return 0x80000000;
}

THUMB int UnkNameKeyboard::moveCursorUp()
{
    return moveCursor(0);
}

THUMB int UnkNameKeyboard::moveCursorDown()
{
    return moveCursor(1);
}

THUMB int UnkNameKeyboard::moveCursorLeft()
{
    return moveCursor(2);
}

THUMB int UnkNameKeyboard::moveCursorRight()
{
    return moveCursor(3);
}

THUMB int UnkNameKeyboard::moveCursor(int dir)
{
    int i = 0;
    while (!isNeighbourKey(dir, i)) {
        i++;
    }
    index_ = i;
    return getTablePosition(i);
}

THUMB unsigned char UnkNameKeyboard::getTableNo(int index)
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

THUMB unsigned char UnkNameKeyboard::getTableUp(int index)
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

THUMB unsigned char UnkNameKeyboard::getTableDown(int index)
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

THUMB unsigned char UnkNameKeyboard::getTableLeft(int index)
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

THUMB unsigned char UnkNameKeyboard::getTableRight(int index)
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

THUMB unsigned char UnkNameKeyboard::getTableCommand(int index)
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

THUMB unsigned char UnkNameKeyboard::getTablePosition(int index)
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

THUMB int UnkNameKeyboard::getCursorKeyType()
{
    return getKeyType(index_);
}

THUMB int UnkNameKeyboard::getKeyType(int index)
{
    switch (getTableCommand(index)) {
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

THUMB int UnkNameKeyboard::isNeighbourKey(int dir, int index)
{
    switch (dir) {
        case 0:
            return getTableUp(index_) == getTableNo(index);
        case 1:
            return getTableDown(index_) == getTableNo(index);
        case 2:
            return getTableLeft(index_) == getTableNo(index);
        case 3:
            return getTableRight(index_) == getTableNo(index);
    }
    return 0;
}

THUMB int UnkNameKeyboard::setCursorPosition(int position)
{
    for (int i = 0; i < 0x42; i++) {
        if (position == getTablePosition(i)) {
            index_ = i;
            return position;
        }
    }
    return 0;
}

THUMB unsigned int UnkNameKeyboard::getCodeAtPosition(int position)
{
    for (int i = 0; i < keyCount_; i++) {
        if (position == getTablePosition(i)) {
            return getCode(i);
        }
    }
    return 0;
}

THUMB int UnkNameKeyboard::getKeyTypeAtPosition(int position)
{
    for (int i = 0; i < keyCount_; i++) {
        if (position == getTablePosition(i)) {
            return getKeyType(i);
        }
    }
    return 6;
}
