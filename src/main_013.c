#include "common.h"

s32 func_00153ED0(s32 arg0) {
    if (func_001DF470(arg0) > 1200) {
        if (func_001E0150(arg0) >= 4) {
            return 500;
        } else {
            return 1000;
        }
    } else {
        return 1500;
    }
}

typedef struct Entry_00153F30 {
    u8 *data;
    u8 rest[0x5C];
} Entry_00153F30;

s32 func_00153F30(s32 arg0) {
    extern s32 func_001DEE50(s32);
    s32 i;
    s32 bestScore;
    s32 result;
    s32 card;
    Entry_00153F30 entry;
    u32 *effect;
    u8 score;

    bestScore = 0x28;
    result = -1;
    if (func_001E01F0(arg0) >= 5) {
        return result;
    }

    for (i = 0; i < func_001DEE50(arg0 == 0 ? 1 : 0); i++) {
        card = func_001DEE00(arg0 == 0 ? 1 : 0, i);
        if ((func_0026FCE0(card) >> 5) != 0) {
            func_001DCD70(&entry, card);
            effect = (u32 *)func_001E09E0(&entry, 0);
            score = entry.data[3];
            if (score >= bestScore && (*effect >> 8) != 0x14) {
                bestScore = score;
                result = i | ((arg0 == 0 ? 1 : 0) << 16);
            }
        }
    }
    return result;
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
} Req_00154040;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00154040;

s32 func_0014FD40(void *, void *, s32);
s32 func_00276290(void *, void *, s32);

