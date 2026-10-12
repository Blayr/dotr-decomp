#include "common.h"

void func_001D7D10(s32 arg0, s32 arg1) {
    u16 ids[4];
    s16 w[4];
    u8 *g = D_00317490;
    u8 *p;
    s32 i;
    s32 x;
    s32 cnt;
    s32 flag;
    s32 ok;
    s32 id;
    s32 n;
    s32 have;
    s32 v;
    s16 r;
    s32 idx;

    p = D_00317490 + arg0 * 0x350;
    func_001DF1E0(arg0);
    func_001D89F0(arg0, 0, 999, 0, 0, 0, 0);
    x = -250;
    for (i = 0; i < g[0xD49]; i++) {
        v = func_001DF0C0(arg0, i);
        if (v < 0) {
            v = 999;
        } else {
            v &= 0xFFF;
        }
        func_001D89F0(arg0, i + 1, v, x, 0x1C0, x, -8);
        x += 0x7D;
    }
    if (arg1 != 0) {
        have = func_001DF110(arg0);
        n = func_001DE9C0(arg0);
        cnt = have + n;
        cnt = cnt < 5 ? cnt : 5;
        ok = n > 0;
        flag = 0;
        if (ok) {
            ok = p[0x344] > 0;
        }
        if (ok && !(p[0x344] & 0x80)) {
            flag = 1;
        }
        if (flag) {
            cnt = cnt + 1 < 5 ? cnt + 1 : 5;
        }
        for (; i < cnt; i++) {
            id = 999;
            if (flag && i + 1 >= cnt) {
                if (func_0026F690(arg0, ids, w, 0) >= 0) {
                    r = func_001A22C0(100.0f * ((f32)func_0019A5C8() / 2147483648.0f));
                    idx = 2;
                    if (r < w[0]) {
                        idx = 0;
                    } else if (r < w[0] + w[1]) {
                        idx = 1;
                    } else {
                    }
                    id = ids[idx];
                }
            }
            if (id == 999) {
                id = func_001DED30(arg0);
            }
            func_001DF130(arg0, id);
            func_001D89F0(arg0, i + 1, id, 0x2EE, 0x1C0, 0x2EE, -8);
        }
        for (; i < 5; i++) {
            func_001DF130(arg0, 999);
            func_001D89F0(arg0, i + 1, 999, 0, 0, 0, 0);
        }
    } else {
        for (; i < 5; i++) {
            func_001D89F0(arg0, i + 1, 999, 0, 0, 0, 0);
        }
    }
    g[0xD4A] = func_001DF110(arg0);
    for (i = 0; i < g[0xD4A]; i++) {
        g[0xD2C + i] = i + 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D8080);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D82C0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D8880);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D89F0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D8CD0);

s32 func_001D8FB0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (arg0 == NULL) {
        return 0;
    }
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) arg1;
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) arg2;
    *(s32 *)((u8 *)arg0 + 0x18) = 0;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0;
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) arg3;
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) arg4;
    *(s32 *)((u8 *)arg0 + 0x28) = 0;
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(s16 *)((u8 *)arg0 + 0x98) = (s16) arg6;
    *(s16 *)((u8 *)arg0 + 0x9A) = (s16) arg5;
    func_001CDEB0(arg0);
    return 1;
}

s32 func_001D9030(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (arg0 == NULL) {
        return 0;
    }
    func_00205CB0((u8 *) arg0 + 0x10, (f32) arg1, (f32) arg2);
    func_00205CB0((u8 *) arg0 + 0x20, (f32) arg3, (f32) arg4);
    *(s16 *)((u8 *) arg0 + 0x98) = (s16) arg6;
    *(s16 *)((u8 *) arg0 + 0x9A) = (s16) arg5;
    func_001CDEB0(arg0);
    return 1;
}

