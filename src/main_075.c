#include "common.h"

typedef struct {
    s32 unk0;
    s32 index1;
    s32 index2;
    s32 value;
} Context_0025ED20;

typedef struct {
    s32 unk0;
    u16 count;
    u8 handle;
    u8 pad;
} State_0025ED20;

/* Effect script 034, step `ID`: its camera, fades and effect module; it changes summon power. */
s32 Ta_Eff_034(void *eInfo, void *Temp, s32 ID) {
    s32 requestData[4];
    s32 *request = requestData;
    Context_0025ED20 *context = eInfo;
    State_0025ED20 *state = Temp;

    requestData[0] = 0x3E7;
    requestData[1] = 0;
    requestData[2] = 0;
    requestData[3] = 0;

    if (ID >= 0) {
        InitEffectTemp(state);
        TaEffect_LoadModule(state, 0x216);
        return 1;
    }
    if (TaEffect_IsLoadModule(state) == 1) {
        if (state->count == 0) {
            request[0] = 0x216;
            request[1] = 0;
            request[2] = 0;
            request[3] = context->value;
            state->handle = Ta_Do_Effect(request, state);
            state->count++;
        } else {
            if (SzEffect_IsUse(state->handle) == 1) {
                return 1;
            }
            SzDuel_CalcSummonPower(context->index1, 4, 0);
            SzDuel_CalcSummonPower(context->index2, 0, context->value);
            SzDuel_CloseMsgPopup();
            return 0;
        }
    }
    return 1;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 index;
} Context_0025EE40;

typedef struct {
    s32 unk0;
    u16 count;
    u8 handle;
    u8 pad;
} State_0025EE40;

/* Effect script 033, step `ID`: its camera, fades and effect module. */
s32 Ta_Eff_033(void *eInfo, void *Temp, s32 ID) {
    s32 requestData[4];
    s32 *request = requestData;
    Context_0025EE40 *context = eInfo;
    State_0025EE40 *state = Temp;

    requestData[0] = 0x3E7;
    requestData[1] = 0;
    requestData[2] = 0;
    requestData[3] = 0;

    if (ID >= 0) {
        InitEffectTemp(state);
        TaEffect_LoadModule(state, 0x215);
        return 1;
    }
    if (TaEffect_IsLoadModule(state) == 1) {
        if (state->count == 0) {
            request[0] = 0x215;
            request[1] = 0;
            request[2] = 0;
            request[3] = 0;
            state->handle = Ta_Do_Effect(request, state);
            state->count++;
        } else {
            if (SzEffect_IsUse(state->handle) == 1) {
                return 1;
            }
            SzDuel_SetHandPhase(context->index, 1);
            SzDuel_CloseMsgPopup();
            return 0;
        }
    }
    return 1;
}

typedef struct State_0025EF40 {
    u8 pad0[4];
    u16 count;
    u8 cards[0x16];
    union {
        s32 flags[0x2E];
        struct {
            s32 first;
            s32 following[0x2D];
        } shifted;
    } data;
    u8 index;
    u8 padD5[0x2B];
    u8 initialized;
    u8 pad101;
    u16 timer;
} State_0025EF40;

/* Effect script 035, step `ID`: its camera, fades and effect module; it destroys units, changes life points, moves
   units, changes the field. */
