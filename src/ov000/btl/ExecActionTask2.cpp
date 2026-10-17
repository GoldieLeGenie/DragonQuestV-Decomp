#include "ov000/btl/ExecActionTask2.hpp"
#include "main/status/BaseAction.hpp"
#include "main/status/UseActionParam.hpp"

inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }

status::UseActionParam* btl::ExecActionTask2::useActionParam_;

THUMB void btl::ExecActionTask2::initialize()
{
    status::BaseAction::beforeAction(useActionParam_);
    status::BaseAction::execActionSetupPre();
    status::BaseAction::execActionSetup();
}

THUMB void btl::ExecActionTask2::terminate()
{
}

THUMB void btl::ExecActionTask2::execute()
{
}

THUMB int btl::ExecActionTask2::isEnd()
{
    return true;
}

THUMB void btl::ExecActionTask3::initialize()
{
    if (useActionParam_->getCurrentTargetIndex() < 1) {
        execute_ = true;
    }
    else {
        execute_ = false;
        return;
    }
    ExecActionTask2::initialize();
}

THUMB void btl::ExecActionTask3::terminate()
{
}

THUMB void btl::ExecActionTask3::execute()
{
}

THUMB int btl::ExecActionTask3::isEnd()
{
    return true;
}
