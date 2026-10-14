#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020CB20);

void func_0020CB90(s32 arg0, u32 *arg1) {
    extern void func_0020C630();
    f32 matrix[4][4];

    func_0020C630(matrix, arg1);
    func_0020BC00(arg0, matrix);
}

void func_0020CBD0(s32 arg0) {
    extern void func_0020C750();
    f32 matrix[4][4];

    func_0020C750(matrix);
    func_0020BC00(arg0, matrix);
}

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020CC10);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020CDD0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020CF00);

void func_0020D070(f32 *arg0) {
    f32 length;

    length = func_001A6C60(arg0[0] * arg0[0] + arg0[1] * arg0[1] + arg0[2] * arg0[2]);
    arg0[0] /= length;
    arg0[1] /= length;
    arg0[2] /= length;
    arg0[3] = arg0[3];
}

f32 func_0020D0E0(f32 *arg0) {
    return func_001A6C60(arg0[0] * arg0[0] + arg0[1] * arg0[1] + arg0[2] * arg0[2]);
}

f32 func_0020D100(f32 *arg0, f32 *arg1) {
    f32 x = arg0[0] - arg1[0];
    f32 y = arg0[1] - arg1[1];
    f32 z = arg0[2] - arg1[2];

    return func_001A6C60(x * x + y * y + z * z);
}

void func_0020D140(f32 *arg0, f32 *arg1, f32 *arg2) {
    arg0[0] = arg1[1] * arg2[2] - arg1[2] * arg2[1];
    arg0[1] = arg1[2] * arg2[0] - arg1[0] * arg2[2];
    arg0[2] = arg1[0] * arg2[1] - arg1[1] * arg2[0];
    arg0[3] = arg1[3];
}

f32 func_0020D1A0(f32 *arg0, f32 *arg1) {
    return arg0[0] * arg1[0] + arg0[1] * arg1[1] + arg0[2] * arg1[2];
}

s64 func_0020D1D0(s32 arg0, s32 arg1, f32 weight0, f32 weight1) {
    extern s64 func_001A22C0(s32, s32, f32);
    s32 end = arg1 & 0xFFFF;
    s32 start = arg0 & 0xFFFF;
    s32 delta = end - start;

    if (delta > 0x8000) {
        end -= 0x10000;
    } else if (delta < -0x8000) {
        end += 0x10000;
    }

    return func_001A22C0(arg0, arg1, (f32)start * weight0 + (f32)end * weight1 + 0.5f);
}

void func_0020D240(s32 *out, s32 *from, s32 *to, f32 weight0, f32 weight1) {
    s32 end[2][3];
    s32 diff[2][3];
    s32 start[3];
    f32 sinX;
    f32 cosX;
    f32 sinZ;
    f32 cosZ;
    f32 cosY;
    f32 cosY2;
    s32 d;
    s32 pick;

    start[0] = (from[0] & 0xFFFF) << 4;
    start[1] = (from[1] & 0xFFFF) << 4;
    start[2] = (from[2] & 0xFFFF) << 4;
    end[0][0] = (to[0] & 0xFFFF) << 4;
    end[0][1] = (to[1] & 0xFFFF) << 4;
    end[0][2] = (to[2] & 0xFFFF) << 4;
    sinX = func_0020B550(to[0]);
    cosX = func_0020B480(to[0]);
    sinZ = func_0020B550(to[2]);
    cosZ = func_0020B480(to[2]);
    cosY = func_0020B480(to[1]);
    end[1][1] = (0x80000 - end[0][1]) & 0xFFFFF;
    cosY2 = func_0020B480(end[1][1] >> 4);
    end[1][0] = ((s32)(65536.0f * (func_001A6C18(sinX * cosY / cosY2, cosX * cosY / cosY2) / 6.2831855f)) & 0xFFFF) << 4;
    end[1][2] = ((s32)(65536.0f * (func_001A6C18(cosY * sinZ / cosY2, cosY * cosZ / cosY2) / 6.2831855f)) & 0xFFFF) << 4;
    {
        s32 i;
        s32 j;

        for (i = 0; i < 2; i++) {
            for (j = 0; j < 3; j++) {
                d = end[i][j] - start[j];
                if (d > 0x80000) {
                    end[i][j] -= 0x100000;
                    diff[i][j] = 0x100000 - d;
                } else if (d < -0x80000) {
                    end[i][j] += 0x100000;
                    diff[i][j] = d + 0x100000;
                } else if (d < 0) {
                    diff[i][j] = -d;
                } else {
                    diff[i][j] = d;
                }
            }
        }
    }
    pick = (diff[0][0] + diff[0][1] + diff[0][2] > diff[1][0] + diff[1][1] + diff[1][2]) ? 1 : 0;
    out[0] = (((s32)(start[0] * weight0 + end[pick][0] * weight1) & 0xFFFFF) + 8) >> 4;
    out[1] = (((s32)(start[1] * weight0 + end[pick][1] * weight1) & 0xFFFFF) + 8) >> 4;
    out[2] = (((s32)(start[2] * weight0 + end[pick][2] * weight1) & 0xFFFFF) + 8) >> 4;
}

