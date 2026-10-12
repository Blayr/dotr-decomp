#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100000);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100008);

INCLUDE_ASM("asm/nonmatchings/main_000", func_001000B8);

INCLUDE_ASM("asm/nonmatchings/main_000", func_001000C0);

INCLUDE_ASM("asm/nonmatchings/main_000", func_001000D0);

s32 func_001001D0(void) {
    func_001FEB80();
    if (func_00209510(0, 0xA, 0x31, 0x600000, 0x780000, 0x180000, 0x4000000) == 0) {
        return 0;
    }
    func_00209E90(0, 0, 0, 0);
    func_001A8520(0xA, 0, 0, 0, 0x400, 0x400);
    func_002007D0();
    func_002031F0();
    func_00217410();
    func_001E7A60();
    func_001F74B0();
    func_001FCC20();
    func_001A6C80();
    func_001F3700();
    func_00203CD0();
    func_002032C0(0, 0xC, 1);
    func_002032C0(1, 0xC, 1);
    if (func_001F74C0(0) == 0) {
        return 0;
    }
    func_001FD2B0();
    func_00214290();
    func_001AD960();
    func_001E4E90();
    if (func_00100350() == 0) {
        return 0;
    }
    func_001A89C0(0x24, 0);
    func_001FCC70(1, 0, 1, 0, 0x5A, 0);
    func_001FD0B0(1);
    func_001FD130(1, 1);
    func_00100780();
    return 1;
}

typedef struct {
    s32 type;
    s32 data;
    s32 arg1;
    s32 arg2;
    u8 position[0x10];
    u8 rotation[0x10];
} Entry_00100350;

s32 func_001E1E70(s32, s32, s32, s32);
s32 func_001E7B20(s32);
extern Entry_00100350 D_0028A880[];

s32 func_00100350(void) {
    s32 index;

    index = 0;
    do {
        if (func_001E7B20(index) == 0) {
            return 0;
        }
        func_001F22B0(index, D_0028A880[index].position);
        func_001F2430(index, D_0028A880[index].rotation);
        func_001E7E70(index, D_0028A880[index].type, D_0028A880[index].data);
        if (D_0028A880[index].type == 5) {
            func_001DF580(index - 0x1E, D_0028A880[index].arg1, D_0028A880[index].arg2,
                         func_001DE130(D_0028A880[index].data), 1);
            func_001E1E70(-1, index, 4, 1);
            func_001E1D70(-1, index, 0, 0xFF);
            func_001E1C10(-1, index, 1, 0);
        } else if (D_0028A880[index].type == 4) {
            s32 mode;
            s32 handle;

            mode = (index - 0x14 < 5) ? 0 : 1;
            handle = func_001DE130(D_0028A880[index].data);
            func_001DF580(mode, D_0028A880[index].arg1, D_0028A880[index].arg2, handle, 0);
            func_001E1E70(-1, index, 4, 1);
            func_001E1D70(-1, index, 0, 0xFF);
            func_001E1C10(-1, index, 1, 0);
        }
        index++;
    } while (index < 0x54);
    return 1;
}

void func_001004C0(void) {
    s32 i;

    func_001F7720(0);
    i = 0;
    do {
        func_001E7DE0(i);
        i += 1;
    } while (i < 0x54);
    func_00209870();
    func_002032A0();
}

void func_00100520(void) {
    func_00209F60(func_001F73C0);
    for (;;) {
        if (func_001AAF60(1) == 1) {
            func_00100780();
        }
        func_00100560();
    }
}

void func_00100560(void) {
    func_00203320();
    func_00217550();
    func_001FF3D0();
    func_001AA260();
    func_001FA220(-1, -1);
    func_001DD220();
    func_00100850();
    func_001A8750(func_002099D0());
    if (func_001A87A0() != 0) {
        func_001A8750(1);
    } else {
        func_001A8770(1);
    }
    func_00100820();
    func_001A8730();
    func_00203840();
}

