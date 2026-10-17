#include "common.h"

typedef struct {
    u8 pad00[0x40];
    u8 x;
    u8 y;
    u8 alternateX;
    u8 alternateY;
    u8 pad44[0x13];
    s8 : 6;
    s8 alternate : 1;
    s8 : 1;
} Card_001F6F50;


/* Which battle animation the monster in the 3D battle plays against its opponent (SzDuel_GetPlayMotion). */
s32 SzEffect_GetPlayMotion(s32 flag) {
    s32 attackerSide;
    s32 attackerUnit;
    s32 defenderSide;
    s32 defenderUnit;
    s32 entry;
    Card_001F6F50 *card;
    u8 x;
    u8 y;

    entry = SzBattle_InqEntry(1);
    card = (Card_001F6F50 *)SzDuel_GetUnit(entry >> 8, entry & 0xFF);
    defenderSide = (s32) D_0031BE98 >> 8;
    defenderUnit = D_0031BE98 & 0xFF;
    attackerSide = (s32) D_0031BE9C >> 8;
    attackerUnit = D_0031BE9C & 0xFF;
    if (card == 0) {
        return -1;
    }
    if ((attackerSide < 0) || (attackerSide >= 3) || (attackerUnit < 0) || (attackerUnit >= 0xB) || (defenderSide < 0) || (defenderSide >= 3) || (defenderUnit < 0) || (defenderUnit >= 0xB)) {
        return -1;
    }
    x = card->alternate ? card->alternateX : card->x;
    y = card->alternate ? card->alternateY : card->y;
    return SzDuel_GetPlayMotion(attackerSide, attackerUnit, defenderSide, defenderUnit, x, y, flag);
}

/* Renders unit `id`'s model into a texture. */
s32 SzEffect_ModelShotTexture2(s32 id, s32 arg1, s32 arg2, s32 arg3) {
    return SzEffect_ModelShotTextureWithFunc2(id, arg1, arg2, arg3, 0, 0);
}

/* Renders the effect target's model into a texture with a draw callback. */
void SzEffect_ModelShotTextureWithFunc(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    SzEffect_ModelShotTextureWithFunc2(D_0031BE9C, arg0, arg1, arg2, arg3, arg4);
}

/* Renders unit `id`'s model into a texture with a draw callback. */
s32 SzEffect_ModelShotTextureWithFunc2(s32 id, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = id >> 8;
    lo = id & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(hi, lo);
    if (id < 0) {
        return 0;
    }
    SzModel_ShotTextureWithFunc(id, arg1, arg2, arg3, arg4, arg5);
    return 1;
}

/* Starts a motion blur on the effect target's model. */
void SzEffect_ReqMotionBlur(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    SzEffect_ReqMotionBlur2(D_0031BE9C, arg0, arg1, arg2, arg3, arg4);
}

/* Starts a motion blur trail on unit `id`'s model. */
s32 SzEffect_ReqMotionBlur2(s32 id, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    extern s32 SzModel_ReqMotionBlur();
    s32 hi;
    s32 lo;

    hi = id >> 8;
    lo = id & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(hi, lo);
    if (id < 0) {
        return 0;
    }
    return SzModel_ReqMotionBlur(id, arg1, arg2, arg3, arg4, arg5);
}

/* Pauses (`on`) or resumes the duel board's models while a 3D battle plays. */
void SzEffect_SetPauseFor3DBattle(s32 on) {
    SzEffect_SetModelPauseForType(4, on);
    SzEffect_SetModelPauseForType(5, on);
    SzEffect_SetModelPauseForType(2, on);
    SzEffect_SetModelPauseForType(3, on);
    SzView_PauseRequest(-1, -1, on);
}

/* Pauses (`on`) or resumes unit `id`'s model. */
s32 SzEffect_SetModelPause2(s32 id, s64 on) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = id >> 8;
    lo = id & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(hi, lo);
    if (id < 0) {
        return 0;
    }
    return SzModel_SetPauseFlag(id, on);
}

/* Pauses (`on`) or resumes every model of kind `type`. */
s32 SzEffect_SetModelPauseForType(s32 type, s32 on) {
    extern s32 SzModel_GetModelType(s32);
    extern s32 SzModel_SetPauseFlag(s32, s32);
    s32 i;

    i = 0;
    do {
        if (type < 0 || type == SzModel_GetModelType(i)) {
            SzModel_SetPauseFlag(i, on);
        }
        i += 1;
    } while (i < 0x54);
}

/* Advances the turn-to-stone effect of every model being petrified. */
void SzEffect_StoneProc(void) {
    s32 stoneRatio;
    s32 stoneRatio2;
    s32 i;
    s32 var_s0_2;
    s32 var_s1;
    s32 j;
    s32 var_v0;
    s32 var_v0_2;

    i = 0;
    do {
        var_s1 = i + 0x14;
        stoneRatio = SzModel_GetStoneRatio(var_s1);
        if ((stoneRatio >= 0) && (stoneRatio < 0xFF)) {
            var_v0 = stoneRatio + 1;
            var_v0 = var_v0 < 0xFF ? var_v0 : 0xFF;
            SzModel_SetStoneRatio(var_s1, var_v0 & 0xFF);
        }
        i += 1;
    } while (i < 0xA);
    j = 0;
    do {
        var_s0_2 = j + 0x1E;
        stoneRatio2 = SzModel_GetStoneRatio(var_s0_2);
        if ((stoneRatio2 >= 0) && (stoneRatio2 < 0xFF)) {
            var_v0_2 = stoneRatio2 + 1;
            var_v0_2 = var_v0_2 < 0xFF ? var_v0_2 : 0xFF;
            SzModel_SetStoneRatio(var_s0_2, var_v0_2 & 0xFF);
        }
        j += 1;
    } while (j < 2);
}

/* Starts the camera system (the one view). */
s32 SzView_Init(void) {
    return 1;
}

/* Creates view `view` (only view 0 exists). */
s32 SzView_Create(s32 view) {
    s32 state;

    if (view < 0 || view > 0) {
        return 0;
    }
    state = SzMem_Alloc(0x8C0);
    if (state == 0) {
        return 0;
    }
    views[view] = state;
    RhMem_FillMemory4((void *) state, 0, 0x230);
    lSzView_InitVars(view);
    return 1;
}

typedef __int128 DotrBlockWord128;
struct DotrBlockQuad {
    unsigned char unknown_bytes[4];
};
struct DotrBlockPair {
    float x, y;
};
struct DotrBlockVector4 {
    float x, y, z;
    float unknown_w;
};
struct DotrBlockTriple {
    struct DotrBlockVector4 unknown_00[3];
};
struct DotrBlockElement {
    struct DotrBlockTriple unknown_00[3];
};
union DotrBlockMatrix48 {
    DotrBlockWord128 unknown_quads[3];
    struct DotrBlockVector4 unknown_vectors[3];
};
struct DotrBlock {
    unsigned char unknown_000[0x30];
    unsigned char unknown_030[0x10];
    int unknown_040;
    float unknown_044;
    unsigned char unknown_048[0x18];
    struct DotrBlockElement unknown_060[10];
    union DotrBlockMatrix48 unknown_600[10];
    struct DotrBlockPair unknown_7e0[10];
    struct DotrBlockPair unknown_830[10];
    struct DotrBlockQuad unknown_880[10];
    unsigned short unknown_8a8;
    unsigned short unknown_8aa;
    unsigned short unknown_8ac;
    unsigned short unknown_8ae;
    int unknown_8b0;
    int unknown_8b4;
    unsigned char unknown_8b8[8];
};
typedef char DotrBlockMustBe8c0[(sizeof(struct DotrBlock) == 0x8c0) ? 1 : -1];
extern struct DotrBlock *D_0031BEB0_b[];
int func_001F9170_b(int index, int position, struct DotrBlockQuad *in);

