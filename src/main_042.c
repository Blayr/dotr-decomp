#include "common.h"

void SzDuel_InitCardControl(void) {
    u8 *p;
    s32 i;

    p = D_0031A7C0;
    i = 0;
    do {
        SzDuel_ClearCardControl(p);
        i += 1;
        p += 0xA0;
    } while (i < 6);
}

typedef struct State_001CDD90 {
    s32 value;
    u8 padding[0x94];
    s16 field98;
    s16 field9A;
    u32 field9C : 26;
    u32 reserved : 6;
} State_001CDD90;

typedef struct Flags_001CDD90 {
    s8 reserved : 2;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001CDD90;

s32 SzDuel_ClearCardControl(u8 *arg0) {
    State_001CDD90 *state = (State_001CDD90 *)arg0;
    Flags_001CDD90 *flags;

    if (arg0 == NULL) {
        return 0;
    }
    state->value = 0;
    state->field98 = 0;
    state->field9A = 0;
    state->field9C = 0xFF;
    flags = (Flags_001CDD90 *)(arg0 + 0x9F);
    flags->bit2 = 0;
    flags->bit3 = 0;
    flags->bit4 = 0;
    flags->bit5 = 0;
    flags->bit6 = 0;
    flags->bit7 = 0;
    return 1;
}

void *SzDuel_GetCardControl(s32 arg0) {
    if (arg0 < 0 || arg0 >= 6) {
        return NULL;
    }

    return &D_0031A7C0[arg0 * 0xA0];
}

typedef struct Flags_001CDEB0 {
    s8 unused : 3;
    s8 position : 1;
    s8 rotation : 1;
    s8 rotation2 : 1;
    s8 scale : 1;
    s8 color : 1;
} Flags_001CDEB0;

typedef struct Output_001CDEB0 {
    f32 position[4];
    s32 rotation[4];
    s32 rotation2[4];
    f32 scale[4];
    u8 color[4];
} Output_001CDEB0;

typedef struct Blend_001CDEB0 {
    Output_001CDEB0 *output;
    u8 padding04[12];
    f32 position0[4];
    f32 position1[4];
    s32 rotation0[4];
    s32 rotation1[4];
    s32 rotation20[4];
    s32 rotation21[4];
    f32 scale0[4];
    f32 scale1[4];
    u8 color0[4];
    u8 color1[4];
    u16 duration;
    u16 progress;
    u8 padding9C[3];
    Flags_001CDEB0 flags;
} Blend_001CDEB0;

s32 SzDuel_DoCardControl0(void *arg0) {
    extern s32 func_001A22C0(f32);
    Output_001CDEB0 *output;
    f32 blend;
    f32 inverse;
    Blend_001CDEB0 *src = arg0;

    output = src->output;
    if (output != NULL) {
        blend = (f32)src->progress / (f32)src->duration;
        inverse = 1.0f - blend;
        if (src->flags.position) {
            output->position[0] = src->position0[0] * inverse + src->position1[0] * blend;
            output->position[1] = src->position0[1] * inverse + src->position1[1] * blend;
            output->position[2] = src->position0[2] * inverse + src->position1[2] * blend;
            output->position[3] = src->position0[3] * inverse + src->position1[3] * blend;
        }
        if (src->flags.rotation) {
            output->rotation[0] = func_001A22C0((f32)src->rotation0[0] * inverse + (f32)src->rotation1[0] * blend) % 0x10000;
            output->rotation[1] = func_001A22C0((f32)src->rotation0[1] * inverse + (f32)src->rotation1[1] * blend) % 0x10000;
            output->rotation[2] = func_001A22C0((f32)src->rotation0[2] * inverse + (f32)src->rotation1[2] * blend) % 0x10000;
            output->rotation[3] = func_001A22C0((f32)src->rotation0[3] * inverse + (f32)src->rotation1[3] * blend) % 0x10000;
        }
        if (src->flags.rotation2) {
            output->rotation2[0] = func_001A22C0((f32)src->rotation20[0] * inverse + (f32)src->rotation21[0] * blend) % 0x10000;
            output->rotation2[1] = func_001A22C0((f32)src->rotation20[1] * inverse + (f32)src->rotation21[1] * blend) % 0x10000;
            output->rotation2[2] = func_001A22C0((f32)src->rotation20[2] * inverse + (f32)src->rotation21[2] * blend) % 0x10000;
            output->rotation2[3] = func_001A22C0((f32)src->rotation20[3] * inverse + (f32)src->rotation21[3] * blend) % 0x10000;
        }
        if (src->flags.scale) {
            output->scale[0] = src->scale0[0] * inverse + src->scale1[0] * blend;
            output->scale[1] = src->scale0[1] * inverse + src->scale1[1] * blend;
            output->scale[2] = src->scale0[2] * inverse + src->scale1[2] * blend;
            output->scale[3] = src->scale0[3] * inverse + src->scale1[3] * blend;
        }
        if (src->flags.color) {
            output->color[2] = func_001A22C0((f32)src->color0[2] * inverse + (f32)src->color1[2] * blend);
            output->color[1] = func_001A22C0((f32)src->color0[1] * inverse + (f32)src->color1[1] * blend);
            output->color[0] = func_001A22C0((f32)src->color0[0] * inverse + (f32)src->color1[0] * blend);
            output->color[3] = func_001A22C0((f32)src->color0[3] * inverse + (f32)src->color1[3] * blend);
        }
        return 1;
    }
    return 0;
}

void SzDuel_DrawUnit(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawUnit_Pipe(RhBase_GetVifPacketArea()));
}

