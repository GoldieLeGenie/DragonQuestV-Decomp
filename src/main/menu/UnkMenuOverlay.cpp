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
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_23_ID);
            break;
        case 2:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_26_ID);
            break;
        case 3:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_27_ID);
            break;
        case 4:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_29_ID);
            break;
        case 5:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_30_ID);
            break;
        case 6:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_25_ID);
            break;
        case 7:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_31_ID);
            break;
        case 8:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_32_ID);
            break;
        case 9:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_33_ID);
            break;
        case 10:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_28_ID);
            break;
        case 13:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_24_ID);
            break;
        case 11:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_34_ID);
            break;
        case 12:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_35_ID);
            break;
        case 14:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_36_ID);
            break;
        case 15:
            data_020a29f4.unkfunc_0204b580((int)&OVERLAY_37_ID);
            break;
    }
}

THUMB void unkfunc_02018e6c(int menu)
{
    switch (menu) {
        case 1:
            data_020a29ec.unkfunc_0204b580((int)&OVERLAY_19_ID);
            break;
        case 2:
            data_020a29ec.unkfunc_0204b580((int)&OVERLAY_18_ID);
            break;
        case 3:
            data_020a29ec.unkfunc_0204b580((int)&OVERLAY_20_ID);
            break;
    }
}

THUMB void unkfunc_02018eac()
{
    data_020a29ec.unkfunc_0204b5a8();
}