/* Resets view `index` to its defaults: camera, look point, lights, fog, screen distance. */
int lSzView_InitVars(int index)
{
    struct DotrBlock *p;
    struct DotrBlockVector4 *v;
    float *f;
    struct DotrBlockElement *e;
    int *angles;
    struct DotrBlockPair *a;
    struct DotrBlockPair *b;
    int i;

    if (index < 0 || index >= 1) {
        return 0;
    }
    p = D_0031BEB0_b[index];
    if (p == 0) {
        return 0;
    }
    

    a = &p->unknown_7e0[9];
    b = &p->unknown_830[9];
    v = (struct DotrBlockVector4 *)&p->unknown_000[0x20];
    v->x = 0.0f;
    v->y = 50.0f;
    v->z = 300.0f;
    v->unknown_w = 1.0f;
    v = (struct DotrBlockVector4 *)p->unknown_030;
    v->x = 0.0f;
    v->y = 50.0f;
    v->z = 0.0f;
    v->unknown_w = 1.0f;
    p->unknown_040 = 0;
    p->unknown_044 = 800.0f;
    f = (float *)p->unknown_048;
    f[0] = 1.0f;
    f[1] = 0.94f;
    f[2] = 1.0f;
    f[3] = 4096.0f;
    e = &p->unknown_060[9];
    e->unknown_00[0].unknown_00[0].y = 0.5f;
    e->unknown_00[0].unknown_00[0].z = 0.5f;
    e->unknown_00[0].unknown_00[0].unknown_w = 0.5f;
    e->unknown_00[0].unknown_00[0].x = 1.0f;
    e->unknown_00[1].unknown_00[0].y = 0.0f;
    e->unknown_00[1].unknown_00[0].z = 0.0f;
    e->unknown_00[1].unknown_00[0].unknown_w = 0.0f;
    e->unknown_00[1].unknown_00[0].x = 1.0f;
    e->unknown_00[2].unknown_00[0].y = 0.0f;
    e->unknown_00[2].unknown_00[0].z = 0.0f;
    e->unknown_00[2].unknown_00[0].unknown_w = 0.0f;
    e->unknown_00[2].unknown_00[0].x = 1.0f;
    angles = (int *)&e->unknown_00[0].unknown_00[1];
    angles[0] = -14336;
    angles[1] = 2048;
    angles[2] = 0;
    angles[3] = 0;
    angles = (int *)&e->unknown_00[1].unknown_00[1];
    angles[0] = 0;
    angles[1] = 0;
    angles[2] = 0;
    angles[3] = 0;
    angles = (int *)&e->unknown_00[2].unknown_00[1];
    angles[0] = 0;
    angles[1] = 0;
    angles[2] = 0;
    angles[3] = 0;
    p->unknown_8a8 = 512;
    SzView_SetStraightLightDirection(0, 9, 0, 0);
    SzView_SetStraightLightDirection(0, 9, 1, 0);
    SzView_SetStraightLightDirection(0, 9, 2, 0);
    a->x = 2000.0f;
    a->y = 4000.0f;
    b->x = 2000.0f;
    b->y = 4000.0f;
    for (i = 0; i < 10; i++) {
        func_001F9170_b(index, i, 0);
    }
    lSzView_CalcRel(index);
    lSzView_CalcLook(index);
    return 1;
}

/* Frees view `view`. */
s32 SzView_Destroy(s32 view) {
    s32 *slot;

    if (view < 0 || view > 0) {
        return 0;
    }
    slot = &views[view];
    if (*slot == 0) {
        return 0;
    }
    SzMem_Free(*slot);
    *slot = 0;
    return 1;
}

typedef struct Light_001F7790 {
    s32 unk0;
    f32 rotation[3];
    s32 x;
    s32 y;
    u8 pad18[0x18];
} Light_001F7790;

