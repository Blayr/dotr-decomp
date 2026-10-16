#include "common.h"

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

s32 Taku_Camp_Kazu_Disp(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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

INCLUDE_ASM("asm/nonmatchings/main_063", Taku_Camp_Ivent_Name);

typedef struct Tables_00224A40 {
    s32 pad[8];
    s32 normal[3];
    s32 type0[3];
    s32 type1[3];
} Tables_00224A40;

typedef struct State_00224A40 {
    u8 pad[0x53CE];
    s8 selected;
    s8 types[12];
    s8 cards[12];
    s8 locations[12];
    u8 pad2[3];
    u16 checksum;
    u16 codes[3];
    u16 values[3];
} State_00224A40;

void Taku_Camp_Ivent_Name_Set(void) {
    extern u16 D_00299CE0[];
    extern u16 D_00299D00[][6];
    extern Tables_00224A40 D_002D19D0;
    extern s32 D_002D19D8;
    extern u16 D_002D49D4[];
    State_00224A40 *state;
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

    state = (State_00224A40 *)0x01ED0000;
    sum_ptr = (u8 *)&D_00299E10;
    i = 0;
    offset = 0;
    out = sum_ptr;
    while (i < 12) {
        group = state->cards[i] / 5;
        slot = (s16)(state->cards[i] % 5) + state->locations[i] * 6;
        if (i == 0) {
            dest = (u16 *)((u8 *)&D_002D49D4[D_002D19D8] + offset);
            switch (state->types[i]) {
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
        switch (state->types[i]) {
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
        if (i == 12 || i == state->selected) {
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
    state->checksum = sum & 0xF;
    code_index = 0;
    shift = 0;
    code_ptr = (u8 *)state;
    while (code_index < 3) {
        *(u16 *)(code_ptr + 0x53F8) = ((s32)D_00299CE0[state->checksum] >> shift) & 0x1F;
        shift += 5;
        *(u16 *)(code_ptr + 0x53FE) = D_00299D00[*(u16 *)(code_ptr + 0x53F8)][0] & 0x3FF;
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

typedef struct {
    u8 pad[0x53A8];
    s8 sel;
    s8 pad53A9;
    s8 mode;
    u8 pad53AB[0x4D];
    u16 codes[3];
    u16 values[3];
} State_00224E40;

extern s16 D_00299ED2;
extern Frame_00224E40 D_0029AA08;
extern Sprite_00224E40 D_0029AA20;
extern Pair_00224E40 D_0029AA50;
extern Sprite_00224E40 D_0029AAA0;
extern Pair_00224E40 D_0029AAD0;
extern Sprite_00224E40 D_0029AB20;
extern Sprite_00224E40 D_0029AB50;
extern Sprite_00224E40 D_002980D0[];
extern Tex_00224E40 D_002950A0[];
extern Code_00224E40 D_00299D00[];
extern char D_0030F0BB[];
extern char D_0030F0C7[];
extern char D_0030F0D4[];
extern char D_0030F0E8[];

#pragma opt_dead_assignments off

s32 Taku_Camp_Ivent_Window(s32 arg0) {
    s16 ny;
    extern s32 Taku_Camp_Ivent_Name();
    extern s32 Taku_Window_Set(s32, void *, s32, s32, u16, u16, s32, s32, s32);
    extern s32 Taku_Obj_Set(s32, void *, s16, s16);
    extern s32 Taku_Bunsyou_Set(s32, s32, s32, s16, s16, f32, f32, s32, void *);
    extern s32 SzMsg_LoadFont_Pipe(s32, s32, s32, s32, s32);
    extern s32 Taku_FT4_Set(s32, void *, s16, s16, u16);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, void *, void (*)(void));
    s16 flag2;
    s8 *ctx;
    s16 i;
    State_00224E40 *state;
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

    ctx = (s8 *)&D_00299E10;
    state = (State_00224E40 *)0x01ED0000;
    frame = D_0029AA08;
    s100 = D_0029AA20;
    pair130 = D_0029AA50;
    s180 = D_0029AAA0;
    pair1B0 = D_0029AAD0;
    s200 = D_0029AB20;
    color.r = color.g = color.b = 0x80;
    color.a = 0x80;
    if (D_00299ED2 == 0x2738 && *(s8 *)0x01ED53A6 != 0) {
        arg0 = Taku_Camp_Ivent_Name(arg0);
    } else if (*(s8 *)0x01ED53A6 != 0) {
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
        frame.x1 = ((w - 0x10) * *(s8 *)0x01ED53A7) / 100 + 0x10;
        frame.y1 = ((h - 0x10) * *(s8 *)0x01ED53A7) / 100 + 0x10;
        arg0 = Taku_Window_Set(arg0, &frame, 2, 0, x, y, 0, 0x80, 0x40);
        if (*(s8 *)0x01ED53A6 != 0) {
            t = (*(s8 *)0x01ED53A7 * 0x280) / 100;
            nx = x + w - 0x8B;
            right = 0x280 - t;
            ny = y + h - 0x2A;
            frame.kind = 9;
            frame.x1 = 0x82;
            frame.y1 = 0x22;
            left = t - 0x280;
            arg0 = Taku_Window_Set(arg0, &frame, 3, 0, nx + right, ny, 0, 0x80, 0x40);
            arg0 = Taku_Obj_Set(arg0, &pair1B0, nx + 0x1B + right, ny + 9);
            arg0 = Taku_Bunsyou_Set(arg0, 1, 0xA7, nx + 0x3C + right, 6 + ny, 1.0f, 1.0f, 0, &color);
            switch (*(s16 *)(0xC2 + ctx)) {
            case 0x2738:
            case 0x276A:
                if (*(s8 *)0x01ED53A6 == 2) {
                    tmpl = D_002980D0;
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
                sel = *(s8 *)0x01ED53A8;
                t = (s16)((sel == 0) ? 0xB0 : 0xE0);
                frame.kind = 8;
                y = t;
                if (*(s16 *)(0xC2 + ctx) == 0x2742) {
                    frame.x1 = 0x148;
                    frame.y1 = 0x21;
                }
                if (*(s8 *)0x01ED53A6 == 2) {
                    arg0 = Taku_Window_Set(arg0, &frame, 3, 0, x + left, y, 0, 0x80, 0x40);
                }
                if (*(s8 *)0x01ED53A6 == 2) {
                    for (i2 = 0; i2 < 2; i2++) {
                        if (i2 == state->sel) {
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
                            arg0 = Taku_Bunsyou_Set(arg0, 1, id, x + 8 + left, 0xB4, sx, sy, 0, &color);
                        } else {
                            if (*(s16 *)(ctx + 0xC2) == 0x276A) {
                                id = 0x101;
                            } else {
                                id = 0xFE;
                            }
                            sy = sx = 1.0f;
                            arg0 = Taku_Bunsyou_Set(arg0, 1, id, x + 8 + right, 0xE4, sx, sy, 0, &color);
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
                    hundreds[n] = D_00299D00[state->codes[n]].number / 100;
                    ones[n] = D_00299D00[state->codes[n]].number % 100;
                    for (m = 0; m < 4; m++) {
                        digits[n][m] = ((s32)D_00299D00[state->codes[n]].digits >> (m * 3)) & 7;
                        types[n][m] = (D_00299D00[state->codes[n]].types >> (5 * m)) & 0x1F;
                    }
                }
                if (*(s8 *)0x01ED5494 == 0) {
                    switch (v = *(s8 *)0x01ED5495) {
                    case 0:
                        cur = 2;
                        break;
                    default:
                        cur = v;
                        break;
                    }
                } else {
                    cur = *(s8 *)0x01ED53A8;
                }
                frame.kind = 1;
                frame.x1 = 0xF0;
                frame.y1 = 0x20;
                arg0 = Taku_Window_Set(arg0, &frame, 2, 0, left + 0xA, 0x8B, 0, 0x80, 0x40);
                sx = 1.0f;
                arg0 = Taku_Bunsyou_Set(arg0, 1, 0xFF, left + 0x10, 0x91, sx, sx, 0, &color);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, left + 0x2E, 0xE6, 1, 0, 0xB, D_0030F0BB, NULL);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, left + 0x52, 0xF5, 1, 0, 0xC, D_0030F0C7, NULL);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, right + 0x1A2, 0xB5, 1, 0, 0x13, D_0030F0D4, NULL);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, right + 0x1A2, 0xDD, 1, 0, 0xE, D_0030F0E8, NULL);

                for (n = 0, xx3 = left; n <= hundreds[cur]; n++, xx3 += 0x10) {
                    if (n < hundreds[cur]) {
                        arg0 = Taku_Obj_Set(arg0, &pair130.s[0], xx3, 0);
                    } else {
                        D_002950A0[pair130.s[1].index].width = (ones[cur] * 16) / 100;
                        pair130.s[1].x1 = pair130.s[1].x0 + D_002950A0[pair130.s[1].index].width;
                        arg0 = Taku_Obj_Set(arg0, &pair130.s[1], xx3, 0);
                    }
                }
                arg0 = Taku_Camp_Kazu_Disp(arg0, hundreds[cur], ones[cur], left);
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
                    mode = state->mode;
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
                q = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, SzDuel_GetMsgName(state->values[cur]), 0, 0x16));
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
        if (*(s8 *)0x01ED53A6 == 1) {
            *(s8 *)0x01ED53A7 += 6;
            if (*(s8 *)0x01ED53A7 >= 100) {
                *(s8 *)0x01ED53A7 = 100;
                *(s8 *)0x01ED53A6 = 2;
            }
        }
        switch (*(s16 *)(ctx + 0xC2)) {
        case 0x2738:
        case 0x276A:
        case 0x2742:
            if (*(s8 *)0x01ED53A6 == 3) {
                *(s8 *)0x01ED53A7 -= 6;
                if (*(s8 *)0x01ED53A7 < 0) {
                    *(s8 *)0x01ED53A7 = 0;
                    *(s8 *)0x01ED53A6 = 4;
                }
            }
            break;
        case 0x2756:
        case 0x2757:
        case 0x2760:
            if (*(s8 *)0x01ED53A6 == 3 && *(s8 *)0x01ED5494 >= 3) {
                *(s8 *)0x01ED53A7 -= 6;
                if (*(s8 *)0x01ED53A7 < 0) {
                    *(s8 *)0x01ED53A7 = 0;
                    *(s8 *)0x01ED53A6 = 4;
                }
            }
            break;
        }
    }
    return arg0;
}
#pragma opt_dead_assignments reset

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

extern s16 D_00299ED2;
extern u8 D_00299F60;
extern Packet_00226120 D_0029AB80;

void *Taku_Camp_Kumo(void *arg0) {
    extern void *Taku_G4_Set();
    s8 *context = &D_00299E10;
    u8 *slot = &D_00299F60;
    Packet_00226120 packet = D_0029AB80;
    s16 state;
    s16 i;

    if (D_00299ED2 == 0x2724 && *(s16 *)0x01ED536C < 6) {
        packet.depth = -10;
    } else if (*(s16 *)(context + 0xC2) == 0x2BB0) {
        packet.depth = -10;
    } else if (*(s16 *)(context + 0xC2) == 0x2F7C) {
        packet.depth = -10;
    }

    state = *(s16 *)0x01ED53A2;
    if (state != 0) {
        switch ((s16)state) {
        case 2:
            break;
        case 3:
            if (0 <= *(s16 *)0x01ED53A4) {
                *(s16 *)0x01ED53A4 -= 0x10;
                if (*(s16 *)0x01ED53A4 <= 0) {
                    *(s16 *)0x01ED53A4 = 0;
                    *(s16 *)0x01ED53A2 = 0;
                }
            }
            break;
        case 4:
            if (*(s16 *)0x01ED53A4 <= 0x1000) {
                *(s16 *)0x01ED53A4 += 0x20;
                if (*(s16 *)0x01ED53A4 >= 0x1000) {
                    *(s16 *)0x01ED53A4 = 0x1000;
                    *(s16 *)0x01ED53A2 = 4;
                }
            }
            break;
        case 10:
            *(s16 *)0x01ED53A4 += 0x400;
            if (*(s16 *)0x01ED53A4 >= 0x1000) {
                *(s16 *)0x01ED53A4 = 0x1000;
                *(s16 *)0x01ED53A2 = 11;
            }
            break;
        case 20:
            *(s16 *)0x01ED53A4 -= 0x100;
            if (*(s16 *)0x01ED53A4 <= 0) {
                *(s16 *)0x01ED53A4 = 0;
                *(s16 *)0x01ED53A2 = 21;
            }
            break;
        case 22:
            *(s16 *)0x01ED53A4 += 0x100;
            if (*(s16 *)0x01ED53A4 >= 0x1000) {
                *(s16 *)0x01ED53A4 = 0x1000;
                *(s16 *)0x01ED53A2 = 23;
            }
            break;
        case 30:
            *(s16 *)0x01ED53A4 += 0x400;
            if (*(s16 *)0x01ED53A4 >= 0x1000) {
                *(s16 *)0x01ED53A4 = 0x1000;
                *(s16 *)0x01ED53A2 = 31;
            }
            break;
        case 32:
            *(s16 *)0x01ED53A4 -= 0x20;
            if (*(s16 *)0x01ED53A4 <= 0) {
                *(s16 *)0x01ED53A4 = 0;
                *(s16 *)0x01ED53A2 = 33;
            }
            break;
        }

        state = *(s16 *)0x01ED53A2;
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

        if (*(s16 *)(context + 0xC2) == 0x2738 && *(s16 *)0x01ED536C > 1) {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 = 0;
        } else if (*(s16 *)(context + 0xC2) == 0x2B9A ||
                   *(s16 *)(context + 0xC2) == 0x2F64) {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 = 0;
        } else {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 =
                (*(s16 *)0x01ED53A4 << 7) >> 12;
            arg0 = Taku_G4_Set(arg0, &packet, 0, 0);
        }
    }

    Taku_Coord_Set(slot);
    for (i = 0; i < 16; i++) {
    }
    return arg0;
}
