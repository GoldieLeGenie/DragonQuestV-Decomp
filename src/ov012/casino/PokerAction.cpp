#include "ov012/casino/PokerAction.hpp"

inline void casino::PokerActionBase::setCardIndex(char index)
{
    index_ = index;
}

THUMB casino::PokerAction* casino::PokerAction::getSingleton()
{
    static PokerAction pokerAction;
    return &pokerAction;
}

THUMB void casino::PokerAction::initialize()
{
    cardAction_[CARD_ACTION_TABULATE] = &pokerActionTabulate_;
    cardAction_[CARD_ACTION_REVERSE] = &pokerActionReverse_;
    cardAction_[CARD_ACTION_MOVE] = &pokerActionMove_;
    cardAction_[CARD_ACTION_FADE] = &pokerActionFade_;
    setCardAction(CARD_ACTION_TABULATE);
}

THUMB void casino::PokerAction::execute()
{
    cardAction_[action_]->execute();
}

THUMB bool casino::PokerAction::isEnd()
{
    return cardAction_[action_]->isEnd();
}

THUMB void casino::PokerAction::setCardAction(CARD_ACTION action)
{
    action_ = action;
    if (action != CARD_ACTION_MAX) {
        cardAction_[action_]->setup();
    }
}

THUMB void casino::PokerAction::setCardIndex(int index)
{
    cardAction_[action_]->setCardIndex(index);
}
