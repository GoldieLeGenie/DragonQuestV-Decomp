#pragma ipa file
#include "main/dss/DssVectorDefault.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkArchive.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/Global.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "nitro/g3.hpp"

static const VecFx32 s_playerCameraUp = { 0, FX32_ONE, 0 };
static const VecFx32 s_fieldCameraTarget = { 0, 0, -FX32_ONE };
static const VecFx32 s_playerCameraTarget = { 0, 0, -FX32_ONE };
static const VecFx32 s_fieldCameraUp = { 0, FX32_ONE, 0 };

static unsigned char s_mapBuffer[0x29078];
static unsigned char s_symbolBuffer[0x9370];

// symbol textures loaded on every map (the others only on the world map)
static int s_symbolLoad[35] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1
};

inline int CWorldSymbol::getNum() const
{
    return m_ndata;
}

inline WorldSymbolData* CWorldSymbol::getData(int index)
{
    return &m_data[index];
}

inline unsigned short CWorldMap::getWorldEdgeX()
{
    return m_syn->mapx * m_syn->wldx;
}

inline unsigned short CWorldMap::getWorldEdgeY()
{
    return m_syn->mapy * m_syn->wldy;
}

THUMB fld::FieldData::FieldData()
{
}

THUMB fld::FieldData::~FieldData()
{
}

THUMB void fld::FieldData::setup(int map, int ch)
{
    frame_ = 0;
    setupBlock(map);
    setupSymbol(map);
    setKanban();
    animCounter8 = 0;
    animCounter24 = 0;
    position_.vx.value = 0;
    position_.vy.value = 0;
    if (ch != 0 && ch <= getChanum()) {
        worldData_.worldChange(ch - 1);
    }
    offset_ = 0;
    searchLeft_ = -14;
    searchRight_ = 14;
    searchTop_ = -12;
    searchBottom_ = 6;
    magmaOffsetX_ = 16;
    magmaOffsetY_ = 5;
}

THUMB void fld::FieldData::setupBlock(int map)
{
    char path8[0x80];
    char path24[0x80];
    dataObject_.setup(s_mapBuffer);
    switch (map) {
    case 0:
        dataObject_.reload("data/field/bin/field.bin", 1);
        blockData_.setup("data/field/field.tex", 1, 0);
        break;
    case 1:
        dataObject_.reload("data/field/bin/fairyA.bin", 1);
        blockData_.setup("data/field/fairyA.tex", 1, 0);
        break;
    case 2:
        dataObject_.reload("data/field/bin/fairyB.bin", 1);
        blockData_.setup("data/field/fairyB.tex", 1, 0);
        break;
    case 3:
        dataObject_.reload("data/field/bin/evil.bin", 1);
        blockData_.setup("data/field/evil.tex", 1, 0);
        break;
    }
    worldData_.setup(dataObject_.getAddr());
    symbolData_.setup(worldData_.m_sym_data);
    TextureObject* texture = (TextureObject*)blockData_.getAddr();
    texture->loadToVram(1);
    dss::memcpy(&blockTextureObject_, texture, sizeof(TextureObject));
    blockTexture_ = &blockTextureObject_;
    dss::memcpy(blockPaletteOrg_, (void*)blockTexture_->getPlttData(), blockTexture_->getPlttSize());
    if (map != 2) {
        blockData_.cleanup();
    }
    switch (map) {
    case 0:
        dss::sprintf_s(path8, sizeof(path8), "data/field/texture/field8.pack", 1);
        dss::sprintf_s(path24, sizeof(path24), "data/field/texture/field24.pack", 1);
        break;
    case 1:
        dss::sprintf_s(path8, sizeof(path8), "data/field/texture/fairyA8.pack", 1);
        dss::sprintf_s(path24, sizeof(path24), "data/field/texture/fairyA24.pack", 1);
        break;
    case 2:
        dss::sprintf_s(path8, sizeof(path8), "data/field/texture/fairyB8.pack", 1);
        dss::sprintf_s(path24, sizeof(path24), "data/field/texture/fairyB24.pack", 1);
        break;
    case 3:
        dss::sprintf_s(path8, sizeof(path8), "data/field/texture/evil8.pack", 1);
        dss::sprintf_s(path24, sizeof(path24), "data/field/texture/evil24.pack", 1);
        break;
    }
    pattern8_.setup(path8, 0, 0);
    pattern24_.setup(path24, 0, 0);
    pattern8Block_ = data_020f4f74.allocTexVram(getArchiveFileSize(pattern8_.getAddr(), 0));
    pattern24Block_ = data_020f4f74.allocTexVram(getArchiveFileSize(pattern24_.getAddr(), 0));
    nextAnimation8();
    nextAnimation24();
}

