#pragma once
#include <globaldefs.h>
#include "main/dss/TextureBillboard.hpp"
#include "main/dss/PolygonObject.hpp"
#include "main/data/DataObject.hpp"

namespace dss {
    struct Camera;
    struct UnkDualCameraBase;
}

// polygon vertices given as four corners
struct UnkPolygonCorners : UnkPolygonVertex {
    UnkPolygonCorners(const dss::Vector3<dss::Fix16>& v0, const dss::Vector3<dss::Fix16>& v1,
                      const dss::Vector3<dss::Fix16>& v2, const dss::Vector3<dss::Fix16>& v3);
};

// billboard texture coordinates given as four corners
struct UnkBillboardTexCorners : UnkBillboardTexCoord {
    UnkBillboardTexCorners(const dss::Vector2<dss::Fix32>& v0, const dss::Vector2<dss::Fix32>& v1,
                           const dss::Vector2<dss::Fix32>& v2, const dss::Vector2<dss::Fix32>& v3);
};

// shadow under a billboard character: a textured quad, or the shadow volume of the shadow polygons
/* vtable 0x0209a630 */
struct UnkCharacterShadow : PolygonObject {
    virtual void draw();
    virtual void setPosition(const dss::Fix32Vector3& position);

    UnkCharacterShadow();
    ~UnkCharacterShadow();
    void unkfunc_020567b0(int type);            // setup
    void unkfunc_02056824();
    static void unkfunc_02056900(int type);     // shadow type
    static int isShadowEnable();              // shadow enable
    static dss::Fix32Vector3 getShadowScale();    // shadow scale
};

// one frame of the character animation
struct UnkBillboardAnimation {
    int index;
    unsigned int time;
};

/* vtable 0x0209a5f0 */
struct BillboardCharacter : TextureBillboard {
    enum {
        FLAG_ENABLE = 0x1,
        FLAG_DISPLAY = 0x2,
        FLAG_VISIBLE = 0x4,
        FLAG_ANIM = 0x8,
        FLAG_STAY = 0x10,
        FLAG_NEAR = 0x20,
        FLAG_SHADOW = 0x40,
        FLAG_SLEEP = 0x80,
        FLAG_WRIGGLE = 0x100,
        FLAG_ANIM_NEUTRAL = 0x200,
        FLAG_ANIM_PALLET = 0x400,
        FLAG_RELOAD = 0x800,
        FLAG_DRAW_RESET = 0x1000,
        FLAG_SHADOW_ONLY = 0x2000,
        FLAG_DEFAULT = 0x1256
    };

    virtual void draw();
    virtual void setPosition(const dss::Fix32Vector3& position);

    unsigned short direction_;                  // 0x0B8
    unsigned short preDirection_;               // 0x0BA
    int textureNum_;                            // 0x0BC
    int dispDirection_;                         // 0x0C0
    int reverse_;                               // 0x0C4
    unsigned short flag_;                       // 0x0C8
    DataObject data_;                           // 0x0CC
    void* textures_[8];                         // 0x0DC
    dss::Fix32Vector3 paletteRgbRate_;                  // 0x0FC palette rgb rate
    dss::Fix32Vector3 unk_108;                  // 0x108 shadow scale
    short textureIndex_;                        // 0x114
    dss::Vector2<dss::Fix32> uvOffset;          // 0x118
    int anmIndex_;                              // 0x120
    unsigned int anmTime_;                      // 0x124
    UnkCharacterShadow shadow_;                 // 0x128
    unsigned char width_;                       // 0x1AC
    unsigned char height_;                      // 0x1AD

    BillboardCharacter();
    void unkfunc_0205568c(void* data);          // sets the texture from a loaded pack
    void resetTexture();                    // restores the default texture
    void* getTexture(int index);          // texture of a direction
    void load(const char* name, dss::File::LoadSwitch loadSwitch);  // load
    void initialize();                    // initialize after the data is loaded
    void cleanup();
    void startAnimation(int index);
    void selectDirectionTexture(int index);           // selects the direction texture
    void setCameraDirection(const dss::Fix32Vector3* direction);
    int isVisible();
    void scaleByCameraDistance(dss::Fix32 scale);    // scale by the camera distance
    static dss::Camera* getBaseCamera();     // camera

    static void setAllCharaAnim(bool flag);
    static void setAllAnimLock(bool flag);
    static void setCamera(dss::UnkDualCameraBase* camera);
    static void setCamera(dss::Camera* camera);
    static void setChangeCameraAngle(bool flag);
    static void loadShadowTexture();             // loads the character shadow texture
    static void releaseShadowTexture();             // releases the character shadow texture
    static void reloadShadowTexture();             // reloads the character shadow texture
    void setRotate(unsigned short direction);
    unsigned short getRotate();
    void execute();
    void setVisibleFlag(int flag);            // sets or clears FLAG_ANIM
    static bool isAllAnimation();
    void setDisplayEnable(int flag);
    bool isDisplayEnable();
    void setAnimFlag(int flag);
    void setNearFlag(int flag);
    void setWriggleFlag(int flag);

    static dss::UnkDualCameraBase* camera_;
    static dss::Camera* baseCamera_;            // camera_ of the mobile version
    static int allAnimLock;
    static int changeAngle_;
    static dss::BitFlag<unsigned char> allFlag_;
    static UnkBillboardAnimation animation_[];  // animation frames, ends with index -1
};

extern dss::Fix32 data_02102ee4;                // scale of a sleeping character
