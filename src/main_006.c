#include "common.h"

typedef struct {
    u16 coordinates;
    u16 unk02;
    s16 state;
    u16 unk06;
    union {
        u32 word;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Entry_0011D110;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_0011D110;


void func_0011D110(void *arg0, s32 arg1) {
    extern void func_0027E770();
    extern s32 func_0027B200();
    extern s32 func_0011D380();
    Entry_0011D110 *entry = arg0;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_0011D110 list[22];
    s16 countA;
    s16 countB;

    if (func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        side = func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = func_001E1090(other >> 8, other & 0xFF);
        player = func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        func_0027E770(work);
        if (arg1 != 0) {
            if (func_0027B200(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                              other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 4) > 0) {
                entry->state = 0x2FF;
                entry->data.word = (other << 16) | entry->data.halves.low;
                return;
            }
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (func_0011D380(entry, 0, player, pos & 0xFF, pos >> 8,
                                  func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, func_0011FA80(side), list, 0, &countA, &countB, 4, work)) {
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
            if (i > 4) {
                break;
            }
        }
        func_0011D3E0(entry);
    }
}

void func_0011D380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 1500, arg_sp28);
}

typedef struct {
    u16 coordinates;
    u16 pad2;
    u16 state;
    u16 pad6;
    u32 value;
} Entry_0011D3E0;

s32 func_0011D4E0(s32, s32, s32, s32 *);

void func_0011D3E0(void *arg0) {
    Entry_0011D3E0 *entry = arg0;
    s32 value;
    s32 index[2];
    s32 state;
    u16 coordinates;

    func_001DE540();
    coordinates = entry->coordinates;
    value = func_001E1090((s32) coordinates >> 8, coordinates & 0xFF);
    coordinates = entry->coordinates;
    if (func_0011D6D0((s32) coordinates >> 8, coordinates & 0xFF) < 0) {
        coordinates = entry->coordinates;
        func_0011D4E0(func_001DF540((s32) coordinates >> 8, coordinates & 0xFF), value & 0xFF, value >> 8, index);
        if (index[0] >= 0) {
            entry->state = 0x6FF;
            entry->value = (index[0] << 16) | (entry->value & 0xFFFF);
        } else {
            entry->state = 0x5FF;
        }
    } else {
        state = ((s32) entry->state >> 8) & 0xFF;
        if (state != 0xF && state != 0x10) {
            entry->state = (((value >> 8) < 4 ? 0xF : 0x10) << 8) | 0xFF;
            entry->value = *(u16 *)&entry->value | 0xFFFF0000;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D4E0);

s32 func_0011D6D0(s32 arg0, s32 arg1) {
    s32 value;

    value = func_001E1090(arg0, arg1);
    switch (value & 0xFF) {
    case 0:
        value >>= 8;
        if ((value >= 0) && (value < 7)) {
            return 3;
        }
        break;
    case 2:
        value >>= 8;
        if ((value > 1) && (value < 5)) {
            return 0;
        }
        break;
    case 4:
        value >>= 8;
        if ((value > 1) && (value < 5)) {
            return 1;
        }
        break;
    case 6:
        value >>= 8;
        if ((value >= 0) && (value < 7)) {
            return 4;
        }
        break;
    }
    return -1;
}

s32 func_0011D7B0(s32 arg0, u8 arg1) {
    s32 row;
    s32 column;
    s32 last_column;
    s32 low;
    s32 high;
    s32 value;

    switch (arg1) {
    case 0:
        column = 2;
        last_column = 4;
        row = 2;
        break;
    case 1:
        column = 2;
        row = 4;
        last_column = 4;
        break;
    case 2:
        column = 1;
        last_column = 5;
        row = 0;
        break;
    case 3:
    default:
        row = 6;
        column = 1;
        last_column = 5;
        break;
    }
    for (; column <= last_column; column++) {
        value = func_001E3790(row, column);
        if (value >= 0) {
            high = value >> 8;
            low = value & 0xFF;
            if ((arg0 == func_00250360(high, low)) &&
                ((func_001E0700(high, low) >> 5) == 0)) {
                return 0;
            }
        }
    }
    return 1;
}

s32 func_0011D8D0(s32 arg0, s32 arg1) {
    s32 result;

    switch (arg1) {
    case 0:
        result = 0x204;
        break;
    case 1:
        result = 0x202;
        break;
    case 2:
        result = 0;
        break;
    default:
    case 3:
        result = 6;
        break;
    }

    return result;
}

s32 func_0011D940(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        return 0x402;
    case 1:
        return 0x404;
    case 2:
        return 0x600;
    default:
    case 3:
        return 0x606;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D9B0);

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_0011DC00;

s32 func_00277CD0(s32, s32, s32, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32);

void func_0011DC00(void *arg0) {
    u8 work[112];
    Slot_0011DC00 slots[22];
    s16 c;
    s16 b;
    u16 a;
    s32 i;
    s32 player;
    s32 position;
    s32 owner;
    s32 state;
    s32 result;
    u16 *record = arg0;
    extern s32 func_002770E0();
    extern void func_0027E770();

    if (func_001DF540((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        player = func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF);
        position = func_001E1090((s32) record[0] >> 8, record[0] & 0xFF);
        owner = func_001DF540((s32) record[0] >> 8, record[0] & 0xFF);
        record[2] = 0xBFF;
        for (i = 0; i < 22; i++) {
            slots[i].position = 0xFFFF;
            slots[i].flag = 0xFF;
        }
        func_0027E770(work);
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 4; i++) {
            state = func_002770E0(state, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i, 0,
                                  func_0011FA80(player), slots, &a, &c, &b, work);
            result = func_00277CD0((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 4, 0x1F, 1, 2, 0, func_0011FA80(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_00277CD0((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                   slots, 4, 0x1F, 0, 2, 0, func_0011FA80(player), a, 1);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 4; i++) {
            state = func_002770E0(state, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF), (u8) i, 0,
                                  func_0011FA80(player), slots, &a, &c, &b, work);
            result = func_002774F0(position & 0xFF, position >> 8, slots, 4, 0x22, 2, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_002774F0(position & 0xFF, position >> 8, slots, 4, 0x1F, 1, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_002774F0(position & 0xFF, position >> 8, slots, 4, 0x1F, 0, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        record[2] = 0x5FF;
    }
}

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_0011DFB0;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_0011DFB0;

s32 func_0011E6E0(s32 arg0, void *arg1);
s32 func_0011E270(s32 arg0, u8 arg1, void *arg2);

s32 func_0011DFB0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_00278890(s32, s32);
    Act_0011DFB0 *act = (Act_0011DFB0 *)arg2;
    Card_0011DFB0 buf;
    s32 res;
    s32 card;
    s32 type;
    s32 r;

    act->card = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    type = func_0011E6E0(arg1, &buf);
    if (type < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (type == 0) {
        if (func_0011EF60(arg1, (u8 *)act, &buf) >= 0) {
            res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_0011FA80(arg1));
            if (res < 0) {
                if (func_001E0150(arg1) < 4) {
                    r = func_0011E270(arg1, type, &buf);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = func_0011E270(arg1, type, &buf);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_0011FA80(arg1));
    }
    if (type == 2) {
        func_0011F3C0(arg1, arg2, (s32)&buf, 0);
        r = func_0011E270(arg1, type, &buf);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 3) {
        func_0011F3C0(arg1, arg2, (s32)&buf, 1);
        r = func_0011E270(arg1, type, &buf);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (func_0011ED50(arg1, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = func_0011E270(arg1, type, &buf);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011E270);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011E6E0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011EB10);

s32 func_0011ED50(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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
        if ((func_0026FCE0(buf[i]) >> 5) != 0 && buf[i] != 0x31F) {
            arg1[6] = i;
            func_001DCD70(arg2, buf[i]);
            return 1;
        }
    }
    return -1;
}

typedef struct Info_0011EF60 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0011EF60;

typedef struct Sprite_0011EF60 {
    Info_0011EF60 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0011EF60;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);
s32 func_00278F10(s32, u16 *, s32, s32);

s32 func_0011EF60(s32 arg0, u8 *arg1, void *arg2) {
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
                if ((func_0026FCE0(card) >> 5) == 0 && card != 0x156) {
                    *node = func_00278A90(arg0, *node, i & 0xFF, card & 0xFFFF, 0, &a, &b);
                    *node = func_00278E40(*node);
                    value = func_00278F10(arg0, *node, 0, 0);
                    if (func_0026FB10(arg0, card) == 1) {
                        if (best < value) {
                            func_0011F150(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_0011EF60 *)arg2)->x = (value >> 16) - (((Sprite_0011EF60 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0011EF60 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0011EF60 *)arg2)->info->y & 0x1FFF);
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
} Info_0011F150;

void func_0011F150(s32 arg0, void *arg1, s32 *arg2) {
    Info_0011F150 *info = arg1;
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
                if (card != 0x3E7 && func_0011F330(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0xDAD && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_0011F330(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if ((arg0 == 0x1F0) || (arg0 == 0x1FD) || (arg0 == 0x1FE) ||
        (arg0 == 0x202) || (arg0 == 0x1F6) || (arg0 == 0x20B)) {
        return 1;
    }
    return 0;
}

typedef struct {
    u8 pad[6];
    u8 indices[5];
} CardState_0011F3C0;

void func_0011EB10(s32, s32, s32, s32);

s32 func_0011F3C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 cards[5];
    s32 *card;
    s32 i;
    s32 card_id;

    if (arg2 == 0) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        ((CardState_0011F3C0 *)(arg1 + i))->indices[0] = 0xFF;
    }
    func_0026FD30(arg0, cards);
    if ((arg3 & 0xFF) == 0) {
        func_0011EB10(arg0, arg1, arg2, 0);
        i = 0;
        if (0 < func_0026FE20(arg0)) {
            card = cards;
            do {
                if ((i != ((CardState_0011F3C0 *)arg1)->indices[0]) && (i != ((CardState_0011F3C0 *)arg1)->indices[1]) && (func_00248F60(0x1E8, *card) >= 0) && ((func_0026FCE0(*card) >> 5) == 2)) {
                    card_id = *card;
                    if ((card_id != 0x31B) && (card_id != 0x31C)) {
                        ((CardState_0011F3C0 *)arg1)->indices[2] = i;
                    }
                }
                card++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
    } else if ((arg3 & 0xFF) == 1) {
        func_0011EB10(arg0, arg1, arg2, 0);
    }
    return 0;
}

void func_0011F530(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011F540);

s32 func_0011FA80(s32 arg0) {
    if (func_001DF470(arg0) > 0x3E8) {
        if (func_001E0150(arg0) >= 3) {
            return 0x1F4;
        } else {
            return 0x3E8;
        }
    } else {
        return 0x7D0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011FAE0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00120150);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001206F0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001211B0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001214E0);

void func_001215E0(void *arg0, u8 arg1) {
    if (arg1 < 2) {
        if (arg1 == 1) {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF) | 0xFFFF0000;
        } else {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF0000) | 0xFFFF;
        }
    }
}

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6[5];
    u8 padB;
    s32 unkC;
    u8 unk10;
} Req_00121630;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00121630;

s32 func_0011C600(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_00121630(s32 arg0, void *arg1) {
    Req_00121630 req;
    Work_00121630 *w;
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
        if (func_0011C600(w, &req, arg0) == 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_006", func_00121800);

typedef struct Unit_00121CE0 {
    u16 pos;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
} Unit_00121CE0;

void func_001229F0(void *, s32);
void func_00122270(void *);
void func_00122B50(void *);
void func_0027CA50(void *, s32, s32, s32);

s32 func_00121CE0(void *arg0) {
    Unit_00121CE0 *unit = arg0;
    s32 handle;

    handle = func_00250360(unit->pos >> 8, unit->pos & 0xFF);
    if (func_001DF540(unit->pos >> 8, unit->pos & 0xFF) != 0 &&
        func_001E2100(unit->pos >> 8, unit->pos & 0xFF, 0) == 0 && unit->pos != 0xFFFF) {
    if ((unit->pos & 0xFF) == 0) {
        if (unit->unk8 == -1) {
            func_0027E210(unit, 3, 2, 0);
        }
    } else {
        switch (func_001E0700(unit->pos >> 8, unit->pos & 0xFF) >> 5) {
        case 0:
            if (func_002507D0(unit->pos >> 8, unit->pos & 0xFF) == 1) {
                func_001229F0(unit, 1);
            } else {
                func_00122270(unit);
            }
            break;
        case 1:
        case 5:
            unit->unk4 = 0x5FF;
            break;
        case 2:
            func_0027CA50(unit, 2, 0, (u8)func_001254A0(handle));
            break;
        case 4:
            func_00122B50(unit);
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

s32 func_00121E90(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_00121CE0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00122D30(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00122D30(pos, arg1, arg2) >= 0) {
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

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122270);

void func_001224D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 1500, arg_sp28);
}

typedef struct {
    u16 coordinates;
    u16 unk02;
    s16 state;
    u16 unk06;
    union {
        u32 word;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Entry_00122530;

s32 func_00122970(s32);
void func_00123500(s32, s32, s32, s32 *);

void func_00122530(void *arg0) {
    Entry_00122530 *entry = arg0;
    s32 packed;
    s32 position;
    s32 result[2];
    u16 coordinates;

    coordinates = entry->coordinates;
    if (func_001DF540((s32) coordinates >> 8, coordinates & 0xFF) != 0) {
        coordinates = entry->coordinates;
        func_0024DE70((s32) coordinates >> 8, coordinates & 0xFF);
        coordinates = entry->coordinates;
        packed = func_001E1090((s32) coordinates >> 8, coordinates & 0xFF);
        entry->state = 0x6FF;
        coordinates = entry->coordinates;
        if (func_001E0290((s32) coordinates >> 8, coordinates & 0xFF, 0) >= 0x5DC) {
            coordinates = entry->coordinates;
            position = func_00122680((s32) coordinates >> 8, coordinates & 0xFF);
            if (position >= 0) {
                entry->data.word = entry->data.halves.low | (func_00122970((position + 1) % 8) << 16);
                return;
            }
            entry->data.word = entry->data.halves.low | (func_00122810(packed & 0xFF, packed >> 8) << 16);
            return;
        }
        coordinates = entry->coordinates;
        func_00123500(func_001DF540((s32) coordinates >> 8, coordinates & 0xFF), packed & 0xFF, packed >> 8, result);
        if (result[0] >= 0) {
            entry->data.word = (result[0] << 16) | entry->data.halves.low;
            return;
        }
        entry->state = 0x5FF;
    }
}

s32 func_00122680(s32 arg0, s32 arg1) {
    s32 x;
    s32 y;

    x = func_001E1090(arg0, arg1) & 0xFF;
    y = func_001E1090(arg0, arg1) >> 8;
    if ((x >= 2) && (x < 6) && (y == 0)) {
        return 0;
    }
    if ((x == 6) && (y >= 0) && (y < 4)) {
        return 1;
    }
    if ((x > 4) && (x < 7) && (y == 4)) {
        return 2;
    }
    if ((x == 4) && (y >= 4) && (y < 6)) {
        return 3;
    }
    if ((x > 0) && (x < 5) && (y == 6)) {
        return 4;
    }
    if ((x == 0) && (y > 2) && (y < 7)) {
        return 5;
    }
    if ((x >= 0) && (x < 2) && (y == 2)) {
        return 6;
    }
    if ((x == 2) && (y > 0) && (y < 3)) {
        return 7;
    }
    return -1;
}

s32 func_00122810(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s6;
    s32 var_v0;

    var_s1 = -1;
    var_s0 = 0;
    do {
        if (arg1 < (func_00122970(var_s0) >> 8)) {
            var_s2 = arg1;
        } else {
            var_s2 = func_00122970(var_s0) >> 8;
        }
        if ((func_00122970(var_s0) >> 8) < arg1) {
            var_s3 = arg1;
        } else {
            var_s3 = func_00122970(var_s0) >> 8;
        }
        if (arg0 < (func_00122970(var_s0) & 0xFF)) {
            var_s6 = arg0;
        } else {
            var_s6 = func_00122970(var_s0) & 0xFF;
        }
        if ((func_00122970(var_s0) & 0xFF) < arg0) {
            var_v0 = arg0;
        } else {
            var_v0 = func_00122970(var_s0) & 0xFF;
        }
        if (((var_v0 - var_s6) + (var_s3 - var_s2)) >= -1) {
            var_s1 = func_00122970(var_s0);
        }
        var_s0 += 1;
    } while (var_s0 < 8);
    return var_s1;
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122970);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001229F0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122B50);

typedef struct {
    s16 card;
    u8 f2;
    u8 pad3;
    s16 f4;
    u8 pad6[6];
    s32 fC;
} Act_00122D30;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 pad3E[0x22];
} Card_00122D30;

s32 func_00123740(s32 arg0, void *arg1);
s32 func_00123010(s32 arg0, u8 arg1, void *arg2, s32 arg3);

s32 func_00122D30(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_00278890(s32, s32);
    Card_00122D30 buf;
    s32 res;
    s32 type;
    Act_00122D30 *act = (Act_00122D30 *)arg2;
    s32 card;
    s32 r;

    act->card = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    if ((type = func_00123740(arg1, &buf)) < 0) {
        return -1;
    }
    act->f2 = 10;
    act->fC = 0;
    card = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (type == 0) {
        if (func_00124810(arg1, (u8 *)act, &buf) >= 0) {
            res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 2, 0x1F, 2, 2, 0, func_001254A0(arg1));
            if (res < 0) {
                if (func_001E0150(arg1) < 4) {
                    r = func_00123010(arg1, type, &buf, res);
                    if (r < 0) {
                        return -1;
                    }
                    act->f4 = r;
                    return 1;
                }
            } else {
                r = func_00123010(arg1, type, &buf, res);
                if (r < 0) {
                    return -1;
                }
                act->f4 = r;
                return 1;
            }
        }
    } else {
        res = func_00276F10(&buf, card & 0xFF, card >> 8, arg1 == 0 ? 1 : 0, 2, 0x1F, 2, 2, 0, func_001254A0(arg1));
    }
    if (type == 3) {
        func_00124C90(arg1, act, &buf, 1);
        r = func_00123010(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else if (type == 2) {
        func_00124C90(arg1, act, &buf, 0);
        r = func_00123010(arg1, type, &buf, res);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    } else {
        if (func_00124610(arg1, (u8 *)act, &buf, buf.id) < 0) {
            return -1;
        }
        r = func_00123010(arg1, type, &buf, -1);
        if (r < 0) {
            return -1;
        }
        act->f4 = r;
        return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123010);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123500);

s32 func_00123670(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        return 0x303;
    case 1:
        return 0x304;
    default:
    case 2:
        return 0x302;
    }
}

s32 func_001236C0(s32 arg0) {
    s32 var_v0;

    switch (arg0) {
        case 0:
            var_v0 = 0x303;
            break;
        case 1:
            var_v0 = 0x304;
            break;
        case 2:
        default:
            var_v0 = 0x302;
            break;
    }
    if ((var_v0 >= 0) && (func_001E36E0(var_v0 & 0xFF, var_v0 >> 8) == 0)) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123740);

s32 func_00123D70(s32 arg0, s32 *arg1) {
    s32 i;
    s32 result;
    s32 *entry;

    result = 0;
    i = 0;
    if (0 < func_0026FE20(arg0)) {
        do {
            entry = &arg1[i];
            if ((func_0026FB10(arg0, *entry) == 1) && ((func_0026FCE0(*entry) >> 5) == 0)) {
                result = (result + (1 << (4 - i))) & 0xFF;
                i = func_0026FE20(arg0);
            }
            i++;
        } while (i < func_0026FE20(arg0));
    }
    {
        s32 resultCheck;
        resultCheck = result & 0xFF;
        if (resultCheck == 0) {
            return 0;
        }
    }
    i = 0;
    if (0 < func_0026FE20(arg0)) {
        do {
            entry = &arg1[i];
            if ((func_0026FB10(arg0, *entry) == 1) && ((func_0026FCE0(*entry) >> 5) == 0x12)) {
                result = (result + (1 << (4 - i))) & 0xFF;
                i = func_0026FE20(arg0);
            }
            i++;
        } while (i < func_0026FE20(arg0));
    }
    {
        s32 resultCheck;
        resultCheck = result & 0xFF;
        if (resultCheck == 2) {
            i = 0;
            if (0 < func_0026FE20(arg0)) {
                do {
                    entry = &arg1[i];
                    if ((func_0026FB10(arg0, *entry) == 1) && ((func_0026FCE0(*entry) >> 5) == 0xF)) {
                        result = (result + (1 << (4 - i))) & 0xFF;
                        i = func_0026FE20(arg0);
                    }
                    i++;
                } while (i < func_0026FE20(arg0));
            }
            return result & 0xFF;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123F90);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00124040);

s32 func_00124520(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;

    func_0026FD30(arg0, entries);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (((arg3 & 0xFFFF) == entries[i]) && (func_0026FB10(arg0, entries[i]) == 1)) {
            ((s8 *)arg1)[6] = i;
            func_001DCD70(arg2, entries[i]);
            return func_0026FCE0(entries[i]) >> 5;
        }
    }
    return -1;
}
