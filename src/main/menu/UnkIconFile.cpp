#include "main/menu/UnkIconFile.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkMessageFind.hpp"

THUMB void UnkIconFile::unkfunc_0206dc2c(const char* file)
{
    unkfunc_0206dc3c(file, NULL, 0, 0);
}

THUMB void UnkIconFile::unkfunc_0206dc3c(const char* file, const char* streamFile, int entrySize, int cacheNum)
{
    file_ = file;
    streamFile_ = streamFile;
    if (file != NULL) {
        data_.setup(file, 1, 0);
    }
    if (streamFile != NULL) {
        unkfunc_0206dd54(entrySize, cacheNum);
    }
}

THUMB void* UnkIconFile::unkfunc_0206dc68(int index)
{
    char* data = NULL;
    if (file_ != NULL) {
        data = findMessage((char*)data_.getAddr(), index);
    }
    if (data != NULL) {
        return data;
    }
    if (streamFile_ != NULL) {
        data = unkfunc_0206dde4(index);
        if (data != NULL) {
            return data;
        }
        char* entry = findMessage((char*)header_, index);
        if (entry != NULL) {
            int maxAge = 0;
            int minAge = 99999999;
            int oldest = -1;
            for (int i = 0; i < cacheNum_; i++) {
                int age = ages_[i];
                if (age > maxAge) {
                    maxAge = age;
                }
                if (age < minAge) {
                    minAge = age;
                    oldest = i;
                }
            }
            dss::g_File.unkfunc_0204b250(streamFile_, cache_ + oldest * entrySize_, entry - (char*)header_, data_0209a2ec, 0);
            data = cache_ + oldest * entrySize_;
            keys_[oldest] = index;
            ages_[oldest] = maxAge + 1;
        }
    }
    if (data == NULL) {
        data = NULL;
    }
    return data;
}

THUMB void UnkIconFile::unkfunc_0206dd28()
{
    if (streamFile_ != NULL) {
        for (int i = 0; i < cacheNum_; i++) {
            keys_[i] = -1;
            ages_[i] = -1;
        }
    }
}

THUMB void UnkIconFile::unkfunc_0206dd54(int entrySize, int cacheNum)
{
    entrySize_ = entrySize;
    cacheNum_ = cacheNum;
    keys_ = (int*)allocAppHeap(&data_020fd24c, cacheNum * 4, 0x20);
    ages_ = (int*)allocAppHeap(&data_020fd24c, cacheNum * 4, 0x20);
    cache_ = (char*)allocAppHeap(&data_020fd24c, entrySize * cacheNum, 0x20);
    unkfunc_0206dd28();
    DataObject header;
    header.setup(streamFile_, 1, 0);
    UnkMessageFile* file = (UnkMessageFile*)header.getAddr();
    int size = file->unk_14 + file->unk_18;
    header.cleanup();
    header_ = allocAppHeap(&data_020fd24c, size, 0x20);
    dss::g_File.unkfunc_0204b250(streamFile_, header_, 0, size, 0);
}

THUMB char* UnkIconFile::unkfunc_0206dde4(int index)
{
    for (int i = 0; i < cacheNum_; i++) {
        if (keys_[i] == index) {
            return cache_ + i * entrySize_;
        }
    }
    return NULL;
}
