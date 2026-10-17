#include "common.h"

/* Sets the position of unit `id`'s model ((side << 8) | unit; `id` then holds the model slot). */
s32 SzEffect_SetModelPos2(s32 id, void *pos) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side;
    s32 slot;

    side = id >> 8;
    slot = id & 0xFF;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_SetPos(id, pos);
}

/* The position of unit `id`'s model ((side << 8) | unit) into `out`. */
s32 SzEffect_GetModelPos2(s32 id, f32 *out) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side = id >> 8;
    s32 slot = id & 0xFF;

    out[2] = 0.0f;
    out[1] = 0.0f;
    out[0] = 0.0f;
    out[3] = 1.0f;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_GetPos(id, out);
}

/* Sets the rotation of unit `id`'s model ((side << 8) | unit; `id` then holds the model slot). */
s32 SzEffect_SetModelRot2(s32 id, void *rot) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side;
    s32 slot;

    side = id >> 8;
    slot = id & 0xFF;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_SetRot(id, rot);
}

/* Sets the rotation centre of the effect target's model. */
void SzEffect_SetModelRotC(s32 arg0) {
    SzEffect_SetModelRotC2(D_0031BE98, arg0);
}

/* Sets the rotation centre of unit `id`'s model ((side << 8) | unit; `id` then holds the model slot). */
s32 SzEffect_SetModelRotC2(s32 id, s32 mode) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side;
    s32 slot;

    side = id >> 8;
    slot = id & 0xFF;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_SetRotC(id, (void *)mode);
}

/* The rotation of unit `id`'s model ((side << 8) | unit) into `out`. */
s32 SzEffect_GetModelRot2(s32 id, void *out) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side = id >> 8;
    s32 slot = id & 0xFF;

    ((s32 *)out)[3] = 0;
    ((s32 *)out)[2] = 0;
    ((s32 *)out)[1] = 0;
    ((s32 *)out)[0] = 0;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_GetRot(id, out);
}

/* The rotation centre of the effect target's model. */
void SzEffect_GetModelRotC(s32 arg0) {
    SzEffect_GetModelRotC2(D_0031BE98, arg0);
}

/* The rotation centre of unit `id`'s model ((side << 8) | unit) into `out`. */
s32 SzEffect_GetModelRotC2(s32 id, s32 out) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side = id >> 8;
    s32 slot = id & 0xFF;

    ((s32 *)out)[3] = 0;
    ((s32 *)out)[2] = 0;
    ((s32 *)out)[1] = 0;
    ((s32 *)out)[0] = 0;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_GetRotC(id, (void *)out);
}

/* Sets the scale of unit `id`'s model ((side << 8) | unit; `id` then holds the model slot). */
s32 SzEffect_SetModelScale2(s32 id, void *scale) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side;
    s32 slot;

    side = id >> 8;
    slot = id & 0xFF;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_SetScale(id, scale);
}

/* The scale of unit `id`'s model ((side << 8) | unit) into `out`. */
s32 SzEffect_GetModelScale2(s32 id, f32 *out) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side = id >> 8;
    s32 slot = id & 0xFF;

    out[2] = 0.0f;
    out[1] = 0.0f;
    out[0] = 0.0f;
    out[3] = 1.0f;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_GetScale(id, out);
}

/* Sets the colour of unit `id`'s model ((side << 8) | unit; `id` then holds the model slot). */
void SzEffect_SetModelRgba2(s32 id, s32 color) {
    SzEffect_SetModelRgbaX(id, -1, color);
}

/* Sets the colour (`mode`, `value`) of unit `id`'s model (side in the high byte, slot in the low byte). */
s32 SzEffect_SetModelRgbaX(s32 id, s32 mode, s32 value) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side;
    s32 slot;

    side = id >> 8;
    slot = id & 0xFF;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_SetRgba(id, mode, (void *) value);
}

/* The colour of the effect target's model. */
void SzEffect_GetModelRgba(s32 arg0) {
    extern s32 SzEffect_GetModelRgba2();

    SzEffect_GetModelRgba2(D_0031BE98, arg0);
}

/* The colour of unit `id`'s model ((side << 8) | unit) into `out`. */
s32 SzEffect_GetModelRgba2(s32 id, u8 *out) {
    if (SzEffect_GetModelRgbaX(id, out) >= 0) {
        return 1;
    }
    return 0;
}

/* The colour of unit `id`'s model into `out` (side in the high byte, slot in the low byte). */
s32 SzEffect_GetModelRgbaX(s32 id, u8 *out) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side = id >> 8;
    s32 slot = id & 0xFF;

    out[3] = 0x80;
    out[0] = 0x80;
    out[1] = 0x80;
    out[2] = 0x80;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return -1;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return -1;
    }
    return SzModel_GetRgba(id, out);
}

