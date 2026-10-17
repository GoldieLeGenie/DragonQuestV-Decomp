#pragma once
#include <globaldefs.h>

// parameters of the script commands
struct PARAM_FADEIN {
    unsigned int frame;
};

struct PARAM_FADEOUT {
    unsigned int frame;
    unsigned int type;
};

struct PARAM_FADEIN2 {
    unsigned int frame;
};

struct PARAM_FADEOUT2 {
    unsigned int frame;
    unsigned int type;
};

struct PARAM_MUSIC_VOLUME {
    unsigned int volume;
    unsigned int frame;
};

struct PARAM_PLAY_MUSIC {
    unsigned int musicNo;
    unsigned int frame;
    unsigned int flag;
};

struct PARAM_IS_TRIGGER_FORWARD {
    int startX;
    int startY;
    int startZ;
    int endX;
    int endY;
    int endZ;
    unsigned int flag;
};

struct PARAM_SET_MUSIC {
    unsigned int music;
};

struct PARAM_MUSIC_PAUSE {
    unsigned int pause;
};

struct PARAM_SET_SHIP_POS {
    int posX;
    int posY;
    int posZ;
};

struct PARAM_CHANGE_FIELD {
    unsigned int index;
};

struct PARAM_RISEUP_MOVE {
    int startX;
    int startY;
    int startZ;
    int endX;
    int endY;
    int endZ;
    unsigned int item;
    unsigned int frame;
};

struct PARAM_SET_CAMERA_TARGET_CHARA_FRAME {
    unsigned int frame;
    unsigned int objId;
};

struct PARAM_CAMERA_ACTION_SET {
    unsigned int flag;
};

struct PARAM_CHECK_SURFACE {
    unsigned int surface;
    unsigned int flag;
};

struct PARAM_DEL_SCRIPT_MAP_OBJECT {
    unsigned int uid;
};

struct PARAM_DEL_TRUCK_WAGON {
    unsigned int uid;
};

struct PARAM_FURNITURE_COLL_MOVE {
    unsigned int target;
    int endX;
    int endY;
    int endZ;
};

struct PARAM_FURNITURE_FADEOUT {
    unsigned int target;
    unsigned int frame;
    unsigned int fade;
    unsigned int priority;
};

struct PARAM_FURNITURE_GROUP_MOVE {
    unsigned int target;
    int speedX;
    int speedY;
    int speedZ;
    unsigned int frame;
};

struct PARAM_FURNITURE_GROUP_ROTATE {
    unsigned int target;
    int speedX;
    int speedY;
    int speedZ;
    unsigned int frame;
};

struct PARAM_FURNITURE_MOVE {
    unsigned int target;
    int endX;
    int endY;
    int endZ;
    unsigned int frame;
};

struct PARAM_FURNITURE_MOVE2 {
    unsigned int target;
    int endX;
    int endY;
    int endZ;
    int rate;
};

struct PARAM_FURNITURE_OPEN {
    unsigned int target;
};

struct PARAM_FURNITURE_ROTATE {
    unsigned int target;
    int endX;
    int endY;
    int endZ;
    unsigned int frame;
};

struct PARAM_IS_MAP_TREASURE {
    unsigned int target;
    unsigned int flag;
};

struct PARAM_MAP_ANIMATION_A {
    unsigned int target;
    unsigned int animation;
};

struct PARAM_MAP_ANIMATION_B {
    unsigned int target;
    unsigned int animation;
};

struct PARAM_MAP_OBJ_GMMICK_MOVE {
    unsigned int uid;
    int speedRate;
    unsigned int direction;
};

struct PARAM_MAP_TEXTURE {
    unsigned int display;
};

struct PARAM_SEARCH_MAP_OBJ2 {
    unsigned int uid1;
    unsigned int uid2;
};

struct PARAM_SETUP_GRID_MOVE {
    unsigned int uid;
    unsigned int flag;
    int length;
};

struct PARAM_SET_CHARA_POS_TO_MAPOBJ {
    unsigned int uid;
    int offsetX;
    int offsetY;
    int offsetZ;
    unsigned int flag;
    unsigned int dir;
};

struct PARAM_SET_EVENT_DOOR {
    unsigned int uid;
    unsigned int type;
};

struct PARAM_SET_FLOOR_MAP_OBJECT {
    unsigned int mapUid;
    int posX;
    int posY;
    int posZ;
};

struct PARAM_SET_FURNITURE_GAZE {
    unsigned int id;
};

struct PARAM_SET_FURNITURE_POSITION {
    int posX;
    int posY;
    int posZ;
    unsigned int uid;
};

struct PARAM_SET_MAP_COLLISION {
    unsigned int target;
    unsigned int collision;
};

struct PARAM_SET_MAP_TEXTURE {
    unsigned int texture;
};

struct PARAM_SET_PARTICLE_DRAW {
    unsigned int type;
};

struct PARAM_SET_PARTICLE_MAX {
    unsigned int max;
};

