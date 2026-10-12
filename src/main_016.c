#include "common.h"

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00169420;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00169420;

s32 func_00169420(s32 arg0, void *arg1, void *arg2) {
    Obj1_00169420 *o1 = arg1;
    Obj2_00169420 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 k;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    func_0026FD30(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (o2->id == list[i] && func_0026FB10(arg0, list[i]) == 1) {
                o1->slot[0] = i;
            }
        }
    }
    k = 1;
    if ((func_0026FCE0(list[o1->slot[0]]) >> 5) == 0) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (func_00248F60(list[o1->slot[0]], list[i]) >= 0 && (func_0026FCE0(list[i]) >> 5) == 2) {
                    if (list[i] != 0x31B && list[i] != 0x31C) {
                        o1->slot[k] = i;
                        k++;
                    }
                }
            }
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_00169610);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00169A10);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00169FE0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016A5C0);

s32 func_0016AE30(s32 arg0, s32 arg1) {
    s32 kind;
    u32 *info;

    kind = func_001E1030();
    func_00250360(arg0, arg1);
    info = func_001E0B70(arg0, arg1, 0);
    func_001E1090(arg0, arg1);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 1) == 5) {
            return 2;
        }
        if (info == NULL) {
            return 2;
        }
        switch (*info >> 8) {
        case 0x27:
            if (func_001DE5C0(arg0) < 4) {
                return 1;
            }
            break;
        case 4:
            if (func_0016B0F0(arg0) == 1) {
                return 1;
            }
            break;
        }
        break;
    case 0:
        switch (kind) {
        case 0xE0:
        case 0x16C:
            if (func_001DE5C0(arg0) < 4) {
                return 1;
            }
            break;
        }
        break;
    }
    return 2;
}

s32 func_0016AFE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 minY;
    s32 maxY;
    s32 minX;
    s32 maxX;
    s32 result;

    minY = arg3 < arg5 ? arg3 : arg5;
    if (arg5 < arg3) {
        maxY = arg3;
    } else {
        maxY = arg5;
    }
    minX = arg2 < arg4 ? arg2 : arg4;
    if (arg4 < arg2) {
        maxX = arg2;
    } else {
        maxX = arg4;
    }
    if ((maxX - minX) + (maxY - minY) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        result = func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1);
        return result != 1 ? 0 : 1;
    }
    return 0;
}

s32 func_0016B0E0(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016B0F0);

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6[5];
    u8 padB;
    s32 unkC;
    u8 unk10;
} Req_0016B1F0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_0016B1F0;

