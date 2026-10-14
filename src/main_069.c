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

void func_00242900(void) {
    func_0017B790(0x20);
}

s32 func_00242910(void) {
    if (D_0029B2F0 != 0) {
        return func_00243580(D_00350620);
    }
    return 1;
}

typedef struct ThreadParams_00242950 {
    s32 attr;
    void (*entry)();
    s32 stack;
    s32 stack_size;
    void *gp;
    s32 priority;
    s32 current_priority;
    s32 status;
    s32 option;
} ThreadParams_00242950;

extern s32 func_0017B5C0(s32, void (*)(), s32);
extern s32 func_0017B5F0(s32, void (*)(), s32);
extern s32 func_0017B6E0(void *);
extern void func_0017B700(s32, void *);
extern void func_001906D0(void);
extern void func_00242190(void);
extern void func_002423A0(void);
extern char D_0030F39A[];
extern u8 D_00317EF0[];
extern s32 D_00350730;
extern s32 D_00350734;
extern s32 D_00350778;
extern s32 D_00350780;

void func_00242950(s32 arg0) {
    ThreadParams_00242950 thread;
    extern s32 func_00190810();
    extern s32 func_00244FB0();
    extern s32 func_002450B0(void *, s32, s32, void (*)(), s32);
    extern void func_00245770();

    *(s32 *)0x1000E000 |= 3;
    *(s32 *)0x1000E010 = 4;
    func_00241A90((void *)D_00350788);
    func_0018EA68();
    func_00244FB0(D_00350680, D_00350380, 0x1C9168, D_00350398,
                 D_00350378, 0x100, D_003503A8, 0x200);
    func_001906D0();
    func_00190810(1, 0x8000, 0);
    func_00243060(D_00350620, D_00350390, 0xC000, 0x6000);
    func_002450B0(D_00350680, 0, 0, (void (*)())func_00242D10, D_00350788);
    if (D_0029B2F0 != 0) {
        func_002450B0(D_00350680, 2, 0, (void (*)())func_00242E40, D_00350788);
    }
    func_00245770(D_00350600,
                 ((u64)((s64)D_00350368 << 36) >> 36) | 0x20000000,
                 (void *)D_00350370, 2);
    thread.entry = func_00242CD0;
    thread.stack = D_00350388;
    thread.stack_size = 0x800;
    thread.priority = 0x20;
    thread.gp = D_00317EF0;
    thread.option = 0;
    D_00350778 = func_0017B6E0(&thread);
    func_0017B700(D_00350778, NULL);
    thread.entry = (void (*)())func_002452E0;
    thread.stack = D_003503A0;
    thread.stack_size = 0x4000;
    thread.priority = 0x20;
    thread.gp = D_00317EF0;
    thread.option = 0;
    D_00350780 = func_0017B6E0(&thread);
    func_0017B700(D_00350780, D_00350680);
    if (func_00243A90(D_00350740, arg0) == 0) {
        do {
            func_00199B50(D_0030F39A, arg0);
        } while (func_00243A90(D_00350740, arg0) == 0);
    }
    D_00350734 = func_0017B5C0(2, func_00242190, 0);
    func_0017C428(2);
    D_00350730 = func_0017B5F0(2, func_002423A0, 0);
    func_0017C4F8(2);
}

void func_00242C20(void) {
    extern void func_00241AC0();
    extern void func_002457C0();
    extern s32 func_0017B730(s32);
    extern s32 func_0017B6F0(s32);
    extern s32 func_0017C490(s32);
    extern s32 func_0017B610(s32, s32);
    extern s32 func_0017C3C0(s32);
    extern s32 func_0017B5E0(s32, s32);
    extern s32 D_00350730;
    extern s32 D_00350734;
    extern s32 D_00350778;
    extern s32 D_00350780;

    func_00241AC0(D_00350788);
    func_002457C0(D_00350600);
    func_0017B730(D_00350780);
    func_0017B6F0(D_00350780);
    func_0017B730(D_00350778);
    func_0017B6F0(D_00350778);
    func_0017C490(2);
    func_0017B610(2, D_00350730);
    func_0017C3C0(2);
    func_0017B5E0(2, D_00350734);
    func_00245100(D_00350680);
    func_00243170(D_00350620);
    func_00243D90(D_00350740);
}