void func_00100610(s32 arg0) {
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;

    func_00209D60(&sp20, &sp24);
    func_00209EF0(0, &sp28, &sp2C, NULL);
    *(s64 *)0x12000000 = ((s64) (arg0 ? 0x7F : 0xFF) << 8) | 0x23;
    *(s64 *)0x12000090 = ((s64) sp2C << 15) | ((s64) (sp28 >> 5) | ((s64) (sp20 >> 6) << 9));
    *(s64 *)0x120000A0 = ((s64) (sp24 - 1) << 44) | (((s64) ((sp20 * 4) - 1) << 32) | 0x0183227C);
    *(s64 *)0x12000070 = ((s64) sp2C << 15) | ((s64) (sp28 >> 5) | ((s64) (sp20 >> 6) << 9));
    *(s64 *)0x12000080 = ((s64) (sp24 - 1) << 44) | (((s64) ((sp20 * 4) - 1) << 32) | 0x0183327C);
    *(s64 *)0x120000D0 = 0;
}

void func_00100780(void) {
    extern s32 func_001F2980(s32);
    s32 i;
    s32 type;

    for (i = 0; i < 0x54; i++) {
        type = func_001F2980(i);
        if (func_001F1240(i) == 0) {
            continue;
        }
        if (type == 4 || type == 5) {
            if (func_001DF540(-1, i) == 0) {
                continue;
            }
        }
        func_001E8780(i, -1, -1, 1);
    }
}

s32 func_00100820(void) {
    func_0019A5C8();
    func_002038F0();
    func_001A86F0();
    return 0;
}

void func_001A9590(void);
void func_001A9800(void);
void func_001A98B0(void);
void func_001F40D0(s32);

typedef union {
    f32 value;
    struct {
        u8 r, g, b, a;
    } color;
} Color_00100850;

void func_00100850(void) {
    extern s32 func_001A8690();
    extern s32 func_00202E00();
    extern s32 func_00208530();
    extern s32 func_00208D00();
    extern Color_00100850 D_0028B840;
    Color_00100850 color;
    s32 initial;
    s32 allocation;
    s32 i;
    s32 level;

    initial = func_00209D20();
    func_00202E00(0, 0);
    func_001EE4A0(0);
    func_00209D30(func_00213FC0(func_001AE5A0(func_001E5590(func_001F8A30(func_002085E0(func_00208530(func_0020A0B0(initial, 1), 1), 1), 0)))));
    func_002085A0(2);
    func_001A9590();
    func_001EE4A0(0);
    func_00208490(0);
    func_002085A0(3);
    if (func_001F5240(0, -1) == 0) {
        if ((func_001F5240(1, -1) == 0) && (func_001F5240(2, -1) == 0)) {
            func_00202D60(4, -1);
        }
    }
    if (func_001F5240(0, -1) == 0) {
        if (func_001F5240(1, -1) == 0) {
            func_00202D60(5, -1);
            func_00202D60(8, -1);
        }
    }
    if (func_001F5240(1, -1) == 0) {
        if (func_001F5240(2, -1) == 0) {
            func_00202D60(6, -1);
        }
    }
    allocation = 0x3BC0;
    allocation += func_00202E00(allocation, 2);
    allocation += func_00202AB0(4, allocation);
    allocation += func_00202AB0(5, allocation);
    allocation += func_00202AB0(6, allocation);
    func_00202AB0(8, allocation);
    func_00208460();
    func_00207360();
    func_001AEE80();
    func_001EDF90(-1);
    func_001CE400();
    i = 0;
    do {
        func_001F2FF0(i, 0);
        i += 1;
    } while (i < 0x54);
    func_001F40D0(0);
    func_001F40D0(1);
    func_001F40D0(2);
    func_001CD6E0();
    func_002073A0();
    func_00208490(1);
    func_001A9800();
    func_002085A0(2);
    if ((level = func_001A8690()) > 0) {
        s32 image = (s32)func_00208D00(0);
        color = D_0028B840;
        color.color.a = level << 4;
        func_00208090(0, 0, 1, image, (s32)&color);
    }
    func_001FCDA0();
    func_002085A0(3);
    func_001A98B0();
}

