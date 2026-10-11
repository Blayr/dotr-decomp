#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DF540);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DF580);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DF5F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DFAF0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DFBB0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DFD50);

s32 func_001E0110(s32 arg0) {
    s32 temp_s0;

    temp_s0 = func_001E0150(arg0);
    return temp_s0 + func_001E01F0(arg0);
}

void *func_001DD130();

static inline u8 *check_001E0150(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E0150(s32 arg0) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 1; i < 6; i++) {
        if (check_001E0150(arg0, i) != NULL) {
            count++;
        }
    }
    return count;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E01F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0290);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E02F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0370);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E03D0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0450);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E04C0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0570);

#define MAX_001E05E0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001E05E0(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    u8 pad_00[0x3A];
    s16 value;
} Obj_001E05E0;

s32 func_001E05E0(void *arg0, s32 arg1, s32 arg2) {
    Obj_001E05E0 *obj = arg0;
    s32 cur;
    s32 val;

    val = arg2;
    if (obj == NULL) {
        return 0;
    }
    cur = obj->value;
    switch (arg1) {
    case 0:
        val = cur + val;
        break;
    case 1:
        val = cur - val;
        break;
    case 2:
        val = cur * val;
        break;
    case 3:
        val = cur / val;
        break;
    case 4:
        break;
    default:
        return 0;
    }
    val = MIN_001E05E0(MAX_001E05E0(val, -9999), 9999);
    obj->value = val;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0690);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0700);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0760);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E07C0);

void *func_001DD130();

static inline u8 *check_001E0830(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E0830(s32 arg0, s32 arg1) {
    u8 *p;

    p = check_001E0830(arg0, arg1);
    if (p != NULL) {
        return p[0x3F];
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0890);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E08F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0950);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E09E0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0B70);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0C00);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0C70);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0C80);

s32 func_001E1030(void) {
    u8 *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        entry = NULL;
    } else if (entry[0x45] >= 11) {
        entry = NULL;
    }
    if (entry != NULL) {
        return *(u16 *)(entry + 0x3C);
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1090);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E10F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E11B0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1360);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E13C0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1420);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E14B0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1520);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1580);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E15E0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1640);

void *func_001DD130();

static inline u8 *check_001E16A0(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E16A0(s32 a0, s32 a1, s8 arg2) {
    u8 *p;

    p = check_001E16A0(a0, a1);
    if (p == NULL) {
        return 0;
    }
    p[0x4B] = arg2;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1700);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1760);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E17D0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1840);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E18A0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1900);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1970);