typedef union Color_001CE430 {
    f32 value;
    struct { u8 r, g, b, a; } channels;
} Color_001CE430;

typedef struct Flags57_001CE430 {
    s8 unused : 6;
    s8 selected : 1;
    s8 unused7 : 1;
} Flags57_001CE430;

typedef struct Flags58_001CE430 {
    s8 hidden : 1;
    s8 unused : 7;
} Flags58_001CE430;

typedef struct Object_001CE430 {
    u8 pad0[0x30];
    s32 render;
    s16 x, z;
    u8 pad38[8];
    u8 cardX, cardZ;
    u8 pad42[2];
    u8 owner, state, model;
    u8 pad47[2];
    u8 moving, turning;
    u8 pad4B[4];
    u8 flags4F;
    u8 pad50;
    u8 status51;
    u8 pad52;
    u8 progress;
    u8 pad54[3];
    Flags57_001CE430 flags57;
    Flags58_001CE430 flags58;
} Object_001CE430;

typedef struct Info_001CE430 {
    u8 pad[0x14];
    s16 height;
} Info_001CE430;

typedef union Render_001CE430 {
    __int128 value;
    s32 words[4];
} Render_001CE430;

extern Color_001CE430 D_002914E0;
extern Color_001CE430 D_002914E8;
extern Color_001CE430 D_002914F0;
extern Render_001CE430 D_00291500;
extern u16 D_00318116;

