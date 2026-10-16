#include "common.h"

s32 lSzDuel_IsDeckReady(s32 arg0, s32 arg1) {
    s32 count;
    s32 card;

    count = SzData_GetDeckCount(arg0, arg1);
    card = SzData_GetLeader(arg0, arg1);
    return (count >= 0x28 && card != 0x3E7) ? 1 : 0;
}

typedef struct Data_001BA420 {
    u8 padding0[9];
    u8 unused0 : 6;
    u8 valid : 1;
    u8 unused1 : 1;
    u8 paddingA[2];
    u8 bytes[8];
} Data_001BA420;

extern s8 D_002BEF79[];

s32 lSzDuel_HitPassword(u8 *arg0) {
    s8 *offsets = D_002BEF79;
    s32 index;
    u8 decoded[8];
    s32 byte;
    Data_001BA420 *entry;
    u8 *out;

    index = 0;
    do {
        entry = (Data_001BA420 *)SzDuel_GetCardConstInfo(index);
        if (entry != NULL && entry->valid) {
            out = decoded;
            byte = 0;
            do {
                *out = (entry->bytes[byte] + offsets[(index + byte) % 8] + 256) % 256;
                if (*out != arg0[byte]) {
                    break;
                }
                byte++;
                out++;
            } while (byte < 8);
            if (byte >= 8) {
                return index;
            }
        }
        index++;
    } while (index < 0x356);
    return -1;
}

typedef struct Entry_001BA520 {
    s16 id;
    u8 state;
    u8 value : 5;
    s8 flag5 : 1;
    s8 flag6 : 1;
    s8 flag7 : 1;
} Entry_001BA520;

extern Entry_001BA520 *D_00317B60;

s32 lSzDuel_ReqGhostCard(s32 arg0, s32 arg1, s64 arg2, s64 arg3, s64 arg4) {
    Entry_001BA520 *entry;
    s32 i;

    entry = D_00317B60;
    i = 0;
    do {
        if (entry->state == 0) {
            entry->id = arg0;
            entry->value = arg1;
            entry->flag5 = (s8)arg2;
            entry->flag6 = (s8)arg3;
            entry->flag7 = (s8)arg4;
            entry->state = 0x80;
            return 1;
        }
        i++;
        entry++;
    } while (i < 8);
    return 0;
}

void lSzDuel_SortBag(void) {
    func_00199BC0(D_00317B68, 0x356, 2, lSzDuel_SortFunc1);
}

void lSzDuel_SortDeck(void) {
    func_00199BC0(D_00317B6C + 2, 0x28, 2, lSzDuel_SortFunc2);
}

extern s32 (*D_00291330[])(s32, s32);

static inline s32 check_001BA630(u8 *data, s32 i) {
    s32 j;

    for (j = 0; j < i; j++) {
        if (data[i + 0xCB6] == data[j + 0xCB6]) {
            break;
        }
    }
    return j < i;
}

s32 lSzDuel_SortFunc1(s32 arg0, s32 arg1) {
    u8 *data = D_00317490.b;
    s32 i;
    s32 result = 0;

    i = 0;
    do {
        if (i == 0 || !check_001BA630(data, i)) {
            result = D_00291330[data[i + 0xCB6]](arg0, arg1);
            if (result != 0) {
                break;
            }
        }
        i++;
    } while (i < 3);
    return result;
}

s32 lSzDuel_SortFunc2(s32 arg0, s32 arg1) {
    u8 *base = D_00317490.b;
    s32 i;
    s32 j;
    s32 result = 0;

    i = 0;
    do {
        if (i != 0) {
            for (j = 0; j < i; j++) {
                if ((base + i)[0xCB9] == (base + j)[0xCB9]) {
                    break;
                }
            }
            if (j < i) {
                continue;
            }
        }
        result = D_00291330[(base + i)[0xCB9]](arg0, arg1);
        if (result != 0) {
            break;
        }
    } while (++i < 3);
    return result;
}

s32 lSzDuel_NewComerCmp(u16 *arg0, u16 *arg1) {
    s32 temp_s0;
    s32 temp_s1;
    s32 var_s2;
    s32 var_a0;
    s32 temp_v1;
    s32 ret;

    temp_v1 = *arg0;
    temp_s0 = D_003181EC;
    temp_s1 = *arg1;
    if (temp_v1 == 0x3E7) {
        var_s2 = 2;
    } else {
        var_s2 = SzData_IsBagNew(temp_s0, temp_v1) ? 0 : 1;
    }
    if (temp_s1 == 0x3E7) {
        var_a0 = 2;
    } else {
        var_a0 = SzData_IsBagNew(temp_s0, temp_s1) ? 0 : 1;
    }
    if (var_a0 < var_s2) {
        ret = 1;
    } else {
        ret = (var_s2 < var_a0) ? -1 : 0;
    }
    return ret;
}

static inline s64 value_001BA8A0(u8 *entry) {
    if (entry != NULL) {
        return (s32)*entry;
    }
    return 0x7FFFFFFF;
}

s32 lSzDuel_ClassCmp(u16 *arg0, u16 *arg1) {
    s64 var_v0;
    s64 var_v1;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;

    temp_s0 = *arg1;
    temp_s0_2 = SzDuel_GetCardConstInfo(*arg0);
    temp_v0 = SzDuel_GetCardConstInfo(temp_s0);
    var_v1 = value_001BA8A0(temp_s0_2);
    var_v0 = value_001BA8A0(temp_v0);
    if (var_v0 < var_v1) {
        return 1;
    }
    return (var_v1 < var_v0) ? -1 : 0;
}

typedef struct {
    u8 pad[0x6D4];
    u16 *values;
} Data_001BA930;

s32 lSzDuel_NameCmp(u16 *arg0, u16 *arg1) {
    Data_001BA930 *data = (Data_001BA930 *)D_00317490.b;
    s32 temp_a1;
    s64 var_a2;
    s64 var_v0;
    s32 temp_v1;
    s32 ret;

    temp_v1 = *arg0;
    temp_a1 = *arg1;
    if (temp_v1 == 0x3E7) {
        var_a2 = 0x7FFFFFFF;
    } else {
        var_a2 = (s32) data->values[temp_v1];
    }
    if (temp_a1 == 0x3E7) {
        var_v0 = 0x7FFFFFFF;
    } else {
        var_v0 = (s32) data->values[temp_a1];
    }
    if (var_v0 < var_a2) {
        ret = 1;
    } else {
        ret = (var_a2 < var_v0) ? -1 : 0;
    }
    return ret;
}

s32 lSzDuel_APCmp(u16 *arg0, u16 *arg1) {
    s32 var_v0;
    s32 var_v1;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;

    temp_s0 = *arg1;
    temp_s0_2 = SzDuel_GetCardConstInfo(*arg0);
    temp_v0 = SzDuel_GetCardConstInfo(temp_s0);
    var_v1 = -1;
    if (temp_s0_2 != NULL) {
        var_v1 = *(u16 *)(temp_s0_2 + 8) & 0x1FFF;
    }
    var_v0 = (temp_v0 != NULL) ? (*(u16 *)(temp_v0 + 8) & 0x1FFF) : -1;
    if (var_v1 < var_v0) {
        var_v0 = 1;
    } else {
        var_v0 = (var_v0 < var_v1) ? -1 : 0;
    }
    return var_v0;
}

s32 lSzDuel_DPCmp(u16 *arg0, u16 *arg1) {
    s32 var_v0;
    s32 var_v1;
    s32 result;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;

    temp_s0 = *arg1;
    temp_s0_2 = SzDuel_GetCardConstInfo(*arg0);
    temp_v0 = SzDuel_GetCardConstInfo(temp_s0);
    var_v1 = -1;
    if (temp_s0_2 != NULL) {
        var_v1 = *(u16 *)(temp_s0_2 + 0xA) & 0x1FFF;
    }
    if (temp_v0 != NULL) {
        var_v0 = *(u16 *)(temp_v0 + 0xA) & 0x1FFF;
    } else {
        var_v0 = -1;
    }
    if (var_v1 < var_v0) {
        result = 1;
    } else {
        result = (var_v0 < var_v1) ? -1 : 0;
    }
    return result;
}

s32 lSzDuel_AttrCmp(u16 *arg0, u16 *arg1) {
    u8 *card0;
    u8 *card1;
    s32 rank0;
    s32 rank1;
    s32 cardId1;

    cardId1 = *arg1;
    card0 = SzDuel_GetCardConstInfo(*arg0);
    card1 = SzDuel_GetCardConstInfo(cardId1);
    rank0 = 0x7FFFFFFF;
    rank1 = 0x7FFFFFFF;
    if (card0 != NULL) {
        rank0 = SzDuel_Kind2Attr((s32) card0[0] >> 5, card0[2] & 0xF);
    }
    if (card1 != NULL) {
        rank1 = SzDuel_Kind2Attr((s32) card1[0] >> 5, card1[2] & 0xF);
    }
    if (rank1 < rank0) {
        return 1;
    }
    return (rank0 < rank1) ? -1 : 0;
}

typedef struct Info_001BAB60 {
    u8 padding[2];
    u8 low : 4;
    u8 rank : 4;
} Info_001BAB60;

static inline s64 rank_001BAB60(void *entry) {
    if (entry != NULL) {
        return (s32)((Info_001BAB60 *)entry)->rank;
    }
    return 0x7FFFFFFF;
}

s32 lSzDuel_LevelCmp(u16 *arg0, u16 *arg1) {
    s64 var_v0;
    s64 var_v1;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;
    s32 result;

    temp_s0 = *arg1;
    temp_s0_2 = SzDuel_GetCardConstInfo(*arg0);
    temp_v0 = SzDuel_GetCardConstInfo(temp_s0);
    var_v1 = rank_001BAB60(temp_s0_2);
    var_v0 = rank_001BAB60(temp_v0);
    if (var_v0 < var_v1) {
        result = 1;
    } else if (var_v1 < var_v0) {
        result = -1;
    } else {
        result = 0;
    }
    return result;
}

s32 lSzDuel_DeckCostCmp(u16 *arg0, u16 *arg1) {
    s64 var_v0;
    s64 var_v1;
    s32 temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;

    temp_s0 = *arg1;
    temp_s0_2 = SzDuel_GetCardConstInfo(*arg0);
    temp_v0 = SzDuel_GetCardConstInfo(temp_s0);
    if (temp_s0_2 != NULL) {
        var_v1 = (s32) temp_s0_2[3];
    } else {
        var_v1 = 0x7FFFFFFF;
    }
    if (temp_v0 != NULL) {
        var_v0 = (s32) temp_v0[3];
    } else {
        var_v0 = 0x7FFFFFFF;
    }
    if (var_v0 < var_v1) {
        return 1;
    }
    return (var_v1 < var_v0) ? -1 : 0;
}

s32 lSzDuel_RankCmp(u16 *arg0, u16 *arg1) {
    extern s64 SzData_GetRank(u8, s32);
    u8 temp_s0;
    s32 temp_s1;
    s32 var_s2;
    s32 var_v0;
    s32 temp_v1;

    temp_v1 = *arg0;
    temp_s0 = D_003181EC;
    temp_s1 = *arg1;
    if ((s32) temp_v1 >= 0x2AB) {
        var_s2 = 0x7FFFFFFF;
    } else {
        var_s2 = (s32) SzData_GetRank(temp_s0, temp_v1);
    }
    if ((s32) temp_s1 >= 0x2AB) {
        var_v0 = 0x7FFFFFFF;
    } else {
        var_v0 = (s32) SzData_GetRank(temp_s0, temp_s1);
    }
    if (var_v0 < var_s2) {
        return 1;
    }
    return (var_s2 < var_v0) ? -1 : 0;
}

s32 lSzDuel_CardColorCmp(u16 *arg0, u16 *arg1) {
    s32 type0;
    s32 type1;
    s32 id1;
    u8 *card0;
    u8 *card1;
    s32 result;

    id1 = *arg1;
    card0 = SzDuel_GetCardConstInfo(*arg0);
    card1 = SzDuel_GetCardConstInfo(id1);

    type0 = card0 != NULL ? card0[0] >> 5 : 0x7FFFFFFFLL;
    type1 = card1 != NULL ? card1[0] >> 5 : 0x7FFFFFFFLL;

    if (type0 != 0x7FFFFFFFLL) {
        if (type0 != 0 || *(u16 *)(card0 + 4) == 0xFFFF) {
            type0 += 6;
        }
    }
    if (type1 != 0x7FFFFFFFLL) {
        if (type1 != 0 || *(u16 *)(card1 + 4) == 0xFFFF) {
            type1 += 6;
        }
    }
    if (type1 < type0) {
        result = 1;
    } else {
        result = type0 < type1 ? -1 : 0;
    }
    return result;
}

s32 lSzDuel_NumberCmp(u16 *arg0, u16 *arg1) {
    u16 temp_v1;
    u16 temp_v0;
    s32 result;

    temp_v1 = *arg0;
    temp_v0 = *arg1;
    if ((s32) temp_v1 > (s32) temp_v0) {
        result = 1;
    } else {
        result = ((s32) temp_v1 < (s32) temp_v0) ? -1 : 0;
    }
    return result;
}

