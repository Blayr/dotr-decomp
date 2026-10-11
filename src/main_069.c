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

typedef struct Buffer_00242E40 {
    s32 unk0;
    s32 unk4;
    u8 *data;
    s32 size;
} Buffer_00242E40;

typedef struct Ring_00242E40 {
    u8 pad[0x50008];
    s32 capacity;
} Ring_00242E40;

s32 func_00242F20(void *, s32, void *, s32, void *, s32, void *, s32);
void func_00243450(void *, s32);

s32 func_00242E40(s32 arg0, void *arg1, u8 *arg2) {
    u8 *data;
    s32 size;
    s32 firstSize;
    void *dst1;
    void *dst2;
    s32 dstSize1;
    s32 dstSize2;
    s32 capacity;
    u8 *end;
    s32 result;

    data = ((Buffer_00242E40 *)arg1)->data + 4;
    capacity = ((Ring_00242E40 *)arg2)->capacity;
    end = arg2 + capacity;
    if (data >= end) {
        data -= capacity;
    }
    size = ((Buffer_00242E40 *)arg1)->size - 4;
    firstSize = end - data;
    if (size < firstSize) {
        firstSize = size;
    }
    func_00243390(D_00350620, &dst1, &dstSize1, &dst2, &dstSize2);
    result = func_00242F20(dst1, dstSize1, dst2, dstSize2,
                          data, firstSize, arg2, size - firstSize);
    func_00243450(D_00350620, result);
    if (result > 0) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00242F20);

typedef struct {
    s32 unk0;
    u8 pad4[0x28];
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
} State_00243060;

s32 func_001828C0(s32);
extern char D_0030F600[];
extern char D_0030F61C[];
extern u8 D_003507C0[];

s32 func_00243060(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    State_00243060 *state = arg0;
    s32 temp_a1;
    s32 temp_a1_2;

    state->unk0 = 0;
    state->unk2C = 0;
    state->unk30 = arg1;
    state->unk34 = 0;
    state->unk38 = 0;
    state->unk3C = arg2;
    state->unk40 = 0;
    state->unk54 = 0;
    state->unk48 = arg3;
    state->unk4C = 0;
    state->unk50 = 0;
    state->unk44 = func_001828C0(arg3);
    temp_a1 = state->unk44;
    if (temp_a1 < 0) {
        func_00199B50(D_0030F600, temp_a1);
        return 0;
    }
    func_00199B50(D_0030F61C, temp_a1, arg3);
    state->unk58 = func_001828C0(0x800);
    temp_a1_2 = state->unk58;
    if (temp_a1_2 < 0) {
        func_00199B50(D_0030F600, temp_a1_2);
        return 0;
    }
    func_00199B50(D_0030F61C, temp_a1_2, 0x800);
    func_00198948(D_003507C0, 0, 0x800U);
    func_00243950(state->unk58, (s32) D_003507C0, 0x800);
    func_002439D0(0x3FFF);
    return 1;
}

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

typedef struct {
    s32 mode;
    u8 data[0x28];
    s32 offset;
    u8 *buffer;
    s32 start;
    s32 end;
    s32 capacity;
} Buffer_00243390;