struct PARAM_SET_SPOT_CLOSE {
    unsigned int R;
    unsigned int R2;
    unsigned int frame;
};

struct PARAM_SET_SPOT_LIGHT {
    int posX;
    int posY;
    int posZ;
    unsigned int R;
    unsigned int frame;
};

struct PARAM_SET_SURFACE_ON_OFF {
    unsigned int surfaceId;
    unsigned int collFlag;
    unsigned int setFlag;
};

struct PARAM_SET_TOWN_SHIP {
    unsigned int name;
    int posX;
    int posY;
    int posZ;
    int idx;
};

struct PARAM_SET_TRUCK_START {
    unsigned int railstart;
    unsigned int railnext;
    unsigned int wagonUid;
};

struct PARAM_SET_TRUCK_SWITCH {
    unsigned int rootNo;
    unsigned int setNo;
    unsigned int switchUid;
    unsigned int switchAnim;
    unsigned int railUid;
    unsigned int railAnim;
};

struct PARAM_SET_WAGON_POSITION {
    unsigned int uid;
    int posX;
    int posY;
    int posZ;
};

struct PARAM_SUGOROKU_END_TYPE {
    unsigned int endType;
};

struct PARAM_TOUCH_MAP_OBJ {
    unsigned int uid1;
    unsigned int uid2;
    unsigned int flag;
};

struct PARAM_TRUCK_SWITCH {
    unsigned int uid;
};

struct PARAM_IS_PLAYER_DIRECTION {
    unsigned int direction;
};

struct PARAM_PARTY_JOIN {
    unsigned int objNo;
    unsigned int index;
    unsigned int pos;
};

struct PARAM_PARTY_JUMP_BY_PLAYER_NO {
    unsigned int playerNo;
};

struct PARAM_PARTY_MOVE2_FORMATION {
    unsigned int frmDir;
    unsigned int charaDir;
    int rate;
};

struct PARAM_PARTY_QUIT {
    unsigned int objNo;
    int index;
};

struct PARAM_PLAYER_ACTION_NOT_CHANGE_DIRECTION {
    unsigned int flag;
};

struct PARAM_PLAYER_EFFECT_MARK {
    unsigned int mark;
};

struct PARAM_PLAYER_LINE_MOVE {
    unsigned int axis;
    unsigned int absFlag;
    int value;
    unsigned int frame;
};

struct PARAM_PLAYER_LINE_MOVE2 {
    unsigned int axis;
    unsigned int absFlag;
    int value;
    int rate;
};

struct PARAM_PLAYER_MOVE2_JUMP {
    int endX;
    int endY;
    int endZ;
    int rate;
};

struct PARAM_PLAYER_MOVE2_TO {
    int endX;
    int endY;
    int endZ;
    int rate;
    unsigned int absFlag;
};

struct PARAM_PLAYER_MOVE_JUMP {
    int endX;
    int endY;
    int endZ;
    unsigned int frame;
};

struct PARAM_PLAYER_MOVE_TO {
    int endX;
    int endY;
    int endZ;
    unsigned int frame;
    unsigned int absFlag;
};

struct PARAM_PLAYER_ROT {
    unsigned int frame;
    int idx;
    unsigned int rotFlag;
    unsigned int endFlag;
};

struct PARAM_PLAYER_SET_COLL {
    unsigned int floorFlag;
    unsigned int wallFlag;
};

struct PARAM_PLAYER_WAIT {
    unsigned int frame;
};

struct PARAM_SET_CHARACTER_POSITION {
    int posX;
    int posY;
    int posZ;
};

struct PARAM_SET_COLL_PLAYER_TO_CHARA {
    unsigned int flag;
};

struct PARAM_SET_PARTY_KEEP {
    unsigned int flag;
};

struct PARAM_SET_PARTY_MARK {
    unsigned int player;
    unsigned int mark;
};

struct PARAM_SET_PARTY_ORDER {
    unsigned int index;
};

struct PARAM_SET_PLAYERPOS_AT_MAPOBJ {
    unsigned int uid;
    int offsetX;
    int offsetY;
    int offsetZ;
    unsigned int flag;
    unsigned int dir;
};

struct PARAM_SET_PLAYER_DIRECTION {
    unsigned int direction;
};

struct PARAM_SET_PLAYER_GET_ON_OFF {
    unsigned int type;
    int posX;
    int posY;
    int posZ;
};

struct PARAM_SET_PLAYER_SLEEP {
    unsigned int flag;
};

struct PARAM_STORE_RESTORE_PLAYER_ITEM {
    unsigned int flag;
};

struct PARAM_SPEAK_TO_PLAYER {
    unsigned int message;
    unsigned int count;
};

struct PARAM_SPEAK_TO_PLAYER2 {
    unsigned int message0;
    unsigned int message1;
    unsigned int message2;
    unsigned int message3;
    unsigned int message4;
    unsigned int message5;
    unsigned int message6;
    unsigned int message7;
};

struct PARAM_SPEAK_TO_PLAYER_SELF_CLOSING {
    unsigned int message;
    unsigned int frame;
};