typedef struct Color_001F7790 {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001F7790;

typedef struct Range_001F7790 {
    f32 near;
    f32 far;
} Range_001F7790;

typedef struct State_001F7790 {
    u8 pad0[0x44];
    f32 radius;
    u8 pad48[0x860];
    u16 lightFlags;
    u16 pad8AA;
    u16 fogFlags;
    u16 secondFlags;
    s32 mode;
} State_001F7790;

typedef struct Reset_001F7790 {
    __int128 value;
} Reset_001F7790;

extern Reset_001F7790 D_00293050;
extern s32 nCurLight;

#pragma conditional_move off

/* Runs view `view` for a frame: its camera requests (moves, turns, shakes), then its matrices. */
s32 SzView_Act(s32 view) {
    extern u32 SzPad_GetPressInfo();
    extern s32 SzModel_GetModelType();
    s32 activeMenu;
    s64 mode2;

    activeMenu = SzDebug_GetActiveMenu();
    mode2 = SzGame_GetMode(1);
    if (view < 0 || view > 0) {
        return 0;
    } else {
        State_001F7790 *temp_s0;
        s32 modelType;
        Light_001F7790 *temp_s2;
        Range_001F7790 *temp_s3;
        Range_001F7790 *temp_s4;
        Color_001F7790 *temp_s5;
        s32 spBC;
        s32 spC0;
        s32 spD0;
        s32 spE0;
        Reset_001F7790 spF0;
        f32 var_f20;
        f32 var_f21;
        f32 var_f22;
        s32 var_v0;
        s32 mode;

        temp_s0 = (State_001F7790 *) views[view];
        if (temp_s0 == 0) {
            return 0;
        }
        spBC = SzDebug_GetActiveModel();
        modelType = SzModel_GetModelType(spBC);
        spC0 = (temp_s0->lightFlags & (1 << modelType)) ? modelType : 9;
        spD0 = (temp_s0->fogFlags & (1 << modelType)) ? modelType : 9;
        spE0 = (temp_s0->secondFlags & (1 << modelType)) ? modelType : 9;
        var_v0 = 9;
        if (spD0 != 9 || spE0 != 9) {
            var_v0 = modelType;
        }
        temp_s5 = (Color_001F7790 *) ((u8 *) temp_s0 + var_v0 * 4 + 0x880);
        temp_s2 = (Light_001F7790 *) ((u8 *) temp_s0 + spC0 * 0x90 + 0x60);
        temp_s3 = (Range_001F7790 *) ((u8 *) temp_s0 + spD0 * 8 + 0x7E0);
        temp_s4 = (Range_001F7790 *) ((u8 *) temp_s0 + spE0 * 8 + 0x830);
        if (mode2 == 0 || mode2 == 5 || mode2 == 12) {
            if (activeMenu == 0xC) {
                if (SzPad_Check(0, 0, 0x4000) != 0) {
                    spF0 = D_00293050;
                    SzView_SetStraightLightDirection(0, spC0, nCurLight, &spF0);
                }
                if (SzPad_Check(0, 2, 0xA000) != 0) {
                    if (SzPad_Check(0, 2, 0x8000) != 0) {
                        nCurLight = (nCurLight + 2) % 3;
                    } else {
                        nCurLight = (nCurLight + 4) % 3;
                    }
                    }
                if (SzPad_Check(0, 2, 0x80) != 0) {
                    temp_s2[nCurLight].y -= 0x100;
                }
                if (SzPad_Check(0, 2, 0x20) != 0) {
                    temp_s2[nCurLight].y += 0x100;
                }
                if (SzPad_Check(0, 2, 0x40) != 0) {
                    temp_s2[nCurLight].x -= 0x100;
                }
                if (SzPad_Check(0, 2, 0x10) != 0) {
                    temp_s2[nCurLight].x += 0x100;
                }
                if (SzPad_Check(0, 2, 0xFFFF) != 0) {
                    SzView_SetStraightLightDirection(0, spC0, nCurLight, NULL);
                }
            }
            if (activeMenu == 0xD) {
                if (SzPad_Check(0, 0, 0x4000) != 0) {
                    SzView_SetStraightLightColor(view, spC0, nCurLight, NULL);
                }
                if (SzPad_Check(0, 2, 0xA000) != 0) {
                    if (SzPad_Check(0, 2, 0x8000) != 0) {
                        nCurLight = (nCurLight + 2) % 3;
                    } else {
                        nCurLight = (nCurLight + 4) % 3;
                    }
                    }
                if (SzPad_Check(0, 2, 0x81) != 0) {
                    temp_s2[nCurLight].rotation[0] -= 0.01f;
                }
                if (SzPad_Check(0, 2, 0x22) != 0) {
                    temp_s2[nCurLight].rotation[0] += 0.01f;
                }
                if (SzPad_Check(0, 2, 0x41) != 0) {
                    temp_s2[nCurLight].rotation[1] -= 0.01f;
                }
                if (SzPad_Check(0, 2, 0x12) != 0) {
                    temp_s2[nCurLight].rotation[1] += 0.01f;
                }
                if (SzPad_Check(0, 2, 5) != 0) {
                    temp_s2[nCurLight].rotation[2] -= 0.01f;
                }
                if (SzPad_Check(0, 2, 0xA) != 0) {
                    temp_s2[nCurLight].rotation[2] += 0.01f;
                }
            }
            if (activeMenu == 0xE) {
                if (SzPad_Check(0, 0, 0x4000) != 0) {
                    temp_s5->r = 0xFFU;
                    temp_s5->g = 0xFFU;
                    temp_s5->b = 0xFFU;
                }
                if (SzPad_Check(0, 2, 0x81) != 0) {
                    if (temp_s5->b > 0) {
                        temp_s5->b--;
                    }
                }
                if (SzPad_Check(0, 2, 0x22) != 0) {
                    if (temp_s5->b < 0xFF) {
                        temp_s5->b++;
                    }
                }
                if (SzPad_Check(0, 2, 0x41) != 0) {
                    if (temp_s5->g > 0) {
                        temp_s5->g--;
                    }
                }
                if (SzPad_Check(0, 2, 0x12) != 0) {
                    if (temp_s5->g < 0xFF) {
                        temp_s5->g++;
                    }
                }
                if (SzPad_Check(0, 2, 5) != 0) {
                    if (temp_s5->r > 0) {
                        temp_s5->r--;
                    }
                }
                if (SzPad_Check(0, 2, 0xA) != 0) {
                    if (temp_s5->r < 0xFF) {
                        temp_s5->r++;
                    }
                }
            }
            if (activeMenu == 0xF) {
                if (SzPad_Check(0, 0, 0x4000) != 0) {
                    temp_s3->near = 2000.0f;
                    temp_s3->far = 4000.0f;
                }
                if (SzPad_Check(0, 0, 0x8000) != 0) {
                    temp_s0->fogFlags &= ~(1 << spD0);
                }
                if (SzPad_Check(0, 0, 0x2000) != 0) {
                    temp_s0->fogFlags |= 1 << spD0;
                }
                if (SzPad_Check(0, 2, 0x80) != 0) {
                    temp_s3->near -= 10.0f;
                }
                if (SzPad_Check(0, 2, 0x20) != 0) {
                    temp_s3->near += 10.0f;
                }
                if (SzPad_Check(0, 2, 0x40) != 0) {
                    temp_s3->far -= 10.0f;
                }
                if (SzPad_Check(0, 2, 0x10) != 0) {
                    temp_s3->far += 10.0f;
                }
            }
            if (activeMenu == 0x10) {
                if (SzPad_Check(0, 0, 0x4000) != 0) {
                    temp_s4->near = 2000.0f;
                    temp_s4->far = 4000.0f;
                }
                if (SzPad_Check(0, 0, 0x8000) != 0) {
                    temp_s0->secondFlags &= ~(1 << spE0);
                }
                if (SzPad_Check(0, 0, 0x2000) != 0) {
                    temp_s0->secondFlags |= 1 << spE0;
                }
                if (SzPad_Check(0, 2, 0x80) != 0) {
                    temp_s4->near -= 10.0f;
                }
                if (SzPad_Check(0, 2, 0x20) != 0) {
                    temp_s4->near += 10.0f;
                }
                if (SzPad_Check(0, 2, 0x40) != 0) {
                    temp_s4->far -= 10.0f;
                }
                if (SzPad_Check(0, 2, 0x10) != 0) {
                    temp_s4->far += 10.0f;
                }
            }
            if (activeMenu == 0x11) {
                if (SzPad_Check(0, 2, 0xC) != 0) {
                    mode = SzView_GetMode(0);
                    if (SzPad_Check(0, 2, 4) != 0) {
                        SzView_SetMode(0, (s32) (mode + 2) % 3);
                    } else {
                        SzView_SetMode(0, (s32) (mode + 4) % 3);
                    }
                }
                if (SzPad_Check(0, 2, 0x4000) != 0) {
                    temp_s0->radius = 800.0f;
                }
                if (SzPad_Check(0, 2, 0x80) != 0) {
                    temp_s0->radius -= 10.0f;
                    if (temp_s0->radius < 10.0f) {
                        temp_s0->radius = 10.0f;
                    }
                }
                if (SzPad_Check(0, 2, 0x20) != 0) {
                    temp_s0->radius += 10.0f;
                    if (!(temp_s0->radius <= 10000.0f)) {
                        temp_s0->radius = 10000.0f;
                    }
                }
            }
        }
        var_f20 = 0.0f;
        var_f21 = 0.0f;
        var_f22 = 0.0f;
        if (SzView_InqRequest(-1, -1) == NULL) {
            if ((u32) (modelType - 4) < 2U) {
                SzView_SetViewCamera(view, spBC, NULL, temp_s0->mode, 1.0f);
            }
        }
        if (SzPad_IsPress(1) != 0) {
            var_f20 += (0.024543693f * (f32) SzPad_GetPressInfo(1, 1)) / 64.0f;
            var_f20 -= (0.024543693f * (f32) SzPad_GetPressInfo(1, 0)) / 64.0f;
            var_f21 += (0.024543693f * (f32) SzPad_GetPressInfo(1, 2)) / 64.0f;
            var_f21 -= (0.024543693f * (f32) SzPad_GetPressInfo(1, 3)) / 64.0f;
            var_f22 += (2.0f * (f32) SzPad_GetPressInfo(1, 8)) / 64.0f;
            var_f22 -= (2.0f * (f32) SzPad_GetPressInfo(1, 9)) / 64.0f;
            SzView_RollCamera(view, 0, 1, var_f20, var_f21, var_f22);
            var_f22 = 0.0f;
            var_f21 = 0.0f;
            var_f20 = 0.0f;
            var_f20 -= (0.024543693f * (f32) SzPad_GetPressInfo(1, 7)) / 64.0f;
            var_f20 += (0.024543693f * (f32) SzPad_GetPressInfo(1, 5)) / 64.0f;
            var_f21 -= (0.024543693f * (f32) SzPad_GetPressInfo(1, 4)) / 64.0f;
            var_f21 += (0.024543693f * (f32) SzPad_GetPressInfo(1, 6)) / 64.0f;
            var_f22 -= (2.0f * (f32) SzPad_GetPressInfo(1, 0xA)) / 64.0f;
            var_f22 += (2.0f * (f32) SzPad_GetPressInfo(1, 0xB)) / 64.0f;
            SzView_RollCamera(view, 0, -1, var_f20, var_f21, var_f22);
        } else {
            if (SzPad_Check(1, 1, 0x8000) != 0) {
                var_f20 += 0.024543693f;
            }
            if (SzPad_Check(1, 1, 0x2000) != 0) {
                var_f20 -= 0.024543693f;
            }
            if (SzPad_Check(1, 1, 0x1000) != 0) {
                var_f21 += 0.024543693f;
            }
            if (SzPad_Check(1, 1, 0x4000) != 0) {
                var_f21 -= 0.024543693f;
            }
            if (SzPad_Check(1, 1, 4) != 0) {
                var_f22 += 2.0f;
            }
            if (SzPad_Check(1, 1, 8) != 0) {
                var_f22 -= 2.0f;
            }
            SzView_RollCamera(view, 0, 1, var_f20, var_f21, var_f22);
            var_f22 = 0.0f;
            var_f21 = 0.0f;
            var_f20 = 0.0f;
            if (SzPad_Check(1, 1, 0x80) != 0) {
                var_f20 -= 0.024543693f;
            }
            if (SzPad_Check(1, 1, 0x20) != 0) {
                var_f20 += 0.024543693f;
            }
            if (SzPad_Check(1, 1, 0x10) != 0) {
                var_f21 -= 0.024543693f;
            }
            if (SzPad_Check(1, 1, 0x40) != 0) {
                var_f21 += 0.024543693f;
            }
            if (SzPad_Check(1, 1, 1) != 0) {
                var_f22 -= 2.0f;
            }
            if (SzPad_Check(1, 1, 2) != 0) {
                var_f22 += 2.0f;
            }
            SzView_RollCamera(view, 0, -1, var_f20, var_f21, var_f22);
        }
        if ((mode2 == 0) || (mode2 == 5) || (mode2 == 0xC)) {
            SzDebug_IsHide();
        }
        SzDebug_IsHide();
        return 1;
    }
}
#pragma conditional_move reset

typedef struct Vec4_001F8A30 {
    f32 x, y, z, w;
} Vec4_001F8A30;

typedef struct Object_001F8A30 {
    u8 pad00[0x10];
    Vec4_001F8A30 vector10;
    Vec4_001F8A30 vector20;
    u8 pad30[0x10];
    s32 flags40;
    f32 value44;
    f32 value48;
    f32 value4C;
    f32 value50;
    f32 value54;
    u8 pad58[0x7D0];
    f32 value828;
    f32 value82C;
    u8 pad830[0x48];
    f32 value878;
    f32 value87C;
    u8 pad880[0x24];
    f32 matrix8A4[16];
} Object_001F8A30;

typedef struct Render_001F8A30 {
    f32 matrix[16];
    Vec4_001F8A30 vector40;
    Vec4_001F8A30 vector50;
    u8 pad60[0x20];
    s32 flags80;
} Render_001F8A30;


/* Sends view `view`'s matrices and screen settings to the renderer. */
s32 SzView_Set_Pipe(s32 packet, s32 view) {
    Render_001F8A30 render;
    Object_001F8A30 *object;

    if ((view < 0) || (view > 0)) {
        return packet;
    }
    object = (Object_001F8A30 *)views[view];
    if (object == 0) {
        return packet;
    }
    RhView_SetScreen(object->value44, 640.0f, 448.0f, 320.0f, 224.0f);
    RhView_SetAspect(object->value48, object->value4C);
    RhView_SetClipZ(object->value50, object->value54);
    Ex3d_InitClipPlane();
    RhView_SetFogParameter(object->matrix8A4, object->value828, object->value82C,
                 object->value878, object->value87C);
    render.vector40 = object->vector20;
    render.vector50 = object->vector10;
    render.flags80 = object->flags40;
    RhView_Set(&render);
    return RhView_SendViewParameters(packet);
}

typedef struct {
    u8 c[4];
} Color_001F8B50;

typedef struct {
    u8 pad0[0x7E0];
    f32 posA[10][2];   /* 0x7E0 */
    f32 posB[10][2];   /* 0x830 */
    Color_001F8B50 color[10]; /* 0x880 */
    u8 pad8A8[4];
    u16 maskA;         /* 0x8AC */
    u16 maskB;         /* 0x8AE */
} Object_001F8B50;

/* Sends the fog of setting set `set` of view `view` for depth `depth`. */
void *SzView_SetFog_Pipe(void *packet, s32 view, s32 set, f32 depth) {
    Object_001F8B50 *obj;
    Color_001F8B50 color;
    f32 *posA;
    f32 *posB;
    u32 idxA;
    u32 idxB;
    s32 scale;

    if ((view < 0) || (view > 0)) {
        return packet;
    }
    obj = (Object_001F8B50 *) views[view];
    if (obj == NULL) {
        return packet;
    }
    if ((set < 0) || (set >= 10)) {
        return packet;
    }
    posA = obj->posA[set];
    posB = obj->posB[set];
    idxB = set;
    idxA = set;
    if (set != 9) {
        if (!(obj->maskA & (1 << idxA))) {
            posA = obj->posA[9];
            idxA = 9;
        }
        if (!(obj->maskB & (1 << set))) {
            posB = obj->posB[9];
            idxB = 9;
        }
        if (idxA == 9 && idxB == 9) {
            set = 9;
        }
    }
    if ((obj->maskA & (1 << idxA)) || (obj->maskB & (1 << idxB))) {
        color = obj->color[set];
        scale = (u32)(128.0f * depth) & 0xFF;
        color.c[2] = (color.c[2] * scale) >> 7;
        color.c[1] = (color.c[1] * scale) >> 7;
        color.c[0] = (color.c[0] * scale) >> 7;
        packet = RhBase_SetFogColor(packet, &color);
        packet = RhVu1Mac_SetFogParameterEx(packet, posA[0], posA[1], posB[0], posB[1]);
    }
    return packet;
}

/* Sends the lights of setting set `set` (0..9; 9 is the default) of view `view`: its directional and point lights. */
s32 SzView_SetLight_Pipe(s32 packet, s32 view, s32 set) {
    u32 sp70[4];
    u8 *straight;
    u8 *point;
    s32 straightSet;
    s32 pointSet;
    u8 *state;

    if ((view < 0) || (view > 0)) {
        return packet;
    }
    state = (u8 *)views[view];
    if (state == NULL) {
        return packet;
    }
    if ((set < 0) || (set >= 0xA)) {
        return packet;
    }
    straight = state + (set * 0x90) + 0x60;
    point = state + (set * 0x30) + 0x600;
    pointSet = set;
    straightSet = set;
    if (set != 9) {
        if (!(*(u16 *)(state + 0x8A8) & (1 << set))) {
            straight = state + 0x570;
            straightSet = 9;
        }
        if (!(*(u16 *)(state + 0x8AA) & (1 << set)) ||
            (*(u16 *)(state + 0x8AE) & (1 << set))) {
            point = state + 0x7B0;
            pointSet = 9;
        }
    }
    RhVu1Mac_SetStraightLightToVu1_Ex(0, NULL, NULL, -1);
    if (*(u16 *)(state + 0x8A8) & (1 << straightSet)) {
        *(s32 *)(straight + 0x2C) = 0;
        RhGeom_MulMatrixVector(sp70, NULL, straight + 0x20);
        RhVu1Mac_SetStraightLightToVu1_Ex(0, straight, sp70, 0);
        *(s32 *)(straight + 0x5C) = 0;
        RhGeom_MulMatrixVector(sp70, NULL, straight + 0x50);
        RhVu1Mac_SetStraightLightToVu1_Ex(0, straight + 0x30, sp70, 1);
        *(s32 *)(straight + 0x8C) = 0;
        RhGeom_MulMatrixVector(sp70, NULL, straight + 0x80);
        RhVu1Mac_SetStraightLightToVu1_Ex(0, straight + 0x60, sp70, 2);
    }
    packet = RhVu1Mac_SetStraightLightToVu1_Ex(packet, NULL, NULL, -1);
    if (*(u16 *)(state + 0x8AA) & (1 << pointSet)) {
        RhGeom_MulMatrixVector(sp70, NULL, point + 0x10);
        sp70[3] = 0x3F800000;
        return RhVu1Mac_SetPointLightToVu1(packet, point, sp70,
                             *(f32 *)(point + 0x20),
                             *(f32 *)(point + 0x24),
                             *(f32 *)(point + 0x28));
    }
    {
        f32 zero = 0.0f;
        return RhVu1Mac_SetPointLightToVu1(packet, NULL, NULL, zero, zero, zero);
    }
}

typedef struct Vec4_001F8F80 {
    f32 x, y, z, w;
} Vec4_001F8F80;

typedef struct Camera_001F8F80 {
    Vec4_001F8F80 result;
    u8 pad10[0x10];
    Vec4_001F8F80 position;
    Vec4_001F8F80 target;
} Camera_001F8F80;


/* Works out view `view`'s look matrix from its camera and look point. */
s32 lSzView_CalcLook(s32 view) {
    Vec4_001F8F80 result;
    Camera_001F8F80 *camera;
    Vec4_001F8F80 *position;
    Vec4_001F8F80 *target;

    if ((view < 0) || (view > 0)) {
        return 0;
    }
    camera = (Camera_001F8F80 *) views[view];
    if (camera == 0) {
        return 0;
    }
    position = &camera->position;
    target = &camera->target;
    result.x = func_001A6C60(
        (position->x - target->x) * (position->x - target->x) +
        (position->z - target->z) * (position->z - target->z));
    result.y = func_001A6C18(position->z - target->z, position->x - target->x);
    result.y = func_001A6C30(6.2831855f + result.y, 6.2831855f);
    result.z = func_001A6C18(position->y - target->y, result.x);
    result.x = func_001A6C60(
        (position->x - target->x) * (position->x - target->x) +
        (position->y - target->y) * (position->y - target->y) +
        (position->z - target->z) * (position->z - target->z));
    camera->result = result;
    return 1;
}

typedef struct {
    u8 pad[0x10];
    f32 direction[4];
    f32 origin[4];
    f32 target[4];
} Direction_001F90E0;

/* Works out view `view`'s camera from its relative (orbit) position. */
s32 lSzView_CalcRel(s32 view) {
    Direction_001F90E0 *entry;

    if ((view < 0) || (view > 0)) {
        return 0;
    }
    entry = (Direction_001F90E0 *)views[view];
    if (entry == 0) {
        return 0;
    }
    entry->direction[0] = entry->target[0] - entry->origin[0];
    entry->direction[1] = entry->target[1] - entry->origin[1];
    entry->direction[2] = entry->target[2] - entry->origin[2];
    entry->direction[3] = 0.0f;
    RhGeom_NormalizeVector(entry->direction);
    return 1;
}

typedef struct Color_001F9170 {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001F9170;

typedef struct Palette_001F9170 {
    u8 padding[0x880];
    Color_001F9170 colors[10];
} Palette_001F9170;

/* Sets the fog colour of setting set `set` (0..9) of view `view`; 0 resets it, 1 keeps the colour and turns it on. */
s32 SzView_SetFogColor(s32 view, s32 set, s32 color) {
    Palette_001F9170 *palette;

    if (view < 0 || view > 0) {
        return 0;
    }
    palette = (Palette_001F9170 *)views[view];
    if (palette == 0) {
        return 0;
    }
    if (set < 0 || set >= 10) {
        return 0;
    }
    if (color != 0) {
        palette->colors[set] = *(Color_001F9170 *)color;
    } else {
        palette->colors[set].r = 0xFF;
        palette->colors[set].g = 0xFF;
        palette->colors[set].b = 0xFF;
    }
    return 1;
}

typedef struct Bounds_001F9230 {
    f32 min;
    f32 max;
} Bounds_001F9230;

typedef struct State_001F9230 {
    u8 pad[0x7E0];
    Bounds_001F9230 bounds[10];
    u8 pad830[0x7C];
    u16 flags;
} State_001F9230;

/* Sets the depth fog range of setting set `set` of view `view`; 0 resets it (2000..4000), 1 keeps it and turns it
   on. */
s32 SzView_SetFogParamZ(s32 view, s32 set, s32 range) {
    State_001F9230 *state;

    if (view < 0 || view > 0) {
        return 0;
    }
    state = (State_001F9230 *)views[view];
    if (state == 0) {
        return 0;
    }
    if (set < 0 || set >= 10) {
        return 0;
    }
    if (range != 0) {
        if (range != 1) {
            state->bounds[set] = *(Bounds_001F9230 *)range;
        }
        state->flags |= 1 << set;
    } else {
        state->bounds[set].min = 2000.0f;
        state->bounds[set].max = 4000.0f;
        state->flags &= ~(1 << set);
    }
    return 1;
}

typedef struct Pair_001F9310 {
    f32 x;
    f32 y;
} Pair_001F9310;

typedef struct Object_001F9310 {
    u8 pad0[0x830];
    Pair_001F9310 pairs[10];
    u8 pad1[0x2E];
    u16 flags;
} Object_001F9310;

/* Sets the height fog range of setting set `set` of view `view`; 0 resets it, 1 keeps it and turns it on. */
s32 SzView_SetFogParamY(s32 view, s32 set, s32 range) {
    Object_001F9310 *object;

    if (view < 0 || view > 0) {
        return 0;
    }
    object = (Object_001F9310 *)views[view];
    if (object == 0) {
        return 0;
    }
    if (set < 0 || set >= 10) {
        return 0;
    }
    if (range != 0) {
        if (range != 1) {
            object->pairs[set] = *(Pair_001F9310 *)range;
        }
        object->flags |= 1 << set;
    } else {
        object->pairs[set].x = 2000.0f;
        object->pairs[set].y = 4000.0f;
        object->flags &= ~(1 << set);
    }
    return 1;
}

typedef struct Vec4_001F93F0 {
    f32 x, y, z, w;
} Vec4_001F93F0;

/* Sets the colour of directional light `light` (0..2) of setting set `set` of view `view`. */
s32 SzView_SetStraightLightColor(s32 view, s32 set, s32 light, void *color) {
    u8 *base;
    s32 row;
    s32 offset;
    f32 value;
    Vec4_001F93F0 *dst;

    if (view < 0 || view > 0) {
        return 0;
    }
    base = (u8 *)views[view];
    if (base == NULL) {
        return 0;
    }
    if (set < 0 || set >= 10) {
        return 0;
    }
    if (light < 0 || light >= 3) {
        return 0;
    }
    row = (s32)base + set * 0x90 + 0x60;
    if (color != NULL) {
        dst = (Vec4_001F93F0 *)(row + light * 0x30);
        *dst = *(Vec4_001F93F0 *)color;
    } else {
        offset = light * 0x30;
        if (light > 0) {
            value = 0.0f;
        } else {
            value = 0.5f;
        }
        dst = (Vec4_001F93F0 *)(offset + row);
        dst->w = value;
        dst->z = value;
        dst->y = value;
    }
    return 1;
}

typedef struct Vec4_001F9500 {
    f32 x, y, z, w;
} Vec4_001F9500;

typedef struct Entry_001F9500 {
    u8 padding[0x20];
    Vec4_001F9500 value;
} Entry_001F9500;

/* The direction of directional light `light` of setting set `set` of view `view` into `out`. */
s32 SzView_GetStraightLightVector(s32 view, s32 set, s32 light, void *out) {
    u8 *base;
    Entry_001F9500 *entries;

    if (view < 0 || view > 0) {
        return 0;
    }
    base = (u8 *)views[view];
    if (base == NULL) {
        return 0;
    }
    if (set < 0 || set >= 10) {
        return 0;
    }
    if (light < 0 || light >= 3) {
        return 0;
    }
    entries = (Entry_001F9500 *)(base + set * 0x90 + 0x60);
    if (out != NULL) {
        *(Vec4_001F9500 *)out = entries[light].value;
    }
    return 1;
}

typedef struct {
    f32 x, y, z, w;
} Vec4_001F95E0;

typedef struct {
    u8 pad[0x10];
    Vec4_001F95E0 rotation;
    Vec4_001F95E0 result;
} Entry_001F95E0;

extern f32 identityMatrix[4][4]; /* original: gSzView_vecUnit */

/* Sets the direction of directional light `light` of setting set `set` of view `view`. */
s32 SzView_SetStraightLightDirection(s32 view, s32 set, s32 light, void *dir) {
    f32 matrix[4][4];
    Entry_001F95E0 *entry;
    u8 *base;
    Entry_001F95E0 *row;

    if ((view < 0) || (view > 0)) {
        return 0;
    }
    base = (u8 *)views[view];
    if (base == NULL) {
        return 0;
    }
    if ((set < 0) || (set >= 10)) {
        return 0;
    }
    if ((light < 0) || (light >= 3)) {
        return 0;
    }
    row = (Entry_001F95E0 *)(base + set * 0x90 + 0x60);
    if (dir != NULL) {
        row[light].rotation = *(Vec4_001F95E0 *)dir;
    }
    entry = &row[light];
    RhGeom_GetRotXYZMatrix(matrix, &entry->rotation);
    RhGeom_MulMatrixVector(&entry->result, matrix, identityMatrix);
    return 1;
}

/* Whether setting set `set` of view `view` has its own directional lights. */
s32 SzView_InqStraightLight(s32 view, s32 set) {
    u8 *data;

    if (view < 0 || view > 0) {
        return 0;
    }
    data = (u8 *)views[view];
    if (data == NULL) {
        return 0;
    }
    if (set < 0 || set >= 10) {
        return 0;
    }
    return (*(u16 *)(data + 0x8A8) & (1 << set)) ? 1 : 0;
}

typedef struct {
    __int128 data[9];
} Block_001F9770;

/* Sets the three directional lights of setting set `set` of view `view` from `values`; 0 turns them off, 1 keeps
   them and turns them on. */
s32 SzView_SetStraightLight(s32 view, s32 set, s32 values) {
    s32 offset;
    u8 *state;
    u8 *slot;

    if ((view < 0) || (view > 0)) {
        return 0;
    }
    state = (u8 *)views[view];
    if (state == NULL) {
        return 0;
    }
    if ((set < 0) || (set >= 10)) {
        return 0;
    }
    if (values != 0) {
        if (values != 1) {
            offset = set * 0x90;
            *(Block_001F9770 *)(offset + (s32)state + 0x60) = *(Block_001F9770 *)values;
            slot = state + offset;
            SzView_SetStraightLightDirection(view, set, 0, slot + 0x70);
            SzView_SetStraightLightDirection(view, set, 1, slot + 0xA0);
            SzView_SetStraightLightDirection(view, set, 2, slot + 0xD0);
        }
        *(u16 *)(state + 0x8A8) |= 1 << set;
    } else {
        *(u16 *)(state + 0x8A8) &= ~(1 << set);
    }
    return 1;
}

/* Whether setting set `set` of view `view` has its own point light. */
s32 SzView_InqPointLight(s32 view, s32 set) {
    s32 state;

    if (view < 0 || view > 0) {
        return 0;
    }
    state = views[view];
    if (state == 0) {
        return 0;
    }
    if (set < 0 || set >= 0xA) {
        return 0;
    }
    return (*(u16 *)((u8 *)state + 0x8AA) & (1 << set)) ? 1 : 0;
}

typedef struct {
    __int128 rows[3];
} Matrix_001F9940;

typedef struct {
    u8 pad[0x600];
    Matrix_001F9940 matrices[10];
    u8 pad_7E0[0xCA];
    u16 flags;
} Object_001F9940;

/* Sets the point light of setting set `set` of view `view` from `values`; 0 turns it off, 1 keeps it and turns it
   on. */
s32 SzView_SetPointLight(s32 view, s32 set, s32 values) {
    Object_001F9940 *object;

    if (view < 0 || view > 0) {
        return 0;
    }
    object = (Object_001F9940 *)views[view];
    if (object == 0) {
        return 0;
    }
    if (set < 0 || set >= 10) {
        return 0;
    }
    if (values != 0) {
        if (values != 1) {
            object->matrices[set] = *(Matrix_001F9940 *)values;
            *(f32 *)((u8 *)&object->matrices[set] + 0x1C) = 1.0f;
        }
        object->flags |= 1 << set;
    } else {
        object->flags &= ~(1 << set);
    }
    return 1;
}

/* View `view`'s screen distance (the lens). */
f32 SzView_GetScreenDistance(s32 view) {
    s32 state;

    if ((view < 0) || (view > 0)) {
        return 0.0f;
    }
    state = views[view];
    if (state == 0) {
        return 0.0f;
    }
    return *(f32 *)((u8 *)state + 0x44);
}

typedef struct Object_001F9A80 {
    u8 pad[0x44];
    f32 value;
} Object_001F9A80;

/* Sets view `view`'s screen distance (the lens). */
s32 SzView_SetScreenDistance(s32 view, f32 fparg0) {
    Object_001F9A80 *object;

    if (view < 0 || view > 0) {
        return 0;
    }
    object = (Object_001F9A80 *)views[view];
    if (object == NULL) {
        return 0;
    }
    object->value = fparg0;
    return 1;
}

/* View `view`'s camera position in spherical form (distance, heading, pitch). */
s32 SzView_GetSP(s32 view) {
    s32 state;

    if (view < 0 || view > 0) {
        return 0;
    }
    state = views[view];
    if (state == 0) {
        return 0;
    }
    return state + 0x20;
}

typedef struct Vec4_001F9B20 {
    f32 x, y, z, w;
} Vec4_001F9B20;

typedef struct Camera_001F9B20 {
    Vec4_001F9B20 result;
    Vec4_001F9B20 direction;
    Vec4_001F9B20 position;
    Vec4_001F9B20 target;
} Camera_001F9B20;

extern Vec4_001F9B20 defaultCameraSpherical; /* original: gSzView_pntSPDef */


/* Works out a view's look direction. */
static inline s32 direction_001F9B20(s32 arg0) {
    Camera_001F9B20 *camera;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0;
    }
    camera = (Camera_001F9B20 *)views[arg0];
    if (camera == 0) {
        return 0;
    }
    camera->direction.x = camera->target.x - camera->position.x;
    camera->direction.y = camera->target.y - camera->position.y;
    camera->direction.z = camera->target.z - camera->position.z;
    camera->direction.w = 0.0f;
    RhGeom_NormalizeVector(&camera->direction.x);
    return 1;
}

/* Works out a view's spherical position. */
static inline s32 polar_001F9B20(s32 arg0) {
    Vec4_001F9B20 result;
    Camera_001F9B20 *camera;
    Vec4_001F9B20 *position;
    Vec4_001F9B20 *target;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0;
    }
    camera = (Camera_001F9B20 *)views[arg0];
    if (camera == 0) {
        return 0;
    }
    position = &camera->position;
    target = &camera->target;
    result.x = func_001A6C60(
        (position->x - target->x) * (position->x - target->x) +
        (position->z - target->z) * (position->z - target->z));
    result.y = func_001A6C18(position->z - target->z, position->x - target->x);
    result.y = func_001A6C30(6.2831855f + result.y, 6.2831855f);
    result.z = func_001A6C18(position->y - target->y, result.x);
    result.x = func_001A6C60(
        (position->x - target->x) * (position->x - target->x) +
        (position->y - target->y) * (position->y - target->y) +
        (position->z - target->z) * (position->z - target->z));
    camera->result = result;
    return 1;
}

