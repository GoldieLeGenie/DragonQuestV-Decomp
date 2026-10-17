#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"

namespace twn {
    struct CommandObjectDefineTownSystem {
        static void setScope();
        static void setLoseReturn();
        static void setEncount();
        static void setLoadReturn();
        static void setReturnNormalMenu();
        static void setMessage();
        static void setMateriel();
        static void setXmenu();
        static void setSugoroku();
        static void setPlayer();
        static void setNormal();
        static void setTreasuerRoom();
        static void setplayerLock();
        static void setReturnMaterielMenu();
        static void setPartChangeNormal();
        static void setPartChangeFall();
        static void setTownMap();
        static void setAfterPartChange();
        static void setMenuTalk();
        static void setMenuSearchNone();
        static void setMenuSearchProgram();
        static void setMenuSearchScript();
        static void setScriptEvent();
        static void setMapLink();
        static void setPartyTalk();
        static void setWalkCount();
        static void setButtonTalk();
        static void setShopList();
        static void setFukubiki();
        static void setScreenEffect();
        static void setPlaySound();
        static void allFalse();
    };

    struct TownCommandEncount : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };
}