struct PARAM_MENU_SHOP {
    unsigned int shop;
};

struct PARAM_EVENT_INN {
    unsigned int type;
    unsigned int index;
};

struct PARAM_SET_SON_DAUGHTER_NAME {
    unsigned int type;
};

struct PARAM_FRIEND_MONSTER_AZUKE {
    unsigned int index;
};

struct PARAM_IS_TRIGGER2 {
    int startX;
    int startY;
    int startZ;
    int endX;
    int endY;
    int endZ;
    unsigned int direction;
};

struct PARAM_IS_TRIGGER_CHARACTER {
    int startX;
    int startY;
    int startZ;
    int endX;
    int endY;
    int endZ;
    unsigned int flag;
};

struct PARAM_SET_OVERVIEW_POINT {
    int posX;
    int posY;
    int posZ;
};

struct PARAM_SET_OVERVIEW_CHURCH {
    int posX;
    int posY;
    int posZ;
};

struct PARAM_SET_IKADA_INFO {
    unsigned int name;
    int posX;
    int posY;
    int posZ;
};

struct PARAM_EFFECT_WAIT {
    unsigned int effect;
    int posX;
    int posY;
    int posZ;
    unsigned int flag;
};

struct PARAM_EFFECT_MOVE {
    unsigned int effect;
    int startX;
    int startY;
    int startZ;
    int endX;
    int endY;
    int endZ;
    unsigned int frame;
};

struct PARAM_EFFECT_FADE {
    unsigned int effect;
    int posX;
    int posY;
    int posZ;
    unsigned int frame;
    unsigned int flag;
};

struct PARAM_MAP_FLASH {
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int frame;
    unsigned int se;
};

struct PARAM_MAP_SET_BACK_COLOR {
    unsigned int index;
    unsigned int frame;
};

struct PARAM_MAP_RESTORE_BACK_COLOR {
    unsigned int frame;
};

struct PARAM_MAP_BLEND_COLOR {
    int r;
    int g;
    int b;
    unsigned int frame;
};

struct PARAM_MAP_BLEND_INIT {
    unsigned int frame;
};

struct PARAM_MAP_TEXTURE_SCALE {
    unsigned int frame;
    int scaleX;
    int scaleY;
};

struct PARAM_SET_MAP_POSITION {
    int x;
    int y;
    int kind;
};

struct PARAM_MAP_CAMERA_POSITION {
    int endX;
    int endY;
    int endZ;
    unsigned int frame;
    unsigned int endFlag;
};

struct PARAM_CAMERA_MOVE_ABS {
    int endX;
    int endY;
    int endZ;
    unsigned int frame;
    unsigned int endFlag;
};

struct PARAM_MAP_CAMERA_ANGLE {
    unsigned int axis;
    int angle;
    unsigned int frame;
    unsigned int endFlag;
};

struct PARAM_MAP_CAMERA_GAZE {
    unsigned int frame;
};

struct PARAM_MAP_EVENT_CAMERA {
    unsigned int channel;
    unsigned int screen;
    unsigned int frame;
};

struct PARAM_MAP_ANIMATION {
    unsigned int channel;
};

struct PARAM_MAP_SHAKE {
    unsigned int type;
    unsigned int count;
};

struct PARAM_CAMERA_CHANGE_DISTANCE {
    int distance;
    unsigned int frame;
    unsigned int endFlag;
};

struct PARAM_CAMERA_LOCK_POV {
    unsigned int flag;
};

struct PARAM_EFFECT_TRANSFER {
    unsigned int effect;
    int posX;
    int posY;
    int posZ;
    unsigned int flag;
};

struct PARAM_EFFECT_TRANSFER_3D {
    unsigned int effect;
    int posX;
    int posY;
    int posZ;
};

struct PARAM_MAP_CAMERA_LOCK_TARGET_PLAYER {
    unsigned int flag;
};

struct PARAM_CAMERA_CLIP_DISTANCE {
    int distance;
};

struct PARAM_MAP_CAMERA_NEAR {
    unsigned int _near;
};

struct PARAM_CAMERA_RESET_DISTANCE {
    unsigned int frame;
};

struct PARAM_CAMERA_MOVE_POV {
    int endX;
    int endY;
    int endZ;
    unsigned int frame;
    unsigned int absFlag;
    unsigned int endFlag;
};

struct PARAM_CAMERA_MOVE_TO_PLAYER {
    unsigned int frame;
};

struct PARAM_IKADA_MOVE2_PLAYER_GET_ON {
    int endX;
    int endY;
    int endZ;
    unsigned int absFlag;
    int rate;
};

struct PARAM_IKADA_MOVE_PLAYER_GET_ON {
    int endX;
    int endY;
    int endZ;
    unsigned int absFlag;
    unsigned int frame;
};

struct PARAM_SET_CAMERA_ANGLE_ABS {
    int angleY;
    unsigned int frame;
    unsigned int endFlag;
};