/* Sets view `view`'s camera position in spherical form (distance, heading, pitch). */
s32 SzView_SetSP(s32 view, void *src) {
    Vec4_001F9B20 *position = src;
    Camera_001F9B20 *camera;

    if ((view < 0) || (view > 0)) {
        return 0;
    }
    camera = (Camera_001F9B20 *)views[view];
    if (camera == 0) {
        return 0;
    }
    if (position == NULL) {
        position = &defaultCameraSpherical;
    }
    camera->position = *position;
    direction_001F9B20(view);
    polar_001F9B20(view);
    return 1;
}

/* View `view`'s camera position. */
s32 SzView_GetCP(s32 view) {
    s32 data;

    if (view < 0 || view >= 1) {
        return 0;
    }
    data = views[view];
    if (data == 0) {
        return 0;
    }
    return data + 0x30;
}

typedef struct Vec4_001F9D80 {
    f32 x, y, z, w;
} Vec4_001F9D80;

typedef struct Camera_001F9D80 {
    Vec4_001F9D80 result;
    Vec4_001F9D80 direction;
    Vec4_001F9D80 position;
    Vec4_001F9D80 target;
} Camera_001F9D80;

extern Vec4_001F9D80 defaultCameraPos; /* original: gSzView_pntCPDef */


/* Works out a view's look direction. */
static inline s32 direction_001F9D80(s32 arg0) {
    Camera_001F9D80 *camera;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0;
    }
    camera = (Camera_001F9D80 *)views[arg0];
    if (camera == 0) {
        return 0;
    }
    camera->direction.x = camera->target.x - camera->position.x;
    camera->direction.y = camera->target.y - camera->position.y;
    camera->direction.z = camera->target.z - camera->position.z;
    camera->direction.w = 0.0f;
    RhGeom_NormalizeVector(&camera->direction.x);
    return 1;
}

