#pragma once
#include <globaldefs.h>

namespace args
{
    struct GameSystem {
        // vtable                               // 0x00

        GameSystem();
        ~GameSystem();
        virtual void initialize() = 0;
        virtual void terminate() = 0;
        virtual void execute() = 0;
        virtual void draw() = 0;
    };

    struct GameSystemManager {
        static const int GAME_SYSTEM_MAX = 64;

        GameSystem* gameSystem_[GAME_SYSTEM_MAX];       // 0x000
        GameSystem* drawSystem_[GAME_SYSTEM_MAX];       // 0x100
        int defExclusion_[GAME_SYSTEM_MAX];             // 0x200
        int execExclusion_[GAME_SYSTEM_MAX];            // 0x300
        int drawExclusion_[GAME_SYSTEM_MAX];            // 0x400
        short execTime_[GAME_SYSTEM_MAX];               // 0x500 ticks spent in execute
        short drawTime_[GAME_SYSTEM_MAX];               // 0x580 ticks spent in draw

        GameSystemManager();
        ~GameSystemManager();
        static GameSystemManager& getSingleton();
        void enRegister(GameSystem& system, int execPriority, int drawPriority, int exclusion);
        void clear();
        void initialize();
        void terminate();
        void execute();
        void draw();
        void setExclusion(int index, bool flag);
        void setDrawExclusion(int index, bool flag);
    };
} // namespace args
