#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/data/DataObject.hpp"
#include "main/dss/UnkSprite2D.hpp"
#include "main/dss/UnkTextureObject.hpp"
#include "main/fld/CWorldMap.hpp"
#include "ov005/fld/FieldActionCalculate.hpp"

namespace fld
{
    struct FieldData {
        static const int SYMBOL_MAX = 128;
        static const int SYMBOL_TEXTURE_NUM = 34;
        static const int ANIM_PATTERN8 = 8;
        static const int ANIM_PATTERN24 = 24;
        static const int KANBAN_MAX = 20;

        int smokeCounter_[3];                           // 0x0000
        DataObject pattern8_;                           // 0x000C
        DataObject pattern24_;                          // 0x001C
        DataObject symbolPack_;                         // 0x002C
        UnkTextureObject* symbolTexture_[SYMBOL_TEXTURE_NUM];   // 0x003C
        UnkSprite2D m_symbol[SYMBOL_MAX];               // 0x00C4
        unsigned short symbolPalette_[SYMBOL_TEXTURE_NUM][16];  // 0x1CC4
        DataObject dataObject_;                         // 0x2104 map file
        DataObject blockData_;                          // 0x2114 block texture file
        UnkTextureObject* blockTexture_;                // 0x2124
        UnkTextureObject blockTextureObject_;           // 0x2128
        UnkMenuSprite ruramoon_;                        // 0x2198
        UnkMenuSprite smoke_;                           // 0x21E8
        UnkMenuSprite magma_;                           // 0x2238
        UnkMenuSprite casinoShip_;                      // 0x2288
        UnkMenuSprite sunkenFirmament_;                 // 0x22D8
        CWorldMap worldData_;                           // 0x2328
        CWorldSymbol symbolData_;                       // 0x234C
        int pattern8Block_;                             // 0x2354 VRAM block of the 8 frame animation
        int pattern24Block_;                            // 0x2358 VRAM block of the 24 frame animation
        unsigned short blockPalette_[256];              // 0x235C
        unsigned short blockPaletteOrg_[256];           // 0x255C
        int animCounter8;                               // 0x275C
        int animCounter24;                              // 0x2760
        int pause_;                                     // 0x2764
        dss::Fix32Vector3 position_;                    // 0x2768
        dss::Vector2<int> baseBlock_;                   // 0x2774
        dss::Vector2<dss::Fix32> ofsBlock_;             // 0x277C
        int offset_;                                    // 0x2784
        int frame_;                                     // 0x2788
        int searchLeft_;                                // 0x278C
        int searchTop_;                                 // 0x2790
        int searchRight_;                               // 0x2794
        int searchBottom_;                              // 0x2798
        int magmaOffsetX_;                              // 0x279C
        int magmaOffsetY_;                              // 0x27A0
        dss::Vector2<int> kanbanPos_[KANBAN_MAX];       // 0x27A4
        unsigned short kanbanId_[KANBAN_MAX];           // 0x2844
        int kanbanCount_;                               // 0x286C

        FieldData();
        ~FieldData();
        void setup(int map, int ch);
        void setupBlock(int map);
        void setupSymbol(int flag);
        void reload();
        void cleanup(int map);
        void setPlayerCamera();
        void setFieldCamera();
        void drawBlock();
        void draw2DField(int x, int y, int u, int v, unsigned char* uv);
        void drawRuramonn();
        void drawRuramoon(dss::Fix32 x, dss::Fix32 y);
        void drawSmoke(dss::Fix32 x, dss::Fix32 y);
        void drawCasinoShip(dss::Fix32 x, dss::Fix32 y);
        void drawMagma(dss::Fix32 x, dss::Fix32 y);
        void drawSunkenFirmament();
        void drawSymbol();
        void nextAnimation8();
        void nextAnimation24();
        void draw();
        void setPosition(dss::Fix32Vector3& pos);
        dss::Fix32Vector3 getPosition();
        void setOffset(int offset);
        int getOffset();
        bool isEnable(int x, int y);
        int getAttr(int x, int y);
        CWorldMap& getWorldMap();
        dss::Fix32Vector3 getSymbolPosition(int index);
        int isSymbolNearArea(dss::Fix32Vector3& pos, int w, int h);
        int isNearSymbol(dss::Fix32Vector3& pos, int type);
        bool isSymbolAttachByUid(int uid, dss::Fix32Vector3& pos);
        int getSearchSymbolAttach(dss::Fix32Vector3& pos, int* id);
        bool isCollSymbol(int x, int y);
        void setPaletteRate(int flag, dss::Fix32Vector3& rate);
        int getChanum();
        void calcDrawPosition(int& x, int& y);
        void pause(int flag);
        void setKanban();
        int searchKanban(int x, int y, dss::Vector2<dss::Fix32>* pos);
        void setDispSymbol(int uid, int disp);
    };

    struct FieldStage {
        FieldData fieldData;                    // 0x0000
        int map_;                               // 0x2870
        int change_;                            // 0x2874
        int scriptShip_;                        // 0x2878

        FieldStage();
        ~FieldStage();
        static FieldStage* getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
        void drawPlayer();
        void reload();
        void ChangeTime(int flag);
        FieldData& getFieldData();
        void setPosition(dss::Fix32Vector3& pos);
        void setOffset(int offset);
        void pause(int flag);
        int getSearchSymbolAttach(dss::Fix32Vector3 pos, int* id);
        bool getBlockAttr(int x, int y);
        int getBlockAttr2(int x, int y);
        int searchKanban(int x, int y, dss::Vector2<dss::Fix32>* pos);
        void setChipAttr(int x, int y, int* attr);
        void setWalkColl(int x, int y, FieldCollInfo& info);
        void setShipColl(int x, int y, FieldCollInfo& info);
        bool getShipColl(int x, int y);
        void setCarpetColl(int x, int y, FieldCollInfo& info);
        bool isCarpetColl(int x, int y);
        dss::Fix32Vector3 getSymbolPosition(int index);
        dss::Vector2<int> calcDrawPosition(dss::Fix32Vector3& pos);
        void setSymbolFlag(int uid);
        void eraseSymbol(int uid);
        void setSymbolDisp(int uid, int disp);
        void drawRuramoon();
        void setScriptShip(bool flag);
    };
} // namespace fld
