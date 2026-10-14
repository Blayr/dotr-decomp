#include "common.h"

typedef struct {
    u16 position;
    u8 flag;
    u8 pad;
} Slot_0012CE50;

void func_0012CE50(void *arg0) {
    u8 work[112];
    Slot_0012CE50 slots[22];
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
    extern s32 func_001E1580();
    extern s32 func_001E1640();

    if (func_001DF540((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        player = func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF);
        position = func_001E1090((s32) record[0] >> 8, record[0] & 0xFF);
        owner = func_001DF540((s32) record[0] >> 8, record[0] & 0xFF);
        record[2] = 0xBFF;
        func_0027E770(work);
        for (i = 0; i < 22; i++) {
            slots[i].position = 0xFFFF;
            slots[i].flag = 0xFF;
        }
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 3; i++) {
            state = func_002770E0(state, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF) == 0 ? 1 : 0, (u8) i, 0,
                                  func_00130780(player), slots, &a, &c, &b, work);
            if ((result = func_00277CD0((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                        slots, 5, 0x1F, 1, 2, 0, func_00130780(player), a, 1)) >= 0) {
                if (func_001E1580(result >> 8, result & 0xFF) == 0 &&
                    func_001E1640(result >> 8, result & 0xFF) == 0) {
                    *(u32 *) (record + 4) = (result << 16) | record[4];
                    return;
                }
            }
            if ((result = func_00277CD0((s32) record[0] >> 8, record[0] & 0xFF, position & 0xFF, position >> 8,
                                        slots, 5, 0x1F, 0, 2, 0, func_00130780(player), a, 1)) >= 0) {
                if (func_001E1580(result >> 8, result & 0xFF) == 0 &&
                    func_001E1640(result >> 8, result & 0xFF) == 0) {
                    *(u32 *) (record + 4) = (result << 16) | record[4];
                    return;
                }
            }
        }
        a = 0;
        b = 0;
        c = 0;
        state = 0;
        for (i = 1; i < 3; i++) {
            state = func_002770E0(state, owner, position & 0xFF, position >> 8,
                                  func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF), (u8) i, 0,
                                  func_00130780(player), slots, &a, &c, &b, work);
            result = func_002774F0(position & 0xFF, position >> 8, slots, 5, 0x22, 2, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_002774F0(position & 0xFF, position >> 8, slots, 5, 0x1F, 1, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
            result = func_002774F0(position & 0xFF, position >> 8, slots, 5, 0x1F, 0, 2, a);
            if (result >= 0) {
                *(u32 *) (record + 4) = (result << 16) | record[4];
                return;
            }
        }
        *(u32 *) (record + 4) = (player << 24) | record[4];
    }
}

typedef struct Result_0012D270 {
    s16 position;
    s8 kind;
    u8 pad3;
    s16 value;
    u8 pad6[6];
    s32 flags;
} Result_0012D270;

typedef struct Work_0012D270 {
    u8 pad0[0x3C];
    u16 field3C;
    u8 pad3E[0x22];
} Work_0012D270;


s32 func_0012D270(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_00278890();
    extern s32 func_00276F10();
    extern s64 func_00130780();
    Work_0012D270 work;
    s32 packed;
    s32 x;
    s32 mode;
    s32 selection;
    s32 value;

    ((Result_0012D270 *)arg2)->position = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5) {
        if (func_00278890(arg1, 1) == 5) {
            return -1;
        }
    }
    mode = func_0012D520(arg1, &work, arg3);
    if (mode < 0) {
        return -1;
    }
    {
        s32 y = arg0 >> 8;
        x = arg0 & 0xFF;
        ((Result_0012D270 *)arg2)->kind = 10;
        ((Result_0012D270 *)arg2)->flags = 0;
        packed = func_001E1090(y, x);
        selection = func_00276F10(&work, packed & 0xFF, packed >> 8,
                                arg1 == 0 ? 1 : 0, 3, 31, 2, 2,
                                (s64)0, (s64)func_00130780(arg1));
        if (mode == 0) {
            if (func_0012DDE0(arg1, (u8 *)arg2, &work) >= 0) {
                s32 packed2 = func_001E1090(y, x);
                selection = func_00276F10(&work, packed2 & 0xFF, packed2 >> 8,
                                        arg1 == 0 ? 1 : 0, 3, 31, 2, 2,
                                        (s64)0, (s64)func_00130780(arg1));
                if (selection < 0) {
                    if (func_001E0150(arg1) < 6) {
                        value = func_0012E3F0(arg1, 0, &work, selection);
                        if (value < 0) {
                            return -1;
                        }
                        ((Result_0012D270 *)arg2)->value = value;
                        return 1;
                    }
                } else {
                    value = func_0012E3F0(arg1, 0, &work, selection);
                    if (value < 0) {
                        return -1;
                    }
                    ((Result_0012D270 *)arg2)->value = value;
                    return 1;
                }
            }
        } else if (mode == 2) {
            func_0012E1F0(arg1, (void *)arg2, &work);
            value = func_0012E3F0(arg1, mode & 0xFF, &work, selection);
            if (value < 0) {
                return -1;
            }
            ((Result_0012D270 *)arg2)->value = value;
            return 1;
        }
        value = func_0012DBE0(arg1, (u8 *)arg2, &work, work.field3C);
        if (value < 0) {
            return -1;
        }
        value = func_0012E3F0(arg1, value & 0xFF, &work, selection);
        if (value < 0) {
            return -1;
        }
        ((Result_0012D270 *)arg2)->value = value;
        return 1;
    }
}