THUMB void fld::FieldData::setupSymbol(int flag)
{
    char path[0x80];
    symbolPack_.setup(s_symbolBuffer);
    dss::sprintf_s(path, sizeof(path), "data/field/symbol/symbol.pack", 1);
    symbolPack_.reload(path, 0);
    for (int i = 0; i < SYMBOL_TEXTURE_NUM; i++) {
        if (flag == 0 && s_symbolLoad[i] == 0) {
            symbolTexture_[i] = NULL;
        } else {
            symbolTexture_[i] = (TextureObject*)getArchiveFile(symbolPack_.getAddr(), i);
            symbolTexture_[i]->loadToVram(1);
        }
    }
    for (int i = 0; i < SYMBOL_MAX; i++) {
        if (i < symbolData_.m_ndata) {
            WorldSymbolData* data = &symbolData_.m_data[i];
            m_symbol[i].texture_ = symbolTexture_[data->id];
            m_symbol[i].setSize(data->w, data->h);
            m_symbol[i].unkfunc_02047ecc(0, 0, data->w, data->h);
            m_symbol[i].screens_ = 1;
            m_symbol[i].depth_ = 1;
            if (symbolTexture_[data->id] == NULL) {
                m_symbol[i].setAlpha(0);
            }
        } else {
            m_symbol[i].unkfunc_02047e88(0x100, 0xc0);
            m_symbol[i].setSize(8, 8);
            m_symbol[i].unkfunc_02047ecc(0, 0, 8, 8);
            m_symbol[i].screens_ = 1;
            m_symbol[i].texture_ = symbolTexture_[0];
            m_symbol[i].depth_ = 1;
        }
    }
    if (flag == 0) {
        ruramoon_.loadFile("data/field/symbol/rulemoon.tex", 1);
        ruramoon_.setMainScreen();
        ruramoon_.setDepth(2);
        ruramoon_.setPolygonID(0x29);
        casinoShip_.loadFile("data/field/symbol/fune.tex", 1);
        casinoShip_.setMainScreen();
        casinoShip_.setDepth(1);
        smoke_.loadFile("data/field/symbol/kazankm1.tex", 1);
        smoke_.setMainScreen();
        smoke_.setDepth(1);
        magma_.loadFile("data/field/symbol/ygn01.tex", 1);
        magma_.setMainScreen();
        magma_.setDepth(1);
        sunkenFirmament_.loadFile("data/chr/tenkujo.tex", 1);
        sunkenFirmament_.setMainScreen();
        sunkenFirmament_.setDepth(1);
        for (int i = 0; i < 3; i++) {
            smokeCounter_[i] = i * 8;
        }
        for (int i = 0; i < SYMBOL_MAX; i++) {
            if (symbolData_.m_data[i].uid == 0x66) {
                m_symbol[i].setAlpha(0x10);
            }
        }
    }
}