void func_001D90E0(s32 arg0, s32 arg1, s32 arg2) {
    f32 sp50[4];
    f32 sp60[4];
    u8 *temp_s3;

    temp_s3 = D_00317490 + (D_003181E4 * 0x350);
    func_001FC950(temp_s3 + 0x1D0, sp50);
    sp60[0] = (f32) arg1;
    sp60[2] = (f32) arg2;
    sp60[1] = (f32) *(s8 *)(temp_s3 + 0x345);
    func_001FA8A0(0, 0, 3, (u16)arg0, 0, sp60);
    func_001FA8A0(0, 0, 4, arg0 & 0xFFFF, 0, sp50);
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D91B0);

typedef struct {
    u8 pad0[0x40];
    u8 x;
    u8 y;
    u8 pad42[2];
    u8 owner;
    u8 slot;
    u8 pad46[0x11];
    s8 pad57 : 4;
    s8 flag : 1;
    s8 pad57b : 3;
} Card_001D9420;

s32 func_001D9420(void *arg0) {
    u8 *duel = D_00317490;
    s32 result;
    void **cell;
    s32 me;
    s32 other;
    s32 flag;
    Card_001D9420 *card = arg0;
    s32 target;
    s32 bits;
    extern s32 func_001DE4E0();

    result = 0;
    if (card != NULL) {
        cell = func_001DCD00(card->x, card->y);
        bits = func_001A82E0(0x1D);
        flag = (bits & (1 << card->owner)) ? 1 : 0;
        me = duel[0xD3C];
        other = duel[0xD3C] ^ 1;
        if (card->owner >= 2) {
            return 0;
        }
        if (cell == NULL || *cell != card) {
            if (flag) {
                if (func_001DE4E0(me) < 0x20 && func_001DE4E0(other) >= 0x64) {
                    result = 1;
                }
            } else if ((u16) func_00203A40(duel[0xD3C], 1, 2) == 0) {
                result = 1;
            }
        } else {
            result = func_00267380((s32) card, duel[0xD3C]);
            if (result == 0 && card->flag == 0) {
                target = func_00250360(card->owner, card->slot);
                if (flag) {
                    if (func_001DE4E0(me) < 0x20 && func_001DE4E0(other) >= 0x64 && func_001DE4E0(target) < 0x20) {
                        result = 1;
                    }
                } else if (duel[0xD3C] == target) {
                    if ((u16) func_00203A40(duel[0xD3C], 1, 2) == 0) {
                        result = 1;
                    }
                } else {
                    result = 1;
                }
            }
        }
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D95F0);

typedef struct {
    u8 pad0[0x1D0];
    u8 f1D0[0x16D];
    u8 x;
    u8 z;
    u8 pad33F[6];
    s8 y;
    s8 active : 1;
    u8 pad347[9];
} Player_001D9820;

typedef struct {
    Player_001D9820 players[4];
    u8 padD40[0x26];
    s8 : 7;
    s8 flagD66 : 1;
    s8 flagD67 : 1;
} State_001D9820;

void func_001D9820(s32 arg0, s32 arg1) {
    extern s32 func_001A22C0(f32);
    State_001D9820 *state = (State_001D9820 *)D_00317490;
    Player_001D9820 *p;
    s32 x;
    s32 z;
    Player_001D9820 *cur;
    f32 pos[4];
    f32 saved[4];

    D_003181E4 = arg1;
    p = (Player_001D9820 *)(D_00317490 + arg1 * 0x350);
    z = func_001A22C0((f32)((p->z - 3) * 50));
    x = func_001A22C0((f32)((p->x - 3) * 50));
    cur = (Player_001D9820 *)(D_00317490 + D_003181E4 * 0x350);
    func_001FC950(cur->f1D0, saved);
    pos[0] = (f32)x;
    pos[2] = (f32)z;
    pos[1] = (f32)cur->y;
    func_001FA8A0(0, 0, 3, 0x20, 0, pos);
    func_001FA8A0(0, 0, 4, 0x20, 0, saved);
    p->active = 1;
    if (func_0027F830(arg1) != 0) {
        p = state->players;
    }
    func_00275E30(p);
    state->flagD66 = 1;
    state->flagD67 = state->flagD66;
}

void func_001D99F0(void) {
    func_00209D30(func_001D9A20(func_00209D20()));
}

s32 func_001D9A20(s32 arg0) {
    return func_001D9A30(arg0, 2);
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D9A30);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D9C40);

