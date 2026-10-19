/* Campaign map, part 3 of 3: the enemy and terrain windows, the map's 3D polygons, TkCamp_Act (one frame of the campaign map), practice duels, help, card rewards. */

#include "common.h"
#include "campaign.h"

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
extern struct DotrTekiWindowRec campaignPlaces[]; /* original: model_data */
struct DotrTekiWindowNames {
    char *s[22];
};
struct DotrTekiWindowPair {
    struct DotrTekiWindowItem it[2];
};
extern struct DotrTekiWindowNames D_0029AEF0;
extern struct DotrTekiWindowPair D_0029AF50;
extern struct DotrTekiWindowWindow campaignEnemyWindow[]; /* original: camp_window_Teki_data */
extern struct DotrTekiWindowWindow D_00297BCA;
extern struct DotrTekiWindowItem roseSprites2[]; /* original: tex_bara_data2 */
extern struct DotrTekiWindowItem campaignEnemyWindowItems[]; /* original: camp_window_teki3 */
extern struct DotrTekiWindowItem camp_window_Enemy[];
extern struct DotrTekiWindowItemU teki_syurui_data;
extern struct DotrTekiWindowItem tex_batti_data2[];
extern struct DotrTekiWindowItem tex_hosi_data2[];
extern struct DotrTekiWindowItem D_00298B1C;
extern unsigned short teki_syurui_tex_no;
extern unsigned char D_002999CC[][4];
extern char D_0030F1E8[];
extern char D_0030F1EF[];
struct DotrTekiWindowCard {
    unsigned char b0;
};
extern int Taku_Window_Set_window(int cursor, struct DotrTekiWindowWindow *window, unsigned short flag, int a3,
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
#define RATIO(cur, xx, yy, lim, limf) \
    info = func_001FEAB0_b(1); \
    if (info->w < lim) { \
        cursor = func_001FE660_b(cur, 1, xx, yy, 1.0f, 1.0f, col, func_001FDFE0_b); \
    } else { \
        cursor = func_001FE660_b(cur, 1, xx, yy, limf / (float)info->w, 1.0f, col, func_001FDFE0_b); \
    } \
    SzMsg_Free(1);

/* Draws the opponent (teki) window: name, face, leader, deck cost; sets up the opponent's deck. (original: Taku_Camp_TEKI_WINDOW) */
int Taku_Camp_ENEMY_WINDOW(int cursor)
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
    x = campaignWork.unk5440 * -640 / 100;
    y = campaignWork.windowOpen - 256;
    yoff = (campaignWork.terrainWindowOpen << 8) >> 4;
    if (campaignWork.unk018C == 1 && b->b198 == 11) {
        side = b->b0 ^ 1;
    } else if (b->b198 == 11) {
        side = b->b0 ^ 1;
    } else if (campaignPlaces[b->b198].h10 == 8) {
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
        if (campaignWork.unk018C != 0) {
            if (campaignWork.duelMenuChoice == 2) {
                name = 217; msg = 239;
                side = 0;
            } else {
                side = 1;
                if (campaignWork.duelMenuChoice == 1) {
                    name = 216; msg = 238;
                } else {
                    name = 197; msg = 219;
                }
            }
        } else if (b->b0 == 0 && b->lv[11] >= 3) {
            if (campaignWork.duelMenuChoice == 1) {
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
    if (campaignWork.windowOpen != 0) {
        if (campaignWork.unk018C != 0) {
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
                    if (campaignWork.unk53AB != 0) {
                        sel = 0;
                    } else {
                        sel = 1;
                        if (b->b198 == 11 && campaignWork.duelMenuChoice == 1 && b->lv[11] < 4) {
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
                    if (campaignWork.unk53AB != 0) {
                        sel = 0;
                    } else {
                        sel = 1;
                    }
                    disp = 1;
                    break;
                }
            }
        }
        if (campaignWork.talkStep != 0 && campaignWork.unk5440 == 100) {
            sel = 1;
            disp = sel;
        }
        if (campaignWork.unk537A != 0 && campaignWork.talkStep != 0 && campaignWork.unk5440 < 100) {
            sel = 1;
            disp = sel;
        }
        if (disp) {
            int yy;
            short no;
            short cost;

            cursor = func_00217BD0_b(cursor, &roseSprites2[side], 0, y);
            cursor = Taku_Window_Set_window(cursor, &campaignEnemyWindow[0], side, 0, 0, y, 0, 128, campaignWork.windowAlpha[0]);
            cursor = Taku_Window_Set_window(cursor, &campaignEnemyWindow[2], side, 0, 0, y, 0, 128, campaignWork.windowAlpha[0]);
            yy = y - yoff;
            cursor = Taku_Window_Set_window(cursor, &campaignEnemyWindow[3], side, 0, 0, yy, 1, 128, 0);
            no = b->h196 + 1;
            if (name == 217) {
                no = b->h196;
            }
            switch (campaignWork.opponentFaceState) {
            case 1:
                campaignWork.opponentFace.id = 255;
                
            case 2:
                campaignWork.opponentFace.no = no;
                campaignWork.opponentFace.kind = D_002999CC[no][campaignWork.opponentLook];
                campaignWork.opponentFace.mode = 1;
                campaignWork.opponentFace.x = campaignEnemyWindow[3].x;
                campaignWork.opponentFace.y = campaignEnemyWindow[3].y + y - yoff;
                ShFace_Request(&campaignWork.opponentFace);
                campaignWork.opponentFaceState = 2;
                break;
            case 10:
                campaignWork.opponentFace.no = no;
                campaignWork.opponentFace.kind = D_002999CC[no][campaignWork.opponentLook];
                campaignWork.opponentFace.mode = 3;
                campaignWork.opponentFace.x = campaignEnemyWindow[3].x;
                campaignWork.opponentFace.y = campaignEnemyWindow[3].y + y - yoff;
                ShFace_Request(&campaignWork.opponentFace);
                campaignWork.opponentFaceState = 2;
                break;
            case 100:
                ShFace_Close((u8 *)&campaignWork.opponentFace);
                campaignWork.opponentFaceState = 0;
                break;
            }
            cursor = func_00218020_b(cursor, &campaignEnemyWindowItems[2], 0, yy, 0);
            cursor = func_00218020_b(cursor, &campaignEnemyWindowItems[3], 0, yy, 0);
            cursor = func_00218020_b(cursor, &campaignEnemyWindowItems[side], 0, yy, 0);
            if (campaignWork.unk5406 == 0) {
                SzData_SetupFromConstDeck(1, b->h196 + 26);
            }
            cost = campaignWork.opponentDeckCost = SzData_GetDeckCost(1, 0);
            cursor = func_00217BD0_b(cursor, &camp_window_Enemy[0], 0, y);
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
            campaignWork.unk5406 = -1;
        } else if (campaignWork.unk5406 == 0) {
            campaignWork.unk5406 = 1;
        }
        if (campaignWork.unk537A != 0 && campaignWork.unk5440 == 100 && campaignWork.unk5406 < 2) {
            campaignWork.unk5406 = 1;
        }
        if (sel) {
            int id;
            int xs;
            short rank;
            int r;
            short tx;
            short ty;

            campaignWork.unk5488 = 1;
            id = SzData_GetLeader(1, 0);
            cursor = Taku_Window_Set_window(cursor, &campaignEnemyWindow[1], side, 0, x, y, 0, 128, campaignWork.windowAlpha[0]);
            cursor = Taku_Window_Set_window(cursor, &campaignEnemyWindow[4], side, 0, x, y, 0, 128, campaignWork.windowAlpha[0]);
            cursor = Taku_Window_Set_window(cursor, &D_00297BCA, side, 0, x, y, 0, 128, campaignWork.windowAlpha[0]);
            xs = x;
            cursor = func_001B6F70_b(cursor, xs + 152, y + 63, 1, 1, 4, D_0030F102, 0);
            cursor = func_001B6F70_b(cursor, xs + 192, y + 63, 1, 1, 6, D_0030F1E8, 0);
            switch ((func_001DD0E0_b(id)->b0 & 0x1f) + 1) {
            case 1: teki_syurui_data.code = 78; break;
            case 2: teki_syurui_data.code = 88; break;
            case 3: teki_syurui_data.code = 93; break;
            case 4: teki_syurui_data.code = 79; break;
            case 5: teki_syurui_data.code = 83; break;
            case 6: teki_syurui_data.code = 85; break;
            case 7: teki_syurui_data.code = 86; break;
            case 8: teki_syurui_data.code = 87; break;
            case 9: teki_syurui_data.code = 81; break;
            case 10: teki_syurui_data.code = 82; break;
            case 11: teki_syurui_data.code = 89; break;
            case 12: teki_syurui_data.code = 84; break;
            case 13: teki_syurui_data.code = 90; break;
            case 14: teki_syurui_data.code = 91; break;
            case 15: teki_syurui_data.code = 92; break;
            case 16: teki_syurui_data.code = 80; break;
            case 17: teki_syurui_data.code = 94; break;
            case 18: teki_syurui_data.code = 95; break;
            case 19: teki_syurui_data.code = 96; break;
            case 20: teki_syurui_data.code = 97; break;
            case 21: teki_syurui_data.code = 101; break;
            default: teki_syurui_data.code = teki_syurui_tex_no; break;
            }
            cursor = func_00217BD0_b(cursor, (struct DotrTekiWindowItem *)&teki_syurui_data, x, y);
            rank = func_00215D30_b(1, id);
            if (rank != 0) {
                r = rank - 1;
                cursor = func_00217BD0_b(cursor, &tex_batti_data2[(short)(r / 3)], x, y);
                switch ((short)(r % 3 + 1)) {
                case 1:
                    cursor = func_00217BD0_b(cursor, &tex_hosi_data2[2], x, y);
                    break;
                case 2:
                    cursor = func_00217BD0_b(cursor, &tex_hosi_data2[0], x, y);
                    cursor = func_00217BD0_b(cursor, &tex_hosi_data2[1], x, y);
                    break;
                case 3:
                    cursor = func_00217BD0_b(cursor, &tex_hosi_data2[0], x, y);
                    cursor = func_00217BD0_b(cursor, &tex_hosi_data2[1], x, y);
                    cursor = func_00217BD0_b(cursor, &tex_hosi_data2[2], x, y);
                    break;
                }
            }
            cursor = func_00217BD0_b(cursor, &camp_window_Enemy[1], x, y);
            cursor = func_00217BD0_b(cursor, &camp_window_Enemy[2], x, y);
            cursor = func_001B6EA0_b(cursor, xs + 324, y + 73, 1, 0, 4, b->h66[b->h196]);
            cursor = func_001B6EA0_b(cursor, xs + 421, y + 73, 1, 0, 4, b->h130[b->h196]);
            cursor = SzMsg_LoadFont_Pipe(cursor, 1, SzDuel_GetMsgName(id), 0, 22);
            cursor = RhText_SetTextureFlush(cursor);
            tx = (short)campaignEnemyWindow[4].x + 4 + x;
            ty = (short)campaignEnemyWindow[4].y + 2 + y;
            RATIO(cursor, tx, ty, 246, 246.0f)
        }
    }
    if (campaignWork.unk5472 != 0) {
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
        campaignEnemyWindow[7].w = wd;
        tx = 320 - ((short)wd >> 1);
        cursor = Taku_Window_Set_window(cursor, &campaignEnemyWindow[7], 2, 0, tx, 224, 0, 128, 64);
        cursor = func_001FE660_b(cursor, 1, tx + 8, 228, 1.0f, 1.0f, col, func_001FDFE0_b);
        SzMsg_Free(1);
    } else if (campaignWork.unk5374 == 0 && campaignWork.unk0004 == 2 && campaignWork.unk0072 == 0 && campaignWork.cursorOnIcon == 0 && campaignWork.unk006E != 0
               && campaignWork.unk5481 != 0 && !SzEffect_IsUse2(-1, -1) && campaignWork.routesIdle != 0 && campaignWork.placesReached == 0) {
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
        if (campaignWork.unk5446 == 0) {
            m = msg;
        } else {
            m = 249;
            campaignWork.unk5446 = 0;
        }
        cursor = SzMsg_LoadFont_Pipe(cursor, 1, m, 0, 22);
        c = RhText_SetTextureFlush(cursor);
        info = func_001FEAB0_b(1);
        wd = *(short *)&info->w + 16;
        campaignEnemyWindow[5].w = wd;
        cx = campaignWork.cursorX;
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
        ty = campaignWork.cursorY + 32;
        if (tx < 128 && ty < 209) {
            ty = 208;
        } else if (ty < 121) {
            ty = 120;
        }
        if (ty >= 290) {
            ty = 290;
        }
        cursor = Taku_Window_Set_window(c, &campaignEnemyWindow[5], 2, 0, px, ty, 0, 128, 64);
        cursor = func_001FE660_b(cursor, 1, tx + 8, ty + 4, 1.0f, 1.0f, col, func_001FDFE0_b);
        SzMsg_Free(1);
    }
    if ((b->b0 == 0 && b->lv[11] >= 3) || campaignWork.unk018C != 0) {
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
#undef RATIO

/* Draws the terrain (tikei) window of the campaign place under the cursor. (original: Taku_Camp_TIKEI_WINDOW) */
s32 Taku_Camp_TERRAIN_WINDOW(s32 packet) {
    extern s32 Taku_Window_Set(s32, void *, s32, s32, u16, s32, s32, s32, s32);
    extern s32 Taku_Camp_TERRAIN_Map_Show(s32, u16, u16, s32);
    extern s32 Taku_Obj_Set();
    extern s32 Taku_FT4_Set();
    extern u8 campaignMapWindow[];
    extern u8 D_00297B9A[];
    extern u8 D_00297BA4[];
    extern u8 campaignTerrainColourTop[];
    extern u8 campaignTerrainColourBottom[];
    extern u8 campaignTerrainParts[];
    extern u8 campaignTerrainGaugeFrame[];
    extern u8 D_00298BB0[];
    s8 *state;
    s16 baseX;
    s64 alpha;
    s64 side;
    s32 i;
    u8 *p;
    s32 j;
    s32 y;
    s32 row;
    u8 *q;
    s16 fade;

    baseX = SelectedBattleArena;
    state = &campaignState;
    if (campaignWork.terrainWindowOn != 0) {
        campaignWork.terrainWindowOpen += 2;
        if (campaignWork.terrainWindowOpen > 16) {
            campaignWork.terrainWindowOpen = 16;
        }
    } else {
        campaignWork.terrainWindowOpen -= 2;
        if (campaignWork.terrainWindowOpen < 0) {
            campaignWork.terrainWindowOpen = 0;
        }
    }
    fade = campaignWork.terrainWindowOpen;
    alpha = (s16)(256 - ((fade << 8) >> 4));
    if (campaignWork.unk018C == 1 && state[0xC6] == 11) {
        side = (s8)(state[0] ^ 1);
    } else if (state[0xC6] == 11) {
        side = (s8)(state[0] ^ 1);
    } else {
        if (*(s16 *)(D_00298BB0 + state[0xC6] * 0x34) == 8) {
            side = 0;
        } else {
            side = 1;
        }
    }
    if (fade != 0) {
        packet = Taku_Window_Set(packet, campaignMapWindow, (u16)(s8)side & 0xFFFF, 0,
                              alpha, 0, 0, 128, campaignWork.windowAlpha[2]);
        packet = Taku_Camp_TERRAIN_Map_Show(packet, baseX, alpha, 0);
        packet = Taku_Window_Set(packet, D_00297B9A, (u16)(s8)side, 0,
                              alpha, 0, 0, 128, 128);
        packet = Taku_Window_Set(packet, D_00297BA4, (u16)(state[0] ^ 1), 0,
                              alpha, 0, 0, 128, 128);
        p = campaignTerrainParts;
        i = 0;
        do {
            packet = Taku_Obj_Set(packet, p, alpha, 0);
            i++;
            p += 0x26;
        } while (i < 10);
        row = 0;
        y = 0;
        do {
            q = campaignTerrainGaugeFrame;
            j = 0;
            do {
                packet = Taku_Obj_Set(packet, q, alpha, y);
                j++;
                q += 0x26;
            } while (j < 3);
            y = (s16)(y + 16);
            row++;
        } while (row < 10);
        packet = Taku_FT4_Set(packet, campaignTerrainColourTop + (s8)side * 0x26, alpha, 0, 0);
        packet = Taku_FT4_Set(packet, campaignTerrainColourBottom + state[0] * 0x26, alpha, 0, 2);
    }
    return packet;
}

typedef struct Sprite_00236F90 {
    s16 xy[8];
    u8 pad10[0x14];
    s16 tile;
} Sprite_00236F90;

/* Draws (hyouji) the small terrain map of deck `deck`'s place at (x, y). (original: Taku_Camp_TIKEI_Map_Hyouji) */
s32 Taku_Camp_TERRAIN_Map_Show(s32 gp, u16 deck, u16 x, u16 y) {
    extern s32 Taku_Obj_Set(s32, void *, s16, s16);
    extern s32 Taku_G4_Set(s32, void *, s16, s16);
    extern s32 Taku_G4_Set2(s32, void *, s16, s16, s16, s16);
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe(s32, s32, s32, s32, s32, s32, s32);
    extern Sprite_00236F90 D_0029AFA0;
    extern Sprite_00236F90 D_0029AFD0;
    extern u8 gSzDuel_MapData[];
    extern Sprite_00236F90 campaignTerrainGauge[][2];
    extern s16 NumOfTilesBoxDistanceFromRightSide;
    extern s16 NumOfTilesBlackBackgroundBox;
    extern s16 NumOfTilesBoxDistanceFromLeftSide;
    extern s16 NumOfTilesBlackBackgroundBox2;
    CampaignWork *work;
    s8 *mode;
    s32 row;
    u8 *grid;
    s32 col;
    Sprite_00236F90 card;
    Sprite_00236F90 bar;
    s32 j;
    s32 i;
    s16 dy;
    s32 cx;
    s16 tile;
    s32 cy;
    f32 scale;
    u8 *cell;
    s32 k;

    mode = &campaignState;
    work = &campaignWork;
    card = D_0029AFA0;
    bar = D_0029AFD0;
    for (i = 0; i < 10; i++) {
        work->terrainCounts[i] = 0;
    }
    for (row = 0, grid = &gSzDuel_MapData[deck * 49]; row < 7; row++) {
        cell = grid;
        for (col = 0; col < 7; col++) {
            switch ((s16)*cell) {
            case 0:
                tile = 'A';
                work->terrainCounts[0]++;
                break;
            case 1:
                tile = 'B';
                work->terrainCounts[1]++;
                break;
            case 2:
                tile = 'C';
                work->terrainCounts[2]++;
                break;
            case 3:
                tile = 'D';
                work->terrainCounts[3]++;
                break;
            case 4:
                tile = 'E';
                work->terrainCounts[4]++;
                break;
            case 5:
                tile = 'F';
                work->terrainCounts[5]++;
                break;
            case 6:
                tile = 'G';
                work->terrainCounts[6]++;
                break;
            case 7:
                tile = 'H';
                work->terrainCounts[7]++;
                break;
            case 8:
                tile = 'I';
                work->terrainCounts[8]++;
                break;
            case 9:
                tile = 'J';
                work->terrainCounts[9]++;
                break;
            default:
                tile = 'A';
                break;
            }
            card.tile = tile;
            if (*mode == 1) {
                cx = 6 - col;
                cy = 6 - row;
            } else {
                cx = col;
                cy = row;
            }
            gp = Taku_Obj_Set(gp, &card, x + cx * 16, y + cy * 16);
            cell++;
        }
        grid += 7;
    }
    for (i = 0, dy = 0; i < 10; i++) {
        bar.xy[0] = NumOfTilesBoxDistanceFromRightSide;
        bar.xy[1] = NumOfTilesBlackBackgroundBox;
        bar.xy[2] = NumOfTilesBoxDistanceFromLeftSide;
        bar.xy[3] = NumOfTilesBlackBackgroundBox;
        bar.xy[4] = NumOfTilesBoxDistanceFromRightSide;
        bar.xy[5] = NumOfTilesBlackBackgroundBox2;
        bar.xy[6] = NumOfTilesBoxDistanceFromLeftSide;
        bar.xy[7] = NumOfTilesBlackBackgroundBox2;
        gp = Taku_G4_Set(gp, &bar, x, y + dy);
        dy += 16;
    }
    for (i = 0, dy = 0; i < 10; i++, dy += 16) {
        if (work->terrainCounts[i] >= 49) {
            scale = 76.0f;
        } else if (work->terrainCounts[i] <= 0) {
            scale = 0.0f;
        } else {
            scale = (76.0f * work->terrainCounts[i]) / 49.0f;
        }
        for (k = 0; k < 2; k++) {
            for (j = 0; j < 8; j++) {
                campaignTerrainGauge[i][k].xy[j] = campaignTerrainGauge[0][k].xy[j];
            }
            gp = Taku_G4_Set2(gp, &campaignTerrainGauge[i][k], x, y + dy, scale, 0);
        }
        gp = SzDuel_DrawWindow_FontDigit_Pipe(gp, x + ((NumOfTilesBoxDistanceFromRightSide + NumOfTilesBoxDistanceFromLeftSide) >> 1),
                                              y + (dy + campaignTerrainGauge[i][0].xy[1]), 1, 2,
                                              (u16)((work->terrainCounts[i] < 10) ? 1 : 2), work->terrainCounts[i]);
    }
    return gp;
}

extern u8 campaignPlaces_2[]; /* original: model_data */
extern u8 campaignCoord[]; /* original: prim_data */
extern s32 D_0029A000;
extern u8 D_0029A44C[];
#pragma opt_strength_reduction off

/* Builds the campaign map's 3D polygons (the ground and the routes). */
void Taku_Camp_3D_Poly_Init(void) {
    s16 spB0;
    u8 *spC0;
    s32 spD0;
    s16 i;
    s32 var_s1;
    u8 *var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    f32 temp_f0;
    f32 temp_f20;
    s32 var_fp;
    s32 var_s7;
    u8 *var_s6;
    s16 j;

    spC0 = campaignCoord;
    var_s6 = D_0029A44C;
    var_s1 = 0;
    Taku_Coord_Init(spC0);
    var_fp = 1;
    var_s7 = 2;
    D_0029A000 = 0;
    spB0 = 0;
    spD0 = 0;
    for (; spB0 < 16; spB0++) {
        var_s2 = spC0;
        i = 0;
        var_s3 = spD0 >> 5;
        var_s4 = (var_fp << 16) >> 5;
        var_s5 = (var_s7 << 16) >> 5;
        for (; i < 4; i++) {
            if (i == 2) {
                *(s32 *)(var_s2 + 0xEC) = 0;
                *(s32 *)(var_s2 + 0xF0) = 0x410A6666;
                *(s32 *)(var_s2 + 0xF4) = 0;
                *(s32 *)(var_s2 + 0xF8) = 0;
            } else {
                switch (i) {
                case 0:
                    var_s1 = var_s3;
                    break;
                case 1:
                    var_s1 = var_s4;
                    break;
                case 3:
                    var_s1 = var_s5;
                    break;
                }
                temp_f20 = 5.0f * RhMath_CosI(var_s1);
                temp_f0 = 5.0f * RhMath_SinI(var_s1);
                *(f32 *)(var_s2 + 0xEC) = temp_f20;
                *(s32 *)(var_s2 + 0xF0) = 0x410A6666;
                *(f32 *)(var_s2 + 0xF4) = temp_f0;
                *(s32 *)(var_s2 + 0xF8) = 0;
            }
            var_s2 += 0x10;
        }
        var_fp += 2;
        var_s7 += 2;
        spC0 += 0x40;
        spD0 += 0x20000;
    }
    j = 0;
    for (; j < 16; j++) {
        Taku_Vector_Set(var_s6, campaignPlaces_2);
        *(s32 *)(var_s6 + 0x20) = 0;
        var_s6[0x26] = 0;
        var_s6[0x2A] = 0;
        var_s6[0x2E] = 0x80;
        var_s6[0x32] = 0x80;
        var_s6[0x24] = 0x80;
        var_s6[0x28] = 0;
        var_s6[0x2C] = 0;
        var_s6[0x30] = 0x80;
        var_s6[0x25] = 0;
        var_s6[0x29] = 0x80;
        var_s6[0x2D] = 0;
        var_s6[0x31] = 0x80;
        var_s6[0x27] = 0x80;
        var_s6[0x2B] = 0;
        var_s6[0x2F] = 0;
        var_s6[0x33] = 0x80;
        var_s6 += 0x34;
    }
}

#include "game.h"
#include "m2c_macros.h"

extern s16 CutSceneNumber;
typedef struct {
    __int128 q;
} TkQ;
extern TkQ D_0029B000;
extern TkQ D_0029B010;
extern s8 D_0030F1F6;
extern s8 D_0030F213;
extern s8 D_0030F227;
extern s8 D_0030F244;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} TkVec4;

extern s32 abs_b(s32 arg0);
extern void SzDuel_OpenOptionPopup_b(s32 arg0, s32 arg1, s32 arg2);
#pragma opt_strength_reduction reset
#pragma conditional_move off
#pragma opt_dead_assignments off
/* Runs one frame of the campaign map mode: input, the camera, pop-ups, the event and duel start, leaving. */
void TkCamp_Act(void) {
    s32 ctx = (s32) &campaignState;
    s16 temp_s1;
    s16 temp_s2;
    s32 var_s3;
    CampaignWork *base = &campaignWork;
    s16 hit;
    s16 ax;
    s16 dx;
    s16 ay;
    s16 sgn;
    s16 temp_s1_3;
    s32 var_s2;
    s16 ok;
    s16 spot;
    f32 vp[4];
    f32 vq[4];
    f32 vr[4];
    f32 vs[4];
    TkQ spE0;
    TkQ spF0;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 fq4;
    s16 *var_a3;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_v0_10;
    s16 temp_v0_11;
    s16 temp_v0_12;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_hi_3;
    s32 temp_hi_4;
    s32 leader;
    s32 currentDeck;
    s32 actMsgPopup;
    s32 var_a0_4;
    s32 i;
    s32 var_s1;
    s32 var_s1_2;
    s32 j;
    s32 temp_a1_4;
    s8 temp_a1_7;
    s8 temp_a1_8;
    s32 temp_v0;
    s8 temp_v0_15;
    s8 temp_v0_16;
    s8 temp_v0_17;
    s32 temp_v0_18;
    s8 temp_v0_20;
    s8 temp_v0_21;
    s32 temp_v0_22;
    s8 c23;
    s8 temp_v0_3;
    s32 temp_v1;
    s8 temp_v1_10;
    s8 temp_v1_11;
    s8 temp_v1_12;
    s8 temp_v1_13;
    s8 temp_v1_14;
    s8 temp_v1_4;
    s8 temp_v1_5;
    s8 temp_v1_6;
    s8 temp_v1_7;
    s8 temp_v1_8;
    s8 temp_v1_9;

    temp_s1 = campaignWork.cursorX;
    temp_s2 = campaignWork.cursorY;
    campaignWork.cursorOnIcon = 0;
    campaignWork.unk5481 = 1;
    campaignWork.placesReached = 0;
    var_s3 = 0;
    if (CutSceneNumber < 0x2710) {
        temp_v0 = campaignWork.unk006E;
        if (temp_v0 != 0) {
            campaignWork.iconSlide = (s16) (campaignWork.iconSlide + 0x14);
            if (campaignWork.iconSlide >= 0x100) {
                campaignWork.iconSlide = 0x100;
                campaignWork.unk5374 = 0;
            }
        } else if ((s8) temp_v0 == 0) {
            campaignWork.unk5374 = 1;
            campaignWork.iconSlide = (s16) (campaignWork.iconSlide - 0x14);
            if (campaignWork.iconSlide <= 0) {
                campaignWork.iconSlide = 0;
            }
        }
        temp_v1 = campaignWork.unk006A;
        if ((temp_v1 != 0) && (campaignWork.unk006E != 0) && (campaignWork.unk53C1 == 0)) {
            if (campaignWork.opponentFaceState == 0) {
                campaignWork.opponentFaceState = 1;
                campaignWork.unk5406 = 0;
            }
            campaignWork.windowOpen = (s16) (campaignWork.windowOpen + 0x14);
            campaignWork.unk53C1 = 0;
            if (campaignWork.windowOpen >= 0x100) {
                campaignWork.windowOpen = 0x100;
            }
        } else if (((s8) temp_v1 == 0) || (campaignWork.unk006E == 0) || (campaignWork.unk53C1 == 1)) {
            campaignWork.windowOpen = (s16) (campaignWork.windowOpen - 0x14);
            if (campaignWork.windowOpen <= 0) {
                campaignWork.windowOpen = 0;
                campaignWork.unk53AB = 0;
                campaignWork.unk53C1 = 0;
                campaignWork.duelMenuChoice = (*(s8 *)(ctx + 0xC9));
                if (campaignWork.opponentFaceState != 0) {
                    ShFace_Close((u8 *)&campaignWork.opponentFace);
                    campaignWork.opponentFaceState = 0;
                }
            }
        }
    } else {
        campaignWork.unk5374 = 1;
        campaignWork.unk006E = 0;
        campaignWork.unk006A = 0;
        if (campaignWork.unk006E == 0) {
            campaignWork.iconSlide = (s16) (campaignWork.iconSlide - 0x14);
            if (campaignWork.iconSlide <= 0) {
                campaignWork.iconSlide = 0;
            }
        }
        if ((campaignWork.unk006A == 0) || (campaignWork.unk006E == 0)) {
            campaignWork.windowOpen = (s16) (campaignWork.windowOpen - 0x14);
            if (campaignWork.windowOpen <= 0) {
                campaignWork.windowOpen = 0;
                campaignWork.unk53AB = 0;
                if (campaignWork.opponentFaceState != 0) {
                    ShFace_Close((u8 *)&campaignWork.opponentFace);
                    campaignWork.opponentFaceState = 0;
                }
            }
        }
    }
    for (j = 0; j <= 0x15; j++) {
        if (base->placeReached[j] != 0) {
            base->placesReached = (s8) (base->placesReached + 1);
        }
    }
    if (campaignWork.routesIdle != 0) {
        if ((campaignWork.placesReached == 0) && (SzEffect_IsUse2(-1, -1) == 0) && (campaignWork.unk5374 == 0) && (campaignWork.unk5375 == 0) && ((*(s16 *)(ctx + 0xC2)) < 0xC8)) {
            for (i = 0; i < 4; i++) {
                var_a3 = &campaignSystemIcons[i * 0x13];
                temp_a1 = base->cursorX;
                if (((M2C_FIELD(var_a3, s16 *, 0) - 2) <= temp_a1) && (temp_a1 <= (M2C_FIELD(var_a3, s16 *, 4) + 2))) {
                    temp_a1_2 = base->cursorY;
                    if (((M2C_FIELD(var_a3, s16 *, 2) - 2) <= temp_a1_2) && (temp_a1_2 <= (M2C_FIELD(var_a3, s16 *, 6) + 2)) && (base->unk0004 != 1)) {
                        base->cursorOnIcon = 1;
                    }
                }
            }
            if ((campaignWork.cursorOnIcon != 0) && (campaignWork.unk543E == 0)) {
                switch (campaignWork.iconUnderCursor) {
                case 0:
                    if (SzPad_Check(0, 0, 0x40) != 0) {
                        SzSound_PlaySE(0, 4);
                        SzGame_SetMenuNum(6, 0);
                        SzGame_Push(6, 0);
                        goto end_TkCamp_Act;
                    }
                    break;
                case 1:
                    switch (campaignWork.helpOpen) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 4);
                            SzGame_InitMemCardProc(1);
                            campaignWork.helpOpen = 1;
                            goto end_TkCamp_Act;
                        }
                        break;
                    default:
                        if (0 > SzGame_ActMemCardProc()) {
                            campaignWork.helpOpen = 0;
                        }
                        goto end_TkCamp_Act;
                    }
                    break;
                case 2:
                    switch (campaignWork.helpOpen) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 4);
                            SzDuel_OpenOptionPopup_b((s32) (*(s8 *)(ctx + 0)), 0, 0x200);
                            campaignWork.helpOpen = 1;
                            campaignWork.helpStep = 0;
                            goto end_TkCamp_Act;
                        }
                        break;
                    case 1:
                        campaignWork.helpStep = (s8) (campaignWork.helpStep + 1);
                        if (campaignWork.helpStep >= 8) {
                            campaignWork.helpStep = 8;
                            campaignWork.helpOpen = 2;
                        }
                        SzDuel_OpenOptionPopup_b(-1, 0, 0x200 - ((s32) (campaignWork.helpStep << 9) >> 3));
                        goto end_TkCamp_Act;
                    case 2:
                        if (SzDuel_ActOptionPopup(0) != 0) {
                            campaignWork.helpOpen = 3;
                        }
                        goto end_TkCamp_Act;
                    case 3:
                        campaignWork.helpStep = (s8) (campaignWork.helpStep - 1);
                        if (campaignWork.helpStep <= 0) {
                            campaignWork.helpStep = 8;
                            campaignWork.helpOpen = 4;
                        }
                        SzDuel_OpenOptionPopup_b(-1, 0, 0x200 - ((s32) (campaignWork.helpStep << 9) >> 3));
                        if (campaignWork.helpOpen == 4) {
                            campaignWork.helpOpen = 0;
                            SzDuel_CloseOptionPopup();
                        }
                        goto end_TkCamp_Act;
                    }
                    break;
                case 3:
                    switch (campaignWork.helpOpen) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 4);
                            campaignWork.helpOpen = 1;
                            campaignWork.helpStep = 0;
                            campaignWork.helpPick = 0;
                            goto end_TkCamp_Act;
                        }
                        break;
                    case 1:
                        campaignWork.helpStep = (s8) (campaignWork.helpStep + 1);
                        if (campaignWork.helpStep >= 8) {
                            campaignWork.helpStep = 8;
                            campaignWork.helpOpen = 2;
                        }
                        goto end_TkCamp_Act;
                    case 2:
                        if (SzPad_Check(0, 0, 0x20) != 0) {
                            SzSound_PlaySE(0, 5);
                            campaignWork.helpOpen = 0xA;
                        } else if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 1);
                            campaignWork.helpOpen = 3;
                        }
                        if (campaignWork.helpOpen == 3) {
                            Taku_Camp_Go_Help();
                        }
                        if (campaignWork.helpOpen < 3) {
                            if (SzPad_Check(0, 2, 0x1000) != 0) {
                                SzSound_PlaySE(0, 3);
                                campaignWork.helpPick = (s8) (campaignWork.helpPick - 1);
                                if (campaignWork.helpPick < 0) {
                                    campaignWork.helpPick = 4;
                                }
                            }
                            if (SzPad_Check(0, 2, 0x4000) != 0) {
                                SzSound_PlaySE(0, 3);
                                campaignWork.helpPick = (s8) (campaignWork.helpPick + 1);
                                if (campaignWork.helpPick > 4) {
                                    campaignWork.helpPick = 0;
                                }
                            }
                        }
                        goto end_TkCamp_Act;
                    case 10:
                        campaignWork.helpStep = (s8) (campaignWork.helpStep - 1);
                        if (campaignWork.helpStep <= 0) {
                            campaignWork.helpStep = 0;
                            campaignWork.helpOpen = 0;
                        }
                        goto end_TkCamp_Act;
                    }
                    break;
                }
            }
            {
                if (campaignWork.helpOpen == 0) {
                    switch (campaignWork.unk543E) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x100) != 0) {
                            SzSound_PlaySE(0, 4);
                            SzDuel_OpenMsgPopup(7, 0, 0x200, 0x91);
                            campaignWork.unk543E = 1;
                            goto end_TkCamp_Act;
                        }
                        break;
                    case 1:
                        campaignWork.unk543F = (s8) (campaignWork.unk543F + 1);
                        if (campaignWork.unk543F >= 8) {
                            campaignWork.unk543F = 8;
                            campaignWork.unk543E = 2;
                        }
                        SzDuel_OpenMsgPopup(7, 0, 0x200 - ((s32) (campaignWork.unk543F << 9) >> 3), -1);
                        goto end_TkCamp_Act;
                    case 2:
                        actMsgPopup = SzDuel_ActMsgPopup(0);
                        switch (actMsgPopup) {
                        case 1:
                            campaignWork.unk543E = 3;
                            break;
                        case 2:
                            campaignWork.unk543E = 4;
                            break;
                        }
                        return;
                    case 3:
                        SzGame_Pop();
                        goto end_TkCamp_Act;
                    case 4:
                        campaignWork.unk543F = (s8) (campaignWork.unk543F - 1);
                        temp_v0_3 = campaignWork.unk543F;
                        if (temp_v0_3 <= 0) {
                            campaignWork.unk543F = 0;
                            campaignWork.unk543E = 0;
                            SzDuel_CloseMsgPopup();
                        } else {
                            SzDuel_OpenMsgPopup(7, 0, 0x200 - ((s32) (temp_v0_3 << 9) >> 3), -1);
                        }
                        goto end_TkCamp_Act;
                    }
                }
                {
                    if (campaignWork.unk543E == 0) {
                        SzPad_Check(0, 1, 0x800);
                        if (SzPad_Check(0, 0, 0x800) != 0) {
                            SzSound_PlaySE(0, 4);
                            temp_v1_4 = campaignWork.unk0072;
                            if (temp_v1_4 == 0) {
                                campaignWork.unk0072 = 1;
                                campaignWork.unk007A = 0;
                                campaignWork.unk007C = 0;
                            } else if (temp_v1_4 == 1) {
                                campaignWork.unk0072 = 2;
                            }
                        }
                    }
                    if (SzPad_IsAnalog(0) != 0) {
                        ax = SzPad_GetAnalogInfo(0, 2) & 0xFF;
                        ay = SzPad_GetAnalogInfo(0, 3) & 0xFF;
                        dx = ax - 0x80;
                        if (abs_b(dx) > 0x30) {
                            sgn = (0 <= dx) ? 1 : -1;
                            campaignWork.cameraTarget[0] = campaignWork.cameraTarget[0] + ((4.0f * (f32) (dx - (sgn * 0x30))) / 79.0f);
                        }
                        ax = ay - 0x80;
                        if (abs_b(ax) > 0x30) {
                            sgn = (0 <= ax) ? 1 : -1;
                            campaignWork.cameraTarget[2] = campaignWork.cameraTarget[2] + ((4.0f * (f32) (ax - (sgn * 0x30))) / 79.0f);
                        }
                    }
                    SzPad_Check(0, 1, 0x100);
                    SzPad_Check(0, 2, 0x100);
                    if (campaignWork.unk0004 == 1) {
                        vp[0] = (f32) (campaignWork.cursorX - 0x140);
                        vp[1] = (f32) (campaignWork.cursorY - 0xE0);
                        vp[2] = 1.0f;
                        vp[3] = 1.0f;
                        vq[0] = (f32) (campaignWork.cursorX - 0x140);
                        vq[1] = (f32) (campaignWork.cursorY - 0xE0);
                        vq[2] = 100.0f;
                        vq[3] = 1.0f;
                        Ex3d_GetPointOnScreen(vp, vp[0], vp[1]);
                        *(TkVec4 *)vq = *(TkVec4 *)SzView_GetSP(0);
                        Ex3d_IntersectP((void *)&campaignWork.groundPlane[0], vp, vq, vr);
                    }
                    if (SzPad_Check(0, 1, 0x1000) != 0) {
                        if (campaignWork.unk0072 != 0) {
                            campaignWork.unk007C = 0;
                            if (SzPad_Check(0, 0, 0x1000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (campaignWork.unk0004 == 1) {
                            temp_v0_5 = campaignWork.cursorY;
                            if (0 < temp_v0_5) {
                                campaignWork.cursorY = (s16) (temp_v0_5 - 0x18);
                                if (campaignWork.cursorY <= 0) {
                                    campaignWork.cursorY = 0;
                                }
                            } else {
                                campaignWork.cursorY = 0;
                            }
                        } else {
                            temp_v0_6 = campaignWork.cursorY;
                            if (0 < temp_v0_6) {
                                campaignWork.cursorY = (s16) (temp_v0_6 - 0x10);
                                if (campaignWork.cursorY <= 0) {
                                    campaignWork.cursorY = 0;
                                }
                            } else {
                                campaignWork.cursorY = 0;
                                campaignWork.cameraTarget[2] = (f32) (campaignWork.cameraTarget[2] - 4.0f);
                            }
                        }
                    }
                    if (SzPad_Check(0, 1, 0x4000) != 0) {
                        if (campaignWork.unk0072 != 0) {
                            campaignWork.unk007C = 1;
                            if (SzPad_Check(0, 0, 0x4000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (campaignWork.unk0004 == 1) {
                            temp_v0_7 = campaignWork.cursorY;
                            if (temp_v0_7 < 0x1A0) {
                                campaignWork.cursorY = (s16) (temp_v0_7 + 0x18);
                                if (campaignWork.cursorY >= 0x1A0) {
                                    campaignWork.cursorY = 0x1A0;
                                }
                            } else {
                                campaignWork.cursorY = 0x1A0;
                            }
                        } else {
                            temp_v0_8 = campaignWork.cursorY;
                            if (temp_v0_8 < 0x1A0) {
                                campaignWork.cursorY = (s16) (temp_v0_8 + 0x10);
                                if (campaignWork.cursorY >= 0x1A0) {
                                    campaignWork.cursorY = 0x1A0;
                                }
                            } else {
                                campaignWork.cursorY = 0x1A0;
                                campaignWork.cameraTarget[2] += 4.0f;
                            }
                        }
                    }
                    if (SzPad_Check(0, 1, 0x8000) != 0) {
                        if (campaignWork.unk0072 != 0) {
                            campaignWork.unk007A = 0;
                            if (SzPad_Check(0, 0, 0x8000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (campaignWork.unk0004 == 1) {
                            temp_v0_9 = campaignWork.cursorX;
                            if (0 < temp_v0_9) {
                                campaignWork.cursorX = (s16) (temp_v0_9 - 0x18);
                                if (campaignWork.cursorX <= 0) {
                                    campaignWork.cursorX = 0;
                                }
                            } else {
                                campaignWork.cursorX = 0;
                            }
                        } else {
                            temp_v0_10 = campaignWork.cursorX;
                            if (0 < temp_v0_10) {
                                campaignWork.cursorX = (s16) (temp_v0_10 - 0x10);
                                if (campaignWork.cursorX <= 0) {
                                    campaignWork.cursorX = 0;
                                }
                            } else {
                                campaignWork.cursorX = 0;
                                campaignWork.cameraTarget[0] = (f32) (campaignWork.cameraTarget[0] - 4.0f);
                            }
                        }
                    }
                    if (SzPad_Check(0, 1, 0x2000) != 0) {
                        if (campaignWork.unk0072 != 0) {
                            campaignWork.unk007A = 1;
                            if (SzPad_Check(0, 0, 0x2000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (campaignWork.unk0004 == 1) {
                            temp_v0_11 = campaignWork.cursorX;
                            if (temp_v0_11 < 0x260) {
                                campaignWork.cursorX = (s16) (temp_v0_11 + 0x18);
                                if (campaignWork.cursorX >= 0x260) {
                                    campaignWork.cursorX = 0x260;
                                }
                            } else {
                                campaignWork.cursorX = 0x260;
                            }
                        } else {
                            temp_v0_12 = campaignWork.cursorX;
                            if (temp_v0_12 < 0x260) {
                                campaignWork.cursorX = (s16) (temp_v0_12 + 0x10);
                                if (campaignWork.cursorX >= 0x260) {
                                    campaignWork.cursorX = 0x260;
                                }
                            } else {
                                campaignWork.cursorX = 0x260;
                                campaignWork.cameraTarget[0] += 4.0f;
                            }
                        }
                    }
                    if (campaignWork.unk0004 == 1) {
                        vp[0] = (f32) (campaignWork.cursorX - 0x140);
                        vp[1] = (f32) (campaignWork.cursorY - 0xE0);
                        vp[2] = 1.0f;
                        vp[3] = 1.0f;
                        vq[0] = (f32) (campaignWork.cursorX - 0x140);
                        vq[1] = (f32) (campaignWork.cursorY - 0xE0);
                        vq[2] = 100.0f;
                        vq[3] = 1.0f;
                        hit = 0;
                        Ex3d_GetPointOnScreen(vp, vp[0], vp[1]);
                        *(TkVec4 *)vq = *(TkVec4 *)SzView_GetSP(0);
                        Ex3d_IntersectP((void *)&campaignWork.groundPlane[0], vp, vq, vs);
                        vs[0] -= vr[0];
                        vs[1] -= vr[1];
                        vs[2] -= vr[2];
                        campaignWork.cameraTarget[0] = (f32) (campaignWork.cameraTarget[0] - vs[0]);
                        campaignWork.cameraTarget[2] = (f32) (campaignWork.cameraTarget[2] - vs[2]);
                        if (campaignWork.cameraTarget[0] < -200.0f) {
                            hit++;
                            campaignWork.cursorX = temp_s1;
                        } else if (110.0f < campaignWork.cameraTarget[0]) {
                            hit++;
                            campaignWork.cursorX = temp_s1;
                        }
                        if (campaignWork.cameraTarget[2] < -220.0f) {
                            hit++;
                            campaignWork.cursorY = temp_s2;
                        } else if (210.0f < campaignWork.cameraTarget[2]) {
                            hit++;
                            campaignWork.cursorY = temp_s2;
                        }
                        if (hit) {
                            campaignWork.cameraTarget[0] = (f32) (campaignWork.cameraTarget[0] + vs[0]);
                            campaignWork.cameraTarget[2] = (f32) (campaignWork.cameraTarget[2] + vs[2]);
                            vp[0] = (f32) (campaignWork.cursorX - 0x140);
                            vp[1] = (f32) (campaignWork.cursorY - 0xE0);
                            vp[2] = 1.0f;
                            vp[3] = 1.0f;
                            vq[0] = (f32) (campaignWork.cursorX - 0x140);
                            vq[1] = (f32) (campaignWork.cursorY - 0xE0);
                            vq[2] = 100.0f;
                            vq[3] = 1.0f;
                            Ex3d_GetPointOnScreen(vp, vp[0], vp[1]);
                            *(TkVec4 *)vq = *(TkVec4 *)SzView_GetSP(0);
                            Ex3d_IntersectP((void *)&campaignWork.groundPlane[0], vp, vq, vs);
                            vs[0] -= vr[0];
                            vs[1] -= vr[1];
                            vs[2] -= vr[2];
                            campaignWork.cameraTarget[0] = (f32) (campaignWork.cameraTarget[0] - vs[0]);
                            campaignWork.cameraTarget[2] = (f32) (campaignWork.cameraTarget[2] - vs[2]);
                        }
                    }
                    if (campaignWork.cameraTarget[0] < -200.0f) {
                        campaignWork.cameraTarget[0] = -200.0f;
                    } else if (110.0f < campaignWork.cameraTarget[0]) {
                        campaignWork.cameraTarget[0] = 110.0f;
                    }
                    if (campaignWork.cameraTarget[2] < -220.0f) {
                        campaignWork.cameraTarget[2] = -220.0f;
                    } else if (210.0f < campaignWork.cameraTarget[2]) {
                        campaignWork.cameraTarget[2] = 210.0f;
                    }
                    SzPad_Check(0, 1, 0x10);
                    temp_a1_4 = ((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3];
                    if ((temp_a1_4 != 0) && (campaignWork.windowOpen == 0x100)) {
                        {
                            ok = 0;
                            if (campaignWork.unk018C != 0) {
                                switch ((*(s8 *)(ctx + 0xC6))) {
                                case 1:
                                case 0xF:
                                case 0x11:
                                    ok = 0;
                                    break;
                                default:
                                    ok = 1;
                                    break;
                                }
                            } else if ((*(s8 *)(ctx + 0)) == 0) {
                                switch ((*(s8 *)(ctx + 0xC6))) {
                                case 1:
                                case 0xF:
                                case 0x11:
                                    ok = 0;
                                    break;
                                default:
                                    if ((s8) temp_a1_4 > 1) {
                                        ok = 1;
                                        if (((*(s8 *)(ctx + 0xC6)) == 0xB) && ((*(s8 *)(ctx + 0xE)) == 3) && (campaignWork.duelMenuChoice == 1)) {
                                            ok = 0;
                                        }
                                    }
                                    break;
                                }
                            } else if ((*(s8 *)(ctx + 0)) == 1) {
                                switch ((*(s8 *)(ctx + 0xC6))) {
                                case 1:
                                case 0xF:
                                case 0x11:
                                    ok = 0;
                                    break;
                                default:
                                    if ((s8) temp_a1_4 > 1) {
                                        ok = 1;
                                    }
                                    break;
                                }
                            }
                            if (ok) {
                                if ((SzPad_Check(0, 0, 0x10) != 0) && (campaignWork.unk0004 == 2) && (campaignWork.unk0072 == 0)) {
                                    SzSound_PlaySE(0, 4);
                                    campaignWork.terrainWindowOn = (s8) (campaignWork.terrainWindowOn ^ 1);
                                } else if (campaignWork.unk0004 != 2) {
                                    campaignWork.terrainWindowOn = 0;
                                }
                            } else {
                                campaignWork.terrainWindowOn = 0;
                            }
                        }
                    } else {
                        campaignWork.terrainWindowOn = 0;
                    }
                    if (SzPad_Check(0, 0, 0x20) != 0) {
                        if (campaignWork.unk0072 == 1) {
                            SzSound_PlaySE(0, 5);
                            campaignWork.unk0072 = 2;
                        }
                    }
                    if (SzPad_Check(0, 1, 0x80) != 0) {
                        if (campaignWork.unk0072 == 0) {
                            if (SzPad_Check(0, 0, 0x80) != 0) {
                                SzSound_PlaySE(0, 4);
                            }
                            campaignWork.unk0004 = 1U;
                        } else {
                            goto block_306;
                        }
                    } else {
block_306:
                        if (campaignWork.unk0004 == 1) {
                            campaignWork.unk0004 = 0U;
                        }
                    }
                    SzPad_Check(0, 2, 0x80);
                    SzPad_Check(0, 1, 0x20);
                    SzPad_Check(0, 0, 0x20);
                    SzPad_Check(0, 1, 4);
                    SzPad_Check(0, 2, 4);
                    SzPad_Check(0, 1, 1);
                    SzPad_Check(0, 2, 1);
                    SzPad_Check(0, 1, 0x200);
                    SzPad_Check(0, 1, 8);
                    SzPad_Check(0, 1, 2);
                    SzPad_Check(0, 1, 0x400);
                    if ((*(s8 *)(ctx + 0)) == 0) {
                        if ((*(s8 *)(ctx + 0xE)) < 3) {
                            goto block_312;
                        }
                        goto block_314;
                    }
block_312:
                    if (campaignWork.unk018C != 0) {
block_314:
                        if ((campaignWork.cursorOnIcon == 0) && (campaignWork.unk0004 == 2) && ((*(s8 *)(ctx + 0xC6)) == 0xB) && (campaignWork.unk53C1 == 0)) {
                            if (SzPad_Check(0, 0, 4) != 0) {
                                SzSound_PlaySE(0, 2);
                                (*(s8 *)(ctx + 0xC9)) = (s8) ((*(s8 *)(ctx + 0xC9)) - 1);
                                campaignWork.unk53C1 = 1;
                                if (campaignWork.unk018C != 0) {
                                    if ((*(s8 *)(ctx + 0xC9)) < 0) {
                                        (*(s8 *)(ctx + 0xC9)) = 2;
                                    }
                                } else if ((*(s8 *)(ctx + 0xC9)) < 0) {
                                    (*(s8 *)(ctx + 0xC9)) = 1;
                                }
                            } else if (SzPad_Check(0, 0, 8) != 0) {
                                SzSound_PlaySE(0, 2);
                                (*(s8 *)(ctx + 0xC9)) = (s8) ((*(s8 *)(ctx + 0xC9)) + 1);
                                campaignWork.unk53C1 = 1;
                                if (campaignWork.unk018C != 0) {
                                    (*(s8 *)(ctx + 0xC9)) = (s8) ((s8) (*(s8 *)(ctx + 0xC9)) % 3);
                                } else {
                                    (*(s8 *)(ctx + 0xC9)) = (s8) ((s8) (*(s8 *)(ctx + 0xC9)) % 2);
                                }
                            }
                        }
                    } else if (((*(s8 *)(ctx + 0)) == 0) && ((*(s8 *)(ctx + 0xE)) < 3)) {
                        (*(s8 *)(ctx + 0xC9)) = 0;
                    }
                }
            }
        }
    }
        if (campaignWork.eventCutScene != (*(s16 *)(ctx + 0xC2))) {
            campaignWork.eventStep = 0;
            campaignWork.unk537A = 0;
        }
        campaignWork.eventCutScene = (s16) (*(s16 *)(ctx + 0xC2));
        switch ((*(s16 *)(ctx + 0xC2))) { /* switch 6; irregular */
        case 0x2738:                                /* switch 6 */
            if (campaignWork.eventWindowState == 2) {
                if (campaignWork.nameTableSlide == 0) {
                    if (SzPad_Check(0, 2, 0x1000) != 0) {
                        SzSound_PlaySE(0, 2);
                        campaignWork.nameRow = (s8) (campaignWork.nameRow - 1);
                        if (campaignWork.nameRow < 0) {
                            campaignWork.nameRow = 5;
                        }
                    }
                    if (SzPad_Check(0, 2, 0x4000) != 0) {
                        SzSound_PlaySE(0, 2);
                        campaignWork.nameRow = (s8) (campaignWork.nameRow + 1);
                        if (campaignWork.nameRow > 5) {
                            campaignWork.nameRow = 0;
                        }
                    }
                    if (SzPad_Check(0, 2, 0x8000) != 0) {
                        SzSound_PlaySE(0, 2);
                        campaignWork.nameColumn = (s8) (campaignWork.nameColumn - 1);
                        if (campaignWork.nameColumn < 0) {
                            campaignWork.nameColumn = 0xE;
                        }
                    }
                    if (SzPad_Check(0, 2, 0x2000) != 0) {
                        SzSound_PlaySE(0, 2);
                        campaignWork.nameColumn = (s8) (campaignWork.nameColumn + 1);
                        if (campaignWork.nameColumn > 0xE) {
                            campaignWork.nameColumn = 0;
                        }
                    }
                    if (SzPad_Check(0, 0, 0x20) != 0) {
                        SzSound_PlaySE(0, 5);
                        campaignWork.nameLength = (s8) (campaignWork.nameLength - 1);
                        campaignWork.nameCursor = campaignWork.nameLength - 1;
                        if (campaignWork.nameLength <= 0) {
                            campaignWork.nameLength = 0;
                            campaignWork.nameCursor = 0;
                        }
                        (campaignWork.nameLetterTable)[campaignWork.nameLength] = 0;
                        (campaignWork.nameLetterColumn)[campaignWork.nameLength] = 6;
                        (campaignWork.nameLetterRow)[campaignWork.nameLength] = 1;
                    }
                    if (campaignWork.nameTyping == 0) {
                        if ((campaignWork.nameLength < 0xC) && (SzPad_Check(0, 0, 0xC0) != 0)) {
                            SzSound_PlaySE(0, 4);
                            campaignWork.nameTyping = 1;
                            campaignWork.namePickedColumn = campaignWork.nameColumn;
                            campaignWork.namePickedRow = campaignWork.nameRow;
                        }
                    }
                    if ((campaignWork.nameTyping == 0) && (campaignWork.nameLength != 0) && (SzPad_Check(0, 0, 0x800) != 0)) {
                        SzSound_PlaySE(0, 1);
                        campaignWork.eventWindowState = 3;
                        Taku_Camp_Event_Name_Set();
                    }
                }
            }
            temp_v1_5 = campaignWork.nameTableTurn;
            if (temp_v1_5 == 1) {
                temp_v0_15 = campaignWork.nameTableSlide;
                if (temp_v0_15 < 0x64) {
                    campaignWork.nameTableSlide = (s8) (temp_v0_15 + 0xA);
                }
                if (campaignWork.nameTableSlide >= 0x64) {
                    campaignWork.nameTableSlide = 0;
                    campaignWork.nameTableTurn = 0;
                    campaignWork.nameTable = (s8) (campaignWork.nameTable - 1);
                    if (campaignWork.nameTable < 0) {
                        campaignWork.nameTable = 2;
                    }
                }
            } else if (temp_v1_5 == 2) {
                temp_v0_16 = campaignWork.nameTableSlide;
                if (temp_v0_16 > -0x64) {
                    campaignWork.nameTableSlide = (s8) (temp_v0_16 - 0xA);
                }
                if (campaignWork.nameTableSlide < -0x63) {
                    campaignWork.nameTableSlide = 0;
                    campaignWork.nameTableTurn = 0;
                    campaignWork.nameTable = (s8) (campaignWork.nameTable + 1);
                    if (campaignWork.nameTable > 2) {
                        campaignWork.nameTable = 0;
                    }
                }
            }
            if (campaignWork.nameTyping == 1) {
                temp_v0_17 = campaignWork.nameTypingT;
                if (temp_v0_17 < 0x64) {
                    campaignWork.nameTypingT = (s8) (temp_v0_17 + 0x14);
                }
                if (campaignWork.nameTypingT >= 0x64) {
                    temp_v1_6 = campaignWork.nameLength;
                    (campaignWork.nameLetterTable)[temp_v1_6] = (s8) campaignWork.nameTable;
                    (campaignWork.nameLetterColumn)[temp_v1_6] = (s8) campaignWork.namePickedColumn;
                    (campaignWork.nameLetterRow)[temp_v1_6] = (s8) campaignWork.namePickedRow;
                    campaignWork.nameTypingT = 0;
                    campaignWork.nameTyping = 0;
                    campaignWork.nameCursor = (s8) campaignWork.nameLength;
                    campaignWork.nameLength = (s8) (campaignWork.nameLength + 1);
                    if (campaignWork.nameLength >= 0xC) {
                        campaignWork.nameLength = 0xC;
                        campaignWork.nameCursor = 0xB;
                    }
                }
            }
            break;
        case 0x2742:                                /* switch 6 */
        case 0x276A:                                /* switch 6 */
            if (campaignWork.eventWindowState == 2) {
                var_s1 = 1;
                if ((*(s16 *)(ctx + 0xC2)) == 0x276A) {
                    if ((*(s8 *)(ctx + 1)) != 0) {
                        var_s1 = 0;
                    }
                    if ((*(s8 *)(ctx + 2)) != 0) {
                        var_s1 = 0;
                    }
                }
                if (SzPad_Check(0, 0, 0x1000) != 0) {
                    if (var_s1 != 0) {
                        SzSound_PlaySE(0, 3);
                        campaignWork.eventWindowChoice = 0;
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                }
                if (SzPad_Check(0, 0, 0x4000) != 0) {
                    if (var_s1 != 0) {
                        SzSound_PlaySE(0, 3);
                        campaignWork.eventWindowChoice = 1;
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                }
                if ((SzPad_Check(0, 1, 0x1000) == 0) && (SzPad_Check(0, 1, 0x4000) == 0) && (SzPad_Check(0, 0, 0x800) != 0)) {
                    campaignWork.eventWindowState = 3;
                    SzSound_PlaySE(0, 1);
                    if (((*(s16 *)(ctx + 0xC2)) == 0x2742) && (campaignWork.eventWindowChoice == 0)) {
                        Taku_Camp_Go_Practice_Duel(0);
                    }
                }
            }
            break;
        case 0x2756:                                /* switch 6 */
            if ((campaignWork.eventWindowState == 2) && (campaignWork.deckShowPhase == 1)) {
                if (campaignWork.deckChoiceTurn == 0) {
                    if (SzPad_Check(0, 0, 0x2000) != 0) {
                        SzSound_PlaySE(0, 9);
                        campaignWork.deckChoiceTurn = 1;
                    }
                    if (SzPad_Check(0, 0, 0x8000) != 0) {
                        SzSound_PlaySE(0, 9);
                        campaignWork.deckChoiceTurn = 2;
                    }
                }
                temp_v0_18 = campaignWork.deckChoiceTurn;
                if (temp_v0_18 != 0) {
                    switch ((s8) temp_v0_18) {
                    case 1:                         /* switch 8 */
                        campaignWork.deckChoiceSlide = (s8) (campaignWork.deckChoiceSlide + 0x14);
                        if (campaignWork.deckChoiceSlide >= 0x64) {
                            campaignWork.deckChoiceSlide = 0;
                            campaignWork.deckChoiceTurn = 0;
                            campaignWork.eventWindowChoice = (s8) (campaignWork.eventWindowChoice + 1);
                            if (campaignWork.eventWindowChoice > 2) {
                                campaignWork.eventWindowChoice = 0;
                            }
                        }
                        break;
                    case 2:                         /* switch 8 */
                        campaignWork.deckChoiceSlide = (s8) (campaignWork.deckChoiceSlide + 0x14);
                        if (campaignWork.deckChoiceSlide >= 0x64) {
                            campaignWork.deckChoiceSlide = 0;
                            campaignWork.deckChoiceTurn = 0;
                            campaignWork.eventWindowChoice = (s8) (campaignWork.eventWindowChoice - 1);
                            if (campaignWork.eventWindowChoice < 0) {
                                campaignWork.eventWindowChoice = 2;
                            }
                        }
                        break;
                    }
                }
                if ((SzPad_Check(0, 0, 0x800) != 0) && (campaignWork.deckChoiceTurn == 0)) {
                    SzSound_PlaySE(0, 1);
                    campaignWork.eventWindowState = 3;
                    campaignWork.deckShowPhase = 2;
                }
            }
            /* fallthrough */
        case 0x2757:                                /* switch 6 */
            /* fallthrough */
        case 0x2760:                                /* switch 6 */
            if (campaignWork.deckShowPhase == 4) {
                SzData_SetupFromConstDeck(0, (s32) (campaignWork.deckChoices)[campaignWork.eventWindowChoice]);
                if (SzModel_IsModelLoading(0x1E) == 0) {
                    spE0 = D_0029B000;
                    spF0 = D_0029B010;
                    currentDeck = SzData_GetCurrentDeck(0);
                    leader = SzData_GetLeader(0, currentDeck);
                    campaignWork.leaderCard = SzData_GetLeader(0, currentDeck);
                    SzModel_SetPos(0x1E, &spE0);
                    SzModel_SetRot(0x1E, &spF0);
                    SzModel_Load(0x1E, -1, SzDuel_New2Xax(leader), 1);
                }
                campaignWork.deckShowPhase = 5;
            }
            break;
        }
        if (campaignWork.unk007A != 0) {
            if (campaignWork.unk007C != 0) {
                spot = 3;
            } else {
                spot = 1;
            }
        } else {
            spot = 0;
            if (campaignWork.unk007C != 0) {
                spot = 2;
            }
        }
        temp_v1_7 = campaignWork.unk0072;
        if (temp_v1_7 == 1) {
            if (campaignWork.cursorMoveT == 0) {
                campaignWork.cursorFromX = campaignWork.cursorX;
                campaignWork.cursorFromY = campaignWork.cursorY;
            }
            campaignWork.cursorMoveT = (s16) (campaignWork.cursorMoveT + 0x20);
            if (campaignWork.cursorMoveT >= 0x100) {
                campaignWork.cursorMoveT = 0x100;
            }
            campaignWork.cursorX = campaignWork.cursorFromX + ((campaignWork.cursorMoveT * ((campaignSystemIcons[spot * 0x13] + 0x10) - campaignWork.cursorFromX)) >> 8);
            campaignWork.cursorY = campaignWork.cursorFromY + ((campaignWork.cursorMoveT * ((campaignSystemIcons[spot * 0x13 + 1] + 0x10) - campaignWork.cursorFromY)) >> 8);
        } else if (temp_v1_7 == 2) {
            campaignWork.cursorMoveT = (s16) (campaignWork.cursorMoveT - 0x20);
            if (campaignWork.cursorMoveT <= 0) {
                campaignWork.cursorMoveT = 0;
                campaignWork.unk0072 = 0;
                campaignWork.unk007A = 0;
                campaignWork.unk007C = 0;
            }
            campaignWork.cursorX = campaignWork.cursorFromX + ((campaignWork.cursorMoveT * ((campaignSystemIcons[spot * 0x13] + 0x10) - campaignWork.cursorFromX)) >> 8);
            campaignWork.cursorY = campaignWork.cursorFromY + ((campaignWork.cursorMoveT * ((campaignSystemIcons[spot * 0x13 + 1] + 0x10) - campaignWork.cursorFromY)) >> 8);
        }
        Taku_Camp_System();
        if (campaignWork.talkStep == 1) {
            Taku_Camp_TEXT_PICK();
        }
        if ((*(s8 *)(ctx + 0)) == 1) {
            if (((*(s16 *)(ctx + 0xC2)) == 0x68) || ((*(s16 *)(ctx + 0xC2)) == 0x69)) {
                var_s3 = 1;
            }
        }
        if (((*(s8 *)(ctx + 0)) == 1) && ((*(s16 *)(ctx + 0xC2)) == 0x6F)) {
            if (campaignWork.talkStep == 1) {
                Taku_Camp_TEXT_PICK();
            }
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
            }
            if (campaignWork.talkStep == 4) {
                if (SzPad_Check(0, 0, 0x40) != 0) {
                    SzSound_PlaySE(0, 2);
                    campaignWork.talkStep = (s8) (campaignWork.talkStep + 1);
                    Taku_Camp_TEXT_PICK();
                }
            }
        } else if (((*(s16 *)(ctx + 0xC2)) >= 0x2711) || (var_s3 != 0)) {
            if (SzPad_Check(0, 0, 0x40) != 0) {
                if (campaignWork.talkStep == 4) {
                    campaignWork.talkStep = 5;
                    campaignWork.unk53B2 = 0;
                    SzSound_PlaySE(0, 2);
                }
                if (campaignWork.eventPictureState == 2) {
                    campaignWork.eventPictureState = 3;
                    campaignWork.unk53B2 = 0;
                    SzSound_PlaySE(0, 2);
                }
                Taku_Camp_TEXT_PICK();
            }
        } else if (campaignWork.unk0004 == 2) {
            var_a0_4 = 0;
            if (campaignWork.cursorOnIcon == 0) {
                if ((*(s8 *)(ctx + 0)) != 0) {
                    if ((*(s8 *)(ctx + 0xC6)) == 0xF) {
                        var_a0_4 = 1;
                    }
                }
                if ((campaignWork.playerDeckCost <= campaignWork.opponentDeckCost) || (campaignWork.talkStep != 0) || (var_a0_4 != 0)) {
                    var_s1_2 = 0;
                    if (campaignWork.talkStep == 0xC) {
                        if (campaignWork.unk53A0 <= 0) {
                            if (campaignWork.unk018C == 0) {
                                temp_v0_20 = campaignWork.unk5440;
                                if (!(0 > temp_v0_20)) {
                                    campaignWork.unk5440 = (s8) (temp_v0_20 - 0xA);
                                    if (campaignWork.unk5440 <= 0) {
                                        campaignWork.unk5440 = 0;
                                    }
                                }
                            }
                        }
                    }
                    if ((campaignWork.routesIdle != 0) && (campaignWork.placesReached == 0) && (SzEffect_IsUse2(-1, -1) == 0) && (campaignWork.unk5374 == 0) && (campaignWork.unk5375 == 0) && ((*(s16 *)(ctx + 0xC2)) < 0xC8)) {
                        var_s1_2 = 1;
                    }
                    if ((((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3] != 0) && (campaignWork.windowOpen == 0x100)) {
                        if ((*(s8 *)(ctx + 0)) == 0) {
                            switch ((*(s8 *)(ctx + 0xC6))) { /* switch 9; irregular */
                            case 15:
                            case 17:
                                func_00199B50(&D_0030F1F6, (*(s8 *)(ctx + 0xC6)));
                                break;
                            case 0:
                            case 1:
                                break;
                            default:                /* switch 9 */
                                if (SzPad_Check(0, 0, 0x40) != 0) {
                                    if ((campaignWork.unk546D == 0) && (campaignWork.talkStep == 0) && (var_s1_2 != 0)) {
                                        SzSound_PlaySE(0, 4);
                                        campaignWork.unk546D = 1;
                                        func_00199B50(&D_0030F213, (*(s8 *)(ctx + 0xC6)));
                                    }
                                    if (((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3] == 1) {
                                        if (campaignWork.talkStep == 0) {
                                            campaignWork.talkStep = 1;
                                            campaignWork.unk53A0 = 0;
                                            campaignWork.unk5375 = 1;
                                            if (campaignWork.leaderShow == 0) {
                                                if (var_s1_2 != 0) {
                                                    campaignWork.leaderShow = 1;
                                                }
                                            }
                                            campaignWork.talkPage = 1;
                                        }
                                        temp_v1_8 = campaignWork.talkStep;
                                        if (temp_v1_8 == 4) {
                                            campaignWork.talkStep = (s8) (temp_v1_8 + 1);
                                            SzSound_PlaySE(0, 2);
                                        }
                                        Taku_Camp_TEXT_PICK();
                                    } else if ((*(s8 *)(ctx + 0xC6)) == 0xB) {
                                        if (((*(s8 *)(ctx + 0xE)) == 3) && (campaignWork.duelMenuChoice == 1)) {
                                            if (campaignWork.talkStep == 0) {
                                                campaignWork.talkStep = 1;
                                                campaignWork.unk53A0 = 0;
                                                campaignWork.unk5375 = 1;
                                                if (campaignWork.leaderShow == 0) {
                                                    if (var_s1_2 != 0) {
                                                        campaignWork.leaderShow = 1;
                                                    }
                                                }
                                                campaignWork.talkPage = 1;
                                            }
                                            temp_v1_9 = campaignWork.talkStep;
                                            if (temp_v1_9 == 4) {
                                                campaignWork.talkStep = (s8) (temp_v1_9 + 1);
                                                SzSound_PlaySE(0, 2);
                                            }
                                            Taku_Camp_TEXT_PICK();
                                        } else {
                                            goto block_544;
                                        }
                                    } else {
block_544:
                                        campaignWork.unk5375 = 1;
                                        if (campaignWork.leaderShow == 0) {
                                            if (var_s1_2 != 0) {
                                                campaignWork.leaderShow = 1;
                                            }
                                        }
                                        temp_v1_10 = campaignWork.talkStep;
                                        if (temp_v1_10 == 4) {
                                            campaignWork.talkStep = (s8) (temp_v1_10 + 1);
                                            SzSound_PlaySE(0, 2);
                                        }
                                    }
                                }
                                break;
                            }
                        } else {
                            switch ((*(s8 *)(ctx + 0xC6))) { /* switch 10; irregular */
                            case 1:
                                func_00199B50(&D_0030F227, (*(s8 *)(ctx + 0xC6)));
                                break;
                            case 15:
                                if (((*(s8 *)(ctx + 0x13)) == 0) && (SzPad_Check(0, 0, 0x40) != 0)) {
                                    if (campaignWork.unk546D == 0) {
                                        if ((campaignWork.talkStep == 0) && (var_s1_2 != 0)) {
                                            SzSound_PlaySE(0, 4);
                                            campaignWork.unk546D = 1;
                                        }
                                    }
                                    if (campaignWork.talkStep == 0) {
                                        campaignWork.unk53A0 = 0;
                                        campaignWork.unk5375 = 1;
                                        if ((campaignWork.leaderShow == 0) && (var_s1_2 != 0)) {
                                            campaignWork.leaderShow = 1;
                                        }
                                    }
                                }
                                break;
                            case 17:
                                break;
                            default:
                                if (SzPad_Check(0, 0, 0x40) != 0) {
                                    if ((campaignWork.unk546D == 0) && (campaignWork.talkStep == 0) && (var_s1_2 != 0)) {
                                        SzSound_PlaySE(0, 4);
                                        campaignWork.unk546D = 1;
                                        func_00199B50(&D_0030F244, (*(s8 *)(ctx + 0xC6)));
                                    }
                                    if (((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3] == 1) {
                                        if (campaignWork.talkStep == 0) {
                                            campaignWork.talkStep = 1;
                                            campaignWork.talkPage = 1;
                                            campaignWork.unk53A0 = 0;
                                            campaignWork.unk5375 = 1;
                                            if ((campaignWork.leaderShow == 0) && (var_s1_2 != 0)) {
                                                campaignWork.leaderShow = 1;
                                            }
                                        }
                                        temp_v1_11 = campaignWork.talkStep;
                                        if (temp_v1_11 == 4) {
                                            campaignWork.talkStep = (s8) (temp_v1_11 + 1);
                                            SzSound_PlaySE(0, 2);
                                        }
                                        Taku_Camp_TEXT_PICK();
                                    } else {
                                        campaignWork.unk5375 = 1;
                                        if (campaignWork.leaderShow == 0) {
                                            if (var_s1_2 != 0) {
                                                campaignWork.leaderShow = 1;
                                            }
                                        }
                                        temp_v1_12 = campaignWork.talkStep;
                                        if (temp_v1_12 == 4) {
                                            campaignWork.talkStep = (s8) (temp_v1_12 + 1);
                                            SzSound_PlaySE(0, 2);
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                } else {
                    temp_s1_3 = (*(s8 *)(ctx + 0));
                    var_s2 = 0;
                    if ((campaignWork.windowOpen == 0x100) && (campaignWork.routesIdle != 0) && (campaignWork.placesReached == 0) && (SzEffect_IsUse2(-1, -1) == 0) && (campaignWork.unk5374 == 0) && (campaignWork.unk5375 == 0) && ((*(s16 *)(ctx + 0xC2)) < 0xC8)) {
                        var_s2 = 1;
                    }
                    if (var_s2 != 0) {
                        if (temp_s1_3 == 0) {
                            switch ((*(s8 *)(ctx + 0xC6))) { /* switch 11; irregular */
                            case 0:
                            case 1:
                                break;
                            case 11:                /* switch 11 */
                                if (((*(s8 *)(ctx + 0xE)) != 0) && (SzPad_Check(0, 1, 0x40) != 0)) {
                                    if (SzPad_Check(0, 0, 0x40) != 0) {
                                        SzSound_PlaySE(0, 6);
                                    }
                                    campaignWork.unk5446 = 1;
                                }
                                break;
                            default:                /* switch 11 */
                                if (SzPad_Check(0, 1, 0x40) != 0) {
                                    if (SzPad_Check(0, 0, 0x40) != 0) {
                                        SzSound_PlaySE(0, 6);
                                    }
                                    campaignWork.unk5446 = 1;
                                }
                                break;
                            }
                        } else {
                            switch ((*(s8 *)(ctx + 0xC6))) { /* switch 12; irregular */
                            case 15:
                            case 17:
                                break;
                            case 11:                /* switch 12 */
                                if (((*(s8 *)(ctx + 0xE)) != 0) && (SzPad_Check(0, 1, 0x40) != 0)) {
                                    if (SzPad_Check(0, 0, 0x40) != 0) {
                                        SzSound_PlaySE(0, 6);
                                    }
                                    campaignWork.unk5446 = 1;
                                }
                                break;
                            default:                /* switch 12 */
                                if (SzPad_Check(0, 1, 0x40) != 0) {
                                    if (SzPad_Check(0, 0, 0x40) != 0) {
                                        SzSound_PlaySE(0, 6);
                                    }
                                    campaignWork.unk5446 = 1;
                                }
                                break;
                            }
                        }
                    }
                }
            } else {
                goto block_623;
            }
        } else {
block_623:
            campaignWork.unk5446 = 0;
        }
        temp_a1_7 = campaignWork.cameraMode;
        switch (temp_a1_7) {                        /* switch 13; irregular */
        case 1:                                     /* switch 13 */
            temp_v0_21 = campaignWork.zoomMove;
            if (temp_v0_21 == 1) {
                campaignWork.zoom = (s16) (campaignWork.zoom + 0x10);
                if (campaignWork.zoom > 0x1000) {
                    campaignWork.zoom = 0x1000;
                    campaignWork.zoomMove = 0;
                }
            } else if (temp_v0_21 == 2) {
                campaignWork.zoom = (s16) (campaignWork.zoom - 0x10);
                if (campaignWork.zoom < 0) {
                    campaignWork.zoom = 0;
                    campaignWork.zoomMove = 0;
                }
            }
            campaignWork.cameraTarget[0] = 0.0f;
            campaignWork.cameraTarget[2] = 0.0f;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.cameraEye[0] = (f32) campaignWork.cameraTarget[0];
            campaignWork.cameraEye[1] = (f32) (20.0f + campaignWork.cameraTarget[1] + ((1700.0f * (f32) campaignWork.zoom) / 4096.0f));
            campaignWork.cameraEye[2] = (f32) (1.0f + campaignWork.cameraTarget[2]);
            campaignWork.cameraEye[3] = campaignWork.cameraTarget[3];
            campaignWork.stoneSpin = (s16) (campaignWork.stoneSpin - 0x300);
            break;
        case 2:                                     /* switch 13 */
            temp_v1_13 = campaignWork.zoomMove;
            if (temp_v1_13 == 1) {
                campaignWork.zoom = (s16) (campaignWork.zoom + 0x100);
                if (campaignWork.zoom > 0x1000) {
                    campaignWork.zoom = 0x1000;
                    campaignWork.zoomMove = 0;
                }
            } else if (temp_v1_13 == 2) {
                campaignWork.zoom = (s16) (campaignWork.zoom - 0x100);
                if (campaignWork.zoom < 0) {
                    campaignWork.zoom = 0;
                    campaignWork.zoomMove = 0;
                }
            }
            if (campaignWork.unk547F != 0) {
                campaignWork.eventPictureMapX = 0.0f;
                campaignWork.eventPictureMapZ = 0.0f;
                temp_a1_8 = campaignWork.unk547F;
                switch (temp_a1_8) {                /* switch 16; irregular */
                case 1:                             /* switch 16 */
                    campaignWork.unk5480 = (s8) (campaignWork.unk5480 + 5);
                    if (campaignWork.unk5480 >= 0x64) {
                        campaignWork.unk5480 = 0x64;
                        campaignWork.unk547F = 2;
                    }
                    break;
                case 2:                             /* switch 16 */
                    campaignWork.unk5480 = 0x64;
                    if (campaignWork.unk546E == 5) {
                        campaignWork.unk547F = 3;
                    }
                    break;
                case 3:                             /* switch 16 */
                    campaignWork.unk5480 = (s8) (campaignWork.unk5480 - 5);
                    if (campaignWork.unk5480 <= 0) {
                        campaignWork.unk5480 = 0;
                        campaignWork.unk547F = 4;
                    }
                    break;
                case 4:                             /* switch 16 */
                    campaignWork.unk547E = 0;
                    break;
                }
                temp_hi = (s32) campaignWork.unk547E % 3;
                switch (temp_hi) {                  /* switch 17; irregular */
                case 0:                             /* switch 17 */
                    campaignWork.eventPictureMapX = 0.0f;
                    break;
                case 1:                             /* switch 17 */
                    var_f0 = (-2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapX = var_f0;
                    break;
                case 2:                             /* switch 17 */
                    var_f0 = (2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapX = var_f0;
                    break;
                }
                temp_hi_2 = (s32) campaignWork.unk547E % 5;
                switch (temp_hi_2) {                /* switch 18; irregular */
                case 0:                             /* switch 18 */
                    campaignWork.eventPictureMapZ = 0.0f;
                    break;
                case 1:                             /* switch 18 */
                    var_f0_2 = (-2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = var_f0_2;
                    break;
                case 2:                             /* switch 18 */
                    var_f0_2 = (2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = var_f0_2;
                    break;
                case 3:                             /* switch 18 */
                    var_f0_2 = (-1.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = var_f0_2;
                    break;
                case 4:                             /* switch 18 */
                    var_f0_2 = (f32) campaignWork.unk5480 / 100.0f;
                    campaignWork.eventPictureMapZ = var_f0_2;
                    break;
                }
                campaignWork.cameraEye[0] = (f32) campaignWork.eventPictureMapX;
                campaignWork.cameraEye[1] = (f32) campaignWork.eventPictureMapZ;
                campaignWork.cameraEye[2] = 512.0f;
                *(s32 *)&campaignWork.cameraEye[3] = 0;
                campaignWork.cameraTarget[0] = (f32) (((-64.0f * (f32) campaignWork.eventPictureZoom) / 100.0f) + campaignWork.eventPictureMapX);
                campaignWork.cameraTarget[1] = (f32) (20.2f + ((768.0f * (f32) campaignWork.zoom) / 4096.0f) + campaignWork.eventPictureMapZ);
                campaignWork.cameraTarget[2] = 0.0f;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
                campaignWork.unk547E = (u8) (campaignWork.unk547E + 1);
            } else {
                campaignWork.cameraEye[0] = 0.0f;
                campaignWork.cameraEye[1] = 0.0f;
                campaignWork.cameraEye[2] = 512.0f;
                *(s32 *)&campaignWork.cameraEye[3] = 0;
                campaignWork.cameraTarget[0] = (f32) ((-64.0f * (f32) campaignWork.eventPictureZoom) / 100.0f);
                campaignWork.cameraTarget[1] = (f32) (20.2f + ((768.0f * (f32) campaignWork.zoom) / 4096.0f));
                campaignWork.cameraTarget[2] = 0.0f;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
            }
            break;
        case 3:                                     /* switch 13 */
            temp_v1_14 = campaignWork.zoomMove;
            if (temp_v1_14 == 1) {
                campaignWork.zoom = (s16) (campaignWork.zoom + 0x80);
                if (campaignWork.zoom > 0x1000) {
                    campaignWork.zoom = 0x1000;
                    campaignWork.zoomMove = 0;
                }
            } else if (temp_v1_14 == 2) {
                campaignWork.zoom = (s16) (campaignWork.zoom - 0x80);
                if (campaignWork.zoom < 0) {
                    campaignWork.zoom = 0;
                    campaignWork.zoomMove = 0;
                }
            }
            temp_v0_22 = campaignWork.unk547F;
            if (temp_v0_22 != 0) {
                switch ((s8) temp_v0_22) {
                case 1:                             /* switch 20 */
                    campaignWork.unk5480 = (s8) (campaignWork.unk5480 + 5);
                    if (campaignWork.unk5480 >= 0x64) {
                        campaignWork.unk5480 = 0x64;
                        campaignWork.unk547F = 2;
                    }
                    break;
                case 2:                             /* switch 20 */
                    campaignWork.unk5480 = 0x64;
                    if (campaignWork.unk546E == 5) {
                        campaignWork.unk547F = 3;
                    }
                    break;
                case 3:                             /* switch 20 */
                    campaignWork.unk5480 = (s8) (campaignWork.unk5480 - 5);
                    if (campaignWork.unk5480 <= 0) {
                        campaignWork.unk5480 = 0;
                        campaignWork.unk547F = 4;
                    }
                    break;
                case 4:                             /* switch 20 */
                    campaignWork.unk547E = 0U;
                    break;
                }
                temp_hi_3 = (s32) campaignWork.unk547E % 3;
                switch (temp_hi_3) {                /* switch 21; irregular */
                case 0:                             /* switch 21 */
                    campaignWork.eventPictureMapX = 0.0f;
                    break;
                case 1:                             /* switch 21 */
                    var_f0_3 = (-2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapX = var_f0_3;
                    break;
                case 2:                             /* switch 21 */
                    var_f0_3 = (2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapX = var_f0_3;
                    break;
                }
                temp_hi_4 = (s32) campaignWork.unk547E % 5;
                switch (temp_hi_4) {                /* switch 22; irregular */
                case 0:                             /* switch 22 */
                    campaignWork.eventPictureMapZ = 0.0f;
                    break;
                case 1:                             /* switch 22 */
                    fq4 = (-2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = fq4;
                    break;
                case 2:                             /* switch 22 */
                    fq4 = (2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = fq4;
                    break;
                case 3:                             /* switch 22 */
                    fq4 = (-1.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = fq4;
                    break;
                case 4:                             /* switch 22 */
                    fq4 = (f32) campaignWork.unk5480 / 100.0f;
                    campaignWork.eventPictureMapZ = fq4;
                    break;
                }
                campaignWork.cameraEye[0] = (f32) campaignWork.eventPictureMapX;
                campaignWork.cameraEye[1] = (f32) campaignWork.eventPictureMapZ;
                campaignWork.cameraEye[2] = 512.0f;
                *(s32 *)&campaignWork.cameraEye[3] = 0;
                campaignWork.cameraTarget[0] = (f32) (((-64.0f * (f32) campaignWork.eventPictureZoom) / 100.0f) + campaignWork.eventPictureMapX);
                campaignWork.cameraTarget[1] = (f32) (20.2f + ((512.0f * (f32) campaignWork.zoom) / 4096.0f) + campaignWork.eventPictureMapZ);
                campaignWork.cameraTarget[2] = 0.0f;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
                campaignWork.unk547E = (u8) (campaignWork.unk547E + 1);
            } else {
                campaignWork.cameraEye[0] = 0.0f;
                campaignWork.cameraEye[1] = 0.0f;
                campaignWork.cameraEye[2] = 512.0f;
                *(s32 *)&campaignWork.cameraEye[3] = 0;
                campaignWork.cameraTarget[0] = (f32) ((-64.0f * (f32) campaignWork.eventPictureZoom) / 100.0f);
                campaignWork.cameraTarget[1] = (f32) (20.2f + ((512.0f * (f32) campaignWork.zoom) / 4096.0f));
                campaignWork.cameraTarget[2] = 0.0f;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
                campaignWork.unk547E = 0U;
            }
            break;
        default:                                    /* switch 13 */
            c23 = campaignWork.zoomMove;
            if (c23 == 1) {
                campaignWork.zoom = (s16) (campaignWork.zoom + 8);
                if (campaignWork.zoom > 0x100) {
                    campaignWork.zoom = 0x100;
                    campaignWork.zoomMove = 0;
                }
            } else if (c23 == 2) {
                campaignWork.zoom = (s16) (campaignWork.zoom - 8);
                if (campaignWork.zoom < 0) {
                    campaignWork.zoom = 0;
                    campaignWork.zoomMove = 0;
                }
            }
            campaignWork.cameraTarget[1] = 0.0f;
            campaignWork.cameraEye[0] = campaignWork.cameraTarget[0];
            campaignWork.cameraEye[1] = 96.0f + campaignWork.cameraTarget[1] + ((96.0f * (f32) campaignWork.zoom) / 256.0f);
            campaignWork.cameraEye[2] = 96.0f + campaignWork.cameraTarget[2];
            campaignWork.cameraEye[3] = campaignWork.cameraTarget[3];
            break;
        }
        SzView_SetCamera(0, (void *)&campaignWork.cameraEye[0], (void *)&campaignWork.cameraTarget[0]);
        TkCamp_Act2(0);
end_TkCamp_Act:;
}

typedef struct Vec3_0023B1F0 {
    f32 x;
    f32 y;
    f32 z;
} Vec3_0023B1F0;

typedef struct Vec4_0023B1F0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_0023B1F0;

typedef struct Item_0023B1F0 {
    Vec3_0023B1F0 pos;
    u8 pad0C[0x28];
} Item_0023B1F0;
#pragma opt_dead_assignments reset
#pragma conditional_move reset

/* Runs the campaign map's second half of a frame: its windows, events and the move to a duel. */
void TkCamp_Act2(s32 param) {
    extern u8 campaignCoord[];
    extern Item_0023B1F0 campaignPlaces_3[];
    extern s32 campaignAct2Lock;
    extern void Taku_3D_2D_Set();
    Vec4_0023B1F0 top;
    CampaignWork *work;
    s16 show;
    s8 *state;
    s16 result;
    s16 i;
    s32 sx;
    s16 *rect;
    s32 dx;
    s16 j;
    Item_0023B1F0 *item;
    Vec4_0023B1F0 side;
    s32 *spot;
    s32 sy;
    s32 radius;

    state = &campaignState;
    work = &campaignWork;
    result = 0;
    Taku_Coord_Set(campaignCoord);
    item = campaignPlaces_3;
    for (i = 0, spot = (s32 *)work; i <= 21; i++) { /* spot[0x23] is placeScreenX[i], spot[0x43] placeScreenY[i] */
        show = 0;
        top.x = item->pos.x;
        top.y = 8.65f + item->pos.y;
        top.z = item->pos.z;
        side.x = 5.0f + item->pos.x;
        side.y = 8.65f + item->pos.y;
        side.z = item->pos.z;
        if (param != 0) {
            show = 1;
        }
        if (work->unk018C != 0) {
            show = 1;
        } else if (state[0] == 0) {
            if (i == 0 || i == 11) {
                show = 1;
            } else if (i > 0 && i < 11 && state[i + 3] != 0) {
                show = 1;
            }
        } else {
            if (i == 0 || i == 11) {
                show = 1;
            } else if (i >= 12 && i < 22 && state[i + 3] != 0) {
                show = 1;
            }
        }
        if (show) {
            Taku_3D_2D_Set(&spot[0x23], &spot[0x43], &top);
            Taku_3D_2D_Set(&sx, &sy, &side);
            radius = sx - spot[0x23];
            if (campaignAct2Lock == 0) {
                if (work->leaderShow != 0) {
                    work->cursorX = *(s16 *)&work->placeScreenX[state[0xC6]];
                    work->cursorY = *(s16 *)&work->placeScreenY[state[0xC6]];
                }
                dx = work->cursorX - spot[0x23];
                if (func_001A6C60(func_001A6C48(dx, 2.0f) + func_001A6C48(work->cursorY - spot[0x43], 2.0f)) < radius) {
                    if (work->windowOpen == 0 || work->leaderShow != 0) {
                        if (i != state[0xC6]) {
                            state[0xC6] = i;
                        }
                    }
                    if (state[0xC6] == i) {
                        result = 1;
                    }
                    if (work->leaderShow != 0) {
                        work->cursorX = *(s16 *)&work->placeScreenX[state[0xC6]];
                        work->cursorY = *(s16 *)&work->placeScreenY[state[0xC6]];
                    }
                }
            } else {
                result = 1;
            }
        }
        item++;
        spot++;
    }
    rect = campaignSystemIcons;
    for (j = 0; j < 4; j++) {
        if (rect[0] - 2 <= work->cursorX && work->cursorX <= rect[2] + 2 &&
            rect[1] - 2 <= work->cursorY && work->cursorY <= rect[3] + 2) {
            work->iconUnderCursor = j;
            work->cursorOnIcon = 1;
            result = 2;
        }
        rect = (s16 *)((u8 *)rect + 0x26);
    }
    if (campaignWork.unk0004 != 1) {
        switch (result) {
        case 0:
            campaignWork.unk006A = 0;
            campaignWork.unk007E = 0;
            campaignWork.unk0004 = 0;
            break;
        case 1:
            if (state[0xC6] == 11) {
                switch (state[state[0xC6] + 3]) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    if (campaignWork.unk0072 == 0 || campaignWork.unk537A != 0) {
                        campaignWork.unk006A = 1;
                        campaignWork.unk007E = 0;
                        campaignWork.unk0004 = 0;
                        campaignWork.unk0004 = 2;
                    }
                    break;
                }
            } else {
                switch (state[state[0xC6] + 3]) {
                case 1:
                case 2:
                case 3:
                    if (campaignWork.unk0072 == 0 || campaignWork.unk537A != 0) {
                        campaignWork.unk006A = 1;
                        campaignWork.unk007E = 0;
                        campaignWork.unk0004 = 2;
                    }
                    break;
                }
            }
            break;
        case 2:
            campaignWork.unk007E = 1;
            campaignWork.unk006A = 0;
            campaignWork.unk0004 = 2;
            campaignWork.cursorOnIcon = 1;
            break;
        }
    } else {
        campaignWork.unk006A = 0;
        campaignWork.unk007E = 0;
    }
    if (campaignWork.cursorY < 0x78) {
        campaignWork.windowAlpha[0] -= 8;
        if (campaignWork.windowAlpha[0] <= 0x60) {
            campaignWork.windowAlpha[0] = 0x60;
        }
    } else {
        campaignWork.windowAlpha[0] += 8;
        if (campaignWork.windowAlpha[0] >= 0x80) {
            campaignWork.windowAlpha[0] = 0x80;
        }
    }
    if (campaignWork.cursorY >= 0x154) {
        campaignWork.windowAlpha[1] -= 8;
        if (campaignWork.windowAlpha[1] <= 0x60) {
            campaignWork.windowAlpha[1] = 0x60;
        }
    } else {
        campaignWork.windowAlpha[1] += 8;
        if (campaignWork.windowAlpha[1] >= 0x80) {
            campaignWork.windowAlpha[1] = 0x80;
        }
    }
    if (campaignWork.cursorX >= 0x1C8) {
        campaignWork.windowAlpha[2] -= 8;
        if (campaignWork.windowAlpha[2] <= 0x60) {
            campaignWork.windowAlpha[2] = 0x60;
        }
    } else {
        campaignWork.windowAlpha[2] += 8;
        if (campaignWork.windowAlpha[2] >= 0x80) {
            campaignWork.windowAlpha[2] = 0x80;
        }
    }
}

typedef struct Copy_0023B920 {
    s32 words[0x3FE8];
} Copy_0023B920;

extern s8 campaignHelpFlag; /* original: HELP_flg */

/* Ends the campaign map: frees its models, textures and windows. */
void TkCamp_Term(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 i;
    s32 x;
    s32 y;

    if (campaignHelpFlag != 0) {
        *(Copy_0023B920 *)GAME_DATA_COPY_ADDR = *(Copy_0023B920 *)SzData_GetData(0);
        a = SzData_GetOption(0, 0);
        b = SzData_GetOption(0, 1);
        c = SzData_GetOption(0, 2);
        switch (campaignWork.helpPick) {
        case 0:
            i = 0x20;
            x = 0x11;
            y = 0x12;
            break;
        case 1:
            i = 0x21;
            x = 0x13;
            y = 0x14;
            break;
        case 2:
            i = 0x22;
            x = 0x15;
            y = 0x16;
            break;
        case 3:
            i = 0x23;
            x = 0x17;
            y = 0x18;
            break;
        default:
            i = 0x24;
            x = 0x19;
            y = 0x1A;
            break;
        }
        SzGame_SetMenuNum(1, 0);
        SzGame_SetMenuNum(2, 0);
        SzGame_SetMenuNum(3, i);
        SzGame_SetMenuNum(4, i);
        SzData_SetupFromConstDeck(0, x);
        SzData_SetupFromConstDeck(1, y);
        for (i = 0; i < 2; i++) {
            SzData_SetOption(i, 0, a);
            SzData_SetOption(i, 1, b);
            SzData_SetOption(i, 2, c);
        }
    }
    SzDuel_CloseMsgPopup();
}

/* Starts practice duel `param` from the campaign: picks the opponent, deck and map for the current practice level. (original: Taku_Camp_Go_Rensyu_Duel) */
void Taku_Camp_Go_Practice_Duel(s32 param) {
    s32 opponent;
    s32 deck0;
    s32 deck1;

    switch (practiceDuelFlag) {
    case 0:
        opponent = 0x20;
        deck0 = 0x11;
        deck1 = 0x12;
        break;
    case 1:
        opponent = 0x21;
        deck0 = 0x13;
        deck1 = 0x14;
        break;
    case 2:
        opponent = 0x22;
        deck0 = 0x15;
        deck1 = 0x16;
        break;
    case 3:
        opponent = 0x23;
        deck0 = 0x17;
        deck1 = 0x18;
        break;
    case 4:
        opponent = 0x24;
        deck0 = 0x19;
        deck1 = 0x1A;
        break;
    }
    SzGame_SetMenuNum(1, 0);
    SzGame_SetMenuNum(2, 0);
    SzGame_SetMenuNum(3, opponent);
    SzGame_SetMenuNum(4, opponent);
    SzData_SetupFromConstDeck(0, deck0);
    SzData_SetupFromConstDeck(1, deck1);
    if (practiceDuelFlag < 3) {
        practiceDuelFlag += 1;
        if (practiceDuelFlag > 2) {
            practiceDuelFlag = 0;
            practiceDuelEnd = 1;
        }
    }
    if (param != 0) {
        SzGame_Goto(1, 0);
    } else {
        SzGame_Push(1, 0);
    }
}

typedef struct Copy_0023BC80 {
    s32 words[0x3FE8];
} Copy_0023BC80;

/* Opens the campaign's help screen. */
void Taku_Camp_Go_Help(void) {
    campaignHelpFlag = 1;
    *(Copy_0023BC80 *)GAME_DATA_COPY_ADDR = *(Copy_0023BC80 *)SzData_GetData(0);
    SzGame_Push(1, 0);
}

typedef int DotrHelpWord;
struct DotrHelpWindow {
    short x, y, w, h;
    char unknown_08[2];
};
struct DotrHelpWindows {
    struct DotrHelpWindow w[4];
};
extern struct DotrHelpWindows D_0029B020;
extern signed char D_00299E10_b_2[];
extern DotrHelpWord Taku_Window_Set_window_2(DotrHelpWord cursor, struct DotrHelpWindow *window,
                                    unsigned short flag, int a3, unsigned short x,
                                    unsigned short y, int a6, int a7, int a8);
extern DotrHelpWord func_001B6F70_b_2(DotrHelpWord cursor, int x, int y, int a,
                                                int flags, int n, const char *text, int c);
extern DotrHelpWord func_0021C450_b(DotrHelpWord cursor, int index, int no, int x, int y,
                                     int unused, unsigned char *col, float sx, float sy);

/* Draws the campaign's help window. */
int Taku_Camp_Help_Window(int cursor)
{
    signed char *st;
    short y;
    short i;
    int ix;
    short yy;
    struct DotrHelpWindows win;
    unsigned char col[4];
    short xx;
    int no;
    int px;
    CampaignWork *blk;

    st = D_00299E10_b_2;
    win = D_0029B020;
    col[0] = col[1] = col[2] = 128;
    col[3] = 128;
    y = 512 - ((campaignWork.helpStep << 9) >> 3);
    blk = &campaignWork; /* helpPick is read both directly and through this pointer, as in the original */
    if (campaignWork.helpOpen != 0) {
        cursor = Taku_Window_Set_window_2(cursor, &win.w[0], 2, 0, 128, y + 80, 0, 128, 101);
        cursor = Taku_Window_Set_window_2(cursor, &win.w[1], 2, 0, 128, y + 80, 0, 128, 101);
        cursor = Taku_Window_Set_window_2(cursor, &win.w[3], st[0] + 10, 0, 282, y + 94, 0, 128, 128);
        cursor = func_001B6F70_b_2(cursor, 296, y + 102, 2, 1, 4, D_0030F113, 0);
        

        px = 160;
        xx = px;
        ix = xx;
        yy = 144;
        cursor = Taku_Window_Set_window_2(cursor, &win.w[2], 2, 0, px, y + ((short)(campaignWork.helpPick * 36) + yy), 0, 128, 0);
        yy += 2;
        for (i = 0; i < 5; i++) {
            if (i == blk->helpPick) {
                col[0] = col[1] = col[2] = 255;
                col[3] = 128;
            } else {
                col[0] = col[1] = col[2] = 64;
                col[3] = 128;
            }
            switch (i) {
            case 0:
                no = 3049;
                break;
            case 1:
                no = 3050;
                break;
            case 2:
                no = 3051;
                break;
            case 3:
                no = 3052;
                break;
            default:
                no = 3053;
                break;
            }
            cursor = func_0021C450_b(cursor, 1, no, ix + 16, (short)(yy + y), 0, col, 1.0f, 1.0f);
            yy += 36;
        }
    }
    return cursor;
}

typedef struct Flags_0023BFF0 {
    s8 unused : 4;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
} Flags_0023BFF0;

typedef struct Draw_0023BFF0 {
    u8 pad00[0x10];
    s32 field10;
    s32 field14;
    s32 field18;
    s32 field1C;
    u8 vector20[0x10];
    s32 field30;
    s32 field34;
    u8 pad38[0x49];
    Flags_0023BFF0 flags;
    u8 pad82[0xE];
} Draw_0023BFF0;

typedef struct Texture_0023BFF0 {
    u8 pad00[0x44];
    u8 field44;
    u8 pad45[0x1B];
} Texture_0023BFF0;

/* Draws the card just won (card `card`) flying in at screen point (x, y). */
void *Taku_Camp_Card_Get(void *packet, f32 x, s32 card, f32 y, s32 depth) {
    extern void SzDuel_ClearDrawCard();
    Texture_0023BFF0 texture;
    Draw_0023BFF0 draw;

    SzDuel_ClearDrawCard(&draw);
    draw.flags.enabled = 1;
    draw.flags.colored = 1;
    draw.flags.reserved = 0;
    draw.flags.horizontal = 1;
    draw.field30 = 0x3F000000;
    draw.field34 = 0x3F000000;
    SzDuel_InitCardInfo(&texture, 999);
    texture.field44 = card;
    Ex3d_GetLookVector((s32)draw.vector20);
    draw.field10 = 0;
    draw.field14 = depth;
    draw.field18 = 0;
    draw.field1C = 0;
    packet = (void *)SzDuel_StartCardSession_Pipe((s32)packet);
    SzDuel_SetCardDefPrioZ(0xFFFFFF);
    Ex3d_GetPointOnScreen(&draw, x, y);
    return (void *)SzDuel_FinishCardSessionX_Pipe(SzDuel_DrawCard_Pipe(
        SzDuel_SetupCard2_Pipe((s32)packet, (s32)(SzDuel_GetCardNode(&draw, 1) ? &texture : NULL), &draw),
        (s32)&draw));
}

/* How many duels since the last reincarnation (reincarnation needs 5; campaignState + 0xCA). */
s32 Taku_Get_Duel5_flg(void) {
    return D_00299EDA;
}

/* Starts that count again (after a reincarnation). */
void Taku_Set_Duel5_flg(void) {
    D_00299EDA = 0;
}

/* How many campaign duels the player has won. */
s32 Taku_Get_WinCount(void) {
    return (s32) winCount;
}

typedef struct State_0023C170 {
    u8 pad00[0x8];
    s32 field08;
    s32 field0C;
    s32 field10;
    s32 field14;
    s32 field18;
    s32 field1C;
    s32 field20;
    s32 field24;
    u8 pad28[4];
    s16 field2C;
    s16 field2E;
    s16 field30;
    u8 pad32[2];
    s16 field34;
    s16 field36;
    s16 field38;
    s16 field3A;
    s16 field3C;
    s16 field3E;
    s16 field40;
    s16 field42;
    u8 pad44[4];
    s32 field48;
    s32 field4C;
    s16 field50;
    s16 field52;
    s16 field54;
    s16 field56;
    u8 pad58[4];
    s32 field5C;
    s32 field60;
    s32 field64;
    s32 field68;
    u8 pad6C[0x214];
    s16 field280;
    u8 pad282[2];
    s32 field284;
    s32 field288;
    s32 field28C;
    s32 field290;
    s16 field294;
    s16 field296;
    u8 pad298[0x10];
    s16 field2A8;
    s16 field2AA;
    s16 field2AC;
    s16 field2AE;
    s16 field2B0;
    s16 field2B2;
    s16 field2B4;
    s16 field2B6;
    s16 field2B8;
    u8 pad2BA[4];
    s16 field2BE;
    u8 pad2C0[0x580];
} State_0023C170;

/* Resets the memory-card job state (`mode` picks the job). (original: TakuCard_inti) */
s32 TakuCard_init(s32 mode) {
    extern void *memCardTrunkData;
    extern void *WhiteSaveData;
    extern s8 saveFileHeader;
    extern State_0023C170 D_0034FB00;
    extern s32 func_00194248(s32, s32 *, s32 *);
    extern s32 func_00194380(s32, s32, s32 *, s32 *, s32 *);
    s32 found[2];
    State_0023C170 *state = &D_0034FB00;
    s16 i;
    s32 *out;

    memCardTrunkData = SzData_GetData(0);
    WhiteSaveData = SzData_GetData(1);
    saveFileHeader = 1;
    func_00195108((s32)&D_0034FB00, 0x840);
    D_0034FB00.field30 = 0;
    D_0034FB00.field34 = 0;
    D_0034FB00.field36 = 0;
    D_0034FB00.field38 = 0;
    D_0034FB00.field3A = 0;
    D_0034FB00.field3C = 0;
    D_0034FB00.field3E = 0;
    D_0034FB00.field40 = 0;
    D_0034FB00.field42 = 0;
    D_0034FB00.field54 = 0;
    D_0034FB00.field56 = 0;
    D_0034FB00.field48 = 0;
    D_0034FB00.field4C = 0;
    D_0034FB00.field50 = 0;
    D_0034FB00.field52 = 0;
    D_0034FB00.field08 = 0;
    D_0034FB00.field0C = 0;
    D_0034FB00.field10 = 0;
    D_0034FB00.field14 = 0;
    D_0034FB00.field18 = 0;
    D_0034FB00.field1C = 0;
    D_0034FB00.field20 = 0;
    D_0034FB00.field24 = 0;
    D_0034FB00.field2C = 0;
    D_0034FB00.field2E = 0;
    D_0034FB00.field5C = 0;
    D_0034FB00.field60 = 0;
    D_0034FB00.field68 = 6;
    D_0034FB00.field64 = 0;
    D_0034FB00.field284 = 0;
    D_0034FB00.field288 = 0;
    D_0034FB00.field28C = 0;
    D_0034FB00.field290 = 0;
    D_0034FB00.field294 = 0;
    D_0034FB00.field296 = 0;
    D_0034FB00.field2B4 = 0;
    D_0034FB00.field280 = 0;
    D_0034FB00.field2A8 = 0;
    D_0034FB00.field2AA = 0;
    D_0034FB00.field2AC = 0;
    D_0034FB00.field2AE = 0;
    D_0034FB00.field2B0 = 0;
    D_0034FB00.field2B2 = 0;
    D_0034FB00.field2B6 = 0;
    D_0034FB00.field2B8 = 0;

    out = found;
    for (i = 0; i < 2; i++) {
        func_00194380(i, state->field0C, &state->field10, &state->field14, &state->field18);
        func_00194248(0, &state->field20, out);
        out++;
    }

    if (mode == 1 && (found[0] != 0 || found[1] != 0)) {
        return 1;
    }
    return 0;
}

typedef struct State_0023E610 {
    s32 result;
    u8 pad04[0x1C];
    s32 command;
    s32 status;
    u8 pad28[8];
    s16 field30;
    u8 pad32[2];
    s16 field34;
    u8 pad36[0xA];
    s16 field40;
} State_0023E610;

extern struct State_0023E610 D_0034FB00;

struct State_0023E610;

extern State_0023E610 D_0034FB00;

typedef struct Header_0023F5A0 {
    s16 first;
    s16 second;
} Header_0023F5A0;
extern s32 *memCardTrunkData; /* original: p_kaban_data */
extern Header_0023F5A0 saveFileHeader; /* original: Taku_card_info */
