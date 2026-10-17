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

typedef struct Header_001C3E20 {
    u16 type;
    u16 count;
    u32 pad;
    u64 registers;
} Header_001C3E20;

typedef struct Vertex_001C3E20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C3E20;

typedef struct Packet_001C3E20 {
    Header_001C3E20 header;
    u8 r, g, b, a;
    f32 q;
    Vertex_001C3E20 first;
    Vertex_001C3E20 second;
} Packet_001C3E20;

typedef struct Labels_001C3E20 {
    s8 *text[3];
} Labels_001C3E20;

typedef struct Work_001C3E20 {
    Labels_001C3E20 labels;
    Packet_001C3E20 packet;
} Work_001C3E20;

static inline s32 side_001C3E20(s32 player, s32 left, s32 right) {
    return player != 0 ? right : left;
}

#define SIDE_001C3E20(left, right) side_001C3E20(arg1, left, right)

static inline s32 text_001C3E20(s32 cursor, s32 x, s32 y, s32 align,
                               s32 flags, s8 *text, void *color) {
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    s32 length = func_0019BEF0((char *)text);
    return SzDuel_DrawWindow_Font_Pipe(cursor, x, y, align, flags,
                        length, text, color);
}

static inline s32 total_001C3E20(s32 player) {
    u8 *state = D_00317490.b;
    u8 *cards;
    s32 total;
    s32 i;

    if (player != 0) {
        cards = *(u8 **)(state + 0x6E4);
    } else {
        cards = *(u8 **)(state + 0x6E0);
    }
    total = 0;
    i = 0;
    do {
        total += *cards++;
        i++;
    } while (i < 0x356);
    return total;
}

static inline s32 number_001C3E20(s32 cursor, s32 x, s32 y, s32 player) {
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    s32 count = SzData_GetBagCountAll(player);
    return SzDuel_DrawWindow_FontDigit_Pipe(cursor, x, y, 1, 0, 4, count);
}

static inline s32 rectangle_001C3E20(s32 cursor, Packet_001C3E20 *packet,
                                    s32 x, s32 y, u8 *data) {
    ((Header_001C3E20 *)(s32)&packet->header)->count = 6;
    ((Header_001C3E20 *)(s32)&packet->header)->type = 3;
    ((Header_001C3E20 *)(s32)&packet->header)->registers = 0x441;
    ((Header_001C3E20 *)(s32)&packet->header)->pad = 0;
    packet->r = 0xA0;
    packet->g = 0xA0;
    packet->b = 0xA0;
    packet->a = 0x80;
    packet->q = 1.0f;
    packet->first.x = (x + 0x6CA) << 4;
    packet->first.y = (y + 0x738) << 4;
    packet->first.z = *(s32 *)(data + 0xC58);
    packet->first.fog = 0;
    packet->second.x = (x + 0x6F2) << 4;
    packet->second.y = (y + 0x739) << 4;
    packet->second.z = *(s32 *)(data + 0xC58);
    packet->second.fog = 0;
    return ExSortPrim_Pipe(cursor, (s32)&packet->header, 0, 0);
}

#pragma opt_propagation off

