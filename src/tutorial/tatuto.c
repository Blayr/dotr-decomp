/* The tutorial driver (TaTuto_*). */

#include "common.h"

/* Sets up tutorial `nTutoID` (its board, summon power and graveyard) for the computer opponent `pCtl`. */
void TaTuto_InitTutorial(u8 nTutoID, s32 pCtl) {
    TaTuto_InitTutoData(pCtl);
    switch (nTutoID) {
    case 32:
        TaTuto_Init032();
        break;
    case 35:
        SzDuel_CalcSummonPower(0, 4, 8);
        SzDuel_CalcSummonPower(1, 4, 8);
        break;
    case 36:
        func_0027F5B0();
        break;
    }
}

typedef struct Entry_0027F480 {
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
    s32 field_8;
    u8 flags : 2;
    u8 reserved : 6;
    u8 padding[3];
} Entry_0027F480;

typedef struct State_0027F480 {
    Entry_0027F480 entries[22];
    u16 indices[32];
    u8 flags : 5;
    u8 reserved : 3;
    u8 padding_1a1;
    u16 field_1a2;
    u16 field_1a4;
    u8 padding_1a6[10];
    f32 position[4];
    f32 rotation[4];
} State_0027F480;

/* Clears the tutorial data in `pCtl` and keeps the camera. */
void TaTuto_InitTutoData(s32 pCtl) {
    f32 *rotation;
    f32 *position;
    u8 *cursor;
    s32 j;
    s32 i;
    Entry_0027F480 *entry;
    State_0027F480 *state = (State_0027F480 *)pCtl;

    position = (f32 *)SzView_GetCP(0);
    rotation = SzView_GetLook(0);
    if (state != 0) {
        state->field_1a2 = 0;
        state->field_1a4 = 0;
        i = 0;
        entry = state->entries;
        do {
            entry->field_0 = 0xFFFF;
            entry->field_2 = 0xFF;
            entry->field_8 = -1;
            entry->field_4 = 0xFFFF;
            i += 1;
            entry->flags = 0;
            entry++;
        } while (i < 22);
        j = 0;
        cursor = (u8 *)state;
        do {
            j += 1;
            *(u16 *)(cursor + 0x160) = 0xFFFF;
            cursor += 2;
        } while (j < 32);
        state->flags = 0;
        state->position[0] = position[0];
        state->position[1] = position[1];
        state->position[2] = position[2];
        state->position[3] = position[3];
        state->rotation[0] = rotation[0];
        state->rotation[1] = rotation[1];
        state->rotation[2] = rotation[2];
        state->rotation[3] = rotation[3];
        state->indices[1] = 0;
    }
}

/* Sets up tutorial 32 (nothing to do). */
void TaTuto_Init032(void) {

}

/* Puts the tutorial's starting cards in the graveyard. */
void func_0027F5B0(void) {
    SzDuel_AddGrave(0, 0);
    SzDuel_AddGrave(0, 3);
    SzDuel_AddGrave(0, 6);
    SzDuel_AddGrave(0, 700);
    SzDuel_AddGrave(1, 0);
    SzDuel_AddGrave(1, 3);
    SzDuel_AddGrave(1, 6);
    SzDuel_AddGrave(1, 699);
}

typedef struct TutoCtl_0027F630 {
    u8 pad0[0x1A2];
    u16 step;
    u16 wait;
} TutoCtl_0027F630;

/* Plays the tutorial's hand-cursor hint (sound, then the cursor on (nX, nZ)). */
s32 func_0027F630(void *arg0, s32 arg1, s32 nRoll, s32 nX, s32 nZ) {
    TutoCtl_0027F630 *pCtl = arg0;
    u8 bDif = arg1;

    if (pCtl->wait % bDif == 0) {
        SzSound_PlaySE(0, 19);
    }
    if (pCtl->wait++ % bDif < (bDif >> 1)) {
        SzDuel_OpenHandCursor(nRoll, nX, nZ);
    } else {
        SzDuel_CloseHandCursor();
    }
    if (pCtl->wait > bDif) {
        pCtl->wait = 0;
    }
}

typedef struct TutoCtl_0027F700 {
    u8 pad0[0x162];
    u16 timer;
} TutoCtl_0027F700;

typedef struct RGBA_0027F700 {
    u8 r, g, b, a;
} RGBA_0027F700;

#define MAX_0027F700(a, b) ((a) > (b) ? (a) : (b))
#define MIN_0027F700(a, b) ((a) < (b) ? (a) : (b))