struct PARAM_DOOR_ACTION {
    unsigned int door1;
    unsigned int door2;
    unsigned int action;
};

struct PARAM_IS_TRIGGER3 {
    int startX;
    int startY;
    int startZ;
    int endX;
    int endY;
    int endZ;
};

struct PARAM_IS_OPEN_DOOR {
    unsigned int type;
    unsigned int uid;
};

struct PARAM_MAP_CAMERA_DEFAULT_ANGLE {
    int angleX;
    int angleY;
    int angleZ;
};

struct PARAM_SET_CAMERA_LIMIT {
    unsigned int flag;
};

struct PARAM_DELETE_FURNITURE_ITEM {
    unsigned int uid;
    unsigned int flag;
};

struct PARAM_CHARACTER_ACTION_DISPLAY {
    unsigned int flag;
};

struct PARAM_CHARACTER_ACTION_GAZE {
    unsigned int frame;
};

struct PARAM_CHARACTER_ACTION_NEAR {
    unsigned int flag;
};

struct PARAM_CHARACTER_ACTION_PURSUE {
    int rate;
};

struct PARAM_CHARACTER_ACTION_SLEEP {
    unsigned int onoff;
};

struct PARAM_CHARACTER_ACTION_TREMBLE {
    unsigned int frame;
    unsigned int direction;
    unsigned int mode;
    unsigned int sycle;
};

struct PARAM_CHARACTER_ACTION_TURN {
    unsigned int direction;
    unsigned int frame;
    unsigned int rot;
};

struct PARAM_CHARACTER_ANIM {
    unsigned int count;
};

struct PARAM_CHARACTER_EFFECT_MARK {
    unsigned int index;
};

struct PARAM_CHARACTER_LINE_MOVE {
    unsigned int axis;
    unsigned int absFlag;
    int value;
    unsigned int frame;
};

struct PARAM_CHARACTER_LINE_MOVE2 {
    unsigned int axis;
    unsigned int absFlag;
    int value;
    int rate;
};

struct PARAM_CHARACTER_MOVE2_PARTY {
    int rate;
    unsigned int mode;
};

struct PARAM_CHARACTER_MOVE2_PLAYER {
    unsigned int direction;
    int adjust;
    int rate;
    unsigned int mode;
};

struct PARAM_CHARACTER_MOVE2_TO {
    int endX;
    int endY;
    int endZ;
    int rate;
    unsigned int absFlag;
};

struct PARAM_CHARACTER_MOVE_PARTY {
    unsigned int frame;
    unsigned int mode;
};

struct PARAM_CHARACTER_MOVE_PLAYER {
    unsigned int direction;
    int adjust;
    unsigned int frame;
    unsigned int mode;
};

struct PARAM_CHARACTER_MOVE_ROAM {
    int startX;
    int startZ;
    int endX;
    int endZ;
    int rate;
};

struct PARAM_CHARACTER_MOVE_TO {
    int endX;
    int endY;
    int endZ;
    unsigned int frame;
    unsigned int absFlag;
};

struct PARAM_CHARACTER_NORMAL_JUMP {
    int endX;
    int endY;
    int endZ;
    unsigned int frame;
};

struct PARAM_CHARACTER_NOT_CHANGE_DIRECTION {
    unsigned int flag;
};

struct PARAM_CHARACTER_POSE_CHANGE {
    unsigned int index;
};

struct PARAM_CHARACTER_RGB_ANIM2 {
    unsigned int R;
    unsigned int G;
    unsigned int B;
    unsigned int frame;
    unsigned int flag;
};

struct PARAM_CHARACTER_SET_COLL_STAGE {
    unsigned int floorFlag;
    unsigned int wallFlag;
    unsigned int charaFlag;
};

struct PARAM_CHARACTER_SWING_ROUND {
    unsigned int flag;
};

struct PARAM_CHARACTER_WAIT {
    unsigned int frame;
};

struct PARAM_CHARA_ALPHA {
    unsigned int alpha;
};

struct PARAM_CHARA_MOVE_LINE_TO_PLAYER {
    unsigned int line;
    int offset;
    int rate;
};

struct PARAM_CHARA_SHADOW {
    unsigned int flag;
};

struct PARAM_CHARA_START_ACTION {
    unsigned int flag;
};

struct PARAM_CHARA_VOICE {
    unsigned int voice;
};

struct PARAM_CHARCTER_3D_MOTION {
    unsigned int motion;
    unsigned int flag;
};

struct PARAM_COPY_PARTY_CHARA {
    unsigned int playerNo;
};

struct PARAM_FADEIN_CHARACTER {
    unsigned int pattern;
    unsigned int frame;
};

struct PARAM_IS_CHARACTER_DIRECTION {
    unsigned int direction;
};

struct PARAM_IS_CHARACTER_FRONT {
    unsigned int flag;
};

struct PARAM_IS_TALKED_AT_SHOP {
    unsigned int flag;
};

struct PARAM_IS_TRIGGER_DISTANCE {
    int distance;
};