s32 func_0012D520(s32 arg0, void *arg1, s32 arg2) {
    s32 cards[8];
    u8 scratch[32];
    s32 result;
    u8 status0;
    u8 status1;
    u8 count;
    extern s32 func_00278890();

    status0 = func_00278890(arg0, 0);
    status1 = func_00278890(arg0, 1);
    count = 0;
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, cards);
    if (status0 == 5) {
        if (func_0012DBE0(arg0, scratch, arg1, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (status1 == 5) {
        s32 i;
        s32 *p;

        i = 0;
        if (i < func_0026FE20(arg0)) {
            p = cards;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                    func_001DCD70(arg1, cards[i]);
                    return 0;
                }
                p++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
        return -1;
    }
    if ((u8)arg2 == 0) {
        s32 i;

        if ((result = func_0012D960(arg0, cards, arg1, scratch)) >= 0) {
            return 2;
        }
        if (func_001307E0(arg0, 0x342) == 1) {
            if ((result = func_0012DAE0(arg0, cards, arg1, scratch, 0x342)) >= 0) {
                return 2;
            }
        }
        i = 0;
        do {
            if (func_001DF540(0, i) != 0) {
                if (arg0 != func_00250360(0, i)) {
                    count++;
                }
            }
            if (func_001DF540(1, i) != 0 && arg0 != func_00250360(1, i)) {
                count++;
            }
            i++;
        } while (i < 11);
        if (result >= 4) {
            if (func_0012DAE0(arg0, cards, arg1, scratch, 0x146) >= 0) {
                return 2;
            }
        }
        if (func_00130660(arg0) >= 0) {
            if (func_0012DAE0(arg0, cards, arg1, scratch, 0x131) >= 0) {
                return 2;
            }
        }
    } else {
        s32 i;

        if (func_001307E0(arg0, 0x342) == 1) {
            if ((result = func_0012DAE0(arg0, cards, arg1, scratch, 0x342)) >= 0) {
                return 2;
            }
        }
        i = 0;
        do {
            if (func_001DF540(0, i) != 0) {
                if (arg0 != func_00250360(0, i)) {
                    count++;
                }
            }
            if (func_001DF540(1, i) != 0 && arg0 != func_00250360(1, i)) {
                count++;
            }
            i++;
        } while (i < 11);
        if (result >= 4 && func_0012DAE0(arg0, cards, arg1, scratch, 0x146) >= 0) {
            return 2;
        }
    }
    {
        s32 *p;
        s32 i;

        i = 0;
        if (i < func_0026FE20(arg0)) {
            p = cards;
            do {
                if ((func_0026FCE0(*p) >> 5) == 0 && func_0026FB10(arg0, *p) == 1) {
                    return 0;
                }
                p++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
    }
    result = func_0012DBE0(arg0, scratch, arg1, 999);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 func_0012D960(s32 arg0, s32 *arg1, void *arg2, void *arg3) {
    s32 i;
    s32 *p;
    s32 *q;
    s32 j;
    s32 value;

    i = 0;
    if (i < func_0026FE20(arg0)) {
        p = arg1;
        do {
            if (func_001DE020(func_0026FCE0(*p) >> 5) == 2) {
                *((s8 *)arg3 + 6) = i;
                func_001DCD70(arg2, arg1[i]);
                return func_0026FCE0(arg1[i]) >> 5;
            }
            p++;
            i++;
        } while (i < func_0026FE20(arg0));
    }

    j = 0;
    if (j < func_0026FE20(arg0)) {
        q = arg1;
        do {
            if (func_0026FB10(arg0, *q) == 1) {
                value = *q;
                if (value == 0x31B || value == 0x2AC || value == 0x137) {
                    *((s8 *)arg3 + 6) = j;
                    func_001DCD70(arg2, arg1[j]);
                    return func_0026FCE0(arg1[j]) >> 5;
                }
            }
            q++;
            j++;
        } while (j < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_0012DAE0(s32 arg0, s32 *arg1, void *arg2, void *arg3, s32 arg4) {
    s32 i;
    s32 *entry;
    s32 wanted;

    i = 0;
    if (i < func_0026FE20(arg0)) {
        wanted = arg4 & 0xFFFF;
        entry = arg1;
        do {
            if (func_0026FB10(arg0, *entry) == 1) {
                if (wanted == *entry && func_0026FB10(arg0, *entry) == 1) {
                    *((u8 *)arg3 + 6) = i;
                    func_001DCD70(arg2, arg1[i]);
                    return func_0026FCE0(arg1[i]) >> 5;
                }
            }
            entry++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_0012DBE0(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_0012DDE0 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_0012DDE0;

typedef struct Sprite_0012DDE0 {
    Info_0012DDE0 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_0012DDE0;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);

s32 func_0012DDE0(s32 arg0, u8 *arg1, void *arg2) {
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
                            func_0012DFC0(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_0012DDE0 *)arg2)->x = (value >> 16) - (((Sprite_0012DDE0 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_0012DDE0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_0012DDE0 *)arg2)->info->y & 0x1FFF);
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
} Info_0012DFC0;

void func_0012DFC0(s32 arg0, void *arg1, s32 *arg2) {
    Info_0012DFC0 *info = arg1;
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
                if (card != 0x3E7 && func_0012E1A0(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x1069 && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_0012E1A0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    return func_0026FC10(arg0) != 0 ? 1 : 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_0012E1F0;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
    u8 f3E;
} Obj2_0012E1F0;

s32 func_0012E1F0(s32 arg0, void *arg1, void *arg2) {
    Obj1_0012E1F0 *o1 = arg1;
    Obj2_0012E1F0 *o2 = arg2;
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
    return o2->f3E >> 5;
}

typedef struct Nibbles_0012E3F0 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0012E3F0;

s32 func_0012E3F0(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    extern s32 func_00278510();
    extern s32 func_0027A130();
    extern s32 func_002792C0(s32, s32, s32, s32, s32, s32, u16, u8);
    s32 best;
    s32 bestCost;
    s32 nearest;
    Nibbles_0012E3F0 flags[12];
    s32 i;
    Nibbles_0012E3F0 *p;
    u8 kind;

    if (arg2 == NULL) {
        return -1;
    }
    p = flags;
    i = 0;
    do {
        p->low = p->high = 15;
        p++;
        i++;
    } while (i < 12);

    kind = *(u8 *)((u8 *)arg2 + 0x3E) >> 5;
    if (kind == 0U || kind == 3U || kind == 2U) {
        if (arg3 >= 0) {
            s32 candidate;
            s32 y;
            s32 x;
            s32 index;
            s32 originY;
            s32 originX;
            s32 origin;
            s32 cost;

            bestCost = 255;
            best = 65535;
            origin = func_001E1090(arg3 >> 8, arg3 & 255);
            index = 0;
            originY = origin >> 8;
            originX = origin & 255;
            do {
                candidate = func_0024E410(arg0, index);
                if (candidate >= 0) {
                    x = candidate & 255;
                    y = candidate >> 8;
                    if (func_001E22B0(x, y) != 8 &&
                        (func_001E22B0(x, y) != 9 ||
                         func_0024FE40(arg2, x, y) != 1) &&
                        func_001E36E0(x, y) == 0) {
                        if (func_00278510(arg2, arg3, func_00130780(arg0),
                                         originX, originY, 0) > 0) {
                            cost = func_0027A130(arg2, flags, x, y,
                                                originX, originY, arg3, 0,
                                                5, (u16)func_00130780(arg0));
                        } else {
                            cost = func_002792C0((s32)arg2, (s32)flags, x, y,
                                                originX, originY, arg3, 2);
                        }
                        if (func_0027AFC0((u8 *)flags) > 0 && cost < bestCost) {
                            bestCost = cost;
                            best = candidate;
                        }
                    }
                }
                index++;
            } while (index < 8);
            if (best != 65535) {
                return best;
            }
            best = -1;
            return best;
        }
        {
            s32 originY;
            s32 originX;
            s32 maxY;
            s32 maxX;
            s32 y;
            s32 x;
            s32 index;
            s32 distance;
            s32 candidate;
            s32 minY;
            s32 minX;
            s32 origin;

            distance = 14;
            nearest = -1;
            origin = func_001E1090(arg0 == 0 ? 1 : 0, 0);
            index = 0;
            originY = origin >> 8;
            originX = origin & 255;
            do {
                candidate = func_0024E410(arg0, index);
                if (candidate >= 0) {
                    x = candidate & 255;
                    y = candidate >> 8;
                    if (func_001E22B0(x, y) != 8 &&
                        (func_001E22B0(x, y) != 9 ||
                         func_0024FE40(arg2, x, y) != 1) &&
                        func_001E3790(x, y) < 0) {
                        if (y < originY) {
                            minY = y;
                        } else {
                            minY = originY;
                        }
                        if (y > originY) {
                            maxY = y;
                        } else {
                            maxY = originY;
                        }
                        if (x < originX) {
                            minX = x;
                        } else {
                            minX = originX;
                        }
                        if (x > originX) {
                            maxX = x;
                        } else {
                            maxX = originX;
                        }
                        origin = (maxX - minX) + (maxY - minY);
                        if (origin < distance && origin >= 0) {
                            nearest = candidate;
                            distance = origin;
                        }
                    }
                }
                index++;
            } while (index < 8);
            if (distance < 14) {
                return nearest;
            }
        }
    } else {
        s32 y;
        s32 x;
        s32 index;
        s32 last;
        s32 candidate;

        last = -1;
        index = 0;
        do {
            candidate = func_0024E410(arg0, index);
            if (candidate >= 0) {
                x = candidate & 255;
                y = candidate >> 8;
                if (func_001E22B0(x, y) != 8 &&
                    func_001E22B0(x, y) != 9 &&
                    func_001E3790(x, y) < 0 && y < 8) {
                    last = candidate;
                }
            }
            index++;
        } while (index < 8);
        if (last >= 0) {
            return last;
        }
    }
    return -1;
}

typedef struct Nibbles_0012E820 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_0012E820;

typedef struct Output_0012E820 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_0012E820;

s32 func_00276CC0(s32, s32, s32, s32, s32, s32);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_0012E820(u16 *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    Output_0012E820 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_0012E820 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_0012E820 *p;
    extern s32 func_00130940(s32, s32, void *, u8);
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);

    target = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    p = nibbles;
    i = 0;
    do {
        i++;
        p->low = p->high = 0xF;
        p++;
    } while (i < 12);
    {
        s32 range;
        s32 y;
        u8 minY;
        u8 minX;
        s32 candidateScore;
        u8 maxY;
        s32 packedY;
        s32 centerY;
        s32 centerX;
        s32 x;
        s32 limit;
        u16 initialScore;

        initialScore = func_00130780(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (func_00276CC0(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00130940(*arg0 >> 8, *arg0 & 0xFF, arg0, arg4);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if ((range = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00130940(*arg0 >> 8, *arg0 & 0xFF, arg0, arg4);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        best = 0xFF;
        bestScore = 0xFFFF;
        minX = (u8)func_00250860(0, centerX - (range & 0xF));
        limit = centerX + (range & 0xF);
        endX = limit >= 7 ? 6 : limit;
        minY = (u8)func_00250860(0, centerY - (range & 0xF));
        limit = centerY + (range & 0xF);
        if (limit >= 7) {
            limit = 6;
        }
        maxY = (u8)limit;
        if ((*arg0 & 0xFF) == 0) {
            extra = (u8)func_0027BBC0(*arg0 >> 8, *arg0 & 0xFF, 0);
        } else {
            extra = 0;
        }
        for (x = minX; x <= endX; x++) {
            y = minY;
            packedY = y << 8;
            for (; y <= maxY; packedY += 0x100, y++) {
                if ((((x < centerX ? centerX : x) - (centerX < x ? centerX : x)) +
                    ((y < centerY ? centerY : y) - (centerY < y ? centerY : y))) > (range & 0xF)) {
                    continue;
                }
                if (func_00279C40(*arg0 >> 8, *arg0 & 0xFF, centerX, centerY, x, y, arg0, extra) == 1) {
                    if (func_0027BE10(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0) {
                        candidateScore = func_00276CC0(x, y, *arg0, 3, (u16)func_00130780(arg1), 0);
                        if (candidateScore < bestScore) {
                            bestScore = candidateScore;
                            best = packedY | x;
                        } else if (candidateScore == bestScore && func_001E36E0(x, y) == 0 &&
                            func_001E36E0(best & 0xFF, best >> 8) != 0) {
                            bestScore = candidateScore;
                            best = packedY | x;
                        }
                    }
                }
            }
        }
        if (best != 0xFF) {
            output->position = *arg0;
            output->action = 6;
            output->destination = best;
            if (best == target) {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            } else {
                output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 0, 0);
            }
            output->special = func_00130940(*arg0 >> 8, *arg0 & 0xFF, arg0, arg4);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00130940(*arg0 >> 8, *arg0 & 0xFF, arg0, arg4);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    }
}

typedef struct Coord_0012ED70 {
    u8 x : 4;
    u8 y : 4;
} Coord_0012ED70;

typedef struct Result_0012ED70 {
    u16 card;
    u8 action;
    u8 pad03;
    u16 position;
    u8 pad06[6];
    s32 count;
    u8 flags;
} Result_0012ED70;

s32 func_0012ED70(void *arg0, s32 arg1, s32 arg2, u8 arg3) {
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);
    Coord_0012ED70 positions[12];
    s32 i;
    Coord_0012ED70 *p;
    s32 position;

    position = func_001E1090(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF);
    p = positions;
    i = 0;
    do {
        p->x = p->y = 15;
        i++;
        p++;
    } while (i < 12);
    {
        s32 data;
        s32 card;
        s32 player;

        data = func_00130660(arg1);
        if (data >= 0) {
            player = (u16)(data >> 16);
            card = func_0027DBC0(player, data & 0xFF, 30);
            ((Result_0012ED70 *)arg2)->card = *(u16 *)arg0;
            ((Result_0012ED70 *)arg2)->action = 12;
            ((Result_0012ED70 *)arg2)->flags = func_0027E360(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 1, 0);
            ((Result_0012ED70 *)arg2)->count = 1;
            *(u16 *)(arg2 + 4) = (player << 8) | card;
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }
    if (func_001E2100(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 4) != 0) {
        func_001E1E70(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0, 1);
        ((Result_0012ED70 *)arg2)->card = *(u16 *)arg0;
        ((Result_0012ED70 *)arg2)->action = 14;
        return 0;
    }
    {
        s32 y;
        s32 cost;
        s32 packedY;
        s32 minY;
        s32 minX;
        s32 maxY;
        s32 centerY;
        s32 centerX;
        s32 x;
        s32 bestPosition;
        s32 bestCost;
        u8 maxX;
        u8 flags;
        s32 bound;
        s32 rangeResult;
        u16 card;

        card = func_00130780(arg1);
        centerX = position & 0xFF;
        centerY = position >> 8;
        if (func_00276CC0(centerX, centerY, *(u16 *)arg0, 3, card, 0) == 0) {
            ((Result_0012ED70 *)arg2)->card = *(u16 *)arg0;
            ((Result_0012ED70 *)arg2)->action = 6;
            *(u16 *)(arg2 + 4) = position;
            ((Result_0012ED70 *)arg2)->flags = func_0027E360(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 1, 0);
            ((Result_0012ED70 *)arg2)->count = 2;
            func_0027B1B0(arg0, arg3);
        } else {
            rangeResult = func_002464F0(func_001DF540(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF), centerX, centerY);
            if (rangeResult == 0) {
                ((Result_0012ED70 *)arg2)->card = *(u16 *)arg0;
                ((Result_0012ED70 *)arg2)->action = 6;
                *(u16 *)(arg2 + 4) = position;
                ((Result_0012ED70 *)arg2)->flags = func_0027E360(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 1, 0);
                ((Result_0012ED70 *)arg2)->count = 2;
                func_0027B1B0(arg0, arg3);
                return 0;
            } else {
                bestPosition = 0xFF;
                bestCost = 0xFFFF;
                minX = (u8)func_00250860(0, centerX - (rangeResult & 15));
                bound = centerX + (rangeResult & 15);
                if (bound >= 7) {
                    maxX = 6;
                } else {
                    maxX = (u8)bound;
                }
                minY = (u8)func_00250860(0, centerY - (rangeResult & 15));
                bound = centerY + (rangeResult & 15);
                if (bound >= 7) {
                    bound = 6;
                }
                maxY = (u8)bound;
                if ((*(u16 *)arg0 & 0xFF) == 0) {
                    flags = (u8)func_0027BBC0(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, 0);
                } else {
                    flags = 0;
                }
                for (x = (u8)minX; x <= (u8)maxX; x++) {
                    for (y = (u8)minY, packedY = y << 8; y <= (u8)maxY; packedY += 0x100, y++) {
                        if (((x < centerX ? centerX : x) - (centerX < x ? centerX : x)) +
                            ((y < centerY ? centerY : y) - (centerY < y ? centerY : y)) <= (rangeResult & 15)) {
                            if (func_00279C40(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, centerX, centerY, x, y, arg0, (u8)flags) == 1 &&
                                (func_0027BE10(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, x, y, 0) == 0 || (u8)*(u16 *)arg0 == 0)) {
                                card = func_00130780(arg1);
                                cost = func_00276CC0(x, y, *(u16 *)arg0, 3, card, 0);
                                if (cost < bestCost) {
                                    bestCost = cost;
                                    bestPosition = packedY | x;
                                } else if (cost == bestCost && func_001E36E0(x, y) == 0 &&
                                           func_001E36E0(bestPosition & 0xFF, bestPosition >> 8) != 0) {
                                    bestCost = cost;
                                    bestPosition = packedY | x;
                                }
                            }
                        }
                    }
                }
                if (bestPosition != 0xFF) {
                    ((Result_0012ED70 *)arg2)->card = *(u16 *)arg0;
                    ((Result_0012ED70 *)arg2)->action = 6;
                    *(u16 *)(arg2 + 4) = bestPosition;
                    if (bestPosition == position) {
                        ((Result_0012ED70 *)arg2)->flags = func_0027E360(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 1, 0);
                    } else {
                        ((Result_0012ED70 *)arg2)->flags = func_0027E360(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 0, 0);
                    }
                    ((Result_0012ED70 *)arg2)->count = 2;
                } else {
                    ((Result_0012ED70 *)arg2)->card = *(u16 *)arg0;
                    ((Result_0012ED70 *)arg2)->action = 6;
                    *(u16 *)(arg2 + 4) = position;
                    ((Result_0012ED70 *)arg2)->flags = func_0027E360(*(u16 *)arg0 >> 8, *(u16 *)arg0 & 0xFF, *(u16 *)(arg2 + 4), 1, 0);
                    ((Result_0012ED70 *)arg2)->count = 2;
                }
                func_0027B1B0(arg0, arg3);

            }
        }
    }
    return 0;
}

typedef struct Source_0012F350 {
    u16 position;
    u8 pad2[6];
    u32 targets;
} Source_0012F350;

typedef struct Output_0012F350 {
    u16 position;
    u8 mode;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 flag;
    u8 value;
} Output_0012F350;

typedef struct Position_0012F350 {
    u8 x : 4;
    u8 y : 4;
} Position_0012F350;

s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 target_0012F350(void *arg0, u8 which) {
    Source_0012F350 *source = arg0;
    if (which == 1) {
        return (u16)(source->targets >> 16);
    }
    return *(u16 *)&source->targets;
}

s32 func_0012F350(void *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4) {
    extern void func_0027A090();
    s32 sourceTarget;
    s32 count;
    s32 sourceY;
    s32 sourceX;
    s32 selectedFlag;
    Position_0012F350 positions[12];
    s32 flag;
    s32 otherTarget;
    s32 j;
    Position_0012F350 *walk;
    s32 object;
    u32 targetXWord;
    u32 targetYWord;
    Source_0012F350 *source = arg0;
    Output_0012F350 *output = arg2;

    targetXWord = target_0012F350(arg0, arg3);
    targetYWord = target_0012F350(arg0, arg3);
    if (func_001DF540(targetYWord >> 8, targetXWord & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }

    flag = func_00130940(source->position >> 8, source->position & 0xFF, arg0, arg4);
    sourceTarget = func_001E1090(source->position >> 8, source->position & 0xFF);
    targetXWord = target_0012F350(arg0, arg3);
    targetYWord = target_0012F350(arg0, arg3);
    otherTarget = func_001E1090(targetYWord >> 8, targetXWord & 0xFF);
    walk = positions;
    j = 0;
    do {
        walk->x = walk->y = 15;
        j++;
        walk++;
    } while (j < 12);

    object = func_001DF540(source->position >> 8, source->position & 0xFF);
    sourceX = sourceTarget & 0xFF;
    sourceY = sourceTarget >> 8;
    if (func_002464F0(object, sourceX, sourceY) == 0) {
        s32 cost;
        output->position = source->position;
        output->mode = 6;
        output->target = sourceTarget;
        cost = func_00276CC0(sourceX, sourceY, arg1, 3, 1,
                            (u8)func_00130780(arg1));
        if (cost >= func_001E0290(source->position >> 8, source->position & 0xFF, 0)) {
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 1, 0);
        } else {
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        }
        func_0027B1B0(arg0, arg3);
    } else {
        s32 targetY;
        s32 targetX;
        Position_0012F350 *current;
        s32 i;
        s32 bestCost;
        s32 selected;
        u16 position = source->position;

        func_0027A090(position >> 8, position & 0xFF, positions,
                      sourceX, sourceY, targetX = otherTarget & 0xFF,
                      targetY = otherTarget >> 8,
                      target_0012F350(arg0, arg3), 0, 30, (u16)func_00130780(arg1));
        count = func_0027AFC0((u8 *)positions);
        selected = 0xFF;
        if (count > 0) {
            selectedFlag = 0;
            bestCost = 0xFFFF;
            for (i = 0; i < count; i++) {
                s32 state = func_00130BB0(source->position >> 8, source->position & 0xFF,
                                          sourceX, sourceY, targetX, targetY);
                if (state == 1) {
                    Position_0012F350 *forcedPosition = &positions[i];
                    selected = i;
                    selectedFlag = 1;
                    i = count;
                    forcedPosition->x = targetX;
                    forcedPosition->y = targetY;
                } else {
                    s32 cost;
                    current = &positions[i];
                    cost = func_00276CC0(current->x, current->y, arg1, 3, 1,
                                        (u8)func_00130780(arg1));
                    if (cost < bestCost) {
                        bestCost = cost;
                        selected = i;
                    } else if (cost == bestCost) {
                        if (((targetX < current->x ? current->x : targetX) -
                             (current->x < targetX ? current->x : targetX)) +
                            ((targetY < current->y ? current->y : targetY) -
                             (current->y < targetY ? current->y : targetY)) <
                            ((targetX < positions[selected].x ? positions[selected].x : targetX) -
                             (positions[selected].x < targetX ? positions[selected].x : targetX)) +
                            ((targetY < positions[selected].y ? positions[selected].y : targetY) -
                             (positions[selected].y < targetY ? positions[selected].y : targetY))) {
                            bestCost = cost;
                            selected = i;
                        }
                    }
                }
            }
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = flag;
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (selected != 0xFF) {
            output->position = source->position;
            output->mode = 6;
            output->target = (positions[selected].y << 8) | positions[selected].x;
            output->flag = selectedFlag;
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
        } else {
            output->position = source->position;
            output->mode = 6;
            output->target = sourceTarget;
            output->flag = selectedFlag;
            output->value = func_0027E360(source->position >> 8, source->position & 0xFF,
                                        output->target, 0, 0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Unit_0012F930 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 halves[2];
    } destination;
} Unit_0012F930;

typedef struct Order_0012F930 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 value;
    u8 flags;
} Order_0012F930;

typedef struct Point_0012F930 {
    u8 x : 4;
    u8 y : 4;
} Point_0012F930;

s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 destination_0012F930(void *unit, s32 side) {
    if (side == 1) {
        return (u16)(((Unit_0012F930 *)unit)->destination.packed >> 16);
    }
    return ((Unit_0012F930 *)unit)->destination.halves[0];
}

s32 func_0012F930(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4, u8 arg5) {
    extern s32 func_00130940(s32, s32, void *, u8);
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    extern void func_00279230(s32, s32, void *, s32, s32, s32, s32, s32, u8);
    s32 count;
    s32 position;
    Point_0012F930 points[12];
    s32 id;
    s32 score;
    u32 destinationValue;
    Unit_0012F930 *unit = arg0;
    Order_0012F930 *order = arg2;

    {
    s32 bestScore;
    s32 bestIndex;
    s32 side;
    Point_0012F930 *point;
    s32 index;

    position = func_001E1090((s32)unit->position >> 8, unit->position & 0xFF);
    side = arg3;
    if (destination_0012F930(unit, side) == 0xFFFF) {
        if (position == destination_0012F930(unit, side)) {
            order->position = unit->position;
            order->kind = 6;
            order->destination = position;
            order->flags = func_0027E360((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, arg4, 0);
            order->value = func_00130940((s32)unit->position >> 8, unit->position & 0xFF, unit, arg5);
            func_0027B1B0(unit, arg3);
            return 0;
        }
    }

    point = points;
    {
        s32 i = 0;
        Point_0012F930 *p = point;
        do {
            p->x = p->y = 15;
            i++;
            p++;
        } while (i < 12);
    }

    destinationValue = destination_0012F930(unit, side);
    id = func_001E3790(destination_0012F930(unit, side) & 0xFF,
                       destinationValue >> 8);
    if (id < 0) {
        id = 0xFFFF;
    }
    destinationValue = destination_0012F930(unit, side);
    func_00279230((s32)unit->position >> 8, unit->position & 0xFF, points,
                  position & 0xFF, position >> 8,
                  destination_0012F930(unit, side) & 0xFF,
                  destinationValue >> 8, (u16)id, 7);
    count = func_0027AFC0((u8 *)points);
    if (count > 0) {
        bestIndex = 0xFF;
        bestScore = 0xFFFF;
        for (index = 0; index < count; index++, point++) {
            if (func_001E36E0(point->x, point->y) == 0) {
                score = func_00276CC0(point->x, point->y, arg1, 3, 1, (u8)func_00130780(arg1));
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
                    Point_0012F930 *best = &points[bestIndex];

                    oldY = best->y;
                    if (oldY < (destination_0012F930(unit, side) >> 8)) {
                        oldYMin = (u8)oldY;
                    } else {
                        oldYMin = destination_0012F930(unit, side) >> 8;
                    }
                    if ((destination_0012F930(unit, side) >> 8) < oldY) {
                        oldYMax = (u8)oldY;
                    } else {
                        oldYMax = destination_0012F930(unit, side) >> 8;
                    }
                    oldX = best->x;
                    if (oldX < (destination_0012F930(unit, side) & 0xFF)) {
                        oldXMin = (u8)oldX;
                    } else {
                        oldXMin = destination_0012F930(unit, side) & 0xFF;
                    }
                    if ((destination_0012F930(unit, side) & 0xFF) < oldX) {
                        oldXMax = (u8)oldX;
                    } else {
                        oldXMax = destination_0012F930(unit, side) & 0xFF;
                    }

                    currentY = point->y;
                    if (currentY < (destination_0012F930(unit, side) >> 8)) {
                        currentYMin = (u8)currentY;
                    } else {
                        currentYMin = destination_0012F930(unit, side) >> 8;
                    }
                    if ((destination_0012F930(unit, side) >> 8) < currentY) {
                        currentYMax = (u8)currentY;
                    } else {
                        currentYMax = destination_0012F930(unit, side) >> 8;
                    }
                    currentX = point->x;
                    if (currentX < (destination_0012F930(unit, side) & 0xFF)) {
                        currentXMin = (u8)currentX;
                    } else {
                        currentXMin = destination_0012F930(unit, side) & 0xFF;
                    }
                    if ((destination_0012F930(unit, side) & 0xFF) < currentX) {
                        currentXMax = (u8)currentX;
                    } else {
                        currentXMax = destination_0012F930(unit, side) & 0xFF;
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
                                   order->destination, arg4, 0);
        order->value = func_00130940((s32)unit->position >> 8, unit->position & 0xFF, unit, arg5);
        func_0027B1B0(unit, arg3);
        return 0;
    }
        if (bestIndex != 0xFF) {
            order->position = unit->position;
            order->kind = 6;
            order->destination = (points[bestIndex].y << 8) | points[bestIndex].x;
            order->flags = func_0027E360((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, arg4, 0);
            order->value = func_00130940((s32)unit->position >> 8, unit->position & 0xFF, unit, arg5);
        } else {
            order->position = unit->position;
            order->kind = 6;
            order->destination = position;
            order->flags = func_0027E360((s32)unit->position >> 8, unit->position & 0xFF,
                                       order->destination, arg4, 0);
            order->value = func_00130940((s32)unit->position >> 8, unit->position & 0xFF, unit, arg5);
        }
        func_0027B1B0(unit, arg3);
    }
    return 0;
}

typedef struct {
    u16 position;
    u8 pad2[6];
    union {
        u32 both;
        u16 half[2];
    } target;
} Source_00130120;

typedef struct {
    u16 position;
    u8 action;
    u8 pad3;
    u16 target;
    u8 pad6[10];
    s8 result;
} Action_00130120;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Point_00130120;

#define MIN_00130120(a, b) ((a) < (b) ? (a) : (b))
#define MAX_00130120(a, b) ((b) < (a) ? (a) : (b))

s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 target_00130120(void *arg0, s32 mode) {
    Source_00130120 *source = arg0;
    if (mode == 1) {
        return (u16)(source->target.both >> 16);
    }
    return source->target.half[0];
}

static inline void fill_00130120(void *arg0, void *arg2, s32 target, s32 flag) {
    Source_00130120 *source = arg0;
    Action_00130120 *action = arg2;
    action->position = source->position;
    action->action = 6;
    action->target = target;
    action->result = func_0027E360(source->position >> 8,
        source->position & 0xFF, action->target, flag, 0);
}

s32 func_00130120(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 start;
    s32 count;
    s32 startY;
    Point_00130120 points[16];
    s32 bestScore;
    Point_00130120 *p;
    s32 targetY;
    s32 targetX;
    s32 i;
    s32 bestIndex;
    s32 mode;
    s32 target;
    s32 startX;
    u32 xPosition;
    u32 yPosition;
    Source_00130120 *source = arg0;
    Action_00130120 *action = arg2;
    extern void func_0027A090();

    mode = arg3 & 0xFF;
    xPosition = target_00130120(arg0, mode);
    yPosition = target_00130120(arg0, mode);
    if (func_001DF540(yPosition >> 8, xPosition & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    start = func_001E1090(source->position >> 8, source->position & 0xFF);
    xPosition = target_00130120(arg0, mode);
    yPosition = target_00130120(arg0, mode);
    target = func_001E1090(yPosition >> 8, xPosition & 0xFF);
    if (target_00130120(arg0, mode) == 0xFFFF) {
        fill_00130120(arg0, arg2, start, 1);
        return 0;
    } else {
        s32 unit = func_001DF540(source->position >> 8, source->position & 0xFF);
        startX = start & 0xFF;
        startY = start >> 8;
        if (func_002464F0(unit, startX, startY) == 0 ||
                func_0027BBC0(source->position >> 8, source->position & 0xFF, 0) == 1) {
            fill_00130120(arg0, arg2, start, 1);
            return 0;
        } else {
            p = points;
            {
                s32 n = 0;
                Point_00130120 *q = p;
                do {
                    q->x = q->y = 0xF;
                    q++;
                    n++;
                } while (n < 12);
            }
            {
                s32 position = source->position;
                u16 card = (u16)func_00130780(arg1);
                func_0027A090(position >> 8, position & 0xFF, points,
                    startX, startY, targetX = target & 0xFF,
                    targetY = target >> 8, target_00130120(arg0, mode),
                    0, 30, card);
            }
            count = func_0027AFC0((u8 *)points);
            bestIndex = 0xFF;
            if (count > 0) {
                bestScore = 0;
                for (i = 0; i < count; i++, p++) {
                    if (func_001E36E0(p->x, p->y) == 0) {
                        s32 score = func_00276CC0(p->x, p->y, arg1, 3, 1,
                            func_00130780(arg1) & 0xFF);
                        if (bestScore < score) {
                            bestScore = score;
                            bestIndex = i;
                        } else if (score == bestScore) {
                            if (MAX_00130120(p->x, targetX) - MIN_00130120(p->x, targetX)
                                    + (MAX_00130120(p->y, targetY) - MIN_00130120(p->y, targetY))
                                    < MAX_00130120(points[bestIndex].x, targetX) - MIN_00130120(points[bestIndex].x, targetX)
                                    + (MAX_00130120(points[bestIndex].y, targetY) - MIN_00130120(points[bestIndex].y, targetY))) {
                                bestScore = score;
                                bestIndex = i;
                            }
                        }
                    }
                }
            } else {
                fill_00130120(arg0, arg2, start, 1);
                return 0;
            }
            if (bestIndex != 0xFF) {
                action->position = source->position;
                action->action = 6;
                action->target = (points[bestIndex].y << 8) | points[bestIndex].x;
                action->result = func_0027E360(source->position >> 8,
                    source->position & 0xFF, action->target, 0, 0);
            } else {
                fill_00130120(arg0, arg2, start, 1);
                return 0;
            }
        }
    }
    return 0;
}

s32 func_00130660(s32 arg0) {
    extern s32 func_001DEE50();
    s32 i;
    s32 entry;
    u8 *state;
    u32 *info;

    if (func_001E01F0(arg0) >= 5) {
        return -1;
    }
    for (i = 0; i < func_001DEE50(arg0); i++) {
        entry = func_001DEE00(arg0, i);
        if ((func_0026FCE0(entry) >> 5) != 0) {
            state = func_001DD0E0(entry);
            info = func_0026FC90(entry, 0);
            if ((info != NULL) && (state == NULL) && (state[3] >= 0xF) &&
                (func_001E01F0(arg0) < 5) && ((*info >> 8) != 0x14)) {
                return (arg0 << 0x10) | i;
            }
        }
    }
    return -1;
}

s32 func_00130780(s32 arg0) {
    if (func_001DF470(arg0) > 0x7D0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x960;
    }
}

s32 func_001307E0(s32 arg0, s32 arg1) {
    extern s32 func_001E1030();
    s32 data[4];
    s32 i;
    s32 mask;
    s32 coords;
    s32 card;
    s32 y;
    s32 x;
    s32 cell;

    func_00254C90(data, *(s32 *) ((u8 *) func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(data, arg0)) < 0) {
        return 0;
    }
    for (i = 0; i < func_0024E910(mask); i++) {
        cell = func_0024EC50(mask, i);
        x = cell >> 8;
        y = cell & 0xFF;
        coords = func_001E1090(x, y);
        card = func_001E1030(x, y);
        if (func_002509E0(x, y, coords & 0xFF, coords >> 8) >= 3000 || card == 0x12A ||
            (card == 0x131 && func_001E2100(x, y, 4) == 0) || card == 0x146) {
            return 0;
        }
    }
    return 1;
}

s32 func_00130940(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    extern s32 func_001E1030();
    s32 card;
    s32 position;
    u8 count;

    card = func_001E1030(arg0, arg1);
    func_00250360(arg0, arg1);
    position = func_001E1090(arg0, arg1);
    count = 0;
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 0:
        switch (card) {
        case 0x12A:
            return 1;
        case 0x142:
            if ((arg3 & 0xFF) == 1) {
                return 1;
            }
            break;
        case 0x146:
            for (card = 0; card < 11; card++) {
                if (func_001DF540(0, card) != 0 && arg0 != func_00250360(0, card)) {
                    count++;
                }
                if (func_001DF540(1, card) != 0 && arg0 != func_00250360(1, card)) {
                    count++;
                }
            }
            if (count >= 4) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_001307E0(func_00250360(arg0, arg1), card) == 1 &&
            func_001E22B0(position & 0xFF, position >> 8) != 9) {
            return 1;
        }
        break;
    case 1:
        return (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) ? 2 : 1;
    case 2:
    case 3:
    case 4:
        break;
    }
    return 2;
}

static inline s32 max_00130BB0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00130BB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00130BB0(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00130BB0(arg4, arg2);
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

s32 func_00130CB0(void) {
    /* both really take (player, slot); the headers say (void) */
    s32 func_001E1580();
    s32 func_001E1640();
    s32 player;
    u8 count3;
    s32 i;
    u8 count1;
    u8 count2;
    s32 j;

    player = func_001DE540();
    count1 = 0;
    count3 = 0;
    for (i = 0; i < 11; i++) {
        if (func_001E1580(player, i) > 0 || func_001E1640(player, i) > 0 ||
            func_00250360(player, i) != player) {
            count1++;
        }
        if (func_001E1580(player == 0 ? 1 : 0, i) > 0 || func_001E1640(player == 0 ? 1 : 0, i) > 0 ||
            func_00250360(player == 0 ? 1 : 0, i) != player) {
            count1++;
        }
    }
    if (count1 >= 4) {
        return 0;
    }
    count2 = 0;
    for (j = 0; j < 11; j++) {
        if (func_00250360(player, j) != player) {
            count2++;
        }
        if (func_00250360(player == 0 ? 1 : 0, j) != player) {
            count2++;
        }
    }
    for (j = 0; j < 11; j++) {
        if (func_00250360(player, j) == player) {
            count3++;
        }
        if (func_00250360(player == 0 ? 1 : 0, j) == player) {
            count3++;
        }
    }
    if (count2 < 2 && count3 >= 4) {
        return 1;
    }
    return 0;
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
} Req_00130E90;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00130E90;

s32 func_00276290(void *, void *, s32);

s32 func_00130E90(s32 arg0, void *arg1) {
    Req_00130E90 req;
    Work_00130E90 *w;
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
        if (func_0012BB70(w, &req, arg0) == 0) {
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

#pragma conditional_move off

s32 func_00131060(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = func_001DE540();
    found = 0;
    if ((result = func_00131750(arg0, side, (s32)arg1)) < 0) {
        return 0;
    }
    index = func_00276C80(arg0, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((arg0[index * 8 + 2] >> 8) & 0xFF) == 10) {
            func_0027B1B0(arg0 + index * 8, 1);
        } else {
            func_0027B1B0(arg0 + index * 8, 0);
        }
        return 1;
    }
    func_00131540(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001336A0(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_00133BE0(arg0 + index * 8, side, arg1, 1) < 0) {
                func_0027B1B0(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (func_00132460(arg0[index * 8], side, (s32)arg1) < 0) {
            func_0027B1B0(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            func_0027B1B0(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001341C0(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001341C0(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 1, 0, func_00134AE0(side), 4, 1);
        found = 1;
        break;
    case 14:
        func_00276EC0(arg0 + index * 8, side, arg1);
        found = 1;
        break;
    default:
        found = 0;
        break;
    }
    if (found == 1) {
        return 1;
    }
    found = 0;
    switch (arg0[index * 8 + 2] & 0xFF) {
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001336A0(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_00133BE0(arg0 + index * 8, side, arg1, 0) < 0) {
                func_001336A0(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (func_00132460(arg0[index * 8], side, (s32)arg1) < 0) {
            func_0027B1B0(arg0 + index * 8, 0);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            func_0027B1B0(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001341C0(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001341C0(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 0, 0, func_00134AE0(side), 4, 1);
        found = 1;
        break;
    case 14:
        func_00276EC0(arg0 + index * 8, side, arg1);
        break;
    default:
        return 0;
    }
    if (found == 1) {
        return 1;
    }
    return 0;
}
#pragma conditional_move reset

void func_0027CA50(void *arg0, s32 arg1, s32 arg2, s32 arg3);

typedef struct {
    u16 card;
    u8 pad2[2];
    u16 result;
    u8 pad6[2];
    s32 flags;
} Data_00131540;

s32 func_00131540(void *arg0) {
    Data_00131540 *data = (Data_00131540 *)arg0;
    s32 temp = func_00250360((s32)data->card >> 8, data->card & 0xFF);
    u16 value = data->card;

    if (func_001DF540((s32)value >> 8, value & 0xFF) != 0) {
        value = data->card;
        if (func_001E2100((s32)value >> 8, value & 0xFF, 0) == 0) {
            value = data->card;
            if (value != 0xFFFF) {
                if ((value & 0xFF) == 0) {
                    if (data->flags == -1) {
                        if (func_0027BBC0((s32)value >> 8, value & 0xFF, 0) == 1) {
                            if (func_001DE6D0((s32)data->card >> 8) == 1) {
                                data->result = 0x50A;
                            } else {
                                data->result = 0x5FF;
                            }
                        } else if (func_001DE6D0((s32)data->card >> 8) == 1) {
                            data->result = 0xA06;
                            data->flags = (data->flags & 0xFFFF0000) |
                                (func_001E1090(temp == 0 ? 1 : 0, 0) & 0xFF);
                        } else {
                            data->result = 0x6FF;
                            data->flags = *(u16 *)&data->flags |
                                ((func_001E1090(temp == 0 ? 1 : 0, 0) & 0xFF) << 16);
                        }
                    }
                } else {
                    s32 type = func_001E0700((s32)value >> 8, value & 0xFF) >> 5;

                    switch (type) {
                    case 0:
                        func_00131B30(arg0, 1);
                        break;
                    case 2:
                        func_0027CA50(arg0, 4, 0, func_00134AE0(temp) & 0xFF);
                        break;
                    case 1:
                    case 3:
                        func_00132280(arg0);
                        break;
                    default:
                        data->result = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }

    return 0;
}

s32 func_00131750(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_00131540(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00132460(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00132460(pos, arg1, arg2) >= 0) {
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
} Entry_00131B30;

typedef struct {
    u16 card;
    u8 flag;
    u8 pad;
} Slot_00131B30;

void func_00131B30(void *arg0, s32 arg1) {
    extern void func_0027E770();
    extern s32 func_0027B200();
    extern s32 func_00131DE0();
    extern s32 func_001E1030();
    Entry_00131B30 *entry = arg0;
    s32 side;
    s32 player;
    s32 other;
    s32 pos;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00131B30 list[22];
    s16 countA;
    s16 countB;

    if (func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        side = func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = func_001E1090(other >> 8, other & 0xFF);
        player = func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF);
        func_0027E770(work);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        if (func_001E1030(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0x198 &&
            func_001DF470(side) <= 1000) {
            entry->state = 0x3FF;
            entry->data.word = (pos << 16) | entry->data.halves.low;
        }
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
            switch (func_00131DE0(entry, 0, player, pos & 0xFF, pos >> 8,
                                  func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  i & 0xFF, func_00134AE0(side), list, 0, &countA, &countB, 4, work)) {
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
        func_00131E40(entry);
    }
}

void func_00131DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 0x708, arg_sp28);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00131E40;

typedef struct {
    u16 position;
    u16 pad2;
    u16 state;
    u16 pad6;
    union {
        u32 value;
        u16 low;
    } data;
} State_00131E40;


void func_00131E40(void *arg0) {
    s32 occupied;
    s32 destination;
    State_00131E40 *state = arg0;
    Nibbles_00131E40 entries[12];
    s32 i;
    Nibbles_00131E40 *entry;
    u32 *kind;
    s32 result;
    u16 position;

    position = state->position;
    occupied = func_00250360(position >> 8, position & 0xFF);
    position = state->position;
    destination = func_001E1090(position >> 8, position & 0xFF);
    position = state->position;
    kind = func_001E0B70(position >> 8, position & 0xFF, 1);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    if (kind != NULL && (*kind >> 8) == 8) {
        state->state = 0x2FF;
        state->data.value = state->data.low | ((occupied != 0 ? 0 : 1) << 24);
    } else {
        state->state = 0x6FF;
        position = state->position;
        result = func_00131F80(func_001DF540(position >> 8, position & 0xFF),
                              destination & 0xFF, destination >> 8);
        if (result >= 0) {
            state->data.value = (result << 16) | state->data.low;
        } else {
            state->state = 0x5FF;
        }
    }
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00131F80;

s32 func_00131F80(s32 arg0, s32 arg1, s32 arg2) {
    Nibbles_00131F80 buffer[12];
    s32 result;
    s32 owner;
    s32 i;
    Nibbles_00131F80 *p;
    extern s32 func_0027A130();
    extern s32 func_00250A60();

    result = -1;
    owner = func_00250370((void *)arg0);
    p = buffer;
    i = 0;
    do {
        i++;
        p->low = p->high = 15;
        p++;
    } while (i < 12);

    if (arg0 == 0) {
        return -1;
    }
    if (arg1 >= 3 && (arg2 == 0 || arg2 == 1 || (u32)(arg2 - 4) < 2)) {
        result = ((arg2 % 2 == 0 ? arg2 + 2 : arg2 + 1) << 8) | 6;
    } else if (arg1 < 3 && (u32)(arg2 - 2) < 2) {
        result = 0x400;
    }
    if (result >= 0) {
        if (func_0027A130(arg0, buffer, arg1, arg2, result & 0xFF,
                         result >> 8, -1, 0, 7, (u16)func_00134AE0(owner)) >= 0) {
            return result;
        }
    }

    if (arg1 < 3 && (arg2 == 0 || arg2 == 1 || (u32)(arg2 - 4) < 2) &&
        func_00250A60(arg0, 0, arg2 % 2 ? arg2 + 1 : arg2) < 1500) {
        result = (arg2 % 2 == 0 ? arg2 + 2 : arg2 + 1) << 8;
    } else if (arg1 >= 3 && arg2 == 2 && func_00250A60(arg0, 6, 3) < 1500) {
        result = 0x406;
    }
    if (result >= 0) {
        if (func_0027A130(arg0, buffer, arg1, arg2, result & 0xFF,
                         result >> 8, -1, 0, 7, (u16)func_00134AE0(owner)) >= 0) {
            return result;
        }
    }

    result = func_001E1090(func_00250370((void *)arg0) == 0 ? 1 : 0, 0);
    if (result >= 0) {
        if (func_0027A130(arg0, buffer, arg1, arg2, result & 0xFF,
                         result >> 8, -1, 0, 7, (u16)func_00134AE0(owner)) >= 0) {
            return result;
        }
    }
    return ((result >> 8) << 8) | arg1;
}

void func_00132280(u16 *arg0) {
    u16 value;
    s32 temp_s0;
    s32 temp_s3;
    s32 temp_s1;
    void *temp_v0;
    s32 result;

    value = arg0[0];
    temp_s0 = func_00250360(value >> 8, value & 0xFF);
    value = arg0[0];
    temp_s3 = (func_001E0700(value >> 8, value & 0xFF) >> 5) & 0xFF;
    value = arg0[0];
    temp_s1 = func_001E1090(value >> 8, value & 0xFF);
    value = arg0[0];
    temp_v0 = func_001E0B70(value >> 8, value & 0xFF, 0);

    switch (temp_s3 & 0xFF) {
    case 3:
        arg0[2] = 0x3FF;
        value = arg0[0];
        result = func_00131F80(func_001DF540(value >> 8, value & 0xFF), temp_s1 & 0xFF, temp_s1 >> 8);
        if (result >= 0) {
            *(u32 *)((u8 *)arg0 + 8) = (result << 16) | *(u16 *)((u8 *)arg0 + 8);
            return;
        }
        arg0[2] = 0x5FF;
        return;
    case 1:
        if (temp_v0 == NULL) {
            return;
        }
        switch (*(u32 *)temp_v0 >> 8) {
        case 2:
        case 0x48:
            arg0[2] = 0x6FF;
            result = func_001349A0(temp_s0);
            if (result >= 0) {
            *(u32 *)(arg0 + 4) = (result << 16) | arg0[4];
                return;
            }
            *(u32 *)(arg0 + 4) = arg0[4] | 0x60000;
            return;
        case 0x25:
            arg0[2] = 0x3FF;
            value = arg0[0];
            result = func_00131F80(func_001DF540(value >> 8, value & 0xFF), temp_s1 & 0xFF, temp_s1 >> 8);
            if (result >= 0) {
                *(u32 *)(arg0 + 4) = (result << 16) | arg0[4];
                return;
            }
            arg0[2] = 0x5FF;
            return;
        }
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
} Ctx_00132460;

typedef struct {
    u8 pad0[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00132460;

s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

s32 func_00132460(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_00278890(s32, s32);
    Work_00132460 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00132460 *ctx = (Ctx_00132460 *)arg2;

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_001326F0(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->unk2 = 10;
    ctx->unkC = 0;
    pos = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    if (kind == 0) {
        if (func_00132D00(arg1, (u8 *)ctx, &work) >= 0) {
            ret = func_00276F10(&work, pos & 0xFF, pos >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00134AE0(arg1));
            if (ret < 0) {
                if (func_001E0150(arg1) < 5) {
                    res = func_00133320(arg1, kind, &work, ret);
                    if (res < 0) {
                        return -1;
                    }
                    ctx->unk4 = res;
                    return 1;
                }
            } else {
                res = func_00133320(arg1, kind, &work, ret);
                if (res < 0) {
                    return -1;
                }
                ctx->unk4 = res;
                return 1;
            }
        }
    } else {
        ret = func_00276F10(&work, pos & 0xFF, pos >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00134AE0(arg1));
    }
    if (kind == 2) {
        func_00133130(arg1, ctx, &work);
        res = func_00133320(arg1, kind, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->unk4 = res;
        return 1;
    }
    if (func_00132B00(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_00133320(arg1, kind, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->unk4 = res;
    return 1;
}

s32 func_001326F0(s32 arg0, void *arg1) {
    s32 cards[8];
    u8 work[32];
    u8 first;
    u8 second;
    s32 i;
    s32 slot;
    s32 *q;
    s32 j;
    s32 ret;
    extern s32 func_00278890();
    extern s32 func_001E1030();

    first = func_00278890(arg0, 0);
    second = func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, cards);
    if (first == 5) {
        if (func_00132B00(arg0, work, arg1, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (second == 5) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if ((func_0026FCE0(cards[i]) >> 5) == 0 && func_0026FB10(arg0, cards[i]) == 1) {
                func_001DCD70(arg1, cards[i]);
                return 0;
            }
        }
        return -1;
    }
    if (func_00132A10(arg0, work, arg1, 0x340) >= 0) {
        if (func_00135000(arg0, 0x340) == 1) {
            return 2;
        }
    }
    slot = 1;
    while (1) {
        if (func_001DF540(arg0, slot) != 0 &&
            func_001E1030(arg0, slot) == 0x91 &&
            arg0 == func_00250360(arg0, slot) &&
            func_00132A10(arg0, work, arg1, 0x2EA) >= 0) {
            return 2;
        }
        if (func_001DF540(arg0 == 0 ? 1 : 0, slot) != 0 &&
            func_001E1030(arg0 == 0 ? 1 : 0, slot) == 0x91 &&
            arg0 == func_00250360(arg0 == 0 ? 1 : 0, slot) &&
            func_00132A10(arg0 == 0 ? 1 : 0, work, arg1, 0x2EA) >= 0) {
            return 2;
        }
        slot++;
        if (slot > 5) {
            break;
        }
    }
    j = 0;
    if (j < func_0026FE20(arg0)) {
        q = cards;
        do {
            if ((func_0026FCE0(*q) >> 5) == 0 && func_0026FB10(arg0, *q) == 1) {
                func_001DCD70(arg1, cards[j]);
                return 0;
            }
            q++;
            j++;
        } while (j < func_0026FE20(arg0));
    }
    ret = func_00132B00(arg0, work, arg1, 999);
    if (ret >= 0) {
        return ret;
    }
    return -1;
}

s32 func_00132A10(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 values[8];
    s32 index;
    s32 *value;

    func_0026FD30(arg0, values);
    index = 0;
    if (index < func_0026FE20(arg0)) {
        value = values;
        do {
            if (((arg3 & 0xFFFF) == *value) && (func_0026FB10(arg0, *value) == 1)) {
                *((s8 *)arg1 + 6) = index;
                func_001DCD70(arg2, values[index]);
                return func_0026FCE0(values[index]) >> 5;
            }
            value++;
            index++;
        } while (index < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_00132B00(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

typedef struct Info_00132D00 {
    u8 pad00[8];
    u16 x;
    s16 y;
} Info_00132D00;

typedef struct Sprite_00132D00 {
    Info_00132D00 *info;
    u8 pad04[0x34];
    s16 x;
    s16 y;
} Sprite_00132D00;

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);

s32 func_00132D00(s32 arg0, u8 *arg1, void *arg2) {
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
                            func_00132EE0(arg0, *node, entries);
                            func_00278DD0((u8 *)*node + 2, arg1 + 6);
                            func_001DCD70(arg2, **node);
                            ((Sprite_00132D00 *)arg2)->x = (value >> 16) - (((Sprite_00132D00 *)arg2)->info->x & 0x1FFF);
                            ((Sprite_00132D00 *)arg2)->y = (value & 0xFFFF) - (((Sprite_00132D00 *)arg2)->info->y & 0x1FFF);
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
} Info_00132EE0;

void func_00132EE0(s32 arg0, void *arg1, s32 *arg2) {
    Info_00132EE0 *info = arg1;
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
                if (card != 0x3E7 && func_001330C0(card) == 0 && level >= func_0026FA80(card, arg0)) {
                    cost = func_0026FBB0(card);
                    if ((cost & 0xFFFF) + (cost >> 16) * 2 < 0x10CD && func_0026FC10(card) == 2 &&
                        (u16)func_002789F0(info->id, (u16)card) == 0x3E7) {
                        func_00278D20(info->values, buf[i]);
                    }
                }
            }
        }
    }
}

s32 func_001330C0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if ((arg0 == 0x23D) || (arg0 == 0x216) || (arg0 == 0x63)) {
        return 1;
    }
    return 0;
}

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00133130;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00133130;

s32 func_00133130(s32 arg0, void *arg1, void *arg2) {
    Obj1_00133130 *o1 = arg1;
    Obj2_00133130 *o2 = arg2;
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

typedef struct Nibbles_00133320 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00133320;

typedef struct Object_00133320 {
    u8 pad[0x3E];
    u8 flags;
} Object_00133320;

s32 func_00133320(s32 arg0, u8 arg1, void *arg2, s32 arg3) {
    s32 bestCell;
    s32 bestCost;
    Nibbles_00133320 path[12];
    s32 i;
    Nibbles_00133320 *p;

    extern s32 func_00278510();
    extern s32 func_0027A130();
    extern s32 func_002792C0(s32, s32, s32, s32, s32, s32, u16, u8);

    if (arg2 == NULL) {
        return -1;
    }
    p = path;
    i = 0;
    do {
        p->low = p->high = 15;
        p++;
        i++;
    } while (i < 12);

    if ((u8)(((Object_00133320 *)arg2)->flags >> 5) == 0 && arg3 >= 0) {
        s32 cell;
        s32 y;
        s32 x;
        s32 index;
        s32 targetY;
        s32 targetX;
        s32 target;
        s32 cost;

        bestCost = 255;
        bestCell = 0xFFFF;
        target = func_001E1090(arg3 >> 8, arg3 & 0xFF);
        index = 0;
        targetY = target >> 8;
        targetX = target & 0xFF;
        do {
            cell = func_0024E410(arg0, index);
            if (cell >= 0) {
                x = cell & 0xFF;
                y = cell >> 8;
                if (func_001E22B0(x, y) != 8 &&
                    (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                    func_001E36E0(x, y) == 0) {
                    if (func_00278510((s32)arg2, arg3, func_00134AE0(arg0), targetX, targetY, 0) > 0) {
                        cost = func_0027A130((s32)arg2, (s32)path, x, y, targetX, targetY, arg3, 0, 4,
                                            func_00134AE0(arg0) & 0xFFFF);
                    } else {
                        cost = func_002792C0((s32)arg2, (s32)path, x, y, targetX, targetY, arg3, 4);
                    }
                    if (func_0027AFC0((u8 *)path) > 0 && cost < bestCost) {
                        bestCost = cost;
                        bestCell = cell;
                    }
                }
            }
            index++;
        } while (index < 8);
        if (bestCell != 0xFFFF) {
            return bestCell;
        } else {
            bestCell = -1;
            return bestCell;
        }
    } else {
        s32 maxY;
        s32 maxX;
        s32 y;
        s32 x;
        s32 index;
        s32 bestDistance;
        s32 cell;
        s32 target;
        s32 targetY;
        s32 distance;
        s32 minY;
        s32 minX;

        bestDistance = 14;
        arg3 = -1;
        index = 0;
        do {
            cell = func_0024E410(arg0, index);
            if (cell >= 0) {
                x = cell & 0xFF;
                y = cell >> 8;
                if (func_001E22B0(x, y) != 8 &&
                    (func_001E22B0(x, y) != 9 || func_0024FE40(arg2, x, y) != 1) &&
                    func_001E3790(x, y) < 0) {
                    target = func_00131F80((s32)arg2, x, y);
                    targetY = target >> 8;
                    minY = y < targetY ? y : targetY;
                    if (targetY < y) {
                        maxY = y;
                    } else {
                        maxY = targetY;
                    }
                    minX = x < (target & 0xFF) ? x : (target & 0xFF);
                    if ((target & 0xFF) < x) {
                        maxX = x;
                    } else {
                        maxX = target & 0xFF;
                    }
                    distance = (maxX - minX) + (maxY - minY);
                    if (distance < bestDistance && distance >= 0) {
                        arg3 = cell;
                        bestDistance = distance;
                    }
                }
            }
            index++;
        } while (index < 8);
        arg3 = bestDistance < 14 ? arg3 : -1;
    }
    return arg3;
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Flags_001336A0;

typedef struct {
    u16 id;
    u8 action;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 value;
    u8 mode;
} Output_001336A0;

s32 func_0027BE10(s32, s32, s32, s32, s32);
s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

s32 func_001336A0(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern s32 func_00279C40(s32, s32, s32, s32, s32, s32, void *, u8);
    extern s32 func_00134B40();
    s32 position;
    u8 upperX;
    u8 flag;
    Flags_001336A0 cells[12];
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
    Output_001336A0 *out = arg2;

    position = func_001E1090(*arg0 >> 8, *arg0 & 0xFF);
    i = 0;
    do {
        cells[i].low = cells[i].high = 15;
        i++;
    } while (i < 12);

    {
        u16 value = (u16)func_00134AE0(arg1);
        originalX = position & 0xFF;
        originalY = position >> 8;
        if (func_00276CC0(originalX, originalY, *arg0, 3, value, 0) == 0) {
            out->id = *arg0;
            out->action = 6;
            out->position = position;
            out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
            out->value = func_00134B40(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        } else {
            result = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), originalX, originalY);
            if (result == 0) {
                out->id = *arg0;
                out->action = 6;
                out->position = position;
                out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                out->value = func_00134B40(*arg0 >> 8, *arg0 & 0xFF, arg0);
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
                    flag = func_0027BBC0(*arg0 >> 8, *arg0 & 0xFF, 0) & 0xFF;
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
                                (func_0027BE10(*arg0 >> 8, *arg0 & 0xFF, x, y, 0) == 0 || (u8)*arg0 == 0)) {
                                value = (u16)func_00134AE0(arg1);
                                score = func_00276CC0(x, y, *arg0, 3, value, 0);
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
                        out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    } else {
                        out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 0, 0);
                    }
                    out->value = func_00134B40(*arg0 >> 8, *arg0 & 0xFF, arg0);
                } else {
                    out->id = *arg0;
                    out->action = 6;
                    out->position = position;
                    out->mode = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, out->position, 1, 0);
                    out->value = func_00134B40(*arg0 >> 8, *arg0 & 0xFF, arg0);
                }
                func_0027B1B0(arg0, arg3);
            }
        }
    }
    return 0;
}

s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

typedef struct Input_00133BE0 {
    u16 position;
    u8 pad2[6];
    u32 destinations;
} Input_00133BE0;

typedef struct Output_00133BE0 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 flag;
    u8 result;
} Output_00133BE0;

typedef struct Position_00133BE0 {
    u8 x : 4;
    u8 y : 4;
} Position_00133BE0;

static inline u32 destination_00133BE0(void *input, s32 mode) {
    if (mode == 1) {
        return (u16)(((Input_00133BE0 *)input)->destinations >> 16);
    }
    return (u16)((Input_00133BE0 *)input)->destinations;
}

static inline s32 minimum_00133BE0(s32 a, s32 b) {
    return a > b ? b : a;
}

static inline s32 maximum_00133BE0(s32 a, s32 b) {
    return b < a ? a : b;
}

s32 func_00133BE0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void func_0027A090();
    Position_00133BE0 positions[12];
    s32 start;
    s32 card;
    s32 count;
    s32 startY;
    s32 startX;
    s32 flag;
    s32 target;
    s32 targetX;
    Position_00133BE0 *current;
    s32 initialFlag;
    s32 sourcePosition;
    s32 mode = arg3;
    s32 candidate;
    s32 i;
    s32 bestScore;
    s32 bestIndex;
    u32 positionX;
    u32 positionY;
    Input_00133BE0 *input = arg0;
    Output_00133BE0 *output = arg2;

    positionX = destination_00133BE0(arg0, mode);
    positionY = destination_00133BE0(arg0, mode);
    if (func_001DF540(positionY >> 8, positionX & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    initialFlag = func_00134B40(input->position >> 8, input->position & 0xFF, arg0);
    start = func_001E1090(input->position >> 8, input->position & 0xFF);
    positionX = destination_00133BE0(arg0, mode);
    positionY = destination_00133BE0(arg0, mode);
    target = func_001E1090(positionY >> 8, positionX & 0xFF);
    for (i = 0; i < 12; i++) {
        positions[i].x = positions[i].y = 15;
    }
    card = func_001DF540(input->position >> 8, input->position & 0xFF);
    startX = start & 0xFF;
    startY = start >> 8;
    if (func_002464F0(card, startX, startY) == 0) {
        s32 score;
        output->position = input->position;
        output->action = 6;
        output->destination = start;
        score = func_00276CC0(startX, startY, arg1, 3, 1, (u8)func_00134AE0(arg1));
        if (score >= func_001E0290(input->position >> 8, input->position & 0xFF, 0)) {
            output->result = func_0027E360(input->position >> 8, input->position & 0xFF, output->destination, 1, 0);
        } else {
            output->result = func_0027E360(input->position >> 8, input->position & 0xFF, output->destination, 0, 0);
        }
        func_0027B1B0(arg0, arg3);
    } else {
        s32 sourceX;
        s32 sourceY;
        u16 leader;
        sourcePosition = input->position;
        leader = (u16)func_00134AE0(arg1);
        sourceY = sourcePosition >> 8;
        sourceX = sourcePosition & 0xFF;
        targetX = target & 0xFF;
        func_0027A090(sourceY, sourceX, positions,
                     startX, startY, targetX, target >>= 8, destination_00133BE0(arg0, mode),
                     0, 30, leader);
        count = func_0027AFC0((u8 *)positions);
        bestIndex = 0xFF;
        if (count > 0) {
            flag = 0;
            bestScore = 0xFFFF;
            for (candidate = 0; candidate < count; candidate++) {
                if (func_00134F00(input->position >> 8, input->position & 0xFF,
                                 startX, startY, targetX, target) == 1) {
                    bestIndex = candidate;
                    flag = 1;
                    positions[candidate].x = targetX;
                    positions[candidate].y = target;
                    candidate = count;
                } else {
                    s32 score;
                    current = &positions[candidate];
                    score = func_00276CC0(current->x, current->y, arg1,
                                         4, 1, (u8)func_00134AE0(arg1));
                    if (score < bestScore) {
                        bestScore = score;
                        bestIndex = candidate;
                    } else if (score == bestScore) {
                        Position_00133BE0 *best = &positions[bestIndex];
                        s32 bestMinY = (best->y < target ? best->y : target);
                        s32 bestMaxY = maximum_00133BE0(best->y, target);
                        s32 bestMinX = (best->x < targetX ? best->x : targetX);
                        s32 bestMaxX = maximum_00133BE0(best->x, targetX);
                        s32 currentMinY = (current->y < target ? current->y : target);
                        s32 currentMaxY = maximum_00133BE0(current->y, target);
                        s32 currentMinX = (current->x < targetX ? current->x : targetX);
                        s32 currentMaxX = maximum_00133BE0(current->x, targetX);
                        if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) <
                            (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                            bestScore = score;
                            bestIndex = candidate;
                        }
                    }
                }
            }
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = start;
            output->flag = initialFlag;
            output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (bestIndex != 0xFF) {
            output->position = input->position;
            output->action = 6;
            output->destination = (positions[bestIndex].y << 8) | positions[bestIndex].x;
            output->flag = flag;
            output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 0);
        } else {
            output->position = input->position;
            output->action = 6;
            output->destination = start;
            output->flag = flag;
            output->result = func_0027E360(input->position >> 8, input->position & 0xFF,
                                          output->destination, 0, 0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
    }
    return 0;
}

typedef struct Position_001341C0 {
    u8 x : 4;
    u8 y : 4;
} Position_001341C0;

typedef struct Source_001341C0 {
    u16 id;
    u8 pad2[6];
    u32 target;
} Source_001341C0;

typedef struct Result_001341C0 {
    u16 id;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flags;
} Result_001341C0;

s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

#define target_001341C0(src, side) ((side) == 1 ? ((((Source_001341C0 *)(src))->target >> 16) & 0xFFFF) : (u32)(u16)((Source_001341C0 *)(src))->target)

#define min_001341C0(a, b) ((a) < (b) ? (a) : (b))
#define max_001341C0(a, b) ((b) < (a) ? (a) : (b))
#define distance_001341C0(pos, src, side) \
    ((max_001341C0((u8)(pos).x, (u32)(u8)target_001341C0(src, side)) - \
      min_001341C0((u8)(pos).x, (u32)(u8)target_001341C0(src, side))) + \
     (max_001341C0((u8)(pos).y, (u32)target_001341C0(src, side) >> 8) - \
      min_001341C0((u8)(pos).y, (u32)target_001341C0(src, side) >> 8)))

s32 func_001341C0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4) {
    extern void func_00279230();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Position_001341C0 positions[12];
    s32 start;
    s32 count;

    start = func_001E1090(((Source_001341C0 *)arg0)->id >> 8, ((Source_001341C0 *)arg0)->id & 0xFF);
    {
        s32 score;
        s32 best;
        s32 side = arg3;
        Position_001341C0 *p;
        s32 i;
        if (target_001341C0(arg0, side) == 0xFFFF && start == target_001341C0(arg0, side)) {
            ((Result_001341C0 *)arg2)->id = ((Source_001341C0 *)arg0)->id;
            ((Result_001341C0 *)arg2)->kind = 6;
            ((Result_001341C0 *)arg2)->target = start;
            ((Result_001341C0 *)arg2)->flags = func_0027E360(((Source_001341C0 *)arg0)->id >> 8, ((Source_001341C0 *)arg0)->id & 0xFF, ((Result_001341C0 *)arg2)->target, arg4, 0);
            ((Result_001341C0 *)arg2)->value = func_00134B40(((Source_001341C0 *)arg0)->id >> 8, ((Source_001341C0 *)arg0)->id & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        p = positions;
        {
            s32 clear_count = 0;
            Position_001341C0 *clear = p;
            s32 terrain;
            do {
                clear->x = clear->y = 15;
                clear_count++;
                clear++;
            } while (clear_count < 12);

            terrain = func_001E3790(target_001341C0(arg0, side) & 0xFF, (u32)target_001341C0(arg0, side) >> 8);
            if (terrain < 0) {
                terrain = 0xFFFF;
            }
            func_00279230(((Source_001341C0 *)arg0)->id >> 8, ((Source_001341C0 *)arg0)->id & 0xFF, positions,
                          start & 0xFF, start >> 8, target_001341C0(arg0, side) & 0xFF,
                          (u32)target_001341C0(arg0, side) >> 8, (u16)terrain, 7);
            count = func_0027AFC0((u8 *)positions);
        }
        if (count > 0) {
            best = 0xFF;
            score = 0xFFFF;
            for (i = 0; i < count; i++, p++) {
                if (func_001E36E0(p->x, p->y) == 0) {
                    s32 value = func_00276CC0(p->x, p->y, arg1, 4, 1, (u8)func_00134AE0(arg1));
                    if (value < score) {
                        score = value;
                        best = i;
                    } else if (value == score) {
                        if (distance_001341C0(*p, arg0, side) < distance_001341C0(positions[best], arg0, side)) {
                            score = value;
                            best = i;
                        }
                    }
                }
            }
        } else {
            ((Result_001341C0 *)arg2)->id = ((Source_001341C0 *)arg0)->id;
            ((Result_001341C0 *)arg2)->kind = 6;
            ((Result_001341C0 *)arg2)->target = start;
            ((Result_001341C0 *)arg2)->flags = func_0027E360(((Source_001341C0 *)arg0)->id >> 8, ((Source_001341C0 *)arg0)->id & 0xFF, ((Result_001341C0 *)arg2)->target, arg4, 0);
            ((Result_001341C0 *)arg2)->value = func_00134B40(((Source_001341C0 *)arg0)->id >> 8, ((Source_001341C0 *)arg0)->id & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (best != 0xFF) {
            ((Result_001341C0 *)arg2)->id = ((Source_001341C0 *)arg0)->id;
            ((Result_001341C0 *)arg2)->kind = 6;
            ((Result_001341C0 *)arg2)->target = (positions[best].y << 8) | positions[best].x;
            ((Result_001341C0 *)arg2)->flags = func_0027E360(((Source_001341C0 *)arg0)->id >> 8, ((Source_001341C0 *)arg0)->id & 0xFF, ((Result_001341C0 *)arg2)->target, arg4, 0);
            ((Result_001341C0 *)arg2)->value = func_00134B40(((Source_001341C0 *)arg0)->id >> 8, ((Source_001341C0 *)arg0)->id & 0xFF, arg0);
        } else {
            ((Result_001341C0 *)arg2)->id = ((Source_001341C0 *)arg0)->id;
            ((Result_001341C0 *)arg2)->kind = 6;
            ((Result_001341C0 *)arg2)->target = start;
            ((Result_001341C0 *)arg2)->flags = func_0027E360(((Source_001341C0 *)arg0)->id >> 8, ((Source_001341C0 *)arg0)->id & 0xFF, ((Result_001341C0 *)arg2)->target, arg4, 0);
            ((Result_001341C0 *)arg2)->value = func_00134B40(((Source_001341C0 *)arg0)->id >> 8, ((Source_001341C0 *)arg0)->id & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
    }
    return 0;
}

s32 func_001349A0(s32 arg0) {
    s32 row;
    s32 column;
    s32 position;

    for (row = 0; row < 7; row++) {
        if (row % 2 == 1) {
            column = 1;
            do {
                if (func_001E22B0(column, row) != 8) {
                    return (row << 8) | column;
                }
                column++;
            } while (column <= 5);
        }
    }

    for (row = 0; row < 7; row++) {
        column = 0;
        do {
            position = func_001E3790(row, column);
            if (position >= 0 &&
                arg0 != func_00250360(position >> 8, position & 0xFF) &&
                column < 3 &&
                func_001E22B0(6, 0) != 8 &&
                func_001E22B0(5, 0) != 8) {
                return 6;
            }
            column++;
        } while (column <= 6);
    }

    return -1;
}

s32 func_00134AE0(s32 arg0) {
    if (func_001DF470(arg0) > 0x3E8) {
        if (func_001E0150(arg0) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x6A4;
    }
}

s32 func_00134B40(s32 arg0, s32 arg1, void *arg2) {
    extern s32 func_001E1030();
    s32 i;
    s32 card;
    s32 position;
    u32 *effect;
    u8 count;

    card = func_001E1030();
    func_00250360(arg0, arg1);
    position = func_001E1090(arg0, arg1);
    effect = func_001E0B70(arg0, arg1, 0);
    count = 0;
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 0:
        switch (card) {
        case 0xBE:
            i = 1;
            while (1) {
                if ((func_001E0700(arg0, i) & 0x1F) == 9) {
                    if (arg0 == func_00250360(arg0, i)) {
                        count++;
                    }
                }
                if ((func_001E0700(arg0 == 0 ? 1 : 0, i) & 0x1F) == 9) {
                    if (arg0 == func_00250360(arg0 == 0 ? 1 : 0, i)) {
                        count++;
                    }
                }
                i++;
                if (i > 5) {
                    break;
                }
            }
            if (count >= 3) {
                return 1;
            }
            break;
        }
        return 2;
    case 5:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (func_00135000(func_00250360(arg0, arg1), card) == 1) {
            if (func_001E22B0(position & 0xFF, position >> 8) != 9) {
                return 1;
            }
        }
        break;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (effect == NULL) {
            return 2;
        }
        switch (*effect >> 8) {
        case 2:
        case 0x48: {
            i = func_001349A0(arg0);
            if (i >= 0 && i == func_001E1090(arg0, arg1)) {
                return 1;
            }
            break;
        }
        case 0xD:
            return 1;
        case 0x25: {
            i = 1;
            while (1) {
                if (func_001DF540(arg0, i) != 0) {
                    if (func_001E1030(arg0, i) != 0x91) {
                        if (arg0 == func_00250360(arg0, i)) {
                            count++;
                        }
                    }
                }
                if (func_001DF540(arg0 == 0 ? 1 : 0, i) != 0) {
                    if (func_001E1030(arg0 == 0 ? 1 : 0, i) != 0x91) {
                        if (arg0 == func_00250360(arg0 == 0 ? 1 : 0, i)) {
                            count++;
                        }
                    }
                }
                i++;
                if (i > 5) {
                    break;
                }
            }
            if (count > 0) {
                return 1;
            }
            break;
        }
        }
        break;
    default:
        return 2;
    }
    return 2;
}

static inline s32 min_00134F00(s32 a, s32 b) {
    if (a < b) {
        return a;
    }
    return b;
}

static inline s32 max_00134F00(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00134F00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = min_00134F00(arg3, arg5);
    arg5 = max_00134F00(arg5, arg3);
    min_x = min_00134F00(arg2, arg4);
    arg4 = max_00134F00(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        return func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1) != 1 ? 0 : 1;
    }
    return 0;
}

s32 func_00135000(s32 arg0, s32 arg1) {
    s32 sp20[4];

    func_00254C90(sp20, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if (func_00254890(sp20, arg0) < 0) {
        return 0;
    }
    return 1;
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
} Req_00135060;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00135060;

s32 func_00276290(void *, void *, s32);

s32 func_00135060(s32 arg0, void *arg1) {
    Req_00135060 req;
    Work_00135060 *w;
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
        if (func_00131060(w, &req, arg0) == 0) {
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

#pragma conditional_move off

s32 func_00135230(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = func_001DE540();
    found = 0;
    if ((result = func_00135970(arg0, side, (s32)arg1)) < 0) {
        return 0;
    }
    index = func_00276C80(arg0, result & 0xFFFF);
    if (index < 0) {
        return 0;
    }
    if ((result >> 16) == 1) {
        if (((arg0[index * 8 + 2] >> 8) & 0xFF) == 10) {
            func_0027B1B0(arg0 + index * 8, 1);
        } else {
            func_0027B1B0(arg0 + index * 8, 0);
        }
        return 1;
    }
    func_00135790(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001374D0(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_001379F0(arg0 + index * 8, side, arg1, 1) < 0) {
                func_0027B1B0(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (func_00136210(arg0[index * 8], side, (s32)arg1) < 0) {
            func_0027B1B0(arg0 + index * 8, 1);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            func_0027B1B0(arg0 + index * 8, 1);
            found = 1;
        }
        break;
    case 6:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00137FB0(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00137FB0(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 1, 1, 0, 2, 1);
        found = 1;
        break;
    case 12:
        func_00138780(arg0 + index * 8, side, arg1, 1);
        found = 1;
        break;
    case 13:
        func_00138950(arg0 + index * 8, side, arg1, 1);
        found = 1;
        break;
    case 14:
        func_00276EC0(arg0 + index * 8, side, arg1);
        found = 1;
        break;
    default:
        found = 0;
        break;
    }
    if (found == 1) {
        return 1;
    }
    found = 0;
    switch (arg0[index * 8 + 2] & 0xFF) {
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_001374D0(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_001379F0(arg0 + index * 8, side, arg1, 0) < 0) {
                func_001374D0(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (func_00136210(arg0[index * 8], side, (s32)arg1) < 0) {
            func_0027B1B0(arg0 + index * 8, 0);
            *(u8 *)((u8 *)arg1 + 2) = 0xFF;
            found = 1;
            *(s32 *)((u8 *)arg1 + 0xC) = 0;
        } else {
            func_0027B1B0(arg0 + index * 8, 0);
            found = 1;
        }
        break;
    case 6:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00137FB0(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00137FB0(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 0, 1, 0, 2, 1);
        found = 1;
        break;
    case 12:
        func_00138780(arg0 + index * 8, side, arg1, 0);
        found = 1;
        break;
    case 13:
        func_00138950(arg0 + index * 8, side, arg1, 0);
        found = 1;
        break;
    case 14:
        func_00276EC0(arg0 + index * 8, side, arg1);
        found = 1;
        break;
    default:
        return 0;
    }
    if (found == 1) {
        return 1;
    }
    return 0;
}
#pragma conditional_move reset