/* Works out a view's spherical position. */
static inline s32 polar_001F9D80(s32 arg0) {
    Vec4_001F9D80 result;
    Camera_001F9D80 *camera;
    Vec4_001F9D80 *position;
    Vec4_001F9D80 *target;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0;
    }
    camera = (Camera_001F9D80 *)views[arg0];
    if (camera == 0) {
        return 0;
    }
    position = &camera->position;
    target = &camera->target;
    result.x = func_001A6C60(
        (position->x - target->x) * (position->x - target->x) +
        (position->z - target->z) * (position->z - target->z));
    result.y = func_001A6C18(position->z - target->z, position->x - target->x);
    result.y = func_001A6C30(6.2831855f + result.y, 6.2831855f);
    result.z = func_001A6C18(position->y - target->y, result.x);
    result.x = func_001A6C60(
        (position->x - target->x) * (position->x - target->x) +
        (position->y - target->y) * (position->y - target->y) +
        (position->z - target->z) * (position->z - target->z));
    camera->result = result;
    return 1;
}

/* Sets view `view`'s camera position. */
s32 SzView_SetCP(s32 view, void *src) {
    Vec4_001F9D80 *target = src;
    Camera_001F9D80 *camera;

    if ((view < 0) || (view > 0)) {
        return 0;
    }
    camera = (Camera_001F9D80 *)views[view];
    if (camera == 0) {
        return 0;
    }
    if (target == NULL) {
        target = &defaultCameraPos;
    }
    camera->target = *target;
    direction_001F9D80(view);
    polar_001F9D80(view);
    return 1;
}

