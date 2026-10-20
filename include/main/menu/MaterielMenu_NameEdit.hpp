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

    void unkfunc_0202acd4();                    // setup
    void unkfunc_0202ad28();                    // cleanup
    unsigned int unkfunc_0202ad54();            // code of the pressed key (0x80000000: special key)
    unsigned int unkfunc_0202ad80();            // code of the key under the cursor
    unsigned int unkfunc_0202ae3c(int index);   // code of a key
    unsigned short unkfunc_0202aef0(int index); // char number of a key
    unsigned int unkfunc_0202afa4();            // key data count
    unsigned int unkfunc_0202afdc(int no);      // code of a char number
    int unkfunc_0202b010(int no);               // key of a char number
    int unkfunc_0202b040(unsigned int code);    // key of a code
    int unkfunc_0202b098(int position);         // 1: key drawn as a text
    int unkfunc_0202b0d4(int no);               // char number with the (han)dakuten of the current key
    unsigned int unkfunc_0202b0f4(int index, unsigned int code);  // code with (han)dakuten (-1: none)
    int unkfunc_0202b15c(int index);            // char number without (han)dakuten (-1: none)
    int unkfunc_0202b1c4(int index);            // key with (han)dakuten (-1: none)
    unsigned int unkfunc_0202b1ec();            // switch the page
    int unkfunc_0202b200();                     // cursor up
    int unkfunc_0202b20c();                     // cursor down
    int unkfunc_0202b218();                     // cursor left
    int unkfunc_0202b224();                     // cursor right
    int unkfunc_0202b230(int dir);
    unsigned char unkfunc_0202b260(int index);  // key table No
    unsigned char unkfunc_0202b314(int index);  // key table Up
    unsigned char unkfunc_0202b3c8(int index);  // key table down
    unsigned char unkfunc_0202b47c(int index);  // key table left
    unsigned char unkfunc_0202b530(int index);  // key table right
    unsigned char unkfunc_0202b5e4(int index);  // key table command
    unsigned char unkfunc_0202b698(int index);  // key table position
    int unkfunc_0202b74c();                     // type of the key under the cursor
    int unkfunc_0202b758(int index);            // type of a key
    int unkfunc_0202b798(int dir, int index);   // 1: index is the neighbour of the cursor key
    int unkfunc_0202b82c(int position);         // move the cursor to a position
    unsigned int unkfunc_0202b850(int position);    // code of the key at a position
    int unkfunc_0202b880(int position);         // type of the key at a position
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
    void unkfunc_0202a528();
    void clearName();
    char* getNameUTF8();
    void setDefaultName(const char* name);
    void unkfunc_0202a610();                    // texts of the keys
    int unkfunc_0202a670();                     // title message
    void drawMessageInput(int message);         // draw the message input window
    void unkfunc_0202a6e0(int message);         // draw the name input window
    void commandUpdate();
    void unkfunc_0202a8a4(int index, unsigned int code);   // add a char
    void unkfunc_0202a8e4(int index, unsigned int code);   // replace the last char
    void deleteLastChar();                    // delete the last char
    bool judgeNameEnable();
    void unkfunc_0202a9fc();                    // special key
    void endMenu(EDIT_STATUS status);
    void getNamePointer(unsigned int* pointer);
    int unpackCharCode(unsigned int code, char* buf);    // UTF-8 bytes of a code
    void unkfunc_0202ac90(unsigned int code);   // add a char of the default name
    int unkfunc_0202acc0();                     // max char count of a name
};

extern MaterielMenu_NameEdit gMaterielMenu_NameEdit;