struct PARAM_SET_CHARACTER_COLLISION {
    unsigned int collision;
};

struct PARAM_SET_CHARACTER_DIRECTION {
    unsigned int direction;
};

struct PARAM_SET_CHARACTER_HUE {
    unsigned int type;
    unsigned int frame;
};

struct PARAM_SET_CHARACTER_SCALE {
    int scale;
};

struct PARAM_SET_CHARA_MAP_UID {
    unsigned int uid;
};

struct PARAM_SET_CHARA_MORTION_LOCK {
    unsigned int flag;
};

struct PARAM_SET_CHARA_MOTION2 {
    unsigned int motion;
    unsigned int flag;
};

struct PARAM_SET_CHARA_ROT {
    unsigned int frame;
    int idx;
    unsigned int rotFlag;
    unsigned int endFlag;
};

struct PARAM_SET_CHARA_SYNCHRONIZED_MOVE {
    unsigned int pairObject;
    unsigned int flag;
};

struct PARAM_SET_PASSIVE_CHARA_COLL {
    int minX;
    int minZ;
    int maxX;
    int maxZ;
};

struct PARAM_SET_ROCK_RELOCATION {
    unsigned int id;
};

struct PARAM_SET_ROCK_SAVE {
    unsigned int id;
};

struct PARAM_SET_SHADOW_ONLY {
    unsigned int flag;
};

struct PARAM_FLOOR_CHANGE {
    unsigned int floor;
    int exitX;
    int exitY;
    int exitZ;
    unsigned int direction;
    unsigned int flag;
};

struct PARAM_FLOOR_EXIT {
    unsigned int floor;
    unsigned int exitNo;
    unsigned int flag;
};

struct PARAM_SET_MAP_LINK_ON_OFF {
    unsigned int surfaceNo;
    unsigned int on_off;
};

struct PARAM_CHANGE_MAP_LINK {
    unsigned int nextMapName;
    unsigned int nextId;
    unsigned int nowId;
};

struct PARAM_MAP_LINK_FIELD_DIRECT {
    unsigned int symbol;
    int posX;
    int posY;
    unsigned int flag;
};

struct PARAM_IS_DOORWAY {
    unsigned int doorway;
};

struct PARAM_SET_TOWN_TO_FIELD_LINK {
    unsigned int symbolNo;
    int posX;
    int posY;
    int posZ;
    unsigned int surfaceId;
};

struct PARAM_SET_FIELD_TO_TOWN_LINK {
    unsigned int townNameID;
    unsigned int surfaceId;
    unsigned int symbolNo;
};

struct PARAM_FIELD_ERASE_SYMBOL {
    unsigned int uid;
};

struct PARAM_FIELD_SYMBOL_DISP {
    unsigned int uid;
    unsigned int disp;
};

struct PARAM_FLOOR_CHANGE_ENDING {
    unsigned int floor;
    int exitX;
    int exitY;
    int exitZ;
    unsigned int index;
};

struct PARAM_ISMONSTER {
    unsigned int flag;
};

struct PARAM_SET_PLAYER_RIDE_ON {
    unsigned int flag;
};

struct PARAM_SET_PLAYER_SHADOW {
    unsigned int flag;
    unsigned int index;
};

struct PARAM_SET_FIELD_PLAYER_SHADOW {
    unsigned int enable;
};

struct PARAM_SET_PARTY_QUIT {
    unsigned int index;
    unsigned int flag;
};

struct PARAM_SET_PARTY_JOIN {
    unsigned int index;
    unsigned int pos;
};

struct PARAM_SET_PARTY_TOTAL_RECOVERY {
    unsigned int flag;
};

struct PARAM_IS_PARTY_ORDER {
    unsigned int order;
    unsigned int index;
};

struct PARAM_IS_PARTY_ORDER2 {
    unsigned int order;
    unsigned int index;
};

struct PARAM_IS_PLAYER_STATUS_DEAD {
    unsigned int index;
    unsigned int type;
};

struct PARAM_SET_PLAYER_RECOVERY {
    unsigned int player;
    unsigned int flag;
};

struct PARAM_SET_PLAYER_IN_CARRIAGE {
    unsigned int index;
};

struct PARAM_SET_PLAYER_MAGIC {
    unsigned int index;
    unsigned int magic;
};

struct PARAM_SET_PLAYER_EQUIP {
    unsigned int index;
    unsigned int weaponID;
    unsigned int armorID;
    unsigned int shieldID;
    unsigned int helmetID;
    unsigned int accessoryID;
};

struct PARAM_BOOKING_PANTHER_NAME {
    unsigned int name;
};

struct PARAM_CHANGE_PLAYER_DRAW {
    unsigned int id;
    unsigned int charaId;
};

struct PARAM_SET_VEHICLE {
    unsigned int type;
    unsigned int flag;
    int Xpos;
    int Ypos;
};

struct PARAM_SEARCH_MAP_OBJECT {
    unsigned int target;
};