void SzDuel_DrawBuildDeck(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawBuildDeck_Pipe(RhBase_GetVifPacketArea()));
}

s32 SzDuel_DrawBuildDeck_Pipe(s32 arg0) {
    extern s16 D_00318122;
    extern void RhBase_AssignRenderFrame();
    extern s32 lSzDuel_DrawBuildDeck_Title_Pipe();
    extern s32 lSzDuel_DrawBuildDeck_Library_Pipe();
    extern s32 func_001BDAF0();
    extern s32 lSzDuel_DrawBuildDeck_Bag_Pipe();
    extern s32 lSzDuel_DrawBuildDeck_Deck_Pipe();
    extern s32 lSzDuel_DrawBuildDeck_DeckCursor_Pipe();
    extern s32 lSzDuel_DrawBuildDeck_Reincarnation_Pipe();
    extern s32 lSzDuel_DrawBuildDeck_Password_Pipe();
    extern s32 lSzDuel_DrawBuildDeck_PasswordFail_Pipe();
    extern s32 lSzDuel_DrawBuildDeck_PasswordDone_Pipe();
    extern s32 lSzDuel_DrawBuildDeck_Caution_Pipe();
    u8 *state;
    s32 player;
    s32 flag;
    s32 value;
    s32 position;
    s32 result;

    player = D_003181EC;
    state = D_00317490.b;
    RhBase_AssignRenderFrame(5, 2, 0x32);
    arg0 = (s32)RhBase_EnableRenderFrame((void *)arg0);
    value = lSzDuel_DrawBuildDeck_Title_Pipe(
        RhBase_MaskFBuffer((void *)lSzDuel_DrawBuildDeck_Base_Pipe((s32)RhBase_MaskFBuffer(
                          (void *)SzDuel_StartWindowSessionWithPalette_Pipe((s32)RhBase_DisableRenderFrame(RhBase_ClearRenderFrame((u8 *)arg0, NULL)), 2),
                          0xFF000000)),
                      0),
        D_00318122, 0);
    if (D_00318122 > 0x140) {
        value = lSzDuel_DrawBuildDeck_Library_Pipe(value, *(s16 *)(state + 0xC92), 0);
    }
    if (*(s16 *)(state + 0xC92) > 0) {
        if (state[0xD5D] == 0) {
            flag = 0;
            position = state[0xD61] + (state[0xD60] + state[0xD62]) * 10;
            if (SzData_GetBagCount(player, position, -1) > 0) {
                flag = 1;
            }
            if (SzData_GetLookFlag(player, position) != 0) {
                flag = 1;
            }
            if (flag != 0) {
                value = func_001BDAF0(value, position, *(s16 *)(state + 0xC92), 0, 0, 0, 0, 1);
            }
        } else {
            value = func_001BDAF0(value,
                                   (*(u16 **)(state + 0x6D8))[*(u16 *)(state + 0xC8A) + state[0xD5E]],
                                   *(s16 *)(state + 0xC92), 0, 0, (state[0xD5D] == 1) ? 1 : 0, 0, 1);
        }
    }
    if (*(s16 *)(state + 0xC92) > -0x140 && *(s16 *)(state + 0xC92) < 0x280) {
        value = lSzDuel_DrawBuildDeck_Bag_Pipe(value, *(s16 *)(state + 0xC92), 0);
    }
    if (*(s16 *)(state + 0xC92) < 0x140) {
        value = lSzDuel_DrawBuildDeck_Deck_Pipe(value, *(s16 *)(state + 0xC92), 0);
    }
    if (*(s16 *)(state + 0xC92) < 0) {
        value = func_001BDAF0(value,
                               (*(u16 **)(state + 0x6DC))[*(u16 *)(state + 0xC8E) + state[0xD5F]],
                               *(s16 *)(state + 0xC92), 0, 1, (state[0xD5D] == 6) ? 1 : 0, 0, 0);
    }
    result = lSzDuel_DrawBuildDeck_Ghost_Pipe(value, *(s16 *)(state + 0xC92), 0);
    switch (state[0xD5D]) {
    case 2:
    case 3:
        result = lSzDuel_DrawBuildDeck_BagCursor_Pipe(result, *(s16 *)(state + 0xC92), 0, state[0xD5E]);
        break;
    case 4:
    case 5:
        result = lSzDuel_DrawBuildDeck_DeckCursor_Pipe(result, *(s16 *)(state + 0xC92), 0, state[0xD5F]);
        break;
    case 7:
        result = lSzDuel_DrawBuildDeck_Reincarnation_Pipe(result, 0, 0);
        break;
    case 8:
        result = lSzDuel_DrawBuildDeck_ReincarnationDone_Pipe(result, 0, 0);
        break;
    case 9:
        result = lSzDuel_DrawBuildDeck_Password_Pipe(result, 0, 0);
        break;
    case 10:
        result = lSzDuel_DrawBuildDeck_PasswordSuccess_Pipe(result, 0, 0);
        break;
    case 11:
        result = lSzDuel_DrawBuildDeck_PasswordFail_Pipe(result, 0, 0);
        break;
    case 12:
        result = lSzDuel_DrawBuildDeck_PasswordDone_Pipe(result, 0, 0);
        break;
    case 13:
        result = lSzDuel_DrawBuildDeck_Caution_Pipe(result, 0, 0);
        break;
    }
    SzMsg_Free(0);
    RhBase_FreeRenderFrame();
    return result;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001BB260;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001BB260;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001BB260;

typedef struct {
    Color_001BB260 color;
    Vertex_001BB260 xyz;
} Point_001BB260;

typedef struct {
    u64 tag[2];
    Point_001BB260 points[4];
    u64 end;
} Packet_001BB260;

typedef struct {
    u8 b, g, r, a;
} Source_001BB260;

static inline void set_color_001BB260(Color_001BB260 *a, Color_001BB260 *b,
                                      Source_001BB260 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

static inline void set_xyz_001BB260(Vertex_001BB260 *v, s32 x, s32 y) {
    v->x = (x + 0x6C0) << 4;
    v->y = (y + 0x720) << 4;
    v->z = D_003180E8;
    v->fog = 0;
}

s32 lSzDuel_DrawBuildDeck_Base_Pipe(s32 arg0) {
    extern u8 D_002BE850[];
    Source_001BB260 *colors = (Source_001BB260 *)D_002BE850;
    s32 width = 0x140;
    s32 height = 0x1C0;
    Packet_001BB260 packet __attribute__((aligned(8)));

    ((Tag_001BB260 *)packet.tag)->flags = 0x14;
    ((Tag_001BB260 *)packet.tag)->count = 8;
    ((Tag_001BB260 *)packet.tag)->registers = 0x41414141;
    ((Tag_001BB260 *)packet.tag)->padding = 0;
    set_color_001BB260(&packet.points[0].color, &packet.points[2].color, &colors[0]);
    set_color_001BB260(&packet.points[1].color, &packet.points[3].color, &colors[1]);
    set_xyz_001BB260(&packet.points[0].xyz, 0, 0);
    set_xyz_001BB260(&packet.points[1].xyz, width, 0);
    set_xyz_001BB260(&packet.points[2].xyz, 0, height);
    set_xyz_001BB260(&packet.points[3].xyz, width, height);
    arg0 = ExSortPrim_Pipe(arg0, (s32)packet.tag, 0, 0);
    set_color_001BB260(&packet.points[0].color, &packet.points[2].color, &colors[1]);
    set_color_001BB260(&packet.points[1].color, &packet.points[3].color, &colors[0]);
    set_xyz_001BB260(&packet.points[0].xyz, width, 0);
    set_xyz_001BB260(&packet.points[1].xyz, width * 2, 0);
    set_xyz_001BB260(&packet.points[2].xyz, width, height);
    set_xyz_001BB260(&packet.points[3].xyz, width * 2, height);
    return ExSortPrim_Pipe(arg0, (s32)packet.tag, 0, 0);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

typedef int DotrCaptionTitleWord;
extern DotrCaptionTitleWord func_001B4780_b(DotrCaptionTitleWord cursor, int a1, int a2, int a3, int x, int y, int a6, int a7, long a8);
extern DotrCaptionTitleWord func_001B6F70_b(DotrCaptionTitleWord cursor, int x, int y, int font, int flags, int n, const char *text, int c);
typedef int DotrCaptionAddress;
struct DotrCaptionControl {
    char unknown_000[0x6d0];
    DotrCaptionAddress work;
    char unknown_6d4[4];
    unsigned short *list_cards;
    unsigned short *deck_cards;
    char unknown_6e0[0xc58 - 0x6e0];
    int pic_z;
    char unknown_c5c[0xc8a - 0xc5c];
    unsigned short list_cursor;
    char unknown_c8c[2];
    unsigned short deck_cursor;
    char unknown_c90[2];
    short slide;
    char unknown_c94[0xcc2 - 0xc94];
    char pass[8];
    char unknown_cca[0xd36 - 0xcca];
    unsigned char choice;
    char unknown_d37[0xd57 - 0xd37];
    unsigned char step;
    char unknown_d58[0xd5c - 0xd58];
    unsigned char side;
    unsigned char mode;
    unsigned char list_top;
    unsigned char deck_top;
    unsigned char grid_top;
    unsigned char grid_col;
    unsigned char grid_row;
};
extern struct DotrCaptionControl D_00317490_1bb6d0;
extern char D_002BEF80[];
extern char D_00290080_1bb6d0[];
extern DotrCaptionTitleWord func_001B3CC0_b(DotrCaptionTitleWord cursor, char *def, int x, int y, int a4, int a5, int a6,
                                                int a7, int a8, int a9, int a10, int a11, int a12, int a13);
extern DotrCaptionTitleWord func_001B6EA0_b(DotrCaptionTitleWord cursor, int x, int y, int a, int flags, int width, int value);

int lSzDuel_DrawBuildDeck_Title_Pipe(int cursor, int x, int y)
{
    int side;
    int deck;
    char *text;
    int px;
    int py;
    int qx;
    int qy;

    side = D_00317490_1bb6d0.side;
    deck = SzData_GetCurrentDeck(side);
    text = D_002BEF80 + 2;
    px = x + 224;
    py = y + 32;

    cursor = lSzDuel_DrawWindow_Base_Pipe(cursor, px, py, 6, 1);
    cursor = func_001B4780_b(cursor, -1, 115, 4, px, py, 21, 2, 1);
    px = x + 320;
    py = y + 39;
    cursor = func_001B6F70_b(cursor, px, py, 2, 3, func_0019BEF0(text), text, 0);
    px = x + 432;
    py = y + 16;
    cursor = func_001B4780_b(cursor, 12, -1, 11, px, py, -128, -48, 1);
    px = x + 2202;
    py = y + 1848;
    cursor = func_001B3CC0_b(cursor, D_00290080_1bb6d0 + 2330, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 128);
    qx = x + 2172;
    qy = y + 1866;
    cursor = func_001B3CC0_b(cursor, D_00290080_1bb6d0 + 2160, qx, qy, 0, 1, 0, 0, 0, 0, 1, 0, -1, 128);
    qx = x + 464;
    qy = y + 44;
    cursor = func_001B6EA0_b(cursor, qx, qy, 1, 0, 4, SzData_GetDeckCost(side, deck));
    qx = x + 2236;
    qy = y + 1866;
    cursor = func_001B3CC0_b(cursor, D_00290080_1bb6d0 + 2050, qx, qy, 0, 1, 0, 0, 0, 0, 1, 0, -1, 128);
    qx = x + 528;
    qy = y + 44;
    return func_001B6EA0_b(cursor, qx, qy, 1, 0, 2, SzData_GetDeckCount(side, deck));
}

typedef struct Vertex_001BB940 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001BB940;

typedef struct Header_001BB940 {
    u16 type;
    u16 count;
    u32 pad;
    u64 registers;
} Header_001BB940;

typedef struct Packet_001BB940 {
    u64 tag;
    Header_001BB940 header;
    u8 r, g, b, a;
    f32 q;
    Vertex_001BB940 first;
    Vertex_001BB940 second;
} Packet_001BB940;

typedef union Color_001BB940 {
    f32 value;
    u8 bytes[4];
} Color_001BB940;

extern u8 D_00290080[];
extern u8 D_00290828[];
extern u8 D_00290832[];
extern u8 D_00290896[];
extern u8 D_002908A0[];
extern u8 D_00290A6C[];
extern u8 D_00290AA8[];
extern u8 D_00290AB2[];
extern u8 D_00290ABC[];
extern u8 D_00290AC6[];
extern s8 *D_00290FD0[];
extern Color_001BB940 D_00291360;
extern u8 D_002BE8A4[];
extern char D_002BEF8D[];
extern char D_002BEF93[];
extern u8 D_003181EC;
extern u8 D_003181ED;
extern u16 D_00318118;

static inline s32 text_001BB940(s32 cursor, s32 x, s32 y, s32 align,
                               s32 flags, s8 *text, void *color) {
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    s32 length = func_0019BEF0((char *)text);
    return SzDuel_DrawWindow_Font_Pipe(cursor, x, y, align, flags,
                        length, text, color);
}

static inline s32 rectangle_001BB940(s32 cursor, Packet_001BB940 *packet,
                                    s32 x, s32 y, u8 *data) {
    ((Header_001BB940 *)(s32)&packet->header)->count = 6;
    ((Header_001BB940 *)(s32)&packet->header)->type = 3;
    ((Header_001BB940 *)(s32)&packet->header)->registers = 0x441;
    ((Header_001BB940 *)(s32)&packet->header)->pad = 0;
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

static inline s32 number_001BB940(s32 cursor, s32 x, s32 y, s32 player) {
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    s32 count = SzData_GetBagCountAll(player);
    return SzDuel_DrawWindow_FontDigit_Pipe(cursor, x, y, 1, 0, 4, count);
}

static inline s32 ready_001BB940(s32 player, s32 deck) {
    s32 count;
    s32 card;

    count = SzData_GetDeckCount(player, deck);
    card = SzData_GetLeader(player, deck);
    return (count >= 0x28 && card != 0x3E7) ? 1 : 0;
}

#pragma opt_propagation off

s32 lSzDuel_DrawBuildDeck_Bag_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe();
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern u8 D_0029086E[];
    extern char D_002BEF9D[];
    u8 *data;
    s32 player;
    u8 *color;
    s8 *sortText;
    s32 special;
    char *titleText;
    char *descText;
    s32 cursor;
    s32 sortIndex;
    s32 selection;
    Packet_001BB940 packet;
    Color_001BB940 shine;
    s32 enabled;
    u8 *sortData;
    s32 sortX;
    s32 sortY;
    s32 numY;
    s32 style;
    s32 sortCursor;
    s32 flags;
    s32 textX;
    s32 textY;
    s32 numX;
    s32 cardX;
    s32 cardY;
    s32 cardIndex;
    s32 deckCursor;
    s32 actionCursor;
    s32 eligible;
    s32 barX;
    s32 barY;
    s32 pageX;
    s32 pageY;

    data = D_00317490.b;
    player = D_003181EC;
    special = ((D_003181ED == 3) || (data[0xD5D] == 2)) ? 1 : 0;
    enabled = 0;
    if (special != 0) {
        if (SzPad_Check(0, 1, 0x100) != 0) {
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
    titleText = D_002BEF8D;
    if (data[0xD5D] == 2) {
        descText = D_002BEF93;
    } else {
        descText = D_002BEF98;
    }
    sortText = D_00290FD0[data[0xCB6 + selection]];
    textX = arg1 + 0x10;
    textY = arg2 + 0x10;
    arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, 0xC, -1, 11, textX, textY, -0xC0, -0x30, 1);
    textX = arg1 + 0x70;
    textY = arg2 + 0x1F;
    cursor = text_001BB940(arg0, textX, textY, 2, 3, (s8 *)titleText, NULL);
    cursor = lSzDuel_DrawWindow_Frame_Pipe(cursor, 0xC, -1, 5, arg1 + 0x10, arg2 + 0x40, -0x40, -0x14, 1);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_0029086E, arg1 + 0x6D2, arg2 + 0x762,
                        0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    {
        s32 c = cursor;
        s32 x = arg1 + 0x27;
        s32 y = arg2 + 0x44;
        cursor = number_001BB940(c, x, y, player);
    }
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 2, arg1 + 0x10, arg2 + 0x54, -0x40, -0x1C, -1, 0);
    if (special != 0) {
        cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AA8, arg1 + 0x6D5, arg2 + 0x77D,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    }
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290828, arg1 + 0x6EC, arg2 + 0x77C,
                        0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 2, arg1 + 0x50, arg2 + 0x40, -0xF0, -0x30, -1, 0);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290896, arg1 + 0x71E, arg2 + 0x765,
                        0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    if (special != 0) {
        cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290ABC, arg1 + 0x717, arg2 + 0x77E,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    }
    sortX = arg1 + 0x738;
    sortY = arg2 + 0x769;
    sortData = data + selection;
    sortIndex = 0;
    do {
        style = -1;
        if (sortData[0xCB6] == sortIndex) {
            style = selection != 0 ? 2 : 1;
        }
        cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290080 + (sortIndex + 0xD1) * 10, sortX, sortY,
                            0, 1, 0, 0, 0, 0, 1, color, style, 0x80);
        sortIndex++;
        sortX += 0x10;
    } while (sortIndex < 10);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_002908A0, arg1 + 0x7DA, arg2 + 0x765,
                        0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    sortCursor = cursor;
    if (special != 0) {
        sortCursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AC6, arg1 + 0x7E3, arg2 + 0x77E,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    }
    textX = arg1 + 0xC8;
    textY = arg2 + 0x5E;
    flags = func_0019BEF0((char *)sortText);
    cursor = SzDuel_DrawWindow_Font_Pipe(sortCursor, textX, textY, 0, (color != NULL ? 8 : 0) | 3, flags, sortText, color);
    cardX = arg1 + 8;
    cardY = arg2 + 0x70;
    cardIndex = 0;
    do {
        cursor = (s32) lSzDuel_DrawBuildDeck_Card_Pipe((void *) cursor, (*(u16 **)(data + 0x6D8))[*(u16 *)(data + 0xC8A) + cardIndex],
                            cardX, cardY, 0, 1);
        cardIndex++;
        cardY += 0x36;
    } while (cardIndex < 5);
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 2, arg1 + 0x10, arg2 + 0x17E, -0xEC, -0x32, -1, 0);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290832, arg1 + 0x6EC, arg2 + 0x8A2,
                        0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    deckCursor = cursor;
    if (special != 0) {
        actionCursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AB2, arg1 + 0x6D5, arg2 + 0x8A7,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        actionCursor = lSzDuel_DrawWindow_ExIcon_Pipe(actionCursor, D_00290A6C, arg1 + 0x6D7, arg2 + 0x8BA,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        {
            s32 c = actionCursor;
            s32 x = arg1 + 0x2C;
            s32 y = arg2 + 0x19D;
            deckCursor = text_001BB940(c, x, y, 1, 0, (s8 *)descText, NULL);
        }
    }
    if (special != 0) {
        eligible = SzData_GetBagCount(player, (*(u16 **)(data + 0x6D8))[*(u16 *)(data + 0xC8A) + data[0xD5E]], 3);
        if (SzFile_InqRequestEx() != 0) {
            eligible = 0;
        }
        if (Taku_Get_Duel5_flg() < 5) {
            eligible = 0;
        }
        if (!ready_001BB940(player, 0) && !ready_001BB940(player, 1) && !ready_001BB940(player, 2)) {
            eligible = 0;
        }
        if (eligible > 0) {
            shine = D_00291360;
            shine.bytes[3] = D_00318118 >> 8;
            titleText = D_002BEF9D;
            textX = arg1 + 0xA4;
            textY = arg2 + 0x191;
            deckCursor = text_001BB940(deckCursor, textX, textY, 0, 3, (s8 *)titleText, &shine);
        }
    }
    barX = arg1 + 0xFC;
    barY = arg2 + 0x17E;
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(deckCursor, 2, barX, barY, -0x3C, -0x32, -1, 0);
    cursor = rectangle_001BB940(cursor, &packet, barX, barY, data);
    pageX = arg1 + 0x11A;
    pageY = arg2 + 0x186;
    cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, pageX, pageY, 1, 2, 3, *(u16 *)(data + 0xC8A) + data[0xD5E] + 1);
    return SzDuel_DrawWindow_FontDigit_Pipe(cursor, pageX, pageY + 0x17, 1, 2, 3, *(u16 *)(data + 0xC8C));
}
#pragma opt_propagation reset

