#include "common.h"

void Taku_Camp_Set_Go_Duel(void) {
    s16 temp_s0;

    temp_s0 = D_00299ED4;
    SzGame_SetMenuNum(1, (s32) temp_s0);
    SzGame_SetMenuNum(2, (s32) save_data);
    if (save_data == 0) {
        SzGame_SetMenuNum(3, 0x44C);
        SzGame_SetMenuNum(4, temp_s0 + 0x3E8);
    } else {
        SzGame_SetMenuNum(3, temp_s0 + 0x3E8);
        SzGame_SetMenuNum(4, 0x44C);
    }
    SzGame_Push(1, 0);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

typedef int DotrDareWord;
struct DotrDareItem {
    short w[8];
    short unknown_10[10];
    short code;
};
struct DotrDareWindow {
    unsigned short x, y, w, h;
    char unknown_08[2];
};
struct DotrDareInfo {
    int unknown_00[3];
    int w;
};
struct DotrDareFace {
    unsigned char id, no, kind, mode;
    unsigned short x, y;
};
extern struct DotrDareWindow camp_window_Teki_data[];
extern struct DotrDareItem tex_bara_data2[];
extern struct DotrDareItem camp_window_teki3[];
extern unsigned char D_002999CC[][4];
#define DOTR_DARE_SLIDE0 (*(short *)0x1ed53b6)
#define DOTR_DARE_SLIDE1 (*(short *)0x1ed53b8)
#define DOTR_DARE_NAME0 (*(short *)0x1ed53ba)
#define DOTR_DARE_NAME1 (*(short *)0x1ed53bc)
#define DOTR_DARE_SIDE0 (*(signed char *)0x1ed53be)
#define DOTR_DARE_SIDE1 (*(signed char *)0x1ed53bf)
#define DOTR_DARE_STATE0 (*(signed char *)0x1ed5407)
#define DOTR_DARE_STATE1 (*(signed char *)0x1ed5408)
#define DOTR_DARE_FACE0 ((struct DotrDareFace *)0x1ed540c)
#define DOTR_DARE_FACE1 ((struct DotrDareFace *)0x1ed5414)
#define DOTR_DARE_LOOK1 (*(signed char *)0x1ed5469)
#define DOTR_DARE_LOOK0 (*(signed char *)0x1ed546a)
extern DotrDareWord Taku_Window_Set_b(DotrDareWord cursor, struct DotrDareWindow *window,
                                    unsigned short flag, int a3, unsigned short x, int y,
                                    int a6, int a7, int a8);
extern DotrDareWord func_00217BD0_b(DotrDareWord cursor, struct DotrDareItem *item, short x,
                                 short y);
extern DotrDareWord func_00218020_b(DotrDareWord cursor, struct DotrDareItem *item, short x,
                                 short y, int a4);
extern struct DotrDareInfo *func_001FEAB0_b(int index);
extern void func_001FDFE0_b(void);
extern DotrDareWord func_001FE660_b(DotrDareWord cursor, int index, int x, int y,
                                          float sx, float sy, void *e,
                                          void (*function)(void));

int Taku_Camp_BUN_DARE(int cursor)
{
    short xx, yy;
    unsigned char col[4];

    col[0] = col[1] = col[2] = 128;
    col[3] = 128;
    xx = 0;
    yy = 0;
    if (DOTR_DARE_SLIDE0 != 0) {
        short x;
        short y;
        signed char n;
        int no;
        short w;
        struct DotrDareInfo *info;

        w = DOTR_DARE_SLIDE0;
        x = (w * 640 >> 10) - 640;
        y = (w * 256 >> 10) - 256;
        n = DOTR_DARE_SIDE0;
        cursor = func_00217BD0_b(cursor, &tex_bara_data2[n], x + xx, 0);
        cursor = Taku_Window_Set_b(cursor, &camp_window_Teki_data[0], n, 0, x + xx, 0, 0, 128, 128);
        no = DOTR_DARE_NAME0 - 195;
        switch (DOTR_DARE_STATE0) {
        case 1:
            DOTR_DARE_FACE0->id = 255;
            
        case 2:
            DOTR_DARE_FACE0->no = no;
            DOTR_DARE_FACE0->kind = D_002999CC[no][DOTR_DARE_LOOK0];
            DOTR_DARE_FACE0->mode = 1;
            DOTR_DARE_FACE0->x = camp_window_Teki_data[3].x + xx;
            DOTR_DARE_FACE0->y = y + (camp_window_Teki_data[3].y + yy);
            ShFace_Request(DOTR_DARE_FACE0);
            DOTR_DARE_STATE0 = 2;
            break;
        case 10:
            DOTR_DARE_FACE0->no = no;
            DOTR_DARE_FACE0->kind = D_002999CC[no][DOTR_DARE_LOOK0];
            DOTR_DARE_FACE0->mode = 3;
            DOTR_DARE_FACE0->x = camp_window_Teki_data[3].x + xx;
            DOTR_DARE_FACE0->y = y + (camp_window_Teki_data[3].y + yy);
            ShFace_Request(DOTR_DARE_FACE0);
            DOTR_DARE_STATE0 = 2;
            break;
        case 100:
            ShFace_Close(DOTR_DARE_FACE0);
            DOTR_DARE_STATE0 = 0;
            break;
        }
        cursor = Taku_Window_Set_b(cursor, &camp_window_Teki_data[3], n, 0, xx, (unsigned short)(y + yy), 1, 128, 0);
        cursor = func_00218020_b(cursor, &camp_window_teki3[2], xx, y + yy, 0);
        cursor = func_00218020_b(cursor, &camp_window_teki3[3], xx, y + yy, 0);
        cursor = func_00218020_b(cursor, &camp_window_teki3[n], xx, y + yy, 0);
        cursor = SzMsg_LoadFont_Pipe(cursor, 1, DOTR_DARE_NAME0, 0, 22);
        cursor = RhText_SetTextureFlush(cursor);
        info = func_001FEAB0_b(1);
        if (info->w < 324) {
            cursor = func_001FE660_b(cursor, 1, x + 53, 21, 1.0f, 1.0f, col, func_001FDFE0_b);
        } else {
            cursor = func_001FE660_b(cursor, 1, x + 53, 21, 324.0f / (float)info->w, 1.0f, col, func_001FDFE0_b);
        }
        SzMsg_Free(1);
    }
    if (DOTR_DARE_SLIDE1 != 0) {
        short x;
        short y;
        signed char n;
        int no;
        short w;
        struct DotrDareInfo *info;

        w = DOTR_DARE_SLIDE1;
        x = 640 - (w * 640 >> 10);
        y = 256 - (w * 256 >> 10);
        n = DOTR_DARE_SIDE1;
        cursor = func_00217BD0_b(cursor, &tex_bara_data2[n], x + 144, 304);
        cursor = Taku_Window_Set_b(cursor, &camp_window_Teki_data[0], n, 0, x + 144, 304, 0, 128, 128);
        xx = -480;
        yy = 320;
        no = DOTR_DARE_NAME1 - 195;
        switch (DOTR_DARE_STATE1) {
        case 1:
            DOTR_DARE_FACE1->id = 255;
            
        case 2:
            DOTR_DARE_FACE1->no = no;
            DOTR_DARE_FACE1->kind = D_002999CC[no][DOTR_DARE_LOOK1];
            DOTR_DARE_FACE1->mode = 1;
            DOTR_DARE_FACE1->x = camp_window_Teki_data[3].x + xx;
            DOTR_DARE_FACE1->y = y + (camp_window_Teki_data[3].y + yy);
            ShFace_Request(DOTR_DARE_FACE1);
            DOTR_DARE_STATE1 = 2;
            break;
        case 10:
            DOTR_DARE_FACE1->no = no;
            DOTR_DARE_FACE1->kind = D_002999CC[no][DOTR_DARE_LOOK1];
            DOTR_DARE_FACE1->mode = 3;
            DOTR_DARE_FACE1->x = camp_window_Teki_data[3].x + xx;
            DOTR_DARE_FACE1->y = y + (camp_window_Teki_data[3].y + yy);
            ShFace_Request(DOTR_DARE_FACE1);
            DOTR_DARE_STATE1 = 2;
            break;
        case 100:
            ShFace_Close(DOTR_DARE_FACE1);
            DOTR_DARE_STATE1 = 0;
            break;
        }
        cursor = Taku_Window_Set_b(cursor, &camp_window_Teki_data[3], n, 0, xx, (unsigned short)(y + yy), 1, 128, 0);
        cursor = func_00218020_b(cursor, &camp_window_teki3[4], xx, y + 184, 2);
        cursor = func_00218020_b(cursor, &camp_window_teki3[5], xx, y + 184, 2);
        cursor = func_00218020_b(cursor, &camp_window_teki3[n], xx, y + 176, 0);
        cursor = SzMsg_LoadFont_Pipe(cursor, 1, DOTR_DARE_NAME1, 0, 22);
        cursor = RhText_SetTextureFlush(cursor);
        info = func_001FEAB0_b(1);
        if (info->w < 324) {
            cursor = func_001FE660_b(cursor, 1, x + 197, 325, 1.0f, 1.0f, col, func_001FDFE0_b);
        } else {
            cursor = func_001FE660_b(cursor, 1, x + 197, 325, 324.0f / (float)info->w, 1.0f, col, func_001FDFE0_b);
        }
        SzMsg_Free(1);
    }
    return cursor;
}
#undef DOTR_DARE_SLIDE0
#undef DOTR_DARE_SLIDE1
#undef DOTR_DARE_NAME0
#undef DOTR_DARE_NAME1
#undef DOTR_DARE_SIDE0
#undef DOTR_DARE_SIDE1
#undef DOTR_DARE_STATE0
#undef DOTR_DARE_STATE1
#undef DOTR_DARE_FACE0
#undef DOTR_DARE_FACE1
#undef DOTR_DARE_LOOK1
#undef DOTR_DARE_LOOK0

void Taku_Camp_SINEMA_Init(s8 arg0) {
    *(s16 *)0x01ED001C = 0;
    switch (arg0) {
    case 0:
        *(s16 *)0x01ED001A = 0;
        *(s16 *)0x01ED001E = 0;
        *(s16 *)0x01ED0020 = 0;
        *(s16 *)0x01ED0022 = 0;
        break;
    case 1:
        *(s16 *)0x01ED001A = 1;
        *(s16 *)0x01ED001E = 0x40;
        *(s16 *)0x01ED0020 = 0;
        *(s16 *)0x01ED0022 = 0;
        break;
    case 2:
        *(s16 *)0x01ED001A = 2;
        *(s16 *)0x01ED001E = 0x40;
        *(s16 *)0x01ED0020 = 0x40;
        *(s16 *)0x01ED0022 = 0;
        break;
    case 3:
        *(s16 *)0x01ED001A = 3;
        *(s16 *)0x01ED001E = 0x40;
        *(s16 *)0x01ED0020 = 0x40;
        *(s16 *)0x01ED0022 = 0x74;
        break;
    }
}

typedef int DotrTikeiWord;
struct DotrTikeiItem {
    short w[8];
    short unknown_10[10];
    short code;
};
extern DotrTikeiWord func_00218970_b(DotrTikeiWord cursor, struct DotrTikeiItem *quad, short dx,
                                 short dy);
struct DotrSinemaWork {
    short unknown_00[13];
    short mode;                 
    short state;                
    short cut0;                 
    short cut1;                 
    short cut2;                 
    char unknown_24[72];
    short hold;                 
};
#define DOTR_SINEMA_BLOCK ((struct DotrSinemaWork *)0x1ed0000)
#define DOTR_SINEMA_MODE (*(short *)0x1ed001a)
#define DOTR_SINEMA_STATE (*(short *)0x1ed001c)
#define DOTR_SINEMA_CUT0 (*(short *)0x1ed001e)
#define DOTR_SINEMA_CUT1 (*(short *)0x1ed0020)
#define DOTR_SINEMA_CUT2 (*(short *)0x1ed0022)
#define DOTR_SINEMA_HOLD (*(short *)0x1ed006c)
struct DotrSinemaQuad {
    short w[8];
    unsigned char col[16];
    signed char flag;
    char unknown_21;
    short z;
    short code;
};
extern struct DotrSinemaQuad D_0029AEC0;
extern struct DotrSinemaQuad tex_sinema_brack[2];
#define DOTR_SINEMA_C0 (b->cut0 * 64 / 64)
#define DOTR_SINEMA_C1 (b->cut1 * 64 / 64)
#define DOTR_SINEMA_C2 (b->cut2 * 116 / 116)

int Taku_Camp_SINEMA_CUT(int cursor, unsigned short fade)
{
    struct DotrSinemaWork *b = DOTR_SINEMA_BLOCK;
    struct DotrSinemaQuad q = D_0029AEC0;
    int i;
    int j;
    int n;

    if (fade == 0) {
        if (DOTR_SINEMA_STATE == 1 && DOTR_SINEMA_HOLD == 0) {
            n = 0;
            if (DOTR_SINEMA_MODE == 0) {
                if (0 <= DOTR_SINEMA_CUT0) {
                    DOTR_SINEMA_CUT0 -= 8;
                    if (DOTR_SINEMA_CUT0 <= 0) {
                        DOTR_SINEMA_CUT0 = 0;
                        n++;
                    }
                }
                if (0 <= DOTR_SINEMA_CUT1) {
                    DOTR_SINEMA_CUT1 -= 8;
                    if (DOTR_SINEMA_CUT1 <= 0) {
                        DOTR_SINEMA_CUT1 = 0;
                        n++;
                    }
                }
                if (0 <= DOTR_SINEMA_CUT2) {
                    DOTR_SINEMA_CUT2 -= 8;
                    if (DOTR_SINEMA_CUT2 <= 0) {
                        DOTR_SINEMA_CUT2 = 0;
                        n++;
                    }
                }
            } else if (DOTR_SINEMA_MODE == 1) {
                if (DOTR_SINEMA_CUT0 <= 64) {
                    DOTR_SINEMA_CUT0 += 8;
                    if (DOTR_SINEMA_CUT0 >= 64) {
                        DOTR_SINEMA_CUT0 = 64;
                        n++;
                    }
                }
                if (0 <= DOTR_SINEMA_CUT1) {
                    DOTR_SINEMA_CUT1 -= 8;
                    if (DOTR_SINEMA_CUT1 <= 0) {
                        DOTR_SINEMA_CUT1 = 0;
                        n++;
                    }
                }
                if (0 <= DOTR_SINEMA_CUT2) {
                    DOTR_SINEMA_CUT2 -= 8;
                    if (DOTR_SINEMA_CUT2 <= 0) {
                        DOTR_SINEMA_CUT2 = 0;
                        n++;
                    }
                }
            } else if (DOTR_SINEMA_MODE == 2) {
                if (DOTR_SINEMA_CUT0 < 64) {
                    DOTR_SINEMA_CUT0 += 8;
                    if (DOTR_SINEMA_CUT0 >= 64) {
                        DOTR_SINEMA_CUT0 = 64;
                        n++;
                    }
                } else {
                    DOTR_SINEMA_CUT0 = 64;
                    n++;
                    if (DOTR_SINEMA_CUT1 <= 64) {
                        DOTR_SINEMA_CUT1 += 8;
                        if (DOTR_SINEMA_CUT1 >= 64) {
                            DOTR_SINEMA_CUT1 = 64;
                            n++;
                        }
                    }
                }
                if (0 <= DOTR_SINEMA_CUT2) {
                    DOTR_SINEMA_CUT2 -= 8;
                    if (DOTR_SINEMA_CUT2 <= 0) {
                        DOTR_SINEMA_CUT2 = 0;
                        n++;
                    }
                }
            } else if (DOTR_SINEMA_MODE == 3) {
                if (DOTR_SINEMA_CUT0 < 64) {
                    DOTR_SINEMA_CUT0 += 8;
                    if (DOTR_SINEMA_CUT0 >= 64) {
                        DOTR_SINEMA_CUT0 = 64;
                        n++;
                    }
                } else if (DOTR_SINEMA_CUT1 < 64) {
                    DOTR_SINEMA_CUT0 = 64;
                    DOTR_SINEMA_CUT1 += 8;
                    n++;
                    if (DOTR_SINEMA_CUT1 >= 64) {
                        DOTR_SINEMA_CUT1 = 64;
                        n++;
                    }
                } else {
                    DOTR_SINEMA_CUT0 = 64;
                    DOTR_SINEMA_CUT1 = 64;
                    DOTR_SINEMA_CUT2 += 8;
                    n += 2;
                    if (DOTR_SINEMA_CUT2 >= 116) {
                        DOTR_SINEMA_CUT2 = 116;
                        n++;
                    }
                }
            }
            if (n >= 3) {
                DOTR_SINEMA_STATE = 2;
            }
        }
        for (i = 0; i < 2; i++) {
            q = tex_sinema_brack[i];
            
            if (i == 0) {
                q.w[5] = DOTR_SINEMA_C2 + (tex_sinema_brack[i].w[1] + DOTR_SINEMA_C0 + DOTR_SINEMA_C1);
                q.w[7] = DOTR_SINEMA_C2 + (tex_sinema_brack[i].w[1] + DOTR_SINEMA_C0 + DOTR_SINEMA_C1);
            } else {
                q.w[1] = tex_sinema_brack[i].w[1] - DOTR_SINEMA_C0 - DOTR_SINEMA_C1 - DOTR_SINEMA_C2;
                q.w[3] = tex_sinema_brack[i].w[1] - DOTR_SINEMA_C0 - DOTR_SINEMA_C1 - DOTR_SINEMA_C2;
            }
            for (j = 0; j < 16; j++) {
                if (j % 4 == 3) {
                    q.col[j] = 128;
                } else {
                    q.col[j] = 0;
                }
            }
            q.flag = 0;
            cursor = func_00218970_b(cursor, (struct DotrTikeiItem *)&q, 0, 0);
        }
    } else {
        if (DOTR_SINEMA_STATE == 1) {
            if (DOTR_SINEMA_MODE == 0) {
                if (DOTR_SINEMA_CUT0 < 255) {
                    DOTR_SINEMA_CUT0 += 32;
                    if (DOTR_SINEMA_CUT0 >= 255) {
                        DOTR_SINEMA_CUT0 = 255;
                        DOTR_SINEMA_MODE = 1;
                        DOTR_SINEMA_STATE = 0;
                    }
                } else {
                    DOTR_SINEMA_MODE = 1;
                    DOTR_SINEMA_CUT0 = 255;
                    DOTR_SINEMA_STATE = 0;
                }
            } else {
                if (0 < DOTR_SINEMA_CUT0) {
                    DOTR_SINEMA_CUT0 -= 32;
                    if (DOTR_SINEMA_CUT0 <= 0) {
                        DOTR_SINEMA_CUT0 = 0;
                        DOTR_SINEMA_MODE = 0;
                        DOTR_SINEMA_STATE = 0;
                    }
                } else {
                    DOTR_SINEMA_MODE = 0;
                    DOTR_SINEMA_CUT0 = 0;
                    DOTR_SINEMA_STATE = 0;
                }
            }
        }
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 8; j++) {
                q.w[j] = tex_sinema_brack[i].w[j];
            }
            q.col[3] = q.col[7] = q.col[11] = q.col[15] = b->cut0;
            cursor = func_00218970_b(cursor, (struct DotrTikeiItem *)&q, 0, 0);
        }
    }
    return cursor;
}
#undef DOTR_SINEMA_BLOCK
#undef DOTR_SINEMA_MODE
#undef DOTR_SINEMA_STATE
#undef DOTR_SINEMA_CUT0
#undef DOTR_SINEMA_CUT1
#undef DOTR_SINEMA_CUT2
#undef DOTR_SINEMA_HOLD
#undef DOTR_SINEMA_C0
#undef DOTR_SINEMA_C1
#undef DOTR_SINEMA_C2

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrStWindowItem {
    short w[8];
    short unknown_10[10];
    short code;                 
};
struct DotrStWindowWindow {
    short x, y, w, h;
    char unknown_08[2];
};
struct DotrStWindowRec {
    char unknown_00[16];
    short kind;                 
    char unknown_12[34];
};
struct DotrStWindowInfo {
    int unknown_00[3];
    int w;                      
};
struct DotrStWindowBoard {
    signed char mode;           
    signed char unknown_01[2];
    signed char seen[59];       
    short wins[2];              
    char unknown_42[132];
    signed char kind;           
};
extern struct DotrStWindowBoard D_00299E10_b;
extern struct DotrStWindowRec model_data[];
extern struct DotrStWindowWindow camp_window_My_data[];
extern struct DotrStWindowItem tex_bara_data[];
extern struct DotrStWindowItem tex_deck_data[];
extern struct DotrStWindowItem tex_batti_data[];
extern struct DotrStWindowItem tex_hosi_data[];
extern struct DotrStWindowItem camp_card[];
extern struct DotrStWindowItem camp_window_data[];
extern char D_0030F0F7[];
extern char D_0030F0FC[];
#define DOTR_ST_WINDOW_BASE 0x1ed0000
struct DotrStWindowBank {
    char unknown_000[0x226];
    short depth;                
};
extern int Taku_Window_Set_window(int cursor, struct DotrStWindowWindow *window, unsigned short flag, int a3,
                           unsigned short x, unsigned short a5, int a6, int a7, int a8);
