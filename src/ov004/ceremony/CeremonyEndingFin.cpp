#pragma ipa file
#include "ov004/ceremony/CeremonyEndingFin.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/RenderObject.hpp"

inline DSSAObject2D::DSSAObject2D()
{
}

inline DSSAObject2D::~DSSAObject2D()
{
}

inline PaletteAnimation::~PaletteAnimation()
{
}

inline PaletteAnimationObject::PaletteAnimationObject()
{
    texture_ = 0;
}

THUMB ceremony::CeremonyEndingFin::CeremonyEndingFin()
{
}

THUMB ceremony::CeremonyEndingFin::~CeremonyEndingFin()
{
}

THUMB ceremony::CeremonyEndingFin* ceremony::CeremonyEndingFin::getSingleton()
{
    static CeremonyEndingFin m_singleton;
    return &m_singleton;
}

THUMB void ceremony::CeremonyEndingFin::initialize()
{
    dss::Fix32 scl;
    scl.value = 0x320;
    DSSAObject::setDefaultScale(scl);
    DSSAObject::setPriority(1);
    char path[128];
    dss::sprintf_s(path, sizeof(path), "data/ending/the_end/pen.tex");
    penTextureData_.setup(path, 0, 0);
    penTexture_ = (TextureObject*)penTextureData_.getAddr();
    penTexture_->loadToVram(1);
    dss::sprintf_s(path, sizeof(path), "data/ending/the_end/pen.dssa");
    penData_.setup(path, 0, 0);
    penDssa_.setup(penData_.getAddr());
    penDssa_.setTexture(penTexture_);
    penDssa_.pause(true);
    dss::Fix32Vector3 pos(0.0f, 18.0f, 0.0f);
    penDssa_.setPosition(pos);
    theSprite_[0].loadFile("data/ending/the_end/the_u.tex", 0);
    theSprite_[1].loadFile("data/ending/the_end/the_d.tex", 0);
    endSprite_[0].loadFile("data/ending/the_end/end_u.tex", 0);
    endSprite_[1].loadFile("data/ending/the_end/end_d.tex", 0);
    pamData_.setup("data/ending/the_end/end.pam", 0, 0);
    pam_.anim_.setup(pamData_.getAddr());
    m_frame = 0;
    m_pam_index = 0;
    dss::memcpy(palette_, pam_.anim_.getColor(m_pam_index), pam_.anim_.getColorCount() * 2);
    for (int i = 0; i < 2; i++) {
        theSprite_[i].setAlpha(0x1f);
        int depth = 0x3c - i;
        theSprite_[i].setPolygonID(depth);
        theSprite_[i].setMainScreen();
        theSprite_[i].setSize(0x40, 0x40);
        theSprite_[i].setTexCoords(0, 0, 0x40, 0x40);
        theSprite_[i].setPosition(0x40, 0x40);
        endSprite_[i].setAlpha(0x1f);
        endSprite_[i].setPolygonID(depth);
        endSprite_[i].setMainScreen();
        endSprite_[i].setSize(0x40, 0x40);
        endSprite_[i].setTexCoords(0, 0, 0x40, 0x40);
        endSprite_[i].setPosition(0x80, 0x40);
    }
    enable_ = 1;
    penDssa_.start(0);
}

THUMB void ceremony::CeremonyEndingFin::terminate()
{
    theSprite_[0].unload();
    theSprite_[1].unload();
    endSprite_[0].unload();
    endSprite_[1].unload();
    pamData_.cleanup();
    pam_.unkfunc_02051648();
    penTexture_->freeVram();
    penTextureData_.cleanup();
    penDssa_.cleanup();
    penData_.cleanup();
}

THUMB void ceremony::CeremonyEndingFin::execute()
{
    animTheEnd();
}

THUMB void ceremony::CeremonyEndingFin::draw()
{
    setupOrtho2D();
    for (int i = 0; i < 2; i++) {
        theSprite_[i].draw();
        endSprite_[i].draw();
    }
    if ((getDisplayFrame() & 1) && !penDssa_.isEnd()) {
        penDssa_.draw();
    }
}

THUMB void ceremony::CeremonyEndingFin::animTheEnd()
{
    if (enable_ == 0) {
        return;
    }
    penDssa_.execute();
    m_frame++;
    if (m_frame >= pam_.anim_.getWait(m_pam_index)) {
        m_frame = 0;
        m_pam_index++;
        if (m_pam_index >= pam_.anim_.getFrameCount()) {
            enable_ = 0;
            return;
        }
        dss::memcpy(palette_, pam_.anim_.getColor(m_pam_index), pam_.anim_.getColorCount() * 2);
    }
    unsigned char* data = (unsigned char*)theSprite_[0].getTextureData();
    for (int x = 0; x < 0x40; x++) {
        for (int y = 0; y < 0x40; y++) {
            if (palette_[data[x + y * 0x40]] == 0) {
                data[x + y * 0x40] = 0;
            }
        }
    }
    data = (unsigned char*)endSprite_[0].getTextureData();
    for (int x = 0; x < 0x40; x++) {
        for (int y = 0; y < 0x40; y++) {
            if (palette_[data[x + y * 0x40]] == 0) {
                data[x + y * 0x40] = 0;
            }
        }
    }
    theSprite_[0].freeVram();
    theSprite_[0].allocVram();
    theSprite_[0].transferToVram();
    endSprite_[0].freeVram();
    endSprite_[0].allocVram();
    endSprite_[0].transferToVram();
}

THUMB bool ceremony::CeremonyEndingFin::isEnd()
{
    if (enable_ == 0) {
        return true;
    }
    return false;
}