typedef struct Vertex_001BC350 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001BC350;

typedef struct Header_001BC350 {
    u16 type;
    u16 count;
    u32 pad;
    u64 registers;
} Header_001BC350;

typedef struct Packet_001BC350 {
    Header_001BC350 header;
    u8 r, g, b, a;
    f32 q;
    Vertex_001BC350 first;
    Vertex_001BC350 second;
} Packet_001BC350;

extern u8 D_00290080[];
extern u8 D_00290828[];
extern u8 D_00290832[];
extern u8 D_00290896[];
extern u8 D_002908A0[];
extern u8 D_0029095E[];
extern u8 D_00290968[];
extern u8 D_00290972[];
extern u8 D_00290A6C[];
extern u8 D_00290AA8[];
extern u8 D_00290AB2[];
extern u8 D_00290ABC[];
extern u8 D_00290AC6[];
extern s8 *D_00290FD0[];
extern u8 D_002BE8A4[];
extern char D_002BEF93[];
extern char D_002BEFAB[];
extern u8 D_003181ED;

static inline s32 text_001BC350(s32 cursor, s32 x, s32 y, s32 align,
                               s32 flags, s8 *text, void *color) {
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    s32 length = func_0019BEF0((char *)text);
    return SzDuel_DrawWindow_Font_Pipe(cursor, x, y, align, flags,
                        length, text, color);
}

static inline s32 rectangle_001BC350(s32 cursor, Packet_001BC350 *packet,
                                    s32 x, s32 y, u8 *data) {
    ((Header_001BC350 *)(s32)&packet->header)->count = 6;
    ((Header_001BC350 *)(s32)&packet->header)->type = 3;
    ((Header_001BC350 *)(s32)&packet->header)->registers = 0x441;
    ((Header_001BC350 *)(s32)&packet->header)->pad = 0;
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
#pragma alignlabel off

void lSzDuel_DrawBuildDeck_Deck_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern u8 D_00290A76[];
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    u8 *data;
    s32 deckX;
    u8 *color;
    s32 baseX;
    s32 cursor;
    s32 leader;
    char *deckText;
    s8 *sortText;
    s32 state;
    s32 flags;
    s32 special;
    char *actionText;
    Packet_001BC350 packet;
    s32 sortIndex;
    s32 deckY;
    u8 *sortData;
    s32 sortY;
    s32 textX;
    s32 textY;
    s32 sortCursor;
    s32 cardX;
    s32 cardY;
    s32 cardIndex;
    s32 barX;
    s32 barY;
    s32 pageX;
    s32 pageY;
    s32 actionCursor;
    s32 actionX;
    s32 actionY;
    s32 deckCursor;
    s32 selection;
    s32 enabled;
    s32 sortX;
    s32 style;

    leader = D_003181EC;
    data = D_00317490.b;
    special = ((D_003181ED == 4) || (data[0xD5D] == 5)) ? 1 : 0;
    enabled = 0;
    if (special != 0) {
        if (SzPad_Check(0, 1, 0x100) != 0) {
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
    deckText = D_002BEFAB;
    if (data[0xD5D] == 5) {
        actionText = D_002BEF93;
    } else {
        actionText = D_002BEF98;
    }
    sortText = D_00290FD0[data[0xCB9 + selection]];
    state = SzData_GetCurrentDeck(leader);
    baseX = arg1 + 0x280;
    flags = 3;
    arg0 = lSzDuel_DrawWindow_Frame_Pipe(arg0, -1, -1, 11, baseX - 0x50, arg2 + 0x10, -0x40, -0x44, 1);
    cursor = lSzDuel_DrawWindow_PicMini_Pipe(arg0, leader, baseX - 0x4B, arg2 + 0x15, 0x36, 0x3A,
                        *(s32 *)(data + 0xC58), 1);
    cursor = lSzDuel_DrawWindow_Frame_Pipe(cursor, -1, -1, 4, baseX - 0x4B, arg2 + 0x15, -0x36, -0x3A, 1);
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 2, baseX - 0x50, arg2 + 0x54, -0x40, -0x1C, -1, 0);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290828, baseX + 0x674, arg2 + 0x77C,
                        0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    if (special != 0) {
        cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AA8, baseX + 0x695, arg2 + 0x77C,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    }
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 2, baseX - 0x140, arg2 + 0x40, -0xF0, -0x30, -1, 0);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290896, baseX + 0x58E, arg2 + 0x765,
                        0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    if (special != 0) {
        cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290ABC, baseX + 0x587, arg2 + 0x77E,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    }
    sortX = baseX + 0x5A8;
    sortY = arg2 + 0x769;
    sortData = data + selection;
    sortIndex = 0;
    do {
        style = -1;
        if (sortData[0xCB9] == sortIndex) {
            style = selection != 0 ? 2 : 1;
        }
        cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290080 + (sortIndex + 0xD1) * 10, sortX, sortY,
                            0, 1, 0, 0, 0, 0, 1, color, style, 0x80);
        sortIndex++;
        sortX += 0x10;
    } while (sortIndex < 10);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_002908A0, baseX + 0x64A, arg2 + 0x765,
                        0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    sortCursor = cursor;
    if (special != 0) {
        sortCursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AC6, baseX + 0x653, arg2 + 0x77E,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    }
    textX = baseX - 0xC8;
    textY = arg2 + 0x5E;
    if (color != NULL) {
        flags |= 8;
    }
    cursor = text_001BC350(sortCursor, textX, textY, 0, flags, sortText, color);
    cardX = baseX - 0x138;
    cardY = arg2 + 0x70;
    cardIndex = 0;
    do {
        s32 first;
        first = 0;
        if (*(u16 *)(data + 0xC8E) == 0) {
            if (cardIndex == 0) {
                first = 1;
            }
        }
        cursor = (s32) lSzDuel_DrawBuildDeck_Card_Pipe((void *) cursor, (*(u16 **)(data + 0x6DC))[*(u16 *)(data + 0xC8E) + cardIndex],
                            cardX, cardY, first != 0 ? 1 : 0, 0);
        cardIndex++;
        cardY += 0x36;
    } while (cardIndex < 5);
    barX = baseX - 0x138;
    barY = arg2 + 0x17E;
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 2, barX, barY, -0x3C, -0x32, -1, 0);
    cursor = rectangle_001BC350(cursor, &packet, barX, barY, data);
    pageX = baseX - 0x11A;
    pageY = arg2 + 0x186;
    cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, pageX, pageY, 1, 2, 2, *(u16 *)(data + 0xC8E) + data[0xD5F] + 1);
    cursor = SzDuel_DrawWindow_FontDigit_Pipe(cursor, pageX, pageY + 0x17, 1, 2, 2, *(u16 *)(data + 0xC90));
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, 2, baseX - 0xFC, arg2 + 0x17E, -0xEC, -0x32, -1, 0);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290832, baseX + 0x674, arg2 + 0x8A2,
                        0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    deckCursor = cursor;
    if (special != 0) {
        deckCursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290AB2, baseX + 0x695, arg2 + 0x8A7,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    }
    if (special != 0) {
        actionCursor = lSzDuel_DrawWindow_ExIcon_Pipe(deckCursor, D_00290A6C, baseX + 0x699, arg2 + 0x8BA,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        actionX = baseX - 0x4F;
        actionY = arg2 + 0x19D;
        cursor = text_001BC350(actionCursor, actionX, actionY, 1, 0, (s8 *)actionText, NULL);
        deckCursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290A76, baseX + 0x5D8, arg2 + 0x8A2,
                            0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    }
    deckX = baseX - 0xCE;
    deckY = arg2 + 0x184;
    cursor = text_001BC350(deckCursor, deckX, deckY, 1, 0, (s8 *)deckText, NULL);
    cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_0029095E, baseX + 0x5D8, arg2 + 0x8B4,
                        0, 1, 0, 0, 0, 0, state == 0 ? 1 : 0, 0, -1, 0x80);
    {
        s32 x = baseX + 0x608;
        s32 y = arg2 + 0x8B4;
        cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290968, x, y, 0, 1, 0, 0, 0, 0, state == 1 ? 1 : 0, 0, -1, 0x80);
    }
    {
        s32 x = baseX + 0x638;
        s32 y = arg2 + 0x8B4;
        lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290972, x, y, 0, 1, 0, 0, 0, 0, state == 2 ? 1 : 0, 0, -1, 0x80);
    }
}
#pragma alignlabel reset
#pragma opt_propagation reset

