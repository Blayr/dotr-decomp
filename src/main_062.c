#include "common.h"
#include "campaign.h"

/* Sets a campaign coordinate record to scale 1, no rotation, no move. */
void Taku_Coord_Init(void *coord) {
    f32 *values = coord;

    values[3] = 1.0f;
    values[2] = 1.0f;
    values[1] = 1.0f;
    values[0] = 1.0f;
    values[7] = 0.0f;
    values[6] = 0.0f;
    values[5] = 0.0f;
    values[4] = 0.0f;
    values[11] = 0.0f;
    values[10] = 0.0f;
    values[9] = 0.0f;
    values[8] = 0.0f;
}


typedef struct {
    f32 m[4][4];
} Matrix_0021BB20;

/* Builds a campaign coordinate record's matrix: world-to-screen times its scale, rotation and position. */
void Taku_Coord_Set(u8 *coord) {
    Matrix_0021BB20 matrix;

    RhView_GetWorldScreenMatrix(coord + 0x30);
    RhGeom_GetScaleRotXYZTransMatrix(&matrix, coord, coord + 0x10, coord + 0x20);
    RhGeom_MulMatrix((s32)(coord + 0x30), &matrix);
}

/* Copies a 3-float vector. */
void Taku_Vector_Set(void *dst, void *src) {
    ((f32 *)dst)[0] = ((f32 *)src)[0];
    ((f32 *)dst)[1] = ((f32 *)src)[1];
    ((f32 *)dst)[2] = ((f32 *)src)[2];
}

/* The screen position of world point `point` on the campaign map into (outX, outY); -1 when off screen. */
void Taku_3D_2D_Set(s32 *outX, s32 *outY, s32 point) {
    u16 projected[6];
    s32 depth;

    if (Ex3d_RotTransPers(point, D_00299F90, projected, &depth) != 0) {
        *outX = ((s32) projected[0] >> 4) - 0x6C0;
        *outY = ((s32) projected[1] >> 4) - 0x720;
    } else {
        *outX = -1;
        *outY = -1;
    }
}

/* Builds a smooth path through `count` points (a cubic spline), `spacing` apart, into outX / outY. */
void Taku_spline2(f32 *outX, f32 *outY, s16 *outCount, f32 *points,
                   f32 *intervals, s32 count, s16 mode, f32 spacing) {
    f32 lower[64];
    f32 diagonal[64];
    f32 upper[64];
    f32 slopes[2][64];
    f32 rhs[2][64];
    f32 cubic[2];
    f32 quadratic[2];
    f32 linear[2];
    f32 constant[2];
    s32 i;
    s32 dimension;
    s32 written;

    diagonal[0] = 2.0f * intervals[0];
    upper[0] = intervals[0];
    lower[count - 1] = intervals[count - 2];
    diagonal[count - 1] = 2.0f * intervals[count - 2];
    for (i = 1; i <= count - 2; i++) {
        lower[i] = intervals[i];
        diagonal[i] = 2.0f * (intervals[i - 1] + intervals[i]);
        upper[i] = intervals[i - 1];
    }

    {
        dimension = 0;
        while (1) {
            rhs[dimension][0] = 3.0f * (points[dimension + 2] - points[dimension]);
            rhs[dimension][count - 1] = 3.0f *
                ((points + dimension)[2 * count - 2] - (points + dimension)[2 * count - 4]);
            for (i = 1; i <= count - 2; i++) {
                rhs[dimension][i] = func_0021C320((points + dimension)[2 * i - 2],
                    (points + dimension)[2 * i], (points + dimension)[2 * i + 2],
                    intervals[i - 1], intervals[i]);
            }
            tri_diag(lower, diagonal, upper, rhs[dimension], slopes[dimension], count);
            dimension++;
            if (dimension > 1) {
                break;
            }
        }
    }

    {
    dimension = 0;
    written = 0;
    for (; dimension < count - 1; dimension++) {
        i = 0;
        while (1) {
            cubic[i] = (slopes[i][dimension] + slopes[i][dimension + 1]) /
                (intervals[0] * intervals[0]) +
                (2.0f * (points[i] - points[i + 2])) /
                func_001A6C48(intervals[0], 3.0f);
            quadratic[i] = (3.0f * (points[i + 2] - points[i])) /
                (intervals[0] * intervals[0]) -
                (2.0f * slopes[i][dimension] + slopes[i][dimension + 1]) / intervals[0];
            linear[i] = slopes[i][dimension];
            constant[i] = points[i];
            i++;
            if (i > 1) {
                break;
            }
        }
        if (mode == 1) {
            if (dimension < count - 2) {
                f32 t;
                for (t = 0.0f; t <= intervals[0] - 0.1f; t += 0.1f) {
                    outX[written] = constant[0] + t *
                        (linear[0] + t * (quadratic[0] + cubic[0] * t));
                    outY[written] = constant[1] + t *
                        (linear[1] + t * (quadratic[1] + cubic[1] * t));
                    written++;
                }
            } else {
                f32 t;
                for (t = 0.0f; t <= intervals[0]; t += 0.1f) {
                    outX[written] = constant[0] + t *
                        (linear[0] + t * (quadratic[0] + cubic[0] * t));
                    outY[written] = constant[1] + t *
                        (linear[1] + t * (quadratic[1] + cubic[1] * t));
                    written++;
                }
            }
        } else {
            s16 samples;
            f32 dx;
            f32 dySquared;

            dx = points[2] - points[0];
            dySquared = func_001A6C48(points[3] - points[1], 2.0f);
            dx = func_001A6C48(dx, 2.0f);
            samples = func_001A22C0(func_001A6C60(dx + dySquared) / spacing);
            if (dimension < count - 2) {
                f32 t;
                for (i = 0; i < samples;) {
                    t = ((f32)i * intervals[0]) / (f32)samples;
                    i++;
                    outX[written] = constant[0] + t *
                        (linear[0] + t * (quadratic[0] + cubic[0] * t));
                    outY[written] = constant[1] + t *
                        (linear[1] + t * (quadratic[1] + cubic[1] * t));
                    written++;
                }
            } else {
                f32 t;
                for (i = 0; i <= samples;) {
                    t = ((f32)i * intervals[0]) / (f32)samples;
                    i++;
                    outX[written] = constant[0] + t *
                        (linear[0] + t * (quadratic[0] + cubic[0] * t));
                    outY[written] = constant[1] + t *
                        (linear[1] + t * (quadratic[1] + cubic[1] * t));
                    written++;
                }
            }
        }
        *outCount = written - 1;
        points += 2;
        intervals++;
    }
    }
}