void func_001D9DD0(void) {
    func_00209D30(func_001D9E00(func_00209D20()));
}

s32 func_001D9E00(s32 arg0) {
    s32 temp_s0;
    s32 temp_s0_2;

    func_0020A9E0();
    temp_s0_2 = func_0020A0B0(arg0, 0);
    temp_s0 = func_002084D0(temp_s0_2, func_00208680(0, 4));
    func_001FEAF0(0);
    func_001FEAF0(1);
    func_001FEAF0(2);
    return temp_s0;
}

s32 func_001D9E70(s32 arg0) {
    s32 temp_s0;

    func_0020A9E0();
    temp_s0 = func_002084D0(arg0, func_00208680(0, 4));
    func_001FEAF0(0);
    func_001FEAF0(1);
    func_001FEAF0(2);
    return temp_s0;
}

void func_001D9ED0(s32 arg0) {
    D_003180E4 = arg0;
}

void func_001D9EE0(s32 arg0) {
    D_003180E8 = arg0;
}

s32 func_001D9EF0(void) {
    return D_0031810C;
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D9F00);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DA2B0);

s32 func_001DA4C0(s32 mode, void *dst) {
    f32 negativeHalfWidth;
    f32 negativeHalfHeight;
    f32 halfHeight;
    f32 uMax;
    f32 vMax;
    f32 halfWidth;
    f32 width;
    f32 height;

    width = 120.0f;
    height = 180.0f;
    if (mode != 0) {
        width = 256.0f;
        height = 368.0f;
    }
    halfWidth = width / 2.0f;
    halfHeight = height / 2.0f;
    vMax = height / 512.0f;
    uMax = width / 512.0f;
    *(u8 *)((u8 *)dst + 0x18) = 0x80;
    *(u8 *)((u8 *)dst + 0x19) = 0x80;
    *(u8 *)((u8 *)dst + 0x1A) = 0x80;
    *(u8 *)((u8 *)dst + 0x1B) = 0x80;
    *(s32 *)((u8 *)dst + 0x1C) = 0x3F800000;
    negativeHalfWidth = -halfWidth;
    *(f32 *)((u8 *)dst + 0x0) = negativeHalfWidth;
    *(f32 *)((u8 *)dst + 0x4) = halfHeight;
    *(s32 *)((u8 *)dst + 0x8) = 0;
    *(s32 *)((u8 *)dst + 0xC) = 0x3F800000;
    *(s32 *)((u8 *)dst + 0x20) = 0;
    *(s32 *)((u8 *)dst + 0x24) = 0;

    *(u8 *)((u8 *)dst + 0x48) = 0x80;
    *(u8 *)((u8 *)dst + 0x49) = 0x80;
    *(u8 *)((u8 *)dst + 0x4A) = 0x80;
    *(u8 *)((u8 *)dst + 0x4B) = 0x80;
    *(s32 *)((u8 *)dst + 0x4C) = 0x3F800000;
    *(f32 *)((u8 *)dst + 0x30) = negativeHalfWidth;
    negativeHalfHeight = -halfHeight;
    *(f32 *)((u8 *)dst + 0x34) = negativeHalfHeight;
    *(s32 *)((u8 *)dst + 0x38) = 0;
    *(s32 *)((u8 *)dst + 0x3C) = 0x3F800000;
    *(s32 *)((u8 *)dst + 0x50) = 0;
    *(f32 *)((u8 *)dst + 0x54) = vMax;

    *(u8 *)((u8 *)dst + 0x78) = 0x80;
    *(u8 *)((u8 *)dst + 0x79) = 0x80;
    *(u8 *)((u8 *)dst + 0x7A) = 0x80;
    *(u8 *)((u8 *)dst + 0x7B) = 0x80;
    *(s32 *)((u8 *)dst + 0x7C) = 0x3F800000;
    *(f32 *)((u8 *)dst + 0x60) = halfWidth;
    *(f32 *)((u8 *)dst + 0x64) = negativeHalfHeight;
    *(s32 *)((u8 *)dst + 0x68) = 0;
    *(s32 *)((u8 *)dst + 0x6C) = 0x3F800000;
    *(f32 *)((u8 *)dst + 0x80) = uMax;
    *(f32 *)((u8 *)dst + 0x84) = vMax;

    *(u8 *)((u8 *)dst + 0xA8) = 0x80;
    *(u8 *)((u8 *)dst + 0xA9) = 0x80;
    *(u8 *)((u8 *)dst + 0xAA) = 0x80;
    *(u8 *)((u8 *)dst + 0xAB) = 0x80;
    *(s32 *)((u8 *)dst + 0xAC) = 0x3F800000;
    *(f32 *)((u8 *)dst + 0x90) = halfWidth;
    *(f32 *)((u8 *)dst + 0x94) = halfHeight;
    *(s32 *)((u8 *)dst + 0x98) = 0;
    *(s32 *)((u8 *)dst + 0x9C) = 0x3F800000;
    *(f32 *)((u8 *)dst + 0xB0) = uMax;
    *(s32 *)((u8 *)dst + 0xB4) = 0;
    return 4;
}