s32 Ta_Eff_035(s32 arg0, void *arg1, s32 arg2) {
    extern void TaEffect_LoadModule(void *, s32);
    extern void TaView_ReqStdCompleteView(s32);
    extern void TaView_RestoreOriginalView(void *, s32);
    s32 command[4];
    s32 *params = command;
    s32 i;
    s32 pending;
    s32 old;
    s32 high;
    State_0025EF40 *state = arg1;

    command[0] = 999;
    command[1] = 0;
    command[2] = 0;
    command[3] = 0;
    SzDuel_SetWindowDraw(0);
    if (arg2 >= 0) {
        InitEffectTemp(arg1);
        TaEffect_LoadModule(arg1, 0x23);
        TaView_ReqStdCompleteView(0x10);
        return 1;
    }
    switch (state->count) {
    case 0:
        if (TaEffect_IsLoadModule(arg1) == 1) {
            params[0] = 0x23;
            params[1] = 0;
            params[2] = 0;
            params[3] = 0;
            state->cards[state->index] = Ta_Do_Effect(params, arg1);
            state->data.shifted.following[state->index] = 0;
            state->index++;
            state->count++;
        }
        break;
    default:
        if (SzEffect_IsUse(state->cards[state->index - 1]) == 1) {
            if (SzEffect_GetStatus(state->cards[0]) == 2) {
                if (state->data.flags[1] == 0) {
                    s32 x;
                    s32 y;
                    s32 player;
                    s32 slot;
                    s32 low;
                    s32 location;

                    Ta_InitMazePiece();
                    i = 0;
                    do {
                        x = func_0019A5C8() % 7;
                        y = func_0019A5C8() % 7;
                        if (func_0019A5C8() % 2 == 0) player = 0; else player = 1;
                        slot = func_0019A5C8() % 10 + 1;
                        location = SzDuel_GetMapUnitID(x, y);
                        if (location >= 0) {
                            high = location >> 8;
                            low = location & 0xFF;
                            if (Ta_IsLDRangeAvilityWithLocation(high, low, x, y, 0xB) == 0 && low > 0) {
                                if ((pending = Ta_GetStackMapPiece()) >= 0) {
                                    old = SzDuel_GetUnitLoc(player, slot);
                                    SzDuel_MoveUnit(player, slot, pending & 0xFF, pending >> 8);
                                    SzDuel_MoveUnit(high, low, old & 0xFF, old >> 8);
                                    SzDuel_MoveUnit(player, slot, x, y);
                                }
                            }
                        } else {
                            SzDuel_MoveUnit(player, slot, x, y);
                        }
                        i++;
                    } while (i < 100);
                    state->data.flags[state->index] = 1;
                }
            }
            return 1;
        }
        if (state->initialized == 0) {
            state->initialized++;
            TaView_RestoreOriginalView(arg1, 0x10);
        } else {
            if (state->timer++ > 0x10) {
                if (SzDuel_GetWindowDisp() != 0) {
                    SzDuel_SetWindowDraw(1);
                }
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
        return 1;
    }
    return 1;
}

/* The square of the unit being stacked on. */
s32 Ta_GetStackMapPiece(void) {
    s32 row;
    s32 column;
    s32 result;

    for (row = 0; row < 7; row++) {
        for (column = 0; column < 7; column++) {
            result = SzDuel_GetMapUnitID(row, column);
            if (result < 0) {
                return result;
            }
        }
    }
    return -1;
}

/* Puts the labyrinth back on the board's labyrinth squares. */
void Ta_InitMazePiece(void) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = 0;
    do {
        do {
            if (SzDuel_GetField(var_s0, var_s1) == 8) {
                SzDuel_SetField(var_s0, var_s1, 7);
            }
            var_s1 += 1;
        } while (var_s1 < 7);
        var_s0 += 1;
        var_s1 = 0;
    } while (var_s0 < 7);
}

/* Whether an effect script's animation has finished. */
s32 Ta_IsFinishEffect(void *Temp) {
    s32 i;

    for (i = 0; i < ((u8 *)Temp)[0xD4]; i++) {
        if (SzEffect_IsUse(((u8 *)((u32)Temp + i))[6]) != 0) {
            return -1;
        }
    }
    return 1;
}

typedef struct State_0025F400 {
    u16 unknown0;
    u16 timer;
    u16 unknown4;
    u8 ids[0x1A];
    s32 entries[0x2D];
    u8 count;
} State_0025F400;

typedef struct Source_0025F400 {
    u8 padding[8];
    s32 mask;
} Source_0025F400;

typedef struct Command_0025F400 {
    s32 kind;
    s32 flags;
    s32 position;
    s32 extra;
} Command_0025F400;


/* Runs the destroy animation of an effect's targets, then calls `pCall`. */
s32 Ta_ManageDestroyEffect(void *eInfo, void *Temp, void *pCall) {
    s32 i;
    u32 mask;
    Source_0025F400 *source = eInfo;
    State_0025F400 *state = Temp;
    Command_0025F400 *command = pCall;
    u16 timer;

    mask = 0;
    for (i = 0; i < state->count; i++) {
        if (SzEffect_IsUse(state->ids[i]) != 0 &&
            SzEffect_GetStatus(state->ids[i]) == 2 &&
            state->entries[i] >= 0) {
            state->entries[i] = -1;
            state->timer = 1;
        }
    }
    timer = state->timer;
    if (timer > 0) {
        state->timer = timer + 1;
        if (timer > 0x10) {
            s32 position;
            u8 id;
            s32 final_y;
            s32 final_x;
            s32 j;

            for (i = 0; i < Ta_GetUnitNumFrom22bitFlagList(source->mask); i++) {
                s32 value = Ta_GetUnitOwnerIDFromLstCount(source->mask, i);
                s32 y;
                s32 x;

                x = value >> 8;
                y = value & 0xFF;

                if (SzDuel_GetUnitStatus(x, y, 4) != 0 &&
                    (SzDuel_GetUnitKind(x, y) >> 5) == 0) {
                    mask = ConvUnitIDtoFlagList(mask, x, y);
                }
            }
            if (Ta_GetUnitNumFrom22bitFlagList(mask) == 0) {
                mask = source->mask;
            }
            position = Ta_GetRandomUnit(mask);
            SzDuel_GetUnitLoc(position >> 8, position & 0xFF);
            command->kind = 0x25B;
            command->flags = 0;
            command->position = position;
            command->extra = 0;
            id = Ta_Do_Effect(command, state);
            state->ids[state->count] = id;
            if (id >= 0) {
                state->count++;
            }
            TaView_ReqFocusCamera(0, position, 0x64, 0xB4);
            for (j = 0; j < Ta_GetUnitNumFrom22bitFlagList(source->mask); j++) {
                s32 value = Ta_GetUnitOwnerIDFromLstCount(source->mask, j);

                if (value != position) {
                    final_x = value >> 8;
                    final_y = value & 0xFF;

                    Ta_UnitFade(final_x, final_y, -1, 7, 3);
                    SzDuel_SetUnitCtlRate(final_x, final_y, -1, 0);
                }
            }
            state->timer = 0;
            return 1;
        }
    }
    return 0;
}


typedef struct {
    u8 pad[8];
    u32 flags;
} Flags_0025F670;

/* Whether the destroy animation has finished (then the units are removed). */
s32 Ta_IsFinishDestEfc(void *eInfo, void *Temp) {
    s32 var_s1;

    if (Ta_IsFinishEffect(Temp) == 1) {
        var_s1 = 0;
        do {
            if (((((Flags_0025F670 *)eInfo)->flags >> (0x15 - var_s1)) & 1) == 1) {
                if (var_s1 < 0xB) {
                    Ta_DelUnit(0, var_s1);
                } else {
                    Ta_DelUnit(1, var_s1 - 0xB);
                }
            }
            var_s1 += 1;
        } while (var_s1 < 0x16);
        return 1;
    }
    return 0;
}


typedef struct Source_0025F720 {
    s32 pad[2];
    s32 handle;
} Source_0025F720;
typedef struct Request_0025F720 {
    s32 type, zero, value, flag;
} Request_0025F720;
typedef struct Result_0025F720 {
    u8 pad[6];
    u8 status[26];
    s32 values[45];
    u8 count;
} Result_0025F720;

/* Starts effect animation `eNO` on every unit of an effect's target list. */
void Ta_SetEffectDependOnFlagLst(void *eInfo, void *Temp, void *pCall, s32 eNO) {
    s32 index;
    s32 count;
    s32 value;
    s64 flag;
    u8 result;
    Source_0025F720 *src = eInfo;
    Result_0025F720 *dst = Temp;
    Request_0025F720 *req = pCall;

    count = Ta_GetUnitNumFrom22bitFlagList(src->handle);
    for (index = 0; index < count; index++) {
        value = Ta_GetUnitOwnerIDFromLstCount(src->handle, index);
        req->type = eNO;
        req->zero = 0;
        req->value = value;
        if (eNO == 0x25B) {
            flag = 1;
        } else {
            flag = 0;
        }
        req->flag = flag;
        result = Ta_Do_Effect(req, dst);
        dst->status[dst->count] = result;
        if ((s32)result >= 0) {
            dst->values[dst->count] = value;
            dst->count++;
        }
    }
}

typedef struct Source_0025F820 {
    u8 pad[0xC];
    u32 flags;
} Source_0025F820;

typedef struct Results_0025F820 {
    u8 pad[6];
    u8 results[0x1A];
    s32 slots[45];
    u8 count;
} Results_0025F820;

typedef struct Request_0025F820 {
    s32 id;
    s32 mode;
    s32 slot;
    u32 special;
} Request_0025F820;


/* Starts effect animation `eNO` on the effect's targets (second layout). */
void Ta_SetEffectDependOnFlagLst2(void *eInfo, void *Temp, void *pCall, s32 eNO) {
    Source_0025F820 *source = eInfo;
    Results_0025F820 *results = Temp;
    Request_0025F820 *request = pCall;
    s32 special;
    s32 i;

    i = 0;
    do {
        special = 1;
        if (((source->flags >> (0x15 - i)) & 1) == 1) {
            if (i < 0xB) {
                request->id = eNO;
                request->mode = 0;
                request->slot = i;
                if (eNO == 0x25B) {
                    special = 1;
                } else {
                    special = 0;
                }
                request->special = special;
                if ((results->results[results->count] = Ta_Do_Effect(request, results)) >= 0) {
                    results->slots[results->count] = i;
                    results->count++;
                }
            } else {
                request->id = eNO;
                request->mode = 0;
                request->slot = (i - 0xB) | 0x100;
                if (eNO == 0x25B) {
                    special = 1;
                } else {
                    special = 0;
                }
                request->special = special;
                if ((results->results[results->count] = Ta_Do_Effect(request, results)) >= 0) {
                    results->slots[results->count] = ((u32)i - 0xB) | 0x100;
                    results->count++;
                }
            }
        }
        i++;
    } while (i < 0x16);
}

typedef struct {
    u32 unused;
    u32 flags;
} Source_0025F990;

typedef struct {
    u8 unused[6];
    u8 results[26];
    s32 slots[45];
    u8 count;
} Output_0025F990;

typedef struct {
    s32 id;
    s32 unused;
    s32 slot;
    u32 enabled;
} Request_0025F990;


/* Starts effect animation `eNO` on the effect's targets (third layout). */
void Ta_SetEffectDependOnFlagLst3(void *eInfo, void *Temp, void *pCall, s32 eNO) {
    Source_0025F990 *source = eInfo;
    Output_0025F990 *output = Temp;
    Request_0025F990 *request = pCall;
    s32 enabled;
    s32 i;

    i = 0;
    do {
        enabled = 1;
        if (((source->flags >> (21 - i)) & 1) == 1) {
            if (i < 11) {
                request->id = eNO;
                request->unused = 0;
                request->slot = i;
                if (eNO == 0x25B) {
                    enabled = 1;
                } else {
                    enabled = 0;
                }
                request->enabled = enabled;
                if ((output->results[output->count] = Ta_Do_Effect(request, output)) >= 0) {
                    output->slots[output->count] = i;
                    output->count++;
                }
            } else {
                request->id = eNO;
                request->unused = 0;
                request->slot = (i - 11) | 0x100;
                if (eNO == 0x25B) {
                    enabled = 1;
                } else {
                    enabled = 0;
                }
                request->enabled = enabled;
                if ((output->results[output->count] = Ta_Do_Effect(request, output)) >= 0) {
                    output->slots[output->count] = ((u32)i - 11) | 0x100;
                    output->count++;
                }
            }
        }
        i++;
    } while (i < 22);
}

/* Changes side `nSide`'s life points by effect `Efc` in `Mode` during an effect script. */
void Ta_CalcLPinEffectSeq(s32 nSide, s32 Mode, s32 Efc) {
    switch (Mode) {
    case 0:
        Efc = Ta_GetLPRevByNaturalEffect(0x2B, Efc);
        SzDuel_CalcLP(nSide, 0, Efc);
        break;
    case 1:
        SzDuel_CalcLP(nSide, 1, Ta_GetLPRevByNaturalEffect(0x2C, Efc));
        break;
    case 2:
        SzDuel_CalcLP(nSide, 0, Ta_GetLPRevByNaturalEffect(0x2B, SzDuel_GetLP(nSide)));
        break;
    case 3:
        SzDuel_CalcLP(nSide, 1, Ta_GetLPRevByNaturalEffect(0x2C, SzDuel_GetLP(nSide)));
        break;
    case 4:
        if (SzDuel_GetLP(nSide) < Efc) {
            SzDuel_CalcLP(nSide, 4, Efc);
        }
        break;
    }
}

typedef struct Object_0025FC30 {
    u8 pad00[0xCC];
    u32 mask;
} Object_0025FC30;

/* Fades every unit of a target list in or out (second form). */
void Ta_AllUnitFade2(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern s32 SzDuel_GetUnitCtlGoalM();
    Object_0025FC30 *object = arg1;
    s32 i = 0;

    do {
        if (arg3 < 0) {
            if (i < 11) {
                if (SzDuel_GetUnitCtlGoalM(0, i) > 0) {
                    Ta_UnitFade(0, i, arg3, arg4, arg5);
                    object->mask = ConvUnitIDtoFlagList(object->mask, 0, i);
                }
            } else {
                if (SzDuel_GetUnitCtlGoalM(1, i - 11) > 0) {
                    Ta_UnitFade(1, i - 11, arg3, arg4, arg5);
                    object->mask = ConvUnitIDtoFlagList(object->mask, 1, i - 11);
                }
            }
        } else if (((object->mask >> (21 - i)) & 1) == 1) {
            if (i < 11) {
                Ta_UnitFade(0, i, arg3, arg4, arg5);
            } else {
                Ta_UnitFade(1, i - 11, arg3, arg4, arg5);
            }
        }
        i++;
    } while (i < 22);
}

/* Whether every unit fade has finished (then restores the normal speeds). */
s32 Ta_IsFinishFade(void) {
    s32 row;
    s32 col;
    s32 total;
    s32 done;
    s32 cell;
    s32 kind;
    extern s32 SzDuel_GetUnitCtlRateC();
    extern s32 SzDuel_GetUnitCtlGoalC();
    extern s32 SzDuel_GetUnitCtlRateM();
    extern s32 SzDuel_GetUnitCtlGoalM();

    total = 0;
    done = 0;
    for (row = 0; row < 7; row++) {
        for (col = 0; col < 7; col++) {
            cell = SzDuel_GetMapUnitID(row, col);
            if (cell >= 0) {
                total++;
                if (SzDuel_GetUnitCtlRateC(cell >> 8, cell & 0xFF) == SzDuel_GetUnitCtlGoalC(cell >> 8, cell & 0xFF)) {
                    if ((SzDuel_GetUnitStatus(cell >> 8, cell & 0xFF, 4) != 0 || (cell & 0xFF) == 0) && (cell & 0xFF) < 6) {
                        kind = SzDuel_GetUnitCtlRateM(cell >> 8, cell & 0xFF);
                        if (kind == 0 || kind == 0x80) {
                            if (SzDuel_GetUnitCtlGoalM(cell >> 8, cell & 0xFF) == 0x80) {
                                TaEff_RestoreStdRate(cell >> 8, cell & 0xFF);
                            }
                            done++;
                        }
                    } else {
                        if (SzDuel_GetUnitCtlGoalC(cell >> 8, cell & 0xFF) == 0x80) {
                            TaEff_RestoreStdRate(cell >> 8, cell & 0xFF);
                        }
                        done++;
                    }
                }
            }
        }
    }
    if (total == done) {
        return 1;
    }
    return 0;
}

/* Puts the normal animation speeds back after an effect. */
void TaEff_RestoreStdRate(s32 nSide, s32 nID) {
    extern s32 SzDuel_SetUnitCtlGoalM();
    extern s32 SzDuel_SetUnitCtlGoalC();

    SzDuel_SetUnitCtlModeC(nSide, nID, 1);
    if (SzDuel_GetUnitStatus(nSide, nID, 4) != 0 || nID == 0) {
        SzDuel_SetUnitCtlModeM(nSide, nID, 7);
        SzDuel_SetUnitCtlGoalM(nSide, nID, 0x80);
        SzDuel_SetUnitCtlRateM(nSide, nID, 1, 0x80);
    } else {
        SzDuel_SetUnitCtlModeM(nSide, nID, 7);
        SzDuel_SetUnitCtlGoalM(nSide, nID, 0x80);
        SzDuel_SetUnitCtlRateM(nSide, nID, 0, 0);
    }
    SzDuel_SetUnitCtlGoalC(nSide, nID, 0x80);
    SzDuel_SetUnitCtlRateC(nSide, nID, 1, 0x80);
}

typedef struct {
    u8 pad00[8];
    u32 bits;
} Owner_00260020;

typedef struct {
    u8 pad00[0xCC];
    u32 bits;
} Field_00260020;


/* Fades every unit of a target list in or out. */
void Ta_AllUnitFade(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Owner_00260020 *owner = arg0;
    Field_00260020 *field = arg1;
    s32 i;
    extern s32 SzDuel_GetUnitCtlGoalC();
    extern s32 SzDuel_GetUnitCtlGoalM();

    for (i = 0; i < 22; i++) {
        if (((owner->bits >> (21 - i)) & 1) == 1) {
            if (i < 11) {
                SzEffect_SetBusyFlag2(i, arg4);
            } else {
                SzEffect_SetBusyFlag2((i - 11) | 0x100, arg4);
            }
        } else if (arg3 < 0) {
            if (i < 11) {
                if (SzDuel_GetUnitCtlGoalM(0, i) > 0 && SzDuel_GetUnitCtlGoalC(0, i) > 0) {
                    Ta_UnitFade(0, i, arg3, arg5, 1);
                    field->bits = ConvUnitIDtoFlagList(field->bits, 0, i);
                }
            } else if (SzDuel_GetUnitCtlGoalM(1, i - 11) > 0 && SzDuel_GetUnitCtlGoalC(1, i - 11) > 0) {
                Ta_UnitFade(1, i - 11, arg3, arg5, 1);
                field->bits = ConvUnitIDtoFlagList(field->bits, 1, i - 11);
            }
        } else if (((field->bits >> (21 - i)) & 1) == 1) {
            if (i < 11) {
                Ta_UnitFade(0, i, arg3, arg5, 1);
            } else {
                Ta_UnitFade(1, i - 11, arg3, arg5, 1);
            }
        }
    }
}


typedef struct State_00260200 {
    u32 unknown;
    u16 phase;
    u8 handles[0xCE];
    u8 index;
} State_00260200;

/* Effect script ETC, step `ID`: its camera, fades and effect module. */
s32 Ta_Eff_ETC(void *eInfo, void *Temp, s32 ID) {
    s32 request[4];
    s32 *p = request;
    State_00260200 *state = Temp;

    request[0] = 0x3E7;
    request[1] = 0;
    request[2] = 0;
    request[3] = 0;
    if (ID >= 0) {
        InitEffectTemp(Temp);
        TaEffect_LoadModule(Temp, 0x201);
    } else {
        switch (state->phase) {
        case 0:
            if (TaEffect_IsLoadModule(Temp) == 1) {
                state->phase++;
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x104);
                p[0] = 0x201;
                p[1] = 0;
                p[2] = *(s32 *)((u8 *)eInfo + 8);
                p[3] = 0;
                state->handles[state->index] = Ta_Do_Effect(p, Temp);
            }
            break;
        default:
            if (SzEffect_IsUse(state->handles[0]) == 0) {
                SzDuel_CloseMsgPopup();
                return 0;
            }
            break;
        }
    }
    return 1;
}

typedef struct {
    u8 padding[8];
    s32 id;
    u32 duration;
} Config_00260320;

typedef struct {
    u16 ticks;
    u16 padding2;
    u16 phase;
    u8 padding6[0xFC];
    u16 fade;
} State_00260320;


/* Effect script WAIT, step `ID`: its camera, fades and effect module. */
s32 Ta_Eff_WAIT(void *eInfo, void *Temp, s32 ID) {
    State_00260320 *state = Temp;
    Config_00260320 *config = eInfo;
    s32 id;
    u16 fade;

    if (config->id != 0xFFFF) {
        SzDuel_SetWindowDraw(0);
    }
    if (ID >= 0) {
        InitEffectTemp(state);
        id = config->id;
        if (id != 0xFFFF) {
            TaView_ReqFocusCamera(0, id, 0x12C, 0x12C);
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x10E);
        }
        state->ticks++;
    } else {
        switch (state->phase) {
        case 0:
            if (state->ticks++ <= config->duration) {
                return 1;
            }
            SzDuel_CloseMsgPopup();
            if (config->id != 0xFFFF) {
                TaView_RestoreOriginalView(state, 0x10);
            }
            state->phase++;
            break;
        default:
            if (config->id != 0xFFFF) {
                fade = state->fade;
                state->fade = fade + 1;
                if (fade > 0x10) {
                    if (SzDuel_GetWindowDisp() != 0) {
                        SzDuel_SetWindowDraw(1);
                    }
                    SzDuel_CloseMsgPopup();
                    return 0;
                }
            } else {
                SzDuel_CloseMsgPopup();
                return 0;
            }
            break;
        }
    }
    return 1;
}

/* Highlights the squares of range `nRangeMode` around (nX, nZ) (`sKey` picks which). */
void Ta_SetRangeVisual(s32 nX, s32 nZ, s32 nAlphaMode, s32 fExtend, s32 fInit, s32 nRangeMode, s32 sKey) {
    u8 colorData[4];
    s32 y;
    s32 yMax;
    s32 yMin;
    u8 *color = colorData;
    s32 xMax;
    s32 x;
    s32 i;

    if (sKey > 0) {
        switch (sKey) {
        case 0x10:
            color[2] = 0;
            color[1] = 0xFF;
            color[0] = 0;
            color[3] = 0x80;
            break;
        case 0xF:
            color[2] = 0xFF;
            color[1] = 0;
            color[0] = 0x80;
            color[3] = 0x80;
            break;
        case 0xD:
            color[2] = 0;
            color[1] = 0x80;
            color[0] = 0xFF;
            color[3] = 0x80;
            break;
        case 0xB:
            color[2] = 0;
            color[1] = 0xFF;
            color[0] = 0xFF;
            color[3] = 0x80;
            break;
        default:
            color[2] = 0xFF;
            color[1] = 0xFF;
            color[0] = 0xFF;
            color[3] = 0x80;
            break;
        }
    } else {
        color[2] = 0;
        color[1] = 0;
        color[0] = 0;
        color[3] = 0xFF;
    }
    if (nRangeMode == 0x12) {
        i = 0;
        do {
            SzDuel_SetMapColor(i, nZ, nAlphaMode, (s32) color, fInit);
            SzDuel_SetMapColor(nX, i, nAlphaMode, (s32) color, fInit);
            i++;
        } while (i < 7);
    } else {
        x = GetCap(0, nX - (fExtend == 1 ? 2 : 1));
        if (nX + (fExtend == 1 ? 2 : 1) >= 7) {
            xMax = 6;
        } else {
            xMax = nX + (fExtend == 1 ? 2 : 1);
        }
        yMin = GetCap(0, nZ - (fExtend == 1 ? 2 : 1));
        if (nZ + (fExtend == 1 ? 2 : 1) >= 7) {
            yMax = 6;
        } else {
            yMax = nZ + (fExtend == 1 ? 2 : 1);
        }
        for (; x <= xMax; x++) {
            for (y = yMin; y <= yMax; y++) {
                SzDuel_SetMapColor(x, y, nAlphaMode, (s32) color, fInit);
            }
        }
    }
}

