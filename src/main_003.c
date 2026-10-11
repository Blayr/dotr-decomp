#include "common.h"

s32 func_00109CA0(s32 arg0) {
    D_0030FF40 = (s32 *)arg0;
    D_0030FF48 = arg0 + 0x2A80;
    func_00198948(D_0030FF40, 0, 0x2A80);
    *(s32 *)((u8 *)D_0030FF40 + 0x1DC) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x1F4) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x2248) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x2254) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x224C) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x2258) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x2250) = -1;
    *(s32 *)((u8 *)D_0030FF40 + 0x225C) = -1;
    func_0010BDC0();
    func_00109A90();
    return 1;
}

void func_00109D50(void) {
    func_0010C720(0xF004, D_0030FF40[5]);
}

void func_00109D70(s32 arg0) {
    if (arg0 != 0) {
        func_0010A160(0, 0);
        func_0010C720(0x5004, 0x7FFF);
    }
    func_0010C720(0xF006, arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_00109DC0);

s32 func_00109E80(s32 arg0, s32 arg1) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return 0;
    }
    if (!(D_0030FF40[1] & 2)) {
        return 1;
    }
    if (D_0030FF40[0] & 1) {
        if (arg1 != 0) {
            func_0010B490();
        } else {
            func_0010B3C0();
        }
    }
    return 1;
}

s32 func_00109F10(void) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return 0;
    }
    return (*D_0030FF40 & 0x2000) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_00109F60);

INCLUDE_ASM("asm/nonmatchings/main_003", func_00109FC0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A010);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A090);

static inline u32 flags_0010A0F0(void) {
    if (D_0030FF40 == NULL) {
        return 0;
    }
    return *(u32 *)D_0030FF40;
}

s32 func_0010A0F0(void) {
    if (D_0030FF40 == NULL || D_0030FF48 == 0) {
        return 0;
    }
    if ((u64)flags_0010A0F0() & 0x100) {
        return D_0030FF40[0x1EC / sizeof(s32)];
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A160);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A1D0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A280);

void func_0010A390(s32 arg0, s32 arg1, s32 arg2) {
    func_0010A280(arg0, arg1, 0, 0, 0, arg2);
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A3B0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A450);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A4D0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A780);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A8A0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A8B0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010A8D0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010AC20);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010ADB0);

s32 func_0010B1F0(void) {
    D_0030FF40[0] |= 0x100;
    D_0030FF40[0x1FC / 4] &= ~4;
    D_0030FF40[0x1D4 / 4] = 0;
    D_0030FF40[0x2254 / 4] = D_0030FF40[0x1DC / 4];
    func_0010C720(0x1020, D_0030FF40[0x14 / 4], 0x40000, 1);
    return 1;
}

s32 func_0010B270(void) {
    s32 temp_v1;

    if (!(D_0030FF40[1] & 2)) {
        return 0;
    }
    temp_v1 = D_0030FF40[0];
    if (temp_v1 & 0x100) {
        D_0030FF40[0] = temp_v1 & ~0x100;
        D_0030FF40[0] &= ~0x200;
        *(s32 *)((u8 *)D_0030FF40 + 0x18) = 0;
        *(s32 *)((u8 *)D_0030FF40 + 0x1C4) = 0;
        *(s32 *)((u8 *)D_0030FF40 + 0x1C0) = 0;
        func_0010C720(0x1021);
        *(s32 *)((u8 *)D_0030FF40 + 0x1D4) = 0;
        *(s32 *)((u8 *)D_0030FF40 + 0x1D8) = 0;
        *(s32 *)((u8 *)D_0030FF40 + 0x2254) = -1;
    }
    return 1;
}

void func_0010B330(void) {
    s32 temp_a0;

    temp_a0 = *D_0030FF40;
    if (!(temp_a0 & 0x10)) {
        *D_0030FF40 = temp_a0 | 0x10;
    }
}

void func_0010B360(void) {
    if (!(D_0030FF40[0] & 0x40)) {
        func_0010C720(0x5000);
        D_0030FF40[0] |= 0x40;
        D_0030FF40[0x7A] = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010B3C0);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010B490);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010B6C0);

s32 func_0010BBC0(void) {
    if (D_0030FF40 == NULL) {
        return 0;
    }
    if (!(D_0030FF40[1] & 4)) {
        return 0;
    }
    if (D_0030FF40[0] & 1) {
        return func_0010BCC0();
    }
    return 0;
}

void func_0010BC30(s32 arg0, s32 arg1) {
    *(s32 *)((u8 *)D_0030FF40 + 0x20B4) = arg0;
    func_0019B648((u8 *)D_0030FF40 + 0x2070, D_002B90B0, arg1);
    func_0010C110((u8 *)D_0030FF40 + 0x2070, (u8 *)D_0030FF48 + 0x101800, 0, 0x80800);
    *D_0030FF40 |= 0x4000;
    *(s32 *)((u8 *)D_0030FF40 + 0x20B0) = 0x1E;
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BCC0);

s32 func_0010BD40(s32 *arg0, void *arg1) {
    s32 temp_v1_2;
    s8 temp_v1;

    temp_v1 = *(s8 *)((u8 *)D_0030FF40 + 0x20C5);
    if (temp_v1 == *(s8 *)((u8 *)D_0030FF40 + 0x20C4)) {
        return 0;
    }
    *(s8 *)((u8 *)D_0030FF40 + 0x20C5) = (s8)((temp_v1 + 1) & 7);
    temp_v1_2 = temp_v1 << 5;
    *arg0 = *(s32 *)(temp_v1_2 + (u32)D_0030FF40 + 0x20C8);
    func_0019C2B8(arg1, (u8 *)D_0030FF40 + temp_v1_2 + 0x20CC, 0x1C);
    return 1;
}

