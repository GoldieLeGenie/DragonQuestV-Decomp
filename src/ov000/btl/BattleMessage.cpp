#include "ov000/btl/BattleMessage.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionParam.hpp"

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline bool status::UseActionParam::isTargetResult(int index) { return targetResult_[index]; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline status::UseActionMessage& status::UseActionParam::getUseActionMessage(int index) { return message_[index]; }
inline int status::HaveStatusInfo::getUseActionEffectValue() { return effectValue_; }

THUMB void btl::BattleMessage::setMessage(int mes0, int mes1, int mes2, int mes3)
{
    if ((mes0 | mes1 | mes2 | mes3) == 0) {
        return;
    }
    MenuAPI::openBattleMessage();
    if (mes0 != 0) {
        MenuAPI::addMessageSerial(mes0);
    }
    if (mes1 != 0) {
        MenuAPI::addMessageSerial(mes1);
    }
    if (mes2 != 0) {
        MenuAPI::addMessageSerial(mes2);
    }
    if (mes3 != 0) {
        MenuAPI::addMessageSerial(mes3);
    }
    BattleAutoFeed::setCursor();
    BattleAutoFeed::setMessage();
}

THUMB void btl::BattleMessage::setMessageNoSeqNum(int mes0, int mes1, int mes2, int mes3, int mes4, int mes5, int mes6, int mes7)
{
    if ((mes0 | mes1 | mes2 | mes3 | mes4 | mes5 | mes6 | mes7) == 0) {
        return;
    }
    MenuAPI::openBattleMessage();
    if (mes0 != 0) {
        MenuAPI::addMessage(mes0);
    }
    if (mes1 != 0) {
        MenuAPI::addMessage(mes1);
    }
    if (mes2 != 0) {
        MenuAPI::addMessage(mes2);
    }
    if (mes3 != 0) {
        MenuAPI::addMessage(mes3);
    }
    if (mes4 != 0) {
        MenuAPI::addMessage(mes4);
    }
    if (mes5 != 0) {
        MenuAPI::addMessage(mes5);
    }
    if (mes6 != 0) {
        MenuAPI::addMessage(mes6);
    }
    if (mes7 != 0) {
        MenuAPI::addMessage(mes7);
    }
    BattleAutoFeed::setCursor();
    BattleAutoFeed::setMessage();
}

THUMB void btl::BattleMessage::setMessageInTown(int mes0, int mes1, int mes2, int mes3)
{
    MenuAPI::openCommonMessage();
    if (mes0 != 0) {
        MenuAPI::addMessageSerial(mes0);
    }
    if (mes1 != 0) {
        MenuAPI::addMessageSerial(mes1);
    }
    if (mes2 != 0) {
        MenuAPI::addMessageSerial(mes2);
    }
    if (mes3 != 0) {
        MenuAPI::addMessageSerial(mes3);
    }
    BattleAutoFeed::setCursor();
    BattleAutoFeed::setMessage();
}

THUMB bool btl::BattleMessage::setBeforeMessage(status::UseActionParam& useActionParam)
{
    int message[4] = { 0, 0, 0, 0 };
    status::UseActionMessage* msg = &useActionParam.getUseActionMessage(0);
    message[0] = msg->beforeMessage_[0];
    message[1] = msg->beforeMessage_[1];
    if (message[0] + message[1] == 0) {
        return false;
    }
    setMessage(message[0], message[1], 0, 0);
    return true;
}

THUMB bool btl::BattleMessage::setExecMessage(status::UseActionParam& useActionParam)
{
    int message[4] = { 0, 0, 0, 0 };
    status::UseActionMessage* msg = &useActionParam.getUseActionMessage(0);
    message[0] = msg->execMessage_[0];
    message[1] = msg->execMessage_[1];
    message[2] = msg->execMessage_[2];
    message[3] = msg->execMessage_[3];
    if (message[0] + message[1] + message[2] + message[3] == 0) {
        return false;
    }
    setMessage(message[0], message[1], message[2], message[3]);
    return true;
}

THUMB bool btl::BattleMessage::setSpecialMessage(status::UseActionParam& useActionParam, int currentTarget)
{
    int message[4] = { 0, 0, 0, 0 };
    message[0] = useActionParam.getUseActionMessage(currentTarget).spclMessage_[0];
    message[1] = useActionParam.getUseActionMessage(currentTarget).spclMessage_[1];
    if (message[0] + message[1] + message[2] + message[3] == 0) {
        return false;
    }
    setMessage(message[0], message[1], message[2], message[3]);
    return true;
}

THUMB bool btl::BattleMessage::setResultMessage(status::UseActionParam& useActionParam, int currentTarget)
{
    int message[3] = { 0, 0, 0 };
    message[0] = useActionParam.getUseActionMessage(currentTarget).resultMessage_[0];
    message[1] = useActionParam.getUseActionMessage(currentTarget).resultMessage_[1];
    if (message[0] + message[1] == 0) {
        return false;
    }
    setMessage(message[0], message[1], 0, 0);
    return true;
}

THUMB bool btl::BattleMessage::setAfterMessage(status::UseActionParam& useActionParam, int currentTarget)
{
    int message[4] = { 0, 0, 0, 0 };
    message[0] = useActionParam.getUseActionMessage(currentTarget).addMessage_[0];
    message[1] = useActionParam.getUseActionMessage(currentTarget).addMessage_[1];
    if (message[0] + message[1] == 0) {
        return false;
    }
    setMessage(message[0], message[1], 0, 0);
    return true;
}

THUMB void btl::BattleMessage::setShakeMessage(status::UseActionParam& useActionParam, int currentTarget)
{
    status::CharacterStatus* target = useActionParam.getTargetCharacterStatus(currentTarget);
    if (target == NULL) {
        return;
    }
    if (!useActionParam.isTargetResult(currentTarget)) {
        return;
    }
    if (status::UseAction::getDamageType(useActionParam.getActionIndex()) != status::UseAction::DamageTypeDamage) {
        return;
    }
    if (target->getCharacterType() != PLAYER) {
        return;
    }
    if (target->getHaveStatusInfo().getUseActionEffectValue() != 0) {
        MenuAPI::shakeMessage();
    }
}

THUMB void btl::BattleMessage::openMessage()
{
    MenuAPI::openBattleMessage();
}

THUMB void btl::BattleMessage::openEncountMessage()
{
    MenuAPI::openEncountMessage();
}

THUMB void btl::BattleMessage::addEncountMessage(int message)
{
    MenuAPI::catMessage(message);
    BattleAutoFeed::setMessage();
}