THUMB void fld::FieldData::reload()
{
    ((TextureObject*)blockData_.getAddr())->transferToVram(0);
    nextAnimation8();
    nextAnimation24();
    for (int i = 0; i < SYMBOL_TEXTURE_NUM; i++) {
        if (symbolTexture_[i] != NULL) {
            symbolTexture_[i]->transferToVram(0);
        }
    }
}

THUMB void fld::FieldData::cleanup(int map)
{
    data_020f4f74.freeTexVram(pattern8Block_);
    data_020f4f74.freeTexVram(pattern24Block_);
    pattern8_.cleanup();
    pattern24_.cleanup();
    for (int i = 0; i < SYMBOL_TEXTURE_NUM; i++) {
        if (map != 0 || s_symbolLoad[i] != 0) {
            symbolTexture_[i]->freeVram();
        }
    }
    symbolPack_.cleanup();
    blockTextureObject_.freeVram();
    if (map == 2) {
        blockData_.cleanup();
    }
    dataObject_.cleanup();
    if (ruramoon_.isLoaded()) {
        ruramoon_.unload();
    }
    if (smoke_.isLoaded()) {
        smoke_.unload();
    }
    if (magma_.isLoaded()) {
        magma_.unload();
    }
    if (casinoShip_.isLoaded()) {
        casinoShip_.unload();
    }
    if (sunkenFirmament_.isLoaded()) {
        sunkenFirmament_.unload();
    }
}

THUMB void fld::FieldData::setPlayerCamera()
{
    G3_Viewport(0, 0, 255, 191);
    int x = position_.vx.value / FX32_ONE;
    int y = position_.vy.value / FX32_ONE;
    func_020760b4(y << 12, (y << 12) + (192 << 12), x << 12, (x << 12) + (256 << 12), -(1024 << 12), 1024 << 12, 1024 << 12, 1, NULL);
    G3_StoreMtx(0);
    G3_MtxMode(1);
    VecFx32 camPos = { 0, 0, 0 };
    VecFx32 camUp = s_playerCameraUp;
    VecFx32 target = s_playerCameraTarget;
    func_02076118(&camPos, &camUp, &target, 1, NULL);
    G3_MaterialColorDiffAmb(0x7fff, 0x4210, 1);
    G3_MaterialColorSpecEmi(0x4210, 0, 0);
    G3_PolygonAttr(0, 0, 0xc0, 0, 31, 0);
}

THUMB void fld::FieldData::setFieldCamera()
{
    G3_Viewport(0, 0, 255, 191);
    int ofs = offset_;
    int left = -ofs;
    int top = -ofs;
    int right = ofs + 256;
    int bottom = ofs + 192;
    int x = position_.vx.value / FX32_ONE;
    int y = position_.vy.value / FX32_ONE;
    func_020760b4((y + top) << 12, (y + bottom) << 12, (x + left) << 12, (x + right) << 12, -(1024 << 12), 1024 << 12, 1024 << 12, 1, NULL);
    G3_StoreMtx(0);
    G3_MtxMode(1);
    VecFx32 camPos = { 0, 0, 0 };
    VecFx32 camUp = s_fieldCameraUp;
    VecFx32 target = s_fieldCameraTarget;
    func_02076118(&camPos, &camUp, &target, 1, NULL);
    G3_MaterialColorDiffAmb(0x7fff, 0x4210, 1);
    G3_MaterialColorSpecEmi(0x4210, 0, 0);
    G3_PolygonAttr(0, 0, 0xc0, 0, 31, 0);
}