void func_00242CD0(void) {
loop_1:
    func_0017B790(0x20);
    goto loop_1;
}

void func_00242CF0(s8 *arg0) {
    func_00199B50(D_0030F3AE, arg0);
}

void func_00242D00(void) {
    func_002435A0(D_00350620);
}

typedef struct Buffer_00242D10 {
    s32 unk0;
    s32 unk4;
    u8 *data;
    u32 size;
    s64 unk10;
    s64 unk18;
} Buffer_00242D10;

typedef struct Ring_00242D10 {
    u8 pad[0x50008];
    s32 capacity;
} Ring_00242D10;

s32 func_00242D10(s32 arg0, void *arg1, u8 *arg2) {
    extern s32 func_00245160();
    extern char D_0030F5E0[];
    Ring_00242D10 *ring;
    Buffer_00242D10 *buffer;
    u8 *data;
    u32 avail;
    u32 first;
    u32 rest;
    s32 dst1;
    s32 dst2;
    s32 dstSize1;
    s32 dstSize2;
    s32 result;

    ring = (Ring_00242D10 *)arg2;
    buffer = (Buffer_00242D10 *)arg1;
    data = buffer->data;
    avail = (u8 *)ring + ring->capacity - data;
    first = buffer->size;
    first = (first < avail) ? first : avail;
    rest = ((Buffer_00242D10 *)arg1)->size - first;
    func_002450D0(D_00350680, &dst1, &dstSize1, &dst2, &dstSize2);
    result = func_00242F20((void *)((dst1 & 0x0FFFFFFF) | 0x20000000), dstSize1,
                           (void *)((dst2 & 0x0FFFFFFF) | 0x20000000), dstSize2,
                           data, first, ring, rest);
    if (result > 0 && func_00245160(D_00350680, ((Buffer_00242D10 *)arg1)->unk10,
                                    ((Buffer_00242D10 *)arg1)->unk18, dst1, result) == 0) {
        func_00242CF0(D_0030F5E0);
    }
    func_002450E0(D_00350680, result);
    return (result > 0) ? 1 : 0;
}

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

s32 func_00242F20(void *arg0, s32 arg1, void *arg2, s32 arg3,
                  void *arg4, s32 arg5, void *arg6, s32 arg7) {
    s32 gap;

    if ((arg1 + arg3) < (arg5 + arg7)) {
        return 0;
    }
    if (arg5 >= arg1) {
        func_00198790(arg0, arg4, arg1);
        func_00198790(arg2, (const u8 *)arg4 + arg1, arg5 - arg1);
        func_00198790((u8 *)arg2 + arg5 - arg1, arg6, arg7);
    } else {
        gap = arg1 - arg5;
        if (arg7 >= gap) {
            func_00198790(arg0, arg4, arg5);
            func_00198790((u8 *)arg0 + arg5, arg6, gap);
            func_00198790(arg2, (const u8 *)arg6 + arg1 - arg5, arg7 - gap);
        } else {
            func_00198790(arg0, arg4, arg5);
            func_00198790((u8 *)arg0 + arg5, arg6, arg7);
        }
    }
    return arg5 + arg7;
}

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

void func_002431B0(void *arg0) {
    s32 *p = (s32 *)arg0;
    s32 func_00190810(s32, ...);

    p[0] = 3;
    func_00243A40(0);
    p[0x14] = (func_00190810(1, 0x80E0, 0, 2, 0, 0) & 0xFFFFFF) - p[0x11];
    func_00190810(1, 0x80D0, 0, 0, p[0x16], 0x4000, 0x800);
}

void func_00243230(void *arg0) {
    s32 *p = (s32 *)arg0;
    s32 func_00190810(s32, s32, s32, s32, s32, s32, s32);
    func_00243A40(0x7FFF);
    func_00190810(1, 0x80E0, 0, 0x13, p[0x11], (p[0x12] >> 10) << 10, p[0x11] + p[0x14]);
    *(s32 *)arg0 = 2;
}

