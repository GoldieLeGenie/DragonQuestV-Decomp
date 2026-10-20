#include "main/dss/UnkArrayWarning.hpp"
#include "main/dss/DssUtils.hpp"

int data_0209a288 = 1;
int data_020fd180;
UnkArrayWarning data_020fd184[16];

ARM void setArrayErrorEnabled(int enable)
{
    data_0209a288 = enable;
}

ARM void addArrayError(int index, int size, unsigned int caller)
{
    if (data_020fd180 < 16) {
        data_020fd184[data_020fd180].index_ = index;
        data_020fd184[data_020fd180].size_ = size;
        data_020fd184[data_020fd180].caller_ = caller;
    }
    data_020fd180++;
}

ARM UnkArrayWarning* getArrayError(int index)
{
    return &data_020fd184[index];
}

ARM int getArrayErrorCount()
{
    return data_020fd180;
}

ARM void reportArrayError(int index, int size)
{
    register unsigned int caller = 0;
    asm { mov caller, lr }
    if (data_0209a288 != 0) {
        addArrayError(index, size, caller);
        char buf[0x40];
        dss::sprintf_s(buf, sizeof(buf), "ARRAY ERROR %d/%d %08x !!!!", index, size, caller);
        if (data_0209a288 == 1) {
            (void)buf;                          // printed in the debug build
        }
    }
}
