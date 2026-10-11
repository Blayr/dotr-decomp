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

void *func_001DD130();
s32 func_001E02F0(void *arg0, s32 arg1);

static inline void *lookup_001E0290(s32 arg0, s32 arg1)
{
    void *object = func_001DD130(arg0, arg1);

    if (object == 0) {
        return 0;
    }
    if (*((u8 *)object + 0x45) >= 11) {
        return 0;
    }
    return object;
}

s32 func_001E0290(s32 arg0, s32 arg1, s32 arg2)
{
    return func_001E02F0(lookup_001E0290(arg0, arg1), arg2);
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E02F0);

void *func_001DD130();
s32 func_001E03D0(void *, s32);

static inline void *lookup_001E0370(s32 arg0, s32 arg1) {
    void *ptr;

    ptr = func_001DD130(arg0, arg1);
    if (ptr == NULL) {
        return NULL;
    }
    if (*((u8 *)ptr + 0x45) >= 11) {
        return NULL;
    }
    return ptr;
}

s32 func_001E0370(s32 arg0, s32 arg1, s32 arg2) {
    return func_001E03D0(lookup_001E0370(arg0, arg1), arg2);
}

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

void *func_001DD130();

static inline u8 *check_001E0760(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E0760(s32 a0, s32 a1, s8 arg2) {
    u8 *p;

    p = check_001E0760(a0, a1);
    if (p == NULL) {
        return 0;
    }
    p[0x3E] = arg2;
    return 1;
}

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

void *func_001DD130();
void func_001E0950(void *, s32);

static inline void *check_001E08F0(void *var_v0) {
    if (var_v0 == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)var_v0 + 0x45) >= 0xB) {
        return NULL;
    }
    return var_v0;
}

void func_001E08F0(s32 arg0, s32 arg1, s32 arg2) {
    func_001E0950(check_001E08F0(func_001DD130()), arg2);
}

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

void *func_001DD130();

static inline u8 *get_001E1090(void) {
    u8 *data;

    data = func_001DD130();
    if (data == NULL) {
        return NULL;
    }
    if (data[0x45] >= 0xB) {
        return NULL;
    }
    return data;
}

s32 func_001E1090(s32 arg0, s32 arg1) {
    u8 *data;

    data = get_001E1090();
    if (data != NULL) {
        return (data[0x41] << 8) | data[0x40];
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E10F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E11B0);

void *func_001DD130(void);

static inline void *lookup_001E1360(void) {
    void *ptr;

    ptr = func_001DD130();
    if (ptr == NULL) {
        ptr = NULL;
    } else if (*((u8 *)ptr + 0x45) >= 11) {
        ptr = NULL;
    }
    return ptr;
}

s32 func_001E1360(void) {
    void *ptr;

    ptr = lookup_001E1360();
    if (ptr != NULL) {
        return *((u8 *)ptr + 0x46);
    }
    return -1;
}

typedef struct Entry_001E13C0 {
    u8 padding[0x45];
    u8 type;
    u8 padding46;
    u8 value;
} Entry_001E13C0;

void *func_001DD130(void);

s32 func_001E13C0(void) {
    Entry_001E13C0 *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        entry = NULL;
    } else if (entry->type >= 0xB) {
        entry = NULL;
    }
    if (entry != NULL) {
        return entry->value;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1420);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E14B0);

void *func_001DD130();

static inline void *lookup_001E1520(void) {
    void *entry = func_001DD130();

    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 11) {
        return NULL;
    }
    return entry;
}

s32 func_001E1520(s32 arg0, s32 arg1, s8 arg2) {
    void *entry = lookup_001E1520();

    if (entry == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)entry + 0x49) = arg2;
    return 1;
}

void *func_001DD130(void);

static inline void *get_001E1580(void) {
    void *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 11) {
        return NULL;
    }
    return entry;
}

s32 func_001E1580(void) {
    void *entry;

    entry = get_001E1580();
    if (entry != NULL) {
        return *(u8 *)((u8 *)entry + 0x49);
    }
    return -1;
}

s32 func_001E15E0(s32 arg0, s32 arg1, s8 arg2) {
    void *var_v0;

    var_v0 = func_001DD130();
    if (var_v0 == NULL) {
        var_v0 = NULL;
    } else if (*(u8 *)((u8 *)var_v0 + 0x45) >= 0xB) {
        var_v0 = NULL;
    }
    if (var_v0 == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)var_v0 + 0x4A) = arg2;
    return 1;
}

void *func_001DD130(void);

static inline u8 *check_001E1640(void) {
    u8 *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 11) {
        entry = NULL;
    }
    return entry;
}

s32 func_001E1640(void) {
    u8 *entry;

    entry = check_001E1640();
    if (entry != NULL) {
        return entry[0x4A];
    }
    return -1;
}

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

void *func_001DD130(void);

static inline u8 *valid_001E1700(void) {
    u8 *ptr;

    ptr = func_001DD130();
    if (ptr == NULL) {
        return NULL;
    }
    if (ptr[0x45] >= 0xB) {
        return NULL;
    }
    return ptr;
}

s32 func_001E1700(void) {
    u8 *ptr;

    ptr = valid_001E1700();
    if (ptr != NULL) {
        return ptr[0x4B];
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1760);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E17D0);

s32 func_001E1840(s32 arg0, s32 arg1, s8 arg2) {
    void *var_v0;

    var_v0 = func_001DD130();
    if (var_v0 == NULL) {
        var_v0 = NULL;
    } else if (*(u8 *)((u8 *)var_v0 + 0x45) >= 0xB) {
        var_v0 = NULL;
    }
    if (var_v0 == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)var_v0 + 0x4E) = arg2;
    return 1;
}

static inline void *check_001E18A0(void) {
    void *p = func_001DD130();
    if (p == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)p + 0x45) >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E18A0(s32 arg0, s32 arg1, s8 arg2) {
    void *p = check_001E18A0();
    if (p == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)p + 0x4F) = arg2;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1900);

static inline void *get_001E1970(void) {
    void *p;

    p = func_001DD130();
    if (p == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)p + 0x45) >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E1970(s32 arg0, s32 arg1, s8 arg2) {
    void *p;

    p = get_001E1970();
    if (p == NULL) {
        return 0;
    }
    *(s8 *)((u8 *)p + 0x50) = arg2;
    return 1;
}
