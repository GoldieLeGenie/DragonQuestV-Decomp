#pragma once
#include <globaldefs.h>

struct CNK_SYN {
    unsigned char wldx;                         // 0x00
    unsigned char wldy;                         // 0x01
    unsigned char mapx;                         // 0x02
    unsigned char mapy;                         // 0x03
};

struct CNK_CHA {
    unsigned short id;                          // 0x00
    short sx;                                   // 0x02
    short sy;                                   // 0x04
    short ex;                                   // 0x06
    short ey;                                   // 0x08
    int ofs;                                    // 0x0C
};

struct CNK_TEX {
    unsigned char attr;                         // 0x00
    unsigned char aflag;                        // 0x01
    short ano;                                  // 0x02
    short no;                                   // 0x04
};

enum WMAP_ATTR {
    WMAP_ATTR_NOT = 0,
    WMAP_ATTR_SOUG = 1,
    WMAP_ATTR_SIGE = 2,
    WMAP_ATTR_SUNA = 3,
    WMAP_ATTR_MORI = 4,
    WMAP_ATTR_YAMA1 = 5,
    WMAP_ATTR_YAMA2 = 6,
    WMAP_ATTR_KAIG = 7,
    WMAP_ATTR_UMI = 8,
    WMAP_ATTR_ASAS = 9,
    WMAP_ATTR_DOKU = 10,
    WMAP_ATTR_GA = 11,
    WMAP_ATTR_TAKI = 12,
    WMAP_ATTR_WGA = 13,
    WMAP_SYMBOL_START = 14,
    WMAP_SYMBOL_HASI01 = 14,
    WMAP_SYMBOL_2DCAST01 = 15,
    WMAP_SYMBOL_DP01 = 16,
    WMAP_SYMBOL_MACHI = 17,
    WMAP_SYMBOL_MURA02 = 18,
    WMAP_SYMBOL_HOUSE01 = 19,
    WMAP_SYMBOL_HOUSE02 = 20,
    WMAP_SYMBOL_TENTO01 = 21,
    WMAP_SYMBOL_SB01 = 22,
    WMAP_SYMBOL_KNBN01 = 23,
    WMAP_SYMBOL_DOKT01 = 24,
    WMAP_SYMBOL_DOKT02 = 25,
    WMAP_SYMBOL_DOKT03 = 26,
    WMAP_SYMBOL_TOWER01 = 27,
    WMAP_SYMBOL_TOWER02 = 28,
    WMAP_SYMBOL_HKR01 = 29,
    WMAP_SYMBOL_FMURA01 = 30,
    WMAP_SYMBOL_FMURA02 = 31,
    WMAP_SYMBOL_KOORI01 = 32,
    WMAP_SYMBOL_YAMA01 = 33,
    WMAP_SYMBOL_SUIMON01 = 34,
    WMAP_SYMBOL_SUIMON02 = 35,
    WMAP_SYMBOL_SUIMON03 = 36,
    WMAP_SYMBOL_XD1 = 37,
    WMAP_SYMBOL_MACHI2 = 38,
    WMAP_SYMBOL_TBTB01 = 39,
    WMAP_SYMBOL_XB1 = 40,
    WMAP_SYMBOL_MACHI3 = 41,
    WMAP_SYMBOL_EVYM01 = 42,
    WMAP_SYMBOL_KOORI02 = 43,
    WMAP_SYMBOL_YMSG1 = 44,
    WMAP_SYMBOL_NUKI01 = 45,
    WMAP_SYMBOL_SBROSE1 = 46,
    WMAP_SYMBOL_COLL01 = 47,
    WMAP_ATTR_MAX = 48,
};

struct CWorldMap {
    struct header {
        unsigned int id;                        // 0x00
        unsigned int size;                      // 0x04
        unsigned int unk_08;                    // 0x08
        unsigned int unk_0c;                    // 0x0C
    };

    struct chunk {
        unsigned int id;                        // 0x00
        unsigned int size;                      // 0x04
    };

    struct UV_TBL {
        unsigned char u0;                       // 0x00
        unsigned char v0;                       // 0x01
        unsigned char u1;                       // 0x02
        unsigned char v1;                       // 0x03
        unsigned char u2;                       // 0x04
        unsigned char v2;                       // 0x05
        unsigned char u3;                       // 0x06
        unsigned char v3;                       // 0x07
    };

    CNK_SYN* m_syn;                             // 0x00
    CNK_CHA* m_cha;                             // 0x04
    short* m_map;                               // 0x08
    short* m_cmap;                              // 0x0C
    CNK_TEX* m_tex;                             // 0x10
    UV_TBL* m_uv_tbl;                           // 0x14
    unsigned char* m_uv_id;                     // 0x18
    void* m_sym_data;                           // 0x1C
    unsigned short m_chanum;                    // 0x20
    unsigned short m_texnum;                    // 0x22

    CWorldMap();
    ~CWorldMap();
    void setup(void* data);
    unsigned short getWorldEdgeX();
    unsigned short getWorldEdgeY();
    unsigned char* getUV(int x, int y);
    WMAP_ATTR getAttr(int x, int y);
    unsigned short getWorldNo(int x, int y);
    CNK_TEX* getTextureData(int num);
    void worldChange(int num);
};

struct WorldSymbolData {
    unsigned char flags;                        // 0x00
    unsigned char id;                           // 0x01
    unsigned short uid;                         // 0x02
    short x;                                    // 0x04
    short y;                                    // 0x06
    unsigned char w;                            // 0x08
    unsigned char h;                            // 0x09
};

struct CWorldSymbol {
    struct chunk {
        unsigned int id;                        // 0x00
        unsigned int size;                      // 0x04
    };

    WorldSymbolData* m_data;                    // 0x00
    unsigned short m_ndata;                     // 0x04

    void setup(void* data);
    int getNum() const;
    WorldSymbolData* getData(int index);
};
