#include "common.h"

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrTekiWindowItem {
    short w[8];
    short unknown_10[10];
    short code;                 
};
struct DotrTekiWindowItemU {
    short w[8];
    short unknown_10[10];
    unsigned short code;        
};
struct DotrTekiWindowWindow {
    unsigned short x, y, w, h;
    char unknown_08[2];
};
struct DotrTekiWindowInfo {
    int unknown_00[3];
    int w;                      
};
struct DotrTekiWindowFace {
    unsigned char id, no, kind, mode;
    unsigned short x, y;
};
struct DotrTekiWindowBoard {
    signed char b0;             
    signed char b1;
    signed char b2;
    signed char lv[63];         
    short h66[32];              
    short h130[32];             
    short h194;
    short h196;                 
    signed char b198;           
};
extern struct DotrTekiWindowBoard D_00299E10_b;
struct DotrTekiWindowRec {
    short unknown_00[8];
    short h10;                  
    char unknown_12[34];
};
extern struct DotrTekiWindowRec D_00298BA0[];
struct DotrTekiWindowNames {
    char *s[22];
};
struct DotrTekiWindowPair {
    struct DotrTekiWindowItem it[2];
};
extern struct DotrTekiWindowNames D_0029AEF0;
extern struct DotrTekiWindowPair D_0029AF50;
extern struct DotrTekiWindowWindow D_00297B40[];
extern struct DotrTekiWindowWindow D_00297BCA;
extern struct DotrTekiWindowItem D_00298120[];
extern struct DotrTekiWindowItem D_002983A0[];
extern struct DotrTekiWindowItem D_00298320[];
extern struct DotrTekiWindowItemU D_002980A0;
extern struct DotrTekiWindowItem D_00297D00[];
extern struct DotrTekiWindowItem D_00297DA0[];
extern struct DotrTekiWindowItem D_00298B1C;
extern unsigned short D_00297EA0;
extern unsigned char D_002999CC[][4];
extern char D_0030F1E8[];
extern char D_0030F1EF[];
struct DotrTekiWindowCard {
    unsigned char b0;
};
#define DOTR_TEKI_WINDOW_BASE 0x1ed0000
#define DOTR_TEKI_WINDOW_FACE ((struct DotrTekiWindowFace *)0x1ed5424)
extern int Taku_Window_Set(int cursor, struct DotrTekiWindowWindow *window, unsigned short flag, int a3,
                           unsigned short x, unsigned short y, int a6, int a7, int a8);
extern int func_00217BD0_b(int cursor, struct DotrTekiWindowItem *item, short x, short y);
extern int func_00218020_b(int cursor, struct DotrTekiWindowItem *item, short x, short y, int a4);
extern int func_00218970_b(int cursor, struct DotrTekiWindowItem *item, short x, short y);
extern struct DotrTekiWindowInfo *func_001FEAB0_b(int index);
extern void func_001FDFE0_b(void);
extern int func_001FE660_b(int cursor, int index, int x, int y, float sx, float sy, void *e,
                                 void (*function)(void));
extern int func_00215D30_b(int side, int id);
extern int func_001B6EA0_b(int cursor, int x, int y, int a, int flags, int width,
                                            int value);
extern int func_001B6F70_b(int cursor, int x, int y, int a, int flags, int n,
                                       const char *text, int c);
extern struct DotrTekiWindowCard *func_001DD0E0_b(int id);
#define WB(o) (*(signed char *)(DOTR_TEKI_WINDOW_BASE + (o)))
#define WH(o) (*(short *)(DOTR_TEKI_WINDOW_BASE + (o)))
#define WU(o) (*(unsigned short *)(DOTR_TEKI_WINDOW_BASE + (o)))
#define FACE DOTR_TEKI_WINDOW_FACE
#define RATIO(cur, xx, yy, lim, limf) \
    info = func_001FEAB0_b(1); \
    if (info->w < lim) { \
        cursor = func_001FE660_b(cur, 1, xx, yy, 1.0f, 1.0f, col, func_001FDFE0_b); \
    } else { \
        cursor = func_001FE660_b(cur, 1, xx, yy, limf / (float)info->w, 1.0f, col, func_001FDFE0_b); \
    } \
    SzMsg_Free(1);