THUMB void fld::FieldData::drawBlock()
{
    unsigned short Edgex = worldData_.getWorldEdgeX();
    unsigned short Edgey = worldData_.getWorldEdgeY();
    int nx;
    int px;
    int address;
    unsigned char* uv_tbl;
    CNK_TEX* data;
    int x;
    int y;
    int ny;
    int num;
    unsigned short no;
    G3_PushMtx();
    blockTexture_->applyTexImageParam();
    blockTexture_->applyPlttBase();
    x = baseBlock_.vx - 4;
    y = baseBlock_.vy - 4;
    address = 0;
    do {
        do {
            nx = x;
            ny = y;
            px = x << 4;
            if (x >= Edgex) {
                nx = x - Edgex;
            } else if (x < 0) {
                nx = x + Edgex;
            }
            if (y >= Edgey) {
                ny -= Edgey;
            } else if (y < 0) {
                ny += Edgey;
            }
            num = worldData_.getWorldNo(nx, ny);
            data = &worldData_.m_tex[num];
            uv_tbl = worldData_.getUV(nx, ny);
            if (data->aflag == 0) {
                address = blockTexture_->getTexAddr();
                no = data->no;
            } else {
                if (data->aflag == 8) {
                    address = data_020f4f74.getTexVramAddr(pattern8Block_);
                } else if (data->aflag == 24) {
                    address = data_020f4f74.getTexVramAddr(pattern24Block_);
                }
                no = data->ano;
            }
            G3_TexImageParam(blockTexture_->unk_20, GX_TEXGEN_TEXCOORD, blockTexture_->unk_24, blockTexture_->unk_28, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, address);
            G3_PolygonAttr(0, 0, 0xc0, 0, 31, 0);
            draw2DField(px, y << 4, (no & 0xf) * 16, (no / 16) * 16, uv_tbl);
            x++;
        } while (x - baseBlock_.vx <= 20);
        y++;
        x = baseBlock_.vx - 4;
    } while (y - baseBlock_.vy <= 16);
    G3_PopMtx(1);
}

THUMB void fld::FieldData::draw2DField(int x, int y, int u, int v, unsigned char* uv)
{
    G3_Identity();
    G3_Translate(ofsBlock_.vx.value + ((short)x << 12), ofsBlock_.vy.value + ((short)y << 12), -(1024 << 12));
    G3_Scale(16 << 12, 16 << 12, FX32_ONE);
    G3_Begin(1);
    G3_TexCoord((u + uv[0]) << 12, (v + uv[1]) << 12);
    G3_Vtx(0, 0, 0);
    G3_TexCoord((u + uv[2]) << 12, (v + uv[3]) << 12);
    G3_Vtx(0, 0x1000, 0);
    G3_TexCoord((u + uv[4]) << 12, (v + uv[5]) << 12);
    G3_Vtx(0x1000, 0x1000, 0);
    G3_TexCoord((u + uv[6]) << 12, (v + uv[7]) << 12);
    G3_Vtx(0x1000, 0, 0);
    G3_End();
}

THUMB void fld::FieldData::drawRuramonn()
{
    if (ruramoon_.isLoaded() && status::g_StageInfo.getTimeZone() == 4 && !g_AreaFlag.check(0xc7) && g_AreaFlag.check(0xc6)) {
        ruramoon_.draw();
    }
}

THUMB void fld::FieldData::drawRuramoon(dss::Fix32 x, dss::Fix32 y)
{
    if (ruramoon_.isLoaded() && status::g_StageInfo.getTimeZone() == 4 && !g_AreaFlag.check(0xc7) && g_AreaFlag.check(0xc6) && pause_ == 0) {
        unsigned int fcount = frame_;
        unsigned char alpha;
        if (fcount % 0xf8 < 0x7c) {
            alpha = (fcount % 0x7c) / 4;
        } else {
            alpha = 0x1f - (fcount % 0x7c) / 4;
        }
        ruramoon_.setAlpha(alpha);
        ruramoon_.setPositionFix32(x, y);
    }
}

