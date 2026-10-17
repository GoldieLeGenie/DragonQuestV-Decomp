#include "gx_internal.h"

/* BG screen / character base address getters */

void *func_02075564(void) {
    s32 blockOffset = (REG_BG0CNT & 0x1f00) >> 8;
    u32 offset      = (REG_DISPCNT_V & 0x38000000) >> 27;
    return (void *)(0x6000000 + offset * 0x10000 + blockOffset * 0x800);
}

void *func_02075598(void) {
    s32 blockOffset = (REG_BG0CNT_SUB & 0x1f00) >> 8;
    return (void *)(0x6200000 + blockOffset * 0x800);
}

void *func_020755b8(void) {
    s32 blockOffset = (REG_BG1CNT & 0x1f00) >> 8;
    u32 offset      = (REG_DISPCNT_V & 0x38000000) >> 27;
    return (void *)(0x6000000 + offset * 0x10000 + blockOffset * 0x800);
}

void *func_020755ec(void) {
    s32 blockOffset = (REG_BG1CNT_SUB & 0x1f00) >> 8;
    return (void *)(0x6200000 + blockOffset * 0x800);
}

void *func_0207560c(void) {
    u32 bgMode = REG_DISPCNT_V & 7;
    u32 bgcnt  = REG_BG2CNT;
    u32 offset = ((REG_DISPCNT_V & 0x38000000) >> 27) * 0x10000;
    u32 block  = (bgcnt & 0x1f00) >> 8;

    switch (bgMode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return (void *)(0x6000000 + offset + block * 0x800);
    case 5:
        if (bgcnt & 0x80) {
            return (void *)(0x6000000 + block * 0x4000);
        } else {
            return (void *)(0x6000000 + offset + block * 0x800);
        }
    case 6:
        return (void *)0x6000000;
    default:
        return NULL;
    }
}

void *func_02075690(void) {
    u32 bgMode = REG_DISPCNT_SUB_V & 7;
    u32 bgcnt  = REG_BG2CNT_SUB;
    u32 block  = (bgcnt & 0x1f00) >> 8;

    switch (bgMode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return (void *)(0x6200000 + block * 0x800);
    case 5:
        if (bgcnt & 0x80) {
            return (void *)(0x6200000 + block * 0x4000);
        } else {
            return (void *)(0x6200000 + block * 0x800);
        }
    case 6:
        return NULL;
    default:
        return NULL;
    }
}

void *func_02075704(void) {
    u32 bgMode = REG_DISPCNT_V & 7;
    u32 bgcnt  = REG_BG3CNT;
    u32 offset = ((REG_DISPCNT_V & 0x38000000) >> 27) * 0x10000;
    u32 block  = (bgcnt & 0x1f00) >> 8;

    switch (bgMode) {
    case 0:
    case 1:
    case 2:
        return (void *)(0x6000000 + offset + block * 0x800);
    case 3:
    case 4:
    case 5:
        if (bgcnt & 0x80) {
            return (void *)(0x6000000 + block * 0x4000);
        } else {
            return (void *)(0x6000000 + offset + block * 0x800);
        }
    case 6:
        return NULL;
    default:
        return NULL;
    }
}

void *func_02075788(void) {
    u32 bgMode = REG_DISPCNT_SUB_V & 7;
    u32 bgcnt  = REG_BG3CNT_SUB;
    u32 block  = (bgcnt & 0x1f00) >> 8;

    switch (bgMode) {
    case 0:
    case 1:
    case 2:
        return (void *)(0x6200000 + block * 0x800);
    case 3:
    case 4:
    case 5:
        if (bgcnt & 0x80) {
            return (void *)(0x6200000 + block * 0x4000);
        } else {
            return (void *)(0x6200000 + block * 0x800);
        }
    case 6:
        return NULL;
    default:
        return NULL;
    }
}

void *func_020757fc(void) {
    s32 blockOffset = (REG_BG0CNT & 0x3c) >> 2;
    u32 offset      = (REG_DISPCNT_V & 0x7000000) >> 24;
    return (void *)(0x6000000 + offset * 0x10000 + blockOffset * 0x4000);
}

void *func_02075830(void) {
    s32 blockOffset = (REG_BG0CNT_SUB & 0x3c) >> 2;
    return (void *)(0x6200000 + blockOffset * 0x4000);
}

void *func_02075850(void) {
    s32 blockOffset = (REG_BG1CNT & 0x3c) >> 2;
    u32 offset      = (REG_DISPCNT_V & 0x7000000) >> 24;
    return (void *)(0x6000000 + offset * 0x10000 + blockOffset * 0x4000);
}

void *func_02075884(void) {
    s32 blockOffset = (REG_BG1CNT_SUB & 0x3c) >> 2;
    return (void *)(0x6200000 + blockOffset * 0x4000);
}

void *func_020758a4(void) {
    s32 bgMode = REG_DISPCNT_V & 7;
    u32 bgcnt  = REG_BG2CNT;

    if (bgMode < 5 || !(bgcnt & 0x80)) {
        u32 offset = (REG_DISPCNT_V & 0x7000000) >> 24;
        u32 block  = (bgcnt & 0x3c) >> 2;
        return (void *)(0x6000000 + offset * 0x10000 + block * 0x4000);
    }
    return NULL;
}

void *func_020758f4(void) {
    s32 bgMode = REG_DISPCNT_SUB_V & 7;
    u32 bgcnt  = REG_BG2CNT_SUB;

    if (bgMode < 5 || !(bgcnt & 0x80)) {
        u32 block = (bgcnt & 0x3c) >> 2;
        return (void *)(0x6200000 + block * 0x4000);
    }
    return NULL;
}

void *func_02075934(void) {
    s32 bgMode = REG_DISPCNT_V & 7;
    u32 bgcnt  = REG_BG3CNT;

    if (bgMode < 3 || (bgMode < 6 && !(bgcnt & 0x80))) {
        u32 offset = (REG_DISPCNT_V & 0x7000000) >> 24;
        u32 block  = (bgcnt & 0x3c) >> 2;
        return (void *)(0x6000000 + offset * 0x10000 + block * 0x4000);
    }
    return NULL;
}

void *func_0207598c(void) {
    s32 bgMode = REG_DISPCNT_SUB_V & 7;
    u32 bgcnt  = REG_BG3CNT_SUB;

    if (bgMode < 3 || (bgMode < 6 && !(bgcnt & 0x80))) {
        u32 block = (bgcnt & 0x3c) >> 2;
        return (void *)(0x6200000 + block * 0x4000);
    }
    return NULL;
}
