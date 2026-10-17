#pragma once
#include <globaldefs.h>
#include "main/status/BaseHaveAction.hpp"

namespace status {
    struct HaveAction {
        enum ActionMode {
            TownMode = 0,
            BattleMode = 1,
        };
        static const int ACTION_NONE = 0;
        static const int ACTION_MAX = 18;

        BaseHaveAction action_[ACTION_MAX];
        unsigned short index_;
        unsigned short kind_;
        unsigned short level_;

        static int addRulaLevel_;           // data_020a1024
        static ActionMode mode_;            // data_020a1028
        static int addParupunteLevel_;      // data_020a102c

        HaveAction();
        ~HaveAction();
        static void setBattleMode();
        static bool isBattleMode();
        static void setTownMode();
        static bool isTownMode();
        static ActionMode getActionMode();
        static void setActionMode(ActionMode md);
        static unsigned char getRulaLevel();
        static unsigned char getParupunteLevel();
        static void setRulaLevel(unsigned char level);
        static void setParupunteLevel(unsigned char level);
        void setup(int index, int level);
        void cleanup(int index);
        void clear();
        void execLevelup(int level, bool flag);
        void debugLevelup(int level);
        void loadLevelup(int level, int rulaLevel, int parupunteLevel);
        void levelup(int index, int level, bool flag);
        void add(int battleAction, int usuallyAction, bool flag);
        int getAction(int index);
        int getCount();
        int getCountAll();
        int getActionAll(int index);
        bool isAction(int actionIndex);
        int getRememberingAction();
        void clearRememberingAction();
    };
}