typedef struct Vertex_001DA5E0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    u8 pad10[8];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
    f32 u;
    f32 v;
    u8 pad28[8];
} Vertex_001DA5E0;

s32 func_001DA5E0(s32 arg0, f32 x, f32 y, void *arg1, void *arg2) {
    f32 *scale = arg2;
    f32 width;
    f32 height;
    f32 halfWidth;
    f32 halfHeight;
    f32 z;
    Vertex_001DA5E0 *vertex;

    width = arg0 ? 256 : 120;
    height = arg0 ? 368 : 180;
    vertex = arg1;
    halfWidth = (scale ? width * scale[0] : width) / 2.0f;
    halfHeight = (scale ? height * scale[1] : height) / 2.0f;
    z = func_001F9A20(0);

    vertex[0].r = 0x80;
    vertex[0].g = 0x80;
    vertex[0].b = 0x80;
    vertex[0].a = 0x80;
    vertex[0].q = 1.0f;
    vertex[0].x = x - halfWidth;
    vertex[0].y = y - halfHeight;
    vertex[0].z = z;
    vertex[0].w = 1.0f;
    vertex[0].u = 0.0f;
    vertex[0].v = 0.0f;

    vertex[1].r = 0x80;
    vertex[1].g = 0x80;
    vertex[1].b = 0x80;
    vertex[1].a = 0x80;
    vertex[1].q = 1.0f;
    vertex[1].x = x - halfWidth;
    vertex[1].y = y + halfHeight;
    vertex[1].z = z;
    vertex[1].w = 1.0f;
    vertex[1].u = 0.0f;
    vertex[1].v = height / 512.0f;

    vertex[2].r = 0x80;
    vertex[2].g = 0x80;
    vertex[2].b = 0x80;
    vertex[2].a = 0x80;
    vertex[2].q = 1.0f;
    vertex[2].x = x + halfWidth;
    vertex[2].y = y + halfHeight;
    vertex[2].z = z;
    vertex[2].w = 1.0f;
    vertex[2].u = width / 512.0f;
    vertex[2].v = height / 512.0f;

    vertex[3].r = 0x80;
    vertex[3].g = 0x80;
    vertex[3].b = 0x80;
    vertex[3].a = 0x80;
    vertex[3].q = 1.0f;
    vertex[3].x = x + halfWidth;
    vertex[3].y = y - halfHeight;
    vertex[3].z = z;
    vertex[3].w = 1.0f;
    vertex[3].u = width / 512.0f;
    vertex[3].v = 0.0f;
    return 4;
}

void func_001DA7A0(s32 arg0, s32 arg1) {
    func_00209D30(func_001DA7F0(func_00209D20(), arg0, arg1));
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DA7F0);

