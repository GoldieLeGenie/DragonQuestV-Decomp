#pragma once
#include <globaldefs.h>

// tells whether the town part is running (game part 4)
struct UnkTownPartCheck {
    UnkTownPartCheck();
    ~UnkTownPartCheck();
    bool isTownPart();
};

extern UnkTownPartCheck data_020efb48;