s32 SzDuel_DrawUnit_Pipe(s32 arg0) {
    extern f32 SzModel_GetAnimFrame();
    extern s32 SzGame_GetMode();
    u32 mode;
    Color_001CE430 *tint;
    f32 position[4];
    Render_001CE430 render;
    Color_001CE430 ownColor, otherColor, warningColor;
    u8 *game;
    f32 *pos;
    u8 *player;
    s32 row, column;
    Object_001CE430 *object;
    s32 selected;
    s32 model;
    Info_001CE430 *info;
    s32 extraModel, extra;
    u8 alpha;
    f32 fade;

    game = D_00317490.b;
    player = D_00317490.b + D_003181E4 * 0x350;
    mode = SzGame_GetMode(1);
    alpha = (u8)((((s32)D_00318116 >> 8) & 0xFF) + 0x40);
    ownColor = D_002914E0;
    ownColor.channels.r = D_003181E4 == 0 ? 0 : 0x60;
    ownColor.channels.g = game[0xD54] == 0 ? 0 : 0x60;
    ownColor.channels.b = game[0xD54] == 0 ? 0x80 : 0x60;
    ownColor.channels.a = alpha;
    otherColor = D_002914E8;
    otherColor.channels.r = game[0xD54] == 0 ? 0x60 : 0;
    otherColor.channels.g = game[0xD54] == 0 ? 0x60 : 0;
    otherColor.channels.b = game[0xD54] == 0 ? 0x60 : 0x80;
    otherColor.channels.a = alpha;
    warningColor = D_002914F0;
    warningColor.channels.r = game[0xD54] == 0 ? 0x60 : 0x60;
    warningColor.channels.g = game[0xD54] == 0 ? 0 : 0x80;
    warningColor.channels.b = game[0xD54] == 0 ? 0x80 : 0;
    warningColor.channels.a = alpha;
    tint = NULL;
    pos = NULL;
    fade = (f32)(u32)(u8)SzEffect_GetBlackOutForMonster() / 128.0f;
    SzEffect_SetIntensityOnly(4, fade);
    SzEffect_SetIntensityOnly(5, fade);
    if (mode == 1) {
        Object_001CE430 *target;
        target = (Object_001CE430 *)SzDuel_GetMapUnit(player[0x33D], player[0x33E]);
        if (target != NULL && target->owner != game[0xD54]) {
            tint = &otherColor;
        } else {
            tint = &ownColor;
        }
        if (game[0xD57] >= 0x1D) {
            tint = &warningColor;
        }
    }
    if (mode < 2U) {
        pos = position;
    }
    row = 0;
    do {
        column = 0;
        do {
            object = (Object_001CE430 *)SzDuel_GetUnit(row, column);
            selected = 0;
            render = D_00291500;
            if (object != NULL) {
                model = object->model;
                if (SzModel_IsModelDisp(model) != 0 &&
                    (object->state == 0 || object->status51 != 0 || object->progress != 0)) {
                    info = (Info_001CE430 *)SzDuel_GetMapInfo(object->cardX, object->cardZ);
                    if (mode == 1 && game[0xD38] == 0) {
                        Object_001CE430 *target;
                        if (object->moving != 0 || object->turning != 0) {
                            if ((u32)func_001A23B0(SzModel_GetAnimFrame(model)) < 2U) {
                                SzModel_SetAnimDir(model, 0);
                            }
                        } else {
                            SzModel_SetAnimDir(model, 1);
                        }
                        target = *(Object_001CE430 **)(game + 0x6C8);
                        if (target != NULL) {
                            if (target == object) {
                                selected = 1;
                            } else if (target->flags57.selected &&
                                       *(Object_001CE430 **)(game + 0x6CC) != NULL &&
                                       *(Object_001CE430 **)(game + 0x6CC) == object) {
                                selected = 1;
                            }
                        }
                        if (selected == 0) {
                            SzDuel_TrimUnitDir1(object->owner, object->state);
                        }
                        render.words[1] = object->render;
                    }
                    if (pos != NULL) {
                        if (object->flags58.hidden) {
                            pos[2] = 0.0f;
                            pos[1] = 0.0f;
                            pos[0] = 0.0f;
                        } else {
                            s32 height;
                            u32 remaining;
                            height = info->height;
                            height = height > 0 ? height : 0;
                            pos[0] = (f32)object->x;
                            pos[1] = (f32)(height * 35) / 128.0f;
                            pos[2] = (f32)object->z;
                            if (object->flags4F & 4) {
                                remaining = 128 - object->progress;
                                remaining = (s32)remaining > 0 ? remaining : 0;
                                pos[1] -= (50.0f * (f32)remaining) / 128.0f;
                            }
                        }
                    }
                    if (selected) {
                        SzModel_SetFilter(model, 1, tint);
                    }
                    arg0 = SzModel_ExSort_Pipe(arg0, model, (s32)pos, (s32)&render, 0, 0, 0x80FFFFF6);
                    if (selected) {
                        SzModel_SetFilter(model, 1, NULL);
                    }
                }
            }
            column++;
        } while (column < 6);
        row++;
    } while (row < 2);
    extra = 0;
    do {
        extraModel = extra + 0x20;
        if (SzModel_IsModelDisp(extraModel)) {
            arg0 = SzModel_ExSort_Pipe(arg0, extraModel, NULL, NULL, 0, 0, 0x80FFFFF6);
        }
        extra++;
    } while (extra < 2);
    return arg0;
}

typedef struct Vec4_001CEA50 {
    f32 x, y, z, w;
} Vec4_001CEA50;

typedef struct Flags_001CEA50 {
    s8 unused : 4;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
} Flags_001CEA50;

