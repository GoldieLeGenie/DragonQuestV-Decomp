#include "ov001/town/TownSystem.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"

#pragma thumb on

twn::TownSystemParticle::TownSystemParticle()
{
}

twn::TownSystemParticle::~TownSystemParticle()
{
}

void twn::TownSystemParticle::initialize()
{
    cmn::CommonParticleEmitter::getSingleton()->initialize();
}

void twn::TownSystemParticle::terminate()
{
    cmn::CommonParticleEmitter::getSingleton()->terminate();
}

void twn::TownSystemParticle::execute()
{
    cmn::CommonParticleEmitter::getSingleton()->execute();
}

void twn::TownSystemParticle::draw()
{
    cmn::CommonParticleEmitter::getSingleton()->draw();
}