typedef struct Packet_001DBC40 {
    u8 pad00[0x18];
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 pad1C[0x14];
} Packet_001DBC40;

typedef struct Data_001DBC40 {
    u8 pad00[0x40];
    u8 blue;
    u8 green;
    u8 red;
    u8 alpha;
    u8 pad44[0x34];
    Packet_001DBC40 *packets;
    u8 pad7C[5];
    s8 flags : 7;
    s8 update : 1;
    s16 count : 12;
    s16 unused : 4;
} Data_001DBC40;

s32 func_001DBC40(s32 arg0, s32 arg1, void *arg2) {
    s32 i;
    Data_001DBC40 *data = arg2;

    arg0 = func_001DA7F0(arg0, arg1, (s32)arg2);
    if (data->update) {
        for (i = 0; i < data->count; i++) {
            data->packets[i].red = data->red;
            data->packets[i].green = data->green;
            data->packets[i].blue = data->blue;
            data->packets[i].alpha = data->alpha;
        }
    }
    return arg0;
}

void func_001DBCF0(s32 arg0) {
    func_00209D30(func_001DBD30(func_00209D20(), arg0));
}

typedef struct {
    u8 pad_00[0x48];
    u8 data[0x30];
    s32 value;
    u8 pad_7C[6];
    s16 index : 12;
    s16 unused : 4;
} Params_001DBD30;

s32 func_00207AA0(s32, void *, s32, s32, s32, s32);

s32 func_001DBD30(s32 arg0, s32 arg1) {
    Params_001DBD30 *params = (Params_001DBD30 *)arg1;

    return func_00207AA0(arg0, params->data, params->index,
                        params->value, 0, 0);
}

typedef struct Vertex_001DBD50 {
    f32 x, y, z;
    u8 pad0C[0xC];
    u8 r, g, b, a;
    f32 q;
    u8 pad20[0x10];
} Vertex_001DBD50;

typedef struct Prim_001DBD50 {
    u16 flags;
    u16 kind;
    u32 pad;
    u64 value;
    u64 alpha;
    u64 tex0;
    u64 tex1;
    u64 clamp;
} Prim_001DBD50;

s32 func_002070F0(s32, s32, void *, s32, void *, s32, s32);
s32 func_00207AA0(s32, void *, s32, s32, s32, s32);

static inline void initPrim_001DBD50(s32 kind, void *prim) {
    ((Prim_001DBD50 *)prim)->kind = kind;
    ((Prim_001DBD50 *)prim)->flags = 0;
    ((Prim_001DBD50 *)prim)->value = 0;
    ((Prim_001DBD50 *)prim)->pad = 0;
}

void func_001DBD50(s32 arg0, f32 *position, f32 width, f32 height,
                   s32 arg2, u8 *color, s32 arg4) {
    void *scratchpad = (void *)0x70000000;
    Vertex_001DBD50 *vertices = (Vertex_001DBD50 *)((u8 *)scratchpad + 0x2000);
    s32 repeats = 2;
    s32 count;
    s32 original = arg0;
    Prim_001DBD50 prim;
    u8 *end;

    arg0 = func_00207FA0(arg0);
    do {
        vertices[0].r = 0x80;
        vertices[0].g = 0x80;
        vertices[0].b = 0x80;
        vertices[0].a = 0x80;
        if (color != NULL) {
            vertices[0].r = color[2];
            vertices[0].g = color[1];
            vertices[0].b = color[0];
            vertices[0].a = color[3];
        }
        vertices[0].q = 1.0f;
        vertices[0].x = position[0] - width;
        vertices[0].y = position[1];
        vertices[0].z = position[2] - height;
        vertices[1].x = position[0] + width;
        vertices[1].y = position[1];
        vertices[1].z = position[2] - height;
        vertices[2].x = position[0] + width;
        vertices[2].y = position[1];
        vertices[2].z = position[2] + height;
        vertices[3].x = position[0] - width;
        vertices[3].y = position[1];
        vertices[3].z = position[2] + height;
        vertices[4].x = position[0] - width;
        vertices[4].y = position[1];
        vertices[4].z = position[2] - height;
        count = func_002070F0(0, 5, vertices, 0xAA, scratchpad, 0, 0);
        func_00207230(NULL, count, vertices);
        if (arg4 != 0) {
            initPrim_001DBD50(5, &prim);
        } else {
            initPrim_001DBD50(0x402, &prim);
        }
        if (vertices[0].a < 0xFF) {
            func_002086D0(&prim, func_00208D00(arg2));
        }
        arg0 = func_00207AA0(arg0, &prim, count, (s32)vertices, 0, 0);
        if (arg4 != 0 || repeats-- <= 0) {
            break;
        }
        width -= 0.2f;
        height -= 0.2f;
    } while (1);
    end = func_00207500();
    func_00208030(arg0, original, (s32)end, func_00205D10(position, 0.0f));
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DBFE0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DC560);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DC790);