/* Sets view `view`'s camera roll. */
s32 SzView_SetRoll(s32 view, s32 roll) {
    void *state;

    if (view < 0 || view > 0) {
        return 0;
    }
    state = (void *)views[view];
    if (state == NULL) {
        return 0;
    }
    *(s32 *)((u8 *)state + 0x40) = roll;
    return 1;
}

typedef struct Vec4_001F9FE0 {
    f32 x, y, z, w;
} Vec4_001F9FE0;

typedef struct Camera_001F9FE0 {
    Vec4_001F9FE0 result;
    Vec4_001F9FE0 direction;
    Vec4_001F9FE0 position;
    Vec4_001F9FE0 target;
} Camera_001F9FE0;


/* Works out a view's look direction. */
static inline s32 direction_001F9FE0(s32 arg0) {
    Camera_001F9FE0 *camera;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0;
    }
    camera = (Camera_001F9FE0 *)views[arg0];
    if (camera == 0) {
        return 0;
    }
    camera->direction.x = camera->target.x - camera->position.x;
    camera->direction.y = camera->target.y - camera->position.y;
    camera->direction.z = camera->target.z - camera->position.z;
    camera->direction.w = 0.0f;
    RhGeom_NormalizeVector(&camera->direction.x);
    return 1;
}

/* Works out a view's spherical position. */
static inline s32 polar_001F9FE0(s32 arg0) {
    Vec4_001F9FE0 result;
    Camera_001F9FE0 *camera;
    Vec4_001F9FE0 *position;
    Vec4_001F9FE0 *target;

    if ((arg0 < 0) || (arg0 > 0)) {
        return 0;
    }
    camera = (Camera_001F9FE0 *)views[arg0];
    if (camera == 0) {
        return 0;
    }
    position = &camera->position;
    target = &camera->target;
    result.x = func_001A6C60(
        (position->x - target->x) * (position->x - target->x) +
        (position->z - target->z) * (position->z - target->z));
    result.y = func_001A6C18(position->z - target->z, position->x - target->x);
    result.y = func_001A6C30(6.2831855f + result.y, 6.2831855f);
    result.z = func_001A6C18(position->y - target->y, result.x);
    result.x = func_001A6C60(
        (position->x - target->x) * (position->x - target->x) +
        (position->y - target->y) * (position->y - target->y) +
        (position->z - target->z) * (position->z - target->z));
    camera->result = result;
    return 1;
}

/* Sets view `view`'s camera position and look point. */
s32 SzView_SetCamera(s32 view, void *cameraPos, void *lookTarget) {
    extern struct Vec4_001F9B20 defaultCameraSpherical;
    extern struct Vec4_001F9D80 defaultCameraPos;
    Vec4_001F9FE0 *position = cameraPos;
    Vec4_001F9FE0 *target = lookTarget;
    Camera_001F9FE0 *camera;

    if ((view < 0) || (view > 0)) {
        return 0;
    }
    camera = (Camera_001F9FE0 *)views[view];
    if (camera == 0) {
        return 0;
    }
    if (position == NULL) {
        position = (Vec4_001F9FE0 *)&defaultCameraSpherical;
    }
    if (target == NULL) {
        target = (Vec4_001F9FE0 *)&defaultCameraPos;
    }
    camera->position = *position;
    camera->target = *target;
    direction_001F9FE0(view);
    polar_001F9FE0(view);
    return 1;
}

typedef struct Camera_001FA220 {
    Vec4_001F9B20 polar;
    Vec4_001F9B20 rotation;
    Vec4_001F9B20 position;
    Vec4_001F9B20 target;
    s32 roll;
    f32 fov;
} Camera_001FA220;

typedef union Value_001FA220 {
    s32 i;
    void *p;
    Vec4_001F9B20 v;
} Value_001FA220;

typedef struct Slot_001FA220 {
    s8 active : 1;
    s8 type : 7;
    s8 flag : 1;
    s8 other : 7;
    s8 owner;
    s8 target;
    u16 count;
    u16 timer;
    u8 pad08[8];
    Value_001FA220 from;
    Value_001FA220 to;
} Slot_001FA220;

/* Linear blend from `from` to `to`. */
static inline s32 lerp_001FA220(s32 from, s32 to, f32 t) {
    s32 d = to - from;

    return from + (s32)(d * t);
}

/* Sets a view's field of view. */
static inline s32 setFov_001FA220(s32 index, s32 fov) {
    Camera_001FA220 *camera;

    if (index < 0 || index > 0) {
        return 0;
    }
    camera = (Camera_001FA220 *)views[index];
    if (camera == NULL) {
        return 0;
    }
    camera->fov = fov;
    return 1;
}

/* Sets a view's roll. */
static inline s32 setRoll_001FA220(s32 index, s32 roll) {
    Camera_001FA220 *camera;

    if (index < 0 || index > 0) {
        return 0;
    }
    camera = (Camera_001FA220 *)views[index];
    if (camera == NULL) {
        return 0;
    }
    camera->roll = (s32)(f32)roll;
    return 1;
}

/* Sets a view's camera position. */
static inline s32 setPosition_001FA220(s32 index, Vec4_001F9B20 *position) {
    Camera_001FA220 *camera;

    if (index < 0 || index > 0) {
        return 0;
    }
    camera = (Camera_001FA220 *)views[index];
    if (camera == NULL) {
        return 0;
    }
    if (position == NULL) {
        position = &defaultCameraSpherical;
    }
    camera->position = *position;
    lSzView_CalcRel(index);
    lSzView_CalcLook(index);
    return 1;
}

