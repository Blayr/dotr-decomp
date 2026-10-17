#include "common.h"
#include "game.h"
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
    u8 *base = (u8 *)0x01ED0000;
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
    s32 temp_s1_2;
    s32 temp_v0_19;
    s32 temp_v0_2;
    s32 var_a0_4;
    s32 var_a2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_v1;
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

    temp_s1 = *(s16 *)0x01ED0000;
    temp_s2 = *(s16 *)0x01ED0002;
    *(s8 *)0x01ED547A = 0;
    *(s8 *)0x01ED5481 = 1;
    *(s8 *)0x01ED5482 = 0;
    var_s3 = 0;
    if (D_00299ED2 < 0x2710) {
        temp_v0 = *(s8 *)0x01ED006E;
        if (temp_v0 != 0) {
            *(s16 *)0x01ED0070 = (s16) (*(s16 *)0x01ED0070 + 0x14);
            if (*(s16 *)0x01ED0070 >= 0x100) {
                *(s16 *)0x01ED0070 = 0x100;
                *(s8 *)0x01ED5374 = 0;
            }
        } else if ((s8) temp_v0 == 0) {
            *(s8 *)0x01ED5374 = 1;
            *(s16 *)0x01ED0070 = (s16) (*(s16 *)0x01ED0070 - 0x14);
            if (*(s16 *)0x01ED0070 <= 0) {
                *(s16 *)0x01ED0070 = 0;
            }
        }
        temp_v1 = *(s8 *)0x01ED006A;
        if ((temp_v1 != 0) && (*(s8 *)0x01ED006E != 0) && (*(s8 *)0x01ED53C1 == 0)) {
            if (*(s8 *)0x01ED540A == 0) {
                *(s8 *)0x01ED540A = 1;
                *(s8 *)0x01ED5406 = 0;
            }
            *(s16 *)0x01ED006C = (s16) (*(s16 *)0x01ED006C + 0x14);
            *(s8 *)0x01ED53C1 = 0;
            if (*(s16 *)0x01ED006C >= 0x100) {
                *(s16 *)0x01ED006C = 0x100;
            }
        } else if (((s8) temp_v1 == 0) || (*(s8 *)0x01ED006E == 0) || (*(s8 *)0x01ED53C1 == 1)) {
            *(s16 *)0x01ED006C = (s16) (*(s16 *)0x01ED006C - 0x14);
            if (*(s16 *)0x01ED006C <= 0) {
                *(s16 *)0x01ED006C = 0;
                *(s8 *)0x01ED53AB = 0;
                *(s8 *)0x01ED53C1 = 0;
                *(s8 *)0x01ED53C2 = (*(s8 *)(ctx + 0xC9));
                if (*(s8 *)0x01ED540A != 0) {
                    ShFace_Close((u8 *)0x01ED5424);
                    *(s8 *)0x01ED540A = 0;
                }
            }
        }
    } else {
        *(s8 *)0x01ED5374 = 1;
        *(s8 *)0x01ED006E = 0;
        *(s8 *)0x01ED006A = 0;
        if (*(s8 *)0x01ED006E == 0) {
            *(s16 *)0x01ED0070 = (s16) (*(s16 *)0x01ED0070 - 0x14);
            if (*(s16 *)0x01ED0070 <= 0) {
                *(s16 *)0x01ED0070 = 0;
            }
        }
        if ((*(s8 *)0x01ED006A == 0) || (*(s8 *)0x01ED006E == 0)) {
            *(s16 *)0x01ED006C = (s16) (*(s16 *)0x01ED006C - 0x14);
            if (*(s16 *)0x01ED006C <= 0) {
                *(s16 *)0x01ED006C = 0;
                *(s8 *)0x01ED53AB = 0;
                if (*(s8 *)0x01ED540A != 0) {
                    ShFace_Close((u8 *)0x01ED5424);
                    *(s8 *)0x01ED540A = 0;
                }
            }
        }
    }
    for (var_v1 = 0; var_v1 <= 0x15; var_v1++) {
        if (((s16 *)base)[var_v1 + 0x2976] != 0) {
            *(s8 *)(base + 0x5482) = (s8) (*(s8 *)(base + 0x5482) + 1);
        }
    }
    if (*(s8 *)0x01ED5376 != 0) {
        if ((*(s8 *)0x01ED5482 == 0) && (SzEffect_IsUse2(-1, -1) == 0) && (*(s8 *)0x01ED5374 == 0) && (*(s8 *)0x01ED5375 == 0) && ((*(s16 *)(ctx + 0xC2)) < 0xC8)) {
            for (var_a2 = 0; var_a2 < 4; var_a2++) {
                var_a3 = &camp_sys_icon[var_a2 * 0x13];
                temp_a1 = *(s16 *)(base + 0);
                if (((M2C_FIELD(var_a3, s16 *, 0) - 2) <= temp_a1) && (temp_a1 <= (M2C_FIELD(var_a3, s16 *, 4) + 2))) {
                    temp_a1_2 = *(s16 *)(base + 2);
                    if (((M2C_FIELD(var_a3, s16 *, 2) - 2) <= temp_a1_2) && (temp_a1_2 <= (M2C_FIELD(var_a3, s16 *, 6) + 2)) && (*(u16 *)(base + 4) != 1)) {
                        *(s8 *)(base + 0x547A) = 1;
                    }
                }
            }
            if ((*(s8 *)0x01ED547A != 0) && (*(s8 *)0x01ED543E == 0)) {
                switch (*(s16 *)0x01ED0080) {
                case 0:
                    if (SzPad_Check(0, 0, 0x40) != 0) {
                        SzSound_PlaySE(0, 4);
                        SzGame_SetMenuNum(6, 0);
                        SzGame_Push(6, 0);
                        goto end_TkCamp_Act;
                    }
                    break;
                case 1:
                    switch (*(s8 *)0x01ED543C) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 4);
                            SzGame_InitMemCardProc(1);
                            *(s8 *)0x01ED543C = 1;
                            goto end_TkCamp_Act;
                        }
                        break;
                    default:
                        if (0 > SzGame_ActMemCardProc()) {
                            *(s8 *)0x01ED543C = 0;
                        }
                        goto end_TkCamp_Act;
                    }
                    break;
                case 2:
                    switch (*(s8 *)0x01ED543C) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 4);
                            SzDuel_OpenOptionPopup_b((s32) (*(s8 *)(ctx + 0)), 0, 0x200);
                            *(s8 *)0x01ED543C = 1;
                            *(s8 *)0x01ED543D = 0;
                            goto end_TkCamp_Act;
                        }
                        break;
                    case 1:
                        *(s8 *)0x01ED543D = (s8) (*(s8 *)0x01ED543D + 1);
                        if (*(s8 *)0x01ED543D >= 8) {
                            *(s8 *)0x01ED543D = 8;
                            *(s8 *)0x01ED543C = 2;
                        }
                        SzDuel_OpenOptionPopup_b(-1, 0, 0x200 - ((s32) (*(s8 *)0x01ED543D << 9) >> 3));
                        goto end_TkCamp_Act;
                    case 2:
                        if (SzDuel_ActOptionPopup(0) != 0) {
                            *(s8 *)0x01ED543C = 3;
                        }
                        goto end_TkCamp_Act;
                    case 3:
                        *(s8 *)0x01ED543D = (s8) (*(s8 *)0x01ED543D - 1);
                        if (*(s8 *)0x01ED543D <= 0) {
                            *(s8 *)0x01ED543D = 8;
                            *(s8 *)0x01ED543C = 4;
                        }
                        SzDuel_OpenOptionPopup_b(-1, 0, 0x200 - ((s32) (*(s8 *)0x01ED543D << 9) >> 3));
                        if (*(s8 *)0x01ED543C == 4) {
                            *(s8 *)0x01ED543C = 0;
                            SzDuel_CloseOptionPopup();
                        }
                        goto end_TkCamp_Act;
                    }
                    break;
                case 3:
                    switch (*(s8 *)0x01ED543C) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 4);
                            *(s8 *)0x01ED543C = 1;
                            *(s8 *)0x01ED543D = 0;
                            *(s8 *)0x01ED546B = 0;
                            goto end_TkCamp_Act;
                        }
                        break;
                    case 1:
                        *(s8 *)0x01ED543D = (s8) (*(s8 *)0x01ED543D + 1);
                        if (*(s8 *)0x01ED543D >= 8) {
                            *(s8 *)0x01ED543D = 8;
                            *(s8 *)0x01ED543C = 2;
                        }
                        goto end_TkCamp_Act;
                    case 2:
                        if (SzPad_Check(0, 0, 0x20) != 0) {
                            SzSound_PlaySE(0, 5);
                            *(s8 *)0x01ED543C = 0xA;
                        } else if (SzPad_Check(0, 0, 0x40) != 0) {
                            SzSound_PlaySE(0, 1);
                            *(s8 *)0x01ED543C = 3;
                        }
                        if (*(s8 *)0x01ED543C == 3) {
                            Taku_Camp_Go_Help();
                        }
                        if (*(s8 *)0x01ED543C < 3) {
                            if (SzPad_Check(0, 2, 0x1000) != 0) {
                                SzSound_PlaySE(0, 3);
                                *(s8 *)0x01ED546B = (s8) (*(s8 *)0x01ED546B - 1);
                                if (*(s8 *)0x01ED546B < 0) {
                                    *(s8 *)0x01ED546B = 4;
                                }
                            }
                            if (SzPad_Check(0, 2, 0x4000) != 0) {
                                SzSound_PlaySE(0, 3);
                                *(s8 *)0x01ED546B = (s8) (*(s8 *)0x01ED546B + 1);
                                if (*(s8 *)0x01ED546B > 4) {
                                    *(s8 *)0x01ED546B = 0;
                                }
                            }
                        }
                        goto end_TkCamp_Act;
                    case 10:
                        *(s8 *)0x01ED543D = (s8) (*(s8 *)0x01ED543D - 1);
                        if (*(s8 *)0x01ED543D <= 0) {
                            *(s8 *)0x01ED543D = 0;
                            *(s8 *)0x01ED543C = 0;
                        }
                        goto end_TkCamp_Act;
                    }
                    break;
                }
            }
            {
                if (*(s8 *)0x01ED543C == 0) {
                    switch (*(s8 *)0x01ED543E) {
                    case 0:
                        if (SzPad_Check(0, 0, 0x100) != 0) {
                            SzSound_PlaySE(0, 4);
                            SzDuel_OpenMsgPopup(7, 0, 0x200, 0x91);
                            *(s8 *)0x01ED543E = 1;
                            goto end_TkCamp_Act;
                        }
                        break;
                    case 1:
                        *(s8 *)0x01ED543F = (s8) (*(s8 *)0x01ED543F + 1);
                        if (*(s8 *)0x01ED543F >= 8) {
                            *(s8 *)0x01ED543F = 8;
                            *(s8 *)0x01ED543E = 2;
                        }
                        SzDuel_OpenMsgPopup(7, 0, 0x200 - ((s32) (*(s8 *)0x01ED543F << 9) >> 3), -1);
                        goto end_TkCamp_Act;
                    case 2:
                        temp_v0_2 = SzDuel_ActMsgPopup(0);
                        switch (temp_v0_2) {
                        case 1:
                            *(s8 *)0x01ED543E = 3;
                            break;
                        case 2:
                            *(s8 *)0x01ED543E = 4;
                            break;
                        }
                        return;
                    case 3:
                        SzGame_Pop();
                        goto end_TkCamp_Act;
                    case 4:
                        *(s8 *)0x01ED543F = (s8) (*(s8 *)0x01ED543F - 1);
                        temp_v0_3 = *(s8 *)0x01ED543F;
                        if (temp_v0_3 <= 0) {
                            *(s8 *)0x01ED543F = 0;
                            *(s8 *)0x01ED543E = 0;
                            SzDuel_CloseMsgPopup();
                        } else {
                            SzDuel_OpenMsgPopup(7, 0, 0x200 - ((s32) (temp_v0_3 << 9) >> 3), -1);
                        }
                        goto end_TkCamp_Act;
                    }
                }
                {
                    if (*(s8 *)0x01ED543E == 0) {
                        SzPad_Check(0, 1, 0x800);
                        if (SzPad_Check(0, 0, 0x800) != 0) {
                            SzSound_PlaySE(0, 4);
                            temp_v1_4 = *(s8 *)0x01ED0072;
                            if (temp_v1_4 == 0) {
                                *(s8 *)0x01ED0072 = 1;
                                *(s16 *)0x01ED007A = 0;
                                *(s16 *)0x01ED007C = 0;
                            } else if (temp_v1_4 == 1) {
                                *(s8 *)0x01ED0072 = 2;
                            }
                        }
                    }
                    if (SzPad_IsAnalog(0) != 0) {
                        ax = SzPad_GetAnalogInfo(0, 2) & 0xFF;
                        ay = SzPad_GetAnalogInfo(0, 3) & 0xFF;
                        dx = ax - 0x80;
                        if (abs_b(dx) > 0x30) {
                            sgn = (0 <= dx) ? 1 : -1;
                            *(f32 *)0x01ED0040 = *(f32 *)0x01ED0040 + ((4.0f * (f32) (dx - (sgn * 0x30))) / 79.0f);
                        }
                        ax = ay - 0x80;
                        if (abs_b(ax) > 0x30) {
                            sgn = (0 <= ax) ? 1 : -1;
                            *(f32 *)0x01ED0048 = *(f32 *)0x01ED0048 + ((4.0f * (f32) (ax - (sgn * 0x30))) / 79.0f);
                        }
                    }
                    SzPad_Check(0, 1, 0x100);
                    SzPad_Check(0, 2, 0x100);
                    if (*(u16 *)0x01ED0004 == 1) {
                        vp[0] = (f32) (*(s16 *)0x01ED0000 - 0x140);
                        vp[1] = (f32) (*(s16 *)0x01ED0002 - 0xE0);
                        vp[2] = 1.0f;
                        vp[3] = 1.0f;
                        vq[0] = (f32) (*(s16 *)0x01ED0000 - 0x140);
                        vq[1] = (f32) (*(s16 *)0x01ED0002 - 0xE0);
                        vq[2] = 100.0f;
                        vq[3] = 1.0f;
                        Ex3d_GetPointOnScreen(vp, vp[0], vp[1]);
                        *(TkVec4 *)vq = *(TkVec4 *)SzView_GetSP(0);
                        Ex3d_IntersectP((void *)0x01ED0190, vp, vq, vr);
                    }
                    if (SzPad_Check(0, 1, 0x1000) != 0) {
                        if (*(s8 *)0x01ED0072 != 0) {
                            *(s16 *)0x01ED007C = 0;
                            if (SzPad_Check(0, 0, 0x1000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (*(u16 *)0x01ED0004 == 1) {
                            temp_v0_5 = *(s16 *)0x01ED0002;
                            if (0 < temp_v0_5) {
                                *(s16 *)0x01ED0002 = (s16) (temp_v0_5 - 0x18);
                                if (*(s16 *)0x01ED0002 <= 0) {
                                    *(s16 *)0x01ED0002 = 0;
                                }
                            } else {
                                *(s16 *)0x01ED0002 = 0;
                            }
                        } else {
                            temp_v0_6 = *(s16 *)0x01ED0002;
                            if (0 < temp_v0_6) {
                                *(s16 *)0x01ED0002 = (s16) (temp_v0_6 - 0x10);
                                if (*(s16 *)0x01ED0002 <= 0) {
                                    *(s16 *)0x01ED0002 = 0;
                                }
                            } else {
                                *(s16 *)0x01ED0002 = 0;
                                *(f32 *)0x01ED0048 = (f32) (*(f32 *)0x01ED0048 - 4.0f);
                            }
                        }
                    }
                    if (SzPad_Check(0, 1, 0x4000) != 0) {
                        if (*(s8 *)0x01ED0072 != 0) {
                            *(s16 *)0x01ED007C = 1;
                            if (SzPad_Check(0, 0, 0x4000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (*(u16 *)0x01ED0004 == 1) {
                            temp_v0_7 = *(s16 *)0x01ED0002;
                            if (temp_v0_7 < 0x1A0) {
                                *(s16 *)0x01ED0002 = (s16) (temp_v0_7 + 0x18);
                                if (*(s16 *)0x01ED0002 >= 0x1A0) {
                                    *(s16 *)0x01ED0002 = 0x1A0;
                                }
                            } else {
                                *(s16 *)0x01ED0002 = 0x1A0;
                            }
                        } else {
                            temp_v0_8 = *(s16 *)0x01ED0002;
                            if (temp_v0_8 < 0x1A0) {
                                *(s16 *)0x01ED0002 = (s16) (temp_v0_8 + 0x10);
                                if (*(s16 *)0x01ED0002 >= 0x1A0) {
                                    *(s16 *)0x01ED0002 = 0x1A0;
                                }
                            } else {
                                *(s16 *)0x01ED0002 = 0x1A0;
                                *(f32 *)0x01ED0048 += 4.0f;
                            }
                        }
                    }
                    if (SzPad_Check(0, 1, 0x8000) != 0) {
                        if (*(s8 *)0x01ED0072 != 0) {
                            *(s16 *)0x01ED007A = 0;
                            if (SzPad_Check(0, 0, 0x8000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (*(u16 *)0x01ED0004 == 1) {
                            temp_v0_9 = *(s16 *)0x01ED0000;
                            if (0 < temp_v0_9) {
                                *(s16 *)0x01ED0000 = (s16) (temp_v0_9 - 0x18);
                                if (*(s16 *)0x01ED0000 <= 0) {
                                    *(s16 *)0x01ED0000 = 0;
                                }
                            } else {
                                *(s16 *)0x01ED0000 = 0;
                            }
                        } else {
                            temp_v0_10 = *(s16 *)0x01ED0000;
                            if (0 < temp_v0_10) {
                                *(s16 *)0x01ED0000 = (s16) (temp_v0_10 - 0x10);
                                if (*(s16 *)0x01ED0000 <= 0) {
                                    *(s16 *)0x01ED0000 = 0;
                                }
                            } else {
                                *(s16 *)0x01ED0000 = 0;
                                *(f32 *)0x01ED0040 = (f32) (*(f32 *)0x01ED0040 - 4.0f);
                            }
                        }
                    }
                    if (SzPad_Check(0, 1, 0x2000) != 0) {
                        if (*(s8 *)0x01ED0072 != 0) {
                            *(s16 *)0x01ED007A = 1;
                            if (SzPad_Check(0, 0, 0x2000) != 0) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (*(u16 *)0x01ED0004 == 1) {
                            temp_v0_11 = *(s16 *)0x01ED0000;
                            if (temp_v0_11 < 0x260) {
                                *(s16 *)0x01ED0000 = (s16) (temp_v0_11 + 0x18);
                                if (*(s16 *)0x01ED0000 >= 0x260) {
                                    *(s16 *)0x01ED0000 = 0x260;
                                }
                            } else {
                                *(s16 *)0x01ED0000 = 0x260;
                            }
                        } else {
                            temp_v0_12 = *(s16 *)0x01ED0000;
                            if (temp_v0_12 < 0x260) {
                                *(s16 *)0x01ED0000 = (s16) (temp_v0_12 + 0x10);
                                if (*(s16 *)0x01ED0000 >= 0x260) {
                                    *(s16 *)0x01ED0000 = 0x260;
                                }
                            } else {
                                *(s16 *)0x01ED0000 = 0x260;
                                *(f32 *)0x01ED0040 += 4.0f;
                            }
                        }
                    }
                    if (*(u16 *)0x01ED0004 == 1) {
                        vp[0] = (f32) (*(s16 *)0x01ED0000 - 0x140);
                        vp[1] = (f32) (*(s16 *)0x01ED0002 - 0xE0);
                        vp[2] = 1.0f;
                        vp[3] = 1.0f;
                        vq[0] = (f32) (*(s16 *)0x01ED0000 - 0x140);
                        vq[1] = (f32) (*(s16 *)0x01ED0002 - 0xE0);
                        vq[2] = 100.0f;
                        vq[3] = 1.0f;
                        hit = 0;
                        Ex3d_GetPointOnScreen(vp, vp[0], vp[1]);
                        *(TkVec4 *)vq = *(TkVec4 *)SzView_GetSP(0);
                        Ex3d_IntersectP((void *)0x01ED0190, vp, vq, vs);
                        vs[0] -= vr[0];
                        vs[1] -= vr[1];
                        vs[2] -= vr[2];
                        *(f32 *)0x01ED0040 = (f32) (*(f32 *)0x01ED0040 - vs[0]);
                        *(f32 *)0x01ED0048 = (f32) (*(f32 *)0x01ED0048 - vs[2]);
                        if (*(f32 *)0x01ED0040 < -200.0f) {
                            hit++;
                            *(s16 *)0x01ED0000 = temp_s1;
                        } else if (110.0f < *(f32 *)0x01ED0040) {
                            hit++;
                            *(s16 *)0x01ED0000 = temp_s1;
                        }
                        if (*(f32 *)0x01ED0048 < -220.0f) {
                            hit++;
                            *(s16 *)0x01ED0002 = temp_s2;
                        } else if (210.0f < *(f32 *)0x01ED0048) {
                            hit++;
                            *(s16 *)0x01ED0002 = temp_s2;
                        }
                        if (hit) {
                            *(f32 *)0x01ED0040 = (f32) (*(f32 *)0x01ED0040 + vs[0]);
                            *(f32 *)0x01ED0048 = (f32) (*(f32 *)0x01ED0048 + vs[2]);
                            vp[0] = (f32) (*(s16 *)0x01ED0000 - 0x140);
                            vp[1] = (f32) (*(s16 *)0x01ED0002 - 0xE0);
                            vp[2] = 1.0f;
                            vp[3] = 1.0f;
                            vq[0] = (f32) (*(s16 *)0x01ED0000 - 0x140);
                            vq[1] = (f32) (*(s16 *)0x01ED0002 - 0xE0);
                            vq[2] = 100.0f;
                            vq[3] = 1.0f;
                            Ex3d_GetPointOnScreen(vp, vp[0], vp[1]);
                            *(TkVec4 *)vq = *(TkVec4 *)SzView_GetSP(0);
                            Ex3d_IntersectP((void *)0x01ED0190, vp, vq, vs);
                            vs[0] -= vr[0];
                            vs[1] -= vr[1];
                            vs[2] -= vr[2];
                            *(f32 *)0x01ED0040 = (f32) (*(f32 *)0x01ED0040 - vs[0]);
                            *(f32 *)0x01ED0048 = (f32) (*(f32 *)0x01ED0048 - vs[2]);
                        }
                    }
                    if (*(f32 *)0x01ED0040 < -200.0f) {
                        *(f32 *)0x01ED0040 = -200.0f;
                    } else if (110.0f < *(f32 *)0x01ED0040) {
                        *(f32 *)0x01ED0040 = 110.0f;
                    }
                    if (*(f32 *)0x01ED0048 < -220.0f) {
                        *(f32 *)0x01ED0048 = -220.0f;
                    } else if (210.0f < *(f32 *)0x01ED0048) {
                        *(f32 *)0x01ED0048 = 210.0f;
                    }
                    SzPad_Check(0, 1, 0x10);
                    temp_a1_4 = ((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3];
                    if ((temp_a1_4 != 0) && (*(s16 *)0x01ED006C == 0x100)) {
                        {
                            ok = 0;
                            if (*(s8 *)0x01ED018C != 0) {
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
                                        if (((*(s8 *)(ctx + 0xC6)) == 0xB) && ((*(s8 *)(ctx + 0xE)) == 3) && (*(s8 *)0x01ED53C2 == 1)) {
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
                                if ((SzPad_Check(0, 0, 0x10) != 0) && (*(u16 *)0x01ED0004 == 2) && (*(s8 *)0x01ED0072 == 0)) {
                                    SzSound_PlaySE(0, 4);
                                    *(s8 *)0x01ED0066 = (s8) (*(s8 *)0x01ED0066 ^ 1);
                                } else if (*(u16 *)0x01ED0004 != 2) {
                                    *(s8 *)0x01ED0066 = 0;
                                }
                            } else {
                                *(s8 *)0x01ED0066 = 0;
                            }
                        }
                    } else {
                        *(s8 *)0x01ED0066 = 0;
                    }
                    if (SzPad_Check(0, 0, 0x20) != 0) {
                        if (*(s8 *)0x01ED0072 == 1) {
                            SzSound_PlaySE(0, 5);
                            *(s8 *)0x01ED0072 = 2;
                        }
                    }
                    if (SzPad_Check(0, 1, 0x80) != 0) {
                        if (*(s8 *)0x01ED0072 == 0) {
                            if (SzPad_Check(0, 0, 0x80) != 0) {
                                SzSound_PlaySE(0, 4);
                            }
                            *(u16 *)0x01ED0004 = 1U;
                        } else {
                            goto block_306;
                        }
                    } else {
block_306:
                        if (*(u16 *)0x01ED0004 == 1) {
                            *(u16 *)0x01ED0004 = 0U;
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
                    if (*(s8 *)0x01ED018C != 0) {
block_314:
                        if ((*(s8 *)0x01ED547A == 0) && (*(u16 *)0x01ED0004 == 2) && ((*(s8 *)(ctx + 0xC6)) == 0xB) && (*(s8 *)0x01ED53C1 == 0)) {
                            if (SzPad_Check(0, 0, 4) != 0) {
                                SzSound_PlaySE(0, 2);
                                (*(s8 *)(ctx + 0xC9)) = (s8) ((*(s8 *)(ctx + 0xC9)) - 1);
                                *(s8 *)0x01ED53C1 = 1;
                                if (*(s8 *)0x01ED018C != 0) {
                                    if ((*(s8 *)(ctx + 0xC9)) < 0) {
                                        (*(s8 *)(ctx + 0xC9)) = 2;
                                    }
                                } else if ((*(s8 *)(ctx + 0xC9)) < 0) {
                                    (*(s8 *)(ctx + 0xC9)) = 1;
                                }
                            } else if (SzPad_Check(0, 0, 8) != 0) {
                                SzSound_PlaySE(0, 2);
                                (*(s8 *)(ctx + 0xC9)) = (s8) ((*(s8 *)(ctx + 0xC9)) + 1);
                                *(s8 *)0x01ED53C1 = 1;
                                if (*(s8 *)0x01ED018C != 0) {
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
        if (*(s16 *)0x01ED536E != (*(s16 *)(ctx + 0xC2))) {
            *(s16 *)0x01ED536C = 0;
            *(s8 *)0x01ED537A = 0;
        }
        *(s16 *)0x01ED536E = (s16) (*(s16 *)(ctx + 0xC2));
        switch ((*(s16 *)(ctx + 0xC2))) { /* switch 6; irregular */
        case 0x2738:                                /* switch 6 */
            if (*(s8 *)0x01ED53A6 == 2) {
                if (*(s8 *)0x01ED53C9 == 0) {
                    if (SzPad_Check(0, 2, 0x1000) != 0) {
                        SzSound_PlaySE(0, 2);
                        *(s8 *)0x01ED53C4 = (s8) (*(s8 *)0x01ED53C4 - 1);
                        if (*(s8 *)0x01ED53C4 < 0) {
                            *(s8 *)0x01ED53C4 = 5;
                        }
                    }
                    if (SzPad_Check(0, 2, 0x4000) != 0) {
                        SzSound_PlaySE(0, 2);
                        *(s8 *)0x01ED53C4 = (s8) (*(s8 *)0x01ED53C4 + 1);
                        if (*(s8 *)0x01ED53C4 > 5) {
                            *(s8 *)0x01ED53C4 = 0;
                        }
                    }
                    if (SzPad_Check(0, 2, 0x8000) != 0) {
                        SzSound_PlaySE(0, 2);
                        *(s8 *)0x01ED53C3 = (s8) (*(s8 *)0x01ED53C3 - 1);
                        if (*(s8 *)0x01ED53C3 < 0) {
                            *(s8 *)0x01ED53C3 = 0xE;
                        }
                    }
                    if (SzPad_Check(0, 2, 0x2000) != 0) {
                        SzSound_PlaySE(0, 2);
                        *(s8 *)0x01ED53C3 = (s8) (*(s8 *)0x01ED53C3 + 1);
                        if (*(s8 *)0x01ED53C3 > 0xE) {
                            *(s8 *)0x01ED53C3 = 0;
                        }
                    }
                    if (SzPad_Check(0, 0, 0x20) != 0) {
                        SzSound_PlaySE(0, 5);
                        *(s8 *)0x01ED53CD = (s8) (*(s8 *)0x01ED53CD - 1);
                        *(s8 *)0x01ED53CE = *(s8 *)0x01ED53CD - 1;
                        if (*(s8 *)0x01ED53CD <= 0) {
                            *(s8 *)0x01ED53CD = 0;
                            *(s8 *)0x01ED53CE = 0;
                        }
                        ((s8 *)0x01ED53CF)[*(s8 *)0x01ED53CD] = 0;
                        ((s8 *)0x01ED53DB)[*(s8 *)0x01ED53CD] = 6;
                        ((s8 *)0x01ED53E7)[*(s8 *)0x01ED53CD] = 1;
                    }
                    if (*(s8 *)0x01ED53CA == 0) {
                        if ((*(s8 *)0x01ED53CD < 0xC) && (SzPad_Check(0, 0, 0xC0) != 0)) {
                            SzSound_PlaySE(0, 4);
                            *(s8 *)0x01ED53CA = 1;
                            *(s8 *)0x01ED53C5 = *(s8 *)0x01ED53C3;
                            *(s8 *)0x01ED53C6 = *(s8 *)0x01ED53C4;
                        }
                    }
                    if ((*(s8 *)0x01ED53CA == 0) && (*(s8 *)0x01ED53CD != 0) && (SzPad_Check(0, 0, 0x800) != 0)) {
                        SzSound_PlaySE(0, 1);
                        *(s8 *)0x01ED53A6 = 3;
                        Taku_Camp_Ivent_Name_Set();
                    }
                }
            }
            temp_v1_5 = *(s8 *)0x01ED53C8;
            if (temp_v1_5 == 1) {
                temp_v0_15 = *(s8 *)0x01ED53C9;
                if (temp_v0_15 < 0x64) {
                    *(s8 *)0x01ED53C9 = (s8) (temp_v0_15 + 0xA);
                }
                if (*(s8 *)0x01ED53C9 >= 0x64) {
                    *(s8 *)0x01ED53C9 = 0;
                    *(s8 *)0x01ED53C8 = 0;
                    *(s8 *)0x01ED53C7 = (s8) (*(s8 *)0x01ED53C7 - 1);
                    if (*(s8 *)0x01ED53C7 < 0) {
                        *(s8 *)0x01ED53C7 = 2;
                    }
                }
            } else if (temp_v1_5 == 2) {
                temp_v0_16 = *(s8 *)0x01ED53C9;
                if (temp_v0_16 > -0x64) {
                    *(s8 *)0x01ED53C9 = (s8) (temp_v0_16 - 0xA);
                }
                if (*(s8 *)0x01ED53C9 < -0x63) {
                    *(s8 *)0x01ED53C9 = 0;
                    *(s8 *)0x01ED53C8 = 0;
                    *(s8 *)0x01ED53C7 = (s8) (*(s8 *)0x01ED53C7 + 1);
                    if (*(s8 *)0x01ED53C7 > 2) {
                        *(s8 *)0x01ED53C7 = 0;
                    }
                }
            }
            if (*(s8 *)0x01ED53CA == 1) {
                temp_v0_17 = *(s8 *)0x01ED53CB;
                if (temp_v0_17 < 0x64) {
                    *(s8 *)0x01ED53CB = (s8) (temp_v0_17 + 0x14);
                }
                if (*(s8 *)0x01ED53CB >= 0x64) {
                    temp_v1_6 = *(s8 *)0x01ED53CD;
                    ((s8 *)0x01ED53CF)[temp_v1_6] = (s8) *(s8 *)0x01ED53C7;
                    ((s8 *)0x01ED53DB)[temp_v1_6] = (s8) *(s8 *)0x01ED53C5;
                    ((s8 *)0x01ED53E7)[temp_v1_6] = (s8) *(s8 *)0x01ED53C6;
                    *(s8 *)0x01ED53CB = 0;
                    *(s8 *)0x01ED53CA = 0;
                    *(s8 *)0x01ED53CE = (s8) *(s8 *)0x01ED53CD;
                    *(s8 *)0x01ED53CD = (s8) (*(s8 *)0x01ED53CD + 1);
                    if (*(s8 *)0x01ED53CD >= 0xC) {
                        *(s8 *)0x01ED53CD = 0xC;
                        *(s8 *)0x01ED53CE = 0xB;
                    }
                }
            }
            break;
        case 0x2742:                                /* switch 6 */
        case 0x276A:                                /* switch 6 */
            if (*(s8 *)0x01ED53A6 == 2) {
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
                        *(s8 *)0x01ED53A8 = 0;
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                }
                if (SzPad_Check(0, 0, 0x4000) != 0) {
                    if (var_s1 != 0) {
                        SzSound_PlaySE(0, 3);
                        *(s8 *)0x01ED53A8 = 1;
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                }
                if ((SzPad_Check(0, 1, 0x1000) == 0) && (SzPad_Check(0, 1, 0x4000) == 0) && (SzPad_Check(0, 0, 0x800) != 0)) {
                    *(s8 *)0x01ED53A6 = 3;
                    SzSound_PlaySE(0, 1);
                    if (((*(s16 *)(ctx + 0xC2)) == 0x2742) && (*(s8 *)0x01ED53A8 == 0)) {
                        Taku_Camp_Go_Rensyu_Duel(0);
                    }
                }
            }
            break;
        case 0x2756:                                /* switch 6 */
            if ((*(s8 *)0x01ED53A6 == 2) && (*(s8 *)0x01ED5494 == 1)) {
                if (*(s8 *)0x01ED53AA == 0) {
                    if (SzPad_Check(0, 0, 0x2000) != 0) {
                        SzSound_PlaySE(0, 9);
                        *(s8 *)0x01ED53AA = 1;
                    }
                    if (SzPad_Check(0, 0, 0x8000) != 0) {
                        SzSound_PlaySE(0, 9);
                        *(s8 *)0x01ED53AA = 2;
                    }
                }
                temp_v0_18 = *(s8 *)0x01ED53AA;
                if (temp_v0_18 != 0) {
                    switch ((s8) temp_v0_18) {
                    case 1:                         /* switch 8 */
                        *(s8 *)0x01ED53A9 = (s8) (*(s8 *)0x01ED53A9 + 0x14);
                        if (*(s8 *)0x01ED53A9 >= 0x64) {
                            *(s8 *)0x01ED53A9 = 0;
                            *(s8 *)0x01ED53AA = 0;
                            *(s8 *)0x01ED53A8 = (s8) (*(s8 *)0x01ED53A8 + 1);
                            if (*(s8 *)0x01ED53A8 > 2) {
                                *(s8 *)0x01ED53A8 = 0;
                            }
                        }
                        break;
                    case 2:                         /* switch 8 */
                        *(s8 *)0x01ED53A9 = (s8) (*(s8 *)0x01ED53A9 + 0x14);
                        if (*(s8 *)0x01ED53A9 >= 0x64) {
                            *(s8 *)0x01ED53A9 = 0;
                            *(s8 *)0x01ED53AA = 0;
                            *(s8 *)0x01ED53A8 = (s8) (*(s8 *)0x01ED53A8 - 1);
                            if (*(s8 *)0x01ED53A8 < 0) {
                                *(s8 *)0x01ED53A8 = 2;
                            }
                        }
                        break;
                    }
                }
                if ((SzPad_Check(0, 0, 0x800) != 0) && (*(s8 *)0x01ED53AA == 0)) {
                    SzSound_PlaySE(0, 1);
                    *(s8 *)0x01ED53A6 = 3;
                    *(s8 *)0x01ED5494 = 2;
                }
            }
            /* fallthrough */
        case 0x2757:                                /* switch 6 */
            /* fallthrough */
        case 0x2760:                                /* switch 6 */
            if (*(s8 *)0x01ED5494 == 4) {
                SzData_SetupFromConstDeck(0, (s32) ((u16 *)0x01ED53F8)[*(s8 *)0x01ED53A8]);
                if (SzModel_IsModelLoading(0x1E) == 0) {
                    spE0 = D_0029B000;
                    spF0 = D_0029B010;
                    temp_v0_19 = SzData_GetCurrentDeck(0);
                    temp_s1_2 = SzData_GetLeader(0, temp_v0_19);
                    *(s16 *)0x01ED5404 = SzData_GetLeader(0, temp_v0_19);
                    SzModel_SetPos(0x1E, &spE0);
                    SzModel_SetRot(0x1E, &spF0);
                    SzModel_Load(0x1E, -1, SzDuel_New2Xax(temp_s1_2), 1);
                }
                *(s8 *)0x01ED5494 = 5;
            }
            break;
        }
        if (*(s16 *)0x01ED007A != 0) {
            if (*(s16 *)0x01ED007C != 0) {
                spot = 3;
            } else {
                spot = 1;
            }
        } else {
            spot = 0;
            if (*(s16 *)0x01ED007C != 0) {
                spot = 2;
            }
        }
        temp_v1_7 = *(s8 *)0x01ED0072;
        if (temp_v1_7 == 1) {
            if (*(s16 *)0x01ED0074 == 0) {
                *(s16 *)0x01ED0076 = *(s16 *)0x01ED0000;
                *(s16 *)0x01ED0078 = *(s16 *)0x01ED0002;
            }
            *(s16 *)0x01ED0074 = (s16) (*(s16 *)0x01ED0074 + 0x20);
            if (*(s16 *)0x01ED0074 >= 0x100) {
                *(s16 *)0x01ED0074 = 0x100;
            }
            *(s16 *)0x01ED0000 = *(s16 *)0x01ED0076 + ((*(s16 *)0x01ED0074 * ((camp_sys_icon[spot * 0x13] + 0x10) - *(s16 *)0x01ED0076)) >> 8);
            *(s16 *)0x01ED0002 = *(s16 *)0x01ED0078 + ((*(s16 *)0x01ED0074 * ((camp_sys_icon[spot * 0x13 + 1] + 0x10) - *(s16 *)0x01ED0078)) >> 8);
        } else if (temp_v1_7 == 2) {
            *(s16 *)0x01ED0074 = (s16) (*(s16 *)0x01ED0074 - 0x20);
            if (*(s16 *)0x01ED0074 <= 0) {
                *(s16 *)0x01ED0074 = 0;
                *(s8 *)0x01ED0072 = 0;
                *(s16 *)0x01ED007A = 0;
                *(s16 *)0x01ED007C = 0;
            }
            *(s16 *)0x01ED0000 = *(s16 *)0x01ED0076 + ((*(s16 *)0x01ED0074 * ((camp_sys_icon[spot * 0x13] + 0x10) - *(s16 *)0x01ED0076)) >> 8);
            *(s16 *)0x01ED0002 = *(s16 *)0x01ED0078 + ((*(s16 *)0x01ED0074 * ((camp_sys_icon[spot * 0x13 + 1] + 0x10) - *(s16 *)0x01ED0078)) >> 8);
        }
        Taku_Camp_System();
        if (*(s8 *)0x01ED537B == 1) {
            Taku_Camp_BUN_HANTEI();
        }
        if ((*(s8 *)(ctx + 0)) == 1) {
            if (((*(s16 *)(ctx + 0xC2)) == 0x68) || ((*(s16 *)(ctx + 0xC2)) == 0x69)) {
                var_s3 = 1;
            }
        }
        if (((*(s8 *)(ctx + 0)) == 1) && ((*(s16 *)(ctx + 0xC2)) == 0x6F)) {
            if (*(s8 *)0x01ED537B == 1) {
                Taku_Camp_BUN_HANTEI();
            }
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
            }
            if (*(s8 *)0x01ED537B == 4) {
                if (SzPad_Check(0, 0, 0x40) != 0) {
                    SzSound_PlaySE(0, 2);
                    *(s8 *)0x01ED537B = (s8) (*(s8 *)0x01ED537B + 1);
                    Taku_Camp_BUN_HANTEI();
                }
            }
        } else if (((*(s16 *)(ctx + 0xC2)) >= 0x2711) || (var_s3 != 0)) {
            if (SzPad_Check(0, 0, 0x40) != 0) {
                if (*(s8 *)0x01ED537B == 4) {
                    *(s8 *)0x01ED537B = 5;
                    *(s8 *)0x01ED53B2 = 0;
                    SzSound_PlaySE(0, 2);
                }
                if (*(s8 *)0x01ED53AC == 2) {
                    *(s8 *)0x01ED53AC = 3;
                    *(s8 *)0x01ED53B2 = 0;
                    SzSound_PlaySE(0, 2);
                }
                Taku_Camp_BUN_HANTEI();
            }
        } else if (*(u16 *)0x01ED0004 == 2) {
            var_a0_4 = 0;
            if (*(s8 *)0x01ED547A == 0) {
                if ((*(s8 *)(ctx + 0)) != 0) {
                    if ((*(s8 *)(ctx + 0xC6)) == 0xF) {
                        var_a0_4 = 1;
                    }
                }
                if ((*(s16 *)0x01ED5442 <= *(s16 *)0x01ED5444) || (*(s8 *)0x01ED537B != 0) || (var_a0_4 != 0)) {
                    var_s1_2 = 0;
                    if (*(s8 *)0x01ED537B == 0xC) {
                        if (*(s8 *)0x01ED53A0 <= 0) {
                            if (*(s8 *)0x01ED018C == 0) {
                                temp_v0_20 = *(s8 *)0x01ED5440;
                                if (!(0 > temp_v0_20)) {
                                    *(s8 *)0x01ED5440 = (s8) (temp_v0_20 - 0xA);
                                    if (*(s8 *)0x01ED5440 <= 0) {
                                        *(s8 *)0x01ED5440 = 0;
                                    }
                                }
                            }
                        }
                    }
                    if ((*(s8 *)0x01ED5376 != 0) && (*(s8 *)0x01ED5482 == 0) && (SzEffect_IsUse2(-1, -1) == 0) && (*(s8 *)0x01ED5374 == 0) && (*(s8 *)0x01ED5375 == 0) && ((*(s16 *)(ctx + 0xC2)) < 0xC8)) {
                        var_s1_2 = 1;
                    }
                    if ((((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3] != 0) && (*(s16 *)0x01ED006C == 0x100)) {
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
                                    if ((*(s8 *)0x01ED546D == 0) && (*(s8 *)0x01ED537B == 0) && (var_s1_2 != 0)) {
                                        SzSound_PlaySE(0, 4);
                                        *(s8 *)0x01ED546D = 1;
                                        func_00199B50(&D_0030F213, (*(s8 *)(ctx + 0xC6)));
                                    }
                                    if (((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3] == 1) {
                                        if (*(s8 *)0x01ED537B == 0) {
                                            *(s8 *)0x01ED537B = 1;
                                            *(s8 *)0x01ED53A0 = 0;
                                            *(s8 *)0x01ED5375 = 1;
                                            if (*(s8 *)0x01ED5373 == 0) {
                                                if (var_s1_2 != 0) {
                                                    *(s8 *)0x01ED5373 = 1;
                                                }
                                            }
                                            *(s8 *)0x01ED537D = 1;
                                        }
                                        temp_v1_8 = *(s8 *)0x01ED537B;
                                        if (temp_v1_8 == 4) {
                                            *(s8 *)0x01ED537B = (s8) (temp_v1_8 + 1);
                                            SzSound_PlaySE(0, 2);
                                        }
                                        Taku_Camp_BUN_HANTEI();
                                    } else if ((*(s8 *)(ctx + 0xC6)) == 0xB) {
                                        if (((*(s8 *)(ctx + 0xE)) == 3) && (*(s8 *)0x01ED53C2 == 1)) {
                                            if (*(s8 *)0x01ED537B == 0) {
                                                *(s8 *)0x01ED537B = 1;
                                                *(s8 *)0x01ED53A0 = 0;
                                                *(s8 *)0x01ED5375 = 1;
                                                if (*(s8 *)0x01ED5373 == 0) {
                                                    if (var_s1_2 != 0) {
                                                        *(s8 *)0x01ED5373 = 1;
                                                    }
                                                }
                                                *(s8 *)0x01ED537D = 1;
                                            }
                                            temp_v1_9 = *(s8 *)0x01ED537B;
                                            if (temp_v1_9 == 4) {
                                                *(s8 *)0x01ED537B = (s8) (temp_v1_9 + 1);
                                                SzSound_PlaySE(0, 2);
                                            }
                                            Taku_Camp_BUN_HANTEI();
                                        } else {
                                            goto block_544;
                                        }
                                    } else {
block_544:
                                        *(s8 *)0x01ED5375 = 1;
                                        if (*(s8 *)0x01ED5373 == 0) {
                                            if (var_s1_2 != 0) {
                                                *(s8 *)0x01ED5373 = 1;
                                            }
                                        }
                                        temp_v1_10 = *(s8 *)0x01ED537B;
                                        if (temp_v1_10 == 4) {
                                            *(s8 *)0x01ED537B = (s8) (temp_v1_10 + 1);
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
                                    if (*(s8 *)0x01ED546D == 0) {
                                        if ((*(s8 *)0x01ED537B == 0) && (var_s1_2 != 0)) {
                                            SzSound_PlaySE(0, 4);
                                            *(s8 *)0x01ED546D = 1;
                                        }
                                    }
                                    if (*(s8 *)0x01ED537B == 0) {
                                        *(s8 *)0x01ED53A0 = 0;
                                        *(s8 *)0x01ED5375 = 1;
                                        if ((*(s8 *)0x01ED5373 == 0) && (var_s1_2 != 0)) {
                                            *(s8 *)0x01ED5373 = 1;
                                        }
                                    }
                                }
                                break;
                            case 17:
                                break;
                            default:
                                if (SzPad_Check(0, 0, 0x40) != 0) {
                                    if ((*(s8 *)0x01ED546D == 0) && (*(s8 *)0x01ED537B == 0) && (var_s1_2 != 0)) {
                                        SzSound_PlaySE(0, 4);
                                        *(s8 *)0x01ED546D = 1;
                                        func_00199B50(&D_0030F244, (*(s8 *)(ctx + 0xC6)));
                                    }
                                    if (((s8 *)((*(s8 *)(ctx + 0xC6)) + ctx))[3] == 1) {
                                        if (*(s8 *)0x01ED537B == 0) {
                                            *(s8 *)0x01ED537B = 1;
                                            *(s8 *)0x01ED537D = 1;
                                            *(s8 *)0x01ED53A0 = 0;
                                            *(s8 *)0x01ED5375 = 1;
                                            if ((*(s8 *)0x01ED5373 == 0) && (var_s1_2 != 0)) {
                                                *(s8 *)0x01ED5373 = 1;
                                            }
                                        }
                                        temp_v1_11 = *(s8 *)0x01ED537B;
                                        if (temp_v1_11 == 4) {
                                            *(s8 *)0x01ED537B = (s8) (temp_v1_11 + 1);
                                            SzSound_PlaySE(0, 2);
                                        }
                                        Taku_Camp_BUN_HANTEI();
                                    } else {
                                        *(s8 *)0x01ED5375 = 1;
                                        if (*(s8 *)0x01ED5373 == 0) {
                                            if (var_s1_2 != 0) {
                                                *(s8 *)0x01ED5373 = 1;
                                            }
                                        }
                                        temp_v1_12 = *(s8 *)0x01ED537B;
                                        if (temp_v1_12 == 4) {
                                            *(s8 *)0x01ED537B = (s8) (temp_v1_12 + 1);
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
                    if ((*(s16 *)0x01ED006C == 0x100) && (*(s8 *)0x01ED5376 != 0) && (*(s8 *)0x01ED5482 == 0) && (SzEffect_IsUse2(-1, -1) == 0) && (*(s8 *)0x01ED5374 == 0) && (*(s8 *)0x01ED5375 == 0) && ((*(s16 *)(ctx + 0xC2)) < 0xC8)) {
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
                                    *(s8 *)0x01ED5446 = 1;
                                }
                                break;
                            default:                /* switch 11 */
                                if (SzPad_Check(0, 1, 0x40) != 0) {
                                    if (SzPad_Check(0, 0, 0x40) != 0) {
                                        SzSound_PlaySE(0, 6);
                                    }
                                    *(s8 *)0x01ED5446 = 1;
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
                                    *(s8 *)0x01ED5446 = 1;
                                }
                                break;
                            default:                /* switch 12 */
                                if (SzPad_Check(0, 1, 0x40) != 0) {
                                    if (SzPad_Check(0, 0, 0x40) != 0) {
                                        SzSound_PlaySE(0, 6);
                                    }
                                    *(s8 *)0x01ED5446 = 1;
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
            *(s8 *)0x01ED5446 = 0;
        }
        temp_a1_7 = *(s8 *)0x01ED53B3;
        switch (temp_a1_7) {                        /* switch 13; irregular */
        case 1:                                     /* switch 13 */
            temp_v0_21 = *(s8 *)0x01ED0062;
            if (temp_v0_21 == 1) {
                *(s16 *)0x01ED0064 = (s16) (*(s16 *)0x01ED0064 + 0x10);
                if (*(s16 *)0x01ED0064 > 0x1000) {
                    *(s16 *)0x01ED0064 = 0x1000;
                    *(s8 *)0x01ED0062 = 0;
                }
            } else if (temp_v0_21 == 2) {
                *(s16 *)0x01ED0064 = (s16) (*(s16 *)0x01ED0064 - 0x10);
                if (*(s16 *)0x01ED0064 < 0) {
                    *(s16 *)0x01ED0064 = 0;
                    *(s8 *)0x01ED0062 = 0;
                }
            }
            *(f32 *)0x01ED0040 = 0.0f;
            *(f32 *)0x01ED0048 = 0.0f;
            *(s32 *)0x01ED004C = 0;
            *(f32 *)0x01ED0030 = (f32) *(f32 *)0x01ED0040;
            *(f32 *)0x01ED0034 = (f32) (20.0f + *(f32 *)0x01ED0044 + ((1700.0f * (f32) *(s16 *)0x01ED0064) / 4096.0f));
            *(f32 *)0x01ED0038 = (f32) (1.0f + *(f32 *)0x01ED0048);
            *(f32 *)0x01ED003C = *(f32 *)0x01ED004C;
            *(s16 *)0x01ED53F4 = (s16) (*(s16 *)0x01ED53F4 - 0x300);
            break;
        case 2:                                     /* switch 13 */
            temp_v1_13 = *(s8 *)0x01ED0062;
            if (temp_v1_13 == 1) {
                *(s16 *)0x01ED0064 = (s16) (*(s16 *)0x01ED0064 + 0x100);
                if (*(s16 *)0x01ED0064 > 0x1000) {
                    *(s16 *)0x01ED0064 = 0x1000;
                    *(s8 *)0x01ED0062 = 0;
                }
            } else if (temp_v1_13 == 2) {
                *(s16 *)0x01ED0064 = (s16) (*(s16 *)0x01ED0064 - 0x100);
                if (*(s16 *)0x01ED0064 < 0) {
                    *(s16 *)0x01ED0064 = 0;
                    *(s8 *)0x01ED0062 = 0;
                }
            }
            if (*(s8 *)0x01ED547F != 0) {
                *(f32 *)0x01ED548C = 0.0f;
                *(f32 *)0x01ED5490 = 0.0f;
                temp_a1_8 = *(s8 *)0x01ED547F;
                switch (temp_a1_8) {                /* switch 16; irregular */
                case 1:                             /* switch 16 */
                    *(s8 *)0x01ED5480 = (s8) (*(s8 *)0x01ED5480 + 5);
                    if (*(s8 *)0x01ED5480 >= 0x64) {
                        *(s8 *)0x01ED5480 = 0x64;
                        *(s8 *)0x01ED547F = 2;
                    }
                    break;
                case 2:                             /* switch 16 */
                    *(s8 *)0x01ED5480 = 0x64;
                    if (*(s8 *)0x01ED546E == 5) {
                        *(s8 *)0x01ED547F = 3;
                    }
                    break;
                case 3:                             /* switch 16 */
                    *(s8 *)0x01ED5480 = (s8) (*(s8 *)0x01ED5480 - 5);
                    if (*(s8 *)0x01ED5480 <= 0) {
                        *(s8 *)0x01ED5480 = 0;
                        *(s8 *)0x01ED547F = 4;
                    }
                    break;
                case 4:                             /* switch 16 */
                    *(u8 *)0x01ED547E = 0;
                    break;
                }
                temp_hi = (s32) *(u8 *)0x01ED547E % 3;
                switch (temp_hi) {                  /* switch 17; irregular */
                case 0:                             /* switch 17 */
                    *(f32 *)0x01ED548C = 0.0f;
                    break;
                case 1:                             /* switch 17 */
                    var_f0 = (-2.0f * (f32) *(s8 *)0x01ED5480) / 100.0f;
                    *(f32 *)0x01ED548C = var_f0;
                    break;
                case 2:                             /* switch 17 */
                    var_f0 = (2.0f * (f32) *(s8 *)0x01ED5480) / 100.0f;
                    *(f32 *)0x01ED548C = var_f0;
                    break;
                }
                temp_hi_2 = (s32) *(u8 *)0x01ED547E % 5;
                switch (temp_hi_2) {                /* switch 18; irregular */
                case 0:                             /* switch 18 */
                    *(f32 *)0x01ED5490 = 0.0f;
                    break;
                case 1:                             /* switch 18 */
                    var_f0_2 = (-2.0f * (f32) *(s8 *)0x01ED5480) / 100.0f;
                    *(f32 *)0x01ED5490 = var_f0_2;
                    break;
                case 2:                             /* switch 18 */
                    var_f0_2 = (2.0f * (f32) *(s8 *)0x01ED5480) / 100.0f;
                    *(f32 *)0x01ED5490 = var_f0_2;
                    break;
                case 3:                             /* switch 18 */
                    var_f0_2 = (-1.0f * (f32) *(s8 *)0x01ED5480) / 100.0f;
                    *(f32 *)0x01ED5490 = var_f0_2;
                    break;
                case 4:                             /* switch 18 */
                    var_f0_2 = (f32) *(s8 *)0x01ED5480 / 100.0f;
                    *(f32 *)0x01ED5490 = var_f0_2;
                    break;
                }
                *(f32 *)0x01ED0030 = (f32) *(f32 *)0x01ED548C;
                *(f32 *)0x01ED0034 = (f32) *(f32 *)0x01ED5490;
                *(f32 *)0x01ED0038 = 512.0f;
                *(s32 *)0x01ED003C = 0;
                *(f32 *)0x01ED0040 = (f32) (((-64.0f * (f32) *(s8 *)0x01ED5437) / 100.0f) + *(f32 *)0x01ED548C);
                *(f32 *)0x01ED0044 = (f32) (20.2f + ((768.0f * (f32) *(s16 *)0x01ED0064) / 4096.0f) + *(f32 *)0x01ED5490);
                *(f32 *)0x01ED0048 = 0.0f;
                *(s32 *)0x01ED004C = 0;
                *(u8 *)0x01ED547E = (u8) (*(u8 *)0x01ED547E + 1);
            } else {
                *(f32 *)0x01ED0030 = 0.0f;
                *(f32 *)0x01ED0034 = 0.0f;
                *(f32 *)0x01ED0038 = 512.0f;
                *(s32 *)0x01ED003C = 0;
                *(f32 *)0x01ED0040 = (f32) ((-64.0f * (f32) *(s8 *)0x01ED5437) / 100.0f);
                *(f32 *)0x01ED0044 = (f32) (20.2f + ((768.0f * (f32) *(s16 *)0x01ED0064) / 4096.0f));
                *(f32 *)0x01ED0048 = 0.0f;
                *(s32 *)0x01ED004C = 0;
            }
            break;
        case 3:                                     /* switch 13 */
            temp_v1_14 = *(s8 *)0x01ED0062;
            if (temp_v1_14 == 1) {
                *(s16 *)0x01ED0064 = (s16) (*(s16 *)0x01ED0064 + 0x80);
                if (*(s16 *)0x01ED0064 > 0x1000) {
                    *(s16 *)0x01ED0064 = 0x1000;
                    *(s8 *)0x01ED0062 = 0;
                }
            } else if (temp_v1_14 == 2) {
                *(s16 *)0x01ED0064 = (s16) (*(s16 *)0x01ED0064 - 0x80);
                if (*(s16 *)0x01ED0064 < 0) {
                    *(s16 *)0x01ED0064 = 0;
                    *(s8 *)0x01ED0062 = 0;
                }
            }
            temp_v0_22 = *(s8 *)0x01ED547F;
            if (temp_v0_22 != 0) {
                switch ((s8) temp_v0_22) {
                case 1:                             /* switch 20 */
                    *(s8 *)0x01ED5480 = (s8) (*(s8 *)0x01ED5480 + 5);
                    if (*(s8 *)0x01ED5480 >= 0x64) {
                        *(s8 *)0x01ED5480 = 0x64;
                        *(s8 *)0x01ED547F = 2;
                    }
                    break;
                case 2:                             /* switch 20 */
                    *(s8 *)0x01ED5480 = 0x64;
                    if (*(s8 *)0x01ED546E == 5) {
                        *(s8 *)0x01ED547F = 3;
                    }
                    break;
                case 3:                             /* switch 20 */
                    *(s8 *)0x01ED5480 = (s8) (*(s8 *)0x01ED5480 - 5);
                    if (*(s8 *)0x01ED5480 <= 0) {
                        *(s8 *)0x01ED5480 = 0;
                        *(s8 *)0x01ED547F = 4;
                    }
                    break;
                case 4:                             /* switch 20 */
                    *(u8 *)0x01ED547E = 0U;
                    break;
                }
                temp_hi_3 = (s32) *(u8 *)0x01ED547E % 3;
                switch (temp_hi_3) {                /* switch 21; irregular */
                case 0:                             /* switch 21 */
                    *(f32 *)0x01ED548C = 0.0f;
                    break;
                case 1:                             /* switch 21 */
                    var_f0_3 = (-2.0f * (f32) *(s8 *)0x01ED5480) / 100.0f;
                    *(f32 *)0x01ED548C = var_f0_3;
                    break;
                case 2:                             /* switch 21 */
                    var_f0_3 = (2.0f * (f32) *(s8 *)0x01ED5480) / 100.0f;
                    *(f32 *)0x01ED548C = var_f0_3;
                    break;
                }
                temp_hi_4 = (s32) *(u8 *)0x01ED547E % 5;
                switch (temp_hi_4) {                /* switch 22; irregular */
                case 0:                             /* switch 22 */
                    *(f32 *)0x01ED5490 = 0.0f;
                    break;
                case 1:                             /* switch 22 */
                    fq4 = (-2.0f * (f32) *(s8 *)0x01ED5480) / 100.0f;
                    *(f32 *)0x01ED5490 = fq4;
                    break;
                case 2:                             /* switch 22 */
                    fq4 = (2.0f * (f32) *(s8 *)0x01ED5480) / 100.0f;
                    *(f32 *)0x01ED5490 = fq4;
                    break;
                case 3:                             /* switch 22 */
                    fq4 = (-1.0f * (f32) *(s8 *)0x01ED5480) / 100.0f;
                    *(f32 *)0x01ED5490 = fq4;
                    break;
                case 4:                             /* switch 22 */
                    fq4 = (f32) *(s8 *)0x01ED5480 / 100.0f;
                    *(f32 *)0x01ED5490 = fq4;
                    break;
                }
                *(f32 *)0x01ED0030 = (f32) *(f32 *)0x01ED548C;
                *(f32 *)0x01ED0034 = (f32) *(f32 *)0x01ED5490;
                *(f32 *)0x01ED0038 = 512.0f;
                *(s32 *)0x01ED003C = 0;
                *(f32 *)0x01ED0040 = (f32) (((-64.0f * (f32) *(s8 *)0x01ED5437) / 100.0f) + *(f32 *)0x01ED548C);
                *(f32 *)0x01ED0044 = (f32) (20.2f + ((512.0f * (f32) *(s16 *)0x01ED0064) / 4096.0f) + *(f32 *)0x01ED5490);
                *(f32 *)0x01ED0048 = 0.0f;
                *(s32 *)0x01ED004C = 0;
                *(u8 *)0x01ED547E = (u8) (*(u8 *)0x01ED547E + 1);
            } else {
                *(f32 *)0x01ED0030 = 0.0f;
                *(f32 *)0x01ED0034 = 0.0f;
                *(f32 *)0x01ED0038 = 512.0f;
                *(s32 *)0x01ED003C = 0;
                *(f32 *)0x01ED0040 = (f32) ((-64.0f * (f32) *(s8 *)0x01ED5437) / 100.0f);
                *(f32 *)0x01ED0044 = (f32) (20.2f + ((512.0f * (f32) *(s16 *)0x01ED0064) / 4096.0f));
                *(f32 *)0x01ED0048 = 0.0f;
                *(s32 *)0x01ED004C = 0;
                *(u8 *)0x01ED547E = 0U;
            }
            break;
        default:                                    /* switch 13 */
            c23 = *(s8 *)0x01ED0062;
            if (c23 == 1) {
                *(s16 *)0x01ED0064 = (s16) (*(s16 *)0x01ED0064 + 8);
                if (*(s16 *)0x01ED0064 > 0x100) {
                    *(s16 *)0x01ED0064 = 0x100;
                    *(s8 *)0x01ED0062 = 0;
                }
            } else if (c23 == 2) {
                *(s16 *)0x01ED0064 = (s16) (*(s16 *)0x01ED0064 - 8);
                if (*(s16 *)0x01ED0064 < 0) {
                    *(s16 *)0x01ED0064 = 0;
                    *(s8 *)0x01ED0062 = 0;
                }
            }
            *(f32 *)0x01ED0044 = 0.0f;
            *(f32 *)0x01ED0030 = *(f32 *)0x01ED0040;
            *(f32 *)0x01ED0034 = 96.0f + *(f32 *)0x01ED0044 + ((96.0f * (f32) *(s16 *)0x01ED0064) / 256.0f);
            *(f32 *)0x01ED0038 = 96.0f + *(f32 *)0x01ED0048;
            *(f32 *)0x01ED003C = *(f32 *)0x01ED004C;
            break;
        }
        SzView_SetCamera(0, (void *)0x01ED0030, (void *)0x01ED0040);
        TkCamp_Act2(0);
end_TkCamp_Act:;
}
#pragma opt_dead_assignments reset
#pragma conditional_move reset
