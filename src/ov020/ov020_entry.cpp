#include "ov020/ov020_entry.hpp"

// work buffer of the overlay, its address is kept by the main module while ov020 is loaded
char data_ov020_0216f220[0xc000];

// Called right after loading ov020, gives the buffer to the caller
extern "C" THUMB void* ov020_entry()
{
    return data_ov020_0216f220;
}