void func_00243290(void *arg0) {
    s32 *p = (s32 *)arg0;
    s32 func_00190810(s32, s32, s32, s32, s32, s32, s32);
    func_00243A40(0x7FFF);
    func_00190810(1, 0x80E0, 0, 0x13, p[0x11], (p[0x12] >> 10) << 10, p[0x11] + p[0x14]);
    *(s32 *)arg0 = 2;
}

void func_002432F0(void *arg0) {
    s32 *p = (s32 *)arg0;
    s32 func_00190810(s32, ...);

    p[0] = 3;
    func_00243A40(0);
    p[0x14] = (func_00190810(1, 0x80E0, 0, 2, 0, 0) & 0xFFFFFF) - p[0x11];
    func_00190810(1, 0x80D0, 0, 0, p[0x16], 0x4000, 0x800);
    p[0] = 0;
    p[0xB] = 0;
    p[0xD] = 0;
    p[0xE] = 0;
    p[0x10] = 0;
    p[0x15] = 0;
    p[0x13] = 0;
    p[0x14] = 0;
}

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

typedef struct State_00243450 {
    s32 printed;
    s8 byteParams[4];
    s32 wordParams[7];
    s8 moreByteParams[4];
    s32 moreWordParam;
    u32 delay;
    s32 unused;
    s32 position;
    s32 elapsed;
    s32 period;
    s32 total;
} State_00243450;

extern char D_0030F645[];
extern char D_0030F676[];
extern char D_0030F7B1[];

void func_00243450(void *arg0, u32 arg1) {
    u32 amount;
    State_00243450 *state;

    state = arg0;
    if (state->printed == 0) {
        amount = 0x28 - state->delay;
        amount = amount < arg1 ? amount : arg1;
        state->delay += amount;
        if (state->delay >= 0x28U) {
            state->printed = 1;
            func_00199B50(D_0030F645);
            func_00199B50(D_0030F676,
                state->byteParams[0], state->byteParams[1],
                state->byteParams[2], state->byteParams[3],
                state->wordParams[0], state->wordParams[1],
                state->wordParams[2], (s64)state->wordParams[3],
                (s64)state->wordParams[4], (s64)state->wordParams[5],
                (s64)state->wordParams[6]);
            func_00199B50(D_0030F7B1,
                state->moreByteParams[0], state->moreByteParams[1],
                state->moreByteParams[2], state->moreByteParams[3],
                state->moreWordParam);
        }
        arg1 -= amount;
    }
    state->position = (s32)(state->position + arg1) % state->period;
    state->elapsed += arg1;
    state->total += arg1;
}

s32 func_00243580(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x54) >= *(s32 *)((u8 *)arg0 + 0x48);
}

typedef struct Stream_002435A0 {
    s32 kind;
    u8 pad04[0x2C];
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    u8 pad40[4];
    s32 f44;
    s32 f48;
    s32 f4C;
    u8 pad50[4];
    s32 f54;
} Stream_002435A0;

s32 func_002435A0(void *arg0) {
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 result = 0;
    s32 pos;
    s32 avail;
    s32 first;
    s32 rest;
    Stream_002435A0 *st;

    extern s32 func_00190810(s32, ...);

    st = arg0;
    switch (st->kind) {
    case 0:
        return 0;
    case 1:
        sp30 = st->f44 + (st->f54 % st->f48);
        sp38 = st->f48 - st->f54;
        sp34 = 0;
        sp3C = 0;
        break;
    case 2:
        func_00243750(&sp30, &sp38, &sp34, &sp3C, st, (func_00190810(1, 0x8100, 0) & 0xFFFFFF) - st->f44);
        break;
    case 3:
        return 0;
    }

    pos = st->f30 + (st->f3C + (st->f34 - st->f38)) % st->f3C;
    avail = (st->f38 >> 10) << 10;
    first = st->f30 + st->f3C - pos;
    if (avail < first) {
        first = avail;
    }
    rest = avail - first;
    if (sp38 + sp3C >= 0x400 && first + rest >= 0x400) {
        result = func_002437F0(sp30, sp38, sp34, sp3C, pos, first, st->f30, rest);
    }
    st->f38 = st->f38 - result;
    st->f54 = st->f54 + result;
    st->f4C = (st->f4C + result) % st->f48;
    return result;
}

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

