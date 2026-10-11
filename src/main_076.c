#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_076", func_00265890);

INCLUDE_ASM("asm/nonmatchings/main_076", func_002660E0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266500);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266910);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266A80);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266C70);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266DF0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00266F70);

INCLUDE_ASM("asm/nonmatchings/main_076", func_002670F0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00267380);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00267560);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00267700);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00267860);

INCLUDE_ASM("asm/nonmatchings/main_076", func_002679C0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00267B30);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00267C50);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268460);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268600);

s32 func_002686F0(s32 arg0) {
    s32 result;

    switch (arg0) {
    case 0:
        result = 0x38;
        break;
    case 1:
        result = 0x39;
        break;
    case 2:
        result = 0x36;
        break;
    case 3:
        result = 0x37;
        break;
    default:
        result = 0;
        break;
    }

    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268760);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00268AD0);

typedef struct {
    u8 pad00[4];
    s32 f4;
    u32 f8;
    u32 fC;
} Src_00268FA0;

typedef struct {
    u8 pad00[4];
    u16 state;
    u8 ids[0x1A];
    s32 f20;
    u8 pad24[0xD4 - 0x24];
    u8 nids;
    u8 padD5[0x102 - 0xD5];
    u16 timer;
} Work_00268FA0;

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
} Req_00268FA0;

void func_001DE7E0(s32);
s32 func_001DE780(void);
void func_001DF490(s32, s32, s32);
void func_001E42C0(s32, s32, s32, s32);
void func_001E4530(void);
s32 func_001F51D0(s32);
void func_00250CA0(s32, s32, s32, u32);
void func_00250E80(s32, s32, s32, u32);
void func_00255960(void *);
u8 func_00255A30(void *, void *);
void func_00255AC0(void *, s32);
s32 func_00255B50(void *);
void func_0025F720(void *, void *, void *, s32);
void func_00260740(s32);
void func_00260A70(void *, s32);
s32 func_002670F0(s32, s32);

s32 func_00268FA0(void *arg0, void *arg1, s32 arg2) {
    Src_00268FA0 *src = (Src_00268FA0 *)arg0;
    Work_00268FA0 *w = (Work_00268FA0 *)arg1;
    Req_00268FA0 req;
    s32 count;
    Req_00268FA0 *p;
    s32 i;
    s32 j;

    req.w0 = 0x3E7;
    req.w4 = 0;
    req.w8 = 0;
    req.wC = 0;
    p = &req;
    count = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00260740(0x10);
        func_00255AC0(arg1, 0x1FC);
        func_00255AC0(arg1, 0x211);
        func_00260740(0x10);
        return 1;
    }
    switch (w->state) {
    case 0:
        if (func_00255B50(arg1) == 1) {
            p->w0 = 0x1FC;
            p->w4 = 0;
            p->w8 = 1;
            p->wC = func_002670F0(0x2C, (u16)src->fC);
            w->ids[0] = func_00255A30(p, arg1);
            w->f20 = 0xFFFF;
            w->nids++;
            w->state++;
        }
        break;
    case 1:
        if (func_001F51D0(w->ids[0]) == 1) {
            return 1;
        }
        func_001DF490(src->f4, 1, func_002670F0(0x2C, (u16)src->fC));
        w->state++;
        break;
    case 2:
        func_001E42C0(0, -0x78, 0x50, 0x106);
        func_0025F720(arg0, arg1, p, 0x211);
        w->state++;
        break;
    case 3:
        for (i = 0; i < w->nids; i++) {
            if (func_001F51D0(w->ids[i]) == 0) {
                count++;
            }
        }
        if (count < w->nids) {
            return 1;
        }
        func_001E4530();
        for (j = 0; j < 0x16; j++) {
            if ((src->f8 >> (0x15 - j)) & 1) {
                if (j < 0xB) {
                    func_00250E80(0, j, 0, src->fC >> 16);
                    func_00250CA0(0, j, 0, src->fC >> 16);
                } else {
                    func_00250E80(1, j - 0xB, 0, src->fC >> 16);
                    func_00250CA0(1, j - 0xB, 0, src->fC >> 16);
                }
            }
        }
        func_00260A70(arg1, 0x10);
        w->state++;
        break;
    default:
        if (w->timer++ > 0x10) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_002692D0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_002695D0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00269D60);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00269E10);

INCLUDE_ASM("asm/nonmatchings/main_076", func_00269EC0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026A0A0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026AB80);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026AC90);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026AE70);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026B1F0);

s32 func_0026B430(void *arg0) {
    ((s32 *)arg0)[0] = 0x66;
    ((s32 *)arg0)[1] = 1;
    ((s32 *)arg0)[2] = func_0026AB80(0, 0x2E);
    ((s32 *)arg0)[3] = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026B480);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026BB80);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026BE20);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026BF50);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026C170);

void func_0026CD80(s32 arg0) {
    f32 v[4];
    f32 *p;

    if (arg0 < 0) {
        func_001F1E10(1, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        p = &v[1];
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        func_001F1EE0(1, v);
        func_001F1E10(5, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        func_001F1EE0(5, v);
        func_001F1E10(6, v);
        if (v[0] - 0.08f < 0.0f) {
            v[0] = 0.0f;
        } else {
            v[0] -= 0.08f;
        }
        if (*p - 0.08f < 0.0f) {
            *p = 0.0f;
        } else {
            *p -= 0.08f;
        }
        func_001F1EE0(6, v);
    } else {
        func_001F1E10(1, v);
        v[0] = 0.8f;
        p = &v[1];
        *p = 0.8f;
        func_001F1EE0(1, v);
        func_001F1E10(5, v);
        v[0] = 0.8f;
        *p = 0.8f;
        func_001F1EE0(5, v);
        func_001F1E10(6, v);
        v[0] = 0.8f;
        *p = 0.8f;
        func_001F1EE0(6, v);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026CFC0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026D3C0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026D600);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026D6E0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026D840);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026D8F0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026DCC0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026E1F0);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026E610);

INCLUDE_ASM("asm/nonmatchings/main_076", func_0026E950);

s32 func_0026EA00(s32 *arg0) {
    s32 temp_v1;

    temp_v1 = *arg0;
    switch (temp_v1) {
    case 0:
        return func_00270030();
    case 1:
        return func_00270260();
    case 2:
        return func_0026FE70();
    default:
        return 0;
    }
}
