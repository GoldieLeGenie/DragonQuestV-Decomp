#include "ov005/fld/FieldSystem.hpp"

THUMB fld::FieldSystemWorldMap::FieldSystemWorldMap()
{
}

THUMB fld::FieldSystemWorldMap::~FieldSystemWorldMap()
{
}

THUMB void fld::FieldSystemWorldMap::initialize()
{
    imageMap.setup(&FieldSystem::getSingleton()->render_);
}

THUMB void fld::FieldSystemWorldMap::terminate()
{
    imageMap.cleanup();
}

THUMB void fld::FieldSystemWorldMap::execute()
{
    imageMap.execute();
}

THUMB void fld::FieldSystemWorldMap::draw()
{
    imageMap.draw();
}

THUMB void fld::FieldSystemWorldMap::openAreaMap()
{
    imageMap.open();
}

THUMB void fld::FieldSystemWorldMap::closeAreaMap()
{
    imageMap.close();
}

THUMB bool fld::FieldSystemWorldMap::isAreaMapOpen()
{
    return imageMap.isOpen();
}

THUMB bool fld::FieldSystemWorldMap::isAreaMapClose()
{
    return imageMap.isClose();
}
