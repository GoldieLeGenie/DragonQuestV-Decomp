#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// key layout of the name entry keyboard (KeyTable/KeyData level data, kana or alphabet pages)
struct UnkNameKeyboard {
    int index_;                                 // 0x00 key under the cursor
    int page_;                                  // 0x04 0: hiragana / alphabet, 1: katakana / accented letters
    int japanese_;                              // 0x08
    int keyCount_;                              // 0x0C
    unsigned int space_;                        // 0x10 code of the space char

    void setup();                    // setup
    void cleanup();                    // cleanup
    unsigned int getPressedCode();            // code of the pressed key (0x80000000: special key)
    unsigned int getCursorCode();            // code of the key under the cursor
    unsigned int getCode(int index);   // code of a key
    unsigned short getCharNo(int index); // char number of a key
    unsigned int getKeyDataCount();            // key data count
    unsigned int getCodeOfCharNo(int no);      // code of a char number
    int getKeyOfCharNo(int no);               // key of a char number
    int getKeyOfCode(unsigned int code);    // key of a code
    int isTextKey(int position);         // 1: key drawn as a text
    int getDakutenCharNo(int no);               // char number with the (han)dakuten of the current key
    unsigned int getDakutenCode(int index, unsigned int code);  // code with (han)dakuten (-1: none)
    int getBaseCharNo(int index);            // char number without (han)dakuten (-1: none)
    int getDakutenKey(int index);            // key with (han)dakuten (-1: none)
    unsigned int switchPage();            // switch the page
    int moveCursorUp();                     // cursor up
    int moveCursorDown();                     // cursor down
    int moveCursorLeft();                     // cursor left
    int moveCursorRight();                     // cursor right
    int moveCursor(int dir);
    unsigned char getTableNo(int index);  // key table No
    unsigned char getTableUp(int index);  // key table Up
    unsigned char getTableDown(int index);  // key table down
    unsigned char getTableLeft(int index);  // key table left
    unsigned char getTableRight(int index);  // key table right
    unsigned char getTableCommand(int index);  // key table command
    unsigned char getTablePosition(int index);  // key table position
    int getCursorKeyType();                     // type of the key under the cursor
    int getKeyType(int index);            // type of a key
    int isNeighbourKey(int dir, int index);   // 1: index is the neighbour of the cursor key
    int setCursorPosition(int position);         // move the cursor to a position
    unsigned int getCodeAtPosition(int position);    // code of the key at a position
    int getKeyTypeAtPosition(int position);         // type of the key at a position
    unsigned int getSpace();
};

// name entry keyboard menu
struct MaterielMenu_NameEdit : menu::MenuBase {
    enum INPUT_TYPE {
        TYPE_NAME_EDIT = 0,
        TYPE_TAISHI_NAME = 1,
        TYPE_MESSAGE = 2,
        TYPE_NULL = 3,
    };
    enum EDIT_STATUS {
        EDIT_INIT = 0,                          // INIT in the mobile port (macro name here)
        EXEC = 1,
        CANCEL = 2,
        ERROR_S = 3,
        COMPLETE = 4,
    };

    menu::MenuItem menuItem_;                   // 0x1C
    int language_;                                 // 0x80
    INPUT_TYPE inputType_;                      // 0x84
    int unk_88;                                 // 0x88
    int unk_8C;                                 // 0x8C
    int cursorTimer_;                           // 0x90
    UnkNameKeyboard keyboard_;                  // 0x94
    int closeFlag_;                             // 0xA8
    int cancelLock_;                            // 0xAC

    static EDIT_STATUS status_;

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();

    void setNonCancelMode();
    void setInputType(INPUT_TYPE type);
    void setTaishiNameMode();
    void setMessageMode();
    void clearName();
    char* getNameUTF8();
    void setDefaultName(const char* name);
    void buildKeyLabels();                    // texts of the keys
    int getPromptMessage();                     // title message
    void drawMessageInput(int message);         // draw the message input window
    void drawNameInput(int message);         // draw the name input window
    void commandUpdate();
    void appendChar(int index, unsigned int code);   // add a char
    void replaceLastChar(int index, unsigned int code);   // replace the last char
    void deleteLastChar();                    // delete the last char
    bool judgeNameEnable();
    void onSpecialKey();                    // special key
    void endMenu(EDIT_STATUS status);
    void getNamePointer(unsigned int* pointer);
    int unpackCharCode(unsigned int code, char* buf);    // UTF-8 bytes of a code
    void appendDefaultChar(unsigned int code);   // add a char of the default name
    int getNameMaxCount();                     // max char count of a name
};

extern MaterielMenu_NameEdit gMaterielMenu_NameEdit;