/* Colours the board squares around (nX, nZ) that a tutorial trap covers. */
void TaTuto_DrawTrapArea(void *pCtlIn, s32 bDifIn, s32 nX, s32 nZ) {
    extern void SzDuel_SetMapColor();
    TutoCtl_0027F700 *pCtl = pCtlIn;
    u8 bDif = bDifIn;
    s32 i;
    s32 j;
    RGBA_0027F700 *pRGBA;
    RGBA_0027F700 RGBA;

    RGBA.b = 0xC0;
    RGBA.g = 0;
    RGBA.r = 0xC0;
    RGBA.a = 0x80;
    pRGBA = &RGBA;
    if (pCtl->timer++ % bDif == 0) {
        for (i = 0; i <= 6; i++) {
            for (j = 0; j <= 6; j++) {
                if ((MAX_0027F700(nX, i) - MIN_0027F700(nX, i)) + (MAX_0027F700(nZ, j) - MIN_0027F700(nZ, j)) < 2) {
                    SzDuel_SetMapColor(i, j, 0, pRGBA, 1);
                }
            }
        }
    }
    if (pCtl->timer > bDif) {
        pCtl->timer = 0;
    }
}

/* Whether side `nSide` is playing a tutorial duel. */
s32 TaTuto_IsTuto(s32 nSide) {
    extern s32 SzDuel_GetPlayer();
    s32 var_s0;

    var_s0 = 0;
    if (SzDuel_GetPlayer(nSide) >= 0x20) {
        if (SzDuel_GetPlayer(nSide) < 0x64) {
            var_s0 = 1;
        }
    }
    return (var_s0 != 0) ? 1 : 0;
}

/* Fades the duel and monster black-out in or out (`Flip`) at speed `FadeSpd` for the tutorial. */
s32 func_0027F890(s32 FadeSpd, s32 Flip, s32 arg2) {
    u8 EndCond;

    EndCond = 0;
    if (Flip > 0) {
        if (SzEffect_GetBlackOutForDuel() < 0x80) {
            SzEffect_SetBlackOutForDuel((u8)(SzEffect_GetBlackOutForDuel() + FadeSpd));
        } else {
            EndCond++;
        }
        if (SzEffect_GetBlackOutForMonster() < 0x80) {
            SzEffect_SetBlackOutForMonster((u8)(SzEffect_GetBlackOutForMonster() + FadeSpd));
        } else {
            EndCond++;
        }
    } else if (Flip < 0) {
        if (SzEffect_GetBlackOutForDuel() > 0) {
            if (SzEffect_GetBlackOutForDuel() - FadeSpd < 0) {
                SzEffect_SetBlackOutForDuel(0);
            } else {
                SzEffect_SetBlackOutForDuel((u8)(SzEffect_GetBlackOutForDuel() - FadeSpd));
            }
        } else {
            EndCond++;
        }
        if (SzEffect_GetBlackOutForMonster() > 0) {
            if (SzEffect_GetBlackOutForMonster() - FadeSpd < 0) {
                SzEffect_SetBlackOutForMonster(0);
            } else {
                SzEffect_SetBlackOutForMonster((u8)(SzEffect_GetBlackOutForMonster() - FadeSpd));
            }
        } else {
            EndCond++;
        }
    }
    if (EndCond == 2) {
        return 1;
    }
    return 0;
}

typedef struct Vec_0027FA30 {
    f32 x, y, z, w;
} Vec_0027FA30;

typedef struct Cam_0027FA30 {
    Vec_0027FA30 pnt;
    Vec_0027FA30 vec;
} Cam_0027FA30;

/* Moves the camera to a tutorial view over `nSpeed` frames. */
s32 func_0027FA30(void *arg0, s32 nSpeed) {
    Cam_0027FA30 *pCam = arg0;

    SzView_FreeRequest(0, 0);
    SzView_ReqCamera(0, 0, 3, (u8)nSpeed & 0xFF, 0, &pCam->pnt);
    SzView_ReqCamera(0, 0, 4, (u8)nSpeed, 0, &pCam->vec);
}

typedef struct Vec_0027FAB0 {
    f32 x, y, z, w;
} Vec_0027FAB0;

typedef struct Cam_0027FAB0 {
    Vec_0027FAB0 pnt;
    Vec_0027FAB0 vec;
} Cam_0027FAB0;

/* Saves the current camera for the tutorial. */
s32 func_0027FAB0(void *arg0) {
    Cam_0027FAB0 *pCam = arg0;
    Vec_0027FAB0 *pVec;
    Vec_0027FAB0 *pPnt;

    pPnt = (Vec_0027FAB0 *)SzView_GetCP(0);
    pVec = (Vec_0027FAB0 *)SzView_GetLook(0);
    pCam->pnt.x = pPnt->x;
    pCam->pnt.y = pPnt->y;
    pCam->pnt.z = pPnt->z;
    pCam->pnt.w = pPnt->w;
    pCam->vec.x = pVec->x;
    pCam->vec.y = pVec->y;
    pCam->vec.z = pVec->z;
    pCam->vec.w = pVec->w;
}

