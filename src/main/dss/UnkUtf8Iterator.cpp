#pragma ipa file

#include "main/dss/UnkTextConvert.hpp"

unsigned short data_02099e40[2][21] = {
    {
        0x3042, 0x3044, 0x3046, 0x3048, 0x304a, 0x3064, 0x3084, 0x3086,
        0x3088, 0x308f, 0x30a2, 0x30a4, 0x30a6, 0x30a8, 0x30aa, 0x30c4,
        0x30e4, 0x30e6, 0x30e8, 0x30ef, 0x0000,
    },
    {
        0x3041, 0x3043, 0x3045, 0x3047, 0x3049, 0x3063, 0x3083, 0x3085,
        0x3087, 0x308e, 0x30a1, 0x30a3, 0x30a5, 0x30a7, 0x30a9, 0x30c3,
        0x30e3, 0x30e5, 0x30e7, 0x30ee, 0x0000,
    },
};

unsigned short data_02099e94[2][52] = {
    {
        0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048,
        0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f, 0x0050,
        0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058,
        0x0059, 0x005a, 0x0152, 0x00c0, 0x00c1, 0x00c2, 0x00c4, 0x00c7,
        0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
        0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d8, 0x00d9,
        0x00da, 0x00db, 0x00dc, 0x0000,
    },
    {
        0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068,
        0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f, 0x0070,
        0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078,
        0x0079, 0x007a, 0x0153, 0x00e0, 0x00e1, 0x00e2, 0x00e4, 0x00e7,
        0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
        0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f8, 0x00f9,
        0x00fa, 0x00fb, 0x00fc, 0x0000,
    },
};

// Unicode tables of the Shift-JIS lead bytes 0x81-0x9F and 0xE0-0xEF (file data, set by initSjisTables)
int s_size81;
int s_sizeE0;
unsigned short* s_table81;
unsigned short* s_tableE0;
unsigned char data_020f679c[0x800];

unsigned short data_0209a0b8[2][96] = {
    {
        0x3000, 0xff01, 0x201d, 0xff03, 0xff04, 0xff05, 0xff06, 0x2019,
        0xff08, 0xff09, 0xff0a, 0xff0b, 0xff0c, 0xff0d, 0xff0e, 0xff0f,
        0xff10, 0xff11, 0xff12, 0xff13, 0xff14, 0xff15, 0xff16, 0xff17,
        0xff18, 0xff19, 0xff1a, 0xff1b, 0xff1c, 0xff1d, 0xff1e, 0xff1f,
        0xff20, 0xff21, 0xff22, 0xff23, 0xff24, 0xff25, 0xff26, 0xff27,
        0xff28, 0xff29, 0xff2a, 0xff2b, 0xff2c, 0xff2d, 0xff2e, 0xff2f,
        0xff30, 0xff31, 0xff32, 0xff33, 0xff34, 0xff35, 0xff36, 0xff37,
        0xff38, 0xff39, 0xff3a, 0xff3b, 0xffe5, 0xff3d, 0xff3e, 0xff3f,
        0xff40, 0xff41, 0xff42, 0xff43, 0xff44, 0xff45, 0xff46, 0xff47,
        0xff48, 0xff49, 0xff4a, 0xff4b, 0xff4c, 0xff4d, 0xff4e, 0xff4f,
        0xff50, 0xff51, 0xff52, 0xff53, 0xff54, 0xff55, 0xff56, 0xff57,
        0xff58, 0xff59, 0xff5a, 0xff5b, 0xff5c, 0xff5d, 0xffe3, 0x0000,
    },
    {
        0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
        0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
        0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
        0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
        0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
        0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
        0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
        0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
        0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
        0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
        0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
        0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x0000,
    },
};

