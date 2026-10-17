#include "common.h"

typedef struct {
    s16 x0, y0, x1, y1;
    s16 kind;
} BunWin;

typedef struct {
    s32 x, y, w, h;
} BunBox;

typedef struct {
    s32 id;
    BunBox box;
} BunInfo;

typedef struct {
    s32 v[4];
} __attribute__((aligned(16))) BunRect;

typedef struct {
    s16 v[19];
} BunG4;

extern s32 func_00218970_b(s32, void *, s16, s16);
extern s32 SzMsg_DrawRatioX_Pipe_b(s32, s32, s32, s32, f32, f32, void *, void *);
extern void SzMsg_DrawRect_Pipe_b(void);
extern s32 func_001FE7D0_b(s32, s32, s32, s32, void *, void *);
extern BunRect D_0029AEB0;
extern BunG4 D_00298AF6 __attribute__((aligned(2)));
extern BunWin D_00297B72 __attribute__((aligned(2)));


typedef struct {
    u8 pad0000[0x4];
    u16 f0004;
    u8 pad0006[0x5A];
    s16 f0060;
    u8 pad0062[0xA];
    s16 f006C;
    s8 f006E;
    u8 pad006F[0x3];
    s8 f0072;
    u8 pad0073[0x119];
    s8 f018C;
    u8 pad018D[0x51DF];
    s16 f536C;
    u8 pad536E[0x4];
    s8 f5372;
    s8 f5373;
    s8 f5374;
    s8 f5375;
    s8 f5376;
    u8 pad5377[0x1];
    s16 msg;
    s8 f537A;
    s8 step;
    s8 f537C;
    s8 f537D;
    s8 mode;
    u8 pad537F[0x1];
    s16 tbl[4][4];
    s8 f53A0;
    u8 pad53A1[0xA];
    s8 f53AB;
    u8 pad53AC[0x8];
    s8 f53B4;
    s8 f53B5;
    s16 f53B6;
    s16 f53B8;
    u8 pad53BA[0x6];
    s8 f53C0;
    u8 pad53C1[0x46];
    s8 f5407;
    s8 f5408;
    u8 pad5409[0x1];
    s8 f540A;
    u8 pad540B[0x1];
    u8 face0[8];
    u8 face1[8];
    u8 pad541C[0x10];
    s16 lv[5];
    u8 pad5436[0x1];
    s8 f5437;
    u8 pad5438[0x8];
    s8 f5440;
    u8 pad5441[0x27];
    s8 f5468;
    u8 pad5469[0x11];
    s8 f547A;
    u8 pad547B[0x6];
    s8 f5481;
    s8 f5482;
    s8 f5483;
} BunWork;

#define W ((BunWork *)0x01ED0000)