extern int Taku_Obj_Set_b(int cursor, struct DotrStWindowItem *item, short x, short y);
extern int SzData_GetRank_b(int side, int id);
extern struct DotrStWindowInfo *SzMsg_GetInfo_b(int index);
extern void SzMsg_DrawRect_Pipe_b(void);
extern int SzMsg_DrawRatioX_Pipe_b(int cursor, int index, int x, int y, float sx, float sy, void *e,
                                 void (*function)(void));
extern int SzDuel_DrawWindow_FontDigit_Pipe_b(int cursor, int x, int y, int a, int flags, int width,
                                            int value);
extern int SzDuel_DrawWindow_Font_Pipe_b(int cursor, int x, int y, int a, int flags, int n,
                                       const char *text, int c);
#define ST_MODE (*(signed char *)(DOTR_ST_WINDOW_BASE + 0x18c))
#define ST_SLIDE (*(short *)(DOTR_ST_WINDOW_BASE + 0x70))
#define ST_OPEN (*(short *)(DOTR_ST_WINDOW_BASE + 0x6c))
#define ST_LOC11 (*(signed char *)(DOTR_ST_WINDOW_BASE + 0x53c2))
#define ST_DEPTH (*(short *)(DOTR_ST_WINDOW_BASE + 0x226))
#define ST_COST (*(short *)(DOTR_ST_WINDOW_BASE + 0x5442))