/* Moves the camera to the standard full-board view over `nSpeed` frames. */
void TaView_ReqStdCompleteView(s32 nSpeed) {
    s32 sp20[4];
    s32 sp30[4];
    s32 sp40[4];

    SzView_FreeRequest(0, 0);
    SzDuel_CalcUnitPos(3, 3, 0, sp20);
    Ta_GetStdCompleteView(sp30);
    SzView_IV2V(sp30, sp40);
    SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, sp20);
    SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp40);
}

/* Moves the camera to the standard top-down view over `nSpeed` frames. */
void TaView_ReqStdTopDownView(s32 nSpeed) {
    s32 sp20[4];
    s32 sp30[4];
    s32 sp40[4];

    SzView_FreeRequest(0, 0);
    SzDuel_CalcUnitPos(3, 3, 0, sp20);
    Ta_GetStdTopDownView(sp30);
    SzView_IV2V(sp30, sp40);
    SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, sp20);
    SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp40);
}

/* Moves the camera to the flat full-board view over `nSpeed` frames. */
void TaView_ReqFlatCompleteView(s32 nSpeed) {
    s32 sp20[4];
    s32 sp30[4];
    s32 sp40[4];

    SzView_FreeRequest(0, 0);
    SzDuel_CalcUnitPos(3, 3, 0x64, sp20);
    Ta_GetFlatCompleteView(sp30);
    SzView_IV2V(sp30, sp40);
    SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, sp20);
    SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp40);
}

/* Moves the camera to the destiny-draw view for level `Lvl`. */
void TaView_SetDestinyCamera(s32 Lvl) {
    f32 sp20[4];
    f32 sp30[4];
    f32 sp40[4];

    SzView_FreeRequest(0, 0);
    switch ((u8)Lvl) {
    case 0:
        SzDuel_CalcUnitPos(3, 3, 0x190, &sp20);
        Ta_GetDestinyView(&sp30);
        SzView_IV2V(&sp30, &sp40);
        SzView_ReqCamera(0, 0, 3, 0, 0, &sp20);
        SzView_ReqCamera(0, 0, 4, 0, 0, &sp40);
        break;
    }
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Vec4_00260990;


/* Turns the camera by `nAngle` over `nSpeed` frames. */
void TaView_ReqRotCamera(s32 nSpeed, s32 nAngle) {
    Vec4_00260990 *rotation;
    Vec4_00260990 sp40;
    f32 sp50[4];
    s32 var_v0;
    s32 var_v1;

    rotation = &sp40;
    SzView_FreeRequest(0, 0);
    SzView_V2IV(SzView_GetLook(0), rotation);
    if ((rotation->y + nAngle) >= 0) {
        var_v1 = rotation->y + nAngle;
    } else {
        var_v1 = -(rotation->y + nAngle);
    }
    if (var_v1 >= 0xFFFF) {
        var_v0 = ((rotation->y + nAngle) - 0x8000) - 0x7FFF;
    } else {
        var_v0 = rotation->y + nAngle;
    }
    rotation->y = var_v0;
    SzView_IV2V(rotation, sp50);
    SzView_ReqCamera(0, 0, 4, nSpeed & 0xFF, 0, sp50);
}

/* Moves the camera back to where it was before the effect, over `nSpeed` frames. */
void TaView_RestoreOriginalView(void *Temp, s32 nSpeed) {
    SzView_FreeRequest(0, 0);
    SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, (u8 *)Temp + 0xE0);
    SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, (u8 *)Temp + 0xF0);
    *(s16 *)((u8 *)Temp + 0x102) = 0;
}

/* Moves the camera to the front of unit `nOwnerID`'s model over `nSpeed` frames. */
void TaView_ReqFocusCamera(s32 nSpeed, s32 nOwnerID, s32 nFocus, s32 cFocus) {
    extern s32 SzDuel_GetUnitCtlRateM(s32, s32);
    u8 sp70[16];
    u8 sp80[16];
    f32 sp90[4];
    s32 val;

    SzView_FreeRequest(0, 0);
    if (SzEffect_IsModelStandby2(nOwnerID) != 0) {
        if ((SzDuel_GetUnitStatus(nOwnerID >> 8, nOwnerID & 0xFF, 4) != 0 || (nOwnerID & 0xFF) == 0) &&
            SzDuel_GetUnitCtlRateM(nOwnerID >> 8, nOwnerID & 0xFF) > 0) {
            TaView_SetModelFrontView(sp80, nOwnerID, nFocus);
            SzView_IV2V(sp80, sp90);
            sp90[0] += SzEffect_GetRadius2(nOwnerID);
            SzView_ReqCamera(0, 0, 7, (u8)nSpeed & 0xFF, SzDuel_GetUnitModelID(nOwnerID >> 8, nOwnerID & 0xFF), NULL);
            SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp90);
            return;
        }
        val = SzDuel_GetUnitLoc(nOwnerID >> 8, nOwnerID & 0xFF);
        SzDuel_CalcUnitPos(val & 0xFF, val >> 8, 0, sp70);
        Ta_GetStdFocusView(sp80, cFocus);
        SzView_IV2V(sp80, sp90);
        SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, sp70);
        SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp90);
    }
    val = SzDuel_GetUnitLoc(nOwnerID >> 8, nOwnerID & 0xFF);
    SzDuel_CalcUnitPos(val & 0xFF, val >> 8, 0, sp70);
    Ta_GetStdFocusView(sp80, cFocus);
    SzView_IV2V(sp80, sp90);
    SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, sp70);
    SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp90);
}

/* Moves the camera to the front of unit `nOwnerID`'s model (third form). */
void TaView_ReqFocusCamera3(s32 nSpeed, s32 nOwnerID, s32 nFocus, s32 cFocus) {
    extern s32 SzDuel_GetUnitCtlRateM(s32, s32);
    u8 sp70[0x10];
    u8 sp80[0x10];
    f32 sp90[4];
    s32 col;
    s32 row;
    s32 id;

    SzView_FreeRequest(0, 0);
    if (SzEffect_IsModelStandby2(nOwnerID) != 0) {
        row = nOwnerID >> 8;
        col = nOwnerID & 0xFF;
        if ((SzDuel_GetUnitStatus(row, col, 4) != 0 || col == 0) &&
            SzDuel_GetUnitCtlRateM(row, col) > 0) {
            TaView_SetModelFrontView(sp80, nOwnerID, nFocus);
            SzView_IV2V(sp80, sp90);
            sp90[0] += SzEffect_GetRadius2(nOwnerID);
            SzView_ReqCamera(0, 0, 7, (u8)nSpeed & 0xFF, SzDuel_GetUnitModelID(row, col), NULL);
            SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp90);
            return;
        }
    }
    id = SzDuel_GetUnitLoc(nOwnerID >> 8, nOwnerID & 0xFF);
    SzDuel_CalcUnitPos(id & 0xFF, id >> 8, 0, sp70);
    Ta_GetStdFocusView2(sp80, cFocus);
    SzView_IV2V(sp80, sp90);
    SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, sp70);
    SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp90);
}

/* Moves the camera close to the front of unit `nOwnerID`'s model. */
void TaView_ReqExzFocusCamera(s32 nSpeed, s32 nOwnerID, s32 nFocus, s32 cFocus) {
    extern s32 SzDuel_GetUnitCtlRateM(s32, s32);
    u8 sp70[16];
    u8 sp80[16];
    f32 sp90[4];
    s32 val;

    SzView_FreeRequest(0, 0);
    if (SzEffect_IsModelStandby2(nOwnerID) != 0) {
        if ((SzDuel_GetUnitStatus(nOwnerID >> 8, nOwnerID & 0xFF, 4) != 0 || (nOwnerID & 0xFF) == 0) &&
            SzDuel_GetUnitCtlRateM(nOwnerID >> 8, nOwnerID & 0xFF) > 0) {
            TaView_SetExzModelFrontView(sp80, nOwnerID, nFocus);
            SzView_IV2V(sp80, sp90);
            sp90[0] += SzEffect_GetRadius2(nOwnerID);
            SzView_ReqCamera(0, 0, 7, (u8)nSpeed & 0xFF, SzDuel_GetUnitModelID(nOwnerID >> 8, nOwnerID & 0xFF), NULL);
            SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp90);
            return;
        }
        val = SzDuel_GetUnitLoc(nOwnerID >> 8, nOwnerID & 0xFF);
        SzDuel_CalcUnitPos(val & 0xFF, val >> 8, 0, sp70);
        Ta_GetStdFocusView(sp80, cFocus);
        SzView_IV2V(sp80, sp90);
        SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, sp70);
        SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp90);
    }
    val = SzDuel_GetUnitLoc(nOwnerID >> 8, nOwnerID & 0xFF);
    SzDuel_CalcUnitPos(val & 0xFF, val >> 8, 0, sp70);
    Ta_GetStdFocusView(sp80, cFocus);
    SzView_IV2V(sp80, sp90);
    SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, sp70);
    SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp90);
}

/* Moves the camera behind unit `nOwnerID`'s model. */
void TaView_ReqBackFocusCamera(s32 nSpeed, s32 nOwnerID, s32 nFocus, s32 cFocus) {
    u8 buf[16];
    f32 vec[4];
    f32 pos[4];
    s32 lo;
    s32 hi;
    s32 t;

    SzView_FreeRequest(0, 0);
    if (SzEffect_IsModelStandby2(nOwnerID) != 0) {
        hi = nOwnerID >> 8;
        lo = nOwnerID & 0xFF;
        if (SzDuel_GetUnitStatus(hi, lo, 4) != 0 || lo == 0) {
            TaView_SetModelBackView(vec, nOwnerID, nFocus);
            SzView_IV2V(vec, pos);
            pos[0] += SzEffect_GetRadius2(nOwnerID);
            SzView_ReqCamera(0, 0, 7, (u8)nSpeed & 0xFF, SzDuel_GetUnitModelID(hi, lo), NULL);
            SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, pos);
            return;
        }
        t = SzDuel_GetUnitLoc(hi, lo);
        SzDuel_CalcUnitPos(t & 0xFF, t >> 8, 0, buf);
        Ta_GetStdFocusView(vec, cFocus);
        SzView_IV2V(vec, pos);
        SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, buf);
        SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, pos);
        return;
    }
    t = SzDuel_GetUnitLoc(nOwnerID >> 8, nOwnerID & 0xFF);
    SzDuel_CalcUnitPos(t & 0xFF, t >> 8, 0, buf);
    Ta_GetStdFocusView(vec, cFocus);
    SzView_IV2V(vec, pos);
    SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, buf);
    SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, pos);
}

/* The camera in front of unit `nOwnerID`'s model into `pVec`. */
void TaView_SetModelFrontView(void *pVec, s32 nOwnerID, s32 nFocus) {
    s32 temp_a0;
    s32 temp_s1;
    s32 var_a1;

    temp_s1 = SzDuel_GetUnit(nOwnerID >> 8, nOwnerID & 0xFF);
    SzEffect_GetModelRot2(nOwnerID, pVec);
    ((s32 *)pVec)[0] += nFocus;
    temp_a0 = *(s32 *)((u8 *)temp_s1 + 0x30);
    var_a1 = 0x47FF - temp_a0;
    if (var_a1 < 0) {
        var_a1 = 0x147FE - temp_a0;
    }
    ((s32 *)pVec)[1] += var_a1;
    ((s32 *)pVec)[2] += 0x2000;
}

/* The close camera in front of unit `nOwnerID`'s model into `pVec`. */
void TaView_SetExzModelFrontView(void *pVec, s32 nOwnerID, s32 nFocus) {
    s32 temp_a0;
    s32 temp_s1;
    s32 var_a1;

    temp_s1 = SzDuel_GetUnit(nOwnerID >> 8, nOwnerID & 0xFF);
    SzEffect_GetModelRot2(nOwnerID, pVec);
    ((s32 *)pVec)[0] += nFocus;
    temp_a0 = *(s32 *)((u8 *)temp_s1 + 0x30);
    var_a1 = 0x3FFF - temp_a0;
    if (var_a1 < 0) {
        var_a1 = 0x13FFE - temp_a0;
    }
    ((s32 *)pVec)[1] += var_a1;
    ((s32 *)pVec)[2] += 0x1000;
}