/* Draws (hyouji) the campaign text window: the speaker's face and the text line by line. */
s32 Taku_Camp_BUN_HYOUJI(s32 p) {
    s16 flagB;
    s16 i;
    BunWork *w;
    s8 *ctx;
    s16 j;
    s16 count;
    u8 col[4][4];
    BunBox box;
    BunRect rect;
    BunG4 g4;
    BunBox box2;
    BunWin win;
    BunWin win2;
    s32 msg;
    s16 flagA;

    w = W;
    msg = 0;
    flagB = 0;
    flagA = 0;
    ctx = &campaignState;
    rect = D_0029AEB0;
    for (i = 0; i < 4; i++) {
        col[i][0] = col[i][1] = col[i][2] = 0x80;
        col[i][3] = 0x80;
    }
    w->f5468 = 0;
    if (w->step != 0) {
        if (w->mode == 0) {
            BunInfo *info;
            s32 x;
            s16 n;
            s32 ty;
            s32 y;

            g4 = D_00298AF6;
            p = SzMsg_LoadFont_Pipe(p, 1, w->msg, 0, 0x16);
            p = RhText_SetTextureFlush(p);
            info = SzMsg_GetInfo(1);
            box = info->box;
            rect.v[2] = box.w;
            count = box.h / 22;
            if (count > 3) {
                count = 3;
            }
            if (*(s16 *)(ctx + 0xC2) < 200) {
                w->f5468 = 0;
            } else if (*(s16 *)(ctx + 0xC2) < 300) {
                w->f5468 = 1;
            } else {
                w->f5468 = 2;
                if (*(s16 *)(ctx + 0xC4) == 14 && w->f537D == 1) {
                    w->f5468 = 3;
                }
            }
            switch (w->step) {
            case 1:
                w->f53A0 = 0;
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 4; i++) {
                        w->tbl[j + 1][i] = 0;
                    }
                }
                w->step++;
                break;
            case 2:
                w->f53A0 += 20;
                if (w->f53A0 >= 100) {
                    w->f53A0 = 100;
                    w->step++;
                }
                break;
            case 3:
                w->f540A = 10;
                for (j = 0; j < count; j++) {
                    for (i = 0; i < 4; i++) {
                        switch (i) {
                        case 1:
                            if (w->tbl[j + 1][2] >= 0x80) {
                                w->tbl[j + 1][i] += 0x20;
                            }
                            break;
                        case 2:
                            if (w->tbl[j + 1][0] > 0x40) {
                                w->tbl[j + 1][i] += 0x20;
                            }
                            break;
                        case 3:
                            if (w->tbl[j + 1][1] > 0x20) {
                                w->tbl[j + 1][i] += 0x20;
                            }
                            break;
                        default:
                            if (j == 0) {
                                w->tbl[j + 1][i] += 0x20;
                            } else if (w->tbl[j][1] >= 0x80) {
                                w->tbl[j + 1][i] += 0x20;
                            }
                            break;
                        }
                        if (w->tbl[j + 1][i] >= 0x80) {
                            w->tbl[j + 1][i] = 0x80;
                        }
                    }
                }
                if (w->tbl[count][3] >= 0x80) {
                    w->step++;
                }
                break;
            case 4:
                break;
            case 5:
                if (w->f537D < w->f537C) {
                    for (j = 0; j < count; j++) {
                        for (i = 0; i < 4; i++) {
                            w->tbl[j + 1][i] -= 0x10;
                            if (w->tbl[j + 1][i] <= 0) {
                                w->tbl[j + 1][i] = 0;
                            }
                        }
                    }
                    if (w->tbl[count][3] <= 0) {
                        for (j = 0; j < 3; j++) {
                            for (i = 0; i < 4; i++) {
                                w->tbl[j + 1][i] = 0;
                            }
                        }
                        w->step = 2;
                        w->f537D++;
                        Taku_Camp_BUN_HANTEI();
                    }
                } else {
                    w->step = 11;
                }
                break;
            case 11:
                for (j = 0; j < count; j++) {
                    for (i = 0; i < 4; i++) {
                        w->tbl[j + 1][i] -= 0x10;
                        if (w->tbl[j + 1][i] <= 0) {
                            w->tbl[j + 1][i] = 0;
                        }
                    }
                }
                if (w->tbl[count][3] <= 0) {
                    for (j = 0; j < 3; j++) {
                        for (i = 0; i < 4; i++) {
                            w->tbl[j + 1][i] = 0;
                        }
                    }
                    w->step = 12;
                }
                break;
            case 12:
                if (0 <= w->f53A0) {
                    w->f53A0 -= 20;
                    if (w->f53A0 <= 0) {
                        s16 ok;

                        w->f53A0 = 0;
                        if (w->f018C != 0 && *(s16 *)(ctx + 0xC2) >= 200) {
                            w->f537D = 0;
                            w->step = 0;
                            w->f537A = 0;
                            *(s16 *)(ctx + 0xC2) = 0;
                            w->f536C = 0;
                            w->f0060 = 0;
                            w->f5372 = 0;
                            w->f5373 = 0;
                            w->f5375 = 0;
                            break;
                        }
                        w->f53AB = 0;
                        ok = 1;
                        if (*(s16 *)(ctx + 0xC2) >= 300 && *(s16 *)(ctx + 0xC2) < 10000) {
                            if (w->f537A == 3) {
                                ok = 1;
                            } else {
                                ok = 0;
                            }
                        }
                        if (w->f5440 <= 0 && ok) {
                            w->f5440 = 0;
                            if (ctx[0] == 0 && *(s16 *)(ctx + 0xC2) == 0x139 &&
                                ctx[3 + w->f53C0] != 0 && *(s16 *)(ctx + 0xC2) >= 300 &&
                                *(s16 *)(ctx + 0xC2) < 10000) {
                                *(s16 *)(ctx + 0xC2) = 0x2BAC;
                                ctx[0xE] = 5;
                                break;
                            }
                            if (ctx[3 + w->f53C0] < 3 && *(s16 *)(ctx + 0xC2) >= 300 &&
                                *(s16 *)(ctx + 0xC2) < 10000) {
                                if (ctx[0] == 0) {
                                    if (*(s16 *)(ctx + 0xC2) == 0x134) {
                                        *(s16 *)(ctx + 0xC2) = 0x2B84;
                                        ctx[3 + ctx[0xC6]] = 3;
                                    } else if (*(s16 *)(ctx + 0xC2) == 0x138) {
                                        *(s16 *)(ctx + 0xC2) = 0x2B98;
                                        ctx[0xE] = 3;
                                    } else if (*(s16 *)(ctx + 0xC2) == 0x139) {
                                        *(s16 *)(ctx + 0xC2) = 0x2BAC;
                                        ctx[0xE] = 5;
                                    } else {
                                        *(s16 *)(ctx + 0xC2) -= 200;
                                        ctx[3 + ctx[0xC6]] = 3;
                                    }
                                } else if (*(s16 *)(ctx + 0xC2) == 0x138 || ((s16 *)ctx)[0x61] == 0x139) {
                                    *(s16 *)(ctx + 0xC2) = 0x2F76;
                                    ctx[0xE] = 3;
                                } else {
                                    *(s16 *)(ctx + 0xC2) -= 200;
                                    ctx[3 + ctx[0xC6]] = 3;
                                }
                                w->f537D = 0;
                                w->step = 0;
                                w->f537A = 0;
                                w->f536C = 0;
                                w->f0060 = 0;
                                w->f5372 = 1;
                                w->f5373 = 0;
                                w->f5375 = 1;
                            } else if (*(s16 *)(ctx + 0xC2) >= 200) {
                                if (ctx[0] == 0 && *(s16 *)(ctx + 0xC2) == 0xD5) {
                                    ctx[0xE] = 4;
                                } else if (ctx[3 + ctx[0xC6]] == 1 && *(s16 *)(ctx + 0xC2) >= 200) {
                                    ctx[3 + ctx[0xC6]] = 2;
                                }
                                w->f537D = 0;
                                w->step = 0;
                                w->f537A = 0;
                                *(s16 *)(ctx + 0xC2) = 0;
                                w->f536C = 0;
                                w->f0060 = 0;
                                w->f5372 = 0;
                                w->f5373 = 0;
                                w->f5375 = 0;
                            }
                        }
                    }
                }
                break;
            }
            g4.v[5] = D_00298AF6.v[1] + w->f53A0 * (D_00298AF6.v[5] - D_00298AF6.v[1]) / 100;
            g4.v[7] = g4.v[5];
            p = func_00218970_b(p, &g4, 0, 0);
            for (i = 0; i < 4; i++) {
                col[i][0] = col[i][1] = col[i][2] = 0x80;
                col[i][3] = w->tbl[0][i];
            }
            n = count;
            x = D_00298AF6.v[0] + 6;
            ty = D_00298AF6.v[1] + 6;
            for (i = 0, y = 0; i < n; i++) {
                s16 yy = y;

                for (j = 0; j < 4; j++) {
                    col[j][3] = w->tbl[i + 1][j];
                }
                info->box.y = box.y + i * 0x16;
                info->box.h = 0x16;
                p = SzMsg_DrawRectG_Pipe(p, 1, x, ty + yy, &rect, col[0]);
                y = (s16)(y + 0x16);
            }
            SzMsg_Free(1);
        } else if (w->mode == 1) {
            s16 done;

            done = 0;
            if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                if (w->msg > 0x7F0) {
                    w->lv[0] += 2;
                    if (w->lv[0] >= 200) {
                        w->lv[0] = 200;
                    }
                }
                if (w->msg > 0x7F2) {
                    w->lv[1] += 2;
                    if (w->lv[1] >= 200) {
                        w->lv[1] = 200;
                    }
                }
                if (w->msg > 0x7F3) {
                    w->lv[2] += 2;
                    if (w->lv[2] >= 200) {
                        w->lv[2] = 200;
                    }
                }
                if (w->msg > 0x7F5) {
                    w->lv[3] += 2;
                    if (w->lv[3] >= 200) {
                        w->lv[3] = 200;
                    }
                }
                if (w->msg >= 0x7FB) {
                    w->lv[4] += 2;
                    if (w->lv[4] >= 200) {
                        w->lv[4] = 200;
                        done = 1;
                    }
                }
            }
            switch (w->step) {
            case 1:
                w->f53A0 = 0;
                for (j = 0; j < 4; j++) {
                    w->tbl[0][j] = 0;
                }
                w->step++;
                break;
            case 2:
            case 3:
                if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                    switch (w->msg) {
                    case 0x7F0:
                        w->lv[0] += 2;
                        if (w->lv[0] >= 100) {
                            w->lv[0] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7F1:
                        w->lv[1] += 2;
                        if (w->lv[1] >= 100) {
                            w->lv[1] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7F3:
                        w->lv[2] += 2;
                        if (w->lv[2] >= 100) {
                            w->lv[2] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7F4:
                        w->lv[3] += 2;
                        if (w->lv[3] >= 100) {
                            w->lv[3] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7FA:
                        w->lv[4] += 2;
                        if (w->lv[4] >= 100) {
                            w->lv[4] = 100;
                            flagA = 1;
                        }
                        break;
                    default:
                        flagA = 1;
                        break;
                    }
                }
                for (j = 0; j < 4; j++) {
                    switch (j) {
                    case 1:
                    case 2:
                        if (w->tbl[0][0] > 0x40) {
                            w->tbl[0][j] += 0x20;
                        }
                        break;
                    case 3:
                        if (w->tbl[0][1] > 0x40) {
                            w->tbl[0][j] += 0x20;
                        }
                        break;
                    default:
                        w->tbl[0][j] += 0x20;
                        break;
                    }
                    if (w->tbl[0][j] >= 0x80) {
                        w->tbl[0][j] = 0x80;
                    }
                }
                if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                    if (flagA && w->tbl[0][3] >= 0x80) {
                        w->step++;
                    }
                } else if (w->tbl[0][3] >= 0x80) {
                    w->step++;
                }
                break;
            case 4:
                break;
            case 5:
                if (*(s16 *)(ctx + 0xC2) == 0x2724 && w->msg == 0x7F6) {
                    w->lv[3] += 2;
                    if (w->lv[3] >= 200) {
                        w->lv[3] = 200;
                        flagA = 1;
                    }
                }
                if (w->f537D < w->f537C) {
                    for (j = 0; j < 4; j++) {
                        switch (j) {
                        case 1:
                        case 2:
                            if (w->tbl[0][0] < 0x40) {
                                w->tbl[0][j] -= 0x20;
                            }
                            break;
                        case 3:
                            if (w->tbl[0][1] < 0x40) {
                                w->tbl[0][j] -= 0x20;
                            }
                            break;
                        default:
                            w->tbl[0][j] -= 0x20;
                            break;
                        }
                        if (w->tbl[0][j] <= 0) {
                            w->tbl[0][j] = 0;
                            if (*(s16 *)(ctx + 0xC2) == 0x2724 && w->msg == 0x7F6) {
                                if (j == 3 && flagA) {
                                    w->step = 3;
                                    w->f537D++;
                                    Taku_Camp_BUN_HANTEI();
                                }
                            } else if (j == 3) {
                                w->step = 3;
                                w->f537D++;
                                Taku_Camp_BUN_HANTEI();
                            }
                        }
                    }
                } else {
                    w->step = 11;
                }
                break;
            case 11:
                for (j = 0; j < 4; j++) {
                    switch (j) {
                    case 1:
                    case 2:
                        if (w->tbl[0][0] < 0x40) {
                            w->tbl[0][j] -= 0x20;
                        }
                        break;
                    case 3:
                        if (w->tbl[0][1] < 0x40) {
                            w->tbl[0][j] -= 0x20;
                        }
                        break;
                    default:
                        w->tbl[0][j] -= 0x20;
                        break;
                    }
                    if (w->tbl[0][j] <= 0) {
                        w->tbl[0][j] = 0;
                        if (j == 3) {
                            if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                                if (done) {
                                    w->step = 12;
                                }
                            } else {
                                w->step = 12;
                            }
                        }
                    }
                }
                break;
            }
            for (i = 0; i < 4; i++) {
                col[i][0] = col[i][1] = col[i][2] = 0x80;
                col[i][3] = w->tbl[0][i];
            }
            p = SzMsg_LoadFont_Pipe(p, 1, w->msg, 0, 0x16);
            p = RhText_SetTextureFlush(p);
            p = func_001FE7D0_b(p, 1, 0x59, 0x150, col, SzMsg_DrawRectG_Pipe);
            SzMsg_Free(1);
        } else {
            s32 y;
            BunInfo *info;
            s32 n;
            s32 x;
            s32 ty;

            p = SzMsg_LoadFont_Pipe(p, 1, w->msg, 0, 0x16);
            p = RhText_SetTextureFlush(p);
            info = SzMsg_GetInfo(1);
            box2 = info->box;
            rect.v[2] = box2.w;
            count = box2.h / 22;
            if (count > 3) {
                count = 3;
            }
            switch (w->step) {
            case 1:
                w->f53A0 = 0;
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 4; i++) {
                        w->tbl[j + 1][i] = 0;
                    }
                }
                w->step++;
                break;
            case 2:
                if (w->f53B4 != 0) {
                    if (w->f5407 == 0) {
                        w->f5407 = 1;
                    }
                    if (w->f53B6 < 0x400) {
                        w->f53B6 += 0x40;
                    }
                    if (w->f53B6 >= 0x400) {
                        w->f53B6 = 0x400;
                    }
                } else {
                    if (0 < w->f53B6) {
                        w->f53B6 -= 0x40;
                    }
                    if (w->f53B6 <= 0) {
                        w->f53B6 = 0;
                    }
                }
                if (w->f53B5 != 0) {
                    if (w->f5408 == 0) {
                        w->f5408 = 1;
                    }
                    if (w->f53B8 < 0x400) {
                        w->f53B8 += 0x40;
                    }
                    if (w->f53B8 >= 0x400) {
                        w->f53B8 = 0x400;
                    }
                } else {
                    if (0 < w->f53B8) {
                        w->f53B8 -= 0x40;
                    }
                    if (w->f53B8 <= 0) {
                        w->f53B8 = 0;
                    }
                }
                if (w->f53B4 != 0 && w->f53B5 != 0) {
                    if (w->f53B6 >= 0x400 && w->f53B8 >= 0x400) {
                        w->step++;
                    }
                } else if (w->f53B4 != 0 && w->f53B5 == 0) {
                    if (w->f53B6 >= 0x400 && w->f53B8 <= 0) {
                        w->step++;
                    }
                } else if ((s8)w->f53B4 == 0 && w->f53B5 != 0) {
                    if (w->f53B6 <= 0 && w->f53B8 >= 0x400) {
                        w->step++;
                    }
                } else if (w->f53B6 <= 0 && w->f53B8 <= 0) {
                    w->step++;
                }
                break;
            case 3:
                if (w->mode == 2) {
                    if (w->f53B5 != 0) {
                        w->f5437 += 10;
                        if (w->f5437 >= 100) {
                            w->f5437 = 100;
                            w->f5408 = 10;
                            flagB = 1;
                        }
                    } else if (w->f5437 <= 0) {
                        w->f5437 += 10;
                        if (0 <= w->f5437) {
                            flagB = 1;
                            w->f5437 = 0;
                        }
                    } else {
                        w->f5437 -= 10;
                        if (w->f5437 <= 0) {
                            flagB = 1;
                            w->f5437 = 0;
                        }
                    }
                }
                if (w->mode == 3) {
                    if (w->f53B4 != 0) {
                        w->f5437 -= 10;
                        if (w->f5437 < -100) {
                            w->f5437 = -100;
                            w->f5407 = 10;
                            flagB = 1;
                        }
                    } else if (w->f5437 <= 0) {
                        w->f5437 += 10;
                        if (0 <= w->f5437) {
                            flagB = 1;
                            w->f5437 = 0;
                        }
                    } else {
                        w->f5437 -= 10;
                        if (w->f5437 <= 0) {
                            flagB = 1;
                            w->f5437 = 0;
                        }
                    }
                }
                if (flagB) {
                    for (j = 0; j < count; j++) {
                        for (i = 0; i < 4; i++) {
                            switch (i) {
                            case 1:
                                if (w->tbl[j + 1][2] >= 0x80) {
                                    w->tbl[j + 1][i] += 0x20;
                                }
                                break;
                            case 2:
                                if (w->tbl[j + 1][0] > 0x40) {
                                    w->tbl[j + 1][i] += 0x20;
                                }
                                break;
                            case 3:
                                if (w->tbl[j + 1][1] > 0x20) {
                                    w->tbl[j + 1][i] += 0x20;
                                }
                                break;
                            default:
                                if (j == 0) {
                                    w->tbl[j + 1][i] += 0x20;
                                } else if (w->tbl[j][1] >= 0x80) {
                                    w->tbl[j + 1][i] += 0x20;
                                }
                                break;
                            }
                            if (w->tbl[j + 1][i] >= 0x80) {
                                w->tbl[j + 1][i] = 0x80;
                            }
                        }
                    }
                }
                if (w->tbl[count][3] >= 0x80) {
                    w->step++;
                }
                break;
            case 4:
                break;
            case 5:
                if (w->f537D < w->f537C) {
                    for (j = 0; j < count; j++) {
                        for (i = 0; i < 4; i++) {
                            w->tbl[j + 1][i] -= 0x10;
                            if (w->tbl[j + 1][i] <= 0) {
                                w->tbl[j + 1][i] = 0;
                            }
                        }
                    }
                    if (w->tbl[count][3] <= 0) {
                        for (j = 0; j < 3; j++) {
                            for (i = 0; i < 4; i++) {
                                w->tbl[j + 1][i] = 0;
                            }
                        }
                        w->step = 2;
                        w->f537D++;
                        Taku_Camp_BUN_HANTEI();
                    }
                } else {
                    w->step = 11;
                }
                break;
            case 11:
                for (j = 0; j < count; j++) {
                    for (i = 0; i < 4; i++) {
                        w->tbl[j + 1][i] -= 0x10;
                        if (w->tbl[j + 1][i] <= 0) {
                            w->tbl[j + 1][i] = 0;
                        }
                    }
                }
                if (w->tbl[count][3] <= 0) {
                    for (j = 0; j < 3; j++) {
                        for (i = 0; i < 4; i++) {
                            w->tbl[j + 1][i] = 0;
                        }
                    }
                    w->step = 12;
                }
                break;
            case 13:
                if (w->f5437 <= 0) {
                    w->f5437 += 10;
                    if (0 <= w->f5437) {
                        flagB = 1;
                        w->f5437 = 0;
                    }
                } else {
                    w->f5437 -= 10;
                    if (w->f5437 <= 0) {
                        flagB = 1;
                        w->f5437 = 0;
                    }
                }
                if (flagB) {
                    if (0 < w->f53B6) {
                        w->f53B6 -= 0x40;
                    }
                    if (0 < w->f53B8) {
                        w->f53B8 -= 0x40;
                    }
                    if (w->f53B6 <= 0) {
                        w->f53B6 = 0;
                        if (w->f5407 != 0) {
                            ShFace_Close(w->face0);
                            w->f5407 = 0;
                        }
                    }
                    if (w->f53B8 <= 0) {
                        w->f53B8 = 0;
                        if (w->f5408 != 0) {
                            ShFace_Close(w->face1);
                            w->f5408 = 0;
                        }
                    }
                    if (w->f53B6 <= 0 && w->f53B8 <= 0) {
                        w->step = 14;
                        w->f53B4 = 0;
                        w->f53B5 = 0;
                    }
                }
                break;
            }
            if (w->mode == 2) {
                x = 0xA0;
                ty = 0x160;
            } else {
                x = 0x18;
                ty = 0x30;
            }
            n = count;
            for (i = 0, y = 0; i < n; i++) {
                s16 yy = y;

                for (j = 0; j < 4; j++) {
                    col[j][3] = w->tbl[i + 1][j];
                }
                info->box.y = box2.y + i * 0x16;
                info->box.h = 0x16;
                if (w->f5483 == 0) {
                    p = SzMsg_DrawRectG_Pipe(p, 1, x, ty + yy, &rect, col[0]);
                }
                y = (s16)(y + 0x16);
            }
            SzMsg_Free(1);
        }
    }
    if (w->f006E != 0 && w->f006C == 0 && w->f5374 == 0 && w->f0004 == 0 &&
        w->f0072 == 0 && w->f547A == 0 && w->f5481 != 0 && SzEffect_IsUse2(-1, -1) == 0 &&
        w->f5376 != 0 && w->f5482 == 0) {
        BunInfo *info;
        f32 sy;
        f32 sx;

        win = D_00297B72;
        msg = 0x886;
        p = SzMsg_LoadFont_Pipe(p, 1, msg, 0, 0x16);
        p = RhText_SetTextureFlush(p);
        info = SzMsg_GetInfo(1);
        win.x1 = (s16)info->box.w + 12;
        win.y1 = (s16)info->box.h + 12;
        p = Taku_Window_Set(p, &win, 2, 0, 0xC4, 0x30, 0, 0x80, 0x40);
        for (i = 0; i < 4; i++) {
            col[i][0] = col[i][1] = col[i][2] = 0x80;
            col[i][3] = 0x80;
        }
        sy = sx = 1.0f;
        p = SzMsg_DrawRatioX_Pipe_b(p, 1, 0xCA, 0x36, sx, sy, col, SzMsg_DrawRect_Pipe_b);
        SzMsg_Free(1);
    }
    switch (*(s16 *)(ctx + 0xC2)) {
    case 0x2B70:
        msg = 0x8AB;
        break;
    case 0x2B74:
        msg = 0x8AD;
        break;
    case 0x2B8D:
        msg = 0x8DF;
        break;
    }
    if (w->f5483 != 0) {
        BunInfo *info;
        s32 x;

        win2 = D_00297B72;
        p = SzMsg_LoadFont_Pipe(p, 1, msg, 0, 0x16);
        p = RhText_SetTextureFlush(p);
        info = SzMsg_GetInfo(1);
        win2.x1 = (s16)info->box.w + 12;
        win2.y1 = (s16)info->box.h + 12;
        x = 0x140 - (info->box.w >> 1);
        p = Taku_Window_Set(p, &win2, 2, 0, x, 0xE0, 0, 0x80, 0x40);
        for (i = 0; i < 4; i++) {
            col[i][0] = col[i][1] = col[i][2] = 0x80;
            col[i][3] = 0x80;
        }
        p = SzMsg_DrawRatioX_Pipe_b(p, 1, x + 6, 0xE6, 1.0f, 1.0f, col, SzMsg_DrawRect_Pipe_b);
        SzMsg_Free(1);
    }
    return p;
}