s32 func_001678B0(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_0016B1F0(s32 arg0, void *arg1) {
    Req_0016B1F0 req;
    Work_0016B1F0 *w;
    s32 i;
    s32 ret;

    w = arg1;
    req.unk0 = 0xFFFF;
    req.unk2 = 0xFF;
    req.unk4 = 0xFFFF;
    req.unkC = 0;
    req.unk10 = 0xFF;
    if (w == NULL) {
        return 0x800;
    }
    for (i = 0; i < 5; i++) {
        req.unk6[i] = 0xFF;
    }
    w->count++;
    if (w->count == 600) {
        return 0x20;
    }
    if (w->count == 601) {
        return 0x20;
    }
    if (w->count == 602) {
        return 0x20;
    }
    if (!(w->count < 603)) {
        return 0x800;
    }
    if (w->idx == 0) {
        func_00275E80(w);
        if (func_001678B0(w, &req, arg0) == 0) {
            return 0x800;
        }
        if (func_00276290(w, &req, arg0) < 0) {
            return 0;
        }
    }
    ret = w->list[w->idx - 1];
    if (ret == 0xFFFF) {
        return 0;
    }
    if (w->list[w->idx] == 0xFFFF) {
        w->idx = 0;
        for (i = 0; i < 32; i++) {
            w->list[i] = 0xFFFF;
        }
    } else {
        w->idx++;
    }
    return (u16)ret;
}

#define MAX_0016B3C0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_0016B3C0(a, b) ((a) < (b) ? (a) : (b))

s32 func_0016B3C0(s32 arg0) {
    extern s32 func_001E1580(s32, s32);
    extern s32 func_001E1640(s32, s32);
    s32 pos;
    s32 x0;
    s32 y0;
    u16 *p;
    s32 x;
    s32 y;
    s32 bestPos;
    s32 i;
    s32 best;
    u32 obj;
    s32 score;
    s32 cur;
    s32 found;
    u16 list[22];

    pos = func_001E1090(arg0 == 0 ? 1 : 0, 0);
    if (func_00266DF0(0x39) > 0) {
        return -1;
    }
    obj = func_00272210(func_0024CA40(0, 0, arg0, 2, 0x21, 0xE), arg0);
    p = list;
    for (i = 0; i < 22; i++) {
        p[i] = 0xFFFF;
    }
    func_0027C070(arg0 == 0 ? 1 : 0, list, 0x34, 0);
    found = -1;
    bestPos = found;
    best = 1;
    i = 0;
    if (i < func_0027C670(list)) {
        x0 = pos >> 8;
        y0 = pos & 0xFF;
        do {
            cur = func_001E1090(*p >> 8, *p & 0xFF);
            x = cur >> 8;
            y = cur & 0xFF;
            if (MAX_0016B3C0(y0, y) - MIN_0016B3C0(y0, y) + (MAX_0016B3C0(x0, x) - MIN_0016B3C0(x0, x)) == 1) {
                if (func_001E2100(*p >> 8, *p & 0xFF, 1) == 0 &&
                    func_001E1580(*p >> 8, *p & 0xFF) == 0 &&
                    func_001E1640(*p >> 8, *p & 0xFF) == 0) {
                    if ((score = func_002509E0(*p >> 8, *p & 0xFF, y, x)) >= best) {
                        bestPos = *p;
                        if (bestPos == func_0024EC50(obj, 0)) {
                            found = bestPos;
                        }
                        best = score;
                    }
                }
            }
            p++;
            i++;
        } while (i < func_0027C670(list));
    }
    if (bestPos < 0) {
        return -1;
    }
    return ((u16)bestPos << 16) | (u16)found;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016B610);

s32 func_0016C6B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 best_other;
    s32 best_own;
    s32 list;
    s32 i;
    s32 card;
    s32 lo;
    s32 hi;
    s32 value;

    for (i = 0; i < 22; i++) {
    }
    best_own = -1;
    best_other = -1;
    list = func_0024CA40(0, 0, arg0, arg1, arg2, 14);
    for (i = 0; i < func_0024E910(list); i++) {
        card = func_0024EC50(list, i);
        hi = card >> 8;
        lo = card & 0xFF;
        if (arg0 == func_00250360(hi, lo)) {
            value = func_002509E0(hi, lo, func_001E1090(hi, lo) & 0xFF, func_001E1090(hi, lo) >> 8);
            if (best_own < value) {
                best_own = value;
            }
        } else {
            value = func_002509E0(hi, lo, func_001E1090(hi, lo) & 0xFF, func_001E1090(hi, lo) >> 8);
            if (best_other < value) {
                best_other = value;
            }
        }
    }
    if (best_own < best_other && best_other > 2500) {
        return 1;
    }
    if (arg1 & 1) {
        if (func_0024E910(func_0024CA40(0, 0, arg0, 1, arg2, 14)) > 0) {
            return 0;
        }
    }
    if (arg1 >> 1) {
        if (func_0024E910(func_0024CA40(0, 0, arg0, 2, arg2, 14)) > 3) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016C8F0);

s32 func_0016CBB0(s32 arg0, s32 *arg1) {
    u16 cells[0x16];
    s32 first;
    s32 second;
    s32 pos;
    s32 y;
    s32 i;
    s32 list;
    s32 x;
    u8 count;
    s32 cell;
    s32 col;
    s32 row;
    s32 j;

    for (j = 0; j < 0x16; j++) {
        cells[j] = 0xFFFF;
    }
    switch (*arg1 & 0x3F) {
    case 0x1D:
        func_0027C2C0((arg0 == 0) ? 1 : 0, cells, 0x1D, 0, 0);
        first = func_0027B650(cells);
        for (j = 0; j < 0x16; j++) {
            cells[j] = 0xFFFF;
        }
        func_0027C070(arg0, cells, 0x1D, 1);
        second = func_0027B650(cells);
        if (first >= 0 && second >= 0) {
            pos = func_001E1090(first >> 8, first & 0xFF);
            if (func_002781F0(first, second, pos & 0xFF, pos >> 8) >= 0) {
                return pos;
            }
        }
        break;
    case 0x1E:
        for (x = 0; x < 7; x++) {
            for (y = 0; y < 7; y++) {
                count = 0;
                list = func_0024CA40(x, y, arg0, 1, 0x34, 0x12);
                for (i = 0; i < func_0024E910(list); i++) {
                    cell = func_0024EC50(list, i);
                    row = cell >> 8;
                    col = cell & 0xFF;
                    if (func_001E2100(row, col, 4) == 0) {
                        count++;
                    } else if ((func_001E0700(row, col) >> 5) != 0) {
                        count++;
                    }
                }
                if (count > 2) {
                    return (y << 8) | x;
                }
            }
        }
        break;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016CE00);

s32 func_0016CF10(s32 arg0) {
    return ((u32) (arg0 - 0x36) < 4U) ? 1 : 0;
}

s32 func_0016CF30(s32 arg0) {
    extern s32 func_001E1030();

    if (func_001E1030(arg0, 0) == 0x3A) {
        if (func_002151D0(arg0, func_002158B0(arg0), 0x36) >= 0 && func_002151D0(arg0, func_002158B0(arg0), 0x37) >= 0 && func_002151D0(arg0, func_002158B0(arg0), 0x38) >= 0 && func_002151D0(arg0, func_002158B0(arg0), 0x39) >= 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016CFF0);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016D140);

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016D6A0);

s32 func_0016D8C0(u16 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 pos;
    s32 ret;
    s32 idx;
    u16 list[22];

    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1D, 1);
    ret = func_0027B360(arg1, list, arg0);
    if (ret >= 0) {
        return ret;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1E, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if ((func_001E0700(list[i] >> 8, list[i] & 0xFF) >> 5) == 3 &&
            func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    pos = arg1 << 8;
    idx = func_00276C80(arg0, pos);
    func_0016D6A0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0016F4D0(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0016F4D0(pos, arg1, arg2) >= 0) {
        return pos | 0x10000;
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_001E2100(list[i] >> 8, list[i] & 0xFF, 0) == 0 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    return -1;
}

void func_0016DCA0(u16 *arg0) {
    s32 temp_s1;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v1;

    temp_v0 = *arg0;
    if (func_001DF540((s32) temp_v0 >> 8, temp_v0 & 0xFF) != 0) {
        temp_v0_2 = *arg0;
        temp_s1 = ((func_0024DE70((s32) temp_v0_2 >> 8, temp_v0_2 & 0xFF) == 0) ? 1 : 0) << 8;
        temp_v1 = *arg0;
        func_001E1090((s32) temp_v1 >> 8, temp_v1 & 0xFF);
        func_001E1090(temp_s1 >> 8, temp_s1 & 0xFF);
        temp_v0_3 = *arg0;
        func_001DF540((s32) temp_v0_3 >> 8, temp_v0_3 & 0xFF);
        temp_v0_4 = *arg0;
        if (func_001E0290((s32) temp_v0_4 >> 8, temp_v0_4 & 0xFF, 0) >= 0x9C4) {
            func_0016DDA0(arg0);
            return;
        }
        temp_v0_5 = *arg0;
        if (func_0016E000((s32) temp_v0_5 >> 8, temp_v0_5 & 0xFF, 1) == 1) {
            func_0016E0E0(arg0, 1);
            return;
        }
        func_0016DDA0(arg0, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016DDA0);

s32 func_0016E000(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s3;
    s32 var_s4;
    s32 packed;

    if ((arg2 & 0xFF) == 1) {
        var_s4 = 3;
    } else {
        var_s4 = 4;
    }
    packed = (arg0 << 8) | arg1;
    var_s3 = 1;
    for (;;) {
        temp_v0 = func_001E3790(var_s3, var_s4);
        if (temp_v0 != 0) {
            if (temp_v0 == packed) {
                return 1;
            }
            temp_s2 = func_00250360(temp_v0 >> 8, temp_v0 & 0xFF);
            if (temp_s2 == func_00250360(arg0, arg1)) {
                return 0;
            }
        }
        var_s3++;
        if (var_s3 > 5) {
            break;
        }
    }
    return 1;
}

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_0016E0E0;

void func_0016E0E0(u16 *arg0, s32 arg1) {
    u8 work[112];
    Slot_0016E0E0 slots[22];
    s16 b;
    s16 a;
    s32 i;
    s32 target;
    s32 player;
    s32 enemy;
    s32 position;
    s32 enemyPos;
    s32 owner;
    u16 *record = arg0;
    extern s32 func_0027B200();
    extern s32 func_0016E4B0();
    extern void func_0027E770();

    if ((arg1 & 0xFF) == 1) {
        target = 3;
    } else {
        target = 4;
    }
    func_001E1090((s32) record[0] >> 8, record[0] & 0xFF);
    if (func_001DF540((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        player = func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF);
        enemy = (player == 0 ? 1 : 0) << 8;
        position = func_001E1090((s32) record[0] >> 8, record[0] & 0xFF);
        enemyPos = func_001E1090(enemy >> 8, enemy & 0xFF);
        owner = func_001DF540((s32) record[0] >> 8, record[0] & 0xFF);
        func_0027E770(work);
        for (i = 0; i < 22; i++) {
            slots[i].position = 0xFFFF;
            slots[i].flag = 0xFF;
        }
        if (func_0027B200((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                          enemy >> 8, enemy & 0xFF, enemyPos & 0xFF, enemyPos >> 8, 2) > 0) {
            record[2] = 0x2FF;
            *(u32 *) (record + 4) = (enemy << 16) | record[4];
            return;
        }
        a = 0;
        b = 0;
        i = 1;
        while (1) {
            switch (func_0016E4B0(record, 0, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i,
                                  func_00172310(player), slots, 0, &b, &a, 2, work)) {
            case 3:
                record[2] = 0x6FF;
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            case 2:
                record[2] = 0x3FF;
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            case 1:
                return;
            case 0:
                record[2] = 0x3FF;
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            }
            i++;
            if (i > 2) {
                break;
            }
        }
        if ((position >> 8) == target) {
            switch ((u8) (record[2] >> 8)) {
            case 16:
                if ((position & 0xFF) > 1) {
                    *(u32 *) (record + 4) = ((position >> 8) << 24) | record[4];
                } else {
                    record[2] = 0xFFF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 5) << 16) | record[4];
                }
                break;
            case 15:
                if ((position & 0xFF) < 5) {
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 5) << 16) | record[4];
                } else {
                    record[2] = 0x10FF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 1) << 16) | record[4];
                }
                break;
            default:
                if (func_0019A5C8() % 2 == 0) {
                    record[2] = 0x10FF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 1) << 16) | record[4];
                } else {
                    record[2] = 0xFFF;
                    *(u32 *) (record + 4) = ((((position >> 8) << 8) | 5) << 16) | record[4];
                }
                break;
            }
            return;
        }
        record[2] = 0x6FF;
        *(u32 *) (record + 4) = record[4] | (((target << 8) | (position & 0xFF)) << 16);
    }
}