extern f32 D_003269F0;
extern f32 D_003269F4;
extern f32 D_003269F8;
extern f32 D_003269FC;
extern f32 D_00326A00;
extern f32 D_00326A04;
extern f32 D_00326A08;
extern f32 D_00326A0C;
extern f32 D_00326A10;
extern f32 D_00326A14;
extern f32 D_00326A18;
extern f32 D_00326A1C;

typedef union Angles_0020D5E0 {
    s32 a[4];
    __int128 q;
} Angles_0020D5E0;

typedef union Matrix_0020D5E0 {
    f32 m[4][4];
    __int128 q[4];
} Matrix_0020D5E0;

static inline void normalize_0020D5E0(f32 *dest, f32 *src) {
    f32 length;

    length = func_001A6C60(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
    dest[0] = src[0] / length;
    dest[1] = src[1] / length;
    dest[2] = src[2] / length;
    dest[3] = src[3];
}

void func_0020D5E0(f32 *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    Angles_0020D5E0 angles;
    Matrix_0020D5E0 matrix;

    D_003269F0 = arg2[2];
    D_003269F4 = 0.0f;
    D_003269F8 = -arg2[0];
    D_00326A00 = -arg2[1] * arg2[0];
    D_00326A04 = arg2[0] * arg2[0] + arg2[2] * arg2[2];
    D_00326A08 = -arg2[1] * arg2[2];
    *(__int128 *)&D_00326A10 = *(__int128 *)arg2;
    normalize_0020D5E0(&D_003269F0, &D_003269F0);
    normalize_0020D5E0(&D_00326A00, &D_00326A00);
    normalize_0020D5E0(&D_00326A10, &D_00326A10);
    arg0[0] = -D_003269F0;
    arg0[1] = -D_003269F4;
    arg0[2] = -D_003269F8;
    arg0[3] = 0.0f;
    arg0[4] = -D_00326A00;
    arg0[5] = -D_00326A04;
    arg0[6] = -D_00326A08;
    arg0[7] = 0.0f;
    arg0[8] = D_00326A10;
    arg0[9] = D_00326A14;
    arg0[10] = D_00326A18;
    arg0[11] = 0.0f;
    arg0[12] = arg1[0];
    arg0[13] = arg1[1];
    arg0[14] = arg1[2];
    arg0[15] = 1.0f;
    angles.a[0] = 0;
    angles.a[1] = 0;
    angles.a[2] = arg3;
    func_0020C630(&matrix, angles.a);
    func_0020BC00((s32) arg0, &matrix);
    func_0020BDE0(arg0, arg0);
}

void func_0020D8E0(f32 *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5, f32 fparg6, f32 fparg7, f32 arg_sp0) {
    extern void func_0020BBB0(void *);
    f32 matrix[16];

    func_0020BBB0(matrix);
    matrix[0] = fparg0;
    matrix[5] = fparg0;
    matrix[10] = 0.0f;
    matrix[15] = 0.0f;
    matrix[14] = 1.0f;
    matrix[11] = 1.0f;
    func_0020BBB0(arg0);
    arg0[0] = fparg1;
    arg0[5] = fparg2;
    arg0[10] = (arg_sp0 * fparg7 * (-fparg5 + fparg6)) / (-fparg7 + arg_sp0);
    arg0[12] = fparg3;
    arg0[13] = fparg4;
    arg0[14] = (-fparg6 * fparg7 + fparg5 * arg_sp0) / (-fparg7 + arg_sp0);
    func_0020BC00((s32) arg0, matrix);
}

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020D9F0);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DA70);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DB00);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DB20);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DB80);

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020DBE0);