unsigned short data_02099f64[2][85] = {
    {
        0x30a1, 0x30a2, 0x30a3, 0x30a4, 0x30a5, 0x30a6, 0x30a7, 0x30a8,
        0x30a9, 0x30aa, 0x30ab, 0x30ac, 0x30ad, 0x30ae, 0x30af, 0x30b0,
        0x30b1, 0x30b2, 0x30b3, 0x30b4, 0x30b5, 0x30b6, 0x30b7, 0x30b8,
        0x30b9, 0x30ba, 0x30bb, 0x30bc, 0x30bd, 0x30be, 0x30bf, 0x30c0,
        0x30c1, 0x30c2, 0x30c3, 0x30c4, 0x30c5, 0x30c6, 0x30c7, 0x30c8,
        0x30c9, 0x30ca, 0x30cb, 0x30cc, 0x30cd, 0x30ce, 0x30cf, 0x30d0,
        0x30d1, 0x30d2, 0x30d3, 0x30d4, 0x30d5, 0x30d6, 0x30d7, 0x30d8,
        0x30d9, 0x30da, 0x30db, 0x30dc, 0x30dd, 0x30de, 0x30df, 0x30e0,
        0x30e1, 0x30e2, 0x30e3, 0x30e4, 0x30e5, 0x30e6, 0x30e7, 0x30e8,
        0x30e9, 0x30ea, 0x30eb, 0x30ec, 0x30ed, 0x30ee, 0x30ef, 0x30f0,
        0x30f1, 0x30f2, 0x30f3, 0xff0d, 0x0000,
    },
    {
        0x3041, 0x3042, 0x3043, 0x3044, 0x3045, 0x3046, 0x3047, 0x3048,
        0x3049, 0x304a, 0x304b, 0x304c, 0x304d, 0x304e, 0x304f, 0x3050,
        0x3051, 0x3052, 0x3053, 0x3054, 0x3055, 0x3056, 0x3057, 0x3058,
        0x3059, 0x305a, 0x305b, 0x305c, 0x305d, 0x305e, 0x305f, 0x3060,
        0x3061, 0x3062, 0x3063, 0x3064, 0x3065, 0x3066, 0x3067, 0x3068,
        0x3069, 0x306a, 0x306b, 0x306c, 0x306d, 0x306e, 0x306f, 0x3070,
        0x3071, 0x3072, 0x3073, 0x3074, 0x3075, 0x3076, 0x3077, 0x3078,
        0x3079, 0x307a, 0x307b, 0x307c, 0x307d, 0x307e, 0x307f, 0x3080,
        0x3081, 0x3082, 0x3083, 0x3084, 0x3085, 0x3086, 0x3087, 0x3088,
        0x3089, 0x308a, 0x308b, 0x308c, 0x308d, 0x308e, 0x308f, 0x3090,
        0x3091, 0x3092, 0x3093, 0x30fc, 0x0000,
    },
};

THUMB UnkTextIterator::UnkTextIterator()
{
    unk_04 = 0;
    buf_ = NULL;
    pos_ = 0;
    count_ = 0;
    length_ = 0;
    size_ = 0;
    countValid_ = 0;
    lengthValid_ = 0;
}

THUMB void UnkTextIterator::setText(const char* text)
{
    buf_ = (char*)text;
    pos_ = 0;
    count_ = 0;
    countValid_ = 0;
    length_ = 0;
    lengthValid_ = 0;
    size_ = 0;
}

THUMB void UnkTextIterator::setBuffer(char* text, int size)
{
    buf_ = text;
    pos_ = 0;
    count_ = 0;
    countValid_ = 0;
    length_ = 0;
    lengthValid_ = 0;
    size_ = size;
}

THUMB void UnkTextIterator::initBuffer(char* buf, int size)
{
    buf_ = buf;
    pos_ = 0;
    count_ = 0;
    countValid_ = 0;
    length_ = 0;
    lengthValid_ = 0;
    size_ = size;
    buf_[pos_] = 0;
    buf_[pos_ + 1] = 0;
}

THUMB int UnkTextIterator::getCount()
{
    if (countValid_ == 0) {
        count_ = countChars();
        countValid_ = 1;
    }
    return count_;
}

