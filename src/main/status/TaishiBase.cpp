#include "main/status/TaishiBase.hpp"
#include "main/dss/DssUtils.hpp"

THUMB status::TaishiBase::TaishiBase()
{
}

THUMB status::TaishiBase::~TaishiBase()
{
}

THUMB void status::TaishiBase::clearTaishi()
{
    isTaishi_ = 0;
    uniqueId_ = 0;
    price_ = 0;
    objectId_ = 0;
    production_ = 0;
    for (int i = 0; i < 28; i++) {
        taishiName_[i] = 0;
    }
    for (int i = 0; i < 26; i++) {
        producer_[i] = 0;
    }
    for (int i = 0; i < 136; i++) {
        message_[i] = 0;
    }
}

THUMB void status::TaishiBase::setTaishiName(char* name)
{
    for (int i = 0; i < 28; i++) {
        taishiName_[i] = 0;
    }
    dss::strcpy_s(taishiName_, 28, name);
}

THUMB void status::TaishiBase::setTaishiProducer(char* producer)
{
    for (int i = 0; i < 26; i++) {
        producer_[i] = 0;
    }
    dss::strcpy_s(producer_, 26, producer);
}

THUMB void status::TaishiBase::setTaishiMessage(char* message)
{
    for (int i = 0; i < 136; i++) {
        message_[i] = 0;
    }
    dss::strcpy_s(message_, 136, message);
}
