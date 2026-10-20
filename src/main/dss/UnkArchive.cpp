#include "main/dss/UnkArchive.hpp"

ARM int unkfunc_0204c860(void* archive)
{
    return ((int*)archive)[4];
}

ARM int getArchiveFileSize(void* archive, int index)
{
    return ((int*)archive)[index * 2 + 9];
}

ARM void* getArchiveFile(void* archive, int index)
{
    return (unsigned char*)archive + (((unsigned int*)archive)[index * 2 + 8] & ~3) + (((unsigned int*)archive)[5] & ~3);
}