typedef struct Entry_001BCCE0 {
    u16 id;
    u8 progress;
    struct {
        u8 index : 5;
        s8 swap : 1;
        s8 mode : 1;
        s8 reverse : 1;
    } flags;
} Entry_001BCCE0;

extern struct Entry_001BA520 *D_00317B60;

s32 lSzDuel_DrawBuildDeck_Ghost_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    Entry_001BCCE0 *entry;
    s32 lower;
    s32 upper;
    s32 i;
    s32 result;
    s32 to;
    s32 from;
    s32 remaining;
    u8 progress;
    u8 amount;

    result = arg0;
    entry = (Entry_001BCCE0 *)D_00317B60;
    lower = arg1 + 8;
    upper = arg1 + 0x148;
    i = 0;
    do {
        progress = entry->progress;
        if (progress != 0) {
            amount = progress;
            if (entry->flags.reverse != 0) {
                amount = 0x80 - progress;
            }
            if (entry->flags.swap != 0) {
                to = lower;
                from = upper;
            } else {
                to = upper;
                from = lower;
            }
            result = lSzDuel_DrawBuildDeck_GhostCard_Pipe(result, entry->id,
                from + (((progress & 0xFF) * (to - from)) >> 7),
                arg2 + 0x70 + entry->flags.index * 0x36,
                entry->flags.mode, amount);
            remaining = entry->progress - 0x10;
            entry->progress = remaining > 0 ? remaining : 0;
        }
        i++;
        entry++;
    } while (i < 8);
    return result;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001BCE20;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001BCE20;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001BCE20;

typedef struct {
    u64 tag[2];
    Color_001BCE20 color;
    Vertex_001BCE20 vertex0;
    Vertex_001BCE20 vertex1;
    u64 end;
} Box_001BCE20;

typedef struct {
    u8 kind;
    u8 pad1;
    u8 attribute : 4;
    u8 level : 4;
    u8 stars;
    u16 link;
    u8 pad6[2];
    u16 attack;
    u16 defense;
} Card_001BCE20;

