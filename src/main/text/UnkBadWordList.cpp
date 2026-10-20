#include "main/text/TextAPI.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkUtf8Iterator.hpp"

THUMB void UnkBadWordList::load()
{
    char line[0x200];
    m_data.setup("DATA/G2D/bin/badword_ja.txt", 0, 0);
    UnkUtf8Iterator it;
    it.setText((char*)m_data.getAddr());
    while (readNextWord(&it, line, 0x200) != 0) {
    }
}

THUMB void UnkBadWordList::unload()
{
    m_data.cleanup();
}

THUMB int UnkBadWordList::containsBadWord(char* name)
{
    char buf[0x200];
    char conv[0x200];
    char line[0x200];
    if (*(unsigned char*)name == '@') {
        convertSjisToUtf8(buf, 0x200, name + 1);
    } else {
        dss::strcpy_s(buf, 0x200, name);
    }
    translateText(data_02099f64[1], data_02099f64[0], conv, 0x200, buf);
    translateText(data_02099e40[0], data_02099e40[1], buf, 0x200, conv);
    dss::strcpy_s(conv, 0x200, buf);
    convertUtf8ToSjisWork(conv);
    UnkUtf8Iterator it;
    it.setText(conv);
    while (1) {
        if (readNextWord(&it, line, 0x200) == 0) {
            break;
        }
        if (isBadWord(line) != 0) {
            convertUtf8ToSjisWork(line);
            return 1;
        }
    }
    return 0;
}

THUMB int UnkBadWordList::isBadWord(char* word)
{
    char line[0x200];
    char conv[0x200];
    UnkUtf8Iterator it;
    it.setText((char*)m_data.getAddr());
    while (1) {
        if (readNextWord(&it, line, 0x200) == 0) {
            break;
        }
        translateText(data_02099e40[0], data_02099e40[1], conv, 0x200, line);
        dss::strcpy_s(line, 0x200, conv);
        if (dss::strcmp(line, word) == 0) {
            return 1;
        }
    }
    return 0;
}
