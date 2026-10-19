/* Campaign map: start-up, drawing, the enemy models, clouds (TkCamp_*, Taku_*). */

#include "common.h"
#include "campaign.h"

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrCampEntryBoard {
    signed char side;               
    signed char done0;              
    signed char done1;              
    signed char seen[57];           
    short started;                  
    short unknown_3e[66];
    short ticks;                    
    short unknown_c4;
    signed char kind[3];            
    signed char byte_c9;            
    unsigned char unknown_ca[332 - 202];
};
extern struct DotrCampEntryBoard D_00299E10_b;
struct DotrCampEntrySpot {
    float x;
    float y;
    float z;
    unsigned char unknown_0c[8];
    short list[8];                  
    short n;                        
    unsigned char unknown_26[14];
};
extern struct DotrCampEntrySpot D_00298BA0_21c510[];
struct DotrCampEntryQuad {
    float f[4];
};
extern struct DotrCampEntryQuad D_0029A790;
extern struct DotrCampEntryQuad D_0029A7A0;
extern signed char D_0034F6F8_21c510;
struct DotrCampEntryRow {
    unsigned short id;
    unsigned short more[5];
};
extern unsigned short D_00299CE0_21c510[];
extern struct DotrCampEntryRow D_00299D00_21c510[];
extern void func_00233F50_b(int mode);
extern void func_00195108_b(void *a, int b);
extern void func_001F3910_b(int a, int b, int c);
extern void func_00217980_b(int n, int b);
extern int func_001F93F0_b(int a, int b, int c, int d);
#define DOTR_CAMP_ENTRY_MODULES() \
    func_001F3910_b(0, 400, 0); \
    func_001F3910_b(0, 401, 0); \
    func_001F3910_b(0, 402, 0); \
    func_001F3910_b(0, 403, 0); \
    func_001F3910_b(0, 404, 0)
#define DOTR_CAMP_ENTRY_CLEAR_SEEN() \
    for (i = 0; i < 32; i++) { \
        board->seen[i] = 0; \
    }

/* Starts the campaign map (`mode` says from where): loads its models, places the castles, the leaders and the
   camera. */
