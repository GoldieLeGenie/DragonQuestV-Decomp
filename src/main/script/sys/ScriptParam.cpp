#include "main/script/sys/ScriptParam.hpp"
#include "main/dss/UnkArchive.hpp"

static unsigned char* paramBuff;
bool (*ScriptParam::executeCommandFunction_)(void*);
static ScriptParam* tempScriptParam;

ARM ScriptParam::ScriptParam()
{
}

ARM ScriptParam::~ScriptParam()
{
}

ARM void ScriptParam::setup(void* addr)
{
    dataObject_.setup(addr);
    setup();
}

ARM void ScriptParam::setup()
{
    tree_ = (char*)unkfunc_0204c878(dataObject_.getAddr(), 0);
    offset_ = (int*)unkfunc_0204c878(dataObject_.getAddr(), 1);
    command_ = (unsigned char*)unkfunc_0204c878(dataObject_.getAddr(), 2);
    count_ = unkfunc_0204c868(dataObject_.getAddr(), 0);
    char level = -1;
    scriptTree_.clear();
    scriptTree_.setRoot(level);
    for (int i = 0; i < count_; i++) {
        char index = i;
        char lvl = tree_[i];
        if (level + 1 == lvl) {
            scriptTree_.addChild(index);
        } else if (level == lvl) {
            scriptTree_.addNext(index);
        } else {
            scriptTree_.moveCurrentParent(level - lvl);
            scriptTree_.addNext(index);
        }
        level = tree_[i];
    }
}

ARM void ScriptParam::cleanup()
{
    scriptTree_.clear();
    dataObject_.cleanup();
}

ARM static bool ExecuteScriptCommand(int cmdIndex)
{
    return tempScriptParam->execScriptCommand(cmdIndex);
}

ARM static bool CheckScriptCommandStatus()
{
    return tempScriptParam->checkScriptCommandStatus();
}

ARM static void ClearScriptCommandStatus(int cmdIndex)
{
    tempScriptParam->clearScriptCommandStatus(cmdIndex);
}

ARM static int GetScriptCommandType(int cmdIndex)
{
    return tempScriptParam->getScriptCommandType(cmdIndex);
}

ARM static bool GetScriptCommandClearFlag(int cmdIndex)
{
    return tempScriptParam->getScriptCommandClearFlag(cmdIndex);
}

ARM void ScriptParam::execute()
{
    if (count_ == 0) {
        return;
    }
    tempScriptParam = this;
    scriptTree_.moveCurrentRoot();
    scriptTree_.recursiveTree();
}

ARM void ScriptParam::setExecuteCommandFunction(bool (*fc)(void*))
{
    executeCommandFunction_ = fc;
    ScriptTree::setExecuteFunction(ExecuteScriptCommand);
    ScriptTree::setCheckStatusFunction(CheckScriptCommandStatus);
    ScriptTree::setClearStatusFunction(ClearScriptCommandStatus);
    ScriptTree::setGetScriptCommandTypeFunction(GetScriptCommandType);
    ScriptTree::setGetScriptCommandClearFlag(GetScriptCommandClearFlag);
}

ARM bool ScriptParam::execScriptCommand(int cmdIndex)
{
    if (cmdIndex == -1) {
        return true;
    }
    paramBuff = &command_[offset_[cmdIndex]];
    return executeCommandFunction_(paramBuff);
}

ARM bool ScriptParam::checkScriptCommandStatus()
{
    if (paramBuff[2] == 0) {
        return true;
    }
    return (paramBuff[2] & 0x40) ? true : false;
}

ARM void ScriptParam::clearScriptCommandStatus(int cmdIndex)
{
    unsigned char* param = &command_[offset_[cmdIndex]];
    param[2] &= ~0x50;
}

ARM int ScriptParam::getScriptCommandType(int cmdIndex)
{
    unsigned char* param = &command_[offset_[cmdIndex]];
    if (param[2] == 0) {
        return 0;
    }
    return (param[2] & 1) ? 1 : 2;
}

ARM bool ScriptParam::getScriptCommandClearFlag(int cmdIndex)
{
    unsigned char* param = &command_[offset_[cmdIndex]];
    return (param[2] & 2) ? true : false;
}

template void dss::Tree<unsigned char, 160>::clear();
template void dss::Tree<unsigned char, 160>::setRoot(unsigned char);
template void dss::Tree<unsigned char, 160>::addChild(unsigned char);
template void dss::Tree<unsigned char, 160>::addNext(unsigned char);
template void dss::Tree<unsigned char, 160>::moveCurrentRoot();
template void dss::Tree<unsigned char, 160>::moveCurrentChild();
template void dss::Tree<unsigned char, 160>::moveCurrentNext();
template void dss::Tree<unsigned char, 160>::moveCurrentParent(int);
template void dss::NodeArray<unsigned char, 160>::clear();
template int dss::NodeArray<unsigned char, 160>::getNodeIndex(unsigned char);
template void dss::Node<unsigned char>::setValue(unsigned char);
template void dss::Node<unsigned char>::clear();
