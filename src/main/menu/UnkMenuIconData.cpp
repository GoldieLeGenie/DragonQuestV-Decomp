#include "main/menu/UnkMenuIconData.hpp"
#include "main/menu/UnkIconFile.hpp"
#include "main/menu/UnkMenuBg.hpp"
#include "main/data/FileLoader.hpp"

static int s_itemIconType;
static UnkIconFile s_item32;
static UnkIconFile s_char32;
static UnkIconFile s_command32;
static UnkIconFile s_command24;
static UnkIconFile s_face48;
static UnkIconFile s_wireless48;
static UnkIconFile s_loading48;

THUMB void unkfunc_02063250()
{
    s_command32.unkfunc_0206dc2c("DATA/G2D/icon/command32.mptp");
    s_command24.unkfunc_0206dc2c("DATA/G2D/icon/command24.mptp");
    s_item32.unkfunc_0206dc3c(NULL, "DATA/G2D/icon/item32.mptp", 0x258, 24);
    s_char32.unkfunc_0206dc3c(NULL, "DATA/G2D/icon/char32.mptp", 0x208, 14);
    s_face48.unkfunc_0206dc3c(NULL, "DATA/G2D/icon/face48.mpt", 0x900, 12);
    s_wireless48.unkfunc_0206dc2c("DATA/G2D/icon/wireless48.mpt");
    s_loading48.unkfunc_0206dc2c("DATA/G2D/icon/loading48.mpt");
    s_itemIconType = 0;
}

THUMB void unkfunc_020632ec(int type)
{
    if (s_itemIconType != type) {
        const char* path = NULL;
        s_itemIconType = type;
        if (type == 0) {
            path = "DATA/G2D/icon/item32.mptp";
        }
        if (type == 1) {
            path = "DATA/G2D/icon/sure32.mptp";
        }
        if (path != NULL) {
            dss::g_File.unkfunc_0204b21c(path, s_item32.data_.getAddr(), 1);
            data_02106178.icon_.unkfunc_020637ac();
        }
    }
}

THUMB void* unkfunc_0206333c(int type, int index)
{
    if (index != 9999) {
        if (type == 0xf0000000) {
            unkfunc_020632ec(0);
        }
        if (type == 0xf7000000) {
            unkfunc_020632ec(1);
        }
    }
    UnkIconFile* file;
    switch (type) {
    case 0xf0000000:
        file = &s_item32;
        break;
    case 0xf1000000:
        file = &s_char32;
        break;
    case 0xf3000000:
        file = &s_command32;
        break;
    case 0xf4000000:
        file = &s_command24;
        break;
    case 0xf5000000:
        file = &s_face48;
        break;
    case 0xf8000000:
        file = &s_wireless48;
        break;
    case 0xf9000000:
        file = &s_loading48;
        break;
    case 0xf7000000:
        file = &s_item32;
        break;
    default:
        return NULL;
    }
    return file->unkfunc_0206dc68(index);
}
