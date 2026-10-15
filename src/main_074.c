#include "common.h"

s32 Ta_GetSacrificeUnit(s32 *arg0, s32 arg1) {
    s32 ids[6];
    s32 scores[6];
    s32 key[3];
    s32 i;
    s32 j;
    s32 count;
    s32 code;
    s32 *p;
    s32 best;
    s32 value;
    s32 k;
    s32 lowest;

    key[2] = -1;
    key[1] = -1;
    key[0] = -1;
    for (i = 0; i < 6; i++) {
        scores[i] = -1;
        ids[i] = -1;
    }
    for (i = 0; i < 6; i++) {
        switch (i) {
        case 0:
            key[0] = arg0[0];
            key[1] = arg0[1];
            key[2] = arg0[2];
            break;
        case 1:
            key[0] = arg0[0];
            key[1] = arg0[2];
            key[2] = arg0[1];
            break;
        case 2:
            key[0] = arg0[1];
            key[1] = arg0[0];
            key[2] = arg0[2];
            break;
        case 3:
            key[0] = arg0[1];
            key[1] = arg0[2];
            key[2] = arg0[0];
            break;
        case 4:
            key[0] = arg0[2];
            key[1] = arg0[0];
            key[2] = arg0[1];
            break;
        case 5:
            key[0] = arg0[2];
            key[1] = arg0[1];
            key[2] = arg0[0];
            break;
        default:
            key[0] = arg0[0];
            key[1] = arg0[1];
            key[2] = arg0[2];
            break;
        }
        if ((ids[i] = Ta_GetScrificeOrder(key, arg1)) >= 0) {
            scores[i] = 0;
            count = Ta_GetUnitNumFrom22bitFlagList(ids[i]);
            if (count == 3) {
                for (j = 0; j < count; j++) {
                    code = Ta_GetUnitOwnerIDFromLstCount(ids[i], j);
                    scores[i] += Ta_GetAPPlusDP(code >> 8, code & 0xFF);
                }
            } else {
                scores[i] = -1;
            }
        }
    }
    best = 0xFF;
    lowest = 0xFFFF;
    for (k = 5, p = &scores[5]; k >= 0; k--) {
        value = *p;
        if (value >= 0 && value <= lowest) {
            lowest = value;
            best = k;
        }
        p--;
    }
    if (best == 0xFF) {
        return -1;
    }
    return ids[best];
}

s32 Ta_GetScrificeOrder(void *arg0, s32 arg1) {
    s32 result;
    s32 *src;
    s32 selections[3];
    s32 *selection;
    u32 selector;
    s32 i;
    s32 j;
    s32 mask;
    s32 card;
    s32 count;

    selection = selections;
    selector = arg1;
    src = arg0;
    i = 0;
    result = 0;
    do {
        if ((mask = SearchUnitByRange(0, 0, selector, 1, *src, 14)) > 0) {
            for (j = 0; j < Ta_GetUnitNumFrom22bitFlagList(result); j++) {
                card = Ta_GetUnitOwnerIDFromLstCount(result, j);
                if (Ta_GetAgreeOwnerIDon22bitFlagLst(card, mask) != 0) {
                    mask = ConvUnitIDtoFlagList_OFF(mask, card >> 8, card & 0xFF);
                }
            }
            count = Ta_GetMinimumParamUnitFromFlagList(mask);
            if (count > 0) {
                if ((*selection = Ta_GetMinimumOrderUnitFromFlagList(count)) >= 0) {
                    result = ConvUnitIDtoFlagList(result, *selection >> 8, *selection & 0xFF);
                }
            }
        }
        i++;
        src++;
        selection++;
    } while (i < 3);
    if (Ta_GetUnitNumFrom22bitFlagList(result) != 3) {
        return -1;
    }
    return result;
}

void Ta_GetCeremSacrifice(s32 *arg0, s32 arg1) {
    arg0[2] = -1;
    arg0[1] = -1;
    arg0[0] = -1;
    switch (arg1) {
    case 0xBD:
        arg0[0] = 0x07D00039;
        arg0[1] = 0x07D00039;
        arg0[2] = 0x07D00039;
        break;
    case 0xD:
        arg0[0] = 4;
        arg0[1] = 0;
        arg0[2] = 0x11;
        break;
    case 0x91:
        arg0[0] = 0x63001C;
        arg0[1] = 0x023D001C;
        arg0[2] = 0x0216001C;
        break;
    case 0x8F:
        arg0[0] = 0x9B001C;
        arg0[1] = 0x05DC0025;
        arg0[2] = 0x05DC0025;
        break;
    case 0x151:
        arg0[0] = 0x012C001C;
        arg0[1] = 7;
        arg0[2] = 7;
        break;
    case 0xF8:
        arg0[0] = 0xF9001C;
        arg0[1] = 5;
        arg0[2] = 5;
        break;
    case 0x152:
        arg0[0] = 0x0149001C;
        arg0[1] = 0x0121001C;
        arg0[2] = 7;
        break;
    case 0x2:
        arg0[0] = 0x1C;
        arg0[1] = 0x1C;
        arg0[2] = 0x1C;
        break;
    case 0xC3:
        arg0[0] = 0x0236001C;
        arg0[1] = 6;
        arg0[2] = 3;
        break;
    case 0x93:
        arg0[0] = 0xD2001C;
        arg0[1] = 0x0150001C;
        arg0[2] = 0x0295001C;
        break;
    case 0xDC:
        arg0[0] = 0x0279001C;
        arg0[1] = 4;
        arg0[2] = 4;
        break;
    case 0x87:
        arg0[0] = 0x23001C;
        arg0[1] = 3;
        arg0[2] = 3;
        break;
    case 0xA:
        arg0[0] = 0x5001C;
        arg0[1] = 0x0125001C;
        arg0[2] = 0x6001C;
        break;
    case 0xB:
        arg0[0] = 0x8001C;
        arg0[1] = 3;
        arg0[2] = 6;
        break;
    case 0x254:
        arg0[0] = 0x0248001C;
        arg0[1] = 0x10;
        arg0[2] = 0x10;
        break;
    case 0x4D:
        arg0[0] = 0x0131001C;
        arg0[1] = 1;
        arg0[2] = 1;
        break;
    case 0x160:
        arg0[0] = 0x014A001C;
        arg0[1] = 0x03E80025;
        arg0[2] = 0x03E80025;
        break;
    case 0x161:
        arg0[0] = 0xAD001C;
        arg0[1] = 0xE;
        arg0[2] = 0xE;
        break;
    case 0x1A6:
        arg0[0] = 0x018E001C;
        arg0[1] = 9;
        arg0[2] = 9;
        break;
    case 0x94:
        arg0[0] = 0x92001C;
        arg0[1] = 3;
        arg0[2] = 3;
        break;
    case 0x4C:
        arg0[0] = 0x029B001C;
        arg0[1] = 0xCC001C;
        arg0[2] = 0x4F001C;
        break;
    case 0x80:
        arg0[0] = 2;
        arg0[1] = 0xE;
        arg0[2] = 9;
        break;
    case 0x1D8:
        arg0[0] = 0x0214001C;
        arg0[1] = 0xC;
        arg0[2] = 0xC;
        break;
    case 0x4E:
        arg0[0] = 0x3C001C;
        arg0[1] = 0x05DC0025;
        arg0[2] = 0x05DC0025;
        break;
    default:
        arg0[0] = -1;
        arg0[1] = -1;
        arg0[2] = -1;
        break;
    }
}

s32 Ta_Manage_Effect(u32 *arg0, u16 *arg1, s32 arg2) {
    extern void SzDuel_SetUnitStatus(s32, s32, s32, s32);
    extern s32 Ta_Eff_002();
    extern s32 Ta_Eff_009();
    extern s32 Ta_Eff_032();
    extern s32 Ta_Eff_035();
    extern s32 Ta_Eff_017_MEGUMI();
    extern s32 Ta_Eff_064();
    extern s32 Ta_Eff_044();
    extern s32 Ta_Eff_046();
    extern s32 Ta_Eff_058();
    extern s32 Ta_Eff_109();
    extern s32 Ta_Eff_066();
    extern s32 Ta_Eff_BTL_000();
    extern s32 Ta_Eff_BTL_001();
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;

    if ((arg0 == NULL) || (arg1 == NULL)) {
        return 0;
    }
    temp_v0 = *arg0 & 0x7FFF;
    var_s1 = 0;
    switch (temp_v0) {
    case 0x0:
        var_s1 = Ta_Eff_000(arg0, arg1, arg2);
        break;
    case 0x1:
        var_s1 = Ta_Eff_001(arg0, arg1, arg2);
        break;
    case 0x2:
        var_s1 = Ta_Eff_002(arg0, arg1, arg2);
        break;
    case 0x3:
        var_s1 = Ta_Eff_003B(arg0, arg1, arg2);
        break;
    case 0x4:
        var_s1 = Ta_Eff_004(arg0, arg1, arg2);
        break;
    case 0x5:
        var_s1 = Ta_Eff_005(arg0, arg1, arg2);
        break;
    case 0x6:
        var_s1 = Ta_Eff_006(arg0, arg1, arg2);
        break;
    case 0x7:
        var_s1 = Ta_Eff_007(arg0, arg1, arg2);
        break;
    case 0x8:
        var_s1 = Ta_Eff_008(arg0, arg1, arg2);
        break;
    case 0x9:
        var_s1 = Ta_Eff_009(arg0, arg1, arg2);
        break;
    case 0xC:
        var_s1 = Ta_Eff_012(arg0, arg1, arg2);
        break;
    case 0xD:
        var_s1 = Ta_Eff_013(arg0, arg1, arg2);
        break;
    case 0xE:
        var_s1 = Ta_Eff_014(arg0, arg1, arg2);
        break;
    case 0xF:
        var_s1 = Ta_Eff_015(arg0, arg1, arg2);
        break;
    case 0x10:
        var_s1 = Ta_Eff_016(arg0, arg1, arg2);
        break;
    case 0x11:
        var_s1 = Ta_Eff_017_A(arg0, arg1, arg2);
        break;
    case 0x12:
        var_s1 = Ta_Eff_018(arg0, arg1, arg2);
        break;
    case 0x13:
        var_s1 = Ta_Eff_019(arg0, arg1, arg2);
        break;
    case 0x14:
        var_s1 = Ta_Eff_020((s32) arg0, arg1, arg2);
        break;
    case 0x15:
        var_s1 = Ta_Eff_021(arg0, arg1, arg2);
        break;
    case 0x17:
        var_s1 = Ta_Eff_023(arg0, arg1, arg2);
        break;
    case 0x19:
        var_s1 = Ta_Eff_025(arg0, arg1, arg2);
        break;
    case 0x1A:
        var_s1 = Ta_Eff_026(arg0, arg1, arg2);
        break;
    case 0x1C:
        var_s1 = Ta_Eff_028(arg0, arg1, arg2);
        break;
    case 0x1D:
        var_s1 = Ta_Eff_029(arg0, arg1, arg2);
        break;
    case 0x5B:
        var_s1 = Ta_Eff_029_CNG(arg0, arg1, arg2);
        break;
    case 0x1E:
        var_s1 = Ta_Eff_030(arg0, arg1, arg2);
        break;
    case 0x1F:
        var_s1 = Ta_Eff_031(arg0, arg1, arg2);
        break;
    case 0x20:
        var_s1 = Ta_Eff_032(arg0, arg1, arg2);
        break;
    case 0x21:
        var_s1 = Ta_Eff_033(arg0, arg1, arg2);
        break;
    case 0x22:
        var_s1 = Ta_Eff_034(arg0, arg1, arg2);
        break;
    case 0x23:
        var_s1 = Ta_Eff_035(arg0, arg1, arg2);
        break;
    case 0x5A:
        var_s1 = Ta_Eff_017_MEGUMI(arg0, arg1, arg2);
        break;
    case 0x5C:
        var_s1 = Ta_Eff_006_WIND(arg0, arg1, arg2);
        break;
    case 0x5D:
        var_s1 = Ta_Eff_BTL_000(arg0, arg1, arg2);
        break;
    case 0x24:
        var_s1 = Ta_Eff_036(arg0, arg1, arg2);
        break;
    case 0x25:
        var_s1 = Ta_Eff_037(arg0, arg1, arg2);
        break;
    case 0x5E:
        var_s1 = Ta_Eff_BTL_001(arg0, arg1, arg2);
        break;
    case 0x5F:
        var_s1 = Ta_Eff_BTL_002(arg0, arg1, arg2);
        break;
    case 0x2B:
        var_s1 = Ta_Eff_100(arg0, arg1, arg2);
        break;
    case 0x2C:
        var_s1 = Ta_Eff_044(arg0, arg1, arg2);
        break;
    case 0x2D:
        var_s1 = Ta_Eff_045(arg0, arg1, arg2);
        break;
    case 0x2E:
        var_s1 = Ta_Eff_046(arg0, arg1, arg2);
        break;
    case 0x33:
        var_s1 = Ta_Eff_051(arg0, arg1, arg2);
        break;
    case 0x36:
        var_s1 = Ta_Eff_054(arg0, arg1, arg2);
        break;
    case 0x38:
        var_s1 = Ta_Eff_056(arg0, arg1, arg2);
        break;
    case 0x39:
        var_s1 = Ta_Eff_057(arg0, arg1, arg2);
        break;
    case 0x3A:
        var_s1 = Ta_Eff_058(arg0, arg1, arg2);
        break;
    case 0x3B:
        var_s1 = Ta_Eff_059(arg0, arg1, arg2);
        break;
    case 0x3C:
        var_s1 = Ta_Eff_060(arg0, arg1, arg2);
        break;
    case 0x3F:
        var_s1 = Ta_Eff_063(arg0, arg1, arg2);
        break;
    case 0x40:
        var_s1 = Ta_Eff_064(arg0, arg1, arg2);
        break;
    case 0x41:
        var_s1 = Ta_Eff_065(arg0, arg1, arg2);
        break;
    case 0x42:
        var_s1 = Ta_Eff_066(arg0, arg1, arg2);
        break;
    case 0x43:
        var_s1 = Ta_Eff_067(arg0, arg1, arg2);
        break;
    case 0x46:
        var_s1 = Ta_Eff_070(arg0, arg1, arg2);
        break;
    case 0x47:
        var_s1 = Ta_Eff_071(arg0, arg1, arg2);
        break;
    case 0x48:
        var_s1 = Ta_Eff_072(arg0, arg1, arg2);
        break;
    case 0x64:
        var_s1 = Ta_Eff_100(arg0, arg1, arg2);
        break;
    case 0x65:
        var_s1 = Ta_Eff_101(arg0, arg1, arg2);
        break;
    case 0x66:
        var_s1 = Ta_Eff_102(arg0, arg1, arg2);
        break;
    case 0x6D:
        var_s1 = Ta_Eff_109(arg0, arg1, arg2);
        break;
    case 0x70:
        var_s1 = Ta_Eff_112(arg0, arg1, arg2);
        break;
    case 0x71:
        var_s1 = Ta_Eff_113(arg0, arg1, arg2);
        break;
    case 0x72:
        var_s1 = Ta_Eff_114(arg0, arg1, arg2);
        break;
    case 0x96:
        var_s1 = Ta_Eff_Hand_Dest(arg0, arg1, arg2);
        break;
    case 0xFF:
        var_s1 = Ta_Eff_ETC(arg0, arg1, arg2);
        break;
    case 0xFE:
        var_s1 = Ta_Eff_WAIT(arg0, arg1, arg2);
        break;
    case 0x3E7:
        var_s1 = 0;
        break;
    default:
        var_s1 = 0;
        break;
    }
    if (var_s1 == 0) {
        var_s0 = 1;
        do {
            if (SzDuel_Kind2Type(SzDuel_GetUnitKind(0, var_s0) >> 5) == 2) {
                if (SzDuel_GetUnitStatus(0, var_s0, 4) != 0) {
                    SzEffect_SetBusyFlag2(var_s0, 0);
                    SzDuel_SetUnitStatus(0, var_s0, 0, 1);
                }
            }
            if ((SzDuel_Kind2Type(SzDuel_GetUnitKind(1, var_s0) >> 5) == 2) && (SzDuel_GetUnitStatus(1, var_s0, 4) != 0)) {
                SzDuel_SetUnitStatus(1, var_s0, 0, 1);
                SzEffect_SetBusyFlag2(var_s0 | 0x100, 0);
            }
            var_s0 += 1;
        } while (var_s0 < 0xB);
    }
    return var_s1;
}

void InitEffectTemp(void *arg0) {
    f32 *temp_v0_2;
    f32 *temp_s0;
    s32 var_a0;
    u8 *var_a1;

    *(s16 *)((u8 *)arg0 + 0) = 0;
    *(s16 *)((u8 *)arg0 + 2) = 0;
    *(s16 *)((u8 *)arg0 + 4) = 0;
    *(s8 *)((u8 *)arg0 + 0xD4) = 0;
    TaEffect_ClearEffectTemp(arg0);
    var_a0 = 0;
    var_a1 = arg0;
    do {
        *(u8 *)((u32)arg0 + var_a0 + 6) = 0xFF;
        *(s32 *)(var_a1 + 0x20) = 0;
        var_a0 += 1;
        var_a1 += 4;
    } while (var_a0 < 0x18);
    temp_s0 = (f32 *)SzView_GetCP(0);
    temp_v0_2 = SzView_GetLook(0);
    *(s32 *)((u8 *)arg0 + 0xD0) = 0;
    *(s32 *)((u8 *)arg0 + 0xCC) = 0;
    *(s8 *)((u8 *)arg0 + 0x100) = 0;
    *(s16 *)((u8 *)arg0 + 0x102) = 0;
    *(f32 *)((u8 *)arg0 + 0xE0) = temp_s0[0];
    *(f32 *)((u8 *)arg0 + 0xE4) = temp_s0[1];
    *(f32 *)((u8 *)arg0 + 0xE8) = temp_s0[2];
    *(f32 *)((u8 *)arg0 + 0xEC) = temp_s0[3];
    *(f32 *)((u8 *)arg0 + 0xF0) = temp_v0_2[0];
    *(f32 *)((u8 *)arg0 + 0xF4) = temp_v0_2[1];
    *(f32 *)((u8 *)arg0 + 0xF8) = temp_v0_2[2];
    *(f32 *)((u8 *)arg0 + 0xFC) = temp_v0_2[3];
}

typedef struct Request_00255A30 {
    s32 id;
    u32 flags;
    u32 value;
    u32 kind;
} Request_00255A30;