/* Opens tutorial message `nMsgID` (its time into `wTime`). */
s32 func_0027FB30(s32 nMsgID, u16 *wTime) {
    extern s32 func_0027FDA0(s32);

    if (*wTime < 480) {
        nMsgID = func_0027FDA0(nMsgID);
        SzDuel_OpenMsgPopup(1, 0, 480 - (*wTime += 80), nMsgID);
    } else {
        return 1;
    }
    return 0;
}

/* Shows tutorial message `nMsgID` and closes it when its time `wTime` runs out. */
s32 func_0027FBA0(s32 nMsgID, u16 *wTime) {
    extern s32 func_0027FDA0(s32);

    if (*wTime > 0) {
        nMsgID = func_0027FDA0(nMsgID);
        SzDuel_OpenMsgPopup(1, 0, 480 - (*wTime -= 80), nMsgID);
    } else {
        SzDuel_CloseMsgPopup();
        return 1;
    }
    return 0;
}

typedef struct TutoCtl_0027FC20 {
    u8 pad0[0x160];
    u16 msg;
    u16 timer;
    u8 pad164[0x3E];
    u16 step;
    u16 wait;
} TutoCtl_0027FC20;

/* Shows tutorial messages `nStartMsgID` to `nEndMsgID`, one per button press. */
s32 func_0027FC20(s32 nStartMsgID, s32 nEndMsgID, void *arg2) {
    extern s32 func_0027FB30(s32, u16 *);
    extern s32 func_0027FBA0(s32, u16 *);
    extern s32 func_0027FDA0(s32);
    TutoCtl_0027FC20 *pCtl = arg2;

    if (pCtl->msg == 0xFFFF) {
        pCtl->msg = nStartMsgID;
    }
    if (pCtl->msg == nStartMsgID) {
        if (func_0027FB30(pCtl->msg, &pCtl->wait) == 1) {
            if (SzPad_Check(0, 0, 0xF0)) {
                if (nStartMsgID == nEndMsgID) {
                    SzSound_PlaySE(0, 4);
                    pCtl->msg = 0xFFFE;
                } else {
                    SzSound_PlaySE(0, 3);
                    pCtl->msg++;
                }
            }
        }
    } else if (pCtl->msg == 0xFFFE) {
        if (func_0027FBA0(nEndMsgID, &pCtl->wait) == 1) {
            pCtl->msg = 0xFFFF;
            pCtl->step++;
            pCtl->wait = 0;
            return 1;
        }
    } else {
        SzDuel_OpenMsgPopup(1, 0, 0, func_0027FDA0(pCtl->msg));
        if (SzPad_Check(0, 0, 0xF0)) {
            if (pCtl->msg == nEndMsgID) {
                SzSound_PlaySE(0, 4);
                pCtl->msg = 0xFFFE;
            } else {
                SzSound_PlaySE(0, 3);
                pCtl->msg++;
            }
        }
    }
    return 0;
}

/* The real message id of tutorial message `nMsgID` (by the options and the turn owner). */
s32 func_0027FDA0(s32 nMsgID) {
    if (SzData_GetOption(SzDuel_GetTurnOwner(), 0) == 0) {
        return nMsgID;
    }
    switch (nMsgID - 2524) {
    case 27:
        return 3054;
    case 479:
        return 3055;
    case 480:
        return 3056;
    case 481:
        return 3057;
    case 311:
        return 3058;
    case 319:
        return 3059;
    case 325:
        return 3060;
    case 328:
        return 3061;
    case 338:
        return 3062;
    case 339:
        return 3063;
    case 341:
        return 3064;
    case 353:
        return 3065;
    case 358:
        return 3066;
    case 360:
        return 3067;
    case 381:
        return 3068;
    case 386:
        return 3069;
    case 388:
        return 3070;
    case 427:
        return 3071;
    case 430:
        return 3072;
    }
    return nMsgID;
}

/* Asks for the half-far camera view over side `side`'s leader. */
void TaView_ReqHalfFarView(s32 side) {
    void *leader;
    f32 *pos;

    SzView_FreeRequest(0, 0);
    leader = (void *)SzView_GetCP(0);
    pos = SzView_GetLook(0);
    *pos = 2.0f * *pos;
    SzView_ReqCamera(0, 0, 3, (u8)side & 0xFF, 0, leader);
    SzView_ReqCamera(0, 0, 4, (u8)side, 0, pos);
}
