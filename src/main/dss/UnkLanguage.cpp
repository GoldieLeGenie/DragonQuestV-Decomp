#include "main/dss/UnkLanguage.hpp"

static char s_noCode[] = "----";
const char* data_02099a10 = s_noCode;
static UnkLanguage s_language;
static int s_region;
static int s_code;

ARM UnkLanguage::UnkLanguage()
{
    s_region = 3;
    setRegionGameCode();
}

ARM int getGameRegion()
{
    return s_region;
}

ARM void setRegionGameCode()
{
    switch (s_region) {
    case 1:
        data_02099a10 = "yv5j";
        s_code = 0x998;
        break;
    case 2:
        data_02099a10 = "yv5e";
        s_code = 0x400779;
        break;
    case 3:
        data_02099a10 = "yv5p";
        s_code = 0x8002ac;
        break;
    default:
        data_02099a10 = "----";
        s_code = 0;
        break;
    }
}

ARM int getGgid()
{
    return s_code;
}
