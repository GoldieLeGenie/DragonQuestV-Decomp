#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

struct BaseTask;

// one task at a time, switched by id
struct RandomTaskManager {
    BaseTask* parts_[24];                       // 0x00
    BaseTask* currentTask_;                     // 0x60
    int currentTaskID_;                         // 0x64
    int previousTaskID_;                        // 0x68
    int nextTaskID_;                            // 0x6C
    int sleepTaskID_;                           // 0x70

    RandomTaskManager();
    ~RandomTaskManager();
    void initialize();
    void run();
    void registerTask(int id, BaseTask* task);
    void setNextTask(int id);
    int getCurrentTask();
    bool checkTask(int id);
    int getPreviousTask();
    void setNextTaskWithSleep(int id);
    void wakeup();
};

// tasks run one after the other
struct SequentialTaskManager {
    // vtable                                   // 0x00
    dss::Flag flag_;                            // 0x04
    int currentId_;                             // 0x08
    BaseTask* pExecTask_[32];                   // 0x0C

    SequentialTaskManager();
    ~SequentialTaskManager();
    void initialize();
    virtual void initialize_user() = 0;
    void terminate();
    virtual void terminate_user() = 0;
    bool execute();
    void clear();
    void resister(int index, BaseTask* execTask);
    virtual void interruptResister(int index);
};

struct BaseTask {
    // vtable                                   // 0x00
    dss::Flag flag_;                            // 0x04

    BaseTask();
    ~BaseTask();
    bool exec();
    virtual void initialize();
    virtual void terminate();
    virtual void execute();
    virtual int isEnd();
};