void func_001DCC90(void *arg0) {
    *(s32 *)arg0 = 0;
    ((u8 *)arg0)[6] = 0;
    ((u8 *)arg0)[5] = 0;
    ((u8 *)arg0)[4] = 0;
    ((u8 *)arg0)[7] = 0;
    ((u8 *)arg0)[0xA] = 0;
    ((u8 *)arg0)[9] = 0;
    ((u8 *)arg0)[8] = 0;
    ((u8 *)arg0)[0xB] = 0;
    ((u8 *)arg0)[0xE] = 0;
    ((u8 *)arg0)[0xD] = 0;
    ((u8 *)arg0)[0xC] = 0;
    ((u8 *)arg0)[0xF] = 0;
    ((u8 *)arg0)[0x12] = 0;
    ((u8 *)arg0)[0x11] = 0;
    ((u8 *)arg0)[0x10] = 0;
    ((u8 *)arg0)[0x13] = 0;
    ((u8 *)arg0)[0x16] = 0;
    ((u8 *)arg0)[0x17] = 0;
    ((u8 *)arg0)[0x18] = 0;
    ((u8 *)arg0)[0x19] = 0;
    ((u8 *)arg0)[0x1A] = 0x80;
    *(s16 *)((u8 *)arg0 + 0x14) = 0;
}

void *func_001DCD00(s32 arg0, s32 arg1) {
    if ((arg0 < 0) || (arg0 >= 7) || (arg1 < 0) || (arg1 >= 7)) {
        return NULL;
    }
    return (arg0 * 0x1C) + (D_00318E60 + (arg1 * 0xC4));
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DCD70);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DD0E0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DD130);

void func_001DD2D0(u8 *, s32);
extern u8 D_00318E60[];

static inline u8 *cell_001DD220(s32 x, s32 y, u8 *cell) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return cell;
}

void func_001DD220(void) {
    s32 var_s0;
    s32 var_s1;
    u8 *var_a0;
    u8 *var_s2;
    u8 *var_s3;

    var_s3 = D_00318E60;
    var_s1 = 0;
    do {
        var_s0 = 0;
        var_s2 = var_s3;
        do {
            var_a0 = cell_001DD220(var_s0, var_s1, var_s2);
            func_001DD2D0(var_a0, *(s32 *)var_a0);
            var_s0 += 1;
            var_s2 += 0x1C;
        } while (var_s0 < 7);
        var_s1 += 1;
        var_s3 += 0xC4;
    } while (var_s1 < 7);
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DD2D0);

s32 func_001DD890(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *first;
    u8 *second;
    s32 result;

    first = (u8 *)func_001DF540(arg0, arg1);
    second = (u8 *)func_001DF540(arg2, arg3);
    result = 0;
    if (first == second) {
        second = 0;
    }
    if (first != 0 && second != 0) {
        result |= func_001DDAC0(arg0, arg1, second[0x40], second[0x41]);
        result |= func_001DDAC0(arg2, arg3, first[0x40], first[0x41]);
    } else {
        if (first != 0) {
            result |= func_001DD990(arg0, arg1);
        }
        if (second != 0) {
            result |= func_001DD990(arg2, arg3);
        }
    }
    return result;
}

