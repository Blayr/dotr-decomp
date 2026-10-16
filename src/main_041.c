#include "common.h"

void SzDuel_TermTrade(void) {

}

typedef struct {
    s8 axis_0 : 2;
    s8 axis_1 : 2;
    s8 unused : 4;
} MoveFlags_001C2540;

void SzDuel_ActTrade(void) {
    extern s32 SzGame_ActMemCardProc(u8 *, u8 *);
    extern s32 lSzDuel_ActTradeProc(s32);
    extern u16 D_00318118;
    extern u8 D_003181F3;
    extern MoveFlags_001C2540 D_003181F4;
    u8 *state = D_00317490.b;
    u8 *state2;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;

    if (D_003181F3 != 0) {
        ((MoveFlags_001C2540 *)(state + 0xD64))->axis_0 = 1;
    }
    var_v1 = (s32)((MoveFlags_001C2540 *)(state + 0xD64))->axis_0 << 9;
    var_v0 = *(u16 *)(state + 0xC86);
    var_v1 = var_v0 + var_v1;
    var_v0 = var_v1 > 0 ? var_v1 : 0;
    if (var_v0 < 0x8000) {
        var_v1 = var_v1 > 0 ? var_v1 : 0;
    } else {
        var_v1 = 0x8000;
    }
    *(u16 *)(state + 0xC86) = (u16)var_v1;
    if ((*(u16 *)(state + 0xC86) == 0) || ((s32)*(u16 *)(state + 0xC86) >= 0x8000)) {
        ((MoveFlags_001C2540 *)(state + 0xD64))->axis_0 = -((MoveFlags_001C2540 *)(state + 0xD64))->axis_0;
    }
    state2 = D_00317490.b;
    temp_v1 = (s32)D_003181F4.axis_1 << 0xB;
    var_v0_2 = D_00318118 + temp_v1;
    if (var_v0_2 > 0) {
        var_v0_2 = *(u16 *)(state2 + 0xC88) + temp_v1;
    } else {
        var_v0_2 = 0;
    }
    if (var_v0_2 < 0x8000) {
        var_v0_2 = *(u16 *)(state2 + 0xC88) + temp_v1;
        var_v0_2 = var_v0_2 > 0 ? var_v0_2 : 0;
    } else {
        var_v0_2 = 0x8000;
    }
    *(u16 *)(state2 + 0xC88) = (u16)var_v0_2;
    if ((*(u16 *)(state2 + 0xC88) == 0) || ((s32)*(u16 *)(state2 + 0xC88) >= 0x8000)) {
        ((MoveFlags_001C2540 *)(state2 + 0xD64))->axis_1 = -((MoveFlags_001C2540 *)(state2 + 0xD64))->axis_1;
    }
    if ((SzGame_ActMemCardProc(state2, state) < 0) && (lSzDuel_ActTradeProc(0) == 0)) {
        lSzDuel_ActTradeProc(1);
    }
}

static inline s32 count_001C2720(s32 player) {
    u8 *q;
    s32 sum;
    u8 *b = D_00317490.b;
    s32 i;

    if (player) {
        q = *(u8 **)(b + 0x6E4);
    } else {
        q = *(u8 **)(b + 0x6E0);
    }
    sum = 0;
    for (i = 0; i < 0x356; i++) {
        sum += *q++;
    }
    return sum;
}

s32 lSzDuel_ActTradeProc(s32 player) {
    u8 *base;
    s32 limit;
    s32 id;
    s32 old;
    s32 oldCursor;
    u16 *list;
    s32 fast;
    s32 delta;
    u16 *timer;
    u8 *counts;
    u16 *scroll;
    u8 *p;
    s32 before;
    u8 *slot;
    u8 *cursor;
    u8 *digits;
    u8 *state;
    u16 *total;

    base = D_00317490.b;
    if (player) {
        list = *(u16 **)(base + 0x6DC);
    } else {
        list = *(u16 **)(base + 0x6D8);
    }
    if (player) {
        counts = *(u8 **)(base + 0x6E4);
    } else {
        counts = *(u8 **)(base + 0x6E0);
    }
    if (player) {
        digits = base + 0xCB9;
    } else {
        digits = base + 0xCB6;
    }
    if (player) {
        timer = (u16 *)(base + 0xC98);
    } else {
        timer = (u16 *)(base + 0xC96);
    }
    if (player) {
        scroll = (u16 *)(base + 0xC8E);
    } else {
        scroll = (u16 *)(base + 0xC8A);
    }
    if (player) {
        total = (u16 *)(base + 0xC90);
    } else {
        total = (u16 *)(base + 0xC8C);
    }
    if (player) {
        cursor = base + 0xD5F;
    } else {
        cursor = base + 0xD5E;
    }
    state = (u8 *)(player + (s32)base) + 0xCBE;
    if (*state < 4) {
        if (SzPad_Check(player, 1, 0xFFFF)) {
            *timer = 0x5A;
        } else if (*timer != 0) {
            (*timer)--;
        }
    }
    switch (*state) {
    case 0: {
        s16 *slide = (s16 *)((player << 1) + (s32)base + 0xC92);
        *slide = (*slide - 0x2D > 0) ? *slide - 0x2D : 0;
        if (*slide <= 0) {
            *state = 1;
        }
        break;
    }
    case 1:
        id = list[*scroll + *cursor];
        fast = SzPad_Check(player, 1, 0x100) ? 1 : 0;
        oldCursor = *cursor;
        delta = 0;
        if (*total != 0) {
            if (SzPad_Check(player, 2, 0xC)) {
                if (SzPad_Check(player, 2, 4)) {
                    delta = -5;
                } else {
                    delta = 5;
                }
            } else if (SzPad_Check(player, 2, 0x5000)) {
                if (SzPad_Check(player, 2, 0x1000)) {
                    if (*cursor > 0) {
                        (*cursor)--;
                    } else {
                        delta = -1;
                    }
                } else if (*cursor < 4) {
                    (*cursor)++;
                } else {
                    delta = 1;
                }
            }
            if (*cursor != oldCursor) {
                SzSound_PlaySE(0, 3);
                break;
            }
            if (delta == 0 && SzPad_IsAnalog(player)) {
                s32 stick = SzPad_GetAnalogInfo(player, 3) - 0x80;
                s32 size;
                if (stick >= 0) {
                    size = stick;
                } else {
                    size = -stick;
                }
                if (size > 0x30) {
                    if (stick > 0) {
                        stick -= 0x30;
                    } else {
                        stick += 0x30;
                    }
                    delta = (stick * 15) >> 7;
                }
            }
            if (delta != 0) {
                s32 max;
                s32 next;
                u16 prev;
                if (*total - 5 > 0) {
                    max = *total - 5;
                } else {
                    max = 0;
                }
                prev = *scroll;
                next = prev + delta;
                next = ((next > 0 ? next : 0) < max) ? (next > 0 ? next : 0) : max;
                *scroll = next;
                if (*scroll != prev) {
                    SzSound_PlaySE(0, 3);
                }
                *timer = 0x5A;
                break;
            }
            if (SzPad_Check(player, 2, 0xC0)) {
                if (id == 999 || base[player + 0xCC0] == 2) {
                    SzSound_PlaySE(0, 6);
                    break;
                }
                limit = SzData_GetBagCount(player, id, 3);
                slot = counts + id;
                before = *slot;
                if (SzPad_Check(player, 2, (u16)(player ? 0x80 : 0x40))) {
                    if (*slot < limit) {
                        (*slot)++;
                    }
                } else if (*slot > 0) {
                    (*slot)--;
                }
                if (before == *slot) {
                    SzSound_PlaySE(0, 6);
                    break;
                }
                SzSound_PlaySE(0, 3);
                break;
            }
            if (SzPad_Check(player, 0, 0x10)) {
                if (id == 999) {
                    SzSound_PlaySE(0, 6);
                    break;
                }
                *state = 2;
                SzSound_PlaySE(0, 0x10);
                break;
            }
        }
        if (SzPad_Check(player, 0, 0x600)) {
            if (SzPad_Check(player, 0, 0x200)) {
                base[player + 0xCC0] = (base[player + 0xCC0] + 2) % 3;
            } else {
                base[player + 0xCC0] = (base[player + 0xCC0] + 4) % 3;
            }
            lSzDuel_SetupTrade(player);
            *scroll = 0;
            SzSound_PlaySE(0, 0x13);
            break;
        }
        if (SzPad_Check(player, 0, 0x800)) {
            if (base[(player ^ 1) + 0xCBE] == 4) {
                if (count_001C2720(player) > 0 || count_001C2720(player ^ 1) > 0) {
                    SzSound_PlaySE(0, 4);
                    base[0xCBE] = 6;
                    base[0xCBF] = 6;
                    base[0xD36] = 0;
                    break;
                }
                SzSound_PlaySE(0, 6);
                break;
            }
            SzSound_PlaySE(0, 4);
            *state = 4;
            break;
        }
        if (SzPad_Check(player, 2, 3)) {
            p = digits + fast;
            old = *p;
            if (SzPad_Check(player, 2, 1)) {
                *p = (*p + 9) % 10;
            } else {
                *p = (*p + 11) % 10;
            }
            if (old != *p) {
                lSzDuel_SortTrade(player);
                SzSound_PlaySE(0, 0x13);
            }
            break;
        }
        if (SzPad_Check(player, 0, 0x20)) {
            if (base[(player ^ 1) + 0xCBE] == 1) {
                SzSound_PlaySE(0, 5);
                base[0xCBE] = 5;
                base[0xCBF] = 5;
                base[0xD36] = 0;
            } else {
                SzSound_PlaySE(0, 6);
            }
        }
        break;
    case 2: {
        s16 *slide = (s16 *)((player << 1) + (s32)base + 0xC92);
        *slide = (*slide + 0x2D < 0x140) ? *slide + 0x2D : 0x140;
        if (*slide >= 0x140) {
            *state = 3;
        }
        break;
    }
    case 3:
        if (SzPad_Check(player, 2, 0x5000)) {
            p = (u8 *)(player + (u32)base) + 0xCBC;
            before = *p;
            if (SzPad_Check(player, 2, 0x1000)) {
                *p = (*p + 3) % 4;
            } else {
                *p = (*p + 5) % 4;
            }
            if (*p != before) {
                SzSound_PlaySE(0, 0x13);
            }
            break;
        }
        if (SzPad_Check(player, 0, 0x30)) {
            *state = 0;
            SzSound_PlaySE(0, 0x11);
        }
        break;
    case 4:
        if (SzPad_Check(player, 0, 0x20)) {
            SzSound_PlaySE(0, 5);
            *state = 1;
        }
        break;
    case 5:
        if (SzPad_Check(player, 0, 0xA000)) {
            old = base[0xD36];
            if (SzPad_Check(player, 0, 0x8000)) {
                base[0xD36] = 1;
            } else {
                base[0xD36] = 0;
            }
            if (base[0xD36] != old) {
                SzSound_PlaySE(0, 3);
            }
            break;
        }
        if (SzPad_Check(player, 0, 0xC0)) {
            SzSound_PlaySE(0, 4);
            if (base[0xD36] != 0) {
                SzGame_Pop();
                break;
            }
            base[0xCBE] = 1;
            base[0xCBF] = 1;
            break;
        }
        if (SzPad_Check(player, 0, 0x20)) {
            SzSound_PlaySE(0, 5);
            base[0xCBE] = 1;
            base[0xCBF] = 1;
        }
        break;
    case 6:
        if (SzPad_Check(player, 0, 0xA000)) {
            old = base[0xD36];
            if (SzPad_Check(player, 0, 0x8000)) {
                base[0xD36] = 1;
            } else {
                base[0xD36] = 0;
            }
            if (base[0xD36] != old) {
                SzSound_PlaySE(0, 3);
            }
            break;
        }
        if (SzPad_Check(player, 0, 0xC0)) {
            SzSound_PlaySE(0, 4);
            if (base[0xD36] != 0) {
                if (lSzDuel_TradeDo() > 0) {
                    base[0xCBE] = 8;
                    base[0xCBF] = 8;
                    break;
                }
                base[0xCBE] = 7;
                base[0xCBF] = 7;
                SzGame_InitMemCardProc(5);
                return 1;
            }
            *state = 1;
            base[(player ^ 1) + 0xCBE] = 4;
            break;
        }
        if (SzPad_Check(player, 0, 0x20)) {
            SzSound_PlaySE(0, 5);
            *state = 1;
            base[(player ^ 1) + 0xCBE] = 4;
        }
        break;
    case 7:
        SzGame_Pop();
        break;
    case 8:
        if (SzPad_Check(player, 0, 0xF0)) {
            SzSound_PlaySE(0, 4);
            SzGame_Pop();
        }
        break;
    }
    return 0;
}

typedef struct {
    u8 padding[0x6E0];
    u8 *first;
    u8 *second;
} State_001C32B0;


s32 lSzDuel_TradeDo(void) {
    State_001C32B0 *state = (State_001C32B0 *)D_00317490.b;
    s32 var_s1;
    s32 var_a1;
    s32 var_a2;
    u8 *temp_a3;
    u8 *temp_t0;
    u8 temp_a0;
    u8 temp_a1;

    var_s1 = 0;
    var_a2 = 0;
    do {
        temp_a3 = state->first + var_a2;
        temp_a1 = *temp_a3;
        if (temp_a1 != 0) {
            temp_t0 = state->second + var_a2;
            temp_a0 = *temp_t0;
            if (temp_a0 != 0) {
                if ((temp_a1 & 0xFF) > (temp_a0 & 0xFF)) {
                    *temp_a3 = temp_a1 - temp_a0;
                    state->second[var_a2] = 0;
                } else {
                    *temp_t0 = temp_a0 - temp_a1;
                    state->first[var_a2] = 0;
                }
            }
        }
        var_a2 += 1;
    } while (var_a2 < 0x356);
    lSzDuel_TradeDoSide(0);
    lSzDuel_TradeDoSide(1);
    for (var_a1 = 0; var_a1 < 0x356; var_a1++) {
        var_s1 += state->first[var_a1];
        var_s1 += state->second[var_a1];
    }
    return var_s1;
}

typedef struct {
    u32 id : 31;
    u32 flag : 1;
    u32 position : 30;
    u32 state : 2;
} Entry_001C33A0;

typedef struct {
    u8 padding[0x6E0];
    u8 *counts0;
    u8 *counts1;
} State_001C33A0;


void lSzDuel_TradeDoSide(s32 player) {
    s32 id;
    s32 slot;
    Entry_001C33A0 *entry;
    u8 *counts;
    u8 *count;
    s32 opponent;
    State_001C33A0 *state;

    state = (State_001C33A0 *)D_00317490.b;
    if (player != 0) {
        counts = state->counts1;
    } else {
        counts = state->counts0;
    }
    id = 0;
    opponent = player ^ 1;
    do {
        count = counts + id;
        while (*count != 0) {
            if (SzData_GetBagCount(opponent, id, -1) >= 9) {
                break;
            }
            slot = 0;
            do {
                entry = SzData_GetCardInfo(player, id, slot);
                if (entry->id != 0 && entry->state == 3 &&
                    SzData_CheckDup(opponent, entry->id, entry->position, id) == 0) {
                    break;
                }
                slot++;
            } while (slot < 9);
            if (slot >= 9) {
                break;
            }
            SzData_AddBag2(opponent, entry->id, entry->position, id);
            SzData_ClearCardInfo(entry);
            (*count)--;
        }
        id++;
    } while (id < 0x356);
}