/* The camera behind unit `nOwnerID`'s model into `pVec`. */
void TaView_SetModelBackView(void *pVec, s32 nOwnerID, s32 nFocus) {
    s32 temp_a0;
    s32 *temp_s1;
    s32 var_a1;

    temp_s1 = (s32 *)SzDuel_GetUnit(nOwnerID >> 8, nOwnerID & 0xFF);
    SzEffect_GetModelRot2(nOwnerID, pVec);
    ((s32 *)pVec)[0] += nFocus;
    temp_a0 = temp_s1[12];
    var_a1 = 0xC7FF - temp_a0;
    if (var_a1 < 0) {
        var_a1 = 0x1C7FE - temp_a0;
    }
    ((s32 *)pVec)[1] += var_a1;
    ((s32 *)pVec)[2] += 0x2000;
}

/* Moves the camera to square `nLoc` over `nSpeed` frames. */
void TaView_ReqFocusCamera2(s32 nSpeed, s32 nLoc, s32 nFocus) {
    f32 sp40[4];
    f32 sp50[4];
    f32 sp60[4];
    

    SzView_FreeRequest(0, 0);
    SzDuel_CalcUnitPos(nLoc & 0xFF, nLoc >> 8, 0, &sp40);
    Ta_GetStdFocusView(&sp50, nFocus);
    SzView_IV2V(&sp50, &sp60);
    SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, sp40);
    SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, sp60);
}

/* Moves the camera to the attack view on unit `nGoalUnit` for `nTime` frames. */
void TaView_ReqFireView(s32 nTime, s32 nGoalUnit, u8 nFocus, u8 cFocus) {
    TaView_ReqFocusCamera(nTime, nGoalUnit, nFocus, cFocus);
}

/* Moves the camera to the top view. */
void TaView_ReqTopView(void) {
    s32 params[4];
    s32 position[4];
    s32 converted[4];

    SzView_FreeRequest(0, 0);
    SzDuel_CalcUnitPos(3, 3, 0x3E8, params);
    Ta_GetTopView(position);
    SzView_IV2V(position, converted);
    SzView_ReqCamera(0, 0, 3, 0, 0, params);
    SzView_ReqCamera(0, 0, 4, 0, 0, converted);
}

/* Moves the camera to the sky view. */
void TaView_ReqSkyView(void) {
    s32 sp10[4];
    s32 sp20[4];
    s32 sp30[4];

    SzView_FreeRequest(0, 0);
    SzDuel_CalcUnitPos(3, 3, 0x3E8, sp10);
    Ta_GetSkyView(sp20);
    SzView_IV2V(sp20, sp30);
    SzView_ReqCamera(0, 0, 3, 0, 0, sp10);
    SzView_ReqCamera(0, 0, 4, 0, 0, sp30);
}

/* Plays unit `nOwnerID`'s hurt motion. */
void TaEffect_SetOuchMotion(s32 nOwnerID) {
    f32 temp_f0;

    if (SzEffect_GetAnim2(nOwnerID) != 4) {
        SzEffect_SetAnimIntr2(nOwnerID, 4);
        return;
    }
    temp_f0 = SzEffect_GetAnimFrame2(nOwnerID, 4);
    if (!(temp_f0 < 16.0f)) {
        SzEffect_SetAnimFrame2(nOwnerID, 11.0f);
        return;
    }
    if (!(temp_f0 <= 11.0f) && ((func_0019A5C8() % 3) == 0)) {
        SzEffect_SetAnimFrame2(nOwnerID, temp_f0 - 2.0f);
    }
}

typedef struct Command_00261760 {
    s32 unk0;
    s32 mode;
    u32 mask;
    u32 value;
} Command_00261760;

typedef struct State_00261760 {
    u16 fade;
    u16 unk2;
    u16 phase;
    u8 handles[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00261760;

typedef struct Effect_00261760 {
    s32 kind;
    s32 value1;
    s32 value2;
    s32 value3;
} Effect_00261760;

/* Effect script 017_MEGUMI, step `ID`: its camera, fades and effect module; it changes attack or defence. */
s32 Ta_Eff_017_MEGUMI(void *eInfo, void *Temp, s32 ID) {
    Effect_00261760 effect;
    s32 complete;
    Effect_00261760 *command = &effect;
    Command_00261760 *config = eInfo;
    State_00261760 *state = Temp;

    effect.kind = 999;
    effect.value1 = 0;
    effect.value2 = 0;
    effect.value3 = 0;
    complete = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        state->fade = 0x80;
        TaView_ReqStdCompleteView(16);
        TaEffect_LoadModule(Temp, 20);
        TaEffect_LoadModule(Temp, 0x211);
        Ta_AllUnitFade(eInfo, Temp, ID, -1, 1, 1);
    } else {
        switch (state->phase) {
    case 0:
        if (state->fade > 0x3F) {
            state->fade -= 15;
        } else {
            state->fade = 0x30;
            if (TaEffect_IsLoadModule(Temp) == 1) {
                if (state->timer++ > 16) {
                    u8 handle;

                    SzDuel_OpenMsgPopup(0, -120, 80, 0x106);
                    command->kind = 20;
                    command->value1 = 0;
                    command->value2 = 0;
                    command->value3 = 0;
                    handle = Ta_Do_Effect((s32 *)command, Temp);
                    state->handles[state->count] = handle;
                    if (handle >= 0) {
                        state->count++;
                    }
                    state->phase++;
                    state->timer = 0;
                }
            }
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        return 1;
    case 1:
        if (SzEffect_IsUse(state->handles[0]) == 1) {
            return 1;
        }
        Ta_SetEffectDependOnFlagLst(eInfo, Temp, command, 0x211);
        state->phase++;
        return 1;
    case 2:
        {
            s32 i;

            for (i = 0; i < state->count; i++) {
                if (SzEffect_IsUse(state->handles[i]) == 0) {
                    complete++;
                }
            }
            if (complete < state->count) {
                return 1;
            }
            SzDuel_CloseMsgPopup();
            complete = 0;
            do {
                if ((config->mask >> (21 - complete)) & 1) {
                    if (complete < 11) {
                        TaUtil_CalcUnitDP(0, complete, config->value >> 16, config->value & 0xFFFF);
                        if (config->mode == 1) {
                            TaUtil_CalcUnitAP(0, complete, config->value >> 16, config->value & 0xFFFF);
                        }
                    } else {
                        TaUtil_CalcUnitDP(1, complete - 11, config->value >> 16, config->value & 0xFFFF);
                        if (config->mode == 1) {
                            TaUtil_CalcUnitAP(1, complete - 11, config->value >> 16, config->value & 0xFFFF);
                        }
                    }
                }
                complete++;
            } while (complete < 22);
            state->phase++;
        }
        break;
    case 3:
        if (state->timer++ > 16) {
            Ta_AllUnitFade(eInfo, Temp, ID, 1, 0, 1);
            TaView_RestoreOriginalView(Temp, 16);
            state->timer = 0;
            state->phase++;
        }
        break;
    default:
        state->fade += 15;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        if (state->fade == 0x80) {
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
    }
    return 1;
}

typedef struct Command_00261B70 {
    s32 unk0;
    s32 mode;
    u32 mask;
    u32 value;
} Command_00261B70;

typedef struct State_00261B70 {
    u16 fade;
    u16 unk2;
    u16 phase;
    u8 handles[0xCE];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00261B70;

typedef struct Effect_00261B70 {
    s32 kind;
    s32 value1;
    s32 value2;
    s32 value3;
} Effect_00261B70;


/* Effect script 006_WIND, step `ID`: its camera, fades and effect module; it changes attack or defence, changes
   life points, changes the field. */
s32 Ta_Eff_006_WIND(void *eInfo, void *Temp, s32 ID) {
    Effect_00261B70 effect;
    s32 complete;
    Effect_00261B70 *command = &effect;
    Command_00261B70 *config = eInfo;
    State_00261B70 *state = Temp;

    effect.kind = 999;
    effect.value1 = 0;
    effect.value2 = 0;
    effect.value3 = 0;
    complete = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        state->fade = 0x80;
        TaView_ReqStdCompleteView(30);
        TaEffect_LoadModule(Temp, 6);
        TaEffect_LoadModule(Temp, 0x211);
    } else {
        switch (state->phase) {
    case 0:
        if (state->fade > 0x30) {
            state->fade -= 15;
        } else {
            state->fade = 0x30;
            if (TaEffect_IsLoadModule(Temp) == 1) {
                command->kind = 6;
                command->value1 = 0;
                command->value2 = 0;
                command->value3 = 0;
                state->handles[state->count] = Ta_Do_Effect((s32 *)command, Temp);
                state->count++;
                state->phase++;
            }
        }
        if (state->fade < 0x30) {
            state->fade = 0x30;
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        return 1;
    case 1:
        if (SzEffect_IsUse(state->handles[0]) == 1) {
            return 1;
        }
        SzDuel_OpenMsgPopup(0, -120, 80, 0x106);
        Ta_SetEffectDependOnFlagLst(eInfo, Temp, command, 0x211);
        state->phase++;
        return 1;
    case 2:
        {
            s32 i;

            for (i = 0; i < state->count; i++) {
                if (SzEffect_IsUse(state->handles[i]) == 0) {
                    complete++;
                }
            }
            if (complete < state->count) {
                return 1;
            }
            SzDuel_CloseMsgPopup();
            complete = 0;
            do {
                if ((config->mask >> (21 - complete)) & 1) {
                    if (complete < 11) {
                        TaUtil_CalcUnitDP(0, complete, config->value >> 16, config->value & 0xFFFF);
                        if (config->mode == 1) {
                            TaUtil_CalcUnitAP(0, complete, config->value >> 16, config->value & 0xFFFF);
                        }
                    } else {
                        TaUtil_CalcUnitDP(1, complete - 11, config->value >> 16, config->value & 0xFFFF);
                        if (config->mode == 1) {
                            TaUtil_CalcUnitAP(1, complete - 11, config->value >> 16, config->value & 0xFFFF);
                        }
                    }
                }
                complete++;
            } while (complete < 22);
            state->phase++;
            TaView_RestoreOriginalView(Temp, 16);
            if (SzDuel_GetWindowDisp() != 0) {
                SzDuel_SetWindowDraw(1);
            }
        }
        break;
    default:
        state->fade += 15;
        if (state->fade > 0x80) {
            state->fade = 0x80;
        }
        SzEffect_SetBlackOutForDuel((u8)state->fade);
        if (state->fade == 0x80) {
            if (state->timer++ >= 16 && Ta_IsFinishFade() == 1) {
                SzDuel_CloseMsgPopup();
                return 0;
            }
        }
        break;
        }
    }
    return 1;
}

typedef struct Flags_00261F20 {
    u8 pad0:5;
    u8 field5:1;
    u8 field6:1;
    u8 pad7:1;
} Flags_00261F20;

typedef struct Result_00261F20 {
    u8 pad0[0xC];
    s32 value;
    Flags_00261F20 flags;
} Result_00261F20;


/* The attack effects of unit (nSide_1, ID_1) attacking unit (nSide_2, ID_2) (attribute advantage, effects), into
   `pDat`. */
s32 Manage_AtkEfc(s32 nSide_1, s32 ID_1, s32 nSide_2, s32 ID_2, void *pDat) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 var_fp;
    s32 var_s0;
    s32 var_s1;
    s32 var_s7;
    Result_00261F20 *temp_s2;
    void *temp_v0;
    void *temp_v0_3;

    temp_s2 = (Result_00261F20 *)pDat;
    var_s7 = 0;
    var_fp = 0;
    var_s1 = 0;
    var_s0 = 0;
    temp_s2->value = ChkAttrAdv(SzDuel_GetUnitAttr(nSide_1, ID_1), SzDuel_GetUnitAttr(nSide_2, ID_2));
    temp_v0 = Ta_GetUnitEffect(nSide_1, ID_1, 0);
    if (temp_v0 != NULL) {
        temp_v0_2 = Do_AtkEfc(*(s32 *)temp_v0, *(s32 *)((u8 *)temp_v0 + 4), temp_s2, nSide_1, ID_1, nSide_2, ID_2, 0);
        var_s0 = temp_v0_2;
        var_fp = 1;
        temp_s2->flags.field5 = ((temp_v0_2 >> 0x18) & 1);
    }
    temp_v0_3 = Ta_GetUnitEffect(nSide_2, ID_2, 0);
    if (temp_v0_3 != NULL) {
        temp_v0_4 = Do_AtkEfc(*(s32 *)temp_v0_3, *(s32 *)((u8 *)temp_v0_3 + 4), temp_s2, nSide_2, ID_2, nSide_1, ID_1, 1);
        var_s1 = temp_v0_4;
        var_s7 = 1;
        temp_s2->flags.field6 = ((temp_v0_4 >> 0x18) & 1);
    }
    if ((var_fp == 0) && (var_s7 == 0) && (temp_s2->value == 0)) {
        return 0;
    }
    temp_a0 = var_s0 & 0xFF;
    if ((temp_a0 == 1) && ((var_s1 & 0xFF) == 1)) {
        return 0x01010001;
    }
    if (temp_a0 == 1) {
        return 0x01000001;
    }
    if ((var_s1 & 0xFF) == 1) {
        return 0x10001;
    }
    temp_a0_2 = (var_s0 >> 0x10) & 1;
    if ((temp_a0_2 == 1) && (((var_s1 >> 0x10) & 1) == 1)) {
        return 0x01010000;
    }
    if (temp_a0_2 == 0) {
        if (((var_s1 >> 0x10) & 1) == 1) {
            return 0x10000;
        }
    }
    if (temp_a0_2 == 1) {
        if (((var_s1 >> 0x10) & 1) == 0) {
            return 0x01000000;
        }
    }
    return 0;
}

typedef struct Flags_00262190 {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 unused : 3;
} Flags_00262190;

typedef struct State_00262190 {
    Flags_00262190 flags;
    u8 pad1[3];
    s32 value0;
    s32 value1;
    u8 padC[4];
    Flags_00262190 flags10;
} State_00262190;

/* Applies attack effect `eID` (with `eParam`) of the attacker on the defender, into `pDat`. */
s32 Do_AtkEfc(u32 eID, u32 eParam, void *pDat, s32 nSide_Do, s32 ID_Do,
                  s32 nSide_Done, s32 ID_Done, s32 fAtkSide) {
    extern s32 SzDuel_SetField();

    switch (eID >> 8) {
    case 4:
        if (Match_AtkEfcObj((eID >> 6) & 3, eID & 0x3F, nSide_Do, ID_Do, nSide_Done, ID_Done) == 1) {
            if (ID_Done != 0 && ID_Do != 0) {
                ((State_00262190 *)pDat)->flags.bit0 = 0;
                if (fAtkSide == 1) {
                    ((State_00262190 *)pDat)->flags.bit1 = 1;
                } else {
                    ((State_00262190 *)pDat)->flags.bit2 = 1;
                }
                return 0x10001;
            }
        }
        return 0;
    case 2: {
        s32 row;
        s32 y;
        s32 x;
        s32 col;
        u32 range;
        u32 value;

        if (fAtkSide == 0) {
            y = SzDuel_GetUnitLoc(nSide_Do, ID_Do) & 0xFF;
            x = SzDuel_GetUnitLoc(nSide_Do, ID_Do) >> 8;
        } else {
            y = SzDuel_GetUnitLoc(nSide_Done, ID_Done) & 0xFF;
            x = SzDuel_GetUnitLoc(nSide_Done, ID_Done) >> 8;
        }
        row = 0;
        range = eParam >> 16;
        value = eParam & 0xFFFF;
        do {
            col = 0;
            do {
                if ((u32)(((row < y ? y : row) - (y < row ? y : row)) +
                          ((col < x ? x : col) - (x < col ? x : col))) <= range &&
                    SzDuel_GetField(row, col) != 8) {
                    SzDuel_SetField(row, col, value);
                }
                col++;
            } while (col < 7);
            row++;
        } while (row < 7);
        return 0x10000;
    }
    case 27:
        if (Match_AtkEfcObj(2, eParam >> 16, nSide_Do, ID_Do, nSide_Done, ID_Done) == 1) {
            if (ID_Done != 0 && ID_Do != 0) {
                if (fAtkSide == 0) {
                    ((State_00262190 *)pDat)->value0 += eParam & 0xFFFF;
                } else {
                    ((State_00262190 *)pDat)->value1 += eParam & 0xFFFF;
                }
                return 0x10000;
            }
        }
        return 0;
    case 5:
        if (ID_Done != 0) {
            if (ID_Do != 0) {
                if (fAtkSide == 0) {
                    ((State_00262190 *)pDat)->flags10.bit0 = 1;
                } else {
                    ((State_00262190 *)pDat)->flags10.bit1 = 1;
                }
                return 0x10000;
            }
        }
        break;
    case 13: {
        s32 value = eParam & 0xFFFF;
        eParam >>= 16;
        switch (eParam) {
        case 0:
            value = Ta_GetLPRevByNaturalEffect(0x2B, value);
            break;
        case 1:
            value = Ta_GetLPRevByNaturalEffect(0x2C, value);
            break;
        }
        SzDuel_CalcLP(nSide_Do, eParam, value);
        return 0x10000;
    }
    case 0x3A:
        if (ID_Done != 0 && ID_Do != 0) {
            ((State_00262190 *)pDat)->flags10.bit2 = 1;
            return 0x10000;
        }
        break;
    case 1:
        if (ID_Done != 0 && ID_Do != 0) {
            if (fAtkSide == 0) {
                ((State_00262190 *)pDat)->flags10.bit4 = 1;
            } else {
                ((State_00262190 *)pDat)->flags10.bit3 = 1;
            }
            return 0x10000;
        }
        break;
    case 0x3F:
        if (fAtkSide == 0) {
            u32 first;
            u32 divisor;
            divisor = ((eParam & 0xFFFF) / 100) + 1;
            first = (u32)func_0019A5C8() % divisor;
            ((State_00262190 *)pDat)->value0 = (first - (u32)func_0019A5C8() % divisor) * 100;
        } else {
            u32 first;
            u32 divisor;
            divisor = ((eParam & 0xFFFF) / 100) + 1;
            first = (u32)func_0019A5C8() % divisor;
            ((State_00262190 *)pDat)->value1 = (first - (u32)func_0019A5C8() % divisor) * 100;
        }
        return 0x10000;
    default:
        return 0;
    }
    return 0;
}

/* Whether an attack effect's target `eObj` matches the battle's units. */
s32 Match_AtkEfcObj(s32 eOwner, s32 eObj, s32 nSide_1, s32 ID1, s32 nSide_2, s32 ID2) {
    switch (eOwner) {
    case 1:
        return Do_Match_AtkEfcObj(eObj, nSide_1, ID1);
    case 2:
        return Do_Match_AtkEfcObj(eObj, nSide_2, ID2);
    default:
        return 0;
    }
}

/* Whether unit (nSide, nID) is the kind or attribute target `eObj` means. */
s32 Do_Match_AtkEfcObj(s32 eObj, s32 nSide, s32 nID) {
    switch (eObj) {
    case 0:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 0) ? 1 : -1;
    case 1:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 1) ? 1 : -1;
    case 2:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 2) ? 1 : -1;
    case 3:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 3) ? 1 : -1;
    case 4:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 4) ? 1 : -1;
    case 5:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 5) ? 1 : -1;
    case 6:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 6) ? 1 : -1;
    case 7:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 7) ? 1 : -1;
    case 8:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 8) ? 1 : -1;
    case 9:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 9) ? 1 : -1;
    case 10:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 10) ? 1 : -1;
    case 11:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 11) ? 1 : -1;
    case 12:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 12) ? 1 : -1;
    case 13:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 13) ? 1 : -1;
    case 14:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 14) ? 1 : -1;
    case 15:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 15) ? 1 : -1;
    case 16:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 16) ? 1 : -1;
    case 17:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 17) ? 1 : -1;
    case 18:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 18) ? 1 : -1;
    case 19:
        return ((SzDuel_GetUnitKind(nSide, nID) & 0x1F) == 19) ? 1 : -1;
    case 20:
        return (SzDuel_GetUnitAttr(nSide, nID) == 0) ? 1 : -1;
    case 21:
        return (SzDuel_GetUnitAttr(nSide, nID) == 1) ? 1 : -1;
    case 22:
        return (SzDuel_GetUnitAttr(nSide, nID) == 2) ? 1 : -1;
    case 23:
        return (SzDuel_GetUnitAttr(nSide, nID) == 3) ? 1 : -1;
    case 24:
        return (SzDuel_GetUnitAttr(nSide, nID) == 4) ? 1 : -1;
    case 25:
        return (SzDuel_GetUnitAttr(nSide, nID) == 5) ? 1 : -1;
    }
    return 0;
}