/* Sets the colour filter of the effect target's model. */
void SzEffect_SetModelFilter(s32 arg0) {
    SzEffect_SetModelFilterX(D_0031BE98, -1, arg0);
}

/* Sets the colour filter of unit `id`'s model ((side << 8) | unit; `id` then holds the model slot). */
void SzEffect_SetModelFilter2(s32 id, s32 color) {
    SzEffect_SetModelFilterX(id, -1, color);
}

/* Sets the colour filter of unit `id`'s model (side in the high byte, slot in the low byte). */
s32 SzEffect_SetModelFilterX(s32 id, s32 mode, s32 value) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side;
    s32 slot;

    side = id >> 8;
    slot = id & 0xFF;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_SetFilter(id, mode, (void *) value);
}

/* The animation of unit `id`'s model ((side << 8) | unit). */
s32 SzEffect_GetAnim2(s32 id) {
    extern s32 SzModel_GetAnim(s32);
    s32 side;
    s32 slot;

    side = id >> 8;
    slot = id & 0xFF;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return -1;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return -1;
    }
    return SzModel_GetAnim(id);
}

/* Sets the animation (blending in) of unit `id`'s model ((side << 8) | unit). */
s32 SzEffect_SetAnimIntr2(s32 id, s32 value) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side;
    s32 slot;

    side = id >> 8;
    slot = id & 0xFF;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_SetAnimIntr(id, value);
}

/* Sets the animation direction of unit `id`'s model ((side << 8) | unit). */
s32 SzEffect_SetAnimDir2(s32 id, s64 value) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 side;
    s32 slot;

    side = id >> 8;
    slot = id & 0xFF;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_SetAnimDir(id, value);
}

/* The animation frame of unit `id`'s model ((side << 8) | unit). */
f32 SzEffect_GetAnimFrame2(s32 id, s32 value) {
    s32 SzDuel_GetUnitModelID();
    f32 SzModel_GetAnimFrame();
    s32 side = id >> 8;
    s32 slot = id & 0xFF;

    if (side < 0 || side >= 3 || slot < 0 || slot >= 11) {
        return 0.0f;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0.0f;
    }
    return SzModel_GetAnimFrame(id);
}

/* Sets the animation frame of unit `id`'s model ((side << 8) | unit). */
s32 SzEffect_SetAnimFrame2(s32 id, f32 value) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    extern s32 SzModel_SetAnimFrame(s32, f32);
    s32 side;
    s32 slot;

    side = id >> 8;
    slot = id & 0xFF;
    if (side < 0 || side >= 3 || slot < 0 || slot >= 0xB) {
        return 0;
    }
    id = SzDuel_GetUnitModelID(side, slot);
    if (id < 0) {
        return 0;
    }
    return SzModel_SetAnimFrame(id, value);
}

/* Sets the fog colour for the monster view. */
void SzEffect_SetFogColorForMonster(s32 value) {
    SzView_SetFogColor(0, 4, value);
    SzView_SetFogColor(0, 5, value);
}

/* Sets the fog colour for the duel board. */
void SzEffect_SetFogColorForDuel(s32 value) {
    SzView_SetFogColor(0, 0, value);
    SzView_SetFogColor(0, 1, value);
    SzView_SetFogColor(0, 8, value);
}

/* Sets the fog colour for 3D battles. */
void SzEffect_SetFogColorForBattle(s32 value) {
    SzView_SetFogColor(0, 2, value);
    SzView_SetFogColor(0, 3, value);
}

/* Sets the depth fog range for the monster view. */
void SzEffect_SetFogParamZForMonster(s32 value) {
    SzView_SetFogParamZ(0, 4, value);
    SzView_SetFogParamZ(0, 5, value);
}

/* Sets the depth fog range for the duel board. */
void SzEffect_SetFogParamZForDuel(s32 value) {
    SzView_SetFogParamZ(0, 0, value);
    SzView_SetFogParamZ(0, 1, value);
    SzView_SetFogParamZ(0, 8, value);
}

/* Sets the depth fog range for 3D battles. */
void SzEffect_SetFogParamZForBattle(s32 value) {
    SzView_SetFogParamZ(0, 2, value);
    SzView_SetFogParamZ(0, 3, value);
}

/* Sets the height fog range for the monster view. */
void SzEffect_SetFogParamYForMonster(s32 value) {
    SzView_SetFogParamY(0, 4, value);
    SzView_SetFogParamY(0, 5, value);
}

