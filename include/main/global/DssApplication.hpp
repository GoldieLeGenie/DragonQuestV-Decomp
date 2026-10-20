#pragma once
#include <globaldefs.h>
#include "main/dss/DssCore.hpp"


struct DssApplication {
    virtual void vf00();                        // called by unkfunc_02051658 after the system init
    virtual void vf04();  
    virtual void vf08();  
    virtual void vf0c();  
    virtual int vf10();                          // first task given to UnkGlobalSystem
    virtual void vf14();  

    void unkfunc_02051658(int arg);
    void unkfunc_02051690();
};

extern DssApplication data_0210bb78;