void *lSzDuel_DrawBuildDeck_Card_Pipe(void *arg0, s32 card, s32 x, s32 y, s32 flag, s32 flag2) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe(s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_Emblem_Pipe(s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 SzDuel_Type2Attr(s32, s32);
    extern s32 lSzDuel_DrawWindow_Frame_Pipe(s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 SzData_GetRank();
    extern u8 D_00290080[];
    extern u8 D_00290020[];
    extern char D_002BEFB7[];
    extern char D_002BE940[];
    extern char D_002BE948[];
    extern s32 D_00290A12;
    extern s32 D_002908E6;
    extern s32 D_002908BE;
    extern s32 D_002908C8;
    extern s32 D_002908F0;
    extern s32 D_0029086E;
    extern s32 D_00290878;
    extern s32 D_0029097C;
    extern s32 D_00290986;
    extern s32 D_00290990;
    s32 player = D_003181EC;
    u8 *state = D_00317490.b;
    s32 id = (s32)arg0;
    Card_001BCE20 *data;
    s32 level;
    s32 rank;
    s32 w;
    u8 *sprite;
    s32 kind;
    s32 attr;
    s32 hint = 0;
    s8 *text;
    s32 px;
    s32 py;
    f32 scale;
    Box_001BCE20 box __attribute__((aligned(8)));
    s8 digit;

    data = (Card_001BCE20 *)SzDuel_GetCardConstInfo(card);
    level = SzData_GetCurrentDeck(player);
    scale = 1.0f;
    if (data == NULL) {
        return (void *)lSzDuel_DrawWindow_Frame_Pipe(id, flag ? 6 : -1, -1, 9, x, y, -0x130, -0x36, flag);
    }
    kind = data->kind >> 5;
    attr = data->kind & 0x1F;
    if (kind == 0) {
        sprite = D_00290080 + attr * 10;
    } else {
        sprite = D_00290080 + (kind + 0x14) * 10;
    }
    attr = SzDuel_Kind2Type(kind);
    rank = SzDuel_Type2Attr(attr, data->attribute);
    if (attr == 0 && data->link != 0xFFFF) {
        attr = 4;
    }
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(id, 1, SzDuel_GetMsgName(card), 0, 0x16));
    id = lSzDuel_DrawWindow_Frame_Pipe(id, flag ? 6 : attr + 7, -1, 9, x, y, -0x130, -0x36, flag);
    if (SzData_IsBagNew(player, card) != 0) {
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A12, x + 0x6C8, y + 0x727, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    } else {
        id = SzDuel_DrawWindow_FontDigit_Pipe(id, x + 8, y + 7, 1, 0, 3, card);
    }
    if (kind == 0) {
        id = lSzDuel_DrawWindow_Emblem_Pipe(id, x + 0x28, y + 3, SzData_GetRank(player, card), 0, 0);
    }
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, sprite, x + 0x6C4, y + 0x73A, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, D_00290020 + rank * 10, x + 0x6DE, y + 0x73A, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    if (flag) {
        text = D_002BEFB7;
        px = x + 0xA0;
        py = y + 0x25;
        id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 0, 2, func_0019BEF0((char *)text), text, hint != 0 ? (s32)D_002BE944 : 0);
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, D_00290080 + (level + 0xE3) * 10, x + 0x7C7, y + 0x730, 0, 1,
                           0, 0, 0, 0, 1, 0, -1, 0x80);
    } else {
        if (kind == 0) {
            id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_002908E6, x + 0x6F8, y + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
            id = SzDuel_DrawWindow_FontDigit_Pipe(id, x + 0x4E, y + 0x25, 1, 0, 2, data->level);
            id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_002908BE, x + 0x7B8, y + 0x723, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
            id = SzDuel_DrawWindow_FontDigit_Pipe(id, x + 0x108, y + 5, 1, 0, 4, data->attack & 0x1FFF);
            id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_002908C8, x + 0x7B8, y + 0x733, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
            id = SzDuel_DrawWindow_FontDigit_Pipe(id, x + 0x108, y + 0x15, 1, 0, 4, data->defense & 0x1FFF);
        }
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_002908F0, x + 0x728, y + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        id = SzDuel_DrawWindow_FontDigit_Pipe(id, x + 0x7E, y + 0x25, 1, 0, 3, data->stars);
        px = x + 0x76D;
        py = y + 0x743;
        if (SzData_GetBagCount(player, card, -1) < 9) {
            id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_0029086E, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        } else {
            id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290878, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        }
        px = x + 0xC0;
        py = y + 0x25;
        id = SzDuel_DrawWindow_FontDigit_Pipe(id, px, py, 1, 0, 1, SzData_GetBagCount(player, card, hint != 0 ? -1 : 3));
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_0029097C, x + 0x78D, y + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0xE0;
        py = y + 0x25;
        digit = SzData_GetBagCount(player, card, 0) + '0';
        id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, 1, &digit, hint != 0 ? (s32)D_002BE944 : 0);
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290986, x + 0x7AD, y + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x100;
        py = y + 0x25;
        digit = SzData_GetBagCount(player, card, 1) + '0';
        id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, 1, &digit, hint != 0 ? (s32)D_002BE944 : 0);
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290990, x + 0x7CD, y + 0x743, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x120;
        py = y + 0x25;
        digit = SzData_GetBagCount(player, card, 2) + '0';
        id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, 1, &digit, hint != 0 ? (s32)D_002BE944 : 0);
    }
    px = x + 0x48;
    py = y + 3;
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, flag ? 6 : attr + 7, px, py, -0xB0, -0x20, -1, 0);
    w = SzMsg_GetInfo(1)[3];
    if (w > 0xA8) {
        scale = 168.0f / (f32)w;
    }
    id = SzMsg_DrawRatioX_Pipe(id, 1, x + 0x4E, y + 9, scale, 1.0f, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
    id = SzMsg_DrawRatioX_Pipe(id, 1, x + 0x4D, y + 8, scale, 1.0f, (s32)D_002BE944, SzMsg_DrawRect_Pipe);
    id = SzMsg_DrawRatioX_Pipe(id, 1, x + 0x4C, y + 7, scale, 1.0f, (s32)D_002BE948, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    if (flag2 != 0 && SzData_GetBagCount(player, card, 3) <= 0) {
        ((Tag_001BCE20 *)box.tag)->flags = 6;
        ((Tag_001BCE20 *)box.tag)->count = 3;
        ((Tag_001BCE20 *)box.tag)->registers = 0x441;
        ((Tag_001BCE20 *)box.tag)->padding = 0;
        ExAssignAlpha(box.tag, ExGetAlphaVal(2));
        box.color.r = 0x80;
        box.color.g = 0x80;
        box.color.b = 0x80;
        box.color.a = 0x40;
        box.color.q = 1.0f;
        box.vertex0.x = (x + 0x6C0) << 4;
        box.vertex0.y = (y + 0x720) << 4;
        box.vertex0.z = *(s32 *)(state + 0xC58);
        box.vertex0.fog = 0;
        box.vertex1.x = (x + 0x7F0) << 4;
        box.vertex1.y = (y + 0x756) << 4;
        box.vertex1.z = *(s32 *)(state + 0xC58);
        box.vertex1.fog = 0;
        id = ExSortPrim_Pipe(id, (s32)box.tag, 0, 0);
    }
    return (void *)id;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001BD8A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001BD8A0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001BD8A0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001BD8A0;

typedef struct {
    u64 tag[2];
    Color_001BD8A0 color;
    u64 uv0;
    Vertex_001BD8A0 vertex0;
    u64 uv1;
    Vertex_001BD8A0 vertex1;
    u64 test;
    s64 texture0;
    s64 texture1;
    u64 clamp;
} Packet_001BD8A0;

static inline void set_uv_001BD8A0(UV_001BD8A0 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}


s32 lSzDuel_DrawBuildDeck_GhostCard_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5) {
    Packet_001BD8A0 packet __attribute__((aligned(8)));
    s32 width = 0x130;
    s32 height = 0x36;
    s32 x;
    s32 y;
    void *texture;
    s32 output;

    ((Tag_001BD8A0 *)packet.tag)->flags = 0x26;
    ((Tag_001BD8A0 *)packet.tag)->count = 5;
    ((Tag_001BD8A0 *)packet.tag)->registers = 0x42421;
    ((Tag_001BD8A0 *)packet.tag)->padding = 0;
    ((Tag_001BD8A0 *)packet.tag)->flags |= 0x800;
    ExAssignAlpha(packet.tag, 0x44 | ((s64)0x80 << 32));
    packet.color.r = 0x80;
    packet.color.g = 0x80;
    packet.color.b = 0x80;
    packet.color.a = arg5;
    packet.color.q = 1.0f;

    arg0 = (s32)RhBase_EnableRenderFrame((void *)arg0);
    texture = lSzDuel_DrawBuildDeck_Card_Pipe(RhBase_ClearRenderFrame((u8 *)arg0, 0), arg1, 0, 0, arg4, 0);
    RhBase_GetTextureInfoForRender(&packet.texture0, &packet.texture1);
    output = RhText_SetTextureFlush((s32)RhBase_DisableRenderFrame(texture));

    x = arg2 + 0x6C0;
    y = arg3 + 0x720;
    set_uv_001BD8A0((UV_001BD8A0 *)&packet.uv0, 0, 0);
    set_uv_001BD8A0((UV_001BD8A0 *)&packet.uv1, width << 4, height << 4);
    packet.vertex0.x = (x << 4) - 8;
    packet.vertex0.y = (y << 4) - 8;
    packet.vertex0.z = D_003180E8;
    packet.vertex0.fog = 0;
    packet.vertex1.x = ((x + width) << 4) - 8;
    packet.vertex1.y = ((y + height) << 4) - 8;
    packet.vertex1.z = D_003180E8;
    packet.vertex1.fog = 0;
    return ExSortPrim_Pipe(output, (s32)packet.tag, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_040", func_001BDAF0);

typedef struct Vertex_001BE5F0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001BE5F0;

typedef struct Header_001BE5F0 {
    u16 type;
    u16 count;
    u32 pad;
    u64 registers;
} Header_001BE5F0;

typedef struct Packet_001BE5F0 {
    Header_001BE5F0 header;
    u8 r, g, b, a;
    f32 q;
    Vertex_001BE5F0 first;
    Vertex_001BE5F0 second;
    u64 unused;
} Packet_001BE5F0;

typedef union Color_001BE5F0 {
    f32 value;
    u8 bytes[4];
} Color_001BE5F0;

typedef struct CardBits_001BE5F0 {
    u64 unused : 16;
    u64 subtype : 4;
    u64 level : 4;
    u64 rest : 40;
} CardBits_001BE5F0;

typedef union Card_001BE5F0 {
    struct {
        u8 kind, unused, stats, cost;
        u16 code, field, attack, defense;
    } data;
    CardBits_001BE5F0 bits;
} Card_001BE5F0;

extern u8 D_00290020[];
extern u8 D_00290080[];
extern u8 D_0029008A[];
extern Color_001BE5F0 D_00291368;
extern u8 D_002BE94C[];
extern char D_002BEFCB[];
extern char D_002BEFDB[];
extern u8 D_003181EC;
extern u16 D_00318118;


static inline s32 text_001BE5F0(s32 cursor, s32 x, s32 y, s32 align,
                               s32 flags, s8 *text, void *color) {
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    s32 length = func_0019BEF0((char *)text);
    return SzDuel_DrawWindow_Font_Pipe(cursor, x, y, align, flags,
                        length, text, color);
}

static inline s32 loading_001BE5F0(s32 cursor, Packet_001BE5F0 *packet,
                                  s32 x, s32 y, u8 *data) {
    ((Header_001BE5F0 *)(s32)&packet->header)->count = 6;
    ((Header_001BE5F0 *)(s32)&packet->header)->type = 3;
    ((Header_001BE5F0 *)(s32)&packet->header)->registers = 0x441;
    ((Header_001BE5F0 *)(s32)&packet->header)->pad = 0;
    packet->r = 0;
    packet->g = 0;
    packet->b = 0;
    packet->a = 0x80;
    packet->q = 1.0f;
    packet->first.x = x << 4;
    packet->first.y = y << 4;
    packet->first.z = *(s32 *)(data + 0xC58);
    packet->first.fog = 0;
    packet->second.x = (x + 0x80) << 4;
    packet->second.y = (y + 0x80) << 4;
    packet->second.z = *(s32 *)(data + 0xC58);
    packet->second.fog = 0;
    return ExSortPrim_Pipe(cursor, (s32)&packet->header, 0, 0);
}

static inline s32 pos_001BE5F0(s32 x, s32 slide) {
    return x + slide;
}

static inline f32 fit_001BE5F0(s32 index, s32 limit) {
    extern s32 *SzMsg_GetInfo(s32);
    s32 width = SzMsg_GetInfo(index)[3];
    if (width > limit) {
        return (f32)limit / width;
    }
    return 1.0f;
}

#pragma opt_propagation off

s32 lSzDuel_DrawBuildDeck_Detail_Basic_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe();
    extern s32 lSzDuel_DrawWindow_PicItem_Pipe();
    extern s32 SzMsg_DrawX_Pipe();
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzData_GetRank();
    extern s32 SzDuel_Type2Attr();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern char D_002BE940[];
    extern u8 D_002901B6[];
    extern u8 D_002908F0[];
    s32 pictureX;
    s32 pictureY;
    u8 *data;
    Card_001BE5F0 *card;
    s32 palette;
    s32 attribute;
    s32 message;
    s32 cardType;
    s32 player;
    u8 *name;
    s32 cardId;
    s32 deckIndex;
    s32 subtype;
    s8 *loadingText;
    s32 slide;
    s32 nameCtx;
    s32 nameX;
    s32 cursor;
    s8 text[0x58];
    Packet_001BE5F0 packet __attribute__((aligned(8)));
    Color_001BE5F0 color;
    f32 scale;
    s32 labelY;
    s32 textX;
    s32 textY;
    s32 labelX;
    s32 boxX;
    s32 numberX;
    s32 i;
    s32 baseX;
    s32 width;
    s32 big;
    s32 c;
    s32 x;
    s32 y;
    s32 stars;

    data = D_00317490.b;
    player = D_003181EC;
    card = (Card_001BE5F0 *)SzDuel_GetCardConstInfo(arg1);
    slide = arg4 ? 0x280 : -0x140;
    deckIndex = -1;
    if (arg1 == 0x29F) {
        name = D_0029008A;
        message = 0x26;
        cardType = 0;
        deckIndex = 0;
        palette = 0;
        subtype = 1;
    } else {
        if (card == NULL) {
            return arg0;
        }
        cardType = card->data.kind >> 5;
        attribute = card->data.kind & 0x1F;
        if (cardType == 0) {
            deckIndex = SzData_GetRank(player, arg1);
            name = D_00290080 + attribute * 10;
            message = attribute + 0x25;
        } else {
            name = D_00290080 + (cardType + 0x14) * 10;
            message = cardType + 0x1E;
        }
        palette = SzDuel_Kind2Type(cardType);
        subtype = SzDuel_Type2Attr(palette, card->data.stats & 0xF);
        if (palette == 0 && card->data.code != 0xFFFF) {
            palette = 4;
        }
    }
    arg0 = SzMsg_LoadFont_Pipe(arg0, 1, 0x9A, 0, 0x16);
    cursor = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(SzMsg_LoadFont_Pipe(SzMsg_LoadFont_Pipe(
          SzMsg_LoadFont_Pipe(SzMsg_LoadFont_Pipe(SzMsg_LoadFont_Pipe(SzMsg_LoadFont_Pipe(
          SzMsg_LoadFont_Pipe(SzMsg_LoadFont_Pipe(arg0, 2, message, 0, 0x2C),
          3, 0x9B, 0, 0x42), 4, subtype + 0x3B, 0, 0x58),
          5, 0x9C, 0, 0x6E), 6, 0x9D, 0, 0x84), 7, 0x9E, 0, 0x9A),
          8, 0xA0, 0, 0xB0), 9, deckIndex + 0x52, 0, 0xC6), 10, 0x9F, 0, 0xDC));
    pictureY = arg3 + 0x57;
    baseX = arg2 + slide;
    pictureX = baseX + 0x9D;
    cardId = arg1 == 0x29F ? arg1 : SzData_ExchSpecial(player, arg1);
    if (SzText_GetReadyItem(1, cardId) != 0) {
        cursor = lSzDuel_DrawWindow_PicItem_Pipe(cursor, cardId, pictureX, pictureY, 0x80, 0x80,
                            *(s32 *)(data + 0xC58));
    } else {
        loadingText = D_002BEFCB;
        pictureX += 0x6C0;
        color = D_00291368;
        color.bytes[3] = D_00318118 >> 8;
        pictureY += 0x720;
        cursor = loading_001BE5F0(cursor, &packet, pictureX, pictureY, data);
        {
            s32 c = cursor;
            s32 x = baseX + 0xDD;
            s32 y = arg3 + 0x87;
            cursor = text_001BE5F0(c, x, y, 0, 2, loadingText, &color);
        }
    }
    cursor = lSzDuel_DrawWindow_Frame_Pipe(cursor, -1, -1, 11, baseX + 0x98, arg3 + 0x52, -0x8A, -0x8A, 1);
    textX = baseX + 0xDD;
    textY = arg3 + 0xDE;
    func_0019B648(text, D_002BEFDB, arg1);
    cursor = text_001BE5F0(cursor, textX, textY, 1, 2, text, NULL);
    labelX = baseX + 0x1D;
    cursor = SzMsg_DrawX_Pipe(cursor, 1, labelX, arg3 + 0x35, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
    x = boxX = baseX + 0x4E;
    y = arg3 + 0x30;
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, palette + 7, x, y, -0xD4, -0x20, -1, 0);
    nameCtx = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, name, pos_001BE5F0(arg2 + 0x712, slide), arg3 + 0x754,
                           0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    nameX = baseX + 0x73;
    labelY = arg3 + 0x34;
    width = SzMsg_GetInfo(2)[3];
    big = width > 172;
    if (big) {
        scale = 172.0f / width;
    } else {
        scale = 1.0f;
    }
    cursor = SzMsg_DrawRatioX_Pipe(nameCtx, 2, nameX, labelY, scale, 1.0f, (s32)D_002BE94C, SzMsg_DrawRect_Pipe);
    if (cardType == 0) {
        cursor = SzMsg_DrawX_Pipe(cursor, 3, labelX, arg3 + 0x56, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
        y = arg3 + 0x51;
        cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, palette + 7, boxX, y, -0x48, -0x20, -1, 0);
        cursor = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_00290020 + subtype * 10, pos_001BE5F0(arg2 + 0x726, slide),
                           arg3 + 0x775, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        cursor = SzMsg_DrawX_Pipe(cursor, 5, labelX, arg3 + 0x77, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
        y = arg3 + 0x72;
        cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, palette + 7, boxX, y, -0x48, -0x20, -1, 0);
        x = numberX = baseX + 0x4F;
        y = arg3 + 0x77;
        if (card != NULL) {
            cursor = SzDuel_DrawWindow_ExDigit_Pipe(cursor, x, y, 4, card->data.attack & 0x1FFF, 1, 0, 0);
        }
        cursor = SzMsg_DrawX_Pipe(cursor, 6, labelX, arg3 + 0x98, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
        y = arg3 + 0x93;
        cursor = c = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, palette + 7, boxX, y, -0x48, -0x20, -1, 0);
        y = arg3 + 0x98;
        if (card != NULL) {
            cursor = SzDuel_DrawWindow_ExDigit_Pipe(c, numberX, y, 4, card->data.defense & 0x1FFF, 1, 0, 0);
        }
        labelY = arg3 + 0xB3;
        cursor = SzMsg_DrawRatioX_Pipe(cursor, 7, labelX, labelY, fit_001BE5F0(7, 116), 1.0f, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
        x = baseX + 0x1A;
        y = arg3 + 0xC9;
        stars = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, palette + 7, x, y, -0x7C, -0x26, -1, 0);
        y = arg3 + 0x7EC;
        x = pos_001BE5F0(arg2 + 0x6DD, slide);
        if (card != NULL) {
            for (i = 0; i < (s32)card->bits.level; i++) {
                stars = lSzDuel_DrawWindow_ExIcon_Pipe(stars, D_002901B6, x + (i % 6) * 16,
                                   y + (i / 6) * 16, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
            }
        }
        x = baseX + 0x87;
        y = arg3 + 0xD6;
        if (card != NULL) {
            stars = SzDuel_DrawWindow_FontDigit_Pipe(stars, x, y, 1, 2, 2, card->bits.level);
        }
        labelY = arg3 + 0xF4;
        cursor = SzMsg_DrawRatioX_Pipe(stars, 8, labelX, labelY, fit_001BE5F0(8, 116), 1.0f, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
        cursor = lSzDuel_DrawWindow_Emblem_Pipe(cursor, baseX + 0x93, arg3 + 0xEF, deckIndex, 0, 0);
        x = baseX + 0xB4;
        y = arg3 + 0xEF;
        cursor = c = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, palette + 7, x, y, -0x6E, -0x20, -1, 0);
        x = baseX + 0xBF;
        y = arg3 + 0xF5;
        if (card != NULL) {
            cursor = SzMsg_DrawX_Pipe(c, 9, x, y, (s32)D_002BE94C, SzMsg_DrawRect_Pipe);
        }
    }
    labelY = arg3 + 0x115;
    cursor = SzMsg_DrawRatioX_Pipe(cursor, 10, labelX, labelY, fit_001BE5F0(10, 116), 1.0f, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
    cursor = lSzDuel_DrawWindow_ExBoard_Pipe(cursor, palette + 7, baseX + 0xB4, arg3 + 0x110, -0x6E, -0x20, -1, 0);
    cursor = c = lSzDuel_DrawWindow_ExIcon_Pipe(cursor, D_002908F0, pos_001BE5F0(arg2 + 0x77B, slide), arg3 + 0x838,
                       0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    x = baseX + 0xDA;
    y = arg3 + 0x116;
    if (card != NULL) {
        cursor = SzDuel_DrawWindow_ExDigit_Pipe(c, x, y, 3, card->data.cost, 1, 0, 0);
    }
    SzMsg_Free(1);
    SzMsg_Free(2);
    SzMsg_Free(3);
    SzMsg_Free(4);
    SzMsg_Free(5);
    SzMsg_Free(6);
    SzMsg_Free(7);
    SzMsg_Free(8);
    SzMsg_Free(9);
    SzMsg_Free(10);
    return cursor;
}

#pragma opt_propagation reset

s32 lSzDuel_DrawBuildDeck_Detail_Special_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern char D_002BE940[];
    s32 offset;
    s32 id;
    s32 *size;
    s32 x;
    s32 y;
    s32 result;
    f32 scaleX;
    f32 scaleY;

    if (arg4 != 0) {
        offset = 0x280;
    } else {
        offset = -0x140;
    }
    scaleX = 1.0f;
    scaleY = 1.0f;
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, arg1 + 0x496, 0, 0x16));
    size = SzMsg_GetInfo(1);
    x = arg2 + offset + 0x1C;
    y = arg3 + 0x30;
    if (size[3] > 0x106) {
        scaleX = 262.0f / size[3];
    }
    if (size[4] > 0x100) {
        scaleY = 256.0f / size[4];
    }
    result = SzMsg_DrawRatioX_Pipe(id, 1, x, y, scaleX, scaleY, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    return result;
}

s32 lSzDuel_DrawBuildDeck_Detail_Enchant_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern s32 *SzMsg_GetInfo(s32);
    extern u8 TaEnc_GetEnchantLst(u16, u16 *);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    s32 count;
    u16 list[24];
    s32 offset;
    s32 i;
    s32 y;
    s32 x;
    s32 *size;
    s32 id;
    f32 scale;

    offset = arg4 ? 0x280 : -0x140;
    if (arg1 >= 0x2AB) {
        return arg0;
    } else {
        count = TaEnc_GetEnchantLst(arg1 & 0xFFFF, list);
        i = 0;
        if (i < count) {
            do {
                arg0 = SzMsg_LoadFont_Pipe(arg0, i + 1, SzDuel_GetMsgName(list[i]), 0, (i + 1) * 22);
                i++;
            } while (i < count);
        }
        arg0 = RhText_SetTextureFlush(arg0);
        i = 0;
        if (i < count) {
            y = arg3 + 0x30;
            x = arg2 + offset + 0x1C;
            do {
                size = SzMsg_GetInfo(i + 1);
                scale = 1.0f;
                id = lSzDuel_DrawWindow_ExBoard_Pipe(arg0, arg5, x, y, -0x106, -0x1A, -1, 0);
                if (size[3] > 0xFE) {
                    scale = 254.0f / size[3];
                }
                arg0 = SzMsg_DrawRatioX_Pipe(id, i + 1, x + 5, y + 2, scale, 1.0f, (s32)D_002BE940, SzMsg_DrawRect_Pipe);
                SzMsg_Free(i + 1);
                i++;
                y += 0x1A;
            } while (i < count);
        }
        return arg0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_040", lSzDuel_DrawBuildDeck_Detail_Ability_Pipe);

INCLUDE_ASM("asm/nonmatchings/main_040", lSzDuel_DrawBuildDeck_Library_Pipe);

s32 lSzDuel_DrawBuildDeck_BagCursor_Pipe(s32 id, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern char D_002BEFE7[];
    extern char D_002BEFEC[];
    extern char D_002BEFF3[];
    extern char D_002BEFFB[];
    extern s32 D_00290A62;
    extern s32 D_00290A58;
    extern s32 D_00290A4E;
    extern s32 D_00290A76;
    extern s32 D_00290864;
    extern u8 D_003181ED;
    u8 *state = D_00317490.b;
    s32 flag = (D_003181ED == 3) ? 1 : 0;
    s8 *text1 = D_002BEFE7;
    s8 *text2 = D_002BEFEC;
    s8 *text3 = D_002BEFF3;
    s8 *text4 = D_002BEFFB;
    s32 hint = 0;
    s32 x;
    s32 y;
    s32 sx;
    s32 sy;
    s32 px;
    s32 py;

    x = arg1 + 8;
    y = arg2 + 0x70 + arg3 * 0x36;
    sx = x + 0x6C0;
    sy = y + 0x720;
    id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, 4, 6, x - 2, y - 2, -0x130, -0x36, 1);
    if (*(u16 *)(state + 0xC96) != 0) {
        return id;
    }
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xD, -1, 7, x, y + 0x36, -0x130, -0x14, 1);
    px = sx + 5;
    py = sy + 0x38;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, px + 0x11, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    px = x + 0x2C;
    py = y + 0x3B;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text1), text1,
                       hint != 0 ? (s32)D_002BE944 : 0);
    if (flag) {
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A4E, sx + 0x6B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x81;
        id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text2), text2,
                           hint != 0 ? (s32)D_002BE944 : 0);
    } else {
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A4E, sx + 0x5B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x71;
        id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text3), text3,
                           hint != 0 ? (s32)D_002BE944 : 0);
    }
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A76, sx + 0xC9, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    px = x + 0xDF;
    py = y + 0x3B;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text4), text4,
                       hint != 0 ? (s32)D_002BE944 : 0);
    return lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290864, sx + 0x11B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
}

