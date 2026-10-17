#include "ov012/casino/PokerManager.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/status/PartyStatus.hpp"
#include "ov012/casino/PokerJudgement.hpp"

inline unsigned int status::BasePartyStatus::getCasinoCoin()
{
    return casinoCoin_;
}

THUMB casino::PokerManager* casino::PokerManager::getSingleton()
{
    static PokerManager pokerManager;
    return &pokerManager;
}

THUMB void casino::PokerManager::initialize()
{
    for (int i = 0; i < 5; i++) {
        defaultNo_[i] = 0;
        chengeCard_[i] = 0;
        cardNo_[i] = 0;
        cardType_[i] = TYPE_SLIME;
        combinationCard_[i] = 0;
    }
    betCoin_ = 0;
    cardPosition_ = 0;
    winningCombination_ = 0;
    clearCard();
    clearDebugCard(-1);
    highAndLow_.initialize();
}

THUMB void casino::PokerManager::clearCard()
{
    for (int i = 0; i < 5; i++) {
        gameCard_[i].defaultNo_ = -1;
        gameCard_[i].type_ = -1;
        gameCard_[i].no_ = -1;
        changeCard_[i].defaultNo_ = -1;
        changeCard_[i].type_ = -1;
        changeCard_[i].no_ = -1;
    }
}

THUMB void casino::PokerManager::clearDebugCard(int index)
{
    if (index == -1) {
        for (int i = 0; i < 5; i++) {
            debugCard_[i].defaultNo_ = -1;
            debugCard_[i].type_ = -1;
            debugCard_[i].no_ = -1;
        }
        return;
    }
    debugCard_[index].defaultNo_ = -1;
    debugCard_[index].type_ = -1;
    debugCard_[index].no_ = -1;
}

THUMB void casino::PokerManager::dealCard(int index)
{
    char count = 0;
    char changeCard;
    if (index == -1) {
        for (int i = 0; i < 5; i++) {
            chengeCard_[i] = -1;
        }
        for (int i = 0; i < 5; i++) {
            if (debugCard_[i].defaultNo_ != -1) {
                setGameCard(gameCard_, i, debugCard_[i].defaultNo_);
                continue;
            }
            changeCard = UnkDssRand::rand(53);
            combinationCard_[i] = 0;
            while (count < i) {
                if (changeCard == gameCard_[count].defaultNo_) {
                    changeCard = UnkDssRand::rand(53);
                    count = 0;
                } else {
                    count++;
                }
            }
            setGameCard(gameCard_, i, changeCard);
            count = 0;
        }
        clearDebugCard(-1);
        return;
    }
    if (debugCard_[index].defaultNo_ != -1) {
        changeCard_[index].defaultNo_ = gameCard_[index].defaultNo_;
        setGameCard(gameCard_, index, debugCard_[index].defaultNo_);
        return;
    }
    changeCard = UnkDssRand::rand(53);
    while (count < 5) {
        if (changeCard == gameCard_[count].defaultNo_) {
            changeCard = UnkDssRand::rand(53);
            count = 0;
        } else if (changeCard_[count].defaultNo_ != -1) {
            if (changeCard == changeCard_[count].defaultNo_) {
                changeCard = UnkDssRand::rand(53);
                count = 0;
            } else {
                count++;
            }
        } else {
            count++;
        }
    }
    changeCard_[index].defaultNo_ = gameCard_[index].defaultNo_;
    setGameCard(gameCard_, index, changeCard);
}

THUMB void casino::PokerManager::setBetCoin(int bet)
{
    if (bet > status::g_Party.getCasinoCoin()) {
        betCoin_ = status::g_Party.getCasinoCoin();
    } else {
        betCoin_ = bet;
    }
}

THUMB int casino::PokerManager::judgementCombination()
{
    winningCombination_ = PokerJudgement::getSingleton()->JudgeCombination();
    if (winningCombination_ == PokerJudgement::NO_PAIRS || winningCombination_ == PokerJudgement::ONE_PAIRS) {
        return 0;
    }
    return winningCombination_;
}

THUMB int casino::PokerManager::getMultiple()
{
    static int diameter[10] = {1, 1, 2, 4, 5, 10, 20, 50, 100, 500};
    if (judgementCombination() == 0) {
        return 0;
    }
    return diameter[judgementCombination() - 2];
}

THUMB void casino::PokerManager::resetCombinationCard()
{
    for (int i = 0; i < 5; i++) {
        combinationCard_[i] = 0;
    }
}

THUMB void casino::PokerManager::startHighAndLow()
{
    highAndLow_.startHighAndLow(-1);
}

THUMB void casino::PokerManager::setAnswer(int answer)
{
    ANSWER ans = ANSWER_HIGH;
    if (answer == true) {
        ans = ANSWER_LOW;
    }
    highAndLow_.setAnswer(ans);
}

THUMB casino::DOUBLEUP_RESULT casino::PokerManager::getHighAndLowResult()
{
    return highAndLow_.getResult();
}

THUMB int casino::PokerManager::getHighAndLowCardType(int base)
{
    int type = changeCardType(highAndLow_.getSelectCardNo());
    if (base == true) {
        type = changeCardType(highAndLow_.baseCard_);
    }
    return type;
}

THUMB int casino::PokerManager::getHighAndLowCardNo(int base)
{
    int no = changeCardNo(highAndLow_.getSelectCardNo());
    if (base == true) {
        no = changeCardNo(highAndLow_.baseCard_);
    }
    return no;
}

THUMB void casino::PokerManager::setGameCard(POKER_CARD* card, int index, char defaultNo)
{
    card[index].defaultNo_ = defaultNo;
    card[index].type_ = defaultNo / 13;
    if (defaultNo == 52) {
        card[index].no_ = -1;
    } else {
        card[index].no_ = defaultNo % 13;
    }
}

THUMB int casino::PokerManager::changeCardNo(int cardNo)
{
    int no;
    if (cardNo == 52) {
        no = -1;
    } else {
        no = cardNo % 13;
    }
    return no;
}

THUMB int casino::PokerManager::changeCardType(int cardNo)
{
    return cardNo / 13;
}
