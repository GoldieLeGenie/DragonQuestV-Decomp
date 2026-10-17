#include "main/text/TextAPI.hpp"
#include "main/dss/DssUtils.hpp"

unsigned char TextAPI::m_msg_last_sound;
int TextAPI::m_extra;
int TextAPI::m_lang;
static int s_folderSet;
static char s_folder1[0x80];
int data_0211b7d8;
char TextAPI::m_work2[0x80];
static char s_folder2[0x80];
static char s_work[0x200];
char TextAPI::m_work1[0x200];

THUMB void TextAPI::setLanguage(int language)
{
    m_lang = language;
    if (language == 0) {
        data_02105fcc = 0;
    } else {
        data_02105fcc = 1;
    }
}

THUMB void TextAPI::setMACRO0(int slot, int type, int value, int value2, int value3)
{
    g_text_env.add_msg_var(slot, 0, type, value, value2, value3);
}

THUMB void TextAPI::setMACRO0(int slot, int type, int value, int value2)
{
    g_text_env.add_msg_var(slot, 0, type, value, value2);
}

THUMB void TextAPI::setMACRO0(int slot, int type, int value)
{
    g_text_env.add_msg_var(slot, 0, type, value);
}

THUMB void TextAPI::setMACRO1(int slot, int type, int value)
{
    g_text_env.add_msg_var(slot, 1, type, value);
}

THUMB void TextAPI::setMACRO2(int slot, int type, int value)
{
    g_text_env.add_msg_var(slot, 2, type, value);
}

THUMB void TextAPI::setMACRO3(int slot, int type, int value)
{
    g_text_env.add_msg_var(slot, 3, type, value);
}

THUMB void TextAPI::setMACRO4(int slot, int type, int value)
{
    g_text_env.add_msg_var(slot, 4, type, value);
}

THUMB void TextAPI::setMACRO5(int slot, int type, int value)
{
    g_text_env.add_msg_var(slot, 5, type, value);
}

THUMB void TextAPI::resetMacro()
{
    g_text_env.resetMacro();
}

THUMB int TextAPI::isExistMessage(int messageID)
{
    return unkfunc_0206ce14(messageID, m_lang);
}

THUMB void TextAPI::getMessage(char* message, int messageSize, int messageID)
{
    unkfunc_0206ce28(messageID, m_lang);
    dss::strcpy_s(s_work, 0x200, msg_get_body());
    g_text_env.process_msg(message, messageSize, s_work);
}

THUMB void TextAPI::getMessage(char* message, int messageSize, char* name, int nameSize, int messageID)
{
    unkfunc_0206ce28(messageID, m_lang);
    dss::strcpy_s(m_work1, 0x200, msg_get_body());
    dss::strcpy_s(m_work2, 0x80, msg_get_head());
    m_msg_last_sound = msg_get_sound();
    g_text_env.process_msg(message, messageSize, m_work1);
    g_text_env.process_msg(name, nameSize, m_work2);
}

THUMB int TextAPI::getMessageSound()
{
    return m_msg_last_sound;
}

THUMB void unkfunc_0206c6bc(const char* folder1, const char* folder2)
{
    dss::strcpy_s(s_folder1, 0x80, folder1);
    dss::strcpy_s(s_folder2, 0x80, folder2);
    s_folderSet = 1;
}

THUMB const char* unkfunc_0206c6e8(int msg_id)
{
    if (s_folderSet == 0) {
        return NULL;
    }
    if (msg_id < 1000000) {
        return s_folder1;
    }
    return s_folder2;
}

THUMB void TextAPI::getMonsterNamePlateTextImitation(char* text, int monsterIndex, int flag)
{
    MsgVar var;
    char work[0x200];
    char upper[0x200];
    char name[0x200];

    var.set(1, 0, 0x60000000, monsterIndex, 0, -1);
    int opt = 0;
    if (isGermanMonsterException(monsterIndex)) {
        opt = 2;
    }
    var.extract_var(work, 0x200, opt);
    unkfunc_0204af38(data_02099e94[0], data_02099e94[1], upper, 0x200, work, 1);
    g_text_extractor.extractText(name, 0x200, 0xf0000000, flag);
    if (flag == 1) {
        dss::sprintf(text, "%s", upper);
    } else {
        dss::sprintf(text, "%s  %s%s", upper, "\xe2\x92\xa9", name);
    }
}

THUMB void TextAPI::getPlayerNamePlateTextImitation(char* text, int playerIndex, int flag)
{
    MsgVar var;
    char work[0x200];
    char upper[0x200];
    char name[0x200];

    var.set(1, 0, 0x50000000, playerIndex, 1, -1);
    var.extract_var(work, 0x200, 0);
    unkfunc_0204af38(data_02099e94[0], data_02099e94[1], upper, 0x200, work, 1);
    g_text_extractor.extractText(name, 0x200, 0xf0000000, flag);
    if (flag == 1) {
        dss::sprintf(text, "%s", upper);
    } else {
        dss::sprintf(text, "%s  %s%s", upper, "\xe2\x92\xa9", name);
    }
}

