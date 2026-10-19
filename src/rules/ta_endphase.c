/* Card rules: the end phase (Ta_Do_EndPhase). */

#include "common.h"
extern int func_001E1E10_b(int a, int b);
extern int func_001E1030_b(int a, int b);
extern void func_00260AF0_b(unsigned char who, int packed, int add, int value);

/* Runs the end of a turn: curse and spell turns count down, into `res`. */
s32 Ta_Do_EndPhase(s32 phase, s32 *res) {
    extern s32 SzDuel_GetUnitSpellRest();
    extern s32 SzDuel_GetUnitCurseRest();
    extern s32 SzDuel_GetUnitCurseFlag();
    extern s32 SzDuel_GetUnitCardNo();
    extern s32 SzDuel_SetUnitCurseRest();
    extern s32 SzDuel_SetUnitSpellRest();
    extern s32 SzDuel_GetTurnFirst();
    extern s32 SzDuel_GetTurnCount();
    s32 row;
    s32 a;
    s32 v;
    s32 pos;
    s32 col;
    s32 player;
    s32 b;
    s32 c;
    s32 vy;
    s32 other;
    s32 hp;
    s32 hi;
    s32 lo;
    s32 n;
    s32 vx;
    s32 i;
    s32 mine;
    s32 w;

    player = SzDuel_GetTurnOwner();
    switch (phase) {
    case 0:
        if (Ta_IsLDAbl(5, player)) {
            res[0] = 8;
            res[1] = 0;
            res[2] = player;
            res[3] = 50;
            return ((phase + 1) << 16) | 1;
        }
        return (phase + 1) << 16;
    case 1:
        return ((phase + 1) << 16) | Ta_IsVirusAll(res);
    case 2:
        pos = SzDuel_GetUnitLoc(player, 0);
        row = 0;
        a = 0;
        b = 0;
        c = 0;
        hi = pos >> 8;
        lo = pos & 0xFF;
        for (; row < 7; row++) {
            for (col = 0; col < 7; col++) {
                v = SzDuel_GetMapUnitID(row, col);
                if (v < 0) {
                    continue;
                }
                vx = v >> 8;
                vy = v & 0xFF;
                if (player == Ta_GetCurrentSide(vx, vy)) {
                    continue;
                }
                if (Ta_IsSquareRange(lo, hi, row, col, Ta_GetLDRange(player)) == 0) {
                    continue;
                }
                if ((SzDuel_GetUnitKind(vx, vy) >> 5) == 0) {
                    if (Ta_IsLDAbl(0x10, player)) {
                        if (Ta_IsLD_DestObj(player, SzDuel_GetUnitKind(vx, vy) & 0x1F) && vy != 0) {
                            a = ConvUnitIDtoFlagList(a, vx, vy);
                        }
                    }
                    if (Ta_IsLDAbl(0xF, player) && Ta_IsLD_CurseObj(player, SzDuel_GetUnitKind(vx, vy) & 0x1F) &&
                        vy != 0 && SzDuel_GetUnitSpellRest(vx, vy) == 0) {
                        b = ConvUnitIDtoFlagList(b, vx, vy);
                    }
                }
                if (Ta_IsLDAbl(0xD, player) && SzDuel_GetUnitStatus(vx, vy, 4) == 0 && vy != 0) {
                    c = ConvUnitIDtoFlagList(c, vx, vy);
                }
            }
        }
        if (a > 0 || b > 0 || c > 0) {
            res[0] = 0x71;
            res[1] = a | 0x80000000;
            res[2] = b;
            res[3] = c;
            return ((phase + 1) << 16) | 1;
        }
        return (phase + 1) << 16;
    case 3:
        for (i = 1; i <= 5; i++) {
            if (SzDuel_GetUnitStatus(player, i, 4) == 1) {
                SzData_CalcExp(player, SzDuel_GetUnitCardNo(player, i), 0, 4);
            } else {
                SzData_CalcExp(player, SzDuel_GetUnitCardNo(player, i), 0, 2);
            }
        }
        n = Ta_SearchUncTypeNaturalEffectUserNum(0x55);
        for (i = 1; i <= 11; i++) {
            mine = SzDuel_GetUnitLoc(player, i);
            if (Ta_SearchUncTypeNaturalEffectUserNum(0x47) <= 0) {
                if ((hp = SzDuel_GetUnitCurseRest(player, i)) > 0 && player == Ta_IsUnitControl(player, i) && SzDuel_GetUnitCurseFlag(player, i) == 0 && hp < 0xFF) {
                    if (n > 0) {
                        SzDuel_SetUnitCurseRest(player, i, GetCap(0, hp - 2));
                    } else {
                        SzDuel_SetUnitCurseRest(player, i, hp - 1);
                    }
                }
                if ((hp = SzDuel_GetUnitCurseRest((player == 0) ? 1 : 0, i)) > 0 && player == Ta_IsUnitControl((player == 0) ? 1 : 0, i) &&
                    SzDuel_GetUnitCurseFlag((player == 0) ? 1 : 0, i) == 0 && hp < 0xFF) {
                    if (n > 0) {
                        SzDuel_SetUnitCurseRest((player == 0) ? 1 : 0, i, GetCap(0, hp - 2));
                    } else {
                        SzDuel_SetUnitCurseRest((player == 0) ? 1 : 0, i, hp - 1);
                    }
                }
            }
            other = SzDuel_GetUnitLoc((player == 0) ? 1 : 0, 0);
            if (SzDuel_GetUnit(player, i)) {
                if (!(Ta_IsLDAbl(0xF, (player == 0) ? 1 : 0) &&
                      Ta_IsLD_CurseObj((player == 0) ? 1 : 0, SzDuel_GetUnitKind(player, i) & 0x1F) &&
                      Ta_IsSquareRange(other & 0xFF, other >> 8, mine & 0xFF, mine >> 8,
                                    Ta_GetLDRange((player == 0) ? 1 : 0))) &&
                    TaPerm_IsPermCurseActive(player, i) == 0) {
                    SzDuel_SetUnitSpellRest(player, i, 0);
                }
            }
            mine = SzDuel_GetUnitLoc((player == 0) ? 1 : 0, i);
            other = SzDuel_GetUnitLoc(player, 0);
            if (SzDuel_GetUnit((player == 0) ? 1 : 0, i)) {
                if (!(Ta_IsLDAbl(0xF, player) &&
                      Ta_IsLD_CurseObj(player, SzDuel_GetUnitKind((player == 0) ? 1 : 0, i) & 0x1F) &&
                      Ta_IsSquareRange(other & 0xFF, other >> 8, mine & 0xFF, mine >> 8, Ta_GetLDRange(player))) &&
                    TaPerm_IsPermCurseActive((player == 0) ? 1 : 0, i) == 0) {
                    SzDuel_SetUnitSpellRest((player == 0) ? 1 : 0, i, 0);
                }
            }
        }
        for (i = 0; i <= 11; i++) {
            SzDuel_SetUnitCurseFlag(player, i, 0);
            SzDuel_SetUnitCurseFlag((player == 0) ? 1 : 0, i, 0);
        }
        return (phase + 1) << 16;
    case 4:
        for (i = 0; i < 8; i++) {
            v = Ta_GetSommonPiecePreference(player, i);
            if (v < 0) {
                continue;
            }
            vy = v & 0xFF;
            vx = v >> 8;
            w = SzDuel_GetMapUnitID(vy, vx);
            if (w >= 0) {
                if (player == Ta_IsUnitControl(w >> 8, w & 0xFF)) {
                    if (SzDuel_GetField(vy, vx) != 8) {
                        return (phase + 1) << 16;
                    }
                }
            } else {
                if (SzDuel_GetField(vy, vx) != 8) {
                    return (phase + 1) << 16;
                }
            }
        }
        return ((phase + 1) << 16) | 5;
    case 5:
        if (player != SzDuel_GetTurnFirst()) {
            if (SzDuel_GetTurnCount() >= 100) {
                return 0xFF0008;
            }
        }
        return 0xFF0000;
    }
    return 0xFF0000;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

extern int func_001DEE50_b(int index);

/* Ends the duel for side `nSide` by condition `bCond`: experience and results. */
int Ta_Do_DuelEnd(int nSide, unsigned char bCond)
{
    int i;
    int gCount_1;
    int gCount_2;

    for (i = 1; i <= 5; i++) {
        if (SzDuel_GetUnitStatus(nSide, i, 4)) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, i), 0, 6);
        } else {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, i), 0, 4);
        }
    }
    gCount_1 = func_001DEE50_b(nSide);
    gCount_2 = func_001DEE50_b(nSide == 0 ? 1 : 0);
    switch (bCond) {
    case 0:
        if (gCount_1 < 5) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 40);
        } else if (gCount_1 < 10) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 32);
        } else if (gCount_1 < 15) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 24);
        } else {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 16);
        }
        if (gCount_2 < 5) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -32);
        } else if (gCount_2 < 10) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -24);
        } else if (gCount_2 < 15) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -16);
        } else {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -8);
        }
        break;
    case 1:
        if (gCount_1 < 5) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 32);
        } else if (gCount_1 < 10) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 24);
        } else if (gCount_1 < 15) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 16);
        } else {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 8);
        }
        if (gCount_2 < 5) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -28);
        } else if (gCount_2 < 10) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -20);
        } else if (gCount_2 < 15) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -12);
        } else {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -4);
        }
        break;
    case 2:
        if (gCount_1 < 5) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 44);
        } else if (gCount_1 < 10) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 36);
        } else if (gCount_1 < 15) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 28);
        } else {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 20);
        }
        if (gCount_2 < 5) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -36);
        } else if (gCount_2 < 10) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -28);
        } else if (gCount_2 < 15) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -20);
        } else {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -12);
        }
        break;
    case 3:
        if (gCount_1 < 5) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 48);
        } else if (gCount_1 < 10) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 40);
        } else if (gCount_1 < 15) {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 32);
        } else {
            SzData_CalcExp(nSide, func_001E1030_b(nSide, 0), 0, 24);
        }
        if (gCount_2 < 5) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -40);
        } else if (gCount_2 < 10) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -32);
        } else if (gCount_2 < 15) {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -24);
        } else {
            SzData_CalcExp(nSide == 0 ? 1 : 0, func_001E1030_b(nSide == 0 ? 1 : 0, 0), 0, -16);
        }
        break;
    default:
        return -1;
    }
    return 1;
}