typedef struct {
    s32 kind;
    u32 source;
    u32 target;
    s32 value;
} Command_00262BE0;

typedef struct {
    u16 sourceActive;
    u16 targetActive;
    u16 stage;
    u8 effect;
    u8 pad07[0x19];
    s32 applied;
    u8 pad24[0xAC];
    s32 timer;
} State_00262BE0;


/* Effect script 100, step `ID`: its camera, fades and effect module; it destroys units, puts a card on the board,
   uses the graveyard. */
s32 Ta_Eff_100(void *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_GetUnitCtlRateM();
    extern s32 SzDuel_GetUnitCtlGoalM();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_SetUnitCtlModeC();
    extern s32 SzDuel_SetUnitCtlGoalC();
    s32 scratch[4];
    s32 *command = scratch;
    State_00262BE0 *state = Temp;
    Command_00262BE0 *input = eInfo;
    s32 status;

    command[0] = 999;
    command[1] = 0;
    command[2] = 0;
    command[3] = 0;

    if (ID >= 0) {
        InitEffectTemp(state);
        if (SzDuel_GetUnitCtlRateM(input->source >> 8, input->source & 0xFF) > 0) {
            Ta_UnitFade(input->source >> 8, input->source & 0xFF, -1, 1, 1);
            state->sourceActive = 1;
        }
        if (SzDuel_GetUnitCtlRateM(input->target >> 8, input->target & 0xFF) > 0) {
            Ta_UnitFade(input->target >> 8, input->target & 0xFF, -1, 1, 1);
            state->targetActive = 1;
        }
        if (input->value == 999) {
            TaEffect_LoadModule(state, 0x21A);
        } else if (input->kind == 0x2B) {
            TaEffect_LoadModule(state, 0x21F);
        } else {
            TaEffect_LoadModule(state, 0x258);
        }
        return 1;
    }

    switch (state->stage) {
        case 0:
        if (TaEffect_IsLoadModule(state) != 1) {
            return 1;
        }
        if (state->sourceActive != 0) {
            status = SzDuel_GetUnitCtlRateM(input->source >> 8, input->source & 0xFF);
            if (status != SzDuel_GetUnitCtlGoalM(input->source >> 8, input->source & 0xFF)) {
                return 1;
            }
        }
        if (state->targetActive != 0) {
            status = SzDuel_GetUnitCtlRateM(input->target >> 8, input->target & 0xFF);
            if (status != SzDuel_GetUnitCtlGoalM(input->target >> 8, input->target & 0xFF)) {
                return 1;
            }
        }
        if (input->value == 999) {
            command[0] = 0x21A;
            command[1] = input->source;
            command[2] = input->target;
            command[3] = 1;
        } else if (input->kind == 0x2B) {
            command[0] = 0x21F;
            command[1] = input->source;
            command[2] = input->target;
            command[3] = 1;
        } else {
            command[0] = 0x258;
            command[1] = input->source;
            command[2] = input->target;
            command[3] = 1;
        }
        state->effect = Ta_Do_Effect(command, state);
        state->applied = 0;
        state->stage++;
        return 1;
        default:
        if (input->value == 999) {
            if (SzEffect_IsUse(state->effect) != 0) {
                switch (state->timer++) {
                    case 0:
                        SzSound_PlaySE(1, 0x38);
                        break;
                    case 20:
                        SzSound_PlaySE(1, 0x39);
                        break;
                    case 30:
                        SzSound_PlaySE(1, 0x4C);
                        break;
                    case 36:
                        SzSound_PlaySE(1, 0x4A);
                        break;
                    case 48:
                        SzSound_PlaySE(1, 0x3C);
                        break;
                }
                return 1;
            }
            Ta_DelUnit(input->source >> 8, input->source & 0xFF);
            if (state->targetActive != 0) {
                Ta_UnitFade(input->target >> 8, input->target & 0xFF, 1, 1, 1);
            }
            SzDuel_CloseMsgPopup();
            return 0;
        }

        if (SzEffect_IsUse(state->effect) != 0) {
            switch (state->timer++) {
                case 0:
                    SzSound_PlaySE(1, 0x38);
                    break;
                case 20:
                    SzSound_PlaySE(1, 0x39);
                    break;
                case 30:
                    SzSound_PlaySE(1, 0x4C);
                    break;
                case 40:
                    SzSound_PlaySE(1, 0x3A);
                    break;
                case 100:
                    SzSound_PlaySE(1, 0x3B);
                    break;
                case 120:
                    SzSound_PlaySE(1, 0x3C);
                    break;
            }
            if (SzEffect_GetStatus(state->effect) != 2) {
                return 1;
            }
            if (state->applied == 0) {
                SzDuel_AddGrave(input->target >> 8,
                             SzDuel_GetUnitCardNo(input->target >> 8, input->target & 0xFF));
                SzDuel_PutUnit(input->target >> 8, input->target & 0xFF, input->value);
                Ta_DelUnit(input->source >> 8, input->source & 0xFF);
                SzDuel_SetUnitCtlModeC(input->target >> 8, input->target & 0xFF, 1);
                SzDuel_SetUnitCtlGoalC(input->target >> 8, input->target & 0xFF, 0);
                SzDuel_SetUnitCtlRateC(input->target >> 8, input->target & 0xFF, -1, 0);
                state->applied = 1;
            }
            return 1;
        }

        SzDuel_SetUnitCtlModeC(input->target >> 8, input->target & 0xFF, 1);
        SzDuel_SetUnitCtlGoalC(input->target >> 8, input->target & 0xFF, 0x80);
        SzDuel_SetUnitCtlRateC(input->target >> 8, input->target & 0xFF, 1, 0x80);
        SzSound_PlaySE(0, 2);
        SzDuel_CloseMsgPopup();
        return 0;
    }
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
extern void func_00260AF0_b(unsigned char who, int packed, int add, int value);
extern void func_00260A70_b(struct jp_69942 *Temp, unsigned char b);

/* Effect script 064, step `ID`: its camera, fades and effect module; it changes attack or defence. */
int Ta_Eff_064(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_6989c * eInfo = eInfo_v;
    struct jp_69942 * Temp = Temp_v;
    struct jp_6989c eCall;
    struct jp_6989c *pCall = &eCall;
    int Loc2;
    int Loc;
    int AP;
    int DP;
    int i;

    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        func_00260AF0_b(30, eInfo->dwTo, 100, 180);
        func_00255AC0_b(Temp, 529);
        return 1;
    }
    switch (Temp->wLvl) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) == 1) {
            if (Temp->wCamTime++ >= 30) {
                SzDuel_OpenMsgPopup(0, -120, 80, 271);
                pCall->eNO = 529;
                pCall->dwFrom = 0;
                pCall->dwTo = eInfo->dwTo;
                pCall->dwPar = 0;
                Temp->eID[0] = Ta_Do_Effect(pCall, Temp);
                Temp->ePos[0] = eInfo->dwTo;
                Temp->wLvl++;
            }
        }
        break;
    case 1:
        if (SzEffect_IsUse(Temp->eID[0]) == 1) {
            return 1;
        }
        Loc = SzDuel_GetUnitLoc(eInfo->dwTo >> 8, eInfo->dwTo & 0xFF);
        for (i = 0; i < 22; i++) {
            if (eInfo->dwFrom >> (21 - i) & 1) {
                if (i < 11) {
                    Loc2 = SzDuel_GetUnitLoc(0, i);
                    AP = TaUtil_GetUnitAP(0, i, Loc2 & 0xFF, Loc2 >> 8);
                    DP = TaUtil_GetUnitDP(0, i, Loc2 & 0xFF, Loc2 >> 8);
                    TaUtil_CalcUnitAP(eInfo->dwTo >> 8, eInfo->dwTo & 0xFF, 0, AP - TaUtil_GetUnitAP3(eInfo->dwTo >> 8, eInfo->dwTo & 0xFF, Loc & 0xFF, Loc >> 8));
                    TaUtil_CalcUnitDP(eInfo->dwTo >> 8, eInfo->dwTo & 0xFF, 0, DP - TaUtil_GetUnitDP3(eInfo->dwTo >> 8, eInfo->dwTo & 0xFF, Loc & 0xFF, Loc >> 8));
                } else {
                    Loc2 = SzDuel_GetUnitLoc(1, i - 11);
                    AP = TaUtil_GetUnitAP(1, i - 11, Loc2 & 0xFF, Loc2 >> 8);
                    DP = TaUtil_GetUnitDP(1, i - 11, Loc2 & 0xFF, Loc2 >> 8);
                    TaUtil_CalcUnitAP(eInfo->dwTo >> 8, eInfo->dwTo & 0xFF, 0, AP - TaUtil_GetUnitAP3(eInfo->dwTo >> 8, eInfo->dwTo & 0xFF, Loc & 0xFF, Loc >> 8));
                    TaUtil_CalcUnitDP(eInfo->dwTo >> 8, eInfo->dwTo & 0xFF, 0, DP - TaUtil_GetUnitDP3(eInfo->dwTo >> 8, eInfo->dwTo & 0xFF, Loc & 0xFF, Loc >> 8));
                }
            }
        }
        SzDuel_CloseMsgPopup();
        Temp->wLvl++;
        func_00260A70_b(Temp, 16);
        Temp->wCamTime = 0;
        break;
    default:
        if (Temp->wCamTime++ > 16) {
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
    u8 pad0[8];
    s32 mask;
    s32 owner;
} Context_00263500;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 ids[0x1A];
    u8 pad20[0xB4];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00263500;