void func_0010BDC0(void) {
    *((s8 *)D_0030FF40 + 0x20C5) = 0;
    *((s8 *)D_0030FF40 + 0x20C4) = 0;
}

s32 func_0010BDE0(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = D_0030FF40[0x1710 / sizeof(s32)];
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = D_0030FF40[0x171C / sizeof(s32)];
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

s32 func_0010BE20(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = *(s32 *)((u8 *)D_0030FF40 + 0x1820);
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = *(s32 *)((u8 *)D_0030FF40 + 0x182C);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010BE60);

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C110);

typedef struct QueueEntry_0010C220 {
    s32 value0;
    s32 value1;
    s32 value2;
    s32 unused;
} QueueEntry_0010C220;

typedef struct Queue_0010C220 {
    u8 padding[0x1720];
    QueueEntry_0010C220 entries[16];
    s32 count;
    s32 write_index;
} Queue_0010C220;

void func_0010C220(s32 arg0, s32 arg1, s32 arg2) {
    QueueEntry_0010C220 *entry;

    entry = &((Queue_0010C220 *)D_0030FF40)->entries[((Queue_0010C220 *)D_0030FF40)->write_index];
    entry->value0 = arg0;
    entry->value1 = arg1;
    entry->value2 = arg2;
    ((Queue_0010C220 *)D_0030FF40)->write_index = (((Queue_0010C220 *)D_0030FF40)->write_index + 1) % 16;
    ((Queue_0010C220 *)D_0030FF40)->count++;
}

s32 func_0010C290(void) {
    s32 var_v0;

    var_v0 = 1;
    if ((D_0030FF40[0x5C4] == 0) && (D_0030FF40[0x5C7] == 0)) {
        var_v0 = 0;
    }
    return var_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C2C0);

s32 func_0010C2D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (!(arg1 & 0xF)) {
        if ((arg2 % 2048) == 0) {
            if ((arg3 % 2048) == 0) {
                D_0030FFA0 = 0;
                D_0030FFA4 = 0;
                D_0030FFA8 = 0;
                D_0030FFAC = 0;
                D_0030FFB0 = 0;
                func_00199B50(D_002B90C0, arg0, arg1);
                if (func_00200510(arg0, arg2, arg3, arg1, func_0010C580, 0, 0x20) == 0) {
                    return -1;
                }
            }
        }
    }
    D_0030FF58 = 1;
    return 1;
}

s32 func_0010C3D0(s32 file, s32 destination, s32 position, s32 size) {
    s32 handle;
    s32 blockStart;
    s32 blockOffset;
    s32 blockSize;
    s32 totalSize;
    s32 copySize;

    func_00199B50(D_002B90DA, file, destination, position, size);
    func_00199B50(D_002B9102);
    if ((handle = func_00200360(file)) < 0) {
        return 0;
    }
    if ((destination & 0xF) || (position % 0x800) || (size % 0x800)) {
        while (size > 0) {
            blockStart = (position >> 11) << 11;
            totalSize = position - blockStart;
            totalSize += size;
            blockSize = totalSize < 0x80001 ? totalSize : 0x80000;
            blockOffset = position - blockStart;
            size = totalSize - blockSize;
            position = blockStart + blockSize;
            func_00199B50(D_002B9112, file, handle);
            func_002003E0(handle, blockStart, ((blockSize + 0x7FF) >> 11) << 11, 0x04000000);
            copySize = blockSize - blockOffset;
            func_00198790((void *)destination, (u8 *)0x04000000 + blockOffset, copySize);
            destination += copySize;
        }
    } else {
        func_00199B50(D_002B9127);
        func_002003E0(handle, position, size, destination);
    }
    func_00199B50(D_002B9135);
    func_002004C0(handle);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C580);

typedef char *VaList_0010C720;
#define VA_START_0010C720(ap, parm) \
    ((ap) = (char *)__builtin_next_arg(parm) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8))
#define VA_ARG_0010C720(ap, T) (*(T *)((ap += 8) - 8))

extern s32 func_0017EA80(s32 *, s32, s32, s32 *, s32, s32 *, s32, s32, s32);

s32 func_0010C720(s32 cmd, ...) {
    s32 id;
    s32 i;
    VaList_0010C720 ap;

    if (D_0030FF40 == NULL) {
        return 0;
    }
    id = cmd;
    VA_START_0010C720(ap, cmd);
    D_0030FF40[0x20] = (s32)&D_0030FF40[0x20];
    for (i = 1; i < 7; i++) {
        D_0030FF40[0x20 + i] = VA_ARG_0010C720(ap, s32);
    }
    return func_0017EA80(&D_0030FF40[7], id, 0, &D_0030FF40[0x20], 0x40, &D_0030FF40[0x60], 0x10, 0, 0);
}

s32 func_0010C800(s32 arg0, s32 arg1, s32 arg2) {
    func_0017BB60(0);
    D_0030FF40[0x11] = arg0;
    D_0030FF40[0x12] = arg1;
    D_0030FF40[0x13] = arg2;
    D_0030FF40[0x14] = 0;
    D_0030FF40[0x19] = func_0017BCA0(&D_0030FF40[0x11], 1);
    return D_0030FF40[0x19];
}

INCLUDE_ASM("asm/nonmatchings/main_003", func_0010C8A0);

s32 func_0010C8B0(void) {
    s32 count;

    do {
        if (func_0017E8B0((u8 *)D_0030FF40 + 0x1C, 0x05730601, 0) < 0) {
            for (;;) {
            }
        }
        count = 1000000;
        while (count-- != 0) {
        }
    } while (D_0030FF40[0x10] == 0);
    func_0017BB60(0);
    return 1;
}
