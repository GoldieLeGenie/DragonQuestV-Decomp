#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkRandom.hpp"

THUMB int dss::getRandomVariation(int value, int under, int over)
{
    return value * (100 - under + UnkDssRand::rand(under + over + 1)) / 100;
}
