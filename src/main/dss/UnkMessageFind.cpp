#include "main/dss/UnkMessageFind.hpp"

int data_0209a2ec = -1;
int data_0209a2e8 = -1;
unsigned char* data_020fe6ac;

ARM char* unkfunc_0204c89c(char* addr, unsigned int msg_id)
{
    if (addr == NULL) {
        return NULL;
    }
    UnkMessageFile* file = (UnkMessageFile*)addr;
    unsigned int first = file->firstId_;
    unsigned int last = file->lastId_;
    unsigned int count = file->count_;
    int offset1 = file->unk_14;
    int offset2 = file->unk_18;
    data_0209a2e8 = -1;
    data_020fe6ac = NULL;
    data_0209a2ec = -1;
    if (first > msg_id) {
        return NULL;
    }
    if (last < msg_id) {
        return NULL;
    }
    msg_id -= first;
    UnkMessageEntry* entry = file->entries_;
    for (unsigned int i = 0; i < count; i++) {
        if (entry->id_ == msg_id) {
            int size = entry->size_;
            char* msg = addr + (offset1 + offset2 + (entry->offset_ << 2));
            data_0209a2e8 = msg_id;
            data_020fe6ac = (unsigned char*)msg;
            data_0209a2ec = size;
            return msg;
        }
        entry++;
    }
    return NULL;
}
