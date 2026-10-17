#include "main/script/ScriptFlagCommand.hpp"
#include "main/script/CommandParam.hpp"
#include "main/status/GameFlag.hpp"

THUMB bool cmdGetFlag(void* scriptParam)
{
    PARAM_GET_FLAG* param = (PARAM_GET_FLAG*)scriptParam;
    switch (param->type) {
    case 0:
        if (param->flag != 0) {
            if (g_AreaFlag.check(param->index)) {
                return true;
            }
        } else if (!g_AreaFlag.check(param->index)) {
            return true;
        }
        return false;
    case 1:
        if (param->flag != 0) {
            if (g_LocalFlag.check(param->index)) {
                return true;
            }
        } else if (!g_LocalFlag.check(param->index)) {
            return true;
        }
        return false;
    case 2:
        if (param->flag != 0) {
            if (g_GlobalFlag.check(param->index)) {
                return true;
            }
        } else if (!g_GlobalFlag.check(param->index)) {
            return true;
        }
        return false;
    }
    return false;
}

THUMB bool cmdSetFlag(void* scriptParam)
{
    PARAM_SET_FLAG* param = (PARAM_SET_FLAG*)scriptParam;
    switch (param->type) {
    case 0:
        if (param->flag != 0) {
            g_AreaFlag.set(param->index);
        } else {
            g_AreaFlag.remove(param->index);
        }
        break;
    case 1:
        if (param->flag != 0) {
            g_LocalFlag.set(param->index);
        } else {
            g_LocalFlag.remove(param->index);
        }
        break;
    case 2:
        if (param->flag != 0) {
            g_GlobalFlag.set(param->index);
        } else {
            g_GlobalFlag.remove(param->index);
        }
        break;
    }
    return true;
}
