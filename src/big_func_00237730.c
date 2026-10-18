#include "common.h"
#include "game.h"
#include "campaign.h"
#include "m2c_macros.h"

extern s16 D_00299ED2;
typedef struct {
    __int128 q;
} TkQ;
extern TkQ D_0029B000;
extern TkQ D_0029B010;
extern s8 D_0030F1F6;
extern s8 D_0030F213;
extern s8 D_0030F227;
extern s8 D_0030F244;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} TkVec4;

extern s32 abs_b(s32 arg0);
extern void SzDuel_OpenOptionPopup_b(s32 arg0, s32 arg1, s32 arg2);

#pragma conditional_move off
#pragma opt_dead_assignments off
/* Runs one frame of the campaign map mode: input, the camera, pop-ups, the event and duel start, leaving. */
void TkCamp_Act(void) {
    s32 ctx = (s32) &campaignState;
    s16 temp_s1;
    s16 temp_s2;
    s32 var_s3;
    CampaignWork *base = &campaignWork;
    s16 hit;
    s16 ax;
    s16 dx;
    s16 ay;
    s16 sgn;
    s16 temp_s1_3;
    s32 var_s2;
    s16 ok;
    s16 spot;
    f32 vp[4];
    f32 vq[4];
    f32 vr[4];
    f32 vs[4];
    TkQ spE0;
    TkQ spF0;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 fq4;
    s16 *var_a3;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_v0_10;
    s16 temp_v0_11;
    s16 temp_v0_12;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_hi_3;
    s32 temp_hi_4;
    s32 leader;
    s32 currentDeck;
    s32 actMsgPopup;
    s32 var_a0_4;
    s32 i;
    s32 var_s1;
    s32 var_s1_2;
    s32 j;
    s32 temp_a1_4;
    s8 temp_a1_7;
    s8 temp_a1_8;
    s32 temp_v0;
    s8 temp_v0_15;
    s8 temp_v0_16;
    s8 temp_v0_17;
    s32 temp_v0_18;
    s8 temp_v0_20;
    s8 temp_v0_21;
    s32 temp_v0_22;
    s8 c23;
    s8 temp_v0_3;
    s32 temp_v1;
    s8 temp_v1_10;
    s8 temp_v1_11;
    s8 temp_v1_12;
    s8 temp_v1_13;
    s8 temp_v1_14;
    s8 temp_v1_4;
    s8 temp_v1_5;
    s8 temp_v1_6;
    s8 temp_v1_7;
    s8 temp_v1_8;
    s8 temp_v1_9;

    temp_s1 = campaignWork.cursorX;
    temp_s2 = campaignWork.cursorY;
    campaignWork.cursorOnIcon = 0;
    campaignWork.unk5481 = 1;
    campaignWork.placesReached = 0;
    var_s3 = 0;
    if (D_00299ED2 < 0x2710) {
        temp_v0 = campaignWork.unk006E;
        if (temp_v0 != 0) {
            campaignWork.iconSlide = (s16) (campaignWork.iconSlide + 0x14);
            if (campaignWork.iconSlide >= 0x100) {
                campaignWork.iconSlide = 0x100;
                campaignWork.unk5374 = 0;
            }
        } else if ((s8) temp_v0 == 0) {
            campaignWork.unk5374 = 1;
            campaignWork.iconSlide = (s16) (campaignWork.iconSlide - 0x14);
            if (campaignWork.iconSlide <= 0) {
                campaignWork.iconSlide = 0;
            }
        }
        temp_v1 = campaignWork.unk006A;
        if ((temp_v1 != 0) && (campaignWork.unk006E != 0) && (campaignWork.unk53C1 == 0)) {
            if (campaignWork.opponentFaceState == 0) {
                campaignWork.opponentFaceState = 1;
                campaignWork.unk5406 = 0;
            }
            campaignWork.windowOpen = (s16) (campaignWork.windowOpen + 0x14);
            campaignWork.unk53C1 = 0;
            if (campaignWork.windowOpen >= 0x100) {
                campaignWork.windowOpen = 0x100;
            }
        } else if (((s8) temp_v1 == 0) || (campaignWork.unk006E == 0) || (campaignWork.unk53C1 == 1)) {
            campaignWork.windowOpen = (s16) (campaignWork.windowOpen - 0x14);
            if (campaignWork.windowOpen <= 0) {
                campaignWork.windowOpen = 0;
                campaignWork.unk53AB = 0;
                campaignWork.unk53C1 = 0;
                campaignWork.duelMenuChoice = (*(s8 *)(ctx + 0xC9));
                if (campaignWork.opponentFaceState != 0) {
                    ShFace_Close((u8 *)&campaignWork.opponentFace);
                    campaignWork.opponentFaceState = 0;
                }
            }
        }
    } else {
        campaignWork.unk5374 = 1;
        campaignWork.unk006E = 0;
        campaignWork.unk006A = 0;
        if (campaignWork.unk006E == 0) {
            campaignWork.iconSlide = (s16) (campaignWork.iconSlide - 0x14);
            if (campaignWork.iconSlide <= 0) {
                campaignWork.iconSlide = 0;
            }
        }
        if ((campaignWork.unk006A == 0) || (campaignWork.unk006E == 0)) {
            campaignWork.windowOpen = (s16) (campaignWork.windowOpen - 0x14);
            if (campaignWork.windowOpen <= 0) {
                campaignWork.windowOpen = 0;
                campaignWork.unk53AB = 0;
                if (campaignWork.opponentFaceState != 0) {
                    ShFace_Close((u8 *)&campaignWork.opponentFace);
                    campaignWork.opponentFaceState = 0;
                }
            }
        }
    }
    for (j = 0; j <= 0x15; j++) {
        if (base->placeReached[j] != 0) {
            base->placesReached = (s8) (base->placesReached + 1);
        }
    }
    if (campaignWork.routesIdle != 0) {
        if ((campaignWork.placesReached == 0) && (SzEffect_IsUse2(-1, -1) == 0) && (campaignWork.unk5374 == 0) && (campaignWork.unk5375 == 0) && ((*(s16 *)(ctx + 0xC2)) < 0xC8)) {
            for (i = 0; i < 4; i++) {
                var_a3 = &campaignSystemIcons[i * 0x13];
                temp_a1 = base->cursorX;
                if (((M2C_FIELD(var_a3, s16 *, 0) - 2) <= temp_a1) && (temp_a1 <= (M2C_FIELD(var_a3, s16 *, 4) + 2))) {
                    temp_a1_2 = base->cursorY;
                    if (((M2C_FIELD(var_a3, s16 *, 2) - 2) <= temp_a1_2) && (temp_a1_2 <= (M2C_FIELD(var_a3, s16 *, 6) + 2)) && (base->unk0004 != 1)) {
                        base->cursorOnIcon = 1;
                    }
                }
            }
            if ((campaignWork.cursorOnIcon != 0) && (campaignWork.unk543E == 0)) {
                switch (campaignWork.iconUnderCursor) {
                case 0:
                    if (SzPad_Check(0, 0, 0x40) != 0) {
                        SzSound_PlaySE(0, 4);
                        SzGame_SetMenuNum(6, 0);
                        SzGame_Push(6, 0);
                        goto end_TkCamp_Act;
                    }
                    break;
                case 1:
                    switch (campaignWork.helpOpen) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 4);
                            SzGame_InitMemCardProc(1);
                            campaignWork.helpOpen = 1;
                            goto end_TkCamp_Act;
                        }
                        break;
                    default:
                        if (0 > SzGame_ActMemCardProc()) {
                            campaignWork.helpOpen = 0;
                        }
                        goto end_TkCamp_Act;
                    }
                    break;
                case 2:
                    switch (campaignWork.helpOpen) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 4);
                            SzDuel_OpenOptionPopup_b((s32) (*(s8 *)(ctx + 0)), 0, 0x200);
                            campaignWork.helpOpen = 1;
                            campaignWork.helpStep = 0;
                            goto end_TkCamp_Act;
                        }
                        break;
                    case 1:
                        campaignWork.helpStep = (s8) (campaignWork.helpStep + 1);
                        if (campaignWork.helpStep >= 8) {
                            campaignWork.helpStep = 8;
                            campaignWork.helpOpen = 2;
                        }
                        SzDuel_OpenOptionPopup_b(-1, 0, 0x200 - ((s32) (campaignWork.helpStep << 9) >> 3));
                        goto end_TkCamp_Act;
                    case 2:
                        if (SzDuel_ActOptionPopup(0) != 0) {
                            campaignWork.helpOpen = 3;
                        }
                        goto end_TkCamp_Act;
                    case 3:
                        campaignWork.helpStep = (s8) (campaignWork.helpStep - 1);
                        if (campaignWork.helpStep <= 0) {
                            campaignWork.helpStep = 8;
                            campaignWork.helpOpen = 4;
                        }
                        SzDuel_OpenOptionPopup_b(-1, 0, 0x200 - ((s32) (campaignWork.helpStep << 9) >> 3));
                        if (campaignWork.helpOpen == 4) {
                            campaignWork.helpOpen = 0;
                            SzDuel_CloseOptionPopup();
                        }
                        goto end_TkCamp_Act;
                    }
                    break;
                case 3:
                    switch (campaignWork.helpOpen) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 4);
                            campaignWork.helpOpen = 1;
                            campaignWork.helpStep = 0;
                            campaignWork.helpPick = 0;
                            goto end_TkCamp_Act;
                        }
                        break;
                    case 1:
                        campaignWork.helpStep = (s8) (campaignWork.helpStep + 1);
                        if (campaignWork.helpStep >= 8) {
                            campaignWork.helpStep = 8;
                            campaignWork.helpOpen = 2;
                        }
                        goto end_TkCamp_Act;
                    case 2:
                        if (SzPad_Check(0, 0, 0x20) != 0) {
                            SzSound_PlaySE(0, 5);
                            campaignWork.helpOpen = 0xA;
                        } else if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 1);
                            campaignWork.helpOpen = 3;
                        }
                        if (campaignWork.helpOpen == 3) {
                            Taku_Camp_Go_Help();
                        }
                        if (campaignWork.helpOpen < 3) {
                            if (SzPad_Check(0, 2, 0x1000) != 0) {
                                SzSound_PlaySE(0, 3);
                                campaignWork.helpPick = (s8) (campaignWork.helpPick - 1);
                                if (campaignWork.helpPick < 0) {
                                    campaignWork.helpPick = 4;
                                }
                            }
                            if (SzPad_Check(0, 2, 0x4000) != 0) {
                                SzSound_PlaySE(0, 3);
                                campaignWork.helpPick = (s8) (campaignWork.helpPick + 1);
                                if (campaignWork.helpPick > 4) {
                                    campaignWork.helpPick = 0;
                                }
                            }
                        }
                        goto end_TkCamp_Act;
                    case 10:
                        campaignWork.helpStep = (s8) (campaignWork.helpStep - 1);
                        if (campaignWork.helpStep <= 0) {
                            campaignWork.helpStep = 0;
                            campaignWork.helpOpen = 0;
                        }
                        goto end_TkCamp_Act;
                    }
                    break;
                }
            }
            {
                if (campaignWork.helpOpen == 0) {
                    switch (campaignWork.unk543E) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x100) != 0) {
                            SzSound_PlaySE(0, 4);
                            SzDuel_OpenMsgPopup(7, 0, 0x200, 0x91);
                            campaignWork.unk543E = 1;
                            goto end_TkCamp_Act;
                        }
                        break;
                    case 1:
                        campaignWork.unk543F = (s8) (campaignWork.unk543F + 1);
                        if (campaignWork.unk543F >= 8) {
                            campaignWork.unk543F = 8;
                            campaignWork.unk543E = 2;
                        }
                        SzDuel_OpenMsgPopup(7, 0, 0x200 - ((s32) (campaignWork.unk543F << 9) >> 3), -1);
                        goto end_TkCamp_Act;
                    case 2:
                        actMsgPopup = SzDuel_ActMsgPopup(0);
                        switch (actMsgPopup) {
                        case 1:
                            campaignWork.unk543E = 3;
                            break;
                        case 2:
                            campaignWork.unk543E = 4;
                            break;
                        }
                        return;
                    case 3:
                        SzGame_Pop();
                        goto end_TkCamp_Act;
                    case 4:
                        campaignWork.unk543F = (s8) (campaignWork.unk543F - 1);
                        temp_v0_3 = campaignWork.unk543F;
                        if (temp_v0_3 <= 0) {
                            campaignWork.unk543F = 0;
                            campaignWork.unk543E = 0;
                            SzDuel_CloseMsgPopup();
                        } else {
                            SzDuel_OpenMsgPopup(7, 0, 0x200 - ((s32) (temp_v0_3 << 9) >> 3), -1);
                        }
                        goto end_TkCamp_Act;
                    }
                }
                {
                    if (campaignWork.unk543E == 0) {
                        SzPad_Check(0, 1, 0x800);
                        if (SzPad_Check(0, 0, 0x800) != 0) {
                            SzSound_PlaySE(0, 4);
                            temp_v1_4 = campaignWork.unk0072;
                            if (temp_v1_4 == 0) {
                                campaignWork.unk0072 = 1;
                                campaignWork.unk007A = 0;
                                campaignWork.unk007C = 0;
                            } else if (temp_v1_4 == 1) {
                                campaignWork.unk0072 = 2;
                            }
                        }
                    }
                    if (SzPad_IsAnalog(0) != 0) {
                        ax = SzPad_GetAnalogInfo(0, 2) & 0xFF;
                        ay = SzPad_GetAnalogInfo(0, 3) & 0xFF;
                        dx = ax - 0x80;
                        if (abs_b(dx) > 0x30) {
                            sgn = (0 <= dx) ? 1 : -1;
                            campaignWork.cameraTarget[0] = campaignWork.cameraTarget[0] + ((4.0f * (f32) (dx - (sgn * 0x30))) / 79.0f);
                        }
                        ax = ay - 0x80;
                        if (abs_b(ax) > 0x30) {
                            sgn = (0 <= ax) ? 1 : -1;
                            campaignWork.cameraTarget[2] = campaignWork.cameraTarget[2] + ((4.0f * (f32) (ax - (sgn * 0x30))) / 79.0f);
                        }
                    }
                    SzPad_Check(0, 1, 0x100);
                    SzPad_Check(0, 2, 0x100);
                    if (campaignWork.unk0004 == 1) {
                        vp[0] = (f32) (campaignWork.cursorX - 0x140);
                        vp[1] = (f32) (campaignWork.cursorY - 0xE0);
                        vp[2] = 1.0f;
                        vp[3] = 1.0f;
                        vq[0] = (f32) (campaignWork.cursorX - 0x140);
                        vq[1] = (f32) (campaignWork.cursorY - 0xE0);
                        vq[2] = 100.0f;
                        vq[3] = 1.0f;
                        Ex3d_GetPointOnScreen(vp, vp[0], vp[1]);
                        *(TkVec4 *)vq = *(TkVec4 *)SzView_GetSP(0);
                        Ex3d_IntersectP((void *)&campaignWork.groundPlane[0], vp, vq, vr);
                    }
                    if (SzPad_Check(0, 1, 0x1000) != 0) {
                        if (campaignWork.unk0072 != 0) {
                            campaignWork.unk007C = 0;
                            if (SzPad_Check(0, 0, 0x1000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (campaignWork.unk0004 == 1) {
                            temp_v0_5 = campaignWork.cursorY;
                            if (0 < temp_v0_5) {
                                campaignWork.cursorY = (s16) (temp_v0_5 - 0x18);
                                if (campaignWork.cursorY <= 0) {
                                    campaignWork.cursorY = 0;
                                }
                            } else {
                                campaignWork.cursorY = 0;
                            }
                        } else {
                            temp_v0_6 = campaignWork.cursorY;
                            if (0 < temp_v0_6) {
                                campaignWork.cursorY = (s16) (temp_v0_6 - 0x10);
                                if (campaignWork.cursorY <= 0) {
                                    campaignWork.cursorY = 0;
                                }
                            } else {
                                campaignWork.cursorY = 0;
                                campaignWork.cameraTarget[2] = (f32) (campaignWork.cameraTarget[2] - 4.0f);
                            }
                        }
                    }
                    if (SzPad_Check(0, 1, 0x4000) != 0) {
                        if (campaignWork.unk0072 != 0) {
                            campaignWork.unk007C = 1;
                            if (SzPad_Check(0, 0, 0x4000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (campaignWork.unk0004 == 1) {
                            temp_v0_7 = campaignWork.cursorY;
                            if (temp_v0_7 < 0x1A0) {
                                campaignWork.cursorY = (s16) (temp_v0_7 + 0x18);
                                if (campaignWork.cursorY >= 0x1A0) {
                                    campaignWork.cursorY = 0x1A0;
                                }
                            } else {
                                campaignWork.cursorY = 0x1A0;
                            }
                        } else {
                            temp_v0_8 = campaignWork.cursorY;
                            if (temp_v0_8 < 0x1A0) {
                                campaignWork.cursorY = (s16) (temp_v0_8 + 0x10);
                                if (campaignWork.cursorY >= 0x1A0) {
                                    campaignWork.cursorY = 0x1A0;
                                }
                            } else {
                                campaignWork.cursorY = 0x1A0;
                                campaignWork.cameraTarget[2] += 4.0f;
                            }
                        }
                    }
                    if (SzPad_Check(0, 1, 0x8000) != 0) {
                        if (campaignWork.unk0072 != 0) {
                            campaignWork.unk007A = 0;
                            if (SzPad_Check(0, 0, 0x8000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (campaignWork.unk0004 == 1) {
                            temp_v0_9 = campaignWork.cursorX;
                            if (0 < temp_v0_9) {
                                campaignWork.cursorX = (s16) (temp_v0_9 - 0x18);
                                if (campaignWork.cursorX <= 0) {
                                    campaignWork.cursorX = 0;
                                }
                            } else {
                                campaignWork.cursorX = 0;
                            }
                        } else {
                            temp_v0_10 = campaignWork.cursorX;
                            if (0 < temp_v0_10) {
                                campaignWork.cursorX = (s16) (temp_v0_10 - 0x10);
                                if (campaignWork.cursorX <= 0) {
                                    campaignWork.cursorX = 0;
                                }
                            } else {
                                campaignWork.cursorX = 0;
                                campaignWork.cameraTarget[0] = (f32) (campaignWork.cameraTarget[0] - 4.0f);
                            }
                        }
                    }
                    if (SzPad_Check(0, 1, 0x2000) != 0) {
                        if (campaignWork.unk0072 != 0) {
                            campaignWork.unk007A = 1;
                            if (SzPad_Check(0, 0, 0x2000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (campaignWork.unk0004 == 1) {
                            temp_v0_11 = campaignWork.cursorX;
                            if (temp_v0_11 < 0x260) {
                                campaignWork.cursorX = (s16) (temp_v0_11 + 0x18);
                                if (campaignWork.cursorX >= 0x260) {
                                    campaignWork.cursorX = 0x260;
                                }
                            } else {
                                campaignWork.cursorX = 0x260;
                            }
                        } else {
                            temp_v0_12 = campaignWork.cursorX;
                            if (temp_v0_12 < 0x260) {
                                campaignWork.cursorX = (s16) (temp_v0_12 + 0x10);
                                if (campaignWork.cursorX >= 0x260) {
                                    campaignWork.cursorX = 0x260;
                                }
                            } else {
                                campaignWork.cursorX = 0x260;
                                campaignWork.cameraTarget[0] += 4.0f;
                            }
                        }
                    }
                    if (campaignWork.unk0004 == 1) {
                        vp[0] = (f32) (campaignWork.cursorX - 0x140);
                        vp[1] = (f32) (campaignWork.cursorY - 0xE0);
                        vp[2] = 1.0f;
                        vp[3] = 1.0f;
                        vq[0] = (f32) (campaignWork.cursorX - 0x140);
                        vq[1] = (f32) (campaignWork.cursorY - 0xE0);
                        vq[2] = 100.0f;
                        vq[3] = 1.0f;
                        hit = 0;
                        Ex3d_GetPointOnScreen(vp, vp[0], vp[1]);
                        *(TkVec4 *)vq = *(TkVec4 *)SzView_GetSP(0);
                        Ex3d_IntersectP((void *)&campaignWork.groundPlane[0], vp, vq, vs);
                        vs[0] -= vr[0];
                        vs[1] -= vr[1];
                        vs[2] -= vr[2];
                        campaignWork.cameraTarget[0] = (f32) (campaignWork.cameraTarget[0] - vs[0]);
                        campaignWork.cameraTarget[2] = (f32) (campaignWork.cameraTarget[2] - vs[2]);
                        if (campaignWork.cameraTarget[0] < -200.0f) {
                            hit++;
                            campaignWork.cursorX = temp_s1;
                        } else if (110.0f < campaignWork.cameraTarget[0]) {
                            hit++;
                            campaignWork.cursorX = temp_s1;
                        }
                        if (campaignWork.cameraTarget[2] < -220.0f) {
                            hit++;
                            campaignWork.cursorY = temp_s2;
                        } else if (210.0f < campaignWork.cameraTarget[2]) {
                            hit++;
                            campaignWork.cursorY = temp_s2;
                        }
                        if (hit) {
                            campaignWork.cameraTarget[0] = (f32) (campaignWork.cameraTarget[0] + vs[0]);
                            campaignWork.cameraTarget[2] = (f32) (campaignWork.cameraTarget[2] + vs[2]);
                            vp[0] = (f32) (campaignWork.cursorX - 0x140);
                            vp[1] = (f32) (campaignWork.cursorY - 0xE0);
                            vp[2] = 1.0f;
                            vp[3] = 1.0f;
                            vq[0] = (f32) (campaignWork.cursorX - 0x140);
                            vq[1] = (f32) (campaignWork.cursorY - 0xE0);
                            vq[2] = 100.0f;
                            vq[3] = 1.0f;
                            Ex3d_GetPointOnScreen(vp, vp[0], vp[1]);
                            *(TkVec4 *)vq = *(TkVec4 *)SzView_GetSP(0);
                            Ex3d_IntersectP((void *)&campaignWork.groundPlane[0], vp, vq, vs);
                            vs[0] -= vr[0];
                            vs[1] -= vr[1];
                            vs[2] -= vr[2];
                            campaignWork.cameraTarget[0] = (f32) (campaignWork.cameraTarget[0] - vs[0]);
                            campaignWork.cameraTarget[2] = (f32) (campaignWork.cameraTarget[2] - vs[2]);
                        }
                    }
                    if (campaignWork.cameraTarget[0] < -200.0f) {
                        campaignWork.cameraTarget[0] = -200.0f;
                    } else if (110.0f < campaignWork.cameraTarget[0]) {
                        campaignWork.cameraTarget[0] = 110.0f;
                    }
                    if (campaignWork.cameraTarget[2] < -220.0f) {
                        campaignWork.cameraTarget[2] = -220.0f;
                    } else if (210.0f < campaignWork.cameraTarget[2]) {
                        campaignWork.cameraTarget[2] = 210.0f;
                    }
                    SzPad_Check(0, 1, 0x10);
                    temp_a1_4 = ((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3];
                    if ((temp_a1_4 != 0) && (campaignWork.windowOpen == 0x100)) {
                        {
                            ok = 0;
                            if (campaignWork.unk018C != 0) {
                                switch ((*(s8 *)(ctx + 0xC6))) {
                                case 1:
                                case 0xF:
                                case 0x11:
                                    ok = 0;
                                    break;
                                default:
                                    ok = 1;
                                    break;
                                }
                            } else if ((*(s8 *)(ctx + 0)) == 0) {
                                switch ((*(s8 *)(ctx + 0xC6))) {
                                case 1:
                                case 0xF:
                                case 0x11:
                                    ok = 0;
                                    break;
                                default:
                                    if ((s8) temp_a1_4 > 1) {
                                        ok = 1;
                                        if (((*(s8 *)(ctx + 0xC6)) == 0xB) && ((*(s8 *)(ctx + 0xE)) == 3) && (campaignWork.duelMenuChoice == 1)) {
                                            ok = 0;
                                        }
                                    }
                                    break;
                                }
                            } else if ((*(s8 *)(ctx + 0)) == 1) {
                                switch ((*(s8 *)(ctx + 0xC6))) {
                                case 1:
                                case 0xF:
                                case 0x11:
                                    ok = 0;
                                    break;
                                default:
                                    if ((s8) temp_a1_4 > 1) {
                                        ok = 1;
                                    }
                                    break;
                                }
                            }
                            if (ok) {
                                if ((SzPad_Check(0, 0, 0x10) != 0) && (campaignWork.unk0004 == 2) && (campaignWork.unk0072 == 0)) {
                                    SzSound_PlaySE(0, 4);
                                    campaignWork.terrainWindowOn = (s8) (campaignWork.terrainWindowOn ^ 1);
                                } else if (campaignWork.unk0004 != 2) {
                                    campaignWork.terrainWindowOn = 0;
                                }
                            } else {
                                campaignWork.terrainWindowOn = 0;
                            }
                        }
                    } else {
                        campaignWork.terrainWindowOn = 0;
                    }
                    if (SzPad_Check(0, 0, 0x20) != 0) {
                        if (campaignWork.unk0072 == 1) {
                            SzSound_PlaySE(0, 5);
                            campaignWork.unk0072 = 2;
                        }
                    }
                    if (SzPad_Check(0, 1, 0x80) != 0) {
                        if (campaignWork.unk0072 == 0) {
                            if (SzPad_Check(0, 0, 0x80) != 0) {
                                SzSound_PlaySE(0, 4);
                            }
                            campaignWork.unk0004 = 1U;
                        } else {
                            goto block_306;
                        }
                    } else {
block_306:
                        if (campaignWork.unk0004 == 1) {
                            campaignWork.unk0004 = 0U;
                        }
                    }
                    SzPad_Check(0, 2, 0x80);
                    SzPad_Check(0, 1, 0x20);
                    SzPad_Check(0, 0, 0x20);
                    SzPad_Check(0, 1, 4);
                    SzPad_Check(0, 2, 4);
                    SzPad_Check(0, 1, 1);
                    SzPad_Check(0, 2, 1);
                    SzPad_Check(0, 1, 0x200);
                    SzPad_Check(0, 1, 8);
                    SzPad_Check(0, 1, 2);
                    SzPad_Check(0, 1, 0x400);
                    if ((*(s8 *)(ctx + 0)) == 0) {
                        if ((*(s8 *)(ctx + 0xE)) < 3) {
                            goto block_312;
                        }
                        goto block_314;
                    }
block_312:
                    if (campaignWork.unk018C != 0) {
block_314:
                        if ((campaignWork.cursorOnIcon == 0) && (campaignWork.unk0004 == 2) && ((*(s8 *)(ctx + 0xC6)) == 0xB) && (campaignWork.unk53C1 == 0)) {
                            if (SzPad_Check(0, 0, 4) != 0) {
                                SzSound_PlaySE(0, 2);
                                (*(s8 *)(ctx + 0xC9)) = (s8) ((*(s8 *)(ctx + 0xC9)) - 1);
                                campaignWork.unk53C1 = 1;
                                if (campaignWork.unk018C != 0) {
                                    if ((*(s8 *)(ctx + 0xC9)) < 0) {
                                        (*(s8 *)(ctx + 0xC9)) = 2;
                                    }
                                } else if ((*(s8 *)(ctx + 0xC9)) < 0) {
                                    (*(s8 *)(ctx + 0xC9)) = 1;
                                }
                            } else if (SzPad_Check(0, 0, 8) != 0) {
                                SzSound_PlaySE(0, 2);
                                (*(s8 *)(ctx + 0xC9)) = (s8) ((*(s8 *)(ctx + 0xC9)) + 1);
                                campaignWork.unk53C1 = 1;
                                if (campaignWork.unk018C != 0) {
                                    (*(s8 *)(ctx + 0xC9)) = (s8) ((s8) (*(s8 *)(ctx + 0xC9)) % 3);
                                } else {
                                    (*(s8 *)(ctx + 0xC9)) = (s8) ((s8) (*(s8 *)(ctx + 0xC9)) % 2);
                                }
                            }
                        }
                    } else if (((*(s8 *)(ctx + 0)) == 0) && ((*(s8 *)(ctx + 0xE)) < 3)) {
                        (*(s8 *)(ctx + 0xC9)) = 0;
                    }
                }
            }
        }
    }
        if (campaignWork.eventCutScene != (*(s16 *)(ctx + 0xC2))) {
            campaignWork.eventStep = 0;
            campaignWork.unk537A = 0;
        }
        campaignWork.eventCutScene = (s16) (*(s16 *)(ctx + 0xC2));
        switch ((*(s16 *)(ctx + 0xC2))) { /* switch 6; irregular */
        case 0x2738:                                /* switch 6 */
            if (campaignWork.eventWindowState == 2) {
                if (campaignWork.nameTableSlide == 0) {
                    if (SzPad_Check(0, 2, 0x1000) != 0) {
                        SzSound_PlaySE(0, 2);
                        campaignWork.nameRow = (s8) (campaignWork.nameRow - 1);
                        if (campaignWork.nameRow < 0) {
                            campaignWork.nameRow = 5;
                        }
                    }
                    if (SzPad_Check(0, 2, 0x4000) != 0) {
                        SzSound_PlaySE(0, 2);
                        campaignWork.nameRow = (s8) (campaignWork.nameRow + 1);
                        if (campaignWork.nameRow > 5) {
                            campaignWork.nameRow = 0;
                        }
                    }
                    if (SzPad_Check(0, 2, 0x8000) != 0) {
                        SzSound_PlaySE(0, 2);
                        campaignWork.nameColumn = (s8) (campaignWork.nameColumn - 1);
                        if (campaignWork.nameColumn < 0) {
                            campaignWork.nameColumn = 0xE;
                        }
                    }
                    if (SzPad_Check(0, 2, 0x2000) != 0) {
                        SzSound_PlaySE(0, 2);
                        campaignWork.nameColumn = (s8) (campaignWork.nameColumn + 1);
                        if (campaignWork.nameColumn > 0xE) {
                            campaignWork.nameColumn = 0;
                        }
                    }
                    if (SzPad_Check(0, 0, 0x20) != 0) {
                        SzSound_PlaySE(0, 5);
                        campaignWork.nameLength = (s8) (campaignWork.nameLength - 1);
                        campaignWork.nameCursor = campaignWork.nameLength - 1;
                        if (campaignWork.nameLength <= 0) {
                            campaignWork.nameLength = 0;
                            campaignWork.nameCursor = 0;
                        }
                        (campaignWork.nameLetterTable)[campaignWork.nameLength] = 0;
                        (campaignWork.nameLetterColumn)[campaignWork.nameLength] = 6;
                        (campaignWork.nameLetterRow)[campaignWork.nameLength] = 1;
                    }
                    if (campaignWork.nameTyping == 0) {
                        if ((campaignWork.nameLength < 0xC) && (SzPad_Check(0, 0, 0xC0) != 0)) {
                            SzSound_PlaySE(0, 4);
                            campaignWork.nameTyping = 1;
                            campaignWork.namePickedColumn = campaignWork.nameColumn;
                            campaignWork.namePickedRow = campaignWork.nameRow;
                        }
                    }
                    if ((campaignWork.nameTyping == 0) && (campaignWork.nameLength != 0) && (SzPad_Check(0, 0, 0x800) != 0)) {
                        SzSound_PlaySE(0, 1);
                        campaignWork.eventWindowState = 3;
                        Taku_Camp_Ivent_Name_Set();
                    }
                }
            }
            temp_v1_5 = campaignWork.nameTableTurn;
            if (temp_v1_5 == 1) {
                temp_v0_15 = campaignWork.nameTableSlide;
                if (temp_v0_15 < 0x64) {
                    campaignWork.nameTableSlide = (s8) (temp_v0_15 + 0xA);
                }
                if (campaignWork.nameTableSlide >= 0x64) {
                    campaignWork.nameTableSlide = 0;
                    campaignWork.nameTableTurn = 0;
                    campaignWork.nameTable = (s8) (campaignWork.nameTable - 1);
                    if (campaignWork.nameTable < 0) {
                        campaignWork.nameTable = 2;
                    }
                }
            } else if (temp_v1_5 == 2) {
                temp_v0_16 = campaignWork.nameTableSlide;
                if (temp_v0_16 > -0x64) {
                    campaignWork.nameTableSlide = (s8) (temp_v0_16 - 0xA);
                }
                if (campaignWork.nameTableSlide < -0x63) {
                    campaignWork.nameTableSlide = 0;
                    campaignWork.nameTableTurn = 0;
                    campaignWork.nameTable = (s8) (campaignWork.nameTable + 1);
                    if (campaignWork.nameTable > 2) {
                        campaignWork.nameTable = 0;
                    }
                }
            }
            if (campaignWork.nameTyping == 1) {
                temp_v0_17 = campaignWork.nameTypingT;
                if (temp_v0_17 < 0x64) {
                    campaignWork.nameTypingT = (s8) (temp_v0_17 + 0x14);
                }
                if (campaignWork.nameTypingT >= 0x64) {
                    temp_v1_6 = campaignWork.nameLength;
                    (campaignWork.nameLetterTable)[temp_v1_6] = (s8) campaignWork.nameTable;
                    (campaignWork.nameLetterColumn)[temp_v1_6] = (s8) campaignWork.namePickedColumn;
                    (campaignWork.nameLetterRow)[temp_v1_6] = (s8) campaignWork.namePickedRow;
                    campaignWork.nameTypingT = 0;
                    campaignWork.nameTyping = 0;
                    campaignWork.nameCursor = (s8) campaignWork.nameLength;
                    campaignWork.nameLength = (s8) (campaignWork.nameLength + 1);
                    if (campaignWork.nameLength >= 0xC) {
                        campaignWork.nameLength = 0xC;
                        campaignWork.nameCursor = 0xB;
                    }
                }
            }
            break;
        case 0x2742:                                /* switch 6 */
        case 0x276A:                                /* switch 6 */
            if (campaignWork.eventWindowState == 2) {
                var_s1 = 1;
                if ((*(s16 *)(ctx + 0xC2)) == 0x276A) {
                    if ((*(s8 *)(ctx + 1)) != 0) {
                        var_s1 = 0;
                    }
                    if ((*(s8 *)(ctx + 2)) != 0) {
                        var_s1 = 0;
                    }
                }
                if (SzPad_Check(0, 0, 0x1000) != 0) {
                    if (var_s1 != 0) {
                        SzSound_PlaySE(0, 3);
                        campaignWork.eventWindowChoice = 0;
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                }
                if (SzPad_Check(0, 0, 0x4000) != 0) {
                    if (var_s1 != 0) {
                        SzSound_PlaySE(0, 3);
                        campaignWork.eventWindowChoice = 1;
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                }
                if ((SzPad_Check(0, 1, 0x1000) == 0) && (SzPad_Check(0, 1, 0x4000) == 0) && (SzPad_Check(0, 0, 0x800) != 0)) {
                    campaignWork.eventWindowState = 3;
                    SzSound_PlaySE(0, 1);
                    if (((*(s16 *)(ctx + 0xC2)) == 0x2742) && (campaignWork.eventWindowChoice == 0)) {
                        Taku_Camp_Go_Rensyu_Duel(0);
                    }
                }
            }
            break;
        case 0x2756:                                /* switch 6 */
            if ((campaignWork.eventWindowState == 2) && (campaignWork.deckShowPhase == 1)) {
                if (campaignWork.deckChoiceTurn == 0) {
                    if (SzPad_Check(0, 0, 0x2000) != 0) {
                        SzSound_PlaySE(0, 9);
                        campaignWork.deckChoiceTurn = 1;
                    }
                    if (SzPad_Check(0, 0, 0x8000) != 0) {
                        SzSound_PlaySE(0, 9);
                        campaignWork.deckChoiceTurn = 2;
                    }
                }
                temp_v0_18 = campaignWork.deckChoiceTurn;
                if (temp_v0_18 != 0) {
                    switch ((s8) temp_v0_18) {
                    case 1:                         /* switch 8 */
                        campaignWork.deckChoiceSlide = (s8) (campaignWork.deckChoiceSlide + 0x14);
                        if (campaignWork.deckChoiceSlide >= 0x64) {
                            campaignWork.deckChoiceSlide = 0;
                            campaignWork.deckChoiceTurn = 0;
                            campaignWork.eventWindowChoice = (s8) (campaignWork.eventWindowChoice + 1);
                            if (campaignWork.eventWindowChoice > 2) {
                                campaignWork.eventWindowChoice = 0;
                            }
                        }
                        break;
                    case 2:                         /* switch 8 */
                        campaignWork.deckChoiceSlide = (s8) (campaignWork.deckChoiceSlide + 0x14);
                        if (campaignWork.deckChoiceSlide >= 0x64) {
                            campaignWork.deckChoiceSlide = 0;
                            campaignWork.deckChoiceTurn = 0;
                            campaignWork.eventWindowChoice = (s8) (campaignWork.eventWindowChoice - 1);
                            if (campaignWork.eventWindowChoice < 0) {
                                campaignWork.eventWindowChoice = 2;
                            }
                        }
                        break;
                    }
                }
                if ((SzPad_Check(0, 0, 0x800) != 0) && (campaignWork.deckChoiceTurn == 0)) {
                    SzSound_PlaySE(0, 1);
                    campaignWork.eventWindowState = 3;
                    campaignWork.deckShowPhase = 2;
                }
            }
            /* fallthrough */
        case 0x2757:                                /* switch 6 */
            /* fallthrough */
        case 0x2760:                                /* switch 6 */
            if (campaignWork.deckShowPhase == 4) {
                SzData_SetupFromConstDeck(0, (s32) (campaignWork.deckChoices)[campaignWork.eventWindowChoice]);
                if (SzModel_IsModelLoading(0x1E) == 0) {
                    spE0 = D_0029B000;
                    spF0 = D_0029B010;
                    currentDeck = SzData_GetCurrentDeck(0);
                    leader = SzData_GetLeader(0, currentDeck);
                    campaignWork.leaderCard = SzData_GetLeader(0, currentDeck);
                    SzModel_SetPos(0x1E, &spE0);
                    SzModel_SetRot(0x1E, &spF0);
                    SzModel_Load(0x1E, -1, SzDuel_New2Xax(leader), 1);
                }
                campaignWork.deckShowPhase = 5;
            }
            break;
        }
        if (campaignWork.unk007A != 0) {
            if (campaignWork.unk007C != 0) {
                spot = 3;
            } else {
                spot = 1;
            }
        } else {
            spot = 0;
            if (campaignWork.unk007C != 0) {
                spot = 2;
            }
        }
        temp_v1_7 = campaignWork.unk0072;
        if (temp_v1_7 == 1) {
            if (campaignWork.cursorMoveT == 0) {
                campaignWork.cursorFromX = campaignWork.cursorX;
                campaignWork.cursorFromY = campaignWork.cursorY;
            }
            campaignWork.cursorMoveT = (s16) (campaignWork.cursorMoveT + 0x20);
            if (campaignWork.cursorMoveT >= 0x100) {
                campaignWork.cursorMoveT = 0x100;
            }
            campaignWork.cursorX = campaignWork.cursorFromX + ((campaignWork.cursorMoveT * ((campaignSystemIcons[spot * 0x13] + 0x10) - campaignWork.cursorFromX)) >> 8);
            campaignWork.cursorY = campaignWork.cursorFromY + ((campaignWork.cursorMoveT * ((campaignSystemIcons[spot * 0x13 + 1] + 0x10) - campaignWork.cursorFromY)) >> 8);
        } else if (temp_v1_7 == 2) {
            campaignWork.cursorMoveT = (s16) (campaignWork.cursorMoveT - 0x20);
            if (campaignWork.cursorMoveT <= 0) {
                campaignWork.cursorMoveT = 0;
                campaignWork.unk0072 = 0;
                campaignWork.unk007A = 0;
                campaignWork.unk007C = 0;
            }
            campaignWork.cursorX = campaignWork.cursorFromX + ((campaignWork.cursorMoveT * ((campaignSystemIcons[spot * 0x13] + 0x10) - campaignWork.cursorFromX)) >> 8);
            campaignWork.cursorY = campaignWork.cursorFromY + ((campaignWork.cursorMoveT * ((campaignSystemIcons[spot * 0x13 + 1] + 0x10) - campaignWork.cursorFromY)) >> 8);
        }
        Taku_Camp_System();
        if (campaignWork.talkStep == 1) {
            Taku_Camp_BUN_HANTEI();
        }
        if ((*(s8 *)(ctx + 0)) == 1) {
            if (((*(s16 *)(ctx + 0xC2)) == 0x68) || ((*(s16 *)(ctx + 0xC2)) == 0x69)) {
                var_s3 = 1;
            }
        }
        if (((*(s8 *)(ctx + 0)) == 1) && ((*(s16 *)(ctx + 0xC2)) == 0x6F)) {
            if (campaignWork.talkStep == 1) {
                Taku_Camp_BUN_HANTEI();
            }
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
            }
            if (campaignWork.talkStep == 4) {
                if (SzPad_Check(0, 0, 0x40) != 0) {
                    SzSound_PlaySE(0, 2);
                    campaignWork.talkStep = (s8) (campaignWork.talkStep + 1);
                    Taku_Camp_BUN_HANTEI();
                }
            }
        } else if (((*(s16 *)(ctx + 0xC2)) >= 0x2711) || (var_s3 != 0)) {
            if (SzPad_Check(0, 0, 0x40) != 0) {
                if (campaignWork.talkStep == 4) {
                    campaignWork.talkStep = 5;
                    campaignWork.unk53B2 = 0;
                    SzSound_PlaySE(0, 2);
                }
                if (campaignWork.eventPictureState == 2) {
                    campaignWork.eventPictureState = 3;
                    campaignWork.unk53B2 = 0;
                    SzSound_PlaySE(0, 2);
                }
                Taku_Camp_BUN_HANTEI();
            }
        } else if (campaignWork.unk0004 == 2) {
            var_a0_4 = 0;
            if (campaignWork.cursorOnIcon == 0) {
                if ((*(s8 *)(ctx + 0)) != 0) {
                    if ((*(s8 *)(ctx + 0xC6)) == 0xF) {
                        var_a0_4 = 1;
                    }
                }
                if ((campaignWork.playerDeckCost <= campaignWork.opponentDeckCost) || (campaignWork.talkStep != 0) || (var_a0_4 != 0)) {
                    var_s1_2 = 0;
                    if (campaignWork.talkStep == 0xC) {
                        if (campaignWork.unk53A0 <= 0) {
                            if (campaignWork.unk018C == 0) {
                                temp_v0_20 = campaignWork.unk5440;
                                if (!(0 > temp_v0_20)) {
                                    campaignWork.unk5440 = (s8) (temp_v0_20 - 0xA);
                                    if (campaignWork.unk5440 <= 0) {
                                        campaignWork.unk5440 = 0;
                                    }
                                }
                            }
                        }
                    }
                    if ((campaignWork.routesIdle != 0) && (campaignWork.placesReached == 0) && (SzEffect_IsUse2(-1, -1) == 0) && (campaignWork.unk5374 == 0) && (campaignWork.unk5375 == 0) && ((*(s16 *)(ctx + 0xC2)) < 0xC8)) {
                        var_s1_2 = 1;
                    }
                    if ((((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3] != 0) && (campaignWork.windowOpen == 0x100)) {
                        if ((*(s8 *)(ctx + 0)) == 0) {
                            switch ((*(s8 *)(ctx + 0xC6))) { /* switch 9; irregular */
                            case 15:
                            case 17:
                                func_00199B50(&D_0030F1F6, (*(s8 *)(ctx + 0xC6)));
                                break;
                            case 0:
                            case 1:
                                break;
                            default:                /* switch 9 */
                                if (SzPad_Check(0, 0, 0x40) != 0) {
                                    if ((campaignWork.unk546D == 0) && (campaignWork.talkStep == 0) && (var_s1_2 != 0)) {
                                        SzSound_PlaySE(0, 4);
                                        campaignWork.unk546D = 1;
                                        func_00199B50(&D_0030F213, (*(s8 *)(ctx + 0xC6)));
                                    }
                                    if (((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3] == 1) {
                                        if (campaignWork.talkStep == 0) {
                                            campaignWork.talkStep = 1;
                                            campaignWork.unk53A0 = 0;
                                            campaignWork.unk5375 = 1;
                                            if (campaignWork.leaderShow == 0) {
                                                if (var_s1_2 != 0) {
                                                    campaignWork.leaderShow = 1;
                                                }
                                            }
                                            campaignWork.talkPage = 1;
                                        }
                                        temp_v1_8 = campaignWork.talkStep;
                                        if (temp_v1_8 == 4) {
                                            campaignWork.talkStep = (s8) (temp_v1_8 + 1);
                                            SzSound_PlaySE(0, 2);
                                        }
                                        Taku_Camp_BUN_HANTEI();
                                    } else if ((*(s8 *)(ctx + 0xC6)) == 0xB) {
                                        if (((*(s8 *)(ctx + 0xE)) == 3) && (campaignWork.duelMenuChoice == 1)) {
                                            if (campaignWork.talkStep == 0) {
                                                campaignWork.talkStep = 1;
                                                campaignWork.unk53A0 = 0;
                                                campaignWork.unk5375 = 1;
                                                if (campaignWork.leaderShow == 0) {
                                                    if (var_s1_2 != 0) {
                                                        campaignWork.leaderShow = 1;
                                                    }
                                                }
                                                campaignWork.talkPage = 1;
                                            }
                                            temp_v1_9 = campaignWork.talkStep;
                                            if (temp_v1_9 == 4) {
                                                campaignWork.talkStep = (s8) (temp_v1_9 + 1);
                                                SzSound_PlaySE(0, 2);
                                            }
                                            Taku_Camp_BUN_HANTEI();
                                        } else {
                                            goto block_544;
                                        }
                                    } else {
block_544:
                                        campaignWork.unk5375 = 1;
                                        if (campaignWork.leaderShow == 0) {
                                            if (var_s1_2 != 0) {
                                                campaignWork.leaderShow = 1;
                                            }
                                        }
                                        temp_v1_10 = campaignWork.talkStep;
                                        if (temp_v1_10 == 4) {
                                            campaignWork.talkStep = (s8) (temp_v1_10 + 1);
                                            SzSound_PlaySE(0, 2);
                                        }
                                    }
                                }
                                break;
                            }
                        } else {
                            switch ((*(s8 *)(ctx + 0xC6))) { /* switch 10; irregular */
                            case 1:
                                func_00199B50(&D_0030F227, (*(s8 *)(ctx + 0xC6)));
                                break;
                            case 15:
                                if (((*(s8 *)(ctx + 0x13)) == 0) && (SzPad_Check(0, 0, 0x40) != 0)) {
                                    if (campaignWork.unk546D == 0) {
                                        if ((campaignWork.talkStep == 0) && (var_s1_2 != 0)) {
                                            SzSound_PlaySE(0, 4);
                                            campaignWork.unk546D = 1;
                                        }
                                    }
                                    if (campaignWork.talkStep == 0) {
                                        campaignWork.unk53A0 = 0;
                                        campaignWork.unk5375 = 1;
                                        if ((campaignWork.leaderShow == 0) && (var_s1_2 != 0)) {
                                            campaignWork.leaderShow = 1;
                                        }
                                    }
                                }
                                break;
                            case 17:
                                break;
                            default:
                                if (SzPad_Check(0, 0, 0x40) != 0) {
                                    if ((campaignWork.unk546D == 0) && (campaignWork.talkStep == 0) && (var_s1_2 != 0)) {
                                        SzSound_PlaySE(0, 4);
                                        campaignWork.unk546D = 1;
                                        func_00199B50(&D_0030F244, (*(s8 *)(ctx + 0xC6)));
                                    }
                                    if (((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3] == 1) {
                                        if (campaignWork.talkStep == 0) {
                                            campaignWork.talkStep = 1;
                                            campaignWork.talkPage = 1;
                                            campaignWork.unk53A0 = 0;
                                            campaignWork.unk5375 = 1;
                                            if ((campaignWork.leaderShow == 0) && (var_s1_2 != 0)) {
                                                campaignWork.leaderShow = 1;
                                            }
                                        }
                                        temp_v1_11 = campaignWork.talkStep;
                                        if (temp_v1_11 == 4) {
                                            campaignWork.talkStep = (s8) (temp_v1_11 + 1);
                                            SzSound_PlaySE(0, 2);
                                        }
                                        Taku_Camp_BUN_HANTEI();
                                    } else {
                                        campaignWork.unk5375 = 1;
                                        if (campaignWork.leaderShow == 0) {
                                            if (var_s1_2 != 0) {
                                                campaignWork.leaderShow = 1;
                                            }
                                        }
                                        temp_v1_12 = campaignWork.talkStep;
                                        if (temp_v1_12 == 4) {
                                            campaignWork.talkStep = (s8) (temp_v1_12 + 1);
                                            SzSound_PlaySE(0, 2);
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                } else {
                    temp_s1_3 = (*(s8 *)(ctx + 0));
                    var_s2 = 0;
                    if ((campaignWork.windowOpen == 0x100) && (campaignWork.routesIdle != 0) && (campaignWork.placesReached == 0) && (SzEffect_IsUse2(-1, -1) == 0) && (campaignWork.unk5374 == 0) && (campaignWork.unk5375 == 0) && ((*(s16 *)(ctx + 0xC2)) < 0xC8)) {
                        var_s2 = 1;
                    }
                    if (var_s2 != 0) {
                        if (temp_s1_3 == 0) {
                            switch ((*(s8 *)(ctx + 0xC6))) { /* switch 11; irregular */
                            case 0:
                            case 1:
                                break;
                            case 11:                /* switch 11 */
                                if (((*(s8 *)(ctx + 0xE)) != 0) && (SzPad_Check(0, 1, 0x40) != 0)) {
                                    if (SzPad_Check(0, 0, 0x40) != 0) {
                                        SzSound_PlaySE(0, 6);
                                    }
                                    campaignWork.unk5446 = 1;
                                }
                                break;
                            default:                /* switch 11 */
                                if (SzPad_Check(0, 1, 0x40) != 0) {
                                    if (SzPad_Check(0, 0, 0x40) != 0) {
                                        SzSound_PlaySE(0, 6);
                                    }
                                    campaignWork.unk5446 = 1;
                                }
                                break;
                            }
                        } else {
                            switch ((*(s8 *)(ctx + 0xC6))) { /* switch 12; irregular */
                            case 15:
                            case 17:
                                break;
                            case 11:                /* switch 12 */
                                if (((*(s8 *)(ctx + 0xE)) != 0) && (SzPad_Check(0, 1, 0x40) != 0)) {
                                    if (SzPad_Check(0, 0, 0x40) != 0) {
                                        SzSound_PlaySE(0, 6);
                                    }
                                    campaignWork.unk5446 = 1;
                                }
                                break;
                            default:                /* switch 12 */
                                if (SzPad_Check(0, 1, 0x40) != 0) {
                                    if (SzPad_Check(0, 0, 0x40) != 0) {
                                        SzSound_PlaySE(0, 6);
                                    }
                                    campaignWork.unk5446 = 1;
                                }
                                break;
                            }
                        }
                    }
                }
            } else {
                goto block_623;
            }
        } else {
block_623:
            campaignWork.unk5446 = 0;
        }
        temp_a1_7 = campaignWork.cameraMode;
        switch (temp_a1_7) {                        /* switch 13; irregular */
        case 1:                                     /* switch 13 */
            temp_v0_21 = campaignWork.zoomMove;
            if (temp_v0_21 == 1) {
                campaignWork.zoom = (s16) (campaignWork.zoom + 0x10);
                if (campaignWork.zoom > 0x1000) {
                    campaignWork.zoom = 0x1000;
                    campaignWork.zoomMove = 0;
                }
            } else if (temp_v0_21 == 2) {
                campaignWork.zoom = (s16) (campaignWork.zoom - 0x10);
                if (campaignWork.zoom < 0) {
                    campaignWork.zoom = 0;
                    campaignWork.zoomMove = 0;
                }
            }
            campaignWork.cameraTarget[0] = 0.0f;
            campaignWork.cameraTarget[2] = 0.0f;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.cameraEye[0] = (f32) campaignWork.cameraTarget[0];
            campaignWork.cameraEye[1] = (f32) (20.0f + campaignWork.cameraTarget[1] + ((1700.0f * (f32) campaignWork.zoom) / 4096.0f));
            campaignWork.cameraEye[2] = (f32) (1.0f + campaignWork.cameraTarget[2]);
            campaignWork.cameraEye[3] = campaignWork.cameraTarget[3];
            campaignWork.stoneSpin = (s16) (campaignWork.stoneSpin - 0x300);
            break;
        case 2:                                     /* switch 13 */
            temp_v1_13 = campaignWork.zoomMove;
            if (temp_v1_13 == 1) {
                campaignWork.zoom = (s16) (campaignWork.zoom + 0x100);
                if (campaignWork.zoom > 0x1000) {
                    campaignWork.zoom = 0x1000;
                    campaignWork.zoomMove = 0;
                }
            } else if (temp_v1_13 == 2) {
                campaignWork.zoom = (s16) (campaignWork.zoom - 0x100);
                if (campaignWork.zoom < 0) {
                    campaignWork.zoom = 0;
                    campaignWork.zoomMove = 0;
                }
            }
            if (campaignWork.unk547F != 0) {
                campaignWork.eventPictureMapX = 0.0f;
                campaignWork.eventPictureMapZ = 0.0f;
                temp_a1_8 = campaignWork.unk547F;
                switch (temp_a1_8) {                /* switch 16; irregular */
                case 1:                             /* switch 16 */
                    campaignWork.unk5480 = (s8) (campaignWork.unk5480 + 5);
                    if (campaignWork.unk5480 >= 0x64) {
                        campaignWork.unk5480 = 0x64;
                        campaignWork.unk547F = 2;
                    }
                    break;
                case 2:                             /* switch 16 */
                    campaignWork.unk5480 = 0x64;
                    if (campaignWork.unk546E == 5) {
                        campaignWork.unk547F = 3;
                    }
                    break;
                case 3:                             /* switch 16 */
                    campaignWork.unk5480 = (s8) (campaignWork.unk5480 - 5);
                    if (campaignWork.unk5480 <= 0) {
                        campaignWork.unk5480 = 0;
                        campaignWork.unk547F = 4;
                    }
                    break;
                case 4:                             /* switch 16 */
                    campaignWork.unk547E = 0;
                    break;
                }
                temp_hi = (s32) campaignWork.unk547E % 3;
                switch (temp_hi) {                  /* switch 17; irregular */
                case 0:                             /* switch 17 */
                    campaignWork.eventPictureMapX = 0.0f;
                    break;
                case 1:                             /* switch 17 */
                    var_f0 = (-2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapX = var_f0;
                    break;
                case 2:                             /* switch 17 */
                    var_f0 = (2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapX = var_f0;
                    break;
                }
                temp_hi_2 = (s32) campaignWork.unk547E % 5;
                switch (temp_hi_2) {                /* switch 18; irregular */
                case 0:                             /* switch 18 */
                    campaignWork.eventPictureMapZ = 0.0f;
                    break;
                case 1:                             /* switch 18 */
                    var_f0_2 = (-2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = var_f0_2;
                    break;
                case 2:                             /* switch 18 */
                    var_f0_2 = (2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = var_f0_2;
                    break;
                case 3:                             /* switch 18 */
                    var_f0_2 = (-1.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = var_f0_2;
                    break;
                case 4:                             /* switch 18 */
                    var_f0_2 = (f32) campaignWork.unk5480 / 100.0f;
                    campaignWork.eventPictureMapZ = var_f0_2;
                    break;
                }
                campaignWork.cameraEye[0] = (f32) campaignWork.eventPictureMapX;
                campaignWork.cameraEye[1] = (f32) campaignWork.eventPictureMapZ;
                campaignWork.cameraEye[2] = 512.0f;
                *(s32 *)&campaignWork.cameraEye[3] = 0;
                campaignWork.cameraTarget[0] = (f32) (((-64.0f * (f32) campaignWork.eventPictureZoom) / 100.0f) + campaignWork.eventPictureMapX);
                campaignWork.cameraTarget[1] = (f32) (20.2f + ((768.0f * (f32) campaignWork.zoom) / 4096.0f) + campaignWork.eventPictureMapZ);
                campaignWork.cameraTarget[2] = 0.0f;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
                campaignWork.unk547E = (u8) (campaignWork.unk547E + 1);
            } else {
                campaignWork.cameraEye[0] = 0.0f;
                campaignWork.cameraEye[1] = 0.0f;
                campaignWork.cameraEye[2] = 512.0f;
                *(s32 *)&campaignWork.cameraEye[3] = 0;
                campaignWork.cameraTarget[0] = (f32) ((-64.0f * (f32) campaignWork.eventPictureZoom) / 100.0f);
                campaignWork.cameraTarget[1] = (f32) (20.2f + ((768.0f * (f32) campaignWork.zoom) / 4096.0f));
                campaignWork.cameraTarget[2] = 0.0f;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
            }
            break;
        case 3:                                     /* switch 13 */
            temp_v1_14 = campaignWork.zoomMove;
            if (temp_v1_14 == 1) {
                campaignWork.zoom = (s16) (campaignWork.zoom + 0x80);
                if (campaignWork.zoom > 0x1000) {
                    campaignWork.zoom = 0x1000;
                    campaignWork.zoomMove = 0;
                }
            } else if (temp_v1_14 == 2) {
                campaignWork.zoom = (s16) (campaignWork.zoom - 0x80);
                if (campaignWork.zoom < 0) {
                    campaignWork.zoom = 0;
                    campaignWork.zoomMove = 0;
                }
            }
            temp_v0_22 = campaignWork.unk547F;
            if (temp_v0_22 != 0) {
                switch ((s8) temp_v0_22) {
                case 1:                             /* switch 20 */
                    campaignWork.unk5480 = (s8) (campaignWork.unk5480 + 5);
                    if (campaignWork.unk5480 >= 0x64) {
                        campaignWork.unk5480 = 0x64;
                        campaignWork.unk547F = 2;
                    }
                    break;
                case 2:                             /* switch 20 */
                    campaignWork.unk5480 = 0x64;
                    if (campaignWork.unk546E == 5) {
                        campaignWork.unk547F = 3;
                    }
                    break;
                case 3:                             /* switch 20 */
                    campaignWork.unk5480 = (s8) (campaignWork.unk5480 - 5);
                    if (campaignWork.unk5480 <= 0) {
                        campaignWork.unk5480 = 0;
                        campaignWork.unk547F = 4;
                    }
                    break;
                case 4:                             /* switch 20 */
                    campaignWork.unk547E = 0U;
                    break;
                }
                temp_hi_3 = (s32) campaignWork.unk547E % 3;
                switch (temp_hi_3) {                /* switch 21; irregular */
                case 0:                             /* switch 21 */
                    campaignWork.eventPictureMapX = 0.0f;
                    break;
                case 1:                             /* switch 21 */
                    var_f0_3 = (-2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapX = var_f0_3;
                    break;
                case 2:                             /* switch 21 */
                    var_f0_3 = (2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapX = var_f0_3;
                    break;
                }
                temp_hi_4 = (s32) campaignWork.unk547E % 5;
                switch (temp_hi_4) {                /* switch 22; irregular */
                case 0:                             /* switch 22 */
                    campaignWork.eventPictureMapZ = 0.0f;
                    break;
                case 1:                             /* switch 22 */
                    fq4 = (-2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = fq4;
                    break;
                case 2:                             /* switch 22 */
                    fq4 = (2.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = fq4;
                    break;
                case 3:                             /* switch 22 */
                    fq4 = (-1.0f * (f32) campaignWork.unk5480) / 100.0f;
                    campaignWork.eventPictureMapZ = fq4;
                    break;
                case 4:                             /* switch 22 */
                    fq4 = (f32) campaignWork.unk5480 / 100.0f;
                    campaignWork.eventPictureMapZ = fq4;
                    break;
                }
                campaignWork.cameraEye[0] = (f32) campaignWork.eventPictureMapX;
                campaignWork.cameraEye[1] = (f32) campaignWork.eventPictureMapZ;
                campaignWork.cameraEye[2] = 512.0f;
                *(s32 *)&campaignWork.cameraEye[3] = 0;
                campaignWork.cameraTarget[0] = (f32) (((-64.0f * (f32) campaignWork.eventPictureZoom) / 100.0f) + campaignWork.eventPictureMapX);
                campaignWork.cameraTarget[1] = (f32) (20.2f + ((512.0f * (f32) campaignWork.zoom) / 4096.0f) + campaignWork.eventPictureMapZ);
                campaignWork.cameraTarget[2] = 0.0f;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
                campaignWork.unk547E = (u8) (campaignWork.unk547E + 1);
            } else {
                campaignWork.cameraEye[0] = 0.0f;
                campaignWork.cameraEye[1] = 0.0f;
                campaignWork.cameraEye[2] = 512.0f;
                *(s32 *)&campaignWork.cameraEye[3] = 0;
                campaignWork.cameraTarget[0] = (f32) ((-64.0f * (f32) campaignWork.eventPictureZoom) / 100.0f);
                campaignWork.cameraTarget[1] = (f32) (20.2f + ((512.0f * (f32) campaignWork.zoom) / 4096.0f));
                campaignWork.cameraTarget[2] = 0.0f;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
                campaignWork.unk547E = 0U;
            }
            break;
        default:                                    /* switch 13 */
            c23 = campaignWork.zoomMove;
            if (c23 == 1) {
                campaignWork.zoom = (s16) (campaignWork.zoom + 8);
                if (campaignWork.zoom > 0x100) {
                    campaignWork.zoom = 0x100;
                    campaignWork.zoomMove = 0;
                }
            } else if (c23 == 2) {
                campaignWork.zoom = (s16) (campaignWork.zoom - 8);
                if (campaignWork.zoom < 0) {
                    campaignWork.zoom = 0;
                    campaignWork.zoomMove = 0;
                }
            }
            campaignWork.cameraTarget[1] = 0.0f;
            campaignWork.cameraEye[0] = campaignWork.cameraTarget[0];
            campaignWork.cameraEye[1] = 96.0f + campaignWork.cameraTarget[1] + ((96.0f * (f32) campaignWork.zoom) / 256.0f);
            campaignWork.cameraEye[2] = 96.0f + campaignWork.cameraTarget[2];
            campaignWork.cameraEye[3] = campaignWork.cameraTarget[3];
            break;
        }
        SzView_SetCamera(0, (void *)&campaignWork.cameraEye[0], (void *)&campaignWork.cameraTarget[0]);
        TkCamp_Act2(0);
end_TkCamp_Act:;
}
#pragma opt_dead_assignments reset
#pragma conditional_move reset
