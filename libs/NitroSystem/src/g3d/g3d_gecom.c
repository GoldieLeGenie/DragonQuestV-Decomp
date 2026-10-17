#include "g3d_internal.h"

#pragma thumb on

UnkGeState data_02127b1c;

// Sets the geometry command buffer (only when none is set)
void func_020825dc(NNSG3dGeBuffer* buf) {
    if (data_02127b1c.buf == NULL) {
        buf->idx = 0;
        data_02127b1c.buf = buf;
    }
}

// Flushes and releases the geometry command buffer
NNSG3dGeBuffer* func_020825f0(void) {
    NNSG3dGeBuffer* buf;
    func_02082604();
    buf = data_02127b1c.buf;
    data_02127b1c.buf = NULL;
    return buf;
}

// Sends the buffered geometry commands to the FIFO
void func_02082604(void) {
    if (data_02127b1c.busy) {
        func_0208263c();
    }
    if (data_02127b1c.buf && data_02127b1c.buf->idx) {
        MI_CpuFillFromSrc(&data_02127b1c.buf->data[0], &REG_GFX_FIFO, data_02127b1c.buf->idx * 4);
        data_02127b1c.buf->idx = 0;
    }
}

// Waits for the end of a display list transfer
void func_0208263c(void) {
    while (data_02127b1c.busy) {
    }
}

// Display list transfer end callback
void func_0208264c(void* arg) {
    *(u32*)arg = 0;
}

void func_02082654(u32 flag) {
    data_02127b1c.useDmaAsync = flag;
}

// Sends a display list
void func_02082660(const u32* dl, u32 size) {
    if (size < 0x100 || data_0209c504 == (u32)-1) {
        func_020826d0(*dl, dl + 1, (size >> 2) - 1);
    } else {
        func_02082604();
        data_02127b1c.busy = 1;
        if (data_02127b1c.useDmaAsync) {
            func_0207013c(data_0209c504, dl, size, func_0208264c, (void*)&data_02127b1c.busy);
        } else {
            func_0206ffd0(data_0209c504, dl, size, func_0208264c, (void*)&data_02127b1c.busy);
        }
    }
}

// Sends (or buffers) a geometry command with its parameters
void func_020826d0(u32 op, const void* args, u32 num) {
    if (data_02127b1c.buf) {
        if (data_02127b1c.busy) {
            u32 idx = data_02127b1c.buf->idx;
            if (idx + 1 + num <= 0xc0) {
                data_02127b1c.buf->idx = idx + 1;
                data_02127b1c.buf->data[idx] = op;
                if (num) {
                    MI_CpuCopy(args, &data_02127b1c.buf->data[data_02127b1c.buf->idx], num * 4);
                    data_02127b1c.buf->idx += num;
                }
                return;
            }
        }
        if (data_02127b1c.buf->idx) {
            func_02082604();
        } else if (data_02127b1c.busy) {
            func_0208263c();
        }
    } else if (data_02127b1c.busy) {
        func_0208263c();
    }
    REG_GFX_FIFO = op;
    MI_CpuFillFromSrc(args, &REG_GFX_FIFO, num * 4);
}

// Gets the current position/vector matrices
void func_02082758(MtxFx43* m, MtxFx33* n) {
    MtxFx44 tmp;

    func_02082604();
    REG_GFX_FIFO_MATRIX_MODE = 0;
    REG_GFX_FIFO_MATRIX_PUSH = 0;
    REG_GFX_FIFO_MATRIX_IDENTITY = 0;

    if (m) {
        while (func_02075e58(&tmp)) {
        }
        func_0208965c(&tmp, m);
    }
    if (n) {
        while (func_02075e88(n)) {
        }
    }

    REG_GFX_FIFO_MATRIX_POP = 1;
    REG_GFX_FIFO_MATRIX_MODE = 2;
}
