#pragma once
#include <globaldefs.h>


struct UnkGameTask {
    virtual void vf00();                        // called when the task starts
    virtual void vf04();                        // called when the task ends
    virtual void vf08();                        // called every frame
    virtual void vf0c();                        // called every frame
    virtual void vf10();                        // called every frame
};


struct UnkGameTaskHook {
    // vtable                                   // 0x00
    void (*unk_04)();                           // 0x04  called once after a task change
    void (*unk_08)();                           // 0x08  called every frame

    virtual void vf00();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
    virtual void vf10();
};


struct UnkGlobalSystem {
    UnkGameTask* task_[24];                     // 0x00
    UnkGameTask* currentTask_;                  // 0x60
    int part_id_;                               // 0x64  current task
    int prevPartId_;                            // 0x68
    int nextPartId_;                            // 0x6C
    int unk_70;                                 // 0x70
    int callChangeHook_;                                 // 0x74  call the task change hook once
    int unk_78;                                 // 0x78
    int frameCount_;                            // 0x7C  frames of the current task

    UnkGlobalSystem();
    ~UnkGlobalSystem();
    void run(int partId);                      // run (never returns)
    void registerTask(int partId, UnkGameTask* task);   // register task
    void setNextPart(int partId);                      // set next task
    int getNextPart();                                 // next task
    int getCurrentPart();                                 // current task (13 = battle auto feed)
    int isCurrentPart(int partId);                       // part_id_ == partId
    static void setFrameHook(void (*func)());
    static void setTaskChangeHook(void (*func)());
    static void setTaskEndHook(void (*func)());
    static void startTask(UnkGameTask* task);
    static void endTask(UnkGameTask* task);
    static void executeTask(UnkGameTask* task);
};

extern UnkGlobalSystem data_02101c88;