THUMB int UnkTextIterator::getLength()
{
    if (lengthValid_ == 0) {
        length_ = getByteLength();
        lengthValid_ = 1;
    }
    return length_;
}

THUMB void UnkTextIterator::truncate(int pos)
{
    buf_[pos] = 0;
    countValid_ = 0;
    lengthValid_ = 0;
}

THUMB UnkUtf16Iterator::UnkUtf16Iterator()
{
    unk_04 = 2;
}

THUMB unsigned short UnkUtf16Iterator::getChar()
{
    return (unsigned short)(((unsigned char)buf_[pos_ + 1] << 8) | (unsigned char)buf_[pos_]);
}

THUMB int UnkUtf16Iterator::putChar(int c)
{
    getCount();
    int length = getLength();
    if (length + 4 > (unsigned int)size_) {
        return 0;
    }
    buf_[length] = c;
    (buf_ + length)[1] = c >> 8;
    (buf_ + length)[2] = 0;
    (buf_ + length)[3] = 0;
    count_++;
    length_ += 2;
    return 1;
}

THUMB int UnkUtf16Iterator::nextChar()
{
    if (UnkUtf16Iterator::getChar() == 0) {
        return 0;
    }
    pos_ += 2;
    return 1;
}

THUMB int UnkUtf16Iterator::prevChar()
{
    if (pos_ == 0) {
        return 0;
    }
    pos_ -= 2;
    return 1;
}

THUMB int UnkUtf16Iterator::countChars()
{
    if (buf_ == NULL) {
        return 0;
    }
    int pos = pos_;
    int count = 0;
    pos_ = 0;
    while (nextChar()) {
        count++;
    }
    pos_ = pos;
    return count;
}

THUMB int UnkUtf16Iterator::getByteLength()
{
    if (buf_ == NULL) {
        return 0;
    }
    return UnkUtf16Iterator::countChars() * 2;
}

THUMB UnkUtf8Iterator::UnkUtf8Iterator()
{
    unk_04 = 1;
}

THUMB unsigned short UnkUtf8Iterator::getChar()
{
    return decodeChar((unsigned char*)buf_ + pos_);
}

THUMB int UnkUtf8Iterator::putChar(int c)
{
    getCount();
    int length = getLength();
    if (length + 4 > (unsigned int)size_) {
        return 0;
    }
    int size = encodeChar((unsigned char*)buf_ + length, c);
    if (length_ + size < (unsigned int)size_) {
        count_++;
        length_ += size;
        return 1;
    }
    buf_[length] = 0;
    return 0;
}

THUMB int UnkUtf8Iterator::nextChar()
{
    int size = getCharSize((unsigned char*)buf_ + pos_);
    if (size == -1) {
        return 0;
    }
    if (size == 0) {
        return 0;
    }
    pos_ += size;
    return 1;
}

THUMB int UnkUtf8Iterator::prevChar()
{
    if (pos_ == 0) {
        return 0;
    }
    while (pos_ != 0) {
        pos_--;
        if (isLeadByte((unsigned char*)buf_ + pos_) == 1) {
            break;
        }
    }
    return 1;
}

THUMB int UnkUtf8Iterator::countChars()
{
    if (buf_ == NULL) {
        return 0;
    }
    int pos = pos_;
    getCharSize((unsigned char*)buf_);
    int count = 0;
    pos_ = 0;
    while (nextChar()) {
        count++;
    }
    pos_ = pos;
    return count;
}

THUMB int UnkUtf8Iterator::getByteLength()
{
    if (buf_ == NULL) {
        return 0;
    }
    int length = 0;
    for (const unsigned char* p = (unsigned char*)buf_; *p != 0; p++) {
        length++;
    }
    return length;
}

THUMB int UnkUtf8Iterator::isLeadByte(const unsigned char* p)
{
    return (*p & 0xc0) != 0x80;
}