typedef struct {
    u8 pad_000[0x6D8];
    s32 values[2];
    u8 pad_6E0[0x67C];
    s8 selection;
} State_001C3520;

void lSzDuel_SortTrade(s32 arg0) {
    State_001C3520 *state = (State_001C3520 *)D_00317490.b;
    s32 var_a1;
    void (*var_a3)(void);

    if (arg0 != 0) {
        var_a1 = state->values[1];
    } else {
        var_a1 = state->values[0];
    }
    if (arg0 != 0) {
        var_a3 = lSzDuel_SortFunc2;
    } else {
        var_a3 = lSzDuel_SortFunc1;
    }
    state->selection = arg0;
    func_00199BC0(var_a1, 0x356, 2, var_a3);
}

void SzDuel_DrawTrade(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawTrade_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct State_001C35A0 {
    u8 pad0[0x6D8];
    u16 *values0;
    u16 *values1;
    u8 pad1[0x5AA];
    u16 index0;
    u16 condition0;
    u16 index1;
    u16 condition1;
    s16 amount0;
    s16 amount1;
    u8 pad2[0x28];
    u8 mode0;
    u8 mode1;
    u8 pad3[0x9C];
    u8 side;
    u8 pad4;
    u8 selection0;
    u8 selection1;
} State_001C35A0;

s32 lSzDuel_DrawTrade_Bag_Pipe(s32, s32, s32, s32);
s32 lSzDuel_DrawTrade_Ready_Pipe(s32, s32, s32);
s32 func_001BDAF0(s32, s32, s32, s32, s32, s32, s32, s32);
extern u16 D_0031811C;

s32 SzDuel_DrawTrade_Pipe(s32 arg0) {
    State_001C35A0 *state = (State_001C35A0 *)D_00317490.b;
    s32 result;
    s32 next;
    extern s32 lSzDuel_DrawTrade_Title_Pipe();
    extern s32 lSzDuel_Draw_Fade_Pipe();
    extern s32 lSzDuel_DrawTrade_Exit_Pipe();
    extern s32 lSzDuel_DrawTrade_Do_Pipe();
    extern s32 lSzDuel_DrawTrade_Notice_Pipe();

    next = lSzDuel_DrawTrade_Title_Pipe(lSzDuel_DrawTrade_Base_Pipe(SzDuel_StartWindowSessionWithPalette_Pipe(arg0, 2)), 0, 0);
    next = lSzDuel_DrawTrade_Bag_Pipe(next, 0, 0, 0);
    if (D_0031811C != 0) {
        next = lSzDuel_DrawTrade_Cursor_Pipe(next, 0, 0, 0, state->selection0);
    }
    if (state->amount0 != 0) {
        next = lSzDuel_Draw_Fade_Pipe(next, 0, 0, 320, 448,
                            (u8)(((s16)state->amount0 << 6) / 320));
        state->side = 0;
        next = func_001BDAF0(next, state->values0[state->index0 + state->selection0],
                            state->amount0, 0, 0, 1, 1, 0);
    }
    if (!(state->mode0 != 4 && state->mode0 != 6 && state->mode0 != 7)) {
        next = lSzDuel_Draw_Fade_Pipe(next, 0, 0, 320, 448, 64);
        next = lSzDuel_DrawTrade_Ready_Pipe(next, -160, 0);
    }
    result = lSzDuel_DrawTrade_Bag_Pipe(next, 1, 0, 0);
    if (state->condition1 != 0) {
        result = lSzDuel_DrawTrade_Cursor_Pipe(result, 1, 0, 0, state->selection1);
    }
    if (state->amount1 != 0) {
        result = lSzDuel_Draw_Fade_Pipe(result, 320, 0, 320, 448,
                              (u8)(((s16)state->amount1 << 6) / 320));
        state->side = 1;
        result = func_001BDAF0(result, state->values1[state->index1 + state->selection1],
                              -state->amount1, 0, 1, 1, 1, 0);
    }
    if (!(state->mode1 != 4 && state->mode1 != 6 && state->mode1 != 7)) {
        result = lSzDuel_Draw_Fade_Pipe(result, 320, 0, 320, 448, 64);
        result = lSzDuel_DrawTrade_Ready_Pipe(result, 160, 0);
    }
    if (state->mode0 == 5 || state->mode1 == 5) {
        result = lSzDuel_DrawTrade_Exit_Pipe(result, 0, 0);
    }
    if (state->mode0 == 6 || state->mode1 == 6) {
        result = lSzDuel_DrawTrade_Do_Pipe(result, 0, 0);
    }
    if (state->mode0 == 8 || state->mode1 == 8) {
        result = lSzDuel_DrawTrade_Notice_Pipe(result, 0, 0);
    }
    SzMsg_Free(0);
    return result;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C38E0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C38E0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C38E0;

typedef struct {
    Color_001C38E0 color;
    Vertex_001C38E0 xyz;
} Point_001C38E0;

typedef struct {
    u64 tag[2];
    Point_001C38E0 points[4];
    u64 end;
} Packet_001C38E0;

typedef struct {
    u8 b, g, r, a;
} Source_001C38E0;

static inline void set_color_001C38E0(Color_001C38E0 *a, Color_001C38E0 *b,
                                      Source_001C38E0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

static inline void set_xyz_001C38E0(Vertex_001C38E0 *v, s32 x, s32 y) {
    v->x = (x + 0x6C0) << 4;
    v->y = (y + 0x720) << 4;
    v->z = D_003180E8;
    v->fog = 0;
}

s32 lSzDuel_DrawTrade_Base_Pipe(s32 arg0) {
    extern u8 D_002BE858[];
    Source_001C38E0 *colors = (Source_001C38E0 *)D_002BE858;
    s32 width = 0x140;
    s32 height = 0x1C0;
    Packet_001C38E0 packet __attribute__((aligned(8)));

    ((Tag_001C38E0 *)packet.tag)->flags = 0x14;
    ((Tag_001C38E0 *)packet.tag)->count = 8;
    ((Tag_001C38E0 *)packet.tag)->registers = 0x41414141;
    ((Tag_001C38E0 *)packet.tag)->padding = 0;
    set_color_001C38E0(&packet.points[0].color, &packet.points[2].color, &colors[0]);
    set_color_001C38E0(&packet.points[1].color, &packet.points[3].color, &colors[1]);
    set_xyz_001C38E0(&packet.points[0].xyz, 0, 0);
    set_xyz_001C38E0(&packet.points[1].xyz, width, 0);
    set_xyz_001C38E0(&packet.points[2].xyz, 0, height);
    set_xyz_001C38E0(&packet.points[3].xyz, width, height);
    arg0 = ExSortPrim_Pipe(arg0, (s32)packet.tag, 0, 0);
    set_color_001C38E0(&packet.points[0].color, &packet.points[2].color, &colors[1]);
    set_color_001C38E0(&packet.points[1].color, &packet.points[3].color, &colors[0]);
    set_xyz_001C38E0(&packet.points[0].xyz, width, 0);
    set_xyz_001C38E0(&packet.points[1].xyz, width * 2, 0);
    set_xyz_001C38E0(&packet.points[2].xyz, width, height);
    set_xyz_001C38E0(&packet.points[3].xyz, width * 2, height);
    return ExSortPrim_Pipe(arg0, (s32)packet.tag, 0, 0);
}

void lSzDuel_DrawTrade_Title_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32)&D_002BF00B;
    s32 x = arg1 + 0xE0;
    s32 y = arg2 + 0x20;
    s32 element;

    arg0 = lSzDuel_DrawWindow_Base_Pipe(arg0, x, y, 6, 1);
    element = lSzDuel_DrawWindow_Frame_Pipe(arg0, -1, 0x73, 4, x, y, 0x15, 2, 1);
    SzDuel_DrawWindow_Font_Pipe(element, arg1 + 0x140, arg2 + 0x27, 2, 3,
                  func_0019BEF0((const char *)text), (s8 *)text, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_041", lSzDuel_DrawTrade_Bag_Pipe);

INCLUDE_ASM("asm/nonmatchings/main_041", lSzDuel_DrawTrade_Card_Pipe);

s32 lSzDuel_DrawTrade_Cursor_Pipe(s32 id, s32 player, s32 arg2, s32 arg3, s32 arg4) {
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern char D_002BF030[];
    extern char D_002BEFEC[];
    extern s32 D_00290A62;
    extern s32 D_00290A58;
    extern s32 D_00290A4E;
    extern s32 D_00290A76;
    u8 *state = D_00317490.b;
    s8 *text1 = D_002BF030 + 3;
    s8 *text2 = D_002BEFEC;
    s8 *text4 = (s8 *)&D_002BF00B;
    s32 hint = 0;
    u16 busy;
    s32 x;
    s32 y;
    s32 sx;
    s32 sy;
    s32 px;
    s32 py;

    x = arg2 + 8 + (player != 0 ? 0x140 : 0);
    y = arg3 + 0x70 + arg4 * 0x36;
    sx = x + 0x6C0;
    sy = y + 0x720;
    busy = (player != 0) ? *(u16 *)(state + 0xC98) : *(u16 *)(state + 0xC96);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, 4, 6, x - 2, y - 2, -0x130, -0x36, 1);
    if (busy != 0) {
        return id;
    }
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xD, -1, 7, x, y + 0x36, -0x130, -0x14, 1);
    if (state[player + 0xCC0] < 2) {
        px = sx + 5;
        py = sy + 0x38;
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, px + 0x11, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x2C;
        py = y + 0x3B;
        id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text1), text1,
                           hint != 0 ? (s32)D_002BE944 : 0);
    }
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A4E, sx + 0x6B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    px = x + 0x81;
    py = y + 0x3B;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text2), text2,
                       hint != 0 ? (s32)D_002BE944 : 0);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A76, sx + 0xC9, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    px = x + 0xDF;
    py = y + 0x3B;
    return SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

INCLUDE_ASM("asm/nonmatchings/main_041", lSzDuel_DrawTrade_Ready_Pipe);

void lSzDuel_DrawTrade_Exit_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 lSzDuel_DrawDialog_Window_Pipe(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawX_Pipe(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    u8 *state = D_00317490.b;
    s32 text = (s32)D_002BEF98;
    s8 *text2 = D_002BEF6F;
    s8 *text3 = D_002BEF73;
    s32 id;
    s32 *size;

    arg0 = lSzDuel_DrawDialog_Window_Pipe(arg0, 2, -1, 0x7E, arg1 + 0x140, arg2 + 0x83, 0x140, 0xBA,
                         func_0019BEF0((char *)text), text, 0);
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, 0x7F, 0, 0x16));
    size = SzMsg_GetInfo(1);
    id = SzMsg_DrawX_Pipe(id, 1, arg1 + 0x140 - (size[3] >> 1), arg2 + 0x119 - (size[4] + 12), 0,
                       SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    id = SzDuel_DrawWindow_Font_Pipe(id, arg1 + 0xF0, arg2 + 0x119, 2, 3, func_0019BEF0((char *)text2), text2,
                       D_003181C6 != 0 ? 0 : (s32)D_002BE944);
    SzDuel_DrawWindow_Font_Pipe(id, arg1 + 0x190, arg2 + 0x119, 2, 3, func_0019BEF0((char *)text3), text3,
                  state[0xD36] != 0 ? (s32)D_002BE944 : 0);
}

void lSzDuel_DrawTrade_Do_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 lSzDuel_DrawDialog_Window_Pipe(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawX_Pipe(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    u8 *state = D_00317490.b;
    s32 text = (s32)&D_002BF00B;
    s8 *text2 = D_002BEF6F;
    s8 *text3 = D_002BEF73;
    s32 id;
    s32 *size;

    arg0 = lSzDuel_DrawDialog_Window_Pipe(arg0, 2, -1, 0x7D, arg1 + 0x140, arg2 + 0x8E, 0x140, 0xA4,
                         func_0019BEF0((char *)text), text, 0);
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, 0x7F, 0, 0x16));
    size = SzMsg_GetInfo(1);
    id = SzMsg_DrawX_Pipe(id, 1, arg1 + 0x140 - (size[3] >> 1), arg2 + 0x10E - (size[4] + 12), 0,
                       SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    id = SzDuel_DrawWindow_Font_Pipe(id, arg1 + 0xF0, arg2 + 0x10E, 2, 3, func_0019BEF0((char *)text2), text2,
                       D_003181C6 != 0 ? 0 : (s32)D_002BE944);
    SzDuel_DrawWindow_Font_Pipe(id, arg1 + 0x190, arg2 + 0x10E, 2, 3, func_0019BEF0((char *)text3), text3,
                  state[0xD36] != 0 ? (s32)D_002BE944 : 0);
}

void lSzDuel_DrawTrade_Notice_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32) &D_002BF040;
    s32 length = func_0019BEF0((const char *) text);

    lSzDuel_DrawDialog_Window_Pipe(arg0, 2, -1, 0x80, arg1 + 0x140, arg2 + 0xA3,
                  0x140, 0x7A, length, text, 1);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrMiscLargeEntry {
    int unknown_words[16360];
};
struct DotrMiscLargeEntry *SzData_GetData_b(int value);
struct DotrMiscControlPair {
    unsigned short top;
    unsigned short count;
};
struct DotrMiscControlLists {
    unsigned char unknown_000[0x6d4];
    void *table;
    short *lists[2];
    unsigned char *counts[2];
    unsigned char unknown_6e8[0x5a2];
    struct DotrMiscControlPair pairs[2];
    short unknown_c92;
    short unknown_c94;
    short unknown_c96;
    short unknown_c98;
    unsigned char unknown_c9a[0x1c];
    unsigned char unknown_cb6[6];
    unsigned char unknown_cbc[2];
    unsigned char unknown_cbe[2];
    unsigned char modes[2];
    unsigned char unknown_cc2[0x9a];
    unsigned char side;         
    unsigned char unknown_d5d;
    unsigned char rows[2];
};
extern struct DotrMiscControlLists D_00317490_1c5d70;
struct DotrCustomDuelSide {
    unsigned char unknown_000[0x33a];
    unsigned short lp;
    unsigned char deck;
    unsigned char unknown_33d[5];
    unsigned char n;
    unsigned char unknown_343[0xd];
};
struct DotrCustomDuelControl {
    struct DotrCustomDuelSide side[2];
    unsigned char unknown_6a0[0x692];
    unsigned char a;
    unsigned char b;
};
struct DotrCustomDuel {
    unsigned char f0[2];
    unsigned char f2[2];
    unsigned char deck[2];
    unsigned char f6[2];
    unsigned char f8[2];
    unsigned char fa[2];
    unsigned char fc[2];
    unsigned char fe[2];
    unsigned short lp[2];
    unsigned short lp2[2];
    unsigned short list[56];
    unsigned char mode;
    unsigned char last;
    unsigned char count;
    unsigned char f8b;
    unsigned char f8c;
    unsigned char f8d;
};
#define DOTR_CUSTOM_DUEL ((struct DotrCustomDuel *)0xa9c000)
struct DotrCustomDuelFlags {
    unsigned char unknown_0000[0xff9c];
    unsigned int b0 : 5;
    unsigned int b5 : 1;
};
extern unsigned char *RhMem_CopyMemory_b(unsigned char *destination, unsigned char *source, int count);

