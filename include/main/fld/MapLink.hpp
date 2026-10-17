#pragma once
#include <globaldefs.h>

struct MAP_LINK_IDX {
    unsigned short map_id;                      // 0x00
    unsigned short n_exit;                      // 0x02
    unsigned short tbl_ofs;                     // 0x04
};

struct MAP_LINK_TBL {
    int exit_id;                                // 0x00
    int target_id;                              // 0x04
    unsigned short map_id;                      // 0x08
    unsigned short pad;                         // 0x0A
};

struct CMapLink {
    struct chunk {
        unsigned int id;                        // 0x00
        unsigned int size;                      // 0x04
    };

    void* m_data;                               // 0x00
    void* m_idx;                                // 0x04
    unsigned short m_ndata;                     // 0x08
    int m_exit_id;                              // 0x0C

    void setup(void* data);
    int search(int map_id, int exit_id);
    int get_exit_id();
};