typedef struct Vec4_00100B00 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00100B00;

void func_002058D0(void *, void *, s32, s32, s32);
extern f32 D_0030FF00[];

void func_00100B00(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5) {
    Vec4_00100B00 vertices[3];

    vertices[0] = *(Vec4_00100B00 *)arg0;
    vertices[1] = *(Vec4_00100B00 *)arg1;
    vertices[2] = *(Vec4_00100B00 *)arg2;
    func_002058D0(vertices, D_0030FF00, arg3, arg4, arg5);
}

typedef struct Vec4_00100BA0 {
    f32 x, y, z, w;
} Vec4_00100BA0;

void func_002058D0(void *, void *, s32, s32, s32);
extern f32 D_0030FF00[];

void func_00100BA0(void *arg0, void *arg1, void *arg2, void *arg3,
                   s32 arg4, s32 arg5, s32 arg6) {
    Vec4_00100BA0 vectors[4];

    vectors[0] = *(Vec4_00100BA0 *)arg0;
    vectors[1] = *(Vec4_00100BA0 *)arg1;
    vectors[2] = *(Vec4_00100BA0 *)arg2;
    vectors[3] = *(Vec4_00100BA0 *)arg3;
    func_002058D0(vectors, D_0030FF00, arg4, arg5, arg6);
}

typedef struct {
    u16 x : 14;
    u16 flags_x : 2;
    u16 y : 14;
    u16 flags_y : 2;
} PackedCoordinates_00100C60;

