#include "main/fld/CWorldMap.hpp"
#include "nitro/os.hpp"

inline unsigned short CWorldMap::getWorldEdgeX()
{
    return m_syn->mapx * m_syn->wldx;
}

THUMB CWorldMap::CWorldMap()
{
}

THUMB CWorldMap::~CWorldMap()
{
}

THUMB void CWorldMap::setup(void* data)
{
    chunk* cnk = (chunk*)((header*)data + 1);

    while (cnk->id != 0) {
        switch (cnk->id) {
        case 0x4e595357:
            m_syn = (CNK_SYN*)(cnk + 1);
            break;
        case 0x41484357:
            m_cha = (CNK_CHA*)(cnk + 1);
            m_chanum = cnk->size / sizeof(CNK_CHA);
            break;
        case 0x50414d57:
            m_map = (short*)(cnk + 1);
            break;
        case 0x414d4357:
            m_cmap = (short*)(cnk + 1);
            break;
        case 0x58455457:
            m_tex = (CNK_TEX*)(cnk + 1);
            m_texnum = cnk->size / sizeof(CNK_TEX);
            break;
        case 0x54565557:
            m_uv_tbl = (UV_TBL*)(cnk + 1);
            m_uv_id = (unsigned char*)(cnk + 1) + 0x80;
            break;
        case 0x54414453:
            m_sym_data = cnk;
            break;
        default:
            OS_Terminate();
            break;
        }
        cnk = (chunk*)((unsigned char*)cnk + cnk->size + sizeof(chunk));
    }
}

THUMB WMAP_ATTR CWorldMap::getAttr(int x, int y)
{
    int np = y * getWorldEdgeX() + x;
    short num = m_map[np] - 1;
    short sym_id = num >> 10;
    if (sym_id) {
        return (WMAP_ATTR)(sym_id + (WMAP_SYMBOL_START - 1));
    }
    return (WMAP_ATTR)m_tex[num].attr;
}

THUMB unsigned short CWorldMap::getWorldNo(int x, int y)
{
    int np = y * getWorldEdgeX() + x;
    unsigned short num = m_map[np] - 1;
    return num & 0x3ff;
}

THUMB void CWorldMap::worldChange(int num)
{
    if (num < m_chanum) {
        CNK_CHA* c_data = &m_cha[num];
        unsigned short wldedx = getWorldEdgeX();
        int cnum = c_data->ofs;
        for (int y = c_data->sy; y < c_data->ey; y++) {
            for (int x = c_data->sx; x < c_data->ex; x++) {
                m_map[y * wldedx + x] = m_cmap[cnum++];
            }
        }
    } else {
        OS_Terminate();
    }
}

THUMB unsigned char* CWorldMap::getUV(int x, int y)
{
    int np = y * getWorldEdgeX() + x;
    int id = m_uv_id[np / 2];
    if (np & 1) {
        id &= 0xf;
    } else {
        id = (id >> 4) & 0xf;
    }
    return (unsigned char*)&m_uv_tbl[id];
}