/* Effect script 063, step `ID`: its camera, fades and effect module; it destroys units, puts a card on the board. */
s32 Ta_Eff_063(void *eInfo, void *Temp, s32 ID) {
    s32 data[4];
    s32 *data_ptr = data;
    s32 i;
    s32 inactive;
    Context_00263500 *context = eInfo;
    State_00263500 *state = Temp;

    data[0] = 999;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    inactive = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        TaEffect_LoadModule(Temp, 0x230);
        if (Ta_GetUnitNumFrom22bitFlagList(context->mask) == 1) {
            TaView_ReqFocusCamera(0x1E, Ta_GetUnitOwnerIDFromLstCount(context->mask, 0), 0x64, 0xB4);
        } else {
            TaView_ReqStdCompleteView(0x1E);
        }
        return 1;
    }

    switch (state->state) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) == 1) {
            if (state->timer++ >= 0x1E) {
                Ta_SetEffectDependOnFlagLst(eInfo, Temp, data_ptr, 0x230);
                state->state++;
            }
        }
        break;
    case 1: {
        u8 *entry;
        s32 target;
        s32 location;

        for (i = 0, entry = Temp; i < state->count; entry += 4, i++) {
            if (SzEffect_IsUse(state->ids[i]) == 1) {
                if (SzEffect_GetStatus(state->ids[i]) == 2) {
                    target = *(s32 *)(entry + 0x20);
                    if ((target & 0xFFFF) != 0xFFFF) {
                        location = SzDuel_GetUnitLoc(target >> 8, target & 0xFF);
                        target = *(s32 *)(entry + 0x20);
                        Ta_DelUnit(target >> 8, target & 0xFF);
                        SzDuel_AddUnit(*(s32 *)(entry + 0x20) >> 8,
                                     location & 0xFF, location >> 8, context->owner, 0);
                        *(s32 *)(entry + 0x20) = 0xFFFF;
                    }
                }
            } else {
                inactive++;
            }
        }
        if (inactive < state->count) {
            return 1;
        } else {
            state->state++;
            state->timer = 0;
            TaView_RestoreOriginalView(Temp, 0x10);
        }
        break;
    }
    default:
        if (state->timer++ > 0x10) {
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


typedef struct Config_00263790 {
    u8 padding[8];
    u32 id;
    s32 duration;
} Config_00263790;

typedef struct State_00263790 {
    u32 unknown;
    u16 phase;
    u8 handle;
} State_00263790;

/* Effect script 065, step `ID`: its camera, fades and effect module; it turns cards face up, changes summon power. */
s32 Ta_Eff_065(void *eInfo, void *Temp, s32 ID) {
    s32 request[4];
    s32 *p = request;
    State_00263790 *state = Temp;
    Config_00263790 *config = eInfo;

    request[0] = 0x3E7;
    request[1] = 0;
    request[2] = 0;
    request[3] = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        TaEffect_LoadModule(Temp, 0x216);
        return 1;
    }
    switch (state->phase) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) != 1) {
            break;
        }
        if (SzDuel_GetSummonPower(config->id) <= (u32)config->duration) {
            p[0] = 0x216;
            p[1] = 0;
            p[2] = 0;
            p[3] = config->duration - SzDuel_GetSummonPower(config->id);
        } else {
            p[0] = 0x216;
            p[1] = 0;
            p[2] = 1;
            p[3] = SzDuel_GetSummonPower(config->id) - config->duration;
        }
        state->handle = Ta_Do_Effect(p, Temp);
        state->phase++;
        break;
    default:
        if (SzEffect_IsUse(state->handle) == 1) {
            return 1;
        }
        SzDuel_CalcSummonPower(config->id, 4, config->duration);
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
}

struct ActEfcInfo_00263930_s {
    u32 dwID;
    u32 dwParam;
};

struct ActEfcEffect_00263930_s {
    s32 eNO;
    u32 dwFrom;
    u32 dwTo;
    u32 dwPar;
};

struct ActEfcKind_00263930_s {
    u8 bType;
    u8 bKind;
};

#pragma conditional_move on

/* Runs the effect a unit sets off when it acts (summoned, flipped, moved): finds its targets in range, applies it,
   into `eInfo`. */