typedef struct Flags_001DD990 {
    s8 unused : 1;
    s8 facing : 1;
    s8 remaining : 6;
} Flags_001DD990;

typedef struct State_001DD990 {
    u8 pad00[0x30];
    s32 angle;
    u8 pad34[0x23];
    Flags_001DD990 flags;
} State_001DD990;

s32 func_001DD990(s32 arg0, s32 arg1) {
    State_001DD990 *state;
    s32 result;
    s32 target;
    s32 delta;

    state = (State_001DD990 *)func_001DF540();
    result = 0;
    if (state != 0) {
        target = state->flags.facing ? 0x8000 : 0;
        if (state->angle != target) {
            delta = (target - state->angle) % 0x10000;
            if (delta < -0x7FFF) {
                delta += 0x10000;
            } else if (delta > 0x8000) {
                delta -= 0x10000;
            }
            if (delta != 0) {
                if (delta > 0) {
                    if (delta > 0x800) {
                        delta = 0x800;
                    }
                    state->angle += delta;
                } else {
                    if (delta < -0x800) {
                        delta = -0x800;
                    }
                    state->angle += delta;
                }
                state->angle = (state->angle + 0x10000) % 0x10000;
                if (state->angle > 0x8000) {
                    state->angle -= 0x10000;
                }
            }
        }
        result = 1;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DDAC0);

void func_001E7F70(s32, s32, s32);
void func_001E8780(s32, s32, s32, s32);
extern u8 D_002BF080[];

static inline u8 *lookup_001DDD80(s32 index) {
    if (index < 0 || index >= 0x356) {
        return NULL;
    }
    return D_002BF080 + index * 0x14;
}

void func_001DDD80(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;
    u8 *var_v1;

    func_001F3910(0, 0x26C, 0, arg3);
    func_001E7F70(6, 0, 0);
    func_001E7F70(0, 0, 0);
    var_s0 = 0;
    var_s1 = 0;
    do {
        var_a0 = func_002159D0(var_s0, func_002158B0(var_s0));
        if (var_a0 == 0x29F) {
            var_a0 = 0x3E7;
        }
        var_v1 = lookup_001DDD80(var_a0);
        if (var_v1 != NULL) {
            func_001E8780(var_s0 + 5, -1, (*var_v1 & 0x1F) + var_s1, 1);
        }
        var_s0 += 1;
        var_s1 += 0x64;
    } while (var_s0 < 2);
}

extern u8 D_002CEE5C[][7][7];
void *func_002145E0(s32);

typedef struct {
    u8 pad[0xFEA3];
    u8 maps[5][7][7];
} Maps_001DDE80;

void func_001DDE80(s32 arg0) {
    s32 y;
    s32 x;
    Maps_001DDE80 *maps;
    extern s32 func_001E2220();

    if (arg0 >= 0 && arg0 < 0x2E) {
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 7; x++) {
                func_001E2220(x, y, D_002CEE5C[arg0][y][x]);
            }
        }
    } else if (arg0 < 0x33) {
        maps = func_002145E0(0);
        arg0 -= 0x2E;
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 7; x++) {
                func_001E2220(x, y, maps->maps[arg0][y][x]);
            }
        }
    } else if (arg0 < 0x38) {
        maps = func_002145E0(1);
        arg0 -= 0x33;
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 7; x++) {
                func_001E2220(x, y, maps->maps[arg0][y][x]);
            }
        }
    }
}

s32 func_001DE020(s32 arg0) {
    return arg0 == 1 ? 1
         : arg0 == 2 ? 1
         : arg0 == 3 ? 2
         : arg0 == 4 ? 2
         : arg0 == 5 ? 3
         : arg0;
}

s32 func_001DE090(s64 arg0, s32 arg1) {
    return arg0 > 0 ? (s32)arg0 + 5 : arg1;
}