s32 func_002437F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;

    temp_v0 = arg1 + arg3;
    temp_v1 = arg5 + arg7;
    if (temp_v0 < temp_v1) {
        temp_v1_2 = temp_v1 - temp_v0;
        if (temp_v1_2 >= arg7) {
            arg5 -= temp_v1_2 - arg7;
            arg7 = 0;
        } else {
            arg7 -= temp_v1_2;
        }
    }
    if (arg5 >= arg1) {
        func_00243950(arg0, arg4, arg1);
        func_00243950(arg2, arg4 + arg1, arg5 - arg1);
        func_00243950((arg2 + arg5) - arg1, arg6, arg7);
    } else {
        temp_s0 = arg1 - arg5;
        if (arg7 >= temp_s0) {
            func_00243950(arg0, arg4, arg5);
            func_00243950(arg0 + arg5, arg6, temp_s0);
            func_00243950(arg2, (arg6 + arg1) - arg5, arg7 - temp_s0);
        } else {
            func_00243950(arg0, arg4, arg5);
            func_00243950(arg0 + arg5, arg6, arg7);
        }
    }
    return arg5 + arg7;
}

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

typedef struct File_00243A90 {
    s32 disc;
    s32 size;
    s32 handle;
    s32 disc_size;
    u8 pad10[0x1C];
    u32 allocation;
    s32 fd;
} File_00243A90;

s32 func_0017FA98(const char *, s32);
void func_0017FD20(s32);
s32 func_0017FEA0(s32, s32, s32);
s32 func_001828C0(s32);
s32 func_00190FF0(void *, const char *);
s32 func_00191A58(s32);
s32 func_0019BC90(const char *, const char *);
s32 func_0019D9E0(s32);
extern char D_0030F7F0[];
extern char D_0030F7F7[];
extern char D_0030F7F8[];
extern char D_0030F800[];
extern char D_0030F806[];
extern char D_0030F80C[];
extern char D_0030F816[];
extern char D_0030F839[];
extern char D_0030F854[];
extern char D_0030F86F[];

s32 func_00243A90(void *arg0, s32 arg1) {
    extern void func_0019B648();
    char path[256];
    char prefix[76];
    u8 mode[3];
    char *separator;
    File_00243A90 *file = arg0;

    separator = func_001976D8((char *)arg1, ':');
    if (separator != NULL) {
        s32 prefix_length;

        prefix_length = separator - (char *)arg1;
        func_0019C2B8(prefix, (char *)arg1, prefix_length);
        prefix[prefix_length] = 0;
        if (func_0019BC90(prefix, D_0030F7F0) == 0) {
            s32 i;
            s32 length;
            char *current;
            char *suffix;

            length = func_0019BEF0(separator + 1);
            file->disc = 1;
            for (i = 0; i < length; i++) {
                current = separator + i + 1;
                if (*current == '/') {
                    *current = '\\';
                }
                *current = func_0019D9E0(*current);
            }
            suffix = func_001976D8((char *)arg1, ';') ? D_0030F7F7 : D_0030F7F8;
            func_0019B648(path, D_0030F7F8 + 3, separator + 1, suffix);
        } else {
            file->disc = 0;
            func_0019B648(path, D_0030F800, prefix, separator + 1);
        }
    } else {
        func_0019BDD8(prefix, D_0030F806);
        file->disc = 0;
        func_0019B648(path, D_0030F800, prefix, arg1);
    }
    func_00199B50(D_0030F80C, path);
    if (file->disc != 0) {
        do {
        } while (func_00191A58(0) != 2);
        file->allocation = func_001828C0(0x28010);
        func_00191F90(0x50, 5, ((file->allocation + 0xF) >> 4) << 4);
        if (func_00190FF0(&file->handle, path) == 0) {
            func_00199B50(D_0030F816, path);
            return 0;
        }
        file->size = file->disc_size;
        mode[0] = 0;
        mode[1] = 0;
        mode[2] = 0;
        func_00191FC0(file->handle, mode);
    } else {
        file->fd = func_0017FA98(path, 1);
        if (file->fd < 0) {
            func_00199B50(D_0030F839, path);
            return 0;
        }
        file->size = func_0017FEA0(file->fd, 0, 2);
        if (file->size < 0) {
            func_00199B50(D_0030F854, path, file->size);
            func_0017FD20(file->fd);
            return 0;
        }
        if (func_0017FEA0(file->fd, 0, 0) < 0) {
            func_00199B50(D_0030F86F, path);
            func_0017FD20(file->fd);
            return 0;
        }
    }
    return 1;
}

