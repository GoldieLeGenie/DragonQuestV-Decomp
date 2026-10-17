#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

struct ExecTask {
    // vtable                           // 0x00
    dss::Flag flag_;                    // 0x04

    ExecTask();
    ~ExecTask();
    bool execute();
    virtual void setup();
    virtual void exec();
    void terminate();
    virtual void cleanup();
    virtual bool isEnd();
};

struct ExecTask2 {
    // vtable                           // 0x00
    dss::Flag flag_;                    // 0x04
    int autoMessage_;                   // 0x08

    ExecTask2();
    ~ExecTask2();
    bool execute();
    void setAutoMessage(bool flag);
    virtual void setup() = 0;
    virtual void exec();
    virtual void cleanup() = 0;
    virtual bool isEnd();
};

struct ExecTaskManager {
    // vtable                           // 0x00
    dss::Flag flag_;                    // 0x04
    ExecTask* pExecTask_[16];           // 0x08
    int currentId_;                     // 0x48

    ExecTaskManager();
    ~ExecTaskManager();
    virtual void initialize();
    void terminate();
    bool execute();
    void unkfunc_0202392c();
    void resister(int id, ExecTask* task);
};

struct ExecTaskManager2 {
    // vtable                           // 0x00
    dss::Flag flag_;                    // 0x04
    int currentId_;                     // 0x08
    ExecTask2* pExecTask_[16];          // 0x0C

    ExecTaskManager2();
    void initialize();
    virtual void initialize_user() = 0;
    bool execute();
    void terminate();
    virtual void terminate_user() = 0;
    void clear();
    void resister(int index, ExecTask2* execTask);
};