/* The slope term of a cubic spline at a point from its neighbours and intervals. */
f32 func_0021C320(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    return 3.0f * (((fparg4 * (fparg1 - fparg0)) / fparg3) + ((fparg3 * (fparg2 - fparg1)) / fparg4));
}

/* Solves a tridiagonal system of n equations (for the spline). */
void tri_diag(f32 *a, f32 *b, f32 *c, f32 *r, f32 *u, s32 n) {
    f32 gamma[64];
    f32 denominator;
    s32 i;

    denominator = b[0];
    u[0] = r[0] / denominator;
    for (i = 1; i < n; i++) {
        gamma[i] = c[i - 1] / denominator;
        denominator = b[i] - a[i] * gamma[i];
        u[i] = (r[i] - a[i] * u[i - 1]) / denominator;
    }
    for (i = n - 2; i >= 0; i--) {
        u[i] -= gamma[i + 1] * u[i + 1];
    }
}

/* Draws message `msg` in text slot `slot` at (x, y) in colour `color` (loads, draws and frees it). */
s32 Taku_Bunsyou_Set(s32 packet, s32 slot, s32 msg, s64 x, s64 y, s32 arg5, s32 color) {
    s32 result;
    s32 object;

    object = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, slot, msg, 0, slot * 22));
    SzMsg_GetInfo(slot);
    result = SzMsg_DrawRatioX_Pipe(object, slot, (s16)x, (s16)y, 1.0f, 1.0f, color, SzMsg_DrawRect_Pipe);
    SzMsg_Free(slot);
    return result;
}

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
        

        campaignWork.deckHash = 0;
        p = &campaignWork;
        for (k = 0; k < 3; k++) {
            p->deckChoices[k] = (D_00299CE0_21c510[w->deckHash] >> (k * 5)) & 0x1f;
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
        campaignWork.deckHash = 0;
        p = &campaignWork;
        for (k = 0; k < 3; k++) {
            p->deckChoices[k] = (D_00299CE0_21c510[w->deckHash] >> (k * 5)) & 0x1f;
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
#undef DOTR_CAMP_ENTRY_WORK
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
        clear = (u16 *)&campaignWork; /* clears placeReached[i] and unk532C[i] */
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
    campaignWork.deckHash = total & 0xF;
    j = 0;
    shift = 0;
    halves = (u16 *)&campaignWork; /* halves[0x53F8 / 2] is deckChoices[j], halves[0x53FE / 2] unk53FE[j] */
    for (; j < 3; j++) {
        halves[0x53F8 / 2] = ((s32)campaignDeckChoiceSets[base->deckHash] >> shift) & 0x1F;
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
                var_s6 = Taku_Camp_Teki_Model_Disp(var_s6, 0x1F, temp_s5 + x_offset,
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
    extern s32 Taku_Camp_Kumo();
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
                packet = Taku_Camp_STON(packet);
            }
            break;
        case 0x2B9A:
            if (campaignWork.eventStep >= 9) {
                packet = Taku_Camp_3D(packet);
            } else {
                packet = Taku_Camp_STON(packet);
            }
            break;
        case 0x2BAC:
            if (campaignWork.eventStep >= 2) {
                packet = Taku_Camp_STON(packet);
            } else {
                packet = Taku_Camp_3D(packet);
            }
            break;
        case 0x2F64:
            if (campaignWork.eventStep < 0xA) {
                packet = Taku_Camp_STON(packet);
            } else {
                packet = Taku_Camp_3D(packet);
            }
            break;
        case 0x2F76:
            if (campaignWork.eventStep > 1) {
                packet = Taku_Camp_STON(packet);
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
            packet = Taku_Camp_STON(packet);
            break;
        default:
            if (v < 0x2AF8) {
                packet = Taku_Camp_STON(packet);
            } else {
                packet = Taku_Camp_3D(packet);
            }
            break;
        }
    } else {
        packet = Taku_Camp_3D(packet);
    }
    if (*(s16 *)(rec + 0xC2) >= 0x2710) {
        packet = Taku_Camp_Kumo(packet);
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

/* Draws the opponent's (teki) model `id` rendered into a texture at (x, y), w x h, with `alpha`. */
void *Taku_Camp_Teki_Model_Disp(void *packet, s32 id, s32 x, s32 y, f32 depth, s32 width, s32 height, s32 alpha) {
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
