#include "main/fld/MapLink.hpp"
#include "nitro/os.hpp"

ARM void CMapLink::setup(void* data)
{
    chunk* cnk = (chunk*)data;

    while (cnk->id != 0) {
        switch (cnk->id) {
        case 0x41544144: // "DATA"
            m_data = cnk + 1;
            break;
        case 0x58444e49: { // "INDX"
            unsigned short* p = (unsigned short*)(cnk + 1);
            m_ndata = *p;
            m_idx = p + 1;
            break;
        }
        default:
            OS_Terminate();
            break;
        }
        cnk = (chunk*)((unsigned char*)cnk + cnk->size + sizeof(chunk));
    }
}

ARM int CMapLink::search(int map_id, int exit_id)
{
    MAP_LINK_IDX* idx;
    int left;
    int right;
    int mid;

    idx = (MAP_LINK_IDX*)m_idx;
    left = 0;
    right = m_ndata - 1;
    while (left < right) {
        mid = (left + right) / 2;
        if (idx[mid].map_id < map_id) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    if (map_id == idx[left].map_id) {
        idx = &idx[left];
        MAP_LINK_TBL* tbl = (MAP_LINK_TBL*)((unsigned char*)m_data + idx->tbl_ofs);
        for (int i = 0; i < idx->n_exit; i++) {
            if (tbl[i].exit_id == exit_id && tbl[i].map_id != 0) {
                m_exit_id = tbl[i].target_id;
                return tbl[i].map_id;
            }
        }
    }
    return 0;
}
