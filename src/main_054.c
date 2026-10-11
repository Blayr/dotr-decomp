#include "common.h"

void func_001FF250(s8 *p) {
    s32 network;
    s32 first;
    s32 c;

    first = p[0];
    network = 0;
    if ((first == '/' && p[1] == '/') ||
        (first == '\\' && p[1] == '\\')) {
        network = 1;
    }
    func_00200300(p);
    while ((c = *p) != 0) {
        if (network != 0) {
            if (c == '/') {
                *p = '\\';
            }
        } else if (c == '\\') {
            *p = '/';
        }
        p++;
    }
}

s32 func_001FF300(void) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (func_001FF360(var_s0, 1) != 0) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 >= 5) {
        return 0;
    }
    goto loop_1;
}

s32 func_001FF350(s32 arg0) {
    return func_001FF360(arg0, 0);
}

typedef struct Record_001FF360 {
    s32 status;
    s16 id;
    u8 padding[0x1E];
} Record_001FF360;

extern Record_001FF360 D_00320370[];

s32 func_001FF360(s32 arg0, s32 arg1) {
    Record_001FF360 *record;
    s32 remaining;
    s32 shift;

    shift = arg1 ? 10 : 0;
    record = D_00320370;
    for (remaining = 0x100; remaining--; record++) {
        if (record->status >= 0 &&
            (arg0 < 0 || arg0 == (record->id >> shift))) {
            return (s32) record;
        }
    }
    record = NULL;
    return (s32) record;
}

void func_001FF3D0(void) {
    s32 start;

    start = *(s32 *)0x10000800;
    do {
        if (func_001FF420() == 0) {
            break;
        }
    } while (*(s32 *)0x10000800 - start <= 0x40);
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FF420);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FF480);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FF9C0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFAC0);

typedef struct Entry_001FFC50 {
    s32 key;
    s32 value;
} Entry_001FFC50;

extern Entry_001FFC50 D_00322770[];

s32 func_001FFC50(s32 arg0, s32 arg1) {
    Entry_001FFC50 *entry;
    s32 remaining;

    entry = D_00322770;
    remaining = 0x40;
    while (remaining--) {
        if (entry->key < 0) {
            entry->key = arg0;
            entry->value = arg1;
            return 1;
        }
        entry++;
    }
    return 0;
}

void func_001FFCB0(void *arg0) {
    func_001FFCC0(arg0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFCC0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFD30);

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFE00);

typedef struct Flags_001FFF60 {
    s8 enabled : 1;
    s8 reserved : 7;
} Flags_001FFF60;

extern Flags_001FFF60 D_00322980;

void func_001FFF60(s32 arg0, s64 arg1) {
    D_00322980.enabled = (s8)arg1;
}

u8 *func_001FFF90(void) {
    u8 *ret;

    ret = func_00197548();
    if (ret == NULL) {
        ret = D_002D0655;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_001FFFC0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200170);

s32 func_00200210(void) {
    return 1;
}

void func_00200220(s32 arg0, s32 arg1) {
    func_00200230(arg0, 0, 0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200230);

void func_00200300(s8 *arg0) {
    s8 *var_a0;
    s32 temp_a1;

    var_a0 = arg0;
    while ((temp_a1 = *var_a0) != 0) {
        if ((temp_a1 >= 0x61) && (temp_a1 < 0x7B)) {
            *var_a0 = temp_a1 - 0x20;
        }
        var_a0 += 1;
    }
}

void func_00200350(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200360);

INCLUDE_ASM("asm/nonmatchings/main_054", func_002003E0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_002004C0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200510);

typedef struct CallbackTable_00200680 {
    u8 pad[0x6680];
    void (*callback)(s32, void *);
} CallbackTable_00200680;

extern CallbackTable_00200680 D_0031C2F0;
extern s32 D_00322970;

void func_00200680(void *arg0) {
    CallbackTable_00200680 *table = &D_0031C2F0;

    if (D_00322970 != 0) {
        table->callback(*(s32 *)((u8 *)arg0 + 0x1C), table);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_002006C0);

INCLUDE_ASM("asm/nonmatchings/main_054", func_002007D0);

typedef struct Entry_002008A0 {
    s32 occupied;
    s32 unknown;
    s16 flags : 3;
    s16 category : 13;
    s16 id;
} Entry_002008A0;

extern Entry_002008A0 D_003229A0[];

void *func_002008A0(s32 arg0, s32 arg1) {
    Entry_002008A0 *entry;
    s32 i;

    entry = D_003229A0;
    if ((arg0 < 0) || (arg0 >= 10)) {
        return NULL;
    }
    if (arg1 < 0) {
        return NULL;
    }
    i = 0;
    do {
        if (entry->occupied && (entry->category == arg0) && (entry->id == arg1)) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 1024);
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_00200930);
