#include "common.h"

s32 func_00242580(s32 arg0) {
    s32 temp_a1;

    temp_a1 = D_003503B8;
    D_003503B8 = temp_a1 + 1;
    func_00199B50(D_0030F354, temp_a1);
    func_00242950(arg0);
    func_00242600(D_00350680, D_00350788, D_00350740);
    func_00242C20();
    return D_003505F0;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242600);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242900);

s32 func_00242910(void) {
    if (D_0029B2F0 != 0) {
        return func_00243580(D_00350620);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242950);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242C20);

void func_00242CD0(void) {
loop_1:
    func_0017B790(0x20);
    goto loop_1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242CF0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242D00);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242D10);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242E40);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242F20);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243060);

s32 func_00243170(void *arg0) {
    func_00182A28(*(s32 *)((u8 *)arg0 + 0x44));
    func_00182A28(*(s32 *)((u8 *)arg0 + 0x58));
    func_002439D0(0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_002431B0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243230);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243290);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002432F0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243390);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243450);

s32 func_00243580(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x54) >= *(s32 *)((u8 *)arg0 + 0x48);
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_002435A0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243750);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002437F0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243950);

void func_002439D0(s32 arg0) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_00190810(1, 0x8010, var_s0 | 0x980, arg0);
        func_00190810(1, 0x8010, var_s0 | 0xA80, arg0);
        var_s0 += 1;
    } while (var_s0 < 2);
}

void func_00243A40(s32 arg0) {
    func_00190810(1, 0x8010, 0xF80, arg0);
    func_00190810(1, 0x8010, 0x1080, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243A90);

typedef struct {
    s32 unk00;
    u8 pad04[0x28];
    s32 unk2C;
    s32 unk30;
} Obj_00243D90;

void func_0017FD20(s32);
void func_00182A28(s32);
void func_00192058(void);

s32 func_00243D90(void *arg0) {
    Obj_00243D90 *p = (Obj_00243D90 *)arg0;

    if (p->unk00 != 0) {
        func_00192058();
        func_00182A28(p->unk2C);
    } else {
        func_0017FD20(p->unk30);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243DE0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243EE0);

typedef struct {
    s64 a;
    s64 b;
    s32 c;
    s32 d;
} Ent_00243F60;

typedef struct {
    u64 tag;
    u64 pad;
} Tag_00243F60;

typedef struct {
    u32 base;
    Tag_00243F60 *tags;
    s32 nTags;
    s32 f0C;
    s32 f10;
    s32 f14;
    u8 pad18[0x2C];
    s32 f44;
    u8 pad48[8];
    Ent_00243F60 *ents;
    s32 nEnts;
    s32 f58;
    s32 f5C;
} Obj_00243F60;

void func_001843E0(void);
void func_00184428(void);

s32 func_00243F60(void *arg0) {
    Obj_00243F60 *obj = arg0;
    s32 i;

    obj->f0C = 0;
    obj->f10 = 0;
    obj->f14 = 0;
    obj->f44 = 1;
    obj->f58 = 0;
    obj->f5C = 0;
    for (i = 0; i < obj->nEnts; i++) {
        obj->ents[i].a = -1;
        obj->ents[i].b = -1;
        obj->ents[i].c = 0;
        obj->ents[i].d = 0;
    }
    for (i = 0; i < obj->nTags; i++) {
        obj->tags[i].tag = ((u64)((obj->base + i * 0x800) & 0x0FFFFFFF) << 32) | 0x30000080;
    }
    obj->tags[i].tag = ((u64)((u32)obj->tags & 0x0FFFFFFF) << 32) | 0x20000000;
    *(u32 *)0x1000B420 = 0;
    *(u32 *)0x1000B410 = obj->base & 0x0FFFFFFF;
    *(u32 *)0x1000B430 = (u32)obj->tags & 0x0FFFFFFF;
    func_001843E0();
    *(u32 *)0x1000F590 = *(u32 *)0x1000F520 | 0x10000;
    *(u32 *)0x1000B400 = 5;
    *(u32 *)0x1000F590 = *(u32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_002440F0);

typedef struct Counter_002441F0 {
    u8 pad0[0x14];
    s32 count;
    u8 pad18[0x28];
    s32 semaphore;
    u8 pad44[4];
    s64 total;
} Counter_002441F0;

void func_0017B900(s32);
void func_0017B920(s32);

void func_002441F0(void *arg0, s32 arg1) {
    Counter_002441F0 *counter = arg0;

    func_0017B920(counter->semaphore);
    counter->count += arg1;
    counter->total += arg1;
    func_0017B900(counter->semaphore);
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244250);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244530);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244680);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244A40);

typedef struct Data_00244AD0 {
    u8 pad_00[0x10];
    s32 field_10;
    s32 field_14;
    u8 pad_18[0x28];
    s32 field_40;
} Data_00244AD0;

void func_0017B900(s32);
void func_0017B920(s32);

s32 func_00244AD0(void *arg0) {
    Data_00244AD0 *data = arg0;
    s32 temp_s0;

    func_0017B920(data->field_40);
    temp_s0 = data->field_14 + (data->field_10 << 11);
    func_0017B900(data->field_40);
    return temp_s0;
}

void func_0017B900(s32);
void func_0017B920(s32);

typedef struct State_00244B20 {
    u8 pad_00[0x14];
    s32 field_14;
    u8 pad_18[0x28];
    s32 field_40;
} State_00244B20;

void func_00244B20(void *arg0) {
    State_00244B20 *state = arg0;

    func_0017B920(state->field_40);
    state->field_14 = ((state->field_14 + 0x7FF) >> 11) << 11;
    func_0017B900(state->field_40);
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244B70);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244CB0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244DE0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244FB0);

s32 func_002450B0(void) {
    func_0018E200();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_002450D0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002450E0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002450F0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00245100);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00245140);