void func_001C5D70(int mode)
{
    struct DotrCustomDuelControl *c = (struct DotrCustomDuelControl *)&D_00317490_1c5d70;
    unsigned short *p = DOTR_CUSTOM_DUEL->list;
    int deck = 101;
    int i;
    struct DotrMiscLargeEntry *src;
    struct DotrMiscLargeEntry *dst;

    if (mode >= 0) {
        DOTR_CUSTOM_DUEL->mode = mode;
    }
    switch (DOTR_CUSTOM_DUEL->mode) {
    case 0:
        break;
    case 1:
        src = SzData_GetData_b(0);
        dst = SzData_GetData_b(1);
        RhMem_CopyMemory_b((unsigned char *)dst, (unsigned char *)src, 0xffa0);
        ((struct DotrCustomDuelFlags *)dst)->b5 = 0;
        deck = 22;
        break;
    case 2:
        SzData_SetupFromConstDeck(1, 50);
        deck = 25;
        break;
    case 3:
        SzData_SetupFromConstDeck(1, 49);
        deck = 24;
        break;
    case 4:
        SzData_SetupFromConstDeck(1, 48);
        deck = 23;
        break;
    }
    SzText_Free(0, 1);
    SzText_Free(0, 0);
    SzText_Free(1, -1);
    if (mode >= 0) {
        c->side[0].deck = 100;
        c->side[0].lp = 4000;
        c->side[0].n = 3;
        c->side[1].deck = deck;
        c->side[1].lp = 4000;
        c->side[1].n = 3;
        DOTR_CUSTOM_DUEL->f0[0] = 0;
        DOTR_CUSTOM_DUEL->f2[0] = 0;
        DOTR_CUSTOM_DUEL->deck[0] = SzData_GetCurrentDeck(0);
        DOTR_CUSTOM_DUEL->lp[0] = 4000;
        DOTR_CUSTOM_DUEL->lp2[0] = 4000;
        DOTR_CUSTOM_DUEL->f6[0] = 3;
        DOTR_CUSTOM_DUEL->f8[0] = 1;
        DOTR_CUSTOM_DUEL->fa[0] = 1;
        DOTR_CUSTOM_DUEL->fc[0] = 1;
        DOTR_CUSTOM_DUEL->fe[0] = 1;
        DOTR_CUSTOM_DUEL->f0[1] = 0;
        DOTR_CUSTOM_DUEL->f2[1] = 0;
        DOTR_CUSTOM_DUEL->deck[1] = SzData_GetCurrentDeck(1);
        DOTR_CUSTOM_DUEL->lp[1] = 4000;
        DOTR_CUSTOM_DUEL->lp2[1] = 4000;
        DOTR_CUSTOM_DUEL->f6[1] = 3;
        DOTR_CUSTOM_DUEL->f8[1] = 1;
        DOTR_CUSTOM_DUEL->fa[1] = 1;
        DOTR_CUSTOM_DUEL->fc[1] = 1;
        DOTR_CUSTOM_DUEL->fe[1] = 1;
        DOTR_CUSTOM_DUEL->f8c = 0;
        DOTR_CUSTOM_DUEL->f8d = 0;
        DOTR_CUSTOM_DUEL->count = 24;
        for (i = 0; i < 24; i++) {
            *p++ = i | 0x200;
        }
        if (SzData_GetMapEditFlag(0)) {
            DOTR_CUSTOM_DUEL->count += 5;
            for (i = 0; i < 5; i++) {
                *p++ = i;
            }
            DOTR_CUSTOM_DUEL->f8d = 5;
            DOTR_CUSTOM_DUEL->f8c = DOTR_CUSTOM_DUEL->f8d - 2;
        }
        if (SzData_GetMapEditFlag(1)) {
            DOTR_CUSTOM_DUEL->count += 5;
            for (i = 0; i < 5; i++) {
                *p++ = i | 0x100;
            }
        }
        DOTR_CUSTOM_DUEL->last = DOTR_CUSTOM_DUEL->count - 2;
        DOTR_CUSTOM_DUEL->f8b = 0;
    } else {
        c->side[0].deck = 100;
        c->side[0].lp = DOTR_CUSTOM_DUEL->lp2[0];
        c->side[1].deck = deck;
        c->side[1].lp = DOTR_CUSTOM_DUEL->lp2[1];
    }
    SzText_LoadMerge(4, 1);
    SzText_LoadMerge(7, 1);
    c->a = 0;
    c->b = 0;
}
#undef DOTR_CUSTOM_DUEL


void SzDuel_TermCustomDuel(void) {

}