s32 lSzDuel_DrawBuildDeck_DeckCursor_Pipe(s32 id, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern char D_002BEFE7[];
    extern char D_002BEFEC[];
    extern char D_002BEFF3[];
    extern s32 D_00290A62;
    extern s32 D_00290A58;
    extern s32 D_00290A4E;
    extern u8 D_003181ED;
    u8 *state = D_00317490.b;
    s32 flag = (D_003181ED == 4) ? 1 : 0;
    s8 *text1 = D_002BEFE7;
    s8 *text2 = D_002BEFEC;
    s8 *text3 = D_002BEFF3;
    s32 hint = 0;
    s32 x;
    s32 y;
    s32 sx;
    s32 sy;
    s32 px;
    s32 py;

    x = arg1 + 0x148;
    y = arg2 + 0x70 + arg3 * 0x36;
    sx = x + 0x6C0;
    sy = y + 0x720;
    id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, 4, 6, x - 2, y - 2, -0x130, -0x36, 1);
    if (*(u16 *)(state + 0xC96) != 0) {
        return id;
    }
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xD, -1, 7, x, y + 0x36, -0x130, -0x14, 1);
    px = sx + 5;
    py = sy + 0x38;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, px + 0x11, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    px = x + 0x2C;
    py = y + 0x3B;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text1), text1,
                       hint != 0 ? (s32)D_002BE944 : 0);
    if (flag) {
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A4E, sx + 0x6B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x81;
        py = y + 0x3B;
        return SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text2), text2,
                             hint != 0 ? (s32)D_002BE944 : 0);
    } else {
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A4E, sx + 0x5B, sy + 0x38, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        px = x + 0x71;
        py = y + 0x3B;
        return SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 0, func_0019BEF0((char *)text3), text3,
                             hint != 0 ? (s32)D_002BE944 : 0);
    }
}

void lSzDuel_DrawBuildDeck_Reincarnation_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 lSzDuel_DrawDialog_Window_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern s32 SzMsg_DrawX_Pipe();
    extern char D_002BEF9D[];
    extern u16 D_0031811A;
    extern u8 D_003181EE;
    s32 text0;
    char *text1;
    char *text2;
    s32 table;
    u8 *state;
    s32 icon;
    s32 res;
    s32 *info;

    state = D_00317490.b;
    text0 = (s32)D_002BEF9D;
    text1 = D_002BEF6F;
    text2 = D_002BEF73;
    table = *(u16 *)((u8 *)D_00317B68 + (D_0031811A + D_003181EE) * 2);
    icon = SzDuel_GetMsgName(table);
    arg0 = lSzDuel_DrawDialog_Window_Pipe(arg0, 2, table, icon, arg1 + 0x140, arg2 + 0x48, -0x1CC, 0x130,
                         func_0019BEF0((char *)text0), text0, 0);
    res = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, 0x92, 0, 0x16));
    info = SzMsg_GetInfo(1);
    res = SzMsg_DrawX_Pipe(res, 1, (arg1 + 0x140) - (info[3] >> 1), (arg2 + 0x154) - (info[4] + 0xC), 0,
                        SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    res = SzDuel_DrawWindow_Font_Pipe(res, arg1 + 0xCD, arg2 + 0x154, 2, 3, func_0019BEF0(text1), text1,
                        D_003181C6 != 0 ? 0 : (s32)D_002BE944);
    SzDuel_DrawWindow_Font_Pipe(res, arg1 + 0x1B3, arg2 + 0x154, 2, 3, func_0019BEF0(text2), text2,
                  state[0xD36] != 0 ? (s32)D_002BE944 : 0);
}

s32 lSzDuel_DrawBuildDeck_ReincarnationDone_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    u8 *state;
    char *text;
    u16 *cards;
    s32 icon;
    s32 color0;
    s32 color1;
    s32 result;
    extern char D_002BEF9D;
    extern struct Entry_001BA520 *D_00317B60;
    extern s32 lSzDuel_DrawDialog_Window_Pipe();
    extern s32 lSzDuel_DrawWindow_PicItem_Pipe();
    extern s32 ExClampMode_Pipe();
    extern s64 ExGetRegVal();

    state = D_00317490.b;
    text = &D_002BEF9D;
    cards = (u16 *)((u8 *)D_00317B60 + 0x20);
    icon = -1;
    if ((s32) D_003181C6 >= 0x80) {
        icon = 0x93;
        if ((s32)state[0xD57] < 3) {
            icon = SzDuel_GetMsgName(cards[(u8)state[0xD57]]);
        }
    }
    arg0 = lSzDuel_DrawDialog_Window_Pipe(arg0, 2, -1, icon, arg1 + 0x140, arg2 + 0x5D,
                         -0x1CC, 0x106, func_0019BEF0(text),
                         text, (s32)state[0xD36] < 0x80 ? 0 : 1);
    if (state[0xD57] == 0) {
        arg0 = ExClampMode_Pipe(arg0, ((s64)state[0xD36] << 14) | 0xA |
                                   ((s64)state[0xD36] << 34));
        color0 = color1 = state[0xD36];
    } else {
        color1 = color0 = 0x80;
    }
    arg0 = lSzDuel_DrawWindow_PicItem_Pipe(arg0, cards[0], arg1 + 0x74, arg2 + 0xBB,
                         color0, color1, *(s32 *)(state + 0xC58));
    if ((s32)state[0xD57] <= 0) {
        color0 = color1 = 0;
    } else if (state[0xD57] == 1) {
        arg0 = ExClampMode_Pipe(arg0, ((s64)state[0xD36] << 14) | 0xA |
                                   ((s64)state[0xD36] << 34));
        color0 = color1 = state[0xD36];
    } else {
        color1 = color0 = 0x80;
    }
    arg0 = lSzDuel_DrawWindow_PicItem_Pipe(arg0, cards[1], arg1 + 0x100, arg2 + 0xBB,
                         color0, color1, *(s32 *)(state + 0xC58));
    if ((s32)state[0xD57] < 2) {
        color0 = color1 = 0;
    } else if (state[0xD57] == 2) {
        arg0 = ExClampMode_Pipe(arg0, ((s64)state[0xD36] << 14) | 0xA |
                                   ((s64)state[0xD36] << 34));
        color0 = color1 = state[0xD36];
    } else {
        color1 = color0 = 0x80;
    }
    result = lSzDuel_DrawWindow_PicItem_Pipe(arg0, cards[2], arg1 + 0x18C, arg2 + 0xBB,
                           color0, color1, *(s32 *)(state + 0xC58));
    if ((s32)state[0xD57] < 3) {
        result = ExClampMode_Pipe(result, ExGetRegVal(0, 4));
    }
    return result;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