THUMB int TextAPI::extractText(char* text, int size, int type, int value)
{
    return g_text_extractor.extractText(text, size, type, value);
}

THUMB void TextAPI::setHeroName(char* name)
{
    g_text_extractor.setHeroName(name);
}

THUMB MACRO_STAT TextAPI::getMacroStat()
{
    return g_text_extractor.m_macro_stat;
}

THUMB void TextAPI::setMacroStat(MACRO_STAT stat)
{
    g_text_extractor.m_macro_stat = stat;
}

THUMB void TextAPI::setUserString(int index, char* string)
{
    g_text_extractor.setUserString(index, string);
}

THUMB int TextAPI::isGermanMonsterException(int monsterIndex)
{
    int result = 0;
    if (m_lang == 3) {
        switch (monsterIndex) {
            case 0x11:
            case 0x23:
            case 0x2f:
            case 0x32:
            case 0x38:
            case 0x52:
            case 0xe4:
                result = 1;
                break;
        }
    }
    return result;
}

THUMB bool TextAPI::isGirlieName(const char* name)
{
    UnkUtf8Iterator it;
    it.unkfunc_0204a800(name);
    int count = it.unkfunc_0204a848();
    switch (count) {
    case 2:
        break;
    case 3:
        it.unkfunc_0204a9ec();
        break;
    case 4:
        it.unkfunc_0204a9ec();
        it.unkfunc_0204a9ec();
        break;
    default:
        return false;
    }
    char* last2 = it.buf_ + it.pos_;
    it.unkfunc_0204a9ec();
    char* last = it.buf_ + it.pos_;
    const char* ko = "\xe3\x81\x93";
    if (count == 3) {
        if (dss::strcmp(last, ko) == 0) {
            return true;
        }
        if (dss::strcmp(last, "\xe3\x82\xb3") == 0) {
            return true;
        }
    }
    if (count == 2 || count == 3) {
        if (dss::strcmp(last, "\xe3\x81\xbf") == 0) {
            return true;
        }
        if (dss::strcmp(last, "\xe3\x83\x9f") == 0) {
            return true;
        }
        if (dss::strcmp(last, "\xe3\x81\x88") == 0) {
            return true;
        }
        if (dss::strcmp(last, "\xe3\x82\xa8") == 0) {
            return true;
        }
    }
    if (count == 4) {
        if (dss::strcmp(last2, "\xe3\x82\x8a\xe3\x82\x93") == 0) {
            return true;
        }
        if (dss::strcmp(last2, "\xe3\x83\xaa\xe3\x83\xb3") == 0) {
            return true;
        }
    }
    return false;
}

THUMB int TextAPI::splitMessage(int msg_id, unsigned char* line0, unsigned char* line1, unsigned char* line2,
                                unsigned char* line3, unsigned char* line4, unsigned char* line5, unsigned char* line6,
                                unsigned char* line7)
{
    unsigned char* lines[8];
    UnkUtf8Iterator src;
    UnkUtf8Iterator dst;
    char buf[0x200];
    int count = 0;
    lines[0] = line0;
    if (line0 != NULL) {
        line0[0] = 0;
    }
    lines[1] = line1;
    if (line1 != NULL) {
        line1[0] = 0;
    }
    lines[2] = line2;
    if (line2 != NULL) {
        line2[0] = 0;
    }
    lines[3] = line3;
    if (line3 != NULL) {
        line3[0] = 0;
    }
    lines[4] = line4;
    if (line4 != NULL) {
        line4[0] = 0;
    }
    lines[5] = line5;
    if (line5 != NULL) {
        line5[0] = 0;
    }
    lines[6] = line6;
    if (line6 != NULL) {
        line6[0] = 0;
    }
    lines[7] = line7;
    if (line7 != NULL) {
        line7[0] = 0;
    }
    getMessage(buf, 0x200, msg_id);
    src.unkfunc_0204a800(buf);
    dst.unkfunc_0204a814((char*)lines[count], 0x100);
    count++;
    if (src.unkfunc_0204a990() != 0) {
        unsigned char** next = &lines[count];
        int c;
        do {
            c = src.unkfunc_0204a990();
            src.unkfunc_0204a9ec();
            if (c != '\n') {
                dst.unkfunc_0204a9a0(c);
            } else {
                dst.unkfunc_0204a9a0(0xffff);
                if (*next == NULL) {
                    return count;
                }
                dst.unkfunc_0204a814((char*)*next, 0x100);
                next++;
                count++;
            }
        } while (c != 0);
    }
    dst.unkfunc_0204a9a0(0xffff);
    return count;
}