THUMB void fld::FieldData::drawSmoke(dss::Fix32 x, dss::Fix32 y)
{
    const int step = 2;
    const int ofs = 0xc;
    const int scale = 0x14;
    const int count = 0x18;
    int i;
    int r2;
    int j;
    int rand;
    int rest;
    int size;
    int w;
    if (smoke_.isLoaded() && pause_ == 0) {
        rand = UnkDssRand::rand(1);
        if (((frame_ + 1) & 3) == 0) {
            for (j = 0; j < 3; j++) {
                smokeCounter_[j] += step;
                smokeCounter_[j] %= count;
            }
        }
        int* counter = smokeCounter_;
        for (i = 0; i < 3; i++) {
            r2 = rand * 2;
            rest = count - *counter;
            size = *counter * scale / count;
            smoke_.setDepth(rest * 4 / count);
            w = r2;
            w += size;
            w += ofs;
            smoke_.setSize(w, w);
            smoke_.setPosition(x.value / FX32_ONE + magmaOffsetX_ - (r2 + size + ofs) / 2 - rand, y.value / FX32_ONE + magmaOffsetY_ - *counter - rand);
            smoke_.setAlpha((unsigned char)(rest * 31 / count));
            smoke_.setPolygonID(i + 0x28);
            smoke_.draw();
            counter++;
        }
    }
}

THUMB void fld::FieldData::drawMagma(dss::Fix32 x, dss::Fix32 y)
{
    const int ofsX = 0xc000;
    const int ofsY = 0x2000;
    magma_.setPositionFix32(x + ofsX, y + ofsY);
    magma_.draw();
}

THUMB void fld::FieldData::drawCasinoShip(dss::Fix32 x, dss::Fix32 y)
{
    if (casinoShip_.isLoaded()) {
        casinoShip_.setPositionFix32(x, y);
        casinoShip_.draw();
    }
}

THUMB void fld::FieldData::drawSunkenFirmament()
{
    const int x = 0xdea;
    const int y = 0x73a;
    const int margin = 0x1000;
    const int ctrl_id = 0x1f04;
    if (status::g_Story.isVehicleEnable(3) == false && sunkenFirmament_.isLoaded()) {
        sunkenFirmament_.setPosition(x - 0x20, y - 0x34);
        sunkenFirmament_.setAlpha(0x10);
        sunkenFirmament_.draw();
    }
}

THUMB void fld::FieldData::drawSymbol()
{
    drawSunkenFirmament();
    for (int i = 0; i < symbolData_.m_ndata; i++) {
        WorldSymbolData* data = &symbolData_.m_data[i];
        int x = data->x - data->w / 2;
        int y = data->y - data->h;
        calcDrawPosition(x, y);
        int margin = offset_ + 0x40;
        if (x >= position_.vx.value / FX32_ONE - margin && x < offset_ + (position_.vx.value / FX32_ONE + 0x100) &&
            y >= position_.vy.value / FX32_ONE - margin && y < offset_ + (position_.vy.value / FX32_ONE + 0xc0)) {
            dss::Fix32 fx;
            dss::Fix32 fy;
            fx.value = ofsBlock_.vx.value + (x << 12);
            fy.value = ofsBlock_.vy.value + (y << 12);
            if (data->uid == 0x62) {
                drawRuramoon(fx, fy);
            } else {
                if (data->uid == 0x68) {
                    drawSmoke(fx, fy);
                }
                if (data->uid == 0x3d) {
                    drawMagma(fx, fy);
                }
                if (data->uid == 0x67) {
                    drawCasinoShip(fx, fy);
                }
                if (data->uid == 0x1e) {
                    if (!g_AreaFlag.check(0xde)) {
                        fx.value -= 0x5000;
                        m_symbol[i].setPositionFix32(fx, fy);
                        m_symbol[i].setSize(data->w * 3 / 2 + 1, data->h);
                        m_symbol[i].draw();
                    }
                } else if (data->uid == 0x1f) {
                    if (g_AreaFlag.check(0xde)) {
                        fx.value -= 0x5000;
                        m_symbol[i].setPositionFix32(fx, fy);
                        m_symbol[i].setSize(data->w * 3 / 2 + 1, data->h);
                        m_symbol[i].draw();
                    }
                } else {
                    m_symbol[i].setPositionFix32(fx, fy);
                    m_symbol[i].draw();
                }
            }
        }
    }
}

