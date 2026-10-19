/* Card rules: odds and ends (Ta_Eff_114, TaLib_*, Ta_Lk*). */

#include "common.h"

typedef struct State_0027E840 {
    u16 value;
    u8 pad2[2];
    u16 state;
    u8 id;
    u8 pad7[0xFB];
    u16 ticks;
} State_0027E840;

typedef struct Message_0027E840 {
    s32 code;
    s32 kind;
    s32 text;
    s32 flags;
} Message_0027E840;

/* Effect script 114, step `ID`: its camera, fades and effect module; it uses the graveyard, changes summon power. */
s32 Ta_Eff_114(void *eInfo, void *Temp, s32 ID) {
    Message_0027E840 messageData;
    State_0027E840 *state = Temp;
    u16 value;
    Message_0027E840 *message;

    messageData.code = 999;
    messageData.kind = 0;
    messageData.text = 0;
    messageData.flags = 0;
    message = &messageData;

    if (ID >= 0) {
        InitEffectTemp(Temp);
        state->value = 0x80;
        TaEffect_LoadModule(Temp, 0x271);
        SzDuel_CloseHandPopup();
        TaView_SetDestinyCamera(0);
        SzEffect_SetBusyFlag2(*(s32 *)((u8 *)eInfo + 4) << 8, 1);
        return 1;
    }

    SzDuel_SetWindowDraw(0);
    switch (state->state) {
    case 0:
        value = Ta_CalcCtrlRate(state->value, 15, -1);
        state->value = value;
        if (value > 0) {
            SzEffect_SetBlackOutForBattle(*(u8 *)state);
            SzEffect_SetBlackOutForDuel(*(u8 *)state);
        } else {
            SzEffect_SetBlackOutForBattle(*(u8 *)state);
            SzEffect_SetBlackOutForDuel(*(u8 *)state);
            if (TaEffect_IsLoadModule(Temp) == 1) {
                state->state++;
            }
        }
        break;
    case 1:
        SzDuel_OpenMsgPopup(0, -120, 80, 0x115);
        message->code = 0x271;
        message->kind = 0;
        message->text = SzDuel_GetUnitLoc(*(s32 *)((u8 *)eInfo + 4), 0);
        message->flags = 0;
        state->id = Ta_Do_Effect((s32 *)message, Temp);
        state->state++;
        break;
    case 2:
        if (SzEffect_IsUse(state->id) != 0) {
            if (state->ticks == 0) {
                SzSound_PlaySE(0, 0x22);
            }
            if (state->ticks++ == 19) {
                TaView_ReqBackFocusCamera(0, *(s32 *)((u8 *)eInfo + 4) << 8, 300, 300);
                SzSound_PlaySE(0, 0x25);
                SzSound_PlaySE(0, 0x24);
            }
            return 1;
        } else {
            SzDuel_CloseMsgPopup();
            TaView_RestoreOriginalView(Temp, 16);
            state->ticks = 0;
            state->value = 0;
            state->state++;
        }
        break;
    default:
        state->ticks++;
        value = Ta_CalcCtrlRate(state->value, 15, 1);
        state->value = value;
        if (value < 128) {
            SzEffect_SetBlackOutForBattle(*(u8 *)state);
            SzEffect_SetBlackOutForDuel(*(u8 *)state);
        } else if ((s32)state->ticks > 16) {
            SzEffect_SetBusyFlag2(*(s32 *)((u8 *)eInfo + 4) << 8, 0);
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

typedef struct Vec4_0027EB00 {
    f32 x, y, z, w;
} Vec4_0027EB00;

typedef union Scale_0027EB00 {
    Vec4_0027EB00 vector;
    struct { s32 x, y, z, w; } fixed;
} Scale_0027EB00;

typedef struct Flags_0027EB00 {
    s8 low : 5;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 high : 1;
} Flags_0027EB00;

typedef union Record_0027EB00 {
    __int128 data[10];
    struct {
        Vec4_0027EB00 position;
        Scale_0027EB00 scale;
        Vec4_0027EB00 transform;
        Vec4_0027EB00 rotation;
        u8 pad40[0x41];
        Flags_0027EB00 flags;
        u8 pad82[0x1E];
    } fields;
} Record_0027EB00;

typedef struct History_0027EB00 {
    Vec4_0027EB00 rotation;
    Vec4_0027EB00 scale;
    Vec4_0027EB00 position;
    u8 pad30[0x40];
} History_0027EB00;

typedef struct State_0027EB00 {
    History_0027EB00 history[5];
    Record_0027EB00 first;
    Record_0027EB00 second;
    Vec4_0027EB00 firstPosition;
    Vec4_0027EB00 firstScale;
    s32 firstAngles[3];
    s32 pad39C;
    f32 firstSpeedX;
    f32 firstSpeedY;
    u8 pad3A8[8];
    f32 firstX;
    f32 firstY;
    s32 firstActive;
    s32 pad3BC;
    Vec4_0027EB00 secondPosition;
    Vec4_0027EB00 secondScale;
    s32 secondAngles[3];
    s32 pad3EC;
    f32 secondSpeedX;
    f32 secondSpeedY;
    u8 pad3F8[8];
    f32 secondX;
    f32 secondY;
    s32 secondActive;
    s32 pad40C;
    s32 timer;
    s32 mode;
    s32 flags;
    s32 firstAlpha;
    s32 secondAlpha;
    s32 finish;
    u8 pad428[8];
} State_0027EB00;

/* Draws a card flying across the screen for an effect (effect `eInfo`, card `nID`). */
s32 TaLib_c615(void *pobj, void *eInfo, s32 nID) {
    s32 firstId;
    s32 secondId;
    Record_0027EB00 *first;
    Record_0027EB00 *second;
    s32 result;

    ExGetMyOT();
    firstId = *(s32 *) ((u8 *) eInfo + 4);
    secondId = *(s32 *) ((u8 *) eInfo + 8);
    first = (Record_0027EB00 *) SzEffect_GetCardRequest2(firstId);
    second = (Record_0027EB00 *) SzEffect_GetCardRequest2(secondId);
    if (first == 0 && second == 0) {
        return 8;
    }
    {
        State_0027EB00 *state = (State_0027EB00 *) pobj;

        if (nID >= 0) {
            func_00195108((s32) state, 0x430);
            Ta_LkInitCoordinate(state);
            if (first != 0) {
                state->first = *first;
            }
            if (second != 0) {
                state->second = *second;
            }
            if (first != 0) {
                SzEffect_SetBusyFlag2(firstId, 1);
                state->first.fields.flags.bit6 = 1;
                state->first.fields.flags.bit5 = 1;
            }
            if (second != 0) {
                SzEffect_SetBusyFlag2(secondId, 1);
                state->second.fields.flags.bit6 = 1;
                state->second.fields.flags.bit5 = 1;
            }
            state->flags = 0;
            state->mode = nID;
            state->timer = 14;
            state->finish = 0;
            if (first != 0) {
                *((u8 *) first + 0x43) = 0;
            }
            if (second != 0) {
                *((u8 *) second + 0x43) = 0;
            }
            state->secondAlpha = 128;
            state->firstAlpha = 128;
            state->firstX = -125.0f;
            state->firstY = -8.0f;
            state->secondX = 125.0f;
            state->secondY = -8.0f;
            if (first != 0) {
                state->flags |= 1;
                state->firstActive = 1;
                Ex3d_GetPointOnScreen(&state->first, state->firstX, state->firstY);
                state->firstPosition = first->fields.position;
                Ex3d_GetLookVector((s32) &state->first.fields.transform);
                state->firstAngles[2] = 0;
                state->firstAngles[1] = 0;
                state->firstAngles[0] = 0;
                state->first.fields.scale.fixed.x = 0;
                state->first.fields.scale.fixed.y = 0x10000;
                state->first.fields.scale.fixed.z = 0x10000;
                state->firstScale = first->fields.scale.vector;
                state->firstSpeedY = 0.1f;
                state->firstSpeedX = 0.1f;
                state->first.fields.rotation.x = 0.46875f;
                state->first.fields.rotation.y = 0.4891299903392792f;
            }
            if (second != 0) {
                s32 i;
                History_0027EB00 *history;

                state->flags |= 2;
                state->secondActive = 1;
                Ex3d_GetPointOnScreen(&state->second, state->secondX, state->secondY);
                state->secondPosition = second->fields.position;
                Ex3d_GetLookVector((s32) &state->second.fields.transform);
                state->secondAngles[2] = 0;
                state->secondAngles[1] = 0;
                state->secondAngles[0] = 0;
                state->second.fields.scale.fixed.x = 0;
                state->second.fields.scale.fixed.y = 0x10000;
                state->second.fields.scale.fixed.z = 0x10000;
                state->secondScale = second->fields.scale.vector;
                state->secondSpeedY = 0.1f;
                state->secondSpeedX = 0.1f;
                state->second.fields.rotation.x = 0.46875f;
                state->second.fields.rotation.y = 0.4891299903392792f;
                i = 0;
                history = state->history;
                do {
                    ++i;
                    history[1].position = state->second.fields.position;
                    history[1].scale = state->second.fields.scale.vector;
                    history[1].rotation = state->second.fields.rotation;
                    ++history;
                } while (i < 4);
            }
        }
        result = 0;
        Ta_LkSetCoordinate((u8 *) state);
        SzDuel_StartCardSession();
        if (state->mode == 0 && first != 0) {
            Ta_LkPrim_DrawCard(&state->first, state->firstAlpha, 0);
        }
        if (second != 0) {
            Ta_LkPrim_DrawCard(&state->second, state->secondAlpha, 0);
        }
        if (state->mode == 1) {
            Ex3d_GetPointOnScreen(&state->first, state->firstX, state->firstY);
            if (state->timer < 7) {
                Ta_LkOBJ_TransitVector(&state->second, &state->first, state->timer);
            }
            if (state->timer != 0) {
                --state->timer;
            } else {
                if (Ta_LkCheckFlag(state->flags, 31) == 0) {
                    state->flags |= 0x80000000;
                }
                state->timer = 27;
            }
        }
        SzDuel_FinishCardSession();
        {
            History_0027EB00 *history;
            s32 i;

            i = 3;
            history = &state->history[3];
            do {
                if (i != 0) {
                    history[1].position = history->position;
                    history[1].scale = history->scale;
                    history[1].rotation = history->rotation;
                } else {
                    history[1].position = state->second.fields.position;
                    history[1].scale = state->second.fields.scale.vector;
                    history[1].rotation = state->second.fields.rotation;
                }
                --i;
                --history;
            } while (i >= 0);
        }
        if (Ta_LkCheckFlag(state->flags, 31) != 0) {
            ++state->finish;
            if (state->finish == 4) {
                result = 2;
            } else if (state->finish > 4) {
                state->finish = 999;
            }
        }
        return result;
    }
}

/* Clears a screen-coordinate record. */
void Ta_LkInitCoordinate(void *coord) {
    f32 *values = coord;

    values[0] = values[1] = values[2] = values[3] = 1.0f;
    values[4] = values[5] = values[6] = values[7] = 0.0f;
    values[8] = values[9] = values[10] = values[11] = 0.0f;
}

typedef struct {
    f32 values[4][4];
} Matrix_0027F110;

/* Works out a screen-coordinate record from the view, scale, rotation and position. */
void Ta_LkSetCoordinate(u8 *coord) {
    Matrix_0027F110 matrix;

    RhView_GetWorldScreenMatrix(coord + 0x30);
    RhGeom_GetScaleRotXYZTransMatrix(&matrix, coord, coord + 0x10, coord + 0x20);
    RhGeom_MulMatrix((s32)(coord + 0x30), &matrix);
}

/* Whether bit `bitno` of `flags` is set. */
s32 Ta_LkCheckFlag(s32 flags, s32 bitno) {
    return !(flags & (1 << bitno)) ? 0 : 1;
}

typedef struct Vertex_0027F180 {
    u8 pad0[0x10];
    u64 lower : 32;
    u64 color : 24;
    u64 upper : 8;
    u8 pad18[3];
    u8 alpha;
    u8 pad1C[0x14];
} Vertex_0027F180;

typedef struct Count_0027F180 {
    s16 count : 12;
    s16 reserved : 4;
} Count_0027F180;

typedef struct Object_0027F180 {
    u8 pad0[0x78];
    Vertex_0027F180 *vertices;
    s32 field7C;
    s16 field80;
    Count_0027F180 field82;
    u8 pad84[0xC];
    s32 field90;
} Object_0027F180;

/* Draws a card at screen point `scrpnt` with fade `fade`. */
s32 Ta_LkPrim_DrawCard(void *pCardReq, s32 fade, f32 *scrpnt) {
    Object_0027F180 *object = pCardReq;
    s32 result;
    s32 i;

    if (scrpnt != NULL) {
        result = SzDuel_GetCardNodeOnScreen(object, 0, scrpnt[0], scrpnt[1]);
    } else {
        result = SzDuel_GetCardNode(object, 1);
    }
    for (i = 0; i < object->field82.count; i++) {
        object->vertices[i].color = 0xFFFFFF;
        object->vertices[i].alpha = fade;
    }
    if (result != 0) {
        SzDuel_SetupCard(object->field90, (s32) object);
    } else {
        SzDuel_SetupCard(0, (s32) object);
    }
    SzDuel_DrawCard((s32) object);
    return 0;
}

typedef struct Vec3_0027F290 {
    f32 x;
    f32 y;
    f32 z;
} Vec3_0027F290;

/* Moves `point` toward `target` over `timer` frames. */
void Ta_LkOBJ_TransitVector(void *point, void *target, s32 timer) {
    Vec3_0027F290 vec;
    f32 temp_f1;

    if (timer != 0) {
        vec.x = ((Vec3_0027F290 *)target)->x;
        vec.y = ((Vec3_0027F290 *)target)->y;
        vec.z = ((Vec3_0027F290 *)target)->z;
        Ta_LkSubVector(&vec, point);
        temp_f1 = (f32) timer;
        vec.x /= temp_f1;
        vec.y /= temp_f1;
        vec.z /= temp_f1;
        Ta_LkAddVector(point, &vec);
        return;
    }
    ((Vec3_0027F290 *)point)->x = ((Vec3_0027F290 *)target)->x;
    ((Vec3_0027F290 *)point)->y = ((Vec3_0027F290 *)target)->y;
    ((Vec3_0027F290 *)point)->z = ((Vec3_0027F290 *)target)->z;
}

/* Adds `velocity` to `target`. */
void Ta_LkAddVector(void *target, void *velocity) {
    f32 *dst = target;
    f32 *src = velocity;

    dst[0] += src[0];
    dst[1] += src[1];
    dst[2] += src[2];
}

/* Subtracts `velocity` from `target`. */
void Ta_LkSubVector(void *target, void *velocity) {
    f32 *dst = target;
    f32 *src = velocity;

    dst[0] -= src[0];
    dst[1] -= src[1];
    dst[2] -= src[2];
}
