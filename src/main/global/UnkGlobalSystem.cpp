#include "main/global/UnkGlobalSystem.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkArrayWarning.hpp"

UnkGlobalSystem data_02101c88;
static void (*s_endHook)();
static UnkGameTaskHook s_hook;

ARM UnkGlobalSystem::UnkGlobalSystem()
{
    currentTask_ = 0;
    part_id_ = 0;
    prevPartId_ = -1;
    nextPartId_ = -1;
    unk_70 = 1;
    unk_78 = 1;
    frameCount_ = 0;
}

ARM UnkGlobalSystem::~UnkGlobalSystem()
{
}

ARM void UnkGlobalSystem::unkfunc_020516e4(int partId)
{
    part_id_ = partId;
    markHeapBlocks(&data_020fd24c);
    while (1) {
        int id = part_id_;
        if (id >= 24) {
            reportArrayError(id, 24);
        }
        if (id < 0) {
            reportArrayError(id, 24);
        }
        currentTask_ = task_[id];
        unkfunc_0205185c(currentTask_);
        while (true) {
            unkfunc_0205189c(currentTask_);
            if (s_hook.unk_08 != 0) {
                s_hook.unk_08();
            }
            if (nextPartId_ != -1) {
                break;
            }
            frameCount_++;
        }
        unkfunc_02051870(currentTask_);
        prevPartId_ = part_id_;
        part_id_ = nextPartId_;
        nextPartId_ = -1;
        if (unk_74 != 0) {
            unk_74 = 0;
            if (s_hook.unk_04 != 0) {
                s_hook.unk_04();
            }
        }
    }
}

ARM void UnkGlobalSystem::unkfunc_020517c0(int partId, UnkGameTask* task)
{
    if (partId >= 24) {
        reportArrayError(partId, 24);
    }
    if (partId < 0) {
        reportArrayError(partId, 24);
    }
    task_[partId] = task;
}

ARM void UnkGlobalSystem::unkfunc_02051800(int partId)
{
    nextPartId_ = partId;
}

ARM int UnkGlobalSystem::unkfunc_02051808()
{
    return nextPartId_;
}

ARM int UnkGlobalSystem::unkfunc_02051810()
{
    return part_id_;
}

ARM int UnkGlobalSystem::unkfunc_02051818(int partId)
{
    return part_id_ == partId;
}

ARM void UnkGlobalSystem::unkfunc_0205182c(void (*func)())
{
    s_hook.unk_08 = func;
}

ARM void UnkGlobalSystem::unkfunc_0205183c(void (*func)())
{
    s_hook.unk_04 = func;
}

ARM void UnkGlobalSystem::unkfunc_0205184c(void (*func)())
{
    s_endHook = func;
}

ARM void UnkGlobalSystem::unkfunc_0205185c(UnkGameTask* task)
{
    task->vf00();
}

ARM void UnkGlobalSystem::unkfunc_02051870(UnkGameTask* task)
{
    task->vf04();
    if (s_endHook != 0) {
        s_endHook();
    }
}

ARM void UnkGlobalSystem::unkfunc_0205189c(UnkGameTask* task)
{
    task->vf08();
    task->vf0c();
    task->vf10();
}

ARM void UnkGameTaskHook::vf00()
{
}

ARM void UnkGameTaskHook::vf04()
{
}

ARM void UnkGameTaskHook::vf08()
{
}

ARM void UnkGameTaskHook::vf10()
{
}

ARM void UnkGameTaskHook::vf0c()
{
}
