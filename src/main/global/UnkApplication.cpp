#include "main/global/UnkApplication.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/UnkSleep.hpp"

ARM void UnkApplication::unkfunc_02051658(int arg)
{
    unkfunc_0204b09c(arg);
    unkfunc_0204b15c();
    unkfunc_0204b50c();
    unkfunc_0204afd8();
    unkfunc_0204bf48();
    UnkDssRand::unkfunc_0204f328();
    vf00();
}

ARM void UnkApplication::unkfunc_02051690()
{
    data_02101c88.unkfunc_020516e4(vf10());
}