s32 SzDuel_ActCustomDuel(void) {
    s32 result = lSzDuel_ActCustomDuelProc(0);

    if (result != 0 || *(u8 *)0xA9C088 != 0) {
        return result;
    }
    return lSzDuel_ActCustomDuelProc(1);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrCustomProcControlSide {
    unsigned char unknown_000[0x33c];
    unsigned char deck;                 
    unsigned char unknown_33d[0x13];
};
struct DotrCustomProcControl {
    struct DotrCustomProcControlSide side[2];
    unsigned char unknown_6a0[0x692];
    unsigned char reload[2];            
};
extern signed char D_00317490_b[];
struct DotrCustomProc {
    unsigned char cur[2];               
    unsigned char menu[2];              
    unsigned char deck[2];              
    unsigned char charge[2];            
    unsigned char f8[2];                
    unsigned char fa[2];                
    unsigned char fc[2];                
    unsigned char fe[2];                
    short lp[2];                        
    short lp2[2];                       
    unsigned short list[56];            
    unsigned char mode;                 
    unsigned char last;                 
    unsigned char count;                
    unsigned char f8b;                  
    unsigned char map;                  
    unsigned char maps;                 
    unsigned char yes;                  
};
struct DotrCustomProcAt {
    unsigned char pad[0xa9c000];
    unsigned char cur;
    unsigned char pad01;
    unsigned char menu;
    unsigned char pad03;
    unsigned char deck;
    unsigned char pad05;
    unsigned char charge;
    unsigned char pad07;
    unsigned char f8;
    unsigned char pad09;
    unsigned char fa;
    unsigned char pad0b;
    unsigned char fc;
    unsigned char pad0d;
    unsigned char fe;
    unsigned char pad0f;
    short lp;
    short pad12;
    short lp2;
};
#define DOTR_CUSTOM_PROC ((struct DotrCustomProc *)0xa9c000)
#define DOTR_CUSTOM_PROC_BYTES_AT(i) ((struct DotrCustomProcAt *)(i))
#define DOTR_CUSTOM_PROC_WORDS_AT(i) ((struct DotrCustomProcAt *)((i) * 2))
struct DotrCustomProcSave {
    unsigned char pad[0xfea3];
    unsigned char map[1][7][7];
};
extern unsigned char D_002BEAC0_1c6170[2][2][5];
extern void func_00215920_b(int side, int deck);
extern void func_002029B0_b(int a, int b);
extern int func_001DE690_b(int index);
extern void func_001DE6B0_b(int index, int value);
extern int func_001E2220_b(int x, int y, int value);
#define MENU(i) (DOTR_CUSTOM_PROC_BYTES_AT(i)->menu)
#define LP(i) (DOTR_CUSTOM_PROC_WORDS_AT(i)->lp)
#define LP2(i) (DOTR_CUSTOM_PROC_WORDS_AT(i)->lp2)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(v, lo, hi) MIN(MAX(v, lo), hi)
static inline int DotrCustomProcIsDeckReady(int side, int list)
{
    int count = SzData_GetDeckCount(side, list);
    int value = SzData_GetLeader(side, list);

    if (count >= 40) {
        if (value == 999) {
            if (!list && !count) {
            }
        } else {
            return 1;
        }
    }
    return 0;
}

int lSzDuel_ActCustomDuelProc(int side)
{
    struct DotrCustomProcControl *c = (struct DotrCustomProcControl *)D_00317490_b;
    int deck = SzData_GetCurrentDeck(side);
    unsigned char *reload = side ? &c->reload[1] : &c->reload[0];
    


    struct DotrCustomProcAt *w = (struct DotrCustomProcAt *)side;



    int m;
    int old;
    int x;
    int y;
    int v;
    int row;

    if (SzFile_InqRequestEx() == 0 && *reload) {
        SzText_LoadMerge(side + 5, 1);
        *reload = 0;
        if (DOTR_CUSTOM_PROC->mode == 1) {
            SzText_LoadMerge(6, 1);
        }
    }
    

    m = w->menu;
    if (m & 0xf0) {
    switch (m & 0xf0) {
    case 0x10:
        switch (m & 0xf) {
        case 0:
            if (SzPad_Check(side, 2, 0xa000) || SzPad_Check(side, 2, 12)) {
                if (SzPad_Check(side, 2, 0x8004)) {
                    w->deck = (w->deck + 2) % 3;
                } else {
                    w->deck = (w->deck + 4) % 3;
                }
                SzSound_PlaySE(0, 3);
            } else if (SzPad_Check(side, 0, 192)) {
                if (DotrCustomProcIsDeckReady(side, w->deck)) {
                    if (deck != w->deck) {
                        SzSound_PlaySE(0, 4);
                        func_00215920_b(side, w->deck);
                        func_002029B0_b(2, side);
                        *reload = 1;
                        if (DOTR_CUSTOM_PROC->mode == 1) {
                            func_00215920_b(1, w->deck);
                            func_002029B0_b(2, 1);
                        }
                    }
                } else {
                    SzSound_PlaySE(0, 6);
                }
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        case 1:
            if (SzPad_Check(side, 2, 0xa000) || SzPad_Check(side, 2, 12)) {
                short *p = &LP(side);

                old = *p;
                if (SzPad_Check(side, 2, 0x8004)) {
                    *p = ((*p + 50) / 100 - 1) * 100;
                } else {
                    *p = ((*p + 50) / 100 + 1) * 100;
                }
                *p = CLAMP(*p, 1, 9999);
                if (*p == old) {
                    SzSound_PlaySE(0, 6);
                } else {
                    SzSound_PlaySE(0, 3);
                }
            } else if (SzPad_Check(side, 0, 192)) {
                short *p = &LP(side);

                if (*p != SzDuel_GetLP(side)) {
                    SzSound_PlaySE(0, 4);
                    SzDuel_CalcLP(side, 4, *p);
                    LP2(side) = *p;
                    if (DOTR_CUSTOM_PROC->mode) {
                        

                        v = MAX(*p, 4000);
                        side ^= 1;
                        SzDuel_CalcLP(side, 4, v);
                        LP2(side) = MAX(*p, 4000);
                    }
                }
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        case 2:
            if (SzPad_Check(side, 2, 0xa000) || SzPad_Check(side, 2, 12)) {
                old = w->charge;
                if (SzPad_Check(side, 2, 0x8004)) {
                    w->charge = MAX(w->charge - 1, 1);
                } else {
                    w->charge = MIN(w->charge + 1, 12);
                }
                if (w->charge == old) {
                    SzSound_PlaySE(0, 6);
                } else {
                    SzSound_PlaySE(0, 3);
                }
            } else if (SzPad_Check(side, 0, 192)) {
                if (w->charge != func_001DE690_b(side)) {
                    SzSound_PlaySE(0, 4);
                    func_001DE6B0_b(side, w->charge);
                    if (DOTR_CUSTOM_PROC->mode) {
                        func_001DE6B0_b(side ^ 1, (unsigned char)MAX(w->charge, 3));
                    }
                }
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        case 3:
            if (SzPad_Check(side, 2, 0xa000)) {
                old = w->f8;
                if (SzPad_Check(side, 2, 0x8000)) {
                    w->f8 = 0;
                } else {
                    w->f8 = 1;
                }
                if (w->f8 != old) {
                    SzSound_PlaySE(0, 3);
                }
            } else if (SzPad_Check(side, 0, 192)) {
                if (w->f8 != w->fa) {
                    SzSound_PlaySE(0, 4);
                    w->fa = w->f8;
                }
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        case 4:
            if (SzPad_Check(side, 2, 0xa000)) {
                old = w->fc;
                if (SzPad_Check(side, 2, 0x8000)) {
                    w->fc = 0;
                } else {
                    w->fc = 1;
                }
                if (w->fc != old) {
                    SzSound_PlaySE(0, 3);
                }
            } else if (SzPad_Check(side, 0, 192)) {
                if (w->fc != w->fe) {
                    SzSound_PlaySE(0, 4);
                    w->fe = w->fc;
                }
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        case 5:
            w->menu &= 0xf;
            break;
        case 6:
            if (SzGame_ActMemCardProc() < 0) {
                w->menu &= 0xf;
            }
            break;
        case 7:
            if (SzPad_Check(side, 2, 0x5000)) {
                if (SzPad_Check(side, 2, 0x1000)) {
                    DOTR_CUSTOM_PROC->map = (DOTR_CUSTOM_PROC->map + DOTR_CUSTOM_PROC->maps - 1) % DOTR_CUSTOM_PROC->maps;
                } else {
                    DOTR_CUSTOM_PROC->map = (DOTR_CUSTOM_PROC->map + DOTR_CUSTOM_PROC->maps + 1) % DOTR_CUSTOM_PROC->maps;
                }
                SzSound_PlaySE(0, 3);
            } else if (SzPad_Check(side, 0, 192)) {
                struct DotrCustomProcSave *d = SzData_GetData(side);
                int n = (DOTR_CUSTOM_PROC->map + 2) % DOTR_CUSTOM_PROC->maps;

                for (y = 0; y < 7; y++) {
                    for (x = 0; x < 7; x++) {
                        func_001E2220_b(x, y, d->map[n][y][x]);
                    }
                }
                SzSound_PlaySE(0, 4);
                SzGame_SetMenuNum(13, 0);
                SzGame_Push(13, 2);
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        }
        break;
    case 0x20:
        if (SzPad_Check(side, 0, 32)) {
            SzSound_PlaySE(0, 5);
            w->menu &= 0xf;
        }
        break;
    case 0x30:
        if (SzPad_Check(side, 0, 0xa000)) {
            old = DOTR_CUSTOM_PROC->yes;
            if (SzPad_Check(side, 0, 0x8000)) {
                DOTR_CUSTOM_PROC->yes = 1;
            } else {
                DOTR_CUSTOM_PROC->yes = 0;
            }
            if (DOTR_CUSTOM_PROC->yes != old) {
                SzSound_PlaySE(0, 3);
            }
        } else if (SzPad_Check(side, 0, 192)) {
            SzSound_PlaySE(0, 4);
            if (DOTR_CUSTOM_PROC->yes) {
                SzGame_Pop();
            } else {
                DOTR_CUSTOM_PROC->menu[0] &= 0xf;
                DOTR_CUSTOM_PROC->menu[1] &= 0xf;
            }
        } else if (SzPad_Check(side, 0, 32)) {
            SzSound_PlaySE(0, 5);
            DOTR_CUSTOM_PROC->menu[0] &= 0xf;
            DOTR_CUSTOM_PROC->menu[1] &= 0xf;
        }
        break;
    case 0x40:
        if (SzPad_Check(side, 2, 12)) {
            if (SzPad_Check(side, 2, 4)) {
                DOTR_CUSTOM_PROC->last = (DOTR_CUSTOM_PROC->last + DOTR_CUSTOM_PROC->count - 5) % DOTR_CUSTOM_PROC->count;
            } else {
                DOTR_CUSTOM_PROC->last = (DOTR_CUSTOM_PROC->last + DOTR_CUSTOM_PROC->count + 5) % DOTR_CUSTOM_PROC->count;
            }
            SzSound_PlaySE(0, 3);
        } else if (SzPad_Check(side, 2, 0x5000)) {
            if (SzPad_Check(side, 2, 0x1000)) {
                DOTR_CUSTOM_PROC->last = (DOTR_CUSTOM_PROC->last + DOTR_CUSTOM_PROC->count - 1) % DOTR_CUSTOM_PROC->count;
            } else {
                DOTR_CUSTOM_PROC->last = (DOTR_CUSTOM_PROC->last + DOTR_CUSTOM_PROC->count + 1) % DOTR_CUSTOM_PROC->count;
            }
            SzSound_PlaySE(0, 3);
        } else if (SzPad_Check(side, 0, 192)) {
            
            v = DOTR_CUSTOM_PROC->list[(DOTR_CUSTOM_PROC->last + 2) % DOTR_CUSTOM_PROC->count];
            row = v >> 8;
            v = v & 0xff;
            if (row < 2) {
                v += row * 5 + 46;
            } else {
                v += 22;
            }
            SzGame_SetMenuNum(2, 0);
            SzGame_SetMenuNum(1, v);
            SzGame_SetMenuNum(3, c->side[0].deck + 1000);
            SzGame_SetMenuNum(4, c->side[1].deck + 1000);
            SzGame_SetMenuNum(28, (DOTR_CUSTOM_PROC->f8[0] ? 1 : 0) | (DOTR_CUSTOM_PROC->f8[1] ? 2 : 0));
            SzGame_SetMenuNum(29, (DOTR_CUSTOM_PROC->fc[0] ? 1 : 0) | (DOTR_CUSTOM_PROC->fc[1] ? 2 : 0));
            SzGame_Push(1, 1);
            SzSound_PlaySE(0, 4);
            return 1;
        } else if (SzPad_Check(side, 0, 32)) {
            SzSound_PlaySE(0, 5);
            DOTR_CUSTOM_PROC->menu[0] &= 0xf;
            DOTR_CUSTOM_PROC->menu[1] &= 0xf;
            if (DOTR_CUSTOM_PROC->mode == 0) {
                MENU(side ^ 1) |= 0x20;
            }
        }
        break;
    }
    return 0;
    }
    switch (m) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if (SzPad_Check(side, 2, 0xf000)) {
                
                int row;
                int col;
                unsigned char (*t)[5];

                row = w->cur / 5;
                col = w->cur % 5;
                t = D_002BEAC0_1c6170[DOTR_CUSTOM_PROC->mode ? 1 : 0];
                do {
                    if (SzPad_Check(side, 2, 0x1000)) {
                        col = (col + 4) % 5;
                    } else if (SzPad_Check(side, 2, 0x4000)) {
                        col = (col + 6) % 5;
                    } else if (SzPad_Check(side, 2, 0x8000)) {
                        row = (row + 1) % 2;
                    } else if (SzPad_Check(side, 2, 0x2000)) {
                        row = (row + 3) % 2;
                    }
                    v = t[row][col];
                } while (v == 255 || (v == 7 && !SzData_GetMapEditFlag(side)));
                if (w->menu != v) {
                    w->cur = col + row * 5;
                    w->menu = v;
                    SzSound_PlaySE(0, 3);
                }
            } else if (SzPad_Check(side, 0, 2048)) {
                unsigned char *q = &MENU(side ^ 1);

                if ((*q & 0xf0) == 0x20) {
                    SzSound_PlaySE(0, 4);
                    *q &= 0xf;
                    DOTR_CUSTOM_PROC->menu[0] |= 0x40;
                    DOTR_CUSTOM_PROC->menu[1] |= 0x40;
                } else {
                    SzSound_PlaySE(0, 4);
                    if (DOTR_CUSTOM_PROC->mode) {
                        DOTR_CUSTOM_PROC->menu[0] |= 0x40;
                        DOTR_CUSTOM_PROC->menu[1] |= 0x40;
                    } else {
                        w->menu |= 0x20;
                    }
                }
            } else if (SzPad_Check(side, 0, 192)) {
                SzSound_PlaySE(0, 4);
                switch (w->menu) {
                case 5:
                    SzGame_SetMenuNum(6, 0);
                    SzGame_Push(6, 1);
                    break;
                case 6:
                    SzGame_InitMemCardProc(1);
                    break;
                }
                w->menu |= 0x10;
            } else if (SzPad_Check(side, 0, 32)) {
                if (MENU(side ^ 1) < 8) {
                    SzSound_PlaySE(0, 5);
                    DOTR_CUSTOM_PROC->menu[0] |= 0x30;
                    DOTR_CUSTOM_PROC->menu[1] |= 0x30;
                    DOTR_CUSTOM_PROC->yes = 0;
                } else {
                    SzSound_PlaySE(0, 6);
                }
            }
            break;
        }
    return 0;
}
#undef DOTR_CUSTOM_PROC
#undef DOTR_CUSTOM_PROC_BYTES_AT
#undef DOTR_CUSTOM_PROC_WORDS_AT
#undef MENU
#undef LP
#undef LP2
#undef MAX
#undef MIN
#undef CLAMP

void SzDuel_DrawCustomDuel(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawCustomDuel_Pipe(RhBase_GetVifPacketArea()));
}

INCLUDE_ASM("asm/nonmatchings/main_041", SzDuel_DrawCustomDuel_Pipe);

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C7790;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C7790;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C7790;

typedef struct {
    Color_001C7790 color;
    Vertex_001C7790 xyz;
} Point_001C7790;

typedef struct {
    u64 tag[2];
    Point_001C7790 points[4];
    u64 end;
} Packet_001C7790;

typedef struct {
    u8 b, g, r, a;
} Source_001C7790;

static inline void set_color_001C7790(Color_001C7790 *a, Color_001C7790 *b,
                                      Source_001C7790 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

static inline void set_xyz_001C7790(Vertex_001C7790 *v, s32 x, s32 y) {
    v->x = (x + 0x6C0) << 4;
    v->y = (y + 0x720) << 4;
    v->z = D_003180E8;
    v->fog = 0;
}

s32 lSzDuel_DrawCustomDuel_Base_Pipe(s32 arg0) {
    extern u8 D_002BE860[];
    Source_001C7790 *colors = (Source_001C7790 *)D_002BE860;
    s32 width = 0x140;
    s32 height = 0x1C0;
    Packet_001C7790 packet __attribute__((aligned(8)));

    ((Tag_001C7790 *)packet.tag)->flags = 0x14;
    ((Tag_001C7790 *)packet.tag)->count = 8;
    ((Tag_001C7790 *)packet.tag)->registers = 0x41414141;
    ((Tag_001C7790 *)packet.tag)->padding = 0;
    set_color_001C7790(&packet.points[0].color, &packet.points[2].color, &colors[0]);
    set_color_001C7790(&packet.points[1].color, &packet.points[3].color, &colors[1]);
    set_xyz_001C7790(&packet.points[0].xyz, 0, 0);
    set_xyz_001C7790(&packet.points[1].xyz, width, 0);
    set_xyz_001C7790(&packet.points[2].xyz, 0, height);
    set_xyz_001C7790(&packet.points[3].xyz, width, height);
    arg0 = ExSortPrim_Pipe(arg0, (s32)packet.tag, 0, 0);
    set_color_001C7790(&packet.points[0].color, &packet.points[2].color, &colors[1]);
    set_color_001C7790(&packet.points[1].color, &packet.points[3].color, &colors[0]);
    set_xyz_001C7790(&packet.points[0].xyz, width, 0);
    set_xyz_001C7790(&packet.points[1].xyz, width * 2, 0);
    set_xyz_001C7790(&packet.points[2].xyz, width, height);
    set_xyz_001C7790(&packet.points[3].xyz, width * 2, height);
    return ExSortPrim_Pipe(arg0, (s32)packet.tag, 0, 0);
}

void lSzDuel_DrawCustomDuel_Title_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern char D_002BF047[];
    extern char D_002BF04E[];
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    s32 text = (s32)D_002BF047;
    s32 text2 = (s32)D_002BF04E;
    s32 hint = 0;
    s32 x = arg1 + 0xE0;
    s32 y = arg2 + 0x20;
    s32 tx;
    s32 ty;
    s32 element;

    arg0 = lSzDuel_DrawWindow_Base_Pipe(arg0, x, y, 6, 1);
    element = lSzDuel_DrawWindow_Frame_Pipe(arg0, -1, 0x73, 4, x, y, 0x15, 2, 1);
    tx = arg1 + 0x140;
    ty = arg2 + 0x27;
    element = SzDuel_DrawWindow_Font_Pipe(element, tx, ty, 2, 3, func_0019BEF0((const char *)text), (s8 *)text,
                            hint != 0 ? (s32)D_002BE944 : 0);
    SzDuel_DrawWindow_Font_Pipe(element, arg1 + 0x140, arg2 + 0x46, 2, 3, func_0019BEF0((const char *)text2),
                  (s8 *)text2, hint != 0 ? (s32)D_002BE944 : 0);
}

INCLUDE_ASM("asm/nonmatchings/main_041", lSzDuel_DrawCustomDuel_PlayerInfo_Pipe);

s32 lSzDuel_DrawCustomDuel_Menu_Pipe(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    extern s32 lSzDuel_DrawCustomDuel_Menu_SelectMapEdit_Pipe(s32, u8 *, s32, s32);
    u8 kind;

    kind = arg1[0xA9C002];
    if ((kind & 0xF0) == 0x10) {
        switch (kind & 0xF) {
        case 0:
            arg0 = lSzDuel_DrawCustomDuel_Menu_SelectDeck_Pipe(arg0, arg1, arg2 + 0xE, arg3 + 0xB);
            break;
        case 1:
            arg0 = lSzDuel_DrawCustomDuel_Menu_LifeSet_Pipe(arg0, (s32)arg1, arg2 + 0xE, arg3 + 0xB);
            break;
        case 2:
            arg0 = lSzDuel_DrawCustomDuel_Menu_SummonCharge_Pipe(arg0, arg1, arg2 + 0xE, arg3 + 0xB);
            break;
        case 3:
            arg0 = lSzDuel_DrawCustomDuel_Menu_LeaderAbility_Pipe(arg0, arg1, arg2 + 0xE, arg3 + 0xB);
            break;
        case 4:
            arg0 = lSzDuel_DrawCustomDuel_Menu_CardDisp_Pipe(arg0, arg1, arg2 + 0xE, arg3 + 0xB);
            break;
        case 5:
        case 6:
            arg0 = lSzDuel_DrawCustomDuel_Menu_Top_Pipe(arg0, arg1, arg2, arg3);
            break;
        case 7:
            arg0 = lSzDuel_DrawCustomDuel_Menu_SelectMapEdit_Pipe(arg0, arg1, arg2 + 0xE, arg3 - 6);
            break;
        }
    } else {
        arg0 = lSzDuel_DrawCustomDuel_Menu_Top_Pipe(arg0, arg1, arg2, arg3);
    }
    return arg0;
}

s32 lSzDuel_DrawCustomDuel_Menu_Top_Pipe(s32 arg0, u8 *arg1, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern u8 D_002BEAC0[2][10];
    extern char D_002BF05B[];
    extern char D_002BF03A[];
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    extern s32 D_00290A76;
    u8 *cursor = (u8 *)0xA9C000;
    s8 *text1 = D_002BF05B;
    s8 *text2 = D_002BEF98;
    s8 *text3 = D_002BF03A;
    s32 row;
    s32 enabled;
    s32 width = 0x25A;
    u8 *list;
    s32 hint = 0;
    s32 col;
    s32 item;
    s32 sel;
    s32 w;
    s32 *info;
    f32 scale;
    s32 px;
    s32 py;

    width = (*(u8 *)0xA9C088 != 0) ? width : 0x12A;
    list = D_002BEAC0[(*(u8 *)0xA9C088 != 0) ? 1 : 0];
    arg0 = SzMsg_LoadFont_Pipe(arg0, 1, 0x81, 0, 0x16);
    arg0 = SzMsg_LoadFont_Pipe(arg0, 2, 0x82, 0, 0x2C);
    arg0 = SzMsg_LoadFont_Pipe(arg0, 3, 0x83, 0, 0x42);
    arg0 = SzMsg_LoadFont_Pipe(arg0, 4, 0x84, 0, 0x58);
    arg0 = SzMsg_LoadFont_Pipe(arg0, 5, 0x85, 0, 0x6E);
    arg0 = SzMsg_LoadFont_Pipe(arg0, 6, 0x86, 0, 0x84);
    arg0 = SzMsg_LoadFont_Pipe(arg0, 7, 0x87, 0, 0x9A);
    arg0 = SzMsg_LoadFont_Pipe(arg0, 8, 0x88, 0, 0xB0);
    arg0 = lSzDuel_DrawWindow_Frame_Pipe(RhText_SetTextureFlush(arg0), (s32)arg1, (s32)arg1, 0, x, y, -(width - 0x14), -0xAE, 1);
    for (row = 0; row < 2; row++) {
        for (col = 0; col < 5; col++) {
            item = list[row * 5 + col];
            enabled = 1;
            if (item == 0xFF) {
                continue;
            }
            if (item == 7) {
                if (SzData_GetMapEditFlag((s32)arg1) == 0) {
                    enabled = 0;
                }
            }
            if (enabled) {
                info = SzMsg_GetInfo(item + 1);
                if (cursor[0x88]) {
                    w = info[3];
                    scale = 1.0f;
                    if (w > 0xAC) {
                        scale = 172.0f / (f32)w;
                    }
                    arg0 = SzMsg_DrawRatioX_Pipe(arg0, item + 1, x + (width / 3) * (row + 1) - (s32)((f32)(w >> 1) * scale),
                                         y + 0x20 + col * 0x20,
                                         scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
                } else {
                    w = info[3];
                    scale = 1.0f;
                    if (w > 0xAC) {
                        scale = 172.0f / (f32)w;
                    }
                    arg0 = SzMsg_DrawRatioX_Pipe(arg0, item + 1, x + (width >> 1) - (s32)((f32)(w >> 1) * scale),
                                         y + 0x1A + col * 0x14,
                                         scale, 0.90909094f, 0, SzMsg_DrawRect_Pipe);
                }
                sel = cursor[(s32)arg1 + 2] & 0xF;
                if (sel == item) {
                    if (cursor[0x88]) {
                        arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, -1, -1, 6, x + (width / 3) * (row + 1) - 0x62,
                                             y + 0x1C + col * 0x20, -0xBE, -0x1A, 1);
                    } else {
                        arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, -1, -1, 6, x + (width >> 1) - 0x62,
                                             y + 0x16 + col * 0x14, -0xBE, -0x18, 1);
                    }
                }
            }
            SzMsg_Free(item + 1);
        }
    }
    arg0 = lSzDuel_DrawWindow_ExBoard_Pipe(arg0, (s32)arg1, x + 0x20, y + 0x85, -(width - 0x3A), -0x34, -1, 0);
    px = x + 0x6D0 + ((width - 0x3A) >> 2);
    py = y + 0x7AC;
    arg0 = lSzDuel_DrawWindow_ExIcon_Pipe(arg0, &D_00290A58, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x6E0 + ((width - 0x3A) >> 2);
    py = y + 0x7AC;
    arg0 = lSzDuel_DrawWindow_ExIcon_Pipe(arg0, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x20 + ((width - 0x3A) >> 2);
    py = y + 0xA7;
    arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, px, py, 1, 2, func_0019BEF0((char *)text1), text1,
                         hint != 0 ? (s32)D_002BE944 : 0);
    px = x + 0x6D8 + (((width - 0x3A) * 2) >> 2);
    py = y + 0x7AC;
    arg0 = lSzDuel_DrawWindow_ExIcon_Pipe(arg0, &D_00290A6C, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x20 + (((width - 0x3A) * 2) >> 2);
    py = y + 0xA7;
    arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, px, py, 1, 2, func_0019BEF0((char *)text2), text2,
                         hint != 0 ? (s32)D_002BE944 : 0);
    px = x + 0x6D8 + (((width - 0x3A) * 3) >> 2);
    py = y + 0x7AC;
    arg0 = lSzDuel_DrawWindow_ExIcon_Pipe(arg0, &D_00290A76, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x20 + (((width - 0x3A) * 3) >> 2);
    py = y + 0xA7;
    return SzDuel_DrawWindow_Font_Pipe(arg0, px, py, 1, 2, func_0019BEF0((char *)text3), text3,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

static inline u8 *save_001C8DC0(u8 *save) {
    return save + 0xA9C000;
}

s32 lSzDuel_DrawCustomDuel_Menu_SelectDeck_Pipe(s32 arg0, u8 *arg1, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern u8 D_00290080[];
    extern char D_002BF05B[];
    extern char D_002BEF93[];
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    u8 *state = D_00317490.b;
    s8 *text3 = D_002BF05B;
    s8 *text4 = D_002BEF93;
    s32 color = (arg1[0xA9C002] & 0xF) + 0x81;
    s32 width = 0x244;
    f32 scale;
    s32 hint = 0;
    s32 cx;
    s32 w;
    s32 id;
    u8 *p;
    s32 i;
    s32 a;
    s32 b;
    s32 ok;
    s32 sel;
    s32 okColor;
    s32 selColor;
    s32 base;
    s32 off;
    s32 bx;
    s32 px;
    s32 py;
    s32 by;

    width = (*(u8 *)0xA9C088 != 0) ? width : 0x114;
    scale = 1.0f;
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, color, 0, 0x16));
    cx = x + (width >> 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, 3, 4, cx - 0x59, y, -0xB2, -0x20, 1);
    w = SzMsg_GetInfo(1)[3];
    if (w > 0x9A) {
        scale = 154.0f / (f32)w;
    }
    id = SzMsg_DrawRatioX_Pipe(id, 1, cx - (s32)((f32)(w >> 1) * scale), y + 5, scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, (s32)arg1, -1, 0xB, x, y + 0x20, -width, -0x96, 1);
    i = 0;
    p = save_001C8DC0(arg1);
    do {
        a = SzData_GetDeckCount((s32)arg1, i);
        b = SzData_GetLeader((s32)arg1, i);
        ok = (a >= 0x28 && b != 0x3E7) ? 1 : 0;
        sel = (p[4] == i) ? 1 : 0;
        selColor = sel ? 4 : 7;
        okColor = ok ? -1 : 5;
        base = arg1 ? 0x14 : 0xA;
        off = (width * (i + 1)) >> 2;
        px = x + 0x6B4 + off;
        py = y + 0x74B;
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, D_00290080 + (i + 0xE3) * 10, px, py, 0, 1, 0, 0, 0, 0, sel, 0, -1,
                           hint != 0 ? 0x40 : 0x80);
        bx = x + off - 0x18;
        by = y + 0x46;
        id = lSzDuel_DrawWindow_PicMini_Pipe(id, i + base, bx, by, 0x30, 0x30, *(s32 *)(state + 0xC58), sel);
        id = lSzDuel_DrawWindow_Frame_Pipe(id, okColor, -1, selColor, bx, by, -0x30, -0x30, 1);
        i++;
    } while (i < 3);
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, (s32)arg1, x + 0x12, y + 0x7A, -(width - 0x24), -0x34, -1, 0);
    px = x + 0x6C2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x6D2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + ((width - 0x24) >> 2);
    py = y + 0x9C;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 2, func_0019BEF0((char *)text3), text3,
                       hint != 0 ? (s32)D_002BE944 : 0);
    px = x + 0x6CA + (((width - 0x24) * 2) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A6C, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + (((width - 0x24) * 2) >> 2);
    py = y + 0x9C;
    return SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 2, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C92C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C92C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C92C0;

typedef struct {
    Color_001C92C0 color;
    Vertex_001C92C0 xyz;
} Point_001C92C0;

typedef struct {
    u64 tag[2];
    Point_001C92C0 points[4];
    u64 end;
} Packet_001C92C0;

typedef struct {
    u8 b, g, r, a;
} Source_001C92C0;

typedef struct {
    Source_001C92C0 c[2];
} Pair_001C92C0;

static inline void set_color_001C92C0(Color_001C92C0 *a, Color_001C92C0 *b,
                                      Source_001C92C0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

static inline void set_xyz_001C92C0(Vertex_001C92C0 *v, s32 x, s32 y, u8 *state) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = *(s32 *)(state + 0xC58);
    v->fog = 0;
}

s32 lSzDuel_DrawCustomDuel_Menu_LifeSet_Pipe(s32 arg0, s32 player, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawX_Pipe(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe(s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern char D_002BF05B[];
    extern char D_002BEF93[];
    extern s32 D_00290A1C;
    extern s32 D_00290896;
    extern s32 D_002908A0;
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    extern Pair_001C92C0 D_002914A0;
    u8 *state = D_00317490.b;
    s8 *text3 = D_002BF05B;
    s8 *text4 = D_002BEF93;
    s32 tmp = (((u8 *)player)[0xA9C002] & 0xF) + 0x81;
    s32 width;
    s32 hint = 0;
    s32 cx;
    s32 id;
    s16 *life;
    s32 px;
    s32 py;
    s32 w;
    s32 h;
    Pair_001C92C0 colors;
    Packet_001C92C0 packet __attribute__((aligned(8)));

    if (*(u8 *)0xA9C088 != 0) {
        width = 0x244;
    } else {
        width = 0x114;
    }
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, tmp, 0, 0x16));
    cx = x + (width >> 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, 3, 4, cx - 0x59, y, -0xB2, -0x20, 1);
    id = SzMsg_DrawX_Pipe(id, 1, cx - (((s32 *)SzMsg_GetInfo(1))[3] >> 1), y + 5, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, player, -1, 0xB, x, y + 0x20, -width, -0x96, 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, -1, 5, cx - 0x38, y + 0x38, -0x70, -0x14, 1);
    px = x + 0x68A + (width >> 1);
    py = y + 0x75A;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A1C, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    life = &((s16 *)0xA9C010)[player];
    id = SzDuel_DrawWindow_FontDigit_Pipe(id, cx - 0xE, y + 0x3C, 0, 0, 4, *life);
    px = x + 0x64E + (width >> 1);
    py = y + 0x76C;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290896, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    tmp = cx - 0x58;
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xD, -1, 7, tmp, y + 0x50, -0xB0, -0x10, 1);
    px = x + 0x668 + (width >> 1);
    py = y + 0x770;
    w = (s32)((f32)*life * 176.0f / 9999.0f);
    h = 8;
    colors = D_002914A0;
    if (player == 0) {
        colors.c[1].b = 0;
        colors.c[1].g = 0;
        colors.c[0].b = 0;
        colors.c[0].g = 0;
    }
    ((Tag_001C92C0 *)packet.tag)->flags = 0x14;
    ((Tag_001C92C0 *)packet.tag)->count = 8;
    ((Tag_001C92C0 *)packet.tag)->registers = 0x41414141;
    ((Tag_001C92C0 *)packet.tag)->padding = 0;
    set_color_001C92C0(&packet.points[0].color, &packet.points[1].color, &colors.c[0]);
    set_color_001C92C0(&packet.points[2].color, &packet.points[3].color, &colors.c[1]);
    set_xyz_001C92C0(&packet.points[0].xyz, px, py, state);
    set_xyz_001C92C0(&packet.points[1].xyz, px + w, py, state);
    set_xyz_001C92C0(&packet.points[2].xyz, px, py + h, state);
    set_xyz_001C92C0(&packet.points[3].xyz, px + w, py + h, state);
    id = ExSortPrim_Pipe(id, (s32)packet.tag, 0, 0);
    set_color_001C92C0(&packet.points[0].color, &packet.points[1].color, &colors.c[1]);
    set_color_001C92C0(&packet.points[2].color, &packet.points[3].color, &colors.c[0]);
    set_xyz_001C92C0(&packet.points[0].xyz, px, py + h, state);
    set_xyz_001C92C0(&packet.points[1].xyz, px + w, py + h, state);
    set_xyz_001C92C0(&packet.points[2].xyz, px, py + h * 2, state);
    set_xyz_001C92C0(&packet.points[3].xyz, px + w, py + h * 2, state);
    id = ExSortPrim_Pipe(id, (s32)packet.tag, 0, 0);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, -1, 7, tmp, y + 0x50, -0xB0, -0x10, 1);
    px = x + 0x71A + (width >> 1);
    py = y + 0x76C;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_002908A0, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, player, x + 0x12, y + 0x7A, -(width - 0x24), -0x34, -1, 0);
    px = x + 0x6C2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x6D2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + ((width - 0x24) >> 2);
    py = y + 0x9C;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 2, func_0019BEF0((char *)text3), text3,
                       hint != 0 ? (s32)D_002BE944 : 0);
    px = x + 0x6CA + (((width - 0x24) * 2) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A6C, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + (((width - 0x24) * 2) >> 2);
    py = y + 0x9C;
    return SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 2, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

s32 lSzDuel_DrawCustomDuel_Menu_SummonCharge_Pipe(s32 arg0, u8 *arg1, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe(s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern char D_002BF05B[];
    extern char D_002BEF93[];
    extern s32 D_00290896;
    extern s32 D_002908E6;
    extern s32 D_002908A0;
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s8 *text3 = D_002BF05B;
    s8 *text4 = D_002BEF93;
    s32 color = (arg1[0xA9C002] & 0xF) + 0x81;
    s32 width;
    f32 scale;
    s32 hint = 0;
    s32 cx;
    s32 w;
    s32 id;
    s32 px;
    s32 py;

    if (*(u8 *)0xA9C088 != 0) {
        width = 0x244;
    } else {
        width = 0x114;
    }
    scale = 1.0f;
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, color, 0, 0x16));
    cx = x + (width >> 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, 3, 4, cx - 0x59, y, -0xB2, -0x20, 1);
    w = SzMsg_GetInfo(1)[3];
    if (w > 0x9A) {
        scale = 154.0f / (f32)w;
    }
    id = SzMsg_DrawRatioX_Pipe(id, 1, cx - (s32)((f32)(w >> 1) * scale), y + 5, scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, (s32)arg1, -1, 0xB, x, y + 0x20, -width, -0x96, 1);
    px = x + 0x688 + (width >> 1);
    py = y + 0x764;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290896, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, -1, 5, cx - 0x1E, y + 0x46, -0x3C, -0x14, 1);
    px = x + 0x6A4 + (width >> 1);
    py = y + 0x768;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_002908E6, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    id = SzDuel_DrawWindow_FontDigit_Pipe(id, cx - 6, y + 0x4A, 0, 0, 2, arg1[0xA9C006]);
    px = x + 0x6E0 + (width >> 1);
    py = y + 0x764;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_002908A0, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, (s32)arg1, x + 0x12, y + 0x7A, -(width - 0x24), -0x34, -1, 0);
    px = x + 0x6C2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x6D2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + ((width - 0x24) >> 2);
    py = y + 0x9C;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 2, func_0019BEF0((char *)text3), text3,
                       hint != 0 ? (s32)D_002BE944 : 0);
    px = x + 0x6CA + (((width - 0x24) * 2) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A6C, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + (((width - 0x24) * 2) >> 2);
    return SzDuel_DrawWindow_Font_Pipe(id, px, y + 0x9C, 1, 2, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

s32 lSzDuel_DrawCustomDuel_Menu_LeaderAbility_Pipe(s32 arg0, u8 *arg1, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawX_Pipe(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s64, s64, s64, s64, s64, s64);
    extern char D_002BF05B[];
    extern char D_002BEF93[];
    extern char D_002BF062[];
    extern char D_002BF066[];
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s8 *text3 = D_002BF05B;
    s8 *text4 = D_002BEF93;
    s8 *text2 = D_002BF062;
    s8 *text1 = D_002BF066;
    s32 hint = 0;
    s32 win;
    s32 tx;
    s32 ty;
    s32 id;

    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, (arg1[0xA9C002] & 0xF) + 0x81, 0, 0x16));
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, 3, 4, x + 0x31, y, -0xB2, -0x20, 1);
    id = SzMsg_DrawX_Pipe(id, 1, x + 0x8A - (((s32 *)SzMsg_GetInfo(1))[3] >> 1), y + 5, 0,
                       SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    win = lSzDuel_DrawWindow_Frame_Pipe(id, (s32)arg1, -1, 0xB, x, y + 0x20, -0x114, -0x96, 1);
    tx = x + 0x5C;
    ty = y + 0x4D;
    id = SzDuel_DrawWindow_Font_Pipe(win, tx, ty, 0, 3, func_0019BEF0((char *)text1), text1,
                       arg1[0xA9C008] != 0 ? (s32)D_002BE944 : 0);
    tx = x + 0xB8;
    ty = y + 0x4D;
    id = SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 0, 3, func_0019BEF0((char *)text2), text2,
                       arg1[0xA9C008] != 0 ? 0 : (s32)D_002BE944);
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, (s32)arg1, x + 0x12, y + 0x7A, -0xF0, -0x34, -1, 0);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, x + 0x6FE, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, x + 0x70E, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    tx = x + 0x4E;
    ty = y + 0x9C;
    id = SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 1, 2, func_0019BEF0((char *)text3), text3,
                       hint != 0 ? (s32)D_002BE944 : 0);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A6C, x + 0x742, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    tx = x + 0x8A;
    ty = y + 0x9C;
    return SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 1, 2, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