THUMB void fld::FieldData::nextAnimation8()
{
    void* data = getArchiveFile(pattern8_.getAddr(), animCounter8);
    if (data != NULL) {
        data_020f4f74.transferToVram(0, data, data_020f4f74.getTexVramAddr(pattern8Block_), data_020f4f74.getTexVramSize(pattern8Block_), 0);
    }
    animCounter8++;
    if (animCounter8 >= ANIM_PATTERN8) {
        animCounter8 = 0;
    }
}

THUMB void fld::FieldData::nextAnimation24()
{
    void* data = getArchiveFile(pattern24_.getAddr(), animCounter24);
    if (data != NULL) {
        data_020f4f74.transferToVram(0, data, data_020f4f74.getTexVramAddr(pattern24Block_), data_020f4f74.getTexVramSize(pattern24Block_), 0);
    }
    animCounter24++;
    if (animCounter24 >= ANIM_PATTERN24) {
        animCounter24 = 0;
    }
}

THUMB void fld::FieldData::draw()
{
    if (getDisplayFrame() & 1) {
        setFieldCamera();
        drawSymbol();
        drawBlock();
        if (pause_ == 0) {
            if ((frame_ & 0xf) == 0) {
                nextAnimation8();
            }
            if (((frame_ + 1) & 0xf) == 0) {
                nextAnimation24();
            }
            frame_++;
        }
    }
}

THUMB void fld::FieldData::setPosition(dss::Fix32Vector3& pos)
{
    position_ = pos;
    baseBlock_.vx = position_.vx.value / 16 / FX32_ONE;
    baseBlock_.vy = position_.vy.value / 16 / FX32_ONE;
    ofsBlock_.vx.value = position_.vx.value % FX32_ONE;
    ofsBlock_.vy.value = position_.vy.value % FX32_ONE;
}

THUMB bool fld::FieldData::isEnable(int x, int y)
{
    int attr = worldData_.getAttr(x, y);
    if (attr == WMAP_ATTR_UMI) {
        return false;
    }
    if (attr == WMAP_ATTR_YAMA2) {
        return false;
    }
    if (attr == WMAP_ATTR_ASAS) {
        return false;
    }
    if (attr == WMAP_ATTR_GA) {
        return false;
    }
    if (attr == WMAP_ATTR_WGA) {
        return false;
    }
    if (attr == WMAP_ATTR_TAKI) {
        return false;
    }
    if (attr == WMAP_ATTR_KAIG) {
        unsigned short num = worldData_.getWorldNo(x, y);
        CNK_TEX* data = &worldData_.m_tex[num];
        if (data->aflag != 0) {
            num = data->ano;
        }
        switch (g_Global.getFieldType()) {
        case 3:
            if (num < 0x24) {
                return true;
            }
            return false;
        case 1:
        case 2:
            if (num < 0x23) {
                return true;
            }
            return false;
        }
        if (num < 3) {
            return false;
        }
        if (num < 0x19) {
            return true;
        }
        return false;
    }
    for (int i = 0; i < kanbanCount_; i++) {
        if (x == kanbanPos_[i].vx / 16 && y == (kanbanPos_[i].vy - 16) / 16) {
            return false;
        }
    }
    return true;
}

THUMB int fld::FieldData::getAttr(int x, int y)
{
    int attr = worldData_.getAttr(x, y);
    if (attr == WMAP_ATTR_KAIG) {
        unsigned short num = worldData_.getWorldNo(x, y);
        CNK_TEX* data = &worldData_.m_tex[num];
        if (data->aflag != 0) {
            num = data->ano;
        }
        switch (g_Global.getFieldType()) {
        case 3:
            if (num < 0x24) {
                return WMAP_ATTR_KAIG;
            }
            return WMAP_ATTR_YAMA2;
        case 1:
        case 2:
            if (num < 0x23) {
                return WMAP_ATTR_KAIG;
            }
            return WMAP_ATTR_YAMA2;
        }
        if (num < 3) {
            return WMAP_ATTR_ASAS;
        }
        if (num < 0x19) {
            return WMAP_ATTR_KAIG;
        }
        return WMAP_ATTR_YAMA2;
    }
    return attr;
}