s32 lSzDuel_DrawTrade_Bag_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe();
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern s32 lSzDuel_DrawTrade_Card_Pipe();
    extern u8 D_00290080[];
    extern u8 D_00290828[];
    extern u8 D_00290832[];
    extern u8 D_0029086E[];
    extern u8 D_00290896[];
    extern u8 D_002908A0[];
    extern u8 D_00290A6C[];
    extern u8 D_00290AA8[];
    extern u8 D_00290AB2[];
    extern u8 D_00290ABC[];
    extern u8 D_00290AC6[];
    extern s8 *D_00290FD0[];
    extern Labels_001C3E20 D_00291490;
    extern u8 D_002BE8A4[];
    extern char D_002BF021[];
    extern char D_002BF024[];
    extern u8 D_0031814E[];
    u8 *data;
    char *descText;
    s8 *sortText;
    s32 flags;
    u16 *list;
    u16 top;
    u16 count;
    u8 pos;
    u8 *state;
    s32 x;
    s32 special;
    s32 style;
    s32 sortY;
    u8 *color;
    s32 labelY;
    s32 labelX;
    s32 active;
    s8 *subText;
    s32 textX;
    s32 textY;
    s32 barY;
    s8 **labelPtr;
    s8 *labelText;
    s32 pageX;
    s32 sortIndex;
    u8 *sortData;
    s32 barX;
    s32 cardY;
    s32 cursor;
    s32 selection;
    s32 sortX;
    s32 cardX;
    s32 pageY;
    s8 *titleText;
    s32 enabled;
    Work_001C3E20 work;

    data = D_00317490.b;
    special = (D_0031814E[arg1] == 1) ? 1 : 0;
    enabled = 0;
    if (special != 0) {
        if (SzPad_Check(arg1, 1, 0x100) != 0) {
            enabled = 1;
        }
    }
    selection = enabled != 0 ? 1 : 0;
    color = NULL;
    if (selection != 0) {
        color = D_002BE8A4;
    } else {
        color = NULL;
    }
    if (arg1 != 0) {
        titleText = (s8 *)D_002BF021;
    } else {
        titleText = (s8 *)D_002BF024;
    }
    subText = D_002BF024 + 3;
    descText = D_002BEF98;
    work.labels = D_00291490;
    if (arg1 != 0) {
        list = *(u16 **)(data + 0x6DC);
    } else {
        list = *(u16 **)(data + 0x6D8);
    }
    top = arg1 != 0 ? *(u16 *)(data + 0xC8E) : *(u16 *)(data + 0xC8A);
    count = arg1 != 0 ? *(u16 *)(data + 0xC90) : *(u16 *)(data + 0xC8C);
    pos = arg1 != 0 ? data[0xD5F] : data[0xD5E];
    sortData = (arg1 != 0 ? data + 0xCB9 : data + 0xCB6) + selection;
    sortText = D_00290FD0[*sortData];
    flags = 3;
    textX = arg2 + SIDE_001C3E20(0x10, 0x240);
    textY = arg3 + 0x10;
    arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, 0xC, -1, 0xB, textX, textY, -0x30, -0x30, 1);
    textX = arg2 + SIDE_001C3E20(0x10, 0x240) + 0x18;
    textY = arg3 + 0x1F;
    cursor = text_001C3E20(arg0, textX, textY, 2, 3, titleText, NULL);
    x = arg2 + SIDE_001C3E20(0x40, 0x1B0);
    cursor = lSzDuel_DrawWindow_Frame_Pipe(cursor, 0xC, -1, 6, x, arg3 + 0x10, -0x8C, -0x2C, 1);
    textX = arg2 + SIDE_001C3E20(0x40, 0x1B0) + 0x48;
    textY = arg3 + 0x15;
    cursor = text_001C3E20(cursor, textX, textY, 1, 3, subText, NULL);
    textX = arg2 + SIDE_001C3E20(0x40, 0x1B0) + 0x24;
    textY = arg3 + 0x23;
    cursor = text_001C3E20(cursor, textX, textY, 1, 3, work.labels.text[1], NULL);
    textY = arg3 + 0x31;
    cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, textX, textY, 1, 2, 4, total_001C3E20(arg1));
    textX = arg2 + SIDE_001C3E20(0x40, 0x1B0) + 0x6C;
    textY = arg3 + 0x23;
    cursor = text_001C3E20(cursor, textX, textY, 1, 3, work.labels.text[2], NULL);
    textY = arg3 + 0x31;
    cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, textX, textY, 1, 2, 4, total_001C3E20(arg1 ^ 1));
    x = arg2 + SIDE_001C3E20(0x10, 0x230);
    cursor = lSzDuel_DrawWindow_Frame_Pipe(cursor, 0xC, -1, 5, x, arg3 + 0x40, -0x40, -0x14, 1);
    x = arg2 + 0x6C2 + SIDE_001C3E20(0x10, 0x230);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_0029086E, x, arg3 + 0x762, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    {
        s32 c = cursor;
        s32 x = arg2 + SIDE_001C3E20(0x10, 0x230) + 0x17;
        s32 y = arg3 + 0x44;
        cursor = number_001C3E20(c, x, y, arg1);
    }
    x = arg2 + SIDE_001C3E20(0x10, 0x230);
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 3, x, arg3 + 0x54, -0x40, -0x1C, -1, 0);
    x = arg2 + 0x6C0 + SIDE_001C3E20(0x15, 0x255);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AA8, x, arg3 + 0x77D, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = arg2 + 0x6C0 + SIDE_001C3E20(0x2C, 0x234);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290828, x, arg3 + 0x77C, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = arg2 + SIDE_001C3E20(0x50, 0x140);
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 3, x, arg3 + 0x40, -0xF0, -0x30, -1, 0);
    x = arg2 + 0x6CE + SIDE_001C3E20(0x50, 0x140);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290896, x, arg3 + 0x765, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = arg2 + 0x6C7 + SIDE_001C3E20(0x50, 0x140);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290ABC, x, arg3 + 0x77E, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    sortX = arg2 + 0x6E8 + SIDE_001C3E20(0x50, 0x140);
    sortY = arg3 + 0x769;
    sortIndex = 0;
    do {
        style = -1;
        if (sortIndex == *sortData) {
            style = selection != 0 ? 2 : 1;
        }
        cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290080 + (sortIndex + 0xD1) * 10, sortX, sortY,
                            0, 1, 0, 0, 0, 0, 1, color, style, 0x80);
        sortIndex++;
        sortX += 0x10;
    } while (sortIndex < 10);
    x = arg2 + 0x78A + SIDE_001C3E20(0x50, 0x140);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_002908A0, x, arg3 + 0x765, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = arg2 + 0x793 + SIDE_001C3E20(0x50, 0x140);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AC6, x, arg3 + 0x77E, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    sortX = arg2 + SIDE_001C3E20(0x50, 0x140) + 0x78;
    sortY = arg3 + 0x5E;
    if (color != NULL) {
        flags |= 8;
    }
    cursor = text_001C3E20(cursor, sortX, sortY, 0, flags, sortText, color);
    textX = arg2 + SIDE_001C3E20(8, 0x148);
    sortY = arg3 + 0x70;
    sortIndex = 0;
    do {
        cursor = lSzDuel_DrawTrade_Card_Pipe(cursor, arg1, list[top + sortIndex], textX, sortY, 1);
        sortY += 0x36;
        sortIndex++;
    } while (sortIndex < 5);
    x = arg2 + SIDE_001C3E20(0x10, 0x184);
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 3, x, arg3 + 0x17E, -0xEC, -0x32, -1, 0);
    x = arg2 + 0x6C0 + SIDE_001C3E20(0x2C, 0x234);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290832, x, arg3 + 0x8A2, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = arg2 + 0x6C0 + SIDE_001C3E20(0x15, 0x255);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AB2, x, arg3 + 0x8A7, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = arg2 + 0x6C0 + SIDE_001C3E20(0x17, 0x259);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290A6C, x, arg3 + 0x8BA, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    {
        s32 c = cursor;
        s32 x = arg2 + SIDE_001C3E20(0x2C, 0x231);
        s32 y = arg3 + 0x19D;
        cursor = text_001C3E20(c, x, y, 1, 0, (s8 *)descText, NULL);
    }
    labelX = arg2 + SIDE_001C3E20(0x7E, 0x18A);
    labelY = arg3 + 0x182;
    labelPtr = work.labels.text;
    sortIndex = 0;
    state = data + arg1;
    do {
        if (state[0xCC0] == sortIndex) {
            active = 1;
        } else {
            active = 0;
        }
        cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 3, labelX, labelY, -0x78, -0xE, -1, 1);
        labelText = *labelPtr;
        cursor = SzDuel_DrawWindow_Font_Pipe(cursor, labelX + 1, labelY + 1, 1, 0, func_0019BEF0((char *)labelText),
                                             labelText, active != 0 ? 0 : (s32)D_002BE944);
        sortIndex++;
        labelY += 0xE;
        labelPtr++;
    } while (sortIndex < 3);
    sortX = arg2 + SIDE_001C3E20(0xFC, 0x148);
    sortY = arg3 + 0x17E;
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 3, sortX, sortY, -0x3C, -0x32, -1, 0);
    if (count) {
        cursor = rectangle_001C3E20(cursor, &work.packet, sortX, sortY, data);
        pageX = arg2 + SIDE_001C3E20(0xFC, 0x148) + 0x1E;
        pageY = arg3 + 0x186;
        cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, pageX, pageY, 1, 2, 3, top + pos + 1);
        cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, pageX, pageY + 0x17, 1, 2, 3, count);
    }
    return cursor;
}
#pragma opt_propagation reset

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C4B00;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C4B00;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C4B00;

