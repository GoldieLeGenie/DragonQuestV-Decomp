#include "main/text/TextAPI.hpp"

MsgData g_msg_data_default;
MsgData g_msg_data[11];
TextEnv g_text_env;
UnkTextExtractor g_text_extractor;
UnkBadWordList g_bad_word_list;
UnkMsgFile g_msg_file;

THUMB void TextAPI::unkfunc_0206cb34()
{
}

THUMB void TextAPI::Init()
{
    g_msg_data_default.msg_setup(0, 1999999, 0x14000, 1000);
    g_msg_data[0].msg_setup(830000, 0, 0x1400, 1000);
    g_msg_data[1].msg_setup(831000, 0, 0x3000, 1000);
    g_msg_data[2].msg_setup(1000000, 0, 0x5800, 1000);
    g_msg_data[3].msg_setup(1001000, 0, 0x2000, 1000);
    g_msg_data[4].msg_setup(1002000, 0, 0x4c00, 1000);
    g_msg_data[5].msg_setup(1003000, 0, 0x1400, 1000);
    g_msg_data[6].msg_setup(1004000, 0, 0x1000, 1000);
    g_msg_data[7].msg_setup(1005000, 0, 0x400, 1000);
    g_msg_data[8].msg_setup(1006000, 0, 0x1000, 1000);
    g_msg_data[9].msg_setup(1007000, 0, 0x7400, 1000);
    g_msg_data[10].msg_setup(1010000, 0, 0x2000, 1000);
    g_msg_file.unkfunc_0206b848();
}

THUMB void TextAPI::unkfunc_0206cc94()
{
}

THUMB void TextAPI::unkfunc_0206cc98()
{
    g_msg_data_default.unkfunc_0206b9d4();
    g_msg_data[0].unkfunc_0206b9d4();
    g_msg_data[1].unkfunc_0206b9d4();
    g_msg_data[2].unkfunc_0206b9d4();
    g_msg_data[3].unkfunc_0206b9d4();
    g_msg_data[4].unkfunc_0206b9d4();
    g_msg_data[5].unkfunc_0206b9d4();
    g_msg_data[6].unkfunc_0206b9d4();
    g_msg_data[7].unkfunc_0206b9d4();
    g_msg_data[8].unkfunc_0206b9d4();
    g_msg_data[9].unkfunc_0206b9d4();
    g_msg_data[10].unkfunc_0206b9d4();
    g_msg_file.unkfunc_0206b874();
}

THUMB void TextAPI::unkfunc_0206cd20()
{
    resetMacro();
}

THUMB void TextAPI::unkfunc_0206cd28()
{
}

THUMB void TextAPI::unkfunc_0206cd2c()
{
}

THUMB MsgData* unkfunc_0206cd30(int msg_id)
{
    MsgData* msg = 0;
    if (g_msg_data_default.unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data_default;
    }
    if (g_msg_data[0].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[0];
    }
    if (g_msg_data[1].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[1];
    }
    if (g_msg_data[2].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[2];
    }
    if (g_msg_data[3].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[3];
    }
    if (g_msg_data[4].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[4];
    }
    if (g_msg_data[5].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[5];
    }
    if (g_msg_data[6].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[6];
    }
    if (g_msg_data[7].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[7];
    }
    if (g_msg_data[8].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[8];
    }
    if (g_msg_data[9].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[9];
    }
    if (g_msg_data[10].unkfunc_0206b9f8(msg_id)) {
        msg = &g_msg_data[10];
    }
    return msg;
}

THUMB int unkfunc_0206ce14(int msg_id, int lang)
{
    return g_msg_file.unkfunc_0206b88c(msg_id, lang);
}

THUMB int unkfunc_0206ce28(int msg_id, int lang)
{
    return g_msg_file.unkfunc_0206b910(msg_id, lang);
}

THUMB char* msg_get_head()
{
    return (char*)g_msg_file.unkfunc_0206b948(10);
}

THUMB char* msg_get_body()
{
    return (char*)g_msg_file.unkfunc_0206b948(11);
}

THUMB unsigned char msg_get_sound()
{
    return *g_msg_file.unkfunc_0206b948(12);
}

THUMB int CheckBadWord(char* name)
{
    if (TextAPI::m_lang != 0) {
        return 0;
    }
    g_bad_word_list.unkfunc_0206b6b4();
    int result = g_bad_word_list.unkfunc_0206b704(name);
    g_bad_word_list.unkfunc_0206b6fc();
    return result;
}

THUMB int unkfunc_0206cea4(char* name)
{
    unkfunc_0204e478(10);
    unkfunc_0204dfbc(NULL, 0, 0, 0, name, 0);
    if (unkfunc_0204e540() > 0x30) {
        return 1;
    }
    return 0;
}
