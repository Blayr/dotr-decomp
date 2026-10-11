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
    func_001DF1E0();
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

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D90E0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D91B0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D9420);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D95F0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D9820);

void func_001D99F0(void) {
    func_00209D30(func_001D9A20(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D9A20);

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

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D9ED0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D9EE0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D9EF0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001D9F00);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DA2B0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DA4C0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DA5E0);

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

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DBD50);

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

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DD890);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DD990);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DDAC0);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DDD80);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DDE80);

INCLUDE_ASM("asm/nonmatchings/main_043", func_001DE020);

s32 func_001DE090(s64 arg0, s32 arg1) {
    return arg0 > 0 ? (s32)arg0 + 5 : arg1;
}
