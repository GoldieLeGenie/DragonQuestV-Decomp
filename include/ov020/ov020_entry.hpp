#pragma once
#include <globaldefs.h>

// work buffer of ov020 (0xc000 bytes), returned right after the overlay is loaded
extern "C" void* ov020_entry();