s32 Ta_Do_Effect(void *arg0, void *arg1) {
    extern s32 SzEffect_Entry(s32, s32, s32, s32, s32);
    Request_00255A30 *req = arg0;
    s32 ret;

    switch (TaEffect_IsLoadModule2(arg1, req->id)) {
    case 0:
        return -2;
    case -1:
        return -3;
    default:
        ret = SzEffect_Entry(0, req->id, req->kind, req->value, req->flags);
        if (ret < 0) {
            return -1;
        }
        return ret;
    }
}

typedef struct State_00255AC0 {
    u8 padding[0x80];
    u8 flag : 1;
    u8 count : 5;
    u8 flags : 2;
    s16 entries[32];
} State_00255AC0;

s32 TaEffect_LoadModule(void *arg0, s16 arg1) {
    extern s32 SzEffect_LoadModule(s32, s16, s32);
    State_00255AC0 *state = arg0;

    if (SzEffect_LoadModule(0, arg1, 0) != 0) {
        state->entries[state->count] = arg1;
        state->count++;
        return 1;
    }
    return -1;
}

typedef struct {
    s8 ready : 1;
    u8 count : 5;
    u8 reserved : 2;
} Flags_00255B50;

typedef struct {
    u8 pad[0x80];
    Flags_00255B50 flags;
    u8 pad81;
    u16 ids[24];
    s8 types[24];
} Data_00255B50;


s32 TaEffect_IsLoadModule(void *arg0) {
    s32 i;
    Data_00255B50 *cursor;
    Data_00255B50 *data;
    u16 id;
    u8 *entry;
    s32 type;

    data = arg0;
    i = 0;
    cursor = data;
    for (; i < data->flags.count; i++) {
        id = cursor->ids[0];
        if (id != 0xFFFF) {
            entry = SzEffect_GetModuleInfo(0, id);
            if (entry != NULL) {
                type = *entry & 7;
                if (type < 2) {
                    if (type == 0) {
                        data->types[i] = 0;
                    } else {
                        return -1;
                    }
                } else {
                    data->types[i] = type;
                }
            }
        }
        cursor = (Data_00255B50 *)((u8 *)cursor + 2);
    }
    data->flags.ready = 1;
    return 1;
}

typedef struct Slots_00255C30 {
    u8 pad[0x82];
    u16 ids[24];
} Slots_00255C30;


s32 TaEffect_IsLoadModule2(void *arg0, s32 arg1) {
    s32 state;
    s32 i;
    u8 *entry;
    Slots_00255C30 *slots = arg0;

    if (arg0 == NULL) {
        return 0;
    }

    for (i = 0; i < 24; i++) {
        if (arg1 == slots->ids[i]) {
            entry = SzEffect_GetModuleInfo(0, slots->ids[i]);
            if (entry != NULL) {
                state = *entry & 7;
                if (state < 2) {
                    return state == 0 ? 0 : -1;
                }
            }
            return 1;
        }
    }
    return 0;
}

typedef struct {
    u8 padding[0x80];
    s8 active : 1;
    u8 count : 5;
    u8 reserved : 2;
    u8 padding81;
    u16 entries[0x18];
    u8 states[0x18];
} State_00255CD0;

void TaEffect_ClearEffectTemp(void *arg0) {
    State_00255CD0 *state = arg0;
    s32 i;

    state->active = 0;
    state->count = 0;
    for (i = 0; i < 0x18; i++) {
        state->entries[i] = 0xFFFF;
        state->states[i] = 0;
    }
}

void Ta_GetStdCompleteView(s32 *arg0) {
    if (SzDuel_GetTurnOwner() == 0) {
        arg0[0] = 0x1F4;
        arg0[1] = 0x3FFF;
        arg0[2] = 0x17FF;
        arg0[3] = 0;
    } else {
        arg0[0] = 0x1F4;
        arg0[1] = 0xBFFF;
        arg0[2] = 0x17FF;
        arg0[3] = 0;
    }
}

typedef struct Config_00255DB0 {
    s32 value;
    s32 flags;
    s32 limit;
    s32 reserved;
} Config_00255DB0;

void Ta_GetStdTopDownView(void *arg0) {
    Config_00255DB0 *config = arg0;

    if (SzDuel_GetTurnOwner() == 0) {
        config->value = 0x1F4;
        config->flags = 0x3FFF;
        config->limit = 0x3800;
        config->reserved = 0;
    } else {
        config->value = 0x2BC;
        config->flags = 0xBFFF;
        config->limit = 0x3800;
        config->reserved = 0;
    }
}

void Ta_GetFlatCompleteView(void *arg0) {
    s32 *values = arg0;

    if (SzDuel_GetTurnOwner() == 0) {
        values[0] = 0x1F4;
        values[1] = 0x2000;
        values[2] = 0x400;
        values[3] = 0;
    } else {
        values[0] = 0x1F4;
        values[1] = 0xA000;
        values[2] = 0x400;
        values[3] = 0;
    }
}

void Ta_GetDestinyView(void *arg0) {
    s32 *values = (s32 *)arg0;

    if (SzDuel_GetTurnOwner() == 0) {
        values[0] = 0x7A;
        values[1] = 0x5000;
        values[2] = -0x1000;
        values[3] = 0;
    } else {
        values[0] = 0x7A;
        values[1] = 0xD000;
        values[2] = -0x1000;
        values[3] = 0;
    }
}

void Ta_GetStdFocusView(void *arg0, s32 arg1) {
    s32 *data = arg0;

    if (SzDuel_GetTurnOwner() == 0) {
        data[0] = arg1;
        data[1] = 0x3FFF;
        data[2] = 0x1000;
        data[3] = 0;
    } else {
        data[0] = arg1;
        data[1] = 0xBFFF;
        data[2] = 0x1000;
        data[3] = 0;
    }
}

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} Block_00255F70;

void Ta_GetStdFocusView2(void *arg0, s32 arg1) {
    if (SzDuel_GetTurnOwner() == 0) {
        ((Block_00255F70 *)arg0)->f0 = arg1;
        ((Block_00255F70 *)arg0)->f4 = 0x4FFF;
        ((Block_00255F70 *)arg0)->f8 = 0x1800;
        ((Block_00255F70 *)arg0)->fC = 0;
    } else {
        ((Block_00255F70 *)arg0)->f0 = arg1;
        ((Block_00255F70 *)arg0)->f4 = 0xCFFF;
        ((Block_00255F70 *)arg0)->f8 = 0x1800;
        ((Block_00255F70 *)arg0)->fC = 0;
    }
}

void Ta_GetTopView(void *arg0) {
    s32 *values = arg0;

    if (SzDuel_GetTurnOwner() == 0) {
        values[0] = 0xFA;
        values[1] = 0x2000;
        values[2] = -0x1800;
        values[3] = 0;
    } else {
        values[0] = 0xFA;
        values[1] = 0xA000;
        values[2] = -0x1800;
        values[3] = 0;
    }
}

void Ta_GetSkyView(void *arg0) {
    s32 *values = arg0;

    if (SzDuel_GetTurnOwner() == 0) {
        values[0] = 0x1F4;
        values[1] = 0x6000;
        values[2] = -0x800;
        values[3] = 0;
    } else {
        values[0] = 0x1F4;
        values[1] = 0xE000;
        values[2] = -0x800;
        values[3] = 0;
    }
}

typedef struct Flags_002560C0 {
    s8 ready : 1;
    s8 unused : 7;
} Flags_002560C0;

typedef struct Context_002560C0 {
    s32 unused;
    s32 mode;
    s32 handle;
    s32 option;
} Context_002560C0;

typedef struct State_002560C0 {
    u16 alpha;
    u16 unused2;
    u16 phase;
    u8 handles[0x1A];
    s32 positions[24];
    Flags_002560C0 flags;
    u8 unused81[0x53];
    u8 count;
    u8 unusedD5[0x2B];
    u8 active;
    u8 unused101;
    u16 timer;
} State_002560C0;


s32 Ta_Eff_000(void *arg0, void *arg1, s32 arg2) {
    extern s32 TaUtil_GetObjSideNum();
    extern s32 SzDuel_SetUnitSpellRest();
    s32 effect[4];
    Context_002560C0 *context = arg0;
    State_002560C0 *state = arg1;
    s32 *effectData = effect;
    s32 i;
    s32 count;
    u8 flags;
    u8 *cursor;
    s32 position;

    effect[0] = 999;
    effect[1] = 0;
    effect[2] = 0;
    effect[3] = 0;
    count = 0;
    flags = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(state);
        Ta_GetUnitNumFrom22bitFlagList(context->handle);
        state->alpha = 0x80;
        Ta_AllUnitFade(context, state, arg2, -1, 1, 1);
        TaEffect_LoadModule(state, 500);
        if (Ta_GetUnitNumFrom22bitFlagList(context->handle) == 1) {
            TaView_ReqFocusCamera(0x20, Ta_GetUnitOwnerIDFromLstCount(context->handle, 0), 100, 180);
        } else {
            TaView_ReqStdCompleteView(0x20);
        }
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (state->alpha > 0x30) {
            state->alpha -= 15;
        } else {
            state->alpha = 0x30;
            if (state->timer++ >= 0x30) {
                if (state->flags.ready == 0) {
                    if (TaEffect_IsLoadModule(state) == 1) {
                        state->flags.ready = 1;
                    }
                } else {
                    if (context->option != 0) {
                        SzDuel_OpenMsgPopup(TaUtil_GetObjSideNum(context->handle), -120, 80, 0x108);
                    } else {
                        SzDuel_OpenMsgPopup(TaUtil_GetObjSideNum(context->handle), -120, 80, 0x118);
                    }
                    Ta_SetEffectDependOnFlagLst(context, state, effectData, 500);
                    state->phase++;
                }
            }
        }
        if (state->alpha < 0x30) {
            state->alpha = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        break;
    case 1:
        for (i = 0; i < state->count; i++) {
            if (SzEffect_IsUse(state->handles[i]) == 0) {
                count++;
            }
        }
        if (count >= state->count) {
            SzDuel_CloseMsgPopup();
            for (count = 0, cursor = (u8 *)state; count < state->count; cursor += 4, count++) {
                if (context->mode == 1) {
                    position = *(s32 *)(cursor + 0x20);
                    SzDuel_SetUnitSpellRest(position >> 8, position & 0xFF, 0xFF);
                } else {
                    position = *(s32 *)(cursor + 0x20);
                    Ta_SetUnitCurseRest(position >> 8, position & 0xFF, (u8)context->option);
                    if (context->option != 0) {
                        position = *(s32 *)(cursor + 0x20);
                        SzDuel_SetUnitStatus(position >> 8, position & 0xFF, 0, 1);
                    }
                }
            }
            state->phase++;
            Ta_AllUnitFade(context, state, arg2, 1, 0, 1);
        }
        break;
    default:
        state->alpha += 15;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 0x80) {
            flags = 1;
        }
        break;
    }

    switch (state->active) {
    case 0:
        if (flags & 1) {
            if (state->timer++ > 0x10) {
                state->active++;
                state->timer = 0;
                TaView_RestoreOriginalView(state, 0x20);
            }
        }
        break;
    default:
        if (state->timer++ > 0x20) {
            flags |= 2;
        }
        break;
    }
    if (flags == 3) {
        if (Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
    }
    return 1;
}

