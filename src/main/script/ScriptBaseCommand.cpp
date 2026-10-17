#include "main/script/ScriptBaseCommand.hpp"
#include "main/script/sys/PlacementParameter.hpp"
#include "main/global/UnkTownPartCheck.hpp"
#include "ov001/town/TownCharacterManager.hpp"

inline bool CommandParameter::isTypeA()
{
    return flag_ == FLAG_TYPE_A;
}

inline bool CommandParameter::isTypeB()
{
    return flag_ & FLAG_TYPE_B;
}

inline void CommandParameter::setInitialized()
{
    flag_ |= FLAG_INITIALIZED;
}

inline bool CommandParameter::isInitialized()
{
    return flag_ & FLAG_INITIALIZED;
}

inline void CommandParameter::setTerminated()
{
    flag_ |= FLAG_TERMINATED;
}

inline bool CommandParameter::isTerminated()
{
    return flag_ & FLAG_TERMINATED;
}

inline char* CommandParameter::getParam()
{
    return param_;
}

THUMB bool ScriptCommand::exec(CommandParameter* param)
{
    if (param->isTypeA()) {
        execute();
    }
    if (param->isTypeB()) {
        if (!param->isInitialized()) {
            param->setInitialized();
            initialize(param->getParam());
        }
        if (!param->isTerminated()) {
            execute();
            if (isEnd()) {
                param->setTerminated();
                terminate();
            }
        }
    }
    return param->isTerminated();
}

THUMB void ScriptCommand::execute()
{
}

THUMB void ScriptCommand::terminate()
{
}

THUMB int StartFunction(void* startParam)
{
    Param param = *(Param*)startParam;
    int ctrl = 0;
    if (data_020efb48.unkfunc_0203f2a8()) {
        TOWN_CHARACTER chara;
        chara.charaIndex = param.index_;
        chara.dir = param.dir_ << 14;
        chara.position.vx.value = param.x_;
        chara.position.vy.value = param.y_;
        chara.position.vz.value = param.z_;
        ctrl = TownCharacterManager::getSingleton()->setup(chara);
    }
    return ctrl;
}

int ctrlId_;
int objectCount;
int scriptObjectCtrl[48];
int scriptObjectEnable[48];

THUMB void initializeScriptObjectEnble()
{
    for (int i = 0; i < 48; i++) {
        scriptObjectEnable[i] = false;
    }
}

THUMB void setScriptObjectEnable(int index, bool flag)
{
    scriptObjectEnable[index] = flag;
}

THUMB int isScriptObjectEnble(int index)
{
    return scriptObjectEnable[index];
}

THUMB int getObjectCount()
{
    return objectCount;
}

THUMB void initializeScriptObjectCtrl()
{
    for (int i = 0; i < 48; i++) {
        scriptObjectCtrl[i] = 0;
    }
    objectCount = 0;
}

THUMB void setScriptObjectCtrl(int index, int ctrl)
{
    scriptObjectCtrl[index] = ctrl;
    objectCount++;
}

THUMB int getScriptObjectCtrl(int index)
{
    for (int i = 0; i < 48; i++) {
        if (index == scriptObjectCtrl[i]) {
            return i;
        }
    }
    return -1;
}

THUMB int getScriptObjectIndex(int ctrl)
{
    return scriptObjectCtrl[ctrl];
}

THUMB void setPlacementCtrlId(int ctrl)
{
    ctrlId_ = ctrl;
}

THUMB int getPlacementCtrlId()
{
    return ctrlId_;
}

THUMB int getPlacementCtrlId(int index)
{
    return getScriptObjectCtrl(index);
}

THUMB int getPlacementIndex(int ctrl)
{
    return getScriptObjectIndex(ctrl);
}