void func_00100C60(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 var_a1;
    s32 var_a2;

    var_a1 = ((s32) ((u16 *) arg1)[0] >> 4) - 0x6C0 + arg2;
    var_a2 = ((s32) ((u16 *) arg1)[1] >> 4) - 0x720 + arg3;
    if (var_a1 <= 0) {
        var_a1 = 1;
    } else if (var_a1 > 0x27F) {
        var_a1 = 0x27F;
    }
    if (var_a2 <= 0) {
        var_a2 = 1;
    } else if (var_a2 > 0x1BF) {
        var_a2 = 0x1BF;
    }
    ((PackedCoordinates_00100C60 *) arg0)->x = var_a1 << 4;
    ((PackedCoordinates_00100C60 *) arg0)->y = var_a2 << 4;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3_00100D00;


s32 func_00100D00(s32 arg0) {
    Vec3_00100D00 v;
    s32 ret;

    ret = 1;
    func_001F5F90(arg0, &v);
    if (v.z < 0.0f) {
        ret = -1;
    }
    return ret;
}

f32 func_00100D50(s32 arg0, s32 arg1, s32 arg2) {
    f32 temp_f20;

    temp_f20 = func_001A6B70(6.2831855f * ((f32) ((s32) ((arg1 - arg0) << 0x10) / (s32) (arg1 * 5)) / 65536.0f));
    return 1.0f - func_001A6C48(temp_f20 / func_001A6B70(1.2566179f), (f32) arg2);
}

typedef struct {
    u32 values[4];
} Config_00100E00;

void func_0020CB90(s32, u32 *);
extern Config_00100E00 D_0028C210;

void func_00100E00(s32 arg0, s32 arg1, s32 arg2) {
    Config_00100E00 values;
    u32 *words = (u32 *)&values;

    values = D_0028C210;
    arg1 &= 0xFFFF;
    words[arg2] = arg1;
    func_0020CB90(arg0, words);
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
typedef struct {
    unsigned int values[4];
} Config_00100E00;

extern Config_00100E00 D_0028C210;
#endif


void func_0020BBB0(void *);
void func_0020CB90(s32, u32 *);

void func_00100E40(void *matrix, f32 *vector) {
    Config_00100E00 rotationZ;
    Config_00100E00 rotationY;
    f32 xSquared;
    s64 angleZ;
    s64 angleY;

    func_0020BBB0(matrix);
    angleZ = func_001A22C0(65536.0f * (func_001A6C18(vector[1], vector[0]) / 6.2831855f));
    rotationZ = D_0028C210;
    ((s32 *)&rotationZ)[2] = angleZ & 0xFFFF;
    func_0020CB90((s32)matrix, (u32 *)&rotationZ);
    xSquared = func_001A6C48(vector[0], 2.0f);
    angleY = func_001A22C0(65536.0f * (func_001A6C18(func_001A6C60(xSquared + func_001A6C48(vector[1], 2.0f)), vector[2]) / 6.2831855f));
    rotationY = D_0028C210;
    ((s32 *)&rotationY)[1] = angleY & 0xFFFF;
    func_0020CB90((s32)matrix, (u32 *)&rotationY);
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00100F60);

f32 func_00100FF0(f32 fparg0, f32 fparg1, f32 fparg2) {
    f32 var_f0;

    var_f0 = 1.0f;
    if (!(fparg0 <= fparg2)) {
        var_f0 = (fparg0 - fparg1) / (fparg2 - fparg1);
    }
    return var_f0;
}

f32 func_00101020(f32 fparg0, f32 fparg1) {
    f32 var_f0;

    var_f0 = 1.0f;
    if (fparg0 < fparg1) {
        var_f0 = fparg0 / fparg1;
    }
    return var_f0;
}

s32 func_00101050(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 < arg1) {
        arg0 = arg1;
    } else if (arg2 < arg0) {
        arg0 = arg2;
    }
    return arg0;
}

void func_001878E0(void *, void *, void *);
void func_00187B48(void *, void *, f32);
extern f32 D_0028BC10[4][32][3];

static inline void rotate_00101080(void *matrix, s32 angle, s32 axis) {
    Config_00100E00 values;
    u32 *words = (u32 *)&values;

    values = D_0028C210;
    angle &= 0xFFFF;
    words[axis] = angle;
    func_0020CB90((s32)matrix, words);
}

void func_00101080(f32 *vector, f32 scale) {
    f32 matrix[16];
    f32 *value;
    f32 sign;

    value = &D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
    sign = 2.0f * (f32)((func_0019A5C8() >> 23) % 2) - 1.0f;
    vector[0] = sign * *value;

    value = &D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
    sign = 2.0f * (f32)((func_0019A5C8() >> 23) % 2) - 1.0f;
    vector[1] = sign * *value;

    value = &D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
    sign = 2.0f * (f32)((func_0019A5C8() >> 23) % 2) - 1.0f;
    vector[2] = sign * *value;
    vector[3] = 1.0f;
    func_00187B48(vector, vector, scale);
    func_0020BBB0(matrix);
    rotate_00101080(matrix, (((func_0019A5C8() >> 23) % 256) << 16) >> 8, 0);
    rotate_00101080(matrix, (((func_0019A5C8() >> 23) % 256) << 16) >> 8, 1);
    rotate_00101080(matrix, (((func_0019A5C8() >> 23) % 256) << 16) >> 8, 2);
    func_001878E0(vector, matrix, vector);
}

typedef struct Point_00101430 {
    u16 x;
    u16 y;
} Point_00101430;

typedef struct Vec4_00101430 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00101430;

s32 func_00101430(void *arg0, void *arg1, void *arg2) {
    Point_00101430 *a = arg0;
    Point_00101430 *b = arg1;
    Point_00101430 *c = arg2;
    s32 result = 1;
    f32 normal[4];
    Vec4_00101430 verts[3];

    verts[0].x = (u32)a->x;
    verts[0].y = (u32)a->y;
    verts[0].z = 0.0f;
    verts[0].w = 1.0f;
    verts[1].x = (u32)b->x;
    verts[1].y = (u32)b->y;
    verts[1].z = 0.0f;
    verts[1].w = 1.0f;
    verts[2].x = (u32)c->x;
    verts[2].y = (u32)c->y;
    verts[2].z = 0.0f;
    verts[2].w = 1.0f;
    func_00205E70(3, verts, normal);
    if (!(normal[2] < 0.0f)) {
        result = 0;
    }
    return result;
}

s32 func_00101600(void *arg0) {
    u16 x;
    u16 y;

    x = ((u16 *)arg0)[0];
    if ((f32)x < 22528.0f) {
        return 0;
    }
    if (!((f32)x <= 43008.0f)) {
        return 0;
    }
    y = ((u16 *)arg0)[1];
    if ((f32)y < 25600.0f) {
        return 0;
    }
    if ((f32)y > 39936.0f) {
        return 0;
    }
    return 1;
}

s32 func_00101770(void *arg0) {
    u16 *p = (u16 *)arg0;
    if ((f32)(u32)p[0] < 27648.0f) return 0;
    if ((f32)(u32)p[0] > 37888.0f) return 0;
    if ((f32)(u32)p[1] < 29184.0f) return 0;
    if ((f32)(u32)p[1] > 36352.0f) return 0;
    return 1;
}

f32 func_001018E0(f32 fparg0, f32 fparg1) {
    return (fparg0 / (fparg1 / 256.0f)) * (func_001F9A20(0) / 800.0f);
}

void func_00101940(f32 *arg0, s32 *arg1) {
    arg1[0] = (u16) func_001A22C0(65536.0f * (func_001A6C18(func_001A6C60(arg0[0] * arg0[0] + arg0[2] * arg0[2]), arg0[1]) / 6.2831855f));
    arg1[1] = (u16) func_001A22C0(65536.0f * (func_001A6C18(arg0[0], arg0[2]) / 6.2831855f));
    arg1[2] = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00101A00);

void func_00101AD0(s8 *arg0, s8 arg1, s8 arg2, s8 arg3) {
    arg0[2] = arg1;
    arg0[0] = arg1;
    arg0[1] = arg2;
    arg0[3] = arg3;
}

typedef struct Timer_00101AF0 {
    u8 count;
    u8 delay;
} Timer_00101AF0;

s32 func_00101AF0(void *arg0) {
    Timer_00101AF0 *timer = arg0;
    u8 temp_v0;
    u8 temp_v1;

    temp_v1 = timer->count;
    if (temp_v1 == 0) {
        return 0;
    }
    temp_v0 = timer->delay;
    if (temp_v0 != 0) {
        timer->delay = (u8) (temp_v0 - 1);
        return 0;
    }
    timer->count = (u8) (temp_v1 - 1);
    return 1;
}

void func_00101B40(void *arg0, s8 arg1, s8 arg2) {
    ((s8 *)arg0)[2] = arg1;
    ((s8 *)arg0)[0] = arg1;
    ((s8 *)arg0)[1] = arg2;
}

typedef struct Counter_00101B50 {
    u8 count;
    u8 delay;
} Counter_00101B50;

s32 func_00101B50(void *arg0) {
    Counter_00101B50 *counter = arg0;

    if (counter->count == 0) {
        return 0;
    }
    if (counter->delay != 0) {
        counter->delay--;
        return 0;
    }
    counter->count--;
    return 1;
}

void func_00101BA0(void *arg0, s32 arg1) {
    u8 temp_a0;

    temp_a0 = *((u8 *)arg0 + 5);
    switch (temp_a0) {
    case 0:
        return;
    case 1:
        func_001F5620(func_001F53A0(temp_a0), *((u8 *)arg0 + 6), arg1);
        return;
    case 2:
        func_001F5620(func_001F5380(temp_a0), *((u8 *)arg0 + 6), arg1);
        return;
    }
}

s32 func_00101C30(u8 *arg0, s32 arg1, s32 arg2) {
    s32 offset;
    s32 i;

    i = 0;
    if (i < arg2) {
        offset = 0;
        do {
            if (arg0[offset] == 0) {
                return i;
            }
            i++;
            offset += arg1;
        } while (i < arg2);
    }
    return -1;
}

void func_00101C80(void *arg0, void *arg1) {
    s8 *out = (s8 *)arg1;

    switch (((u8 *)arg0)[5]) {
    case 1:
        out[0] = 0;
        out[1] = 1;
        out[2] = 0;
        out[3] = 1;
        break;
    case 2:
        out[0] = 0;
        out[1] = 2;
        out[2] = 0;
        out[3] = 1;
        break;
    case 3:
        out[0] = 1;
        out[1] = 0;
        out[2] = 0;
        out[3] = 1;
        break;
    case 4:
        out[0] = 2;
        out[1] = 0;
        out[2] = 0;
        out[3] = 1;
        break;
    }
}

typedef struct Coord_00101D20 {
    u16 val : 14;
    u16 hi : 2;
} Coord_00101D20;

typedef struct Vert_00101D20 {
    u8 pad0[8];
    Coord_00101D20 x;
    Coord_00101D20 y;
    u8 padC[4];
} Vert_00101D20;

typedef struct Sprite_00101D20 {
    u16 pad0;
    u16 flags;
    u8 pad4[0xC];
    Vert_00101D20 v[4];
} Sprite_00101D20;

void func_00101D20(void *arg0, void *arg1, void *arg2) {
    Sprite_00101D20 *dst = arg0;
    s32 *src = arg1;
    u8 sp4C[4];

    dst->flags |= 0x800;
    dst->v[0].x.val = src[2] << 4;
    dst->v[0].y.val = src[4] << 4;
    dst->v[1].x.val = src[3] << 4;
    dst->v[1].y.val = src[4] << 4;
    dst->v[2].x.val = src[2] << 4;
    dst->v[2].y.val = src[5] << 4;
    dst->v[3].x.val = src[3] << 4;
    dst->v[3].y.val = src[5] << 4;
    func_00208CB0(arg0, 0xA | ((s64)src[2] << 4) | ((s64)(src[3] - 1) << 14) | ((s64)src[4] << 24) |
                            ((s64)(src[5] - 1) << 34));
    func_00208700(arg0, arg2, 1);
    func_00101C80(arg1, sp4C);
    func_002086D0(arg0, (s64)sp4C[0] | ((s64)sp4C[1] << 2) | ((s64)sp4C[2] << 4) | ((s64)sp4C[3] << 6));
}

typedef struct Coord_00101EE0 {
    u16 val : 14;
    u16 hi : 2;
} Coord_00101EE0;

typedef struct Vert_00101EE0 {
    u8 pad0[8];
    Coord_00101EE0 x;
    Coord_00101EE0 y;
    u8 padC[0xC];
} Vert_00101EE0;

typedef struct Sprite_00101EE0 {
    u16 pad0;
    u16 flags;
    u8 pad4[0xC];
    Vert_00101EE0 v[4];
} Sprite_00101EE0;

void func_00101EE0(void *arg0, void *arg1, void *arg2) {
    Sprite_00101EE0 *dst = arg0;
    s32 *src = arg1;
    u8 sp4C[4];

    dst->flags |= 0x800;
    dst->v[0].x.val = src[2] << 4;
    dst->v[0].y.val = src[4] << 4;
    dst->v[1].x.val = src[3] << 4;
    dst->v[1].y.val = src[4] << 4;
    dst->v[2].x.val = src[2] << 4;
    dst->v[2].y.val = src[5] << 4;
    dst->v[3].x.val = src[3] << 4;
    dst->v[3].y.val = src[5] << 4;
    func_00208CB0(arg0, 0xA | ((s64)src[2] << 4) | ((s64)(src[3] - 1) << 14) | ((s64)src[4] << 24) |
                            ((s64)(src[5] - 1) << 34));
    func_00208700(arg0, arg2, 1);
    if (((u8 *)arg1)[5] != 0) {
        func_00101C80(arg1, sp4C);
        func_002086D0(arg0, (s64)sp4C[0] | ((s64)sp4C[1] << 2) | ((s64)sp4C[2] << 4) | ((s64)sp4C[3] << 6));
    }
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_001020B0);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00102210);

