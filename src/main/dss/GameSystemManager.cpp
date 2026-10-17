#include "main/dss/GameSystemManager.hpp"
#include "main/dss/CommandObject.hpp"
#include "main/dss/DssCore.hpp"

ARM args::CommandObjectManager::CommandObjectManager()
{
    for (int i = 0; i < COMMAND_OBJECT_MAX; i++) {
        commandObject_[i] = NULL;
    }
}

ARM args::CommandObjectManager::~CommandObjectManager()
{
}

ARM void args::CommandObjectManager::initialize()
{
    for (int i = 0; i < COMMAND_OBJECT_MAX; i++) {
        commandObject_[i] = NULL;
    }
}

ARM void args::CommandObjectManager::enRegister(CommandObject& object, int priority)
{
    commandObject_[priority] = &object;
}

ARM void args::CommandObjectManager::execute()
{
    if (!commandObject_[state_]->isEnd()) {
        return;
    }
    for (int i = 0; i < COMMAND_OBJECT_MAX; i++) {
        if (commandObject_[i] != NULL && commandObject_[i]->isExec()) {
            commandObject_[i]->exec();
            state_ = i;
            return;
        }
    }
}

ARM args::CommandObject::CommandObject()
{
}

ARM args::CommandObject::~CommandObject()
{
}

ARM args::GameSystemManager::GameSystemManager()
{
}

ARM args::GameSystemManager::~GameSystemManager()
{
}

ARM args::GameSystemManager& args::GameSystemManager::getSingleton()
{
    static GameSystemManager m_singleton;
    return m_singleton;
}

ARM void args::GameSystemManager::enRegister(GameSystem& system, int execPriority, int drawPriority, int exclusion)
{
    gameSystem_[execPriority] = &system;
    drawSystem_[drawPriority] = &system;
    defExclusion_[execPriority] = exclusion;
}

ARM void args::GameSystemManager::setExclusion(int index, bool flag)
{
    execExclusion_[index] = flag;
}

ARM void args::GameSystemManager::setDrawExclusion(int index, bool flag)
{
    drawExclusion_[index] = flag;
}

ARM void args::GameSystemManager::clear()
{
    for (int i = 0; i < GAME_SYSTEM_MAX; i++) {
        gameSystem_[i] = NULL;
        drawSystem_[i] = NULL;
        defExclusion_[i] = false;
        execExclusion_[i] = true;
        drawExclusion_[i] = true;
        execTime_[i] = 0;
        drawTime_[i] = 0;
    }
}

ARM void args::GameSystemManager::initialize()
{
    for (int i = 0; i < GAME_SYSTEM_MAX; i++) {
        if (gameSystem_[i] != NULL) {
            gameSystem_[i]->initialize();
        }
    }
}

ARM void args::GameSystemManager::terminate()
{
    for (int i = GAME_SYSTEM_MAX - 1; i >= 0; i--) {
        if (gameSystem_[i] != NULL) {
            gameSystem_[i]->terminate();
        }
    }
}

ARM void args::GameSystemManager::execute()
{
    for (int i = 0; i < GAME_SYSTEM_MAX; i++) {
        if (gameSystem_[i] == NULL) {
            continue;
        }
        if (defExclusion_[i] && !execExclusion_[i]) {
            continue;
        }
        int tick = unkfunc_0204afe0();
        gameSystem_[i]->execute();
        execTime_[i] = unkfunc_0204afe0() - tick;
    }
}

ARM void args::GameSystemManager::draw()
{
    for (int i = 0; i < GAME_SYSTEM_MAX; i++) {
        if (drawSystem_[i] == NULL) {
            continue;
        }
        if (defExclusion_[i] && !drawExclusion_[i]) {
            continue;
        }
        int tick = unkfunc_0204afe0();
        drawSystem_[i]->draw();
        drawTime_[i] = unkfunc_0204afe0() - tick;
    }
}

ARM args::GameSystem::GameSystem()
{
}

ARM args::GameSystem::~GameSystem()
{
}