void func_0016E4B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016E510);

void func_0016F240(u16 *arg0) {
    extern s32 func_001E1030();
    extern s32 func_001F9FE0();
    s32 id;
    s32 value;
    s32 *effect;
    s32 position;
    s32 result;
    u32 action;

    func_001E0700(arg0[0] >> 8, arg0[0] & 0xFF);
    id = func_001E1030(arg0[0] >> 8, arg0[0] & 0xFF);
    value = func_00250360(arg0[0] >> 8, arg0[0] & 0xFF);
    effect = func_00250740(arg0[0] >> 8, arg0[0] & 0xFF, 0);
    position = func_001E1090(arg0[0] >> 8, arg0[0] & 0xFF);
    action = *(u32 *)effect;
    switch (action >> 8) {
    case 0x14:
        arg0[2] = 0xCFF;
        return;
    case 4:
        result = func_0016CBB0(value, effect);
        if (result >= 0) {
            arg0[2] = 0x6FF;
            if (!(effect[0] & 0x3F)) {
                *(u32 *)&arg0[4] = arg0[4] | ((((position >> 8) << 8) | (result & 0xFF)) << 16);
            } else {
                *(u32 *)&arg0[4] = (result << 16) | arg0[4];
            }
            return;
        }
        break;
    case 2:
        result = func_0027C770(func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF),
            position & 0xFF, position >> 8, *((u8 *)effect + 4), 8, 2);
        if (result >= 0) {
            arg0[2] = 0x6FF;
            *(u32 *)&arg0[4] = (result << 16) | arg0[4];
            return;
        }
        break;
    case 0x25:
        if ((action & 0x3F) == 0x21) {
            if (func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF) != 0) {
                id = ((func_0024DE70(arg0[0] >> 8, arg0[0] & 0xFF) == 0) ? 1 : 0) << 8;
                func_001E1090(arg0[0] >> 8, arg0[0] & 0xFF);
                func_001E1090(id >> 8, id & 0xFF);
                func_001DF540(arg0[0] >> 8, arg0[0] & 0xFF);
                if (func_001E0290(arg0[0] >> 8, arg0[0] & 0xFF, 0) >= 0x9C4) {
                    func_0016DDA0(arg0);
                } else {
                    if (func_0016E000(arg0[0] >> 8, arg0[0] & 0xFF, 1) == 1) {
                        func_0016E0E0(arg0, 1);
                    } else {
                        func_0016DDA0(arg0);
                    }
                }
            }
            return;
        }
        break;
    case 0x1F:
        if (id == 0x2DC) {
            arg0[2] = 0xDFF;
            return;
        }
        break;
    default:
        break;
    }
    arg0[2] = 0x5FF;
}