s32 Ta_Manage_ActEfc(ActEfcInfo_00263930 *eInfo, s32 nSide, s32 nID, s32 eSide, s32 eID, s32 nX, s32 nZ,
                     ActEfcEffect_00263930 *Effect, ActEfcKind_00263930 *pInfo, u8 bHeap)
{
    extern s32 SzDuel_SetUnitDelayCount();
    extern s32 SzDuel_GetUnitCardNo();
    s32 i;
    s32 temp;
    s32 Num;
    s32 LOC;
    s32 eObj;
    s32 Unit;
    s32 Unit2;
    s32 EFC;
    s32 NUM;
    s32 fN;
    s32 fE;
    s32 pKindP;
    s32 pKindS;
    ActEfcInfo_00263930 *eTemp;

    eObj = 0;
    pKindP = 0;
    i = 0;
    do {
        i++;
    } while (i < 0x31);
    pInfo->bType = 0;
    pInfo->bKind = 0;
    fE = 0;
    fN = 0;
    switch ((u32)(Unit = eInfo->dwID) >> 8) {
    case 2:
        switch ((u16)eInfo->dwParam) {
        case 8:
            Effect->eNO = 2;
            Effect->dwFrom = (nZ << 8) | nX;
            Effect->dwTo = eInfo->dwParam >> 16;
            Effect->dwPar = (u16)eInfo->dwParam;
            break;
        default:
            Effect->eNO = 2;
            Effect->dwFrom = (nZ << 8) | nX;
            Effect->dwTo = eInfo->dwParam >> 16;
            Effect->dwPar = (u16)eInfo->dwParam;
            break;
        }
        return 1;
    case 0x12:
        if ((eInfo->dwParam >> 16) == 0x16) {
            NUM = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), ((u32)Unit >> 6) & 3, Unit & 0x3F, 0x16);
        } else {
            NUM = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), ((u32)Unit >> 6) & 3,
                                    ((eInfo->dwParam >> 16) << 16) | (Unit & 0x3F), 0xE);
        }
        if (NUM == 0) {
            return 0;
        }
        Effect->eNO = 0x1D;
        Effect->dwFrom = 1;
        Effect->dwTo = NUM;
        Effect->dwPar = (u16)eInfo->dwParam;
        return 1;
    case 0x13:
        if (eID > 0 && eSide >= 0 && (bHeap & 0xFF) != 2) {
            eObj = ConvUnitIDtoFlagList(0, eSide, eID);
        } else {
            return 0;
        }
        Effect->eNO = 0x39;
        Effect->dwFrom = 0;
        Effect->dwTo = eObj;
        Effect->dwPar = (u16)eInfo->dwParam;
        return eObj == 0 ? 0 : 1;
    case 0x33:
        NUM = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), ((u32)Unit >> 6) & 3,
                                ((eInfo->dwParam >> 16) << 16) | (0x3F & Unit), 0xE);
        Effect->eNO = 0x3F;
        Effect->dwFrom = 0;
        Effect->dwTo = NUM;
        Effect->dwPar = (u16)eInfo->dwParam;
        return NUM == 0 ? 0 : 1;
    case 0x17:
        if (0x1A == (pKindP = Unit & 0x3F)) {
            if (eID > 0 && eSide >= 0 && (bHeap & 0xFF) != 2) {
                NUM = ConvUnitIDtoFlagList(0, eSide, eID);
            } else {
                return 0;
            }
        } else {
            NUM = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), ((u32)Unit >> 6) & 3, pKindP, 0xE);
        }
        Effect->eNO = 0;
        Effect->dwFrom = 0;
        Effect->dwTo = NUM;
        Effect->dwPar = (u16)eInfo->dwParam;
        if (0 == NUM) {
            return 0;
        }
        return 1;
    case 0xD:
        Effect->eNO = 8;
        Effect->dwFrom = 0;
        Effect->dwTo = Ta_GetEOwnerSide(Ta_GetCurrentSide(nSide, nID), (eInfo->dwID >> 6) & 3);
        Effect->dwPar = ((eInfo->dwParam >> 16) << 16) | (eInfo->dwParam & 0xFFFF);
        return 1;
    case 0x14:
        if ((Unit = Ta_IsUnitControl(nSide, nID)) != SzDuel_GetTurnOwner()) {
            return 0;
        }
        if ((Unit = Ta_IsActiveTrapB(nSide == 0 ? 1 : 0, 0x4C)) >= 0) {
            if (Ta_IsActiveTrapB(nSide == 0 ? 1 : 0, 0x2E) >= 0) {
                Effect->eNO = 1;
                Effect->dwFrom = Ta_GetCurrentSide(nSide, nID) | 0x20000;
                Effect->dwTo = Ta_GetSummonablePiece(Ta_GetCurrentSide(nSide, nID), 1);
                Effect->dwPar = 0;
                switch ((eInfo->dwID >> 6) & 3) {
                case 3:
                    LOC = 2;
                    break;
                case 1:
                    LOC = Ta_GetCurrentSide(nSide, nID) != 0 ? 1 : 0;
                    break;
                }
                Num = 0;
                switch (eInfo->dwID & 0x3F) {
                case 0x1E:
                    if (LOC == 2) {
                        Num += TaUtil_GetGraveCardNum(0, 1);
                        Num += TaUtil_GetGraveCardNum(1, 1);
                        Num += TaUtil_GetGraveCardNum(0, 2);
                        Num += TaUtil_GetGraveCardNum(1, 2);
                        Num += TaUtil_GetGraveCardNum(0, 3);
                        Num += TaUtil_GetGraveCardNum(1, 3);
                        Num += TaUtil_GetGraveCardNum(0, 4);
                        Num += TaUtil_GetGraveCardNum(1, 4);
                        Num += TaUtil_GetGraveCardNum(0, 5);
                        Num += TaUtil_GetGraveCardNum(1, 5);
                    } else {
                        Num += TaUtil_GetGraveCardNum(LOC, 1);
                        Num += TaUtil_GetGraveCardNum(LOC, 2);
                        Num += TaUtil_GetGraveCardNum(LOC, 3);
                        Num += TaUtil_GetGraveCardNum(LOC, 4);
                        Num += TaUtil_GetGraveCardNum(LOC, 5);
                    }
                    if (Num == 0) {
                        return 0;
                    }
                    pKindS = 2;
                    break;
                default:
                    return 0;
                }
                pInfo->bType = 0;
                pInfo->bKind = (LOC << 4) | pKindS;
                return 4;
            } else {
                Effect->eNO = 0x66;
                Effect->dwFrom = 1;
                Effect->dwTo = Unit;
                Effect->dwPar = 0;
                return 1;
            }
        } else {
            if (Ta_GetSummonablePiece(Ta_GetCurrentSide(nSide, nID), 1) < 0) {
                return 0;
            }
            Effect->eNO = 1;
            Effect->dwFrom = Ta_GetCurrentSide(nSide, nID) | 0x20000;
            Effect->dwTo = Ta_GetSummonablePiece(Ta_GetCurrentSide(nSide, nID), 1);
            Effect->dwPar = 0;
            switch ((eInfo->dwID >> 6) & 3) {
            case 3:
                LOC = 2;
                break;
            case 1:
                LOC = Ta_GetCurrentSide(nSide, nID) != 0 ? 1 : 0;
                break;
            }
            Num = 0;
            switch (eInfo->dwID & 0x3F) {
            case 0x1E:
                if (LOC == 2) {
                    Num += TaUtil_GetGraveCardNum(0, 1);
                    Num += TaUtil_GetGraveCardNum(1, 1);
                    Num += TaUtil_GetGraveCardNum(0, 2);
                    Num += TaUtil_GetGraveCardNum(1, 2);
                    Num += TaUtil_GetGraveCardNum(0, 3);
                    Num += TaUtil_GetGraveCardNum(1, 3);
                    Num += TaUtil_GetGraveCardNum(0, 4);
                    Num += TaUtil_GetGraveCardNum(1, 4);
                    Num += TaUtil_GetGraveCardNum(0, 5);
                    Num += TaUtil_GetGraveCardNum(1, 5);
                } else {
                    Num += TaUtil_GetGraveCardNum(LOC, 1);
                    Num += TaUtil_GetGraveCardNum(LOC, 2);
                    Num += TaUtil_GetGraveCardNum(LOC, 3);
                    Num += TaUtil_GetGraveCardNum(LOC, 4);
                    Num += TaUtil_GetGraveCardNum(LOC, 5);
                }
                if (Num == 0) {
                    return 0;
                }
                pKindS = 2;
                break;
            default:
                return 0;
            }
            pInfo->bType = 0;
            pInfo->bKind = (LOC << 4) | pKindS;
            return pKindS;
        }
    case 0x23:
        NUM = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), ((u32)Unit >> 6) & 3, Unit & 0x3F, 0xE);
        NUM = ConvUnitIDtoFlagList_OFF(NUM, nSide, nID);
        if (eID > 0 && eSide >= 0 && (bHeap & 0xFF) == 2) {
            NUM = ConvUnitIDtoFlagList_OFF(NUM, eSide, eID);
        }
        Effect->eNO = 0xD;
        Effect->dwFrom = 5;
        Effect->dwTo = NUM;
        Effect->dwPar = (u16)eInfo->dwParam;
        return NUM == 0 ? 0 : 1;
    case 0x18:
        NUM = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), ((u32)Unit >> 6) & 3,
                                ((eInfo->dwParam >> 16) << 16) | (0x3F & Unit), 0xE);
        NUM = ConvUnitIDtoFlagList_OFF(NUM, nSide, nID);
        if ((eInfo->dwID & 0x3F) == 0x2D) {
            Unit2 = Ta_GetMaximumOrderUnitFromFlagList(NUM);
            NUM = ConvUnitIDtoFlagList(0, Unit2 >> 8, Unit2 & 0xFF);
        }
        Effect->eNO = 0xD;
        Effect->dwFrom = 4;
        Effect->dwTo = NUM;
        Effect->dwPar = (u16)eInfo->dwParam;
        if (NUM == 0) {
            return 0;
        }
        return 1;
    case 4:
        if (0x1A == (pKindP = 0x3F & Unit)) {
            if (eID <= 0 || eSide < 0 || (bHeap & 0xFF) == 2) {
                return 0;
            }
            switch (eInfo->dwParam >> 16) {
            case 2:
                if ((SzDuel_GetUnitKind(eSide, eID) & 0x1F) == 2) {
                    eObj = ConvUnitIDtoFlagList(0, eSide, eID);
                }
                break;
            default:
                eObj = ConvUnitIDtoFlagList(0, eSide, eID);
                break;
            }
        } else if (pKindP == 0x30) {
            Unit2 = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), 3, 0x1F, 0xE);
            Unit2 = ConvUnitIDtoFlagList_OFF(Unit2, nSide, nID);
            Unit2 = Ta_GetRandomUnit(Unit2);
            if (Unit2 < 0) {
                return 0;
            }
            eObj = ConvUnitIDtoFlagList(0, Unit2 >> 8, 0xFF & Unit2);
        } else if ((eInfo->dwParam >> 16) != 0) {
            temp = SzDuel_GetUnitLoc(nSide, nID);
            Unit = eInfo->dwID;
            eObj = SearchUnitByRange(temp & 0xFF, temp >> 8, Ta_GetCurrentSide(nSide, nID),
                                     ((u32)Unit >> 6) & 3, Unit & 0x3F, eInfo->dwParam >> 16);
        } else {
            eObj = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), ((u32)Unit >> 6) & 3, pKindP, 0xE);
        }
        Effect->eNO = 0x15;
        Effect->dwFrom = 0;
        Effect->dwTo = eObj;
        Effect->dwPar = 0;
        if (0 == eObj) {
            return 0;
        }
        if (eID > 0 && eSide >= 0) {
            if (Ta_GetAgreeOwnerIDon22bitFlagLst((eSide << 8) | eID, eObj) != 0) {
                if ((bHeap & 0xFF) > 0) {
                    return 0x201;
                }
                return 1;
            }
            if (Ta_GetAgreeOwnerIDon22bitFlagLst((nSide << 8) | nID, eObj) != 0) {
                if ((0xFF & bHeap) > 0) {
                    return 0x401;
                }
                return 1;
            }
        }
        return 1;
    case 0x38:
        switch (eInfo->dwParam >> 16) {
        case 0x1F:
            if ((Unit = Ta_GetSummonablePiece(Ta_IsUnitControl(nSide, nID), 1)) > 0 &&
                Ta_GetUnitNum(Ta_IsUnitControl(nSide, nID), 4) < 5) {
                if (SzDuel_GetUnitCardNo(nSide, nID) != 0x129 && SzDuel_GetUnitCardNo(nSide, nID) != 0x112) {
                    Effect->eNO = 1;
                    Effect->dwFrom = Ta_GetCurrentSide(nSide, nID) | 0x10000;
                    Effect->dwTo = Unit;
                    Effect->dwPar = (u16)eInfo->dwParam;
                } else {
                    Effect->eNO = 1;
                    Effect->dwFrom = Ta_GetCurrentSide(nSide, nID);
                    Effect->dwTo = Unit;
                    Effect->dwPar = (u16)eInfo->dwParam;
                }
            } else {
                return 0;
            }
            break;
        default:
            return 0;
        }
        return 1;
    case 0x16:
        if ((Unit = eInfo->dwParam >> 16) == 0x1A) {
            if (eID > 0 && eSide >= 0 && (bHeap & 0xFF) != 2) {
                NUM = ConvUnitIDtoFlagList(0, eSide, eID);
            } else {
                return 0;
            }
        } else {
            NUM = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), 3, Unit, 0xE);
        }
        Effect->eNO = 0x40;
        Effect->dwFrom = NUM;
        Effect->dwTo = (nSide << 8) | nID;
        Effect->dwPar = 0;
        if (NUM == 0) {
            return 0;
        }
        return 1;
    case 0x1A:
        Effect->eNO = 0x41;
        Effect->dwFrom = 0;
        Effect->dwTo = Ta_GetCurrentSide(nSide, nID);
        Effect->dwPar = (u16)eInfo->dwParam;
        return 1;
    case 0x26:
        Effect->eNO = 0x21;
        Effect->dwFrom = 0;
        Effect->dwTo = Ta_GetCurrentSide(nSide, nID);
        Effect->dwPar = 0;
        return 1;
    case 0x35:
        Unit = ConvUnitIDtoFlagList(0, nSide, nID);
        if (Unit == 0) {
            return 0;
        }
        switch ((EFC = eInfo->dwID) & 0x3F) {
        case 0x22:
            Effect->eNO = 0x1D;
            Effect->dwFrom = 1;
            Effect->dwTo = Unit;
            Effect->dwPar = (u16)eInfo->dwParam;
            return (eInfo->dwParam >> 16) == SzDuel_GetUnitCardNo(Ta_GetCurrentSide(nSide, nID), 0) ? 1 : 0;
        case 0x38:
            Effect->eNO = 0x1D;
            Effect->dwFrom = 1;
            Effect->dwTo = Unit;
            Effect->dwPar = (u16)eInfo->dwParam;
            return (eInfo->dwParam >> 16) == (SzDuel_GetUnitKind(Ta_GetCurrentSide(nSide, nID), 0) & 0x1F) ? 1 : 0;
        case 0x2E:
            Unit2 = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), 3, eInfo->dwParam >> 16, 0xE);
            NUM = (u16)eInfo->dwParam * Ta_GetUnitNumFrom22bitFlagList(Unit2);
            Effect->eNO = 0x1D;
            Effect->dwFrom = 1;
            Effect->dwTo = Unit;
            Effect->dwPar = NUM;
            return NUM != 0 ? 1U : 0U;
        case 0x2F:
            Unit = ConvUnitIDtoFlagList(Unit, nSide, nID);
            if ((eInfo->dwParam >> 16) == 0x1D) {
                temp = (u16)eInfo->dwParam * TaUtil_GetGraveCardNum(Ta_IsUnitControl(nSide, nID), 0);
            } else if ((eInfo->dwParam >> 16) == 0x1C) {
                temp = (u16)eInfo->dwParam * (TaLogic_GetGraveCardCount(nSide, 3, 0x3C) +
                                              TaLogic_GetGraveCardCount(nSide, 3, 0x57));
            }
            if (temp <= 0) {
                return 0;
            }
            Effect->eNO = 0x1D;
            Effect->dwFrom = 1;
            Effect->dwTo = Unit;
            Effect->dwPar = temp;
            return 1;
        default:
            return 0;
        }
    case 0x1E:
        NUM = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), ((u32)Unit >> 6) & 3, Unit & 0x3F, 0xE);
        NUM = ConvUnitIDtoFlagList_OFF(NUM, nSide, nID);
        Effect->eNO = 0xF;
        Effect->dwFrom = 0;
        Effect->dwTo = NUM;
        Effect->dwPar = 0;
        return NUM == 0 ? 0 : 1;
    case 0x36:
    case 0x37:
        if ((pKindP = Unit & 0x3F) == 0x1A) {
            if (eID > 0 && eSide >= 0 && (bHeap & 0xFF) != 2) {
                NUM = ConvUnitIDtoFlagList(0, eSide, eID);
            } else {
                return 0;
            }
        } else {
            NUM = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), ((u32)Unit >> 6) & 3, pKindP, 0xE);
        }
        NUM = ConvUnitIDtoFlagList_OFF(NUM, nSide, nID);
        Effect->eNO = 0x42;
        Effect->dwFrom = eInfo->dwID >> 8;
        Effect->dwTo = NUM;
        Effect->dwPar = (u16)eInfo->dwParam;
        if (NUM == 0) {
            return 0;
        }
        return 1;
    case 0x24:
        if ((Unit & 0x3F) == 0x1A) {
            if (eID > 0 && eSide >= 0 && (0xFF & bHeap) != 2) {
                eObj = ConvUnitIDtoFlagList(0, eSide, eID);
                Effect->eNO = 0x1E;
                Effect->dwFrom = 0;
                Effect->dwTo = eObj;
                Effect->dwPar = Ta_GetCurrentSide(eSide, nID);
            } else {
                return 0;
            }
        } else if ((Unit & 0x3F) == 0x1B) {
            eObj = ConvUnitIDtoFlagList(0, nSide, nID);
            Effect->eNO = 0x1E;
            Effect->dwFrom = 0;
            Effect->dwTo = eObj;
            Effect->dwPar = Ta_GetCurrentSide(nSide, nID);
        }
        if (eID > 0 && eSide >= 0 && (0xFF & bHeap) != 2 &&
            Ta_GetAgreeOwnerIDon22bitFlagLst((eSide << 8) | eID, eObj) != 0) {
            fE = 1;
        }
        if (nSide >= 0 && nID >= 0 &&
            Ta_GetAgreeOwnerIDon22bitFlagLst((nSide << 8) | nID, eObj) != 0) {
            fN = 1;
        }
        if ((0xFF & bHeap) == 1) {
            return (fN << 10) | ((fE << 9) | 1);
        }
        return 1;
    case 0x1F:
        if (Ta_SearchUncTypeNaturalEffectUserNum(0x39) > 0) {
            return 0;
        }
        Unit = eInfo->dwID;
        switch (pKindP = Unit & 0x3F) {
        case 0x1A:
            if (eID <= 0 || eSide < 0 || (bHeap & 0xFF) == 2) {
                return 0;
            }
            switch (eInfo->dwParam >> 16) {
            case 0xE:
                if ((SzDuel_GetUnitKind(Ta_GetCurrentSide(eSide, eID), eID) & 0x1F) == 0xE) {
                    NUM = ConvUnitIDtoFlagList(0, eSide, eID);
                } else {
                    return 0;
                }
                break;
            default:
                NUM = ConvUnitIDtoFlagList(0, eSide, eID);
                break;
            }
            Effect->eNO = 0x1A;
            Effect->dwFrom = Ta_GetCurrentSide(nSide, nID);
            Effect->dwTo = NUM;
            Effect->dwPar = 0xFFFE;
            if (NUM == 0) {
                return 0;
            }
            if ((bHeap & 0xFF) == 1) {
                return 0x101;
            }
            return 1;
        default:
            NUM = SearchUnitByRange(0, 0, Ta_GetCurrentSide(nSide, nID), ((u32)Unit >> 6) & 3, pKindP, 0xE);
            Effect->eNO = 0x1A;
            Effect->dwFrom = Ta_GetCurrentSide(nSide, nID);
            Effect->dwTo = NUM;
            Effect->dwPar = 0xFFFE;
            if (NUM == 0) {
                return 0;
            }
            if (Ta_GetAgreeOwnerIDon22bitFlagLst((eSide << 8) | eID, NUM) == 1) {
                if ((bHeap & 0xFF) == 1) {
                    return 0x101;
                }
                return 1;
            }
            return 1;
        }
    case 0x25:
        switch (eInfo->dwParam >> 16) {
        case 0x1E:
            if ((NUM = Ta_GetSummonablePiece(Ta_GetCurrentSide(nSide, nID) == 0 ? 1 : 0, 1)) >= 0) {
                Effect->eNO = 0x1F;
                Effect->dwFrom = (nSide << 8) | nID;
                Effect->dwTo = 0;
                Effect->dwPar = NUM;
                if ((0xFF & bHeap) == 1) {
                    return 0x801;
                }
                return 1;
            }
            break;
        case 0x1F:
            if ((NUM = Ta_GetSummonablePiece(Ta_GetCurrentSide(nSide, nID), 1)) >= 0) {
                Effect->eNO = 0x1F;
                Effect->dwFrom = (nSide << 8) | nID;
                Effect->dwTo = 0;
                Effect->dwPar = NUM;
                if ((bHeap & 0xFF) == 1) {
                    return 0x801;
                }
                return 1;
            }
            break;
        case 0x20:
            break;
        }
        return 0;
    case 0x3C:
        Unit = SzDuel_GetUnitLoc(nSide, nID);
        NUM = SearchUnitByRange(0xFF & Unit, Unit >> 8, Ta_GetCurrentSide(nSide, nID), 3,
                                 ((u16)eInfo->dwParam << 16) | (eInfo->dwID & 0x3F), 1);
        if (NUM > 0 && (Unit = Ta_GetSummonablePiece(Ta_GetCurrentSide(nSide, nID) == 0 ? 1 : 0, 1)) >= 0) {
            Unit2 = Ta_GetMinimumOrderUnitFromFlagList(NUM);
            Effect->eNO = 0x1F;
            Effect->dwFrom = Unit2;
            Effect->dwTo = 0;
            Effect->dwPar = Unit;
            if (Unit2 == ((eSide << 8) | eID)) {
                if ((0xFF & bHeap) == 2) {
                    return 0x201;
                }
                return 1;
            }
            return 1;
        }
        return 0;
    case 0x46:
    case 0xC:
        NUM = ConvUnitIDtoFlagList(0, nSide, nID);
        Effect->eNO = 0x43;
        Effect->dwFrom = 0;
        Effect->dwTo = NUM;
        Effect->dwPar = 0;
        SzDuel_SetUnitDelayCount(nSide, nID, (eInfo->dwParam >> 16) + 1);
        return NUM != 0 ? 1U : 0U;
    case 0x57:
        Effect->eNO = 0xE;
        Effect->dwFrom = 0;
        Effect->dwTo = Ta_GetCurrentSide(nSide, nID) == 0 ? 1 : 0;
        Effect->dwPar = 1;
        return 1;
    case 0x51:
        if (Ta_SearchUncTypeNaturalEffectUserNum(0x39) > 0) {
            return 0;
        }
        if (eID > 0 && eSide >= 0 && (bHeap & 0xFF) != 2) {
            Effect->eNO = 0x43;
            Effect->dwFrom = (nSide << 8) | nID;
            Effect->dwTo = (eSide << 8) | eID;
            Effect->dwPar = 1;
            eTemp = SzDuel_GetUnitEffect(eSide, eID, 2);
            if (eTemp != NULL) {
                eTemp->dwID = 0x51FD;
                eTemp->dwParam = 0;
            }
            eTemp = SzDuel_GetUnitEffect(eSide, eID, 4);
            if (eTemp != NULL) {
                eTemp->dwID = 0x515C;
                eTemp->dwParam = (((Ta_IsUnitControl(nSide, nID) << 8) | 0x1F) << 16) | 0x2A0;
            }
            TaUtil_DoOpen(eSide, eID, 1);
            return ((bHeap & 0xFF) == 1) ? 0x101 : 1;
        }
        break;
    default:
        return 0;
    }
    return 0;
}
#pragma conditional_move reset