s32 lSzDuel_DrawCustomDuel_Menu_CardDisp_Pipe(s32 arg0, u8 *arg1, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawX_Pipe(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s64, s64, s64, s64, s64, s64);
    extern char D_002BF05B[];
    extern char D_002BEF93[];
    extern char D_002BF051[];
    extern char D_002BF056[];
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s8 *text3 = D_002BF05B;
    s8 *text4 = D_002BEF93;
    s8 *text2 = D_002BF051;
    s8 *text1 = D_002BF056;
    s32 hint = 0;
    s32 win;
    s32 tx;
    s32 ty;
    s32 id;

    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, (arg1[0xA9C002] & 0xF) + 0x81, 0, 0x16));
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, 3, 4, x + 0x31, y, -0xB2, -0x20, 1);
    id = SzMsg_DrawX_Pipe(id, 1, x + 0x8A - (((s32 *)SzMsg_GetInfo(1))[3] >> 1), y + 5, 0,
                       SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    win = lSzDuel_DrawWindow_Frame_Pipe(id, (s32)arg1, -1, 0xB, x, y + 0x20, -0x114, -0x96, 1);
    tx = x + 0x5C;
    ty = y + 0x4D;
    id = SzDuel_DrawWindow_Font_Pipe(win, tx, ty, 0, 3, func_0019BEF0((char *)text1), text1,
                       arg1[0xA9C00C] != 0 ? (s32)D_002BE944 : 0);
    tx = x + 0xB8;
    ty = y + 0x4D;
    id = SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 0, 3, func_0019BEF0((char *)text2), text2,
                       arg1[0xA9C00C] != 0 ? 0 : (s32)D_002BE944);
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, (s32)arg1, x + 0x12, y + 0x7A, -0xF0, -0x34, -1, 0);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, x + 0x6FE, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, x + 0x70E, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    tx = x + 0x4E;
    ty = y + 0x9C;
    id = SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 1, 2, func_0019BEF0((char *)text3), text3,
                       hint != 0 ? (s32)D_002BE944 : 0);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A6C, x + 0x742, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    tx = x + 0x8A;
    ty = y + 0x9C;
    return SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 1, 2, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001CA7C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001CA7C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001CA7C0;

