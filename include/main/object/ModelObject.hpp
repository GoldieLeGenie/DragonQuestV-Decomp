#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkMatrix43.hpp"
#include "main/dss/UnkModelMember.hpp"
#include "main/data/DataObject.hpp"
#include "main/dss/Camera.hpp"

struct UnkModelMember;

// Abstract base of the DS model objects (DS-only, name invented). It has no home TU: every `#pragma ipa file`
// TU constructing a model (LogoPart, TownModelDraw, ModelObjectWithCamera) emits a weak copy of its vtable
// that the linker strips but that still takes part in the data sort, and its dead vptr store adds sinit pcodes.
struct UnkModelInterface {
    virtual void vf00() = 0;
    virtual void vf04() = 0;
    virtual void draw() = 0;
    virtual void cleanup(int flag) = 0;
};

struct UnkModelObjectBase : UnkModelInterface {
    virtual void vf00();                    // slot 0
    virtual void vf04();                    // slot 1
    virtual void draw();                    // slot 2
    virtual void cleanup(int flag);         // slot 3

    int unk_004;                            /* 0x004 */
    NNSG3dRenderObj renderObj_[4];          /* 0x008 */
    int count_;                             /* 0x158 */
    UnkModelMember* member_;                /* 0x15C */
    dss::Fix32Vector3 m_scl;                 /* 0x160 */
    dss::Fix32Vector3 m_pos;                 /* 0x16C */
    dss::Fix32Vector3 m_rgb;                 /* 0x178 */
    dss::Vector3<short> m_rot;              /* 0x184 */
    dss::UnkMatrix43 m_matrix;              /* 0x18C */

    dss::Fix32Vector3& getPosition();
    dss::Fix32Vector3& getScale();
    void setupModel(UnkModelMember* member);          // setup
    void setLightColor(int light, unsigned short color);            // light color
    void setLightVector(int light, dss::Vector3<dss::Fix16> vector);    // light vector
    void addAnimation(NNSG3dAnmObj* obj);               // add animation
    void removeAnimation(NNSG3dAnmObj* obj);               // remove animation
    void setModelScale(dss::Fix32Vector3 scale);
    void setModelPosition(dss::Fix32Vector3 position);
    void setModelRotation(dss::Vector3<short> rotation);
};

struct ModelAnimation {
    int flag_;                              /* 0x00  1: loop, 2: end */
    void* resource_;                        /* 0x04 */
    void* anm_;                             /* 0x08 */
    NNSG3dAnmObj* obj_;                     /* 0x0C */
    NNSFndAllocator allocator_;             /* 0x10 */

    void setup(void* resource, void* model);
    void cleanup();
    void start(int loop);
    void execute();
    int isEnd();
    bool checkFlag(int bit) const;
};

// model object without animations
struct UnkStaticModelObject : UnkModelObjectBase {
    virtual void vf00();
    virtual void vf04();

    DataObject modelData_;                  /* 0x1BC */
    UnkModelMember model_;                 /* 0x1CC */

    void setup(const char* name, int loadSwitch);
};

struct ModelObject : UnkStaticModelObject {
    virtual void vf00();
    virtual void draw();
    virtual void cleanup(int flag);

    DataObject animData_[6];                /* 0x1D8 */
    ModelAnimation animation_[6];        /* 0x238 */
    int m_play_flag;                        /* 0x2F8 */
    int m_pause_flag;                       /* 0x2FC */
    int m_animation_index;                  /* 0x300 */

    static dss::Fix32 defaultScale;

    void setup(const char* name, const char* animName, int loadSwitch);
    void setup(void* model, int flag);
    void loadAnimation(const char* name, int index, int loadSwitch);    // set animation (file)
    void setAnimation(void* animation, int index);     // set animation
    void start(int loop);
    void startAnimation(int index, int loop);
    void setScale(dss::Fix32 scale);
    void setScale(const dss::Fix32Vector3& scale);
    void setPosition(const dss::Fix32Vector3& position);
    void setRotationIdx(const dss::Vector3<short>& rotation);
    void pause(int flag);
    int getAnimation();
};

/* vtable 0x020c3c08 */
struct ModelObjectWithCamera : ModelObject {
    enum CameraType {
        Normal = 0,
        Follow = 1,
        Standard = 2,
        Near = 3,
        Near2 = 4,
        Far = 5,
        Max = 6
    };

    virtual void draw();

    CameraType type_;                       /* 0x304 */

    static dss::Camera* camera_;
    static dss::Fix32 distance_;
    static dss::Fix32 relativeScale_;

    ModelObjectWithCamera();
    void execNormal();
    void execFollow();
    void execNear();
    void execNear2();
    void execFar();
};