typedef struct State_00265050 {
    u32 unk0;
    u16 state;
    u8 handle;
    u8 handle2;
    u8 pad8[0xFA];
    u16 timer;
} State_00265050;

typedef struct Request_00265050 {
    s32 id;
    s32 unk4;
    u32 position;
    s32 flag;
} Request_00265050;


/* Effect script 045, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_045(void *eInfo, void *Temp, s32 ID) {
    Request_00265050 packet;
    Request_00265050 *request = &packet;
    State_00265050 *state = Temp;
    u32 *data = eInfo;
    extern s32 SzDuel_GetUnitOpenRate();
    extern s32 SzDuel_GetUnitCtlRateC();

    packet.id = 999;
    packet.unk4 = 0;
    packet.position = 0;
    packet.flag = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        TaUtil_DoOpen(data[1] >> 8, data[1] & 0xFF, 1);
        TaUtil_DoOpen(data[2] >> 8, data[2] & 0xFF, 1);
        TaView_ReqFocusCamera(0, data[1], 100, 180);
        TaEffect_LoadModule(Temp, 0x221);
        TaEffect_LoadModule(Temp, 0x259);
        TaEffect_LoadModule(Temp, 0x25A);
        TaEffect_LoadModule(Temp, 0x25B);
        return 1;
    }
    switch (state->state) {
    case 0:
        if (SzDuel_GetUnitOpenRate(data[1] >> 8, data[1] & 0xFF) < 255 ||
            SzDuel_GetUnitOpenRate(data[2] >> 8, data[2] & 0xFF) < 255 ||
            SzDuel_GetUnitCtlRateC(data[2] >> 8, data[2] & 0xFF) < 128) {
            return 1;
        }
        if ((SzDuel_GetUnitKind(data[2] >> 8, data[2] & 0xFF) >> 5) == 0 &&
            SzEffect_IsModelStandby2(data[2]) == 0) {
            return 1;
        }
        if (TaEffect_IsLoadModule(Temp) == 1) {
            state->state++;
        }
        return 1;
    case 1:
        SzDuel_OpenMsgPopup(0, -120, 80, 0x103);
        request->id = 0x25A;
        request->unk4 = 0;
        request->position = data[1];
        request->flag = 0;
        state->handle = Ta_Do_Effect(request, Temp);
        state->state++;
        return 1;
    case 2:
        if (SzEffect_IsUse(state->handle) == 0) {
            SzDuel_SetUnitStatus(data[1] >> 8, data[1] & 0xFF, 0, 1);
            request->id = 0x259;
            request->unk4 = 0;
            request->position = data[1];
            request->flag = 1;
            state->handle = Ta_Do_Effect(request, Temp);
            state->state++;
        }
        return 1;
    case 3:
        if (SzEffect_IsUse(state->handle) == 0) {
            TaView_ReqFocusCamera(16, data[2], 100, 180);
            Ta_DelUnit(data[1] >> 8, data[1] & 0xFF);
            request->id = 0x25B;
            request->unk4 = 0;
            request->position = data[2];
            request->flag = 0;
            state->handle = Ta_Do_Effect(request, Temp);
            request->id = 0x221;
            request->unk4 = 0;
            request->position = data[2];
            request->flag = 0;
            state->handle2 = Ta_Do_Effect(request, Temp);
            state->state++;
        }
        return 1;
    case 4:
        if (SzEffect_IsUse(state->handle) != 0 ||
            SzEffect_IsUse(state->handle2) != 0) {
            return 1;
        }
        Ta_DelUnit(data[2] >> 8, data[2] & 0xFF);
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(Temp, 16);
        state->state++;
        break;
    default:
        if (state->timer++ > 16) {
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

typedef struct Effect_00265440 {
    u32 pad0;
    u32 source;
    u32 target;
    u32 param;
} Effect_00265440;

typedef struct Step_00265440 {
    u8 pad0[4];
    u16 step;
    u8 slot;
    u8 slot2;
    u8 pad8[0xFA];
    u16 timer;
} Step_00265440;

typedef struct Request_00265440 {
    s32 id;
    s32 unk4;
    u32 position;
    s32 unkC;
} Request_00265440;

/* Effect script 044, step `ID`: its camera, fades and effect module; it destroys units, changes attack or defence,
   curses units, turns cards face up. */
s32 Ta_Eff_044(void *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_GetUnitOpenRate();
    extern void Ta_DelUnit();
    Request_00265440 request;
    Request_00265440 *req;
    Effect_00265440 *effect = eInfo;
    Step_00265440 *state = Temp;

    request.id = 999;
    request.unk4 = 0;
    request.position = 0;
    request.unkC = 0;
    req = &request;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(state);
        TaUtil_DoOpen(effect->source >> 8, effect->source & 0xFF, 1);
        TaUtil_DoOpen(effect->target >> 8, effect->target & 0xFF, 1);
        TaView_ReqFocusCamera(0, effect->source, 100, 180);
        TaEffect_LoadModule(state, 0x259);
        TaEffect_LoadModule(state, 0x25A);
        TaEffect_LoadModule(state, 0x220);
        if ((u16)effect->param != 0) {
            TaEffect_LoadModule(state, 0x22D);
        }
        return 1;
    }
    switch (state->step) {
    case 0:
        SzDuel_OpenMsgPopup(0, -120, 80, 0x103);
        if (SzDuel_GetUnitOpenRate(effect->source >> 8, effect->source & 0xFF) < 0xFF ||
            SzDuel_GetUnitOpenRate(effect->target >> 8, effect->target & 0xFF) < 0xFF) {
            return 1;
        }
        if (TaEffect_IsLoadModule(state) == 1) {
            req->id = 0x25A;
            req->unk4 = 0;
            req->position = effect->source;
            req->unkC = 0;
            state->slot = Ta_Do_Effect(req, state);
            state->step++;
        }
        return 1;
    case 1:
    case 4:
        if (SzEffect_IsUse(state->slot) != 1) {
            if (state->step == 1) {
                SzDuel_SetUnitStatus(effect->source >> 8, effect->source & 0xFF, 0, 1);
            }
            state->step++;
        }
        return 1;
    case 2:
        if (SzEffect_IsUse(state->slot) == 0) {
            req->id = 0x259;
            req->unk4 = 0;
            req->position = effect->source;
            req->unkC = 1;
            state->slot = Ta_Do_Effect(req, state);
            state->step++;
        }
        return 1;
    case 3:
        if (SzEffect_IsUse(state->slot) == 0) {
            TaView_ReqFocusCamera(0x10, effect->target, 100, 180);
            SzDuel_OpenMsgPopup(0, -120, 80, 0x108);
            Ta_DelUnit(effect->source >> 8, effect->source & 0xFF);
            req->id = 0x220;
            req->unk4 = 0;
            req->position = effect->target;
            req->unkC = 0;
            state->slot = Ta_Do_Effect(req, state);
            if ((u16)effect->param != 0 && (SzDuel_GetUnitKind(effect->target >> 8, effect->target & 0xFF) >> 5) == 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 0x107);
                req->id = 0x22D;
                req->unk4 = 0;
                req->position = effect->target;
                req->unkC = 0;
                state->slot2 = Ta_Do_Effect(req, state);
            }
            state->step++;
        }
        return 1;
    case 5:
        SzDuel_SetUnitStatus(effect->target >> 8, effect->target & 0xFF, 0, 1);
        Ta_SetUnitCurseRest(effect->target >> 8, effect->target & 0xFF, (effect->param >> 16) & 0xFF);
        if ((u16)effect->param != 0 && (SzDuel_GetUnitKind(effect->target >> 8, effect->target & 0xFF) >> 5) == 0) {
            TaUtil_CalcUnitAP(effect->target >> 8, effect->target & 0xFF, 1, (u16)effect->param);
            TaUtil_CalcUnitDP(effect->target >> 8, effect->target & 0xFF, 1, (u16)effect->param);
        }
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(state, 0x10);
        state->step++;
        break;
    default:
        if (state->timer++ > 0x10) {
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
