#include "common.h"

s32 SzEffect_SetModelPos2(s32 arg0, void *arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_SetPos(arg0, arg1);
}

s32 SzEffect_GetModelPos2(s32 arg0, f32 *arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    arg1[2] = 0.0f;
    arg1[1] = 0.0f;
    arg1[0] = 0.0f;
    arg1[3] = 1.0f;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_GetPos(arg0, arg1);
}

s32 SzEffect_SetModelRot2(s32 arg0, void *arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_SetRot(arg0, arg1);
}

void SzEffect_SetModelRotC(s32 arg0) {
    SzEffect_SetModelRotC2(D_0031BE98, arg0);
}

s32 SzEffect_SetModelRotC2(s32 arg0, s32 arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_SetRotC(arg0, (void *)arg1);
}

s32 SzEffect_GetModelRot2(s32 arg0, void *arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    ((s32 *)arg1)[3] = 0;
    ((s32 *)arg1)[2] = 0;
    ((s32 *)arg1)[1] = 0;
    ((s32 *)arg1)[0] = 0;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_GetRot(arg0, arg1);
}

void SzEffect_GetModelRotC(s32 arg0) {
    SzEffect_GetModelRotC2(D_0031BE98, arg0);
}

s32 SzEffect_GetModelRotC2(s32 arg0, s32 arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    ((s32 *)arg1)[3] = 0;
    ((s32 *)arg1)[2] = 0;
    ((s32 *)arg1)[1] = 0;
    ((s32 *)arg1)[0] = 0;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_GetRotC(arg0, (void *)arg1);
}

s32 SzEffect_SetModelScale2(s32 arg0, void *arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_SetScale(arg0, arg1);
}

s32 SzEffect_GetModelScale2(s32 arg0, f32 *arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    arg1[2] = 0.0f;
    arg1[1] = 0.0f;
    arg1[0] = 0.0f;
    arg1[3] = 1.0f;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_GetScale(arg0, arg1);
}

void SzEffect_SetModelRgba2(s32 arg0, s32 arg1) {
    SzEffect_SetModelRgbaX(arg0, -1, arg1);
}

s32 SzEffect_SetModelRgbaX(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_SetRgba(arg0, arg1, (void *) arg2);
}

void SzEffect_GetModelRgba(s32 arg0) {
    extern s32 SzEffect_GetModelRgba2();

    SzEffect_GetModelRgba2(D_0031BE98, arg0);
}

s32 SzEffect_GetModelRgba2(s32 arg0, u8 *arg1) {
    if (SzEffect_GetModelRgbaX(arg0, arg1) >= 0) {
        return 1;
    }
    return 0;
}

s32 SzEffect_GetModelRgbaX(s32 arg0, u8 *arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    arg1[3] = 0x80;
    arg1[0] = 0x80;
    arg1[1] = 0x80;
    arg1[2] = 0x80;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return -1;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return -1;
    }
    return SzModel_GetRgba(arg0, arg1);
}

void SzEffect_SetModelFilter(s32 arg0) {
    SzEffect_SetModelFilterX(D_0031BE98, -1, arg0);
}

void SzEffect_SetModelFilter2(s32 arg0, s32 arg1) {
    SzEffect_SetModelFilterX(arg0, -1, arg1);
}

s32 SzEffect_SetModelFilterX(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_SetFilter(arg0, arg1, (void *) arg2);
}

s32 SzEffect_GetAnim2(s32 arg0) {
    extern s32 SzModel_GetAnim(s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return -1;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return -1;
    }
    return SzModel_GetAnim(arg0);
}

s32 SzEffect_SetAnimIntr2(s32 arg0, s32 arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_SetAnimIntr(arg0, arg1);
}

s32 SzEffect_SetAnimDir2(s32 arg0, s64 arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_SetAnimDir(arg0, arg1);
}

f32 SzEffect_GetAnimFrame2(s32 arg0, s32 arg1) {
    s32 SzDuel_GetUnitModelID();
    f32 SzModel_GetAnimFrame();
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;

    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 11) {
        return 0.0f;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0.0f;
    }
    return SzModel_GetAnimFrame(arg0);
}

