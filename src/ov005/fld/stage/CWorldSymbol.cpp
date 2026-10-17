#include "main/fld/CWorldMap.hpp"
#include "nitro/os.hpp"

THUMB void CWorldSymbol::setup(void* data)
{
    chunk* cnk = (chunk*)data;

    while (cnk->id != 0) {
        switch (cnk->id) {
        case 0x54414453:
            m_data = (WorldSymbolData*)(cnk + 1);
            m_ndata = cnk->size / sizeof(WorldSymbolData);
            break;
        default:
            OS_Terminate();
            break;
        }
        cnk = (chunk*)((unsigned char*)cnk + cnk->size + sizeof(chunk));
    }
}