struct PARAM_PLAYER_ITEM_INTO_FUKURO {
    unsigned int index;
};

struct PARAM_SET_PLAYER_AZUKE {
    unsigned int index;
};

struct PARAM_IS_PLAYER_NAME {
    unsigned int select;
};

struct PARAM_PARTY_DISPLAY {
    unsigned int flag;
};

struct PARAM_PARTY_DISPLAY2 {
    unsigned int flag;
};

struct PARAM_SET_PARTY_DIRECTION_BY_PLAYER_NO {
    unsigned int playerNO;
    unsigned int direction;
};

struct PARAM_RESET_PARTY_DIRECTION_BY_PLAYER_NO {
    unsigned int playerNO;
};

struct PARAM_GET_FLAG {
    unsigned int type;
    unsigned int index;
    unsigned int flag;
};

struct PARAM_SET_FLAG {
    unsigned int type;
    unsigned int index;
    unsigned int flag;
};

struct PARAM_IS_PROCURE_ITEM {
    unsigned int item;
};

struct PARAM_IS_PARTY_TOP {
    unsigned int type;
    unsigned int sex;
    unsigned int life;
    unsigned int player0;
    unsigned int player1;
    unsigned int player2;
    unsigned int player3;
    unsigned int player4;
};

struct PARAM_CHECK_PLAYER_ITEM {
    unsigned int flag;
    unsigned int index;
};

struct PARAM_IS_PARTY_RIDE_CARRIAGE {
    unsigned int index;
};

struct PARAM_IS_PARTY_MEMBER {
    unsigned int index;
};

struct PARAM_CHECK_PLAYER_HP_MP {
    unsigned int index;
    unsigned int hpFlag;
    unsigned int mpFlag;
};

struct PARAM_CHECK_PLAYER_HP_MP2 {
    unsigned int index;
    unsigned int hpFlag;
    unsigned int hpCheckFlag;
    unsigned int checkHp;
    unsigned int mpFlag;
    unsigned int mpCheckFlag;
    unsigned int checkMp;
};

struct PARAM_SET_PLAYER_HP_MP {
    unsigned int index;
    unsigned int hpFlag;
    unsigned int mpFlag;
    unsigned int percentHP;
    unsigned int percentMP;
};

struct PARAM_IS_PARTY_ITEM {
    unsigned int carriage;
    unsigned int bag;
    unsigned int rule;
    unsigned int item0;
    unsigned int item1;
    unsigned int item2;
    unsigned int item3;
};

struct PARAM_IS_PLAYER_ITEM {
    unsigned int flag;
    unsigned int index;
    unsigned int rule;
    unsigned int item0;
    unsigned int item1;
    unsigned int item2;
    unsigned int item3;
};

struct PARAM_IS_PARTY_HEAD_COUNT {
    unsigned int select;
    unsigned int carriage;
    unsigned int life;
    unsigned int operation;
    unsigned int value;
};

struct PARAM_SET_PLAYER_PARAM {
    unsigned int index;
    unsigned int change;
    unsigned int flag;
    unsigned int value;
};

struct PARAM_SET_PLAYER_CONDITION {
    unsigned int select;
    unsigned int index;
    unsigned int condition;
    unsigned int curse;
};

struct PARAM_IS_PUTIN_MONSTER_JISAN {
    unsigned int index;
};

struct PARAM_SET_RETURN_CHURCH {
    unsigned int index;
};

struct PARAM_PARTY_COPY_CHARACTER {
    unsigned int order;
    unsigned int objNo;
};

struct PARAM_IS_PARTY_ALL {
    unsigned int criterion;
    unsigned int andor;
    unsigned int sex;
    unsigned int condition;
    unsigned int index0;
    unsigned int index1;
    unsigned int index2;
    unsigned int index3;
};

struct PARAM_CHECK_INN_COUNT {
    unsigned int flag;
    unsigned int count;
};

struct PARAM_PARTY_ADD_NPC {
    unsigned int charNo;
};

struct PARAM_PARTY_DEL_NPC {
    unsigned int charNo;
};

struct PARAM_SET_PARTY_QUIT_TO_AZUKE {
    unsigned int flag;
    unsigned int index;
};

struct PARAM_SET_HEAD_CHARA {
    unsigned int index;
};

struct PARAM_RETURN_IN_CARRIAGE {
    unsigned int flag;
    unsigned int index;
};

struct PARAM_SORT_PARTY_KIND {
    unsigned int flag;
};

struct PARAM_SET_SE {
    unsigned int se;
};

struct PARAM_CUT_SE {
    unsigned int se;
};

struct PARAM_SET_SOUND_IN_SETUP {
    unsigned int no;
};

struct PARAM_BGM_FADE {
    unsigned int sound;
    unsigned int frame;
    unsigned int flag;
};

struct PARAM_CHANGE_SHOP_CHAPTER {
    unsigned int chapter;
};

struct PARAM_CHARCTER_3D_ROTATE {
    unsigned int rotX;
    unsigned int rotY;
    unsigned int rotZ;
};

