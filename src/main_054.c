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

typedef struct State_001FF420 {
    u8 pad[0x6688];
    s32 current;
} State_001FF420;

typedef struct Flags_001FF420 {
    s8 reserved : 1;
    s8 active : 1;
    s8 remaining : 6;
} Flags_001FF420;

s32 func_001FF480(s32);
s32 func_001FF9C0(void);

s32 func_001FF420(void) {
    extern State_001FF420 D_0031C2F0;
    extern Flags_001FF420 D_00322980;
    State_001FF420 *state = &D_0031C2F0;
    s32 temp_v0;

    if (D_00322980.active == 0) {
        temp_v0 = func_001FF9C0();
        state->current = temp_v0;
        if (temp_v0 < 0) {
            return 0;
        }
    }
    return func_001FF480(state->current);
}

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

typedef struct Entry_001FFCC0 {
    s32 value;
    s32 unknown;
} Entry_001FFCC0;

void *func_001FFCC0(void *arg0, s32 arg1) {
    extern struct Entry_001FFC50 D_00322770[];
    s32 shift;
    s32 count;
    Entry_001FFCC0 *entry;

    shift = arg1 ? 10 : 0;
    count = 64;
    entry = (Entry_001FFCC0 *)D_00322770;
    while (count--) {
        if (entry->value >= 0) {
            if ((s32)arg0 < 0 || (s32)arg0 == (entry->value >> shift)) {
                return entry;
            }
        }
        entry++;
    }
    return NULL;
}

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

u8 *func_001FFF90(s32 unused0) {
    u8 *ret;

    ret = func_00197548(unused0);
    if (ret == NULL) {
        ret = D_002D0655;
    }
    return ret;
}

typedef struct Module_001FFFC0 {
    s32 name;
    s32 arg;
} Module_001FFFC0;

typedef struct File_001FFFC0 {
    s32 name;
    s32 unk4;
    s32 sector;
    s32 unkC[3];
    s32 size;
    s32 unk1C;
} File_001FFFC0;

typedef struct Stat_001FFFC0 {
    s32 sector;
    u32 size;
    s32 unk8[10];
} Stat_001FFFC0;

extern char D_002D0657[];
extern Module_001FFFC0 D_002CFCE0[];
extern char D_002D0638[];
extern File_001FFFC0 D_00293090[];
extern char D_002D066F[];

void func_0017E240(s32);
void func_00191778(s32);
s32 func_00183A38(char *);
s32 func_00183A00(void);
void func_00182838(void);
void func_00182CC8(void);
void func_00191C50(s32);
void func_0017FA60(void);
s32 func_00191A58(s32);
s32 func_00190FF0(Stat_001FFFC0 *, s32);
void func_00190C48(s32, u8 *, s32);
void func_00190A90(void (*)(void));
void func_00200170(void);

s32 func_001FFFC0(void) {
    extern s32 func_00200220(s32, s32);
    extern u8 D_0031C2F0[];
    u8 *buf = D_0031C2F0;
    s32 i;
    Module_001FFFC0 *mod;
    File_001FFFC0 *file;
    u32 j;
    Stat_001FFFC0 stat;

    func_0017E240(0);
    func_00191778(0);
    while (func_00183A38(D_002D0657) == 0) {
    }
    while (func_00183A00() == 0) {
    }
    func_0017E240(0);
    func_00182838();
    func_00182CC8();
    func_00191778(0);
    func_00191C50(2);
    func_0017FA60();
    while (func_00191A58(0) != 2) {
    }
    for (i = 0, mod = D_002CFCE0; mod->name != 0; i++) {
        if (func_00200220(mod->name, mod->arg) == 0) {
            return 0;
        }
        mod++;
    }
    if (func_00197548((s32)D_002D0638) != NULL) {
        file = D_00293090;
        for (j = 0; j < 0x61; j++) {
            while (func_00191A58(0) != 2) {
            }
            if (func_00190FF0(&stat, file->name) != 0) {
                file->sector = stat.sector;
                file->size = stat.size >> 11;
            } else {
                file->name = (s32)D_002D066F;
            }
            file++;
        }
    }
    func_00190C48(0, buf + 0x80, 0x4000);
    func_00190A90(func_00200170);
    return 1;
}

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

typedef struct State_00200360 {
    u8 pad[0x6684];
    char *file;
} State_00200360;

s32 func_00200360(s32 arg0) {
    extern State_00200360 D_0031C2F0;
    extern char D_002D0680[];
    extern char D_002D0686[];
    extern u8 *func_00197548();
    extern void func_0019B648(void *, void *, ...);
    State_00200360 *state = &D_0031C2F0;
    char path[128];
    u8 *directory;

    directory = func_00197548(D_002D0680);
    if (directory == NULL) {
        directory = D_002D0655;
    }
    func_0019B648(path, D_002D0686, directory, arg0);
    state->file = func_00217B60(path);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_054", func_002003E0);

typedef struct State_002004C0 {
    u8 pad[0x6684];
    s32 handle;
} State_002004C0;

s32 func_002004C0(s32 arg0) {
    extern State_002004C0 D_0031C2F0;
    State_002004C0 *state = &D_0031C2F0;

    if (arg0 < 0) {
        return 0;
    }
    if (state->handle != 0) {
        func_00217B50(state->handle);
        state->handle = 0;
    }
    return 1;
}

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

typedef struct Record_002007D0 {
    s32 value0;
    s32 value4;
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s16 index : 13;
    s16 valueA;
} Record_002007D0;

extern struct Entry_002008A0 D_003229A0[];

void func_002007D0(void) {
    Record_002007D0 *record;
    s32 i;

    record = (Record_002007D0 *)D_003229A0;
    func_0020B3C0((s8 *)&D_00322990, 0, 6);
    i = 0;
    do {
        record->value0 = 0;
        record->value4 = 0;
        record->flag0 = 0;
        record->flag1 = 0;
        record->flag2 = 0;
        record->index = record->valueA = -1;
        record++;
        i++;
    } while (i < 0x400);
}

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