INCLUDE_ASM("asm/nonmatchings/main_000", func_001022D0);

void func_00102330(s8 *arg0, s32 arg1) {
    s8 *var_s0;
    s32 var_s1;

    var_s0 = arg0;
    for (var_s1 = 0; var_s1 < arg1; var_s1 += 1) {
        *var_s0 = (s8) (func_0019A5C8() >> 4);
        var_s0 += 1;
    }
}

void func_00102390(s32 n, f32 *x, f32 *y, f32 *y2) {
    f32 h[8];
    f32 d[8];
    s32 i;
    f32 m;

    y2[n - 1] = 0.0f;
    y2[0] = 0.0f;
    for (i = 0; i < n - 1; i++) {
        h[i] = x[i + 1] - x[i];
        d[i + 1] = (y[i + 1] - y[i]) / h[i];
    }
    y2[1] = (d[2] - d[1]) - h[0] * y2[0];
    d[1] = 2.0f * (x[2] - x[0]);
    for (i = 1; i < n - 2; i++) {
        m = h[i] / d[i];
        y2[i + 1] = (d[i + 2] - d[i + 1]) - m * y2[i];
        d[i + 1] = 2.0f * (x[i + 2] - x[i]) - m * h[i];
    }
    y2[n - 2] -= h[n - 2] * y2[n - 1];
    for (i = n - 2; i > 0; i--) {
        y2[i] = (y2[i] - h[i] * y2[i + 1]) / d[i];
    }
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00102550);

