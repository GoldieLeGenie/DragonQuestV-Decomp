#include "main/task/BaseTask.hpp"

ARM BaseTask::BaseTask()
{
    flag_.clear();
}

ARM BaseTask::~BaseTask()
{
}

ARM bool BaseTask::exec()
{
    if (!flag_.check(1)) {
        flag_.clear();
        flag_.flag_ |= 1;
        initialize();
    }
    execute();
    if (isEnd()) {
        terminate();
        flag_.clear();
        return false;
    }
    return true;
}

ARM void BaseTask::initialize()
{
}

ARM void BaseTask::terminate()
{
}

ARM void BaseTask::execute()
{
}

ARM int BaseTask::isEnd()
{
    return true;
}

ARM RandomTaskManager::RandomTaskManager()
{
    currentTask_ = NULL;
    currentTaskID_ = 0;
    previousTaskID_ = -1;
    nextTaskID_ = -1;
    sleepTaskID_ = -1;
}

ARM RandomTaskManager::~RandomTaskManager()
{
}

ARM void RandomTaskManager::initialize()
{
    currentTask_ = NULL;
    currentTaskID_ = 0;
    previousTaskID_ = -1;
    nextTaskID_ = -1;
    sleepTaskID_ = -1;
}

ARM void RandomTaskManager::run()
{
    if (currentTask_ != NULL) {
        currentTask_->execute();
    }
    if (sleepTaskID_ != -1) {
        if (currentTaskID_ != -1) {
            return;
        }
        previousTaskID_ = currentTaskID_;
        currentTaskID_ = nextTaskID_;
        nextTaskID_ = -1;
        currentTask_ = parts_[currentTaskID_];
        currentTask_->initialize();
        return;
    }
    if (nextTaskID_ == -1) {
        return;
    }
    if (currentTask_ != NULL) {
        currentTask_->terminate();
    }
    previousTaskID_ = currentTaskID_;
    currentTaskID_ = nextTaskID_;
    nextTaskID_ = -1;
    currentTask_ = parts_[currentTaskID_];
    currentTask_->initialize();
}

ARM void RandomTaskManager::registerTask(int id, BaseTask* task)
{
    parts_[id] = task;
}

ARM void RandomTaskManager::setNextTask(int id)
{
    nextTaskID_ = id;
}

ARM int RandomTaskManager::getCurrentTask()
{
    return currentTaskID_;
}

ARM bool RandomTaskManager::checkTask(int id)
{
    return currentTaskID_ == id;
}

ARM int RandomTaskManager::getPreviousTask()
{
    return previousTaskID_;
}

ARM void RandomTaskManager::setNextTaskWithSleep(int id)
{
    sleepTaskID_ = currentTaskID_;
    currentTaskID_ = -1;
    setNextTask(id);
}

ARM void RandomTaskManager::wakeup()
{
    currentTaskID_ = sleepTaskID_;
    sleepTaskID_ = -1;
    currentTask_ = parts_[currentTaskID_];
}

ARM SequentialTaskManager::SequentialTaskManager()
{
    flag_.clear();
}

ARM SequentialTaskManager::~SequentialTaskManager()
{
}

ARM void SequentialTaskManager::initialize()
{
    clear();
    flag_.flag_ |= 1;
    initialize_user();
}

ARM void SequentialTaskManager::terminate()
{
    terminate_user();
    flag_.flag_ &= ~1;
}

ARM bool SequentialTaskManager::execute()
{
    if (!flag_.check(1)) {
        initialize();
    }
    if (!flag_.check(2)) {
        if (pExecTask_[currentId_] != NULL) {
            if (!pExecTask_[currentId_]->exec()) {
                currentId_++;
                if (pExecTask_[currentId_] == NULL) {
                    interruptResister(currentId_);
                }
                if (pExecTask_[currentId_] == NULL) {
                    flag_.flag_ |= 2;
                }
            }
        } else {
            flag_.flag_ |= 2;
        }
    }
    if (!flag_.check(2)) {
        return true;
    }
    terminate();
    return false;
}

ARM void SequentialTaskManager::clear()
{
    flag_.clear();
    currentId_ = 0;
    for (int i = 0; i < 32; i++) {
        pExecTask_[i] = NULL;
    }
}

ARM void SequentialTaskManager::resister(int index, BaseTask* execTask)
{
    pExecTask_[index] = execTask;
}

ARM void SequentialTaskManager::interruptResister(int index)
{
}
