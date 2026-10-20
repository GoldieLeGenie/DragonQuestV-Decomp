#include "main/menu/UnkMenuOverlay.hpp"
#include "main/dss/DssUtils.hpp"

UnkOverlaySlot data_020a29f4;
UnkOverlaySlot data_020a29ec;

THUMB void unkfunc_02018d64(int menu)
{
    switch (menu) {
        case 0:
            break;
        case 1:
            data_020a29f4.load((int)&OVERLAY_23_ID);
            break;
        case 2:
            data_020a29f4.load((int)&OVERLAY_26_ID);
            break;
        case 3:
            data_020a29f4.load((int)&OVERLAY_27_ID);
            break;
        case 4:
            data_020a29f4.load((int)&OVERLAY_29_ID);
            break;
        case 5:
            data_020a29f4.load((int)&OVERLAY_30_ID);
            break;
        case 6:
            data_020a29f4.load((int)&OVERLAY_25_ID);
            break;
        case 7:
            data_020a29f4.load((int)&OVERLAY_31_ID);
            break;
        case 8:
            data_020a29f4.load((int)&OVERLAY_32_ID);
            break;
        case 9:
            data_020a29f4.load((int)&OVERLAY_33_ID);
            break;
        case 10:
            data_020a29f4.load((int)&OVERLAY_28_ID);
            break;
        case 13:
            data_020a29f4.load((int)&OVERLAY_24_ID);
            break;
        case 11:
            data_020a29f4.load((int)&OVERLAY_34_ID);
            break;
        case 12:
            data_020a29f4.load((int)&OVERLAY_35_ID);
            break;
        case 14:
            data_020a29f4.load((int)&OVERLAY_36_ID);
            break;
        case 15:
            data_020a29f4.load((int)&OVERLAY_37_ID);
            break;
    }
}

THUMB void unkfunc_02018e6c(int menu)
{
    switch (menu) {
        case 1:
            data_020a29ec.load((int)&OVERLAY_19_ID);
            break;
        case 2:
            data_020a29ec.load((int)&OVERLAY_18_ID);
            break;
        case 3:
            data_020a29ec.load((int)&OVERLAY_20_ID);
            break;
    }
}

THUMB void unkfunc_02018eac()
{
    data_020a29ec.unload();
}