void TkCamp_Init(int mode)
{
    

    struct DotrCampEntryQuad pos;
    struct DotrCampEntryQuad rot;
    CampaignWork *w = &campaignWork;
    struct DotrCampEntryBoard *board = &D_00299E10_b;
    int deck;
    int leader;
    int i;
    int j;
    short r;
    short n;
    short k;
    CampaignWork *p;
    int flag;
    short m;

    campaignMoveDone = 0;
    Taku_Camp_Data_Init();
    Taku_spline_init();
    Taku_Camp_3D_Poly_Init();
    func_00233F50_b(3);
    for (i = 0; i < 2; i++) {
        SzModel_SetDrawFlag(i + 30, 0);
    }
    if (board->done0 != 0 && board->done1 != 0) {
        campaignWork.unk018C = 1;
    } else {
        campaignWork.unk018C = 0;
    }
    Taku_Screen_Init();
    SzGame_SetMenuNum(11, 1);
    campaignWork.nameTable = 2;
    

    switch (mode) {
    case 0:
        func_00195108_b(board, 332);
        SzModel_LoadMerge(3, 4, 0);
        SzText_LoadMerge(10, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 0;
        board->done0 = 0;
        board->done1 = 0;
        campaignWork.unk018C = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 10020;
        board->started = 1;
        func_00233F50_b(3);
        campaignWork.cameraMode = 1;
        D_0034F6F8_21c510 = 0;
        practiceDuelFlag = 0;
        func_00217980_b(24, 0);
        break;
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
        if (SzModel_IsModelLoading(30) == 0) {
            pos = D_0029A790;
            rot = D_0029A7A0;
            deck = SzData_GetCurrentDeck(0);
            leader = SzData_GetLeader(0, deck);
            campaignWork.leaderCard = SzData_GetLeader(0, deck);
            SzModel_SetPos(30, &pos);
            SzModel_SetRot(30, &rot);
            SzModel_Load(30, -1, SzDuel_New2Xax(leader), 1);
        }
        if (campaignWork.unk018C != 0) {
            SzModel_LoadMerge(3, 2, 0);
            func_001F93F0_b(0, 7, 0, 0);
            SzEffect_SetIntensityOnly(7, 1.0f);
            board->done0 = 1;
            board->done1 = 1;
            campaignWork.unk018C = 1;
            board->ticks = 0;
            if (campaignWork.unk018C != 0) {
                p = &campaignWork;
                for (i = 0; i < 32; i++) {
                    p->placeReached[i] = 0;
                    p->placeBlink[i] = 0;
                    board->seen[i] = 3;
                }
                p = &campaignWork;
                
                for (m = 0; m < 2; m++) {
                    for (i = 0; i < 16; i++) {
                        p->routes[m][i].state = 3;
                    }
                }
            }
            board->ticks = 0;
            func_00233F50_b(0);
            campaignWork.cameraMode = 0;
            func_00217980_b(4, 0);
            break;
        }
        flag = 0;
        if (practiceDuelEnd != 0) {
            practiceDuelEnd = 0;
            SzModel_LoadMerge(3, 4, 0);
            SzText_LoadMerge(10, 0);
            if (board->done0 != 0) {
                board->side = 1;
                board->done0 = 1;
                board->done1 = 0;
                campaignWork.unk018C = 0;
            } else if (board->done1 != 0) {
                board->side = 0;
                board->done0 = 0;
                board->done1 = 1;
                campaignWork.unk018C = 0;
            }
            DOTR_CAMP_ENTRY_CLEAR_SEEN();
            board->ticks = 10060;
            board->started = 1;
            func_00233F50_b(3);
            campaignWork.cameraMode = 3;
            func_00217980_b(25, 1);
            flag = 1;
        } else if (board->started != 0) {
            SzModel_LoadMerge(3, 2, 0);
            func_001F93F0_b(0, 7, 0, 0);
            SzEffect_SetIntensityOnly(7, 1.0f);
            if (board->side == 0) {
                

                n = 0;
                board->seen[0] = 1;
                for (j = 1; j <= 11; j++) {
                    if (board->seen[j] == 3) {
                        for (r = 0; r < D_00298BA0_21c510[j].n; r++) {
                            w->routes[0][D_00298BA0_21c510[j].list[r]].state = 3;
                        }
                    }
                }
                for (i = 2; i <= 10; i++) {
                    if (board->seen[i] >= 3) {
                        n++;
                        if (n >= 8) {
                            w->routes[0][12].state = 3;
                            w->routes[0][13].state = 3;
                            w->routes[0][11].state = 3;
                        }
                    }
                }
            } else {
                campaignWork.routes[1][0].state = 3;
                p = &campaignWork;
                
                for (j = 12, n = 1; j <= 21; j++, n++) {
                    if (board->seen[j] == 3) {
                        p->routes[1][n].state = 3;
                    }
                }
                if (board->seen[0] == 3) {
                    campaignWork.routes[1][11].state = 3;
                }
            }
            board->started = 1;
            func_00233F50_b(0);
            campaignWork.cameraMode = 0;
            

            campaignWork.cameraTarget[0] = D_00298BA0_21c510[board->kind[0]].x;
            campaignWork.cameraTarget[1] = 0.0f;
            campaignWork.cameraTarget[2] = D_00298BA0_21c510[board->kind[0]].z;
            campaignWork.cameraTarget[0] = D_00298BA0_21c510[board->kind[1]].x;
            campaignWork.cameraTarget[1] = 0.0f;
            campaignWork.cameraTarget[2] = D_00298BA0_21c510[board->kind[1]].z;
            campaignWork.cameraEye[0] = campaignWork.cameraTarget[0];
            campaignWork.cameraEye[1] = 96.0f + campaignWork.cameraTarget[1];
            campaignWork.cameraEye[2] = 96.0f + campaignWork.cameraTarget[2];
            campaignWork.cameraEye[3] = campaignWork.cameraTarget[3];
            SzView_SetCamera(0, (void *)&campaignWork.cameraEye[0], (void *)&campaignWork.cameraTarget[0]);
            func_00217980_b(4, 0);
        } else {
            SzModel_LoadMerge(3, 4, 0);
            SzText_LoadMerge(10, 0);
            if (board->done0 != 0) {
                board->side = 1;
                board->done0 = 1;
                board->done1 = 0;
                campaignWork.unk018C = 0;
                campaignWork.eventWindowChoice = 0;
                board->byte_c9 = 0;
            } else if (board->done1 != 0) {
                board->side = 0;
                board->done0 = 0;
                board->done1 = 1;
                campaignWork.unk018C = 0;
                campaignWork.eventWindowChoice = 1;
                board->byte_c9 = 2;
            }
            DOTR_CAMP_ENTRY_CLEAR_SEEN();
            board->ticks = 10090;
            board->started = 1;
            func_00233F50_b(3);
            campaignWork.cameraMode = 3;
        }
        DOTR_CAMP_ENTRY_MODULES();
        if (flag == 0) {
            func_00217980_b(26, 0);
        }
        break;
    case 3:
        SzModel_LoadMerge(3, 4, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 0;
        board->done0 = 0;
        board->done1 = 0;
        campaignWork.unk018C = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 10040;
        board->started = 1;
        func_00233F50_b(2);
        func_00217980_b(24, 1);
        break;
    case 20:
        SzModel_LoadMerge(3, 0, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 0;
        board->done0 = 0;
        board->done1 = 0;
        campaignWork.unk018C = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 11182;
        board->started = 1;
        func_00233F50_b(2);
        func_00217980_b(34, 1);
        break;
    case 30:
        SzModel_LoadMerge(3, 0, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 0;
        board->done0 = 0;
        board->done1 = 0;
        campaignWork.unk018C = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 12154;
        board->started = 1;
        func_00233F50_b(2);
        func_00217980_b(38, 1);
        break;
    case 40:
        SzModel_LoadMerge(3, 4, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 0;
        board->done0 = 0;
        board->done1 = 0;
        campaignWork.unk018C = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 11000;
        func_00217980_b(24, 1);
        break;
    case 50:
        SzModel_LoadMerge(3, 4, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 1;
        board->done0 = 0;
        board->done1 = 0;
        campaignWork.unk018C = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 12000;
        func_00217980_b(24, 1);
        break;
    case 60:
        

        campaignWork.startingDeckSet = 0;
        p = &campaignWork;
        for (k = 0; k < 3; k++) {
            p->deckChoices[k] = (D_00299CE0_21c510[w->startingDeckSet] >> (k * 5)) & 0x1f;
            p->deckChoiceCards[k] = D_00299D00_21c510[p->deckChoices[k]].id & 0x3ff;
        }
        SzModel_LoadMerge(3, 4, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 0;
        board->done0 = 0;
        board->done1 = 0;
        campaignWork.unk018C = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 10050;
        board->started = 1;
        func_00233F50_b(2);
        func_00217980_b(25, 1);
        break;
    case 10:
        campaignWork.startingDeckSet = 0;
        p = &campaignWork;
        for (k = 0; k < 3; k++) {
            p->deckChoices[k] = (D_00299CE0_21c510[w->startingDeckSet] >> (k * 5)) & 0x1f;
            p->deckChoiceCards[k] = D_00299D00_21c510[p->deckChoices[k]].id & 0x3ff;
        }
        SzModel_LoadMerge(3, 4, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 0;
        board->done0 = 0;
        board->done1 = 0;
        campaignWork.unk018C = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 10070;
        board->started = 1;
        func_00233F50_b(2);
        func_00217980_b(25, 1);
        break;
    }
}
#undef DOTR_CAMP_ENTRY_MODULES
#undef DOTR_CAMP_ENTRY_CLEAR_SEEN

typedef struct Buffer_0021D480 {
    u32 data[0x3FE8];
} Buffer_0021D480;

typedef struct Entry_0021D480 {
    u16 value;
    u16 other[5];
} Entry_0021D480;

extern u16 campaignDeckChoiceSets[]; /* original: DeckTab */
extern Entry_0021D480 campaignDeckChoices[]; /* original: DeckDat */
extern s8 campaignHelpFlag; /* original: HELP_flg */

/* Sets up the campaign state from the save: the decks, the places, the help flag. */
void Taku_Camp_Data_Init(void) {
    CampaignWork *base = &campaignWork;
    u8 *record = (u8 *)&campaignState;
    f32 groundPoint0[4];
    f32 groundPoint1[4];
    f32 groundPoint2[4];
    s32 i;
    s32 inner;
    s32 k;
    s16 *cell;
    u8 *row;
    s16 *count;
    s16 *block;
    u8 *rows;
    u8 *counts;
    u8 *data;
    s32 outer;
    s16 n;
    s32 total;
    u16 j;
    s32 shift;
    u32 *words;
    u16 *halves;

    func_00195108((s32)base, sizeof(CampaignWork)); /* clears the whole work area */
    groundPoint0[0] = 0.0f;
    groundPoint0[1] = 8.65f;
    groundPoint0[2] = 100.0f;
    groundPoint1[0] = 0.0f;
    groundPoint1[1] = 8.65f;
    groundPoint1[2] = 0.0f;
    groundPoint2[0] = 100.0f;
    groundPoint2[1] = 8.65f;
    groundPoint2[2] = 0.0f;
    Ex3d_GetSurfaceC(groundPoint0, groundPoint1, groundPoint2, campaignWork.groundPlane);
    i = 0;
    do {
        base->nameLetterTable[i] = 0;
        base->nameLetterColumn[i] = 6;
        base->nameLetterRow[i] = 1;
        i++;
    } while (i < 12);
    campaignWork.leaderAlpha = 0x80;
    campaignWork.cursorX = 0x140;
    campaignWork.cursorY = 0xBE;
    *(s16 *)&campaignWork.unk0004 = 0;
    campaignWork.cinemaMode = 0;
    campaignWork.cinemaState = 0;
    campaignWork.cinemaCut[0] = 0;
    campaignWork.eventCutScene = *(s16 *)(record + 0xC2);
    campaignWork.eventStep = 0;
    campaignWork.unk5372 = 0;
    campaignWork.unk006E = 0;
    campaignWork.cameraTarget[0] = 0.0f;
    campaignWork.cameraTarget[1] = 0.0f;
    campaignWork.cameraTarget[2] = 0.0f;
    campaignWork.cameraTarget[3] = 0.0f;
    campaignWork.cameraEye[0] = campaignWork.cameraTarget[0];
    campaignWork.cameraEye[1] = 96.0f + campaignWork.cameraTarget[1];
    campaignWork.cameraEye[2] = 96.0f + campaignWork.cameraTarget[2];
    campaignWork.cameraEye[3] = campaignWork.cameraTarget[3];
    SzView_SetCamera(0, (void *)&campaignWork.cameraEye[0], (void *)&campaignWork.cameraTarget[0]);

    i = 0;
    words = (u32 *)&campaignWork; /* this loop clears placeScreenX[i] and placeScreenY[i] */
    do {
        words[0x8C / 4] = 0;
        words[0x10C / 4] = 0;
        words++;
        i++;
    } while (i < 32);
    campaignWork.shipT = 0;
    campaignWork.unk01AE = 0;
    campaignWork.shipPoint = 0;
    campaignWork.shipTo = 0;
    campaignWork.windowAlpha[0] = 0x80;
    rows = (u8 *)&campaignWork;
    campaignWork.windowAlpha[1] = 0x80;
    campaignWork.windowAlpha[2] = 0x80;
    outer = 0; /* these loops clear every route's state, routeDrawn and routePointRise */
    counts = (u8 *)&campaignWork;
    data = (u8 *)&campaignWork;
    do {
        inner = 0;
        row = rows;
        count = (s16 *)counts;
        block = (s16 *)data;
        do {
            *(s16 *)(row + 0x42E) = 0;
            count[0x42AC / 2] = 0;
            k = 0;
            cell = block;
            do {
                k++;
                cell[0x42EC / 2] = 0;
                cell++;
            } while (k < 64);
            inner++;
            row += 0x204;
            count++;
            block += 64;
        } while (inner < 16);
        outer++;
        rows += 0x2040;
        counts += 0x20;
        data += 0x800;
    } while (outer < 2);
    {
        u16 *clear;
        s32 clear_count = 0;
        clear = (u16 *)&campaignWork; /* clears placeReached[i] and placeBlink[i] */
        do {
            clear_count++;
            clear[0x52EC / 2] = 0;
            clear[0x532C / 2] = 0;
            clear++;
        } while (clear_count < 32);
    }

    if (campaignHelpFlag != 0) {
        *(Buffer_0021D480 *)SzData_GetData(0) = *(Buffer_0021D480 *)GAME_DATA_COPY_ADDR;
        campaignHelpFlag = 0;
    }
    n = 0;
    total = 0;
    for (; n < 12; n++) {
        total += (s32)*(u16 *)(record + 0x24) % 16;
        record += 2;
    }
    campaignWork.startingDeckSet = total & 0xF;
    j = 0;
    shift = 0;
    halves = (u16 *)&campaignWork; /* halves[0x53F8 / 2] is deckChoices[j], halves[0x53FE / 2] deckChoiceCards[j] */
    for (; j < 3; j++) {
        halves[0x53F8 / 2] = ((s32)campaignDeckChoiceSets[base->startingDeckSet] >> shift) & 0x1F;
        shift += 5;
        halves[0x53FE / 2] = campaignDeckChoices[halves[0x53F8 / 2]].value & 0x3FF;
        halves++;
    }
}

typedef struct Coord_0021D850 {
    f32 x;
    f32 y;
    f32 z;
} Coord_0021D850;

extern u8 campaignPlaces[]; /* original: model_data */
extern u8 D_00298BA8[];
extern s8 D_00299ED6;
extern s8 D_00299ED7;
extern u8 campaignCoord; /* original: prim_data */

/* Points the camera at the current place and works out every place's screen position. */
void Taku_Screen_Init(void) {
    s16 place;
    u8 *placeData;
    s32 *screen;
    Coord_0021D850 pos;

    Taku_Coord_Set(&campaignCoord);
    campaignWork.cameraTarget[0] = *(f32 *)(campaignPlaces + D_00299ED6 * 0x34);
    campaignWork.cameraTarget[1] = 0.0f;
    campaignWork.cameraTarget[2] = *(f32 *)(D_00298BA8 + D_00299ED6 * 0x34);
    campaignWork.cameraTarget[0] = *(f32 *)(campaignPlaces + D_00299ED7 * 0x34);
    campaignWork.cameraTarget[1] = 0.0f;
    campaignWork.cameraTarget[2] = *(f32 *)(D_00298BA8 + D_00299ED7 * 0x34);
    campaignWork.cameraEye[0] = campaignWork.cameraTarget[0];
    campaignWork.cameraEye[1] = 96.0f + campaignWork.cameraTarget[1];
    campaignWork.cameraEye[2] = 96.0f + campaignWork.cameraTarget[2];
    campaignWork.cameraEye[3] = campaignWork.cameraTarget[3];
    SzView_SetCamera(0, (void *)&campaignWork.cameraEye[0], (void *)&campaignWork.cameraTarget[0]);
    placeData = campaignPlaces;
    place = 0;
    screen = (s32 *)&campaignWork; /* screen + 0x8C / 0x10C below are placeScreenX[place] and placeScreenY[place] */
    while (place <= 0x15) {
        pos.x = *(f32 *)placeData;
        pos.y = 8.65f + *(f32 *)(placeData + 4);
        pos.z = *(f32 *)(placeData + 8);
        Taku_3D_2D_Set((s32 *)((u8 *)screen + 0x8C), (s32 *)((u8 *)screen + 0x10C), (s32)&pos);
        placeData += 0x34;
        screen++;
        place++;
    }
    campaignWork.cursorX = 0x140;
    campaignWork.cursorY = 0xBE;
}

/* Draws the campaign map's 3D layer: the map, the clouds, the stone. */
void TkCamp_Draw(void) {
    if (campaignMoveDone == 0) {
        RhBase_SetVifPacketArea(TkCamp_Draw_Pipe(RhBase_GetVifPacketArea()));
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec4_0021DAA0;

extern s16 teki_a_seru;
extern s16 D_00298AD2;
extern s16 D_00298AD4;
extern s16 D_00298ADA;
extern Vec4_0021DAA0 D_0029A7B0;
extern Vec4_0021DAA0 D_0029A7C0;

/* A screen y moved by the scroll. */
static inline s32 offset_y_0021DAA0(s32 y) {
    return (s16)y - 0x100;
}

/* Draws the campaign map's 2D layer: the windows, the opponent's model in its window, the won card. */
void TkCamp_Draw_After(void) {
    extern void *Taku_G4_Set(void *, void *, s16, s16);
    Vec4_0021DAA0 sp80;
    Vec4_0021DAA0 sp90;
    s8 *state;
    s16 angle;
    s16 x_offset;
    s16 y_offset;
    s32 temp_s4;
    s32 temp_s5;
    s16 temp_v0;
    s16 temp_v0_2;
    s8 temp_a1;
    void *var_s6;

    state = &campaignState;
    angle = ((campaignWork.unk5478 << 10) >> 12) - 0x200;
    if (campaignMoveDone == 0) {
        var_s6 = Taku_Camp_2D(RhBase_GetVifPacketArea());
        temp_v0 = campaignWork.windowOpen;
        if (temp_v0 != 0) {
            temp_a1 = campaignWork.unk5440;
            y_offset = offset_y_0021DAA0(temp_v0);
            x_offset = (temp_a1 * -0x280) / 100;
            if (campaignWork.unk5488 != 0) {
                var_s6 = Taku_G4_Set(var_s6, &teki_a_seru, x_offset, y_offset);
                campaignWork.unk5488 = 0;
            }
            if (SzModel_IsModelLoading(0x1F) == 0) {
                if ((campaignWork.unk5406 == 1) && (campaignWork.windowOpen != 0)) {
                    sp80 = D_0029A7B0;
                    sp90 = D_0029A7C0;
                    campaignWork.leaderCard = SzData_GetLeader(1, 0);
                    SzModel_SetPos(0x1F, &sp80);
                    SzModel_SetRot(0x1F, &sp90);
                    SzModel_Load(0x1F, -1, SzDuel_New2Xax(campaignWork.leaderCard), 1);
                    campaignWork.unk5406 = 2;
                    campaignWork.unk543A = 0;
                }
            }
            if ((SzModel_IsModelStandby(0x1F) != 0) && (campaignWork.unk5406 == 2)) {
                temp_v0_2 = campaignWork.unk543A;
                if (temp_v0_2 < 0x80) {
                    campaignWork.unk543A = temp_v0_2 + 8;
                }
                if (campaignWork.unk543A >= 0x80) {
                    campaignWork.unk543A = 0x80;
                }
                temp_s4 = D_00298AD2;
                temp_s5 = teki_a_seru;
                var_s6 = Taku_Camp_EnemyModel_Disp(var_s6, 0x1F, temp_s5 + x_offset,
                    temp_s4 + y_offset, (f32)SzDuel_GetCamDist(campaignWork.leaderCard),
                    D_00298AD4 - temp_s5, D_00298ADA - temp_s4, campaignWork.unk543A);
            }
        }
        if (campaignWork.unk5472 != 0) {
            var_s6 = Taku_Camp_Card_Get(var_s6, (f32)angle, *state ^ 1, 0.0f, campaignWork.unk5474);
        }
        campaignWork.unk5481 = 0;
        RhBase_SetVifPacketArea((s32) var_s6);
    }
}

/* Draws the campaign map into the packet. */
s32 TkCamp_Draw_Pipe(s32 packet) {
    extern s16 D_00299ED2;
    extern s32 Taku_Camp_3D();
    extern s32 Taku_Camp_Clouds();
    u8 *rec;
    s32 v;

    rec = (u8 *)&campaignState;
    if (D_00299ED2 >= 0x2710) {
        v = *(s16 *)(rec + 0xC2);
        switch (v) {
        case 0x2B98:
            if (campaignWork.eventStep < 2) {
                packet = Taku_Camp_3D(packet);
            } else {
                packet = Taku_Camp_STONE(packet);
            }
            break;
        case 0x2B9A:
            if (campaignWork.eventStep >= 9) {
                packet = Taku_Camp_3D(packet);
            } else {
                packet = Taku_Camp_STONE(packet);
            }
            break;
        case 0x2BAC:
            if (campaignWork.eventStep >= 2) {
                packet = Taku_Camp_STONE(packet);
            } else {
                packet = Taku_Camp_3D(packet);
            }
            break;
        case 0x2F64:
            if (campaignWork.eventStep < 0xA) {
                packet = Taku_Camp_STONE(packet);
            } else {
                packet = Taku_Camp_3D(packet);
            }
            break;
        case 0x2F76:
            if (campaignWork.eventStep > 1) {
                packet = Taku_Camp_STONE(packet);
            } else {
                packet = Taku_Camp_3D(packet);
            }
            break;
        case 0x2AF8:
        case 0x2BAE:
        case 0x2BB0:
        case 0x2EE0:
        case 0x2F62:
        case 0x2F78:
        case 0x2F7A:
        case 0x2F7C:
            packet = Taku_Camp_STONE(packet);
            break;
        default:
            if (v < 0x2AF8) {
                packet = Taku_Camp_STONE(packet);
            } else {
                packet = Taku_Camp_3D(packet);
            }
            break;
        }
    } else {
        packet = Taku_Camp_3D(packet);
    }
    if (*(s16 *)(rec + 0xC2) >= 0x2710) {
        packet = Taku_Camp_Clouds(packet);
    }
    return packet;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_0021DFF0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_0021DFF0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_0021DFF0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_0021DFF0;

typedef struct {
    u64 tag[2];
    Color_0021DFF0 color;
    u64 uv0;
    Vertex_0021DFF0 vertex0;
    u64 uv1;
    Vertex_0021DFF0 vertex1;
    u64 test;
    s64 texture0;
    s64 texture1;
    u64 clamp;
} Packet_0021DFF0;

typedef struct {
    u8 pad00[0x40];
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;
    u8 pad4C[4];
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    u8 pad5C[0x24];
    s32 roll;
    u8 pad84[0xC];
} View_0021DFF0;

/* Sets a sprite corner's texture coordinates. */
static inline void set_uv_0021DFF0(UV_0021DFF0 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_0021DFF0;

/* Draws the opponent's (teki) model `id` rendered into a texture at (x, y), w x h, with `alpha`. (original: Taku_Camp_Teki_Model_Disp) */
void *Taku_Camp_EnemyModel_Disp(void *packet, s32 id, s32 x, s32 y, f32 depth, s32 width, s32 height, s32 alpha) {
    extern s32 RhBase_AssignRenderFrame(s32, s32, s32);
    View_0021DFF0 view;
    Vec4_0021DFF0 position;
    Packet_0021DFF0 sprite __attribute__((aligned(8)));
    s32 output;
    s32 half;

    x -= 0x140;
    y -= 0xE0;
    ((Tag_0021DFF0 *)sprite.tag)->flags = 0x26;
    ((Tag_0021DFF0 *)sprite.tag)->count = 5;
    ((Tag_0021DFF0 *)sprite.tag)->registers = 0x42421;
    ((Tag_0021DFF0 *)sprite.tag)->padding = 0;
    ((Tag_0021DFF0 *)sprite.tag)->flags |= 0x800;
    ExAssignAlpha(sprite.tag, 0x44 | ((s64)0x80 << 32));
    sprite.color.r = 0x80;
    sprite.color.g = 0x80;
    sprite.color.b = 0x80;
    sprite.color.a = alpha;
    sprite.color.q = 1.0f;
    sprite.vertex0.z = 0xFFFFFA;
    sprite.vertex0.fog = 0;
    sprite.vertex1.z = 0xFFFFFA;
    sprite.vertex1.fog = 0;
    RhView_GetCurView(&view);
    if (RhView_PushStack() != 0) {
        RhBase_AssignRenderFrame(0, 0xA, 0x31);
        packet = RhBase_EnableRenderFrame(packet);
        packet = RhBase_ClearRenderFrame(packet, 0);
        SzModel_GetCenter(id, &position);
        view.eyeX = 0.0f;
        view.eyeY = position.y;
        view.eyeZ = -depth;
        view.targetX = 0.0f;
        view.targetY = 0.0f;
        view.targetZ = 1.0f;
        view.roll = 0;
        RhView_SetClipZ(1.0f, 512.0f);
        RhView_Modify(&view);
        packet = (void *)RhView_SendViewParameters((s32)packet);
        SzModel_SetDrawFlag(id, 1);
        packet = (void *)SzModel_Draw_Pipe((s32)packet, id, 0, 0, 0, 0, 0);
        SzModel_Motion(id);
        SzModel_SetDrawFlag(id, 0);
        RhBase_GetTextureInfoForRender(&sprite.texture0, &sprite.texture1);
        output = RhText_SetTextureFlush((s32)RhBase_DisableRenderFrame(packet));
        half = ((width * 448) / height) >> 1;
        set_uv_0021DFF0((UV_0021DFF0 *)&sprite.uv0, (0x140 - half) << 4, 0);
        set_uv_0021DFF0((UV_0021DFF0 *)&sprite.uv1, (half + 0x140) << 4, 0x1C0 << 4);
        sprite.vertex0.x = (x + 0x800) << 4;
        sprite.vertex0.y = (y + 0x800) << 4;
        sprite.vertex1.x = (x + 0x800 + width) << 4;
        sprite.vertex1.y = (y + 0x800 + height) << 4;
        RhView_PopStack();
        RhView_GetCurView(&view);
        RhView_Modify(&view);
        packet = (void *)ExSortPrim_Pipe(RhView_SendViewParameters(output), (s32)&sprite, 0, 0);
        RhBase_FreeRenderFrame();
    }
    return packet;
}

#include "game.h"
#include "m2c_macros.h"

extern s16 D_00298C32;
extern s16 D_00298CD0;
extern f32 D_00298D0C;
extern f32 D_00298D14;
extern s16 D_00298D6A;
extern f32 D_00298DDC;
extern f32 D_00298DE4;
extern s16 D_00299ED2;

/* Runs the campaign's events (ivent): the script of each place's story, the duels it starts and what they unlock. (original: Taku_Camp_Ivent) */
void Taku_Camp_Event(void) {
    u8 *ctx = (u8 *)&campaignState;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_a1_3;
    s16 temp_a1_4;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_a2_3;
    s16 temp_a2_4;
    s16 temp_a2_5;
    s16 temp_a2_6;
    s16 temp_a2_7;
    s16 temp_a2_8;
    s16 temp_a2_9;
    s16 temp_v1;
    s16 temp_v1_10;
    s16 temp_v1_11;
    s16 temp_v1_12;
    s16 temp_v1_13;
    s16 temp_v1_14;
    s16 temp_v1_15;
    s16 temp_v1_16;
    s16 temp_v1_17;
    s16 temp_v1_18;
    s16 temp_v1_19;
    s16 temp_v1_20;
    s16 temp_v1_21;
    s16 temp_v1_22;
    s16 temp_v1_23;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 temp_v1_5;
    s16 temp_v1_6;
    s16 temp_v1_7;
    s16 temp_v1_8;
    s16 temp_v1_9;

    switch (D_00299ED2) {
        case 0x2724:                                /* switch 2 */
            temp_v1 = campaignWork.eventStep;
            switch (temp_v1) {                      /* switch 3 */
            case 0:                                 /* switch 3 */
                func_001F48F0(0, 0x190, 0, 0, 0);
                func_00217980(0x18, 1);
                campaignWork.cameraTarget[0] = 0;
                campaignWork.cameraTarget[2] = 0;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.cameraMode = 1;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0x1000;
                campaignWork.cloudState = 1;
                campaignWork.cloudCover = 0x1000;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.unk53B4 = 0;
                campaignWork.unk53B5 = 0;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.unk546C = 0;
                campaignWork.unk546D = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 3 */
                if (campaignWork.cinemaState == 2) {
                    campaignWork.talkStep = 1;
                    campaignWork.talkPage = 1;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            default:                                /* switch 3 */
dflt_3:
                goto end_0021E330;
            case 2:                                 /* switch 3 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.cloudState = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 3:                                 /* switch 3 */
                campaignWork.zoomMove = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 4:                                 /* switch 3 */
                campaignWork.cloudState = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 5:                                 /* switch 3 */
                if (campaignWork.zoom < 0x7D0) {
                    if (campaignWork.unk546C == 0) {
                        func_00217980(0x19, 0);
                        campaignWork.unk546C = 1;
                    }
                }
                if (campaignWork.zoom < 0x50) {
                    campaignWork.cloudState = 0xA;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 6:                                 /* switch 3 */
                if (campaignWork.cloudState == 0xB) {
                    (*(s16 *)(ctx + 0xC2)) = 0x2738;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x2738:                                /* switch 2 */
            temp_v1_2 = campaignWork.eventStep;
            switch (temp_v1_2) {                    /* switch 4 */
            case 0:                                 /* switch 4 */
                func_001F48F0(0, 0x191, 0, 0, 0);
                campaignWork.cameraTarget[0] = 0;
                campaignWork.cameraTarget[2] = 0;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
                func_00233F50(2);
                campaignWork.cameraMode = 2;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0x1000;
                campaignWork.cloudState = 0x14;
                campaignWork.cloudCover = 0x1000;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.unk546C = 0;
                campaignWork.eventPictureZoom = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 4 */
                if (campaignWork.cloudState == 0x15) {
                    func_00217710(0, 0x22);
                    func_00217710(0, 0x23);
                    campaignWork.zoomMove = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 4 */
                if (campaignWork.zoomMove == 0) {
                    campaignWork.cloudState = 0x1E;
                    campaignWork.cloudCover = 0;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 3:                                 /* switch 4 */
                if (campaignWork.cloudState == 0x1F) {
                    campaignWork.cloudState = 0x20;
                    campaignWork.cloudCover = 0x1000;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 4:                                 /* switch 4 */
                if (campaignWork.cloudState == 0x21) {
                    func_00217980(0x19, 1);
                    campaignWork.talkStep = 1;
                    campaignWork.talkPage = 1;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 5:                                 /* switch 4 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0xD;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 6:                                 /* switch 4 */
                if (campaignWork.talkStep == 0xE) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 0;
                    campaignWork.cameraMode = 3;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 7:                                 /* switch 4 */
                if (campaignWork.cinemaState == 2) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventWindowState = 1;
                    campaignWork.eventWindowOpen = 0;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 8:                                 /* switch 4 */
                if (campaignWork.eventWindowState == 4) {
                    campaignWork.eventWindowState = 0;
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.cameraMode = 3;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 9:                                 /* switch 4 */
                if (campaignWork.cinemaState == 2) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventWindowState = 0;
                    campaignWork.eventWindowOpen = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2739;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            default:                                    /* switch 4 */
                goto dflt_3;
            }
            break;
        case 0x2739:                                /* switch 2 */
            temp_a0 = campaignWork.eventStep;
            switch (temp_a0) {                      /* switch 5; irregular */
            case 0:                                 /* switch 5 */
                func_00233F50(2);
                campaignWork.cameraMode = 3;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventPictureZoom = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 5 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventWindowState = 0;
                    campaignWork.eventWindowOpen = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2742;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x2742:                                /* switch 2 */
            temp_v1_3 = campaignWork.eventStep;
            switch (temp_v1_3) {                    /* switch 6; irregular */
            case 0:                                 /* switch 6 */
                func_00233F50(2);
                campaignWork.cameraMode = 3;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 6 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventWindowState = 1;
                    campaignWork.eventWindowOpen = 0;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 6 */
                if (campaignWork.eventWindowState == 4) {
                    campaignWork.eventWindowState = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x274C;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x274C:                                /* switch 2 */
            temp_v1_4 = campaignWork.eventStep;
            switch (temp_v1_4) {                    /* switch 7; irregular */
            case 0:                                 /* switch 7 */
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.cameraMode = 3;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 7 */
                if (campaignWork.cinemaState == 2) {
                    campaignWork.talkStep = 1;
                    campaignWork.talkPage = 1;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 7 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2756;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x2756:                                /* switch 2 */
            temp_v1_5 = campaignWork.eventStep;
            switch (temp_v1_5) {                    /* switch 8; irregular */
            case 0:                                 /* switch 8 */
                func_00233F50(2);
                campaignWork.cameraMode = 3;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.deckShowPhase = 0;
                campaignWork.deckShowDone = 0;
                campaignWork.deckCardSlide[0] = 0;
                campaignWork.deckCardSlide[1] = -0x64;
                campaignWork.deckCardSlide[2] = -0xC8;
                campaignWork.deckShowSound[0] = 0;
                campaignWork.deckShowSound[1] = 0;
                campaignWork.deckShowSound[2] = 0;
                campaignWork.eventWindowChoice = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 8 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventWindowState = 1;
                    campaignWork.eventWindowOpen = 0;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 8 */
                if (campaignWork.eventWindowState == 4) {
                    campaignWork.eventWindowState = 4;
                    (*(s16 *)(ctx + 0xC2)) = 0x2757;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
    case 0x2757:
        temp_a0_2 = campaignWork.eventStep;
        switch (temp_a0_2) {
        case 0:
            func_00233F50(2);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 4;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2760;
                campaignWork.eventStep = 0;
                func_00217980(0x1A, 0);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2760:                                    /* switch 1 */
        temp_v1_6 = campaignWork.eventStep;
        switch (temp_v1_6) {                        /* switch 9; irregular */
        case 0:                                     /* switch 9 */
            func_00233F50(2);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.unk546D = 0;
            campaignWork.unk546C = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 9 */
            if (campaignWork.talkPage == 3) {
                if ((campaignWork.talkStep == 5) && (campaignWork.unk546C == 0)) {
                    func_00217980(0x1A, 1);
                    campaignWork.unk546C = 1;
                }
            }
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowChoice = 1;
                (*(s16 *)(ctx + 0xC2)) = 0x276A;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x276A:                                    /* switch 1 */
        temp_a2 = campaignWork.eventStep;
        switch (temp_a2) {                          /* switch 10; irregular */
        case 0:                                     /* switch 10 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            func_00217980(0x1A, 1);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            func_00217980(0x1A, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 10 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 10 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowState = 1;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 10 */
            if (campaignWork.eventWindowState == 4) {
                campaignWork.eventWindowState = 0;
                if (campaignWork.eventWindowChoice == 0) {
                    (*(s8 *)(ctx + 0)) = 1;
                    (*(s16 *)(ctx + 0xC2)) = 0x2EE0;
                    (*(s8 *)(ctx + 0xC9)) = 2;
                } else {
                    (*(s8 *)(ctx + 0)) = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2AF8;
                    (*(s8 *)(ctx + 0xC9)) = 0;
                }
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2AF8:                                    /* switch 1 */
        temp_a1 = campaignWork.eventStep;
        switch (temp_a1) {                          /* switch 11; irregular */
        case 0:                                     /* switch 11 */
            func_00233F50(2);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 11 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 11 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cloudState = 0x16;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 11 */
            if (campaignWork.cloudState == 0x17) {
                func_00233F50(3);
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                func_001E7F70(3, 2, 0);
                func_001F93F0(0, 7, 0, NULL);
                func_001F6E80(7, 1.0f);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 11 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 0;
                campaignWork.cameraTarget[0] = D_00298DDC;
                campaignWork.cameraTarget[2] = D_00298DE4;
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x64;
                func_00217980(4, 1);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B02:
        break;
    case 0x2B0C:                                    /* switch 1 */
        temp_v1_7 = campaignWork.eventStep;
        switch (temp_v1_7) {                        /* switch 12 */
        case 0:                                     /* switch 12 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureState = 1;
            campaignWork.eventPictureZoom = 0;
            func_00217980(0x1B, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 12 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureX = (s16) (campaignWork.eventPictureX - 4);
                if (campaignWork.eventPictureX < -0x280) {
                    campaignWork.eventPictureX = -0x280;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 12 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 12 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 12 */
            if (campaignWork.talkStep == 0xE) {
                func_00217980(4, 0);
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 12 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x65;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 12 */
            goto dflt_3;
        }
        break;
    case 0x2B70:                                    /* switch 1 */
        temp_v1_8 = campaignWork.eventStep;
        switch (temp_v1_8) {                        /* switch 13; irregular */
        case 0:                                     /* switch 13 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk5483 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            func_00217980(0x1C, 0);
            goto end_0021E330;
        case 1:                                     /* switch 13 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.unk5483 = 1;
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 13 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.unk5483 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 13 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B72;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B72:                                    /* switch 1 */
        temp_a2_2 = campaignWork.eventStep;
        switch (temp_a2_2) {                        /* switch 14; irregular */
        case 0:                                     /* switch 14 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = -0x1C0;
            campaignWork.eventPictureState = 1;
            func_00217980(0x1C, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 14 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureY = (s16) (campaignWork.eventPictureY + 4);
                if (campaignWork.eventPictureY > -0x50) {
                    campaignWork.eventPictureY = -0x50;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 14 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 14 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 14 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B74;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B74:                                    /* switch 1 */
        temp_a2_3 = campaignWork.eventStep;
        switch (temp_a2_3) {                        /* switch 15; irregular */
        case 0:                                     /* switch 15 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.cameraTarget[0] = D_00298D0C;
            campaignWork.cameraTarget[2] = D_00298D14;
            campaignWork.placeReached[7] = 0;
            campaignWork.unk5483 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 15 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.unk5483 = 1;
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 15 */
            if (campaignWork.talkStep == 0xC) {
                func_00217980(4, 0);
                campaignWork.unk5483 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 15 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.routes[0][12].state = D_00298C32;
                campaignWork.routes[0][13].state = D_00298CD0;
                campaignWork.routes[0][11].state = D_00298D6A;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 15 */
            if (campaignWork.placeReached[7] == 1) {
                (*(s16 *)(ctx + 0xC2)) = 0;
                campaignWork.eventStep = 0;
                campaignWork.unk5374 = 0;
                campaignWork.unk5375 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 0;
                campaignWork.leaderShow = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B84:                                    /* switch 1 */
        temp_v1_9 = campaignWork.eventStep;
        switch (temp_v1_9) {                        /* switch 16 */
        case 0:                                     /* switch 16 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureZoom = 0;
            campaignWork.unk546C = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 16 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 16 */
            if (campaignWork.talkPage == 4) {
                if (campaignWork.unk546C == 0) {
                    func_00217980(0x1D, 0);
                    campaignWork.unk546C = 1;
                }
            }
            if (campaignWork.talkPage == 6) {
                if (campaignWork.unk546C < 2) {
                    func_00217980(0x1D, 1);
                    campaignWork.unk546C = 2;
                }
            }
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 16 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 16 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 16 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B86;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 16 */
            goto dflt_3;
        }
        break;
    case 0x2B86:                                    /* switch 1 */
        temp_a2_4 = campaignWork.eventStep;
        switch (temp_a2_4) {                        /* switch 17; irregular */
        case 0:                                     /* switch 17 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureState = 1;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 17 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureY = (s16) (campaignWork.eventPictureY - 4);
                if (campaignWork.eventPictureY < -0x1C0) {
                    campaignWork.eventPictureY = -0x1C0;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 17 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 17 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 17 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B87;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                func_00217980(0x1E, 0);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B87:                                    /* switch 1 */
        temp_v1_10 = campaignWork.eventStep;
        switch (temp_v1_10) {                       /* switch 18; irregular */
        case 0:                                     /* switch 18 */
            func_00233F50(3);
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 18 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2B88;
                campaignWork.eventStep = 0;
                func_00217980(0x1E, 1);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B88:                                    /* switch 1 */
        temp_v1_11 = campaignWork.eventStep;
        switch (temp_v1_11) {                       /* switch 19 */
        case 0:                                     /* switch 19 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureState = 1;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 19 */
            if (campaignWork.cinemaState == 2) {
                if (campaignWork.eventPictureState < 3) {
                    campaignWork.eventPictureState = 2;
                    campaignWork.talkSpeaker = 2;
                }
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 19 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 19 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 1;
                campaignWork.eventPictureState = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 19 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureFade = 1;
                campaignWork.eventPictureAlpha = 0x80;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 19 */
            if (campaignWork.eventPictureFade == 0xA) {
                if (campaignWork.eventPictureState < 3) {
                    campaignWork.eventPictureState = 2;
                    campaignWork.talkSpeaker = 2;
                }
            }
            if (campaignWork.eventPictureState == 3) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 19 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B8A;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                campaignWork.eventPictureAlpha = 0x80;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 19 */
            goto dflt_3;
        }
        break;
    case 0x2B8A:                                    /* switch 1 */
        temp_a2_5 = campaignWork.eventStep;
        switch (temp_a2_5) {                        /* switch 20; irregular */
        case 0:                                     /* switch 20 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureState = 1;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 20 */
            if (campaignWork.cinemaState == 2) {
                if (campaignWork.eventPictureState < 3) {
                    campaignWork.eventPictureState = 2;
                    campaignWork.talkSpeaker = 2;
                }
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 20 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 20 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 20 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B8B;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B8B:                                    /* switch 1 */
        temp_a0_2 = campaignWork.eventStep;
        switch (temp_a0_2) {                        /* switch 21; irregular */
        case 0:                                     /* switch 21 */
            func_00233F50(3);
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 21 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2B8C;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B8C:                                    /* switch 1 */
        temp_a2_6 = campaignWork.eventStep;
        switch (temp_a2_6) {                        /* switch 22; irregular */
        case 0:                                     /* switch 22 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk5483 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 22 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 22 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 22 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                (*(s16 *)(ctx + 0xC2)) = (s16) ((*(s16 *)(ctx + 0xC2)) + 1);
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 22 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x6C;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B8D:                                    /* switch 1 */
        temp_v1_12 = campaignWork.eventStep;
        switch (temp_v1_12) {                       /* switch 23; irregular */
        case 0:                                     /* switch 23 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk5483 = 1;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 23 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.unk5483 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                func_00217980(4, 0);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 23 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x6C;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B98:                                    /* switch 1 */
        temp_v1_13 = campaignWork.eventStep;
        switch (temp_v1_13) {                       /* switch 24 */
        case 0:                                     /* switch 24 */
            func_00217980(0x1F, 0);
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 3;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk546C = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 24 */
            if (campaignWork.cinemaState == 2) {
                func_001E7F70(3, 0, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 24 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 3;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 24 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 24 */
            if (campaignWork.talkPage == 3) {
                if (campaignWork.unk546C == 0) {
                    func_00217980(0x1F, 1);
                    campaignWork.unk546C = 1;
                }
            }
            if (campaignWork.talkPage == 0xD) {
                if (campaignWork.unk546C < 2) {
                    func_00217980(0x20, 1);
                    campaignWork.unk546C = 2;
                    campaignWork.unk547F = 1;
                    campaignWork.unk5480 = 0;
                }
            }
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 24 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 24 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B9A;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 24 */
            goto dflt_3;
        }
        break;
    case 0x2B9A:                                    /* switch 1 */
        temp_v1_14 = campaignWork.eventStep;
        switch (temp_v1_14) {                       /* switch 25 */
        case 0:                                     /* switch 25 */
            func_001F48F0(0, 0x191, 0, 0, 0);
            campaignWork.cameraTarget[0] = 0;
            campaignWork.cameraTarget[2] = 0;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 2;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0x1000;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk546E = 0;
            campaignWork.unk5470 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 25 */
            if (campaignWork.cinemaState == 2) {
                func_00217710(0, 0x22);
                func_00217710(0, 0x23);
                campaignWork.zoomMove = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 25 */
            if (campaignWork.zoomMove == 0) {
                campaignWork.cloudState = 0x1E;
                campaignWork.cloudCover = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 25 */
            if (campaignWork.cloudState == 0x1F) {
                campaignWork.cloudState = 0x20;
                campaignWork.cloudCover = 0x1000;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 25 */
            if (campaignWork.cloudState == 0x21) {
                campaignWork.eventPictureZoom = (s8) (campaignWork.eventPictureZoom - 4);
                if (campaignWork.eventPictureZoom < -0x63) {
                    campaignWork.eventPictureZoom = -0x64;
                    campaignWork.unk546E = 1;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 5:                                     /* switch 25 */
            if ((campaignWork.unk546E == 5) && (campaignWork.unk547F == 4)) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                func_00217980(0x21, 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 25 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 7:                                     /* switch 25 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                func_00217980(4, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 8:                                     /* switch 25 */
            if (campaignWork.cinemaState == 2) {
                func_001E7F70(3, 2, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 9:                                     /* switch 25 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                (*(s8 *)(ctx + 0xC9)) = 1;
                campaignWork.cameraTarget[0] = D_00298DDC;
                campaignWork.cameraTarget[2] = D_00298DE4;
                goto end_0021E330;
            }
            break;
        case 10:                                    /* switch 25 */
            if (campaignWork.cinemaState == 2) {
                (*(s8 *)(ctx + 0xC9)) = 1;
                campaignWork.cameraTarget[0] = D_00298DDC;
                campaignWork.cameraTarget[2] = D_00298DE4;
                (*(s16 *)(ctx + 0xC2)) = 0x70;
                campaignWork.eventStep = 0;
                campaignWork.unk5374 = 1;
                campaignWork.unk5375 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 0;
                campaignWork.leaderShow = 0;
                campaignWork.unk546C = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 25 */
            goto dflt_3;
        }
        break;
    case 0x2BAC:                                    /* switch 1 */
        temp_v1_15 = campaignWork.eventStep;
        switch (temp_v1_15) {                       /* switch 26 */
        case 0:                                     /* switch 26 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 3;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk546E = 0;
            campaignWork.unk5470 = 0;
            campaignWork.unk547F = 0;
            campaignWork.unk5480 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 26 */
            if (campaignWork.cinemaState == 2) {
                func_001E7F70(3, 0, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 26 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 3;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 26 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 26 */
            if (campaignWork.talkPage == 3) {
                if ((campaignWork.talkStep == 3) && (campaignWork.unk546E == 0) && (campaignWork.eventPictureZoom < -0x63)) {
                    campaignWork.unk546E = 1;
                    campaignWork.unk5470 = 0;
                    campaignWork.unk547F = 1;
                }
            }
            if ((campaignWork.talkStep == 0xC) && (campaignWork.unk546E == 5) && (campaignWork.unk547F == 4)) {
                campaignWork.talkStep = 0xD;
                campaignWork.unk547F = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 26 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.unk546E = 0;
                campaignWork.unk5470 = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 26 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2BAE;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 26 */
            goto dflt_3;
        }
        break;
    case 0x2BAE:                                    /* switch 1 */
        temp_v1_16 = campaignWork.eventStep;
        switch (temp_v1_16) {                       /* switch 27 */
        case 0:                                     /* switch 27 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = -0x180;
            campaignWork.eventPictureState = 1;
            func_00217980(0x22, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 27 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureX = (s16) (campaignWork.eventPictureX - 2);
                if (campaignWork.eventPictureX < -0xC0) {
                    campaignWork.eventPictureX = -0xC0;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                temp_a1_2 = campaignWork.eventPictureX;
                campaignWork.eventPictureY = (-temp_a1_2 * 0x180) / 384 - 0x180;
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 27 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 27 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 1;
                campaignWork.eventPictureState = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 27 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureX = (s16) (campaignWork.eventPictureX - 2);
                if (campaignWork.eventPictureX < -0x180) {
                    campaignWork.eventPictureX = -0x180;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                temp_a1_3 = campaignWork.eventPictureX;
                campaignWork.eventPictureY = (-temp_a1_3 * 0x180) / 384 - 0x180;
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 3;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 5:                                     /* switch 27 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2BB0;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 27 */
            goto dflt_3;
        }
        break;
    case 0x2BB0:                                    /* switch 1 */
        temp_v1_17 = campaignWork.eventStep;
        switch (temp_v1_17) {                       /* switch 28; irregular */
        case 0:                                     /* switch 28 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 1;
            campaignWork.cameraTarget[0] = 0;
            campaignWork.cameraTarget[2] = 0;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.zoomMove = 1;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk5447 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto block_534;
        case 1:                                     /* switch 28 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            }
            goto block_534;
        case 2:                                     /* switch 28 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                (*(s16 *)(ctx + 0x3C)) = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            }
            goto block_534;
        case 3:                                     /* switch 28 */
            if (campaignWork.cinemaState == 2) {
                if (campaignWork.helpOpen == 0) {
                    (*(s8 *)(ctx + 1)) = 1;
                    if ((*(s8 *)(ctx + 1)) != 0) {
                        if ((*(s8 *)(ctx + 2)) != 0) {
                            func_00217230(0, 1);
                        }
                    }
                    func_001AAFA0(2);
                    campaignWork.helpOpen = 1;
                }
                if (0 > func_001AB1D0()) {
                    campaignWork.helpOpen = 0;
                    func_001A8360(2, 1, 0);
                    campaignMoveDone = 1;
                    func_001A8320(0xA, 1);
                    func_001A8920();
                    goto block_534;
                }
            } else {
                goto block_534;
            }
            break;
        default:                                    /* switch 28 */
block_534:
            if (campaignWork.zoom > 0xBB8) {
                campaignWork.cloudState = 4;
            }
            if ((campaignWork.zoom > 0x7D0) && (campaignWork.unk5447 == 0)) {
                func_001F48F0(0, 0x192, 0, 0, 0);
                campaignWork.unk5447 = 1;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2EE0:                                    /* switch 1 */
        temp_v1_18 = campaignWork.eventStep;
        switch (temp_v1_18) {                       /* switch 29; irregular */
        case 0:                                     /* switch 29 */
            func_00233F50(2);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.unk546E = 0;
            campaignWork.unk5470 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 29 */
            if (campaignWork.talkPage == 4) {
                if ((campaignWork.talkStep == 3) && (campaignWork.unk546E == 0)) {
                    campaignWork.unk546E = 1;
                    campaignWork.unk5470 = 0;
                }
            }
            if ((campaignWork.talkStep == 0xC) && (campaignWork.unk546E == 5)) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 29 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cloudState = 0x16;
                campaignWork.unk546E = 0;
                campaignWork.unk5470 = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 29 */
            if (campaignWork.cloudState == 0x17) {
                func_00233F50(3);
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                func_001E7F70(3, 2, 0);
                func_001F93F0(0, 7, 0, NULL);
                func_001F6E80(7, 1.0f);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 29 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 0;
                campaignWork.cameraTarget[0] = D_00298DDC;
                campaignWork.cameraTarget[2] = D_00298DE4;
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x64;
                func_00217980(4, 1);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F08:                                    /* switch 1 */
        temp_v1_19 = campaignWork.eventStep;
        switch (temp_v1_19) {                       /* switch 30; irregular */
        case 0:                                     /* switch 30 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            func_00217980(0x23, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 30 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 30 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x68;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F09:                                    /* switch 1 */
        temp_a1_4 = campaignWork.eventStep;
        switch (temp_a1_4) {                        /* switch 31; irregular */
        case 0:                                     /* switch 31 */
            func_00233F50(2);
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 31 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 31 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.placeReached[16] = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 31 */
            if ((campaignWork.placeReached[16] == 0) && (func_0022C3C0(1) != 0)) {
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 31 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0;
                campaignWork.eventStep = 0;
                campaignWork.unk5374 = 0;
                campaignWork.unk5375 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 0;
                campaignWork.leaderShow = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F62:                                    /* switch 1 */
        temp_v1_20 = campaignWork.eventStep;
        switch (temp_v1_20) {                       /* switch 32 */
        case 0:                                     /* switch 32 */
            func_00233F50(3);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            func_00217980(0x24, 1);
            func_001E7F70(3, 0, 0);
            campaignWork.unk547F = 0;
            campaignWork.unk5480 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 32 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 3;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 32 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 32 */
            if (campaignWork.talkPage == 2) {
                if (campaignWork.talkStep == 3) {
                    campaignWork.unk547F = 1;
                }
            }
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 32 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 32 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2F64;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 32 */
            goto dflt_3;
        }
        break;
    case 0x2F64:                                    /* switch 1 */
        temp_v1_21 = campaignWork.eventStep;
        switch (temp_v1_21) {                       /* switch 33 */
        case 0:                                     /* switch 33 */
            func_001F48F0(0, 0x191, 0, 0, 0);
            campaignWork.cameraTarget[0] = 0;
            campaignWork.cameraTarget[2] = 0;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 2;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0x1000;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.unk546E = 0;
            campaignWork.unk5470 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 33 */
            if (campaignWork.cinemaState == 2) {
                func_00217710(0, 0x22);
                func_00217710(0, 0x23);
                campaignWork.zoomMove = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 33 */
            if (campaignWork.zoomMove == 0) {
                campaignWork.cloudState = 0x1E;
                campaignWork.cloudCover = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 33 */
            if (campaignWork.cloudState == 0x1F) {
                campaignWork.cloudState = 0x20;
                campaignWork.cloudCover = 0x1000;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 33 */
            if (campaignWork.cloudState == 0x21) {
                campaignWork.eventPictureZoom = (s8) (campaignWork.eventPictureZoom - 4);
                if (campaignWork.eventPictureZoom < -0x63) {
                    campaignWork.eventPictureZoom = -0x64;
                    campaignWork.unk546E = 1;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 5:                                     /* switch 33 */
            if ((campaignWork.unk546E == 5) && (campaignWork.unk547F == 4)) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                func_00217980(0x21, 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 33 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 7:                                     /* switch 33 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                func_00217980(4, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 8:                                     /* switch 33 */
            if (campaignWork.cinemaState == 2) {
                func_001E7F70(3, 2, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 9:                                     /* switch 33 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 0;
                campaignWork.cameraTarget[0] = D_00298DDC;
                campaignWork.cameraTarget[2] = D_00298DE4;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 10:                                    /* switch 33 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0;
                campaignWork.unk5374 = 0;
                campaignWork.unk5375 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 0;
                campaignWork.leaderShow = 0;
                campaignWork.unk546C = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 33 */
            goto dflt_3;
        }
        break;
    case 0x2F76:                                    /* switch 1 */
        temp_a2_7 = campaignWork.eventStep;
        switch (temp_a2_7) {                        /* switch 34; irregular */
        case 0:                                     /* switch 34 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 3;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.unk546E = 0;
            campaignWork.unk5470 = 0;
            campaignWork.unk547F = 0;
            campaignWork.unk5480 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 34 */
            if (campaignWork.cinemaState == 2) {
                func_001E7F70(3, 0, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 34 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 3;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 34 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 34 */
            if (campaignWork.talkPage == 2) {
                if ((campaignWork.unk546E == 0) && (campaignWork.eventPictureZoom < -0x63)) {
                    campaignWork.unk546E = 1;
                    campaignWork.unk5470 = 0;
                    campaignWork.unk547F = 1;
                }
            }
            if ((campaignWork.talkStep == 0xC) && (campaignWork.unk546E == 5) && (campaignWork.unk547F == 4)) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2F78;
                campaignWork.unk546E = 0;
                campaignWork.unk5470 = 0;
                campaignWork.unk547F = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F78:                                    /* switch 1 */
        temp_a2_8 = campaignWork.eventStep;
        switch (temp_a2_8) {                        /* switch 35; irregular */
        case 0:                                     /* switch 35 */
            func_00233F50(2);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            func_00217980(0x25, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 35 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 35 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 35 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2F7A;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F7A:                                    /* switch 1 */
        temp_v1_22 = campaignWork.eventStep;
        switch (temp_v1_22) {                       /* switch 36 */
        case 0:                                     /* switch 36 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 1;
            campaignWork.cameraTarget[0] = 0;
            campaignWork.cameraTarget[2] = 0;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = -0x180;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureState = 1;
            campaignWork.eventPictureFade = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 36 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureX = (s16) (campaignWork.eventPictureX + 2);
                if (0 < campaignWork.eventPictureX) {
                    campaignWork.eventPictureX = 0;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                temp_a2_9 = campaignWork.eventPictureX;
                campaignWork.eventPictureY = (-temp_a2_9 * 0x19C) / 384 - 0x19C;
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 36 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 36 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 36 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventPictureFade = 1;
                campaignWork.eventPictureAlpha = 0x80;
                campaignWork.zoomMove = 1;
                campaignWork.zoom = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 36 */
            if (campaignWork.eventPictureFade == 0xA) {
                (*(s16 *)(ctx + 0xC2)) = 0x2F7C;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 36 */
            goto dflt_3;
        }
        break;
    case 0x2F7C:                                    /* switch 1 */
        temp_v1_23 = campaignWork.eventStep;
        switch (temp_v1_23) {                       /* switch 37; irregular */
        case 0:                                     /* switch 37 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 1;
            campaignWork.cameraTarget[0] = 0;
            campaignWork.cameraTarget[2] = 0;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.zoomMove = 1;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.unk5447 = 0;
            func_00217980(0x26, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto block_727;
        case 1:                                     /* switch 37 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            }
            goto block_727;
        case 2:                                     /* switch 37 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                (*(s16 *)(ctx + 0x3C)) = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            }
            goto block_727;
        case 3:                                     /* switch 37 */
            if (campaignWork.cinemaState == 2) {
                if (campaignWork.helpOpen == 0) {
                    (*(s8 *)(ctx + 2)) = 1;
                    if ((*(s8 *)(ctx + 1)) != 0) {
                        if ((*(s8 *)(ctx + 2)) != 0) {
                            func_00217230(0, 1);
                        }
                    }
                    func_001AAFA0(2);
                    campaignWork.helpOpen = 1;
                }
                if (0 > func_001AB1D0()) {
                    campaignWork.helpOpen = 0;
                    func_001A8360(3, 1, 0);
                    campaignMoveDone = 1;
                    func_001A8320(0xA, 1);
                    func_001A8920();
                    (*(s16 *)(ctx + 0xC2)) = 0;
                    goto block_727;
                }
            } else {
                goto block_727;
            }
            break;
        default:                                    /* switch 37 */
block_727:
            if (campaignWork.zoom > 0xBB8) {
                campaignWork.cloudState = 4;
            }
            if ((campaignWork.zoom > 0x7D0) && (campaignWork.unk5447 == 0)) {
                func_001F48F0(0, 0x192, 0, 0, 0);
                campaignWork.unk5447 = 1;
                goto end_0021E330;
            }
            break;
        }
        break;
    default:
        campaignWork.cameraMode = 0;
        break;
    }
end_0021E330:;
}

typedef struct {
    __int128 value;
} Scale_002232F0;

extern Scale_002232F0 D_0029A7D0;

typedef struct {
    s32 x, y, w, h;
} Rect_002232F0;

typedef struct {
    s32 pad;
    Rect_002232F0 rect;
} Texture_002232F0;

typedef struct {
    u8 r, g, b, a;
} Color_002232F0;

/* Draws a number in the campaign windows' digits. (original: Taku_Camp_Kazu_Disp) */
s32 Taku_Camp_Number_Disp(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 SzMsg_GetInfo();
    extern s32 SzMsg_DrawRect_Pipe();
    Rect_002232F0 rect;
    Scale_002232F0 scale;
    Color_002232F0 color;
    s16 i;
    s16 column;
    s16 row;
    s16 x;
    s32 digit;
    Texture_002232F0 *texture;

    scale = D_0029A7D0;
    color.r = color.g = color.b = 0xFF;
    color.a = 0x80;
    i = 0;
    x = 0xA0;
    for (; i < 4; i++) {
        digit = 0;
        switch (i) {
        case 0:
            digit = arg1 % 10;
            break;
        case 1:
            digit = 10;
            break;
        case 2:
            digit = (arg2 / 10) % 10;
            break;
        case 3:
            digit = arg2 % 10;
            break;
        }
        if (digit == 0) {
            column = 4;
            row = 1;
        } else if (digit < 6) {
            column = digit - 1;
            row = 0;
        } else if (digit < 10) {
            column = digit - 6;
            row = 1;
        } else {
            column = 2;
            row = 4;
        }
        arg0 = SzMsg_LoadFont_Pipe(arg0, 1, 7, 0, 0x16);
        arg0 = RhText_SetTextureFlush(arg0);
        texture = (Texture_002232F0 *)SzMsg_GetInfo(1);
        rect = texture->rect;
        color.r = color.g = color.b = 0xFF;
        color.a = 0x80;
        texture->rect.x = rect.x + column * 0x16;
        texture->rect.y = rect.y + row * 0x16;
        texture->rect.w = 0x16;
        texture->rect.h = 0x16;
        arg0 = SzMsg_DrawRect_Pipe(arg0, 1, x + arg3, 0x110, &scale, &color);
        SzMsg_Free(1);
        x += 0x10;
    }
    return arg0;
}

typedef struct {
    s16 x, y;
    u8 pad04[12];
    u8 r, g, b, a;
    u8 pad14[3], alpha1;
    u8 pad18[3], alpha2;
    u8 pad1C[3], alpha3;
    u8 pad20[6];
} Sprite_00223600;
typedef struct { s32 value[4]; } UV_00223600;
typedef struct { s16 rgb[10][3]; } Palette_00223600;
typedef struct { Sprite_00223600 item[6]; } SixSprites_00223600;
typedef struct { Sprite_00223600 item[3]; } ThreeSprites_00223600;
typedef struct { s16 u, v, w, h, page; } Image_00223600;
typedef struct { s32 x, y, w, h; } Rect_00223600;
typedef struct { s32 flags; Rect_00223600 rect; } Texture_00223600;

extern UV_00223600 D_0029A7E0;
extern Palette_00223600 D_0029A7F0;
extern Image_00223600 D_0029A830;
extern SixSprites_00223600 D_0029A840;
extern Sprite_00223600 D_0029A930;
extern ThreeSprites_00223600 D_0029A960;
extern Sprite_00223600 D_0029A9E0;
extern s16 D_002999A0[][3];
extern s8 D_0030F0B0[];
#pragma conditional_move off
#pragma opt_dead_assignments off

/* Draws the campaign event window's title: the place's name, the opponent's name and portrait. (original: Taku_Camp_Ivent_Name) */
s32 Taku_Camp_Event_Name(s32 packet) {
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern s32 Taku_Obj_Set(s32, void *, s16, s16);
    extern s32 Taku_G4_Set(s32, void *, s16, s16);
    extern s32 SzMsg_DrawRect_Pipe();
    extern s32 SzMsg_GetInfo();
    extern s32 Taku_Text_Set(s32, s32, s32, s16, s16, f32, f32, s32, void *);
    s16 fromX;
    s32 font;
    s16 row;
    s16 textRow;
    s16 section;
    s16 page;
    s16 left;
    s16 right;
    s16 textOffset;
    s16 paletteRow;
    s16 nextPaletteRow;
    s16 cellBase;
    s16 sectionX;
    s16 (*entry)[3];
    s16 colourIndex;
    s32 slide;
    s16 fromY;
    CampaignWork *state;
    s16 shift;
    s16 scroll;
    s16 rowY;
    s32 selX;
    s32 selY;
    Texture_00223600 *texture;
    s16 charX;
    s32 texX;
    s32 texY;
    s16 col;
    s16 i;
    s16 k;
    s16 texCol;
    s16 texRow;
    Texture_00223600 *selTex;
    Sprite_00223600 *sprite;
    s32 labelX;
    s16 labelLeft;
    s16 labelRight;
    s16 count;
    s16 x;
    s16 y;
    s16 dx;
    s16 band;
    s16 offset;
    s16 cellX;
    s16 toX;
    s16 group;
    s8 cell;
    s16 n;
    s16 lcol;
    s16 lrow;
    s16 lx;
    s16 ly;
    s32 ltx;
    s32 lty;
    s32 px;
    s32 sy;
    s16 py;
    s16 tx;
    s32 ty;
    Rect_00223600 baseRect;
    UV_00223600 uv;
    Palette_00223600 palette;
    SixSprites_00223600 decorations;
    Sprite_00223600 tile;
    ThreeSprites_00223600 labels;
    Sprite_00223600 cursor;
    Rect_00223600 listRect;
    Rect_00223600 selectedRect;
    Image_00223600 image;
    u8 rgba[4];

    state = &campaignWork;
    font = 0;
    uv = D_0029A7E0;
    palette = D_0029A7F0;
    image = D_0029A830;
    decorations = D_0029A840;
    tile = D_0029A930;
    labels = D_0029A960;
    cursor = D_0029A9E0;
    rgba[2] = 255; rgba[1] = 255; rgba[0] = 255; rgba[3] = 128;
    image.page = 2;
    image.w = 0x300;
    image.h = (state->eventWindowOpen * 404) / 100 + 16;
    if (state->eventWindowState == 1) {
        state->eventWindowOpen += 6;
        if (state->eventWindowOpen >= 100) {
            state->eventWindowOpen = 100;
            state->eventWindowState = 2;
        }
    }
    if (state->eventWindowState == 3) {
        state->eventWindowOpen -= 6;
        if (state->eventWindowOpen < 0) {
            state->eventWindowOpen = 0;
            state->eventWindowState = 4;
        }
    }
    packet = Taku_Window_Set(packet, &image, 2, 0, 0xFFC0, 16, 0, 128, 64);
    if (0 < state->eventWindowState) {
        slide = (state->eventWindowOpen * 640) / 100;
        left = 640 - slide;
        image.page = 2;
        image.w = 236;
        image.h = 32;
        right = slide - 640;
        x = left + 28;
        packet = Taku_Window_Set(packet, &image, 5, 0, x, 28, 0, 128, 128);
        x += 43;
        packet = SzDuel_DrawWindow_Font_Pipe(packet, x, 35, 2, 1, 10, D_0030F0B0, 0);
        image.page = 0;
        x = right + 176;
        image.w = 288;
        image.h = 40;
        packet = Taku_Window_Set(packet, &image, 2, 0, x, 88, 0, 128, 64);
        labelX = (s16)x + 96;
        sprite = labels.item;
        i = 0;
        labelLeft = x - 12;
        labelRight = 288 + x;
        for (; i < 3; i++) {
            x = labelX;
            y = 74;
            switch (i) {
            case 0:
                break;
            case 1:
                x = labelLeft;
                y = 92;
                break;
            case 2:
                x = labelRight;
                y = 92;
                break;
            }
            packet = (s32)Taku_FT4_Set((void *)packet, sprite, x, y, 0);
            sprite++;
        }
        x = right + (state->nameLength * 22 + 185);
        if (0 <= state->nameBlink) {
            y = (s8)state->nameBlink;
        } else {
            y = -(s8)state->nameBlink;
        }
        cursor.alpha3 = y;
        cursor.alpha2 = y;
        cursor.alpha1 = y;
        cursor.a = y;
        state->nameBlink += 16;
        if (state->nameLength < 12) {
            packet = Taku_G4_Set(packet, &cursor, x, 94);
        }
        x = 48 + left;
        image.page = 9;
        image.w = 540;
        image.h = 34;
        packet = Taku_Window_Set(packet, &image, 3, 0, x, 383, 0, 128, 64);
        sprite = decorations.item;
        for (i = 0; i < 6; i++) {
            x = left + 0;
            if (i != 3 && i != 4) {
                packet = Taku_Obj_Set(packet, sprite, x, 0);
            }
            sprite++;
        }
        dx = left;
        entry = D_002999A0;
        for (i = 0; i < 3; i++) {
            font = (*entry)[2];
            packet = Taku_Text_Set(packet, 1, font, (s16)dx + (*entry)[0], (*entry)[1], 1.0f, 1.0f, 0, rgba);
            entry++;
        }
        if (state->nameTableTurn != 0) {
            count = 3;
            scroll = (state->nameTableSlide * 640) / 100;
        } else {
            count = 1;
            scroll = 0;
        }
        for (page = 0; page < count; page++) {
            shift = 0;
            switch (page) {
            case 1:
                shift = -640;
                break;
            case 2:
                shift = 640;
                break;
            }
            for (section = 0, sectionX = 0; section < 3; section++) {
                band = 0;
                switch (state->nameTable) {
                case 0:
                    switch (page) {
                    case 0:
                        break;
                    case 1:
                        band = 6;
                        break;
                    case 2:
                        band = 3;
                        break;
                    }
                    break;
                case 1:
                    switch (page) {
                    case 0:
                        band = 3;
                        break;
                    case 1:
                        break;
                    case 2:
                        band = 6;
                        break;
                    }
                    break;
                case 2:
                    switch (page) {
                    case 0:
                        band = 6;
                        break;
                    case 1:
                        band = 3;
                        break;
                    case 2:
                        band = 0;
                        break;
                    }
                    break;
                }
                paletteRow = section + band;
                nextPaletteRow = section + 1 + band;
                cellBase = sectionX + 0;
                for (row = 0, rowY = 0; row < 6; row++) {
                    if (row % 2 == 0) {
                        colourIndex = paletteRow;
                    } else {
                        colourIndex = nextPaletteRow;
                    }
                    if (row % 2 == 0) {
                        offset = right;
                    } else {
                        offset = left;
                    }
                    cellX = cellBase;
                    for (col = 0; col < 5; col++) {
                        tx = offset + (shift + cellX);
                        ty = rowY;
                        tile.r = (palette.rgb[(s16)colourIndex][0] >> 1) * 3;
                        tile.g = (palette.rgb[(s16)colourIndex][1] >> 1) * 3;
                        tile.b = (palette.rgb[(s16)colourIndex][2] >> 1) * 3;
                        packet = Taku_Obj_Set(packet, &tile, (s16)(tx + scroll), ty);
                        cellX = cellX + 32;
                    }
                    rowY += 36;
                }
                sectionX += 160;
            }
            for (textRow = 0; textRow < 3; textRow++) {
                switch (state->nameTable) {
                case 0:
                    switch (page) {
                    case 0:
                        font = textRow + 11;
                        break;
                    case 1:
                        font = textRow + 5;
                        break;
                    case 2:
                        font = textRow + 14;
                        break;
                    }
                    break;
                case 1:
                    switch (page) {
                    case 0:
                        font = textRow + 14;
                        break;
                    case 1:
                        font = textRow + 11;
                        break;
                    case 2:
                        font = textRow + 5;
                        break;
                    }
                    break;
                case 2:
                    switch (page) {
                    case 0:
                        font = textRow + 5;
                        break;
                    case 1:
                        font = textRow + 14;
                        break;
                    case 2:
                        font = textRow + 11;
                        break;
                    }
                    break;
                }
                packet = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, font, 0, 22));
                texture = (Texture_00223600 *)SzMsg_GetInfo(1);
                baseRect = texture->rect;
                texY = baseRect.y;
                for (row = 0; row < 6; row++) {
                    if (row % 2 == 0) {
                        textOffset = right;
                    } else {
                        textOffset = left;
                    }
                    texX = baseRect.x;
                    for (col = 0, charX = 0; col < 5; col++) {
                        tx = textOffset + (tile.x + 5 + charX + textRow * 160);
                        py = tile.y + 5 + row * 36;
                        rgba[2] = 0; rgba[1] = 0; rgba[0] = 0; rgba[3] = 128;
                        texture->rect.x = texX;
                        texture->rect.y = texY;
                        texture->rect.w = 22;
                        texture->rect.h = 22;
                        packet = SzMsg_DrawRect_Pipe(packet, 1, scroll + (tx + shift), py, &uv, rgba);
                        tx = textOffset + (tile.x + 3 + charX + textRow * 160);
                        py = tile.y + 3 + row * 36;
                        rgba[2] = 255; rgba[1] = 255; rgba[0] = 255; rgba[3] = 128;
                        texture->rect.x = texX;
                        texture->rect.y = texY;
                        texture->rect.w = 22;
                        texture->rect.h = 22;
                        packet = SzMsg_DrawRect_Pipe(packet, 1, scroll + (tx + shift), py, &uv, rgba);
                        charX = charX + 32;
                        texX += 22;
                    }
                    texY += 22;
                }
                SzMsg_Free(1);
            }
        }
        if (state->nameTyping == 1) {
            for (k = 0; k < 3; k++) {
                texCol = state->namePickedColumn % 5;
                texRow = state->namePickedRow;
                if (state->namePickedColumn / 5 == k) {
                    switch (state->nameTable) {
                    case 0:
                        font = k + 11;
                        break;
                    case 1:
                        font = k + 14;
                        break;
                    case 2:
                        font = k + 5;
                        break;
                    }
                    packet = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, font, 0, 22));
                    selTex = (Texture_00223600 *)SzMsg_GetInfo(1);
                    selectedRect = selTex->rect;
                    rgba[2] = 0; rgba[1] = 0; rgba[0] = 0; rgba[3] = 128;
                    toX = state->nameLength * 22 + 190;
                    fromX = tile.x + 5 + state->namePickedColumn * 32;
                    fromY = tile.y + 5 + state->namePickedRow * 36;
                    px = fromX + (s16)((state->nameTypingT * (toX - fromX)) / 100);
                    sy = fromY + (s16)((state->nameTypingT * (96 - fromY)) / 100);
                    selX = selectedRect.x + (s16)texCol * 22;
                    selTex->rect.x = selX;
                    selY = selectedRect.y + (s16)texRow * 22;
                    selTex->rect.y = selY;
                    selTex->rect.w = 22;
                    selTex->rect.h = 22;
                    packet = SzMsg_DrawRect_Pipe(packet, 1, px, sy, &uv, rgba);
                    rgba[2] = 255; rgba[1] = 255; rgba[0] = 255; rgba[3] = 128;
                    fromX = tile.x + 3 + state->namePickedColumn * 32;
                    fromY = tile.y + 3 + state->namePickedRow * 36;
                    px = fromX + (s16)((state->nameTypingT * ((s16)(state->nameLength * 22 + 188) - fromX)) / 100);
                    sy = fromY + (s16)((state->nameTypingT * (94 - fromY)) / 100);
                    selTex->rect.x = selX;
                    selTex->rect.y = selY;
                    selTex->rect.w = 22;
                    selTex->rect.h = 22;
                    packet = SzMsg_DrawRect_Pipe(packet, 1, px, sy, &uv, rgba);
                    SzMsg_Free(1);
                }
            }
        }
        image.page = 10;
        image.w = 36;
        image.h = 36;
        x = (s16)(left + (tile.x - 4 + state->nameColumn * 32));
        y = (s16)(tile.y - 4 + state->nameRow * 36);
        packet = Taku_Window_Set(packet, &image, 3, 0, x, y, 0, 128, 0);
        n = 0;
        lx = 190;
        ly = 188;
        for (; n < 12; n++) {
            /* 41 copies of header prototypes: the compiler-state lever (PLAYBOOK, Taku_Camp_Event_Name section)
               that keeps Taku_Camp_Event_Window, later in this file, matching; code-neutral here. */
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            cell = state->nameLetterColumn[n];
            lcol = cell % 5;
            lrow = state->nameLetterRow[n];
            group = cell / 5;
            switch (state->nameLetterTable[n]) {
            case 0:
                font = (s16)group + 11;
                break;
            case 1:
                font = (s16)group + 14;
                break;
            case 2:
                font = (s16)group + 5;
                break;
            }
            packet = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, font, 0, 22));
            texture = (Texture_00223600 *)SzMsg_GetInfo(1);
            listRect = texture->rect;
            tx = right + lx;
            rgba[2] = 0; rgba[1] = 0; rgba[0] = 0; rgba[3] = 128;
            ltx = listRect.x + (s16)lcol * 22;
            texture->rect.x = ltx;
            lty = listRect.y + (s16)lrow * 22;
            texture->rect.y = lty;
            texture->rect.w = 22;
            texture->rect.h = 22;
            packet = SzMsg_DrawRect_Pipe(packet, 1, tx, 99, &uv, rgba);
            rgba[2] = 255; rgba[1] = 255; rgba[0] = 255; rgba[3] = 128;
            tx = right + ly;
            texture->rect.x = ltx;
            texture->rect.y = lty;
            texture->rect.w = 22;
            texture->rect.h = 22;
            packet = SzMsg_DrawRect_Pipe(packet, 1, tx, 97, &uv, rgba);
            SzMsg_Free(1);
            lx = lx + 22;
            ly = ly + 22;
        }
    }
    return packet;
}

typedef struct Tables_00224A40 {
    s32 pad[8];
    s32 normal[3];
    s32 type0[3];
    s32 type1[3];
} Tables_00224A40;
#pragma opt_dead_assignments reset
#pragma conditional_move reset

/* Picks the texts of the campaign event window for the current place and opponent. (original: Taku_Camp_Ivent_Name_Set) */
void Taku_Camp_Event_Name_Set(void) {
    extern u16 campaignDeckChoiceSets[];
    extern u16 campaignDeckChoices_2[][6];
    extern Tables_00224A40 D_002D19D0;
    extern s32 D_002D19D8;
    extern u16 D_002D49D4[];
    CampaignWork *state;
    s16 i;
    s16 group;
    s16 slot;
    u16 *dest;
    s32 offset;
    u8 *out;
    u8 *sum_ptr;
    s32 sum;
    s16 sum_index;
    u16 code_index;
    s32 shift;
    u8 *code_ptr;

    state = &campaignWork;
    sum_ptr = (u8 *)&campaignState;
    i = 0;
    offset = 0;
    out = sum_ptr;
    while (i < 12) {
        group = state->nameLetterColumn[i] / 5;
        slot = (s16)(state->nameLetterColumn[i] % 5) + state->nameLetterRow[i] * 6;
        if (i == 0) {
            dest = (u16 *)((u8 *)&D_002D49D4[D_002D19D8] + offset);
            switch (state->nameLetterTable[i]) {
            case 0:
                *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.type0[group] * 2 + slot * 2) & 0x1FFF;
                break;
            case 1:
                *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.type1[group] * 2 + slot * 2) & 0x1FFF;
                break;
            default:
                *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.normal[group] * 2 + slot * 2) & 0x3FFF;
                break;
            }
        }
        dest = (u16 *)((u8 *)&D_002D49D4[D_002D19D8] + offset + 4);
        switch (state->nameLetterTable[i]) {
        case 0:
            *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.type0[group] * 2 + slot * 2) & 0x1FFF;
            break;
        case 1:
            *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.type1[group] * 2 + slot * 2) & 0x1FFF;
            break;
        default:
            *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.normal[group] * 2 + slot * 2) & 0x3FFF;
            break;
        }
        if (i == 12 || i == state->nameCursor) {
            *dest |= 0x8000;
        }
        i++;
        offset += 2;
        *(s16 *)(out + 0x24) = *(s16 *)dest;
        out += 2;
    }
    sum_index = 0;
    sum = 0;
    while (sum_index < 12) {
        sum += (s32)*(u16 *)(sum_ptr + 0x24) % 16;
        sum_index++;
        sum_ptr += 2;
    }
    state->startingDeckSet = sum & 0xF;
    code_index = 0;
    shift = 0;
    code_ptr = (u8 *)state;
    while (code_index < 3) {
        *(u16 *)(code_ptr + 0x53F8) = ((s32)campaignDeckChoiceSets[state->startingDeckSet] >> shift) & 0x1F;
        shift += 5;
        *(u16 *)(code_ptr + 0x53FE) = campaignDeckChoices_2[*(u16 *)(code_ptr + 0x53F8)][0] & 0x3FF;
        code_index++;
        code_ptr += 2;
    }
}

typedef struct {
    s16 x0, y0, x1, y1;
    s16 kind;
} Frame_00224E40;

typedef struct {
    s16 x0, y0, x1, y1, x2, y2, x3, y3;
    u8 data[0x14];
    u16 index;
} Sprite_00224E40;

typedef struct {
    Sprite_00224E40 s[2];
} Pair_00224E40;

typedef struct {
    u8 r, g, b, a;
} Color_00224E40;

typedef struct {
    s16 u, v, width, height;
    u8 pad08[8];
    u16 texture;
    u8 pad12[2];
} Tex_00224E40;

typedef struct {
    u16 value;
    u16 number;
    u16 digits;
    u16 pad06;
    u32 types;
} Code_00224E40;
extern Frame_00224E40 D_0029AA08;
extern Sprite_00224E40 D_0029AA20;
extern Pair_00224E40 D_0029AA50;
extern Sprite_00224E40 D_0029AAA0;
extern Pair_00224E40 D_0029AAD0;
extern Sprite_00224E40 D_0029AB20;
extern Sprite_00224E40 D_0029AB50;
extern Sprite_00224E40 roseSprites[]; /* original: tex_bara_data */
extern Tex_00224E40 campaignSprites[]; /* original: tex_uv_data */
extern Code_00224E40 campaignDeckChoices_2[]; /* original: DeckDat */
extern char D_0030F0BB[];
extern char D_0030F0C7[];
extern char D_0030F0D4[];
extern char D_0030F0E8[];
#pragma opt_dead_assignments off

/* Draws the campaign event window: the event's text, the opponent, the rewards and the duel choice. (original: Taku_Camp_Ivent_Window) */
s32 Taku_Camp_Event_Window(s32 arg0) {
    s16 ny;
    extern s32 Taku_Camp_Event_Name();
    extern s32 Taku_Window_Set(s32, void *, s32, s32, u16, u16, s32, s32, s32);
    extern s32 Taku_Obj_Set(s32, void *, s16, s16);
    extern s32 Taku_Text_Set(s32, s32, s32, s16, s16, f32, f32, s32, void *);
    extern s32 SzMsg_LoadFont_Pipe(s32, s32, s32, s32, s32);
    extern s32 Taku_FT4_Set(s32, void *, s16, s16, u16);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, void *, void (*)(void));
    s16 flag2;
    s8 *ctx;
    s16 i;
    CampaignWork *state;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 nx;
    s32 right;
    s32 left;
    s32 t;
    s32 xx;
    s16 j;
    s16 n;
    s16 m;
    s16 k2;
    Sprite_00224E40 *tmpl;
    s16 k3;
    s16 i2;
    s32 xx3;
    s32 pos;
    s8 v;
    s16 cur;
    s16 flag;
    s16 flip;
    s16 k1;
    s16 k;
    s32 id;
    s32 q;
    s32 width;
    s8 sel;
    s8 mode;
    Code_00224E40 *code;
    f32 sx;
    f32 sy;

    u16 digits[3][4];
    u16 types[3][4];
    Sprite_00224E40 s100;
    Pair_00224E40 pair130;
    Sprite_00224E40 s180;
    Pair_00224E40 pair1B0;
    Sprite_00224E40 s200;
    Sprite_00224E40 s230;
    u16 hundreds[3];
    u16 ones[3];
    Frame_00224E40 frame;
    Color_00224E40 color;

    ctx = (s8 *)&campaignState;
    state = &campaignWork;
    frame = D_0029AA08;
    s100 = D_0029AA20;
    pair130 = D_0029AA50;
    s180 = D_0029AAA0;
    pair1B0 = D_0029AAD0;
    s200 = D_0029AB20;
    color.r = color.g = color.b = 0x80;
    color.a = 0x80;
    if (D_00299ED2 == 0x2738 && campaignWork.eventWindowState != 0) {
        arg0 = Taku_Camp_Event_Name(arg0);
    } else if (campaignWork.eventWindowState != 0) {
        switch (*(s16 *)(0xC2 + ctx)) {
        case 0x2738:
            x = 0x1B;
            y = 0x28;
            w = 0x24A;
            h = 0x180;
            break;
        case 0x276A:
        case 0x2742:
            x = 0x5B;
            y = 0x93;
            w = 0x1CA;
            h = 0x9A;
            break;
        case 0x2756:
            x = 0x1B;
            y = 0xAB;
            w = 0x24A;
            h = 0x8A;
            break;
        }
        frame.kind = 2;
        frame.x1 = ((w - 0x10) * campaignWork.eventWindowOpen) / 100 + 0x10;
        frame.y1 = ((h - 0x10) * campaignWork.eventWindowOpen) / 100 + 0x10;
        arg0 = Taku_Window_Set(arg0, &frame, 2, 0, x, y, 0, 0x80, 0x40);
        if (campaignWork.eventWindowState != 0) {
            t = (campaignWork.eventWindowOpen * 0x280) / 100;
            nx = x + w - 0x8B;
            right = 0x280 - t;
            ny = y + h - 0x2A;
            frame.kind = 9;
            frame.x1 = 0x82;
            frame.y1 = 0x22;
            left = t - 0x280;
            arg0 = Taku_Window_Set(arg0, &frame, 3, 0, nx + right, ny, 0, 0x80, 0x40);
            arg0 = Taku_Obj_Set(arg0, &pair1B0, nx + 0x1B + right, ny + 9);
            arg0 = Taku_Text_Set(arg0, 1, 0xA7, nx + 0x3C + right, 6 + ny, 1.0f, 1.0f, 0, &color);
            switch (*(s16 *)(0xC2 + ctx)) {
            case 0x2738:
            case 0x276A:
                if (campaignWork.eventWindowState == 2) {
                    tmpl = roseSprites;
                    for (i = 0; i < 2; i++) {
                        s100 = *tmpl;
                        if (i == 0) {
                            s100.x0 = 0x90;
                            s100.y0 = 0xE0;
                        } else {
                            s100.x0 = 0x90;
                            s100.y0 = 0xB0;
                        }
                        s100.x1 = s100.x0 + 0x20;
                        s100.y1 = s100.y0 + 0x20;
                        arg0 = Taku_Obj_Set(arg0, &s100, 0, 0);
                        tmpl++;
                    }
                }
                frame.x1 = 0x140;
                frame.y1 = 0x21;
            case 0x2742:
                if (*(s16 *)(ctx + 0xC2) == 0x2742) {
                    x = 0x97;
                } else {
                    x = 0xB0;
                }
                sel = campaignWork.eventWindowChoice;
                t = (s16)((sel == 0) ? 0xB0 : 0xE0);
                frame.kind = 8;
                y = t;
                if (*(s16 *)(0xC2 + ctx) == 0x2742) {
                    frame.x1 = 0x148;
                    frame.y1 = 0x21;
                }
                if (campaignWork.eventWindowState == 2) {
                    arg0 = Taku_Window_Set(arg0, &frame, 3, 0, x + left, y, 0, 0x80, 0x40);
                }
                if (campaignWork.eventWindowState == 2) {
                    for (i2 = 0; i2 < 2; i2++) {
                        if (i2 == state->eventWindowChoice) {
                            color.r = color.g = color.b = 0x80;
                            color.a = 0x80;
                        } else {
                            color.r = color.g = color.b = 0x40;
                            color.a = 0x80;
                        }
                        if (*(s16 *)(0xC2 + ctx) == 0x2742) {
                            x = 0x97;
                        } else {
                            x = 0xB0;
                        }
                        if (i2 == 0) {
                            sy = sx = 1.0f;
                            if (*(s16 *)(0xC2 + ctx) == 0x276A) {
                                id = 0x100;
                            } else {
                                id = 0xFD;
                            }
                            arg0 = Taku_Text_Set(arg0, 1, id, x + 8 + left, 0xB4, sx, sy, 0, &color);
                        } else {
                            if (*(s16 *)(ctx + 0xC2) == 0x276A) {
                                id = 0x101;
                            } else {
                                id = 0xFE;
                            }
                            sy = sx = 1.0f;
                            arg0 = Taku_Text_Set(arg0, 1, id, x + 8 + right, 0xE4, sx, sy, 0, &color);
                        }
                    }
                }
                color.r = color.g = color.b = 0x80;
                color.a = 0x80;
                break;
            case 0x2756:
            case 0x2757:
            case 0x2760:
                for (n = 0; n < 3; n++) {
                    hundreds[n] = campaignDeckChoices_2[state->deckChoices[n]].number / 100;
                    ones[n] = campaignDeckChoices_2[state->deckChoices[n]].number % 100;
                    for (m = 0; m < 4; m++) {
                        digits[n][m] = ((s32)campaignDeckChoices_2[state->deckChoices[n]].digits >> (m * 3)) & 7;
                        types[n][m] = (campaignDeckChoices_2[state->deckChoices[n]].types >> (5 * m)) & 0x1F;
                    }
                }
                if (campaignWork.deckShowPhase == 0) {
                    switch (v = campaignWork.deckShowDone) {
                    case 0:
                        cur = 2;
                        break;
                    default:
                        cur = v;
                        break;
                    }
                } else {
                    cur = campaignWork.eventWindowChoice;
                }
                frame.kind = 1;
                frame.x1 = 0xF0;
                frame.y1 = 0x20;
                arg0 = Taku_Window_Set(arg0, &frame, 2, 0, left + 0xA, 0x8B, 0, 0x80, 0x40);
                sx = 1.0f;
                arg0 = Taku_Text_Set(arg0, 1, 0xFF, left + 0x10, 0x91, sx, sx, 0, &color);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, left + 0x2E, 0xE6, 1, 0, 0xB, D_0030F0BB, NULL);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, left + 0x52, 0xF5, 1, 0, 0xC, D_0030F0C7, NULL);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, right + 0x1A2, 0xB5, 1, 0, 0x13, D_0030F0D4, NULL);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, right + 0x1A2, 0xDD, 1, 0, 0xE, D_0030F0E8, NULL);

                for (n = 0, xx3 = left; n <= hundreds[cur]; n++, xx3 += 0x10) {
                    if (n < hundreds[cur]) {
                        arg0 = Taku_Obj_Set(arg0, &pair130.s[0], xx3, 0);
                    } else {
                        campaignSprites[pair130.s[1].index].width = (ones[cur] * 16) / 100;
                        pair130.s[1].x1 = pair130.s[1].x0 + campaignSprites[pair130.s[1].index].width;
                        arg0 = Taku_Obj_Set(arg0, &pair130.s[1], xx3, 0);
                    }
                }
                arg0 = Taku_Camp_Number_Disp(arg0, hundreds[cur], ones[cur], left);
                for (n = 0; n < 4; n++) {
                    flag = 1;
                    switch (digits[cur][n]) {
                    case 1:
                        s180.index = 0x8A;
                        break;
                    case 2:
                        s180.index = 0x8F;
                        break;
                    case 3:
                        s180.index = 0x8C;
                        break;
                    case 4:
                        s180.index = 0x8D;
                        break;
                    case 5:
                        s180.index = 0x8B;
                        break;
                    case 6:
                        s180.index = 0x8E;
                        break;
                    default:
                        flag = 0;
                        break;
                    }
                    if (flag) {
                        arg0 = Taku_Obj_Set(arg0, &s180, right + (0x208 - n * 0x20), 0xC4);
                    }
                }
                for (k3 = 0; k3 < 4; k3++) {
                    flag2 = 1;
                    switch (types[cur][k3]) {
                    case 1:
                        s180.index = 0x4E;
                        break;
                    case 2:
                        s180.index = 0x58;
                        break;
                    case 3:
                        s180.index = 0x5D;
                        break;
                    case 4:
                        s180.index = 0x4F;
                        break;
                    case 5:
                        s180.index = 0x53;
                        break;
                    case 6:
                        s180.index = 0x55;
                        break;
                    case 7:
                        s180.index = 0x56;
                        break;
                    case 8:
                        s180.index = 0x57;
                        break;
                    case 9:
                        s180.index = 0x51;
                        break;
                    case 10:
                        s180.index = 0x52;
                        break;
                    case 11:
                        s180.index = 0x59;
                        break;
                    case 12:
                        s180.index = 0x54;
                        break;
                    case 13:
                        s180.index = 0x5A;
                        break;
                    case 14:
                        s180.index = 0x5B;
                        break;
                    case 15:
                        s180.index = 0x5C;
                        break;
                    case 16:
                        s180.index = 0x50;
                        break;
                    case 17:
                        s180.index = 0x5E;
                        break;
                    case 18:
                        s180.index = 0x5F;
                        break;
                    case 19:
                        s180.index = 0x60;
                        break;
                    case 20:
                        s180.index = 0x61;
                        break;
                    case 21:
                        s180.index = 0x65;
                        break;
                    default:
                        flag2 = 0;
                        break;
                    }
                    if (k3 == 3) {
                        s200.index = s180.index;
                    }
                    if (flag2) {
                        arg0 = Taku_Obj_Set(arg0, &s180, right + (0x208 - k3 * 0x20), 0xEB);
                    }
                }
                for (k = 0, xx = 0xE0; k < 2; k++, xx += 0x94) {
                    s230 = D_0029AB50;
                    flip = 0;
                    if (1 == k) {
                        s230.x0 = 0x18;
                        s230.y0 = 0;
                        s230.x1 = 0;
                        s230.y1 = 0;
                        s230.x2 = 0x18;
                        s230.y2 = 0x18;
                        s230.x3 = 0;
                        s230.y3 = 0x18;
                        flip = 1;
                    }
                    mode = state->deckChoiceTurn;
                    if (mode == 0) {
                        if (k == 0) {
                            arg0 = Taku_FT4_Set(arg0, &s230, left + xx, 0xF1, flip);
                        } else {
                            arg0 = Taku_FT4_Set(arg0, &s230, right + xx, 0xF1, flip);
                        }
                    } else if (mode == 1 && k == 0) {
                        arg0 = Taku_FT4_Set(arg0, &s230, xx, 0xF1, flip);
                    } else if (mode == 2 && k == 1) {
                        arg0 = Taku_FT4_Set(arg0, &s230, xx, 0xF1, flip);
                    }
                }
                frame.kind = 9;
                frame.x1 = 0xD5;
                frame.y1 = 0x22;
                arg0 = Taku_Window_Set(arg0, &frame, 1, 0, 0x22 + left, 0xB2, 0, 0x80, 0x40);
                arg0 = Taku_Obj_Set(arg0, &s200, 0x27 + left, 0xB7);
                q = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, SzDuel_GetMsgName(state->deckChoiceCards[cur]), 0, 0x16));
                width = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0xC);
                if (width <= 0xA9) {
                    sy = sx = 1.0f;
                    arg0 = SzMsg_DrawRatioX_Pipe(q, 1, left + 0x45, 0xB7, sx, sy, &color, SzMsg_DrawRect_Pipe);
                } else {
                    arg0 = SzMsg_DrawRatioX_Pipe(q, 1, left + 0x45, 0xB7, 170.0f / width, 1.0f, &color, SzMsg_DrawRect_Pipe);
                }
                SzMsg_Free(1);
                break;
            }
        }
        if (campaignWork.eventWindowState == 1) {
            campaignWork.eventWindowOpen += 6;
            if (campaignWork.eventWindowOpen >= 100) {
                campaignWork.eventWindowOpen = 100;
                campaignWork.eventWindowState = 2;
            }
        }
        switch (*(s16 *)(ctx + 0xC2)) {
        case 0x2738:
        case 0x276A:
        case 0x2742:
            if (campaignWork.eventWindowState == 3) {
                campaignWork.eventWindowOpen -= 6;
                if (campaignWork.eventWindowOpen < 0) {
                    campaignWork.eventWindowOpen = 0;
                    campaignWork.eventWindowState = 4;
                }
            }
            break;
        case 0x2756:
        case 0x2757:
        case 0x2760:
            if (campaignWork.eventWindowState == 3 && campaignWork.deckShowPhase >= 3) {
                campaignWork.eventWindowOpen -= 6;
                if (campaignWork.eventWindowOpen < 0) {
                    campaignWork.eventWindowOpen = 0;
                    campaignWork.eventWindowState = 4;
                }
            }
            break;
        }
    }
    return arg0;
}

typedef struct Packet_00226120 {
    s16 x0, y0, x1, y1, x2, y2, x3, y3;
    u8 r0, g0, b0, a0;
    u8 r1, g1, b1, a1;
    u8 r2, g2, b2, a2;
    u8 r3, g3, b3, a3;
    s16 field20;
    s16 depth;
    s16 field24;
} Packet_00226120;
extern Packet_00226120 D_0029AB80;
#pragma opt_dead_assignments reset

/* Draws the clouds drifting over the campaign map. (original: Taku_Camp_Kumo) */
void *Taku_Camp_Clouds(void *packetIn) {
    extern void *Taku_G4_Set();
    s8 *context = &campaignState;
    u8 *slot = &campaignCoord;
    Packet_00226120 packet = D_0029AB80;
    s16 state;
    s16 i;

    if (D_00299ED2 == 0x2724 && campaignWork.eventStep < 6) {
        packet.depth = -10;
    } else if (*(s16 *)(context + 0xC2) == 0x2BB0) {
        packet.depth = -10;
    } else if (*(s16 *)(context + 0xC2) == 0x2F7C) {
        packet.depth = -10;
    }

    state = campaignWork.cloudState;
    if (state != 0) {
        switch ((s16)state) {
        case 2:
            break;
        case 3:
            if (0 <= campaignWork.cloudCover) {
                campaignWork.cloudCover -= 0x10;
                if (campaignWork.cloudCover <= 0) {
                    campaignWork.cloudCover = 0;
                    campaignWork.cloudState = 0;
                }
            }
            break;
        case 4:
            if (campaignWork.cloudCover <= 0x1000) {
                campaignWork.cloudCover += 0x20;
                if (campaignWork.cloudCover >= 0x1000) {
                    campaignWork.cloudCover = 0x1000;
                    campaignWork.cloudState = 4;
                }
            }
            break;
        case 10:
            campaignWork.cloudCover += 0x400;
            if (campaignWork.cloudCover >= 0x1000) {
                campaignWork.cloudCover = 0x1000;
                campaignWork.cloudState = 11;
            }
            break;
        case 20:
            campaignWork.cloudCover -= 0x100;
            if (campaignWork.cloudCover <= 0) {
                campaignWork.cloudCover = 0;
                campaignWork.cloudState = 21;
            }
            break;
        case 22:
            campaignWork.cloudCover += 0x100;
            if (campaignWork.cloudCover >= 0x1000) {
                campaignWork.cloudCover = 0x1000;
                campaignWork.cloudState = 23;
            }
            break;
        case 30:
            campaignWork.cloudCover += 0x400;
            if (campaignWork.cloudCover >= 0x1000) {
                campaignWork.cloudCover = 0x1000;
                campaignWork.cloudState = 31;
            }
            break;
        case 32:
            campaignWork.cloudCover -= 0x20;
            if (campaignWork.cloudCover <= 0) {
                campaignWork.cloudCover = 0;
                campaignWork.cloudState = 33;
            }
            break;
        }

        state = campaignWork.cloudState;
        if (state >= 30) {
            packet.r0 = packet.r1 = packet.r2 = packet.r3 = 255;
            packet.g0 = packet.g1 = packet.g2 = packet.g3 = 255;
            packet.b0 = packet.b1 = packet.b2 = packet.b3 = 255;
        } else if (state >= 20) {
            packet.r0 = packet.r1 = packet.r2 = packet.r3 = 0;
            packet.g0 = packet.g1 = packet.g2 = packet.g3 = 0;
            packet.b0 = packet.b1 = packet.b2 = packet.b3 = 0;
        } else if (state >= 10) {
            packet.r0 = packet.r1 = packet.r2 = packet.r3 = 0;
            packet.g0 = packet.g1 = packet.g2 = packet.g3 = 0;
            packet.b0 = packet.b1 = packet.b2 = packet.b3 = 32;
        }

        packet.x0 = packet.x2 = 0;
        packet.x1 = packet.x3 = 640;
        packet.y0 = packet.y1 = 0;
        packet.y2 = packet.y3 = 448;

        if (*(s16 *)(context + 0xC2) == 0x2738 && campaignWork.eventStep > 1) {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 = 0;
        } else if (*(s16 *)(context + 0xC2) == 0x2B9A ||
                   *(s16 *)(context + 0xC2) == 0x2F64) {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 = 0;
        } else {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 =
                (campaignWork.cloudCover << 7) >> 12;
            packetIn = Taku_G4_Set(packetIn, &packet, 0, 0);
        }
    }

    Taku_Coord_Set(slot);
    for (i = 0; i < 16; i++) {
    }
    return packetIn;
}