INCLUDE_ASM("asm/nonmatchings/main_000", func_00102A50);

typedef struct Vec3_00102CB0 {
    f32 x, y, z;
} Vec3_00102CB0;

typedef struct Curve_00102CB0 {
    s32 count;
    f32 radius;
    f32 angle;
    f32 angleStep;
    Vec3_00102CB0 start;
    Vec3_00102CB0 end;
    Vec3_00102CB0 *points;
} Curve_00102CB0;

extern void func_0020C630(void *, s32 *);

void func_00102CB0(void *arg0) {
    extern s32 func_001A22C0(f32);
    f32 matrix[16];
    Vec3_00102CB0 delta;
    Vec3_00102CB0 point;
    s32 angles[3];
    Vec3_00102CB0 *p;
    Vec3_00102CB0 *end;
    s32 i;
    f32 step;
    f32 angle;
    f32 horizontalDistance;
    Curve_00102CB0 *curve = arg0;

    p = curve->points;
    *p = curve->start;
    end = p + curve->count;
    *end = curve->end;
    p++;
    delta.x = curve->end.x - curve->start.x;
    delta.y = curve->end.y - curve->start.y;
    delta.z = curve->end.z - curve->start.z;
    step = func_0020D0E0(&delta.x) / (f32)curve->count;
    horizontalDistance = func_001A6C60(delta.x * delta.x + delta.z * delta.z);
    angles[0] = (u16)func_001A22C0(65536.0f * (func_001A6C18(horizontalDistance, delta.y) / 6.2831855f));
    angles[1] = (u16)func_001A22C0(65536.0f * (func_001A6C18(delta.x, delta.z) / 6.2831855f));
    angles[2] = 0;
    func_0020C630(matrix, angles);
    for (i = 1; i < curve->count; i++) {
        angle = (3.1415927f * (curve->angle + curve->angleStep * (f32)i)) / 180.0f;
        point.x = curve->radius * func_001A6898(angle);
        point.z = curve->radius * func_001A6A88(angle);
        point.y = step * (f32)i;
        func_0020CDD0(p, matrix, &point);
        p->x += curve->start.x;
        p->y += curve->start.y;
        p->z += curve->start.z;
        p++;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_000", func_00102F20);