struct jp_6989c {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_68cb4 {
    int fLoad : 1;
    unsigned char bModNum : 5;
    unsigned short wModule[24];
    unsigned char bModCond[24];
};
struct jp_69942 {
    unsigned short wCount_1;
    unsigned short wCount_2;
    unsigned short wLvl;
    unsigned char eID[24];
    int ePos[24];
    struct jp_68cb4 eMod;
    unsigned int fObj;
    unsigned int fObj2;
    unsigned char oNum;
    unsigned char unknown_d5[0xb];
    int camDat[8];
    unsigned char bCamLvl;
    unsigned short wCamTime;
    unsigned char unknown_104[0xc];
    int nTasakiEfc[0x10c];
};
extern int func_00255AC0_b(struct jp_69942 *q, int id);
extern void func_00260740_b(unsigned char who);
extern void func_00260A70_b(struct jp_69942 *Temp, unsigned char b);
extern void func_002614C0_b(unsigned char b, int cell, int value);
#define E002_MIN(a, b) ((a) < (b) ? (a) : (b))
#define E002_MAX(a, b) ((b) < (a) ? (a) : (b))
#define E002_NEAR(x, y) \
    ((E002_MAX(y, (eInfo->dwFrom & 0xFF)) - E002_MIN(y, (eInfo->dwFrom & 0xFF))) \
     + (E002_MAX(x, (eInfo->dwFrom >> 8)) - E002_MIN(x, (eInfo->dwFrom >> 8))) <= eInfo->dwTo)

int Ta_Eff_002(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_6989c * eInfo = eInfo_v;
    struct jp_69942 * Temp = Temp_v;
    int stored;
    int Buf[49];
    int tCount;
    struct jp_6989c eCall;
    struct jp_6989c *pCall = &eCall;
    int j;
    int i;
    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    tCount = 0;
    for (j = 0; j < 49; j++) {
        Buf[j] = -1;
    }
    if (ID >= 0) {
        InitEffectTemp(Temp);
        Ta_AllUnitFade2(eInfo, Temp, ID, -1, 1, 3);
        for (j = 0; j < 7; j++) {
            for (i = 0; i < 7; i++) {
                if (E002_NEAR((unsigned)i, (unsigned)j)) {
                    Buf[tCount] = (i << 8) | j;
                    tCount++;
                }
            }
        }
        if (tCount != 1) {
            func_00260740_b(30);
        } else {
            func_002614C0_b(0, Buf[0], 180);
        }
        if (eInfo->dwPar == 8) {
            func_00255AC0_b(Temp, 503);
        } else {
            func_00255AC0_b(Temp, 502);
        }
        return 1;
    }
    switch (Temp->wLvl) {
    case 0:
        if (Ta_IsFinishFade() == 0 || TaEffect_IsLoadModule(Temp) != 1) {
            return 1;
        }
        for (i = 0; i < 49; i++) {
            Buf[i] = -1;
        }
        switch (eInfo->dwTo) {
        case 16:
            for (i = 0; i < 7; i++) {
                Buf[i] = ((eInfo->dwFrom >> 8) << 8) | i;
                tCount++;
            }
            break;
        default:
            for (j = 0; j < 7; j++) {
                for (i = 0; i < 7; i++) {
                    if (E002_NEAR((unsigned)i, (unsigned)j)) {
                        Buf[tCount] = (i << 8) | j;
                        tCount++;
                    }
                }
            }
            break;
        }
        for (i = 0; i < tCount; i++) {
            switch (eInfo->dwPar) {
            case 8:
                if (i == 0) {
                    pCall->eNO = 503;
                    pCall->dwFrom = 1;
                    pCall->dwTo = Buf[i];
                    pCall->dwPar = eInfo->dwPar;
                } else {
                    pCall->eNO = 503;
                    pCall->dwFrom = 0;
                    pCall->dwTo = Buf[i];
                    pCall->dwPar = eInfo->dwPar;
                }
                break;
            default:
                if (i == 0) {
                    if (SzDuel_GetField(Buf[i] & 0xFF, Buf[i] >> 8) != 8) {
                        pCall->eNO = 502;
                        pCall->dwFrom = 1;
                        pCall->dwTo = Buf[i];
                        pCall->dwPar = eInfo->dwPar;
                    }
                } else {
                    if (SzDuel_GetField(Buf[i] & 0xFF, Buf[i] >> 8) != 8) {
                        pCall->eNO = 502;
                        pCall->dwFrom = 0;
                        pCall->dwTo = Buf[i];
                        pCall->dwPar = eInfo->dwPar;
                    }
                }
                break;
            }
            

            if ((stored = (Temp->eID[i] = Ta_Do_Effect(pCall, Temp))) >= 0) {
                Temp->ePos[Temp->oNum] = ((Buf[i] >> 8) << 8) | (Buf[i] & 0xFF);
                Temp->oNum++;
            }
        }
        Temp->wLvl++;
        return 1;
    case 1:
        for (i = 0; i < Temp->oNum; i++) {
            if (SzEffect_IsUse(Temp->eID[i]) != 0) {
                if (SzEffect_GetStatus(Temp->eID[i]) == 2) {
                    if ((Temp->ePos[i] & 0xFFFF) != 0xFFFF) {
                        Temp->ePos[i] = 0xFFFF;
                    }
                }
            } else {
                tCount++;
            }
        }
        if (tCount >= Temp->oNum) {
            Temp->wLvl++;
            func_00260A70_b(Temp, 30);
            Ta_AllUnitFade2(eInfo, Temp, ID, 1, 1, 3);
        }
        return 1;
    default:
        if (Temp->wCamTime++ > 30) {
            if (Ta_IsFinishFade() == 1) {
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
        break;
    }
    return 1;
}
#undef E002_MIN
#undef E002_MAX
#undef E002_NEAR

typedef struct State_00256AB0 {
    u8 pad0[4];
    u16 state;
    u8 ids[0x1A];
    s32 values[0x2D];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00256AB0;

typedef struct Input_00256AB0 {
    s32 unused;
    s32 first;
    s32 second;
} Input_00256AB0;

typedef struct Request_00256AB0 {
    s32 id;
    s32 flags;
    s32 value;
    s32 kind;
} Request_00256AB0;


s32 Ta_Eff_003B(void *arg0, void *arg1, s32 arg2) {
    Request_00256AB0 request;
    State_00256AB0 *state = arg1;
    Input_00256AB0 *input = arg0;
    {
    Request_00256AB0 *p = &request;
    s32 complete;
    s32 i;
    u8 *walk;

    request.id = 999;
    request.flags = 0;
    request.value = 0;
    request.kind = 0;
    complete = 0;

    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        Ta_AllUnitFade2(arg0, arg1, arg2, -1, 1, 3);
        TaView_ReqStdCompleteView(30);
        TaEffect_LoadModule(arg1, 503);
        TaEffect_LoadModule(arg1, 502);
        return 1;
    } else {
        switch (state->state) {
        case 0: {
            if (state->timer++ > 30) {
              if (TaEffect_IsLoadModule(arg1) == 1) {
                u8 id;
                p->id = 503;
                p->flags = 1;
                p->value = input->second;
                p->kind = 8;
                id = Ta_Do_Effect((s32 *)p, arg1);
                state->ids[state->count] = id;
                if ((s32)id >= 0) {
                    state->values[state->count] = input->second;
                    state->count++;
                }
                p->id = 502;
                p->flags = 0;
                p->value = input->first;
                p->kind = 7;
                id = Ta_Do_Effect((s32 *)p, arg1);
                state->ids[state->count] = id;
                if ((s32)id >= 0) {
                    state->values[state->count] = input->first;
                    state->count++;
                }
                state->state++;
              }
            }
            return 1;
        }
        case 1: {
            i = 0;
            walk = arg1;
            for (; i < state->count; walk += 4, i++) {
                if (SzEffect_IsUse(state->ids[i]) != 0) {
                    if (SzEffect_GetStatus(state->ids[i]) == 2 && *(u16 *)(walk + 0x20) != 0xFFFF) {
                        *(s32 *)(walk + 0x20) = 0xFFFF;
                    }
                } else {
                    complete++;
                }
            }
            if (complete >= state->count) {
                state->state++;
                TaView_RestoreOriginalView(arg1, 30);
                state->timer = 0;
                Ta_AllUnitFade2(arg0, arg1, arg2, 1, 1, 3);
            }
            return 1;
        }
        default: {
            if (state->timer++ > 30 && Ta_IsFinishFade() == 1) {
                return 0;
            }
            break;
        }
        }
    }
    return 1;
    }
}

typedef struct Command_00256D80 {
    s32 type;
    union {
        u32 word;
        struct {
            u16 id;
            u16 options;
        } parts;
        struct {
            u32 id : 16;
            u32 copy : 1;
            u32 remove : 1;
            u32 unused : 14;
        } bits;
    } flags;
    u32 position;
    u32 card;
} Command_00256D80;

typedef struct State_00256D80 {
    s32 unused0;
    u16 step;
    u8 slot;
    u8 unused7[0x19];
    union {
        u32 word;
        u8 byte;
    } pending;
    u8 unused24[0xA8];
    u32 position;
    u8 unusedD0[4];
    u8 count;
    u8 unusedD5[0x2B];
    u8 phase;
    u8 unused101;
    u16 timer;
} State_00256D80;

typedef struct Card_00256D80 {
    u8 unused0[0x3E];
    u8 kind;
    u8 unused3F[5];
    u8 x;
    u8 y;
    u8 unused46[0x11];
    struct {
        s8 marked : 1;
        s8 unused : 7;
    } flags;
} Card_00256D80;


s32 Ta_Eff_001(void *arg0, void *arg1, s32 arg2) {
    extern s32 SzDuel_GetGraveCount();
    extern void *SzDuel_AddUnit();
    s32 packet[4];
    s32 *p;
    Command_00256D80 *command = arg0;
    State_00256D80 *state = arg1;
    s32 i;
    s32 count;
    u32 card;

    packet[0] = 999;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    p = packet;

    if (arg2 >= 0) {
        InitEffectTemp(state);
        if (command->card == 999) {
            SzDuel_CloseMsgPopup();
            return 0;
        }
        switch (TaHand_GetCardKind(command->card & 0xFFFF) >> 5) {
        case 0:
            if (SzDuel_GetUnitMonsterCount(command->flags.parts.id) >= 5) {
                command->card = 999;
                SzDuel_CloseMsgPopup();
                return 0;
            }
            break;
        default:
            if (SzDuel_GetUnitSpellCount(command->flags.parts.id) >= 5) {
                command->card = 999;
                SzDuel_CloseMsgPopup();
                return 0;
            }
            break;
        }
        SzDuel_SetWindowDraw(0);
        TaEffect_LoadModule(state, 501);
        TaView_ReqFocusCamera2(16, command->position, 180);
        return 1;
    }

    switch (state->step) {
    case 0:
        if (command->card == 999) {
            SzDuel_CloseMsgPopup();
            return 0;
        }
        switch (TaHand_GetCardKind(command->card & 0xFFFF) >> 5) {
        case 0:
            if (SzDuel_GetUnitMonsterCount(command->flags.parts.id) >= 5) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
            break;
        default:
            if (SzDuel_GetUnitSpellCount(command->flags.parts.id) >= 5) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
            break;
        }
        SzDuel_SetWindowDraw(0);
        if (TaEffect_IsLoadModule(state) != 1) {
            return 1;
        }
        state->step++;
        break;
    case 1:
        SzDuel_SetWindowDraw(0);
        p[0] = 501;
        p[1] = 0;
        p[2] = command->position;
        p[3] = 0;
        if ((s32)(state->slot = Ta_Do_Effect(p, state)) >= 0) {
            state->count++;
        }
        state->step++;
        break;
    case 2:
        SzDuel_SetWindowDraw(0);
        if (SzEffect_IsUse(state->slot) != 0) {
            if (SzEffect_GetStatus(state->slot) == 2) {
                if (state->pending.byte != 0xFFFF) {
                    if (command->card == 999) {
                        u32 position = command->position;
                        Card_00256D80 *result;
                        result = SzDuel_AddUnit(command->flags.parts.id,
                            position & 0xFF, position >> 8,
                            SzDuel_InqGrave(command->flags.parts.id,
                                SzDuel_GetGraveCount(command->flags.parts.id) - 1), 0);
                        if (result != 0) {
                            if (((s32)result->kind >> 5) != 0) {
                                result->flags.marked = 1;
                            }
                            if (((command->flags.word >> 16) & 1) == 1) {
                                state->position = (result->x << 8) | result->y;
                            }
                        }
                        if ((command->flags.word >> 17) & 1) {
                            SzDuel_DelGrave(command->card >> 16,
                                SzDuel_GetGraveCount(command->flags.word & 0xFFFF) - 1);
                            SzDuel_PackGrave(command->card >> 16);
                        }
                    } else {
                        Card_00256D80 *result;
                        result = SzDuel_AddUnit(command->flags.parts.id,
                            command->position & 0xFF, command->position >> 8,
                            command->card & 0xFFFF, 0);
                        if (result != 0) {
                            if (((s32)result->kind >> 5) != 0) {
                                result->flags.marked = 1;
                            }
                            if (((command->flags.word >> 16) & 1) == 1) {
                                state->position = (result->x << 8) | result->y;
                            }
                        }
                        if ((command->flags.word >> 17) & 1) {
                            count = SzDuel_GetGraveCount(command->card >> 16);
                            for (i = 0; i < count; i++) {
                                card = command->card;
                                if ((card & 0xFFFF) == SzDuel_InqGrave(card >> 16, i)) {
                                    SzDuel_DelGrave(card / 0x10000, i);
                                    i = count;
                                }
                            }
                            SzDuel_PackGrave(command->card >> 16);
                        }
                    }
                    state->pending.word = 0xFFFF;
                }
            }
            return 1;
        }
        state->step++;
        break;
    case 3:
        SzDuel_SetWindowDraw(0);
        if (state->position != 0) {
            TaUtil_DoOpen(state->position >> 8, state->position & 0xFF, 1);
            state->step++;
        } else {
            state->step++;
        }
        break;
    default:
        SzDuel_SetWindowDraw(0);
        switch (state->phase) {
        case 0:
            TaView_RestoreOriginalView(state, 16);
            state->timer = 0;
            state->phase++;
            break;
        default: {
            u16 timer = state->timer++;
            if (timer > 16) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
            break;
        }
        }
        break;
    }
    return 1;
}

typedef struct Context_00257340 {
    s32 unk0;
    s32 side;
    u32 mask;
} Context_00257340;

typedef struct State_00257340 {
    u16 first;
    u16 second;
    u16 phase;
    u8 ids[0xC6];
    u32 timer;
    u8 padD0[4];
    u8 count;
    u8 padD5[0x2B];
    u8 stage;
    u8 pad101;
    u16 frames;
} State_00257340;


static inline u8 valid_00257340(u16 value) {
    return value != 0xFF;
}

s32 Ta_Eff_004(void *arg0, void *arg1, s32 arg2) {
    s32 data[4];
    s32 index;
    u8 flags;
    s32 *command;
    Context_00257340 *context = arg0;
    State_00257340 *state = arg1;
    s32 specialFirst;
    s32 foundFirst;

    extern s32 SzDuel_GetUnitOpenRate();
    extern s32 Ta_Do_Effect();

    data[0] = 999;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    command = data;
    index = 0;
    flags = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(state);
        state->first = 0xFF;
        state->second = 0xFF;
        state->phase = 2;
        if ((foundFirst = Ta_IsActiveTrapB(context->side, 0x2D)) >= 0) {
            if ((specialFirst = Ta_IsActiveTrapB(context->side, 0x2E)) >= 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(0x339));
                TaUtil_DoOpen(specialFirst >> 8, specialFirst & 0xFF, 1);
                state->second = specialFirst;
                state->phase = 0;
                TaEffect_LoadModule(state, 0x25A);
            } else {
                s32 i;
                s32 low;
                s32 high;
                SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(0x338));
                i = 0;
                low = foundFirst & 0xFF;
                high = foundFirst >> 8;
                do {
                    context->mask = ConvUnitIDtoFlagList_OFF(context->mask, Ta_GetCurrentSide(high, low), i);
                    i++;
                } while (i < 11);
                TaUtil_DoOpen(high, low, 1);
                state->second = foundFirst | 0x10000;
                state->phase = 0;
                TaEffect_LoadModule(state, 0x25A);
            }
        }
        {
            s32 low;
            s32 high;
            s32 foundSecond;
            s32 specialSecond;
            s32 i;
            if ((foundSecond = Ta_IsActiveTrapB(context->side == 0 ? 1 : 0, 0x2D)) >= 0) {
                if ((specialSecond = Ta_IsActiveTrapB(context->side, 0x2E)) >= 0) {
                    SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(0x339));
                    TaUtil_DoOpen(specialSecond >> 8, specialSecond & 0xFF, 1);
                    state->first = specialSecond;
                    state->phase = 0;
                    TaEffect_LoadModule(state, 0x25A);
                } else {
                    SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(0x338));
                    i = 0;
                    low = foundSecond & 0xFF;
                    high = foundSecond >> 8;
                    do {
                        context->mask = ConvUnitIDtoFlagList_OFF(context->mask, Ta_GetCurrentSide(high, low), i);
                        i++;
                    } while (i < 11);
                    TaUtil_DoOpen(high, low, 1);
                    state->first = foundSecond | 0x10000;
                    state->phase = 0;
                    TaEffect_LoadModule(state, 0x25A);
                }
            } else {
                state->phase = 2;
            }
        }
        TaEffect_LoadModule(state, 0x15);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (state->second != 0xFF && SzDuel_GetUnitOpenRate(state->second >> 8, state->second & 0xFF) == 0xFF && TaEffect_IsLoadModule(state) == 1) {
            s32 id;
            command[0] = 0x25A;
            command[1] = 0;
            command[2] = state->second;
            command[3] = 0;
            id = Ta_Do_Effect(command, state);
            if (id >= 0) {
                state->ids[state->count] = id;
                state->count++;
            }
            state->phase = 1;
        }
        if (state->first != 0xFF && SzDuel_GetUnitOpenRate(state->first >> 8, state->first & 0xFF) == 0xFF && TaEffect_IsLoadModule(state) == 1) {
            command[0] = 0x25A;
            command[1] = 0;
            command[2] = state->first;
            command[3] = 0;
            state->ids[state->count] = Ta_Do_Effect(command, state);
            state->count++;
            state->phase = 1;
        }
        break;
    case 1: {
        s32 i;
        for (i = 0; i < state->count; i++) {
            if (SzEffect_IsUse(state->ids[i]) == 0) {
                index++;
            }
        }
        SzDuel_SetUnitStatus(state->first >> 8, state->first & 0xFF, 0, 1);
        if (index == state->count) {
            SzDuel_CloseMsgPopup();
            state->phase = 2;
        }
        break;
    }
    case 2:
        state->stage = 2;
        if (TaEffect_IsLoadModule(state) == 1) {
            s32 id;
            command[0] = 0x15;
            command[1] = 0;
            command[2] = context->mask;
            command[3] = 0;
            id = Ta_Do_Effect(command, state);
            if (id >= 0) {
                state->ids[0] = id;
            }
            state->phase++;
        }
        break;
    case 3:
        if (SzEffect_IsUse(state->ids[0]) != 0) {
            if ((state->timer++ % 28U) == 0) {
                SzSound_PlaySE(1, 0x49);
            }
            if (state->timer >= 28U) {
                state->timer = 0;
            }
        } else {
            do {
                if (((context->mask >> (21 - index)) & 1) == 1) {
                    if (index < 11) {
                        Ta_DelUnit(0, index);
                    } else {
                        Ta_DelUnit(1, index - 11);
                    }
                }
                index++;
            } while (index < 22);
            index = 0;
            do {
                SzEffect_SetBusyFlag2(index, 0);
                SzEffect_SetBusyFlag2(index | 0x100, 0);
                index++;
            } while (index < 11);
            flags = 1;
        }
        break;
    default:
        flags = 1;
        break;
    }

    switch (state->stage) {
    case 0: {
        u16 value;
        if (valid_00257340(state->first)) {
            value = state->first;
        } else {
            value = state->second;
        }
        TaView_ReqFocusCamera(0, value & 0xFFFF, 180, 180);
        state->stage++;
        break;
    }
    case 1:
        break;
    case 2:
        TaView_ReqStdCompleteView(20);
        state->stage++;
        break;
    case 3:
        if (state->frames++ >= 20) {
            state->stage++;
            state->frames = 0;
        }
        break;
    case 4:
        if (!(flags & 0xFF & 1) && context->mask != 0) {
            if (state->frames++ == 0) {
                TaView_ReqRotCamera(60, 0x3FFF);
            } else if (state->frames >= 60) {
                state->frames = 0;
            }
        } else {
            TaView_RestoreOriginalView(state, 16);
            state->frames = 0;
            state->stage++;
        }
        break;
    default:
        if (state->frames++ >= 16) {
            flags = (flags | 2) & 0xFF;
        }
        break;
    }
    if ((flags & 0xFF) == 3) {
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
}

typedef struct Request_00257AA0 {
    s32 code;
    s32 position;
    u32 mask;
    u32 flags;
} Request_00257AA0;

typedef struct State_00257AA0 {
    u16 timer;
    u16 targetCount;
    u16 state;
    u8 slots[0x1A];
    s32 positions[13];
    s32 targets[30];
    s32 nextState;
    u32 mask;
    u8 slotCount;
    u8 padding[0x2B];
    u8 phase;
    u8 padding101;
    u16 phaseTimer;
} State_00257AA0;


