/* Campaign map, part 2 of 3: going to a duel, who-is-talking text, cut scenes, status and icon windows (Taku_Camp_*). */

#include "common.h"
#include "campaign.h"

/* Starts the duel of the chosen campaign place. */
void Taku_Camp_Set_Go_Duel(void) {
    s16 place;

    place = SelectedBattleArena;
    SzGame_SetMenuNum(1, (s32) place);
    SzGame_SetMenuNum(2, (s32) campaignState);
    if (campaignState == 0) {
        SzGame_SetMenuNum(3, 0x44C);
        SzGame_SetMenuNum(4, place + 0x3E8);
    } else {
        SzGame_SetMenuNum(3, place + 0x3E8);
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
extern struct DotrDareWindow campaignEnemyWindow[]; /* original: camp_window_Teki_data */
extern struct DotrDareItem roseSprites2[]; /* original: tex_bara_data2 */
extern struct DotrDareItem campaignEnemyWindowItems[]; /* original: camp_window_teki3 */
extern unsigned char D_002999CC[][4];
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

/* Draws the speaker's name (dare: who) of a campaign text. (original: Taku_Camp_BUN_DARE) */
int Taku_Camp_TEXT_WHO(int cursor)
{
    short xx, yy;
    unsigned char col[4];

    col[0] = col[1] = col[2] = 128;
    col[3] = 128;
    xx = 0;
    yy = 0;
    if (campaignWork.duelistSlide[0] != 0) {
        short x;
        short y;
        signed char n;
        int no;
        short w;
        struct DotrDareInfo *info;

        w = campaignWork.duelistSlide[0];
        x = (w * 640 >> 10) - 640;
        y = (w * 256 >> 10) - 256;
        n = campaignWork.duelistSide[0];
        cursor = func_00217BD0_b(cursor, &roseSprites2[n], x + xx, 0);
        cursor = Taku_Window_Set_b(cursor, &campaignEnemyWindow[0], n, 0, x + xx, 0, 0, 128, 128);
        no = campaignWork.duelistName[0] - 195;
        switch (campaignWork.duelistState[0]) {
        case 1:
            campaignWork.duelistFace[0].id = 255;
            
        case 2:
            campaignWork.duelistFace[0].no = no;
            campaignWork.duelistFace[0].kind = D_002999CC[no][campaignWork.duelist0Look];
            campaignWork.duelistFace[0].mode = 1;
            campaignWork.duelistFace[0].x = campaignEnemyWindow[3].x + xx;
            campaignWork.duelistFace[0].y = y + (campaignEnemyWindow[3].y + yy);
            ShFace_Request(&campaignWork.duelistFace[0]);
            campaignWork.duelistState[0] = 2;
            break;
        case 10:
            campaignWork.duelistFace[0].no = no;
            campaignWork.duelistFace[0].kind = D_002999CC[no][campaignWork.duelist0Look];
            campaignWork.duelistFace[0].mode = 3;
            campaignWork.duelistFace[0].x = campaignEnemyWindow[3].x + xx;
            campaignWork.duelistFace[0].y = y + (campaignEnemyWindow[3].y + yy);
            ShFace_Request(&campaignWork.duelistFace[0]);
            campaignWork.duelistState[0] = 2;
            break;
        case 100:
            ShFace_Close((u8 *)&campaignWork.duelistFace[0]);
            campaignWork.duelistState[0] = 0;
            break;
        }
        cursor = Taku_Window_Set_b(cursor, &campaignEnemyWindow[3], n, 0, xx, (unsigned short)(y + yy), 1, 128, 0);
        cursor = func_00218020_b(cursor, &campaignEnemyWindowItems[2], xx, y + yy, 0);
        cursor = func_00218020_b(cursor, &campaignEnemyWindowItems[3], xx, y + yy, 0);
        cursor = func_00218020_b(cursor, &campaignEnemyWindowItems[n], xx, y + yy, 0);
        cursor = SzMsg_LoadFont_Pipe(cursor, 1, campaignWork.duelistName[0], 0, 22);
        cursor = RhText_SetTextureFlush(cursor);
        info = func_001FEAB0_b(1);
        if (info->w < 324) {
            cursor = func_001FE660_b(cursor, 1, x + 53, 21, 1.0f, 1.0f, col, func_001FDFE0_b);
        } else {
            cursor = func_001FE660_b(cursor, 1, x + 53, 21, 324.0f / (float)info->w, 1.0f, col, func_001FDFE0_b);
        }
        SzMsg_Free(1);
    }
    if (campaignWork.duelistSlide[1] != 0) {
        short x;
        short y;
        signed char n;
        int no;
        short w;
        struct DotrDareInfo *info;

        w = campaignWork.duelistSlide[1];
        x = 640 - (w * 640 >> 10);
        y = 256 - (w * 256 >> 10);
        n = campaignWork.duelistSide[1];
        cursor = func_00217BD0_b(cursor, &roseSprites2[n], x + 144, 304);
        cursor = Taku_Window_Set_b(cursor, &campaignEnemyWindow[0], n, 0, x + 144, 304, 0, 128, 128);
        xx = -480;
        yy = 320;
        no = campaignWork.duelistName[1] - 195;
        switch (campaignWork.duelistState[1]) {
        case 1:
            campaignWork.duelistFace[1].id = 255;
            
        case 2:
            campaignWork.duelistFace[1].no = no;
            campaignWork.duelistFace[1].kind = D_002999CC[no][campaignWork.duelist1Look];
            campaignWork.duelistFace[1].mode = 1;
            campaignWork.duelistFace[1].x = campaignEnemyWindow[3].x + xx;
            campaignWork.duelistFace[1].y = y + (campaignEnemyWindow[3].y + yy);
            ShFace_Request(&campaignWork.duelistFace[1]);
            campaignWork.duelistState[1] = 2;
            break;
        case 10:
            campaignWork.duelistFace[1].no = no;
            campaignWork.duelistFace[1].kind = D_002999CC[no][campaignWork.duelist1Look];
            campaignWork.duelistFace[1].mode = 3;
            campaignWork.duelistFace[1].x = campaignEnemyWindow[3].x + xx;
            campaignWork.duelistFace[1].y = y + (campaignEnemyWindow[3].y + yy);
            ShFace_Request(&campaignWork.duelistFace[1]);
            campaignWork.duelistState[1] = 2;
            break;
        case 100:
            ShFace_Close((u8 *)&campaignWork.duelistFace[1]);
            campaignWork.duelistState[1] = 0;
            break;
        }
        cursor = Taku_Window_Set_b(cursor, &campaignEnemyWindow[3], n, 0, xx, (unsigned short)(y + yy), 1, 128, 0);
        cursor = func_00218020_b(cursor, &campaignEnemyWindowItems[4], xx, y + 184, 2);
        cursor = func_00218020_b(cursor, &campaignEnemyWindowItems[5], xx, y + 184, 2);
        cursor = func_00218020_b(cursor, &campaignEnemyWindowItems[n], xx, y + 176, 0);
        cursor = SzMsg_LoadFont_Pipe(cursor, 1, campaignWork.duelistName[1], 0, 22);
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

/* Starts a campaign cut-scene (sinema) `scene`. (original: Taku_Camp_SINEMA_Init) */
void Taku_Camp_CINEMA_Init(s8 scene) {
    campaignWork.cinemaState = 0;
    switch (scene) {
    case 0:
        campaignWork.cinemaMode = 0;
        campaignWork.cinemaCut[0] = 0;
        campaignWork.cinemaCut[1] = 0;
        campaignWork.cinemaCut[2] = 0;
        break;
    case 1:
        campaignWork.cinemaMode = 1;
        campaignWork.cinemaCut[0] = 0x40;
        campaignWork.cinemaCut[1] = 0;
        campaignWork.cinemaCut[2] = 0;
        break;
    case 2:
        campaignWork.cinemaMode = 2;
        campaignWork.cinemaCut[0] = 0x40;
        campaignWork.cinemaCut[1] = 0x40;
        campaignWork.cinemaCut[2] = 0;
        break;
    case 3:
        campaignWork.cinemaMode = 3;
        campaignWork.cinemaCut[0] = 0x40;
        campaignWork.cinemaCut[1] = 0x40;
        campaignWork.cinemaCut[2] = 0x74;
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
struct DotrSinemaQuad {
    short w[8];
    unsigned char col[16];
    signed char flag;
    char unknown_21;
    short z;
    short code;
};
extern struct DotrSinemaQuad D_0029AEC0;
extern struct DotrSinemaQuad cinemaBlackBars[2]; /* original: tex_sinema_brack */
/* The bar heights; the "* 64 / 64" forms are the original's and change the instructions. */
#define DOTR_SINEMA_C0 (b->cinemaCut[0] * 64 / 64)
#define DOTR_SINEMA_C1 (b->cinemaCut[1] * 64 / 64)
#define DOTR_SINEMA_C2 (b->cinemaCut[2] * 116 / 116)

/* Draws a campaign cut-scene picture with fade `fade`. (original: Taku_Camp_SINEMA_CUT) */
int Taku_Camp_CINEMA_CUT(int cursor, unsigned short fade)
{
    CampaignWork *b = &campaignWork;
    struct DotrSinemaQuad q = D_0029AEC0;
    int i;
    int j;
    int n;

    if (fade == 0) {
        if (campaignWork.cinemaState == 1 && campaignWork.windowOpen == 0) {
            n = 0;
            if (campaignWork.cinemaMode == 0) {
                if (0 <= campaignWork.cinemaCut[0]) {
                    campaignWork.cinemaCut[0] -= 8;
                    if (campaignWork.cinemaCut[0] <= 0) {
                        campaignWork.cinemaCut[0] = 0;
                        n++;
                    }
                }
                if (0 <= campaignWork.cinemaCut[1]) {
                    campaignWork.cinemaCut[1] -= 8;
                    if (campaignWork.cinemaCut[1] <= 0) {
                        campaignWork.cinemaCut[1] = 0;
                        n++;
                    }
                }
                if (0 <= campaignWork.cinemaCut[2]) {
                    campaignWork.cinemaCut[2] -= 8;
                    if (campaignWork.cinemaCut[2] <= 0) {
                        campaignWork.cinemaCut[2] = 0;
                        n++;
                    }
                }
            } else if (campaignWork.cinemaMode == 1) {
                if (campaignWork.cinemaCut[0] <= 64) {
                    campaignWork.cinemaCut[0] += 8;
                    if (campaignWork.cinemaCut[0] >= 64) {
                        campaignWork.cinemaCut[0] = 64;
                        n++;
                    }
                }
                if (0 <= campaignWork.cinemaCut[1]) {
                    campaignWork.cinemaCut[1] -= 8;
                    if (campaignWork.cinemaCut[1] <= 0) {
                        campaignWork.cinemaCut[1] = 0;
                        n++;
                    }
                }
                if (0 <= campaignWork.cinemaCut[2]) {
                    campaignWork.cinemaCut[2] -= 8;
                    if (campaignWork.cinemaCut[2] <= 0) {
                        campaignWork.cinemaCut[2] = 0;
                        n++;
                    }
                }
            } else if (campaignWork.cinemaMode == 2) {
                if (campaignWork.cinemaCut[0] < 64) {
                    campaignWork.cinemaCut[0] += 8;
                    if (campaignWork.cinemaCut[0] >= 64) {
                        campaignWork.cinemaCut[0] = 64;
                        n++;
                    }
                } else {
                    campaignWork.cinemaCut[0] = 64;
                    n++;
                    if (campaignWork.cinemaCut[1] <= 64) {
                        campaignWork.cinemaCut[1] += 8;
                        if (campaignWork.cinemaCut[1] >= 64) {
                            campaignWork.cinemaCut[1] = 64;
                            n++;
                        }
                    }
                }
                if (0 <= campaignWork.cinemaCut[2]) {
                    campaignWork.cinemaCut[2] -= 8;
                    if (campaignWork.cinemaCut[2] <= 0) {
                        campaignWork.cinemaCut[2] = 0;
                        n++;
                    }
                }
            } else if (campaignWork.cinemaMode == 3) {
                if (campaignWork.cinemaCut[0] < 64) {
                    campaignWork.cinemaCut[0] += 8;
                    if (campaignWork.cinemaCut[0] >= 64) {
                        campaignWork.cinemaCut[0] = 64;
                        n++;
                    }
                } else if (campaignWork.cinemaCut[1] < 64) {
                    campaignWork.cinemaCut[0] = 64;
                    campaignWork.cinemaCut[1] += 8;
                    n++;
                    if (campaignWork.cinemaCut[1] >= 64) {
                        campaignWork.cinemaCut[1] = 64;
                        n++;
                    }
                } else {
                    campaignWork.cinemaCut[0] = 64;
                    campaignWork.cinemaCut[1] = 64;
                    campaignWork.cinemaCut[2] += 8;
                    n += 2;
                    if (campaignWork.cinemaCut[2] >= 116) {
                        campaignWork.cinemaCut[2] = 116;
                        n++;
                    }
                }
            }
            if (n >= 3) {
                campaignWork.cinemaState = 2;
            }
        }
        for (i = 0; i < 2; i++) {
            q = cinemaBlackBars[i];
            
            if (i == 0) {
                q.w[5] = DOTR_SINEMA_C2 + (cinemaBlackBars[i].w[1] + DOTR_SINEMA_C0 + DOTR_SINEMA_C1);
                q.w[7] = DOTR_SINEMA_C2 + (cinemaBlackBars[i].w[1] + DOTR_SINEMA_C0 + DOTR_SINEMA_C1);
            } else {
                q.w[1] = cinemaBlackBars[i].w[1] - DOTR_SINEMA_C0 - DOTR_SINEMA_C1 - DOTR_SINEMA_C2;
                q.w[3] = cinemaBlackBars[i].w[1] - DOTR_SINEMA_C0 - DOTR_SINEMA_C1 - DOTR_SINEMA_C2;
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
        if (campaignWork.cinemaState == 1) {
            if (campaignWork.cinemaMode == 0) {
                if (campaignWork.cinemaCut[0] < 255) {
                    campaignWork.cinemaCut[0] += 32;
                    if (campaignWork.cinemaCut[0] >= 255) {
                        campaignWork.cinemaCut[0] = 255;
                        campaignWork.cinemaMode = 1;
                        campaignWork.cinemaState = 0;
                    }
                } else {
                    campaignWork.cinemaMode = 1;
                    campaignWork.cinemaCut[0] = 255;
                    campaignWork.cinemaState = 0;
                }
            } else {
                if (0 < campaignWork.cinemaCut[0]) {
                    campaignWork.cinemaCut[0] -= 32;
                    if (campaignWork.cinemaCut[0] <= 0) {
                        campaignWork.cinemaCut[0] = 0;
                        campaignWork.cinemaMode = 0;
                        campaignWork.cinemaState = 0;
                    }
                } else {
                    campaignWork.cinemaMode = 0;
                    campaignWork.cinemaCut[0] = 0;
                    campaignWork.cinemaState = 0;
                }
            }
        }
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 8; j++) {
                q.w[j] = cinemaBlackBars[i].w[j];
            }
            q.col[3] = q.col[7] = q.col[11] = q.col[15] = b->cinemaCut[0];
            cursor = func_00218970_b(cursor, (struct DotrTikeiItem *)&q, 0, 0);
        }
    }
    return cursor;
}
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
extern struct DotrStWindowRec campaignPlaces[]; /* original: model_data */
extern struct DotrStWindowWindow campaignPlayerWindow[]; /* original: camp_window_My_data */
extern struct DotrStWindowItem roseSprites[]; /* original: tex_bara_data */
extern struct DotrStWindowItem campaignDeckSprites[]; /* original: tex_deck_data */
extern struct DotrStWindowItem tex_batti_data[];
extern struct DotrStWindowItem starSprites[]; /* original: tex_hosi_data */
extern struct DotrStWindowItem campaignCardItems[]; /* original: camp_card */
extern struct DotrStWindowItem campaignWindowItems[]; /* original: camp_window_data */
extern char D_0030F0F7[];
extern char D_0030F0FC[];
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

/* Draws the campaign status window. */
int Taku_Camp_ST_WINDOW(int cursor)
{
    struct DotrStWindowBoard *w;
    CampaignWork *g;
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
    y = 128 - (campaignWork.iconSlide * 128 >> 8);
    col[0] = col[1] = col[2] = 128;
    col[3] = 128;
    g = &campaignWork; /* windowAlpha[1] is read through this pointer, as in the original */
    if (campaignWork.unk018C) {
        if (w->kind == 11) {
            if (campaignWork.duelMenuChoice < 2) { t = 1; } else { t = 0; }
        } else if (campaignPlaces[w->kind].kind == 8) {
            t = 0;
        } else {
            t = 1;
        }
        if (w->mode == (signed char)t) {
            cursor = Taku_Obj_Set_b(cursor, &roseSprites[w->mode], 0, y);
            for (i = 0; i < 3; i++) {
                cursor = Taku_Window_Set_window(cursor, &campaignPlayerWindow[i], w->mode + 10, 0, 0, y, 0, 128, g->windowAlpha[1]);
            }
            if (campaignWork.windowOpen == 256) {
                w->mode ^= 1;
            }
        } else {
            cursor = Taku_Obj_Set_b(cursor, &roseSprites[w->mode], 0, y);
            for (i = 0; i < 3; i++) {
                cursor = Taku_Window_Set_window(cursor, &campaignPlayerWindow[i], w->mode, 0, 0, y, 0, 128, g->windowAlpha[1]);
            }
        }
    } else {
        cursor = Taku_Obj_Set_b(cursor, &roseSprites[w->mode], 0, y);
        for (i = 0; i < 3; i++) {
            cursor = Taku_Window_Set_window(cursor, &campaignPlayerWindow[i], w->mode, 0, 0, y, 0, 128, g->windowAlpha[1]);
        }
    }
    cursor = Taku_Window_Set_window(cursor, &campaignPlayerWindow[16], w->mode, 0, 0, y, 0, 128, campaignWork.windowAlpha[1]);
    deck = SzData_GetCurrentDeck(0);
    cursor = Taku_Obj_Set_b(cursor, &campaignDeckSprites[deck], 0, y);
    cost = SzData_GetDeckCost(0, deck);
    campaignWork.playerDeckCost = cost;
    leader = SzData_GetLeader(0, deck);
    rank = SzData_GetRank_b(0, leader);
    if (rank != 0) {
        r = rank - 1;
        cursor = Taku_Obj_Set_b(cursor, &tex_batti_data[(short)(r / 3)], 0, y);
        switch ((short)(r % 3 + 1)) {
        case 1:
            cursor = Taku_Obj_Set_b(cursor, &starSprites[2], 0, y);
            break;
        case 2:
            cursor = Taku_Obj_Set_b(cursor, &starSprites[0], 0, y);
            cursor = Taku_Obj_Set_b(cursor, &starSprites[1], 0, y);
            break;
        case 3:
            cursor = Taku_Obj_Set_b(cursor, &starSprites[0], 0, y);
            cursor = Taku_Obj_Set_b(cursor, &starSprites[1], 0, y);
            cursor = Taku_Obj_Set_b(cursor, &starSprites[2], 0, y);
            break;
        }
    }
    for (j = 0; j < 2; j++) {
        if (w->mode == 0) {
            if (j == 1) {
                for (n = 0; n < 8; n++) {
                    x = n * 16;
                    cursor = Taku_Obj_Set_b(cursor, &campaignCardItems[j], x, y);
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
                    cursor = Taku_Obj_Set_b(cursor, &campaignCardItems[j], x, y);
                }
            }
        } else {
            if (j == 0) {
                for (n = 0; n < 8; n++) {
                    x = n * 16;
                    cursor = Taku_Obj_Set_b(cursor, &campaignCardItems[j], x, y);
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
                    cursor = Taku_Obj_Set_b(cursor, &campaignCardItems[j], x, y);
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        cursor = Taku_Obj_Set_b(cursor, &campaignWindowItems[i], 0, y);
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
    xx = campaignPlayerWindow[2].x + 4;
    yy = campaignPlayerWindow[2].y + 2 + y;
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

/* Draws the campaign's system icons. */
void *Taku_Camp_SYS_ICON(void *packet) {
    s16 coords[19];
    CampaignWork *state;
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

    alpha = (s16)(0x80 - ((campaignWork.iconSlide << 7) >> 8));
    state = &campaignWork;
    packet = Taku_G4_Set(packet, D_002982F8, 0, alpha);
    row = campaignSystemIcons;
    y = (s16)alpha + 0x14F;
    i = 0;
    fade = state; /* fade + 0x82 walks iconGrow[i], 2 bytes per icon */
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
        if (i == state->iconUnderCursor && state->unk007E != 0) {
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
        packet = Taku_Obj_Set(packet, coords, 0, alpha);
        mode = state->unk007E;
        if (mode == 1 && i == state->iconUnderCursor && mode != 0) {
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
            packet = SzDuel_DrawWindow_Font_Pipe(packet, 0x232, y, 1, 1, length, text, 0);
        }
        i++;
        row += 19;
        fade += 2;
    } while (i < 4);
    if (campaignWork.unk007E == 0) {
        packet = Taku_Obj_Set(packet, campaignButtonIcons, 0, alpha);
    } else {
        packet = Taku_Obj_Set(packet, camp_sys_icon_button, 0, alpha);
    }
    if (campaignWork.unk007E == 0) {
        packet = SzDuel_DrawWindow_Font_Pipe(packet, 0x232, y, 1, 1, 6, D_0030F118, 0);
    }
    return packet;
}
