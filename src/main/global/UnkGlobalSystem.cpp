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

ARM void UnkGlobalSystem::run(int partId)
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
        startTask(currentTask_);
        while (true) {
            executeTask(currentTask_);
            if (s_hook.unk_08 != 0) {
                s_hook.unk_08();
            }
            if (nextPartId_ != -1) {
                break;
            }
            frameCount_++;
        }
        endTask(currentTask_);
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

ARM void UnkGlobalSystem::registerTask(int partId, UnkGameTask* task)
{
    if (partId >= 24) {
        reportArrayError(partId, 24);
    }
    if (partId < 0) {
        reportArrayError(partId, 24);
    }
    task_[partId] = task;
}

ARM void UnkGlobalSystem::setNextPart(int partId)
{
    nextPartId_ = partId;
}

ARM int UnkGlobalSystem::getNextPart()
{
    return nextPartId_;
}

ARM int UnkGlobalSystem::getCurrentPart()
{
    return part_id_;
}

ARM int UnkGlobalSystem::isCurrentPart(int partId)
{
    return part_id_ == partId;
}

ARM void UnkGlobalSystem::setFrameHook(void (*func)())
{
    s_hook.unk_08 = func;
}

ARM void UnkGlobalSystem::setTaskChangeHook(void (*func)())
{
    s_hook.unk_04 = func;
}

ARM void UnkGlobalSystem::setTaskEndHook(void (*func)())
{
    s_endHook = func;
}

ARM void UnkGlobalSystem::startTask(UnkGameTask* task)
{
    task->vf00();
}

ARM void UnkGlobalSystem::endTask(UnkGameTask* task)
{
    task->vf04();
    if (s_endHook != 0) {
        s_endHook();
    }
}

ARM void UnkGlobalSystem::executeTask(UnkGameTask* task)
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