s32 SzEffect_SetAnimFrame2(s32 arg0, f32 arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    extern s32 SzModel_SetAnimFrame(s32, f32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_SetAnimFrame(arg0, arg1);
}

void SzEffect_SetFogColorForMonster(s32 arg0) {
    SzView_SetFogColor(0, 4, arg0);
    SzView_SetFogColor(0, 5, arg0);
}

void SzEffect_SetFogColorForDuel(s32 arg0) {
    SzView_SetFogColor(0, 0, arg0);
    SzView_SetFogColor(0, 1, arg0);
    SzView_SetFogColor(0, 8, arg0);
}

void SzEffect_SetFogColorForBattle(s32 arg0) {
    SzView_SetFogColor(0, 2, arg0);
    SzView_SetFogColor(0, 3, arg0);
}

void SzEffect_SetFogParamZForMonster(s32 arg0) {
    SzView_SetFogParamZ(0, 4, arg0);
    SzView_SetFogParamZ(0, 5, arg0);
}

void SzEffect_SetFogParamZForDuel(s32 arg0) {
    SzView_SetFogParamZ(0, 0, arg0);
    SzView_SetFogParamZ(0, 1, arg0);
    SzView_SetFogParamZ(0, 8, arg0);
}

void SzEffect_SetFogParamZForBattle(s32 arg0) {
    SzView_SetFogParamZ(0, 2, arg0);
    SzView_SetFogParamZ(0, 3, arg0);
}

void SzEffect_SetFogParamYForMonster(s32 arg0) {
    SzView_SetFogParamY(0, 4, arg0);
    SzView_SetFogParamY(0, 5, arg0);
}

void SzEffect_SetFogParamYForDuel(s32 arg0) {
    SzView_SetFogParamY(0, 0, arg0);
    SzView_SetFogParamY(0, 1, arg0);
    SzView_SetFogParamY(0, 8, arg0);
}

void SzEffect_SetFogParamYForBattle(s32 arg0) {
    SzView_SetFogParamY(0, 2, arg0);
    SzView_SetFogParamY(0, 3, arg0);
}

void SzEffect_SetStraightLightForMonster(s32 arg0) {
    SzView_SetStraightLight(0, 4, arg0);
    SzView_SetStraightLight(0, 5, arg0);
}

void SzEffect_SetStraightLightForDuel(s32 arg0) {
    SzView_SetStraightLight(0, 0, arg0);
    SzView_SetStraightLight(0, 1, arg0);
    SzView_SetStraightLight(0, 8, arg0);
}

void SzEffect_SetStraightLightForBattle(s32 arg0) {
    SzView_SetStraightLight(0, 2, arg0);
    SzView_SetStraightLight(0, 3, arg0);
}

void SzEffect_SetPointLightForMonster(s32 arg0) {
    SzView_SetPointLight(0, 4, arg0);
    SzView_SetPointLight(0, 5, arg0);
}

void SzEffect_SetPointLightForDuel(s32 arg0) {
    SzView_SetPointLight(0, 0, arg0);
    SzView_SetPointLight(0, 1, arg0);
    SzView_SetPointLight(0, 8, arg0);
}

void SzEffect_SetPointLightForBattle(s32 arg0) {
    SzView_SetPointLight(0, 2, arg0);
    SzView_SetPointLight(0, 3, arg0);
}

void SzEffect_SetBlackOutForMonster(s32 arg0) {
    D_0031BEA0 = arg0;
}

void SzEffect_SetBlackOutForDuel(s32 arg0) {
    D_0031BEA1 = arg0;
}

void SzEffect_SetBlackOutForBattle(s32 arg0) {
    D_0031BEA2 = (s8) arg0;
}

u8 SzEffect_GetBlackOutForMonster(void) {
    return D_0031BEA0;
}

u8 SzEffect_GetBlackOutForDuel(void) {
    return (u8)D_0031BEA1;
}

u8 SzEffect_GetBlackOutForBattle(void) {
    return D_0031BEA2;
}

void SzEffect_SetIntensityForMonster(s32 arg0) {
    SzEffect_SetIntensity(4, arg0);
    SzEffect_SetIntensity(5, arg0);
}

void SzEffect_SetIntensityForDuel(s32 arg0) {
    SzEffect_SetIntensity(0, arg0);
    SzEffect_SetIntensity(1, arg0);
    SzEffect_SetIntensity(8, arg0);
}

void SzEffect_SetIntensityForBattle(s32 arg0) {
    SzEffect_SetIntensity(2, arg0);
    SzEffect_SetIntensity(3, arg0);
}

s32 SzEffect_SetIntensity(s32 arg0, s32 arg1) {
    extern s32 SzModel_GetModelType(s32);
    s32 i;

    i = 0;
    do {
        if (arg0 < 0 || arg0 == SzModel_GetModelType(i)) {
            SzModel_SetIntensity(i, (f32 *) arg1);
        }
        i += 1;
    } while (i < 0x54);
}

void SzEffect_SetIntensityOnly(s32 arg0, f32 fparg0) {
    extern s32 SzModel_GetModelType(s32);
    s32 i;

    i = 0;
    do {
        if (arg0 < 0 || arg0 == SzModel_GetModelType(i)) {
            SzModel_SetIntensityOnly(i, fparg0);
        }
        i++;
    } while (i < 0x54);
}

static inline s32 player_001F6EF0(void) {
    return D_0031BE9C;
}

s32 SzEffect_InqDuelResult(void) {
    if (SzEffect_GetPlayMotion((SzBattle_InqEntry(0) == player_001F6EF0()) ? 0 : 1) == 4) {
        return 1;
    }
    return 0;
}
