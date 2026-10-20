#include "ov005/fld/FieldImageMap.hpp"
#include "main/data/FileLoader.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/status/GameFlag.hpp"
#include "nitro/os.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

// blocks of the map pieces replaced by the files of the story events
static const dss::Vector2<int> s_castleBlock[4] = {
    dss::Vector2<int>(11, 2), dss::Vector2<int>(12, 2), dss::Vector2<int>(11, 3), dss::Vector2<int>(12, 3)
};

static const dss::Vector2<int> s_bridgeBlock(19, 9);

static const dss::Vector2<int> s_magmaBlock[4] = {
    dss::Vector2<int>(27, 14), dss::Vector2<int>(28, 14), dss::Vector2<int>(27, 15), dss::Vector2<int>(28, 15)
};

static const dss::Vector2<int> s_suimonBlock[6] = {
    dss::Vector2<int>(1, 14), dss::Vector2<int>(2, 14), dss::Vector2<int>(1, 15),
    dss::Vector2<int>(2, 15), dss::Vector2<int>(1, 16), dss::Vector2<int>(2, 16)
};

// offset of the player marker on the large map
static int s_markerOffsetY = 2;
static int s_markerOffsetX = -2;

THUMB fld::FieldLargeMap::FieldLargeMap()
{
}

THUMB fld::FieldLargeMap::~FieldLargeMap()
{
}

THUMB void fld::FieldLargeMap::setup(Render* render)
{
    render_ = render;
    setupSprites();
}

THUMB void fld::FieldLargeMap::cleanup()
{
    unk_54.detachRender();
    unk_04.detachRender();
    unk_54.unload();
    unk_04.unload();
}

THUMB void fld::FieldLargeMap::setupSprites()
{
    char path[0x80];
    unk_04.setTexCoords(0, 0, 0x20, 0x20);
    dss::sprintf_s(path, sizeof(path), "data/field/large/largemap.tex");
    unk_54.loadFile(path, 0);
    unk_54.attachRender(render_);
    unk_54.setSubScreen();
    unk_54.setPolygonID(0x3e);
    unk_54.setDepth(0x10);
    unk_54.setAlpha(0);
    dss::sprintf_s(path, sizeof(path), "data/field/2d/point.tex");
    unk_04.loadFile(path, 0);
    unk_04.attachRender(render_);
    unk_04.setSubScreen();
    unk_04.setPolygonID(0x34);
    unk_04.setDepth(0x18);
    unk_04.setAlpha(0);
    unk_04.setEnabled(1);
    unk_04.freeVram();
    unk_54.freeVram();
    buildPlayerMap();
}

THUMB int fld::FieldLargeMap::loadEventBlock(int x, int y, void* buffer)
{
    if (g_AreaFlag.check(0x82)) {
        for (int i = 0; i < 4; i++) {
            if (x == s_castleBlock[i].vx && y == s_castleBlock[i].vy) {
                dss::g_File.readOffset_ = i << 10;
                dss::g_File.loadToBuffer("data/field/large/castle.bin", buffer, 0);
                return 1;
            }
        }
    }
    if (g_AreaFlag.check(0x82)) {
        if (s_bridgeBlock.vx == x && s_bridgeBlock.vy == y) {
            dss::g_File.readOffset_ = 0;
            dss::g_File.loadToBuffer("data/field/large/bridge.bin", buffer, 0);
            return 1;
        }
    }
    if (g_AreaFlag.check(0x176)) {
        for (int i = 0; i < 4; i++) {
            if (x == s_magmaBlock[i].vx && y == s_magmaBlock[i].vy) {
                dss::g_File.readOffset_ = i << 10;
                dss::g_File.loadToBuffer("data/field/large/magma.bin", buffer, 0);
                return 1;
            }
        }
    }
    if (g_AreaFlag.check(0xde)) {
        for (int i = 0; i < 4; i++) {
            if (x == s_suimonBlock[i].vx && y == s_suimonBlock[i].vy) {
                dss::g_File.readOffset_ = i << 10;
                dss::g_File.loadToBuffer("data/field/large/suimon.bin", buffer, 0);
                return 1;
            }
        }
    }
    return 0;
}

THUMB void fld::FieldLargeMap::buildMapTexture(int x, int y)
{
    char* src[8];
    void* buffer[8];
    char* dst = (char*)unk_54.getTextureData();
    for (int i = 0; i < 8; i++) {
        buffer[i] = dssAlloc(&data_020fd24c, 0x400, 0x20);
    }
    int bx;
    int by;
    for (int j = 0; j < 6; j++) {
        by = y + j;
        if (by < 0) {
            by += 0x20;
        }
        if (by >= 0x20) {
            by -= 0x20;
        }
        for (int i = 0; i < 8; i++) {
            bx = x + i;
            if (bx < 0) {
                bx += 0x20;
            }
            if (bx >= 0x20) {
                bx -= 0x20;
            }
            dss::g_File.readSize_ = 0x400;
            if (loadEventBlock(bx, by, buffer[i]) == 0) {
                dss::g_File.readOffset_ = (bx << 10) + (by << 15);
                dss::g_File.loadToBuffer("data/field/large/largemap.bin", buffer[i], 0);
            }
            src[i] = (char*)buffer[i];
        }
        for (int k = 0; k < 0x20; k++) {
            for (int i = 0; i < 8; i++) {
                dss::memcpy(dst, src[i], 0x20);
                dst += 0x20;
                src[i] += 0x20;
            }
        }
    }
    DC_CleanAll();
    for (int i = 0; i < 8; i++) {
        dssFree(&data_020fd24c, buffer[i]);
    }
}

THUMB void fld::FieldLargeMap::buildPlayerMap()
{
    dss::Fix32Vector3 pos = FieldPlayerManager::getSingleton().getPosition();
    int x = (pos.vx.value + 0x40000) / 0x80000 - 4;
    int y = (pos.vy.value + 0x40000) / 0x80000 - 3;
    buildMapTexture(x, y);
    OS_Wait();
    unk_54.allocVram();
    unk_54.transferToVram();
    int px = pos.vx.value - (x << 19);
    int py = pos.vy.value - (y << 19);
    px /= 0x4000;
    py /= 0x4000;
    unk_04.allocVram();
    unk_04.transferToVram();
    unk_04.setSize(0x20, 0x20);
    unk_04.setPosition(px + s_markerOffsetX, s_markerOffsetY + (py - 0x20));
    unk_a4 = px;
    unk_a8 = py;
}

THUMB void fld::FieldLargeMap::setAlpha(unsigned char alpha)
{
    unk_54.setAlpha(alpha);
    unk_04.setAlpha(alpha);
}

THUMB void fld::FieldLargeMap::updatePlayerMarker()
{
    unk_04.setPosition(unk_a4 + s_markerOffsetX, s_markerOffsetY + (unk_a8 - 0x20));
}
