#include "common.h"

typedef struct {
    u16 pos;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
} Unit_00135790;

void func_001360E0(void *);
void func_0027CA50(void *, s32, s32, s32);

s32 func_00135790(void *arg0) {
    extern s32 func_001E1030();
    Unit_00135790 *unit = arg0;

    func_00250360(unit->pos >> 8, unit->pos & 0xFF);
    if (func_001DF540(unit->pos >> 8, unit->pos & 0xFF) != 0 &&
        func_001E2100(unit->pos >> 8, unit->pos & 0xFF, 0) == 0 && unit->pos != 0xFFFF) {
        if ((unit->pos & 0xFF) == 0) {
            if (unit->unk8 == -1) {
                if (func_0027BBC0(unit->pos >> 8, unit->pos & 0xFF, 1) == 1) {
                    if (func_001DE6D0(unit->pos >> 8) == 1) {
                        unit->unk4 = 0x50A;
                    } else {
                        unit->unk4 = 0x5FF;
                    }
                } else {
                    if (func_001DE6D0(unit->pos >> 8) == 1) {
                        unit->unk4 = 0xA05;
                    } else {
                        unit->unk4 = 0x5FF;
                    }
                }
            }
        } else {
            switch (func_001E0700(unit->pos >> 8, unit->pos & 0xFF) >> 5) {
            case 0:
                if (func_001E1030(unit->pos >> 8, unit->pos & 0xFF) == 0xBD) {
                    func_00136010(unit);
                } else {
                    func_00135D50(unit, 1);
                }
                break;
            case 2:
                func_0027CA50(unit, 2, 1, 0);
                break;
            case 1:
                func_001360E0(unit);
                break;
            case 3:
                func_00136010(unit);
                break;
            default:
                unit->unk4 = 0x5FF;
                break;
            }
        }
        return 1;
    }
    return 0;
}

