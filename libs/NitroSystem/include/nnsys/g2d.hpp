#pragma once

struct NNSG2dBinaryBlockHeader {
    unsigned int kind;                          // 0x00
    unsigned int size;                          // 0x04
};

struct NNSG2dCharacterData {
    unsigned short H;                           // 0x00
    unsigned short W;                           // 0x02
    int pixelFmt;                               // 0x04
    int mapingType;                             // 0x08
    unsigned int characterFmt;                  // 0x0C
    unsigned int szByte;                        // 0x10
    void* pRawData;                             // 0x14
};

struct NNSG2dPaletteData {
    int fmt;                                    // 0x00
    int bExtendedPlt;                           // 0x04
    unsigned int szByte;                        // 0x08
    void* pRawData;                             // 0x0C
};

extern "C" {
    NNSG2dBinaryBlockHeader* func_0207ebf8(void* file, unsigned int kind);  // NNS_G2dFindBinaryBlock
    void func_0207ec9c(unsigned int flags);                                  // NNS_G2dSetSpriteAttrEnable
}
