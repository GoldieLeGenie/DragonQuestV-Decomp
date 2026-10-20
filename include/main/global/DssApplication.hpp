#pragma once
#include <globaldefs.h>
#include "main/dss/DssCore.hpp"


struct DssApplication {
    virtual void vf00();                        // called by initialize after the system init
    virtual void vf04();  
    virtual void vf08();  
    virtual void vf0c();  
    virtual int vf10();                          // first task given to UnkGlobalSystem
    virtual void vf14();  

    void initialize(int arg);
    void run();
};

extern DssApplication data_0210bb78;

