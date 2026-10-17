#include "main/dss/UnkVramRequest.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkMemory.hpp"

THUMB void UnkOamBuffer::unkfunc_0204db88()
{
}

THUMB void UnkOamBuffer::unkfunc_0204db8c()
{
    func_02070224(0xc0, oam_, sizeof(oam_));
    prevCount_ = count_;
    count_ = 0;
    unk_408 = 0;
}

THUMB void UnkOamBuffer::unkfunc_0204dbb0(int type)
{
    unkfunc_0204dca8(type, 0, oam_, sizeof(oam_));
}

THUMB GXOamAttr* UnkOamBuffer::unkfunc_0204dbc4()
{
    GXOamAttr* oam = &oam_[count_];
    count_++;
    return oam;
}

THUMB void UnkPaletteBuffer::unkfunc_0204dbd4(int type)
{
    unkfunc_0204dca8(type, 0, color_, sizeof(color_));
}

THUMB void UnkPaletteBuffer::unkfunc_0204dbe8(int index, int color, unsigned short rgb)
{
    color_[index * 16 + color] = rgb;
}

THUMB void UnkPaletteBuffer::unkfunc_0204dbf4(int index, int color, const void* src, int count)
{
    MI_CpuCopyU32(src, &color_[index * 16 + color], count * 2);
}

THUMB UnkVramRequestQueue::UnkVramRequestQueue()
{
    for (int i = 0; i < 128; i++) {
        request_[i].active_ = 0;
    }
    size_ = 0;
    lines_ = 0;
}

UnkVramRequestQueue data_021003e8;

THUMB void unkfunc_0204dc28()
{
    int start;
    int size;
    UnkVramRequest* request;
    int i;
    size = 0;
    start = *(volatile unsigned short*)0x04000006;
    request = data_021003e8.request_;
    for (i = 0; i < 128; i++, request++) {
        if (request->active_ == 1) {
            size += data_021003e8.unkfunc_0204dde4(request);
        }
    }
    int end = *(volatile unsigned short*)0x04000006;
    data_021003e8.size_ = size;
    data_021003e8.lines_ = end - start;
}

THUMB UnkVramRequest* unkfunc_0204dc6c(int type, int offset, void* data, int size)
{
    void* buffer = unkfunc_0204c278(data);
    UnkVramRequest* request = unkfunc_0204dca8(type, offset, buffer, unkfunc_0204c214(data));
    if (request == NULL) {
        unkfunc_0204c5c8(&data_020fd24c, buffer);
        return NULL;
    }
    request->buffer_ = buffer;
    return request;
}

THUMB UnkVramRequest* unkfunc_0204dca8(int type, int offset, const void* src, int size)
{
    for (int i = 0; i < 128; i++) {
        UnkVramRequest* request = &data_021003e8.request_[i];
        if (request->active_ == 0) {
            void* base = data_021003e8.unkfunc_0204dcec(type);
            request->active_ = 1;
            request->type_ = type;
            request->offset_ = offset;
            request->base_ = base;
            request->src_ = src;
            request->size_ = size;
            request->buffer_ = NULL;
            return request;
        }
    }
    return NULL;
}

THUMB void* UnkVramRequestQueue::unkfunc_0204dcec(int type)
{
    switch (type) {
    case 4:
        return func_020757fc();
    case 5:
        return func_02075850();
    case 6:
        return func_020758a4();
    case 7:
        return func_02075934();
    case 20:
        return func_02075830();
    case 21:
        return func_02075884();
    case 22:
        return func_020758f4();
    case 23:
        return func_0207598c();
    case 8:
        return func_02075564();
    case 9:
        return func_020755b8();
    case 10:
        return func_0207560c();
    case 11:
        return func_02075704();
    case 24:
        return func_02075598();
    case 25:
        return func_020755ec();
    case 26:
        return func_02075690();
    case 27:
        return func_02075788();
    case 15:
        return (void*)0x05000000;
    case 31:
        return (void*)0x05000400;
    case 19:
        return (void*)0x06400000;
    case 35:
        return (void*)0x06600000;
    case 14:
        return (void*)0x05000200;
    case 30:
        return (void*)0x05000600;
    case 18:
        return (void*)0x07000000;
    case 34:
        return (void*)0x07000400;
    }
    return NULL;
}

THUMB int UnkVramRequestQueue::unkfunc_0204dde4(UnkVramRequest* request)
{
    MI_CpuCopyU32(request->src_, (unsigned char*)unkfunc_0204dcec(request->type_) + request->offset_, request->size_);
    if (request->buffer_ != NULL) {
        unkfunc_0204c5c8(&data_020fd24c, request->buffer_);
    }
    request->active_ = 0;
    return request->size_;
}

THUMB int unkfunc_0204de14(int bg)
{
    switch (bg) {
    case 0:
        return 4;
    case 1:
        return 5;
    case 2:
        return 6;
    case 3:
        return 7;
    case 4:
        return 20;
    case 5:
        return 21;
    case 6:
        return 22;
    case 7:
        return 23;
    }
    return -1;
}

THUMB int unkfunc_0204de5c(int bg)
{
    switch (bg) {
    case 0:
        return 8;
    case 1:
        return 9;
    case 2:
        return 10;
    case 3:
        return 11;
    case 4:
        return 24;
    case 5:
        return 25;
    case 6:
        return 26;
    case 7:
        return 27;
    }
    return -1;
}
