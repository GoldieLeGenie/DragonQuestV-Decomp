#pragma once
#include <globaldefs.h>

// Text cursor over a char buffer: read (unkfunc_0204a800 + unkfunc_0204a990/unkfunc_0204a9ec) or write (unkfunc_0204a828 +
// unkfunc_0204a9a0)
struct UnkTextIterator {
    virtual unsigned short unkfunc_0204a990() = 0;  // current char
    virtual int unkfunc_0204a9a0(int c) = 0;    // append a char
    virtual int unkfunc_0204a9ec() = 0;         // next char
    virtual int unkfunc_0204aa18() = 0;         // previous char
    virtual int unkfunc_0204aa4c() = 0;         // char count
    virtual int unkfunc_0204aa84() = 0;         // byte length

    int unk_04;                                 // 0x04
    char* buf_;                                 // 0x08
    int pos_;                                   // 0x0C
    int count_;                                 // 0x10
    int length_;                                // 0x14
    int size_;                                  // 0x18
    int countValid_;                            // 0x1C
    int lengthValid_;                           // 0x20

    UnkTextIterator();
    void unkfunc_0204a800(const char* text);
    void unkfunc_0204a814(char* text, int size);
    void unkfunc_0204a828(char* buf, int size);
    int unkfunc_0204a848();                     // cached char count
    int unkfunc_0204a864();                     // cached byte length
    void unkfunc_0204a880(int pos);             // cut the text
};

// UTF-16 text (2 bytes per char)
struct UnkUtf16Iterator : UnkTextIterator {
    UnkUtf16Iterator();
    virtual unsigned short unkfunc_0204a990();
    virtual int unkfunc_0204a9a0(int c);
    virtual int unkfunc_0204a9ec();
    virtual int unkfunc_0204aa18();
    virtual int unkfunc_0204aa4c();
    virtual int unkfunc_0204aa84();
};

// UTF-8 text (1 to 3 bytes per char)
struct UnkUtf8Iterator : UnkTextIterator {
    UnkUtf8Iterator();
    virtual unsigned short unkfunc_0204a990();
    virtual int unkfunc_0204a9a0(int c);
    virtual int unkfunc_0204a9ec();
    virtual int unkfunc_0204aa18();
    virtual int unkfunc_0204aa4c();
    virtual int unkfunc_0204aa84();
    int unkfunc_0204aaa4(const unsigned char* p);   // first byte of a char
    int unkfunc_0204aab8(const unsigned char* p);   // char size (-1: invalid)
    unsigned short unkfunc_0204aae8(const unsigned char* p);    // decode
    int unkfunc_0204ab60(unsigned char* p, int c);  // encode
};

int unkfunc_0204abcc(UnkTextIterator* src, char* buf, int size);   // read the next word
