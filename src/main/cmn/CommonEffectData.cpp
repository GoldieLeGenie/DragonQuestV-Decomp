#pragma ipa file
#include "main/cmn/CommonEffectData.hpp"
#include "main/dss/UnkArchive.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/data/FileLoader.hpp"

inline UnkFileDataObject::UnkFileDataObject()
{
}

inline UnkFileDataObject::~UnkFileDataObject()
{
}

THUMB cmn::CommonEffectData::CommonEffectData()
{
}

THUMB cmn::CommonEffectData::~CommonEffectData()
{
}

THUMB void cmn::CommonEffectData::setup(int index)
{
    char path[0x80];
    if (index < 10000) {
        dss::sprintf_s(path, 0x80, "data/effect/effect%03d.lz", index);
    } else {
        dss::sprintf_s(path, 0x80, "data/effect/effect%03db.lz", index - 10000);
    }
    effectData_.setup(path, 1, 1);
    m_effect_type = *(int*)getArchiveFile(effectData_.getAddr(), 0);
    if (m_effect_type == 0) {
        setupTexture();
    }
}

THUMB void cmn::CommonEffectData::setupTexture()
{
    ((TextureObject*)(getTextureData()))->unkfunc_02049e9c(0);
}

THUMB void cmn::CommonEffectData::cleanup()
{
    if (isEnable()) {
        if (m_effect_type == 0) {
            cleanupTexture();
        }
        effectData_.cleanup();
    }
}

THUMB void cmn::CommonEffectData::cleanupTexture()
{
    ((TextureObject*)(getTextureData()))->unkfunc_02049f90();
}

THUMB void* cmn::CommonEffectData::getTextureData()
{
    return getArchiveFile(effectData_.getAddr(), 1);
}

THUMB void* cmn::CommonEffectData::getAnimationData()
{
    return getArchiveFile(effectData_.getAddr(), 2);
}

THUMB void* cmn::CommonEffectData::getPaletteAnimData()
{
    if (!isPamEnable()) {
        return 0;
    }
    return getArchiveFile(effectData_.getAddr(), 3);
}

THUMB int cmn::CommonEffectData::isPamEnable()
{
    return unkfunc_0204c860(effectData_.getAddr()) > 3;
}

THUMB void* cmn::CommonEffectData::getModelData()
{
    return getArchiveFile(effectData_.getAddr(), 1);
}

THUMB void* cmn::CommonEffectData::getAnimData(int index)
{
    if (unkfunc_0204c860(effectData_.getAddr()) > index + 2) {
        return getArchiveFile(effectData_.getAddr(), index + 2);
    }
    return 0;
}

THUMB int cmn::CommonEffectData::isEnable()
{
    return effectData_.getAddr() != 0;
}

THUMB int cmn::CommonEffectData::getEffectType()
{
    return m_effect_type;
}

THUMB int cmn::CommonEffectData::isSecondEffect(int index)
{
    char path[0x100];
    dss::sprintf_s(path, 0x80, "data/effect/effect%03db.lz", index);
    return dss::g_File.isExist(path, dss::File::Switching);
}