typedef struct Context_00273460 {
    u8 pad0[8];
    s32 cards;
} Context_00273460;

typedef struct State_00273460 {
    u16 alpha;
    u16 pad2;
    u16 phase;
    u8 ids[0x1A];
    s32 cards[45];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00273460;

typedef struct Setup_00273460 {
    s32 card;
    s32 x;
    s32 y;
    s32 z;
} Setup_00273460;

/* Effect script 112, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_112(void *eInfo, void *Temp, s32 ID) {
    Setup_00273460 setup;
    s32 complete;
    Setup_00273460 *config = &setup;
    State_00273460 *walk;
    u8 *id;
    s32 index;
    s32 card;
    State_00273460 *state = Temp;
    Context_00273460 *context = eInfo;

    setup.card = 999;
    setup.x = 0;
    setup.y = 0;
    setup.z = 0;
    complete = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(state);
        Ta_AllUnitFade(context, state, ID, -1, 1, 1);
        state->alpha = 128;
        TaEffect_LoadModule(state, 612);
        for (ID = 0; ID < Ta_GetUnitNumFrom22bitFlagList(context->cards); ID++) {
            card = Ta_GetUnitOwnerIDFromLstCount(context->cards, ID);
            SzEffect_SetBusyFlag2(card, 0);
            TaUtil_DoOpen(card >> 8, card & 255, 1);
        }
        TaView_ReqStdCompleteView(30);
        return 1;
    }
    switch (state->phase) {
    case 0:
        ID = 0;
        if (state->alpha > 48) {
            state->alpha -= 15;
        } else {
            for (ID = 0; ID < Ta_GetUnitNumFrom22bitFlagList(context->cards); ID++) {
                if (SzEffect_IsModelStandby2(Ta_GetUnitOwnerIDFromLstCount(context->cards, ID)) != 0) {
                    complete++;
                }
            }
            if (complete == Ta_GetUnitNumFrom22bitFlagList(context->cards)) {
                if (TaEffect_IsLoadModule(state) == 1) {
                    if (state->timer++ >= 46) {
                        if (complete == 1) {
                            TaView_ReqFocusCamera(0, Ta_GetUnitOwnerIDFromLstCount(context->cards, 0), 100, 180);
                        }
                        SzDuel_OpenMsgPopup(0, -120, 80, 276);
                        Ta_SetEffectDependOnFlagLst(context, state, config, 612);
                        state->timer = 0;
                        state->phase++;
                    }
                }
            }
            state->alpha = 48;
        }
        if (state->alpha < 48) {
            state->alpha = 48;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        break;
    case 1:
        index = 0;
        walk = state;
        for (; index < state->count; index++) {
            id = &state->ids[index];
            if (SzEffect_IsUse(*id) == 1) {
                TaEffect_SetOuchMotion((u16)walk->cards[0]);
                if ((walk->cards[0] >> 16) == 0) {
                    if (state->timer++ >= 32) {
                        card = walk->cards[0];
                        Ta_UnitFade((card & 65535) >> 8, card & 255, -1, 1, 3);
                        walk->cards[0] |= 0x10000;
                    }
                }
                if (SzEffect_GetStatus(*id) == 2) {
                    card = walk->cards[0];
                    if (card >= 0) {
                        SzEffect_SetBusyFlag2(card & 65535, 1);
                        card = walk->cards[0];
                        Ta_DelUnit((card & 65535) >> 8, card & 255);
                        walk->cards[0] = -1;
                    }
                }
            } else {
                complete++;
            }
            walk = (State_00273460 *)((u8 *)walk + 4);
        }
        if (complete >= state->count) {
            Ta_AllUnitFade(context, state, ID, 1, 0, 1);
            state->timer = 0;
            SzDuel_CloseMsgPopup();
            TaView_RestoreOriginalView(state, 16);
            state->phase++;
        }
        break;
    default:
        state->alpha += 15;
        if (state->alpha > 128) {
            state->alpha = 128;
        }
        SzEffect_SetBlackOutForDuel((u8)state->alpha);
        if (state->alpha == 128) {
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

typedef struct Masks_002738B0 {
    u32 unknown;
    u32 first : 22;
    u32 firstFlags : 10;
    s32 second;
    u32 third : 22;
    u32 thirdFlags : 9;
    u32 inverted : 1;
} Masks_002738B0;

typedef struct State_002738B0 {
    u16 player;
    u16 unknown02;
    u16 step;
    u8 handles[0x1A];
    s32 counter;
    u8 unknown24[0xB0];
    u8 count;
    u8 unknownD5[0x2D];
    u16 ticks;
} State_002738B0;

typedef struct Command_002738B0 {
    s32 id;
    s32 flags;
    s32 position;
    s32 argument;
} Command_002738B0;

/* Effect script 113, step `ID`: its camera, fades and effect module; it destroys units, binds units with a spell,
   turns cards face up. */
s32 Ta_Eff_113(void *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_SetUnitSpellRest();
    Command_002738B0 command;
    Command_002738B0 *cmd = &command;
    Masks_002738B0 *masks = eInfo;
    State_002738B0 *state = Temp;
    s32 position;
    s32 player;
    s32 position0;
    s32 i;
    s32 ready;
    s32 column;
    s32 row;
    s32 secondIndex;
    s32 secondCount;
    s32 thirdIndex;
    s32 thirdCount;
    s32 firstCount;
    s32 firstIndex;
    s32 packed;

    command.id = 999;
    command.flags = 0;
    command.position = 0;
    command.argument = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(state);
        if (((u32 *)masks)[3] >> 31) {
            player = (SzDuel_GetTurnOwner() == 0) ? 1 : 0;
        } else {
            player = SzDuel_GetTurnOwner();
        }
        state->player = player;
        position = SzDuel_GetUnitLoc(state->player, 0);
        TaView_ReqFocusCamera(0, state->player << 8, 300, 300);
        SzDuel_OpenMsgPopup(0, -120, 80, 270);
        if (masks->first) {
            Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                         Ta_IsLDAbl(9, state->player), 1, 1, 16);
        } else if (masks->second) {
            Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                         Ta_IsLDAbl(9, state->player), 1, 1, 15);
        } else if (masks->third) {
            Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                         Ta_IsLDAbl(9, state->player), 1, 1, 13);
        }
        TaEffect_LoadModule(state, 0x265);
        if (masks->first) {
            TaEffect_LoadModule(state, 0x25B);
        }
        if (masks->second) {
            TaEffect_LoadModule(state, 0x1F4);
        }
        if (masks->third) {
            TaEffect_LoadModule(state, 0x201);
        }
        return 1;
    }

    switch (state->step) {
    case 0:
        if (TaEffect_IsLoadModule(state) == 1) {
            position0 = SzDuel_GetUnitLoc(state->player, 0);
            Ta_SetRangeVisual(position0 & 0xFF, position0 >> 8, 0,
                         Ta_IsLDAbl(9, state->player), 0, -1, 16);
            cmd->id = 0x265;
            cmd->flags = 0;
            cmd->position = state->player << 8;
            cmd->argument = 0;
            state->handles[0] = Ta_Do_Effect((s32 *)cmd, state);
            state->counter = 0;
            state->step++;
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->handles[0]) == 1) {
            return 1;
        }
        TaView_ReqStdCompleteView(16);
        state->step++;
        return 1;
    case 2:
        if (state->ticks++ >= 16) {
            if (masks->first) {
                Ta_SetEffectDependOnFlagLst3(masks, state, (s32 *)cmd, 0x25B);
            }
            if (masks->second) {
                Ta_SetEffectDependOnFlagLst(masks, state, (s32 *)cmd, 0x1F4);
            }
            if (masks->third) {
                Ta_SetEffectDependOnFlagLst2(masks, state, (s32 *)cmd, 0x201);
            }
            state->step++;
        }
        return 1;
    case 3:
        i = 0;
        ready = 0;
        while (i < state->count) {
            if (SzEffect_IsUse(state->handles[i]) == 0) {
                ready++;
            }
            i++;
        }
        if (state->count == ready) {
            state->step++;
        }
        return 1;
    case 4:
        firstCount = Ta_GetUnitNumFrom22bitFlagList(masks->first);
        for (firstIndex = 0; firstIndex < firstCount; firstIndex++) {
            packed = Ta_GetUnitOwnerIDFromLstCount(masks->first, firstIndex);
            Ta_DelUnit(packed >> 8, packed & 0xFF);
        }
        secondCount = Ta_GetUnitNumFrom22bitFlagList(masks->second);
        for (secondIndex = 0; secondIndex < secondCount; secondIndex++) {
            packed = Ta_GetUnitOwnerIDFromLstCount(masks->second, secondIndex);
            row = packed >> 8;
            column = packed & 0xFF;
            SzDuel_SetUnitSpellRest(row, column, 255);
            SzDuel_SetUnitStatus(row, column, 0, 1);
        }
        thirdCount = Ta_GetUnitNumFrom22bitFlagList(masks->third);
        for (thirdIndex = 0; thirdIndex < thirdCount; thirdIndex++) {
            packed = Ta_GetUnitOwnerIDFromLstCount(masks->third, thirdIndex);
            TaUtil_DoOpen(packed >> 8, packed & 0xFF, 1);
        }
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(state, 16);
        state->ticks = 0;
        state->step++;
        break;
    default:
        if (state->ticks++ > 16) {
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

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct jp_6989c_273e60 {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_68cb4_273e60 {
    int fLoad : 1;
    unsigned char bModNum : 5;
    unsigned short wModule[24];
    unsigned char bModCond[24];
};
struct jp_69942_273e60 {
    unsigned short wCount_1;
    unsigned short wCount_2;
    unsigned short wLvl;
    unsigned char eID[24];
    int ePos[24];
    struct jp_68cb4_273e60 eMod;
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
extern int func_00255AC0_273e60(struct jp_69942_273e60 *q, int id);
extern void func_00260A70_273e60(struct jp_69942_273e60 *Temp, unsigned char b);
extern int func_001E1CB0_b(int a, int b);

/* Effect script BTL_000, step `ID`: its camera, fades and effect module; it changes attack or defence, changes
   life points. */
int Ta_Eff_BTL_000(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_6989c_273e60 * eInfo = eInfo_v;
    struct jp_69942_273e60 * Temp = Temp_v;
    int stored;
    struct jp_6989c_273e60 eCall;
    struct jp_6989c_273e60 *pCall = &eCall;
    int temp;
    int i;
    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    SzDuel_SetWindowDraw(0);
    if (eInfo == 0 || Temp == 0 || pCall == 0) {
        SzDuel_CloseMsgPopup();
        return 0;
    }
    if (ID >= 0) {
        InitEffectTemp(Temp);
        if (Ta_IsLDAbl(6, eInfo->dwTo) != 0) {
            func_00255AC0_273e60(Temp, 557);
            Temp->wLvl = 16;
        }
        if (((eInfo->dwPar >> 20) & 3) != 0 || ((eInfo->dwPar >> 22) & 3) != 0) {
            func_00255AC0_273e60(Temp, 513);
        }
        func_00255AC0_273e60(Temp, 604);
        func_00255AC0_273e60(Temp, 605);
        func_00260AF0_b(0, eInfo->dwFrom, 300, 280);
        Temp->wCount_1 = 128;
        return 1;
    }
    switch (Temp->bCamLvl) {
    case 0:
        if (Temp->wCamTime++ == 0) {
            SzSound_PlaySE(0, 39);
            SzGame_SetAutoBlur(6);
            func_00260AF0_b(12, eInfo->dwFrom, 100, 180);
            return 1;
        }
        if (Temp->wCamTime >= 12) {
            SzGame_SetAutoBlur(4);
        }
        if (Temp->wCamTime >= 24) {
            if (func_001E1E10_b(eInfo->dwFrom >> 8, eInfo->dwFrom & 0xFF) == 255) {
                if (func_001E1CB0_b(eInfo->dwFrom >> 8, eInfo->dwFrom & 0xFF) == 128) {
                    if (SzEffect_IsModelStandby2(eInfo->dwFrom) != 0) {
                        SzGame_SetAutoBlur(0);
                        func_00260AF0_b(0, eInfo->dwTo << 8, 300, 280);
                        Temp->wCamTime = 0;
                        Temp->bCamLvl++;
                    }
                }
            }
        }
        return 1;
    case 1:
        if (Temp->wCamTime++ == 0) {
            SzSound_PlaySE(0, 39);
            SzGame_SetAutoBlur(6);
            func_00260AF0_b(12, eInfo->dwTo << 8, 100, 180);
            return 1;
        }
        if (Temp->wCamTime >= 12) {
            SzGame_SetAutoBlur(4);
        }
        if (Temp->wCamTime >= 24) {
            if (SzEffect_IsModelStandby2(eInfo->dwTo << 8) != 0) {
                SzGame_SetAutoBlur(0);
                func_00260A70_273e60(Temp, 0);
                Temp->wCamTime = 0;
                Temp->bCamLvl++;
            }
        }
        return 1;
    default:
        break;
    }
    if (TaEffect_IsLoadModule(Temp) != 1) {
        return 1;
    }
    switch (Temp->wLvl) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) == 1) {
            SzEffect_SetBusyFlag2(eInfo->dwFrom, 1);
            SzEffect_SetBusyFlag2(eInfo->dwTo << 8, 1);
            if (((eInfo->dwPar >> 20) & 3) != 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 260);
                pCall->eNO = 513;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwFrom;
                pCall->dwPar = 0;
                

                if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) >= 0) {
                    Temp->oNum++;
                }
            }
            if (((eInfo->dwPar >> 22) & 3) != 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 260);
                pCall->eNO = 513;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = 0;
                if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) > 0) {
                    Temp->oNum++;
                }
            }
            Temp->wLvl++;
        }
        return 1;
    case 1:
        if (Temp->oNum > 0) {
            for (i = 0; i < Temp->oNum; i++) {
                if (SzEffect_IsUse(Temp->eID[i]) != 0) {
                    return 1;
                }
            }
        }
        SzDuel_CloseMsgPopup();
        Temp->oNum = 0;
        Temp->wLvl++;
        return 1;
    case 2:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, -1)) > 0) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        } else {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
            Temp->wLvl++;
        }
        return 1;
    case 3:
        temp = Ta_GetLPRevByNaturalEffect(44, (unsigned short)eInfo->dwPar);
        pCall->eNO = 604;
        pCall->dwFrom = eInfo->dwFrom;
        pCall->dwTo = 0;
        if (temp == 0) {
            temp = 0x30000;
        }
        pCall->dwPar = temp;
        Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp);
        Temp->ePos[Temp->oNum] = 0;
        Temp->oNum++;
        Temp->wLvl++;
        return 1;
    case 4:
        if (SzEffect_IsUse(Temp->eID[Temp->oNum - 1]) != 0) {
            if (SzEffect_GetStatus(Temp->eID[Temp->oNum - 1]) == 2) {
                if (Temp->ePos[Temp->oNum - 1] == 1) {
                    SzSound_PlaySE(1, 65);
                }
                Temp->ePos[Temp->oNum - 1]++;
            }
            return 1;
        }
        pCall->eNO = 605;
        pCall->dwFrom = eInfo->dwFrom;
        pCall->dwTo = 0;
        pCall->dwPar = 0;
        Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp);
        Temp->oNum++;
        SzDuel_CalcLP(eInfo->dwTo, 1, Ta_GetLPRevByNaturalEffect(44, (unsigned short)eInfo->dwPar));
        if (SzDuel_GetLP(eInfo->dwTo) > 0) {
            SzData_CalcExp(eInfo->dwFrom >> 8, func_001E1030_b(eInfo->dwFrom >> 8, eInfo->dwFrom & 0xFF), 0, 20);
        } else {
            SzData_CalcExp(eInfo->dwFrom >> 8, func_001E1030_b(eInfo->dwFrom >> 8, eInfo->dwFrom & 0xFF), 0, 24);
        }
        SzData_CalcExp(eInfo->dwTo, func_001E1030_b(eInfo->dwTo, 0), 0, -8);
        Temp->wLvl++;
        return 1;
    case 5:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, 1)) < 128) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        }
        if (SzEffect_IsUse(Temp->eID[Temp->oNum - 1]) != 0) {
            if (Temp->fObj2++ == 20) {
                SzSound_PlaySE(0, 2);
            }
            return 1;
        }
        Temp->wLvl++;
        break;
    case 16:
        SzDuel_OpenMsgPopup(0, -120, 80, 270);
        pCall->eNO = 557;
        pCall->dwFrom = 0;
        pCall->dwTo = eInfo->dwFrom;
        pCall->dwPar = 0;
        Temp->eID[0] = Ta_Do_Effect(pCall, Temp);
        Temp->wLvl++;
        break;
    case 17:
        if (SzEffect_IsUse(Temp->eID[0]) != 0) {
            return 1;
        }
        SzDuel_CloseMsgPopup();
        Temp->wLvl = 0;
        break;
    default:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, 1)) < 128) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
            return 1;
        }
        if ((eInfo->dwFrom >> 16) != 0) {
            if ((eInfo->dwFrom >> 31) == 0) {
                TaUtil_CalcUnitAP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1, (eInfo->dwFrom >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1, (eInfo->dwFrom >> 16) & 0x7FFF);
            } else {
                TaUtil_CalcUnitAP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 0, (eInfo->dwFrom >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 0, (eInfo->dwFrom >> 16) & 0x7FFF);
            }
        }
        SzEffect_SetBlackOutForDuel(128);
        SzEffect_SetBlackOutForMonster(128);
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
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
extern void func_00260A70_b(struct jp_69942 *Temp, unsigned char b);
extern void func_002503B0_b(int a, int b, unsigned char n);
extern int func_001DE2A0_b(int side);

