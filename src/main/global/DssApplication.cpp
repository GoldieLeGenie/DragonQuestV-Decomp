#include "main/global/DssApplication.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/UnkSleep.hpp"

ARM void DssApplication::unkfunc_02051658(int arg)
{
    initSystem(arg);
    clearVram();
    unkfunc_0204b50c();
    unkfunc_0204afd8();
    initSleep();
    UnkDssRand::initSeed();
    vf00();
}

ARM void DssApplication::unkfunc_02051690()
{
    data_02101c88.unkfunc_020516e4(vf10());
}