THUMB int UnkUtf8Iterator::getCharSize(const unsigned char* p)
{
    unsigned char c = *p;
    if (c == 0) {
        return 0;
    }
    if ((c & 0x80) == 0) {
        return 1;
    }
    if ((c & 0xe0) == 0xc0) {
        return 2;
    }
    if ((c & 0xf0) == 0xe0) {
        return 3;
    }
    return -1;
}

THUMB unsigned short UnkUtf8Iterator::decodeChar(const unsigned char* p)
{
    int size = getCharSize(p);
    if (size == 0) {
        return 0;
    }
    if (size == 1) {
        return p[0];
    }
    if (size == 2) {
        unsigned short c0 = p[0] & 0x1f;
        unsigned short c1 = p[1] & 0x3f;
        return (unsigned short)((unsigned short)(c0 << 6) | c1);
    }
    if (size == 3) {
        unsigned short c0 = p[0];
        unsigned short c1 = p[1];
        unsigned short c2 = p[2] & 0x3f;
        c0 = c0 & 0xf;
        c0 = c0 << 12;
        c1 = c1 & 0x3f;
        c1 = c1 << 6;
        return (unsigned short)(c0 | c1 | c2);
    }
    return 0xffff;
}

THUMB int UnkUtf8Iterator::encodeChar(unsigned char* p, int c)
{
    if ((unsigned int)c <= 0x7f) {
        p[0] = c & 0x7f;
        p[1] = 0;
        return 1;
    }
    if ((unsigned int)c <= 0x7ff) {
        p[0] = ((c >> 6) & 0x1f) | 0xc0;
        p[1] = (c & 0x3f) | 0x80;
        p[2] = 0;
        return 2;
    }
    p[0] = ((c >> 12) & 0xf) | 0xe0;
    p[1] = ((c >> 6) & 0x3f) | 0x80;
    p[2] = (c & 0x3f) | 0x80;
    p[3] = 0;
    return 3;
}

static inline int isSeparator(int c)
{
    int separator = 0;
    if (c == 9) {
        separator = 1;
    }
    if (c == 0x20) {
        separator = 1;
    }
    if (c == 0xd) {
        separator = 1;
    }
    if (c == 0xa) {
        separator = 1;
    }
    if (c == 0x3000) {
        separator = 1;
    }
    if (c == 0xff0e) {
        separator = 1;
    }
    if (c == 0x2026) {
        separator = 1;
    }
    if (c == 0xff1f) {
        separator = 1;
    }
    if (c == 0xff01) {
        separator = 1;
    }
    return separator;
}

THUMB int readNextWord(UnkTextIterator* src, char* buf, int size)
{
    int found = 0;
    UnkUtf8Iterator dst;
    dst.initBuffer(buf, size);
    while (true) {
        int c = src->getChar();
        if (c == 0 || c == 0xffff) {
            break;
        }
        if (!isSeparator(c)) {
            break;
        }
        src->nextChar();
    }
    while (true) {
        int c = src->getChar();
        src->nextChar();
        if (c == 0 || c == 0xffff || c == 9 || c == 0x20 || c == 0xd || c == 0xa || c == 0x3000 || c == 0xff0e ||
            c == 0x2026 || c == 0xff1f || c == 0xff01) {
            break;
        }
        dst.putChar(c);
        found = 1;
    }
    return found;
}

THUMB void initSjisTables(unsigned short* table81, int size81, unsigned short* tableE0, int sizeE0)
{
    s_table81 = table81;
    s_tableE0 = tableE0;
    s_size81 = size81;
    s_sizeE0 = sizeE0;
    data_020f679c[0] = '\0';
}

THUMB int convertUtf16ToUtf8(char* dst, int size, const char* src)
{
    UnkUtf8Iterator out;
    out.initBuffer(dst, size);
    UnkUtf16Iterator in;
    in.setText(src);
    while (true) {
        int c = in.getChar();
        in.nextChar();
        if (c == 0) {
            break;
        }
        if (c == 0xffff) {
            return 0;
        }
        out.putChar(c);
    }
    return 1;
}