int Taku_Camp_ST_WINDOW(int cursor)
{
    struct DotrStWindowBoard *w;
    struct DotrStWindowBank *g;
    unsigned char col[4];
    short y;
    int t;
    int i;
    short deck;
    short cost;
    int leader;
    short rank;
    int r;
    short j;
    short k;
    short cnt;
    int n;
    unsigned short x;
    short xx, yy;
    struct DotrStWindowInfo *info;
    float sx;
    float sy;

    w = &D_00299E10_b;
    y = 128 - (ST_SLIDE * 128 >> 8);
    col[0] = col[1] = col[2] = 128;
    col[3] = 128;
    g = (struct DotrStWindowBank *)DOTR_ST_WINDOW_BASE;
    if (ST_MODE) {
        if (w->kind == 11) {
            if (ST_LOC11 < 2) { t = 1; } else { t = 0; }
        } else if (model_data[w->kind].kind == 8) {
            t = 0;
        } else {
            t = 1;
        }
        if (w->mode == (signed char)t) {
            cursor = Taku_Obj_Set_b(cursor, &tex_bara_data[w->mode], 0, y);
            for (i = 0; i < 3; i++) {
                cursor = Taku_Window_Set_window(cursor, &camp_window_My_data[i], w->mode + 10, 0, 0, y, 0, 128, g->depth);
            }
            if (ST_OPEN == 256) {
                w->mode ^= 1;
            }
        } else {
            cursor = Taku_Obj_Set_b(cursor, &tex_bara_data[w->mode], 0, y);
            for (i = 0; i < 3; i++) {
                cursor = Taku_Window_Set_window(cursor, &camp_window_My_data[i], w->mode, 0, 0, y, 0, 128, g->depth);
            }
        }
    } else {
        cursor = Taku_Obj_Set_b(cursor, &tex_bara_data[w->mode], 0, y);
        for (i = 0; i < 3; i++) {
            cursor = Taku_Window_Set_window(cursor, &camp_window_My_data[i], w->mode, 0, 0, y, 0, 128, g->depth);
        }
    }
    cursor = Taku_Window_Set_window(cursor, &camp_window_My_data[16], w->mode, 0, 0, y, 0, 128, ST_DEPTH);
    deck = SzData_GetCurrentDeck(0);
    cursor = Taku_Obj_Set_b(cursor, &tex_deck_data[deck], 0, y);
    cost = SzData_GetDeckCost(0, deck);
    ST_COST = cost;
    leader = SzData_GetLeader(0, deck);
    rank = SzData_GetRank_b(0, leader);
    if (rank != 0) {
        r = rank - 1;
        cursor = Taku_Obj_Set_b(cursor, &tex_batti_data[(short)(r / 3)], 0, y);
        switch ((short)(r % 3 + 1)) {
        case 1:
            cursor = Taku_Obj_Set_b(cursor, &tex_hosi_data[2], 0, y);
            break;
        case 2:
            cursor = Taku_Obj_Set_b(cursor, &tex_hosi_data[0], 0, y);
            cursor = Taku_Obj_Set_b(cursor, &tex_hosi_data[1], 0, y);
            break;
        case 3:
            cursor = Taku_Obj_Set_b(cursor, &tex_hosi_data[0], 0, y);
            cursor = Taku_Obj_Set_b(cursor, &tex_hosi_data[1], 0, y);
            cursor = Taku_Obj_Set_b(cursor, &tex_hosi_data[2], 0, y);
            break;
        }
    }
    for (j = 0; j < 2; j++) {
        if (w->mode == 0) {
            if (j == 1) {
                for (n = 0; n < 8; n++) {
                    x = n * 16;
                    cursor = Taku_Obj_Set_b(cursor, &camp_card[j], x, y);
                }
            } else {
                for (k = 0, cnt = 0; k <= 21; k++) {
                    switch (k) {
                    case 2:
                    case 4:
                    case 5:
                    case 6:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                        if (w->seen[k] >= 3) {
                            cnt++;
                        }
                        break;
                    }
                }
                for (n = 0; n < cnt; n++) {
                    x = n * 16;
                    cursor = Taku_Obj_Set_b(cursor, &camp_card[j], x, y);
                }
            }
        } else {
            if (j == 0) {
                for (n = 0; n < 8; n++) {
                    x = n * 16;
                    cursor = Taku_Obj_Set_b(cursor, &camp_card[j], x, y);
                }
            } else {
                for (k = 0, cnt = 0; k <= 21; k++) {
                    switch (k) {
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 0:
                        if (w->seen[k] == 3) {
                            cnt++;
                        }
                        break;
                    }
                }
                for (n = 0; n < cnt; n++) {
                    x = n * 16;
                    cursor = Taku_Obj_Set_b(cursor, &camp_card[j], x, y);
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        cursor = Taku_Obj_Set_b(cursor, &camp_window_data[i], 0, y);
    }
    cursor = SzDuel_DrawWindow_FontDigit_Pipe_b(cursor, 157, y + 384, 1, 0, 4, cost);
    cursor = SzDuel_DrawWindow_FontDigit_Pipe_b(cursor, 253, y + 384, 1, 0, 4, w->wins[0]);
    cursor = SzDuel_DrawWindow_FontDigit_Pipe_b(cursor, 349, y + 384, 1, 0, 4, w->wins[1]);
    cursor = SzDuel_DrawWindow_Font_Pipe_b(cursor, 411, y + 375, 1, 1, 4, D_0030F0F7, 0);
    cursor = SzDuel_DrawWindow_Font_Pipe_b(cursor, 450, y + 375, 1, 1, 5, D_0030F0FC, 0);
    cursor = SzMsg_LoadFont_Pipe(cursor, 1, 3, 0, 22);
    cursor = RhText_SetTextureFlush(cursor);
    sx = sy = 1.0f;
    cursor = SzMsg_DrawRatioX_Pipe_b(cursor, 1, 54, y + 348, sx, sy, col, SzMsg_DrawRect_Pipe_b);
    SzMsg_Free(1);
    cursor = SzMsg_LoadFont_Pipe(cursor, 1, SzDuel_GetMsgName(leader), 0, 22);
    cursor = RhText_SetTextureFlush(cursor);
    xx = camp_window_My_data[2].x + 4;
    yy = camp_window_My_data[2].y + 2 + y;
    info = SzMsg_GetInfo_b(1);
    if (info->w < 248) {
        sy = sx = 1.0f;
        cursor = SzMsg_DrawRatioX_Pipe_b(cursor, 1, xx, yy, sx, sy, col, SzMsg_DrawRect_Pipe_b);
    } else {
        cursor = SzMsg_DrawRatioX_Pipe_b(cursor, 1, xx, yy, 248.0f / (float)info->w, 1.0f, col, SzMsg_DrawRect_Pipe_b);
    }
    SzMsg_Free(1);
    return cursor;
}
#undef DOTR_ST_WINDOW_BASE
#undef ST_MODE
#undef ST_SLIDE
#undef ST_OPEN
#undef ST_LOC11
#undef ST_DEPTH
#undef ST_COST

void *Taku_Camp_SYS_ICON(void *arg0) {
    s16 coords[19];
    u8 *state;
    s64 alpha;
    s32 i;
    s16 *row;
    u8 *fade;
    s32 y;
    s32 count;
    s16 *dst;
    s16 *src;
    s8 mode;
    s8 length;
    s8 *text;
    extern void *Taku_G4_Set();
    extern void *Taku_Obj_Set();
    extern void *SzDuel_DrawWindow_Font_Pipe();

    alpha = (s16)(0x80 - ((*(s16 *)0x01ED0070 << 7) >> 8));
    state = (u8 *)0x01ED0000;
    arg0 = Taku_G4_Set(arg0, D_002982F8, 0, alpha);
    row = camp_sys_icon;
    y = (s16)alpha + 0x14F;
    i = 0;
    fade = state;
    do {
        dst = coords;
        count = 19;
        src = row;
        do {
            count--;
            *dst = *src;
            src++;
            dst++;
        } while (count > 0);
        if (i == *(s16 *)(state + 0x80) && *(s8 *)(state + 0x7E) != 0) {
            *(s16 *)(fade + 0x82) += 4;
            if (*(s16 *)(fade + 0x82) >= 16) {
                *(s16 *)(fade + 0x82) = 16;
            }
            coords[0] = row[0] - ((*(s16 *)(fade + 0x82) * 6) >> 4);
            coords[1] = row[1] - ((*(s16 *)(fade + 0x82) * 6) >> 4);
            coords[2] = row[2] + ((*(s16 *)(fade + 0x82) * 6) >> 4);
            coords[3] = row[3] + ((*(s16 *)(fade + 0x82) * 6) >> 4);
        } else {
            if (0 < *(s16 *)(fade + 0x82)) {
                *(s16 *)(fade + 0x82) -= 4;
                if (*(s16 *)(fade + 0x82) <= 0) {
                    *(s16 *)(fade + 0x82) = 0;
                }
            }
        }
        arg0 = Taku_Obj_Set(arg0, coords, 0, alpha);
        mode = *(s8 *)(state + 0x7E);
        if (mode == 1 && i == *(s16 *)(state + 0x80) && mode != 0) {
            if (i == 0) {
                text = D_0030F102;
                length = 4;
            } else if (i == 1) {
                text = D_0030F107;
                length = 4;
            } else if (i == 2) {
                text = D_0030F10C;
                length = 6;
            } else {
                text = D_0030F113;
                length = 4;
            }
            arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, 0x232, y, 1, 1, length, text, 0);
        }
        i++;
        row += 19;
        fade += 2;
    } while (i < 4);
    if (*(s8 *)0x01ED007E == 0) {
        arg0 = Taku_Obj_Set(arg0, camp_sys_icon_botan, 0, alpha);
    } else {
        arg0 = Taku_Obj_Set(arg0, D_00298B76, 0, alpha);
    }
    if (*(s8 *)0x01ED007E == 0) {
        arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, 0x232, y, 1, 1, 6, D_0030F118, 0);
    }
    return arg0;
}