typedef struct Entry_0020DDB0 {
    u8 pad0[0xC0];
    u8 unkC0[0x90];
    f32 centerX;
    f32 centerY;
    f32 unk158;
    f32 unk15C;
    f32 unk160;
    f32 width;
    f32 height;
    f32 unk16C;
    f32 farZ;
    f32 range;
    f32 unk178;
    f32 unk17C;
    f32 nearZ;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad188[0x18];
} Entry_0020DDB0;

s32 func_0020DDB0(void) {
    extern s32 D_0032A294;
    extern Entry_0020DDB0 D_0032A2A0[];
    s32 width;
    s32 height;

    D_0032A240 = 0;
    D_0032A294 = 0;
    func_00209D60(&width, &height);
    D_0032A2A0[0].unk160 = 400.0f;
    D_0032A2A0[0].width = width;
    D_0032A2A0[0].height = height;
    D_0032A2A0[0].centerX = D_0032A2A0[0].width / 2.0f;
    D_0032A2A0[0].centerY = D_0032A2A0[0].height / 2.0f;
    D_0032A2A0[0].unk158 = 1.0f;
    D_0032A2A0[0].unk15C = 0.95f;
    D_0032A2A0[0].unk16C = 1.0f;
    D_0032A2A0[0].farZ = 10000.0f;
    D_0032A2A0[0].range = D_0032A2A0[0].farZ - 1000.0f;
    D_0032A2A0[0].unk178 = D_0032A2A0[0].farZ;
    D_0032A2A0[0].unk17C = 0.0f;
    D_0032A2A0[0].nearZ = 1000.0f;
    D_0032A2A0[0].a = 0xFF;
    D_0032A2A0[0].b = 0xFF;
    D_0032A2A0[0].g = 0xFF;
    D_0032A2A0[0].r = 0xFF;
    func_0020E1A0(D_0032A2A0[0].unkC0);
    return 1;
}

s32 func_0020DEE0(void) {
    return 1;
}

typedef struct {
    __int128 data[9];
} Copy_0020DEF0;

extern u8 D_0032A360[];

s32 func_0020DEF0(void *arg0) {
    *(Copy_0020DEF0 *)arg0 =
        *(Copy_0020DEF0 *)(D_0032A360 + D_0032A240 * 0x1A0);
    return 1;
}

typedef struct State_0020DF40 {
    u8 pad000[0x150];
    f32 field150;
    f32 field154;
    u8 pad158[8];
    f32 field160;
    f32 field164;
    f32 field168;
    u8 pad16C[0x34];
} State_0020DF40;

s32 func_0020DF40(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    extern State_0020DF40 D_0032A2A0[];
    State_0020DF40 *state;

    state = &D_0032A2A0[D_0032A240];
    state->field160 = fparg0;
    state->field164 = fparg1;
    state->field168 = fparg2;
    state->field150 = fparg3;
    state->field154 = fparg4;
    return 1;
}

typedef struct State_0020DF90 {
    u8 pad0[0x158];
    f32 field158;
    f32 field15C;
    u8 pad160[0x40];
} State_0020DF90;

s32 func_0020DF90(f32 fparg0, f32 fparg1) {
    extern State_0020DF90 D_0032A2A0[];
    State_0020DF90 *state;

    state = &D_0032A2A0[D_0032A240];
    state->field158 = fparg0;
    state->field15C = fparg1;
    return 1;
}

typedef struct {
    u8 pad_000[0x16C];
    f32 x;
    f32 y;
    u8 pad_174[0x2C];
} Entry_0020DFD0;

s32 func_0020DFD0(f32 fparg0, f32 fparg1) {
    extern Entry_0020DFD0 D_0032A2A0[];
    Entry_0020DFD0 *entry;

    entry = &D_0032A2A0[D_0032A240];
    entry->x = fparg0;
    entry->y = fparg1;
    return 1;
}

typedef struct {
    u8 pad0[0x150];
    f32 x;
    f32 y;
    u8 pad158[0x48];
} Entry_0020E010;

extern s32 D_0032A240;
extern Entry_0020E010 D_0032A2A0[];

s32 func_0020E010(f32 *arg0, f32 *arg1) {
    Entry_0020E010 *e = &D_0032A2A0[D_0032A240];

    *arg0 = e->x;
    *arg1 = e->y;
    return 1;
}