typedef struct {
    s16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_0016F4D0;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0016F4D0;

s32 func_0016F760(s32 arg0, void *arg1);
s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 func_0016F4D0(s32 arg0, s32 arg1, s32 arg2) {
    s32 ret;
    s32 kind;
    Ctx_0016F4D0 *ctx = (Ctx_0016F4D0 *)arg2;
    Work_0016F4D0 work;
    s32 res;
    extern s32 func_00278890();

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_0016F760(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 2;
    arg0 = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (func_0016FEF0(arg1, (u8 *)ctx, &work) >= 0) {
            ret = func_00276F10(&work, arg0 & 0xFF, arg0 >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00172310(arg1));
            if (ret < 0) {
                if (func_001E0150(arg1) < 5) {
                    res = func_00170620(arg1, (u8)kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = func_00170620(arg1, (u8)kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = func_00276F10(&work, arg0 & 0xFF, arg0 >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00172310(arg1));
    }
    if (kind == 2) {
        func_001703E0(arg1, ctx, &work);
        res = func_00170620(arg1, (u8)kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (func_0016FCF0(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_00170620(arg1, (u8)kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_0016F760);

s32 func_0016FC00(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;

    func_0026FD30(arg0, entries);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (((arg3 & 0xFFFF) == entries[i]) && (func_0026FB10(arg0, entries[i]) == 1)) {
            *((s8 *)arg1 + 6) = i;
            func_001DCD70(arg2, entries[i]);
            return func_0026FCE0(entries[i]) >> 5;
        }
    }
    return -1;
}

s32 func_0016FCF0(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
    s32 buf[8];
    s32 i;

    func_0026FD30(arg0, buf);
    if (arg2 == NULL) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        arg1[i + 6] = 0xFF;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (arg3 == buf[i] && arg3 != 999) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(buf[i]) >> 5) != 0 && (func_0026FCE0(buf[i]) >> 5) != 2) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(buf[i]) >> 5) != 0) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    return -1;
}

typedef struct Info_0016FEF0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0016FEF0;

typedef struct Sprite_0016FEF0 {
    Info_0016FEF0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0016FEF0;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_0016FEF0(s32 arg0, u8 *arg1, void *arg2) {
    u16 *nodes[8];
    s32 entries[7];
    s16 a;
    s16 b;
    s32 i;
    s32 card;
    s32 value;
    s32 best;

    if (arg2 == NULL) {
        return -1;
    } else {
        s32 top;
        s32 *entry;
        u16 **node;

        func_0026FD30(arg0, entries);
        best = -1;
        top = -1;
        i = 0;
        if (i < func_0026FE20(arg0)) {
            entry = entries;
            node = nodes;
            do {
                b = 0;
                a = 0;
                card = *entry;
                *node = NULL;
                if ((func_0026FCE0(card) >> 5) == 0) {
                    *node = func_00278A90(arg0, *node, i & 0xFF, card & 0xFFFF, 0, &a, &b);
                    *node = func_00278E40(*node);
                    value = func_00278F10(arg0, *node, 0, 0);
                    if (func_0026FB10(arg0, card) == 1) {
                        if (best < value) {
                            func_001700D0(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_0016FEF0 *)arg2)->x = (value >> 16) - (((Sprite_0016FEF0 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0016FEF0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0016FEF0 *)arg2)->info->y & 0x1FFF);
                            best = value;
                            if (top < value) {
                                top = value;
                            }
                        }
                    } else if (top < value) {
                        top = value;
                    }
                }
                entry++;
                node++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
        return top;
    }
}

s32 func_001702B0(s32 arg0);

typedef struct {
    u16 id;
    u8 values[5];
} Info_001700D0;

void func_001700D0(s32 arg0, void *arg1, s32 *arg2) {
    Info_001700D0 *info = arg1;
    u8 buf[5];
    s32 count;
    s32 i;
    s32 card;
    u8 level;
    u32 cost;
    extern u32 func_0026FBB0();

    if (info != NULL) {
        level = func_0026FA80(info->id, arg0);
        for (i = 0; i < 5; i++) {
            buf[i] = 0xFF;
        }
        for (i = 0, count = 0; i < func_0026FE20(arg0); i++) {
            if ((u8)func_00278E00(i, info->values) == 0) {
                buf[count++] = i;
            }
        }
        if (count != 0) {
            for (i = 0; i < (u8)func_00278D90(buf); i++) {
                card = arg2[buf[i]];
                if (card != 0x3E7 && func_001702B0(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xFA1 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_001702B0);

s64 func_002493A0(s32);

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_001703E0;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_001703E0;

s32 func_001703E0(s32 arg0, void *arg1, void *arg2) {
    Obj1_001703E0 *o1 = arg1;
    Obj2_001703E0 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 k;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    func_0026FD30(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (i != o1->slot[0] && i != o1->slot[1]) {
            if (o2->id == list[i] && func_0026FB10(arg0, list[i]) == 1) {
                o1->slot[0] = i;
            }
        }
    }
    k = 1;
    if ((func_0026FCE0(list[o1->slot[0]]) >> 5) == 0) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (func_00248F60(list[o1->slot[0]], list[i]) >= 0 && (func_0026FCE0(list[i]) >> 5) == 2) {
                    if (list[i] != 0x31B && list[i] != 0x31C) {
                        o1->slot[k] = i;
                        k++;
                        o2->f38 += (s16)func_002493A0(list[i]);
                        o2->f3A += (s16)func_002493A0(list[i]);
                    }
                }
            }
        }
    }
    return 1;
}

void func_00170610(void) {
    func_0024E410();
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00170620;

typedef struct {
    u8 pad[0x3E];
    u8 f3E;
} Card_00170620;

s32 func_0024FE40(void *, s32, s32);

s32 func_00170620(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    extern s32 func_00278510();
    extern s32 func_0027A130(s32, void *, s32, s32, s32, s32, s32, s32, u8, u16);
    extern s32 func_002792C0(s32, void *, s32, s32, s32, s32, u16, u8);
    Card_00170620 *card = arg2;
    Nibbles_00170620 entries[12];
    s32 id;
    s32 hi;
    s32 lo;
    s32 i;
    Nibbles_00170620 *entry;
    s32 pos;
    s32 cost;
    s32 bestId;
    s32 best;
    s32 y;
    s32 x;
    s32 j;
    s32 slot;

    if (card == NULL) {
        return -1;
    }
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    if ((u8)(card->f3E >> 5) == 0 && arg3 >= 0) {
        best = 0xFF;
        bestId = 0xFFFF;
        pos = func_001E1090(arg3 >> 8, arg3 & 0xFF);
        for (i = 0; i < 8; i++) {
            id = func_0024E410(arg0, i);
            if (id < 0) {
                continue;
            }
            lo = id & 0xFF;
            hi = id >> 8;
            if (func_001E22B0(lo, hi) == 8) {
                continue;
            }
            if (func_001E22B0(lo, hi) == 9 && func_0024FE40(card, lo, hi) == 1) {
                continue;
            }
            if (func_001E36E0(lo, hi) != 0) {
                continue;
            }
            if (func_00278510(card, arg3, func_00172310(arg0), pos & 0xFF, pos >> 8, 0) > 0) {
                cost = func_0027A130((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, arg3, 0, 3,
                                     func_00172310(arg0));
            } else {
                cost = func_002792C0((s32)card, entries, lo, hi, pos & 0xFF, pos >> 8, arg3, 3);
            }
            if (func_0027AFC0((u8 *)entries) > 0 && cost < best) {
                best = cost;
                bestId = id;
            }
        }
        if (bestId != 0xFFFF) {
            return bestId;
        }
    }
    for (j = 0; j < 8; j++) {
        slot = func_0024E410(arg0, j);
        if (slot < 0) {
            continue;
        }
        x = slot & 0xFF;
        y = slot >> 8;
        if (func_001E22B0(x, y) == 8) {
            continue;
        }
        if (func_001E22B0(x, y) == 9 && func_0024FE40(card, x, y) == 1) {
            continue;
        }
        if (func_001E3790(x, y) < 0) {
            return slot;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_00170940);

INCLUDE_ASM("asm/nonmatchings/main_016", func_00170F10);

INCLUDE_ASM("asm/nonmatchings/main_016", func_001714F0);

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00171D60;

typedef struct {
    u16 source;
    s8 command;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 count;
    s8 value;
} Output_00171D60;

s32 func_0016C8F0(s32, s32, s32);
s32 func_00170940(u16 *, s32, void *, s32);
void func_001E1E70(s32, s32, s32, s32);
s32 func_0027DBC0(s32, s32, s32);

s32 func_00171D60(u16 *arg0, s32 arg1, void *arg2, s32 arg3) {
    extern void func_0027B1B0();
    s32 address;
    s32 result;
    s32 index;
    Nibbles_00171D60 buffer[12];
    Nibbles_00171D60 *p;
    Output_00171D60 *out = arg2;

    {
    u32 *item;
    s32 state;

    state = (func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) & 0xFF;
    if (state == 0) {
        item = func_001E0B70(*arg0 >> 8, *arg0 & 0xFF, 3);
    } else {
        item = func_001E0B70(*arg0 >> 8, *arg0 & 0xFF, 0);
    }
    address = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    p = buffer;
    index = 0;
    do {
        p->low = p->high = 15;
        p++;
        index++;
    } while (index < 12);

    if (item != NULL) {
        result = func_0016C8F0(arg1, (*item >> 6) & 3, *item & 0x3F);
        if (state != 0) {
            if (func_001E22B0(address & 0xFF, address >> 8) == 9) {
                result = -1;
            }
            if (func_0027D830(*arg0 >> 8, *arg0 & 0xFF, 0, 0, 6, 0) == 5) {
                result = -1;
            }
        }
        if (result >= 0) {
            address = (result >> 16) & 0xFFFF;
            state = func_0027DBC0(address, result & 0xFF, *item & 0x3F);
            out->source = *arg0;
            out->command = 12;
            out->value = func_0027E360(*arg0 >> 8, *arg0 & 0xFF,
                out->target, 1, 0);
            out->count = 1;
            if (((*item >> 6) & 3) != 3) {
                out->target = (arg1 << 8) | state;
            } else {
                out->target = (address << 8) | state;
            }
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }
    if (state != 0) {
        if (func_001E2100(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            func_001E1E70(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
            out->source = *arg0;
            out->command = 14;
            return 0;
        }
    }
    return func_00170940(arg0, arg1, arg2, arg3);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_00172000);

static inline s32 max_00172210(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00172210(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00172210(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00172210(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        if (func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1) != 1) {
            return 0;
        }
        return 1;
    }
    return 0;
}

s32 func_00172310(s32 arg0) {
    if (func_001DF470(arg0) > 0x4B0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x3E8;
        } else {
            return 0x7D0;
        }
    } else {
        return 0x960;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_016", func_00172370);
