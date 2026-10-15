#include "common.h"

void Taku_Coord_Init(void *arg0) {
    f32 *values = arg0;

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

void Taku_Coord_Set(u8 *arg0) {
    Matrix_0021BB20 matrix;

    RhView_GetWorldScreenMatrix(arg0 + 0x30);
    RhGeom_GetScaleRotXYZTransMatrix(&matrix, arg0, arg0 + 0x10, arg0 + 0x20);
    RhGeom_MulMatrix((s32)(arg0 + 0x30), &matrix);
}

void Taku_Vector_Set(void *arg0, void *arg1) {
    ((f32 *)arg0)[0] = ((f32 *)arg1)[0];
    ((f32 *)arg0)[1] = ((f32 *)arg1)[1];
    ((f32 *)arg0)[2] = ((f32 *)arg1)[2];
}

void Taku_3D_2D_Set(s32 *arg0, s32 *arg1, s32 arg2) {
    u16 projected[6];
    s32 depth;

    if (Ex3d_RotTransPers(arg2, D_00299F90, projected, &depth) != 0) {
        *arg0 = ((s32) projected[0] >> 4) - 0x6C0;
        *arg1 = ((s32) projected[1] >> 4) - 0x720;
    } else {
        *arg0 = -1;
        *arg1 = -1;
    }
}

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

f32 func_0021C320(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    return 3.0f * (((fparg4 * (fparg1 - fparg0)) / fparg3) + ((fparg3 * (fparg2 - fparg1)) / fparg4));
}

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

s32 Taku_Bunsyou_Set(s32 arg0, s32 arg1, s32 arg2, s64 arg3, s64 arg4, s32 arg5, s32 arg6) {
    s32 result;
    s32 object;

    object = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, arg1, arg2, 0, arg1 * 22));
    SzMsg_GetInfo(arg1);
    result = SzMsg_DrawRatioX_Pipe(object, arg1, (s16)arg3, (s16)arg4, 1.0f, 1.0f, arg6, SzMsg_DrawRect_Pipe);
    SzMsg_Free(arg1);
    return result;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrCampEntryVec {
    float x, y, z, w;
};
struct DotrCampEntryRecord {
    float x[64];
    float y[64];
    short count;
    short state;                
};
struct DotrCampEntryWork {
    unsigned char unknown_0000[0x30];
    struct DotrCampEntryVec from;   
    struct DotrCampEntryVec to;     
    unsigned char unknown_0050[0x18c - 0x50];
    signed char all;                
    unsigned char unknown_018d[0x22c - 0x18d];
    struct DotrCampEntryRecord records[2][16];  
    short unknown_42ac[2][16];
    short unknown_42ec[2][16][64];
    short rise[32];                 
    short count[32];                
    unsigned char unknown_536c[0x53a8 - 0x536c];
    signed char byte_53a8;          
    unsigned char unknown_53a9[0x53b3 - 0x53a9];
    signed char byte_53b3;          
    unsigned char unknown_53b4[0x53c7 - 0x53b4];
    signed char byte_53c7;          
    unsigned char unknown_53c8[0x53f6 - 0x53c8];
    unsigned short hash;            
    unsigned short pick[3];         
    unsigned short deck[3];         
    short leader;                   
};
#define DOTR_CAMP_ENTRY_WORK ((struct DotrCampEntryWork *)0x1ed0000)
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
extern int SzModel_LoadMerge(int type, int no, int force);
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

