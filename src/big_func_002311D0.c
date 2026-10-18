#include "common.h"
#include "campaign.h"

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



/* Draws (hyouji) the campaign text window: the speaker's face and the text line by line. (original: Taku_Camp_BUN_HYOUJI) */
s32 Taku_Camp_TEXT_SHOW(s32 p) {
    s16 flagB;
    s16 i;
    CampaignWork *w;
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

    w = &campaignWork;
    msg = 0;
    flagB = 0;
    flagA = 0;
    ctx = &campaignState;
    rect = D_0029AEB0;
    for (i = 0; i < 4; i++) {
        col[i][0] = col[i][1] = col[i][2] = 0x80;
        col[i][3] = 0x80;
    }
    w->opponentLook = 0;
    if (w->talkStep != 0) {
        if (w->talkSpeaker == 0) {
            BunInfo *info;
            s32 x;
            s16 n;
            s32 ty;
            s32 y;

            g4 = D_00298AF6;
            p = SzMsg_LoadFont_Pipe(p, 1, w->talkMessage, 0, 0x16);
            p = RhText_SetTextureFlush(p);
            info = SzMsg_GetInfo(1);
            box = info->box;
            rect.v[2] = box.w;
            count = box.h / 22;
            if (count > 3) {
                count = 3;
            }
            if (*(s16 *)(ctx + 0xC2) < 200) {
                w->opponentLook = 0;
            } else if (*(s16 *)(ctx + 0xC2) < 300) {
                w->opponentLook = 1;
            } else {
                w->opponentLook = 2;
                if (*(s16 *)(ctx + 0xC4) == 14 && w->talkPage == 1) {
                    w->opponentLook = 3;
                }
            }
            switch (w->talkStep) {
            case 1:
                w->unk53A0 = 0;
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 4; i++) {
                        w->unk5380[j + 1][i] = 0;
                    }
                }
                w->talkStep++;
                break;
            case 2:
                w->unk53A0 += 20;
                if (w->unk53A0 >= 100) {
                    w->unk53A0 = 100;
                    w->talkStep++;
                }
                break;
            case 3:
                w->opponentFaceState = 10;
                for (j = 0; j < count; j++) {
                    for (i = 0; i < 4; i++) {
                        switch (i) {
                        case 1:
                            if (w->unk5380[j + 1][2] >= 0x80) {
                                w->unk5380[j + 1][i] += 0x20;
                            }
                            break;
                        case 2:
                            if (w->unk5380[j + 1][0] > 0x40) {
                                w->unk5380[j + 1][i] += 0x20;
                            }
                            break;
                        case 3:
                            if (w->unk5380[j + 1][1] > 0x20) {
                                w->unk5380[j + 1][i] += 0x20;
                            }
                            break;
                        default:
                            if (j == 0) {
                                w->unk5380[j + 1][i] += 0x20;
                            } else if (w->unk5380[j][1] >= 0x80) {
                                w->unk5380[j + 1][i] += 0x20;
                            }
                            break;
                        }
                        if (w->unk5380[j + 1][i] >= 0x80) {
                            w->unk5380[j + 1][i] = 0x80;
                        }
                    }
                }
                if (w->unk5380[count][3] >= 0x80) {
                    w->talkStep++;
                }
                break;
            case 4:
                break;
            case 5:
                if (w->talkPage < w->talkMessageCount) {
                    for (j = 0; j < count; j++) {
                        for (i = 0; i < 4; i++) {
                            w->unk5380[j + 1][i] -= 0x10;
                            if (w->unk5380[j + 1][i] <= 0) {
                                w->unk5380[j + 1][i] = 0;
                            }
                        }
                    }
                    if (w->unk5380[count][3] <= 0) {
                        for (j = 0; j < 3; j++) {
                            for (i = 0; i < 4; i++) {
                                w->unk5380[j + 1][i] = 0;
                            }
                        }
                        w->talkStep = 2;
                        w->talkPage++;
                        Taku_Camp_TEXT_PICK();
                    }
                } else {
                    w->talkStep = 11;
                }
                break;
            case 11:
                for (j = 0; j < count; j++) {
                    for (i = 0; i < 4; i++) {
                        w->unk5380[j + 1][i] -= 0x10;
                        if (w->unk5380[j + 1][i] <= 0) {
                            w->unk5380[j + 1][i] = 0;
                        }
                    }
                }
                if (w->unk5380[count][3] <= 0) {
                    for (j = 0; j < 3; j++) {
                        for (i = 0; i < 4; i++) {
                            w->unk5380[j + 1][i] = 0;
                        }
                    }
                    w->talkStep = 12;
                }
                break;
            case 12:
                if (0 <= w->unk53A0) {
                    w->unk53A0 -= 20;
                    if (w->unk53A0 <= 0) {
                        s16 ok;

                        w->unk53A0 = 0;
                        if (w->unk018C != 0 && *(s16 *)(ctx + 0xC2) >= 200) {
                            w->talkPage = 0;
                            w->talkStep = 0;
                            w->unk537A = 0;
                            *(s16 *)(ctx + 0xC2) = 0;
                            w->eventStep = 0;
                            w->moveStep = 0;
                            w->unk5372 = 0;
                            w->leaderShow = 0;
                            w->unk5375 = 0;
                            break;
                        }
                        w->unk53AB = 0;
                        ok = 1;
                        if (*(s16 *)(ctx + 0xC2) >= 300 && *(s16 *)(ctx + 0xC2) < 10000) {
                            if (w->unk537A == 3) {
                                ok = 1;
                            } else {
                                ok = 0;
                            }
                        }
                        if (w->unk5440 <= 0 && ok) {
                            w->unk5440 = 0;
                            if (ctx[0] == 0 && *(s16 *)(ctx + 0xC2) == 0x139 &&
                                ctx[3 + w->unk53C0] != 0 && *(s16 *)(ctx + 0xC2) >= 300 &&
                                *(s16 *)(ctx + 0xC2) < 10000) {
                                *(s16 *)(ctx + 0xC2) = 0x2BAC;
                                ctx[0xE] = 5;
                                break;
                            }
                            if (ctx[3 + w->unk53C0] < 3 && *(s16 *)(ctx + 0xC2) >= 300 &&
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
                                w->talkPage = 0;
                                w->talkStep = 0;
                                w->unk537A = 0;
                                w->eventStep = 0;
                                w->moveStep = 0;
                                w->unk5372 = 1;
                                w->leaderShow = 0;
                                w->unk5375 = 1;
                            } else if (*(s16 *)(ctx + 0xC2) >= 200) {
                                if (ctx[0] == 0 && *(s16 *)(ctx + 0xC2) == 0xD5) {
                                    ctx[0xE] = 4;
                                } else if (ctx[3 + ctx[0xC6]] == 1 && *(s16 *)(ctx + 0xC2) >= 200) {
                                    ctx[3 + ctx[0xC6]] = 2;
                                }
                                w->talkPage = 0;
                                w->talkStep = 0;
                                w->unk537A = 0;
                                *(s16 *)(ctx + 0xC2) = 0;
                                w->eventStep = 0;
                                w->moveStep = 0;
                                w->unk5372 = 0;
                                w->leaderShow = 0;
                                w->unk5375 = 0;
                            }
                        }
                    }
                }
                break;
            }
            g4.v[5] = D_00298AF6.v[1] + w->unk53A0 * (D_00298AF6.v[5] - D_00298AF6.v[1]) / 100;
            g4.v[7] = g4.v[5];
            p = func_00218970_b(p, &g4, 0, 0);
            for (i = 0; i < 4; i++) {
                col[i][0] = col[i][1] = col[i][2] = 0x80;
                col[i][3] = w->unk5380[0][i];
            }
            n = count;
            x = D_00298AF6.v[0] + 6;
            ty = D_00298AF6.v[1] + 6;
            for (i = 0, y = 0; i < n; i++) {
                s16 yy = y;

                for (j = 0; j < 4; j++) {
                    col[j][3] = w->unk5380[i + 1][j];
                }
                info->box.y = box.y + i * 0x16;
                info->box.h = 0x16;
                p = SzMsg_DrawRectG_Pipe(p, 1, x, ty + yy, &rect, col[0]);
                y = (s16)(y + 0x16);
            }
            SzMsg_Free(1);
        } else if (w->talkSpeaker == 1) {
            s16 done;

            done = 0;
            if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                if (w->talkMessage > 0x7F0) {
                    w->unk542C[0] += 2;
                    if (w->unk542C[0] >= 200) {
                        w->unk542C[0] = 200;
                    }
                }
                if (w->talkMessage > 0x7F2) {
                    w->unk542C[1] += 2;
                    if (w->unk542C[1] >= 200) {
                        w->unk542C[1] = 200;
                    }
                }
                if (w->talkMessage > 0x7F3) {
                    w->unk542C[2] += 2;
                    if (w->unk542C[2] >= 200) {
                        w->unk542C[2] = 200;
                    }
                }
                if (w->talkMessage > 0x7F5) {
                    w->unk542C[3] += 2;
                    if (w->unk542C[3] >= 200) {
                        w->unk542C[3] = 200;
                    }
                }
                if (w->talkMessage >= 0x7FB) {
                    w->unk542C[4] += 2;
                    if (w->unk542C[4] >= 200) {
                        w->unk542C[4] = 200;
                        done = 1;
                    }
                }
            }
            switch (w->talkStep) {
            case 1:
                w->unk53A0 = 0;
                for (j = 0; j < 4; j++) {
                    w->unk5380[0][j] = 0;
                }
                w->talkStep++;
                break;
            case 2:
            case 3:
                if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                    switch (w->talkMessage) {
                    case 0x7F0:
                        w->unk542C[0] += 2;
                        if (w->unk542C[0] >= 100) {
                            w->unk542C[0] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7F1:
                        w->unk542C[1] += 2;
                        if (w->unk542C[1] >= 100) {
                            w->unk542C[1] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7F3:
                        w->unk542C[2] += 2;
                        if (w->unk542C[2] >= 100) {
                            w->unk542C[2] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7F4:
                        w->unk542C[3] += 2;
                        if (w->unk542C[3] >= 100) {
                            w->unk542C[3] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7FA:
                        w->unk542C[4] += 2;
                        if (w->unk542C[4] >= 100) {
                            w->unk542C[4] = 100;
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
                        if (w->unk5380[0][0] > 0x40) {
                            w->unk5380[0][j] += 0x20;
                        }
                        break;
                    case 3:
                        if (w->unk5380[0][1] > 0x40) {
                            w->unk5380[0][j] += 0x20;
                        }
                        break;
                    default:
                        w->unk5380[0][j] += 0x20;
                        break;
                    }
                    if (w->unk5380[0][j] >= 0x80) {
                        w->unk5380[0][j] = 0x80;
                    }
                }
                if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                    if (flagA && w->unk5380[0][3] >= 0x80) {
                        w->talkStep++;
                    }
                } else if (w->unk5380[0][3] >= 0x80) {
                    w->talkStep++;
                }
                break;
            case 4:
                break;
            case 5:
                if (*(s16 *)(ctx + 0xC2) == 0x2724 && w->talkMessage == 0x7F6) {
                    w->unk542C[3] += 2;
                    if (w->unk542C[3] >= 200) {
                        w->unk542C[3] = 200;
                        flagA = 1;
                    }
                }
                if (w->talkPage < w->talkMessageCount) {
                    for (j = 0; j < 4; j++) {
                        switch (j) {
                        case 1:
                        case 2:
                            if (w->unk5380[0][0] < 0x40) {
                                w->unk5380[0][j] -= 0x20;
                            }
                            break;
                        case 3:
                            if (w->unk5380[0][1] < 0x40) {
                                w->unk5380[0][j] -= 0x20;
                            }
                            break;
                        default:
                            w->unk5380[0][j] -= 0x20;
                            break;
                        }
                        if (w->unk5380[0][j] <= 0) {
                            w->unk5380[0][j] = 0;
                            if (*(s16 *)(ctx + 0xC2) == 0x2724 && w->talkMessage == 0x7F6) {
                                if (j == 3 && flagA) {
                                    w->talkStep = 3;
                                    w->talkPage++;
                                    Taku_Camp_TEXT_PICK();
                                }
                            } else if (j == 3) {
                                w->talkStep = 3;
                                w->talkPage++;
                                Taku_Camp_TEXT_PICK();
                            }
                        }
                    }
                } else {
                    w->talkStep = 11;
                }
                break;
            case 11:
                for (j = 0; j < 4; j++) {
                    switch (j) {
                    case 1:
                    case 2:
                        if (w->unk5380[0][0] < 0x40) {
                            w->unk5380[0][j] -= 0x20;
                        }
                        break;
                    case 3:
                        if (w->unk5380[0][1] < 0x40) {
                            w->unk5380[0][j] -= 0x20;
                        }
                        break;
                    default:
                        w->unk5380[0][j] -= 0x20;
                        break;
                    }
                    if (w->unk5380[0][j] <= 0) {
                        w->unk5380[0][j] = 0;
                        if (j == 3) {
                            if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                                if (done) {
                                    w->talkStep = 12;
                                }
                            } else {
                                w->talkStep = 12;
                            }
                        }
                    }
                }
                break;
            }
            for (i = 0; i < 4; i++) {
                col[i][0] = col[i][1] = col[i][2] = 0x80;
                col[i][3] = w->unk5380[0][i];
            }
            p = SzMsg_LoadFont_Pipe(p, 1, w->talkMessage, 0, 0x16);
            p = RhText_SetTextureFlush(p);
            p = func_001FE7D0_b(p, 1, 0x59, 0x150, col, SzMsg_DrawRectG_Pipe);
            SzMsg_Free(1);
        } else {
            s32 y;
            BunInfo *info;
            s32 n;
            s32 x;
            s32 ty;

            p = SzMsg_LoadFont_Pipe(p, 1, w->talkMessage, 0, 0x16);
            p = RhText_SetTextureFlush(p);
            info = SzMsg_GetInfo(1);
            box2 = info->box;
            rect.v[2] = box2.w;
            count = box2.h / 22;
            if (count > 3) {
                count = 3;
            }
            switch (w->talkStep) {
            case 1:
                w->unk53A0 = 0;
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 4; i++) {
                        w->unk5380[j + 1][i] = 0;
                    }
                }
                w->talkStep++;
                break;
            case 2:
                if (w->unk53B4 != 0) {
                    if (w->duelistState[0] == 0) {
                        w->duelistState[0] = 1;
                    }
                    if (w->duelistSlide[0] < 0x400) {
                        w->duelistSlide[0] += 0x40;
                    }
                    if (w->duelistSlide[0] >= 0x400) {
                        w->duelistSlide[0] = 0x400;
                    }
                } else {
                    if (0 < w->duelistSlide[0]) {
                        w->duelistSlide[0] -= 0x40;
                    }
                    if (w->duelistSlide[0] <= 0) {
                        w->duelistSlide[0] = 0;
                    }
                }
                if (w->unk53B5 != 0) {
                    if (w->duelistState[1] == 0) {
                        w->duelistState[1] = 1;
                    }
                    if (w->duelistSlide[1] < 0x400) {
                        w->duelistSlide[1] += 0x40;
                    }
                    if (w->duelistSlide[1] >= 0x400) {
                        w->duelistSlide[1] = 0x400;
                    }
                } else {
                    if (0 < w->duelistSlide[1]) {
                        w->duelistSlide[1] -= 0x40;
                    }
                    if (w->duelistSlide[1] <= 0) {
                        w->duelistSlide[1] = 0;
                    }
                }
                if (w->unk53B4 != 0 && w->unk53B5 != 0) {
                    if (w->duelistSlide[0] >= 0x400 && w->duelistSlide[1] >= 0x400) {
                        w->talkStep++;
                    }
                } else if (w->unk53B4 != 0 && w->unk53B5 == 0) {
                    if (w->duelistSlide[0] >= 0x400 && w->duelistSlide[1] <= 0) {
                        w->talkStep++;
                    }
                } else if ((s8)w->unk53B4 == 0 && w->unk53B5 != 0) {
                    if (w->duelistSlide[0] <= 0 && w->duelistSlide[1] >= 0x400) {
                        w->talkStep++;
                    }
                } else if (w->duelistSlide[0] <= 0 && w->duelistSlide[1] <= 0) {
                    w->talkStep++;
                }
                break;
            case 3:
                if (w->talkSpeaker == 2) {
                    if (w->unk53B5 != 0) {
                        w->eventPictureZoom += 10;
                        if (w->eventPictureZoom >= 100) {
                            w->eventPictureZoom = 100;
                            w->duelistState[1] = 10;
                            flagB = 1;
                        }
                    } else if (w->eventPictureZoom <= 0) {
                        w->eventPictureZoom += 10;
                        if (0 <= w->eventPictureZoom) {
                            flagB = 1;
                            w->eventPictureZoom = 0;
                        }
                    } else {
                        w->eventPictureZoom -= 10;
                        if (w->eventPictureZoom <= 0) {
                            flagB = 1;
                            w->eventPictureZoom = 0;
                        }
                    }
                }
                if (w->talkSpeaker == 3) {
                    if (w->unk53B4 != 0) {
                        w->eventPictureZoom -= 10;
                        if (w->eventPictureZoom < -100) {
                            w->eventPictureZoom = -100;
                            w->duelistState[0] = 10;
                            flagB = 1;
                        }
                    } else if (w->eventPictureZoom <= 0) {
                        w->eventPictureZoom += 10;
                        if (0 <= w->eventPictureZoom) {
                            flagB = 1;
                            w->eventPictureZoom = 0;
                        }
                    } else {
                        w->eventPictureZoom -= 10;
                        if (w->eventPictureZoom <= 0) {
                            flagB = 1;
                            w->eventPictureZoom = 0;
                        }
                    }
                }
                if (flagB) {
                    for (j = 0; j < count; j++) {
                        for (i = 0; i < 4; i++) {
                            switch (i) {
                            case 1:
                                if (w->unk5380[j + 1][2] >= 0x80) {
                                    w->unk5380[j + 1][i] += 0x20;
                                }
                                break;
                            case 2:
                                if (w->unk5380[j + 1][0] > 0x40) {
                                    w->unk5380[j + 1][i] += 0x20;
                                }
                                break;
                            case 3:
                                if (w->unk5380[j + 1][1] > 0x20) {
                                    w->unk5380[j + 1][i] += 0x20;
                                }
                                break;
                            default:
                                if (j == 0) {
                                    w->unk5380[j + 1][i] += 0x20;
                                } else if (w->unk5380[j][1] >= 0x80) {
                                    w->unk5380[j + 1][i] += 0x20;
                                }
                                break;
                            }
                            if (w->unk5380[j + 1][i] >= 0x80) {
                                w->unk5380[j + 1][i] = 0x80;
                            }
                        }
                    }
                }
                if (w->unk5380[count][3] >= 0x80) {
                    w->talkStep++;
                }
                break;
            case 4:
                break;
            case 5:
                if (w->talkPage < w->talkMessageCount) {
                    for (j = 0; j < count; j++) {
                        for (i = 0; i < 4; i++) {
                            w->unk5380[j + 1][i] -= 0x10;
                            if (w->unk5380[j + 1][i] <= 0) {
                                w->unk5380[j + 1][i] = 0;
                            }
                        }
                    }
                    if (w->unk5380[count][3] <= 0) {
                        for (j = 0; j < 3; j++) {
                            for (i = 0; i < 4; i++) {
                                w->unk5380[j + 1][i] = 0;
                            }
                        }
                        w->talkStep = 2;
                        w->talkPage++;
                        Taku_Camp_TEXT_PICK();
                    }
                } else {
                    w->talkStep = 11;
                }
                break;
            case 11:
                for (j = 0; j < count; j++) {
                    for (i = 0; i < 4; i++) {
                        w->unk5380[j + 1][i] -= 0x10;
                        if (w->unk5380[j + 1][i] <= 0) {
                            w->unk5380[j + 1][i] = 0;
                        }
                    }
                }
                if (w->unk5380[count][3] <= 0) {
                    for (j = 0; j < 3; j++) {
                        for (i = 0; i < 4; i++) {
                            w->unk5380[j + 1][i] = 0;
                        }
                    }
                    w->talkStep = 12;
                }
                break;
            case 13:
                if (w->eventPictureZoom <= 0) {
                    w->eventPictureZoom += 10;
                    if (0 <= w->eventPictureZoom) {
                        flagB = 1;
                        w->eventPictureZoom = 0;
                    }
                } else {
                    w->eventPictureZoom -= 10;
                    if (w->eventPictureZoom <= 0) {
                        flagB = 1;
                        w->eventPictureZoom = 0;
                    }
                }
                if (flagB) {
                    if (0 < w->duelistSlide[0]) {
                        w->duelistSlide[0] -= 0x40;
                    }
                    if (0 < w->duelistSlide[1]) {
                        w->duelistSlide[1] -= 0x40;
                    }
                    if (w->duelistSlide[0] <= 0) {
                        w->duelistSlide[0] = 0;
                        if (w->duelistState[0] != 0) {
                            ShFace_Close((u8 *)&w->duelistFace[0]);
                            w->duelistState[0] = 0;
                        }
                    }
                    if (w->duelistSlide[1] <= 0) {
                        w->duelistSlide[1] = 0;
                        if (w->duelistState[1] != 0) {
                            ShFace_Close((u8 *)&w->duelistFace[1]);
                            w->duelistState[1] = 0;
                        }
                    }
                    if (w->duelistSlide[0] <= 0 && w->duelistSlide[1] <= 0) {
                        w->talkStep = 14;
                        w->unk53B4 = 0;
                        w->unk53B5 = 0;
                    }
                }
                break;
            }
            if (w->talkSpeaker == 2) {
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
                    col[j][3] = w->unk5380[i + 1][j];
                }
                info->box.y = box2.y + i * 0x16;
                info->box.h = 0x16;
                if (w->unk5483 == 0) {
                    p = SzMsg_DrawRectG_Pipe(p, 1, x, ty + yy, &rect, col[0]);
                }
                y = (s16)(y + 0x16);
            }
            SzMsg_Free(1);
        }
    }
    if (w->unk006E != 0 && w->windowOpen == 0 && w->unk5374 == 0 && w->unk0004 == 0 &&
        w->unk0072 == 0 && w->cursorOnIcon == 0 && w->unk5481 != 0 && SzEffect_IsUse2(-1, -1) == 0 &&
        w->routesIdle != 0 && w->placesReached == 0) {
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
    if (w->unk5483 != 0) {
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