typedef unsigned int DotrCaptionWord;
extern DotrCaptionWord func_001B0CE0_b(DotrCaptionWord cursor, int a1, int a2, int texture, int x, int y, int w, int h, ...);
extern char D_002BF000[];
typedef int DotrCaptionAddress_1c0a30;
struct DotrCaptionControl_1c0a30 {
    char unknown_000[0x6d0];
    DotrCaptionAddress_1c0a30 work;
    char unknown_6d4[4];
    unsigned short *list_cards;
    unsigned short *deck_cards;
    char unknown_6e0[0xc58 - 0x6e0];
    int pic_z;
    char unknown_c5c[0xc8a - 0xc5c];
    unsigned short list_cursor;
    char unknown_c8c[2];
    unsigned short deck_cursor;
    char unknown_c90[2];
    short slide;
    char unknown_c94[0xcc2 - 0xc94];
    char pass[8];
    char unknown_cca[0xd36 - 0xcca];
    unsigned char choice;
    char unknown_d37[0xd57 - 0xd37];
    unsigned char step;
    char unknown_d58[0xd5c - 0xd58];
    unsigned char side;
    unsigned char mode;
    unsigned char list_top;
    unsigned char deck_top;
    unsigned char grid_top;
    unsigned char grid_col;
    unsigned char grid_row;
};
extern struct DotrCaptionControl_1c0a30 D_00317490_1c0a30;
struct DotrCaptionMsgInfo {
    int unknown_00[3];
    int width;
    int height;
};
extern struct DotrCaptionMsgInfo *func_001FEAB0_b(int index);
extern DotrCaptionWord func_001FE7D0_b(DotrCaptionWord cursor, int index, int x, int y, void *e, void (*function)(void));
extern void func_001FDFE0_b(void);
extern char D_00290080_1c0a30[];
extern DotrCaptionWord func_001B3CC0_1c0a30(DotrCaptionWord cursor, char *def, int x, int y, int a4, int a5, int a6, int a7,
                                             int a8, int a9, int a10, int a11, int a12, int a13);
extern DotrCaptionWord func_001B4780_1c0a30(DotrCaptionWord cursor, int a1, int a2, int a3, int x, int y, int a6, int a7, long a8);

unsigned int lSzDuel_DrawBuildDeck_Password_Pipe(unsigned int cursor, int x, int y)
{
    char *text = D_002BF000 + 2;
    struct DotrCaptionMsgInfo *info;
    int px;
    int py;

    cursor = func_001B0CE0_b(cursor, 2, -1, 148, x + 320, y + 142, 346, 164, func_0019BEF0(text), text, 0L);
    cursor = SzDuel_DrawWindow_Font_Pipe(cursor, x + 320, y + 236, 2, 2, 8, D_00317490_1c0a30.pass, 0);
    px = x + 230 + D_00317490_1c0a30.choice * 22;
    py = y + 231;
    cursor = func_001B4780_1c0a30(cursor, -1, -1, 7, px, py, -26, -28, 1L);
    cursor = SzMsg_LoadFont_Pipe(cursor, 1, 170, 0, 22);
    cursor = SzMsg_LoadFont_Pipe(cursor, 2, 173, 0, 44);
    cursor = RhText_SetTextureFlush(cursor);
    info = func_001FEAB0_b(1);
    cursor = func_001FE7D0_b(cursor, 1, x + 234 - (info->width >> 1), y + 272, 0, func_001FDFE0_b);
    px = x + 1914 - (info->width >> 1);
    py = y + 2096;
    cursor = func_001B3CC0_1c0a30(cursor, D_00290080_1c0a30 + 2490, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 128);
    px = x + 1938 - (info->width >> 1);
    cursor = func_001B3CC0_1c0a30(cursor, D_00290080_1c0a30 + 2480, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 128);
    info = func_001FEAB0_b(2);
    px = x + 406 - (info->width >> 1);
    py = y + 272;
    cursor = func_001FE7D0_b(cursor, 2, px, py, 0, func_001FDFE0_b);
    px = x + 2110 - (info->width >> 1);
    py = y + 2096;
    return func_001B3CC0_1c0a30(cursor, D_00290080_1c0a30 + 2500, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, 128);
}

s32 lSzDuel_DrawBuildDeck_PasswordSuccess_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    s32 text;
    u16 *cards;
    s32 name;
    s32 width;
    s32 result;
    f32 scale;
    extern struct Entry_001BA520 *D_00317B60;
    extern s32 lSzDuel_DrawDialog_Window_Pipe();
    extern s32 lSzDuel_DrawWindow_PicItem_Pipe();
    extern s32 SzMsg_DrawX_Pipe();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));

    text = (s32)D_002BF002;
    cards = (u16 *)((u8 *)D_00317B60 + 0x20);
    name = SzDuel_GetMsgName(cards[0]);
    scale = 1.0f;
    arg0 = lSzDuel_DrawDialog_Window_Pipe(arg0, 2, -1, -1, arg1 + 0x140, arg2 + 0x41, 0x1CC, 0x13E,
                         func_0019BEF0((char *)text), text, 1);
    result = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(SzMsg_LoadFont_Pipe(
        lSzDuel_DrawWindow_PicItem_Pipe(arg0, cards[0], arg1 + 0x100, arg2 + 0xB5, 0x80, 0x80, D_003180E8),
        1, 0x95, 0, 0x16), 2, name, 0, 0x42));
    result = SzMsg_DrawX_Pipe(result, 1, (arg1 + 0x140) - (((s32 *)SzMsg_GetInfo(1))[3] >> 1),
                           arg2 + 0x7D, 0, SzMsg_DrawRect_Pipe);
    width = ((s32 *)SzMsg_GetInfo(2))[3];
    if (width > 0x1B4) {
        scale = 436.0f / (f32)width;
    }
    result = SzMsg_DrawRatioX_Pipe(result, 2, (arg1 + 0x140) - (s32)(((f32)width * scale) / 2.0f),
                           arg2 + 0x141, scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    SzMsg_Free(2);
    return result;
}

void lSzDuel_DrawBuildDeck_PasswordFail_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32)D_002BF002;

    lSzDuel_DrawDialog_Window_Pipe(arg0, 2, -1, 0x96, arg1 + 0x140, arg2 + 0x8D,
                  0x1CC, 0xA6, func_0019BEF0((char *)text), text, 1);
}

void lSzDuel_DrawBuildDeck_PasswordDone_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32)D_002BF002;

    lSzDuel_DrawDialog_Window_Pipe(arg0, 2, -1, 0x97, arg1 + 0x140, arg2 + 0x8D,
                  0x1CC, 0xA6, func_0019BEF0((char *)text), text, 1);
}

void lSzDuel_DrawBuildDeck_Caution_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32)D_002BEF67;

    lSzDuel_DrawDialog_Window_Pipe(arg0, 2, -1, 0x7C, arg1 + 0x140, arg2 + 0xA3,
                  0x140, 0x7A, func_0019BEF0((char *)text), text, 1);
}

typedef struct {
    f32 x, y, z, w;
} Quad_001C1090;

typedef struct {
    Quad_001C1090 v[9];
} Block_001C1090;

typedef struct {
    f32 x, y, z;
} Vec3_001C1090;

extern Quad_001C1090 D_00291370;
extern Block_001C1090 D_00291380;
extern Quad_001C1090 D_00291410;
extern Vec3_001C1090 D_00291420;


void SzDuel_Init3DView(s32 arg0) {
    u8 *duel = D_00317490.b;
    s32 i;
    Quad_001C1090 a;
    Block_001C1090 b;
    Quad_001C1090 c;
    Vec3_001C1090 d;
    extern s32 SzModel_SetAnimSpeed(s32, f32);
    extern s32 SzView_SetStraightLight();

    if (arg0 >= 0) {
        s32 id = SzDuel_New2Xax(arg0);

        SzModel_Load(0x1D, -1, id, 1);
        SzSound_TransferSEGrp(2, id, 0);
        return;
    }
    a = D_00291370;
    b = D_00291380;
    c = D_00291410;
    d = D_00291420;
    for (i = 0; i < 0x54; i++) {
        SzModel_SetDrawFlag(i, 0);
    }
    for (i = 0; i < 0x28; i++) {
        SzModel_SetDrawFlag(i + 0x22, 1);
    }
    SzModel_SetDrawFlag(0x1D, 1);
    SzModel_SetScale(0x1D, NULL);
    SzModel_SetRot(0x1D, &a);
    SzModel_SetRotC(0x1D, &a);
    SzModel_SetPos(0x1D, &c);
    SzModel_SetDeform(0x1D, 0);
    SzModel_SetDeformRatio(0x1D, 0);
    SzModel_SetAnimDirect(0x1D, 0);
    SzModel_SetAnimDir(0x1D, 1);
    SzModel_SetAnimSpeed(0x1D, 1.0f);
    SzModel_SetRgba(0x1D, 0, NULL);
    SzModel_SetFilter(0x1D, 1, NULL);
    SzModel_SetIntensity(0x1D, &d.x);
    SzView_SetStraightLight(0, 4, &b);
    SzView_SetCP(0, &c);
    duel[0xD35] = 0;
}

void SzDuel_Term3DView(void) {
    SzModel_Preset(0x1D, -1, 0x3E7);
    SzView_SetPointLight(0, 4, 0);
}

typedef struct Vec4_001C12B0 {
    f32 x, y, z, w;
} Vec4_001C12B0;


static inline s32 abs_001C12B0(s32 value) {
    return value >= 0 ? value : -value;
}

static inline s32 deadzone_001C12B0(s32 value) {
    if (abs_001C12B0(value) >= 48) {
        value -= value > 0 ? 48 : -48;
    } else {
        value = 0;
    }
    return value;
}

static inline f32 absf_001C12B0(f32 value) {
    return value >= 0.0f ? value : -value;
}

static inline f32 max_001C12B0(f32 a, f32 b) {
    return a > b ? a : b;
}

static inline f32 clamp_001C12B0(f32 value, f32 minimum, f32 maximum) {
    return max_001C12B0(value, minimum) < maximum ?
           max_001C12B0(value, minimum) : maximum;
}

void SzDuel_Act3DView(void) {
    extern u32 SzPad_GetPressInfo();
    extern s32 SzModel_GetModelNo();
    extern Vec4_001C12B0 D_00291440;
    extern f32 D_00291430[];
    f32 yaw = 0.0f;
    f32 pitch = 0.0f;
    f32 distance = 0.0f;
    Vec4_001C12B0 camera;

    SzModel_ReqSE(2, 0x1D);
    if (SzPad_Check(0, 0, 0x20)) {
        SzSound_PlaySE(0, 5);
        SzGame_Pop();
    }
    if (SzPad_IsAnalog(0)) {
        s32 x = (u8)SzPad_GetAnalogInfo(0, 3) - 128;
        s32 y = (u8)SzPad_GetAnalogInfo(0, 2) - 128;
        s32 z = (u8)SzPad_GetAnalogInfo(0, 1) - 128;
        SzPad_GetAnalogInfo(0, 0);
        x = deadzone_001C12B0(x);
        y = deadzone_001C12B0(y);
        z = deadzone_001C12B0(z);
        yaw -= 0.024543693f * (f32)y / 40.0f;
        pitch -= 0.024543693f * (f32)x / 40.0f;
        distance += 2.0f * (f32)z / 40.0f;
    }
    if (SzPad_IsPress(0)) {
        yaw += 0.024543693f * (f32)SzPad_GetPressInfo(0, 1) / 64.0f;
        yaw -= 0.024543693f * (f32)SzPad_GetPressInfo(0, 0) / 64.0f;
        pitch += 0.024543693f * (f32)SzPad_GetPressInfo(0, 2) / 64.0f;
        pitch -= 0.024543693f * (f32)SzPad_GetPressInfo(0, 3) / 64.0f;
        distance += 2.0f * (f32)SzPad_GetPressInfo(0, 8) / 64.0f;
        distance -= 2.0f * (f32)SzPad_GetPressInfo(0, 9) / 64.0f;
    } else {
        if (SzPad_Check(0, 1, 0x8000)) {
            yaw += 0.024543693f;
        }
        if (SzPad_Check(0, 1, 0x2000)) {
            yaw -= 0.024543693f;
        }
        if (SzPad_Check(0, 1, 0x1000)) {
            pitch += 0.024543693f;
        }
        if (SzPad_Check(0, 1, 0x4000)) {
            pitch -= 0.024543693f;
        }
        if (SzPad_Check(0, 1, 4)) {
            distance += 2.0f;
        }
        if (SzPad_Check(0, 1, 8)) {
            distance -= 2.0f;
        }
    }
    if (!(absf_001C12B0(yaw) <= 0.000001f &&
          absf_001C12B0(pitch) <= 0.000001f &&
          absf_001C12B0(distance) <= 0.000001f)) {
        f32 minimum;
        camera = *(Vec4_001C12B0 *)SzView_GetLook(0);
        minimum = (f32)SzDuel_GetCamDist(SzDuel_Xax2New(SzModel_GetModelNo(0x1D)));
        camera.x = clamp_001C12B0(camera.x + distance, minimum, 300.0f);
        camera.y = func_001A6C30(6.2831855f + (camera.y + yaw), 6.2831855f);
        camera.z = clamp_001C12B0(camera.z + pitch, -0.3926991f, 1.3744469f);
        SzView_SetLookSP(0, (f32 *)&camera);
        D_00291440 = *(Vec4_001C12B0 *)SzView_GetSP(0);
        SzView_SetPointLight(0, 4, (s32)D_00291430);
    }
}