typedef struct {
    s32 unk00;
    u8 pad04[0x28];
    s32 unk2C;
    s32 unk30;
} Obj_00243D90;

void func_0017FD20(s32);

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

typedef struct {
    f32 value;
} Float_00243DE0;

s32 func_001800D8(s32, s32, s32);
s32 func_00191A58(s32);
s32 func_00192090(s32, s32, s32, s32 *);
extern Float_00243DE0 D_0029B2F8;

s32 func_00243DE0(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Float_00243DE0 sp48;
    s32 sp4C;
    s32 result;

    if (*arg0 != 0) {
        sp48 = D_0029B2F8;
        while (1) {
            func_0017BB60(0);
            result = func_00192090(arg2 >> 11, arg1, 1, &sp4C);
            if (sp4C == 0) {
                break;
            }
            if (D_0029B2F0 != 0) {
                func_002431B0(D_00350620);
            }
            func_00192058();
            while (func_00191A58(0) != 2 || func_00191FC0(arg3, (u8 *)&sp48) == 0) {
            }
            if (D_0029B2F0 != 0) {
                func_00243230(D_00350620);
            }
        }
        result <<= 11;
    } else {
        result = func_001800D8(arg0[12], arg1, arg2);
    }
    return result;
}

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

typedef struct Buffer_002440F0 {
    s32 base;
    s32 unknown04;
    s32 blockCount;
    s32 blockOffset;
    s32 reservedBlocks;
    s32 byteOffset;
    s32 capacity;
    u8 padding1C[0x24];
    s32 semaphore;
} Buffer_002440F0;

void func_002440F0(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    Buffer_002440F0 *buffer = arg0;
    s32 byteOffset;
    s32 start;
    s32 offset;
    s32 length;

    func_0017B920(buffer->semaphore);
    byteOffset = buffer->byteOffset;
    start = (buffer->blockOffset + buffer->reservedBlocks) << 11;
    offset = (start + byteOffset) % buffer->capacity;
    length = ((buffer->blockCount - 2 - buffer->reservedBlocks) << 11) - byteOffset;
    if (buffer->capacity - offset >= length) {
        *arg1 = buffer->base + offset;
        *arg2 = length;
        *arg3 = 0;
        *arg4 = 0;
    } else {
        *arg1 = buffer->base + offset;
        *arg2 = buffer->capacity - offset;
        *arg3 = buffer->base;
        *arg4 = length - (buffer->capacity - offset);
    }
    func_0017B900(buffer->semaphore);
}

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

typedef struct Ring_00244250 {
    u8 *data;
    u8 *tags;
    s32 count;
    s32 read;
    s32 used;
    s32 bytes;
    u8 pad[0x28];
    s32 sema;
    s32 active;
} Ring_00244250;

extern s8 D_0030F890;

static inline u64 tag_00244250(u32 address, u32 id) {
    return ((u64)address << 32) | ((u64)id << 28) | 0x80;
}

