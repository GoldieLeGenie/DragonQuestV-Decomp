#include "main/btl/EncountCountDown.hpp"
#include "main/dss/UnkRandom.hpp"

int btl::CorrectValue[31] = {
    -1193, -982, -844, -737, -647, -568, -497, -432, -371, -313, -258, -204, -152, -101, -51, -1,
    50, 100, 151, 203, 257, 312, 370, 431, 496, 567, 646, 736, 843, 981, 1192,
};

int btl::LandSubtractValue[9] = {
    153, 576, 960, 960, 691, 384, 384, 460, 353,
};

int btl::TileSubtractValue[8] = {
    64, 128, 192, 256, 320, 384, 448, 512,
};

THUMB btl::EncountCountDown::EncountCountDown()
{
    tileIdRate_ = 0;
}

THUMB btl::EncountCountDown::~EncountCountDown()
{
}

THUMB void btl::EncountCountDown::setup()
{
    counter_ = STANDARD_VALUE;
    int rand = UnkDssRand::rand(31);
    counter_ += CorrectValue[rand];
    subtractValue_ = 0;
}

THUMB void btl::EncountCountDown::exec()
{
    counter_ -= subtractValue_;
}

THUMB void btl::EncountCountDown::setTileIdRate(int rate)
{
    tileIdRate_ = rate;
    setLandSubtranctValeu();
}

THUMB void btl::EncountCountDown::setLandType(int landType)
{
    fix_ = 0;
    switch (landType) {
    case 0:
        landType_ = 0;
        break;
    case 1:
        landType_ = 1;
        break;
    case 2:
        landType_ = 2;
        break;
    case 3:
        landType_ = 3;
        break;
    case 4:
        landType_ = 4;
        break;
    case 5:
        landType_ = 5;
        break;
    case 6:
        landType_ = 6;
        break;
    case 7:
        landType_ = 7;
        break;
    case 8:
        fix_ = 1;
        landType_ = 8;
        break;
    }
    setLandSubtranctValeu();
}

THUMB void btl::EncountCountDown::setLandSubtranctValeu()
{
    subtractValue_ = (LandSubtractValue[landType_] * TileSubtractValue[tileIdRate_]) / 256;
    if (fix_) {
        subtractValue_ = (subtractValue_ * 3) / 2;
    }
}
