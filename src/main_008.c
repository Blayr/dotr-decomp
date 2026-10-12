#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012CE50);

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

s32 func_0012E3F0(s32, s32, void *, s32);

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
s32 func_00278F10(s32, u16 *, s32, s32);

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

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012E3F0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012E820);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012ED70);

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

s32 func_00130940(s32, s32, void *, s32);
s32 func_002464F0(s32, s32, s32);
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

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012F930);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130120);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130660);

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

INCLUDE_ASM("asm/nonmatchings/main_008", func_001307E0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130940);

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

s32 func_0012BB70(void *, void *, s32);
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

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131060);

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

s32 func_00133320(s32 arg0, u8 arg1, void *arg2, s32 arg3);
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
s32 func_00278F10(s32, u16 *, s32, s32);

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

INCLUDE_ASM("asm/nonmatchings/main_008", func_00133320);

INCLUDE_ASM("asm/nonmatchings/main_008", func_001336A0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00133BE0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_001341C0);

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

INCLUDE_ASM("asm/nonmatchings/main_008", func_00134B40);

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

s32 func_00131060(void *, void *, s32);
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

INCLUDE_ASM("asm/nonmatchings/main_008", func_00135230);