THUMB dss::Fix32Vector3 fld::FieldData::getSymbolPosition(int index)
{
    dss::Fix32Vector3 pos;
    for (int i = 0; i < symbolData_.getNum(); i++) {
        WorldSymbolData* data = &symbolData_.m_data[i];
        if (data->uid == (index & 0xfff)) {
            pos.vx.value = data->x << 12;
            pos.vy.value = data->y << 12;
            pos.vz.value = 0;
            return pos;
        }
    }
    return pos;
}

THUMB int fld::FieldData::isSymbolNearArea(dss::Fix32Vector3& pos, int w, int h)
{
    int vxValue = pos.vx.value / FX32_ONE;
    int vyValue = pos.vy.value / FX32_ONE;
    for (int i = 0; i < symbolData_.m_ndata; i++) {
        WorldSymbolData* data = &symbolData_.m_data[i];
        int x = vxValue - data->x;
        if (x >= searchLeft_ - w && x <= searchRight_ + w) {
            int y = vyValue - data->y;
            if (y >= searchTop_ - h && y <= searchBottom_ + h) {
                if (!cmn::g_extraMapLink.checkEraseSymbolNo(data->uid)) {
                    return data->uid;
                }
            }
        }
    }
    return -1;
}

THUMB int fld::FieldData::isNearSymbol(dss::Fix32Vector3& pos, int type)
{
    for (int i = 0; i < symbolData_.m_ndata; i++) {
        WorldSymbolData* data = &symbolData_.m_data[i];
        if (data->id == type) {
            int x = pos.vx.value / FX32_ONE - data->x;
            if (x >= searchLeft_ && x <= searchRight_) {
                int y = pos.vy.value / FX32_ONE - data->y;
                if (y >= searchTop_ && y <= searchBottom_) {
                    if (!cmn::g_extraMapLink.checkEraseSymbolNo(data->uid)) {
                        return data->uid;
                    }
                }
            }
        }
    }
    return -1;
}