/* Sets a view's look point. */
static inline s32 setTarget_001FA220(s32 index, Vec4_001F9B20 *target) {
    Camera_001FA220 *camera;

    if (index < 0 || index > 0) {
        return 0;
    }
    camera = (Camera_001FA220 *)views[index];
    if (camera == NULL) {
        return 0;
    }
    if (target == NULL) {
        target = (Vec4_001F9B20 *)&defaultCameraPos;
    }
    camera->target = *target;
    lSzView_CalcRel(index);
    lSzView_CalcLook(index);
    return 1;
}

/* Runs the camera requests of `owner` on view `target`: moves, turns, zooms and shakes over their frames. */
void SzView_DoRequest(s32 owner, s32 target) {
    extern Slot_001FA220 cameraRequests[];
    extern s32 SzGame_GetFrameSpeed();
    Slot_001FA220 *slot;
    s32 delta;
    s32 i;
    s32 done;
    s32 timer;
    s32 d;
    s32 nt;
    f32 t;
    Vec4_001F9B20 pos;
    Vec4_001F9B20 polar;

    slot = cameraRequests;
    delta = SzGame_GetFrameSpeed();
    i = 0;
    do {
        if (slot->active && !slot->flag && (owner < 0 || slot->owner == owner) &&
            (target < 0 || slot->target == target)) {
            done = 0;
            timer = slot->timer + delta;
            if (timer < 0xFFFF) {
                nt = timer;
            } else {
                nt = 0xFFFF;
            }
            slot->timer = nt;
            if (slot->timer >= slot->count) {
                done = 1;
            }
            t = (f32)slot->timer / (f32)slot->count;
            switch (slot->type) {
            case 0:
                d = slot->to.i - slot->from.i;
                setFov_001FA220(slot->owner, slot->from.i + (s32)(d * t));
                break;
            case 1:
                d = slot->to.i - slot->from.i;
                setRoll_001FA220(slot->owner, slot->from.i + (s32)(d * t));
                break;
            case 2:
            case 3:
                pos.x = slot->from.v.x + t * (slot->to.v.x - slot->from.v.x);
                pos.y = slot->from.v.y + t * (slot->to.v.y - slot->from.v.y);
                pos.z = slot->from.v.z + t * (slot->to.v.z - slot->from.v.z);
                if (slot->type == 2) {
                    setPosition_001FA220(slot->owner, &pos);
                } else {
                    setTarget_001FA220(slot->owner, &pos);
                }
                break;
            case 4:
            case 5:
                polar.x = slot->from.v.x + t * (slot->to.v.x - slot->from.v.x);
                polar.y = slot->from.v.y + t * (slot->to.v.y - slot->from.v.y);
                polar.z = slot->from.v.z + t * (slot->to.v.z - slot->from.v.z);
                if (slot->type == 4) {
                    SzView_SetLookSP(slot->owner, &polar.x);
                } else {
                    SzView_SetLookCP(slot->owner, &polar.x);
                }
                break;
            case 6:
                SzView_SetViewCamera(slot->owner, slot->to.i, &slot->from.v.x, 1, t);
                break;
            case 7:
                SzView_SetViewCamera(slot->owner, slot->to.i, &slot->from.v.x, 2, t);
                break;
            case 8:
            case 9:
                SzView_SetInterpCameraMotion(slot->owner, slot->from.p, slot->count, slot->timer, slot->to.i, slot->type == 9);
                break;
            }
            if (done) {
                slot->active = 0;
            }
        }
        i++;
        slot++;
    } while (i < 8);
}

typedef struct Entry_001FA6F0 {
    s8 active : 1;
    s8 : 7;
    s8 unk_01;
    s8 field_02;
    s8 field_03;
    u8 pad_04[0x2C];
} Entry_001FA6F0;

extern Entry_001FA6F0 cameraRequests[]; /* original: gSzView_CameraReq */

/* The first running camera request of `owner` on `target` (-1 for any), or NULL. */
void *SzView_InqRequest(s32 owner, s32 target) {
    Entry_001FA6F0 *entry;
    s32 i;

    entry = cameraRequests;
    i = 0;
    do {
        if (entry->active && (owner < 0 || entry->field_02 == owner) &&
            (target < 0 || entry->field_03 == target)) {
            return entry;
        }
        i++;
        entry++;
    } while (i < 8);
    return NULL;
}

typedef struct Entry_001FA770 {
    s8 active : 1;
    s8 unused0 : 7;
    s8 flag : 1;
    s8 unused1 : 7;
    s8 field2;
    s8 field3;
    u8 padding[0x2C];
} Entry_001FA770;

extern struct Entry_001FA6F0 cameraRequests[]; /* original: gSzView_CameraReq */

/* Pauses (`on`) or resumes the camera requests of `owner` on `target` (-1 for any). Returns whether any matched. */
s32 SzView_PauseRequest(s32 owner, s32 target, s32 on) {
    Entry_001FA770 *entry;
    s32 i;
    s32 found;

    entry = (Entry_001FA770 *) cameraRequests;
    found = 0;
    i = 0;
    do {
        if (entry->active) {
            if (owner < 0 || entry->field2 == owner) {
                if (target < 0 || entry->field3 == target) {
                    entry->flag = (s8) (on ? 1 : 0);
                    found = 1;
                }
            }
        }
        i += 1;
        entry++;
    } while (i < 8);
    return found;
}

typedef struct Entry_001FA810 {
    s8 active : 1;
    s8 : 7;
    s8 unk1;
    s8 x;
    s8 y;
    u8 padding[0x2C];
} Entry_001FA810;

extern struct Entry_001FA6F0 cameraRequests[]; /* original: gSzView_CameraReq */

/* Ends the camera requests of `owner` on `target` (-1 for any). */
s32 SzView_FreeRequest(s32 owner, s32 target) {
    Entry_001FA810 *entry;
    s32 found;
    s32 i;

    entry = (Entry_001FA810 *)cameraRequests;
    found = 0;
    i = 0;
    do {
        if (entry->active && (owner < 0 || entry->x == owner) &&
            (target < 0 || entry->y == target)) {
            found = 1;
            entry->active = 0;
        }
        i++;
        entry++;
    } while (i < 8);
    return found;
}

typedef struct Vec4_001FA8A0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001FA8A0;

typedef struct Camera_001FA8A0 {
    Vec4_001FA8A0 polar;
    Vec4_001FA8A0 rotation;
    Vec4_001FA8A0 direction;
    Vec4_001FA8A0 position;
    s32 roll;
    f32 fov;
} Camera_001FA8A0;

typedef union Value_001FA8A0 {
    s32 i;
    void *p;
    Vec4_001FA8A0 v;
} Value_001FA8A0;

typedef struct Slot_001FA8A0 {
    s8 active : 1;
    s8 type : 7;
    s8 flag : 1;
    s8 other : 7;
    s8 owner;
    s8 target;
    u16 count;
    u16 timer;
    u8 pad08[8];
    Value_001FA8A0 from;
    Value_001FA8A0 to;
} Slot_001FA8A0;

typedef struct Track_001FA8A0 {
    u8 pad00[0xC];
    u16 frames;
} Track_001FA8A0;

#define ROUND_001FA8A0(x) (((x) + (((x) > 0 ? 0x1000 : -0x1000) >> 1)) >> 12)

/* A free camera request slot, or NULL. */
static inline Slot_001FA8A0 *findFree_001FA8A0(void) {
    Slot_001FA8A0 *slot = (Slot_001FA8A0 *)cameraRequests;
    s32 i = 0;

    do {
        if (!slot->active) {
            return slot;
        }
        i++;
        slot++;
    } while (i < 8);
    return NULL;
}

/* Radians to the game's angle units. */
static inline f32 toAngle_001FA8A0(f32 radians) {
    return (32768.0f * radians) / 3.1415927f;
}

/* Asks view `target` for a camera move of `type` over `count` frames (to `data`), owned by `owner`. */
s32 SzView_ReqCamera(s32 owner, s32 target, s32 type, s32 count, s32 value, void *data) {
    Camera_001FA8A0 *camera;
    Slot_001FA8A0 *slot;
    f32 fromAngle;
    f32 toAngle;
    s32 fromSign;
    s32 toSign;
    s32 delta;

    if (owner < 0 || owner > 0) {
        return 0;
    }
    camera = (Camera_001FA8A0 *)views[owner];
    if (camera == NULL) {
        return 0;
    }
    slot = findFree_001FA8A0();
    if (slot == NULL) {
        return 0;
    }
    switch (type) {
    case 0:
        slot->from.i = (s32)camera->fov;
        slot->to.i = value;
        break;
    case 1:
        slot->from.i = camera->roll % 0x10000;
        if (slot->from.i > 0x8000) {
            slot->from.i = -(0x10000 - slot->from.i);
        }
        slot->to.i = value % 0x10000;
        if (slot->to.i > 0x8000) {
            slot->to.i = -(0x10000 - slot->to.i);
        }
        break;
    case 2:
        slot->from.v = camera->direction;
        slot->to.v = *(Vec4_001FA8A0 *)data;
        break;
    case 3:
        slot->from.v = camera->position;
        slot->to.v = *(Vec4_001FA8A0 *)data;
        break;
    case 4:
    case 5:
        slot->from.v = camera->polar;
        slot->to.v = *(Vec4_001FA8A0 *)data;
        fromAngle = toAngle_001FA8A0(slot->from.v.y);
        fromSign = ((s32)fromAngle > 0) ? 0x1000 : -0x1000;
        toAngle = toAngle_001FA8A0(slot->to.v.y);
        toSign = ((s32)toAngle > 0) ? 0x1000 : -0x1000;
        delta = (s32)toAngle;
        delta = (((delta + (toSign >> 1)) >> 12) - (((s32)fromAngle + (fromSign >> 1)) >> 12)) << 12;
        if (delta < -0x8000) {
            slot->to.v.y += 6.2831855f;
        } else if (delta >= 0x8000) {
            slot->to.v.y -= 6.2831855f;
        }
        break;
    case 6:
    case 7:
        slot->from.v = camera->position;
        slot->to.i = value;
        break;
    case 8:
    case 9:
        slot->from.p = data;
        slot->to.i = value;
        if (count == 0) {
            count = (u16)(((Track_001FA8A0 *)data)->frames - 1);
        }
        break;
    default:
        return 0;
    }
    if (count == 0) {
        count = (u16)(count + 1);
    }
    slot->active = 1;
    slot->type = type;
    slot->flag = 0;
    slot->other = 0;
    slot->owner = owner;
    slot->target = target;
    slot->count = count;
    slot->timer = 0;
    return 1;
}