void SzDuel_Draw3DView(void) {
    RhBase_SetVifPacketArea(SzDuel_Draw3DView_Pipe(RhBase_GetVifPacketArea()));
}

struct DotrView3dVector {
    float x;
    float y;
    float z;
    float w;
};
struct DotrView3dAngles {
    int x;
    int y;
    int z;
    int w;
};
struct DotrView3dLight {
    float unknown_00[4];
    struct DotrView3dVector position;
    float unknown_20;
    float unknown_24;
    float unknown_28[2];
};
struct DotrView3dControl {
    unsigned char unknown_0000[0xd35];
    unsigned char unknown_d35;
};
extern struct DotrView3dVector D_00291460;
extern struct DotrView3dAngles D_00291470;
extern struct DotrView3dVector D_00291480;
extern struct DotrView3dLight D_00291430;
extern struct DotrView3dControl D_00317490_b;
extern void *func_001FAF60_b(int index);
extern void *func_001F9D30_b(int index);
extern int func_001F2920_b(int index);
extern void *func_001F9AD0_b(int index);
extern int func_001F9940_b(int index, int position, struct DotrView3dLight *in);
extern int func_001EFA80_b(int cursor, int index, struct DotrView3dVector *c,
                                        void *d, int e, int f, int g);
extern int func_001C1FE0_b(int a, struct DotrView3dVector *centre, int alpha,
                                      float dx, float dz);
extern int func_001EE4B0_b(int cursor, int index, int c, void *d, int e, int f, int g);
#define VIEW3D_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define VIEW3D_MIN(a, b) (((a) < (b)) ? (a) : (b))

int SzDuel_Draw3DView_Pipe(int cursor)
{
    struct DotrView3dControl *control = &D_00317490_b;
    struct DotrView3dVector pos = D_00291460;
    struct DotrView3dAngles rot = D_00291470;
    struct DotrView3dVector centre;
    struct DotrView3dVector cp;
    struct DotrView3dVector look;
    float dist;
    int i;
    int j;

    if (SzModel_IsModelDisp(29)) {
        func_001FAF60_b(0);
        SzModel_GetRadius(29);
        if (control->unknown_d35 != 0) {
            if (SzModel_GetCenter(29, &centre)) {
                cp = *(struct DotrView3dVector *)func_001F9D30_b(0);
                cp.y += VIEW3D_MIN(VIEW3D_MAX(centre.y - cp.y, -1.0f), 1.0f);
                SzView_SetCP(0, &cp);
            }
        } else {
            if (SzModel_GetCenterOfs(29, &centre)) {
                dist = (float)SzDuel_GetCamDist(SzDuel_Xax2New(func_001F2920_b(29)));
                look = D_00291480;
                centre.x *= -1.0f;
                centre.y *= -1.0f;
                centre.z *= -1.0f;
                look.x = dist;
                SzModel_SetPos(29, &centre);
                SzView_SetLookSP(0, &look);
                D_00291430.unknown_20 = dist;
                D_00291430.unknown_24 = 2.0f * dist;
                D_00291430.position = *(struct DotrView3dVector *)func_001F9AD0_b(0);
                func_001F9940_b(0, 4, &D_00291430);
            }
            control->unknown_d35++;
        }
    }
    for (i = 5; i >= -5; i--) {
        pos.y = (float)(i * 500);
        cursor = func_001EFA80_b(cursor, 38, &pos, 0, 0, 0, 0);
    }
    for (i = 5; i >= -5; i--) {
        pos.y = (float)(i * 500);
        for (j = 0; j < 12; j++) {
            rot.y = j * 0x10000 / 12;
            cursor = func_001EFA80_b(cursor, 36, &pos, &rot, 0, 0, 0);
        }
    }
    pos.y = 0.0f;
    for (j = 0; j < 6; j++) {
        rot.y = j * 0x10000 / 6;
        cursor = func_001EFA80_b(cursor, 37, &pos, &rot, 0, 0, 0);
    }
    for (i = 0; i < 5; i++) {
        pos.y = (float)(2500 - i * 100);
        cursor = func_001C1FE0_b(cursor, &pos, 16, 1500.0f, 1500.0f);
    }
    for (i = 0; i < 5; i++) {
        pos.y = (float)(-2500 + i * 100);
        cursor = func_001C1FE0_b(cursor, &pos, 16, 1500.0f, 1500.0f);
    }
    pos.y = -500.0f;
    cursor = func_001EFA80_b(cursor, 34, &pos, 0, 0, 0, 0);
    cursor = func_001EFA80_b(cursor, 35, &pos, 0, 0, 0, 0);
    return func_001EE4B0_b(cursor, 29, 0, 0, 0, 0, 0);
}
#undef VIEW3D_MAX
#undef VIEW3D_MIN

typedef struct Vertex_001C1FE0 {
    f32 x, y, z;
    u8 pad0C[0xC];
    u8 r, g, b, a;
    f32 q;
    u8 pad20[0x10];
} Vertex_001C1FE0;

typedef struct Prim_001C1FE0 {
    u16 flags;
    u16 kind;
    u32 pad;
    u64 value;
    u64 alpha;
    u64 tex0;
    u64 tex1;
    u64 clamp;
} Prim_001C1FE0;

static inline void initPrim_001C1FE0(s32 kind, void *prim) {
    ((Prim_001C1FE0 *)prim)->kind = kind;
    ((Prim_001C1FE0 *)prim)->flags = 0;
    ((Prim_001C1FE0 *)prim)->value = 0;
    ((Prim_001C1FE0 *)prim)->pad = 0;
}

void lSzDuel_DrawFadeBoard_Pipe(s32 arg0, f32 *position, u8 alpha, f32 width, f32 height) {
    extern s32 ExSortNode_Pipe(s32, void *, s32, s32, s32, s32);
    void *scratchpad = (void *)0x70000000;
    Vertex_001C1FE0 *vertices = (Vertex_001C1FE0 *)((u8 *)scratchpad + 0x2000);
    s32 count;
    Prim_001C1FE0 prim;

    vertices[0].r = 0x80;
    vertices[0].g = 0x80;
    vertices[0].b = 0x80;
    vertices[0].a = alpha;
    vertices[0].q = 1.0f;
    vertices[0].x = position[0] - width;
    vertices[0].y = position[1];
    vertices[0].z = position[2] - height;
    vertices[1].x = position[0] + width;
    vertices[1].y = position[1];
    vertices[1].z = position[2] - height;
    vertices[2].x = position[0] + width;
    vertices[2].y = position[1];
    vertices[2].z = position[2] + height;
    vertices[3].x = position[0] - width;
    vertices[3].y = position[1];
    vertices[3].z = position[2] + height;
    vertices[4].x = position[0] - width;
    vertices[4].y = position[1];
    vertices[4].z = position[2] - height;
    count = Ex3d_NodeL2V(0, 5, vertices, 0xAA, scratchpad, 0, 0);
    Ex3d_NodeV2S(NULL, count, vertices);
    initPrim_001C1FE0(5, &prim);
    ExAssignAlpha(&prim, ExGetAlphaVal(2));
    ExSortNode_Pipe(arg0, &prim, count, (s32)vertices, 0, 0);
}

extern u8 D_002CCB48[];
extern u8 D_002CD1F4[];
extern s32 D_003180E8;

#pragma opt_propagation off

void SzDuel_InitTrade(void) {
    u8 *state;
    s16 *var_s1;
    s16 *var_s2;
    s8 *var_s3;
    s8 *var_s4;
    s32 var_a0;
    s32 result;
    u8 *var_v0;

    state = D_00317490.b;
    var_s1 = (s16 *)0x01ED0000;
    var_s2 = (s16 *)0x01ED06AC;
    var_s3 = (s8 *)0x01ED0D58;
    var_s4 = (s8 *)0x01ED10AE;
    result = SzData_GetOption(0, 0);
    D_003180E8 = 0xFFFFF8;
    if (result != 0) {
        var_v0 = D_002CD1F4;
    } else {
        var_v0 = D_002CCB48;
    }
    *(u8 **)(state + 0x6D4) = var_v0;
    *(s32 *)(state + 0x6D8) = 0x01ED0000;
    *(s32 *)(state + 0x6DC) = 0x01ED06AC;
    *(s32 *)(state + 0x6E0) = 0x01ED0D58;
    *(s32 *)(state + 0x6E4) = (s32)var_s4;
    var_a0 = 0;
    do {
        var_a0 += 1;
        *var_s1 = 0x3E7;
        *var_s3 = 0;
        var_s1 += 1;
        var_s3 += 1;
    } while (var_a0 < 0x356);
    var_a0 = 0;
    do {
        var_a0 += 1;
        *var_s2 = 0x3E7;
        *var_s4 = 0;
        var_s2 += 1;
        var_s4 += 1;
    } while (var_a0 < 0x356);
    *(s16 *)(state + 0xC92) = 0;
    *(s16 *)(state + 0xC94) = 0;
    *(s8 *)(state + 0xCB6) = 0;
    *(s8 *)(state + 0xCB7) = 4;
    *(s8 *)(state + 0xCB8) = 0xA;
    *(s8 *)(state + 0xCB9) = 0;
    *(s8 *)(state + 0xCBA) = 4;
    *(s8 *)(state + 0xCBB) = 0xA;
    *(s8 *)(state + 0xCBE) = 1;
    *(s8 *)(state + 0xCBF) = 1;
    *(s8 *)(state + 0xCC0) = 0;
    *(s8 *)(state + 0xCC1) = 0;
    *(s8 *)(state + 0xD5E) = 0;
    *(s8 *)(state + 0xD5F) = 0;
    *(s16 *)(state + 0xC8A) = 0;
    *(s16 *)(state + 0xC8E) = 0;
    *(s16 *)(state + 0xC96) = 0;
    *(s16 *)(state + 0xC98) = 0;
    *(s8 *)(state + 0xCBC) = 0;
    *(s8 *)(state + 0xCBD) = 0;
    lSzDuel_SetupTrade(0);
    lSzDuel_SetupTrade(1);
}
#pragma opt_propagation reset

void lSzDuel_SetupTrade(s32 arg0) {
    extern s32 SzData_GetBagCount();
    u8 *base;
    s16 *var_s0;
    u8 *var_a0;
    u8 *var_a1;
    s32 var_a0_2;
    s32 var_a1_2;
    s32 var_s1;
    s32 var_v0;
    u16 temp_a0;
    u16 *var_s2;
    u16 *var_s3;
    u8 *var_s4;
    u8 temp_v1;

    base = D_00317490.b;
    if (arg0 != 0) {
        var_s2 = (u16 *)(base + 0xC8E);
    } else {
        var_s2 = (u16 *)(base + 0xC8A);
    }
    if (arg0 != 0) {
        var_s3 = (u16 *)(base + 0xC90);
    } else {
        var_s3 = (u16 *)(base + 0xC8C);
    }
    if (arg0 != 0) {
        var_s0 = *(s16 **)(base + 0x6DC);
    } else {
        var_s0 = *(s16 **)(base + 0x6D8);
    }
    if (arg0 != 0) {
        var_a0 = *(u8 **)(base + 0x6E4);
    } else {
        var_a0 = *(u8 **)(base + 0x6E0);
    }
    if (arg0 != 0) {
        var_a1 = *(u8 **)(base + 0x6E0);
    } else {
        var_a1 = *(u8 **)(base + 0x6E4);
    }
    if (arg0 != 0) {
        var_s4 = base + 0xD5F;
    } else {
        var_s4 = base + 0xD5E;
    }
    *var_s3 = 0;
    temp_v1 = *(u8 *)(arg0 + (s32)base + 0xCC0);
    if (temp_v1 != 2) {
        switch (temp_v1) {
            case 0:
                var_s1 = 0;
                do {
                    if (SzData_GetBagCount(arg0, var_s1, 3) > 0) {
                        *var_s0 = var_s1;
                        *var_s3 = (u16)(*var_s3 + 1);
                    } else {
                        *var_s0 = 0x3E7;
                    }
                    var_s1 += 1;
                    var_s0 += 1;
                } while (var_s1 < 0x356);
                break;
            case 1:
                var_a1_2 = 0;
                do {
                    if ((s32)*var_a0 > 0) {
                        *var_s0 = var_a1_2;
                        *var_s3 = (u16)(*var_s3 + 1);
                    } else {
                        *var_s0 = 0x3E7;
                    }
                    var_a1_2 += 1;
                    var_s0 += 1;
                    var_a0 += 1;
                } while (var_a1_2 < 0x356);
                break;
        }
    } else {
        var_a0_2 = 0;
        do {
            if ((s32)*var_a1 > 0) {
                *var_s0 = var_a0_2;
                *var_s3 = (u16)(*var_s3 + 1);
            } else {
                *var_s0 = 0x3E7;
            }
            var_a0_2 += 1;
            var_s0 += 1;
            var_a1 += 1;
        } while (var_a0_2 < 0x356);
    }
    temp_a0 = *var_s3;
    if ((s32)temp_a0 < (*var_s2 + *var_s4)) {
        var_v0 = temp_a0 - 5;
        *var_s2 = (u16)(var_v0 > 0 ? var_v0 : 0);
    }
    lSzDuel_SortTrade(arg0);
}
