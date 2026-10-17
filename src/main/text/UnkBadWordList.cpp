#include "main/text/TextAPI.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkUtf8Iterator.hpp"

THUMB void UnkBadWordList::unkfunc_0206b6b4()
{
    char line[0x200];
    m_data.setup("DATA/G2D/bin/badword_ja.txt", 0, 0);
    UnkUtf8Iterator it;
    it.unkfunc_0204a800((char*)m_data.getAddr());
    while (unkfunc_0204abcc(&it, line, 0x200) != 0) {
    }
}

THUMB void UnkBadWordList::unkfunc_0206b6fc()
{
    m_data.cleanup();
}

THUMB int UnkBadWordList::unkfunc_0206b704(char* name)
{
    char buf[0x200];
    char conv[0x200];
    char line[0x200];
    if (*(unsigned char*)name == '@') {
        unkfunc_0204ae2c(buf, 0x200, name + 1);
    } else {
        dss::strcpy_s(buf, 0x200, name);
    }
    unkfunc_0204aed0(data_02099f64[1], data_02099f64[0], conv, 0x200, buf);
    unkfunc_0204aed0(data_02099e40[0], data_02099e40[1], buf, 0x200, conv);
    dss::strcpy_s(conv, 0x200, buf);
    unkfunc_0204afa8(conv);
    UnkUtf8Iterator it;
    it.unkfunc_0204a800(conv);
    while (1) {
        if (unkfunc_0204abcc(&it, line, 0x200) == 0) {
            break;
        }
        if (unkfunc_0206b7d0(line) != 0) {
            unkfunc_0204afa8(line);
            return 1;
        }
    }
    return 0;
}

THUMB int UnkBadWordList::unkfunc_0206b7d0(char* word)
{
    char line[0x200];
    char conv[0x200];
    UnkUtf8Iterator it;
    it.unkfunc_0204a800((char*)m_data.getAddr());
    while (1) {
        if (unkfunc_0204abcc(&it, line, 0x200) == 0) {
            break;
        }
        unkfunc_0204aed0(data_02099e40[0], data_02099e40[1], conv, 0x200, line);
        dss::strcpy_s(line, 0x200, conv);
        if (dss::strcmp(line, word) == 0) {
            return 1;
        }
    }
    return 0;
}