THUMB unsigned short unicodeToSjis(unsigned short c)
{
    unsigned short* table;
    unsigned int n;
    unsigned int i;
    if (c <= 0x1f) {
        return c;
    }
    if (c <= 0x7f) {
        return c;
    }
    if (c <= 0xff) {
        return 0x3f;
    }
    table = s_table81;
    n = (unsigned int)s_size81 / 2;
    for (i = 0; i < n; i++) {
        if (c == table[i]) {
            return (unsigned short)(i + 0x8100);
        }
    }
    table = s_tableE0;
    n = (unsigned int)s_sizeE0 / 2;
    for (i = 0; i < n; i++) {
        if (c == table[i]) {
            return (unsigned short)(i + 0xe000);
        }
    }
    return 0x3f;
}

THUMB int convertUtf8ToSjis(char* dst, unsigned int size, const char* src)
{
    UnkUtf8Iterator in;
    in.setText(src);
    unsigned int length = 0;
    while (true) {
        unsigned short c = in.getChar();
        in.nextChar();
        if (c == 0) {
            break;
        }
        if (c == 0xffff) {
            return 0;
        }
        unsigned short code = unicodeToSjis(c);
        if (code <= 0xff) {
            *dst++ = code;
            length++;
        } else {
            *dst++ = code >> 8;
            *dst++ = code;
            length += 2;
        }
        if (length > size - 2) {
            return 0;
        }
    }
    dst[0] = 0;
    dst[1] = 0;
    return 1;
}

THUMB int convertSjisToUtf8(char* dst, int size, const char* src)
{
    UnkUtf8Iterator out;
    out.initBuffer(dst, size);
    const unsigned char* p = (const unsigned char*)src;
    while (*p != 0) {
        if (*p <= 0x7f) {
            out.putChar(*p++);
        } else {
            unsigned char lead = *p++;
            unsigned char trail = *p++;
            unsigned short* table = NULL;
            if (lead >= 0x81 && lead <= 0x9f) {
                lead -= 0x81;
                table = s_table81;
            }
            if (lead >= 0xe0 && lead <= 0xef) {
                lead -= 0xe0;
                table = s_tableE0;
            }
            if (table != NULL && table[trail + (lead << 8)] != 0) {
                out.putChar(table[trail + (lead << 8)]);
            }
        }
    }
    return 1;
}

THUMB int translateChar(unsigned short* from, unsigned short* to, int c)
{
    while (*to != 0) {
        if (c == *to) {
            return *from;
        }
        to++;
        from++;
    }
    return c;
}

THUMB int translateText(unsigned short* from, unsigned short* to, char* dst, int size, const char* src)
{
    UnkUtf8Iterator in;
    in.setText(src);
    UnkUtf8Iterator out;
    out.initBuffer(dst, size);
    while (true) {
        int c = in.getChar();
        if (c == 0) {
            break;
        }
        if (c == 0xffff) {
            return 0;
        }
        in.nextChar();
        out.putChar(translateChar(from, to, c));
    }
    return 1;
}

THUMB int translateTextPrefix(unsigned short* from, unsigned short* to, char* dst, int size, const char* src, int count)
{
    UnkUtf8Iterator in;
    in.setText(src);
    UnkUtf8Iterator out;
    out.initBuffer(dst, size);
    while (true) {
        int c = in.getChar();
        if (c == 0) {
            break;
        }
        if (c == 0xffff) {
            return 0;
        }
        in.nextChar();
        if (count > 0) {
            c = translateChar(from, to, c);
            count--;
        }
        out.putChar(c);
    }
    return 1;
}

THUMB char* convertUtf8ToSjisWork(const char* src)
{
    convertUtf8ToSjis((char*)data_020f679c, sizeof(data_020f679c), src);
    for (int i = 0; data_020f679c[i] != 0; i++) {
        if (data_020f679c[i] == 0xa) {
            data_020f679c[i] = 0x7c;
        }
    }
    return (char*)data_020f679c;
}
