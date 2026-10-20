#pragma once
#include <globaldefs.h>

int getArchiveFileCount(void* archive);            // file count of an archive
int getArchiveFileSize(void* archive, int index); // file size in an archive
void* getArchiveFile(void* archive, int index);   // file of an archive
