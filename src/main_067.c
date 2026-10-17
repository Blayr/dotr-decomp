#include "common.h"

/* Draws the terrain (tikei) window of the campaign place under the cursor. */
s32 Taku_Camp_TIKEI_WINDOW(s32 packet) {
    extern s32 Taku_Window_Set(s32, void *, s32, s32, u16, s32, s32, s32, s32);
    extern s32 Taku_Camp_TIKEI_Map_Hyouji(s32, u16, u16, s32);
    extern s32 Taku_Obj_Set();
    extern s32 Taku_FT4_Set();
    extern u8 camp_window_Map_data[];
    extern u8 D_00297B9A[];
    extern u8 D_00297BA4[];
    extern u8 camp_window_tikei_iro_ue[];
    extern u8 camp_window_tikei_iro_sita[];
    extern u8 camp_window_tikei_partu[];
    extern u8 camp_window_tikei_partu_gejiwaku[];
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

    baseX = D_00299ED4;
    state = &campaignState;
    if (*(s8 *)0x01ED0066 != 0) {
        *(s16 *)0x01ED0068 += 2;
        if (*(s16 *)0x01ED0068 > 16) {
            *(s16 *)0x01ED0068 = 16;
        }
    } else {
        *(s16 *)0x01ED0068 -= 2;
        if (*(s16 *)0x01ED0068 < 0) {
            *(s16 *)0x01ED0068 = 0;
        }
    }
    fade = *(s16 *)0x01ED0068;
    alpha = (s16)(256 - ((fade << 8) >> 4));
    if (*(s8 *)0x01ED018C == 1 && state[0xC6] == 11) {
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
        packet = Taku_Window_Set(packet, camp_window_Map_data, (u16)(s8)side & 0xFFFF, 0,
                              alpha, 0, 0, 128, *(s16 *)0x01ED0228);
        packet = Taku_Camp_TIKEI_Map_Hyouji(packet, baseX, alpha, 0);
        packet = Taku_Window_Set(packet, D_00297B9A, (u16)(s8)side, 0,
                              alpha, 0, 0, 128, 128);
        packet = Taku_Window_Set(packet, D_00297BA4, (u16)(state[0] ^ 1), 0,
                              alpha, 0, 0, 128, 128);
        p = camp_window_tikei_partu;
        i = 0;
        do {
            packet = Taku_Obj_Set(packet, p, alpha, 0);
            i++;
            p += 0x26;
        } while (i < 10);
        row = 0;
        y = 0;
        do {
            q = camp_window_tikei_partu_gejiwaku;
            j = 0;
            do {
                packet = Taku_Obj_Set(packet, q, alpha, y);
                j++;
                q += 0x26;
            } while (j < 3);
            y = (s16)(y + 16);
            row++;
        } while (row < 10);
        packet = Taku_FT4_Set(packet, camp_window_tikei_iro_ue + (s8)side * 0x26, alpha, 0, 0);
        packet = Taku_FT4_Set(packet, camp_window_tikei_iro_sita + state[0] * 0x26, alpha, 0, 2);
    }
    return packet;
}

typedef struct Sprite_00236F90 {
    s16 xy[8];
    u8 pad10[0x14];
    s16 tile;
} Sprite_00236F90;

typedef struct Work_00236F90 {
    s16 pad0[3];
    s16 counts[10];
} Work_00236F90;