void TkCamp_Init(int mode)
{
    



    struct DotrCampEntryQuad pos;
    struct DotrCampEntryQuad rot;
    struct DotrCampEntryWork *w = DOTR_CAMP_ENTRY_WORK;
    struct DotrCampEntryBoard *board = &D_00299E10_b;
    int deck;
    int leader;
    int i;
    int j;
    short r;
    short n;
    short k;
    struct DotrCampEntryWork *p;
    int flag;
    short m;

    D_0034F710 = 0;
    Taku_Camp_Data_Init();
    Taku_spline_init();
    Taku_Camp_3D_Poly_Init();
    func_00233F50_b(3);
    for (i = 0; i < 2; i++) {
        SzModel_SetDrawFlag(i + 30, 0);
    }
    if (board->done0 != 0 && board->done1 != 0) {
        DOTR_CAMP_ENTRY_WORK->all = 1;
    } else {
        DOTR_CAMP_ENTRY_WORK->all = 0;
    }
    Taku_Screen_Init();
    SzGame_SetMenuNum(11, 1);
    DOTR_CAMP_ENTRY_WORK->byte_53c7 = 2;
    

    switch (mode) {
    case 0:
        func_00195108_b(board, 332);
        SzModel_LoadMerge(3, 4, 0);
        SzText_LoadMerge(10, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 0;
        board->done0 = 0;
        board->done1 = 0;
        DOTR_CAMP_ENTRY_WORK->all = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 10020;
        board->started = 1;
        func_00233F50_b(3);
        DOTR_CAMP_ENTRY_WORK->byte_53b3 = 1;
        D_0034F6F8_21c510 = 0;
        D_0034F700 = 0;
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
            DOTR_CAMP_ENTRY_WORK->leader = SzData_GetLeader(0, deck);
            SzModel_SetPos(30, &pos);
            SzModel_SetRot(30, &rot);
            SzModel_Load(30, -1, SzDuel_New2Xax(leader), 1);
        }
        if (DOTR_CAMP_ENTRY_WORK->all != 0) {
            SzModel_LoadMerge(3, 2, 0);
            func_001F93F0_b(0, 7, 0, 0);
            SzEffect_SetIntensityOnly(7, 1.0f);
            board->done0 = 1;
            board->done1 = 1;
            DOTR_CAMP_ENTRY_WORK->all = 1;
            board->ticks = 0;
            if (DOTR_CAMP_ENTRY_WORK->all != 0) {
                p = DOTR_CAMP_ENTRY_WORK;
                for (i = 0; i < 32; i++) {
                    p->rise[i] = 0;
                    p->count[i] = 0;
                    board->seen[i] = 3;
                }
                p = DOTR_CAMP_ENTRY_WORK;
                
                for (m = 0; m < 2; m++) {
                    for (i = 0; i < 16; i++) {
                        p->records[m][i].state = 3;
                    }
                }
            }
            board->ticks = 0;
            func_00233F50_b(0);
            DOTR_CAMP_ENTRY_WORK->byte_53b3 = 0;
            func_00217980_b(4, 0);
            break;
        }
        flag = 0;
        if (D_0034F708 != 0) {
            D_0034F708 = 0;
            SzModel_LoadMerge(3, 4, 0);
            SzText_LoadMerge(10, 0);
            if (board->done0 != 0) {
                board->side = 1;
                board->done0 = 1;
                board->done1 = 0;
                DOTR_CAMP_ENTRY_WORK->all = 0;
            } else if (board->done1 != 0) {
                board->side = 0;
                board->done0 = 0;
                board->done1 = 1;
                DOTR_CAMP_ENTRY_WORK->all = 0;
            }
            DOTR_CAMP_ENTRY_CLEAR_SEEN();
            board->ticks = 10060;
            board->started = 1;
            func_00233F50_b(3);
            DOTR_CAMP_ENTRY_WORK->byte_53b3 = 3;
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
                            w->records[0][D_00298BA0_21c510[j].list[r]].state = 3;
                        }
                    }
                }
                for (i = 2; i <= 10; i++) {
                    if (board->seen[i] >= 3) {
                        n++;
                        if (n >= 8) {
                            w->records[0][12].state = 3;
                            w->records[0][13].state = 3;
                            w->records[0][11].state = 3;
                        }
                    }
                }
            } else {
                DOTR_CAMP_ENTRY_WORK->records[1][0].state = 3;
                p = DOTR_CAMP_ENTRY_WORK;
                
                for (j = 12, n = 1; j <= 21; j++, n++) {
                    if (board->seen[j] == 3) {
                        p->records[1][n].state = 3;
                    }
                }
                if (board->seen[0] == 3) {
                    DOTR_CAMP_ENTRY_WORK->records[1][11].state = 3;
                }
            }
            board->started = 1;
            func_00233F50_b(0);
            DOTR_CAMP_ENTRY_WORK->byte_53b3 = 0;
            

            DOTR_CAMP_ENTRY_WORK->to.x = D_00298BA0_21c510[board->kind[0]].x;
            DOTR_CAMP_ENTRY_WORK->to.y = 0.0f;
            DOTR_CAMP_ENTRY_WORK->to.z = D_00298BA0_21c510[board->kind[0]].z;
            DOTR_CAMP_ENTRY_WORK->to.x = D_00298BA0_21c510[board->kind[1]].x;
            DOTR_CAMP_ENTRY_WORK->to.y = 0.0f;
            DOTR_CAMP_ENTRY_WORK->to.z = D_00298BA0_21c510[board->kind[1]].z;
            DOTR_CAMP_ENTRY_WORK->from.x = DOTR_CAMP_ENTRY_WORK->to.x;
            DOTR_CAMP_ENTRY_WORK->from.y = 96.0f + DOTR_CAMP_ENTRY_WORK->to.y;
            DOTR_CAMP_ENTRY_WORK->from.z = 96.0f + DOTR_CAMP_ENTRY_WORK->to.z;
            DOTR_CAMP_ENTRY_WORK->from.w = DOTR_CAMP_ENTRY_WORK->to.w;
            SzView_SetCamera(0, &DOTR_CAMP_ENTRY_WORK->from, &DOTR_CAMP_ENTRY_WORK->to);
            func_00217980_b(4, 0);
        } else {
            SzModel_LoadMerge(3, 4, 0);
            SzText_LoadMerge(10, 0);
            if (board->done0 != 0) {
                board->side = 1;
                board->done0 = 1;
                board->done1 = 0;
                DOTR_CAMP_ENTRY_WORK->all = 0;
                DOTR_CAMP_ENTRY_WORK->byte_53a8 = 0;
                board->byte_c9 = 0;
            } else if (board->done1 != 0) {
                board->side = 0;
                board->done0 = 0;
                board->done1 = 1;
                DOTR_CAMP_ENTRY_WORK->all = 0;
                DOTR_CAMP_ENTRY_WORK->byte_53a8 = 1;
                board->byte_c9 = 2;
            }
            DOTR_CAMP_ENTRY_CLEAR_SEEN();
            board->ticks = 10090;
            board->started = 1;
            func_00233F50_b(3);
            DOTR_CAMP_ENTRY_WORK->byte_53b3 = 3;
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
        DOTR_CAMP_ENTRY_WORK->all = 0;
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
        DOTR_CAMP_ENTRY_WORK->all = 0;
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
        DOTR_CAMP_ENTRY_WORK->all = 0;
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
        DOTR_CAMP_ENTRY_WORK->all = 0;
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
        DOTR_CAMP_ENTRY_WORK->all = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 12000;
        func_00217980_b(24, 1);
        break;
    case 60:
        

        DOTR_CAMP_ENTRY_WORK->hash = 0;
        p = DOTR_CAMP_ENTRY_WORK;
        for (k = 0; k < 3; k++) {
            p->pick[k] = (D_00299CE0_21c510[w->hash] >> (k * 5)) & 0x1f;
            p->deck[k] = D_00299D00_21c510[p->pick[k]].id & 0x3ff;
        }
        SzModel_LoadMerge(3, 4, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 0;
        board->done0 = 0;
        board->done1 = 0;
        DOTR_CAMP_ENTRY_WORK->all = 0;
        DOTR_CAMP_ENTRY_CLEAR_SEEN();
        board->ticks = 10050;
        board->started = 1;
        func_00233F50_b(2);
        func_00217980_b(25, 1);
        break;
    case 10:
        DOTR_CAMP_ENTRY_WORK->hash = 0;
        p = DOTR_CAMP_ENTRY_WORK;
        for (k = 0; k < 3; k++) {
            p->pick[k] = (D_00299CE0_21c510[w->hash] >> (k * 5)) & 0x1f;
            p->deck[k] = D_00299D00_21c510[p->pick[k]].id & 0x3ff;
        }
        SzModel_LoadMerge(3, 4, 0);
        DOTR_CAMP_ENTRY_MODULES();
        board->side = 0;
        board->done0 = 0;
        board->done1 = 0;
        DOTR_CAMP_ENTRY_WORK->all = 0;
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

extern u16 D_00299CE0[];
extern Entry_0021D480 D_00299D00[];
extern s8 D_0034F6F8;

void Taku_Camp_Data_Init(void) {
    u8 *base = (u8 *)0x01ED0000;
    u8 *record = (u8 *)&D_00299E10;
    f32 eye[4];
    f32 target[4];
    f32 up[4];
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

    func_00195108((s32)base, 0x54B0);
    eye[0] = 0.0f;
    eye[1] = 8.65f;
    eye[2] = 100.0f;
    target[0] = 0.0f;
    target[1] = 8.65f;
    target[2] = 0.0f;
    up[0] = 100.0f;
    up[1] = 8.65f;
    up[2] = 0.0f;
    Ex3d_GetSurfaceC(eye, target, up, (f32 *)0x01ED0190);
    i = 0;
    do {
        base[0x53CF + i] = 0;
        base[0x53DB + i] = 6;
        base[0x53E7 + i] = 1;
        i++;
    } while (i < 12);
    *(s16 *)0x01ED547C = 0x80;
    *(s16 *)0x01ED0000 = 0x140;
    *(s16 *)0x01ED0002 = 0xBE;
    *(s16 *)0x01ED0004 = 0;
    *(s16 *)0x01ED001A = 0;
    *(s16 *)0x01ED001C = 0;
    *(s16 *)0x01ED001E = 0;
    *(s16 *)0x01ED536E = *(s16 *)(record + 0xC2);
    *(s16 *)0x01ED536C = 0;
    *(s8 *)0x01ED5372 = 0;
    *(s8 *)0x01ED006E = 0;
    *(f32 *)0x01ED0040 = 0.0f;
    *(f32 *)0x01ED0044 = 0.0f;
    *(f32 *)0x01ED0048 = 0.0f;
    *(f32 *)0x01ED004C = 0.0f;
    *(f32 *)0x01ED0030 = *(f32 *)0x01ED0040;
    *(f32 *)0x01ED0034 = 96.0f + *(f32 *)0x01ED0044;
    *(f32 *)0x01ED0038 = 96.0f + *(f32 *)0x01ED0048;
    *(f32 *)0x01ED003C = *(f32 *)0x01ED004C;
    SzView_SetCamera(0, (void *)0x01ED0030, (void *)0x01ED0040);

    i = 0;
    words = (u32 *)0x01ED0000;
    do {
        words[0x8C / 4] = 0;
        words[0x10C / 4] = 0;
        words++;
        i++;
    } while (i < 32);
    *(s16 *)0x01ED01A6 = 0;
    *(s16 *)0x01ED01AE = 0;
    *(s16 *)0x01ED01B0 = 0;
    *(s16 *)0x01ED01B2 = 0;
    *(s16 *)0x01ED0224 = 0x80;
    rows = (u8 *)0x01ED0000;
    *(s16 *)0x01ED0226 = 0x80;
    *(s16 *)0x01ED0228 = 0x80;
    outer = 0;
    counts = (u8 *)0x01ED0000;
    data = (u8 *)0x01ED0000;
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
        clear = (u16 *)0x01ED0000;
        do {
            clear_count++;
            clear[0x52EC / 2] = 0;
            clear[0x532C / 2] = 0;
            clear++;
        } while (clear_count < 32);
    }

    if (D_0034F6F8 != 0) {
        *(Buffer_0021D480 *)SzData_GetData(0) = *(Buffer_0021D480 *)0x01E301E0;
        D_0034F6F8 = 0;
    }
    n = 0;
    total = 0;
    for (; n < 12; n++) {
        total += (s32)*(u16 *)(record + 0x24) % 16;
        record += 2;
    }
    *(u16 *)0x01ED53F6 = total & 0xF;
    j = 0;
    shift = 0;
    halves = (u16 *)0x01ED0000;
    for (; j < 3; j++) {
        halves[0x53F8 / 2] = ((s32)D_00299CE0[*(u16 *)(base + 0x53F6)] >> shift) & 0x1F;
        shift += 5;
        halves[0x53FE / 2] = D_00299D00[halves[0x53F8 / 2]].value & 0x3FF;
        halves++;
    }
}

typedef struct Coord_0021D850 {
    f32 x;
    f32 y;
    f32 z;
} Coord_0021D850;

extern u8 D_00298BA0[];
extern u8 D_00298BA8[];
extern s8 D_00299ED6;
extern s8 D_00299ED7;
extern u8 D_00299F60;

void Taku_Screen_Init(void) {
    s16 var_s0;
    u8 *var_s1;
    s32 *var_s2;
    Coord_0021D850 pos;

    Taku_Coord_Set(&D_00299F60);
    *(f32 *)0x01ED0040 = *(f32 *)(D_00298BA0 + D_00299ED6 * 0x34);
    *(f32 *)0x01ED0044 = 0.0f;
    *(f32 *)0x01ED0048 = *(f32 *)(D_00298BA8 + D_00299ED6 * 0x34);
    *(f32 *)0x01ED0040 = *(f32 *)(D_00298BA0 + D_00299ED7 * 0x34);
    *(f32 *)0x01ED0044 = 0.0f;
    *(f32 *)0x01ED0048 = *(f32 *)(D_00298BA8 + D_00299ED7 * 0x34);
    *(f32 *)0x01ED0030 = *(f32 *)0x01ED0040;
    *(f32 *)0x01ED0034 = 96.0f + *(f32 *)0x01ED0044;
    *(f32 *)0x01ED0038 = 96.0f + *(f32 *)0x01ED0048;
    *(f32 *)0x01ED003C = *(f32 *)0x01ED004C;
    SzView_SetCamera(0, (void *)0x01ED0030, (void *)0x01ED0040);
    var_s1 = D_00298BA0;
    var_s0 = 0;
    var_s2 = (s32 *)0x01ED0000;
    while (var_s0 <= 0x15) {
        pos.x = *(f32 *)var_s1;
        pos.y = 8.65f + *(f32 *)(var_s1 + 4);
        pos.z = *(f32 *)(var_s1 + 8);
        Taku_3D_2D_Set((s32 *)((u8 *)var_s2 + 0x8C), (s32 *)((u8 *)var_s2 + 0x10C), (s32)&pos);
        var_s1 += 0x34;
        var_s2++;
        var_s0++;
    }
    *(s16 *)0x01ED0000 = 0x140;
    *(s16 *)0x01ED0002 = 0xBE;
}

void TkCamp_Draw(void) {
    if (D_0034F710 == 0) {
        RhBase_SetVifPacketArea(TkCamp_Draw_Pipe(RhBase_GetVifPacketArea()));
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec4_0021DAA0;

extern s16 D_00298AD0;
extern s16 D_00298AD2;
extern s16 D_00298AD4;
extern s16 D_00298ADA;
extern Vec4_0021DAA0 D_0029A7B0;
extern Vec4_0021DAA0 D_0029A7C0;

static inline s32 offset_y_0021DAA0(s32 y) {
    return (s16)y - 0x100;
}

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

    state = &D_00299E10;
    angle = ((*(s16 *)0x01ED5478 << 10) >> 12) - 0x200;
    if (D_0034F710 == 0) {
        var_s6 = Taku_Camp_2D(RhBase_GetVifPacketArea());
        temp_v0 = *(s16 *)0x01ED006C;
        if (temp_v0 != 0) {
            temp_a1 = *(s8 *)0x01ED5440;
            y_offset = offset_y_0021DAA0(temp_v0);
            x_offset = (temp_a1 * -0x280) / 100;
            if (*(s8 *)0x01ED5488 != 0) {
                var_s6 = Taku_G4_Set(var_s6, &D_00298AD0, x_offset, y_offset);
                *(s8 *)0x01ED5488 = 0;
            }
            if (SzModel_IsModelLoading(0x1F) == 0) {
                if ((*(s8 *)0x01ED5406 == 1) && (*(s16 *)0x01ED006C != 0)) {
                    sp80 = D_0029A7B0;
                    sp90 = D_0029A7C0;
                    *(s16 *)0x01ED5404 = SzData_GetLeader(1, 0);
                    SzModel_SetPos(0x1F, &sp80);
                    SzModel_SetRot(0x1F, &sp90);
                    SzModel_Load(0x1F, -1, SzDuel_New2Xax(*(s16 *)0x01ED5404), 1);
                    *(s8 *)0x01ED5406 = 2;
                    *(s16 *)0x01ED543A = 0;
                }
            }
            if ((SzModel_IsModelStandby(0x1F) != 0) && (*(s8 *)0x01ED5406 == 2)) {
                temp_v0_2 = *(s16 *)0x01ED543A;
                if (temp_v0_2 < 0x80) {
                    *(s16 *)0x01ED543A = temp_v0_2 + 8;
                }
                if (*(s16 *)0x01ED543A >= 0x80) {
                    *(s16 *)0x01ED543A = 0x80;
                }
                temp_s4 = D_00298AD2;
                temp_s5 = D_00298AD0;
                var_s6 = Taku_Camp_Teki_Model_Disp(var_s6, 0x1F, temp_s5 + x_offset,
                    temp_s4 + y_offset, (f32)SzDuel_GetCamDist(*(s16 *)0x01ED5404),
                    D_00298AD4 - temp_s5, D_00298ADA - temp_s4, *(s16 *)0x01ED543A);
            }
        }
        if (*(s8 *)0x01ED5472 != 0) {
            var_s6 = Taku_Camp_Card_Get(var_s6, (f32)angle, *state ^ 1, 0.0f, *(s32 *)0x01ED5474);
        }
        *(s8 *)0x01ED5481 = 0;
        RhBase_SetVifPacketArea((s32) var_s6);
    }
}

s32 TkCamp_Draw_Pipe(s32 arg0) {
    extern s16 D_00299ED2;
    extern s32 Taku_Camp_3D();
    extern s32 Taku_Camp_Kumo();
    u8 *rec;
    s32 v;

    rec = (u8 *)&D_00299E10;
    if (D_00299ED2 >= 0x2710) {
        v = *(s16 *)(rec + 0xC2);
        switch (v) {
        case 0x2B98:
            if (*(s16 *)0x01ED536C < 2) {
                arg0 = Taku_Camp_3D(arg0);
            } else {
                arg0 = Taku_Camp_STON(arg0);
            }
            break;
        case 0x2B9A:
            if (*(s16 *)0x01ED536C >= 9) {
                arg0 = Taku_Camp_3D(arg0);
            } else {
                arg0 = Taku_Camp_STON(arg0);
            }
            break;
        case 0x2BAC:
            if (*(s16 *)0x01ED536C >= 2) {
                arg0 = Taku_Camp_STON(arg0);
            } else {
                arg0 = Taku_Camp_3D(arg0);
            }
            break;
        case 0x2F64:
            if (*(s16 *)0x01ED536C < 0xA) {
                arg0 = Taku_Camp_STON(arg0);
            } else {
                arg0 = Taku_Camp_3D(arg0);
            }
            break;
        case 0x2F76:
            if (*(s16 *)0x01ED536C > 1) {
                arg0 = Taku_Camp_STON(arg0);
            } else {
                arg0 = Taku_Camp_3D(arg0);
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
            arg0 = Taku_Camp_STON(arg0);
            break;
        default:
            if (v < 0x2AF8) {
                arg0 = Taku_Camp_STON(arg0);
            } else {
                arg0 = Taku_Camp_3D(arg0);
            }
            break;
        }
    } else {
        arg0 = Taku_Camp_3D(arg0);
    }
    if (*(s16 *)(rec + 0xC2) >= 0x2710) {
        arg0 = Taku_Camp_Kumo(arg0);
    }
    return arg0;
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