s32 func_0020E050(f32 *arg0) {
    Entry_0020E010 *e = &D_0032A2A0[D_0032A240];

    *arg0 = *(f32 *)&e->pad158[8];
    return 1;
}

s32 func_0020E090(f32 *arg0, f32 *arg1) {
    Entry_0020DFD0 *entry = (Entry_0020DFD0 *)&D_0032A2A0[D_0032A240];

    *arg0 = entry->x;
    *arg1 = entry->y;
    return 1;
}

s32 func_0020E0D0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    typedef struct {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    } Color_0020E0D0;
    typedef struct {
        u8 pad[0x174];
        f32 x;
        f32 y;
        f32 z;
        f32 w;
        Color_0020E0D0 color;
        u8 pad188[0x18];
    } Entry_0020E0D0;
    Entry_0020E0D0 *entry;

    entry = (Entry_0020E0D0 *)&D_0032A2A0[D_0032A240];
    entry->x = fparg0;
    entry->y = fparg1;
    entry->z = fparg2;
    entry->w = fparg3;
    entry->color = *(Color_0020E0D0 *)arg0;
    return 1;
}

typedef struct Color_0020E130 {
    u8 r, g, b, a;
} Color_0020E130;

typedef struct Entry_0020E130 {
    u8 pad0[0x174];
    f32 values[4];
    Color_0020E130 color;
    u8 pad188[0x18];
} Entry_0020E130;

s32 func_0020E130(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, u8 *arg4) {
    Entry_0020E130 *entry;

    entry = (Entry_0020E130 *)&D_0032A2A0[D_0032A240];
    *arg0 = entry->values[0];
    *arg1 = entry->values[1];
    *arg2 = entry->values[2];
    *arg3 = entry->values[3];
    *(Color_0020E130 *)arg4 = entry->color;
    return 1;
}

typedef struct {
    u8 pad[0x40];
    f32 vector40[4];
    f32 vector50[4];
    f32 vector60[4];
    f32 vector70[4];
    f32 vector80[4];
} State_0020E1A0;

s32 func_0020BBB0(void *);