typedef struct {
    u64 tag[2];
    Color_001C4B00 color;
    Vertex_001C4B00 vertex0;
    Vertex_001C4B00 vertex1;
    u64 end;
} Box_001C4B00;

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001C4B00;

static inline s32 offset_001C4B00(s32 side, s32 left, s32 right) {
    return side != 0 ? right : left;
}

extern u8 D_00290020[];
extern u8 D_00290080[];
extern u8 D_0029086E[];
extern u8 D_00290878[];
extern u8 D_002908BE[];
extern u8 D_002908C8[];
extern s32 D_002908E6;
extern u8 D_002908F0[];
extern u8 D_00290A12[];
extern s8 D_002BF02D;
extern char D_002BF030[];
extern char D_002BE940[];
extern char D_002BE948[];

#pragma opt_dead_assignments off

s32 lSzDuel_DrawTrade_Card_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s64, s64, s64, s64, s64, s64);
    extern s32 func_001B4540(s32, s32, s32, s64, s32, s32);
    extern s32 func_001B6EA0();
    extern s32 func_001B6F70();
    extern s32 func_001B65F0();
    extern s32 func_001FEAB0();
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern s32 func_001DE090();
    extern s64 func_00215D30();
    s32 ret;
    s32 id3;
    u8 *state = D_00317490.b;
    u8 *info;
    s32 kind;
    s32 style;
    s32 attribute;
    u8 *name;
    u8 *own_counts;
    u8 *counts;
    u8 *other_counts;
    s8 *text;
    u8 mode;
    u8 category;
    s32 low;
    f32 scale;
    s32 px;
    s32 x_position;
    s32 py;
    s32 ty;
    u8 *count;
    s32 width;
    s32 id;
    Box_001C4B00 box __attribute__((aligned(8)));
    s32 value;
    s32 hint = 0;

    info = func_001DD0E0(arg2);
    if (arg1 != 0) {
        own_counts = *(u8 **)(state + 0x6E4);
    } else {
        own_counts = *(u8 **)(state + 0x6E0);
    }
    if (arg1 != 0) {
        other_counts = *(u8 **)(state + 0x6E0);
    } else {
        other_counts = *(u8 **)(state + 0x6E4);
    }
    mode = state[arg1 + 0xCC0];
    if (mode == 2) {
        counts = other_counts;
    } else {
        counts = own_counts;
    }
    if (mode == 2) {
        text = &D_002BF02D;
    } else {
        text = (s8 *)D_002BF030;
    }
    scale = 1.0f;
    if (info == NULL) {
        return func_001B4780(arg0, -1, -1, 9, arg3, arg4, -0x130, -0x36, 0);
    }
    category = info[0];
    kind = (s32)category >> 5;
    low = category & 0x1F;
    if (kind == 0) {
        name = D_00290080 + low * 10;
    } else {
        name = D_00290080 + (kind + 20) * 10;
    }
    style = func_001DE020(kind);
    attribute = func_001DE090(style, info[2] & 0xF);
    if (style == 0) {
        if (*(u16 *)(info + 4) != 0xFFFF) {
            style = 4;
        }
    }
    id = func_001B4780(func_0020F290(func_001FD680(arg0, 1, func_001DE210(arg2), 0, 22)), style + 7, -1, 9, arg3, arg4, -0x130, -0x36, 0);
    if (func_00216920(arg1, arg2) != 0) {
        x_position = arg3 + 0x6C0 + (arg1 != 0 ? 0x108 : 8);
        id = func_001B3CC0(id, D_00290A12, x_position, arg4 + 0x727, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    } else {
        id = func_001B6EA0(id, arg3 + (arg1 != 0 ? 0x108 : 8), arg4 + 7, 1, 0, 3, arg2);
    }
    if (kind == 0) {
        s64 leader = func_00215D30(arg1, arg2);
        x_position = arg3 + offset_001C4B00(arg1, 0x28, 0xE8);
        id = func_001B4540(id, x_position, arg4 + 3, leader, 0, offset_001C4B00(arg1, 0, 1));
    }
    x_position = arg3 + 0x6C0 + (arg1 != 0 ? 0x114 : 4);
    id = func_001B3CC0(id, name, x_position, arg4 + 0x73A, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    x_position = arg3 + 0x6C0 + (arg1 != 0 ? 0xFA : 0x1E);
    id = func_001B3CC0(id, D_00290020 + attribute * 10, x_position, arg4 + 0x73A, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    if (kind == 0) {
        x_position = arg3 + 0x6C0 + (arg1 != 0 ? 0xCF : 0x38);
        id = func_001B3CC0(id, &D_002908E6, x_position, arg4 + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
        id = func_001B6EA0(id, arg3 + (arg1 != 0 ? 0xCF : 0x38) + 0x16, arg4 + 0x25, 1, 0, 2, ((Nibbles_001C4B00 *)(info + 2))->high);
        x_position = arg3 + 0x6C0 + (arg1 != 0 ? 3 : 0xF8);
        id = func_001B3CC0(id, D_002908BE, x_position, arg4 + 0x723, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
        id = func_001B6EA0(id, arg3 + (arg1 != 0 ? 3 : 0xF8) + 0x10, arg4 + 5, 1, 0, 4, *(u16 *)(info + 8) & 0x1FFF);
        x_position = arg3 + 0x6C0 + (arg1 != 0 ? 3 : 0xF8);
        id = func_001B3CC0(id, D_002908C8, x_position, arg4 + 0x733, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
        id = func_001B6EA0(id, arg3 + (arg1 != 0 ? 3 : 0xF8) + 0x10, arg4 + 0x15, 1, 0, 4, *(u16 *)(info + 10) & 0x1FFF);
    }
    x_position = arg3 + 0x6C0 + (arg1 != 0 ? 0x96 : 0x68);
    id = func_001B3CC0(id, D_002908F0, x_position, arg4 + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    ret = func_001B6EA0(id, arg3 + (arg1 != 0 ? 0x96 : 0x68) + 0x16, arg4 + 0x25, 1, 0, 3, info[3]);
    px = arg3 + 0x6C0 + (arg1 != 0 ? 0x66 : 0xAD);
    py = arg4 + 0x743;
    if (func_00216AC0(arg1, arg2, -1) < 9) {
        ret = func_001B3CC0(ret, D_0029086E, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    } else {
        ret = func_001B3CC0(ret, D_00290878, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    }
    px = arg3 + (arg1 != 0 ? 0x66 : 0xAD) + 0x13;
    py = arg4 + 0x25;
    ret = func_001B6EA0(ret, px, py, 1, 0, 1, func_00216AC0(arg1, arg2, hint != 0 ? -1 : 3));
    count = counts + arg2;
    if (*count != 0) {
        ty = arg4 + 0x25;
        ret = func_001B4780(ret, 0xD, -1, 7, arg3 + offset_001C4B00(arg1, 0xE8, 0), arg4 + 0x23, -0x48, -0x10, 1);
        px = arg3 + (arg1 != 0 ? 0 : 0xE8) + 0xC;
        value = func_0019BEF0((char *)text);
        ret = func_001B6F70(ret, px, ty, 1, 0, value, text, 0);
        px = arg3 + (arg1 != 0 ? 0 : 0xE8) + 0x30;
        ret = func_001B6EA0(ret, px, ty, 1, 0, 1, *count);
    }
    id3 = func_001B65F0(ret, style + 7, arg3 + (arg1 != 0 ? 0x38 : 0x48), arg4 + 3, -0xB0, -0x20, -1, 0);
    width = *(s32 *)((u8 *)func_001FEAB0(1) + 0xC);
    if (width > 168) {
        scale = 168.0f / (f32)width;
    }
    id3 = func_001FE660(id3, 1, arg3 + offset_001C4B00(arg1, 0x48, 0x38) + 6, arg4 + 9, scale, 1.0f, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
    id3 = func_001FE660(id3, 1, arg3 + offset_001C4B00(arg1, 0x48, 0x38) + 5, arg4 + 8, scale, 1.0f, (s32)D_002BE944, SzMsg_DrawRect_Pipe);
    id3 = func_001FE660(id3, 1, arg3 + offset_001C4B00(arg1, 0x48, 0x38) + 4, arg4 + 7, scale, 1.0f, (s32)D_002BE948, SzMsg_DrawRect_Pipe);
    func_001FEAF0(1);
    if (arg5 != 0) {
        if (func_00216AC0(arg1, arg2, 3) <= 0) {
            ((Tag_001C4B00 *)box.tag)->flags = 6;
            ((Tag_001C4B00 *)box.tag)->count = 3;
            ((Tag_001C4B00 *)box.tag)->registers = 0x441;
            ((Tag_001C4B00 *)box.tag)->padding = 0;
            func_002086D0(box.tag, func_00208D00(2));
            box.color.r = 0x80;
            box.color.g = 0x80;
            box.color.b = 0x80;
            box.color.a = 0x40;
            box.color.q = 1.0f;
            box.vertex0.x = (arg3 + 0x6C0) << 4;
            box.vertex0.y = (arg4 + 0x720) << 4;
            box.vertex0.z = *(s32 *)(state + 0xC58);
            box.vertex0.fog = 0;
            box.vertex1.x = (arg3 + 0x7F0) << 4;
            box.vertex1.y = (arg4 + 0x756) << 4;
            box.vertex1.z = *(s32 *)(state + 0xC58);
            box.vertex1.fog = 0;
            id3 = func_00207650(id3, (s32)box.tag, 0, 0);
        }
    }
    return id3;
}
#pragma opt_dead_assignments reset

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

#pragma opt_propagation off

s32 lSzDuel_DrawTrade_Ready_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern char D_002BF03A[];
    s8 *text = D_002BF03A;
    s32 width;
    s32 height;
    s32 fx;
    s32 fy;
    s32 ty;

    lSzDuel_GetFontSize(2, 3, strlen(text), text, &width, &height);
    width += 0x18;
    height += 0xC;
    fx = arg1 + 0x140 - (width >> 1);
    fy = arg2 + 0xE0 - (height >> 1);
    arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, 0xC, -1, 0xB, fx, fy, -width, -height, 1);
    ty = arg2 + 0xE8 - (height >> 1);
    return SzDuel_DrawWindow_Font_Pipe(arg0, arg1 + 0x140, ty, 2, 3, strlen(text), text, 0);
}
#pragma opt_propagation reset

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

#pragma opt_propagation off
#pragma opt_lifetimes off

s32 SzDuel_DrawCustomDuel_Pipe(s32 arg0) {
    extern char D_002BF03A[];
    extern s32 lSzDuel_DrawCustomDuel_Title_Pipe();
    extern s32 lSzDuel_DrawCustomDuel_PlayerInfo_Pipe();
    extern s32 lSzDuel_DrawCustomDuel_Menu_Pipe();
    extern s32 lSzDuel_DrawCustomDuel_Menu_SelectMap_Pipe();
    extern s32 lSzDuel_DrawCustomDuel_Exit_Pipe();
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern s32 lSzDuel_Draw_Fade_Pipe();
    s8 *text;
    s32 id;
    s32 textY;
    s32 height;
    s32 width;
    s32 height2;
    s32 width2;
    s32 mode;
    s32 fy;

    id = lSzDuel_DrawCustomDuel_PlayerInfo_Pipe(lSzDuel_DrawCustomDuel_PlayerInfo_Pipe(lSzDuel_DrawCustomDuel_Title_Pipe(lSzDuel_DrawCustomDuel_Base_Pipe(SzDuel_StartWindowSessionWithPalette_Pipe(arg0, 2)), 0, 0), 0, 0x10, 0x40), 1, 0x140, 0x40);
    mode = *(u8 *)0xA9C002 & 0xF0;
    if (mode == 0x40 || (*(u8 *)0xA9C003 & 0xF0) == 0x40) {
        id = lSzDuel_DrawCustomDuel_Menu_SelectMap_Pipe(id, 0, 0x1E, 0xE0);
    } else {
        if (mode == 0x20) {
            text = D_002BF03A;
            lSzDuel_GetFontSize(2, 3, strlen(text), text, &width, &height);
            width += 0x18;
            height += 0xC;
            fy = 0x144 - height / 2;
            id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, -1, 0xB, 0xA0 - width / 2, fy, -width, -height, 1);
            textY = 0x14C - height / 2;
            id = SzDuel_DrawWindow_Font_Pipe(id, 0xA0, textY, 2, 3, strlen(text), text, 0);
        } else {
            id = lSzDuel_DrawCustomDuel_Menu_Pipe(id, 0, 0x10, 0xE6);
        }
        if (*(u8 *)0xA9C088 == 0) {
            if ((*(u8 *)0xA9C003 & 0xF0) == 0x20) {
                text = D_002BF03A;
                lSzDuel_GetFontSize(2, 3, strlen(text), text, &width2, &height2);
                width2 += 0x18;
                height2 += 0xC;
                fy = 0x144 - height2 / 2;
                id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, -1, 0xB, 0x1E0 - width2 / 2, fy, -width2, -height2, 1);
                textY = 0x14C - height2 / 2;
                id = SzDuel_DrawWindow_Font_Pipe(id, 0x1E0, textY, 2, 3, strlen(text), text, 0);
            } else {
                id = lSzDuel_DrawCustomDuel_Menu_Pipe(id, 1, 0x140, 0xE6);
            }
        }
    }
    if ((*(u8 *)0xA9C002 & 0xF0) == 0x30 || (*(u8 *)0xA9C003 & 0xF0) == 0x30) {
        id = lSzDuel_DrawCustomDuel_Exit_Pipe(lSzDuel_Draw_Fade_Pipe(id, 0, 0, 0x280, 0x1C0, 0x40), 0, 0);
    }
    SzMsg_Free(0);
    return id;
}
#pragma opt_lifetimes reset
#pragma opt_propagation reset

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

extern s32 D_002908E6;
extern s32 D_00290A1C;
extern char D_002BF051[];
extern char D_002BF056[];

extern u8 D_00290080[];
extern u8 D_002908F0[];
extern u8 D_0029099A[];

typedef struct TextInfo_001C7D20 {
    u8 pad[12];
    s32 width;
} TextInfo_001C7D20;

static inline f32 scale_001C7D20(s32 index, s32 limit) {
    extern void *func_001FEAB0();
    s32 width = ((TextInfo_001C7D20 *)func_001FEAB0(index))->width;
    if (width > limit) {
        return (f32)limit / (f32)width;
    }
    return 1.0f;
}

static inline s32 wide_001C7D20(TextInfo_001C7D20 *text) {
    return text->width > 200;
}

s32 lSzDuel_DrawCustomDuel_PlayerInfo_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s64, s64, s64, s64, s64, s64);
    extern s32 func_001B4540(s32, s32, s32, s32, s32, s32);
    extern s32 func_001B65F0(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B6EA0(s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001DE690();
    extern s32 func_00215D30();
    extern void *func_001FEAB0();
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    s32 ret;
    s32 nx;
    s32 ny;
    s32 tx;
    s32 px;
    s32 py;
    s32 ty;
    u8 *spD0;
    s32 spEC;
    s32 frame_x;
    s32 temp_v0;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_s0_7;
    s32 image_x;
    s32 temp_v0_2;
    s32 temp_s1;
    s32 image_y;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 first_x;
    s32 first_y;
    s32 var_s3;
    s8 *var_s7;
    u8 *temp_fp;
    s32 temp_fp_2;
    s32 var_a2;
    TextInfo_001C7D20 *first_text;
    f32 first_scale;
    s32 hint = 0;
    s32 number_x;
    s32 number_y;

    spD0 = D_00317490.b;
    temp_v0 = func_002158B0(arg1);
    temp_v0_2 = func_002159D0(arg1, temp_v0);
    temp_fp = func_001DD0E0(temp_v0_2);
    if (*((u8 *)arg1 + 0xA9C00E) != 0) {
        var_s7 = (s8 *)D_002BF051;
    } else {
        var_s7 = (s8 *)D_002BF056;
    }
    var_a2 = 3;
    if (arg1 != 0) {
        u8 mode = *(u8 *)0xA9C088;
        switch (mode) {
        case 0:
            var_a2 = 4;
            break;
        default:
            var_a2 = mode + 0x8C;
            break;
        }
    }
    arg0 = func_001FD680(arg0, 1, var_a2, 0, 0x16);
    temp_s1 = func_0020F290(arg0);
    tx = arg2 + 0x6C0 + ((arg1 != 0) ? 0x110 : 0);
    temp_s1 = func_001B3CC0(temp_s1, D_00290080 + ((arg1 + 0xF3) * 10), tx, arg3 + 0x720, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    frame_x = arg2 + 0x20;
    (void)frame_x; /* keeps the x add at its own statement: the original computes it before arg1 + 5 */
    spEC = func_001B4780(temp_s1, arg1, arg1 + 5, 0xB, frame_x, arg3, -0xF0, -0x20, 1);
    first_x = arg2 + 0x40;
    first_y = arg3 + 5;
    first_text = (TextInfo_001C7D20 *)func_001FEAB0(1);
    if (wide_001C7D20(first_text)) {
        first_scale = 200.0f / (f32)first_text->width;
    } else {
        first_scale = 1.0f;
    }
    temp_s2 = func_001FE660(spEC, 1, first_x, first_y, first_scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    func_001FEAF0(1);
    var_s3 = func_001B65F0(func_001B4780(temp_s2, arg1, -1, 4, arg2, arg3 + 0x20, -0x130, -0x80, 1), arg1, arg2 + 0xD, arg3 + 0x25, -0x116, -0x5E, -1, 0);
    if (temp_fp != NULL) {
        temp_s2_2 = *temp_fp & 0x1F;
        temp_s1 = func_001DE210(temp_v0_2);
        temp_fp_2 = func_00215D30(arg1, temp_v0_2);
        var_s3 = func_001B3CC0(func_001B3CC0(func_001B3CC0(func_001B4780(func_0020F290(func_001FD680(func_001FD680(func_001FD680(var_s3, 1, temp_s1, 0, 0x16), 2, temp_s2_2 + 0x25, 0, 0x2C), 3, temp_fp_2 + 0x52, 0, 0x42)), 0xC, -1, 0xB, arg2 + 0x11, arg3 + 0x29, -0x6E, -0x56, 1), D_0029099A, arg2 + 0x6D9, arg3 + 0x751, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80), D_00290080 + ((temp_v0 + 0xE3) * 10), arg2 + 0x6E4, arg3 + 0x764, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80), D_002908F0, arg2 + 0x6E0, arg3 + 0x784, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        number_x = arg2 + 0x35;
        number_y = arg3 + 0x65;
        var_s3 = func_001B6EA0(var_s3, number_x, number_y, 0, hint != 0 ? 1 : 0, 4, func_00215F00(arg1, temp_v0));
        image_x = arg2 + 0x4A;
        image_y = arg3 + 0x2E;
        temp_s0 = func_001B4780(func_001B7F90(var_s3, arg1, image_x, image_y, 0x30, 0x30, *(s32 *)(spD0 + 0xC58), 1), -1, -1, 4, image_x, image_y, 3, 6, 1);
        temp_s0_2 = func_001FE660(temp_s0, 1, arg2 + 0x81, arg3 + 0x2B, scale_001C7D20(1, 156), 1.0f, 0, SzMsg_DrawRect_Pipe);
        func_001FEAF0(1);
        px = arg2 + 0x741;
        py = arg3 + 0x767;
        temp_s0_3 = func_001B3CC0(temp_s0_2, D_00290080 + (temp_s2_2 * 10), px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
        var_s3 = func_001FE660(temp_s0_3, 2, arg2 + 0x9B, arg3 + 0x47, scale_001C7D20(2, 138), 1.0f, 0, SzMsg_DrawRect_Pipe);
        func_001FEAF0(2);
        if (*(u8 *)0xA9C088 != 0 || *((u8 *)arg1 + 0xA9C00A) != 0) {
            temp_s0_4 = func_001B4540(var_s3, arg2 + 0x81, arg3 + 0x65, temp_fp_2, 1, 0);
            var_s3 = func_001FE660(temp_s0_4, 3, arg2 + 0x9B, arg3 + 0x65, scale_001C7D20(3, 138), 1.0f, 0, SzMsg_DrawRect_Pipe);
        }
        func_001FEAF0(3);
    }
    ret = func_001B3CC0(func_001B4780(var_s3, 0xC, -1, 5, arg2 + 0x14, arg3 + 0x86, -0x70, -0x14, 1), &D_00290A1C, arg2 + 0x6D6, arg3 + 0x7A8, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    nx = arg2 + 0x3E;
    ny = arg3 + 0x8A;
    ret = func_001B3CC0(func_001B4780(func_001B6EA0(ret, nx, ny, 0, hint != 0 ? 1 : 0, 4, func_001DF470(arg1)), 0xC, -1, 5, arg2 + 0x94, arg3 + 0x86, -0x3C, -0x14, 1), &D_002908E6, arg2 + 0x756, arg3 + 0x7A8, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    nx = arg2 + 0xAC;
    ny = arg3 + 0x8A;
    ret = func_001B6EA0(ret, nx, ny, 0, hint != 0 ? 1 : 0, 2, func_001DE690(arg1));
    if (*(u8 *)0xA9C088 == 0) {
        nx = arg2 + 0x100;
        ny = arg3 + 0x8A;
        ret = func_001B6F70(ret, nx, ny, 0, 2, func_0019BEF0((const char *)var_s7), var_s7, hint != 0 ? (s32)D_002BE944 : 0);
    }
    return ret;
}

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

typedef struct {
    u8 enabled : 1;
} Flags_001CC4B0;

typedef struct {
    f32 data[4];
} Vec4_001CC4B0;

extern Vec4_001CC4B0 D_002914B0;
extern Vec4_001CC4B0 D_002914C0;

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

#pragma conditional_move reset


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


typedef struct {
    u8 pad_00[0x90];
    s32 in_use;
    u8 pad_94[0xC];
} Slot_001CDAA0;

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