struct PARAM_CHECK_EVENT_ITEM {
    unsigned int item;
};

struct PARAM_CHECK_EVENT_ITEM2 {
    unsigned int item1;
    unsigned int item2;
    unsigned int item3;
    unsigned int item4;
    unsigned int item5;
    unsigned int item6;
    unsigned int item7;
    unsigned int item8;
};

struct PARAM_CHECK_EVENT_MAGIC {
    unsigned int magic;
};

struct PARAM_CHECK_HERO_LEVEL {
    unsigned int minlevel;
    unsigned int maxlevel;
};

struct PARAM_CHECK_MONEY {
    unsigned int value;
    unsigned int flag;
};

struct PARAM_CHECK_SAVE_MONSTER {
    unsigned int index;
};

struct PARAM_CHECK_SPACE_ITEM_CHARA {
    unsigned int flag;
};

struct PARAM_CHECK_USE_EVENT_ITEM {
    unsigned int item;
};

struct PARAM_COERCTION_SORT {
    unsigned int index1;
    unsigned int index2;
    unsigned int index3;
    unsigned int index4;
};

struct PARAM_COPY_SAVE_MONSTER {
    unsigned int index;
};

struct PARAM_IS_DAY_COUNT {
    unsigned int counter;
};

struct PARAM_IS_LOAD_INIT {
    unsigned int flag;
};

struct PARAM_IS_TIMEZONE {
    unsigned int timezone;
};

struct PARAM_IS_TIMEZONE2 {
    unsigned int timeZone;
};

struct PARAM_IS_TRIGGER {
    int startX;
    int startY;
    int startZ;
    int endX;
    int endY;
    int endZ;
};

struct PARAM_MAP_CHANGE_TIMEZONE {
    unsigned int timezone;
};

struct PARAM_MINI_GAME {
    unsigned int category;
    unsigned int index;
};

struct PARAM_PLAYER_LOCK {
    unsigned int flag;
};

struct PARAM_RISEUP_PLAYER_EQUIP {
    unsigned int playerFlag;
    unsigned int index;
    unsigned int equip;
    unsigned int flag;
    int startX;
    int startY;
    int startZ;
};

struct PARAM_SETUP {
    unsigned int index;
};

struct PARAM_SET_BASHA_GO_INTO {
    unsigned int flag;
};

struct PARAM_SET_CHAPTER {
    unsigned int chapter;
};

struct PARAM_SET_COERCION_SORT_ENABLE {
    unsigned int flag;
};

struct PARAM_SET_COIN {
    unsigned int value;
    unsigned int flag;
};

struct PARAM_SET_DAY_COUNT {
    unsigned int counter;
    unsigned int days;
};

struct PARAM_SET_GOLD {
    unsigned int value;
    unsigned int flag;
};

struct PARAM_SET_ITEM {
    unsigned int index;
    unsigned int item;
    unsigned int value;
    unsigned int flag;
};

struct PARAM_SET_LURA_MESSAGE {
    unsigned int flag;
    unsigned int message;
};

struct PARAM_SET_LURA_MESSAGE2 {
    unsigned int flag;
    unsigned int voice1;
    unsigned int message1;
    unsigned int voice2;
    unsigned int message2;
    unsigned int voice3;
    unsigned int message3;
};

struct PARAM_SET_MACRO_P_M_NAME {
    unsigned int index;
};

struct PARAM_SET_MAGIC_MOVE {
    unsigned int attr;
    unsigned int map;
    unsigned int next;
};

struct PARAM_SET_PLAYER_TOWN_VEHICLE {
    unsigned int vehicle;
};

struct PARAM_SET_RANARUTA {
    unsigned int flag;
};

struct PARAM_SET_RANDOM {
    unsigned int index;
    unsigned int value;
};

struct PARAM_SET_RANDOM2 {
    unsigned int index;
    unsigned int value1;
    unsigned int value2;
};

struct PARAM_SET_RUURA_LOCK {
    unsigned int riremitoDisable;
    unsigned int rulaDisable;
};

struct PARAM_SET_SACK_ITEM {
    unsigned int item;
    unsigned int flag;
    unsigned int count;
};

struct PARAM_SET_SHOP_LIST {
    unsigned int flag;
};

struct PARAM_SET_SLEEP_NEAR {
    unsigned int def;
    unsigned int defNear;
    unsigned int phtmNear;
    unsigned int offset;
};

struct PARAM_SET_TIMEZONE {
    unsigned int timezone;
};

struct PARAM_SET_TIMEZONE_PAUSE {
    unsigned int flag;
};

struct PARAM_SET_WAIT_COUNTER {
    unsigned int frame;
};

struct PARAM_START_OPENING {
    unsigned int floor;
    int exitX;
    int exitY;
    int exitZ;
};

struct PARAM_SYSTEM_WAIT {
    unsigned int frame;
};