s32 func_0020E1A0(void *state) {
    if (state == NULL) {
        state = (u8 *)&D_0032A2A0[D_0032A240] + 0xC0;
    }
    func_0020BBB0(state);
    ((State_0020E1A0 *)state)->vector40[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector40[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector40[2] = 0.0f;
    ((State_0020E1A0 *)state)->vector40[3] = 1.0f;
    ((State_0020E1A0 *)state)->vector50[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector50[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector50[2] = -1.0f;
    ((State_0020E1A0 *)state)->vector50[3] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[2] = 0.0f;
    ((State_0020E1A0 *)state)->vector60[3] = 1.0f;
    ((State_0020E1A0 *)state)->vector70[0] = 0.0f;
    ((State_0020E1A0 *)state)->vector70[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector70[2] = -1.0f;
    ((State_0020E1A0 *)state)->vector70[3] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[1] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[2] = 0.0f;
    ((State_0020E1A0 *)state)->vector80[3] = 0.0f;
    return 1;
}

s32 func_0020E260(void *arg0) {
    typedef struct {
        u8 pad0[0x40];
        u8 unk40[0x80];
        u8 unkC0[0x90];
        f32 x;
        f32 y;
        u8 pad158[8];
        f32 radius;
        f32 width;
        f32 height;
        u8 pad16C[0x1C];
        f32 radius_squared;
        f32 width_squared;
        f32 height_squared;
        u8 pad194[0xC];
    } State_0020E260;
    State_0020E260 *state;

    state = (State_0020E260 *)&D_0032A2A0[D_0032A240];
    func_0020B380(state->unkC0, arg0, 9);
    func_0020E9F0();
    func_0020BBA0();
    func_0020BA90(state->unk40);
    state->radius_squared = 4186116.0f + state->radius * state->radius;
    state->width_squared = (state->width * state->width) / 4.0f + state->radius * state->radius;
    state->height_squared = (state->height * state->height) / 4.0f + state->radius * state->radius;
    func_0020BAD0(arg0);
    func_0020EBA0(D_0032A730);
    func_0020BDE0(D_0032A730, D_0032A730);
    return 1;
}

typedef struct State_0020E360 {
    u8 pad_000[0x40];
    f32 matrix[4][4];
    u8 pad_080[0xE0];
    f32 radius;
    f32 width;
    f32 height;
    u8 pad_16C[0x1C];
    f32 radius_squared;
    f32 width_squared;
    f32 height_squared;
    u8 pad_194[0xC];
} State_0020E360;

s32 func_0020E360(void *arg0) {
    State_0020E360 *state;

    state = (State_0020E360 *)&D_0032A2A0[D_0032A240];
    func_0020B380((u8 *)state + 0xC0, arg0, 9);
    func_0020E9F0();
    func_0020BA90(&state->matrix);
    func_0020B380(arg0, state->matrix, 4);
    state->radius_squared = 4186116.0f + state->radius * state->radius;
    state->width_squared = (state->width * state->width) / 4.0f +
                           state->radius * state->radius;
    state->height_squared = (state->height * state->height) / 4.0f +
                            state->radius * state->radius;
    func_0020EBA0(D_0032A730);
    func_0020BDE0(D_0032A730, D_0032A730);
    return 1;
}

typedef struct Copy_0020E460 {
    __int128 data[26];
} Copy_0020E460;

s32 func_0020E460(void) {
    extern u8 D_0032A440[];

    if (D_0032A240 + 1 >= 2) {
        return 0;
    }
    ((Copy_0020E460 *)D_0032A440)[D_0032A240] = ((Copy_0020E460 *)D_0032A2A0)[D_0032A240];
    D_0032A240 += 1;
    return 1;
}

s32 func_0020E4F0(void) {
    if (D_0032A240 <= 0) {
        return 0;
    }
    D_0032A240 -= 1;
    return 1;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char D_0032A2A0[];
#endif


typedef struct Vec4_0020E520 {
    f32 x, y, z, w;
} Vec4_0020E520;

typedef struct State_0020E520 {
    Vec4_0020E520 point;
    Vec4_0020E520 normal;
    Vec4_0020E520 direction;
    Vec4_0020E520 displacement;
    f32 distance;
    s32 active;
} State_0020E520;

typedef struct Object_0020E520 {
    __int128 reserved0[4];
    Vec4_0020E520 point;
    Vec4_0020E520 direction;
    u8 reserved1[0x20];
    s32 angle;
    u8 reserved2[0xC];
} Object_0020E520;

typedef struct Block_0020E520 {
    __int128 data[26];
} Block_0020E520;

extern s32 D_0032A294;
extern u8 D_0032A360[];
extern u8 D_0032A440[];

static inline void reflect_0020E520(Vec4_0020E520 *v, Vec4_0020E520 *normal) {
    f32 twiceDot = 2.0f * (normal->x * v->x + normal->y * v->y + normal->z * v->z);
    v->x = twiceDot * normal->x - v->x;
    v->y = twiceDot * normal->y - v->y;
    v->z = twiceDot * normal->z - v->z;
}

s32 func_0020E520(f32 *point, f32 *normal, void *output) {
    extern State_0020E520 D_0032A250;
    extern s32 func_001A22C0(f32);
    State_0020E520 *state = &D_0032A250;
    Object_0020E520 *original = (Object_0020E520 *)D_0032A360;
    u8 scratch[0xA0 + 0xF];
    Vec4_0020E520 *up;
    f32 *cross;
    void *matrix;
    void *inverse;
    Object_0020E520 *object = (Object_0020E520 *)output;

    up = (Vec4_0020E520 *)(((u32)scratch + 0xF) & ~0xF);
    up->x = 0.0f;
    up->y = 1.0f;
    up->z = 0.0f;
    cross = (f32 *)((u8 *)up + 0x10);
    matrix = (u8 *)cross + 0x40;
    up->w = 0.0f;
    inverse = (u8 *)matrix + 0x40;
    if (D_0032A294 != 0) {
        return 0;
    }
    *object = *original;
    state->point = *(Vec4_0020E520 *)point;
    state->normal = *(Vec4_0020E520 *)normal;
    state->direction.x = -original->direction.x;
    state->direction.y = -original->direction.y;
    state->direction.z = -original->direction.z;
    state->displacement.x = original->point.x - state->point.x;
    state->displacement.y = original->point.y - state->point.y;
    state->displacement.z = original->point.z - state->point.z;
    state->distance = func_0020D0E0(&state->displacement.x);
    func_0020D070(&state->normal.x);
    func_0020D070(&state->direction.x);
    func_0020D070(&state->displacement.x);
    reflect_0020E520(&state->direction, &state->normal);
    reflect_0020E520(&state->displacement, &state->normal);
    object->direction = state->direction;
    object->point.x = point[0] - state->displacement.x * state->distance;
    object->point.y = point[1] - state->displacement.y * state->distance;
    object->point.z = point[2] - state->displacement.z * state->distance;
    object->point.w = 0.0f;
    func_0020EBA0(matrix);
    func_0020BDE0(inverse, matrix);
    func_0020CDD0(up, inverse, up);
    reflect_0020E520(up, &state->normal);
    func_0020D140(cross, (f32 *)up, &object->direction.x);
    func_0020D5E0(matrix, &object->point, &object->direction, 0);
    func_0020CDD0(cross, matrix, cross);
    object->angle = (s32)func_001A22C0(65536.0f * (func_001A6C18(cross[1], cross[0]) / 6.2831855f)) + 0x8000;
    if (D_0032A240 + 1 < 2) {
        ((Block_0020E520 *)D_0032A440)[D_0032A240] = ((Block_0020E520 *)D_0032A2A0)[D_0032A240];
        D_0032A240++;
    }
    state->active = 1;
    return 1;
}

typedef struct {
    u8 padding[0x44];
    s32 ready;
} State_0020E970;

typedef struct {
    __int128 data[9];
} Buffer_0020E970;

extern State_0020E970 D_0032A250;
extern s32 D_0032A294;
extern u8 D_0032A360[];

s32 func_0020E970(void *arg0) {
    State_0020E970 *state = &D_0032A250;

    if (D_0032A294 == 0) {
        return 0;
    }
    if (D_0032A240 > 0) {
        D_0032A240 -= 1;
    }
    state->ready = 0;
    *(Buffer_0020E970 *)arg0 = *(Buffer_0020E970 *)D_0032A360;
    return 1;
}

#ifndef GAME_H
/* The game translation unit already declares this array with its local type. */
extern unsigned char D_0032A2A0[][0x1A0];
#endif


typedef struct Object_0020E9F0 {
    u8 unk0[0x40];
    f32 matrix40[16];
    f32 matrix80[16];
    u8 unkC0[0x80];
    s32 unk140;
    u8 unk144[0xC];
    f32 unk150;
    f32 unk154;
    f32 unk158;
    f32 unk15C;
    f32 unk160;
    f32 unk164;
    f32 unk168;
    f32 unk16C;
    f32 unk170;
    u8 unk174[0x2C];
} Object_0020E9F0;


s32 func_0020E9F0(void) {
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    f32 temp_f20;
    f32 temp_f21;
    Object_0020E9F0 *temp_s0;
    u8 *temp_s1;

    temp_s0 = (Object_0020E9F0 *)&D_0032A2A0[D_0032A240];
    temp_s1 = (u8 *) temp_s0 + 0xC0;
    func_00209E30(&sp50, &sp54);
    temp_f20 = ((f32) sp50 + temp_s0->unk150) - (temp_s0->unk164 / 2.0f);
    temp_f21 = ((f32) sp54 + temp_s0->unk154) - (temp_s0->unk168 / 2.0f);
    func_00209D80(&sp58, &sp5C);
    func_0020D5E0(temp_s0->matrix40, temp_s1 + 0x40, temp_s1 + 0x50, *(s32 *) (temp_s1 + 0x80));
    func_0020D8E0(temp_s0->matrix80, temp_s0->unk160, temp_s0->unk158, temp_s0->unk15C * func_00209D40(NULL), temp_f20, temp_f21, (f32) sp58, (f32) sp5C, temp_s0->unk16C, 2.0f * temp_s0->unk170);
    func_0020B380(temp_s0, temp_s0->matrix80, 4);
    func_0020BC00((s32) temp_s0, temp_s0->matrix40);
    func_0020B380(temp_s1, temp_s0, 4);
    return 1;
}

typedef struct {
    s32 words[16];
} Block_0020EB40;

void func_0020EB40(void *arg0) {
    *(Block_0020EB40 *)arg0 = *(Block_0020EB40 *)&D_0032A2A0[D_0032A240];
}

typedef struct {
    s32 words[16];
} Block_0020EBA0;

extern u8 D_0032A2E0[][0x1A0];

void func_0020EBA0(void *arg0) {
    *(Block_0020EBA0 *)arg0 = *(Block_0020EBA0 *)D_0032A2E0[D_0032A240];
}

typedef struct {
    s32 words[16];
} Block_0020EC00;

typedef struct {
    Block_0020EC00 block;
    u8 padding[0x160];
} Entry_0020EC00;

extern Entry_0020EC00 D_0032A320[];

void func_0020EC00(void *dst) {
    *(Block_0020EC00 *)dst = D_0032A320[D_0032A240].block;
}

s32 func_0020EC60(s32 arg0) {
    u8 matrix_storage[0x4F];
    u8 *matrix;
    u8 *item;
    void *result;

    matrix = (u8 *)(((u32)matrix_storage + 0xF) & ~0xF);
    item = (u8 *)&D_0032A2A0[D_0032A240];
    result = func_00208E60((void *)arg0, item + 0x80);
    func_0020BDE0(matrix, item);
    return (s32)func_002093E0(
        func_0020A340(
            func_00209320(func_00208EB0(result, matrix), 1,
                *(f32 *)(item + 0x160), *(f32 *)(item + 0x16C),
                *(f32 *)(item + 0x170)),
            item + 0x184),
        *(f32 *)(item + 0x174), *(f32 *)(item + 0x178),
        *(f32 *)(item + 0x17C), *(f32 *)(item + 0x180));
}

typedef struct {
    f32 x, y, z, w;
} Vec4_0020ED30;

void func_0020ED30(void *arg0, f32 fparg0) {
    u8 buffer[31];
    Vec4_0020ED30 *vector;
    void *matrix;

    matrix = (u8 *)&D_0032A2A0[D_0032A240] + 0x80;
    vector = (Vec4_0020ED30 *) (((u32) buffer + 15) & ~15);
    *vector = *(Vec4_0020ED30 *) arg0;
    vector->z -= fparg0;
    func_0020CDD0(vector, matrix, vector);
    func_001A23B0(vector->z / vector->w);
}

INCLUDE_ASM("asm/nonmatchings/main_058", func_0020EDE0);

void func_0020F250(s32 arg0) {
    u8 *entry;
    s32 i;
    s32 count;

    *(s32 *)((u8 *)arg0 + 0xC) = arg0;
    count = *(s32 *)((u8 *)arg0 + 0x58);
    entry = (u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x10);
    for (i = 0; i < count; i += 1) {
        *(s32 *)(entry + 4) = arg0 + *(s32 *)(entry + 4);
        entry += 0x30;
    }
}

s32 func_0020F290(s32 arg0) {
    func_001875F8(D_0032A5E0, arg0);
    func_00187660(D_0032A5E0, 0);
    func_001877F8(D_0032A5E0, 0x11000000);
    func_00187778(D_0032A5E0, 2, 3);
    func_00187858(D_0032A5E0, 0);
    *(u64 *)&D_0032A600 = 0x8000 | ((u64)0x10000000 << 32);
    *((u64 *)&D_0032A600 + 1) = 0xE;
    func_001876B8(D_0032A5E0, D_0032A600);
    func_00187828(D_0032A5E0, 0x3F, 1);
    func_001876D0(D_0032A5E0);
    func_001878B0(D_0032A5E0);
    return func_00187608(D_0032A5E0);
}

s32 func_0020F370(void *arg0) {
    s32 *sections;
    s32 i;
    u32 *entries;
    u32 value;
    u32 *target;
    u8 *resolved;

    sections = (s32 *)((u8 *)arg0 + 0x10);
    entries = (u32 *)((u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    for (i = 0; entries[i] != 0xFFFFFFFF; i++) {
        value = entries[i];
        switch (value & 0xF0000000) {
        case 0x20000000:
            target = (u32 *)((u8 *)arg0 + sections[2] + (value & 0x0FFFFFFF));
            break;
        case 0x30000000:
            target = (u32 *)((u8 *)arg0 + sections[4] + (value & 0x0FFFFFFF));
            break;
        case 0x40000000:
            target = (u32 *)((u8 *)arg0 + sections[6] + (value & 0x0FFFFFFF));
            break;
        case 0x50000000:
            target = (u32 *)((u8 *)arg0 + sections[8] + (value & 0x0FFFFFFF));
            break;
        default:
            continue;
        }
        value = *target;
        switch (value & 0xF0000000) {
        case 0x20000000:
            resolved = (u8 *)arg0 + sections[2] + (value & 0x0FFFFFFF);
            break;
        case 0x30000000:
            resolved = (u8 *)arg0 + sections[4] + (value & 0x0FFFFFFF);
            break;
        case 0x40000000:
            resolved = (u8 *)arg0 + sections[6] + (value & 0x0FFFFFFF);
            break;
        case 0x50000000:
            resolved = (u8 *)arg0 + sections[8] + (value & 0x0FFFFFFF);
            break;
        default:
            continue;
        }
        *target = (u32)resolved;
    }
    return 1;
}

typedef struct Flags_0020F4E0 {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 bit6 : 1;
    u8 bit7 : 1;
} Flags_0020F4E0;

typedef struct Object_0020F4E0 {
    u8 *data;
    Flags_0020F4E0 flags4;
    Flags_0020F4E0 flags5;
    u8 pad6[0x26];
    s32 result;
} Object_0020F4E0;

typedef struct Offset_0020F4E0 {
    s32 unused;
    u32 value : 28;
    u32 flags : 4;
} Offset_0020F4E0;

typedef struct Transform_0020F4E0 {
    u8 pad0[0x30];
    union {
        __int128 quad;
        struct {
            f32 x, y, z, w;
        } values;
    } vector;
} Transform_0020F4E0;

s32 func_0020EDE0(void *, f32);
void *func_0020F780(void *, s32);
void *func_0020FA10(void *);
extern s32 D_0032A770;

void *func_0020F4E0(void *arg0, void *arg1) {
    extern s32 func_0020ED30(void *, f32);
    s32 temp_v1;
    Transform_0020F4E0 *temp_s0;
    s32 var_s1;
    Object_0020F4E0 *obj;

    obj = arg1;
    if (!obj->flags4.bit1 || !obj->flags5.bit2) {
        arg0 = func_00209490(arg0, (u8)obj->flags4.bit1, obj->flags5.bit2);
    }
    *(void **)0x700000C0 = arg0;
    *(u8 **)0x700000DC = obj->data + 0x10;
    *(s32 *)0x700000D8 = ((Offset_0020F4E0 *)(obj->data + *(s32 *)(*(u8 **)0x700000DC + 8)))->value;
    func_0020BAF0(0);
    temp_s0 = (Transform_0020F4E0 *)(obj->data + *(s32 *)*(u8 **)0x700000DC);
    *(__int128 *)0x70000020 = temp_s0->vector.quad;
    *(s32 *)0x7000002C = 0x3F800000;
    if (obj->flags5.bit4 != 0) {
        func_0020B380((void *)0x70000000, (u8 *)arg1 + 0x50, 1);
    } else {
        func_0020CDD0((void *)0x70000000, NULL, (void *)0x70000020);
    }
    obj->result = func_0020ED30((void *)0x70000000, temp_s0->vector.values.w);
    var_s1 = 0;
    if (obj->flags4.bit0 && (func_00209270(NULL, (void *)0x70000050, (f32 *)0x70000030, (f32 *)0x70000034, (f32 *)0x70000038) != 0) && (func_0020D100((f32 *)0x70000050, (f32 *)0x70000000) <= (*(f32 *)0x70000034 + temp_s0->vector.values.w))) {
        var_s1 = 1;
    }
    D_0032A770 = 0;
    if (obj->flags4.bit2 != 0) {
        arg0 = func_0020F780(arg1, var_s1);
    } else {
        *(s32 *)0x700000B0 = func_0020EDE0((void *)0x70000020, temp_s0->vector.values.w);
        temp_v1 = *(s32 *)0x700000B0;
        if (temp_v1 & 1) {
            if ((temp_v1 & 4) || (*(s32 *)(*(u8 **)0x700000DC + 0x1C) > 0) || (var_s1 != 0)) {
                arg0 = func_0020F780(arg1, var_s1);
            } else {
                arg0 = func_0020FA10(arg1);
            }
        }
    }
    func_0020BB50();
    if ((obj->flags4.bit1 == 0) || (obj->flags5.bit2 == 0)) {
        arg0 = func_00209490(arg0, 1, 1);
    }
    return arg0;
}
