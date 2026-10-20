#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/Camera.hpp"

#include "main/dss/Position.hpp"
#include "main/dss/TextureObject.hpp"

struct DSSAParts {
    unsigned char partsIndex_;          /* 0x00 */
    unsigned char flag_;                /* 0x01 */
    short currentFrame_;                /* 0x02 */
    short posX_;                        /* 0x04 */
    short posY_;                        /* 0x06 */
    unsigned short scaleX_;             /* 0x08 */
    unsigned short scaleY_;             /* 0x0A */
    short angle_;                       /* 0x0C */
    char trans_;                        /* 0x0E */
    char priority_;                     /* 0x0F */

    int getPartsIndex();
    int getType();
    int getPosX();
    int getPosY();
    int getScaleX();
    int getScaleY();
    int getAngle();
    int getTrans();
    int getPriority();
    bool getFlipX();
    bool getFlipY();
    bool getAlpha();
    void print();
};

struct BasicInfo {
    short type_[2];                     /* 0x00 */
    short area_[4];                     /* 0x04 */
    short origin_[2];                   /* 0x0C */
};

struct UnkDSSAHeader {
    unsigned char unk_00[0x10];
    int count_;                         /* 0x10 */
    int frame_;                         /* 0x14 */
    unsigned char unk_18[8];
};

struct UnkDSSABoundingBox {
    short area_[4];
};

struct UnkDSSAFrame {
    int unk_00;
    int currentFrame_;                  /* 0x04 */
    int usableCount_;                   /* 0x08 */
    int unk_0c;
};

struct DSSAData {
    void* data_;                        /* 0x00 */
    int count_;                         /* 0x04 */
    int frame_;                         /* 0x08 */
    BasicInfo* basicInfo_;              /* 0x0C */
    UnkDSSABoundingBox* boundingBox_;      /* 0x10 */
    int* offset_;                       /* 0x14 */
    int currentFrame_;                  /* 0x18 */
    int usableCount_;                   /* 0x1C */
    int defineNullInfo[10];             /* 0x20 */
    DSSAParts* parts_;                  /* 0x48 */
    void* texture_;                     /* 0x4C */

    DSSAData();
    ~DSSAData();
    void setup(void* data);
    static int align(int value, int alignment);
    void cleanup();
    void setParts(int frame);
    void setParts(void* frame);
    DSSAParts* getParts(int index);
    int getAreaTop(int index);
    int getAreaLeft(int index);
    int getAreaBottom(int index);
    int getAreaRight(int index);
    int getOriginX(int index);
    int getOriginY(int index);
    int getNullIndex(int index);
};

struct DSSAObject : Position {
    virtual void draw();                                            
    virtual void execute();                                         
    virtual void setupDraw();                                       
    virtual void setupRoot();                                       
    virtual void setupTRS(DSSAParts* parts);                        
    virtual void drawParts(DSSAParts* parts);                       

    void* data_;                        /* 0x34 */
    DSSAData dssaData_;                 /* 0x38 */
    void* palette_;                     /* 0x88 */
    dss::Fix32 alpha_;                   /* 0x8C */
    int flag_;                          /* 0x90 */
    int frame_;                         /* 0x94 */
    int displayPartsCount_;             /* 0x98 */

    DSSAObject();
    ~DSSAObject();
    void setup(void* data);
    void setTexture(void* texture);
    void setPalette(void* palette);
    void cleanup();
    void start(int frame);
    void pause(int pause);
    int isPause();
    int isEnd();
    int isEnable();
    void setAlpha(dss::Fix32 alpha);
    void setCurrentFrame(int frame);
    dss::Fix32Vector3 getNullPosition(int index);
    dss::Vector3<int> getNullPositionInt(int index);
    static void setHueChange(int hue);
    static void setDefaultScale2(dss::Fix32 scale);
    static dss::Fix32 getDefaultScale2();
    static void setDefaultScale(dss::Fix32 scale);
    static dss::Fix32 getDefaultScale();
    void setReverse(int reverse);
    int isReverse();
    static void setPriority(int priority);

    static int posX_;
    static int posY_;
    static int sizeX_;
    static int sizeY_;
    static int scaleX_;
    static int scaleY_;
    static int angle_;
    static int priority_;
    static long trans_;
    static int calcType_;
    static dss::Fix32Vector3 baseScale_;
    static int priorityShift_;
    static int hueChangeFlag_;
};

struct DSSAObject2D : DSSAObject {
    DSSAObject2D();
    ~DSSAObject2D();
    virtual void setupDraw();
    virtual void setupRoot();
    virtual void setupTRS(DSSAParts* parts);
    virtual void drawParts(DSSAParts* parts);

};

struct DSSAObjectWithCamera : DSSAObject {
    enum CameraType {
        Normal = 0,
        Follow = 1,
        Standard = 2,
        Near = 3,
        Near2 = 4,
        Far = 5,
        Normal2 = 6,
        Max = 7
    };

    virtual void draw();
    virtual void execute();

    CameraType type_;                   /* 0x9C */

    static dss::Camera* camera_;
    static dss::Fix32 distance_;
    static dss::Fix32 relativeScale_;

    DSSAObjectWithCamera();
    static void setCamera(dss::Camera* camera);
    void execNormal2();
    void execNormal();
    void execFollow();
    void execNear();
    void execNear2();
    void execFar();
};





extern "C" {
    void func_0208032c(VecFx32* scale);                         /* NNS_G3dGlbSetBaseScale */
    void func_02080308(dss::Fix32Vector3* trans);                /* NNS_G3dGlbSetBaseTrans */
    void func_0206ae58(int light, int x, int y, int z);            /* NNS_G3dGlbLightVector */
    void func_0206ae94(int light, int color);                    /* NNS_G3dGlbLightColor */
    void func_020802dc(void);
    void func_02082604(void);
}