s32 func_00154040(s32 arg0, void *arg1) {
    Req_00154040 req;
    Work_00154040 *w;
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
        if (func_0014FD40(w, &req, arg0) == 0) {
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

void func_00154210(void) {
    func_00172370();
}

#pragma conditional_move off

s32 func_00154220(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = func_001DE540();
    found = 0;
    if ((result = func_00154AD0(arg0, side, (s32)arg1)) < 0) {
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
    func_001547A0(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_00156FC0(arg0 + index * 8, side, arg1, 1) < 0) {
                func_0027B1B0(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00157480(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 10:
        if (func_00155770(arg0[index * 8], side, (s32)arg1) < 0) {
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
            func_00157A50(arg0 + index * 8, side, arg1, 1, 0, 0);
            found = 1;
        }
        break;
    case 7:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00157A50(arg0 + index * 8, side, arg1, 1, 0, 1);
            found = 1;
        }
        break;
    case 3:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00157A50(arg0 + index * 8, side, arg1, 1, 1, 0);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 1, 0, func_00158780(side), 5, 1);
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
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_00156FC0(arg0 + index * 8, side, arg1, 0) < 0) {
                func_00157480(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00157480(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 10:
        if (func_00155770(arg0[index * 8], side, (s32)arg1) < 0) {
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
            func_00157A50(arg0 + index * 8, side, arg1, 0, 0, 0);
            found = 1;
        }
        break;
    case 7:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00157A50(arg0 + index * 8, side, arg1, 0, 0, 1);
            found = 1;
        }
        break;
    case 3:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_00157A50(arg0 + index * 8, side, arg1, 0, 1, 0);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 0, 0, func_00158780(side), 5, 1);
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

typedef struct State_001547A0 {
    u16 id;
    u16 pad2;
    u16 action;
    u16 pad6;
    union {
        s32 all;
        struct {
            u16 lo;
            u16 hi;
        } h;
    } data;
} State_001547A0;

void func_00154EB0(void *);

s32 func_001547A0(void *arg0) {
    extern s32 func_001E1030();
    State_001547A0 *state = arg0;
    s32 card;
    s32 other;

    func_001E1090((s32)state->id >> 8, state->id & 0xFF);
    card = func_00250360((s32)state->id >> 8, state->id & 0xFF);
    if (func_001DF540((s32)state->id >> 8, state->id & 0xFF) != 0) {
        if (func_001E2100((s32)state->id >> 8, state->id & 0xFF, 0) == 0) {
            if (state->id != 0xFFFF) {
                if ((state->id & 0xFF) == 0) {
                    if (state->data.all == -1) {
                        if (func_0027BBC0((s32)state->id >> 8, state->id & 0xFF, 0) == 1) {
                            if (func_001DE6D0((s32)state->id >> 8) == 1) {
                                state->action = 0x50A;
                            } else {
                                state->action = 0x5FF;
                            }
                        } else {
                            if ((other = func_001E3790(3, 5)) < 0) {
                                if (func_001DE6D0((s32)state->id >> 8) == 1) {
                                    state->action = 0xA06;
                                    state->data.all = (state->data.all & 0xFFFF0000) | 0x403;
                                } else {
                                    state->action = 0x6FF;
                                    state->data.all = (u16)state->data.all | 0x04030000;
                                }
                            } else {
                                if (func_001E1090((s32)state->id >> 8, state->id & 0xFF) == 0x403 &&
                                    card == func_00250360(other >> 8, other & 0xFF) && other != state->id) {
                                    if (func_001DE6D0((s32)state->id >> 8) == 1) {
                                        state->action = 0x20A;
                                        state->data.all = (other << 16) | state->data.h.lo;
                                    } else {
                                        state->action = 0x2FF;
                                        state->data.all = (other << 16) | state->data.h.lo;
                                    }
                                } else {
                                    if (func_001DE6D0((s32)state->id >> 8) == 1) {
                                        state->action = 0xA06;
                                        state->data.all = (state->data.all & 0xFFFF0000) | 0x403;
                                    } else {
                                        state->action = 0x6FF;
                                        state->data.all = (u16)state->data.all | 0x04030000;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    other = func_001E0700((s32)state->id >> 8, state->id & 0xFF);
                    card = func_001E1030((s32)state->id >> 8, state->id & 0xFF);
                    switch (other >> 5) {
                    case 0:
                        if (func_002507D0((s32)state->id >> 8, state->id & 0xFF) == 1 ||
                            func_001587E0(card) == 1) {
                            func_00155070(arg0);
                        } else {
                            func_00154EB0(arg0);
                        }
                        break;
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        func_00155230(arg0);
                        break;
                    default:
                        state->action = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

s32 func_00154AD0(u16 *arg0, s32 arg1, s32 arg2) {
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
    for (i = 0; i < 22; i++) {
        list[i] = 0xFFFF;
    }
    func_0027C070(arg1, list, 0x1F, 1);
    for (i = 0; i < func_0027C670(list); i++) {
        if (func_0027B9B0(list[i]) == 1 && func_0027C6D0(list[i]) == 1) {
            return list[i];
        }
    }
    pos = arg1 << 8;
    idx = func_00276C80(arg0, pos);
    func_001547A0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_00155770(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_00155770(pos, arg1, arg2) >= 0) {
        return pos | 0x10000;
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

INCLUDE_ASM("asm/nonmatchings/main_013", func_00154EB0);

typedef struct Action_00155070 {
    u16 location;
    u16 unk2;
    s16 state;
    u16 unk6;
    union {
        s32 value;
        u16 low;
    } data;
} Action_00155070;

void func_00154EB0(void *);

void func_00155070(void *arg0) {
    extern s32 func_001E1030();
    s32 owner;
    s32 i;
    s32 kind;
    s32 list;
    s32 pair;
    u8 count;
    Action_00155070 *action;

    action = arg0;
    owner = func_00250360(action->location >> 8, action->location & 0xFF);
    kind = func_001E1030(action->location >> 8, action->location & 0xFF);
    count = 0;
    switch (kind) {
    case 0x38:
    case 0x39:
    case 0x36:
    case 0x37:
        action->state = 0x6FF;
        action->data.value = action->data.low | (func_001E1090(action->location >> 8, action->location & 0xFF) << 16);
        return;
    case 0x40:
        list = func_0024CA40(0, 0, owner, 2, 3, 0xE);
        for (i = 0; i < func_0024E910(list); i++) {
            pair = func_0024EC50(list, i);
            if (func_002781B0(pair >> 8, pair & 0xFF, 0) == 1) {
                count++;
            }
        }
        if (count > 1) {
            func_00154EB0(action);
            action->state = 0x3FF;
            return;
        }
        break;
    case 0x5F:
        if (func_001DF470(owner) < 0x4B0) {
            func_00154EB0(action);
            action->state = 0x3FF;
            return;
        }
        break;
    }
    func_00154EB0(action);
}

typedef struct State_00155230 {
    u16 position;
    u16 pad2;
    u16 flags;
    u16 pad6;
    u16 destination;
    u16 destination_high;
} State_00155230;

void func_00155230(void *arg0) {
    s32 position;
    u8 kind;
    State_00155230 *state = arg0;
    s32 card;
    s32 destination;

    extern s32 func_001E1030();

    func_00250360(state->position >> 8, state->position & 0xFF);
    kind = (func_001E0700(state->position >> 8, state->position & 0xFF) >> 5) & 0xFF;
    position = func_001E1090(state->position >> 8, state->position & 0xFF);
    card = func_001E1030(state->position >> 8, state->position & 0xFF);
    switch (kind) {
    case 1:
    case 3:
    case 2: {
        s32 y;
        s32 x;

        state->flags = 0x7FF;
        if (func_00155670(state->position >> 8, state->position & 0xFF) == 1) {
            *(u32 *)&state->destination = (position << 16) | state->destination;
            break;
        }
        x = position & 0xFF;
        y = position >> 8;
        if (func_001554B0(x, y, kind) == 0 &&
            func_001554B0(x, y, 0) == 0 && y < 6) {
            *(u32 *)&state->destination = (((position & 0xFF) | 0x600) << 16) | state->destination;
            break;
        }
        destination = func_001555F0(kind);
        if (destination >= 0) {
            *(u32 *)&state->destination = (destination << 16) | state->destination;
            break;
        }
        destination = func_001555F0(0);
        if (destination >= 0) {
            *(u32 *)&state->destination = (destination << 16) | state->destination;
            break;
        }
        state->flags = 0x6FF;
        *(u32 *)&state->destination = state->destination | 0x05030000;
        break;
    }
    case 4:
        if (card != 0x334 && card != 0x337) {
            state->flags = 0x3FF;
            *(u32 *)&state->destination = (position << 16) | state->destination;
            break;
        }
        state->flags = 0x6FF;
        destination = func_001555F0(kind);
        if (destination >= 0) {
            *(u32 *)&state->destination = (destination << 16) | state->destination;
            break;
        }
        destination = func_001555F0(0);
        if (destination >= 0) {
            *(u32 *)&state->destination = (destination << 16) | state->destination;
            break;
        }
        state->flags = 0x6FF;
        *(u32 *)&state->destination = state->destination | 0x05030000;
        break;
    default:
        state->flags = 0x5FF;
        break;
    }
}

s32 func_001554B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = 0;

    do {
        if (func_00155520(i, arg2) == ((arg1 << 8) | arg0)) {
            return 1;
        }
        i++;
    } while (i < 7);
    return 0;
}

s32 func_00155520(s32 arg0, s32 arg1) {
    func_001DE540();
    switch (arg0) {
    case 0:
        return (arg1 == 0) ? 0x200 : 0x206;
    case 1:
        return (arg1 == 0) ? 0x300 : 0x306;
    case 2:
        return (arg1 == 0) ? 0x400 : 0x406;
    case 3:
        return (arg1 == 0) ? 0x500 : 0x506;
    case 4:
        return (arg1 == 0) ? 0x600 : 0x606;
    case 5:
        return (arg1 == 0) ? 0x601 : 0x605;
    case 6:
        return (arg1 == 0) ? 0x602 : 0x604;
    default:
        return -1;
    }
}

s32 func_001555F0(s32 arg0) {
    s32 i;
    s32 temp_v0;

    i = 0;
    do {
        temp_v0 = func_00155520(i, arg0);
        if (((func_001E36E0(temp_v0 & 0xFF, temp_v0 >> 8) == 0) ? 1 : 0) == 1) {
            return func_00155520(i, arg0);
        }
        i++;
    } while (i < 7);
    return -1;
}

s32 func_00155670(s32 arg0, s32 arg1) {
    s32 i;
    s32 side;
    s32 otherSide;
    s32 position;
    s32 candidate;

    func_001E1090(arg0, arg1);
    func_00250360(arg0, arg1);
    side = func_001E0700(arg0, arg1) >> 5;
    otherSide = side != 0 ? 0 : side + 1;
    arg0 = (arg0 << 8) | arg1;

    i = 0;
    do {
        position = func_00155520(i, side);
        candidate = func_001E3790(position & 0xFF, position >> 8);
        if (candidate < 0) {
            return 0;
        }
        if (candidate == arg0) {
            return 1;
        }
    } while (++i < 7);

    i = 0;
    do {
        position = func_00155520(i, otherSide);
        candidate = func_001E3790(position & 0xFF, position >> 8);
        if (candidate < 0) {
            return 0;
        }
        if (candidate == arg0) {
            return 1;
        }
    } while (++i < 7);

    return 0;
}

typedef struct {
    u8 data[0x3C];
    u16 unk3C;
    u8 pad3E[0x22];
} Work_00155770;

typedef struct {
    s16 id;
    u8 kind;
    u8 pad3;
    s16 value;
    u8 pad6[6];
    s32 unkC;
} Ctx_00155770;

s32 func_00155770(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_00278890();
    Work_00155770 work;
    s32 ret;
    s32 res;
    s32 pos;
    s32 kind;
    Ctx_00155770 *ctx = (Ctx_00155770 *)arg2;

    ctx->id = arg0;
    if (func_001DE6D0(arg1) == 0) {
        return -1;
    }
    if (func_00278890(arg1, 0) == 5 && func_00278890(arg1, 1) == 5) {
        return -1;
    }
    kind = func_00155A00(arg1, &work);
    if (kind < 0) {
        return -1;
    }
    ctx->kind = 10;
    ctx->unkC = 0;
    pos = func_001E1090(arg0 >> 8, arg0 & 0xFF);
    ret = func_00276F10(&work, pos & 0xFF, pos >> 8, arg1 == 0 ? 1 : 0, 3, 0x1F, 2, 2, 0, func_00158780(arg1));
    if (kind == 0) {
        if (func_001564E0(arg1, ctx, &work) < 0) {
            goto fallback;
        }
        if (ret < 0) {
            if (func_001E0150(arg1) >= 6) {
                goto fallback;
            }
            res = func_00156B40(arg1, kind & 0xFF, &work, ret);
            if (res < 0) {
                return -1;
            }
            ctx->value = res;
            return 1;
        }
        res = func_00156B40(arg1, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
    if (kind == 2) {
        func_00156910(arg1, ctx, &work);
        res = func_00156B40(arg1, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
    if (kind == 3) {
        func_00155C90(arg1, ctx, &work);
        res = func_00156B40(arg1, kind & 0xFF, &work, ret);
        if (res < 0) {
            return -1;
        }
        ctx->value = res;
        return 1;
    }
fallback:
    if (func_001562E0(arg1, (u8 *)ctx, &work, work.unk3C) < 0) {
        return -1;
    }
    res = func_00156B40(arg1, kind & 0xFF, &work, ret);
    if (res < 0) {
        return -1;
    }
    ctx->value = res;
    return 1;
}

s32 func_00155A00(s32 arg0, void *arg1) {
    extern s32 func_00278890();
    extern s32 func_00158800();
    s32 entries[8];
    u8 work[32];
    u8 kind0;
    u8 kind1;
    s32 i;
    s32 ret;

    kind0 = (u8)func_00278890(arg0, 0);
    kind1 = (u8)func_00278890(arg0, 1);
    if (arg1 == NULL) {
        return -1;
    }
    func_0026FD30(arg0, entries);
    if (kind0 == 5) {
        if (func_001562E0(arg0, work, arg1, 999) >= 0) {
            return 1;
        }
        return -1;
    }
    if (kind1 == 5) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if ((func_0026FCE0(entries[i]) >> 5) == 0 &&
                func_0026FB10(arg0, entries[i]) == 1) {
                func_001DCD70(arg1, entries[i]);
                return 0;
            }
        }
        return -1;
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (func_001DE020(func_0026FCE0(entries[i]) >> 5) == 2) {
            func_001DCD70(arg1, entries[i]);
            return 2;
        }
    }
    if (func_00158800(arg0) == 1) {
        if (func_00155C90(arg0, work, arg1) >= 0) {
            return 3;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((func_0026FCE0(entries[i]) >> 5) == 0 &&
            func_0026FB10(arg0, entries[i]) == 1) {
            return 0;
        }
    }
    ret = func_001562E0(arg0, work, arg1, 999);
    if (ret >= 0) {
        return ret;
    }
    return -1;
}

typedef struct {
    u8 pad[0x38];
    s16 attack;
    s16 defense;
} Stats_00155C90;


s32 func_00155C90(s32 arg0, u8 *arg1, void *arg2) {
    s32 sortCount;
    s32 cards[5];
    u8 selected[5];
    u16 order[5];
    s32 selectedCount;
    u8 *selectedCursor;
    s32 *cardCursor;
    s32 *sortCards;
    u8 *selectedBase;
    u16 *orderBase;
    s32 i;
    u16 *orderCursor;
    s32 j;
    u8 *appendCursor;
    s32 appendIndex;
    s32 remaining;
    s32 copyIndex;

    selectedBase = selected;
    orderBase = order;
    selectedCount = 0;
    sortCount = 0;
    {
        s32 n = 0;
        do {
            selected[n] = order[n] = 0xFF;
            n++;
        } while (n < 5);
    }
    func_0026FD30(arg0, cards);
    i = 0;
    if (0 < func_0026FE20(arg0)) {
        selectedCursor = selectedBase;
        do {
            if (func_001587E0(cards[i]) == 1) {
                *selectedCursor++ = i;
                selectedCount++;
                i = func_0026FE20(arg0);
            }
            i++;
        } while (i < func_0026FE20(arg0));
    }
    if (selectedCount == 0) {
        return -1;
    }
    func_001DCD70(arg2, cards[selected[0]]);
    i = 0;
    if (0 < func_0026FE20(arg0)) {
        cardCursor = cards;
        appendCursor = selected + selectedCount;
        do {
            if (func_00248F60(cards[selected[0]], *cardCursor) >= 0 &&
                (func_0026FCE0(*cardCursor) >> 5) == 2) {
                s32 card = *cardCursor;
                if (card != 0x31B && card != 0x31C) {
                    ((Stats_00155C90 *)arg2)->attack += (s16)func_002493A0(card);
                    ((Stats_00155C90 *)arg2)->defense += (s16)func_002493A0(*cardCursor);
                    selectedCount++;
                    *appendCursor++ = i;
                }
            }
            cardCursor++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    j = 0;
    if (0 < func_0026FE20(arg0)) {
            sortCards = cards;
            orderCursor = orderBase;
            do {
                if (func_00156870(*sortCards) == 0) {
                    *orderCursor++ = j;
                    sortCount++;
                }
                sortCards++;
                j++;
            } while (j < func_0026FE20(arg0));
    }
    func_00155FB0(order, 0, sortCount - 1, arg0, cards);
    remaining = func_0026FE20(arg0) - selectedCount;
    copyIndex = 0;
    if (0 < remaining) {
        do {
            arg1[copyIndex + 6] = *(u8 *)orderBase;
            copyIndex++;
            orderBase++;
        } while (copyIndex < remaining);
    }
    appendIndex = 0;
    if (0 < selectedCount) {
        do {
            arg1[remaining + 6] = *selectedBase;
            appendIndex++;
            remaining++;
            selectedBase++;
        } while (appendIndex < selectedCount);
    }
    return 1;
}

void func_00155FB0(u16 *indices, s32 first, s32 last, s32 key, s32 *values) {
    s32 pivot;
    s32 i;
    u16 *scan;
    s32 score;

    if (first < last) {
        func_001562B0((s32 *)indices, first, (first + last) >> 1);
        i = first + 1;
        pivot = first;
        if (i <= last) {
            scan = &indices[i];
            do {
                score = func_0026FA80(values[*scan], key);
                if (func_0026FA80(values[indices[first]], key) < score) {
                    pivot++;
                    func_001562B0((s32 *)indices, pivot, i);
                }
                i++;
                scan++;
            } while (i <= last);
        }
        func_001562B0((s32 *)indices, first, pivot);
        if (first < pivot) {
            s32 leftPivot;
            s32 j;
            u16 *leftScan;

            func_001562B0((s32 *)indices, first, (first + pivot) >> 1);
            j = first + 1;
            leftPivot = first;
            if (j <= pivot) {
                leftScan = &indices[j];
                do {
                    if (func_0026FA80(values[*leftScan], key) >
                        func_0026FA80(values[indices[first]], key)) {
                        leftPivot++;
                        func_001562B0((s32 *)indices, leftPivot, j);
                    }
                    j++;
                    leftScan++;
                } while (j <= pivot);
            }
            func_001562B0((s32 *)indices, first, leftPivot);
            func_00155FB0(indices, first, leftPivot, key, values);
            func_00155FB0(indices, leftPivot + 1, pivot, key, values);
        }
        if (pivot + 1 < last) {
            s32 rightPivot;
            s32 k;
            u16 *rightScan;
            s32 rightScore;

            func_001562B0((s32 *)indices, pivot + 1, (pivot + 1 + last) >> 1);
            k = pivot + 2;
            rightPivot = pivot + 1;
            if (k <= last) {
                rightScan = &indices[k];
                do {
                    rightScore = func_0026FA80(values[*rightScan], key);
                    if (func_0026FA80(values[indices[pivot + 1]], key) < rightScore) {
                        rightPivot++;
                        func_001562B0((s32 *)indices, rightPivot, k);
                    }
                    k++;
                    rightScan++;
                } while (k <= last);
            }
            func_001562B0((s32 *)indices, pivot + 1, rightPivot);
            func_00155FB0(indices, pivot + 1, rightPivot, key, values);
            func_00155FB0(indices, rightPivot + 1, last, key, values);
        }
    }
}

void func_001562B0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 *temp_a1;
    s32 *temp_a2;

    temp_a1 = &arg0[arg1];
    temp_a2 = &arg0[arg2];
    temp_a0 = *temp_a1;
    *temp_a1 = *temp_a2;
    *temp_a2 = temp_a0;
}

s32 func_001562E0(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
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

u16 *func_00278A90(s32, u16 *, s32, s32, s32, s16 *, s16 *);

typedef struct Info_001564E0 {
    u8 pad[8];
    u16 x;
    s16 y;
} Info_001564E0;

typedef struct Sprite_001564E0 {
    Info_001564E0 *info;
    u8 pad[0x34];
    s16 x;
    s16 y;
} Sprite_001564E0;

s32 func_001564E0(s32 arg0, u8 *arg1, void *arg2) {
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
                if ((func_0026FCE0(card) >> 5) == 0 && func_0026FB10(arg0, card) == 1) {
                    *node = func_00278A90(arg0, *node, i & 0xFF, card & 0xFFFF, 0, &a, &b);
                    *node = func_00278E40(*node);
                    value = func_00278F10(arg0, *node, 0, 0);
                    if (best < (value & 0xFFFF)) {
                        func_001566D0(arg0, *node, entries);
                        func_00278DD0((u8 *)*node + 2, arg1 + 6);
                        func_001DCD70(arg2, (s32)**node);
                        ((Sprite_001564E0 *)arg2)->x = (value >> 16) - (((Sprite_001564E0 *)arg2)->info->x & 0x1FFF);
                        ((Sprite_001564E0 *)arg2)->y = (value & 0xFFFF) - (((Sprite_001564E0 *)arg2)->info->y & 0x1FFF);
                        best = value;
                        if (top < (value & 0xFFFF)) {
                            top = value & 0xFFFF;
                        }
                    } else if (top < (value & 0xFFFF)) {
                        top = value & 0xFFFF;
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

void func_001566D0(s32 arg0, u16 *arg1, s32 *arg2) {
    s32 count;
    s32 i;
    s32 id;
    u8 limit;
    u8 buf[5];

    if (arg1 == NULL) {
        return;
    }
    limit = func_0026FA80(*arg1, arg0);
    for (i = 0; i < 5; i++) {
        buf[i] = 0xFF;
    }
    for (i = 0, count = 0; i < func_0026FE20(arg0); i++) {
        if ((u8)func_00278E00(i, (u8 *)(arg1 + 1)) == 0) {
            buf[count++] = i;
        }
    }
    if (count != 0) {
        for (i = 0; i < (u8)func_00278D90(buf); i++) {
            id = arg2[buf[i]];
            if (id != 999 && func_00156870(id) == 0 && limit >= func_0026FA80(id, arg0) &&
                (u16)func_002789F0(*arg1, (u16)id) == 999) {
                func_00278D20((u8 *)(arg1 + 1), buf[i]);
            }
        }
    }
}

s32 func_00156870(s32 arg0) {
    extern u32 func_0026FBB0();
    s32 cost;

    cost = func_0026FBB0(arg0);
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if ((cost & 0xFFFF) + (cost >> 16) * 2 > 0x1194) {
        return 1;
    }
    if (func_001587E0(arg0) == 1) {
        return 1;
    }
    return 0;
}


typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00156910;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 f3A;
    u16 id;
} Obj2_00156910;

s32 func_00156910(s32 arg0, void *arg1, void *arg2) {
    Obj1_00156910 *o1 = arg1;
    Obj2_00156910 *o2 = arg2;
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

INCLUDE_ASM("asm/nonmatchings/main_013", func_00156B40);

s32 func_00156EA0(void) {
    s32 i;
    s32 value;

    for (i = 0; i < 4; i++) {
        switch ((u8)i) {
        case 0:
            value = 0x303;
            break;
        case 1:
            value = 0x404;
            break;
        case 2:
            value = 0x402;
            break;
        case 3:
            value = 0x503;
            break;
        default:
            value = 0x503;
            break;
        }
        if (func_001E36E0(value & 0xFF, value >> 8) == 0) {
            return value;
        }
    }
    return -1;
}

s32 func_00156F70(void) {
    if (func_001E36E0(2, 3) == 0) {
        return 0x302;
    }
    return (func_001E36E0(4, 3) == 0) ? 0x304 : -1;
}

typedef struct {
    u16 id;
    u8 pad2[6];
    u32 position;
} Record_00156FC0;

typedef struct {
    u16 id;
    u8 kind;
    u8 pad3;
    u16 position;
    u8 pad6[6];
    s32 action;
    u8 status;
} Result_00156FC0;

typedef struct {
    u8 x : 4;
    u8 y : 4;
} Position_00156FC0;

s32 func_00276CC0(s32, s32, s32, s32, s32, s32);

static inline u32 position_00156FC0(void *src, u8 mode) {
    if (mode == 1) {
        return (u16)(((Record_00156FC0 *)src)->position >> 16);
    }
    return (u16)((Record_00156FC0 *)src)->position;
}

static inline s32 closer_00156FC0(Position_00156FC0 *best, Position_00156FC0 *current,
                                 s32 x, s32 y) {
    s32 bestLowY = best->y < y ? best->y : y;
    s32 bestHighY = y < best->y ? best->y : y;
    s32 bestLowX = best->x < x ? best->x : x;
    s32 bestHighX = x < best->x ? best->x : x;
    s32 currentLowY = current->y < y ? current->y : y;
    s32 currentHighY = y < current->y ? current->y : y;
    s32 currentLowX = current->x < x ? current->x : x;
    s32 currentHighX = x < current->x ? current->x : x;
    return ((currentHighX - currentLowX) + (currentHighY - currentLowY)) <
           ((bestHighX - bestLowX) + (bestHighY - bestLowY));
}

s32 func_00156FC0(void *arg0, s32 arg1, void *arg2, u8 arg3) {
    extern void func_0027A090();
    s32 sourcePosition;
    s32 targetPosition;
    s32 count;
    Position_00156FC0 positions[12];
    s32 i;
    Position_00156FC0 *p;
    Position_00156FC0 *candidate;
    s32 sourceY;
    s32 sourceX;
    u32 lowPosition;
    u32 highPosition;
    s32 card;

    lowPosition = position_00156FC0(arg0, arg3);
    highPosition = position_00156FC0(arg0, arg3);
    if (func_001DF540(highPosition >> 8, lowPosition & 0xFF) == 0) {
        func_0027B1B0(arg0, 1);
        return -1;
    }
    sourcePosition = func_001E1090(((Record_00156FC0 *)arg0)->id >> 8, ((Record_00156FC0 *)arg0)->id & 0xFF);
    lowPosition = position_00156FC0(arg0, arg3);
    highPosition = position_00156FC0(arg0, arg3);
    targetPosition = func_001E1090(highPosition >> 8, lowPosition & 0xFF);
    candidate = positions;
    i = 0;
    p = candidate;
    do {
        p->x = p->y = 15;
        i++;
        p++;
    } while (i < 12);

    card = func_001DF540(((Record_00156FC0 *)arg0)->id >> 8, ((Record_00156FC0 *)arg0)->id & 0xFF);
    sourceX = sourcePosition & 0xFF;
    sourceY = sourcePosition >> 8;
    if (func_002464F0(card, sourceX, sourceY) == 0) {
        s32 value;
        ((Result_00156FC0 *)arg2)->id = ((Record_00156FC0 *)arg0)->id;
        ((Result_00156FC0 *)arg2)->kind = 6;
        ((Result_00156FC0 *)arg2)->position = sourcePosition;
        value = func_00276CC0(sourceX, sourceY, arg1, 3, 1,
                             (u8)func_00158780(arg1));
        if (value >= func_001E0290(((Record_00156FC0 *)arg0)->id >> 8, ((Record_00156FC0 *)arg0)->id & 0xFF, 0)) {
            ((Result_00156FC0 *)arg2)->status = 1;
        } else {
            ((Result_00156FC0 *)arg2)->status = 0;
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    } else {
        s32 id;
        u16 flags;
        s32 targetY;
        s32 targetX;
        s32 bestIndex;
        s32 index;
        s32 bestValue;

        id = ((Record_00156FC0 *)arg0)->id;
        flags = (u16)func_00158780(arg1);
        func_0027A090(id >> 8, id & 0xFF, positions, sourceX, sourceY,
                     targetX = targetPosition & 0xFF, targetY = targetPosition >> 8,
                     position_00156FC0(arg0, arg3),
                     (s64)0, (s64)30, (s64)flags);
        count = func_0027AFC0((u8 *)positions);
        bestIndex = 0xFF;
        if (count > 0) {
            bestValue = 0xFFFF;
            index = 0;
            if (index < count) {
            do {
                s32 value;
                value = func_00276CC0(candidate->x, candidate->y, arg1, 2, 1,
                                     (u8)func_00158780(arg1));
                if (value < bestValue) {
                    bestValue = value;
                    bestIndex = index;
                } else if (value == bestValue) {
                    if (closer_00156FC0(&positions[bestIndex], candidate, targetX, targetY)) {
                        bestValue = value;
                        bestIndex = index;
                    }
                }
                index++;
                candidate++;
            } while (index < count);
            }
        } else {
            ((Result_00156FC0 *)arg2)->id = ((Record_00156FC0 *)arg0)->id;
            ((Result_00156FC0 *)arg2)->kind = 6;
            ((Result_00156FC0 *)arg2)->position = sourcePosition;
            ((Result_00156FC0 *)arg2)->action = 2;
            ((Result_00156FC0 *)arg2)->status = 2;
            func_0027B1B0(arg0, arg3);
            return -1;
        }
        if (bestIndex != 0xFF) {
            ((Result_00156FC0 *)arg2)->id = ((Record_00156FC0 *)arg0)->id;
            ((Result_00156FC0 *)arg2)->kind = 6;
            ((Result_00156FC0 *)arg2)->position = (positions[bestIndex].y << 8) | positions[bestIndex].x;
            ((Result_00156FC0 *)arg2)->action = 2;
            ((Result_00156FC0 *)arg2)->status = 2;
        } else {
            ((Result_00156FC0 *)arg2)->id = ((Record_00156FC0 *)arg0)->id;
            ((Result_00156FC0 *)arg2)->kind = 6;
            ((Result_00156FC0 *)arg2)->position = sourcePosition;
            ((Result_00156FC0 *)arg2)->action = 2;
            ((Result_00156FC0 *)arg2)->status = 2;
            func_0027B1B0(arg0, arg3);
            return -1;
        }
    }
    return 0;
}

typedef struct Nibbles_00157480 {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00157480;

typedef struct Output_00157480 {
    u16 position;
    u8 action;
    u8 pad3;
    u16 destination;
    u8 pad6[6];
    s32 special;
    u8 result;
} Output_00157480;

s32 func_00276CC0(s32, s32, s32, s32, s32, s32);
s32 func_0027BE10(s32, s32, s32, s32, s32);

s32 func_00157480(u16 *arg0, s32 arg1, void *arg2, u8 arg3) {
    Output_00157480 *output = arg2;
    s32 target;
    u8 endX;
    u8 extra;
    Nibbles_00157480 nibbles[12];
    s32 bestScore;
    s32 best;
    s32 i;
    Nibbles_00157480 *p;
    extern s32 func_00158360();
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

        initialScore = func_00158780(arg1);
        centerX = target & 0xFF;
        centerY = target >> 8;
        if (func_00276CC0(centerX, centerY, *arg0, 3, initialScore, 0) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00158360(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if ((range = func_002464F0(func_001DF540(*arg0 >> 8, *arg0 & 0xFF), centerX, centerY)) == 0) {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00158360(*arg0 >> 8, *arg0 & 0xFF, arg0);
            func_0027B1B0(arg0, arg3);
            return 0;
        }
        if (func_001E2100(*arg0 >> 8, *arg0 & 0xFF, 4) != 0) {
            if ((func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 1 ||
                (func_001E0700(*arg0 >> 8, *arg0 & 0xFF) >> 5) == 5) {
                func_001E1E70(*arg0 >> 8, *arg0 & 0xFF, 0, 1);
                output->position = *arg0;
                output->action = 0xE;
                return 0;
            }
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
                        candidateScore = func_00276CC0(x, y, *arg0, 3, (u16)func_00158780(arg1), 0);
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
            output->special = func_00158360(*arg0 >> 8, *arg0 & 0xFF, arg0);
        } else {
            output->position = *arg0;
            output->action = 6;
            output->destination = target;
            output->result = func_0027E360(*arg0 >> 8, *arg0 & 0xFF, output->destination, 1, 0);
            output->special = func_00158360(*arg0 >> 8, *arg0 & 0xFF, arg0);
        }
        func_0027B1B0(arg0, arg3);
        return 0;
    }
}

typedef struct Coord_00157A50 {
    u8 x : 4;
    u8 y : 4;
} Coord_00157A50;

typedef struct Unit_00157A50 {
    u16 position;
    u8 pad2[6];
    union {
        u32 packed;
        u16 low;
    } target;
} Unit_00157A50;

typedef struct Output_00157A50 {
    u16 position;
    u8 kind;
    u8 pad3;
    u16 target;
    u8 pad6[6];
    s32 value;
    u8 flag;
} Output_00157A50;


static inline u32 target_00157A50(void *unit, s32 side) {
    return side == 1 ? (u32)(u16)(((Unit_00157A50 *)unit)->target.packed >> 16) : (u32)((Unit_00157A50 *)unit)->target.low;
}

static inline u32 minY_00157A50(void *unit, s32 side, u8 coord) {
    return coord < (target_00157A50(unit, side) >> 8) ? coord : (target_00157A50(unit, side) >> 8);
}

static inline u32 maxY_00157A50(void *unit, s32 side, u8 coord) {
    return (target_00157A50(unit, side) >> 8) < coord ? coord : (target_00157A50(unit, side) >> 8);
}

static inline u32 minX_00157A50(void *unit, s32 side, u8 coord) {
    return coord < (target_00157A50(unit, side) & 0xFF) ? coord : (target_00157A50(unit, side) & 0xFF);
}

static inline u32 maxX_00157A50(void *unit, s32 side, u8 coord) {
    return (target_00157A50(unit, side) & 0xFF) < coord ? coord : (target_00157A50(unit, side) & 0xFF);
}

s32 func_00157A50(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4, u8 arg5) {
    extern s32 func_00158360();
    extern s32 func_00276CC0();
    extern void func_00279230();
    extern void func_0027A090();
    extern s32 func_0027E360(s32, s32, s32, u8, s32);
    Coord_00157A50 coords[12];
    s32 initial;
    s32 cell;
    s32 count;

    initial = func_001E1090(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF);
    {
        s32 bestScore;
        s32 best;
        s32 side = arg3;
        Coord_00157A50 *candidate;
        s32 index;
        if (target_00157A50(arg0, side) == 0xFFFF) {
            if (initial == target_00157A50(arg0, side)) {
                ((Output_00157A50 *)arg2)->position = ((Unit_00157A50 *)arg0)->position;
                ((Output_00157A50 *)arg2)->kind = 6;
                ((Output_00157A50 *)arg2)->target = initial;
                ((Output_00157A50 *)arg2)->flag = func_0027E360(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF, ((Output_00157A50 *)arg2)->target, arg4, 0);
                ((Output_00157A50 *)arg2)->value = func_00158360(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF, arg0);
                func_0027B1B0(arg0, arg3);
                return 0;
            }
        }

        if (func_001E2100(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF, 4) != 0) {
            if ((func_001E0700(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF) >> 5) == 1 ||
                (func_001E0700(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF) >> 5) == 5) {
                func_001E1E70(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF, 0, 1);
                ((Output_00157A50 *)arg2)->position = ((Unit_00157A50 *)arg0)->position;
                ((Output_00157A50 *)arg2)->kind = 14;
                return 0;
            }
        }

        candidate = coords;
        {
            s32 i = 0;
            Coord_00157A50 *entry = candidate;
            do {
                entry->x = entry->y = 0xF;
                i++;
                entry++;
            } while (i < 12);
        }

        cell = func_001E3790(target_00157A50(arg0, side) & 0xFF, target_00157A50(arg0, side) >> 8);
        if (cell < 0) {
            cell = 0xFFFF;
        }
        if (arg5 == 1) {
            func_0027A090(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF,
                         coords, initial & 0xFF, initial >> 8, target_00157A50(arg0, side) & 0xFF,
                         target_00157A50(arg0, side) >> 8, 0xFFFF, 0, 30, (u16)func_00158780(arg1));
        } else {
            func_00279230(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF,
                         coords, initial & 0xFF, initial >> 8, target_00157A50(arg0, side) & 0xFF,
                         target_00157A50(arg0, side) >> 8, (u16)cell, 7);
        }
        count = func_0027AFC0((u8 *)coords);
        {
            if (count > 0) {
                best = 0xFF;
                bestScore = 0xFFFF;
                for (index = 0; index < count; index++) {
                    if (func_001E36E0(candidate->x, candidate->y) == 0) {
                        s32 score = func_00276CC0(candidate->x, candidate->y, arg1, 3, 1, (u8)func_00158780(arg1));
                        if (score < bestScore) {
                            bestScore = score;
                            best = index;
                        } else if (score == bestScore) {
                            u32 bestMinY;
                            u32 bestMaxY;
                            u32 bestMinX;
                            u32 bestMaxX;
                            u32 currentMinY;
                            u32 currentMaxY;
                            u32 currentMinX;
                            u32 currentMaxX;
                            u32 bestY;
                            u32 bestX;
                            u32 currentY;
                            u32 currentX;
                            bestY = (u8)(&coords[best])->y;
                            bestMinY = minY_00157A50(arg0, side, bestY);
                            bestMaxY = maxY_00157A50(arg0, side, bestY);
                            bestX = (&coords[best])->x;
                            bestMinX = minX_00157A50(arg0, side, bestX);
                            bestMaxX = maxX_00157A50(arg0, side, bestX);
                            currentY = (u8)candidate->y;
                            currentMinY = minY_00157A50(arg0, side, currentY);
                            currentMaxY = maxY_00157A50(arg0, side, currentY);
                            currentX = candidate->x;
                            currentMinX = minX_00157A50(arg0, side, currentX);
                            currentMaxX = maxX_00157A50(arg0, side, currentX);
                            if ((currentMaxX - currentMinX) + (currentMaxY - currentMinY) < (bestMaxX - bestMinX) + (bestMaxY - bestMinY)) {
                                bestScore = score;
                                best = index;
                            }
                        }
                    }
                    candidate++;
                }
            } else {
                ((Output_00157A50 *)arg2)->position = ((Unit_00157A50 *)arg0)->position;
                ((Output_00157A50 *)arg2)->kind = 6;
                ((Output_00157A50 *)arg2)->target = initial;
                ((Output_00157A50 *)arg2)->flag = func_0027E360(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF, ((Output_00157A50 *)arg2)->target, arg4, 0);
                ((Output_00157A50 *)arg2)->value = func_00158360(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF, arg0);
                func_0027B1B0(arg0, arg3);
                return 0;
            }

            if (best != 0xFF) {
                ((Output_00157A50 *)arg2)->position = ((Unit_00157A50 *)arg0)->position;
                ((Output_00157A50 *)arg2)->kind = 6;
                ((Output_00157A50 *)arg2)->target = (coords[best].y << 8) | coords[best].x;
                ((Output_00157A50 *)arg2)->flag = func_0027E360(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF, ((Output_00157A50 *)arg2)->target, arg4, 0);
                ((Output_00157A50 *)arg2)->value = func_00158360(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF, arg0);
            } else {
                ((Output_00157A50 *)arg2)->position = ((Unit_00157A50 *)arg0)->position;
                ((Output_00157A50 *)arg2)->kind = 6;
                ((Output_00157A50 *)arg2)->target = initial;
                ((Output_00157A50 *)arg2)->flag = func_0027E360(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF, ((Output_00157A50 *)arg2)->target, arg4, 0);
                ((Output_00157A50 *)arg2)->value = func_00158360(((Unit_00157A50 *)arg0)->position >> 8, ((Unit_00157A50 *)arg0)->position & 0xFF, arg0);
            }
            func_0027B1B0(arg0, arg3);
        }
    }
    return 0;
}

s32 func_00158360(s32 arg0, s32 arg1) {
    u8 sp70[0x20];
    u8 sp90[0x60];
    s32 spF0[8];
    u8 count;
    s32 state;
    s32 mask;
    u32 *data;

    extern s32 func_00158800();

    count = 0;
    state = func_001E1030();
    func_001E1090(arg0, arg1);
    mask = func_00250360(arg0, arg1);
    data = func_001E0B70(arg0, arg1, 0);
    func_0026FD30(arg0, spF0);
    if (func_001E2100(arg0, arg1, 4) != 0) {
        return 0;
    }
    if (func_001587E0(state) == 1) {
        if (func_00158960(mask) == 4) {
            return 1;
        }
    }
    switch (func_001E0700(arg0, arg1) >> 5) {
    case 0:
        switch (state) {
        case 0x5F:
            if (func_001DF470(arg0) < 0x4B0) {
                return 1;
            }
            break;
        case 0x40: {
            s32 i;
            s32 position;

            mask = func_0024CA40(0, 0, mask, 2, 3, 14);
            for (i = 0; i < func_0024E910(mask); i++) {
                position = func_0024EC50(mask, i);
                if (func_002781B0(position >> 8, position & 0xFF, 0) == 1) {
                    count++;
                }
            }
            if ((u8)count > 1) {
                return 1;
            }
            break;
        }
        }
        return 2;
    case 1:
        if (func_0027D830(arg0, arg1, 0, 0, 6, 0) == 5) {
            return 2;
        }
        if (data == NULL) {
            return 2;
        }
        switch (*data >> 8) {
        case 0x22:
            if (func_0024E910(func_0024CA40(0, 0, mask, 2, 0x1D, 14)) > 3) {
                return 1;
            }
            break;
        case 0x17: {
            s32 list;
            s32 i;
            s32 position;

            list = func_0024CA40(0, 0, mask, 2, 0x34, 14);
            for (i = 0; i < func_0024E910(list); i++) {
                position = func_0024EC50(list, i);
                if ((func_001E1090(position >> 8, position & 0xFF) >> 8) >= 2) {
                    return 1;
                }
            }
            break;
        }
        case 0x26: {
            s32 *p;
            s32 i;

            i = 0;
            if (i < func_0026FE20(mask)) {
                p = spF0;
                do {
                    if (func_001DE020(func_0026FCE0(*p) >> 5) == 2) {
                        return 1;
                    }
                    p++;
                    i++;
                } while (i < func_0026FE20(mask));
            }
            if (func_00158800(mask) == 1 && func_00155C90(mask, sp70, sp90) >= 0) {
                return 1;
            }
            break;
        }
        case 0xD:
            if ((*data & 0x3F) == 0x32) {
                if (func_0024E780(mask == 0 ? 1 : 0, 3) >= 3) {
                    return 1;
                }
            } else {
                return 1;
            }
            break;
        }
        break;
    default:
        return 2;
    }
    return 2;
}

s32 func_00158780(s32 arg0) {
    if (func_001DF470(arg0) > 0x4B0) {
        if (func_001E0150(arg0) >= 5) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x960;
    }
}

s32 func_001587E0(s32 arg0) {
    s32 result;

    result = (u32) (arg0 - 0x36) < 4U ? 1 : 0;
    return result;
}

s32 func_00158800(s32 arg0) {
    return func_00158810(arg0);
}

s32 func_00158810(s32 arg0) {
    if (func_0024CA40(0, 0, arg0, 1, 0x032B001C, 14) == 0) {
        if (func_0027DD20(arg0, 1, 0x32B) == 0) {
            return 0;
        }
    }
    if (func_0024CA40(0, 0, arg0, 1, 0x0325001C, 14) == 0) {
        if (func_0027DD20(arg0, 1, 0x325) == 0) {
            return 0;
        }
    }
    if (func_0024CA40(0, 0, arg0, 1, 0x0335001C, 14) == 0) {
        if (func_0027DD20(arg0, 1, 0x335) == 0) {
            return 0;
        }
    }
    if (func_0024CA40(0, 0, arg0, 1, 0x0338001C, 14) == 0) {
        if (func_0027DD20(arg0, 1, 0x338) == 0) {
            return 0;
        }
    }
    return 1;
}

s32 func_00158960(s32 arg0) {
    extern s32 func_001E1030();
    extern s32 func_001E1580();
    extern s32 func_001E1640();
    s32 i;
    s32 count;
    s32 j;
    s32 type;
    s32 v;
    s32 found[4];

    count = 0;
    if (func_001E1030(arg0, 0) == 0x3A) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 8; j++) {
                v = func_0024E410(arg0, j);
                if (func_001E36E0(v & 0xFF, v >> 8) != 0) {
                    v = func_001E3790(v & 0xFF, v >> 8);
                    if (v >= 0) {
                        type = func_001E1030(v >> 8, v & 0xFF);
                        if (type == func_002686F0(i) &&
                            func_001E1580(v >> 8, v & 0xFF) == 0 &&
                            func_001E1640(v >> 8, v & 0xFF) == 0 &&
                            (v >> 8) == arg0) {
                            found[i] = 1;
                        }
                    }
                }
            }
            count += found[i];
        }
        return count;
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
} Req_00158AB0;

typedef struct {
    u8 pad0[0x160];
    u16 list[32];    /* 0x160 */
    u8 idx : 5;      /* 0x1A0 */
    u8 pad1A0 : 3;
    u8 pad1A1;
    u16 count;       /* 0x1A2 */
} Work_00158AB0;

s32 func_00276290(void *, void *, s32);

s32 func_00158AB0(s32 arg0, void *arg1) {
    Req_00158AB0 req;
    Work_00158AB0 *w;
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
        if (func_00154220(w, &req, arg0) == 0) {
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

s32 func_00158C80(void *work, void *arg1, s32 arg2) {
    u16 *arg0 = work;
    s32 side;
    s32 found;
    s32 result;
    s32 index;

    side = func_001DE540();
    found = 0;
    if ((result = func_00159380(arg0, side, (s32)arg1)) < 0) {
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
    func_001591B0(arg0 + index * 8);
    switch ((arg0[index * 8 + 2] >> 8) & 0xFF) {
    case 5:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_0015B250(arg0 + index * 8, side, arg1, 1);
            found = 1;
        }
        break;
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_0015B820(arg0 + index * 8, side, arg1, 1) < 0) {
                func_0027B1B0(arg0 + index * 8, 1);
                return 1;
            }
            found = 1;
        }
        break;
    case 10:
        if (func_0015A360(arg0[index * 8], side, (s32)arg1) < 0) {
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
            func_0015BE00(arg0 + index * 8, side, arg1, 1, 0);
            found = 1;
        }
        break;
    case 3:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_0015BE00(arg0 + index * 8, side, arg1, 1, 1);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 1, 0, func_0015D120(side), 3, 1);
        found = 1;
        break;
    case 11:
        func_0015C670(arg0 + index * 8, side, arg1, 1);
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
            func_0015B250(arg0 + index * 8, side, arg1, 0);
            found = 1;
        }
        break;
    case 2:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            if (func_0015B820(arg0 + index * 8, side, arg1, 0) < 0) {
                func_0015B250(arg0 + index * 8, side, arg1, 0);
            }
            found = 1;
        }
        break;
    case 10:
        if (func_0015A360(arg0[index * 8], side, (s32)arg1) < 0) {
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
            func_0015BE00(arg0 + index * 8, side, arg1, 0, 0);
            found = 1;
        }
        break;
    case 3:
        if (func_001E2100(arg0[index * 8] >> 8, arg0[index * 8] & 0xFF, 0) == 0) {
            func_0015BE00(arg0 + index * 8, side, arg1, 0, 1);
            found = 1;
        }
        break;
    case 9:
        func_0027D020(arg0 + index * 8, side, arg1, 0, 0, func_0015D120(side), 3, 1);
        found = 1;
        break;
    case 11:
        func_0015C670(arg0 + index * 8, side, arg1, 0);
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

s32 func_001591B0(u16 *arg0) {
    extern void func_00159760();
    s32 temp_a1;
    s32 temp_v1_2;
    s32 temp_v1_4;
    u32 temp_v1_3;
    u16 temp_v1;
    s32 temp_s0;

    func_001E1090((s32) arg0[0] >> 8, arg0[0] & 0xFF);
    temp_s0 = func_00250360((s32) arg0[0] >> 8, arg0[0] & 0xFF);
    if (func_001DF540((s32) arg0[0] >> 8, arg0[0] & 0xFF) != 0) {
        if (func_001E2100((s32) arg0[0] >> 8, arg0[0] & 0xFF, 0) == 0) {
            temp_v1 = arg0[0];
            if (temp_v1 != 0xFFFF) {
                temp_a1 = temp_v1 & 0xFF;
                if (temp_a1 == 0) {
                    if (*(s32 *)(arg0 + 4) == -1) {
                        func_00159760(arg0, temp_a1);
                    }
                } else {
                    temp_v1_2 = func_001E0700((s32) temp_v1 >> 8, temp_a1) >> 5;
                    switch (temp_v1_2) {
                    case 0:
                        if (func_002507D0((s32) arg0[0] >> 8, arg0[0] & 0xFF) == 1) {
                            func_00159FE0(arg0);
                        } else {
                            func_00159D00(arg0);
                        }
                        break;
                    case 2:
                        func_0027CA50(arg0, 3, 0, func_0015D120(temp_s0) & 0xFF);
                        break;
                    case 5:
                        func_00159D00(arg0);
                        if ((((s32) arg0[2] >> 8) & 0xFF) == 2) {
                            temp_v1_3 = (u32) *(s32 *)(arg0 + 4) >> 0x10;
                            temp_v1_4 = func_001E1090((s32) ((temp_v1_3 & 0xFFFF) >> 8), temp_v1_3 & 0xFF) << 0x10;
                            arg0[2] = 0x6FF;
                            *(s32 *)(arg0 + 4) = temp_v1_4 | arg0[4];
                        }
                        break;
                    default:
                        arg0[2] = 0x5FF;
                        break;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

s32 func_00159380(u16 *arg0, s32 arg1, s32 arg2) {
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
    func_001591B0(arg0 + idx * 8);
    if (((arg0[idx * 8 + 2] >> 8) & 0xFF) == 10) {
        if (func_001DE6D0(arg1) == 1 && func_0015A360(pos, arg1, arg2) >= 0) {
            return pos | 0x10000;
        }
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001E2100(arg1, 0, 0) == 0) {
        if (func_0027B9B0(pos & 0xFFFF) == 1) {
            return pos;
        }
    } else if (func_001DE6D0(arg1) == 1 && func_0015A360(pos, arg1, arg2) >= 0) {
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

s32 func_00159930(s32, s32); /* extern */
s32 func_00159BE0(s32, s32, s32); /* extern */
s32 func_0015A5F0(s32, void *); /* extern */
void func_0015AB10(s32, void *, void *); /* extern */

typedef struct {
    u16 id;
    u16 pad2;
    s16 status;
    u16 pad6;
    u32 code;
} Object_00159760;

void func_00159760(void *arg0) {
    u8 sp40[0x20];
    u8 sp60[0x60];
    Object_00159760 *obj;
    s32 kind;
    s32 pos;
    s32 result;
    u16 id;

    obj = arg0;
    id = obj->id;
    kind = id >> 8;
    pos = func_001E1090(id >> 8, id & 0xFF);
    if (func_0027BBC0(obj->id >> 8, obj->id & 0xFF, 0) == 1) {
        if (func_001DE6D0(kind) == 1) {
            obj->status = 0x50A;
        } else {
            obj->status = 0x5FF;
        }
        return;
    }
    result = func_0015A5F0(kind, sp60);
    if (result < 0) {
        if (func_001DE6D0(kind) == 1) {
            obj->status = 0x60A;
        } else {
            obj->status = 0x6FF;
        }
        obj->code = (u16)obj->code | (func_00159930(obj->id >> 8, obj->id & 0xFF) << 16);
    } else {
        if (result == 0) {
            func_0015AB10(kind, sp40, sp60);
        }
        if ((sp60[0x3E] >> 5) == 0 && func_001E02F0(sp60, 0) > 0x5DC) {
            if (func_001DE6D0(kind) == 1) {
                obj->status = 0x60A;
            } else {
                obj->status = 0x6FF;
            }
            obj->code = (u16)obj->code | (func_00159BE0(kind, pos & 0xFF, pos >> 8) << 16);
        }
        if (func_001DE6D0(kind) == 1) {
            obj->status = 0x60A;
        } else {
            obj->status = 0x6FF;
        }
        obj->code = (u16)obj->code | (func_00159930(obj->id >> 8, obj->id & 0xFF) << 16);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_013", func_00159930);

s32 func_00159BE0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_0015A120();
    u16 buf[0x31];
    s32 i;
    s32 best;
    s32 result;
    u16 *p;
    u8 count;
    s32 dist;

    result = func_001E1090(arg0 == 0 ? 1 : 0, 0);
    count = func_0015A120(result & 0xFF, result >> 8, buf);
    best = 0xE;
    if (count == 0) {
        return -1;
    }
    for (p = buf, i = 0; i < count; p++, i++) {
        if (func_001DF540(*p & 0xFF, *p >> 8) == 0) {
            dist = (((arg1 < (*p & 0xFF)) ? (*p & 0xFF) : arg1) - (((*p & 0xFF) < arg1) ? (*p & 0xFF) : arg1)) +
                   (((arg2 < (*p >> 8)) ? (*p >> 8) : arg2) - (((*p >> 8) < arg2) ? (*p >> 8) : arg2));
            if (dist < best) {
                best = dist;
                result = *p;
            }
        }
    }
    return result;
}

typedef struct {
    u16 card;
    u8 flag;
    u8 pad3;
} Slot_00159D00;

typedef struct {
    u16 low;
    u16 high;
} DataHalves_00159D00;

typedef struct {
    u16 coordinates;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u32 word;
        DataHalves_00159D00 halves;
    } data;
} Entry_00159D00;

void func_00159D00(void *arg0) {
    extern s32 func_0027B200();
    extern void func_0027E770();
    extern s32 func_00159F80();
    Entry_00159D00 *entry = arg0;
    s32 side;
    s32 player;
    s32 pos;
    s32 other;
    s32 otherPos;
    s32 i;
    u8 work[0x70];
    Slot_00159D00 list[22];
    s16 countA;
    s16 countB;

    if (func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF) != 0) {
        func_0027E770(work);
        side = func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF);
        other = (side == 0 ? 1 : 0) << 8;
        pos = func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF);
        otherPos = func_001E1090(other >> 8, other & 0xFF);
        player = func_001DF540(entry->coordinates >> 8, entry->coordinates & 0xFF);
        for (i = 0; i < 22; i++) {
            list[i].card = 0xFFFF;
            list[i].flag = 0xFF;
        }
        if (func_0027B200(entry->coordinates >> 8, entry->coordinates & 0xFF, pos & 0xFF, pos >> 8,
                          other >> 8, other & 0xFF, otherPos & 0xFF, otherPos >> 8, 3) > 0) {
            entry->state = 0x2FF;
            entry->data.word = (other << 16) | entry->data.halves.low;
            return;
        }
        countB = 0;
        countA = 0;
        i = 1;
        while (1) {
            switch (func_00159F80(entry, 0, player, pos & 0xFF, pos >> 8,
                                  func_0024DE70(entry->coordinates >> 8, entry->coordinates & 0xFF) == 0 ? 1 : 0,
                                  (u8)i, func_0015D120(side), list, 0,
                                  &countA, &countB, 3, work)) {
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
                entry->state = 0x3FF;
                entry->data.word = (pos << 16) | entry->data.halves.low;
                return;
            default:
                break;
            }
            i++;
            if (i > 3) {
                break;
            }
        }
        entry->state = 0x6FF;
        entry->data.word = (otherPos << 16) | entry->data.halves.low;
    }
}

void func_00159F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

void func_00159FE0(void *arg0) {
    extern s32 func_001E1030();
    Entry_00159D00 *entry = arg0;
    s32 slot;

    slot = func_00250360(entry->coordinates >> 8, entry->coordinates & 0xFF);
    switch (func_001E1030(entry->coordinates >> 8, entry->coordinates & 0xFF)) {
    case 0x293:
        if (func_001E2100(entry->coordinates >> 8, entry->coordinates & 0xFF, 4) == 0 && func_0027D720(entry, 0) == 1) {
            return;
        }
        break;
    case 0x287:
        if (func_0027D720(entry, 0) == 1) {
            entry->state = 0xBFF;
            return;
        }
        break;
    case 0x28F:
        if (func_0024E910(func_0024CA40(0, 0, slot, 2, 0x34, 0xE)) > 5) {
            entry->state = 0x3FF;
            entry->data.word = (func_001E1090(entry->coordinates >> 8, entry->coordinates & 0xFF) << 16) | entry->data.halves.low;
            return;
        }
        break;
    }
    func_00159D00(entry);
}

void func_0015A120(s32 a0, s32 a1, u16 *buf) {
    s32 i;

    for (i = 0; i < 0x31; i++) {
        buf[i] = 0xFFFF;
    }
    func_0015A180(a0, a1, buf);
    func_0015A320(buf);
}

static inline s32 upper_0015A180(s32 value) {
    if (value >= 7) {
        return 6;
    }
    return value;
}

void func_0015A180(s32 arg0, s32 arg1, u16 *arg2) {
    s32 var_s0;
    s32 var_s1;

    if ((func_0015A2E0((arg1 << 8) | arg0, arg2) != 1) && (func_001E22B0(arg0, arg1) == 9)) {
        arg2[func_0015A320(arg2)] = (arg1 << 8) | arg0;
        for (var_s0 = func_00250860(0, arg0 - 1); var_s0 <= upper_0015A180(arg0 + 1); var_s0++) {
            for (var_s1 = func_00250860(0, arg1 - 1); var_s1 <= upper_0015A180(arg1 + 1); var_s1++) {
                if (((((arg0 < var_s0) ? var_s0 : arg0) - ((var_s0 < arg0) ? var_s0 : arg0)) + (((arg1 < var_s1) ? var_s1 : arg1) - ((var_s1 < arg1) ? var_s1 : arg1))) == 1) {
                    func_0015A180(var_s0, var_s1, arg2);
                }
            }
        }
    }
}

s32 func_0015A2E0(s32 arg0, u16 *arg1) {
    s32 i;

    i = 0;
    do {
        if (arg0 == *arg1) {
            return 1;
        }
        i++;
        arg1++;
    } while (i < 0x31);
    return 0;
}

s32 func_0015A320(u16 *arg0) {
    s32 i;
    u8 count;

    count = 0;
    i = 0;
    do {
        if (*arg0 != 0xFFFF) {
            count++;
        }
        i++;
        arg0++;
    } while (i < 0x31);
    return count;
}