/* Sets the height fog range for the duel board. */
void SzEffect_SetFogParamYForDuel(s32 value) {
    SzView_SetFogParamY(0, 0, value);
    SzView_SetFogParamY(0, 1, value);
    SzView_SetFogParamY(0, 8, value);
}

/* Sets the height fog range for 3D battles. */
void SzEffect_SetFogParamYForBattle(s32 value) {
    SzView_SetFogParamY(0, 2, value);
    SzView_SetFogParamY(0, 3, value);
}

/* Sets the directional light for the monster view. */
void SzEffect_SetStraightLightForMonster(s32 value) {
    SzView_SetStraightLight(0, 4, value);
    SzView_SetStraightLight(0, 5, value);
}

/* Sets the directional light for the duel board. */
void SzEffect_SetStraightLightForDuel(s32 value) {
    SzView_SetStraightLight(0, 0, value);
    SzView_SetStraightLight(0, 1, value);
    SzView_SetStraightLight(0, 8, value);
}

/* Sets the directional light for 3D battles. */
void SzEffect_SetStraightLightForBattle(s32 value) {
    SzView_SetStraightLight(0, 2, value);
    SzView_SetStraightLight(0, 3, value);
}

/* Sets the point light for the monster view. */
void SzEffect_SetPointLightForMonster(s32 value) {
    SzView_SetPointLight(0, 4, value);
    SzView_SetPointLight(0, 5, value);
}

/* Sets the point light for the duel board. */
void SzEffect_SetPointLightForDuel(s32 value) {
    SzView_SetPointLight(0, 0, value);
    SzView_SetPointLight(0, 1, value);
    SzView_SetPointLight(0, 8, value);
}

/* Sets the point light for 3D battles. */
void SzEffect_SetPointLightForBattle(s32 value) {
    SzView_SetPointLight(0, 2, value);
    SzView_SetPointLight(0, 3, value);
}

/* Sets the black-out level for the monster view. */
void SzEffect_SetBlackOutForMonster(s32 value) {
    D_0031BEA0 = value;
}

/* Sets the black-out level for the duel board. */
void SzEffect_SetBlackOutForDuel(s32 value) {
    D_0031BEA1 = value;
}

/* Sets the black-out level for 3D battles. */
void SzEffect_SetBlackOutForBattle(s32 value) {
    D_0031BEA2 = (s8) value;
}

/* The black-out level for the monster view. */
u8 SzEffect_GetBlackOutForMonster(void) {
    return D_0031BEA0;
}

/* The black-out level for the duel board. */
u8 SzEffect_GetBlackOutForDuel(void) {
    return (u8)D_0031BEA1;
}

/* The black-out level for 3D battles. */
u8 SzEffect_GetBlackOutForBattle(void) {
    return D_0031BEA2;
}

/* Sets the light intensity for the monster view. */
void SzEffect_SetIntensityForMonster(s32 value) {
    SzEffect_SetIntensity(4, value);
    SzEffect_SetIntensity(5, value);
}

/* Sets the light intensity for the duel board. */
void SzEffect_SetIntensityForDuel(s32 value) {
    SzEffect_SetIntensity(0, value);
    SzEffect_SetIntensity(1, value);
    SzEffect_SetIntensity(8, value);
}

/* Sets the light intensity for 3D battles. */
void SzEffect_SetIntensityForBattle(s32 value) {
    SzEffect_SetIntensity(2, value);
    SzEffect_SetIntensity(3, value);
}

/* Sets the light intensity of model slot `index` for the current scene. */
s32 SzEffect_SetIntensity(s32 index, s32 values) {
    extern s32 SzModel_GetModelType(s32);
    s32 i;

    i = 0;
    do {
        if (index < 0 || index == SzModel_GetModelType(i)) {
            SzModel_SetIntensity(i, (f32 *) values);
        }
        i += 1;
    } while (i < 0x54);
}

/* Sets the overall intensity of model slot `index`. */
void SzEffect_SetIntensityOnly(s32 index, f32 fparg0) {
    extern s32 SzModel_GetModelType(s32);
    s32 i;

    i = 0;
    do {
        if (index < 0 || index == SzModel_GetModelType(i)) {
            SzModel_SetIntensityOnly(i, fparg0);
        }
        i++;
    } while (i < 0x54);
}

/* The side the duel result is read for. */
static inline s32 player_001F6EF0(void) {
    return D_0031BE9C;
}

/* Whether the side being watched won the 3D battle (play motion 4). */
s32 SzEffect_InqDuelResult(void) {
    if (SzEffect_GetPlayMotion((SzBattle_InqEntry(0) == player_001F6EF0()) ? 0 : 1) == 4) {
        return 1;
    }
    return 0;
}