THUMB bool fld::FieldData::isSymbolAttachByUid(int uid, dss::Fix32Vector3& pos)
{
    for (int i = 0; i < symbolData_.m_ndata; i++) {
        WorldSymbolData* data = &symbolData_.m_data[i];
        if (data->uid == uid) {
            int x = pos.vx.value / FX32_ONE - data->x;
            if (x >= searchLeft_ && x <= searchRight_) {
                int y = pos.vy.value / FX32_ONE - data->y;
                if (y >= searchTop_ && y <= searchBottom_) {
                    if (!cmn::g_extraMapLink.checkEraseSymbolNo(data->uid)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

THUMB int fld::FieldData::getSearchSymbolAttach(dss::Fix32Vector3& pos, int* id)
{
    for (int i = 0; i < symbolData_.m_ndata; i++) {
        WorldSymbolData* data = &symbolData_.m_data[i];
        int x = pos.vx.value / FX32_ONE - data->x;
        if (x >= searchLeft_ && x <= searchRight_) {
            int y = pos.vy.value / FX32_ONE - data->y;
            if (y >= searchTop_ && y <= searchBottom_) {
                if (!cmn::g_extraMapLink.checkEraseSymbolNo(data->uid)) {
                    if (id != NULL) {
                        *id = data->id;
                    }
                    return data->uid;
                }
            }
        }
    }
    return -1;
}

THUMB bool fld::FieldData::isCollSymbol(int x, int y)
{
    for (int i = 0; i < symbolData_.m_ndata; i++) {
        WorldSymbolData* data = &symbolData_.m_data[i];
        if (data->id == 0x21 && data->x / 16 == x && y == (data->y - data->h) / 16 && !cmn::g_extraMapLink.checkEraseSymbolNo(data->uid)) {
            return true;
        }
    }
    return false;
}

THUMB void fld::FieldData::setPaletteRate(int flag, dss::Fix32Vector3& rate)
{
    dss::memcpy(blockPalette_, blockPaletteOrg_, blockTexture_->getPlttSize());
    setPaletteRgbRate(3, rate);
    applyPaletteRgbRate(blockPalette_, blockTexture_->getPlttSize(), rate);
    data_020f4f74.transferToVram(1, blockPalette_, blockTexture_->getPlttAddr(), blockTexture_->getPlttSize(), 0);
    for (int i = 0; i < SYMBOL_TEXTURE_NUM; i++) {
        if (flag != 0 || s_symbolLoad[i] != 0) {
            MI_CpuCopyU8((void*)symbolTexture_[i]->getPlttData(), symbolPalette_[i], symbolTexture_[i]->getPlttSize());
            setPaletteRgbRate(3, rate);
            applyPaletteRgbRate(symbolPalette_[i], symbolTexture_[i]->getPlttSize(), rate);
            data_020f4f74.transferToVram(1, symbolPalette_[i], symbolTexture_[i]->getPlttAddr(), symbolTexture_[i]->getPlttSize(), 0);
        }
    }
}

THUMB int fld::FieldData::getChanum()
{
    return worldData_.m_chanum;
}

THUMB void fld::FieldData::calcDrawPosition(int& x, int& y)
{
    dss::Fix32Vector3 pos = position_;
    int offset = offset_ + 0x20;
    int px = x;
    int py = y;
    if (px < offset + 0x100 && pos.vx.value / FX32_ONE > 0xf00 - offset) {
        px += 0x1000;
    }
    if (px > 0xf00 - offset && pos.vx.value / FX32_ONE < offset + 0x100) {
        px -= 0x1000;
    }
    if (py < offset + 0xc0 && pos.vy.value / FX32_ONE > 0xf40 - offset) {
        py += 0x1000;
    }
    if (py > 0xf40 - offset && pos.vy.value / FX32_ONE < offset + 0xc0) {
        py -= 0x1000;
    }
    x = px;
    y = py;
}

THUMB void fld::FieldData::setKanban()
{
    kanbanCount_ = 0;
    int maxCount = symbolData_.m_ndata;
    for (int i = 0; i < maxCount; i++) {
        WorldSymbolData* data = &symbolData_.m_data[i];
        if (data->id == 9) {
            kanbanPos_[kanbanCount_].vx = data->x;
            kanbanPos_[kanbanCount_].vy = data->y;
            kanbanId_[kanbanCount_] = data->uid;
            kanbanCount_++;
        }
    }
}

THUMB int fld::FieldData::searchKanban(int x, int y, dss::Vector2<dss::Fix32>* pos)
{
    x = x / FX32_ONE / 16;
    y = y / FX32_ONE / 16;
    for (int i = 0; i < kanbanCount_; i++) {
        if (x == kanbanPos_[i].vx / 16 && y == (kanbanPos_[i].vy - 16) / 16) {
            if (pos != NULL) {
                pos->vx = (kanbanPos_[i].vx << 12) + 0x8000;
                pos->vy = ((kanbanPos_[i].vy - 16) << 12) + 0x8000;
            }
            return kanbanId_[i];
        }
    }
    return -1;
}

THUMB void fld::FieldData::setDispSymbol(int id, int disp)
{
    for (int i = 0; i < SYMBOL_MAX; i++) {
        int uid = symbolData_.m_data[i].uid;
        if (uid == id) {
            m_symbol[i].enable_ = disp;
        }
    }
}