s32 func_00135970(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_00135790(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00136210(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00136210(pos, arg1, arg2) >= 0) {
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

typedef union {
    u32 word;
    struct {
        u16 low;
        u16 high;
    } halves;
} Data_00135D50;

typedef struct {
    u16 coordinates;
    u16 unk2;
    s16 state;
    u16 unk6;
    Data_00135D50 data;
} Entry_00135D50;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_00135D50;

void func_00135D50(void *arg0, s32 arg1) {
    extern void func_0027E770();
    extern s32 func_0027B200();
    extern s32 func_00135FB0();
    Entry_00135D50 *entry = arg0;
    s32 pos;
    s32 otherPos;
    s32 other;
    s32 player;
    s32 i;
    u8 work[0x70];
    Slot_00135D50 list[22];
    s16 countA;
    s16 countB;
    Slot_00135D50 *slot;

    if (func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        other = (func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0) << 8;
        pos = func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = func_001E1090(other >> 8, other & 0xFF);
        player = func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF);
        slot = list;
        i = 0;
        do {
            i++;
            slot->card = 0xFFFF;
            slot->flag = 0xFF;
            slot++;
        } while (i < 22);
        func_0027E770(work);
        if (arg1 != 0) {
            if (func_0027B200(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                              other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 2) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (func_00135FB0(entry, 0, player, pos & 0xFF, pos >> 8,
                                  func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, 0, list, 0, &countA, &countB, 2, work)) {
            case 3:
                entry->state = 0x6FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 2:
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            case 1:
                return;
            case 0:
                entry->state = 0x5FF;
                return;
            }
            i++;
            if (i > 2) {
                break;
            }
        }
        entry->state = 0x5FF;
        return;
    }
}

void func_00135FB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  1, 0x898, arg_sp28);
}

void func_00136010(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_00136060(arg0);
    if (temp_v0 >= 0) {
        *(s16 *)((u8 *)arg0 + 4) = 0x3FF;
        *(u32 *)((u8 *)arg0 + 8) = (temp_v0 << 16) | *(u16 *)((u8 *)arg0 + 8);
        return;
    }
    *(s16 *)((u8 *)arg0 + 4) = 0x5FF;
}

s32 func_00136060(void *arg0) {
    if (func_001E36E0(2, 2) == 0 && func_001E22B0(2, 2) != 8) {
        return 0x202;
    }
    if (func_001E36E0(5, 2) == 0 && func_001E22B0(5, 2) != 8) {
        return 0x205;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_001360E0);

typedef struct {
    u8 data[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00136210;

typedef struct {
    s16 id;
    u8 kind;
    u8 pad3;
    s16 value;
    u8 pad6[6];
    s32 unkC;
} Ctx_00136210;

s32 func_00136B80(s32, void *, void *);

s32 func_00136210(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_00278890();
    Work_00136210 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00136210 *ctx = (Ctx_00136210 *)arg2;

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_00136490(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->kind = 10;
    ctx->unkC = 0;
    pos = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (func_00136B80(arg1, ctx, &work) >= 0) {
            ret = func_00276F10(&work, pos & 0xFF, pos >> 8,
                                arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 1, 0);
            if (ret < 0) {
                if (func_001E0150(arg1) < 4) {
                    res = func_00137120(arg1, kind & 0xFF, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->value = res;
                    return 1;
                }
            } else {
                res = func_00137120(arg1, kind & 0xFF, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->value = res;
                return 1;
            }
        }
    } else {
        ret = func_00276F10(&work, pos & 0xFF, pos >> 8,
                            arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 1, 0);
    }
    if (kind == 2) {
        func_00136F30(arg1, ctx, &work);
        res = func_00137120(arg1, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
    if (func_00136980(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_00137120(arg1, kind & 0xFF, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->value = res;
    return 1;
}

s32 func_00136490(s32 arg0, void *arg1) {
    s32 cards[8];
    u8 scratch[32];
    u8 first;
    u8 second;
    s32 i;
    s32 *p;
    s32 *p2;
    s32 i2;
    s32 *p3;
    s32 i3;
    s32 value;
    s32 result;
    extern s32 func_00278890();

    first = func_00278890(arg0, 0);
    second = func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, cards);
    if (first == 5) {
        if (func_00136980(arg0, scratch, arg1, 999) >= 0) {
            return 1;
        } else {
            return -1;
        }
    }
    if (second == 5) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            p = &cards[i];
            if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                func_001DCD70(arg1, cards[i]);
                return 0;
            }
        }
        return -1;
    }
    if (func_00136890(arg0, scratch, arg1, 0x33E) >= 0) {
        if (func_00138F90(arg0, 0x33E) == 1) {
            return 2;
        }
    }
    if (func_00136890(arg0, scratch, arg1, 0x351) >= 0) {
        if (func_00138F90(arg0, 0x351) == 1) {
            return 2;
        }
    }
    value = func_00138B60(arg0);
    if (value >= 0) {
        if (((value >> 16) & 0xFFFF) != 0xFFFF) {
            value = func_00136890(arg0, scratch, arg1, 0x2DC);
            if (value >= 0) {
                return 2;
            }
        }
        if ((value & 0xFFFF) != 0xFFFF && func_00136890(arg0, scratch, arg1, 0x2DD) >= 0) {
            return 2;
        }
    }
    if (func_00138DB0(arg0) == 1) {
        if (func_00136890(arg0, scratch, arg1, 0x2AB) >= 0) {
            return 2;
        }
    }
    i2 = 0;
    if (i2 < func_0026FE20(arg0)) {
        p2 = cards;
        do {
            if (func_001DE020(func_0026FCE0(*p2) >> 5) == 2) {
                func_001DCD70(arg1, cards[i2]);
                return 1;
            }
            p2++;
            i2++;
        } while (i2 < func_0026FE20(arg0));
    }
    if (func_00136890(arg0, scratch, arg1, 0x2C9) >= 0) {
        return 2;
    }
    if (func_00138EA0(arg0) >= 0) {
        if (func_00136890(arg0, scratch, arg1, 0x2AF) >= 0) {
            return 2;
        }
    }
    i3 = 0;
    if (i3 < func_0026FE20(arg0)) {
        p3 = cards;
        do {
            if ((func_0026FCE0(*p3) >> 5) == 0 && func_0026FB10(arg0, *p3) == 1) {
                func_001DCD70(arg1, cards[i3]);
                return 0;
            }
            p3++;
            i3++;
        } while (i3 < func_0026FE20(arg0));
    }
    result = func_00136980(arg0, scratch, arg1, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 func_00136890(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;
    s32 *entry;
    s32 wanted;

    func_0026FD30(arg0, entries);
    i = 0;
    if (i < func_0026FE20(arg0)) {
        wanted = arg3 & 0xFFFF;
        entry = entries;
        do {
            if (wanted == *entry && func_0026FB10(arg0, *entry) == 1) {
                *((s8 *)arg1 + 6) = i;
                func_001DCD70(arg2, entries[i]);
                return func_0026FCE0(entries[i]) >> 5;
            }
            entry++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_00136980(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

INCLUDE_ASM("asm/nonmatchings/main_009", func_00136B80);

typedef struct {
    u16 id;
    u8 values[5];
} Info_00136D60;

void func_00136D60(s32 arg0, void *arg1, s32 *arg2) {
    Info_00136D60 *info = arg1;
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
                if (card != 0x3E7 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x3E9 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00136F30;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00136F30;

s32 func_00136F30(s32 arg0, void *arg1, void *arg2) {
    Obj1_00136F30 *o1 = arg1;
    Obj2_00136F30 *o2 = arg2;
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

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00137120;

s32 func_0024FE40(void *, s32, s32);

s32 func_00137120(s32 arg0, u8 arg1, void *arg2, s32 arg3) {
    extern s32 func_00278510();
    extern s32 func_0027A130();
    extern s32 func_002792C0(s32, s32, s32, s32, s32, s32, u16, u8);
    Nibbles_00137120 path[12];
    s32 n;
    Nibbles_00137120 *p;
    s32 originY;
    s32 originX;

    if (arg2 == NULL) {
        return -1;
    }
    p = path;
    n = 0;
    do {
        p->low = p->high = 15;
        n++;
        p++;
    } while (n < 12);
    if ((u8)(*((u8 *)arg2 + 0x3E) >> 5) == 0) {
        s32 y;
        s32 x;
        s32 i;
        s32 result;
        s32 position;
        if (arg3 >= 0) {
            s32 position;
            s32 y;
            s32 cost;
            s32 x;
            s32 i;
            s32 bestPosition;
            s32 bestCost;
            s32 origin;

            bestCost = 255;
            bestPosition = 65535;
            origin = func_001E1090(arg3 >> 8, arg3 & 255);
            i = 0;
            originY = origin >> 8;
            originX = origin & 255;
            do {
                position = func_0024E410(arg0, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (func_001E22B0(x, y) != 8 &&
                        (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                        func_001E36E0(x, y) == 0) {
                        if (func_00278510(arg2, arg3, 0, originX, originY, 1) > 0) {
                            cost = func_0027A130(arg2, path, x, y, originX, originY, arg3, 1, (s64)2, (s64)0);
                        } else {
                            cost = func_002792C0((s32)arg2, (s32)path, x, y, originX, originY, arg3, 2);
                        }
                        if (func_0027AFC0((u8 *)path) > 0 && cost < bestCost) {
                            bestCost = cost;
                            bestPosition = position;
                        }
                    }
                }
                i++;
            } while (i < 8);
            if (bestPosition != 65535) {
                return bestPosition;
            }
        }
        result = -1;
        {
            i = 0;
            do {
                position = func_0024E410(arg0, i);
                if (position >= 0) {
                    x = position & 255;
                    y = position >> 8;
                    if (func_001E22B0(x, y) != 8 &&
                        (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                        func_001E3790(x, y) < 0) {
                        result = position;
                    }
                }
                i++;
            } while (i < 8);
        }
        return result;
    } else {
        s32 y;
        s32 x;
        s32 i;
        s32 result;
        s32 position;
        result = -1;
        i = 0;
        do {
            position = func_0024E410(arg0, i);
            if (position >= 0) {
                x = position & 255;
                y = position >> 8;
                if (func_001E22B0(x, y) != 8 &&
                    (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                    func_001E3790(x, y) < 0) {
                    result = position;
                }
            }
            i++;
        } while (i < 8);
        return result;
    }
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_001374D0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_001374D0;

s32 func_00139180(s32, s32, void *);
s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_001374D0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_001374D0 cells[12];
    s32 i;
    s32 result;
    s32 y;
    s32 score;
    s32 packedY;
    s32 originalY;
    s32 originalX;
    s32 x;
    s32 bestPosition;
    s32 bestScore;
    Output_001374D0 *out = arg2;

    position = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    originalX = position & 0xFF;
    originalY = position >> 8;
    if (func_00276CC0(originalX, originalY, *arg0, 3, 0, 1) == 0) {
        out->id = *arg0;
        out->action = 6;
        out->position = position;
        out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 1);
        out->value = func_00139180(*arg0 >> 8, *arg0 & 0xFF, arg0);
        func_0027B1B0(arg0, arg3);
        return 0;
    } else {
        result = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
        if (result == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 1);
            out->value = func_00139180(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        } else {
            u8 startY;
            u8 endY;
            u8 startX;
            s32 end;
            bestPosition = 0xFF;
            bestScore = 0xFFFF;
            startX = func_00250860(0, originalX - (result & 15)) & 0xFF;
            if (originalX + (result & 15) >= 7) {
                end = 6;
            } else {
                end = originalX + (result & 15);
            }
            upperX = end & 0xFF;
            startY = func_00250860(0, originalY - (result & 15)) & 0xFF;
            end = originalY + (result & 15);
            if (end >= 7) {
                end = 6;
            }
            endY = end & 0xFF;
            if ((*arg0 & 0xFF) == 0) {
                flag = func_0027BBC0(*arg0 >> 8, *arg0 & 0xFF, 1) & 0xFF;
            } else {
                flag = 0;
            }
            for (x = startX; x <= upperX; x++) {
                y = startY;
                packedY = y << 8;
                for (; y <= endY; packedY += 0x100, y++) {
                    if ((((x < originalX ? originalX : x) -
                          (originalX < x ? originalX : x)) +
                         ((y < originalY ? originalY : y) -
                          (originalY < y ? originalY : y))) <= (result & 15)) {
                        if (func_00279C40(*arg0 >> 8, *arg0 & 0xFF, originalX, originalY, x, y, arg0, flag) == 1 &&
                            (func_0027BE10(*arg0 >> 8, *arg0 & 0xFF, x, y, 1) == 0 || (u8)*arg0 == 0)) {
                            score = func_00276CC0(x, y, *arg0, 3, 0, 1);
                            if (score < bestScore) {
                                bestScore = score;
                                bestPosition = packedY | x;
                            } else if (score == bestScore &&
                                       func_001E36E0(x, y) == 0 &&
                                       func_001E36E0(bestPosition & 0xFF, bestPosition >> 8) != 0) {
                                bestScore = score;
                                bestPosition = packedY | x;
                            }
                        }
                    }
                }
            }
            if (bestPosition != 0xFF) {
                out->id = *arg0;
                out->action = 6;
                out->position = bestPosition;
                if (bestPosition == position) {
                    out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 1);
                } else {
                    out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 0, 1);
                }
                out->value = func_00139180(*arg0 >> 8, *arg0 & 0xFF, arg0);
            } else {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 1);
                out->value = func_00139180(*arg0 >> 8, *arg0 & 0xFF, arg0);
            }
            func_0027B1B0(arg0, arg3);
        }
    }
    return 0;
}

typedef struct Input_001379F0 {
    u16 position;
    u8 pad2[6];
    u32 destinations;
} Input_001379F0;

typedef struct Output_001379F0 {
    u16 position;
    s8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    s8 result;
} Output_001379F0;

typedef struct Coordinate_001379F0 {
    u8 x : 4;
    u8 y : 4;
} Coordinate_001379F0;

s32 func_00139180(s32, s32, void *);
s32 func_002464F0(s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline s32 destination_001379F0(void *src, u8 mode) {
    Input_001379F0 *input = src;
    if (mode == 1) {
        return (u16)(input->destinations >> 16);
    }
    return (u16)input->destinations;
}

s32 func_001379F0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void func_0027A090();
    Coordinate_001379F0 candidates[12];
    s32 targetPosition;
    s32 initialFlag;
    s32 i;
    s32 bestIndex;
    s32 count;
    s32 originalPosition;
    s32 originalY;
    s32 originalX;
    s32 found;
    s32 originalCard;
    s32 lowDestination;
    s32 highDestination;
    Input_001379F0 *input = arg0;
    Output_001379F0 *output = arg2;

    lowDestination = destination_001379F0(arg0, arg3);
    highDestination = destination_001379F0(arg0, arg3);
    if (func_001DF540((u32)highDestination >> 8, lowDestination & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    initialFlag = func_00139180((s32)input->position >> 8, input->position & 0xFF, arg0);
    originalPosition = func_001E1090((s32)input->position >> 8, input->position & 0xFF);
    lowDestination = destination_001379F0(arg0, arg3);
    highDestination = destination_001379F0(arg0, arg3);
    targetPosition = func_001E1090((u32)highDestination >> 8, lowDestination & 0xFF);
    i = 0;
    do {
        candidates[i].x = candidates[i].y = 15;
        i++;
    } while (i < 12);
    originalCard = func_001DF540((s32)input->position >> 8, input->position & 0xFF);
    originalX = originalPosition & 0xFF;
    originalY = originalPosition >> 8;
    if (func_002464F0(originalCard, originalX, originalY) == 0) {
        s32 score;
        output->position = input->position;
        output->action = 6;
        output->destination = originalPosition;
        score = func_00276CC0(originalX, originalY, arg1, 3, 0, 0);
        if (score >= func_001E0290((s32)input->position >> 8, input->position & 0xFF, 0)) {
            output->result = func_0027E360((s32)input->position >> 8, input->position & 0xFF,
                                          output->destination, 1, 1);
        } else {
            output->result = func_0027E360((s32)input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 1);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    } else {
        s32 targetY;
        s32 targetX;
        Coordinate_001379F0 *candidate;
        s32 candidateIndex;
        s32 bestScore;

        func_0027A090((s32)input->position >> 8, input->position & 0xFF,
                     candidates, originalX, originalY, targetX = targetPosition & 0xFF,
                     targetY = targetPosition >> 8,
                     destination_001379F0(arg0, arg3), 1, 30, 0);
        count = func_0027AFC0((u8 *)candidates);
        bestIndex = 255;
        if (count > 0) {
            found = 0;
            bestScore = 65535;
            for (candidateIndex = 0; candidateIndex < count; candidateIndex++) {
                if (func_00139080((s32)input->position >> 8, input->position & 0xFF,
                                  originalX, originalY, targetX, targetY) == 1) {
                    bestIndex = candidateIndex;
                    found = 1;
                    candidates[candidateIndex].x = targetX;
                    candidates[candidateIndex].y = targetY;
                    candidateIndex = count;
                } else {
                    s32 score;
                    candidate = &candidates[candidateIndex];
                    score = func_00276CC0(candidate->x, candidate->y, arg1, 2, 0, 0);
                    if (score < bestScore) {
                        bestScore = score;
                        bestIndex = candidateIndex;
                    } else if (score == bestScore) {
                        Coordinate_001379F0 *best = &candidates[bestIndex];
                        s32 minBestY;
                        s32 maxBestY;
                        s32 minBestX;
                        s32 maxBestX;
                        s32 minNextY;
                        s32 maxNextY;
                        s32 minNextX;
                        s32 maxNextX;

                        minBestY = best->y < targetY ? best->y : targetY;
                        maxBestY = targetY < best->y ? best->y : targetY;
                        minBestX = best->x < targetX ? best->x : targetX;
                        maxBestX = targetX < best->x ? best->x : targetX;
                        minNextY = candidate->y < targetY ? candidate->y : targetY;
                        maxNextY = targetY < candidate->y ? candidate->y : targetY;
                        minNextX = candidate->x < targetX ? candidate->x : targetX;
                        maxNextX = targetX < candidate->x ? candidate->x : targetX;
                        if ((maxNextX - minNextX) + (maxNextY - minNextY) <
                            (maxBestX - minBestX) + (maxBestY - minBestY)) {
                            bestScore = score;
                            bestIndex = candidateIndex;
                        }
                    }
                }
            }
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = originalPosition;
            output->flag = initialFlag;
            output->result = func_0027E360((s32)input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 1);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (bestIndex != 255) {
            output->position = input->position;
            output->action = 6;
            output->destination = (candidates[bestIndex].y << 8) | candidates[bestIndex].x;
            output->flag = found;
            output->result = func_0027E360((s32)input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 1);
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = originalPosition;
            output->flag = found;
            output->result = func_0027E360((s32)input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 1);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Unit_00137FB0 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 halves[2];
    } destination;
} Unit_00137FB0;

typedef struct Order_00137FB0 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 value;
    u8 flags;
} Order_00137FB0;

typedef struct Point_00137FB0 {
    u8 x : 4;
    u8 y : 4;
} Point_00137FB0;

s32 func_00139180(s32, s32, void *);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 destination_00137FB0(void *unit, s32 side) {
    if (side == 1) {
        return (u16)(((Unit_00137FB0 *)unit)->destination.packed >> 16);
    }
    return ((Unit_00137FB0 *)unit)->destination.halves[0];
}

s32 func_00137FB0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    extern void func_00279230(s32, s32, void *, s32, s32, s32, s32, s32, u8);
    s32 count;
    s32 position;
    Point_00137FB0 points[12];
    s32 id;
    s32 score;
    u32 destinationValue;
    Unit_00137FB0 *unit = arg0;
    Order_00137FB0 *order = arg2;

    {
    s32 bestScore;
    s32 bestIndex;
    s32 side;
    Point_00137FB0 *point;
    s32 index;

    position = func_001E1090((s32)unit->position >> 8, unit->position & 0xFF);
    side = arg3;
    if (destination_00137FB0(unit, side) == 0xFFFF) {
        if (position == destination_00137FB0(unit, side)) {
            order->position = unit->position;
            order->kind = 6;
            order->destination = position;
            order->flags = func_0027E360((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, arg4, 1);
            order->value = func_00139180((s32)unit->position >> 8, unit->position & 0xFF, unit);
            func_0027B1B0(unit, arg3);
            return 0;
        }
    }

    point = points;
    {
        s32 i = 0;
        Point_00137FB0 *p = point;
        do {
            p->x = p->y = 15;
            i++;
            p++;
        } while (i < 12);
    }

    destinationValue = destination_00137FB0(unit, side);
    id = func_001E3790(destination_00137FB0(unit, side) & 0xFF,
                       destinationValue >> 8);
    if (id < 0) {
        id = 0xFFFF;
    }
    destinationValue = destination_00137FB0(unit, side);
    func_00279230((s32)unit->position >> 8, unit->position & 0xFF, points,
                  position & 0xFF, position >> 8,
                  destination_00137FB0(unit, side) & 0xFF,
                  destinationValue >> 8, (u16)id, 7);
    count = func_0027AFC0((u8 *)points);
    if (count > 0) {
        bestIndex = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++, point++) {
            if (func_001E36E0(point->x, point->y) == 0) {
                score = func_00276CC0(point->x, point->y, arg1, 2, 0, 0);
                if (score < bestScore) {
                    bestScore = score;
                    bestIndex = index;
                } else if (score == bestScore) {
                    u32 oldYMin;
                    u32 oldYMax;
                    u32 oldXMin;
                    u32 oldXMax;
                    u8 oldY;
                    u8 oldX;
                    u32 currentYMin;
                    u32 currentYMax;
                    u32 currentXMin;
                    u32 currentXMax;
                    u8 currentY;
                    u8 currentX;
                    Point_00137FB0 *best = &points[bestIndex];

                    oldY = best->y;
                    if (oldY < (destination_00137FB0(unit, side) >> 8)) {
                        oldYMin = (u8)oldY;
                    } else {
                        oldYMin = destination_00137FB0(unit, side) >> 8;
                    }
                    if ((destination_00137FB0(unit, side) >> 8) < oldY) {
                        oldYMax = (u8)oldY;
                    } else {
                        oldYMax = destination_00137FB0(unit, side) >> 8;
                    }
                    oldX = best->x;
                    if (oldX < (destination_00137FB0(unit, side) & 0xFF)) {
                        oldXMin = (u8)oldX;
                    } else {
                        oldXMin = destination_00137FB0(unit, side) & 0xFF;
                    }
                    if ((destination_00137FB0(unit, side) & 0xFF) < oldX) {
                        oldXMax = (u8)oldX;
                    } else {
                        oldXMax = destination_00137FB0(unit, side) & 0xFF;
                    }

                    currentY = point->y;
                    if (currentY < (destination_00137FB0(unit, side) >> 8)) {
                        currentYMin = (u8)currentY;
                    } else {
                        currentYMin = destination_00137FB0(unit, side) >> 8;
                    }
                    if ((destination_00137FB0(unit, side) >> 8) < currentY) {
                        currentYMax = (u8)currentY;
                    } else {
                        currentYMax = destination_00137FB0(unit, side) >> 8;
                    }
                    currentX = point->x;
                    if (currentX < (destination_00137FB0(unit, side) & 0xFF)) {
                        currentXMin = (u8)currentX;
                    } else {
                        currentXMin = destination_00137FB0(unit, side) & 0xFF;
                    }
                    if ((destination_00137FB0(unit, side) & 0xFF) < currentX) {
                        currentXMax = (u8)currentX;
                    } else {
                        currentXMax = destination_00137FB0(unit, side) & 0xFF;
                    }
                    if ((currentXMax - currentXMin) + (currentYMax - currentYMin) <
                        (oldXMax - oldXMin) + (oldYMax - oldYMin)) {
                        bestScore = score;
                        bestIndex = index;
                    }
                }
            }
        }
    } else {
        order->position = unit->position;
        order->kind = 6;
        order->destination = position;
        order->flags = func_0027E360((s32)unit->position >> 8, unit->position & 0xFF,
                                   order->destination, arg4, 1);
        order->value = func_00139180((s32)unit->position >> 8, unit->position & 0xFF, unit);
        func_0027B1B0(unit, arg3);
        return 0;
    }
        if (bestIndex != 0xFF) {
            order->position = unit->position;
            order->kind = 6;
            order->destination = (points[bestIndex].y << 8) | points[bestIndex].x;
            order->flags = func_0027E360((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, arg4, 1);
            order->value = func_00139180((s32)unit->position >> 8, unit->position & 0xFF, unit);
        } else {
            order->position = unit->position;
            order->kind = 6;
            order->destination = position;
            order->flags = func_0027E360((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, arg4, 1);
            order->value = func_00139180((s32)unit->position >> 8, unit->position & 0xFF, unit);
        }
        func_0027B1B0(unit, arg3);
    }
    return 0;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00138780;

typedef struct {
    u16 pos;
    u8 kind;
    u8 unk03;
    u16 target;
    u8 pad06[6];
    s32 flag;
    u8 result;
} Out_00138780;

s32 func_00138EA0(s32 arg0);
s32 func_0027DBC0(s32 arg0, s32 arg1, s32 arg2);
void func_001E1E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_00138780(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    s32 card;
    s32 col;
    u16 row;
    Out_00138780 *out = arg2;
    Nibbles_00138780 entries[12];
    s32 i;
    Nibbles_00138780 *entry;

    func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);

    card = func_00138EA0(arg1);
    if (func_0027D830(*arg0 >> 8, *arg0 & 0xFF, 0, 0, 6, 1) == 5) {
        card = -1;
    }
    if (card >= 0) {
        row = card >> 16;
        col = func_0027DBC0(row, card & 0xFF, 0);
        out->pos = *arg0;
        out->kind = 12;
        out->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->target, 1, 1);
        out->flag = 1;
        out->target = (row << 8) | col;
        func_0027B1B0(arg0, arg3);
        return 0;
    }
    if (func_001E2100(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
        func_001E1E70(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
        out->pos = *arg0;
        out->kind = 14;
        return 0;
    }
    return func_001374D0(arg0, arg1, arg2, arg3);
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138950);

s32 func_00138B60(s32 arg0) {
    extern s32 func_001E1580(s32, s32);
    extern s32 func_001E1640(s32, s32);
    u16 cells[0x16];
    s32 target;
    s32 row;
    s32 col;
    u16 *p;
    s32 y;
    s32 x;
    s32 best;
    s32 i;
    s32 bestScore;
    u32 handle;
    s32 pos;
    s32 score;
    s32 j;

    pos = func_001E1090((arg0 == 0) ? 1 : 0, 0);
    if (func_00266DF0(0x39) > 0) {
        return -1;
    }
    handle = func_00272210(func_0024CA40(0, 0, arg0, 2, 0x21, 0xE), arg0);
    p = cells;
    for (j = 0; j < 0x16; j++) {
        cells[j] = 0xFFFF;
    }
    func_0027C070((arg0 == 0) ? 1 : 0, cells, 0x34, 1);
    target = -1;
    best = target;
    bestScore = 1;
    i = 0;
    if (i < func_0027C670(cells)) {
        row = pos >> 8;
        col = pos & 0xFF;
        do {
        pos = func_001E1090(*p >> 8, *p & 0xFF);
        y = pos >> 8;
        x = pos & 0xFF;
        if ((((x < col) ? col : x) - ((col < x) ? col : x)) +
                (((y < row) ? row : y) - ((row < y) ? row : y)) == 1 &&
            func_001E2100(*p >> 8, *p & 0xFF, 1) == 0 &&
            func_001E1580(*p >> 8, *p & 0xFF) == 0 &&
            func_001E1640(*p >> 8, *p & 0xFF) == 0) {
            if ((score = func_002509E0(*p >> 8, *p & 0xFF, x, y)) >= bestScore) {
                best = *p;
                if (best == func_0024EC50(handle, 0)) {
                    target = best;
                }
                bestScore = score;
            }
        }
        p++;
        } while (++i < func_0027C670(cells));
    }
    if (best < 0) {
        return -1;
    }
    return ((best & 0xFFFF) << 16) | (target & 0xFFFF);
}

s32 func_00138DB0(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;

    if (func_0024E910(func_0024CA40(0, 0, arg0, 2, 0, 14)) >= 2) {
        return 1;
    }
    temp_v0 = func_0024EC50(func_0024CA40(0, 0, arg0, 3, 33, 14), 0);
    temp_s1 = temp_v0 >> 8;
    temp_s0 = temp_v0 & 0xFF;
    if (arg0 != func_00250360(temp_s1, temp_s0)) {
        if (((func_001E0700(temp_s1, temp_s0) >> 5) == 0) && !(func_001E0700(temp_s1, temp_s0) & 0x1F)) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_009", func_00138EA0);

s32 func_00138F90(s32 arg0, s32 arg1) {
    s32 index;
    s32 mask;
    s32 low;
    s32 high;
    s32 packed;
    s32 value;
    s32 data[4];

    func_00254C90(data, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(data, arg0)) < 0) {
        return 0;
    }
    index = 0;
    if (index < func_0024E910(mask)) {
        do {
            packed = func_0024EC50(mask, index);
            high = packed >> 8;
            low = packed & 0xFF;
            value = func_001E1090(high, low);
            if (func_002509E0(high, low, value & 0xFF, value >> 8) >= 0xA28) {
                return 0;
            }
            index++;
        } while (index < func_0024E910(mask));
    }
    return 1;
}

static inline s32 max_00139080(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00139080(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00139080(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00139080(arg4, arg2);
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

INCLUDE_ASM("asm/nonmatchings/main_009", func_00139180);

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6[5];
    u8 padB;
    s32 unkC;
    u8 unk10;
} Req_001396C0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_001396C0;

s32 func_00135230(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_001396C0(s32 arg0, void *arg1) {
    Req_001396C0 req;
    Work_001396C0 *w;
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
        if (func_00135230(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_009", func_00139890);

typedef struct Halves_00139D90 {
    u16 low;
    u16 high;
} Halves_00139D90;

typedef struct Record_00139D90 {
    u16 id;
    u16 pad2;
    s16 code;
    u16 pad6;
    union {
        s32 word;
        Halves_00139D90 halves;
    } data;
} Record_00139D90;


s32 func_00139D90(void *arg0, s32 arg1) {
    extern void func_0013AA40();
    Record_00139D90 *record = arg0;
    s32 value;
    s32 state;

    value = func_001E1090((s32) record->id >> 8, record->id & 0xFF);
    state = func_00250360((s32) record->id >> 8, record->id & 0xFF);
    if (func_001DF540((s32) record->id >> 8, record->id & 0xFF) != 0) {
        if (func_001E2100((s32) record->id >> 8, record->id & 0xFF, 0) == 0) {
            if (record->id != 0xFFFF) {

                if ((record->id & 0xFF) == 0) {
                    if (record->data.word == -1) {
                        if (func_0027BBC0((s32) record->id >> 8, record->id & 0xFF, 0) == 1) {
                            if (func_001DE6D0((s32) record->id >> 8) == 1) {
                                record->code = 0x50A;
                            } else {
                                record->code = 0x5FF;
                            }
                        } else if (func_001DE6D0((s32) record->id >> 8) == 1) {
                            record->code = 0xA06;
                            if ((arg1 & 0xFF) == 1) {
                                record->data.word = (record->data.word & 0xFFFF0000) |
                                    (((((value >> 8) + 1) << 8) | (value & 0xFF)) & 0xFFFF);
                            } else {
                                record->data.word = (record->data.word & 0xFFFF0000) | (value & 0xFFFF);
                            }
                        } else {
                            record->code = 0x6FF;
                            if ((arg1 & 0xFF) == 1) {
                                record->data.word = (u16) record->data.word |
                                    (((((value >> 8) + 1) << 8) | (value & 0xFF)) << 16);
                            } else {
                                record->data.word = (value << 16) | record->data.halves.low;
                            }
                        }
                    }
                } else {
                    switch (func_001E0700((s32) record->id >> 8, record->id & 0xFF) >> 5) {
                    case 0:
                        func_0013A400(arg0, 1, arg1);
                        break;
                    case 2:
                        func_0027CA50(arg0, 2, 0, func_0013DA70(state) & 0xFF);
                        break;
                    case 1:
                    case 3:
                        func_0013AA40(arg0, arg1);
                        break;
                    default:
                        record->code = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

s32 func_0013A010(u16 *arg0, s32 arg1, s32 arg2, void *arg3) {
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
    func_00139D90(arg0 + idx * 8, arg2);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0013AB70(pos, arg1, arg3) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0013AB70(pos, arg1, arg3) >= 0) {
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

typedef struct Entry_0013A400 {
    u16 id;
    u8 flag;
    u8 pad;
} Entry_0013A400;

void func_0013A400(void *arg0, s32 arg1, s32 arg2) {
    extern s32 func_0027B200();
    extern s32 func_0013A6B0();
    extern void func_0027E770();
    s32 position;
    u8 workspace[0x70];
    Entry_0013A400 entries[23];
    s16 count;
    s16 result;
    u16 id;

    id = *(u16 *)arg0;
    if (func_001DF540(id >> 8, id & 0xFF) != 0) {
        s32 side;
        s32 target;
        s32 otherPosition;
        s32 targetLow;
        s32 targetHigh;
        s32 data;
        s32 i;
        Entry_0013A400 *entry;

        id = *(u16 *)arg0;
        side = func_0024DE70(id >> 8, id & 0xFF);
        target = (side == 0 ? 1 : 0) << 8;
        position = func_001E1090(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
        targetHigh = target >> 8;
        targetLow = target & 0xFF;
        otherPosition = func_001E1090(targetHigh, targetLow);
        id = *(u16 *)arg0;
        data = func_001DF540(id >> 8, id & 0xFF);
        func_0027E770(workspace);
        entry = entries;
        i = 0;
        do {
            i++;
            entry->id = 0xFFFF;
            entry->flag = 0xFF;
            entry++;
        } while (i < 22);

        if (arg1 != 0) {
            id = *(u16 *)arg0;
            if (func_0027B200(id >> 8, id & 0xFF, position & 0xFF,
                    position >> 8, targetHigh, targetLow, otherPosition & 0xFF,
                    otherPosition >> 8, 2) > 0) {
                *(u16 *)((u8 *)arg0 + 4) = 0x2FF;
                *(u32 *)((u8 *)arg0 + 8) =
                    (target << 16) | *(u16 *)((u8 *)arg0 + 8);
                return;
            }
        }

        result = 0;
        count = 0;
        for (i = 1; i <= (arg2 ? 1 : 3); i++) {
            s32 limit;
            s32 opposite;
            s32 value;

            limit = arg2 ? 1 : 3;
            opposite = func_0024DE70(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF) == 0 ? 1 : 0;
            value = func_0013DA70(side);
            switch (func_0013A6B0((s32)arg0, 0, data, position & 0xFF,
                        position >> 8, opposite, (u8)i, value,
                        (s32)entries, 0, (s32)&count, (s32)&result,
                        (u8)limit, (s32)workspace)) {
            case 3:
                *(u16 *)((u8 *)arg0 + 4) = 0x6FF;
                *(u32 *)((u8 *)arg0 + 8) =
                    (position << 16) | *(u16 *)((u8 *)arg0 + 8);
                return;
            case 2:
                *(u16 *)((u8 *)arg0 + 4) = 0x3FF;
                *(u32 *)((u8 *)arg0 + 8) =
                    (position << 16) | *(u16 *)((u8 *)arg0 + 8);
                return;
            case 1:
                return;
            case 0:
                *(u16 *)((u8 *)arg0 + 4) = 0x3FF;
                *(u32 *)((u8 *)arg0 + 8) =
                    (position << 16) | *(u16 *)((u8 *)arg0 + 8);
                return;
            }
        }
        func_0013A710(arg0, arg2);
    }
}

void func_0013A6B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

typedef struct Packet_0013A710 {
    u16 location;
    u16 unk2;
    s16 mode;
    u16 unk6;
    union {
        u32 word;
        u16 lower;
    } value;
} Packet_0013A710;

void func_0013A710(void *arg0, s32 arg1) {
    Packet_0013A710 *packet = arg0;
    s32 item;
    s32 encoded;
    s32 result;
    u16 location;

    location = packet->location;
    item = func_00250360(location >> 8, location & 0xFF);
    location = packet->location;
    encoded = func_001E1090(location >> 8, location & 0xFF);
    if ((arg1 & 0xFF) == 1) {
        item = encoded & 0xFF;
        encoded = (encoded >> 8) + 1;
        result = func_001E3790(item, encoded);
        if (result >= 0) {
            packet->mode = 0x2FF;
            packet->value.word = (result << 16) | packet->value.lower;
        } else {
            packet->mode = 0x6FF;
            packet->value.word = packet->value.lower | (((encoded << 8) | item) << 16);
        }
        return;
    } else {
        arg1 = encoded >> 8;
        if (arg1 != func_0013A9A0(item)) {
            result = func_0013A870(item);
            if (result >= 0) {
                packet->mode = 0x6FF;
                packet->value.word = (result << 16) | packet->value.lower;
            } else {
                packet->mode = 0x6FF;
                packet->value.word = packet->value.lower | ((((arg1 + 1) << 8) | (encoded & 0xFF)) << 16);
            }
        } else {
            packet->mode = 0x6FF;
            packet->value.word = (encoded << 16) | packet->value.lower;
        }
    }
}

s32 func_0013A870(s32 arg0) {
    s32 var_s0;
    s32 temp_s1;

    temp_s1 = func_0013A9A0(arg0) & 0xFF;
    var_s0 = 0;
    do {
        switch (var_s0) {
        case 0:
            if (func_001E36E0(3, temp_s1) == 0) {
                return (temp_s1 << 8) | 3;
            }
            break;
        case 1:
            if (func_001E36E0(4, temp_s1) == 0) {
                return (temp_s1 << 8) | 4;
            }
            break;
        case 2:
            if (func_001E36E0(2, temp_s1) == 0) {
                return (temp_s1 << 8) | 2;
            }
            break;
        case 3:
            if (func_001E36E0(5, temp_s1) == 0) {
                return (temp_s1 << 8) | 5;
            }
            break;
        case 4:
            if (func_001E36E0(1, temp_s1) == 0) {
                return (temp_s1 << 8) | 1;
            }
            break;
        }
        var_s0++;
    } while (var_s0 < 5);
    return -1;
}

s32 func_0013A9A0(s32 arg0) {
    s32 i;
    u8 maximum;
    s32 value;

    maximum = 0;
    for (i = 1; i <= 5; i++) {
        if (func_001DF540(arg0, i) != 0) {
            value = (func_001E1090(arg0, i) >> 8) & 0xFF;
            if (maximum < value) {
                maximum = value;
            }
        }
    }
    if (maximum < 2) {
        maximum = 2;
    }
    return maximum;
}

typedef struct State_0013AA40 {
    u16 position;
    u16 unk2;
    s16 mode;
    u16 unk6;
    union {
        u16 halves[2];
        u32 word;
    } info;
} State_0013AA40;

static inline s32 decode_0013AA40(s32 position) {
    return func_001E1090(position >> 8, position & 0xFF);
}

void func_0013AA40(void *arg0) {
    State_0013AA40 *state = arg0;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_a0;
    s32 temp_v0_4;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;

    temp_v0 = state->position;
    temp_s2 = func_00250360((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    temp_v0_2 = state->position;
    temp_s0 = decode_0013AA40(temp_v0_2);
    temp_v0_3 = state->position;
    temp_a0 = func_001E0700((s32) temp_v0_3 >> 8, temp_v0_3 & 0xFF) >> 5;
    switch (temp_a0) {
    case 1:
        temp_v0_4 = func_0013D2C0(temp_s2);
        if (temp_v0_4 >= 0) {
            state->mode = 0x6FF;
            state->info.word = state->info.halves[0] | ((((temp_s0 >> 8) << 8) | (func_001E1090(temp_v0_4 >> 8, temp_v0_4 & 0xFF) & 0xFF)) << 0x10);
            return;
        }
        state->mode = 0x5FF;
        break;
    case 3:
        state->mode = 0x3FF;
        state->info.word = state->info.halves[0] | (((temp_s0 & 0xFF) | ((func_001E1090(temp_s2, 0) >> 8) << 8)) << 0x10);
        return;
    }
    state->mode = 0x5FF;
}

typedef struct {
    u8 pad00[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_0013AB70;

typedef struct {
    u16 id;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Ctx_0013AB70;

s32 func_0013BA30(s32 arg0, u8 arg1, Work_0013AB70 *arg2, s32 arg3);

s32 func_0013AB70(s32 arg0, s32 arg1, void *arg2) {
    extern s32 func_00278890();
    Work_0013AB70 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_0013AB70 *ctx = (Ctx_0013AB70 *)arg2;

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_0013AE00(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (func_0013B420(arg1, (u8 *)ctx, &work) >= 0) {
            ret = func_00276F10(&work, pos & 0xFF, pos >> 8,
                                arg1 == 0 ? 1 : 0, 2, 0x1F, 2, 2,
                                0, func_0013DA70(arg1));
            if (ret < 0) {
                if (func_001E0150(arg1) < 6) {
                    res = func_0013BA30(arg1, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = func_0013BA30(arg1, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = func_00276F10(&work, pos & 0xFF, pos >> 8,
                            arg1 == 0 ? 1 : 0, 2, 0x1F, 2, 2,
                            0, func_0013DA70(arg1));
    }
    if (kind == 2) {
        func_0013B840(arg1, ctx, &work);
        res = func_0013BA30(arg1, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (func_0013B220(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_0013BA30(arg1, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

s32 func_0013AE00(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    extern s32 func_001E1580();
    s32 cards[8];
    u8 work[32];
    u8 status0;
    u8 status1;
    s32 *categoryCard;
    s32 categoryIndex;
    s32 i;
    s32 result;

    status0 = func_00278890(arg0, 0);
    status1 = func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, cards);
    if (status0 == 5) {
        if (func_0013B220(arg0, work, arg1, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (status1 == 5) {
        s32 j;
        for (j = 0; j < func_0026FE20(arg0); j++) {
            if ((func_0026FCE0(cards[j]) >> 5) == 0 &&
                func_0026FB10(arg0, cards[j]) == 1) {
                func_001DCD70(arg1, cards[j]);
                return 0;
            }
        }
        return -1;
    }
    if (func_0013B130(arg0, work, arg1, 0x348) >= 0) {
        if (func_0013D980(arg0, 0x348) == 1) {
            return 2;
        }
    }
    if (func_0013D2C0(arg0) >= 0) {
        if (func_0013B130(arg0, work, arg1, 0x2BC) >= 0) {
            return 2;
        }
    }
    categoryIndex = 0;
    if (categoryIndex < func_0026FE20(arg0)) {
        categoryCard = cards;
        do {
            if (func_001DE020(func_0026FCE0(*categoryCard) >> 5) == 2) {
                func_001DCD70(arg1, cards[categoryIndex]);
                return 1;
            }
            categoryCard++;
            categoryIndex++;
        } while (categoryIndex < func_0026FE20(arg0));
    }
    for (i = 0; i < 11; i++) {
        if (func_001E1580(arg0, i) != 0 &&
            func_0013B130(arg0, work, arg1, 0x31C) >= 0) {
            return 2;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(cards[i]) >> 5) == 0 &&
            func_0026FB10(arg0, cards[i]) == 1) {
            func_001DCD70(arg1, cards[i]);
            return 0;
        }
    }
    result = func_0013B220(arg0, work, arg1, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 func_0013B130(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;
    s32 *entry;

    func_0026FD30(arg0, entries);
    i = 0;
    if (0 < func_0026FE20(arg0)) {
        entry = entries;
        do {
            if ((arg3 & 0xFFFF) == *entry && func_0026FB10(arg0, *entry) == 1) {
                *((u8 *)arg1 + 6) = i;
                func_001DCD70(arg2, entries[i]);
                return func_0026FCE0(entries[i]) >> 5;
            }
            entry++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_0013B220(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_0013B420 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0013B420;

typedef struct Sprite_0013B420 {
    Info_0013B420 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0013B420;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_0013B420(s32 arg0, u8 *arg1, void *arg2) {
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
                            func_0013B600(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_0013B420 *)arg2)->x = (value >> 16) - (((Sprite_0013B420 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0013B420 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0013B420 *)arg2)->info->y & 0x1FFF);
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

typedef struct {
    u16 id;
    u8 values[5];
} Info_0013B600;

void func_0013B600(s32 arg0, void *arg1, s32 *arg2) {
    Info_0013B600 *info = arg1;
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
                if (card != 0x3E7 && func_0013B7E0(card) == 0 && level >= func_0026FA80(card, arg0)) {
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

s32 func_0013B7E0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0013B840;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_0013B840;

s32 func_0013B840(s32 arg0, void *arg1, void *arg2) {
    Obj1_0013B840 *o1 = arg1;
    Obj2_0013B840 *o2 = arg2;
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

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013BA30);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013BE60);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013C430);

INCLUDE_ASM("asm/nonmatchings/main_009", func_0013CA10);

s32 func_0013D280(void) {
    if (func_0013A870(func_001DE540()) < 0) {
        return 1;
    }
    return 0;
}

s32 func_0013D2C0(s32 arg0) {
    u16 buf[0x16];
    s32 i;
    s32 a;
    s32 b;
    s32 r;

    for (i = 0; i < 0x16; i++) {
        buf[i] = 0xFFFF;
    }
    func_0027C2C0(arg0 == 0 ? 1 : 0, buf, 0x1D, 0, 0);
    a = func_0027B650(buf);
    for (i = 0; i < 0x16; i++) {
        buf[i] = 0xFFFF;
    }
    func_0027C070(arg0, buf, 0x1D, 1);
    b = func_0027B650(buf);
    if (a >= 0) {
        if (b >= 0) {
            r = func_001E1090(a >> 8, a & 0xFF);
            if (func_002781F0(a, b, r & 0xFF, r >> 8) > 0) {
                return a;
            }
        }
    }
    return -1;
}
