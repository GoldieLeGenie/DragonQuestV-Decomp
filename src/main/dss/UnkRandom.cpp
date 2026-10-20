#include <globaldefs.h>
#include "main/dss/UnkRandom.hpp"

UnkDssRand::UnkRandom UnkDssRand::UnkDssRand;


ARM void UnkDssRand::initSeed()
{
    unsigned int buffer[8];
    unsigned int seed = 0;
    OS_GetLowEntropyData(buffer);
    for (int i = 0; i < 8; i++) {
        seed += buffer[i];
    }
    UnkDssRand.state = seed;
    UnkDssRand.multiplier = 0x5d588b65;
    UnkDssRand.increment = 0x269ec3;
}

ARM int UnkDssRand::rand(int n) {
    unsigned int masked_n;
    
    UnkDssRand::UnkDssRand.state = UnkDssRand::UnkDssRand.multiplier * UnkDssRand::UnkDssRand.state + UnkDssRand::UnkDssRand.increment;

    masked_n = (unsigned int)n & 0xFFFF;

    if (masked_n != 0) {
        return ((((UnkDssRand::UnkDssRand.state >> 16) * masked_n) >> 16) & 0xFFFF);
    }
    return ((UnkDssRand::UnkDssRand.state >> 16) & 0xFFFF);
}