typedef struct Draw_001CEA50 {
    u8 pad00[0x10];
    Vec4_001CEA50 position;
    u8 bounds[0x10];
    Vec4_001CEA50 color;
    u8 pad40[0x41];
    Flags_001CEA50 flags;
    u8 pad82[0xE];
} Draw_001CEA50;

extern Vec4_001CEA50 D_0031825C;
extern s32 D_00318270;

void SzDuel_DrawCardTest(void) {
    extern void SzDuel_ClearDrawCard();
    u8 matrix[0x60];
    Draw_001CEA50 draw;

    SzDuel_ClearDrawCard(&draw);
    draw.flags.enabled = 1;
    draw.flags.colored = 0;
    draw.flags.reserved = 0;
    SzDuel_InitCardInfo(matrix, SzDuel_Xax2New(D_00318270));
    Ex3d_GetLookVector((s32) draw.bounds);
    draw.position = D_0031825C;
    SzDuel_StartCardSession();
    draw.flags.horizontal = 1;
    SzDuel_GetCardNodeOnScreen(&draw, 0, -192.0f, 0.0f);
    SzDuel_SetupCard((s32) matrix, (s32) &draw);
    SzDuel_DrawCard((s32) &draw);
    draw.flags.horizontal = 0;
    SzDuel_GetCardNodeOnScreen(&draw, 0, 0.0f, -96.0f);
    SzDuel_SetupCard((s32) matrix, (s32) &draw);
    SzDuel_DrawCard((s32) &draw);
    draw.flags.horizontal = 1;
    Ex3d_GetPointOnScreen(&draw, 192.0f, 0.0f);
    SzDuel_SetupCard((s32) (SzDuel_GetCardNode(&draw, 1) ? matrix : NULL), (s32) &draw);
    SzDuel_DrawCard((s32) &draw);
    draw.flags.horizontal = 0;
    Ex3d_GetPointOnScreen(&draw, 0.0f, 96.0f);
    SzDuel_SetupCard((s32) (SzDuel_GetCardNode(&draw, 1) ? matrix : NULL), (s32) &draw);
    SzDuel_DrawCard((s32) &draw);
    if (SzPad_Check(0, 1, 0x80) != 0) {
        draw.flags.colored = 1;
        draw.color.x = 0.46875f;
        draw.color.y = 0.489130437f;
        draw.color.z = 1.0f;
        draw.color.w = 0.0f;
        draw.flags.horizontal = 1;
        Ex3d_GetPointOnScreen(&draw, 0.0f, 96.0f);
        SzDuel_SetupCard((s32) (SzDuel_GetCardNode(&draw, 1) ? matrix : NULL), (s32) &draw);
        SzDuel_DrawCard((s32) &draw);
    }
    SzDuel_FinishCardSession();
}

typedef struct Record_001CECF0 {
    u8 padding[0x33C];
    u8 kind;
    u8 low;
    u8 high;
    u8 tail[0x11];
} Record_001CECF0;

extern s32 (*D_002BAEB0[])(u16, void *);
extern s8 D_0034F700;
extern s8 D_0034F708;

s32 lSzDuel_GetControl(s32 arg0, s32 arg1) {
    u8 *base = D_00317490.b;
    s32 ret = 0;
    Record_001CECF0 *record = (Record_001CECF0 *)(D_00317490.b + arg0 * 0x350);
    void *selected;
    s32 result;

    switch (record->kind) {
    case 0x64:
        ret = SzPad_Check(0, arg1, 0xFFFF) & 0xFFFF;
        break;
    case 0x65:
        ret = SzPad_Check(1, arg1, 0xFFFF) & 0xFFFF;
        break;
    default:
        if (record->kind < 0x64) {
            selected = record;
            if (TaTuto_IsTuto(arg0) != 0) {
                selected = base;
            }
            if (SzView_InqRequest(-1, -1) == NULL) {
                result = D_002BAEB0[record->kind]((u16)((record->high << 8) | record->low), selected);
                if (result < 0) {
                    if (D_0034F700 != 0) {
                        if (result == -1) {
                            Taku_Camp_Go_Rensyu_Duel(1);
                        } else {
                            D_0034F700 = 0;
                            D_0034F708 = 1;
                            SzGame_Pop();
                        }
                    } else {
                        SzGame_Pop();
                    }
                } else {
                    ret = result & 0xFFFF;
                }
            }
        }
        break;
    }
    return ret;
}