s32 Ta_Eff_005(void *arg0, void *arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitCtlRateC();
    extern s32 SzDuel_GetUnitCtlRateM();
    extern s32 SzDuel_GetUnitOpenRate();
    State_00257AA0 *state = arg1;
    Request_00257AA0 *request = arg0;
    s32 i;
    s32 k;
    s32 failed;
    Request_00257AA0 eventData;
    Request_00257AA0 *event = &eventData;
    s32 second;
    s32 *positionp;
    s32 *targetp;
    s32 position;
    s32 card;
    s32 index;
    s32 side;
    s32 j;
    s32 location;
    s32 slot;
    s32 inactive;
    s32 complete;
    u8 flags;

    event->code = 999;
    event->position = 0;
    event->mask = 0;
    event->flags = 0;
    inactive = 0;
    complete = 0;
    flags = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        state->mask = Ta_RemoveObjFromFlagLst(request->mask, *(u16 *)&request->flags);
        if ((arg2 = Ta_IsActiveTrapB((request->flags >> 16) == 0 ? 1 : 0, 0x50)) < 0) {
            TaView_ReqFocusCamera2(0, request->position, 200);
        } else {
            if ((second = Ta_IsActiveTrapB(request->flags >> 16, 0x2E)) < 0) {
                TaView_ReqFocusCamera(0, arg2, 180, 180);
                TaUtil_DoOpen(arg2 >> 8, arg2 & 0xFF, 1);
                state->positions[0] = arg2;
                state->nextState = 0x82;
                state->state = 0x80;
                state->phase = 0x20;
            } else {
                TaView_ReqFocusCamera(0, second, 180, 180);
                TaUtil_DoOpen(second >> 8, second & 0xFF, 1);
                state->positions[0] = second;
                state->nextState = 0xA0;
                state->state = 0x80;
                state->phase = 0x20;
            }
        }
        TaEffect_LoadModule(arg1, 0x1F9);
        TaEffect_LoadModule(arg1, 0x25A);
        return 1;
    }
    if (TaEffect_IsLoadModule(arg1) == 1) {
        if (state->state < 0x80 || state->state == 0xFF) {
            i = 0;
            positionp = (s32 *)state;
            for (; i < state->slotCount; positionp++, i++) {
                if (SzEffect_IsUse(state->slots[i]) != 0 &&
                    SzEffect_GetStatus(state->slots[i]) == 2 &&
                    positionp[8] >= 0 &&
                    SzDuel_GetMapUnit(positionp[8] & 0xFF, positionp[8] >> 8) != 0) {
                    position = SzDuel_GetMapUnitID(positionp[8] & 0xFF, positionp[8] >> 8);
                    if (Ta_GetAgreeOwnerIDon22bitFlagLst(position, request->mask) != 0) {
                        positionp[8] = -1;
                        if (Ta_GetAgreeOwnerIDon22bitFlagLst(position, state->mask) != 0) {
                            index = position & 0xFF;
                            if (index > 0 && index < 6) {
                                Ta_UnitFade(position >> 8, index, -1, 1, 3);
                                state->targets[state->targetCount] = position;
                                state->targetCount++;
                            }
                        } else {
                            side = position >> 8;
                            index = position & 0xFF;
                            card = Ta_GetCurrentSide(side, index);
                            location = SzDuel_GetUnitLoc(card, 0);
                            if (Ta_IsLDRangeAvility(side, index, 11) == 1) {
                                Ta_SetRangeVisual(location & 0xFF, location >> 8, 0,
                                    Ta_IsLDAbl(9, card), 1, 1, 11);
                                SzDuel_OpenMsgPopup(0, -120, 80, 270);
                            }
                        }
                    }
                }
            }
            j = 0;
            targetp = (s32 *)state;
            for (; j < state->targetCount; targetp++, j++) {
                if (SzDuel_GetUnitCtlRateC(targetp[21] >> 8, targetp[21] & 0xFF) <= 0 &&
                    SzDuel_GetUnitCtlRateM(targetp[21] >> 8, targetp[21] & 0xFF) <= 0) {
                    inactive++;
                }
            }
            if (inactive >= state->targetCount) {
                complete++;
            }
            if (state->timer % 12 == 0) {
                if (state->state != 0xFF) {
                    i = 0;
                    if (state->state == 0) {
                        position = request->position;
                        event->code = 0x1F9;
                        event->position = 0;
                        event->mask = position;
                        event->flags = 0;
                        slot = (u8)Ta_Do_Effect(event, arg1);
                        *(u8 *)(state->slotCount + (s32)state + 6) = slot;
                        if (slot >= 0) {
                            *(s32 *)(((s32)state->slotCount << 2) + (s32)state + 0x20) = position;
                            state->slotCount++;
                        }
                        failed = 0;
                    } else {
                        i = 0;
                        failed = 0;
                        do {
                            position = request->position;
                            position = Ta_GetLocDistanceFromCenterOnRangeXY(position, state->state, i);
                            if (position >= 0) {
                                event->code = 0x1F9;
                                event->position = 0;
                                event->mask = position;
                                event->flags = 0;
                                slot = (u8)Ta_Do_Effect(event, arg1);
                                *((u8 *)state + state->slotCount + 6) = slot;
                                if (slot >= 0) {
                                    state->positions[state->slotCount] = position;
                                    state->slotCount++;
                                }
                            } else {
                                failed++;
                            }
                            i++;
                        } while (i < 4);
                    }
                }
                if (failed >= 4) {
                    state->state = 0xFF;
                    k = 0;
                    failed = 0;
                    while (k < state->slotCount) {
                        if (SzEffect_IsUse(state->slots[k]) == 0) {
                            failed++;
                        }
                        k++;
                    }
                    if (failed >= state->slotCount) {
                        complete++;
                    }
                } else {
                    state->state++;
                }
            }
            state->timer++;
            if (complete == 2) {
                for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(state->mask); i++) {
                    position = Ta_GetUnitOwnerIDFromLstCount(state->mask, i);
                    Ta_DelUnit(position >> 8, position & 0xFF);
                }
                flags = 1;
            }
        } else {
            switch (state->state - 0x80) {
                case 0:
                    if (SzDuel_GetUnitOpenRate(state->positions[0] >> 8, state->positions[0] & 0xFF) == 0xFF) {
                        if (state->nextState == 0x82) {
                            SzDuel_OpenMsgPopup(0, -120, 80, 0x103);
                        } else {
                            SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(0x339));
                        }
                        event->code = 0x25A;
                        event->position = 0;
                        event->mask = state->positions[0];
                        event->flags = 0;
                        state->slots[0] = Ta_Do_Effect(event, arg1);
                        state->state++;
                    }
                    break;
                case 1:
                    if (SzEffect_IsUse(*(u8 *)(state->slotCount + (s32)state + 5)) == 0) {
                        SzDuel_SetUnitStatus(state->positions[0] >> 8, state->positions[0] & 0xFF, 0, 1);
                        SzDuel_CloseMsgPopup();
                        state->state = state->nextState;
                        if (state->nextState - 0x80 == 2) {
                            state->phase++;
                        } else {
                            state->phase = 0;
                            TaView_ReqFocusCamera2(0, request->position, 200);
                        }
                    }
                    break;
                case 2:
                    SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(0x335));
                    if (state->targetCount < 10) {
                        if (state->timer % 6 == 0) {
                            event->code = 0x1F9;
                            event->position = 0;
                            event->mask = SzDuel_GetUnitLoc(state->positions[0] >> 8, state->positions[0] & 0xFF);
                            event->flags = 0;
                            *(u8 *)(state->slotCount + (s32)state + 6) = Ta_Do_Effect(event, arg1);
                            *(s32 *)(((s32)state->slotCount << 2) + (s32)state + 0x20) = state->positions[0];
                            state->targetCount++;
                        }
                        state->timer++;
                    } else {
                        SzDuel_CloseMsgPopup();
                        if (SzEffect_IsUse(*(u8 *)(state->slotCount + (s32)state + 5)) == 0) {
                            flags = 1;
                        }
                    }
                    break;
                case 32:
                    event->code = 0x1F9;
                    event->position = 0;
                    event->mask = request->position;
                    event->flags = 0;
                    state->slots[0] = Ta_Do_Effect(event, arg1);
                    state->positions[0] = (((u32)request->position >> 8) << 8) | (request->position & 0xFF);
                    state->slotCount++;
                    state->timer++;
                    state->state = 0;
                    TaView_ReqFocusCamera2(0, request->position, 200);
                    break;
            }
        }
        switch (state->phase) {
            case 0:
                if (state->phaseTimer++ > 16) {
                    state->phaseTimer = 0;
                    state->phase++;
                    TaView_ReqStdCompleteView(30);
                }
                break;
            case 1:
                if (state->phaseTimer++ > 30) {
                    state->phase++;
                }
                break;
            case 2:
                if (flags & 1) {
                    SzDuel_CloseMsgPopup();
                    TaView_RestoreOriginalView(arg1, 16);
                    state->phase = 0xFF;
                    state->phaseTimer = 0;
                }
                break;
            case 32:
                break;
            case 33:
                TaView_ReqFocusCamera(30, state->positions[0], 500, 500);
                state->phase = 1;
                state->phaseTimer = 0;
                break;
            default:
                if (state->phaseTimer++ > 16) {
                    flags |= 2;
                }
                break;
        }
    }
    if (flags == 3) {
        if (Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
    }
    return 1;
}

typedef struct Command_00258490 {
    s32 kind;
    s32 arg;
    u32 mask;
    s32 extra;
} Command_00258490;

typedef struct State_00258490 {
    u8 pad0[4];
    u16 state;
    u8 handle;
    u8 pad7[0xF9];
    u8 phase;
    u8 pad101;
    u16 timer;
} State_00258490;


s32 Ta_Eff_006(void *arg0, void *arg1, s32 arg2) {
    Command_00258490 request;
    {
    Command_00258490 *command = &request;
    u8 flags = 0;
    State_00258490 *state = arg1;
    Command_00258490 *src = arg0;
    s32 i;

    request.kind = 999;
    request.arg = 0;
    request.mask = 0;
    request.extra = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(state);
        TaEffect_LoadModule(state, 6);
        return 1;
    }
    switch (state->state) {
    case 0:
        if (TaEffect_IsLoadModule(state) == 1) {
            command->kind = 6;
            command->arg = 0;
            command->mask = src->mask;
            command->extra = 0;
            state->handle = Ta_Do_Effect((s32 *)command, state);
            state->state++;
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->handle) != 1) {
            i = 0;
            do {
                if ((src->mask >> (21 - i) & 1) == 1) {
                    if (i < 11) {
                        Ta_DelUnit(0, i);
                    } else {
                        Ta_DelUnit(1, i - 11);
                    }
                }
                i++;
            } while (i < 22);
            state->state++;
        }
        break;
    default:
        flags = 1;
        break;
    }
    switch (state->phase) {
    case 0:
        TaView_ReqStdCompleteView(30);
        state->phase++;
        break;
    case 1:
        if (state->timer++ >= 30) {
            state->phase++;
            state->timer = 0;
        }
        break;
    case 2:
        if (!(flags & 1)) {
            if (state->timer++ == 0) {
                TaView_ReqRotCamera(60, 0x3FFF);
            } else if (state->timer >= 60) {
                state->timer = 0;
            }
        } else {
            TaView_RestoreOriginalView(state, 16);
            state->timer = 0;
            state->phase++;
        }
        break;
    default:
        if (state->timer++ >= 16) {
            flags |= 2;
        }
        break;
    }
    if (flags == 3) {
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
    }
}


typedef struct Request_00258760 {
    s32 command;
    s32 field4;
    s32 coord;
    s32 fieldC;
} Request_00258760;

typedef struct Input_00258760 {
    s32 command;
    u32 value;
    u32 field8;
    s32 fieldC;
} Input_00258760;

typedef struct State_00258760 {
    u16 coord;
    u16 next;
    u16 step;
    u8 handles[0x1A];
    s32 coords[0x2C];
    u32 flags;
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_00258760;

s32 Ta_Eff_007(void *arg0, void *arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitOpenRate();
    Request_00258760 requestData;
    s32 i;
    Request_00258760 *request = &requestData;
    s32 second;
    s32 first;
    s32 j;
    s32 k;
    State_00258760 *walk;
    s32 object;
    s32 coord;
    u8 handle;
    Input_00258760 *input = arg0;
    State_00258760 *state = arg1;

    request->command = 999;
    request->field4 = 0;
    request->coord = 0;
    request->fieldC = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(state);
        state->flags = Ta_RemoveObjFromFlagLst(input->field8, (u16)input->fieldC);
        if ((first = Ta_IsActiveTrapB(input->fieldC, 0x4B)) >= 0) {
            if ((second = Ta_IsActiveTrapB(input->fieldC == 0 ? 1 : 0, 0x2E)) >= 0) {
                TaView_ReqFocusCamera(0, first, 0xB4, 0xB4);
                TaUtil_DoOpen(second >> 8, second & 0xFF, 1);
                state->step = 0x20;
                state->coord = second;
                state->next = 0x24;
                TaEffect_LoadModule(state, 0x25A);
                TaEffect_LoadModule(state, 0x1FB);
            } else {
                TaView_ReqFocusCamera(0, second, 0xB4, 0xB4);
                TaUtil_DoOpen(first >> 8, first & 0xFF, 1);
                state->step = 0x20;
                state->coord = first;
                state->next = 0x22;
                TaEffect_LoadModule(state, 0x25A);
                TaEffect_LoadModule(state, 0x25B);
            }
        } else {
            Ta_SetRangeVisual(input->value & 0xFF, input->value >> 8, 0, 0, 1, 0x12, 0xFF);
            TaView_ReqStdCompleteView(0x1E);
            TaEffect_LoadModule(state, 0x1FB);
            TaEffect_LoadModule(state, 0x25B);
        }
        return 1;
    }
    if (TaEffect_IsLoadModule(state) != 1) {
        return 1;
    }
    switch (state->step) {
    case 0:
        Ta_SetEffectDependOnFlagLst(input, state, request, 0x1FB);
        state->step++;
        break;
    case 1:
        for (i = 0, walk = state; i < state->count; walk = (State_00258760 *)((u8 *)walk + 4), i++) {
            if (SzEffect_IsUse(state->handles[i]) == 1 && SzEffect_GetStatus(state->handles[i]) == 2 && walk->coords[0] >= 0) {
                if (Ta_GetAgreeOwnerIDon22bitFlagLst(walk->coords[0], state->flags) != 0) {
                    request->command = 0x25B;
                    request->field4 = 0;
                    request->coord = walk->coords[0];
                    request->fieldC = 1;
                    handle = Ta_Do_Effect((s32 *)request, state);
                    state->handles[state->count + i] = handle;
                    if (handle >= 0) {
                        state->coords[state->count + i] = walk->coords[0];
                        state->next++;
                        walk->coords[0] = -1;
                    }
                } else {
                    object = Ta_GetCurrentSide(walk->coords[0] >> 8, walk->coords[0] & 0xFF);
                    coord = SzDuel_GetUnitLoc(object, 0);
                    if (Ta_IsLDRangeAvility(walk->coords[0] >> 8, walk->coords[0] & 0xFF, 0xB) == 1) {
                        Ta_SetRangeVisual(coord & 0xFF, coord >> 8, 0, Ta_IsLDAbl(9, object), 1, 1, 0xB);
                        SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x10E);
                    }
                    walk->coords[0] = -1;
                }
            }
        }
        for (j = 0; j < state->count + state->next; j++) {
            if (SzEffect_IsUse(state->handles[j]) == 1) {
                return 1;
            }
        }
        k = 0;
        do {
            if (((state->flags >> (0x15 - k)) & 1) == 1) {
                if (k < 0xB) {
                    Ta_DelUnit(0, k);
                } else {
                    Ta_DelUnit(1, k - 0xB);
                }
            }
            k++;
        } while (k < 0x16);
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(state, 0x10);
        state->timer = 0;
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        state->step++;
        break;
    case 2:
        if (state->timer++ > 0x10) {
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    case 0x20:
        if (SzDuel_GetUnitOpenRate(state->coord >> 8, state->coord & 0xFF) != 0xFF) {
            return 1;
        }
        if (state->next == 0x24) {
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x339));
        } else {
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x334));
        }
        request->command = 0x25A;
        request->field4 = 0;
        request->coord = state->coord;
        request->fieldC = 0;
        state->handles[state->count] = Ta_Do_Effect((s32 *)request, state);
        state->count++;
        state->step++;
        break;
    case 0x21:
        if (SzEffect_IsUse(state->handles[state->count - 1]) == 1) {
            return 1;
        }
        SzDuel_SetUnitStatus(state->coord >> 8, state->coord & 0xFF, 0, 1);
        SzDuel_CloseMsgPopup();
        state->step = state->next;
        break;
    case 0x22:
        request->command = 0x25B;
        request->field4 = 0;
        request->coord = state->coord;
        request->fieldC = 0;
        state->handles[state->count] = Ta_Do_Effect((s32 *)request, state);
        state->count++;
        state->next = 0x23;
        state->step = 0x21;
        break;
    case 0x23:
        Ta_DelUnit(state->coord >> 8, state->coord & 0xFF);
        TaView_RestoreOriginalView(state, 0x10);
        state->timer = 0;
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        state->step = 2;
        break;
    case 0x24:
        state->count = 0;
        state->next = 0;
        TaView_ReqStdCompleteView(0x1E);
        Ta_SetEffectDependOnFlagLst(input, state, request, 0x1FB);
        state->step = 1;
        return 1;
    default:
        return 1;
    }
    return 1;
}


typedef struct Input_00258E20 {
    s32 unused[2];
    s32 index;
    u32 value;
} Input_00258E20;