void func_00243390(void *arg0, void **arg1, s32 *arg2, void **arg3, s32 *arg4) {
    s32 available;
    s32 capacity;
    s32 start;
    Buffer_00243390 *buffer = arg0;

    if (buffer->mode == 0) {
        *arg1 = (void *)((u32)buffer->data + buffer->offset);
        *arg2 = 0x28 - buffer->offset;
        *arg3 = buffer->buffer;
        *arg4 = buffer->capacity;
    } else {
        available = (capacity = buffer->capacity) - buffer->end;
        start = buffer->start;
        if ((capacity - start) >= available) {
            *arg1 = buffer->buffer + start;
            *arg2 = available;
            *arg3 = 0;
            *arg4 = 0;
        } else {
            *arg1 = buffer->buffer + start;
            *arg2 = buffer->capacity - buffer->start;
            *arg3 = buffer->buffer;
            *arg4 = available - (buffer->capacity - buffer->start);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00243450);

s32 func_00243580(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x54) >= *(s32 *)((u8 *)arg0 + 0x48);
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_002435A0);

typedef struct Range_00243750 {
    u8 padding[0x44];
    s32 start;
    s32 length;
    s32 cursor;
} Range_00243750;

void func_00243750(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, void *arg4, s32 offset) {
    Range_00243750 *range = arg4;
    s32 length = range->length;
    s32 cursor = range->cursor;

    offset = (((offset + length - cursor - 0x400) % length) >> 10) << 10;
    if (length - cursor >= offset) {
        *arg0 = range->start + cursor;
        *arg1 = offset;
        *arg2 = 0;
        *arg3 = 0;
    } else {
        *arg0 = range->start + cursor;
        *arg1 = range->length - range->cursor;
        *arg2 = range->start;
        *arg3 = offset - (range->length - range->cursor);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_002437F0);

s32 func_00243950(s32 arg0, s32 arg1, s32 arg2) {
    s32 request[4];
    s32 id;

    if (arg2 <= 0) {
        return 0;
    }
    request[0] = arg1;
    request[1] = arg0;
    request[2] = arg2;
    request[3] = 0;
    func_0017BB60(0);
    id = func_0017BCA0(request, 1);
    do {

    } while (func_0017BC80(id) >= 0);
    return arg2;
}

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

typedef struct {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    u32 attr;
    u32 option;
} Sema_00243EE0;

s32 func_0017B8E0(void *);

s32 func_00243EE0(void *arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Sema_00243EE0 sema;

    *(s32 *)arg0 = arg1;
    *(s32 *)((u8 *)arg0 + 4) = (arg2 & 0x0FFFFFFF) | 0x20000000;
    *(s32 *)((u8 *)arg0 + 8) = arg3;
    *(s32 *)((u8 *)arg0 + 0x18) = arg3 << 11;
    *(s32 *)((u8 *)arg0 + 0x50) = arg4;
    *(s32 *)((u8 *)arg0 + 0x54) = arg5;
    sema.init_count = 1;
    sema.max_count = 1;
    *(s32 *)((u8 *)arg0 + 0x40) = func_0017B8E0(&sema);
    func_00243F60(arg0);
    *(s64 *)((u8 *)arg0 + 0x48) = 0;
    return 1;
}

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

s32 func_00244530(u8 *arg0) {
    func_0017B920(*(s32 *)(arg0 + 0x40));
    *(s32 *)(arg0 + 0x44) = 0;
    func_001843E0();
    *(volatile u32 *)0x1000F590 = *(volatile u32 *)0x1000F520 | 0x10000;
    *(volatile u32 *)0x1000B400 = 5;
    *(volatile u32 *)0x1000F590 = *(volatile u32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
    *(s32 *)(arg0 + 0x1C) = *(volatile u32 *)0x1000B410;
    *(s32 *)(arg0 + 0x20) = *(volatile u32 *)0x1000B430;
    *(s32 *)(arg0 + 0x24) = *(volatile u32 *)0x1000B420;
    *(s32 *)(arg0 + 0x28) = *(volatile u32 *)0x1000B400;
    do {
    } while (*(volatile u32 *)0x10002010 & 0xF0);
    func_001843E0();
    *(volatile u32 *)0x1000F590 = *(volatile u32 *)0x1000F520 | 0x10000;
    *(volatile u32 *)0x1000B000 = 0;
    *(volatile u32 *)0x1000F590 = *(volatile u32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
    *(s32 *)(arg0 + 0x2C) = *(volatile u32 *)0x1000B010;
    *(s32 *)(arg0 + 0x30) = *(volatile u32 *)0x1000B020;
    *(s32 *)(arg0 + 0x34) = *(volatile u32 *)0x1000B000;
    *(s32 *)(arg0 + 0x38) = *(volatile u32 *)0x10002020;
    *(s32 *)(arg0 + 0x3C) = *(volatile u32 *)0x10002010;
    func_0017B900(*(s32 *)(arg0 + 0x40));
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244680);

s32 func_00244A40(void *arg0) {
    func_001843E0();
    *(volatile u32 *)0x1000F590 = *(volatile u32 *)0x1000F520 | 0x10000;
    *(volatile u32 *)0x1000B400 = 5;
    *(volatile u32 *)0x1000F590 = *(volatile u32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
    *(volatile u32 *)0x1000B420 = 0;
    *(volatile u32 *)0x1000B410 = 0;
    *(volatile u32 *)0x1000B430 = 0;
    func_0017B8F0(*(s32 *)((u8 *)arg0 + 0x40));
    return 1;
}

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

typedef struct Entry_00244B70 {
    s64 first;
    s64 second;
    s32 position;
    s32 length;
} Entry_00244B70;

typedef struct Queue_00244B70 {
    u8 pad0[8];
    s32 blocks;
    u8 padC[0x44];
    Entry_00244B70 *entries;
    s32 capacity;
    s32 count;
    s32 tail;
} Queue_00244B70;

static inline s32 clamp_00244B70(s32 count) {
    if (count < 0) {
        return 0;
    }
    return count;
}

s32 func_00244B70(void *arg0, void *arg1) {
    Queue_00244B70 *queue = arg0;
    Entry_00244B70 *request = arg1;
    s32 index;
    s32 repeat;
    s32 bufferSize;
    Entry_00244B70 *entry;
    s32 requestLength;
    s32 requestPosition;
    s32 position;
    s32 amount;
    s32 end;

    repeat = 1;
    index = (queue->capacity + (queue->tail - queue->count)) % queue->capacity;
    bufferSize = queue->blocks << 11;
    if (queue->count > 0) {
        do {
            entry = &queue->entries[index];
            amount = entry->length;
            if (amount == 0) {
                break;
            }
            requestLength = request->length;
            if (requestLength == 0) {
                break;
            }
            position = entry->position;
            requestPosition = request->position;
            if ((position + bufferSize - requestPosition) % bufferSize < requestLength) {
                end = requestPosition + requestLength - position;
                amount = amount < end ? amount : end;
                entry->position = (position + amount) % bufferSize;
                entry->length -= amount;
                if (entry->length == 0) {
                    if (entry->first >= 0) {
                        entry->first = -1;
                        entry->second = -1;
                        entry->position = 0;
                        entry->length = 0;
                    }
                    queue->count = clamp_00244B70(queue->count - 1);
                }
            } else {
                repeat = 0;
            }
            index = (index + 1) % queue->capacity;
        } while (repeat != 0);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244CB0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00244DE0);

s32 func_00244FB0(void *arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    func_0018EB08(arg0, arg1, arg2);
    func_0018EF20(arg0, 0, func_00245520, 0);
    func_0018EF20(arg0, 1, func_00245550, 0);
    func_0018EF20(arg0, 2, func_00245580, 0);
    func_0018EF20(arg0, 3, func_002455B0, 0);
    func_0018EF20(arg0, 5, (s32 (*)()) func_002455E0, 0);
    func_002450F0(arg0);
    func_00243EE0((u8 *)arg0 + 0x48, arg3, arg4, arg5, arg6, arg7);
    return 1;
}

s32 func_002450B0(void) {
    func_0018E200();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_069", func_002450D0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002450E0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_002450F0);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00245100);

INCLUDE_ASM("asm/nonmatchings/main_069", func_00245140);