struct PARAM_BATTLE_END_FLAG_SET {
    unsigned int type;
    unsigned int tile;
    unsigned int winFlagType;
    unsigned int winFlagIndex;
    unsigned int loseFlagType;
    unsigned int loseFlagIndex;
};

struct PARAM_ENCOUNT {
    unsigned int type;
    unsigned int tile;
    unsigned int firstAttack;
};

struct PARAM_ENCOUNT_SET_FLAG {
    unsigned int type;
    unsigned int tile;
    unsigned int flagType;
    unsigned int index;
};

struct PARAM_SET_ENCOUNT_DISABLE {
    unsigned int flag;
};

struct PARAM_SET_ENCOUNT_STAGE_DISABLE {
    unsigned int flag;
};

struct PARAM_IS_BATTLE_TURN {
    unsigned int turn;
    unsigned int flag;
};

struct PARAM_GET_BATTLE_TRANSITION {
    unsigned int status;
};

struct PARAM_BATTLE_SYSTEM_LOCK {
    unsigned int flag;
};

struct PARAM_BATTLE_PARTY_ADD {
    unsigned int index;
};

struct PARAM_BATTLE_PARTY_REORDER {
    unsigned int member1;
    unsigned int member2;
    unsigned int member3;
    unsigned int member4;
};

struct PARAM_BATTLE_END {
    unsigned int result;
};

struct PARAM_IS_BATTLE_USE_ITEM {
    unsigned int item;
};

struct PARAM_SET_BATTLE_NPC_MONSTER_INDEX {
    unsigned int id;
    unsigned int monsterId;
};

struct PARAM_SET_BATTLE_MONSTER_INDEX {
    unsigned int id;
    unsigned int monsterId;
};

struct PARAM_SET_BATTLE_MONSTER_ANIMATION_INDEX {
    unsigned int id;
    unsigned int animId;
    unsigned int loopFlag;
};

struct PARAM_SET_BATTLE_MONSTER_LOOP_ANIMATION_INDEX {
    unsigned int id;
    unsigned int animId;
};

struct PARAM_SET_DISABLE_ESCAPE {
    unsigned int flag;
};

struct PARAM_BATTLE_MESSAGE {
    unsigned int message0;
    unsigned int message1;
    unsigned int message2;
    unsigned int message3;
    unsigned int message4;
    unsigned int message5;
    unsigned int message6;
    unsigned int message7;
};

struct PARAM_BATTLE_EFFECT {
    unsigned int target;
    unsigned int effect;
};

struct PARAM_MESSAGE1 {
    unsigned int message;
    unsigned int count;
};

struct PARAM_MESSAGE2 {
    unsigned int message0;
    unsigned int message1;
    unsigned int message2;
    unsigned int message3;
    unsigned int message4;
    unsigned int message5;
    unsigned int message6;
    unsigned int message7;
};

struct PARAM_MENU_YES_NO {
    unsigned int type;
    unsigned int index;
    unsigned int position;
};

struct PARAM_MENU_SAVE {
    unsigned int type;
};

struct PARAM_MESSAGE_WITH_SOUND {
    unsigned int message;
    unsigned int count;
    unsigned int soundNo;
    unsigned int frame;
    unsigned int flag;
    unsigned int automes;
};

struct PARAM_MESSAGE1_SELF_CLOSING {
    unsigned int message;
    unsigned int frame;
};

struct PARAM_SHAKE_MESSAGE {
    unsigned int message;
    unsigned int count;
};

struct PARAM_DELAY_MESSAGE {
    unsigned int message;
    unsigned int frame;
};

struct PARAM_NARRATION_MESSAGE {
    unsigned int message;
    unsigned int count;
};

struct PARAM_NARRATION_MESSAGE2 {
    unsigned int message0;
    unsigned int message1;
    unsigned int message2;
    unsigned int message3;
    unsigned int message4;
    unsigned int message5;
    unsigned int message6;
    unsigned int message7;
};

struct PARAM_SET_MACRO_TARGET_FOR_POSITION {
    unsigned int index;
};

struct PARAM_SET_MACRO_TARGET_WITH_DEATH {
    unsigned int index;
};

struct PARAM_SET_MACRO_M_NAME {
    unsigned int index;
};

struct PARAM_SET_MACRO_SPELL {
    unsigned int magicID;
};

struct PARAM_SET_MACRO_I_NAME {
    unsigned int item;
};

struct PARAM_SET_BASIC_MENU {
    unsigned int menu;
};

struct PARAM_RANDOM_MESSAGE {
    unsigned int count;
    unsigned int message1;
    unsigned int message2;
    unsigned int message3;
    unsigned int message4;
    unsigned int message5;
    unsigned int message6;
    unsigned int message7;
};

struct PARAM_SET_MESSAGE_SOUND {
    unsigned int count;
    unsigned int voice1;
    unsigned int voice2;
    unsigned int voice3;
    unsigned int voice4;
    unsigned int voice5;
    unsigned int voice6;
    unsigned int voice7;
};

struct PARAM_SET_MACRO_TARGET_INDEX {
    unsigned int index;
};