int Taku_Camp_TEKI_WINDOW(int cursor)
{
    struct DotrTekiWindowBoard *b = &D_00299E10_b;
    struct DotrTekiWindowNames names;
    struct DotrTekiWindowPair its;
    short x;
    short y;
    short sel;
    short name;
    short msg;
    signed char side;
    short disp;
    short yoff;
    short k;
    unsigned char col[4];
    struct DotrTekiWindowInfo *info;

    names = D_0029AEF0;
    its = D_0029AF50;
    disp = 0;
    sel = 0;
    name = 196;
    k = b->b198;
    col[0] = col[1] = col[2] = 128;
    col[3] = 128;
    x = WB(0x5440) * -640 / 100;
    y = WH(0x6c) - 256;
    yoff = (WH(0x68) << 8) >> 4;
    if (WB(0x18c) == 1 && b->b198 == 11) {
        side = b->b0 ^ 1;
    } else if (b->b198 == 11) {
        side = b->b0 ^ 1;
    } else if (D_00298BA0[b->b198].h10 == 8) {
        side = 0;
    } else {
        side = 1;
    }
    switch (k) {
    case 0: name = 215; msg = 237; break;
    case 1: msg = 240; break;
    case 2: name = 198; msg = 220; break;
    case 3: name = 205; msg = 227; break;
    case 4: name = 204; msg = 226; break;
    case 5: name = 200; msg = 222; break;
    case 6: name = 203; msg = 225; break;
    case 7: name = 206; msg = 228; break;
    case 8: name = 199; msg = 221; break;
    case 9: name = 202; msg = 224; break;
    case 10: name = 201; msg = 223; break;
    case 11:
        if (WB(0x18c) != 0) {
            if (WB(0x53c2) == 2) {
                name = 217; msg = 239;
                side = 0;
            } else {
                side = 1;
                if (WB(0x53c2) == 1) {
                    name = 216; msg = 238;
                } else {
                    name = 197; msg = 219;
                }
            }
        } else if (b->b0 == 0 && b->lv[11] >= 3) {
            if (WB(0x53c2) == 1) {
                name = 216; msg = 238;
            } else {
                name = 197; msg = 219;
            }
        } else if (b->b0 == 1) {
            name = 217; msg = 239;
        } else {
            name = 197; msg = 219;
        }
        break;
    case 12: name = 207; msg = 229; break;
    case 13: name = 208; msg = 230; break;
    case 14: name = 209; msg = 231; break;
    case 15: msg = 241; break;
    case 16: name = 210; msg = 232; break;
    case 17: msg = 242; break;
    case 18: name = 211; msg = 233; break;
    case 19: name = 212; msg = 234; break;
    case 20: name = 213; msg = 235; break;
    case 21: name = 214; msg = 236; break;
    default: name = 196; msg = 218; break;
    }
    b->h196 = name - 196;
    if (WH(0x6c) != 0) {
        if (WB(0x18c) != 0) {
            if (b->b198 == 1 || b->b198 == 15 || b->b198 == 17) {
                sel = 0;
                disp = 0;
            } else {
                sel = 1;
                disp = sel;
            }
        } else if (b->b0 == 0) {
            if (b->b198 == 0 || b->b198 == 1) {
                sel = 0;
                disp = 0;
            } else if (b->b198 == 11 && b->lv[b->b198] <= 0) {
                sel = 0;
                disp = 0;
            } else {
                switch (b->lv[b->b198]) {
                case 1:
                    disp = 1;
                    sel = 0;
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                    if (WB(0x53ab) != 0) {
                        sel = 0;
                    } else {
                        sel = 1;
                        if (b->b198 == 11 && WB(0x53c2) == 1 && b->lv[11] < 4) {
                            sel = 0;
                        }
                    }
                    disp = 1;
                    break;
                }
            }
        } else {
            if (b->b198 == 15 || b->b198 == 17) {
                sel = 0;
                disp = 0;
            } else if (b->b198 == 11 && b->lv[b->b198] <= 0) {
                sel = 0;
                disp = 0;
            } else {
                switch (b->lv[b->b198]) {
                case 1:
                    disp = 1;
                    sel = 0;
                    break;
                case 2:
                case 3:
                    if (WB(0x53ab) != 0) {
                        sel = 0;
                    } else {
                        sel = 1;
                    }
                    disp = 1;
                    break;
                }
            }
        }
        if (WB(0x537b) != 0 && WB(0x5440) == 100) {
            sel = 1;
            disp = sel;
        }
        if (WB(0x537a) != 0 && WB(0x537b) != 0 && WB(0x5440) < 100) {
            sel = 1;
            disp = sel;
        }
        if (disp) {
            int yy;
            short no;
            short cost;

            cursor = func_00217BD0_b(cursor, &D_00298120[side], 0, y);
            cursor = Taku_Window_Set(cursor, &D_00297B40[0], side, 0, 0, y, 0, 128, WH(0x224));
            cursor = Taku_Window_Set(cursor, &D_00297B40[2], side, 0, 0, y, 0, 128, WH(0x224));
            yy = y - yoff;
            cursor = Taku_Window_Set(cursor, &D_00297B40[3], side, 0, 0, yy, 1, 128, 0);
            no = b->h196 + 1;
            if (name == 217) {
                no = b->h196;
            }
            switch (WB(0x540a)) {
            case 1:
                FACE->id = 255;
                
            case 2:
                FACE->no = no;
                FACE->kind = D_002999CC[no][WB(0x5468)];
                FACE->mode = 1;
                FACE->x = D_00297B40[3].x;
                FACE->y = D_00297B40[3].y + y - yoff;
                ShFace_Request(FACE);
                WB(0x540a) = 2;
                break;
            case 10:
                FACE->no = no;
                FACE->kind = D_002999CC[no][WB(0x5468)];
                FACE->mode = 3;
                FACE->x = D_00297B40[3].x;
                FACE->y = D_00297B40[3].y + y - yoff;
                ShFace_Request(FACE);
                WB(0x540a) = 2;
                break;
            case 100:
                ShFace_Close(FACE);
                WB(0x540a) = 0;
                break;
            }
            cursor = func_00218020_b(cursor, &D_002983A0[2], 0, yy, 0);
            cursor = func_00218020_b(cursor, &D_002983A0[3], 0, yy, 0);
            cursor = func_00218020_b(cursor, &D_002983A0[side], 0, yy, 0);
            if (WB(0x5406) == 0) {
                SzData_SetupFromConstDeck(1, b->h196 + 26);
            }
            cost = WH(0x5444) = SzData_GetDeckCost(1, 0);
            cursor = func_00217BD0_b(cursor, &D_00298320[0], 0, y);
            cursor = func_001B6EA0_b(cursor, 410, y + 26, 0, 0, 4, cost);
            cursor = SzMsg_LoadFont_Pipe(cursor, 1, name, 0, 22);
            cursor = RhText_SetTextureFlush(cursor);
            info = func_001FEAB0_b(1);
            if (info->w < 324) {
                

                float sy;
                float sx;

                sy = sx = 1.0f;
                cursor = func_001FE660_b(cursor, 1, 53, y + 21, sx, sy, col, func_001FDFE0_b);
            } else {
                cursor = func_001FE660_b(cursor, 1, 53, y + 21, 324.0f / (float)info->w, 1.0f, col, func_001FDFE0_b);
            }
            SzMsg_Free(1);
        }
        if (sel == 0) {
            WB(0x5406) = -1;
        } else if (WB(0x5406) == 0) {
            WB(0x5406) = 1;
        }
        if (WB(0x537a) != 0 && WB(0x5440) == 100 && WB(0x5406) < 2) {
            WB(0x5406) = 1;
        }
        if (sel) {
            int id;
            int xs;
            short rank;
            int r;
            short tx;
            short ty;

            WB(0x5488) = 1;
            id = SzData_GetLeader(1, 0);
            cursor = Taku_Window_Set(cursor, &D_00297B40[1], side, 0, x, y, 0, 128, WH(0x224));
            cursor = Taku_Window_Set(cursor, &D_00297B40[4], side, 0, x, y, 0, 128, WH(0x224));
            cursor = Taku_Window_Set(cursor, &D_00297BCA, side, 0, x, y, 0, 128, WH(0x224));
            xs = x;
            cursor = func_001B6F70_b(cursor, xs + 152, y + 63, 1, 1, 4, D_0030F102, 0);
            cursor = func_001B6F70_b(cursor, xs + 192, y + 63, 1, 1, 6, D_0030F1E8, 0);
            switch ((func_001DD0E0_b(id)->b0 & 0x1f) + 1) {
            case 1: D_002980A0.code = 78; break;
            case 2: D_002980A0.code = 88; break;
            case 3: D_002980A0.code = 93; break;
            case 4: D_002980A0.code = 79; break;
            case 5: D_002980A0.code = 83; break;
            case 6: D_002980A0.code = 85; break;
            case 7: D_002980A0.code = 86; break;
            case 8: D_002980A0.code = 87; break;
            case 9: D_002980A0.code = 81; break;
            case 10: D_002980A0.code = 82; break;
            case 11: D_002980A0.code = 89; break;
            case 12: D_002980A0.code = 84; break;
            case 13: D_002980A0.code = 90; break;
            case 14: D_002980A0.code = 91; break;
            case 15: D_002980A0.code = 92; break;
            case 16: D_002980A0.code = 80; break;
            case 17: D_002980A0.code = 94; break;
            case 18: D_002980A0.code = 95; break;
            case 19: D_002980A0.code = 96; break;
            case 20: D_002980A0.code = 97; break;
            case 21: D_002980A0.code = 101; break;
            default: D_002980A0.code = D_00297EA0; break;
            }
            cursor = func_00217BD0_b(cursor, (struct DotrTekiWindowItem *)&D_002980A0, x, y);
            rank = func_00215D30_b(1, id);
            if (rank != 0) {
                r = rank - 1;
                cursor = func_00217BD0_b(cursor, &D_00297D00[(short)(r / 3)], x, y);
                switch ((short)(r % 3 + 1)) {
                case 1:
                    cursor = func_00217BD0_b(cursor, &D_00297DA0[2], x, y);
                    break;
                case 2:
                    cursor = func_00217BD0_b(cursor, &D_00297DA0[0], x, y);
                    cursor = func_00217BD0_b(cursor, &D_00297DA0[1], x, y);
                    break;
                case 3:
                    cursor = func_00217BD0_b(cursor, &D_00297DA0[0], x, y);
                    cursor = func_00217BD0_b(cursor, &D_00297DA0[1], x, y);
                    cursor = func_00217BD0_b(cursor, &D_00297DA0[2], x, y);
                    break;
                }
            }
            cursor = func_00217BD0_b(cursor, &D_00298320[1], x, y);
            cursor = func_00217BD0_b(cursor, &D_00298320[2], x, y);
            cursor = func_001B6EA0_b(cursor, xs + 324, y + 73, 1, 0, 4, b->h66[b->h196]);
            cursor = func_001B6EA0_b(cursor, xs + 421, y + 73, 1, 0, 4, b->h130[b->h196]);
            cursor = SzMsg_LoadFont_Pipe(cursor, 1, SzDuel_GetMsgName(id), 0, 22);
            cursor = RhText_SetTextureFlush(cursor);
            tx = (short)D_00297B40[4].x + 4 + x;
            ty = (short)D_00297B40[4].y + 2 + y;
            RATIO(cursor, tx, ty, 246, 246.0f)
        }
    }
    if (WB(0x5472) != 0) {
        short len;
        int len10;
        short tx;
        int wd;

        len = func_0019BEF0(names.s[b->b198]);
        len10 = (short)(len * 10);
        cursor = SzMsg_LoadFont_Pipe(cursor, 1, 258, 0, 22);
        cursor = RhText_SetTextureFlush(cursor);
        info = func_001FEAB0_b(1);
        if (info->w < (short)len10) {
            wd = len10 + 16;
        } else {
            wd = *(short *)&info->w + 16;
        }
        D_00297B40[7].w = wd;
        tx = 320 - ((short)wd >> 1);
        cursor = Taku_Window_Set(cursor, &D_00297B40[7], 2, 0, tx, 224, 0, 128, 64);
        cursor = func_001FE660_b(cursor, 1, tx + 8, 228, 1.0f, 1.0f, col, func_001FDFE0_b);
        SzMsg_Free(1);
    } else if (WB(0x5374) == 0 && WU(4) == 2 && WB(0x72) == 0 && WB(0x547a) == 0 && WB(0x6e) != 0
               && WB(0x5481) != 0 && !SzEffect_IsUse2(-1, -1) && WB(0x5376) != 0 && WB(0x5482) == 0) {
        int cx;
        short wd;
        int tx;
        int c;
        int d;
        short ty;
        int m;
        int half;
        short px;

        func_0019BEF0(names.s[b->b198]);
        if (WB(0x5446) == 0) {
            m = msg;
        } else {
            m = 249;
            WB(0x5446) = 0;
        }
        cursor = SzMsg_LoadFont_Pipe(cursor, 1, m, 0, 22);
        c = RhText_SetTextureFlush(cursor);
        info = func_001FEAB0_b(1);
        wd = *(short *)&info->w + 16;
        D_00297B40[5].w = wd;
        cx = WH(0);
        half = wd >> 1;
        d = cx - half;
        px = d;
        if (d <= 0) {
            px = 0;
        }
        if (cx + half >= 480) {
            px = 480 - wd;
        }
        tx = px;
        ty = WH(2) + 32;
        if (tx < 128 && ty < 209) {
            ty = 208;
        } else if (ty < 121) {
            ty = 120;
        }
        if (ty >= 290) {
            ty = 290;
        }
        cursor = Taku_Window_Set(c, &D_00297B40[5], 2, 0, px, ty, 0, 128, 64);
        cursor = func_001FE660_b(cursor, 1, tx + 8, ty + 4, 1.0f, 1.0f, col, func_001FDFE0_b);
        SzMsg_Free(1);
    }
    if ((b->b0 == 0 && b->lv[11] >= 3) || WB(0x18c) != 0) {
        if (b->b198 == 11) {
            short yo;
            short ys;

            yo = yoff;
            ys = y;
            cursor = func_00218970_b(cursor, &D_00298B1C, 0, ys - yo);
            cursor = func_001B6F70_b(cursor, D_00298B1C.w[0] + 40,
                                                 D_00298B1C.w[1] + y + 24 - yo, 1, 1, 6,
                                                 D_0030F1EF, 0);
            cursor = func_00217BD0_b(cursor, &its.it[0], D_00298B1C.w[0] + 4,
                                  (short)(D_00298B1C.w[1] + 24) + ys - yo);
            cursor = func_00217BD0_b(cursor, &its.it[1], D_00298B1C.w[2] - 26,
                                  (short)(D_00298B1C.w[1] + 24) + ys - yo);
        }
    }
    return cursor;
}
#undef DOTR_TEKI_WINDOW_BASE
#undef DOTR_TEKI_WINDOW_FACE
#undef WB
#undef WH
#undef WU
#undef FACE
#undef RATIO