/* Effect script BTL_001, step `ID`: its camera, fades and effect module; it destroys units, changes attack or
   defence, changes life points. */
int Ta_Eff_BTL_001(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_6989c * eInfo = eInfo_v;
    struct jp_69942 * Temp = Temp_v;
    int stored;
    struct jp_6989c eCall;
    struct jp_6989c *pCall = &eCall;
    int temp;
    int i;
    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    SzDuel_SetWindowDraw(0);
    if (eInfo == 0 || Temp == 0 || pCall == 0) {
        SzDuel_CloseMsgPopup();
        return 0;
    }
    if (ID >= 0) {
        InitEffectTemp(Temp);
        Temp->wCount_1 = 128;
        if (((eInfo->dwPar >> 20) & 3) != 0 || ((eInfo->dwPar >> 22) & 3) != 0) {
            func_00255AC0_b(Temp, 513);
        }
        func_00255AC0_b(Temp, 604);
        func_00255AC0_b(Temp, 605);
        func_00260AF0_b(0, (unsigned short)eInfo->dwFrom, 300, 280);
        return 1;
    }
    switch (Temp->bCamLvl) {
    case 0:
        if (Temp->wCamTime++ == 0) {
            SzSound_PlaySE(0, 39);
            SzGame_SetAutoBlur(6);
            func_00260AF0_b(12, (unsigned short)eInfo->dwFrom, 100, 180);
            return 1;
        }
        if (Temp->wCamTime >= 12) {
            SzGame_SetAutoBlur(4);
        }
        if (Temp->wCamTime >= 24) {
            if (func_001E1E10_b((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF) == 255) {
                if (func_001E1CB0_b((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF) == 128) {
                    if (SzEffect_IsModelStandby2((unsigned short)eInfo->dwFrom) != 0) {
                        SzGame_SetAutoBlur(0);
                        func_00260AF0_b(0, (unsigned short)eInfo->dwTo, 300, 280);
                        Temp->wCamTime = 0;
                        Temp->bCamLvl++;
                    }
                }
            }
        }
        return 1;
    case 1:
        if (Temp->wCamTime++ == 0) {
            SzSound_PlaySE(0, 39);
            SzGame_SetAutoBlur(6);
            func_00260AF0_b(12, (unsigned short)eInfo->dwTo, 100, 180);
            return 1;
        }
        if (Temp->wCamTime >= 12) {
            SzGame_SetAutoBlur(4);
        }
        if (Temp->wCamTime >= 24) {
            if (func_001E1E10_b((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF) == 255) {
                if (func_001E1CB0_b((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF) == 128) {
                    if (SzEffect_IsModelStandby2((unsigned short)eInfo->dwTo) != 0) {
                        SzGame_SetAutoBlur(0);
                        func_00260A70_b(Temp, 0);
                        Temp->wCamTime = 0;
                        Temp->bCamLvl++;
                    }
                }
            }
        }
        return 1;
    }
    switch (Temp->wLvl) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) == 1) {
            SzEffect_SetBusyFlag2((unsigned short)eInfo->dwFrom, 1);
            SzEffect_SetBusyFlag2((unsigned short)eInfo->dwTo, 1);
            if (((eInfo->dwPar >> 20) & 3) != 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 260);
                pCall->eNO = 513;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwFrom;
                pCall->dwPar = 0;
                

                if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) >= 0) {
                    Temp->oNum++;
                }
            }
            if (((eInfo->dwPar >> 22) & 3) != 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 260);
                pCall->eNO = 513;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = 0;
                if ((stored = (Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp))) > 0) {
                    Temp->oNum++;
                }
            }
            Temp->wLvl++;
        }
        return 1;
    case 1:
        if (Temp->oNum > 0) {
            for (i = 0; i < Temp->oNum; i++) {
                if (SzEffect_IsUse(Temp->eID[i]) != 0) {
                    return 1;
                }
            }
        }
        SzDuel_CloseMsgPopup();
        Temp->oNum = 0;
        Temp->wLvl++;
        return 1;
    case 2:
        Temp->wCamTime++;
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, -1)) > 0) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        } else {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
            if (Temp->wCamTime >= 8) {
                if ((unsigned short)eInfo->dwPar == 0xFFFF) {
                    temp = 0;
                } else {
                    temp = Ta_GetLPRevByNaturalEffect(44, (unsigned short)eInfo->dwPar);
                }
                if (temp == 0) {
                    if (((eInfo->dwPar >> 28) & 1) == 1) {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | (temp | 0x20000) | (((eInfo->dwPar >> 22) & 1) << 20);
                    } else {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | (temp | 0x30000) | (((eInfo->dwPar >> 22) & 1) << 20);
                    }
                } else {
                    if (((eInfo->dwPar >> 28) & 1) == 1) {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | (temp | 0x10000) | (((eInfo->dwPar >> 22) & 1) << 20);
                    } else {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | temp | (((eInfo->dwPar >> 22) & 1) << 20);
                    }
                }
                if ((stored = (Temp->eID[0] = Ta_Do_Effect(pCall, Temp))) >= 0) {
                    Temp->ePos[0] = 0;
                    Temp->oNum++;
                }
                pCall->eNO = 605;
                pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = (((eInfo->dwPar >> 19) & 1) << 1) | ((eInfo->dwPar >> 18) & 1);
                Temp->eID[Temp->oNum] = Ta_Do_Effect(pCall, Temp);
                Temp->ePos[Temp->oNum] = 0;
                SzEffect_Sleep(Temp->eID[Temp->oNum], 1);
                Temp->wLvl++;
            }
        }
        return 1;
    case 3:
        if (SzEffect_IsUse(Temp->eID[0]) != 0) {
            if (SzEffect_GetStatus(Temp->eID[0]) == 2) {
                switch (Temp->ePos[0]) {
                case 0:
                    Temp->ePos[0]++;
                    if (func_001DE2A0_b(SzDuel_GetTurnOwner()) != 0) {
                        if ((unsigned short)eInfo->dwPar != 0xFFFF) {
                            if (TaTuto_IsTuto(SzDuel_GetTurnOwner()) == 0) {
                                SzEffect_Sleep(Temp->eID[0], 1);
                                return 4;
                            }
                        }
                    }
                    break;
                case 1:
                case 2:
                    func_00255AC0_b(Temp, 500);
                    Temp->ePos[0]++;
                    SzSound_PlaySE(1, 65);
                    break;
                }
            }
            return 1;
        }
        Temp->wCount_1 = 0;
        SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
        SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        if (((eInfo->dwPar >> 16) & 1) == 1 && (temp = (unsigned short)eInfo->dwPar) != 0xFFFF) {
            SzDuel_CalcLP(Ta_IsUnitControl((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF), 1, Ta_GetLPRevByNaturalEffect(44, temp));
        } else if (((eInfo->dwPar >> 17) & 1) == 1 && (temp = (unsigned short)eInfo->dwPar) != 0xFFFF) {
            SzDuel_CalcLP(Ta_IsUnitControl((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF), 1, Ta_GetLPRevByNaturalEffect(44, temp));
        }
        SzEffect_Sleep(Temp->eID[Temp->oNum++], 0);
        Temp->fObj2 = 0;
        Temp->wLvl++;
        return 1;
    case 4:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, 1)) < 128) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        }
        if (SzEffect_IsUse(Temp->eID[Temp->oNum - 1]) != 0) {
            switch (Temp->fObj2++) {
            case 0:
                if (((eInfo->dwPar >> 19) & 1) != 0) {
                    Temp->ePos[Temp->oNum - 1]++;
                    SzSound_PlaySE(1, 66);
                    SzSound_PlaySE(1, 45);
                }
                if (((eInfo->dwPar >> 18) & 1) != 0) {
                    Temp->ePos[Temp->oNum - 1]++;
                    SzSound_PlaySE(1, 66);
                    SzSound_PlaySE(1, 45);
                }
                break;
            case 20:
                if (Temp->ePos[Temp->oNum - 1] == 0) {
                    if (((eInfo->dwPar >> 19) & 1) == 0) {
                        SzSound_PlaySE(0, 2);
                    }
                    if (((eInfo->dwPar >> 18) & 1) == 0) {
                        SzSound_PlaySE(0, 2);
                    }
                }
                break;
            case 40:
                if (Temp->ePos[Temp->oNum - 1] > 0) {
                    if (((eInfo->dwPar >> 19) & 1) == 0) {
                        SzSound_PlaySE(0, 2);
                    }
                    if (((eInfo->dwPar >> 18) & 1) == 0) {
                        SzSound_PlaySE(0, 2);
                    }
                }
                break;
            }
            return 1;
        }
        if ((eInfo->dwPar >> 25) != 0) {
            if (((eInfo->dwPar >> 26) & 1) == 1 && ((eInfo->dwPar >> 19) & 1) == 0) {
                func_002503B0_b((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1);
                func_00260AF0_b(0, (unsigned short)eInfo->dwFrom, 180, 180);
                SzDuel_OpenMsgPopup(0, -120, 80, 264);
                pCall->eNO = 500;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwFrom;
                pCall->dwPar = 0;
                Temp->eID[0] = Ta_Do_Effect(pCall, Temp);
            } else if (((eInfo->dwPar >> 25) & 1) == 1 && ((eInfo->dwPar >> 18) & 1) == 0) {
                SzDuel_OpenMsgPopup(0, -120, 80, 264);
                func_002503B0_b((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 1);
                pCall->eNO = 500;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = 0;
                func_00260AF0_b(0, (unsigned short)eInfo->dwTo, 180, 180);
                Temp->eID[0] = Ta_Do_Effect(pCall, Temp);
            }
            Temp->wLvl = 5;
        }
        Temp->wLvl = 16;
        return 1;
    case 5:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, 1)) < 128) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
        }
        

        if (SzEffect_IsUse(Temp->eID[0]) == 0) {
            (void)Temp->wLvl;
        }
        break;
    default:
        if ((Temp->wCount_1 = Ta_CalcCtrlRate(Temp->wCount_1, 15, 1)) < 128) {
            SzEffect_SetBlackOutForDuel((unsigned char)Temp->wCount_1);
            SzEffect_SetBlackOutForMonster((unsigned char)Temp->wCount_1);
            return 1;
        }
        if (SzEffect_IsUse(Temp->eID[0]) == 1) {
            return 1;
        }
        SzDuel_CloseMsgPopup();
        func_00260A70_b(Temp, 0);
        if ((eInfo->dwFrom >> 16) != 0) {
            if ((eInfo->dwFrom >> 31) == 0) {
                TaUtil_CalcUnitAP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1, (eInfo->dwFrom >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1, (eInfo->dwFrom >> 16) & 0x7FFF);
            } else {
                TaUtil_CalcUnitAP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 0, (eInfo->dwFrom >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 0, (eInfo->dwFrom >> 16) & 0x7FFF);
            }
        }
        if ((eInfo->dwTo >> 16) != 0) {
            if ((eInfo->dwTo >> 31) == 0) {
                TaUtil_CalcUnitAP((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 1, (eInfo->dwTo >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 1, (eInfo->dwTo >> 16) & 0x7FFF);
            } else {
                TaUtil_CalcUnitAP((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 0, (eInfo->dwTo >> 16) & 0x7FFF);
                TaUtil_CalcUnitDP((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 0, (eInfo->dwTo >> 16) & 0x7FFF);
            }
        }
        if (SzDuel_GetWindowDisp() != 0) {
            SzDuel_SetWindowDraw(1);
        }
        SzDuel_CloseMsgPopup();
        return 0;
    }
    return 1;
}

typedef struct {
    u32 unknown;
    u16 first;
    u16 padding6;
    u16 second;
    u16 paddingA;
    u32 flags;
} Source_002755D0;

typedef struct {
    u16 first;
    u16 second;
    u8 padding[0xFE];
    u16 counter;
} State_002755D0;

typedef struct {
    s32 id;
    s32 x;
    s32 y;
    s32 z;
} Params_002755D0;

/* One frame of battle effect script 002. */
static inline s32 update_002755D0(void *arg0, void *arg1, void *params_arg, s32 arg2) {
    State_002755D0 *state = arg1;
    Source_002755D0 *source = arg0;
    Params_002755D0 *values = params_arg;
    s32 card;
    s32 position;
    u16 counter;

    if (source == NULL || state == NULL || values == NULL) {
        SzDuel_CloseMsgPopup();
        return 0;
    }
    if (arg2 >= 0) {
        InitEffectTemp(state);
        if ((source->flags & 1) == 1) {
            state->first = source->second;
            state->second = source->first;
        } else {
            state->first = source->first;
            state->second = source->second;
        }
        if ((source->flags >> 1) != 0) {
            card = Ta_GetCurrentSide((s32) state->second >> 8, state->second & 0xFF);
            position = SzDuel_GetUnitLoc(card, 0);
            Ta_SetRangeVisual(position & 0xFF, position >> 8, 0,
                         Ta_IsLDAbl(9, card), 1, 1, 11);
        }
        Ta_UnitFade((s32) state->first >> 8, state->first & 0xFF, -1, 1, 3);
        return 1;
    }
    counter = state->counter;
    state->counter = counter + 1;
    if ((s32) counter < 16) {
        return 1;
    }
    Ta_DelUnit((s32) state->first >> 8, state->first & 0xFF);
    SzDuel_CloseMsgPopup();
    return 0;
}

/* Clears battle effect script 002's work area. */
static inline void init_params_002755D0(void *params_arg) {
    Params_002755D0 *values = params_arg;

    values->id = 999;
    values->x = 0;
    values->y = 0;
    values->z = 0;
}

/* Effect script BTL_002, step `ID`: its camera, fades and effect module. */
s32 Ta_Eff_BTL_002(void *eInfo, void *Temp, s32 ID) {
    Params_002755D0 values;
    Params_002755D0 *params = &values;

    init_params_002755D0(params);
    return update_002755D0(eInfo, Temp, params, ID);
}

typedef struct State_00275740 {
    u8 pad0[4];
    u16 phase;
    u8 handle;
    u8 pad7[0xFB];
    u16 timer;
} State_00275740;

typedef struct Request_00275740 {
    s32 command;
    s32 value;
    u32 cell;
    s32 flag;
} Request_00275740;

/* Effect script 070, step `ID`: its camera, fades and effect module; it destroys units, turns cards face up. */
s32 Ta_Eff_070(u32 *eInfo, void *Temp, s32 ID) {
    extern s32 SzDuel_GetUnitOpenRate();
    extern s32 SzDuel_GetUnitCardNo();
    Request_00275740 data;
    Request_00275740 *request = &data;
    State_00275740 *state = Temp;
    u32 cell;

    data.command = 999;
    data.value = 0;
    data.cell = 0;
    data.flag = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        TaEffect_LoadModule(Temp, 0x259);
        TaEffect_LoadModule(Temp, 0x25A);
        cell = eInfo[1];
        TaUtil_DoOpen(cell >> 8, cell & 0xFF, 1);
        TaView_ReqFocusCamera(0, eInfo[1], 100, 180);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (TaEffect_IsLoadModule(Temp) == 1) {
            cell = eInfo[1];
            if (SzDuel_GetUnitOpenRate(cell >> 8, cell & 0xFF) == 0xFF) {
                SzDuel_OpenMsgPopup(0, -120, 80, 0x103);
                request->command = 0x25A;
                request->value = 0;
                request->cell = eInfo[1];
                request->flag = 0;
                state->handle = Ta_Do_Effect((s32 *)request, Temp);
                state->phase++;
            }
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->handle) == 1) {
            return 1;
        }
        cell = eInfo[1];
        SzDuel_SetUnitStatus(cell >> 8, cell & 0xFF, 0, 1);
        cell = eInfo[1];
        SzDuel_OpenMsgPopup(0, -120, 80, SzDuel_GetMsgName(SzDuel_GetUnitCardNo(cell >> 8, cell & 0xFF)));
        request->command = 0x259;
        request->value = 0;
        request->cell = eInfo[1];
        request->flag = 1;
        state->handle = Ta_Do_Effect((s32 *)request, Temp);
        state->phase++;
        break;
    case 2:
        if (SzEffect_IsUse(state->handle) == 1) {
            return 1;
        }
        cell = eInfo[1];
        Ta_DelUnit(cell >> 8, cell & 0xFF);
        state->phase++;
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(Temp, 16);
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

typedef struct {
    u32 unused;
    u32 source;
    u32 destination;
    s32 flag;
} Data_002759D0;

typedef struct {
    u8 unused[4];
    u16 phase;
    u8 id;
    u8 padding[0xFB];
    u16 timer;
} State_002759D0;

typedef struct {
    s32 code;
    s32 unused;
    s32 position;
    s32 flags;
} Command_002759D0;

/* Effect script 071, step `ID`: its camera, fades and effect module; it curses units, turns cards face up. */
s32 Ta_Eff_071(void *eInfo, void *Temp, s32 ID) {
    Command_002759D0 storage;
    Command_002759D0 *command = &storage;
    Data_002759D0 *data = eInfo;
    State_002759D0 *state = Temp;
    u32 position;
    u16 timer;
    extern s32 SzDuel_TrimUnitDir2();
    extern s32 SzDuel_GetUnitOpenRate();
    extern s32 SzDuel_GetUnitCardNo();

    command->code = 0x3E7;
    command->unused = 0;
    command->position = 0;
    command->flags = 0;
    SzDuel_SetWindowDraw(0);
    if (ID >= 0) {
        InitEffectTemp(Temp);
        position = data->source;
        TaUtil_DoOpen(position >> 8, position & 0xFF, 1);
        TaView_ReqFocusCamera(0, data->source, 0x64, 0xB4);
        TaEffect_LoadModule(Temp, 0x25A);
        if (data->flag != 0) {
            TaEffect_LoadModule(Temp, 0x1F4);
        } else {
            TaEffect_LoadModule(Temp, 0x201);
        }
        return 1;
    }
    switch (state->phase) {
    case 0:
        position = data->source;
        if (SzDuel_GetUnitOpenRate(position >> 8, position & 0xFF) == 0xFF) {
            if (TaEffect_IsLoadModule(Temp) == 1) {
                SzDuel_OpenMsgPopup(0, -0x78, 0x50, 0x103);
                command->code = 0x25A;
                command->unused = 0;
                command->position = data->source;
                command->flags = 0;
                state->id = Ta_Do_Effect((s32 *)command, Temp);
                state->phase++;
            }
        }
        break;
    case 1:
        if (SzEffect_IsUse(state->id) == 1) {
            return 1;
        }
        position = data->source;
        SzDuel_SetUnitStatus(position >> 8, position & 0xFF, 0, 1);
        TaView_ReqFocusCamera(0, data->destination, 0x64, 0xB4);
        if (data->flag != 0) {
            command->code = 0x1F4;
            command->unused = 0;
            command->position = data->destination;
            command->flags = 0;
        } else {
            command->code = 0x201;
            command->unused = 0;
            command->position = data->destination;
            command->flags = 0;
        }
        position = data->source;
        SzDuel_OpenMsgPopup(0, -0x78, 0x50,
            SzDuel_GetMsgName(SzDuel_GetUnitCardNo(position >> 8, position & 0xFF)));
        state->id = Ta_Do_Effect((s32 *)command, Temp);
        state->phase++;
        return 1;
    case 2:
        if (SzEffect_IsUse(state->id) == 1) {
            return 1;
        }
        if (data->flag != 0) {
            position = data->destination;
            Ta_SetUnitCurseRest(position >> 8, position & 0xFF, 0xFF);
        } else {
            position = data->destination;
            SzDuel_SetUnitStatus(position >> 8, position & 0xFF, 3, 0);
            position = data->destination;
            SzDuel_SetUnitStatus(position >> 8, position & 0xFF, 5, 0);
        }
        state->phase++;
        SzDuel_CloseMsgPopup();
        TaView_RestoreOriginalView(Temp, 0x10);
        break;
    default:
        timer = state->timer;
        state->timer = timer + 1;
        if (timer > 0x10) {
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
