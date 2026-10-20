#include "main/global/DssApplication.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/UnkSleep.hpp"

ARM void DssApplication::initialize(int arg)
{
    initSystem(arg);
    clearVram();
    resetBgObjVram();
    unkfunc_0204afd8();
    initSleep();
    UnkDssRand::initSeed();
    vf00();
}

ARM void DssApplication::run()
{
    data_02101c88.run(vf10());
}