typedef struct {
    Color_001CA7C0 color;
    Vertex_001CA7C0 xyz;
} Point_001CA7C0;

typedef struct {
    u64 tag[2];
    Point_001CA7C0 points[4];
    u64 end;
} Packet_001CA7C0;

typedef struct {
    u64 tag[2];
    Color_001CA7C0 color;
    Vertex_001CA7C0 xyz[2];
    u64 end;
} Rect_001CA7C0;

typedef struct {
    u8 b, g, r, a;
} Source_001CA7C0;

typedef struct {
    u8 pad[0xFEA3];
    u8 maps[5][7][7];
} Maps_001CA7C0;

static inline void set_color_001CA7C0(Color_001CA7C0 *a, Color_001CA7C0 *b,
                                      Source_001CA7C0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

static inline void set_xyz_001CA7C0(Vertex_001CA7C0 *v, s32 x, s32 y, u8 *state) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = *(s32 *)(state + 0xC58);
    v->fog = 0;
}

static inline void set_corner_001CA7C0(Vertex_001CA7C0 *v, s32 x, s32 y) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = D_003180E8;
    v->fog = 0;
}

#pragma optimization_level 3

s32 lSzDuel_DrawCustomDuel_Menu_SelectMap_Pipe(s32 id, s32 player, s32 x, s32 y) {
    extern s32 *func_001FEAB0(s32);
    extern s32 func_001FE7D0(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001B6EA0(s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B65F0(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern u8 D_00290080[];
    extern u8 D_002BE8C0[];
    extern u8 D_002CEE5C[][7][7];
    extern char D_002BF06E[];
    extern char D_002BEF93[];
    extern s32 D_00290828;
    extern s32 D_00290AA8;
    extern s32 D_00290832;
    extern s32 D_00290AB2;
    extern s32 D_002902C4;
    extern s32 D_00290256;
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s32 ret;
    u8 *state = D_00317490.b;
    u8 *save = (u8 *)0xA9C000;
    Maps_001CA7C0 *maps;
    s8 *text1;
    s8 *text2;
    s32 sel;
    s32 hint = 0;
    s32 tx;
    s32 ty;
    s32 i;
    s32 last;
    s32 j;
    s32 row;
    s32 count;
    u16 entry;
    s32 n;
    u16 *p;
    s32 hl;
    u8 *board;
    s32 px;
    s32 py;
    s32 w;
    s32 h;
    Rect_001CA7C0 rect __attribute__((aligned(8)));
    Packet_001CA7C0 packet __attribute__((aligned(8)));

    text1 = D_002BF06E;
    text2 = D_002BEF93;
    sel = (*(u8 *)0xA9C089 + 2) % *(u8 *)0xA9C08A;
    id = func_001B4780(func_0020F290(func_001FD680(func_001FD680(func_001FD680(func_001FD680(id, 1, 0x89, 0, 0x16),
                                                                 2, 0x8B, 0, 0x2C),
                                                   3, 0x8C, 0, 0x42),
                                     4, 0x8A, 0, 0x58)),
                       0xC, 3, 4, x + 0xC9, y, -0xB2, -0x20, 1);
    id = func_001FE7D0(id, 1, x + 0x122 - (func_001FEAB0(1)[3] >> 1), y + 5, 0, SzMsg_DrawRect_Pipe);
    func_001FEAF0(1);
    py = y + 0x20;
    id = func_001B4780(id, player, -1, 0xB, x, py, -0x244, -0xAA, 1);
    py = y + 0x745;
    id = func_001B3CC0(id, &D_00290828, x + 0x71D, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x747;
    id = func_001B3CC0(id, &D_00290AA8, x + 0x73D, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x35;
    id = func_001B4780(id, 0xC, -1, 6, x + 0x5D, py, -0xEC, -0x7C, 1);
    px = x + 0x71D;
    py = y + 0x789;
    ((Tag_001CA7C0 *)rect.tag)->flags = 6;
    ((Tag_001CA7C0 *)rect.tag)->count = 3;
    ((Tag_001CA7C0 *)rect.tag)->registers = 0x441;
    ((Tag_001CA7C0 *)rect.tag)->padding = 0;
    rect.color.r = 0x80;
    rect.color.g = 0;
    rect.color.b = 0;
    rect.color.a = 0x80;
    rect.color.q = 1.0f;
    set_corner_001CA7C0(&rect.xyz[0], px, py);
    set_corner_001CA7C0(&rect.xyz[1], px + 0xF0, py + 0x18);
    id = func_00207650(id, (s32)rect.tag, 0, 0);
    py = y + 0x35;
    id = func_001B4780(id, -1, -1, 6, x + 0x5D, py, -0xEC, -0x7C, hint != 0 ? 0 : 1);
    for (i = 0; i < 5; i++) {
        hl = (i == 2) ? 0 : (s32)D_002BE944;
        p = (u16 *)(save + 0x18 + ((save[0x89] + i) % save[0x8A]) * 2);
        n = *p & 0xFF;
        id = func_001FE7D0(id, (*p >> 8) + 2, x + 0x69, y + 0x3A + i * 0x18, hl, SzMsg_DrawRect_Pipe);
        id = func_001B6CA0(id, x + 0x119, y + 0x3A + i * 0x18, 2, n, 0, 1, hl);
    }
    func_001FEAF0(2);
    func_001FEAF0(3);
    func_001FEAF0(4);
    py = y + 0x78D;
    id = func_001B3CC0(id, &D_002902C4, x + 0x71F, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x78D;
    id = func_001B3CC0(id, &D_002902C4, x + 0x803, py, 0, 1, 0, 0, 1, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x7D5;
    id = func_001B3CC0(id, &D_00290832, x + 0x71D, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x7D7;
    id = func_001B3CC0(id, &D_00290AB2, x + 0x73D, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    p = &((u16 *)0xA9C018)[sel];
    switch (*p >> 8) {
        case 0:
            maps = func_002145E0(0);
            board = &maps->maps[*(u8 *)p][0][0];
            break;
        case 1:
            maps = func_002145E0(1);
            board = &maps->maps[*(u8 *)p][0][0];
            break;
        case 2:
            board = &D_002CEE5C[sel + 0x16][0][0];
            break;
    }
    px = x + 0x81C;
    py = y + 0x75C;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            last = func_001B3CC0(id, D_00290080 + (board[i * 7 + j] + 0x10E) * 10, px + j * 16,
                               py + i * 16, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
            id = last;
        }
    }
    py = y + 0x35;
    id = func_001B4780(last, -1, 1, 1, x + 0x155, py, -0x76, -0x76, 1);
    py = y + 0x7C7;
    id = func_001B3CC0(id, &D_00290256, x + 0x834, py, 0, 1, 0, 0, 0, 1, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    for (row = 0; row < 10; row++) {
        count = 0;
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                if (row == board[i * 7 + j]) {
                    count++;
                }
            }
        }
        id = func_001B3CC0(id, D_00290080 + (row + 0x10E) * 10, x + 0x89B, y + 0x745 + row * 16, 0, 1, 0,
                           0, 0, 0, 1, 0, -1, 0x80);
        id = func_001B4780(id, 0xD, -1, 5, x + 0x1EB, y + 0x25 + row * 16, -0x54, -0x10, 1);
        px = x + 0x8AB;
        py = y + 0x745 + row * 16;
        w = (s32)((f32)count * 84.0f / 49.0f);
        h = 8;
        ((Tag_001CA7C0 *)packet.tag)->flags = 0x14;
        ((Tag_001CA7C0 *)packet.tag)->count = 8;
        ((Tag_001CA7C0 *)packet.tag)->registers = 0x41414141;
        ((Tag_001CA7C0 *)packet.tag)->padding = 0;
        set_color_001CA7C0(&packet.points[0].color, &packet.points[1].color, &((Source_001CA7C0 *)D_002BE8C0)[row * 3]);
        set_color_001CA7C0(&packet.points[2].color, &packet.points[3].color, &((Source_001CA7C0 *)D_002BE8C0)[row * 3 + 1]);
        set_xyz_001CA7C0(&packet.points[0].xyz, px, py, state);
        set_xyz_001CA7C0(&packet.points[1].xyz, px + w, py, state);
        set_xyz_001CA7C0(&packet.points[2].xyz, px, py + h, state);
        set_xyz_001CA7C0(&packet.points[3].xyz, px + w, py + h, state);
        id = func_00207650(id, (s32)packet.tag, 0, 0);
        set_color_001CA7C0(&packet.points[0].color, &packet.points[1].color, &((Source_001CA7C0 *)D_002BE8C0)[row * 3 + 1]);
        set_color_001CA7C0(&packet.points[2].color, &packet.points[3].color, &((Source_001CA7C0 *)D_002BE8C0)[row * 3 + 2]);
        set_xyz_001CA7C0(&packet.points[0].xyz, px, py + h, state);
        set_xyz_001CA7C0(&packet.points[1].xyz, px + w, py + h, state);
        set_xyz_001CA7C0(&packet.points[2].xyz, px, py + h * 2, state);
        set_xyz_001CA7C0(&packet.points[3].xyz, px + w, py + h * 2, state);
        id = func_00207650(id, (s32)packet.tag, 0, 0);
        id = func_001B4780(id, -1, -1, 5, x + 0x1EB, y + 0x25 + row * 16, -0x54, -0x10, 1);
        id = func_001B6EA0(id, x + 0x215, y + 0x27 + row * 16, 0, 2, 2, count);
    }
    id = func_001B65F0(id, player, x + 6, y + 0x26, -0x4E, -0x9E, -1, 0);
    py = y + 0x76E;
    id = func_001B3CC0(id, &D_00290A62, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x77E;
    ret = func_001B3CC0(id, &D_00290A58, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    tx = x + 0x20;
    ty = y + 0x58;
    ret = func_001B6F70(ret, tx, ty, 1, 0, func_0019BEF0((char *)text1), text1,
                       hint != 0 ? (s32)D_002BE944 : 0);
    py = y + 0x7B7;
    ret = func_001B3CC0(ret, &D_00290A6C, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    tx = x + 0x20;
    ty = y + 0x99;
    return func_001B6F70(ret, tx, ty, 1, 0, func_0019BEF0((char *)text2), text2,
                         hint != 0 ? (s32)D_002BE944 : 0);
}
#pragma optimization_level reset

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001CB6B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001CB6B0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001CB6B0;

typedef struct {
    Color_001CB6B0 color;
    Vertex_001CB6B0 xyz;
} Point_001CB6B0;

typedef struct {
    u64 tag[2];
    Point_001CB6B0 points[4];
    u64 end;
} Packet_001CB6B0;

typedef struct {
    u64 tag[2];
    Color_001CB6B0 color;
    Vertex_001CB6B0 xyz[2];
    u64 end;
} Rect_001CB6B0;

typedef struct {
    u8 b, g, r, a;
} Source_001CB6B0;

typedef struct {
    u8 pad[0xFEA3];
    u8 maps[5][7][7];
} Maps_001CB6B0;

static inline void set_color_001CB6B0(Color_001CB6B0 *a, Color_001CB6B0 *b,
                                      Source_001CB6B0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

static inline void set_xyz_001CB6B0(Vertex_001CB6B0 *v, s32 x, s32 y, u8 *state) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = *(s32 *)(state + 0xC58);
    v->fog = 0;
}

static inline void set_corner_001CB6B0(Vertex_001CB6B0 *v, s32 x, s32 y) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = D_003180E8;
    v->fog = 0;
}

s32 lSzDuel_DrawCustomDuel_Menu_SelectMapEdit_Pipe(s32 id, s32 player, s32 x, s32 y) {
    extern s32 *func_001FEAB0(s32);
    extern s32 func_001FE7D0(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001B6EA0(s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B65F0(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern u8 D_00290080[];
    extern u8 D_002BE8C0[];
    extern char D_002BF074[];
    extern char D_002BEF93[];
    extern s32 D_002902C4;
    extern s32 D_00290256;
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s32 ret;
    u8 *state = D_00317490.b;
    u8 *save = (u8 *)0xA9C000;
    Maps_001CB6B0 *maps;
    s8 *text1;
    s8 *text2;
    s32 sel;
    s32 hint = 0;
    s32 tx;
    s32 ty;
    s32 i;
    s32 j;
    s32 row;
    s32 count;
    s32 n;
    s32 hl;
    u8 *board;
    s32 px;
    s32 py;
    s32 w;
    s32 h;
    Rect_001CB6B0 rect __attribute__((aligned(8)));
    Packet_001CB6B0 packet __attribute__((aligned(8)));

    maps = func_002145E0(0);
    text1 = D_002BF074;
    text2 = D_002BEF93;
    sel = (*(u8 *)0xA9C08C + 2) % *(u8 *)0xA9C08D;
    id = func_001FD680(id, 1, 0x88, 0, 0x16);
    id = func_0020F290(func_001FD680(id, 2, 0x8B, 0, 0x2C));
    id = func_001B4780(id, 0xC, 3, 4, x + 0xBA, y, -0xD0, -0x20, 1);
    id = func_001FE7D0(id, 1, x + 0x122 - (func_001FEAB0(1)[3] >> 1), y + 5, 0, SzMsg_DrawRect_Pipe);
    func_001FEAF0(1);
    py = y + 0x20;
    id = func_001B4780(id, player, -1, 0xB, x, py, -0x244, -0xAA, 1);
    py = y + 0x35;
    id = func_001B4780(id, 0xC, -1, 6, x + 0x5D, py, -0xEC, -0x7C, 1);
    px = x + 0x71D;
    py = y + 0x789;
    ((Tag_001CB6B0 *)rect.tag)->flags = 6;
    ((Tag_001CB6B0 *)rect.tag)->count = 3;
    ((Tag_001CB6B0 *)rect.tag)->registers = 0x441;
    ((Tag_001CB6B0 *)rect.tag)->padding = 0;
    rect.color.r = 0x80;
    rect.color.g = 0;
    rect.color.b = 0;
    rect.color.a = 0x80;
    rect.color.q = 1.0f;
    set_corner_001CB6B0(&rect.xyz[0], px, py);
    set_corner_001CB6B0(&rect.xyz[1], px + 0xF0, py + 0x18);
    id = func_00207650(id, (s32)rect.tag, 0, 0);
    py = y + 0x35;
    id = func_001B4780(id, -1, -1, 6, x + 0x5D, py, -0xEC, -0x7C, hint != 0 ? 0 : 1);
    for (i = 0; i < 5; i++) {
        hl = (i == 2) ? 0 : (s32)D_002BE944;
        n = (save[0x8C] + i) % save[0x8D];
        id = func_001FE7D0(id, 2, x + 0x69, y + 0x3A + i * 0x18, hl, SzMsg_DrawRect_Pipe);
        id = func_001B6CA0(id, x + 0x119, y + 0x3A + i * 0x18, 2, n, 0, 1, hl);
    }
    func_001FEAF0(2);
    py = y + 0x78D;
    id = func_001B3CC0(id, &D_002902C4, x + 0x71F, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x78D;
    id = func_001B3CC0(id, &D_002902C4, x + 0x803, py, 0, 1, 0, 0, 1, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    board = &maps->maps[sel][0][0];
    px = x + 0x81C;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            id = func_001B3CC0(id, D_00290080 + (board[i * 7 + j] + 0x10E) * 10, px + j * 16,
                               y + 0x75C + i * 16, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        }
    }
    py = y + 0x35;
    id = func_001B4780(id, -1, 1, 1, x + 0x155, py, -0x76, -0x76, 1);
    py = y + 0x7C7;
    id = func_001B3CC0(id, &D_00290256, x + 0x834, py, 0, 1, 0, 0, 0, 1, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    for (row = 0; row < 10; row++) {
        count = 0;
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                if (row == board[i * 7 + j]) {
                    count++;
                }
            }
        }
        id = func_001B3CC0(id, D_00290080 + (row + 0x10E) * 10, x + 0x89B, y + 0x745 + row * 16, 0, 1, 0,
                           0, 0, 0, 1, 0, -1, 0x80);
        id = func_001B4780(id, 0xD, -1, 5, x + 0x1EB, y + 0x25 + row * 16, -0x54, -0x10, 1);
        px = x + 0x8AB;
        py = y + 0x745 + row * 16;
        w = (s32)((f32)count * 84.0f / 49.0f);
        h = 8;
        ((Tag_001CB6B0 *)packet.tag)->flags = 0x14;
        ((Tag_001CB6B0 *)packet.tag)->count = 8;
        ((Tag_001CB6B0 *)packet.tag)->registers = 0x41414141;
        ((Tag_001CB6B0 *)packet.tag)->padding = 0;
        set_color_001CB6B0(&packet.points[0].color, &packet.points[1].color, &((Source_001CB6B0 *)D_002BE8C0)[row * 3]);
        set_color_001CB6B0(&packet.points[2].color, &packet.points[3].color, &((Source_001CB6B0 *)D_002BE8C0)[row * 3 + 1]);
        set_xyz_001CB6B0(&packet.points[0].xyz, px, py, state);
        set_xyz_001CB6B0(&packet.points[1].xyz, px + w, py, state);
        set_xyz_001CB6B0(&packet.points[2].xyz, px, py + h, state);
        set_xyz_001CB6B0(&packet.points[3].xyz, px + w, py + h, state);
        id = func_00207650(id, (s32)packet.tag, 0, 0);
        set_color_001CB6B0(&packet.points[0].color, &packet.points[1].color, &((Source_001CB6B0 *)D_002BE8C0)[row * 3 + 1]);
        set_color_001CB6B0(&packet.points[2].color, &packet.points[3].color, &((Source_001CB6B0 *)D_002BE8C0)[row * 3 + 2]);
        set_xyz_001CB6B0(&packet.points[0].xyz, px, py + h, state);
        set_xyz_001CB6B0(&packet.points[1].xyz, px + w, py + h, state);
        set_xyz_001CB6B0(&packet.points[2].xyz, px, py + h * 2, state);
        set_xyz_001CB6B0(&packet.points[3].xyz, px + w, py + h * 2, state);
        id = func_00207650(id, (s32)packet.tag, 0, 0);
        id = func_001B4780(id, -1, -1, 5, x + 0x1EB, y + 0x25 + row * 16, -0x54, -0x10, 1);
        id = func_001B6EA0(id, x + 0x215, y + 0x27 + row * 16, 0, 2, 2, count);
    }
    id = func_001B65F0(id, player, x + 6, y + 0x26, -0x4E, -0x9E, -1, 0);
    py = y + 0x76E;
    id = func_001B3CC0(id, &D_00290A62, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x77E;
    ret = func_001B3CC0(id, &D_00290A58, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    tx = x + 0x20;
    ty = y + 0x58;
    ret = func_001B6F70(ret, tx, ty, 1, 0, func_0019BEF0((char *)text1), text1,
                       hint != 0 ? (s32)D_002BE944 : 0);
    py = y + 0x7B7;
    ret = func_001B3CC0(ret, &D_00290A6C, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    tx = x + 0x20;
    ty = y + 0x99;
    return func_001B6F70(ret, tx, ty, 1, 0, func_0019BEF0((char *)text2), text2,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

void lSzDuel_DrawCustomDuel_Exit_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 lSzDuel_DrawDialog_Window_Pipe(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    s32 text = (s32)D_002BEF98;
    s8 *text2 = D_002BEF6F;
    s8 *text3 = D_002BEF73;
    s32 id;

    arg0 = lSzDuel_DrawDialog_Window_Pipe(arg0, 2, -1, 0x91, arg1 + 0x140, arg2 + 0x94, 0x140, 0x98,
                         func_0019BEF0((char *)text), text, 0);
    id = SzDuel_DrawWindow_Font_Pipe(arg0, arg1 + 0xF0, arg2 + 0x108, 2, 3, func_0019BEF0((char *)text2), text2,
                       *(u8 *)0xA9C08E != 0 ? 0 : (s32)D_002BE944);
    SzDuel_DrawWindow_Font_Pipe(id, arg1 + 0x190, arg2 + 0x108, 2, 3, func_0019BEF0((char *)text3), text3,
                  *(u8 *)0xA9C08E != 0 ? (s32)D_002BE944 : 0);
}

typedef struct {
    u8 enabled : 1;
} Flags_001CC4B0;

typedef struct {
    f32 data[4];
} Vec4_001CC4B0;

extern Vec4_001CC4B0 D_002914B0;
extern Vec4_001CC4B0 D_002914C0;

void SzDuel_InitMapEdit(s32 arg0) {
    u8 *state = D_00317490.b;
    s32 i;
    Vec4_001CC4B0 vector0;
    Vec4_001CC4B0 vector1;

    vector0 = D_002914B0;
    vector1 = D_002914C0;
    i = 0;
    do {
        SzModel_SetDrawFlag(i, 0);
        i++;
    } while (i < 0x54);
    i = 0;
    do {
        SzModel_SetDrawFlag(i, 1);
        i++;
    } while (i < 5);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x4A, 1);
        i++;
    } while (i < 0xA);
    SzView_SetCP(0, vector0.data);
    SzView_SetLookSP(0, vector1.data);
    *(s8 *)0xA9C08F = 3;
    *(s8 *)0xA9C090 = 3;
    *(s8 *)0xA9C091 = 0;
    ((Flags_001CC4B0 *)0xA9C092)->enabled = 0;
    SzDuel_InitMapColor2(0, 0, 1, 0);
    state[0xD57] = 0x63;
    if (arg0 != 0) {
        *(u8 *)0xA9C08D = 5;
        *(u8 *)0xA9C08C = *(u8 *)0xA9C08D - 2;
    }
    state[0xD63] = 0;
}

void SzDuel_TermMapEdit(void) {

}

typedef struct {
    s8 first : 2;
    s8 second : 2;
    s8 unused : 4;
} PulseFlags_001CC620;

typedef struct {
    u8 padding[0xC86];
    u16 first;
    u16 second;
    u8 padding2[0xD63 - 0xC8A];
    u8 active;
    PulseFlags_001CC620 flags;
} State_001CC620;

typedef struct {
    u8 diagonal : 1;
    u8 unused : 7;
} InputFlags_001CC620;

extern u16 D_00318118;
extern u8 D_003181F3;
extern PulseFlags_001CC620 D_003181F4;

#pragma conditional_move off

void SzDuel_ActMapEdit(void) {
    extern void *SzData_GetData(s32);
    extern s32 SzDuel_SetField();
    State_001CC620 *state = (State_001CC620 *)D_00317490.b;
    s32 row;
    s32 column;
    u8 *cell;
    u8 *rowStart;
    s32 value;
    s32 positive;
    s32 step;
    u8 tile;
    u16 buttons;
    State_001CC620 *p;
    State_001CC620 *p2;

    {
        p = (State_001CC620 *)D_00317490.b;
        if (D_003181F3 != 0) {
            p->flags.first = 1;
        }
        value = p->first + (p->flags.first << 9);
        p->first = (value > 0 ? value : 0) < 0x8000 ?
            (value > 0 ? value : 0) : 0x8000;
        if (p->first == 0 || p->first >= 0x8000) {
            p->flags.first = (s8)-p->flags.first;
        }
    }
    {
        p2 = (State_001CC620 *)D_00317490.b;
        step = D_003181F4.second << 11;
        p2->second = (D_00318118 + step > 0 ? p2->second + step : 0) < 0x8000 ?
            (p2->second + step > 0 ? p2->second + step : 0) : 0x8000;
        if (p2->second == 0 || p2->second >= 0x8000) {
            p2->flags.second = (s8)-p2->flags.second;
        }
    }
    if (*(u8 *)0xA9C091 != 0) {
        --*(u8 *)0xA9C091;
    }
    if (SzPad_Check(0, 0, 0x8C0) != 0) {
        rowStart = (u8 *)SzData_GetData(0) +
            ((*(u8 *)0xA9C08C + 2) % *(u8 *)0xA9C08D) * 49;
        row = 0;
        do {
            column = 0;
            cell = rowStart;
            do {
                cell[0xFEA3] = SzDuel_GetField(column, row);
                ++column;
                ++cell;
            } while (column < 7);
            ++row;
            rowStart += 7;
        } while (row < 7);
        SzSound_PlaySE(0, 4);
        SzGame_Pop();
        return;
    }
    if (SzPad_Check(0, 0, 0x20) != 0) {
        SzSound_PlaySE(0, 5);
        SzGame_Pop();
        return;
    }
    if (SzPad_Check(0, 2, 0xC) != 0) {
        tile = SzDuel_GetField(*(u8 *)0xA9C08F, *(u8 *)0xA9C090);
        if (SzPad_Check(0, 2, 4) != 0) {
            tile = (tile + 9) % 10;
        }
        if (SzPad_Check(0, 2, 8) != 0) {
            tile = (tile + 11) % 10;
        }
        SzSound_PlaySE(0, 3);
        SzDuel_SetField(*(u8 *)0xA9C08F, *(u8 *)0xA9C090, tile);
    }
    if (*(u8 *)0xA9C091 == 0) {
        buttons = SzPad_Check(0, 1, 0xFFFF);
        if (buttons & 0xF000) {
            if (((buttons & 0x8000) && *(u8 *)0xA9C08F <= 0) ||
                ((buttons & 0x2000) && *(u8 *)0xA9C08F >= 6)) {
                buttons &= 0x5FFF;
            }
            if (((buttons & 0x1000) && *(u8 *)0xA9C090 <= 0) ||
                ((buttons & 0x4000) && *(u8 *)0xA9C090 >= 6)) {
                buttons &= 0xAFFF;
            }
            state->active = 60;
            if (((InputFlags_001CC620 *)0xA9C092)->diagonal) {
                if (buttons & 0x5000) {
                    buttons &= 0x5000;
                } else {
                    ((InputFlags_001CC620 *)0xA9C092)->diagonal = 0;
                }
            }
            if (buttons & 0xA000) {
                if (buttons & 0x8000) {
                    --*(u8 *)0xA9C08F;
                } else {
                    ++*(u8 *)0xA9C08F;
                }
                if (buttons & 0x5000) {
                    ((InputFlags_001CC620 *)0xA9C092)->diagonal = 1;
                }
            } else if (buttons & 0x5000) {
                if (buttons & 0x1000) {
                    --*(u8 *)0xA9C090;
                } else {
                    ++*(u8 *)0xA9C090;
                }
                ((InputFlags_001CC620 *)0xA9C092)->diagonal = 0;
            } else {
                ((InputFlags_001CC620 *)0xA9C092)->diagonal = 0;
                return;
            }
            SzSound_PlaySE(0, 3);
            *(u8 *)0xA9C091 = 8;
        }
    }
}
#pragma conditional_move reset

void SzDuel_DrawMapEdit(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawMapEdit_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001CCBB0;

typedef struct {
    u8 pad0[0x8F];
    u8 x;
    u8 y;
} Cursor_001CCBB0;

static inline s32 title_001CCBB0(s32 id, s32 text, s32 x, s32 y) {
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    s32 width;
    s32 result;
    f32 scale;

    scale = 1.0f;
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(id, 1, text + 0x47, 0, 0x16));
    id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, 2, 3, x, y, 9, 0x12, 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 5, -1, 3, x, y + 0x40, 9, 2, 1);
    width = ((s32 *)SzMsg_GetInfo(1))[3];
    if (width > 0x54) {
        scale = 84.0f / (f32)width;
    }
    result = SzMsg_DrawRatioX_Pipe(id, 1, (x + 0x30) - (s32)((f32)(width >> 1) * scale), y + 0x43,
                           scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    return result;
}

s32 SzDuel_DrawMapEdit_Pipe(s32 arg0) {
    extern Color_001CCBB0 D_002914D0;
    extern u16 D_00318116;
    extern s32 lSzDuel_DrawWindow_FieldPiece_Pipe(s32, s32, s32, s32, s32, f32);
    extern s32 lSzDuel_DrawMapEdit_Graph_Pipe(s32, s32, s32);
    extern s32 SzDuel_SetMapColor2();
    Cursor_001CCBB0 *cursor = (Cursor_001CCBB0 *)0xA9C000;
    Color_001CCBB0 color;
    s32 x;
    s32 y;
    s32 id;
    s32 timer;
    s32 hint = 0;

    timer = D_00318116;
    color = D_002914D0;
    color.a = hint != 0 ? 0x80 : (u8)(((timer >> 8) & 0xFF) + 0x40);
    SzDuel_InitMapColor2(0, 0, 0, 0);
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 7; x++) {
            if (cursor->x == x || cursor->y == y) {
                SzDuel_SetMapColor2(x, y, 1, &color, 0, 0);
            }
        }
    }
    SzDuel_SetMapColor2(cursor->x, cursor->y, 1, &color, 0, 0);
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 7; x++) {
            SzDuel_CalcMapColor(x, y);
        }
    }
    SzDuel_SetWindowDefPrioZ(0xFFFFF8);
    arg0 = lSzDuel_DrawWindow_FieldPiece_Pipe(arg0, 0, SzDuel_GetField(cursor->x, cursor->y), 6, 0x150, 100.0f);
    id = SzDuel_StartWindowSessionWithPalette_Pipe(arg0, 0);
    id = title_001CCBB0(id, SzDuel_GetField(cursor->x, cursor->y), 6, 0x150);
    id = lSzDuel_DrawMapEdit_Graph_Pipe(lSzDuel_DrawWindow_CommandGuide_Pipe(id, 0, 0x21A, 0x150), 6, 0x90);
    SzMsg_Free(0);
    return id;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001CCEA0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001CCEA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001CCEA0;

typedef struct {
    Color_001CCEA0 color;
    Vertex_001CCEA0 xyz;
} Point_001CCEA0;

typedef struct {
    u64 tag[2];
    Point_001CCEA0 points[4];
    u64 end;
} Packet_001CCEA0;

typedef struct {
    u8 b, g, r, a;
} Source_001CCEA0;

static inline void set_color_001CCEA0(Color_001CCEA0 *a, Color_001CCEA0 *b,
                                      Source_001CCEA0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

static inline void set_xyz_001CCEA0(Vertex_001CCEA0 *v, s32 x, s32 y, u8 *state) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = *(s32 *)(state + 0xC58);
    v->fog = 0;
}

s32 lSzDuel_DrawMapEdit_Graph_Pipe(s32 arg0, s32 x, s32 y) {
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe(s32, s32, s32, s32, s32, s32, s32);
    extern u8 D_00290080[];
    extern u8 D_002BE8C0[];
    u8 *state = D_00317490.b;
    u8 cur;
    s32 j;
    s32 i;
    s32 row;
    s32 count;
    s32 px;
    s32 py;
    s32 w;
    s32 h;
    s32 id;
    Packet_001CCEA0 packet __attribute__((aligned(8)));

    cur = SzDuel_GetField(*(u8 *)0xA9C08F, *(u8 *)0xA9C090);
    id = lSzDuel_DrawWindow_Frame_Pipe(arg0, 0, -1, 0xB, x, y, -0x6E, -0xAA, 1);
    for (row = 0; row < 10; row++) {
        count = 0;
        for (j = 0; j < 7; j++) {
            for (i = 0; i < 7; i++) {
                if (row == SzDuel_GetField(i, j)) {
                    count++;
                }
            }
        }
        px = x + 0x6C5;
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, D_00290080 + (row + 0x10E) * 10, px, y + 0x725 + row * 16, 0, 1, 0,
                           0, 0, 0, 1, 0, (cur == row) ? 1 : -1, 0x80);
        id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xD, -1, 5, x + 0x15, y + 5 + row * 16, -0x54, -0x10, 1);
        px = x + 0x6D5;
        py = y + 0x725 + row * 16;
        w = (s32)((f32)count * 84.0f / 49.0f);
        h = 8;
        ((Tag_001CCEA0 *)packet.tag)->flags = 0x14;
        ((Tag_001CCEA0 *)packet.tag)->count = 8;
        ((Tag_001CCEA0 *)packet.tag)->registers = 0x41414141;
        ((Tag_001CCEA0 *)packet.tag)->padding = 0;
        set_color_001CCEA0(&packet.points[0].color, &packet.points[1].color, &((Source_001CCEA0 *)D_002BE8C0)[row * 3]);
        set_color_001CCEA0(&packet.points[2].color, &packet.points[3].color, &((Source_001CCEA0 *)D_002BE8C0)[row * 3 + 1]);
        set_xyz_001CCEA0(&packet.points[0].xyz, px, py, state);
        set_xyz_001CCEA0(&packet.points[1].xyz, px + w, py, state);
        set_xyz_001CCEA0(&packet.points[2].xyz, px, py + h, state);
        set_xyz_001CCEA0(&packet.points[3].xyz, px + w, py + h, state);
        id = ExSortPrim_Pipe(id, (s32)packet.tag, 0, 0);
        set_color_001CCEA0(&packet.points[0].color, &packet.points[1].color, &((Source_001CCEA0 *)D_002BE8C0)[row * 3 + 1]);
        set_color_001CCEA0(&packet.points[2].color, &packet.points[3].color, &((Source_001CCEA0 *)D_002BE8C0)[row * 3 + 2]);
        set_xyz_001CCEA0(&packet.points[0].xyz, px, py + h, state);
        set_xyz_001CCEA0(&packet.points[1].xyz, px + w, py + h, state);
        set_xyz_001CCEA0(&packet.points[2].xyz, px, py + h * 2, state);
        set_xyz_001CCEA0(&packet.points[3].xyz, px + w, py + h * 2, state);
        id = ExSortPrim_Pipe(id, (s32)packet.tag, 0, 0);
        id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, -1, 5, x + 0x15, y + 5 + row * 16, -0x54, -0x10, 1);
        id = SzDuel_DrawWindow_FontDigit_Pipe(id, x + 0x3F, y + 7 + row * 16, 0, 2, 2, count);
    }
    return id;
}

typedef struct Draw_001CD560 {
    s32 f00;
    s32 f04;
    s32 f08;
    f32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    s32 f3C;
    u8 g40;
    u8 g41;
    u8 g42;
    u8 alpha;
    u8 g44;
    u8 g45;
    u8 g46;
    u8 g47;
    u16 h48;
    u16 h4A;
    s32 f4C;
    s64 d50;
    u8 pad58[0x20];
    s32 p78;
    s32 p7C;
    s16 a80 : 12;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
    s16 a82 : 12;
    u8 b83a : 2;
    s8 b83c : 1;
    s8 b83d : 1;
} Draw_001CD560;

s32 SzDuel_ClearDrawCard(void *arg0) {
    Draw_001CD560 *p;

    if (arg0 == NULL) {
        return 0;
    }
    p = arg0;
    p->f00 = 0;
    p->f04 = 0;
    p->f08 = 0;
    p->f0C = 1.0f;
    p->f10 = 0x4000;
    p->f14 = 0;
    p->f18 = 0;
    p->f1C = 0;
    p->f20 = 0;
    p->f24 = 0;
    p->f28 = 0;
    p->f2C = 0;
    p->f30 = 0.1f;
    p->f34 = 0.1f;
    p->f38 = 1.0f;
    p->f3C = 0;
    p->g42 = 0x80;
    p->g41 = 0x80;
    p->g40 = 0x80;
    p->alpha = 0x80;
    p->g46 = 0;
    p->g45 = 0;
    p->g44 = 0;
    p->g47 = 0;
    p->h4A = 7;
    p->h48 = 0;
    p->d50 = 0;
    p->f4C = 0;
    p->p78 = 0x70002000;
    p->p7C = 0x70000000;
    p->a80 = 0xAA;
    p->a82 = 0;
    p->b83a = 1;
    p->horizontal = 1;
    p->enabled = 0;
    p->colored = 1;
    p->reserved = 1;
    p->b83c = 0;
    p->b83d = 0;
    return 1;
}

void SzDuel_DrawAllCard(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawAllCard_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct Vec4_001CD710 {
    f32 x, y, z, w;
} Vec4_001CD710;

typedef struct Command_001CD710 {
    __int128 position;
    u8 pad10[0x33];
    u8 flags;
    u8 pad44[0x4C];
} Command_001CD710;

typedef struct Flags_001CD710 {
    s8 low : 6;
    s8 active : 1;
    s8 high : 1;
} Flags_001CD710;

typedef struct Object_001CD710 {
    u8 pad00[4];
    Command_001CD710 *command;
    u8 pad08[0x3C];
    u8 field44;
    u8 field45;
    u8 pad46[0x11];
    Flags_001CD710 flags;
} Object_001CD710;

s32 SzDuel_DrawHandCard_Pipe(s32);

s32 SzDuel_DrawAllCard_Pipe(s32 arg0) {
    extern s32 SzDuel_DrawHandCard_Pipe(s32);
    Vec4_001CD710 position;
    Command_001CD710 command;
    u8 *base = D_00317490.b;
    u8 *selected = D_00317490.b + D_003181E4 * 0x350;
    s32 original;
    s64 mode;
    s32 special;
    s32 value;
    s32 final_value;
    Object_001CD710 *object;
    extern s32 SzView_GetCP();
    extern s32 SzDuel_DrawCard_Pipe();
    extern s32 ExSortAnchor_Pipe();

    mode = SzGame_GetMode(1);
    original = arg0;
    switch (mode) {
    case 1:
    case 0:
        if (SzModel_GetDrawFlag(0) == 0) {
            return original;
        }
        arg0 = ExSetAnchor_Pipe(arg0);
        arg0 = SzDuel_StartCardSession_Pipe(arg0);
        arg0 = SzDuel_DrawCardRequest_Pipe(arg0);
        arg0 = RhBase_SetZBufferMode(arg0, 1);
        SzDuel_GetUnitPos(0, 0, &position.x);
        position.y = 0.0f;
        arg0 = SzDuel_DrawLeaderBase_Pipe(arg0, 0, &position.x, 0x80, 1);
        SzDuel_GetUnitPos(1, 0, &position.x);
        position.y = 0.0f;
        value = RhBase_SetZBufferMode(SzDuel_DrawLeaderBase_Pipe(arg0, 1, &position.x, 0x80, 1), 0);
        if (*(Object_001CD710 **)(base + 0x6C8) != NULL) {
            if ((*(Object_001CD710 **)(base + 0x6C8))->flags.active != 0) {
                special = 0;
                if (base[0xD57] == 0x1D && SzView_InqRequest(-1, -1) != NULL) {
                    special = 1;
                }
                if (special != 0) {
                    position = *(Vec4_001CD710 *)SzView_GetCP(0);
                } else {
                    SzDuel_CalcUnitPos(selected[0x33D], selected[0x33E], 0, &position);
                }
                position.y = 1.0f;
                object = *(Object_001CD710 **)(base + 0x6C8);
                if (object->field45 == 0) {
                    value = RhBase_SetZBufferMode(value, 1);
                    value = SzDuel_DrawLeaderBase_Pipe(value, (*(Object_001CD710 **)(base + 0x6C8))->field44, &position.x, 0x40, 0);
                    value = RhBase_SetZBufferMode(value, 0);
                } else if (object->command != NULL) {
                    command = *object->command;
                    command.flags = ((s32)command.flags << 6) >> 7;
                    *(__int128 *)&command = *(__int128 *)&position;
                    object = SzDuel_GetCardNode(&command, 1) ? object : NULL;
                    value = SzDuel_SetupCard2_Pipe(value, (s32)object, &command);
                    value = RhBase_SetZBufferMode(value, 1);
                    value = SzDuel_DrawCard_Pipe(value, &command);
                    value = RhBase_SetZBufferMode(value, 0);
                }
            }
        }
        final_value = SzDuel_FinishCardSession_Pipe(SzDuel_DrawHandCard_Pipe(value));
        return ExSortAnchor_Pipe(final_value, original, ExGetMyOT(), 0xFFFFFF);
    default:
        return original;
    }
}

void SzDuel_InitCardRequest(void) {
    u8 *entry;
    s32 i;

    entry = D_003193C0;
    i = 0;
    do {
        SzDuel_FreeCardRequest(entry);
        i += 1;
        entry += 0xA0;
    } while (i < 0x20);
}

s32 SzDuel_FreeCardRequest(void *arg0) {
    extern void SzDuel_ClearDrawCard();

    if (arg0 == NULL) {
        return 0;
    }
    SzDuel_ClearDrawCard();
    *(s32 *)((u8 *)arg0 + 0x90) = 0;
    return 1;
}


typedef struct {
    u8 pad_00[0x90];
    s32 in_use;
    u8 pad_94[0xC];
} Slot_001CDAA0;

u8 *SzDuel_GetCardRequest(void) {
    s32 i;
    Slot_001CDAA0 *slot;

    slot = (Slot_001CDAA0 *)D_003193C0;
    i = 0;
    do {
        if (slot->in_use == 0) {
            SzDuel_ClearDrawCard(slot);
            return (u8 *)slot;
        }
        i += 1;
        slot++;
    } while (i < 0x20);
    return NULL;
}

typedef struct {
    s8 unused : 4;
    u8 mode : 2;
    s8 unused6 : 1;
    s8 set : 1;
} Flags_001CDB00;

typedef struct {
    u8 r, g, b, a;
} Color_001CDB00;

typedef struct {
    f32 value;
} PackedColor_001CDB00;

typedef union {
    struct {
        f32 x, y, z, w;
    } value;
    __int128 quad;
} Vector_001CDB00;

typedef struct {
    Vector_001CDB00 position;
    u8 pad10[0x33];
    u8 visible;
    Color_001CDB00 color;
    u8 pad48[0x39];
    Flags_001CDB00 flags81;
    u8 pad82;
    Flags_001CDB00 flags83;
    u8 pad84[0xC];
} Draw_001CDB00;

typedef struct {
    u8 pad00[0x34];
    s16 x, z;
    u8 pad38[8];
    u8 index40, index41;
    u8 pad42[7];
    u8 color49, color4A;
    u8 pad4B[0xC];
    Flags_001CDB00 flags57;
} Unit_001CDB00;

typedef struct {
    Draw_001CDB00 draw;
    Unit_001CDB00 *unit;
    u8 pad94[0xC];
} Entry_001CDB00;

extern f32 D_002914D8;

s32 SzDuel_DrawCardRequest_Pipe(s32 arg0) {
    Draw_001CDB00 draw;
    PackedColor_001CDB00 color;
    Entry_001CDB00 *entry;
    s32 i;
    void *position;
    s32 height;

    entry = (Entry_001CDB00 *)D_003193C0;
    i = 0;
    color = *(PackedColor_001CDB00 *)&D_002914D8;
    do {
        if (entry->unit != NULL) {
            Unit_001CDB00 *unit = entry->unit;

            position = SzDuel_GetMapInfo(unit->index40, unit->index41);
            draw = entry->draw;
            if (!draw.flags83.set && (!draw.flags81.set || draw.visible != 0)) {
                if (!unit->flags57.set) {
                    if (position != NULL) {
                        height = *(s16 *)((u8 *)position + 0x14);
                        height = height > 0 ? height : 0;
                        draw.position.value.y = (f32)(height * 35) / 128.0f;
                        if (unit->color49 != 0 || unit->color4A != 0) {
                            draw.flags83.mode = 3;
                            draw.color = *(Color_001CDB00 *)&color;
                        }
                    }
                    draw.position.value.x += (f32)unit->x;
                    draw.position.value.z += (f32)unit->z;
                }
                arg0 = SzDuel_SetupCard2_Pipe(arg0, (s32)(SzDuel_GetCardNode(&draw, 1) ? unit : NULL), &draw);
                arg0 = RhBase_SetZBufferMode(arg0, 1);
                arg0 = SzDuel_DrawCard_Pipe(arg0, (s32)&draw);
                arg0 = RhBase_SetZBufferMode(arg0, 0);
            }
        }
        i++;
        entry++;
    } while (i < 32);
    return arg0;
}
