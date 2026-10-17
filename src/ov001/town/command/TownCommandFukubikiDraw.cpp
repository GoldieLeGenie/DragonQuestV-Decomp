#include "ov001/town/command/TownCommandFukubikiDraw.hpp"
#include "ov001/town/TownFukubikiDraw.hpp"
#include "ov001/town/shop/TownCurseSpotLight.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/town/TownCommandEncount.hpp"

#pragma thumb on

int twn::TownCommandFukubikiDraw::isExec()
{
    if (!TownFukubikiDraw::getSingleton().isEnd_ || !TownCurseSpotLight::getSingleton().isEnd_) {
        BillboardCharacter::setAllCharaAnim(false);
        return true;
    }
    return false;
}

void twn::TownCommandFukubikiDraw::exec()
{
    CommandObjectDefineTownSystem::setFukubiki();
}

int twn::TownCommandFukubikiDraw::isEnd()
{
    return true;
}