/* View `view`'s relative (orbit) camera position. */
s32 SzView_GetRel(s32 view) {
    s32 state;

    if (view < 0 || view > 0) {
        return 0;
    }
    state = views[view];
    if (state == 0) {
        return 0;
    }
    return state + 0x10;
}

typedef struct Vec4_001FAD60 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001FAD60;

typedef struct Camera_001FAD60 {
    Vec4_001FAD60 polar;
    Vec4_001FAD60 rotation;
    Vec4_001FAD60 direction;
    Vec4_001FAD60 position;
} Camera_001FAD60;


/* Sets view `view`'s relative camera position in spherical form. */
s32 SzView_SetRelSP(s32 view, void *src) {
    Camera_001FAD60 *camera;
    s32 *entry;
    Vec4_001FAD60 *position;
    Vec4_001FAD60 *direction;
    Camera_001FAD60 *camera2;
    Vec4_001FAD60 result;

    if ((view < 0) || (view > 0)) {
        return 0;
    }
    entry = &views[view];
    camera = (Camera_001FAD60 *)*entry;
    if (camera == NULL) {
        return 0;
    }
    if (src == NULL) {
        return 0;
    }
    camera->rotation = *(Vec4_001FAD60 *)src;
    RhGeom_NormalizeVector(&camera->rotation);
    camera->direction.x = camera->position.x - (((Vec4_001FAD60 *)src)->x * camera->polar.x);
    camera->direction.y = camera->position.y - (((Vec4_001FAD60 *)src)->y * camera->polar.x);
    camera->direction.z = camera->position.z - (((Vec4_001FAD60 *)src)->z * camera->polar.x);
    camera->direction.w = 0.0f;
    if ((view >= 0) && (view <= 0)) {
        camera2 = (Camera_001FAD60 *)*entry;
        if (camera2 != NULL) {
            direction = &camera2->direction;
            position = &camera2->position;

            result.x = func_001A6C60(((direction->x - position->x) * (direction->x - position->x)) +
                                     ((direction->z - position->z) * (direction->z - position->z)));
            result.y = func_001A6C18(direction->z - position->z, direction->x - position->x);
            result.y = func_001A6C30(6.2831855f + result.y, 6.2831855f);
            result.z = func_001A6C18(direction->y - position->y, result.x);
            result.x = func_001A6C60(((direction->x - position->x) * (direction->x - position->x)) +
                                     ((direction->y - position->y) * (direction->y - position->y)) +
                                     ((direction->z - position->z) * (direction->z - position->z)));
            camera2->polar = result;
        }
    }
    return 1;
}

/* View `view`'s look point. */
f32 *SzView_GetLook(s32 view) {
    f32 *look;

    if (view < 0 || view > 0) {
        return NULL;
    }
    look = (f32 *)views[view];
    if (look == NULL) {
        look = NULL;
    }
    return look;
}

/* An angle to the game's fixed angle units. */
static inline f32 angleToFixed_001FAFB0(f32 angle) {
    return (32768.0f * angle) / 3.1415927f;
}

/* View `view`'s look direction into `out`. */
s32 SzView_GetLookVector(s32 view, s32 outVec) {
    extern s32 func_001A22C0(f32);
    s32 *out = (s32 *)outVec;
    f32 *angles;

    if ((view < 0) || (view > 0)) {
        return 0;
    }
    angles = (f32 *)views[view];
    if (angles == 0) {
        return 0;
    }
    if (out == 0) {
        return 0;
    }
    out[0] = -(s32)func_001A22C0(angleToFixed_001FAFB0(angles[2]));
    out[1] = 0x4000 - (s32)func_001A22C0(angleToFixed_001FAFB0(angles[1]));
    out[3] = 0;
    out[2] = 0;
    return 1;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vector_001FB0B0;


/* Radians to the game's fixed angle units. */
static inline s32 fixed_angle_001FB0B0(f32 radians) {
    extern s32 func_001A22C0(f32);
    return func_001A22C0((32768.0f * radians) / 3.1415927f);
}

/* A view's look angles. */
static inline s32 angles_001FB0B0(s32 index, s32 *angles) {
    Vector_001FB0B0 *source;

    if (index < 0 || index > 0) {
        return 0;
    }
    source = (Vector_001FB0B0 *)views[index];
    if (source == 0) {
        return 0;
    }
    angles[0] = -fixed_angle_001FB0B0(source->z);
    angles[1] = 0x4000 - fixed_angle_001FB0B0(source->y);
    angles[3] = 0;
    angles[2] = 0;
    return 1;
}

/* View `view`'s look matrix into `out`. */
s32 SzView_GetLookMatrix(s32 view, s32 out) {
    s32 angles[4];

    if (out == 0) {
        return 0;
    }
    if (angles_001FB0B0(view, angles) == 0) {
        return 0;
    }
    RhGeom_GetRotXYZMatrix((void *)out, angles);
    return 1;
}

typedef struct {
    s32 x, y, z, w;
} Vec4i_001FB1D0;

extern Vec4i_001FB1D0 D_00293060;

/* A view's depth range. */
static inline s32 depth_001FB1D0(s32 index) {
    void *object;

    if (index < 0 || index > 0) {
        return 0;
    }
    object = (void *)views[index];
    if (object == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)object + 0x40);
}

/* View `view`'s look matrix, with its roll, into `out`. */
s32 SzView_GetLookMatrixWithRoll(s32 view, s32 out) {
    Vec4i_001FB1D0 translation;
    s32 angles[4];
    f32 matrix[4][4];

    translation = D_00293060;
    translation.z = -depth_001FB1D0(view);
    if (out == 0) {
        return 0;
    }
    if (angles_001FB0B0(view, angles) == 0) {
        return 0;
    }
    RhGeom_GetRotXYZMatrix((void *)out, angles);
    RhGeom_GetRotXYZMatrix(matrix, &translation);
    RhGeom_MulMatrix(out, matrix);
    return 1;
}

extern f32 identityMatrix[4][4]; /* original: gSzView_vecUnit */

typedef struct Vec4_001FB360 {
    f32 x, y, z, w;
} Vec4_001FB360;

typedef struct Camera_001FB360 {
    Vec4_001FB360 param;
    f32 direction[4];
    f32 origin[4];
    f32 target[4];
} Camera_001FB360;

/* Works out a view's aim. */
static inline s32 aim_001FB360(s32 index) {
    Camera_001FB360 *entry;

    if ((index < 0) || (index > 0)) {
        return 0;
    }
    entry = (Camera_001FB360 *)views[index];
    if (entry == 0) {
        return 0;
    }
    entry->direction[0] = entry->target[0] - entry->origin[0];
    entry->direction[1] = entry->target[1] - entry->origin[1];
    entry->direction[2] = entry->target[2] - entry->origin[2];
    entry->direction[3] = 0.0f;
    RhGeom_NormalizeVector(entry->direction);
    return 1;
}

/* Sets view `index`'s look point in spherical form around the camera. */
s32 SzView_SetLookSP(s32 index, f32 *src) {
    Camera_001FB360 *entry;
    f32 matrix[4][4];
    f32 angles[4];

    if ((index < 0) || (index > 0)) {
        return 0;
    }
    entry = (Camera_001FB360 *)views[index];
    if (entry == 0) {
        return 0;
    }
    if (src == NULL) {
        return 0;
    }
    entry->param = *(Vec4_001FB360 *)src;
    entry->param.y = func_001A6C30(6.2831855f + entry->param.y, 6.2831855f);
    if (SzView_GetLookVector(index, (s32)angles) != 0) {
        RhGeom_GetRotXYZMatrix(matrix, angles);
    }
    RhGeom_MulMatrixVector(entry->direction, matrix, identityMatrix);
    entry->origin[0] = entry->target[0] + entry->direction[0] * entry->param.x;
    entry->origin[1] = entry->target[1] + entry->direction[1] * entry->param.x;
    entry->origin[2] = entry->target[2] + entry->direction[2] * entry->param.x;
    entry->origin[3] = 0.0f;
    aim_001FB360(index);
    return 1;
}