typedef struct State_00258E20 {
    s16 active;
    u16 position;
    u16 phase;
    u8 entries[0xCE];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_00258E20;

typedef struct Command_00258E20 {
    s32 type;
    s32 flags;
    s32 position;
    s32 amount;
} Command_00258E20;

s32 Ta_Eff_008(void *arg0, void *arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitOpenRate();
    Input_00258E20 *input = arg0;
    State_00258E20 *state = arg1;
    s32 var_s0;
    Command_00258E20 command;
    Command_00258E20 *action = &command;
    s32 temp_v0;
    s32 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v1;
    u32 temp_a0;

    action->type = 0x3E7;
    action->flags = 0;
    action->position = 0;
    action->amount = 0;
    temp_a0 = input->value;
    if ((temp_a0 >> 0x10) == 4) {
        s32 currentValue = SzDuel_GetLP(input->index);
        var_s0 = (u16) input->value - currentValue;
    } else {
        var_s0 = Ta_GetLPRevByNaturalEffect(0x2B, temp_a0 & 0xFFFF);
    }
    if (var_s0 < 0) {
        var_s0 = 0;
    }
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        TaEffect_LoadModule(arg1, 0x1FC);
        if ((temp_v0 = Ta_IsActiveTrapB(input->index, 0x2A)) < 0) {
            state->phase = 0x20U;
        } else {
            if ((temp_v0_2 = Ta_IsActiveTrapB(input->index, 0x2E)) < 0) {
                state->position = (u16) temp_v0;
                TaEffect_LoadModule(arg1, 0x25A);
                TaEffect_LoadModule(arg1, 0x224);
                state->phase = 0x40U;
            } else {
                TaEffect_LoadModule(arg1, 0x25A);
                TaView_ReqFocusCamera(0, temp_v0_2, 0xB4, 0xB4);
                state->position = (u16) temp_v0_2;
                TaUtil_DoOpen(temp_v0_2 >> 8, temp_v0_2 & 0xFF, 1);
                state->phase = 0x10U;
                state->active = 1;
            }
        }
        return 1;
    }
    if (TaEffect_IsLoadModule(arg1) == 1) {
        temp_v1 = state->phase;
        switch (temp_v1) {                          
        case 0x0:
            if (SzEffect_IsUse((s32) *(u8 *)(state->count + (u32)state + 5)) == 1) {
                return 1;
            }
            SzDuel_CalcLP(input->index, 0, var_s0);
            SzDuel_CloseMsgPopup();
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        case 0x1:
            if (SzDuel_GetUnitOpenRate((s32) state->position >> 8, state->position & 0xFF) != 0xFF) {
                temp_v0_3 = state->position;
                if (SzDuel_GetUnitStatus((s32) temp_v0_3 >> 8, temp_v0_3 & 0xFF, 4) == 0) {
                    temp_v0_4 = state->position;
                    TaUtil_DoOpen((s32) temp_v0_4 >> 8, temp_v0_4 & 0xFF, 1);
                }
                return 1;
            }
            TaView_ReqFocusCamera(0, (s32) state->position, 0xB4, 0xB4);
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x32F));
            action->type = 0x25A;
            action->flags = 0;
            action->position = (s32) state->position;
            action->amount = 0;
            state->entries[state->count] = Ta_Do_Effect((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            state->phase = (u16) (state->phase + 1);
            return 1;
        case 0x2:
        case 0x4:
        case 0x11:
            if (SzEffect_IsUse((s32) *(u8 *)(state->count + (u32)state + 5)) == 0) {
                if (state->phase != 4) {
                    temp_v0_5 = state->position;
                    SzDuel_SetUnitStatus((s32) temp_v0_5 >> 8, temp_v0_5 & 0xFF, 0, 1);
                }
                state->phase = (u16) (state->phase + 1);
            }
            break;
        case 0x3:
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x10B);
            action->type = 0x224;
            action->flags = 0;
            action->position = 0;
            action->amount = var_s0;
            state->entries[state->count] = Ta_Do_Effect((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            state->phase = (u16) (state->phase + 1);
            return 1;
        case 0x5:
            SzDuel_CloseMsgPopup();
            temp_v0_6 = state->position;
            SzDuel_SetUnitStatus((s32) temp_v0_6 >> 8, temp_v0_6 & 0xFF, 0, 1);
            SzDuel_CalcLP(input->index, 1, var_s0);
            state->phase = (u16) (state->phase + 1);
            TaView_RestoreOriginalView(arg1, 0x10);
            state->timer = 0U;
            break;
        case 0x6:
            if (state->timer++ > 0x10) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
            break;
        case 0x10:
            if (SzDuel_GetUnitOpenRate((s32) state->position >> 8, state->position & 0xFF) != 0xFF) {
                temp_v0_7 = state->position;
                if (SzDuel_GetUnitStatus((s32) temp_v0_7 >> 8, temp_v0_7 & 0xFF, 4) == 0) {
                    temp_v0_8 = state->position;
                    TaUtil_DoOpen((s32) temp_v0_8 >> 8, temp_v0_8 & 0xFF, 1);
                }
                return 1;
            }
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x339));
            action->type = 0x25A;
            action->flags = 0;
            action->position = (s32) state->position;
            action->amount = 0;
            state->entries[state->count] = Ta_Do_Effect((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            state->phase = (u16) (state->phase + 1);
            break;
        case 0x12:
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x10A);
            action->type = 0x1FC;
            action->flags = 0;
            action->position = 0;
            action->amount = var_s0;
            state->entries[state->count] = Ta_Do_Effect((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            state->phase = 0U;
            return 1;
        case 0x20:
            action->type = 0x1FC;
            action->flags = 0;
            action->position = 0;
            action->amount = var_s0;
            state->entries[state->count] = Ta_Do_Effect((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x10A);
            state->phase = 0U;
            break;
        case 0x40:
            action->type = 0x1FC;
            action->flags = 0;
            action->position = 0;
            action->amount = (s32) (var_s0 | 0x10000);
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x10A);
            state->phase = (u16) (state->phase + 1);
            state->entries[state->count] = Ta_Do_Effect((s32 *)action, arg1);
            state->count = (u8) (state->count + 1);
            break;
        case 0x41:
            if (SzEffect_IsUse((s32) *(u8 *)(state->count + (u32)state + 5)) == 1) {
                return 1;
            }
            state->phase = 1U;
            break;
        default:
            return 1;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_074", Ta_Eff_009);


typedef struct Task_00259D90 {
    u8 pad0[4];
    u16 active;
    u8 ids[0x1A];
    s32 positions[0x2D];
    u8 count;
    u8 padD5[0x2B];
    u8 state;
    u8 pad101;
    u16 timer;
} Task_00259D90;

s32 Ta_Eff_012(void *arg0, void *arg1, s32 arg2) {
    s32 setupData[4];
    s32 *setup = setupData;
    Task_00259D90 *task = arg1;
    s32 i;
    s32 complete;
    u8 flags;
    u8 *position;
    u8 *id;

    setup[0] = 999;
    setup[1] = 0;
    setup[2] = 0;
    setup[3] = 0;
    complete = 0;
    flags = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        TaView_ReqTopView();
        TaEffect_LoadModule(arg1, 0x200);
        return 1;
    }

    switch (task->active) {
    case 0:
        if (TaEffect_IsLoadModule(arg1) == 1) {
            SzDuel_OpenMsgPopup(0, -120, 80, 0x108);
            Ta_SetEffectDependOnFlagLst(arg0, arg1, setup, 0x200);
            task->active++;
        }
        break;
    default:
        for (i = 0, position = arg1; i < task->count; position += 4, i++) {
            id = &task->ids[i];
            if (SzEffect_IsUse(*id) == 1) {
                if (SzEffect_GetStatus(*id) == 2 && *(s32 *)(position + 0x20) >= 0) {
                    TaUtil_DoOpen(*(s32 *)(position + 0x20) >> 8, *(s32 *)(position + 0x20) & 0xFF, 1);
                    SzDuel_SetUnitStatus(*(s32 *)(position + 0x20) >> 8, *(s32 *)(position + 0x20) & 0xFF, 0, 1);
                    Ta_SetUnitCurseRest(*(s32 *)(position + 0x20) >> 8, *(s32 *)(position + 0x20) & 0xFF, *((u8 *)arg0 + 0xC));
                    *(s32 *)(position + 0x20) = -1;
                }
            } else {
                complete++;
            }
        }
        SzDuel_CloseMsgPopup();
        if (complete >= task->count) {
            flags = 1;
        }
        break;
    }

    switch (task->state) {
    case 0:
        if (task->timer++ > 10) {
            TaView_ReqStdCompleteView(16);
            task->state++;
            task->timer = 0;
        }
        break;
    case 1:
        if (flags & 1) {
            if (task->timer++ > 16) {
                task->state++;
                task->timer = 0;
                TaView_RestoreOriginalView(arg1, 16);
            }
        }
        break;
    default:
        if (task->timer++ > 16) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            flags |= 2;
        }
        break;
    }
    if (flags == 3) {
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
}

typedef struct Request_0025A060 {
    s32 command;
    s32 kind;
    s32 mask;
    s32 value;
} Request_0025A060;

typedef struct State_0025A060 {
    u16 alpha;
    u16 unused;
    u16 phase;
    u8 handles[0x1A];
    s32 cards[0x2D];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0025A060;


s32 Ta_Eff_013(void *arg0, void *arg1, s32 arg2) {
    State_0025A060 *state = arg1;
    Request_0025A060 *request = arg0;
    Request_0025A060 task;
    s32 i;
    s32 finished;
    s32 total;
    s32 card;
    u8 handle;
    u8 *cursor;
    Request_0025A060 *next = &task;

    next->command = 999;
    next->kind = 0;
    next->mask = 0;
    next->value = 0;
    i = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(state);
        state->alpha = 0x80;
        Ta_AllUnitFade(request, state, arg2, -1, 1, 1);
        if (Ta_GetUnitNumFrom22bitFlagList(request->mask) == 1) {
            TaView_ReqFocusCamera(0, Ta_GetUnitOwnerIDFromLstCount(request->mask, 0), 100, 180);
        } else {
            TaView_ReqStdCompleteView(0x10);
        }
        TaEffect_LoadModule(state, 0x201);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if ((s32)state->alpha > 0x3F) {
            state->alpha -= 0xF;
        } else {
            state->alpha = 0x30;
            if (TaEffect_IsLoadModule(state) == 1) {
                if ((s32)state->timer++ > 0x10) {
                    if ((request->kind == 2 || request->kind == 4) && request->value == 0) {
                        total = Ta_GetUnitNumFrom22bitFlagList(request->mask);
                        for (finished = 0; finished < total; finished++) {
                            card = Ta_GetUnitOwnerIDFromLstCount(request->mask, finished);
                            next->command = 0x201;
                            next->kind = 0;
                            next->mask = card;
                            next->value = 1;
                            handle = Ta_Do_Effect((s32 *)next, state);
                            state->handles[state->count] = handle;
                            if ((s32)handle >= 0) {
                                state->cards[state->count] = card;
                                state->count++;
                            }
                        }
                    } else {
                        Ta_SetEffectDependOnFlagLst(request, state, next, 0x201);
                    }
                    state->phase++;
                    state->timer = 0;
                }
            }
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        break;
    case 1:
        finished = 0;
        cursor = (u8 *)state;
        while (finished < state->count) {
            if (SzEffect_IsUse(state->handles[finished]) != 0) {
                if (SzEffect_GetStatus(state->handles[finished]) == 2) {
                    if (*(s32 *)(cursor + 0x20) >= 0) {
                        SzEffect_SetBusyFlag2(*(s32 *)(cursor + 0x20), 0);
                        if (request->kind == 3 || request->kind == 5) {
                            SzDuel_SetUnitStatus(*(s32 *)(cursor + 0x20) >> 8, *(s32 *)(cursor + 0x20) & 0xFF, 5, request->value);
                            SzDuel_SetUnitStatus(*(s32 *)(cursor + 0x20) >> 8, *(s32 *)(cursor + 0x20) & 0xFF, 3, request->value);
                        }
                        if (request->kind == 2 || request->kind == 4) {
                            TaUtil_DoOpen(*(s32 *)(cursor + 0x20) >> 8, *(s32 *)(cursor + 0x20) & 0xFF, request->value);
                        }
                        *(s32 *)(cursor + 0x20) = -1;
                    }
                }
            } else {
                i++;
            }
            cursor += 4;
            finished++;
        }
        if (i < state->count) {
            break;
        }
        if ((s32)state->timer++ > 0x10) {
            TaView_RestoreOriginalView(state, 0x10);
            state->timer = 0;
            Ta_AllUnitFade(request, state, arg2, 1, 0, 1);
            state->phase++;
        }
        break;
    default:
        state->alpha += 0xF;
        if ((s32)state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 0x80 && (s32)state->timer++ > 0x10 && Ta_IsFinishFade() == 1) {
            SzDuel_CloseMsgPopup();
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct Context_0025A4C0 {
    u8 pad0[8];
    s32 side;
    s32 mode;
} Context_0025A4C0;

typedef struct State_0025A4C0 {
    u16 counter;
    u16 field2;
    u16 step;
    u8 handle;
    u8 pad7[0x19];
    s32 side;
    u8 pad24[0xA8];
    s32 fieldCC;
} State_0025A4C0;

typedef struct Command_0025A4C0 {
    s32 id;
    s32 field4;
    s32 field8;
    s32 fieldC;
} Command_0025A4C0;


s32 Ta_Eff_014(void *arg0, u16 *arg1, s32 arg2) {
    Command_0025A4C0 command;
    Command_0025A4C0 *packet = &command;
    Context_0025A4C0 *context = arg0;
    State_0025A4C0 *state = (State_0025A4C0 *)arg1;

    command.id = 999;
    command.field4 = 0;
    command.field8 = 0;
    command.fieldC = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        TaEffect_LoadModule(arg1, 0x202);
        if (context->mode != 0) {
            TaEffect_LoadModule(arg1, 0x263);
        }
        return 1;
    }
    switch (state->step) {
    case 0:
        if (TaEffect_IsLoadModule(arg1) == 1) {
            packet->id = 0x202;
            packet->field4 = 0;
            packet->field8 = 0;
            packet->fieldC = 0;
            state->handle = Ta_Do_Effect((s32 *)packet, arg1);
            state->step++;
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->handle) == 1) {
            return 1;
        }
        if (context->mode == 0) {
            if (SzDuel_GetHandCount(context->side) == 0) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
            if (state->counter < 150) {
                TaEff_PopHand((s32)arg0, arg1, 1, context->side, 1);
                state->counter++;
                return 1;
            }
            if (TaEff_PopHand((s32)arg0, arg1, 1, context->side, 0) == 0) {
                SzDuel_CloseHandPopup();
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                return 0;
            }
        } else {
            if (SzDuel_GetHandCount(context->side == 0 ? 1 : 0) == 0) {
                state->step++;
                return 1;
            }
            if (TaEff_PopHand((s32)arg0, arg1, 0, context->side == 0 ? 1 : 0, 1) == 0) {
                return 1;
            }
            packet->id = 0x263;
            packet->field4 = 0;
            packet->field8 = 0;
            packet->fieldC = 0;
            state->handle = Ta_Do_Effect((s32 *)packet, arg1);
            state->step++;
            state->side = context->side;
        }
        break;
    case 2:
        if (SzEffect_IsUse(state->handle) != 0) {
            if (state->counter++ == 6) {
                SzDuel_CloseHandPopup();
                state->fieldCC = 0;
                state->field2 = 0;
            }
            return 1;
        }
        state->counter = 0;
        if (SzDuel_GetHandCount(context->side) == 0) {
            state->step = 16;
            return 1;
        }
        if (TaEff_PopHand((s32)arg0, arg1, 1, context->side, 1) == 0) {
            return 1;
        }
        packet->id = 0x263;
        packet->field4 = 0;
        packet->field8 = 0;
        packet->fieldC = 0;
        state->handle = Ta_Do_Effect((s32 *)packet, arg1);
        state->side = context->side;
        state->step++;
        break;
    case 3:
        if (SzEffect_IsUse(state->handle) != 0) {
            if (state->counter++ == 6) {
                SzDuel_CloseHandPopup();
            }
            return 1;
        }
        state->step++;
        break;
    default:
        {
            s32 i = 0;
            s32 card;
            do {
                card = SzDuel_InqHand(0, i) & 0xFFF;
                if (card >= 0 && card != 999) {
                    SzDuel_DelHand(0, i);
                    SzDuel_AddGrave(0, card);
                }
                i++;
            } while (i < 5);
            i = 0;
            do {
                card = SzDuel_InqHand(1, i) & 0xFFF;
                if (card >= 0 && card != 999) {
                    SzDuel_DelHand(1, i);
                    SzDuel_AddGrave(1, card);
                }
                i++;
            } while (i < 5);
        }
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
}

s32 TaEff_PopHand(s32 arg0, u16 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a1;
    s32 temp_v1;
    s32 var_s0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v0;

    var_s0 = 0;
    if (arg1[1] == 0) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0xCC);
        *(s32 *)((u8 *)arg1 + 0xCC) = temp_v1 + 1;
        if (temp_v1 == 0) {
            var_v0 = (arg2 & 0xFF) == 1 ? 0 : 0x3C0;
            arg1[1] = var_v0;
        }
    }
    SzDuel_OpenHandPopup(arg3, 0, arg1[1] - 0x1E0);
    if ((arg4 & 0xFF) == 1) {
        if (arg1[1] != 0x1E0) {
            var_v1 = (arg2 & 0xFF) == 1 ? 0x1E : -0x1E;
            arg1[1] += var_v1;
        } else {
            var_s0 = 1;
        }
    } else {
        temp_a1 = arg2 & 0xFF;
        var_v0_2 = temp_a1 == 1 ? 0 : 0x3C0;
        if (arg1[1] != var_v0_2) {
            var_v1_2 = temp_a1 == 1 ? 0x1E : -0x1E;
            arg1[1] -= var_v1_2;
        } else {
            var_s0 = 1;
        }
    }
    return var_s0;
}

typedef struct State_0025AA80 {
    u8 pad0[4];
    u16 step;
    u8 handles[26];
    s32 entries[45];
    u8 count;
    u8 padD5[0x2B];
    u8 phase;
    u8 pad101;
    u16 timer;
} State_0025AA80;

typedef struct Mask_0025AA80 {
    u8 pad0[8];
    u32 mask;
} Mask_0025AA80;


s32 Ta_Eff_015(void *arg0, void *arg1, s32 arg2) {
    s32 descriptor[4];
    s32 i;
    u8 flags;
    s32 *request = descriptor;
    State_0025AA80 *state = arg1;
    Mask_0025AA80 *source = arg0;
    s32 mode = arg2;
    u8 handle;
    u8 phase;

    descriptor[0] = 999;
    descriptor[1] = 0;
    descriptor[2] = 0;
    descriptor[3] = 0;
    i = 0;
    flags = 0;
    SzDuel_SetWindowDraw(0);
    if (mode >= 0) {
        InitEffectTemp(arg1);
        TaView_ReqStdTopDownView(0);
        TaEffect_LoadModule(arg1, 15);
        return 1;
    }
    switch (state->step) {
    case 0:
        if (TaEffect_IsLoadModule(arg1) == 1) {
            do {
                if ((source->mask >> (21 - i) & 1) == 1) {
                    if (i < 11) {
                        request[0] = 15;
                        request[1] = 0;
                        request[2] = i;
                        request[3] = SzDuel_GetUnitKind(0, i) >> 5;
                        handle = Ta_Do_Effect(request, arg1);
                        state->handles[state->count] = handle;
                        if (handle >= 0) {
                            state->entries[state->count] = i;
                            state->count++;
                        }
                    } else {
                        s32 entry;
                        request[0] = 15;
                        entry = i - 11;
                        request[1] = 0;
                        request[2] = entry | 0x100;
                        request[3] = SzDuel_GetUnitKind(1, entry) >> 5;
                        handle = Ta_Do_Effect(request, arg1);
                        state->handles[state->count] = handle;
                        if (handle >= 0) {
                            state->entries[state->count] = (i - 11) | 0x100;
                            state->count++;
                        }
                    }
                }
                i++;
            } while (i < 22);
            state->step++;
        }
        break;
    default: {
        s32 j;
        for (j = 0; j < state->count; j++) {
            if (SzEffect_IsUse(state->handles[j]) == 0) {
                i++;
            }
        }
        if (i >= state->count) {
            flags = 1;
        }
        break;
    }
    }
    phase = state->phase;
    switch (phase) {
    case 0:
        if (flags & 1) {
            state->phase = phase + 1;
            state->timer = 0;
            TaView_RestoreOriginalView(arg1, 30);
        }
        break;
    default:
        if (state->timer++ > 30) {
            flags |= 2;
        }
        break;
    }
    if (flags == 3) {
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
}

typedef struct State_0025AD60 {
    u16 alpha;
    u16 unk2;
    u16 phase;
    u8 slots[0xCE];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0025AD60;


s32 Ta_Eff_016(void *arg0, void *arg1, s32 arg2) {
    s32 packetData[4];
    s32 *packet = packetData;
    State_0025AD60 *state = arg1;
    u8 slot;
    extern s32 Ta_IsFinishDestEfc();

    packetData[0] = 999;
    packetData[1] = 0;
    packetData[2] = 0;
    packetData[3] = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        TaView_ReqStdCompleteView(0x10);
        TaEffect_LoadModule(arg1, 0x204);
        TaEffect_LoadModule(arg1, 0x1F);
        TaEffect_LoadModule(arg1, 0x25B);
        Ta_AllUnitFade(arg0, arg1, arg2, -1, 1, 1);
        state->alpha = 0x80;
        return 1;
    }

    if (state->phase == 0) {
        if (state->alpha > 0x3F) {
            state->alpha -= 0xF;
        } else {
            state->alpha = 0x30;
            if (TaEffect_IsLoadModule(arg1) == 1 && state->timer++ > 0x10) {
                packet[0] = 0x204;
                packet[1] = 0;
                packet[2] = 0;
                packet[3] = 0;
                slot = Ta_Do_Effect(packet, arg1);
                state->slots[state->count] = slot;
                if (slot >= 0) {
                    state->count++;
                }
                state->phase++;
                state->timer = 0;
            }
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
    } else if (state->phase == 1) {
        if (SzEffect_IsUse(state->slots[0]) == 1) {
            return 1;
        }
        Ta_SetEffectDependOnFlagLst(arg0, arg1, packet, 0x1F);
        state->phase++;
    } else if (state->phase == 2) {
        if (Ta_ManageDestroyEffect(arg0, arg1, packet) != 0) {
            state->phase++;
        }
    } else if (state->phase == 3) {
        if (Ta_IsFinishDestEfc(arg0, arg1, packet) != 0) {
            Ta_AllUnitFade(arg0, arg1, arg2, 1, 0, 1);
            TaView_RestoreOriginalView(arg1, 0x10);
            state->timer = 0;
            state->phase++;
        }
    } else {
        state->alpha += 0xF;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 0x80 && state->timer++ > 0x10 && Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
    }
    return 1;
}

typedef struct State_0025B050 {
    u16 alpha;
    u16 unk2;
    u16 phase;
    u8 slots[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0025B050;

typedef struct Params_0025B050 {
    s32 id;
    s32 value1;
    s32 value2;
    s32 value3;
} Params_0025B050;


s32 Ta_Eff_017_A(void *arg0, void *arg1, s32 arg2) {
    extern s32 Ta_IsFinishDestEfc();
    Params_0025B050 params;
    Params_0025B050 *p = &params;
    State_0025B050 *state = arg1;
    u8 slot;

    p->id = 999;
    p->value1 = 0;
    p->value2 = 0;
    p->value3 = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        TaView_ReqStdCompleteView(0x10);
        TaEffect_LoadModule(arg1, 0x14);
        TaEffect_LoadModule(arg1, 0x1F);
        TaEffect_LoadModule(arg1, 0x25B);
        Ta_AllUnitFade(arg0, arg1, arg2, -1, 1, 1);
        state->alpha = 0x80;
        return 1;
    }
    if (state->phase == 0) {
        if (state->alpha > 0x3F) {
            state->alpha -= 0xF;
        } else {
            state->alpha = 0x30;
            if (TaEffect_IsLoadModule(arg1) == 1) {
                p->id = 0x14;
                p->value1 = 0;
                p->value2 = 0;
                p->value3 = 0;
                slot = Ta_Do_Effect((s32 *)p, arg1);
                state->slots[state->count] = slot;
                if (slot >= 0) {
                    state->count++;
                }
                state->phase++;
            }
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
    } else if (state->phase == 1) {
        if (SzEffect_IsUse(state->slots[0]) == 1) {
            return 1;
        }
        Ta_SetEffectDependOnFlagLst(arg0, arg1, p, 0x1F);
        state->phase++;
    } else if (state->phase == 2) {
        if (Ta_ManageDestroyEffect(arg0, arg1, p) != 0) {
            state->phase++;
        }
    } else if (state->phase == 3) {
        if (Ta_IsFinishDestEfc(arg0, arg1, p) != 0) {
            Ta_AllUnitFade(arg0, arg1, arg2, 1, 0, 1);
            TaView_RestoreOriginalView(arg1, 0x10);
            state->timer = 0;
            state->phase++;
        }
    } else {
        state->alpha += 0xF;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 0x80) {
            if (state->timer++ > 0x10 && Ta_IsFinishFade() == 1) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
    }
    return 1;
}

typedef struct {
    u16 fade;
    u16 pad2;
    u16 state;
    u8 entries[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0025B330;


s32 Ta_Eff_018(void *arg0, void *arg1, s32 arg2) {
    extern s32 Ta_IsFinishDestEfc();
    s32 data[4];
    s32 *params = data;
    State_0025B330 *state = arg1;
    u8 result;
    u16 stage;

    data[0] = 999;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        TaEffect_LoadModule(arg1, 0x206);
        TaEffect_LoadModule(arg1, 0x1F);
        TaEffect_LoadModule(arg1, 0x25B);
        Ta_AllUnitFade(arg0, arg1, arg2, -1, 1, 1);
        state->fade = 0x80;
        return 1;
    }

    stage = state->state;
    if (stage == 0) {
        if (state->fade > 0x3F) {
            state->fade -= 0xF;
        } else {
            state->fade = 0x30;
            if (TaEffect_IsLoadModule(arg1) == 1) {
                params[0] = 0x206;
                params[1] = 0;
                params[2] = 0;
                params[3] = 0;
                TaView_ReqStdCompleteView(0x10);
                result = Ta_Do_Effect(params, arg1);
                state->entries[state->count] = result;
                if (result >= 0) {
                    state->count++;
                }
                state->state++;
            }
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
    } else if (stage == 1) {
        if (SzEffect_IsUse(state->entries[0]) == 1) {
            return 1;
        }
        Ta_SetEffectDependOnFlagLst(arg0, arg1, params, 0x1F);
        state->state++;
    } else if (stage == 2) {
        if (Ta_ManageDestroyEffect(arg0, arg1, params) != 0) {
            state->state++;
        }
    } else if (stage == 3) {
        if (Ta_IsFinishDestEfc(arg0, arg1, params) != 0) {
            Ta_AllUnitFade(arg0, arg1, arg2, 1, 0, 1);
            TaView_RestoreOriginalView(arg1, 0x10);
            state->timer = 0;
            state->state++;
        }
    } else {
        state->fade += 0xF;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        if (state->fade == 0x80 && state->timer++ > 0x10 && Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
    }
    return 1;
}

typedef struct State_0025B610 {
    u16 fade;
    u16 unk2;
    u16 phase;
    u8 ids[0x1A];
    s32 flags[0x2D];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0025B610;

typedef struct Source_0025B610 {
    u8 padding[8];
    u32 mask;
} Source_0025B610;


s32 Ta_Eff_019(void *arg0, void *arg1, s32 arg2) {
    s32 event[4];
    s32 *command = event;
    State_0025B610 *state = arg1;
    s32 i;
    u8 id;

    event[0] = 0x3E7;
    event[1] = 0;
    event[2] = 0;
    event[3] = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        Ta_AllUnitFade(arg0, arg1, arg2, -1, 1, 1);
        TaView_ReqStdCompleteView(0x10);
        state->fade = 0x80;
        TaEffect_LoadModule(arg1, 0x38);
    } else if (state->phase == 0) {
        if (state->fade > 0x3F) {
            state->fade -= 0xF;
        } else {
            state->fade = 0x30;
            if (TaEffect_IsLoadModule(arg1) == 1) {
                command[0] = 0x38;
                command[1] = 0;
                command[2] = ((Source_0025B610 *)arg0)->mask;
                command[3] = 0;
                state->flags[state->count] = 1;
                id = Ta_Do_Effect(command, arg1);
                state->ids[state->count] = id;
                if (id >= 0) {
                    state->count++;
                }
                state->phase++;
            }
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        return 1;
    } else if (state->phase == 1) {
        if (SzEffect_IsUse(state->ids[0]) == 1) {
            if (SzEffect_GetStatus(state->ids[0]) == 2) {
                if (state->flags[0] == 1) {
                    i = 0;
                    do {
                        if ((((Source_0025B610 *)arg0)->mask >> (0x15 - i) & 1) == 1) {
                            if (i < 0xB) {
                                Ta_DelUnit(0, i);
                            } else {
                                Ta_DelUnit(1, i - 0xB);
                            }
                        }
                        i++;
                    } while (i < 0x16);
                    state->flags[0] = 0;
                }
            }
            return 1;
        }
        Ta_AllUnitFade(arg0, arg1, arg2, 1, 0, 1);
        TaView_RestoreOriginalView(arg1, 0x10);
        state->timer = 0;
        state->phase++;
    } else {
        state->fade += 0xF;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        if (state->fade == 0x80 && state->timer++ > 0x10 && Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
    }
    return 1;
}

typedef struct State_0025B900 {
    u16 alpha;
    u16 pad2;
    u16 phase;
    u8 events[0x1A];
    s32 handle;
    u8 pad24[0xAC];
    s32 target;
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0025B900;

extern char D_002B86E8[];

s32 Ta_Eff_020(s32 arg0, void *arg1, s32 arg2) {
    s32 data[4];
    State_0025B900 *state = arg1;
    s32 i;
    s32 position;
    u32 pool;
    s32 *command = data;
    s32 y;
    s32 x;
    s32 result;

    extern s32 Ta_IsFinishDestEfc();
    extern s32 SzDuel_GetUnitCtlGoalM();
    extern s32 SzDuel_GetUnitCtlGoalC();
    extern s32 SzDuel_GetUnitCtlRateM();
    extern s32 SzDuel_GetUnitCtlRateC();

    command[0] = 999;
    command[1] = 0;
    command[2] = 0;
    command[3] = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        TaEffect_LoadModule(arg1, 0x11);
        TaEffect_LoadModule(arg1, 0x18);
        TaEffect_LoadModule(arg1, 0x25B);
        Ta_AllUnitFade((void *)arg0, arg1, arg2, -1, 1, 1);
        TaView_ReqFlatCompleteView(0x10);
        state->alpha = 0x80;
        return 1;
    }

    if (state->phase == 0) {
        state->timer++;
        if (state->alpha > 0x3F) {
            state->alpha -= 0xF;
        } else {
            state->alpha = 0x30;
            if (state->timer >= 0x10 && TaEffect_IsLoadModule(arg1) == 1) {
                command[0] = 0x11;
                command[1] = 0;
                command[2] = 0;
                command[3] = 0;
                result = (u8)Ta_Do_Effect(command, arg1);
                state->events[state->count] = result;
                if (result >= 0) {
                    state->count++;
                }
                state->phase++;
            }
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
    } else if (state->phase == 1) {
        if (SzEffect_IsUse(state->events[0]) == 1) {
            return 1;
        }
        pool = 0;
        for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(*(s32 *)(arg0 + 8)); i++) {
            position = Ta_GetUnitOwnerIDFromLstCount(*(s32 *)(arg0 + 8), i);
            x = position >> 8;
            y = position & 0xFF;
            if (SzDuel_GetUnitStatus(x, y, 4) != 0 &&
                (SzDuel_GetUnitKind(x, y) >> 5) == 0) {
                pool = ConvUnitIDtoFlagList(pool, x, y);
            }
        }
        if (Ta_GetUnitNumFrom22bitFlagList(pool) == 0) {
            pool = *(s32 *)(arg0 + 8);
        }
        state->target = Ta_GetRandomUnit(pool);
        TaView_ReqFocusCamera(0, state->target, 100, 180);
        SzDuel_GetUnitLoc(position >> 8, position & 0xFF);
        command[0] = 0x18;
        command[1] = 0;
        command[2] = state->target;
        command[3] = 0;
        result = (u8)Ta_Do_Effect(command, arg1);
        state->events[0] = result;
        if (result >= 0) {
            state->count++;
            state->handle = state->target;
        }
        {
            s32 otherY;
            s32 otherX;
            s32 j;
            s32 other;

            for (j = 0; j < Ta_GetUnitNumFrom22bitFlagList(*(s32 *)(arg0 + 8)); j++) {
                other = Ta_GetUnitOwnerIDFromLstCount(*(s32 *)(arg0 + 8), j);
                if (other != position) {
                    otherX = other >> 8;
                    otherY = other & 0xFF;
                    Ta_UnitFade(otherX, otherY, -1, 7, 3);
                    SzDuel_SetUnitCtlRate(otherX, otherY, -1, 0);
                }
            }
        }
        state->phase++;
    } else if (state->phase == 2) {
        if (SzEffect_IsUse(state->events[0]) != 0 &&
            SzEffect_GetStatus(state->events[0]) == 2 && state->handle >= 0) {
            state->handle = -1;
            command[0] = 0x25B;
            command[1] = 0;
            command[2] = state->target;
            command[3] = 0;
            result = (u8)Ta_Do_Effect(command, arg1);
            state->events[state->count] = result;
            if (result >= 0) {
                state->count++;
            }
            state->phase++;
        }
    } else if (state->phase == 3) {
        if (Ta_IsFinishDestEfc((void *)arg0, arg1, command) != 0) {
            Ta_AllUnitFade((void *)arg0, arg1, arg2, 1, 0, 1);
            TaView_RestoreOriginalView(arg1, 0x10);
            state->timer = 0;
            state->phase++;
        }
    } else {
        {
            s32 c;
            s32 b;
            s32 a;
            s32 d;

            a = SzDuel_GetUnitCtlGoalM(0, 0);
            b = SzDuel_GetUnitCtlGoalC(0, 0);
            c = SzDuel_GetUnitCtlRateM(0, 0);
            d = SzDuel_GetUnitCtlRateC(0, 0);
            func_00199B50(D_002B86E8, a, b, c, d);
        }
        state->alpha += 0xF;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 0x80) {
            if (state->timer++ > 0x10 && Ta_IsFinishFade() == 1) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
    }
    return 1;
}

typedef struct Obj_0025BE50 {
    u16 amount;
    u16 pad2;
    u16 mode;
    u8 pad6[0x102 - 6];
    u16 timer;
} Obj_0025BE50;


s32 Ta_Eff_021(void *arg0, void *arg1, s32 arg2) {
    extern s32 Ta_IsFinishDestEfc();
    s32 work[4];
    s32 *workp;
    Obj_0025BE50 *obj;

    workp = work;
    obj = arg1;
    work[0] = 0x3E7;
    work[1] = 0;
    work[2] = 0;
    work[3] = 0;
    SzDuel_SetWindowDraw(0);

    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        obj->amount = 0x80;
        TaView_ReqStdCompleteView(0x10);
        Ta_AllUnitFade(arg0, arg1, arg2, -1, 1, 1);
        TaEffect_LoadModule(arg1, 0x1F);
        TaEffect_LoadModule(arg1, 0x25B);
        return 1;
    }

    switch (obj->mode) {
    case 0: {
        u16 amount = obj->amount;

        if (amount > 0x3F) {
            amount -= 0xF;
            obj->amount = amount;
        } else {
            amount = 0x30;
            obj->amount = amount;
            if (TaEffect_IsLoadModule(arg1) == 1) {
                Ta_SetEffectDependOnFlagLst(arg0, arg1, workp, 0x1F);
                obj->mode++;
            }
        }
        SzEffect_SetBlackOutForDuel((u8)obj->amount);
        break;
    }
    case 1:
        if (Ta_ManageDestroyEffect(arg0, arg1, workp) != 0) {
            obj->mode++;
        }
        break;
    case 2:
        if (Ta_IsFinishDestEfc(arg0, arg1, workp) != 0) {
            Ta_AllUnitFade(arg0, arg1, arg2, 1, 0, 1);
            TaView_RestoreOriginalView(arg1, 0x10);
            obj->timer = 0;
            obj->mode++;
        }
        break;
    default:
        obj->amount += 0xF;
        if (obj->amount > 0x80) {
            obj->amount = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)obj->amount);
        if (obj->amount == 0x80) {
            u16 oldTimer = obj->timer;
            obj->timer = oldTimer + 1;
            if (oldTimer > 0x10 && Ta_IsFinishFade() == 1) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
        break;
    }
    return 1;
}

typedef struct Obj_0025C0B0 {
    u16 amount;
    u16 pad2;
    u16 mode;
    u8 pad6[0x102 - 6];
    u16 timer;
} Obj_0025C0B0;


s32 Ta_Eff_023(void *arg0, void *arg1, s32 arg2) {
    extern s32 Ta_IsFinishDestEfc();
    s32 work[4];
    s32 *workp;
    Obj_0025C0B0 *obj;

    workp = work;
    obj = arg1;
    work[0] = 0x3E7;
    work[1] = 0;
    work[2] = 0;
    work[3] = 0;
    SzDuel_SetWindowDraw(0);

    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        obj->amount = 0x80;
        TaView_ReqFlatCompleteView(0x10);
        Ta_AllUnitFade(arg0, arg1, arg2, -1, 1, 1);
        TaEffect_LoadModule(arg1, 0x20B);
        TaEffect_LoadModule(arg1, 0x25B);
        return 1;
    }

    switch (obj->mode) {
    case 0: {
        u16 amount;

        obj->timer++;
        amount = obj->amount;
        if (amount > 0x3F) {
            amount -= 0xF;
            obj->amount = amount;
        } else {
            amount = 0x30;
            obj->amount = amount;
            if (obj->timer >= 0x10 && TaEffect_IsLoadModule(arg1) == 1) {
                Ta_SetEffectDependOnFlagLst(arg0, arg1, workp, 0x20B);
                obj->mode++;
            }
        }
        SzEffect_SetBlackOutForDuel((u8)obj->amount);
        break;
    }
    case 1:
        if (Ta_ManageDestroyEffect(arg0, arg1, workp) != 0) {
            obj->mode++;
        }
        break;
    case 2:
        if (Ta_IsFinishDestEfc(arg0, arg1, workp) != 0) {
            Ta_AllUnitFade(arg0, arg1, arg2, 1, 0, 1);
            TaView_RestoreOriginalView(arg1, 0x10);
            obj->timer = 0;
            obj->mode++;
        }
        break;
    default:
        obj->amount += 0xF;
        if (obj->amount > 0x80) {
            obj->amount = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)obj->amount);
        if (obj->amount == 0x80) {
            u16 oldTimer = obj->timer;
            obj->timer = oldTimer + 1;
            if (oldTimer > 0x10 && Ta_IsFinishFade() == 1) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
        break;
    }
    return 1;
}


typedef struct Command_0025C330 {
    s32 kind;
    s32 value;
    s32 position;
    s32 flags;
} Command_0025C330;

typedef struct Owner_0025C330 {
    u8 pad0[12];
    s32 entity;
} Owner_0025C330;

typedef struct State_0025C330 {
    u16 fade;
    u16 count;
    u16 phase;
    u8 primary[10];
    u8 secondary[10];
    u8 pad1A[6];
    s32 positions[10];
    s32 targets[10];
    u8 pad70[0x64];
    u8 allocated;
    u8 padD5[0x2B];
    u8 stage;
    u8 pad101;
    u16 timer;
} State_0025C330;

static inline u8 *primary_0025C330(u8 *bytes) {
    return bytes + 6;
}

s32 Ta_Eff_025(void *arg0, void *arg1, s32 arg2) {
    s32 complete;
    u8 flags;
    Command_0025C330 command;
    s32 randomX;
    s32 entity;
    s32 index;
    s32 cleanupIndex;
    u8 handle;
    u16 oldTimer;
    u8 *entry;
    u8 *cleanupEntry;
    State_0025C330 *state = arg1;
    Command_0025C330 *cmd = &command;

    cmd->kind = 999;
    cmd->value = 0;
    cmd->position = 0;
    cmd->flags = 0;
    complete = 0;
    flags = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(state);
        index = 0;
        entry = (u8 *)state;
        do {
            randomX = (func_0019A5C8() % 7) << 8;
            *(s32 *)(entry + 0x20) = randomX | (func_0019A5C8() % 7);
            index++;
            entry += 4;
        } while (index < 10);
        state->fade = 0x80;
        TaEffect_LoadModule(state, 0x20D);
        TaEffect_LoadModule(state, 0x25B);
        return 1;
    }

    switch (state->stage) {
    case 0:
        if (state->phase > 0) {
            oldTimer = state->timer++;
            if (oldTimer == 0) {
                TaView_ReqStdCompleteView(0x10);
            } else if (state->timer >= 0x10) {
                state->timer = 0;
                state->stage++;
            }
        }
        break;
    case 1:
        if (state->phase < 2) {
            oldTimer = state->timer++;
            if (oldTimer == 0) {
                TaView_ReqRotCamera(0x3C, 0x3FFF);
            } else if (state->timer >= 0x3C) {
                state->timer = 0;
            }
        } else {
            SzDuel_CloseMsgPopup();
            TaView_RestoreOriginalView(state, 0x10);
            state->timer = 0;
            state->stage++;
        }
        break;
    default:
        oldTimer = state->timer++;
        if (oldTimer >= 0x10) {
            flags = 2;
        }
        break;
    }

    switch (state->phase) {
    case 0:
        if (state->fade > 0x30) {
            state->fade -= 15;
        } else {
            state->fade = 0x30;
            if (TaEffect_IsLoadModule(state) == 1) {
                TaView_ReqSkyView();
                state->phase++;
            }
        }
        if (state->fade < 0x30) {
            state->fade = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        break;
    case 1: {
        s32 resolvedPosition;
        u8 *primary;
        u8 *activeEntry;
        s32 x;
        s32 y;
        if ((s32)state->fade % 8 == 0) {
            if (state->count < 10) {
                u8 *scanEntry;
                s32 position;
                s32 scanIndex;
                cmd->kind = 0x20D;
                cmd->value = 0;
                cmd->position = state->positions[state->count];
                cmd->flags = 0;
                handle = Ta_Do_Effect((s32 *)cmd, state);
                state->primary[state->allocated] = handle;
                if ((s32)handle >= 0) {
                    state->allocated++;
                }
                scanIndex = 0;
                scanEntry = (u8 *)state;
                while (scanIndex < state->count) {
                    position = *(s32 *)(scanEntry + 0x20);
                    if (state->positions[(u16)state->count] == position) {
                        *(s32 *)(scanEntry + 0x20) = position | 0x10000;
                    }
                    scanEntry += 4;
                    scanIndex++;
                }
                state->count++;
            }
        }
        index = 0;
        activeEntry = (u8 *)state;
        while (index < state->count) {
            s32 position;
            primary = &state->primary[index];
            if (SzEffect_IsUse(state->primary[index]) == 1 &&
                SzEffect_GetStatus(*primary) == 2) {
                position = *(s32 *)(activeEntry + 0x20);
                if (position >> 16 == 0) {
                    if ((resolvedPosition = SzDuel_GetMapUnitID(position & 0xFF, position >> 8)) >= 0 &&
                        (x = resolvedPosition & 0xFF) > 0) {
                            y = resolvedPosition >> 8;
                            entity = Ta_GetCurrentSide(y, x);
                            if (Ta_IsLDRangeAvility(y, x, 11)) {
                                SzDuel_OpenMsgPopup(0, -120, 80, 270);
                                resolvedPosition = SzDuel_GetUnitLoc(entity, 0);
                                Ta_SetRangeVisual(resolvedPosition & 0xFF, resolvedPosition >> 8, 0,
                                    Ta_IsLDAbl(9, entity), 1, 1, 11);
                            } else if (Ta_IsResistAll(y, x) && entity != ((Owner_0025C330 *)arg0)->entity) {
                                SzDuel_OpenMsgPopup(0, 0, 0, SzDuel_GetMsgName(0x53));
                            } else {
                                cmd->kind = 0x25B;
                                cmd->value = 0;
                                cmd->position = resolvedPosition;
                                cmd->flags = 1;
                                handle = Ta_Do_Effect((s32 *)cmd, state);
                                state->secondary[index] = handle;
                                if ((s32)handle >= 0) {
                                    *(s32 *)(activeEntry + 0x48) = resolvedPosition;
                                }
                            }
                    }
                    *(s32 *)(activeEntry + 0x20) |= 0x10000;
                }
            }
            activeEntry += 4;
            index++;
        }

        cleanupIndex = 0;
        cleanupEntry = (u8 *)state;
        do {
            s32 position;
            primary = &state->primary[cleanupIndex];
            if (SzEffect_IsUse(state->primary[cleanupIndex]) == 0 &&
                SzEffect_IsUse(state->secondary[cleanupIndex]) == 0) {
                position = *(s32 *)(cleanupEntry + 0x48);
                if (position > 0) {
                    Ta_DelUnit(position >> 8, position & 0xFF);
                    *(s32 *)(cleanupEntry + 0x48) = 0;
                }
            }
            if (state->count > 0 && SzEffect_IsUse(*primary) == 0 && SzEffect_IsUse(*primary) == 0) {
                complete++;
            }
            cleanupIndex++;
            cleanupEntry += 4;
        } while (cleanupIndex < 10);

        if (complete >= 10) {
            state->fade = 0x30;
            state->phase++;
        } else {
            u8 *releaseEntry;
            s32 releaseIndex;
            releaseIndex = 10;
            releaseEntry = (u8 *)state + 0x28;
            do {
                s32 position = *(s32 *)(releaseEntry + 0x20);
                if (position > 0) {
                    Ta_DelUnit(position >> 8, position & 0xFF);
                }
                releaseIndex++;
                releaseEntry += 4;
            } while (releaseIndex < 20);
            state->fade++;
        }
        break;
    }
    default:
        state->fade += 15;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        if (state->fade == 0x80) {
            flags |= 1;
        }
        break;
    }
    if (flags == 3) {
        if (SzDuel_GetWindowDisp()) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
}

typedef struct Context_0025C9E0 {
    s32 unk0;
    s32 card;
    u32 mask;
    u32 target;
} Context_0025C9E0;

typedef struct State_0025C9E0 {
    u16 counter;
    u16 card;
    u16 state;
    u8 handle;
    u8 padding[0xFB];
    u16 timer;
} State_0025C9E0;

typedef struct Command_0025C9E0 {
    s32 type;
    s32 flags;
    s32 value;
    s32 unused;
} Command_0025C9E0;


s32 Ta_Eff_026(void *arg0, void *arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitSpellRest();
    Command_0025C9E0 storage;
    s32 *command = (s32 *)&storage;
    Context_0025C9E0 *ctx = arg0;
    State_0025C9E0 *state = arg1;
    s32 i;
    s32 card;
    s32 position;
    s32 owner;

    storage.type = 999;
    storage.flags = 0;
    storage.value = 0;
    storage.unused = 0;

    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        if (ctx->target == -1) {
            SzDuel_CloseMsgPopup();
            return 0;
        }
        SzDuel_SetWindowDraw(0);
        TaView_ReqStdCompleteView(0x10);
        TaEffect_LoadModule(arg1, 0x201);
        TaEffect_LoadModule(arg1, 0x1A);
        TaEffect_LoadModule(arg1, 0x1B);
        return 1;
    }
    if (ctx->target == -1) {
        SzDuel_CloseMsgPopup();
        return 0;
    }
    SzDuel_SetWindowDraw(0);
    switch (state->state) {
    case 0:
        if (TaEffect_IsLoadModule(arg1) == 1) {
            command[0] = 0x1A;
            command[1] = 0;
            command[2] = 0;
            command[3] = 0;
            state->handle = Ta_Do_Effect(command, arg1);
            state->state++;
        }
        break;
    case 1:
    case 3:
        if (SzEffect_IsUse(state->handle) == 0) {
            if (state->state == 3) {
                TaView_RestoreOriginalView(arg1, 0x10);
                state->timer = 0;
            }
            state->state++;
        }
        break;
    case 2:
        if (ctx->target == 0xFFFE) {
            Ta_SetEffectDependOnFlagLst(arg0, arg1, command, 0x1B);
            if (Ta_GetUnitNumFrom22bitFlagList(ctx->mask) == 1) {
                TaView_ReqFocusCamera(0, Ta_GetUnitOwnerIDFromLstCount(ctx->mask, 0), 100, 180);
            }
            state->state++;
        } else {
            command[0] = 0x1B;
            command[1] = 0;
            command[2] = ctx->target;
            command[3] = 0;
            TaView_ReqFocusCamera(0, ctx->target, 100, 180);
            state->handle = Ta_Do_Effect(command, arg1);
            state->state++;
        }
        break;
    case 4:
        state->state++;
        if (ctx->target == 0xFFFE) {
            i = 0;
            do {
                if ((ctx->mask >> (21 - i)) & 1) {
                    if (i < 11) {
                        card = Ta_GetCurrentSide(0, i);
                        if (Ta_IsLDRangeAvility(0, i, 11)) {
                            position = SzDuel_GetUnitLoc(card, 0);
                            Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                                          Ta_IsLDAbl(9, card), 1, 1, 11);
                            SzDuel_OpenMsgPopup(0, -120, 80, 270);
                        } else {
                            card = ctx->target;
                            if (card != Ta_GetCurrentSide(0, i)) {
                                if (SzDuel_GetUnitStatus(0, i, 1)) {
                                    SzDuel_SetUnitStatus(0, i, 1, 0);
                                } else {
                                    SzDuel_SetUnitStatus(0, i, 1, 1);
                                }
                                owner = SzDuel_GetTurnOwner();
                                if (owner == Ta_IsUnitControl(0, i)) {
                                    if (!SzDuel_GetUnitCurseRest(0, i) && !SzDuel_GetUnitSpellRest(0, i)) {
                                        SzDuel_SetUnitStatus(0, i, 0, 0);
                                    }
                                } else {
                                    SzDuel_SetUnitStatus(0, i, 0, 1);
                                }
                            }
                        }
                    } else {
                        card = Ta_GetCurrentSide(1, i - 11);
                        if (Ta_IsLDRangeAvility(1, i - 11, 11)) {
                            position = SzDuel_GetUnitLoc(card, 0);
                            Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                                          Ta_IsLDAbl(9, card), 1, 1, 11);
                            SzDuel_OpenMsgPopup(0, -120, 80, 270);
                        } else {
                            card = ctx->target;
                            if (card != Ta_GetCurrentSide(1, i - 11)) {
                                if (SzDuel_GetUnitStatus(1, i - 11, 1)) {
                                    SzDuel_SetUnitStatus(1, i - 11, 1, 0);
                                } else {
                                    SzDuel_SetUnitStatus(1, i - 11, 1, 1);
                                }
                                owner = SzDuel_GetTurnOwner();
                                if (owner == Ta_IsUnitControl(1, i - 11)) {
                                    if (!SzDuel_GetUnitCurseRest(1, i - 11) && !SzDuel_GetUnitSpellRest(1, i - 11)) {
                                        SzDuel_SetUnitStatus(1, i - 11, 0, 0);
                                    }
                                } else {
                                    SzDuel_SetUnitStatus(1, i - 11, 0, 1);
                                }
                            }
                        }
                    }
                }
                i++;
            } while (i < 22);
            if (state->state > 4) {
                return 1;
            }
            if (state->timer++ > 16) {
                if (SzDuel_GetWindowDisp()) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        } else {
            card = Ta_GetCurrentSide(ctx->target >> 8, ctx->target & 0xFF);
            if (Ta_IsLDRangeAvility(ctx->target >> 8, ctx->target & 0xFF, 11)) {
                position = SzDuel_GetUnitLoc(card, 0);
                Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                              Ta_IsLDAbl(9, card), 1, 1, 11);
                SzDuel_OpenMsgPopup(0, -120, 80, 270);
            } else {
                if (Ta_IsResistAll(ctx->target >> 8, ctx->target & 0xFF) == 1) {
                    state->card = Ta_IsResistAllMaster(ctx->target >> 8, ctx->target & 0xFF);
                    TaView_ReqFocusCamera(0, state->card, 100, 180);
                    command[0] = 0x201;
                    command[1] = 0;
                    command[2] = state->card;
                    command[3] = 0;
                    state->handle = Ta_Do_Effect(command, arg1);
                    state->state = 16;
                } else {
                    card = ctx->card;
                    if (card != Ta_GetCurrentSide(ctx->target >> 8, ctx->target & 0xFF)) {
                        if (SzDuel_GetUnitStatus(ctx->target >> 8, ctx->target & 0xFF, 1)) {
                            SzDuel_SetUnitStatus(ctx->target >> 8, ctx->target & 0xFF, 1, 0);
                        } else {
                            SzDuel_SetUnitStatus(ctx->target >> 8, ctx->target & 0xFF, 1, 1);
                        }
                        if (!SzDuel_GetUnitCurseRest(ctx->target >> 8, ctx->target & 0xFF) &&
                            !SzDuel_GetUnitSpellRest(ctx->target >> 8, ctx->target & 0xFF)) {
                            SzDuel_SetUnitStatus(ctx->target >> 8, ctx->target & 0xFF, 0, 0);
                        }
                    }
                }
            }
        }
        break;
    case 16:
        SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(0x53));
        if (SzEffect_IsUse(state->handle) == 0) {
            if (state->counter++ < 31) {
                SzDuel_CloseMsgPopup();
                TaView_RestoreOriginalView(arg1, 16);
                state->timer = 0;
                state->state++;
            }
        }
        break;
    default:
        if (state->timer++ > 16) {
            SzDuel_CloseMsgPopup();
            if (SzDuel_GetWindowDisp()) {
                SzDuel_SetWindowDraw(1);
            }
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct State_0025D230 {
    u16 alpha;
    u16 unused2;
    u16 phase;
    u8 handles[0xCE];
    u8 count;
    u8 unusedD5[0x2D];
    u16 timer;
} State_0025D230;

typedef struct Mask_0025D230 {
    u8 unused0[8];
    u32 mask;
} Mask_0025D230;

typedef struct Command_0025D230 {
    s32 id;
    s32 x;
    s32 y;
    s32 z;
} Command_0025D230;


s32 Ta_Eff_029_CNG(void *arg0, void *arg1, s32 arg2) {
    s32 i = 0;
    Command_0025D230 data;
    Command_0025D230 *command = &data;
    s32 j;
    State_0025D230 *state = arg1;
    Mask_0025D230 *input = arg0;

    command->id = 999;
    command->x = 0;
    command->y = 0;
    command->z = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        state->alpha = 0x80;
        if (Ta_GetUnitNumFrom22bitFlagList(input->mask) == 1) {
            TaView_ReqFocusCamera(0x10, Ta_GetUnitOwnerIDFromLstCount(input->mask, 0), 100, 180);
        } else {
            TaView_ReqStdCompleteView(0x10);
        }
        Ta_AllUnitFade(arg0, arg1, arg2, -1, 1, 1);
        TaEffect_LoadModule(arg1, 0x211);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (state->alpha > 0x30) {
            state->alpha -= 15;
        } else {
            state->alpha = 0x30;
            if (TaEffect_IsLoadModule(arg1) == 1) {
                SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(0x2E0));
                Ta_SetEffectDependOnFlagLst(arg0, arg1, command, 0x211);
                state->phase++;
            }
        }
        if (state->alpha < 0x30) {
            state->alpha = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        break;
    case 1:
        for (j = 0; j < state->count; j++) {
            if (SzEffect_IsUse(state->handles[j]) == 0) {
                i++;
            }
        }
        if (i >= state->count) {
            SzDuel_CloseMsgPopup();
            i = 0;
            do {
                if ((input->mask >> (21 - i)) & 1) {
                    s32 attackDelta;
                    s32 defenseDelta;
                    if (i < 11) {
                        attackDelta = SzDuel_GetUnitDP(0, i, 0) - SzDuel_GetUnitAP(0, i, 0);
                        defenseDelta = SzDuel_GetUnitAP(0, i, 0) - SzDuel_GetUnitDP(0, i, 0);
                        TaUtil_CalcUnitAP(0, i, 0, attackDelta);
                        TaUtil_CalcUnitDP(0, i, 0, defenseDelta);
                    } else {
                        attackDelta = SzDuel_GetUnitDP(1, i - 11, 0) - SzDuel_GetUnitAP(1, i - 11, 0);
                        defenseDelta = SzDuel_GetUnitAP(1, i - 11, 0) - SzDuel_GetUnitDP(1, i - 11, 0);
                        TaUtil_CalcUnitAP(1, i - 11, 0, attackDelta);
                        TaUtil_CalcUnitDP(1, i - 11, 0, defenseDelta);
                    }
                }
                i++;
            } while (i < 22);
            Ta_AllUnitFade(arg0, arg1, arg2, 1, 0, 1);
            TaView_RestoreOriginalView(arg1, 0x10);
            state->phase++;
        }
        break;
    default:
        state->alpha += 15;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 0x80) {
            if (state->timer++ > 16 && Ta_IsFinishFade() == 1) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
        break;
    }
    return 1;
}

typedef struct Command_0025D640 {
    s32 unk0;
    s32 kind;
    u32 flags;
    u32 values;
} Command_0025D640;

typedef struct State_0025D640 {
    u16 value;
    u16 unk2;
    u16 stage;
    u8 ids[0xCE];
    u8 count;
    u8 padding[0x2D];
    u16 timer;
} State_0025D640;


s32 Ta_Eff_029(void *arg0, void *arg1, s32 arg2) {
    s32 data[4];
    s32 completed;
    s32 *params = data;
    s32 i;
    Command_0025D640 *command = arg0;
    State_0025D640 *state = arg1;

    params[0] = 999;
    params[1] = 0;
    params[2] = 0;
    params[3] = 0;
    completed = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        state->value = 0x80;
        if (Ta_GetUnitNumFrom22bitFlagList(command->flags) == 1) {
            TaView_ReqFocusCamera(0x10, Ta_GetUnitOwnerIDFromLstCount(command->flags, 0), 100, 180);
        } else {
            TaView_ReqStdCompleteView(0x10);
        }
        Ta_AllUnitFade(arg0, arg1, arg2, -1, 1, 1);
        TaEffect_LoadModule(arg1, 0x211);
        return 1;
    }

    switch (state->stage) {
    case 0:
        if (state->value > 0x30) {
            state->value -= 15;
        } else {
            state->value = 0x30;
            if (TaEffect_IsLoadModule(arg1) == 1) {
                SzDuel_OpenMsgPopup(0, -120, 80, 0x106);
                Ta_SetEffectDependOnFlagLst(arg0, arg1, params, 0x211);
                state->stage++;
            }
        }
        if (state->value < 0x30) {
            state->value = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->value);
        break;
    case 1:
        for (i = 0; i < state->count; i++) {
            if (SzEffect_IsUse(state->ids[i]) == 0) {
                completed++;
            }
        }
        if (completed >= state->count) {
            SzDuel_CloseMsgPopup();
            completed = 0;
            do {
                if ((command->flags >> (21 - completed)) & 1) {
                    if (completed < 11) {
                        TaUtil_CalcUnitDP(0, completed, command->values >> 16, command->values & 0xFFFF);
                        if (command->kind == 1) {
                            TaUtil_CalcUnitAP(0, completed, command->values >> 16, command->values & 0xFFFF);
                        }
                    } else {
                        TaUtil_CalcUnitDP(1, completed - 11, command->values >> 16, command->values & 0xFFFF);
                        if (command->kind == 1) {
                            TaUtil_CalcUnitAP(1, completed - 11, command->values >> 16, command->values & 0xFFFF);
                        }
                    }
                }
                completed++;
            } while (completed < 22);
            Ta_AllUnitFade(arg0, arg1, arg2, 1, 0, 1);
            TaView_RestoreOriginalView(arg1, 0x10);
            state->stage++;
        }
        break;
    default:
        state->value += 15;
        if (state->value > 0x80) {
            state->value = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->value);
        if (state->value == 0x80 && state->timer++ > 16 && Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct Input_0025D9D0 {
    s32 unused;
    s32 selection;
    u32 mask;
} Input_0025D9D0;

typedef struct State_0025D9D0 {
    u16 alpha;
    u16 unused;
    u16 step;
    u8 effects[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_0025D9D0;

typedef struct Packet_0025D9D0 {
    s32 type;
    s32 unused;
    s32 position;
    s32 flag;
} Packet_0025D9D0;


s32 Ta_Eff_028(void *arg0, void *arg1, s32 arg2) {
    Packet_0025D9D0 data;
    s32 done;
    Packet_0025D9D0 *packet = &data;
    s32 i;
    s32 j;
    u8 effect;
    Input_0025D9D0 *input = arg0;
    State_0025D9D0 *state = arg1;

    data.type = 999;
    data.unused = 0;
    data.position = 0;
    data.flag = 0;
    done = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(state);
        state->alpha = 0x80;
        TaView_ReqStdCompleteView(0x10);
        TaEffect_LoadModule(state, 0x16);
        TaEffect_LoadModule(state, 0x25B);
        return 1;
    }

    switch (state->step) {
    case 0:
        if (state->alpha > 0x30) {
            state->alpha -= 15;
        } else {
            state->alpha = 0x30;
            if (TaEffect_IsLoadModule(state) == 1) {
                packet->type = 0x16;
                packet->unused = 0;
                packet->position = 0;
                packet->flag = 0;
                effect = Ta_Do_Effect((s32 *)packet, state);
                state->effects[state->count] = effect;
                if (effect >= 0) {
                    state->count++;
                }
                state->step++;
            }
        }
        if (state->alpha < 0x30) {
            state->alpha = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        break;

    case 1: {
        s32 selection;
        s32 y;
        s32 x;
        s32 position;

        if (SzEffect_IsUse(state->effects[0]) == 1) {
            return 1;
        }
        selection = SearchUnitByRange(0, 0, 0, 3, 0x34, 0xE);
        Ta_RemoveObjFromFlagLst2(selection, input->selection);
        if (0 < Ta_GetUnitNumFrom22bitFlagList(selection)) {
            do {
                position = Ta_GetUnitOwnerIDFromLstCount(selection, done);
                x = position >> 8;
                y = position & 0xFF;
                Ta_SetUnitCurseRest(x, y, 0);
                SzDuel_SetUnitSpellRest(x, y, 0);
                TaUtil_CalcUnitAP(x, y, 4, 0);
                TaUtil_CalcUnitDP(x, y, 4, 0);
                done++;
            } while (done < Ta_GetUnitNumFrom22bitFlagList(selection));
        }
        state->step++;
        break;
    }

    case 2:
        i = 0;
        do {
            if (((input->mask >> (21 - i)) & 1) == 1) {
                if (i < 11) {
                    packet->type = 0x25B;
                    packet->unused = 0;
                    packet->position = i;
                    packet->flag = 1;
                    effect = Ta_Do_Effect((s32 *)packet, state);
                    *((u8 *)state + state->count + 6) = effect;
                    if (effect >= 0) {
                        state->count++;
                    }
                } else {
                    packet->type = 0x25B;
                    packet->unused = 0;
                    packet->position = (i - 11) | 0x100;
                    packet->flag = 1;
                    effect = Ta_Do_Effect((s32 *)packet, state);
                    *((u8 *)state + state->count + 6) = effect;
                    if (effect >= 0) {
                        state->count++;
                    }
                }
            }
            i++;
        } while (i < 22);
        state->alpha = 0;
        state->step++;

    case 3:
        for (j = 0; j < state->count; j++) {
            if (SzEffect_IsUse(state->effects[j]) == 0) {
                done++;
            }
        }
        if (done < state->count) {
            return 1;
        }
        i = 0;
        do {
            if ((input->mask >> (21 - i)) & 1) {
                if (i < 11) {
                    Ta_DelUnit(0, i);
                } else {
                    Ta_DelUnit(1, i - 11);
                }
            }
            i++;
        } while (i < 22);
        state->step++;
        TaView_RestoreOriginalView(state, 0x10);
        state->timer = 0;
        break;

    default:
        state->alpha += 15;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 0x80) {
            if (state->timer++ > 16) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
        break;
    }
    return 1;
}

typedef struct State_0025DE70 {
    u16 alpha;
    u16 unk2;
    u16 phase;
    u8 cards[0xCE];
    u8 card_count;
    u8 padD5[0x2D];
    u16 timer;
} State_0025DE70;

typedef struct Context_0025DE70 {
    u8 pad0[8];
    u32 mask;
} Context_0025DE70;

typedef struct Selection_0025DE70 {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
} Selection_0025DE70;


s32 Ta_Eff_030(void *arg0, void *arg1, s32 arg2) {
    s32 count;
    Selection_0025DE70 selection_data;
    Selection_0025DE70 *selection = &selection_data;
    State_0025DE70 *state = arg1;
    Context_0025DE70 *context = arg0;
    extern s32 SzDuel_GetUnitCardNo();

    selection->field0 = 999;
    selection->field4 = 0;
    selection->field8 = 0;
    selection->fieldC = 0;
    count = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        state->alpha = 0x80;
        if (Ta_GetUnitNumFrom22bitFlagList(context->mask) == 1) {
            TaView_ReqFocusCamera(0x10, Ta_GetUnitOwnerIDFromLstCount(context->mask, 0), 0x64, 0xB4);
        } else {
            TaView_ReqStdCompleteView(0x10);
        }
        Ta_AllUnitFade(arg0, arg1, arg2, -1, 1, 1);
        TaEffect_LoadModule(arg1, 0x1E);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if ((s32)state->alpha > 0x3F) {
            state->alpha -= 0xF;
        } else {
            state->alpha = 0x30;
            if (TaEffect_IsLoadModule(arg1) == 1) {
                if ((s32)state->timer++ > 0x10) {
                    Ta_SetEffectDependOnFlagLst(arg0, arg1, selection, 0x1E);
                    state->phase++;
                    state->timer = 0;
                }
            }
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        break;
    case 1: {
        s32 i;

        for (i = 0; i < state->card_count; i++) {
            if (SzEffect_IsUse(state->cards[i]) == 0) {
                count++;
            }
        }
        if (count < state->card_count) {
            return 1;
        }
        count = 0;
        do {
            if ((context->mask >> (0x15 - count)) & 1) {
                if (count < 0xB) {
                    SzDuel_AddDeck(0, SzDuel_GetUnitCardNo(0, count));
                    SzDuel_PackDeck(0);
                    SzDuel_DelUnit(0, count);
                } else {
                    SzDuel_AddDeck(1, SzDuel_GetUnitCardNo(1, count - 0xB));
                    SzDuel_PackDeck(0);
                    SzDuel_DelUnit(1, count - 0xB);
                }
            }
            count++;
        } while (count < 0x16);
        state->phase++;
        break;
    }
    case 2:
        if ((s32)state->timer++ > 0x10) {
            TaView_RestoreOriginalView(arg1, 0x10);
            state->timer = 0;
            Ta_AllUnitFade(arg0, arg1, arg2, 1, 0, 1);
            state->phase++;
        }
        break;
    default:
        state->alpha += 0xF;
        if ((s32)state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 0x80 && (s32)state->timer++ > 0x10 && Ta_IsFinishFade() == 1) {
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct {
    u32 unk0;
    u32 target;
    s32 mask;
    u32 position;
} Command_0025E200;

typedef struct {
    s8 ready : 1;
    s8 reserved : 7;
} Flags_0025E200;

typedef struct {
    u16 alpha;
    u16 unk2;
    u16 phase;
    u8 slots[0x7A];
    Flags_0025E200 flags;
    u8 unk81[0x53];
    u8 count;
    u8 unkD5[0x2D];
    u16 timer;
} State_0025E200;


s32 Ta_Eff_031(void *arg0, void *arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitCtlRateM();
    extern s32 SzDuel_SetUnitCtlGoalM();
    extern s32 Ta_Do_Effect(s32 *, void *);
    s32 request[4];
    s32 *data = request;
    Command_0025E200 *command = arg0;
    State_0025E200 *state = arg1;

    request[0] = 999;
    request[1] = 0;
    request[2] = 0;
    request[3] = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(state);
        state->alpha = 0x80;
        TaEffect_LoadModule(state, 0x213);
        TaEffect_LoadModule(state, 0x214);
        if (Ta_GetUnitNumFrom22bitFlagList(command->mask) == 1) {
            TaView_ReqFocusCamera(0, Ta_GetUnitOwnerIDFromLstCount(command->mask, 0), 100, 180);
        } else {
            TaView_ReqStdCompleteView(0);
        }
        Ta_AllUnitFade(command, state, arg2, -1, 1, 1);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (state->alpha > 0x30) {
            state->alpha -= 15;
        } else {
            state->alpha = 0x30;
            if (state->flags.ready == 0) {
                if (TaEffect_IsLoadModule(state) == 1) {
                    state->flags.ready = 1;
                }
            } else {
                s32 result;
                data[0] = 0x213;
                data[1] = 0;
                data[2] = (u16)command->target;
                data[3] = 0;
                result = Ta_Do_Effect(data, state);
                if (result >= 0) {
                    state->slots[state->count] = result;
                    state->count++;
                    state->phase++;
                } else if ((u32)(result + 2) < 2) {
                    SzDuel_CloseMsgPopup();
                    return 0;
                }
            }
        }
        if (state->alpha < 0x30) {
            state->alpha = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        break;

    case 1:
        if (SzEffect_IsUse(state->slots[state->count - 1]) == 1 &&
            SzEffect_GetStatus(state->slots[state->count - 1]) == 2) {
            if ((command->target >> 16) == 1) {
                SzEffect_SetBusyFlag2(command->target & 0xFFFF, 0);
                SzEffect_SetAnimIntr2((u16)command->target, 0);
                if (SzDuel_GetUnitCtlRateM((command->target & 0xFFFF) >> 8,
                                  command->target & 0xFF) == 0) {
                    SzDuel_SetUnitCtlGoalM((command->target & 0xFFFF) >> 8,
                                  command->target & 0xFF, 0x80);
                    SzDuel_SetUnitCtlRateM((command->target & 0xFFFF) >> 8,
                                  command->target & 0xFF, 1, 0x80);
                }
            }
            SzDuel_MoveUnit((command->target & 0xFFFF) >> 8, command->target & 0xFF,
                          command->position & 0xFF, command->position >> 8);
            state->timer = 0;
            state->phase++;
        }
        break;

    case 2:
        if (state->timer == 0) {
            if (Ta_GetUnitNumFrom22bitFlagList(command->mask) == 1) {
                TaView_ReqFocusCamera(30, Ta_GetUnitOwnerIDFromLstCount(command->mask, 0), 100, 180);
            } else {
                TaView_ReqStdCompleteView(16);
            }
        }
        if (state->timer++ >= 24 &&
            SzEffect_IsUse(state->slots[state->count - 1]) != 1) {
            s32 result;
            data[0] = 0x214;
            data[1] = 0;
            data[2] = (u16)command->target;
            data[3] = 0;
            result = Ta_Do_Effect(data, state);
            if (result >= 0) {
                state->slots[state->count] = result;
                state->count++;
                state->phase++;
            } else if ((u32)(result + 2) < 2) {
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
        break;

    case 3:
        if (SzEffect_IsUse(state->slots[state->count - 1]) != 1) {
            state->phase++;
            TaView_RestoreOriginalView(state, 16);
            Ta_AllUnitFade(command, state, arg2, 1, 0, 1);
        }
        break;

    default:
        state->alpha += 15;
        if (state->alpha > 0x80) {
            state->alpha = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 0x80) {
            if (state->timer++ > 16 && Ta_IsFinishFade() == 1) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
        break;
    }
    return 1;
}

struct jp_6989c_25e710 {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_68cb4_25e710 {
    int fLoad : 1;
    unsigned char bModNum : 5;
    unsigned short wModule[24];
    unsigned char bModCond[24];
};
struct jp_69942_25e710 {
    unsigned short wCount_1;
    unsigned short wCount_2;
    unsigned short wLvl;
    unsigned char eID[24];
    int ePos[24];
    struct jp_68cb4_25e710 eMod;
    unsigned int fObj;
    unsigned int fObj2;
    unsigned char oNum;
    unsigned char unknown_d5[0xb];
    int camDat[8];
    unsigned char bCamLvl;
    unsigned short wCamTime;
    unsigned char unknown_104[0xc];
    int nTasakiEfc[0x10c];
};
extern int func_00255AC0_25e710(struct jp_69942_25e710 *q, int id);
extern void func_00260AF0_b(unsigned char who, int packed, int add, int value);
extern void func_00260740_b(unsigned char who);
extern void func_00260A70_25e710(struct jp_69942_25e710 *Temp, unsigned char b);
extern void func_001DFD50_b(int a, int b, int c, int d);

int Ta_Eff_032(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_6989c_25e710 * eInfo = eInfo_v;
    struct jp_69942_25e710 * Temp = Temp_v;
    int i;
    int j;
    int tCount;
    int nX;
    int nZ;
    int LOC;
    int uID;
    struct jp_6989c_25e710 eCall;
    struct jp_6989c_25e710 *pCall = &eCall;
    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    tCount = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        Temp->wCount_1 = 128;
        if (Ta_GetUnitNumFrom22bitFlagList(eInfo->dwTo) == 1) {
            func_00260AF0_b(0, Ta_GetUnitOwnerIDFromLstCount(eInfo->dwTo, 0), 100, 180);
        } else {
            func_00260740_b(0);
        }
        Ta_AllUnitFade(eInfo, Temp, ID, -1, 1, 1);
        func_00255AC0_25e710(Temp, 531);
        func_00255AC0_25e710(Temp, 532);
        return 1;
    }
    switch (Temp->wLvl) {
    case 0:
        if (Temp->wCount_1 > 48) {
            Temp->wCount_1 -= 15;
        } else {
            Temp->wCount_1 = 48;
            if (TaEffect_IsLoadModule(Temp) == 1) {
                Ta_SetEffectDependOnFlagLst(eInfo, Temp, pCall, 531);
                Temp->wLvl++;
            }
        }
        if (Temp->wCount_1 < 48) {
            Temp->wCount_1 = 48;
        }
        SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
        break;
    case 1:
        for (i = 0; i < Temp->oNum; i++) {
            if (SzEffect_IsUse(Temp->eID[i]) == 0) {
                tCount++;
            }
        }
        if (tCount < Temp->oNum) {
            return 1;
        }
        for (i = 0; i < Temp->oNum; i++) {
            if (Temp->ePos[i] >= 0) {
                LOC = SzDuel_GetUnitLoc(Temp->ePos[i] >> 8, Temp->ePos[i] & 0xFF);
                nX = LOC >> 8;
                nZ = LOC & 0xFF;
                if ((uID = SzDuel_GetMapUnitID(nX, nZ)) < 0) {
                    func_001DFD50_b(Temp->ePos[i] >> 8, Temp->ePos[i] & 0xFF, nX, nZ);
                } else if (uID & 0xFF) {
                    if (Ta_IsLDRangeAvilityWithLocation(uID >> 8, uID & 0xFF, nX, nZ, 11) == 0) {
                        Ta_SwapUnit(Temp->ePos[i] >> 8, Temp->ePos[i] & 0xFF, uID >> 8, uID & 0xFF);
                        for (j = 0; j < Temp->oNum; j++) {
                            if (uID == Temp->ePos[j]) {
                                Temp->ePos[j] = -1;
                            }
                        }
                    }
                }
            }
        }
        Ta_SetEffectDependOnFlagLst(eInfo, Temp, pCall, 532);
        Temp->wLvl++;
        break;
    case 2:
        if (Temp->wCamTime == 0) {
            if (Ta_GetUnitNumFrom22bitFlagList(eInfo->dwTo) == 1) {
                func_00260AF0_b(30, Ta_GetUnitOwnerIDFromLstCount(eInfo->dwTo, 0), 100, 180);
            } else {
                func_00260740_b(16);
            }
        }
        if (Temp->wCamTime++ >= 24) {
            for (i = 0; i < Temp->oNum; i++) {
                if (SzEffect_IsUse(Temp->eID[i]) == 0) {
                    tCount++;
                }
            }
            if (tCount < Temp->oNum) {
                return 1;
            }
            Temp->wLvl++;
            func_00260A70_25e710(Temp, 16);
            Ta_AllUnitFade(eInfo, Temp, ID, 1, 0, 1);
        }
        break;
    default:
        Temp->wCount_1 += 15;
        if (Temp->wCount_1 > 128) {
            Temp->wCount_1 = 128;
        }
        SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
        if (Temp->wCount_1 == 128) {
            if (Temp->wCamTime++ > 16) {
                if (Ta_IsFinishFade() == 1) {
                    if (SzDuel_GetWindowDisp() != 0) {
                        SzDuel_SetWindowDraw(1);
                    }
                    SzDuel_CloseMsgPopup();
                    return 0;
                }
            }
        }
        break;
    }
    return 1;
}

void Ta_SwapUnit(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;

    temp_v0 = Ta_SearchMoveTemp();
    if (temp_v0 >= 0) {
        temp_s0 = SzDuel_GetUnitLoc(arg0, arg1);
        temp_s1 = SzDuel_GetUnitLoc(arg2, arg3);
        SzDuel_MoveUnit(arg0, arg1, temp_v0 & 0xFF, temp_v0 >> 8);
        SzDuel_MoveUnit(arg2, arg3, temp_s0 & 0xFF, temp_s0 >> 8);
        SzDuel_MoveUnit(arg0, arg1, temp_s1 & 0xFF, temp_s1 >> 8);
    }
}

s32 Ta_SearchMoveTemp(void) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    do {
        var_s1 = 0;
        do {
            if (SzDuel_GetMapUnitID(var_s0, var_s1) < 0) {
                return (var_s1 << 8) | var_s0;
            }
            var_s1 += 1;
        } while (var_s1 < 7);
        var_s0 += 1;
    } while (var_s0 < 7);
    return -1;
}