/* Draws (hyouji) the small terrain map of deck `deck`'s place at (x, y). */
s32 Taku_Camp_TIKEI_Map_Hyouji(s32 gp, u16 deck, u16 x, u16 y) {
    extern s32 Taku_Obj_Set(s32, void *, s16, s16);
    extern s32 Taku_G4_Set(s32, void *, s16, s16);
    extern s32 Taku_G4_Set2(s32, void *, s16, s16, s16, s16);
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe(s32, s32, s32, s32, s32, s32, s32);
    extern Sprite_00236F90 D_0029AFA0;
    extern Sprite_00236F90 D_0029AFD0;
    extern u8 D_002CEE5C[];
    extern Sprite_00236F90 camp_window_tikei_partu_geji[][2];
    extern s16 D_00297BAE;
    extern s16 D_00297BB0;
    extern s16 D_00297BB2;
    extern s16 D_00297BB4;
    Work_00236F90 *work;
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
    work = (Work_00236F90 *)0x01ED0000;
    card = D_0029AFA0;
    bar = D_0029AFD0;
    for (i = 0; i < 10; i++) {
        work->counts[i] = 0;
    }
    for (row = 0, grid = &D_002CEE5C[deck * 49]; row < 7; row++) {
        cell = grid;
        for (col = 0; col < 7; col++) {
            switch ((s16)*cell) {
            case 0:
                tile = 'A';
                work->counts[0]++;
                break;
            case 1:
                tile = 'B';
                work->counts[1]++;
                break;
            case 2:
                tile = 'C';
                work->counts[2]++;
                break;
            case 3:
                tile = 'D';
                work->counts[3]++;
                break;
            case 4:
                tile = 'E';
                work->counts[4]++;
                break;
            case 5:
                tile = 'F';
                work->counts[5]++;
                break;
            case 6:
                tile = 'G';
                work->counts[6]++;
                break;
            case 7:
                tile = 'H';
                work->counts[7]++;
                break;
            case 8:
                tile = 'I';
                work->counts[8]++;
                break;
            case 9:
                tile = 'J';
                work->counts[9]++;
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
        bar.xy[0] = D_00297BAE;
        bar.xy[1] = D_00297BB0;
        bar.xy[2] = D_00297BB2;
        bar.xy[3] = D_00297BB0;
        bar.xy[4] = D_00297BAE;
        bar.xy[5] = D_00297BB4;
        bar.xy[6] = D_00297BB2;
        bar.xy[7] = D_00297BB4;
        gp = Taku_G4_Set(gp, &bar, x, y + dy);
        dy += 16;
    }
    for (i = 0, dy = 0; i < 10; i++, dy += 16) {
        if (work->counts[i] >= 49) {
            scale = 76.0f;
        } else if (work->counts[i] <= 0) {
            scale = 0.0f;
        } else {
            scale = (76.0f * work->counts[i]) / 49.0f;
        }
        for (k = 0; k < 2; k++) {
            for (j = 0; j < 8; j++) {
                camp_window_tikei_partu_geji[i][k].xy[j] = camp_window_tikei_partu_geji[0][k].xy[j];
            }
            gp = Taku_G4_Set2(gp, &camp_window_tikei_partu_geji[i][k], x, y + dy, scale, 0);
        }
        gp = SzDuel_DrawWindow_FontDigit_Pipe(gp, x + ((D_00297BAE + D_00297BB2) >> 1),
                                              y + (dy + camp_window_tikei_partu_geji[i][0].xy[1]), 1, 2,
                                              (u16)((work->counts[i] < 10) ? 1 : 2), work->counts[i]);
    }
    return gp;
}

extern u8 campaignPlaces[]; /* original: model_data */
extern u8 campaignCoord[]; /* original: prim_data */
extern s32 D_0029A000;
extern u8 D_0029A44C[];

#pragma opt_strength_reduction off

/* Builds the campaign map's 3D polygons (the ground and the routes). */
void Taku_Camp_3D_Poly_Init(void) {
    s16 spB0;
    u8 *spC0;
    s32 spD0;
    s16 var_s0;
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
    s16 var_s0_2;

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
        var_s0 = 0;
        var_s3 = spD0 >> 5;
        var_s4 = (var_fp << 16) >> 5;
        var_s5 = (var_s7 << 16) >> 5;
        for (; var_s0 < 4; var_s0++) {
            if (var_s0 == 2) {
                *(s32 *)(var_s2 + 0xEC) = 0;
                *(s32 *)(var_s2 + 0xF0) = 0x410A6666;
                *(s32 *)(var_s2 + 0xF4) = 0;
                *(s32 *)(var_s2 + 0xF8) = 0;
            } else {
                switch (var_s0) {
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
    var_s0_2 = 0;
    for (; var_s0_2 < 16; var_s0_2++) {
        Taku_Vector_Set(var_s6, campaignPlaces);
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
#pragma opt_strength_reduction reset
