#include "main/script/sys/ScriptTree.hpp"

bool (*ScriptTree::executeFunction_)(int);
bool (*ScriptTree::displayFunction_)(int);
bool (*ScriptTree::getScriptCommandClearFlag_)(int);
void (*ScriptTree::clearStatusFunction_)(int);
int (*ScriptTree::getScriptCommandTypeFunction_)(int);
bool (*ScriptTree::checkStatusFunction_)();

ARM ScriptTree::ScriptTree()
{
}

ARM ScriptTree::~ScriptTree()
{
}

ARM void ScriptTree::setExecuteFunction(bool (*fc)(int))
{
    executeFunction_ = fc;
}

ARM void ScriptTree::setCheckStatusFunction(bool (*fc)())
{
    checkStatusFunction_ = fc;
}

ARM void ScriptTree::setClearStatusFunction(void (*fc)(int))
{
    clearStatusFunction_ = fc;
}

ARM void ScriptTree::setGetScriptCommandTypeFunction(int (*fc)(int))
{
    getScriptCommandTypeFunction_ = fc;
}

ARM void ScriptTree::setGetScriptCommandClearFlag(bool (*fc)(int))
{
    getScriptCommandClearFlag_ = fc;
}

ARM void ScriptTree::setDisplayFunction(bool (*fc)(int))
{
    displayFunction_ = fc;
}

ARM void ScriptTree::recursiveTree()
{
    while (true) {
        int cmdIndex = getCurrentNode()->getValue();
        if ((unsigned char)cmdIndex == 0xff) {
            if (isCurrentChild()) {
                moveCurrentChild();
                recursiveTree();
                moveCurrentParent(1);
            }
            return;
        }
        bool execFlag = executeFunction_(cmdIndex);
        bool endFlag = checkStatusFunction_();
        if (execFlag && isCurrentChild()) {
            moveCurrentChild();
            recursiveTree();
            moveCurrentParent(1);
        }
        if (!endFlag) {
            return;
        }
        if (isCurrentNext()) {
            moveCurrentNext();
            continue;
        }
        if (!getScriptCommandClearFlag_(getCurrentNode()->getValue())) {
            return;
        }
        while (isCurrentPrev()) {
            moveCurrentPrev();
        }
        while (isCurrentNext()) {
            clearStatusFunction_(getCurrentNode()->getValue());
            moveCurrentNext();
        }
        clearStatusFunction_(getCurrentNode()->getValue());
        return;
    }
}

ARM void ScriptTree::display()
{
    moveCurrentRoot();
    recursiveDisplay();
}

ARM void ScriptTree::recursiveDisplay()
{
    while (true) {
        executeFunction_(getCurrentNode()->getValue());
        if (isCurrentChild()) {
            moveCurrentChild();
            recursiveDisplay();
            moveCurrentParent(1);
        }
        if (!isCurrentNext()) {
            return;
        }
        moveCurrentNext();
    }
}

template dss::Tree<unsigned char, 160>::Tree();
template void dss::Tree<unsigned char, 160>::moveCurrentPrev();
template bool dss::Tree<unsigned char, 160>::isCurrentChild();
template bool dss::Tree<unsigned char, 160>::isCurrentNext();
template bool dss::Tree<unsigned char, 160>::isCurrentPrev();
template dss::Node<unsigned char>* dss::Tree<unsigned char, 160>::getCurrentNode();
template dss::NodeArray<unsigned char, 160>::NodeArray();
template dss::Node<unsigned char>::Node();
template unsigned char dss::Node<unsigned char>::getValue();
template void dss::Tree<unsigned char, 160>::display();
template void dss::Tree<unsigned char, 160>::recursiveTree();