s32 func_00244250(void *arg0) {
    s32 chcr;
    s32 patched;
    u32 current;
    s32 count;
    s32 consumed;
    s32 head;
    s32 index;
    s32 blocks;
    s32 last;
    s32 i;
    s32 id;
    Ring_00244250 *ring = arg0;

    patched = 0;
    func_0017B920(ring->sema);
    if (ring->active == 0) {
        func_00242CF0(&D_0030F890);
        return 0;
    }

    func_001843E0();
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 | 0x10000;
    *(volatile s32 *)0x1000B400 = 5;
    *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 & 0xFFFEFFFF;
    func_00184428();
    chcr = *(volatile s32 *)0x1000B400;
    count = ring->count;
    current = *(volatile s32 *)0x1000B410;
    if (current == ((u32)(ring->tags + (count + 1) * 16) & 0x0FFFFFFF)) {
        current = 0;
    } else {
        current = (u32)(current - (u32)ring->data) >> 11;
    }
    head = ring->read;
    consumed = (s32)(current + count - head) % count;
    ring->read = (head + consumed) % count;
    ring->used -= consumed;
    index = (ring->read + ring->used) % ring->count;
    blocks = ring->bytes >> 11;
    ring->bytes %= 2048;

    if (blocks > 0) {
        last = (ring->count + (ring->read + ring->used - 1)) % ring->count;
        patched = 1;
        *(u64 *)(ring->tags + last * 16) = tag_00244250((u32)ring->data + (last << 11), 3);
    }
    for (i = 0; i < blocks; i++) {
        if (i == blocks - 1) {
            id = 0;
        } else {
            id = 3;
        }
        *(u64 *)(ring->tags + index * 16) = tag_00244250((u32)ring->data + (index << 11), id);
        index = (index + 1) % ring->count;
    }

    ring->used += blocks;
    if (ring->used != 0) {
        if (patched != 0) {
            chcr = (chcr & 0x0FFFFFFF) | 0x30000000;
        }
        func_001843E0();
        *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 | 0x10000;
        *(volatile s32 *)0x1000B400 = chcr | 0x100;
        *(volatile s32 *)0x1000F590 = *(volatile s32 *)0x1000F520 & 0xFFFEFFFF;
        func_00184428();
    }
    func_0017B900(ring->sema);
    return 1;
}

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

typedef struct Record_00244CB0 {
    s64 value0;
    s64 value8;
    s32 value10;
    s32 value14;
} Record_00244CB0;

typedef struct Queue_00244CB0 {
    u8 padding0[0x40];
    s32 semaphore;
    u8 padding44[0xC];
    Record_00244CB0 *records;
    s32 capacity;
    s32 count;
    s32 tail;
} Queue_00244CB0;

void func_0017B900(s32);
void func_0017B920(s32);

s32 func_00244CB0(void *arg0, void *arg1) {
    Record_00244CB0 *record = arg1;
    Queue_00244CB0 *queue = arg0;
    s32 result = 0;

    func_0017B920(queue->semaphore);
    if (queue->count < queue->capacity) {
        func_00244B70(queue, record);
        if (record->value0 >= 0 || record->value8 >= 0) {
            queue->records[queue->tail].value0 = record->value0;
            queue->records[queue->tail].value8 = record->value8;
            queue->records[queue->tail].value10 = record->value10;
            queue->records[queue->tail].value14 = record->value14;
            queue->count++;
            queue->tail = (queue->tail + 1) % queue->capacity;
        }
        result = 1;
    }
    func_0017B900(queue->semaphore);
    return result;
}

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

void func_002450D0(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    func_002440F0((u8 *)arg0 + 0x48, arg1, arg2, arg3, arg4);
}

void func_002450E0(void *arg0, s32 arg1) {
    func_002441F0((u8 *)arg0 + 0x48, arg1);
}

void func_002450F0(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0xA8) = 0;
}

s32 func_00245100(u8 *arg0) {
    s32 func_0018ED10(void *);

    func_00244A40(arg0 + 0x48);
    func_0018ED10(arg0);
    return 1;
}

void func_00245140(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0xA8) = 1;
}
