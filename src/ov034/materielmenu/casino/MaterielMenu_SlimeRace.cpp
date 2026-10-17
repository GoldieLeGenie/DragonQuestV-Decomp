#include "ov034/materielmenu/casino/MaterielMenu_SlimeRace.hpp"
#include "ov034/materielmenu/casino/MaterielMenu_RaceOdds.hpp"
#include "ov003/slimerace/SlimeRace.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/menu/RaceData.hpp"
#include "main/status/MenuStatus.hpp"

inline unsigned char RaceData::getPaddock()
{
    return slimeNum_;
}

inline void RaceData::setBetCoin(unsigned int coin)
{
    betCoin_ = coin;
}

inline void RaceData::setResult(unsigned char result)
{
    result_ = result;
}

inline void RaceData::setWinningNum(unsigned short num)
{
    winningNum_ = num;
}

inline void RaceData::setOdds(unsigned short odds)
{
    odds_ = odds;
}

inline void status::MenuStatus::setBooking(menu::BOOKING_FLAG flag)
{
    bookingFlag_ = flag;
}

THUMB void MaterielMenu_SlimeRace::menuSetup()
{
    g_RaceData.setBetCoin(0);
    g_RaceData.setResult(0xff);
    g_RaceData.slimeResult_ = 0xff;
    g_RaceData.setWinningNum(0);
    gMaterielMenu_RaceOdds.open();
}

THUMB void MaterielMenu_SlimeRace::menuExecute()
{
}

THUMB void MaterielMenu_SlimeRace::menuDraw()
{
}

THUMB void MaterielMenu_SlimeRace::menuUpdate()
{
    if (gMaterielMenu_RaceOdds.mode_ == MaterielMenu_RaceOdds::MODE_START) {
        if (unkfunc_02130860() == 5) {
            dataUpdate();
        }
    }
    if (gMaterielMenu_RaceOdds.mode_ == MaterielMenu_RaceOdds::MODE_ESCAPE) {
        unkfunc_0213086c(7);
        status::g_Menu.setBooking(menu::BOOKING_SLIMERACE);
        gMaterielMenu_RaceOdds.close();
        close();
        stat_ = MENUBASE_STAT_OK;
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
    }
}

THUMB void MaterielMenu_SlimeRace::dataUpdate()
{
    ST_ARG_SL_RACE arg;
    if (SlimeRaceResult(&arg)) {
        int winner = arg.rank[0] + 1;
        int second = arg.rank[1] + 1;
        if (g_RaceData.getPaddock() == 6) {
            g_RaceData.slimeResult_ = 0;
            if (winner == 6) {
                g_RaceData.slimeResult_ = 1;
            }
            if (second == 6) {
                g_RaceData.slimeResult_ = 2;
            }
        }
        if (winner > second) {
            int tmp = winner;
            winner = second;
            second = tmp;
        }
        int winPos = second - 1 - winner;
        for (int i = 1; i < winner; i++) {
            winPos += g_RaceData.getPaddock() - i;
        }
        g_RaceData.setWinningNum(winPos);
        ODDS_DATA* data = &g_RaceData.oddsData_[winPos];
        int coin = data->coin;
        int odds = data->odds;
        if (coin > 0) {
            g_RaceData.setResult(1);
        } else {
            g_RaceData.setResult(0);
        }
        g_RaceData.setBetCoin(coin);
        g_RaceData.setOdds(odds);
        gMaterielMenu_RaceOdds.mode_ = MaterielMenu_RaceOdds::MODE_RESULT;
        redraw_ = 1;
    }
}
