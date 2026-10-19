/* The duel screen, part 2 of 12: windows, hand cards, dialogs, the info panels, fonts, join fades. */

#include "common.h"

/* Starts drawing duel windows (palette 0). */
s32 SzDuel_StartWindowSession_Pipe(s32 packet) {
    return SzDuel_StartWindowSessionWithPalette_Pipe(packet, 0);
}

/* Starts drawing duel windows: loads the window texture and font with palette `palette`. */
s32 SzDuel_StartWindowSessionWithPalette_Pipe(s32 packet, s32 palette) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzText_InitClutManage(s32, s32);
    u8 *base;
    s32 addr;
    s32 length;
    s32 i;

    base = duelState.b;
    addr = RhBase_GetUserGsAddress();
    addr += SzText_InitClutManage(addr, 2);
    packet = SzMsg_Init_Pipe(packet, palette, addr, &length);
    i = 0;
    addr += length;
    do {
        *(s32 *)(base + i * 4 + 0x6A0) = 0;
        i++;
    } while (i < 9);
    *(s32 *)(base + 0x6B8) = SzText_LoadRequest(3, 6);
    *(s32 *)(base + 0x6BC) = SzText_LoadRequest(3, 7);
    packet = SzText_DoRequest_Pipe(packet, 3, addr, &length);
    addr += length;
    SzText_FreeRequest(3, -1);
    {
        s32 *info;

        packet = SzMsg_LoadFont_Pipe(packet, 0, 0x15, 0, 0);
        info = SzMsg_GetInfo(0);
        info[3] = 0x16;
        packet = RhText_SetTextureFlush(packet);
    }
    *(s32 *)(base + 0xC7C) = addr;
    *(s32 *)(base + 0xC58) = 0xFFFFF8;
    SzMsg_SetDefPrioZ(0xFFFFF8);
    return packet;
}

/* Ends drawing duel windows. */
s32 SzDuel_FinishWindowSession_Pipe(s32 packet) {
    SzMsg_Free(0);
    return packet;
}

typedef struct {
    u8 pad[0x6A0];
    s32 entries[8];
} Data_001AF140;

/* The address of duel window texture `index` (0..7), or 0. */
s32 SzDuel_GetWindowTexture(s32 index) {
    Data_001AF140 *data = (Data_001AF140 *)duelState.b;

    if ((index < 0) || (index >= 8)) {
        return 0;
    }
    return data->entries[index];
}

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001AF180;

typedef struct {
    u8 r, g, b, a;
} Color_001AF180;

typedef struct {
    u8 pad00[4];
    Color_001AF180 color;
} Palette_001AF180;

struct CardNode_001AF180_s {
    f32 x, y;
    u8 pad08[0x3C];
    Color_001AF180 color;
    u8 pad48[0x39];
    Flags_001AF180 flags81;
    u8 pad82;
    Flags_001AF180 flags83;
    u8 pad84[0xC];
    s32 resource;
};

typedef struct {
    CardNode_001AF180 *object;
    u8 pad04[0xC];
    u8 tracks[2][0x10];
    u8 pad30[0x40];
    f32 scale;
    u8 pad74[0x24];
    u16 duration;
    u16 timer;
    u8 pad9C[3];
    Flags_001AF180 flags9F;
} Actor_001AF180;

s32 func_001D9F00(void *, s32);
extern u16 D_00318118;

/* Draws one card of the hand as the 3D card it is on screen. */
s32 SzDuel_DrawHandCard_Pipe(s32 packet, CardNode_001AF180 *object) {
    extern Palette_001AF180 sideColors[];
    u8 *state = duelState.b;
    s32 i;
    s32 id;
    Actor_001AF180 *actor;
    s32 resource;

    if (func_001AAF60(1) != 1) {
        return packet;
    }
    if (!((Flags_001AF180 *)(state + 0xD67))->bit2) {
        if (state[0xD45] == 0 && state[0xD47] == 0 && state[0xD48] == 0) {
            return packet;
        }
    }
    i = 5;
    do {
        id = state[0xD2C + i];
        actor = func_001CDE70(id);
        if (actor != NULL) {
            object = actor->object;
            if (object != NULL) {
                resource = object->resource;
                if (!object->flags83.bit6) {
                    if (id != 0) {
                        if (state[0xD47] == 0 && state[0xD4F] == id - 1) {
                            object->color = sideColors[state[0xD3C]].color;
                            object->color.a = D_00318118 >> 8;
                        } else {
                            object->color.a = 0;
                        }
                    }
                    if (actor->flags9F.bit6) {
                        s32 phase;
                        f32 difference = actor->scale - 0.1f;
                        u32 color;
                        f32 progress;
                        extern u32 Ex3d_GetSampleZ(f32, void *);
                        difference = difference >= 0.0f ? difference : -difference;
                        phase = difference <= 0.000001f ? 0 : 1;
                        color = Ex3d_GetSampleZ(30.0f, actor->tracks[phase]);
                        progress = (f32)(u32)actor->timer / (f32)(u32)actor->duration;
                        if (phase != 0) {
                            progress = 1.0f - progress;
                        }
                        func_001D9ED0((u32)((f32)color * (1.0f - progress) + 16777210.0f * progress));
                    } else {
                        func_001D9ED0(0xFFFFFA);
                    }
                    if (actor->flags9F.bit2) {
                        func_001DA2B0(object, 1, object->x, object->y);
                        packet = func_001DBC40(packet, resource, object);
                    } else {
                        s32 result = func_001D9F00(object, 1);
                        resource = result ? resource : 0;
                        packet = func_001DBC40(packet, resource, object);
                        if (0 != id) {
                            if (state[0xD47] != 0) {
                                if (((Flags_001AF180 *)(state + 0xD67))->bit4) {
                                    if (object->flags81.bit4 && result == 0) {
                                        object->flags81.bit4 = 0;
                                        object->flags81.bit6 = 0;
                                    }
                                } else {
                                    if (!object->flags81.bit4 && result == 0) {
                                        object->flags81.bit4 = 1;
                                        object->flags81.bit6 = 1;
                                    }
                                }
                            }
                        }
                    }
                    packet = func_0020A0B0(func_001DBD30(func_0020A0B0(packet, 1), (s32)object), 0);
                }
            }
        }
        i--;
    } while (i >= 0);
    return packet;
}

/* Draws the cursor over the hand card being picked, with its pick-order number. */
s32 SzDuel_DrawHandCursor_Pipe(s32 packet) {
    extern s32 SzGame_GetMode(s32);
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    extern u8 D_002902A6[];
    s32 mode;
    s32 player;
    u8 *state;
    f32 *pos;
    s32 count;
    s32 i;
    s32 x;
    s32 y;
    s32 kind;

    state = duelState.b;
    mode = SzGame_GetMode(1);
    player = duelState.s.turnOwner;
    count = SzDuel_GetHandCount(player);
    if (mode != 1) {
        return packet;
    }
    if (state[0xD45] == 0) {
        return packet;
    }
    if (state[0xD47] != 0) {
        return packet;
    }
    for (i = 0; i < count; i++) {
        pos = (f32 *)SzDuel_GetUnit(2, i + 1);
        if (pos != NULL) {
            pos = ((f32 **)pos)[1];
            if (pos != NULL) {
                x = (s32)pos[0] + 0x104;
                y = (s32)pos[1] + 0x8B;
                kind = SzDuel_InqHand(player, i);
                if (kind >= 0) {
                    if (state[0xD4F] == i) {
                        packet = lSzDuel_DrawWindow_Frame_Pipe(packet, -1, -1, 8, x, y - 4, 0xC, 0x13, 1);
                    }
                    if ((kind & 0xFFF) != 0x3E7) {
                        kind = (kind & 0xF000) >> 12;
                        if (kind != 0) {
                            packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_002902A6, x + 0x6C0, y + 0x704, 1, 1, 0, 0, 1, 0, -1);
                            packet = SzDuel_DrawWindow_FontDigit_Pipe(packet, x + 0x10, y - 0x17, 0, 2, 1, kind);
                        }
                    }
                }
            }
        }
    }
    return packet;
}

/* Draws the duel's dialog layer. */
void SzDuel_DrawDialog(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawDialog_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct Flags_001AF7E0 {
    s8 unused : 4;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
} Flags_001AF7E0;

typedef struct Draw_001AF7E0 {
    u8 pad00[0x30];
    s32 scale[4];
    u8 pad40[0x41];
    Flags_001AF7E0 flags;
    u8 pad82[0xE];
} Draw_001AF7E0;

typedef struct Card_001AF7E0 {
    u8 pad00[0x44];
    s8 owner;
    u8 pad45[0x1B];
} Card_001AF7E0;

extern char *D_00291130[];
extern u8 duelIcons[]; /* original: gSzDuel_Icon */
extern u8 D_00290828[];
extern u8 D_00290832[];
extern u8 D_00290AA8[];
extern u8 D_00290AB2[];
extern u8 D_00290AF8[];
extern u8 D_00290B02[];

/* Draws the duel's dialogs: card pick windows, messages and their cards. */
s32 SzDuel_DrawDialog_Pipe(s32 packetStart) {
    extern s32 lSzDuel_DrawDialog_Window_Pipe();
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 lSzDuel_DrawWindow_Board_Pipe();
    extern s32 func_001BDAF0();
    extern s32 SzMsg_LoadFont_Pipe();
    extern s32 SzMsg_DrawX_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern s32 SzData_GetRank();
    extern s32 lSzDuel_OpenHandCursor_Pipe();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern void SzDuel_ClearDrawCard();
    s32 x_c21;
    s32 x_c20;
    s32 y_c21;
    s32 y_c20;
    char *text_c12;
    s32 x_c12;
    s32 value_c21;
    s32 x_c18;
    s32 width_c21;
    s32 value_c20;
    s32 i_c18;
    s32 width_c20;
    char *text_c8;
    char *text_c7;
    s32 side_c7;
    s32 width;
    char *text1_c8;
    Card_001AF7E0 card;
    s32 y_c7;
    char *text2_c8;
    Draw_001AF7E0 draw;
    Draw_001AF7E0 draw2;
    s32 slot_c7;
    Card_001AF7E0 card2;
    s32 mode2;
    u8 *entry;
    u8 *state = duelState.b;
    s32 mode4;
    char *text;
    s32 x_c7;
    s32 index;
    u8 *p2;
    s32 lowB;
    u8 type;
    s32 icon;
    s32 extra_c9;
    s32 packet;
    char *text_c14;
    u16 *list;
    f32 scale;
    s32 y;
    s32 start;
    s32 page;
    s32 end;
    s32 cardId;
    s32 count;
    s32 value;
    s32 row;
    s32 side;
    s32 cursor;
    s32 on;
    s32 color;
    s32 x;
    s32 lowA;
    s32 dir;
    s32 w;
    s32 msg;
    s32 id;
    u8 *pic;
    u8 *p4;
    char *text1;
    char *text2;
    s32 y_c22;
    s32 value_c22_c22;
    s32 width_c22;
    s32 i;
    s32 side_c9;
    s32 id_c9;
    s32 res;

    index = count = 0;
    for (; index < 4; index++) {
        if (state[index + 0xCB2] != 0x18) {
            count++;
        }
    }
    if (count == 0) {
        return packetStart;
    }
    packet = SzDuel_StartWindowSessionWithPalette_Pipe(packetStart, 0);
    SzDuel_SetWindowDefPrioZ(0xFFFFFE);
    SzMsg_SetDefPrioZ(0xFFFFFE);
    for (index = 0, p4 = state, p2 = state; index < 4; p4 += 4, index++, p2 += 2) {
        type = state[index + 0xCB2];
        if (type == 0x18) {
            continue;
        }
        switch (type) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            side = state[0xD54];
            text = D_00291130[type];
            y = 0x200 - ((*(s16 *)(p4 + 0xC9C) << 9) >> 6);
            cardId = *(u16 *)(p2 + 0xCAA);
            color = side | 0x8000;
            if (type == 2U || type == 3U || type == 4U || type == 5U) {
                cardId = -1;
            }
            if (type == 6) {
                cardId = -1;
                side = 2;
            }
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, side, color, cardId, 0x140, y + 0x80, 0x15A, 0, func_0019BEF0(text), (s32)text, 1);
            break;
        case 7:
            y_c7 = *(s16 *)(p4 + 0xC9C);
            x_c7 = y_c7 + 0xD9;
            text_c7 = D_00291130[type];
            slot_c7 = state[0xD35];
            side_c7 = state[0xD54];
            mode2 = state[0xD36] & 2;
            mode4 = state[0xD36] & 4;
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, side_c7, -1, -1, 0x140, y_c7 + 0x94, 0x234, 0x98, func_0019BEF0(text_c7), (s32)text_c7, 0);
            packet = SzMsg_LoadFont_Pipe(packet, 4, 0x73, 0, 0x58);
            packet = SzMsg_LoadFont_Pipe(packet, 5, 0x77, 0, 0x6E);
            packet = SzMsg_LoadFont_Pipe(packet, 6, 0x78, 0, 0x84);
            packet = SzMsg_LoadFont_Pipe(packet, 7, 0x74, 0, 0x9A);
            packet = SzMsg_LoadFont_Pipe(packet, 8, 0x7A, 0, 0xB0);
            packet = SzMsg_LoadFont_Pipe(packet, 9, 0x79, 0, 0xC6);
            packet = RhText_SetTextureFlush(packet);
            packet = SzMsg_DrawX_Pipe(packet, 4, 0x3E, x_c7, 0, SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 5, 0x11A, x_c7, (s32)(mode2 != 0 ? NULL : D_002BE944), SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 6, 0x1BA, x_c7, (s32)(mode2 != 0 ? D_002BE944 : NULL), SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 7, 0x3E, x_c7 + 0x28, 0, SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 8, 0x11A, x_c7 + 0x28, (s32)(mode4 != 0 ? NULL : D_002BE944), SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 9, 0x1BA, x_c7 + 0x28, (s32)(mode4 != 0 ? D_002BE944 : NULL), SzMsg_DrawRect_Pipe);
            SzMsg_Free(1);
            SzMsg_Free(2);
            SzMsg_Free(3);
            SzMsg_Free(4);
            SzMsg_Free(5);
            SzMsg_Free(6);
            SzMsg_Free(7);
            SzMsg_Free(8);
            SzMsg_Free(9);
            packet = lSzDuel_DrawWindow_Frame_Pipe(packet, -1, -1, 7, 0x3E, x_c7 + slot_c7 * 0x28, -0x204, -0x16, 1);
            break;
        case 8:
            side = state[0xD54];
            text_c8 = D_00291130[type];
            text1_c8 = D_002BEF6F;
            text2_c8 = D_002BEF73;
            y = 0x200 - ((*(s16 *)(p4 + 0xC9C) << 9) >> 6);
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, side, -1, 0x7B, 0x140, y + 0x9F, 0x15A, 0x82, func_0019BEF0(text_c8), (s32)text_c8, 0);
            res = SzDuel_DrawWindow_Font_Pipe(packet, 0xEA, y + 0xFD, 2, 3, func_0019BEF0(text1_c8), text1_c8, state[0xD35] != 0 ? 0 : (s32)D_002BE944);
            packet = SzDuel_DrawWindow_Font_Pipe(res, 0x196, y + 0xFD, 2, 3, func_0019BEF0(text2_c8), text2_c8, state[0xD35] != 0 ? (s32)D_002BE944 : 0);
            break;
        case 9:
        case 10:
            value = *(u16 *)(p2 + 0xCAA);
            text = D_00291130[type + ((value & 0x4000) ? 1 : 0)];
            y = 0x200 - ((*(s16 *)(p4 + 0xC9C) << 9) >> 6);
            id_c9 = value & 0x3FFF;
            if (value & 0x8000) {
                side_c9 = 1;
            } else {
                side_c9 = 0;
            }
            msg = (value & 0x4000) ? 0x60 : 0x5F;
            icon = SzDuel_GetMsgName(id_c9);
            extra_c9 = SzData_GetRank(side_c9, id_c9);
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, side_c9, id_c9, icon, 0x140, y + 0x4C, -0x1CC, 0x128, func_0019BEF0(text), (s32)text, 1);
            packet = SzMsg_LoadFont_Pipe(packet, 1, extra_c9 + 0x52, 0, 0x16);
            packet = SzMsg_LoadFont_Pipe(packet, 2, msg, 0, 0x2C);
            packet = RhText_SetTextureFlush(packet);
            SzMsg_GetInfo(1);
            packet = SzMsg_DrawX_Pipe(packet, 2, 0x140 - (*(s32 *)((u8 *)SzMsg_GetInfo(2) + 0xC) >> 1), y + 0x136, 0, SzMsg_DrawRect_Pipe);
            SzMsg_Free(1);
            SzMsg_Free(2);
            break;
        case 11:
            value = *(u16 *)(p2 + 0xCAA);
            text = D_00291130[type];
            y = 0x200 - ((*(s16 *)(p4 + 0xC9C) << 9) >> 6);
            icon = SzDuel_GetMsgName(value);
            width = 0x15A;
            res = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(SzMsg_LoadFont_Pipe(packet, 2, icon, 0, 0x16), 3, 0x98, 0, 0x2C));
            w = *(s32 *)((u8 *)SzMsg_GetInfo(2) + 0xC) + 0x18;
            if (w > 0x15A) {
                width = w;
            }
            w = *(s32 *)((u8 *)SzMsg_GetInfo(3) + 0xC) + 0x18;
            if (width < w) {
                width = w;
            }
            packet = lSzDuel_DrawDialog_Window_Pipe(res, 2, -1, -1, 0x140, y + 0x32, width, 0x15C, func_0019BEF0(text), (s32)text, 1);
            packet = SzMsg_DrawX_Pipe(packet, 2, 0x140 - (*(s32 *)((u8 *)SzMsg_GetInfo(2) + 0xC) >> 1), y + 0x12E, 0, SzMsg_DrawRect_Pipe);
            packet = SzMsg_DrawX_Pipe(packet, 3, 0x140 - (*(s32 *)((u8 *)SzMsg_GetInfo(3) + 0xC) >> 1), y + 0x150, 0, SzMsg_DrawRect_Pipe);
            SzMsg_Free(2);
            SzMsg_Free(3);
            SzDuel_InitCardInfo(&card, value);
            SzDuel_ClearDrawCard(&draw);
            draw.scale[0] = 0x3EF00000;
            draw.scale[1] = 0x3EFA6F4E;
            draw.scale[2] = 0x3F800000;
            draw.scale[3] = 0;
            draw.flags.reserved = 0;
            SzMsg_Free(0);
            packet = SzDuel_StartCardSession_Pipe(packet);
            SzDuel_SetCardDefPrioZ(0xFFFFFE);
            SzDuel_GetCardNodeOnScreen(&draw, 0, 0.0f, (f32)(y - 0x18));
            packet = SzDuel_DrawCard_Pipe(SzDuel_SetupCard2_Pipe(packet, (s32)&card, &draw), (s32)&draw);
            packet = SzDuel_StartWindowSessionWithPalette_Pipe(SzDuel_FinishCardSessionX_Pipe(packet), 0);
            SzDuel_SetWindowDefPrioZ(0xFFFFFE);
            SzMsg_SetDefPrioZ(0xFFFFFE);
            break;
        case 12:
        case 13:
            value = *(u16 *)(p2 + 0xCAA);
            x_c12 = *(s16 *)(p4 + 0xC9A);
            text_c12 = D_00291130[type];
            y = *(s16 *)(p4 + 0xC9C);
            icon = SzDuel_GetMsgName(value);
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, 2, value, icon, x_c12 + 0x140, y + 0x4C, 0x15A, 0x128, func_0019BEF0(text_c12), (s32)text_c12, 1);
            packet = SzMsg_LoadFont_Pipe(packet, 1, 0x99, 0, 0x16);
            packet = RhText_SetTextureFlush(packet);
            entry = (u8 *)SzMsg_GetInfo(1);
            packet = SzMsg_DrawX_Pipe(packet, 1, (0x140 - (*(s32 *)(entry + 0xC) >> 1)) + x_c12, y + 0x136, 0, SzMsg_DrawRect_Pipe);
            SzMsg_Free(1);
            break;
        case 14:
            text_c14 = D_00291130[type];
            lowA = SzDuel_GetPlayer(0);
            lowB = SzDuel_GetPlayer(1);
            lowA = (lowA & 0xFF) < 0x64 ? 1 : 0;
            lowB = (lowB & 0xFF) < 0x64 ? 1 : 0;
            y = 0x200 - ((*(s16 *)(p4 + 0xC9C) << 9) >> 6);
            on = (state[0xD36] & 0x80) ? 1 : 0;
            page = state[0xD36] & 0x7F;
            start = page != 0 ? *(u16 *)(state + 0xC8E) : *(u16 *)(state + 0xC8A);
            end = page != 0 ? *(u16 *)(state + 0xC90) : *(u16 *)(state + 0xC8C);
            cursor = page != 0 ? state[0xD5F] : state[0xD5E];
            list = page != 0 ? *(u16 **)(state + 0x6DC) : *(u16 **)(state + 0x6D8);
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, 2, -1, -1, 0x140, y + 0x68, 0x15A, 0xF0, func_0019BEF0(text_c14), (s32)text_c14, 0);
            if (on != 0) {
                w = y + 0x7BE;
                if (page == 0) {
                    packet = lSzDuel_DrawWindow_Icon_Pipe(packet, duelIcons + (lowA + 0xB9) * 10, 0x7E8, w, 0, 1, 0, 0, 1, 0, 1);
                } else {
                    packet = lSzDuel_DrawWindow_Icon_Pipe(packet, duelIcons + (lowB + 0xBB) * 10, 0x7E8, w, 0, 1, 0, 0, 1, 0, 1);
                }
            } else {
                dir = page == 0 ? 1 : -1;
                packet = lSzDuel_DrawWindow_Icon_Pipe(packet, duelIcons + (lowA + 0xB9) * 10, 0x7B8, y + 0x7BE, 0, 1, 0, 0, (page == 0 ? 1 : 0), 0, dir);
                packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290B02, 0x7F1, y + 0x7C3, 0, 1, 0, 0, 1, 0, -1);
                packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290AF8, 0x804, y + 0x7C3, 0, 1, 0, 0, 1, 0, -1);
                w = y + 0x7BE;
                if (page == 1) {
                    dir = 1;
                } else {
                    dir = -1;
                }
                packet = lSzDuel_DrawWindow_Icon_Pipe(packet, duelIcons + (lowB + 0xBB) * 10, 0x818, w, 0, 1, 0, 0, (page == 1 ? 1 : 0), 0, dir);
            }
            packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290828, 0x867, y + 0x7C2, 0, 1, 0, 0, 1, 0, -1);
            packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290AA8, 0x88B, y + 0x7C7, 0, 1, 0, 0, 1, 0, -1);
            packet = lSzDuel_DrawWindow_Board_Pipe(packet, page + 0xE, 0xB4, y + 0xB8, -0x118, -0x7E, page + 0xE);
            packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290832, 0x867, y + 0x85C, 0, 1, 0, 0, 1, 0, -1);
            packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290AB2, 0x88B, y + 0x85C, 0, 1, 0, 0, 1, 0, -1);
            for (i = 0, w = y + 0xBB; i < 5 && start + i < end; w += 0x18, i++) {
                id = list[start + i];
                entry = SzDuel_GetCardConstInfo(id);
                if (entry != NULL) {
                    msg = *entry >> 5;
                    value = *entry & 0x1F;
                    if (msg == 0) {
                        pic = duelIcons + value * 10;
                    } else {
                        pic = duelIcons + (msg + 0x14) * 10;
                    }
                    scale = 1.0f;
                    packet = SzMsg_LoadFont_Pipe(packet, 1, SzDuel_GetMsgName(id), 0, 0x16);
                    packet = RhText_SetTextureFlush(packet);
                    packet = lSzDuel_DrawWindow_Icon_Pipe(packet, pic, 0x777, w + 0x720, 0, 1, 0, 0, 1, 0, -1);
                    width = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0xC);
                    if (width > 0xFA) {
                        scale = 250.0f / (f32)width;
                    }
                    packet = SzMsg_DrawRatioX_Pipe(packet, 1, 0xCF, w, scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
                    SzMsg_Free(1);
                }
            }
            if (end != 0) {
                w = y + 0xBB;
                w += cursor * 0x18;
                packet = lSzDuel_DrawWindow_Frame_Pipe(packet, -1, -1, 7, 0xB7, w, -0x112, -0x18, 1);
            }
            break;
        case 15:
        case 16:
            x = *(s16 *)(p4 + 0xC9A);
            y = *(s16 *)(p4 + 0xC9C);
            text = D_00291130[type];
            value = *(u16 *)(p2 + 0xCAA);
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, 2, -1, value, x + 0x140, y + 0xE0, 0, 0, func_0019BEF0(text), (s32)text, 0);
            break;
        case 17:
            y = 0x200 - ((state[0xD3A] << 9) >> 6);
            if (state[0xD35] == 24) {
                value = *(u16 *)(*(u8 **)(state + 0x6C8) + 0x3C);
                state[0xD5C] = *(u8 *)(*(u8 **)(state + 0x6C8) + 0x44);
            } else if (state[0xD35] == 45) {
                value = *(u16 *)(p2 + 0xCAA);
                state[0xD5C] = state[0xD36] & 0x7F;
            } else if (state[0xD35] == 48) {
                value = *(u16 *)(p2 + 0xCAA);
                state[0xD5C] = state[0xD36] & 0x7F;
            } else {
                value = SzDuel_InqHand(state[0xD54], state[0xD4F]);
                if (value < 0) {
                    value = 0x3E7;
                } else {
                    value &= 0xFFF;
                }
                state[0xD5C] = state[0xD54];
            }
            packet = func_001BDAF0(packet, value, -0x1E0, y, 1, 1, 1, 0);
            break;
        case 18:
            x_c18 = *(s16 *)(p4 + 0xC9A);
            y = *(s16 *)(p4 + 0xC9C);
            value = *(u16 *)(p2 + 0xCAA);
            SzMsg_Free(0);
            packet = SzDuel_StartCardSession_Pipe(packet);
            SzDuel_SetCardDefPrioZ(0xFFFFFE);
            SzDuel_ClearDrawCard(&draw2);
            row = -0xFA;
            draw2.flags.horizontal = 0;
            draw2.flags.colored = 0;
            for (i_c18 = 0; i_c18 < 5; i_c18++) {
                id = SzDuel_InqHand(value, i_c18);
                if (id >= 0) {
                    id &= 0xFFF;
                    if (id != 0x3E7) {
                        SzDuel_InitCardInfo(&card2, id);
                        card2.owner = value;
                        SzDuel_GetCardNodeOnScreen(&draw2, 0, (f32)(x_c18 + row), (f32)y);
                        packet = SzDuel_DrawCard_Pipe(SzDuel_SetupCard2_Pipe(packet, (s32)&card2, &draw2), (s32)&draw2);
                    }
                }
                row += 0x7D;
            }
            packet = SzDuel_StartWindowSessionWithPalette_Pipe(SzDuel_FinishCardSessionX_Pipe(packet), 0);
            SzDuel_SetWindowDefPrioZ(0xFFFFFE);
            SzMsg_SetDefPrioZ(0xFFFFFE);
            break;
        case 19:
            packet = lSzDuel_DrawDialog_Window_Pipe(packet, -1, -1, *(u16 *)(p2 + 0xCAA), *(s16 *)(p4 + 0xC9A) + 0x140, *(s16 *)(p4 + 0xC9C) + 0xE0, 0, 0, 0, 0, 0);
            break;
        case 20:
            value_c20 = *(u16 *)(p2 + 0xCAA);
            x_c20 = *(s16 *)(p4 + 0xC9A);
            y_c20 = *(s16 *)(p4 + 0xC9C);
            res = SzMsg_LoadFont_Pipe(packet, 1, value_c20, 0, 0x16);
            res = RhText_SetTextureFlush(res);
            width_c20 = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0x10) + 0x18;
            SzMsg_Free(1);
            packet = lSzDuel_DrawDialog_Window_Pipe(res, -1, -1, value_c20, x_c20 + 0x140, (0xE0 - (width_c20 / 2)) + y_c20, 0, width_c20, 0, 0, 0);
            break;
        case 21:
            value_c21 = *(u16 *)(p2 + 0xCAA);
            x_c21 = *(s16 *)(p4 + 0xC9A);
            y_c21 = *(s16 *)(p4 + 0xC9C);
            res = SzMsg_LoadFont_Pipe(packet, 1, value_c21, 0, 0x16);
            res = RhText_SetTextureFlush(res);
            width_c21 = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0x10) + 0x34;
            SzMsg_Free(1);
            packet = lSzDuel_DrawDialog_Window_Pipe(res, -1, -1, value_c21, x_c21 + 0x140, (0xE0 - (width_c21 / 2)) + y_c21, 0, width_c21, 0, 0, 1);
            break;
        case 22:
            text1 = D_002BEF6F;
            y_c22 = *(s16 *)(p4 + 0xC9C);
            text2 = D_002BEF73;
            value_c22_c22 = *(u16 *)(p2 + 0xCAA);
            res = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, value_c22_c22, 0, 0x16));
            width_c22 = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0x10) + 0x3C;
            SzMsg_Free(1);
            packet = lSzDuel_DrawDialog_Window_Pipe(res, 2, -1, value_c22_c22, 0x140, (0xE0 - (width_c22 >> 1)) + y_c22, 0x15A, width_c22, 0, 0, 0);
            res = SzDuel_DrawWindow_Font_Pipe(packet, 0xEA, (width_c22 >> 1) + 0xBC + y_c22, 2, 3, func_0019BEF0(text1), text1, state[0xD35] != 0 ? 0 : (s32)D_002BE944);
            packet = SzDuel_DrawWindow_Font_Pipe(res, 0x196, (width_c22 >> 1) + 0xBC + y_c22, 2, 3, func_0019BEF0(text2), text2, state[0xD35] != 0 ? (s32)D_002BE944 : 0);
            break;
        case 23:
            packet = lSzDuel_OpenHandCursor_Pipe(packet, *(u16 *)(p2 + 0xCAA), *(s16 *)(p4 + 0xC9A), *(s16 *)(p4 + 0xC9C));
            break;
        }
    }
    SzMsg_Free(0);
    return packet;
}

/* Draws a dialog window at (x, y), at least width x height (a negative width keeps it fixed), with an optional
   title font and text. */
s32 lSzDuel_DrawDialog_Window_Pipe(s32 packet, s32 side, s32 image, s32 font, s32 x, s32 y, s32 width, s32 height,
                  s32 textLength, s32 text, s32 fitText) {
    extern u8 duelIcons[];
    extern s32 func_001B3C80();
    extern s32 func_001B4780();
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    u8 *state;
    s32 frame;
    s32 flip;
    s32 card;
    s32 textW;
    s32 textH;
    s32 minW;
    s32 minH;
    s32 id;
    s32 *info;
    f32 scale;
    s32 nw;

    state = duelState.b;
    frame = (u32)func_001A8720() / 5;
    if (width < 0) {
        flip = 1;
    } else {
        flip = 0;
    }
    card = (image >= 0x8000) ? 1 : 0;
    scale = 1.0f;
    width = Abs(width);
    if (card) {
        image -= 0x8000;
    }
    if (textLength > 0) {
        func_001B76E0(2, 3, textLength, (s8 *)text, &textW, &textH);
        textW += 0x18;
        textH += 0xC;
    } else {
        textH = 0;
        textW = 0;
    }
    if (font >= 0) {
        packet = func_001FD680(packet, 1, font, 0, 0x16);
        packet = func_0020F290(packet);
        info = func_001FEAB0(1);
        if (flip) {
            if (width - 0x18 < info[3]) {
                scale = (f32)(width - 0x18) / (f32)info[3];
            }
            minW = width;
        } else {
            minW = ((info[3] > textW) ? info[3] : textW) + 0x18;
        }
        minH = info[4] + ((textLength > 0) ? textH + 0x18 : 0xC) + 0xC;
    } else {
        minW = textW + 0x18;
        minH = (textLength > 0) ? textH + 0x18 : 0xC;
    }
    if (card) {
        minH += 0x3C;
    } else if (image >= 0) {
        minH += 0x8C;
    }
    if (fitText != 0) {
        minH += 0x1C;
    }
    if (width < minW) {
        width = minW;
    }
    if (height < minH) {
        height = minH;
    }
    nw = -width;
    (void)nw; /* keeps the negation at its own statement, ahead of the frame call's argument copies, as in the original */
    id = func_001B4780(packet, 0xD, -1, 1, x - (width >> 1) - 4, y, nw, -height, 1);
    if (textLength > 0) {
        id = func_001B4780(id, side, -1, 0xB, x - (textW >> 1), y + 0xC, -textW, -textH, 1);
        id = func_001B6F70(id, x, y + 0x14, 2, 3, textLength, (s8 *)text, 0);
    }
    if (card) {
        minW = x - 0x18;
        minH = y + ((textLength > 0) ? textH + 0x18 : 0xC);
        id = func_001B7F90(id, image, minW, minH, 0x30, 0x30, *(s32 *)(state + 0xC58), 1);
        id = func_001B4780(id, -1, -1, 4, minW, minH, 3, 6, 1);
    } else if (image >= 0) {
        id = func_001B7D60(id, image, x - 0x40, y + ((textLength > 0) ? textH + 0x18 : 0xC), 0x80, 0x80,
                           *(s32 *)(state + 0xC58));
    }
    if (font >= 0) {
        minW = x - (s32)((f32)info[3] * scale / 2.0f);
        minH = y + ((textLength > 0) ? textH + 0x18 : 0x10);
        if (card) {
            minH += 0x3C;
        } else if (image >= 0) {
            minH += 0x8C;
        }
        id = func_001FE660(id, 1, minW, minH, scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
        func_001FEAF0(1);
    }
    if (fitText != 0) {
        id = func_001B3C80(id, duelIcons + (frame % 3 + 0xBE) * 10, x + 0x6B8, y + 0x704 + height,
                           0, 1, 0, 0, 1, 0, -1);
    }
    return id;
}

/* Draws the duel's info windows. */
void SzDuel_DrawWindow(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawWindow_Pipe(RhBase_GetVifPacketArea()));
}

typedef int DotrDrawWord;
struct DotrWindowUnit {
    unsigned char unknown_00[64];
    unsigned char x;
    unsigned char y;
    unsigned char unknown_42[2];
    unsigned char side;
    unsigned char place;
    unsigned char unknown_46[17];
    signed char unknown_57_bit_0 : 1;
    signed char unknown_57_bits_1_3 : 3;
    signed char unknown_57_bit_4 : 1;
    signed char unknown_57_bit_5 : 1;
    signed char unknown_57_bit_6 : 1;
    signed char unknown_57_bit_7 : 1;
};
struct DotrWindowSide {
    unsigned char unknown_000[826];
    unsigned short points;
    unsigned char player;
    unsigned char x;
    unsigned char y;
    unsigned char unknown_33f[2];
    unsigned char hand;
    unsigned char unknown_342[4];
    signed char unknown_346_bit_0 : 1;
    signed char unknown_346_high : 7;
    unsigned char unknown_347[9];
};
struct DotrWindowControl {
    struct DotrWindowSide sides[2];
    unsigned char unknown_6a0[40];
    struct DotrWindowUnit *unit_6c8;
    struct DotrWindowUnit *unit_6cc;
    unsigned char unknown_6d0[1416];
    unsigned int unknown_c58;
    unsigned char unknown_c5c[217];
    unsigned char unknown_d35;
    unsigned char unknown_d36[6];
    unsigned char side;
    unsigned char unknown_d3d;
    unsigned char slide;
    unsigned char slide2;
    unsigned char x;
    unsigned char y;
    unsigned char x2;
    unsigned char y2;
    unsigned char unknown_d44;
    unsigned char unknown_d45;
    unsigned char unknown_d46;
    unsigned char unknown_d47;
    unsigned char unknown_d48;
    unsigned char unknown_d49[6];
    unsigned char unknown_d4f;
    unsigned char unknown_d50[3];
    unsigned char unknown_d53;
    unsigned char unknown_d54;
    unsigned char unknown_d55[2];
    unsigned char unknown_d57;
    unsigned char unknown_d58[13];
    signed char unknown_d65_low : 4;
    signed char unknown_d65_bit_4 : 1;
    signed char unknown_d65_high : 3;
    signed char unknown_d66_low : 3;
    signed char unknown_d66_bit_3 : 1;
    signed char unknown_d66_bits_4_6 : 3;
    signed char unknown_d66_bit_7 : 1;
    signed char unknown_d67_bit_0 : 1;
    signed char unknown_d67_bit_1 : 1;
    signed char unknown_d67_bit_2 : 1;
    signed char unknown_d67_bit_3 : 1;
    signed char unknown_d67_bit_4 : 1;
    signed char unknown_d67_high : 3;
};
extern struct DotrWindowControl D_00317490_b;
extern DotrDrawWord func_001B3790_b(DotrDrawWord cursor, int colour, int field, float f, int x, int y);
extern struct DotrWindowUnit *func_001DF540_b(int a, int b);
extern struct DotrWindowUnit *func_001E36E0_b(int x, int y);
extern DotrDrawWord func_001B3100_b(DotrDrawWord cursor, int a1, int a2, int a3);
extern DotrDrawWord func_001B4780_b(DotrDrawWord cursor, int a1, int a2, int a3, int x, int y, int a6, int a7, long a8);
extern DotrDrawWord func_001B6EA0_b(DotrDrawWord cursor, int x, int y, int a, int flags, int width, int value);

/* Draws the duel's info windows for the square under the cursor: player info, level, summon cost, card info, field. */
int SzDuel_DrawWindow_Pipe(int cursor)
{
    extern DotrDrawWord lSzDuel_DrawWindow_CardInfo_Pipe(DotrDrawWord cursor, struct DotrWindowUnit *unit, int x, int y,
        unsigned char side, int a5, int a6, int a7, long a8, long a9);
    struct DotrWindowControl *g = &D_00317490_b;
    int off;
    struct DotrWindowUnit *unit;
    struct DotrWindowUnit *other;
    int x;
    int y;
    int adv;
    DotrDrawWord out;
    struct DotrWindowSide *side;
    long first = 1;
    int adv2;
    int closing = D_00317490_b.unknown_d67_bit_0;
    int step = 8;
    struct DotrWindowSide *s;
    int v;
    int a;
    int px;
    int c1;
    int c2;
    int py;

    if (D_00317490_b.unknown_d67_bit_1) {
        return cursor;
    }
    if (g->unknown_d67_bit_2 || g->unknown_d45 != 0 || g->unknown_d47 != 0 || g->unknown_d48 != 0) {
        if (!g->unknown_d65_bit_4) {
            closing = 1;
            step = 16;
        }
    }
    if (closing) {
        v = g->slide - step;
        g->slide = v > 0 ? v : 0;
    } else {
        v = g->slide + step;
        g->slide = v < 128 ? v : 128;
        if (g->slide == 128) {
            g->side = g->unknown_d54;
            g->unknown_d3d = g->unknown_d53;
            g->unknown_d67_bit_0 = g->unknown_d66_bit_7;
            s = &g->sides[g->side];
            g->x = s->x;
            g->y = s->y;
        }
    }
    if (g->slide == 128) {
        return cursor;
    }
    off = g->slide << 7 >> 7;
    side = &g->sides[g->side];
    SzDuel_SetWindowDefPrioZ(0xfffff8);
    cursor = func_001B3790_b(cursor, g->side, SzDuel_GetField(side->x, side->y), 100.0f, g->side != 0 ? 6 : 538,
                                                off + 336);
    cursor = SzDuel_StartWindowSessionWithPalette_Pipe(cursor, 0);
    cursor = lSzDuel_DrawWindow_PlayerInfo_Pipe(cursor, 0, 18, 20 - off, g->side == 0 ? 1 : 0);
    out = lSzDuel_DrawWindow_PlayerInfo_Pipe(cursor, 1, 440, 20 - off, g->side == 1 ? 1 : 0);
    if (g->unknown_d45 != 0 || g->unknown_d47 != 0) {
        other = g->unit_6cc;
        unit = func_001DF540_b(2, g->unknown_d4f + 1);
        if (g->unknown_d67_bit_3 || (!g->unknown_d67_bit_4 && g->unknown_d47 != 0)) {
            v = g->slide2 - 16;
            g->slide2 = v > 0 ? v : 0;
        } else {
            v = g->slide2 + 16;
            g->slide2 = v < 128 ? v : 128;
        }
        

        if (!(g->unknown_d57 != 81 && g->unknown_d57 != 82 && g->unknown_d57 != 83)) {
            other = g->unit_6c8;
        } else if (g->unknown_d35 == 83) {
            if (!(g->unknown_d57 != 32 && g->unknown_d57 != 33 && g->unknown_d57 != 34)) {
                other = g->unit_6c8;
            }
        }
        a = g->slide2;
        if (a != 0) {
            out = lSzDuel_DrawWindow_CardInfo_Pipe(out, unit, side->x, side->y, unit != 0 ? (int)unit->side : (int)g->side, 104,
                                                   368 - ((unsigned char)a << 6 >> 7) + off, -1, 6, 1);
            first = 0;
        }
        out = lSzDuel_DrawWindow_CardInfo_Pipe(out, other, side->x, side->y, other != 0 ? (int)other->side : (int)g->side, 104,
                                               off + 368, -1, 3, first);
    } else {
        x = -1;
        adv = 1;
        y = -1;
        adv2 = 1;
        if (g->unit_6c8 != 0 && g->unit_6c8->place < 11 && g->unit_6cc != 0 && g->unit_6cc->place < 11) {
            c1 = Ta_IsUnitControl(g->unit_6c8->side, g->unit_6c8->place);
            c2 = Ta_IsUnitControl(g->unit_6cc->side, g->unit_6cc->place);
            if (c1 != c2) {
            adv = Ta_IsVisualAttrAdv(g->unit_6c8->side, g->unit_6c8->place, g->unit_6cc->side, g->unit_6cc->place);
            if (adv < 0) {
                adv2 = adv;
            } else {
                adv2 = 2 - adv;
            }
            }
        }
        px = side->x;
        py = side->y;
        if (g->unit_6c8 != 0 && g->unit_6c8->place < 11 && g->unit_6c8->unknown_57_bit_6) {
            g->x = px = g->unit_6c8->x;
            g->y = py = g->unit_6c8->y;
            if (side->x != px || side->y != py) {
                x = side->x;
                y = side->y;
                if (g->slide2 == 0) {
                    g->x2 = x;
                    g->y2 = y;
                }
            }
        } else if (g->unknown_d57 == 24 || g->unknown_d57 == 62 || g->unknown_d57 == 48) {
            g->x = px;
            g->y = py;
        }
        if (g->x2 == x && g->y2 == y && func_001E36E0_b(x, y) != 0) {
            v = g->slide2 + 16;
            g->slide2 = v < 128 ? v : 128;
        } else {
            v = g->slide2 - 16;
            g->slide2 = v > 0 ? v : 0;
        }
        if (g->slide2 != 0) {
            unit = func_001E36E0_b(g->x2, g->y2);
            out = lSzDuel_DrawWindow_CardInfo_Pipe(out, unit, g->x2, g->y2, unit != 0 ? (int)unit->side : (int)g->side, 104,
                                                   368 - (g->slide2 << 6 >> 7) + off, adv2, 3, 1);
            first = 0;
        }
        unit = func_001E36E0_b(g->x, g->y);
        out = lSzDuel_DrawWindow_CardInfo_Pipe(out, unit, side->x, side->y, unit != 0 ? (int)unit->side : (int)g->side, 104, off + 368,
                                               adv, 3, first);
    }
    cursor = func_001B3100_b(out, g->side, g->side != 0 ? 538 : 6, off + 336);
    cursor = lSzDuel_DrawWindow_Field_Pipe(cursor, SzDuel_GetField(side->x, side->y), g->side != 0 ? 6 : 538, off + 336);
    cursor = func_001B4780_b(cursor, 5, 3, 4, 292, 16 - off, 4, 2, 1);
    cursor = func_001B6EA0_b(cursor, 320, 22 - off, 2, 34, 2, 100 - g->unknown_d3d);
    if (g->unknown_d44 != 0) {
        cursor = lSzDuel_DrawWindow_DualShock2_Pipe(cursor, 320, 72 - off, (unsigned char)((unsigned char)g->unknown_d44 << 7 >> 7));
    }
    if (g->unknown_d48 != 0) {
        y = g->unknown_d45 << 7 >> 7;
        y = 54 - off + (y - 128);
        cursor = lSzDuel_DrawWindow_Level_Pipe(cursor, 220, y);
        cursor = lSzDuel_DrawWindow_SummonCost_Pipe(cursor, 332, y);
    }
    SzDuel_SetWindowDefPrioZ(0xfffffc);
    cursor = SzDuel_DrawHandCursor_Pipe(cursor);
    SzMsg_Free(0);
    return cursor;
}
extern u8 D_00290882[];
extern u8 D_002908E6[];
extern u8 D_0029094A[];
extern u8 D_00290954[];
extern u8 D_00290A1C[];
extern s8 D_002BEF76[];
#pragma opt_propagation off

/* Draws side `side`'s info window at (x, y): portrait, life points, summon power, deck count, monsters and spells
   on the board. */
s32 lSzDuel_DrawWindow_PlayerInfo_Pipe(s32 packet, s32 side, s32 x, s32 y, s32 visible) {
    s32 c0;
    s32 c1;
    s32 baseX;
    s32 screenX;
    s32 lowLevel;
    s32 playerOffset;
    extern s32 SzDuel_GetPlayer();
    extern s32 lSzDuel_DrawWindow_PicMini_Pipe();
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 SzDuel_DrawWindow_Digit_Pipe();
    extern s32 lSzDuel_DrawWindow_Board_Pipe();
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    u8 *playerData;
    u8 *data;
    s32 iconX;
    s32 valueX;
    s32 baseY;
    s32 iconY;
    s32 screenY;
    s32 rowX;
    s32 secondValueY;
    s32 lastX;
    s32 screenValueX;
    s32 numberX;
    s32 numberY;
    s32 screenRowX;
    s32 lastY;
    s32 lowerY;
    s32 hidden;
    s32 rowX2;

    data = duelState.b;
    playerData = duelState.b + side * 0x350;
    baseY = y + 3;
    baseX = x + 3;
    screenY = baseY + 0x720;
    hidden = 1;
    screenX = baseX + 0x6C0;
    if (playerData[0x33C] < 100) {
        lowLevel = 1;
    } else {
        lowLevel = 0;
    }
    if (SzDuel_GetPlayer(0) < 100 && SzDuel_GetPlayer(1) < 100) {
        hidden = 0;
    } else {
        if (SzDuel_GetPlayer(data[0xD3C]) >= 100) {
            if (data[0xD3C] == side) {
                hidden = 0;
            }
        } else if (data[0xD3C] != side) {
            hidden = 0;
        }
    }
    packet = lSzDuel_DrawWindow_Frame_Pipe(packet, side, side, 0, x - 13, y - 15, 37, 13, 1);
    iconX = x + 3 + (side != 0 ? 1 : 127);
    iconY = y + 4;
    packet = lSzDuel_DrawWindow_PicMini_Pipe(packet, side, iconX, iconY, 48, 48, *(s32 *)(data + 0xC58), visible);
    packet = lSzDuel_DrawWindow_Frame_Pipe(packet, -1, -1, 4, iconX, iconY, 3, 6, visible);
    playerOffset = side * 48;
    numberY = baseY + 6;
    rowX = baseX + playerOffset;
    numberX = rowX + 4;
    packet = lSzDuel_DrawWindow_Board_Pipe(packet, side, numberX, numberY, 12, 1, -1);
    packet = SzDuel_DrawWindow_Digit_Pipe(packet, numberX + 34, numberY + 2, 4, *(u16 *)(playerData + 0x33A), 0);
    iconX = screenX + (side != 0 ? 1 : 127);
    packet = lSzDuel_DrawWindow_Icon_Pipe(packet, (s32)(duelIcons + (lowLevel + (side * 2 + 185)) * 10), iconX, 48 + screenY, 0, 1, 0, 0, visible, 0, -1);
    screenRowX = screenX + playerOffset;
    valueX = screenRowX + 8;
    iconX = screenRowX + 8;
    iconY = screenY + 12;
    packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290A1C, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
    packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_002908E6, valueX, screenY + 36, 0, 1, 0, 0, 1, 0, -1);
    rowX2 = rowX + 26;
    iconX = rowX + 26;
    lowerY = baseY + 37;
    if (hidden != 0) {
        packet = SzDuel_DrawWindow_Font_Pipe(packet, iconX, lowerY, 0, 0, 2, D_002BEF76, 0);
    } else {
        packet = SzDuel_DrawWindow_FontDigit_Pipe(packet, iconX, lowerY, 0, 0, 2, playerData[0x341]);
    }
    screenValueX = screenRowX + 64;
    iconX = screenRowX + 64;
    packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_00290882, iconX, screenY + 36, 0, 1, 0, 0, 1, 0, -1);
    lastX = rowX + 82;
    lowerY = baseY + 37;
    packet = SzDuel_DrawWindow_FontDigit_Pipe(packet, lastX, lowerY, 0, 0, 2, SzDuel_GetDeckCount(side));
    c0 = lSzDuel_DrawWindow_Icon_Pipe(packet, D_0029094A, valueX, screenY + 52, 0, 1, 0, 0, 1, 0, -1);
    secondValueY = 53 + baseY;
    if (0 != hidden) {
        c0 = SzDuel_DrawWindow_Font_Pipe(c0, rowX2, secondValueY, 0, 0, 2, D_002BEF76, 0);
    } else {
        c0 = SzDuel_DrawWindow_FontDigit_Pipe(c0, rowX2, secondValueY, 0, 0, 2, SzDuel_GetUnitMonsterCount(side));
    }
    c1 = lSzDuel_DrawWindow_Icon_Pipe(c0, D_00290954, screenValueX, screenY + 52, 0, 1, 0, 0, 1, 0, -1);
    lastY = baseY + 53;
    if (hidden != 0) {
        c1 = SzDuel_DrawWindow_Font_Pipe(c1, lastX, lastY, 0, 0, 2, D_002BEF76, 0);
    } else {
        c1 = SzDuel_DrawWindow_FontDigit_Pipe(c1, lastX, lastY, 0, 0, 2, SzDuel_GetUnitSpellCount(side));
    }
    return c1;
}
#pragma opt_propagation reset

/* Draws the level window at (left, top). */
s32 lSzDuel_DrawWindow_Level_Pipe(s32 packet, s32 left, s32 top) {
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 lSzDuel_DrawWindow_Board_Pipe();
    extern s32 SzDuel_DrawWindow_Digit_Pipe();
    extern s32 SzMsg_GetInfo();
    extern s32 SzDuel_GetUnitLevel();
    extern s32 SzDuel_GetPlayer();
    extern s32 SzMsg_DrawX_Pipe();
    extern u8 D_002901CA[];
    u8 *global;
    s32 x;
    s32 xResult;
    s32 y;
    s32 yResult;
    s32 xCoord;
    s32 result;
    s32 temp;
    s32 flag;
    s32 areaX;
    s32 areaY;

    global = duelState.b;
    x = left + 3;
    y = top + 3;
    areaX = x + 0x6C0;
    areaY = y + 0x720;
    flag = 0;
    if (SzDuel_GetPlayer(WhoGoesFirst) < 0x20) {
        if (SzDuel_GetPlayer(global[0xD3C] ^ 1) >= 0x64) {
            flag = 1;
        }
    }

    packet = lSzDuel_DrawWindow_Frame_Pipe(packet, global[0xD54], -1, 6, left, top, 8, 3, (s64) 1);
    result = lSzDuel_DrawWindow_Icon_Pipe(packet, (s32) D_002901CA, areaX + 4, areaY + 3,
                           0, 1, 0, 0, 1, 0, -1);
    xCoord = x + 0x1E;
    yResult = y + 1;
    xResult = lSzDuel_DrawWindow_Board_Pipe(result, global[0xD54], xCoord, yResult, 3, 1, -1);
    if (flag != 0) {
        temp = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(xResult, 1, 0x1C, 0, 0x16));
        result = SzMsg_GetInfo(1);
        *(s32 *)(result + 0xC) = 0x2C;
        result = SzMsg_DrawX_Pipe(temp, 1, xCoord + 3, yResult + 2, 0, SzMsg_DrawRect_Pipe);
        SzMsg_Free(1);
    } else {
        temp = SzDuel_GetUnitLevel(2, global[0xD4F] + 1, 0);
        result = SzDuel_DrawWindow_Digit_Pipe(xResult, xCoord + 3, yResult + 2, 2, temp, 0);
    }
    return result;
}

/* Draws the summon-cost window at (left, top). */
s32 lSzDuel_DrawWindow_SummonCost_Pipe(s32 packet, s32 left, s32 top) {
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 lSzDuel_DrawWindow_Board_Pipe();
    extern s32 SzDuel_DrawWindow_Digit_Pipe();
    extern s32 SzMsg_GetInfo();
    extern s32 SzDuel_GetUnitLevel();
    extern s32 SzDuel_GetPlayer();
    extern s32 SzMsg_DrawX_Pipe();
    u8 *global;
    s32 x;
    s32 xResult;
    s32 y;
    s32 yResult;
    s32 xCoord;
    s32 result;
    s32 temp;
    s32 flag;
    s32 areaX;
    s32 areaY;

    global = duelState.b;
    x = left + 3;
    y = top + 3;
    areaX = x + 0x6C0;
    areaY = y + 0x720;
    flag = 0;
    if (SzDuel_GetPlayer(WhoGoesFirst) < 0x20) {
        if (SzDuel_GetPlayer(global[0xD3C] ^ 1) >= 0x64) {
            flag = 1;
        }
    }

    packet = lSzDuel_DrawWindow_Frame_Pipe(packet, global[0xD54], -1, 6, left, top, 8, 3, (s64) 1);
    result = lSzDuel_DrawWindow_Icon_Pipe(packet, (s32) D_002909B8, areaX + 4, areaY + 3,
                           0, 1, 0, 0, 1, 0, -1);
    xCoord = x + 0x1E;
    yResult = y + 1;
    xResult = lSzDuel_DrawWindow_Board_Pipe(result, global[0xD54], xCoord, yResult, 3, 1, -1);
    if (flag != 0) {
        temp = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(xResult, 1, 0x1C, 0, 0x16));
        result = SzMsg_GetInfo(1);
        *(s32 *)(result + 0xC) = 0x2C;
        result = SzMsg_DrawX_Pipe(temp, 1, xCoord + 3, yResult + 2, 0, SzMsg_DrawRect_Pipe);
        SzMsg_Free(1);
    } else {
        temp = SzDuel_GetUnitLevel(2, global[0xD4F] + 1, 0);
        result = SzDuel_DrawWindow_Digit_Pipe(xResult, xCoord + 3, yResult + 2, 2,
                             global[0xD4E] != 0 ? Ta_GetSummonCost() : temp, 0);
    }
    return result;
}

typedef struct Flags_001B22F0 {
    signed char bit0 : 1;
    signed char bit1 : 1;
    signed char bit2 : 1;
    signed char rest : 5;
} Flags_001B22F0;

typedef struct Card_001B22F0 {
    s32 active;
    u8 pad04[0x38];
    u16 id;
    u8 type;
    u8 attribute;
    u8 pad40[4];
    u8 owner;
    u8 state;
    u8 pad46[3];
    u8 count1;
    u8 count2;
    u8 pad4B[0xD];
    Flags_001B22F0 flags;
} Card_001B22F0;

#define MAX_001B22F0(a, b) ((a) > (b) ? (a) : (b))
#define MIN_001B22F0(a, b) ((a) < (b) ? (a) : (b))
#pragma opt_propagation off

/* Draws the info window of `cardData` on board square (column, row) for side `side` at (left, top): name, attribute,
   rank, attack and defence with their field bonus. */
s32 lSzDuel_DrawWindow_CardInfo_Pipe(s32 packet, void *cardData, s32 column, s32 row, s32 side, s32 left, s32 top, s32 drawMode, long frameKind, long highlight) {
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 lSzDuel_DrawWindow_Board_Pipe();
    extern s32 SzDuel_DrawWindow_Digit_Pipe();
    extern s32 SzData_GetRank();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void *);
    extern u8 duelAttrIcons[];
    extern u8 duelIcons[];
    extern u8 D_002901D4[];
    extern u8 D_002901DE[];
    extern u8 D_002901E8[];
    extern u8 D_002901F2[];
    extern u8 D_002901FC[];
    extern u8 D_00290206[];
    extern u8 D_00290210[];
    extern u8 D_0029021A[];
    extern u8 D_00290224[];
    extern u8 D_0029022E[];
    extern u8 D_00290238[];
    extern u8 D_00290242[];
    extern u8 D_0029024C[];
    extern u8 D_002909A4[];
    extern u8 D_002909AE[];
    extern u8 D_002909C2[];
    extern u8 D_002909E0[];
    extern u8 D_002909EA[];
    u8 *globalBase;
    u8 *playerState;
    s32 x;
    s32 cardState;
    s32 cardType;
    s32 attribute;
    s32 cardIndex;
    s32 icon1;
    s32 icon3;
    s32 defenseBase;
    s32 effect;
    u8 *label;
    s32 enabled;
    s32 text2;
    s32 mode;
    f32 scale1;
    f32 scale2;
    f32 scale3;
    s32 y;
    s32 labelX;
    s32 labelY;
    s32 cur;
    s32 typeIcon;
    s32 owner;
    s32 hidden;
    s32 textX1;
    s32 textX2;
    s32 textY2;
    s32 textX3;
    s32 text3;
    s32 width1;
    s32 width2;
    s32 width3;
    s32 amount;
    s32 canUse;
    s32 count;
    s32 attackBase;
    s32 numX2;
    s32 attack;
    s32 defense;
    s32 iconY;
    s32 statX;
    s32 statY;
    s32 numX1;
    s32 numY2;
    s64 color;
    Card_001B22F0 *card;
    s32 iconX;

    globalBase = duelState.b;
    playerState = duelState.b + side * 0x350;
    x = left + 3;
    y = top + 4;
    labelX = x + 0x6C0;
    mode = drawMode;
    labelY = y + 0x720;
    card = cardData;
    cur = lSzDuel_DrawWindow_Frame_Pipe(packet, side, (s32)highlight != 0 ? 7 : -1, (s32)frameKind, left, top, 0x33, 10, 1);
    if (card != NULL && card->active != 0) {
        owner = card->owner;
        cardState = card->state;
        cardType = (s32)card->type >> 5;
        typeIcon = card->type & 0x1F;
        attribute = SzDuel_Kind2Attr(cardType, card->attribute);
        if (cardType == 0) {
            label = duelIcons + typeIcon * 10;
        } else {
            label = duelIcons + (cardType + 0x14) * 10;
        }
        cardIndex = SzData_GetRank(side, card->id);
        icon1 = SzDuel_GetMsgName(card->id);
        if (cardType == 0) {
            typeIcon += 0x25;
        } else {
            typeIcon = cardType + 0x1E;
        }
        hidden = 0;
        icon3 = cardIndex + 0x52;
        if (SzGame_GetMenuNum(0x1E) != 0 && cardState > 0) {
            hidden = lSzDuel_IsUnitHide(card);
        }
        if (hidden != 0) {
            icon1 = 0x1C;
        }
        packet = SzMsg_LoadFont_Pipe(cur, 1, icon1, 0, 0x16);
        if (hidden != 0) {
            typeIcon = 0x1D;
        }
        packet = SzMsg_LoadFont_Pipe(packet, 2, typeIcon, 0, 0x2C);
        if (hidden != 0) {
            icon3 = 0x51;
        }
        packet = SzMsg_LoadFont_Pipe(packet, 3, icon3, 0, 0x42);
        packet = RhText_SetTextureFlush(packet);
        textX1 = x + 2;
        typeIcon = lSzDuel_DrawWindow_Board_Pipe(packet, side, textX1, y, 0x1B, 1, -1);
        width1 = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0xC);
        scale1 = (width1 < 229) ^ 1 ? 228.0f / (f32)width1 : 1.0f;
        packet = SzMsg_DrawRatioX_Pipe(typeIcon, 1, textX1 + 5, y + 2, scale1, 1.0f, 0, SzMsg_DrawRect_Pipe);
        packet = lSzDuel_DrawWindow_Icon_Pipe(packet, label, labelX + 3, labelY + 0x1F, hidden, enabled = !hidden, hidden, 0, 1, 0, -1);
        textY2 = y + 0x1D;
        textX2 = x + 0x1D;
        text2 = lSzDuel_DrawWindow_Board_Pipe(packet, side, textX2, textY2, 0xB, 1, -1);
        width2 = *(s32 *)((u8 *)SzMsg_GetInfo(2) + 0xC);
        scale2 = width2 > 100 ? 100.0f / (f32)width2 : 1.0f;
        packet = SzMsg_DrawRatioX_Pipe(text2, 2, textX2 + 5, textY2 + 2, scale2, 1.0f, 0, SzMsg_DrawRect_Pipe);
        iconX = labelX + 0x90;
        iconY = labelY + 0x1F;
        if (mode == 2) {
            color = 1;
        } else {
            color = mode == 0 ? 2LL : -1LL;
        }
        cur = lSzDuel_DrawWindow_Icon_Pipe(packet, duelAttrIcons + attribute * 10, iconX, iconY, 1, enabled, 1, 0, 1, 0, color);
        if (cardType == 0) {
            if (cardState == 0) {
                packet = lSzDuel_DrawWindow_Emblem_Pipe(cur, x + 0xF1, y + 2, cardIndex, 1, 0);
                textX3 = x + 0x10C;
                text3 = lSzDuel_DrawWindow_Board_Pipe(packet, side, textX3, y, 9, 1, -1);
                width3 = *(s32 *)((u8 *)SzMsg_GetInfo(3) + 0xC);
                scale3 = width3 > 88 ? 88.0f / (f32)width3 : 1.0f;
                cur = SzMsg_DrawRatioX_Pipe(text3, 3, textX3 + 3, y + 2, scale3, 1.0f, 0, SzMsg_DrawRect_Pipe);
                if (globalBase[0xD3C] == owner) {
                    amount = SzDuel_GetDeckCount(owner);
                    count = SzDuel_GetHandCount(owner);
                    if (((Flags_001B22F0 *)(playerState + 0x346))->bit0 != 0 && amount + count > 0) {
                        canUse = 0;
                        if ((amount > 0 && playerState[0x344] > 0) != 0) {
                            if (!(playerState[0x344] & 0x80)) {
                                canUse = 1;
                            }
                        }
                        iconX = labelX + 0x16E;
                        iconY = labelY + 2;
                        cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002909B8, iconX, iconY, 0, 1, 0, 0, 1, 0, (canUse != 0 ? 1LL : -1LL));
                    }
                }
                statX = labelX + 0xF1;
                statY = labelY + 0x1F;
                if (SzDuel_GetUnitLeaderAbility2(card, 4, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002901D4, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 5, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002901DE, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 6, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002901E8, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 7, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002901F2, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 8, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002901FC, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 9, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_00290206, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 10, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_00290210, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 11, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_0029021A, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 12, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_00290224, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 13, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_0029022E, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 14, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_00290238, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 15, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_00290242, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                    statX += 0x19;
                }
                if (SzDuel_GetUnitLeaderAbility2(card, 16, 0) != 0) {
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_0029024C, statX, statY, 0, 1, 0, 0, 1, 0, -1);
                }
            } else if (hidden == 0) {
                attackBase = Ta_GetParamOfs((s32)card, column, row, 1);
                defenseBase = Ta_GetParamOfs((s32)card, column, row, 0);
                attack = attackBase + SzDuel_GetUnitAP2(card, 0);
                defense = defenseBase + SzDuel_GetUnitDP2(card, 0);
                effect = CheckLandAgreement(SzDuel_GetField(column, row), card);
                attack = MIN_001B22F0(MAX_001B22F0(attack, 0), 9999);
                defense = MIN_001B22F0(MAX_001B22F0(defense, 0), 9999);
                if (SzDuel_GetUnitConstEffect2(card, 0) != NULL) {
                    iconX = labelX + 0xAD;
                    iconY = labelY + 0x1C;
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002909EA, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
                }
                iconX = labelX + 0xF2;
                iconY = labelY + 2;
                packet = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002909A4, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
                numX1 = x + 0x10C;
                packet = lSzDuel_DrawWindow_Board_Pipe(packet, side, numX1, y, 9, 1, -1);
                packet = SzDuel_DrawWindow_Digit_Pipe(packet, numX1 + 6, y + 2, 4, attack, 0);
                iconX = labelX + 0xF2;
                iconY = labelY + 0x1F;
                packet = lSzDuel_DrawWindow_Icon_Pipe(packet, D_002909AE, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
                numY2 = y + 0x1D;
                numX2 = x + 0x10C;
                packet = lSzDuel_DrawWindow_Board_Pipe(packet, side, numX2, numY2, 9, 1, -1);
                cur = SzDuel_DrawWindow_Digit_Pipe(packet, numX2 + 6, numY2 + 2, 4, defense, 0);
                if (effect != 0) {
                    iconX = labelX + 0x16E;
                    iconY = labelY + 2;
                    cur = lSzDuel_DrawWindow_Icon_Pipe(cur, duelIcons + (effect + 0xED) * 10, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
                }
            }
            if (hidden == 0 && (GetMoveRange((s32)card, column, row) & 0xF) > 1U) {
                iconX = labelX + 0x18B;
                iconY = labelY + 2;
                cur = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002909E0, iconX, iconY, 0, 1, 0, 0, 1, 0, -1);
            }
        }
        SzMsg_Free(1);
        SzMsg_Free(2);
        SzMsg_Free(3);
        if ((cardType != 0 || cardState != 0) && card->flags.bit2 == 0) {
            amount = card->count1;
            if (amount == 0xFF) {
                count = 0x7FFFFFFF;
            } else {
                canUse = card->count2;
                if (canUse == 0xFF) {
                    count = 0x7FFFFFFF;
                } else {
                    count = (u8)(canUse < amount ? amount : canUse);
                }
            }
            if (count != 0) {
                packet = lSzDuel_DrawWindow_Icon_Pipe(cur, D_002909C2, labelX + 0x16E, labelY + 0x1F, 0, 1, 0, 0, 1, 0, -1);
                y += 0x1D;
                labelX = x + 0x188;
                packet = lSzDuel_DrawWindow_Board_Pipe(packet, side, labelX, y, 1, 1, -1);
                cur = SzDuel_DrawWindow_Digit_Pipe(packet, labelX + 4, y + 2, 1, count, 0);
            }
        }
    }
    return cur;
}

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001B3100;

typedef struct {
    u8 pad[0x44];
    u8 x;
    u8 y;
    u8 pad46[0x11];
    Flags_001B3100 flags;
} Card_001B3100;

typedef struct {
    u8 pad[0x33D];
    u8 x;
    u8 y;
    u8 pad33F[7];
    Flags_001B3100 flags;
    u8 pad347[0x381];
    Card_001B3100 *card;
    Card_001B3100 *other;
    u8 pad6D0[0x66C];
    u8 player;
    u8 padD3D[0x29];
    Flags_001B3100 state;
} State_001B3100;

typedef struct {
    u16 graphic : 10;
    u16 x : 3;
    u16 y : 3;
    u16 text;
} Entry_001B3100;

typedef struct {
    u8 pad[0xC];
    s32 width;
} Text_001B3100;
extern Entry_001B3100 D_00291180[];
extern u8 Player_GameState;
#pragma opt_propagation reset

/* Draws the button guide for side `side` at (left, top): which commands the square under the cursor allows. */
s32 lSzDuel_DrawWindow_CommandGuide_Pipe(s32 packet, s32 side, s64 left, s64 top) {
    extern s32 lSzDuel_DrawWindow_Icon_Pipe();
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern void *SzMsg_GetInfo();
    extern s32 SzDuel_GetMapMovable();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    State_001B3100 *state;
    State_001B3100 *player;
    s32 choice;
    s32 x;
    s32 y;
    s32 renderX;
    s32 count;
    s32 text;
    Entry_001B3100 *entry;
    s32 value;
    s32 otherValue;
    Text_001B3100 *info;
    s32 graphic;
    s32 entryX;
    s32 entryY;
    f32 scale;

    state = (State_001B3100 *)duelState.b;
    player = (State_001B3100 *)(duelState.b + WhoGoesFirst * 0x350);
    x = (s32)left + 4;
    y = (s32)top + 4;
    choice = -1;
    packet = lSzDuel_DrawWindow_Frame_Pipe(packet, side, 2, 3, left, top, 9, 0x12, 1);
    switch (Player_GameState) {
    case 0x18:
        if (state->card != NULL) {
            value = Ta_IsUnitControl(state->card->x, state->card->y);
            if (state->player == value) {
                if (state->card->y == 0) {
                    value = SzDuel_GetDeckCount(state->player);
                    otherValue = SzDuel_GetHandCount(state->player);
                    if (player->flags.bit0 && value + otherValue > 0) {
                        if (state->card->flags.bit0) {
                            choice = 3;
                        } else {
                            choice = 1;
                        }
                    } else if (otherValue != 0) {
                        if (state->card->flags.bit0) {
                            choice = 4;
                        } else {
                            choice = 2;
                        }
                    } else {
                        if (state->card->flags.bit0) {
                            choice = 11;
                        } else {
                            choice = 10;
                        }
                    }
                } else {
                    if (state->card->flags.bit0) {
                        choice = 11;
                    } else {
                        choice = 10;
                    }
                }
            } else {
                value = 0;
                if (state->card->y > 0) {
                    value = Ta_IsUnitHide((s32)state->card, state->player);
                }
                choice = value == 0 ? 11 : 0;
            }
        } else {
            choice = 0;
        }
        break;
    case 0x1D:
        if (state->card->y == 0) {
            choice = 5;
            if (state->other != NULL && state->other != state->card) {
                value = Ta_IsUnitControl(state->other->x, state->other->y);
                if (state->player == value) {
                    choice = 6;
                }
            }
        } else {
            if (state->other != NULL) {
                if (state->other == state->card) {
                    if (state->card->flags.bit4) {
                        choice = 13;
                    } else {
                        choice = 12;
                    }
                } else {
                    value = Ta_IsUnitControl(state->other->x, state->other->y);
                    if (state->player == value) {
                        choice = 14;
                    } else {
                        choice = 15;
                    }
                }
            } else {
                choice = 5;
            }
        }
        break;
    case 0x3E:
        if (SzDuel_GetMapMovable(player->x, player->y) == 0) {
            choice = 7;
        }
        break;
    case 0x43:
        choice = 8;
        break;
    case 0x53:
        choice = 17;
        break;
    case 0x46:
        choice = 9;
        break;
    case 0x29:
    case 0x25:
        choice = 18;
        break;
    case 0x2D:
        if (state->state.bit3) {
            choice = 16;
        } else {
            choice = 17;
        }
        break;
    case 0x30:
        if (SzView_InqRequest(-1, -1) == NULL) {
            choice = 19;
        }
        break;
    case 0x63:
        choice = 20;
        break;
    }
    if (choice < 0) {
        return packet;
    }
    renderX = x + 10;
    entry = D_00291180 + choice * 4;
    count = 0;
    do {
        graphic = entry->graphic;
        entryX = entry->x;
        entryY = entry->y;
        text = entry->text;
        if (graphic < 0x3FF) {
            packet = lSzDuel_DrawWindow_Icon_Pipe(packet, duelIcons + graphic * 10,
                                  renderX + 0x6C0 + entryX, y + 0x720 + entryY,
                                  0, 1, 0, 0, 1, 0, -1);
        }
        if (text < 0xFFFF) {
            packet = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, text, 0, 0x16));
            info = SzMsg_GetInfo(1);
            if (info->width >= 0x2D) {
                scale = 44.0f / (f32)info->width;
            } else {
                scale = 1.0f;
            }
            packet = SzMsg_DrawRatioX_Pipe(packet, 1, renderX + 0x1A, y, scale, 1.0f, 0,
                                  SzMsg_DrawRect_Pipe);
            SzMsg_Free(1);
        }
        count++;
        y += 0x16;
        entry++;
    } while (count < 4);
    return packet;
}

/* Draws the window naming field type `field` at (x, y). */
s32 lSzDuel_DrawWindow_Field_Pipe(s32 packet, s32 field, s32 x, s32 y) {
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    s32 id;
    s32 width;
    s32 result;
    f32 scale;

    scale = 1.0f;
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, field + 0x47, 0, 0x16));
    id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, 2, 3, x, y, 9, 0x12, 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 5, -1, 3, x, y + 0x40, 9, 2, 1);
    width = ((s32 *)SzMsg_GetInfo(1))[3];
    if (width > 0x54) {
        scale = 84.0f / (f32)width;
    }
    result = SzMsg_DrawRatioX_Pipe(id, 1, (x + 0x30) - (s32)((f32)(width >> 1) * scale), y + 0x43,
                           scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    return result;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B3790;

typedef struct {
    u8 pad[4];
    u8 b;
    u8 g;
    u8 r;
    u8 a;
} Source_001B3790;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001B3790;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B3790;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B3790;

typedef struct {
    u64 tag[2];
    Color_001B3790 color;
    Vertex_001B3790 vertex0;
    Vertex_001B3790 vertex1;
    u64 end;
} Box_001B3790;

typedef struct {
    u64 tag[2];
    Color_001B3790 color;
    u64 uv0;
    Vertex_001B3790 vertex0;
    u64 uv1;
    Vertex_001B3790 vertex1;
    u64 test;
    s64 texture0;
    s64 texture1;
    u64 clamp;
} Sprite_001B3790;

typedef struct {
    u8 pad00[0x40];
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;
    u8 pad4C[4];
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    u8 pad5C[0x24];
    s32 roll;
    u8 pad84[0xC];
} View_001B3790;

typedef union {
    __int128 q;
    s32 w[4];
} Params_001B3790;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec_001B3790;

/* Sets a sprite corner's texture coordinates. */
static inline void set_uv_001B3790(UV_001B3790 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}

/* Draws a small 3D board piece of `card` in a window, rendered into a texture. */
s32 lSzDuel_DrawWindow_FieldPiece_Pipe(s32 start, s32 colorIndex, s32 card, s32 x, s32 y, f32 scale) {
    extern Source_001B3790 sideColors[];
    extern Params_001B3790 D_002912D0;
    extern s32 RotY;
    extern s32 RhBase_AssignRenderFrame(s32, s32, s32);
    u8 *state = duelState.b;
    Source_001B3790 *color = &sideColors[colorIndex];
    s32 left;
    s32 top;
    s32 width = 0x60;
    s32 height = 0x40;
    s32 id;
    s32 packet;
    View_001B3790 view;
    Params_001B3790 params;
    Box_001B3790 box __attribute__((aligned(8)));
    Sprite_001B3790 sprite __attribute__((aligned(8)));
    Vec_001B3790 rotation;
    Vec_001B3790 front;

    ((Tag_001B3790 *)box.tag)->flags = 6;
    ((Tag_001B3790 *)box.tag)->count = 3;
    ((Tag_001B3790 *)box.tag)->registers = 0x441;
    ((Tag_001B3790 *)box.tag)->padding = 0;
    left = x + 0x6C0;
    top = y + 0x720;
    box.color.r = color->r;
    box.color.g = color->g;
    box.color.b = color->b;
    box.color.a = 0x80;
    box.color.q = 1.0f;
    box.vertex0.x = (left + 2) << 4;
    box.vertex0.y = (top + 2) << 4;
    box.vertex0.z = duelState.s.depth;
    box.vertex0.fog = 0;
    box.vertex1.x = (left + width - 2) << 4;
    box.vertex1.y = (top + height) << 4;
    box.vertex1.z = duelState.s.depth;
    box.vertex1.fog = 0;
    id = ExSortPrim_Pipe(start, (s32)box.tag, 0, 0);
    if (SzModel_IsModelDisp(card + 0x4A) == 0) {
        return id;
    }
    left += 3;
    top += 3;
    width -= 6;
    height -= 3;
    ((Tag_001B3790 *)sprite.tag)->flags = 0x26;
    ((Tag_001B3790 *)sprite.tag)->count = 5;
    ((Tag_001B3790 *)sprite.tag)->registers = 0x42421;
    ((Tag_001B3790 *)sprite.tag)->padding = 0;
    ((Tag_001B3790 *)sprite.tag)->flags |= 0x800;
    ExAssignAlpha(sprite.tag, 0x44 | ((s64)0x80 << 32));
    sprite.color.r = 0xFF;
    sprite.color.g = 0xFF;
    sprite.color.b = 0xFF;
    sprite.color.a = 0x80;
    sprite.color.q = 1.0f;
    sprite.vertex0.z = *(s32 *)(state + 0xC58);
    sprite.vertex0.fog = 0;
    sprite.vertex1.z = *(s32 *)(state + 0xC58);
    sprite.vertex1.fog = 0;
    RhView_GetCurView(&view);
    if (RhView_PushStack() != 0) {
        params = D_002912D0;
        params.w[1] = RotY;
        RhBase_AssignRenderFrame(0, 0xA, 0x31);
        packet = (s32)RhBase_EnableRenderFrame((void *)id);
        packet = (s32)RhBase_ClearRenderFrame((u8 *)packet, 0);
        view.targetZ = func_001A6C60(view.targetX * view.targetX + view.targetZ * view.targetZ);
        view.targetX = 0.0f;
        RhGeom_NormalizeVector(&view.targetX);
        view.eyeX = -(view.targetX * scale);
        view.eyeY = -(view.targetY * scale) - 25.0f;
        view.eyeZ = -(view.targetZ * scale);
        view.roll = 0;
        RhView_Modify(&view);
        id = RhBase_SetZBufferMode(RhView_SendViewParameters(packet), 1);
        SzModel_GetIntensity(card + 0x4A, &rotation.x);
        front = rotation;
        front.z = 1.0f;
        SzModel_SetIntensity(card + 0x4A, &front.x);
        id = SzModel_DrawWithOutCalc_Pipe(id, card + 0x4A, 0, (s32)&params, 0, 0, 0);
        SzModel_SetIntensity(card + 0x4A, &rotation.x);
        id = RhBase_SetZBufferMode(id, 0);
        RhBase_GetTextureInfoForRender(&sprite.texture0, &sprite.texture1);
        id = RhText_SetTextureFlush((s32)RhBase_DisableRenderFrame((void *)id));
        set_uv_001B3790((UV_001B3790 *)&sprite.uv0, 0, 0);
        set_uv_001B3790((UV_001B3790 *)&sprite.uv1, 0x280 << 4, 0x1C0 << 4);
        sprite.vertex0.x = (left << 4) - 8;
        sprite.vertex0.y = (top << 4) - 8;
        sprite.vertex1.x = ((left + width) << 4) - 8;
        sprite.vertex1.y = ((top + height) << 4) - 8;
        RhView_PopStack();
        RhView_GetCurView(&view);
        RhView_Modify(&view);
        id = ExSortPrim_Pipe(RhView_SendViewParameters(id), (s32)&sprite, 0, 0);
        RhBase_FreeRenderFrame();
        RotY += 0x200;
    }
    return id;
}

/* Draws an icon: lSzDuel_DrawWindow_ExIcon_Pipe without flips, at full alpha. */
s32 lSzDuel_DrawWindow_Icon_Pipe(s32 packet, s32 src, s32 x, s32 y,
                   s32 background, s32 image, s32 border, s32 shrink,
                   s32 bright, s32 rgb, s32 blend) {
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, s32, s32, s32, s32, s32, s32, s32,
                              s64, s64, s64, s64, s64, s64);

    return lSzDuel_DrawWindow_ExIcon_Pipe(packet, src, x, y, background, image, border, shrink,
                  0, 0, (s64) bright, (s64) rgb, (s64) blend, 0x80);
}

typedef struct Tag_001B3CC0 {
    u32 count : 16;
    u32 flags : 16;
    u32 reserved;
    u64 registers;
} Tag_001B3CC0;

typedef struct Color_001B3CC0 {
    u32 r : 8;
    u32 g : 8;
    u32 b : 8;
    u32 a : 8;
    f32 q;
} Color_001B3CC0;

typedef struct UV_001B3CC0 {
    u16 u : 14;
    u16 pad0 : 2;
    u16 v : 14;
    u16 pad1 : 2;
    u32 reserved;
} UV_001B3CC0;

typedef struct XYZ_001B3CC0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} XYZ_001B3CC0;

typedef struct Sprite_001B3CC0 {
    u64 tag[2];
    Color_001B3CC0 color;
    u64 uv0;
    XYZ_001B3CC0 xyz0;
    u64 uv1;
    XYZ_001B3CC0 xyz1;
    u64 texture[4];
} Sprite_001B3CC0;

typedef struct Solid_001B3CC0 {
    u64 tag[2];
    Color_001B3CC0 color;
    XYZ_001B3CC0 xyz0;
    XYZ_001B3CC0 xyz1;
    u64 unused;
} Solid_001B3CC0;

typedef struct State_001B3CC0 {
    u8 pad000[0x6A0];
    void *textures[16];
    u8 pad6E0[0x578];
    s32 depth;
} State_001B3CC0;

extern u8 D_002909F4[];

/* Fills a GIF tag. */
static inline void tag_001B3CC0(Tag_001B3CC0 *tag, s32 count, s32 flags, u64 registers) {
    tag->flags = flags;
    tag->count = count;
    tag->registers = registers;
    tag->reserved = 0;
}

/* Clamps at 0x3FFF. */
static inline s32 upper_001B3CC0(s32 value) {
    if (value < 0x3FFF) {
        return value;
    }
    return 0x3FFF;
}

/* Draws icon `src` at (x, y) with optional background, border, flips, brightness, colour and blending. */
s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32 packet, u16 *src, s32 x, s32 y,
                  s32 background, s32 image, s32 border, s32 shrink,
                  s32 flipX, s32 flipY, s32 bright, u8 *rgb,
                  s32 blend, u8 alpha) {
    Sprite_001B3CC0 sprite __attribute__((aligned(8)));
    Solid_001B3CC0 solid __attribute__((aligned(8)));
    State_001B3CC0 *graphics;
    s32 width;
    s32 height;

    graphics = (State_001B3CC0 *)duelState.b;
    width = Abs(src[3] - src[1]);
    height = Abs(src[4] - src[2]);
    if (shrink != 0) {
        width = (width * 3) >> 2;
        height = (height * 3) >> 2;
    }
    tag_001B3CC0((Tag_001B3CC0 *)sprite.tag, 5, 0x26, 0x42421);
    ((Tag_001B3CC0 *)sprite.tag)->flags |= 0x800;
    ExAssignAlpha(&sprite, 0x8000000044LL);
    sprite.color.r = sprite.color.g = sprite.color.b = SzDuel_WindowIntensity(bright);
    sprite.color.a = alpha;
    sprite.color.q = 1.0f;
    sprite.xyz0.z = graphics->depth;
    sprite.xyz0.fog = 0;
    sprite.xyz1.z = graphics->depth;
    sprite.xyz1.fog = 0;
    tag_001B3CC0((Tag_001B3CC0 *)solid.tag, 3, 6, 0x441);
    solid.color.r = 0x80;
    solid.color.g = 0x80;
    solid.color.b = 0x80;
    solid.color.a = 0x80;
    solid.color.q = 1.0f;
    solid.xyz0.z = graphics->depth;
    solid.xyz0.fog = 0;
    solid.xyz1.z = graphics->depth;
    solid.xyz1.fog = 0;
    if (background != 0) {
        solid.color.r = solid.color.g = solid.color.b = 0;
        solid.xyz0.x = x * 16;
        solid.xyz0.y = y * 16;
        solid.xyz1.x = (x + width) * 16;
        solid.xyz1.y = (y + height) * 16;
        packet = ExSortPrim_Pipe(packet, (s32)&solid, 0, 0);
    }
    if (image != 0) {
        ExAssignTexture(&sprite, graphics->textures[((u8 *)src)[0]], 0);
        if (flipX != 0 && flipY != 0) {
            ((UV_001B3CC0 *)&sprite.uv0)->u = AtLeast0(src[3] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv0)->v = AtLeast0(src[4] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv1)->u = AtLeast0(src[1] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv1)->v = AtLeast0(src[2] * 16 - 8);
        } else if (flipX != 0 && flipY == 0) {
            ((UV_001B3CC0 *)&sprite.uv0)->u = AtLeast0(src[3] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv0)->v = upper_001B3CC0(src[2] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv1)->u = AtLeast0(src[1] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv1)->v = upper_001B3CC0(src[4] * 16 + 8);
        } else if (flipX == 0 && flipY != 0) {
            ((UV_001B3CC0 *)&sprite.uv0)->u = upper_001B3CC0(src[1] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv0)->v = AtLeast0(src[4] * 16 - 8);
            ((UV_001B3CC0 *)&sprite.uv1)->u = upper_001B3CC0(src[3] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv1)->v = AtLeast0(src[2] * 16 - 8);
        } else {
            ((UV_001B3CC0 *)&sprite.uv0)->u = upper_001B3CC0(src[1] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv0)->v = upper_001B3CC0(src[2] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv1)->u = upper_001B3CC0(src[3] * 16 + 8);
            ((UV_001B3CC0 *)&sprite.uv1)->v = upper_001B3CC0(src[4] * 16 + 8);
        }
        sprite.xyz0.x = x * 16;
        sprite.xyz0.y = y * 16;
        sprite.xyz1.x = (x + width) * 16;
        sprite.xyz1.y = (y + height) * 16;
        packet = ExSortPrim_Pipe(packet, (s32)&sprite, 0, 0);
    }
    if (border != 0) {
        packet = lSzDuel_DrawWindow_ExIcon_Pipe(packet, (u16 *)D_002909F4, x, y, 0, 1, 0, shrink,
                              0, 0, bright, NULL, -1, 0x80);
    }
    if (blend >= 0) {
        ExAssignAlpha(&solid, ExGetAlphaVal(blend));
        if (rgb != NULL) {
            solid.color.r = rgb[2];
            solid.color.g = rgb[1];
            solid.color.b = rgb[0];
        } else {
            solid.color.r = solid.color.g = solid.color.b = 0x80;
        }
        solid.color.a = D_00318118 >> 8;
        solid.xyz0.x = x * 16;
        solid.xyz0.y = y * 16;
        solid.xyz1.x = (x + width) * 16;
        solid.xyz1.y = (y + height) * 16;
        packet = ExSortPrim_Pipe(packet, (s32)&solid, 0, 0);
    }
    return packet;
}
extern u16 D_00290864[];
#pragma opt_propagation off

/* Draws a card's rank emblem: `rank` stars in rows of three, small or large, optionally mirrored. */
s32 lSzDuel_DrawWindow_Emblem_Pipe(s32 packet, s32 x, s32 y, s32 rank, s32 small, s32 mirrored) {
    s32 result;

    result = packet;
    if (rank > 0) {
        s32 parts;
        s32 px;
        s32 py;
        s32 width;
        s32 quotient;
        u16 *src;

        parts = small ? 0xC : 0x10;
        if (rank > 0) {
            width = ((rank - 1) % 3) + 1;
        } else {
            width = 0;
        }
        quotient = 0;
        if (rank > 0) {
            quotient = (rank - 1) / 3;
        }
        src = (u16 *)(duelIcons + (quotient + 0xC6) * 10);
        result = func_001B3CC0(packet, src, x + 0x6C0, y + 0x720,
                               0, 1, 0, small, (mirrored != 0) ? 1 : 0, 0, 1, 0, -1, 0x80);
        if (width & 1) {
            px = x + 0x6C0 + ((mirrored != 0) ? 0 : parts);
            result = func_001B3CC0(result, D_00290864, px, y + 0x720,
                                   0, 1, 0, small, 0, 0, 1, 0, -1, 0x80);
        }
        if (width & 2) {
            px = x + 0x6C0 + ((mirrored != 0) ? parts : 0);
            result = func_001B3CC0(result, D_00290864, px, y + 0x720, 0, 1, 0, small, 0, 0, 1, 0, -1, 0x80);
            px = x + 0x6C0 + ((mirrored != 0) ? 0 : parts);
            py = y + 0x720 + parts;
            result = func_001B3CC0(result, D_00290864, px, py, 0, 1, 0, small, 0, 0, 1, 0, -1, 0x80);
        }
    }
    return result;
}

typedef struct Tag_001B4780 {
    u32 count : 16;
    u32 flags : 16;
    u32 reserved;
    u64 registers;
} Tag_001B4780;

typedef struct Color_001B4780 {
    u32 r : 8;
    u32 g : 8;
    u32 b : 8;
    u32 a : 8;
    f32 q;
} Color_001B4780;

typedef struct UV_001B4780 {
    u16 u : 14;
    u16 pad0 : 2;
    u16 v : 14;
    u16 pad1 : 2;
    u32 reserved;
} UV_001B4780;

typedef struct XYZ_001B4780 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} XYZ_001B4780;

typedef struct Sprite_001B4780 {
    u64 tag[2];
    Color_001B4780 color;
    u64 uv0;
    XYZ_001B4780 xyz0;
    u64 uv1;
    XYZ_001B4780 xyz1;
    u64 texture[4];
} Sprite_001B4780;

typedef struct Vertex_001B4780 {
    Color_001B4780 color;
    XYZ_001B4780 xyz;
} Vertex_001B4780;

typedef struct Gradient_001B4780 {
    u64 tag[2];
    Vertex_001B4780 v[4];
    u64 alpha;                      /* 0x50: the alpha word ExAssignAlpha writes and ExSortPrim_Pipe reads (flags 0x214) */
} Gradient_001B4780;

typedef struct Corner_001B4780 {
    u64 uv;
    XYZ_001B4780 xyz;
} Corner_001B4780;

typedef struct Quad_001B4780 {
    u64 tag[2];
    Color_001B4780 color;
    Corner_001B4780 c[4];
    u64 texture[4];
} Quad_001B4780;

typedef struct Texture_001B4780 {
    u8 index;
    u8 reserved;
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
} Texture_001B4780;

typedef struct State_001B4780 {
    u8 pad000[0x6A0];
    void *textures[16];
    u8 pad6E0[0x578];
    s32 depth;
} State_001B4780;

extern Texture_001B4780 duelIcons_2[]; /* original: gSzDuel_Icon */
extern u8 sideColors_2[]; /* original: gSzDuel_aaicolRgba */
extern u8 windowFrameOffsets[]; /* original: aabFrameOfs */
extern u8 windowDecoOffsets[]; /* original: abDecoOfs */

/* Fills a GIF tag. */
static inline void tag_001B4780(Tag_001B4780 *tag, s32 count, s32 flags, u64 registers) {
    tag->flags = flags;
    tag->count = count;
    tag->registers = registers;
    tag->reserved = 0;
}

#pragma opt_propagation reset

/* Draws a window frame at (x, y), cols x rows tiles (negative sizes are in pixels), in `style` and side colour
   `colorIndex`, with corner icons. */
s32 lSzDuel_DrawWindow_Frame_Pipe(s32 packet, s32 colorIndex, s32 icons, s32 style, s32 x, s32 y, s32 cols, s32 rows, s64 bright) {
    Sprite_001B4780 sprite __attribute__((aligned(8)));
    Gradient_001B4780 gradient __attribute__((aligned(8)));
    Quad_001B4780 arrow __attribute__((aligned(8)));
    Quad_001B4780 cursor __attribute__((aligned(8)));
    Quad_001B4780 page __attribute__((aligned(8)));
    State_001B4780 *graphics;
    Texture_001B4780 *parts;
    Texture_001B4780 *part;
    Texture_001B4780 *icon;
    u8 *margin;
    s32 dx;
    s32 x0;
    s32 y0;
    s32 height;
    s32 index;
    s32 ih;
    s32 w;
    s32 width;
    s32 kind;
    s32 shift;
    s32 col;
    s32 dy;
    s32 px;
    s32 py;
    s32 row;
    s32 iw;
    u8 *rgb;
    extern s32 ExSortPrim_Pipe();
    u32 tmp;

    graphics = (State_001B4780 *)duelState.b;
    tmp = style;
    parts = &duelIcons_2[tmp * 9 + 0x3B];
    margin = &windowFrameOffsets[tmp * 4];
    tmp = x + 0x6C0;
    style = y + 0x720;
    if (colorIndex >= 0) {
        rgb = &sideColors_2[colorIndex * 8];
        if (cols >= 0) {
            width = ((parts[2].x1 - parts[2].x0) - margin[1]) + (((parts[0].x1 - parts[0].x0) - margin[0]) + cols * (parts[1].x1 - parts[1].x0));
        } else {
            width = Abs(cols);
        }
        if (rows >= 0) {
            height = ((parts[6].y1 - parts[6].y0) - margin[3]) + (((parts[0].y1 - parts[0].y0) - margin[2]) + rows * (parts[3].y1 - parts[3].y0));
        } else {
            height = Abs(rows);
        }
        height >>= 1;
        x0 = tmp + margin[0];
        y0 = style + margin[2];
        tag_001B4780((Tag_001B4780 *)gradient.tag, 8, 0x14, 0x41414141);
        if (colorIndex >= 0xE) {
            ExAssignAlpha(&gradient, ExGetAlphaVal(0));
        } else if (colorIndex >= 0xC) {
            ExAssignAlpha(&gradient, ExGetAlphaVal(2));
        }
        gradient.v[0].color.r = gradient.v[1].color.r = rgb[2];
        gradient.v[0].color.g = gradient.v[1].color.g = rgb[1];
        gradient.v[0].color.b = gradient.v[1].color.b = rgb[0];
        gradient.v[0].color.a = gradient.v[1].color.a = rgb[3];
        gradient.v[0].color.q = gradient.v[1].color.q = 1.0f;
        gradient.v[2].color.r = gradient.v[3].color.r = rgb[6];
        gradient.v[2].color.g = gradient.v[3].color.g = rgb[5];
        gradient.v[2].color.b = gradient.v[3].color.b = rgb[4];
        gradient.v[2].color.a = gradient.v[3].color.a = rgb[7];
        gradient.v[2].color.q = gradient.v[3].color.q = 1.0f;
        gradient.v[0].xyz.x = x0 * 16;
        gradient.v[0].xyz.y = y0 * 16;
        gradient.v[0].xyz.z = graphics->depth;
        gradient.v[0].xyz.fog = 0;
        gradient.v[1].xyz.x = (x0 + width) * 16;
        gradient.v[1].xyz.y = y0 * 16;
        gradient.v[1].xyz.z = graphics->depth;
        gradient.v[1].xyz.fog = 0;
        gradient.v[2].xyz.x = x0 * 16;
        gradient.v[2].xyz.y = (y0 + height) * 16;
        gradient.v[2].xyz.z = graphics->depth;
        gradient.v[2].xyz.fog = 0;
        gradient.v[3].xyz.x = (x0 + width) * 16;
        gradient.v[3].xyz.y = (y0 + height) * 16;
        gradient.v[3].xyz.z = graphics->depth;
        gradient.v[3].xyz.fog = 0;
        packet = ExSortPrim_Pipe(packet, &gradient, 0, 0);
        gradient.v[0].color.r = gradient.v[1].color.r = rgb[6];
        gradient.v[0].color.g = gradient.v[1].color.g = rgb[5];
        gradient.v[0].color.b = gradient.v[1].color.b = rgb[4];
        gradient.v[0].color.a = gradient.v[1].color.a = rgb[7];
        gradient.v[0].color.q = gradient.v[1].color.q = 1.0f;
        gradient.v[2].color.r = gradient.v[3].color.r = rgb[2];
        gradient.v[2].color.g = gradient.v[3].color.g = rgb[1];
        gradient.v[2].color.b = gradient.v[3].color.b = rgb[0];
        gradient.v[2].color.a = gradient.v[3].color.a = rgb[3];
        gradient.v[2].color.q = gradient.v[3].color.q = 1.0f;
        gradient.v[0].xyz.x = x0 * 16;
        gradient.v[0].xyz.y = (y0 + height) * 16;
        gradient.v[0].xyz.z = graphics->depth;
        gradient.v[0].xyz.fog = 0;
        gradient.v[1].xyz.x = (x0 + width) * 16;
        gradient.v[1].xyz.y = (y0 + height) * 16;
        gradient.v[1].xyz.z = graphics->depth;
        gradient.v[1].xyz.fog = 0;
        gradient.v[2].xyz.x = x0 * 16;
        gradient.v[2].xyz.y = (y0 + height * 2) * 16;
        gradient.v[2].xyz.z = graphics->depth;
        gradient.v[2].xyz.fog = 0;
        gradient.v[3].xyz.x = (x0 + width) * 16;
        gradient.v[3].xyz.y = (y0 + height * 2) * 16;
        gradient.v[3].xyz.z = graphics->depth;
        gradient.v[3].xyz.fog = 0;
        packet = ExSortPrim_Pipe(packet, &gradient, 0, 0);
    }
    tag_001B4780((Tag_001B4780 *)sprite.tag, 5, 0x26, 0x42421);
    ((Tag_001B4780 *)sprite.tag)->flags |= 0x800;
    ExAssignAlpha(&sprite, 0x8000000044LL);
    sprite.color.r = sprite.color.g = sprite.color.b = SzDuel_WindowIntensity(bright);
    sprite.color.a = 0x80;
    sprite.color.q = 1.0f;
    sprite.xyz0.z = graphics->depth;
    sprite.xyz0.fog = 0;
    sprite.xyz1.z = graphics->depth;
    sprite.xyz1.fog = 0;
    if (cols < 0) {
        cols += ((parts[0].x1 - parts[0].x0) - margin[0]) + ((parts[2].x1 - parts[2].x0) - margin[1]);
    }
    if (rows < 0) {
        rows += ((parts[0].y1 - parts[0].y0) - margin[2]) + ((parts[6].y1 - parts[6].y0) - margin[3]);
    }
    dy = 0;
    for (row = 0; row < 3; row++) {
        dx = 0;
        for (col = 0; col < 3; col++) {
            index = row * 3 + col;
            part = &parts[index];
            width = part->x1 - part->x0;
            height = part->y1 - part->y0;
            if (index == 1 || index == 4 || index == 7) {
                if (cols > 0) {
                    width *= cols;
                } else if (cols >= 0) {
                    width = cols;
                } else {
                    width = -cols;
                }
            }
            if ((u32)(index - 3) < 3) {
                if (rows > 0) {
                    height *= rows;
                } else if (rows >= 0) {
                    height = rows;
                } else {
                    height = -rows;
                }
            }
            if (index != 4 && width > 0 && height > 0) {
                ExAssignTexture(&sprite, graphics->textures[part->index], 0);
                ((UV_001B4780 *)&sprite.uv0)->u = part->x0 * 16;
                ((UV_001B4780 *)&sprite.uv0)->v = part->y0 * 16;
                ((UV_001B4780 *)&sprite.uv1)->u = part->x1 * 16;
                ((UV_001B4780 *)&sprite.uv1)->v = part->y1 * 16;
                sprite.xyz0.x = (tmp + dx) * 16 - 8;
                sprite.xyz0.y = (style + dy) * 16 - 8;
                sprite.xyz1.x = (width + (tmp + dx)) * 16 - 8;
                sprite.xyz1.y = (height + (style + dy)) * 16 - 8;
                packet = ExSortPrim_Pipe(packet, &sprite, 0, 0);
            }
            dx += width;
        }
        dy += height;
    }
    if (icons >= 0) {
        do {
            kind = icons & 0xF;
            shift = windowDecoOffsets[kind];
            icon = &duelIcons_2[kind + 0x2F];
            if ((u32)(kind - 3) < 2) {
                tag_001B4780((Tag_001B4780 *)arrow.tag, 9, 0x24, 0x24242421 | ((u64)4 << 32));
                ((Tag_001B4780 *)arrow.tag)->flags |= 0x800;
                ExAssignAlpha(&arrow, 0x8000000044LL);
                ExAssignTexture(&arrow, graphics->textures[icon->index], 0);
                arrow.color.r = 0x80;
                arrow.color.g = 0x80;
                arrow.color.b = 0x80;
                arrow.color.a = 0x80;
                arrow.color.q = 1.0f;
                arrow.c[0].xyz.z = graphics->depth;
                arrow.c[0].xyz.fog = 0;
                arrow.c[1].xyz.z = graphics->depth;
                arrow.c[1].xyz.fog = 0;
                arrow.c[2].xyz.z = graphics->depth;
                arrow.c[2].xyz.fog = 0;
                arrow.c[3].xyz.z = graphics->depth;
                arrow.c[3].xyz.fog = 0;
                ((UV_001B4780 *)&arrow.c[0].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&arrow.c[0].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&arrow.c[1].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&arrow.c[1].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&arrow.c[2].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&arrow.c[2].uv)->v = icon->y1 * 16;
                ((UV_001B4780 *)&arrow.c[3].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&arrow.c[3].uv)->v = icon->y1 * 16;
                ih = icon->y1 - icon->y0;
                iw = icon->x1 - icon->x0;
                px = (tmp + margin[0]) - shift;
                py = style + margin[2];
                arrow.c[0].xyz.x = px * 16 + 8;
                arrow.c[0].xyz.y = (py + iw) * 16 + 8;
                arrow.c[1].xyz.x = px * 16 + 8;
                arrow.c[1].xyz.y = py * 16 + 8;
                arrow.c[2].xyz.x = (px + ih) * 16 + 8;
                arrow.c[2].xyz.y = (py + iw) * 16 + 8;
                arrow.c[3].xyz.x = (px + ih) * 16 + 8;
                arrow.c[3].xyz.y = py * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &arrow, 0, 0);
                px = ((parts[0].x1 - parts[0].x0) - margin[0]) + ((parts[2].x1 - parts[2].x0) - margin[1]);
                w = cols > 0 ? cols * (parts[1].x1 - parts[1].x0) : (cols >= 0 ? cols : -cols);
                px += w;
                px = (px + (tmp + margin[0])) - ((icon->y1 - icon->y0) - shift);
                py = style + margin[2];
                arrow.c[0].xyz.x = (px + ih) * 16 - 0x18;
                arrow.c[0].xyz.y = (py + iw) * 16 + 8;
                arrow.c[1].xyz.x = (px + ih) * 16 - 0x18;
                arrow.c[1].xyz.y = py * 16 + 8;
                arrow.c[2].xyz.x = px * 16 - 0x18;
                arrow.c[2].xyz.y = (py + iw) * 16 + 8;
                arrow.c[3].xyz.x = px * 16 - 0x18;
                arrow.c[3].xyz.y = py * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &arrow, 0, 0);
            } else if (kind == 5) {
                tag_001B4780((Tag_001B4780 *)cursor.tag, 9, 0x24, 0x24242421 | ((u64)4 << 32));
                ((Tag_001B4780 *)cursor.tag)->flags |= 0x800;
                ExAssignAlpha(&cursor, 0x8000000044LL);
                ExAssignTexture(&cursor, graphics->textures[icon->index], 0);
                cursor.color.r = 0x80;
                cursor.color.g = 0x80;
                cursor.color.b = 0x80;
                cursor.color.a = 0x80;
                cursor.color.q = 1.0f;
                cursor.c[0].xyz.z = graphics->depth;
                cursor.c[0].xyz.fog = 0;
                cursor.c[1].xyz.z = graphics->depth;
                cursor.c[1].xyz.fog = 0;
                cursor.c[2].xyz.z = graphics->depth;
                cursor.c[2].xyz.fog = 0;
                cursor.c[3].xyz.z = graphics->depth;
                cursor.c[3].xyz.fog = 0;
                ((UV_001B4780 *)&cursor.c[0].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&cursor.c[0].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&cursor.c[1].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&cursor.c[1].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&cursor.c[2].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&cursor.c[2].uv)->v = icon->y1 * 16;
                ((UV_001B4780 *)&cursor.c[3].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&cursor.c[3].uv)->v = icon->y1 * 16;
                ih = icon->y1 - icon->y0;
                iw = icon->x1 - icon->x0;
                px = ((parts[0].x1 - parts[0].x0) - margin[0]) + ((parts[2].x1 - parts[2].x0) - margin[1]);
                if (cols > 0) {
                    w = cols * (parts[1].x1 - parts[1].x0);
                } else if (cols >= 0) {
                    w = cols;
                } else {
                    w = -cols;
                }
                px += w;
                w = ih - shift;
                px = (px + (tmp + margin[0])) - w;
                (void)w; /* keeps ih - shift in its own temp (no fold into px) */
                py = style + margin[2];
                cursor.c[0].xyz.x = (px + ih) * 16 - 0x18;
                cursor.c[0].xyz.y = (py + iw) * 16 + 8;
                cursor.c[1].xyz.x = (px + ih) * 16 - 0x18;
                cursor.c[1].xyz.y = py * 16 + 8;
                cursor.c[2].xyz.x = px * 16 - 0x18;
                cursor.c[2].xyz.y = (py + iw) * 16 + 8;
                cursor.c[3].xyz.x = px * 16 - 0x18;
                cursor.c[3].xyz.y = py * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &cursor, 0, 0);
                icon = &duelIcons_2[0x38];
                ((UV_001B4780 *)&cursor.c[0].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&cursor.c[0].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&cursor.c[1].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&cursor.c[1].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&cursor.c[2].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&cursor.c[2].uv)->v = icon->y1 * 16;
                ((UV_001B4780 *)&cursor.c[3].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&cursor.c[3].uv)->v = icon->y1 * 16;
                ih = icon->y1 - icon->y0;
                iw = icon->x1 - icon->x0;
                py += 8;
                cursor.c[0].xyz.x = (px + ih) * 16 - 0x18;
                cursor.c[0].xyz.y = (py + iw) * 16 + 8;
                cursor.c[1].xyz.x = (px + ih) * 16 - 0x18;
                cursor.c[1].xyz.y = py * 16 + 8;
                cursor.c[2].xyz.x = px * 16 - 0x18;
                cursor.c[2].xyz.y = (py + iw) * 16 + 8;
                cursor.c[3].xyz.x = px * 16 - 0x18;
                cursor.c[3].xyz.y = py * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &cursor, 0, 0);
            } else if (kind == 6) {
                tag_001B4780((Tag_001B4780 *)page.tag, 9, 0x24, 0x24242421 | ((u64)4 << 32));
                ((Tag_001B4780 *)page.tag)->flags |= 0x800;
                ExAssignAlpha(&page, 0x8000000044LL);
                ExAssignTexture(&page, graphics->textures[icon->index], 0);
                page.color.r = 0x80;
                page.color.g = 0x80;
                page.color.b = 0x80;
                page.color.a = 0x80;
                page.color.q = 1.0f;
                page.c[0].xyz.z = graphics->depth;
                page.c[0].xyz.fog = 0;
                page.c[1].xyz.z = graphics->depth;
                page.c[1].xyz.fog = 0;
                page.c[2].xyz.z = graphics->depth;
                page.c[2].xyz.fog = 0;
                page.c[3].xyz.z = graphics->depth;
                page.c[3].xyz.fog = 0;
                ((UV_001B4780 *)&page.c[0].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&page.c[0].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&page.c[1].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&page.c[1].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&page.c[2].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&page.c[2].uv)->v = icon->y1 * 16;
                ((UV_001B4780 *)&page.c[3].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&page.c[3].uv)->v = icon->y1 * 16;
                ih = icon->y1 - icon->y0;
                iw = icon->x1 - icon->x0;
                px = (tmp + margin[0]) - shift;
                py = style + margin[2];
                page.c[0].xyz.x = px * 16 + 8;
                page.c[0].xyz.y = (py + iw) * 16 + 8;
                page.c[1].xyz.x = px * 16 + 8;
                page.c[1].xyz.y = py * 16 + 8;
                page.c[2].xyz.x = (px + ih) * 16 + 8;
                page.c[2].xyz.y = (py + iw) * 16 + 8;
                page.c[3].xyz.x = (px + ih) * 16 + 8;
                page.c[3].xyz.y = py * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &page, 0, 0);
                icon = &duelIcons_2[0x39];
                ((UV_001B4780 *)&page.c[0].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&page.c[0].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&page.c[1].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&page.c[1].uv)->v = icon->y0 * 16;
                ((UV_001B4780 *)&page.c[2].uv)->u = icon->x0 * 16;
                ((UV_001B4780 *)&page.c[2].uv)->v = icon->y1 * 16;
                ((UV_001B4780 *)&page.c[3].uv)->u = icon->x1 * 16;
                ((UV_001B4780 *)&page.c[3].uv)->v = icon->y1 * 16;
                ih = icon->y1 - icon->y0;
                iw = icon->x1 - icon->x0;
                py += 8;
                px -= ih - shift;
                page.c[0].xyz.x = (px + ih) * 16 + 8;
                page.c[0].xyz.y = py * 16 + 8;
                page.c[1].xyz.x = (px + ih) * 16 + 8;
                page.c[1].xyz.y = (py + iw) * 16 + 8;
                page.c[2].xyz.x = px * 16 + 8;
                page.c[2].xyz.y = py * 16 + 8;
                page.c[3].xyz.x = px * 16 + 8;
                page.c[3].xyz.y = (py + iw) * 16 + 8;
                packet = ExSortPrim_Pipe(packet, &page, 0, 0);
            } else {
                px = ((parts[0].x1 - parts[0].x0) - margin[0]) + ((parts[2].x1 - parts[2].x0) - margin[1]);
                w = cols > 0 ? cols * (parts[1].x1 - parts[1].x0) : (cols >= 0 ? cols : -cols);
                px += w;
                px >>= 1;
                px -= (icon->x1 - icon->x0) >> 1;
                px = px + (tmp + margin[0]);
                py = (style + margin[2]) - shift;
                ExAssignTexture(&sprite, graphics->textures[icon->index], 0);
                ((UV_001B4780 *)&sprite.uv0)->u = icon->x0 * 16 + 8;
                ((UV_001B4780 *)&sprite.uv0)->v = icon->y0 * 16 + 8;
                ((UV_001B4780 *)&sprite.uv1)->u = icon->x1 * 16 + 8;
                ((UV_001B4780 *)&sprite.uv1)->v = icon->y1 * 16 + 8;
                iw = icon->x1 - icon->x0;
                ih = icon->y1 - icon->y0;
                sprite.xyz0.x = px * 16;
                sprite.xyz0.y = py * 16;
                sprite.xyz1.x = (px + iw) * 16;
                sprite.xyz1.y = (py + ih) * 16;
                packet = ExSortPrim_Pipe(packet, &sprite, 0, 0);
            }
            icons >>= 4;
        } while (icons != 0);
    }
    return packet;
}

typedef struct {
    u8 texture;
    u8 padding;
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
} Texture_001B62F0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B62F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 padding : 8;
} XYZ_001B62F0;

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Header_001B62F0;

typedef struct {
    u64 header[2];
    u8 r, g, b, a;
    f32 q;
    u64 uv0;
    XYZ_001B62F0 xyz0;
    u64 uv1;
    XYZ_001B62F0 xyz1;
    u64 primitive;
    u64 tex0;
    u64 tex1;
    u64 clamp;
} Packet_001B62F0;

/* Draws the plain window background at (x, y), `columns` x `rows` tiles. */
s32 lSzDuel_DrawWindow_Base_Pipe(s32 packet, s32 x, s32 y, s32 columns, s32 rows) {
    extern u8 D_002907E2[];
    extern void *D_00317B30[];
    Texture_001B62F0 *texture;
    s32 width;
    s32 xOffset;
    s32 column;
    u16 y0;
    u16 y1;
    s32 originY;
    s32 originX;
    s32 height;
    s32 yOffset;
    s32 row;
    Packet_001B62F0 sprite __attribute__((aligned(8)));
    UV_001B62F0 *uv0;
    UV_001B62F0 *uv1;

    originY = y + 0x720;
    texture = (Texture_001B62F0 *)D_002907E2;
    ((Header_001B62F0 *)sprite.header)->flags = 0x26;
    ((Header_001B62F0 *)sprite.header)->count = 5;
    ((Header_001B62F0 *)sprite.header)->registers = 0x42421;
    ((Header_001B62F0 *)sprite.header)->padding = 0;
    originX = x + 0x6C0;
    ((Header_001B62F0 *)sprite.header)->flags |= 0x800;
    ExAssignAlpha(&sprite, 0x8000000044ULL);
    sprite.r = sprite.g = sprite.b = 0x80;
    sprite.a = 0x80;
    sprite.q = 1.0f;
    sprite.xyz0.z = duelState.s.depth;
    sprite.xyz0.padding = 0;
    sprite.xyz1.z = duelState.s.depth;
    sprite.xyz1.padding = 0;
    ExAssignTexture(&sprite, D_00317B30[texture->texture], 0);
    uv0 = (UV_001B62F0 *)&sprite.uv0;
    uv1 = (UV_001B62F0 *)&sprite.uv1;
    uv0->u = texture->left * 16;
    yOffset = 0;
    row = 0;
    uv0->v = texture->top * 16;
    uv1->u = texture->right * 16;
    uv1->v = texture->bottom * 16;
    width = texture->right - texture->left;
    height = texture->bottom - texture->top;
    if (row < rows) {
        do {
            xOffset = 0;
            column = 0;
            if (column < columns) {
                u16 rowY = originY + yOffset;
                y0 = rowY * 16 - 8;
                y1 = (height + rowY) * 16 - 8;
                do {
                    u16 columnX = originX + xOffset;
                    sprite.xyz0.x = columnX * 16 - 8;
                    sprite.xyz0.y = y0;
                    sprite.xyz1.x = (width + columnX) * 16 - 8;
                    sprite.xyz1.y = y1;
                    packet = ExSortPrim_Pipe(packet, (s32)&sprite, 0, 0);
                    column++;
                    xOffset += width;
                } while (column < columns);
            }
            yOffset += height;
            row++;
        } while (row < rows);
    }
    return packet;
}

/* Draws a window board in style 0 (lSzDuel_DrawWindow_ExBoard_Pipe). */
s32 lSzDuel_DrawWindow_Board_Pipe(s32 packet, s32 colorIndex, s32 x, s32 y, s32 w,
                   s32 h, s32 shadow) {
    return lSzDuel_DrawWindow_ExBoard_Pipe(packet, colorIndex, x, y, w, h, shadow, 0);
}

typedef struct {
    u8 texture;
    u8 padding;
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
} Slice_001B65F0;

typedef struct {
    u8 pad[4];
    u8 b;
    u8 g;
    u8 r;
    u8 a;
} Color_001B65F0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B65F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} XYZ_001B65F0;

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Header_001B65F0;

typedef struct {
    u64 header[2];
    u8 r, g, b, a;
    f32 q;
    u64 uv0;
    XYZ_001B65F0 xyz0;
    u64 uv1;
    XYZ_001B65F0 xyz1;
    u64 primitive;
    u64 tex0;
    u64 tex1;
    u64 clamp;
} Sprite_001B65F0;

typedef struct {
    u64 header[2];
    u8 r, g, b, a;
    f32 q;
    XYZ_001B65F0 xyz0;
    XYZ_001B65F0 xyz1;
    u64 end;
} Box_001B65F0;

/* Draws a coloured window board at (x, y), w x h tiles, with an optional shadow, in `style`. */
s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32 packet, s32 colorIndex, s32 x, s32 y, s32 w, s32 h, s32 shadow, s32 style) {
    extern Slice_001B65F0 duelIcons_3[];
    extern Color_001B65F0 sideColors_3[];
    u8 *state = duelState.b;
    Slice_001B65F0 *slices = &duelIcons_3[style * 9 + 0x8C];
    Color_001B65F0 *color;
    s32 originX;
    s32 originY;
    s32 width;
    s32 height;
    s32 xOffset;
    s32 yOffset;
    s32 column;
    Slice_001B65F0 *slice;
    s32 row;
    s32 i;
    u16 y0;
    Sprite_001B65F0 sprite __attribute__((aligned(8)));
    Box_001B65F0 box __attribute__((aligned(8)));

    if (colorIndex < 0) {
        colorIndex = 2;
    }
    color = &sideColors_3[colorIndex];
    ((Header_001B65F0 *)sprite.header)->flags = 0x26;
    ((Header_001B65F0 *)sprite.header)->count = 5;
    ((Header_001B65F0 *)sprite.header)->registers = 0x42421;
    ((Header_001B65F0 *)sprite.header)->padding = 0;
    ((Header_001B65F0 *)sprite.header)->flags |= 0x800;
    ExAssignAlpha(sprite.header, ExGetAlphaVal(0));
    originX = x + 0x6C0;
    originY = y + 0x720;
    sprite.r = color->r;
    sprite.g = color->g;
    sprite.b = color->b;
    sprite.a = color->a;
    sprite.q = 1.0f;
    sprite.xyz0.z = *(s32 *)(state + 0xC58);
    sprite.xyz0.fog = 0;
    sprite.xyz1.z = *(s32 *)(state + 0xC58);
    sprite.xyz1.fog = 0;
    if (shadow >= 0) {
        color = &sideColors_3[shadow];
        if (w >= 0) {
            width = (slices[2].right - slices[2].left) +
                    ((slices[0].right - slices[0].left) + w * (slices[1].right - slices[1].left));
        } else {
            width = (w >= 0) ? w : -w;
        }
        if (h >= 0) {
            height = (slices[6].bottom - slices[6].top) +
                     ((slices[0].bottom - slices[0].top) + h * (slices[3].bottom - slices[3].top));
        } else {
            height = (h >= 0) ? h : -h;
        }
        ((Header_001B65F0 *)box.header)->flags = 6;
        ((Header_001B65F0 *)box.header)->count = 3;
        ((Header_001B65F0 *)box.header)->registers = 0x441;
        ((Header_001B65F0 *)box.header)->padding = 0;
        if (shadow >= 0xE) {
            ExAssignAlpha(box.header, ExGetAlphaVal(0));
        } else if (shadow >= 0xC) {
            ExAssignAlpha(box.header, ExGetAlphaVal(2));
        }
        box.r = color->r;
        box.g = color->g;
        box.b = color->b;
        box.a = color->a;
        box.q = 1.0f;
        box.xyz0.z = *(s32 *)(state + 0xC58);
        box.xyz0.fog = 0;
        box.xyz1.z = *(s32 *)(state + 0xC58);
        box.xyz1.fog = 0;
        box.xyz0.x = originX << 4;
        box.xyz0.y = originY << 4;
        box.xyz1.x = (originX + width) << 4;
        box.xyz1.y = (originY + height) << 4;
        packet = ExSortPrim_Pipe(packet, (s32)&box, 0, 0);
    }
    if (w < 0) {
        w += (slices[0].right - slices[0].left) + (slices[2].right - slices[2].left);
    }
    if (h < 0) {
        h += (slices[0].bottom - slices[0].top) + (slices[6].bottom - slices[6].top);
    }
    yOffset = 0;
    for (row = 0; row < 3; row++) {
        xOffset = 0;
        y0 = (u16)(originY + yOffset) * 16 - 8;
        for (column = 0; column < 3; column++) {
            i = row * 3 + column;
            slice = &slices[i];
            width = slice->right - slice->left;
            height = slice->bottom - slice->top;
            if (i == 1 || i == 4 || i == 7) {
                if (w > 0) {
                    width *= w;
                } else {
                    width = (w >= 0) ? w : -w;
                }
            }
            if ((u32)(i - 3) < 3) {
                if (h > 0) {
                    height *= h;
                } else {
                    height = (h >= 0) ? h : -h;
                }
            }
            if (i != 4 && width > 0 && height > 0) {
                u16 columnX;

                ExAssignTexture(&sprite, *(void **)(state + 0x6A0 + slice->texture * 4), 0);
                ((UV_001B65F0 *)&sprite.uv0)->u = slice->left * 16;
                columnX = originX + xOffset;
                ((UV_001B65F0 *)&sprite.uv0)->v = slice->top * 16;
                ((UV_001B65F0 *)&sprite.uv1)->u = slice->right * 16;
                ((UV_001B65F0 *)&sprite.uv1)->v = slice->bottom * 16;
                sprite.xyz0.x = columnX * 16 - 8;
                sprite.xyz0.y = y0;
                sprite.xyz1.x = (width + columnX) * 16 - 8;
                sprite.xyz1.y = (height + (u16)(originY + yOffset)) * 16 - 8;
                packet = ExSortPrim_Pipe(packet, (s32)&sprite, 0, 0);
            }
            xOffset += width;
        }
        yOffset += height;
    }
    return packet;
}

/* Draws `number` as `digits` digits at (x, y) (SzDuel_DrawWindow_ExDigit_Pipe without padding). */
s32 SzDuel_DrawWindow_Digit_Pipe(s32 packet, s32 x, s32 y, s32 digits, s32 number, s32 narrow) {
    return SzDuel_DrawWindow_ExDigit_Pipe(packet, x, y, digits, number, narrow, 0, 0);
}

typedef struct Result_001B6CA0 {
    s32 unk0;
    s32 unk4;
} Result_001B6CA0;

/* Draws `number` right-aligned in `digits` digits at (x, y); 0x7FFFFFFF draws dashes, `zeroPad` keeps leading
   zeros. */
s32 SzDuel_DrawWindow_ExDigit_Pipe(s32 packet, s32 x, s32 y, s32 digits, s32 number, s32 narrow, s32 zeroPad, s32 arg7) {
    extern s32 SzMsg_GetInfo();
    extern s32 SzMsg_DrawX_Pipe();
    Result_001B6CA0 *info;
    s32 stride;
    s32 digit;

    info = (Result_001B6CA0 *) SzMsg_GetInfo(0);
    stride = 0x14 - (narrow ? 4 : 0);
    {
        s32 power = 1;

        if (number == 0x7FFFFFFF) {
            digit = 0;
            info->unk4 = 0x108;
            if (0 < digits) {
                do {
                    packet = SzMsg_DrawX_Pipe(packet, 0, x + (stride * (digits - digit - 1)), y, arg7, SzMsg_DrawRect_Pipe);
                    digit += 1;
                } while (digit < digits);
            }
            return packet;
        }
        digit = 0;
        if (0 < digits) {
            do {
                info->unk4 = (((number / power) % 10) * 0x16);
                packet = SzMsg_DrawX_Pipe(packet, 0, x + (stride * (digits - digit - 1)), y, arg7, SzMsg_DrawRect_Pipe);
                power *= 10;
                digit += 1;
            } while ((zeroPad != 0 || number >= power) && digit < digits);
        }
        if (digit < digits) {
            if (number < 0) {
                info->unk4 = 0xF2;
                packet = SzMsg_DrawX_Pipe(packet, 0, x + (stride * (digits - digit - 1)), y, arg7, SzMsg_DrawRect_Pipe);
            }
        }
    }
    return packet;
}

/* Draws `number` as text in the window font at (x, y). */
s32 SzDuel_DrawWindow_FontDigit_Pipe(s32 packet, s32 x, s32 y, s32 font,
                   s32 flags, s32 width, s32 number) {
    s8 text[16];
    s32 padded;
    s32 power;
    s32 i;

    power = 1;
    padded = 0;
    if (flags & 0x20) {
        padded = 1;
    }
    for (i = 0; i < width; i++) {
        text[i] = ' ';
    }
    for (i = 0; i < width;) {
        text[width - i - 1] = (number / power) % 10 + '0';
        power *= 10;
        i++;
        if (!padded && number < power) {
            break;
        }
    }
    return SzDuel_DrawWindow_Font_Pipe(packet, x, y, font, flags, width, text, 0);
}

typedef struct {
    u8 texture;
    u8 padding;
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
} Glyph_001B6F70;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B6F70;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} XYZ_001B6F70;

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Header_001B6F70;

typedef struct {
    u64 uv;
    XYZ_001B6F70 xyz;
} Corner_001B6F70;

typedef struct {
    u64 header[2];
    u8 r, g, b, a;
    f32 q;
    Corner_001B6F70 corners[4];
    u64 extra[4];
} Sprite_001B6F70;

static s32 lSzDuel_GetFontIndex(s8 character);

/* Draws `count` characters of `text` in window font `font` at (x, y), in `color` (or white). */
s32 SzDuel_DrawWindow_Font_Pipe(s32 packet, s32 x, s32 y, s32 font, s32 flags, s32 count, s8 *text, u8 *color) {
    extern u8 windowFontSizes[];
    extern u8 D_002BE951[];
    extern Glyph_001B6F70 windowFontGlyphs[];
    extern u8 icolRgba[];
    u8 *state;
    s32 width;
    s32 lineHeight;
    s32 originX;
    s32 cursorX;
    s32 cursorY;
    s32 proportional;
    s32 centered;
    s32 italic;
    s32 additive;
    s32 subtractive;
    s32 i;
    s64 blend;
    Sprite_001B6F70 sprite __attribute__((aligned(8)));

    originX = x + 0x6C0;
    state = duelState.b;
    width = windowFontSizes[font * 2];
    cursorY = y + 0x720;
    lineHeight = D_002BE951[font * 2];
    proportional = 0;
    centered = 0;
    italic = 0;
    additive = 0;
    subtractive = 0;
    if (flags & 1) {
        proportional = 1;
    }
    if (flags & 2) {
        centered = 1;
    }
    if (flags & 4) {
        italic = 1;
    }
    if (flags & 8) {
        additive = 1;
    }
    if (flags & 0x10) {
        subtractive = 1;
    }
    if (color == NULL) {
        color = icolRgba;
    }
    ((Header_001B6F70 *)sprite.header)->flags = 0x24;
    ((Header_001B6F70 *)sprite.header)->count = 9;
    ((Header_001B6F70 *)sprite.header)->registers = 0x424242421ULL;
    ((Header_001B6F70 *)sprite.header)->padding = 0;
    ((Header_001B6F70 *)sprite.header)->flags |= 0x800;
    if (additive) {
        blend = ExGetAlphaVal(2);
    } else if (subtractive) {
        blend = ExGetAlphaVal(3);
    } else {
        blend = ExGetAlphaVal(0);
    }
    ExAssignAlpha(sprite.header, blend);
    sprite.r = color[2];
    sprite.g = color[1];
    sprite.b = color[0];
    sprite.a = color[3];
    sprite.q = 1.0f;
    sprite.corners[0].xyz.z = *(s32 *)(state + 0xC58);
    sprite.corners[0].xyz.fog = 0;
    sprite.corners[1].xyz.z = *(s32 *)(state + 0xC58);
    sprite.corners[1].xyz.fog = 0;
    sprite.corners[2].xyz.z = *(s32 *)(state + 0xC58);
    sprite.corners[2].xyz.fog = 0;
    sprite.corners[3].xyz.z = *(s32 *)(state + 0xC58);
    sprite.corners[3].xyz.fog = 0;
    if (centered) {
        s32 maxWidth = 0;
        s32 lineWidth = 0;

        for (i = 0; i < count; i++) {
            s8 *character = text + i;
            s32 glyph = lSzDuel_GetFontIndex(*character);
            Glyph_001B6F70 *entry;

            if (glyph < 0) {
                if (*character == '\n') {
                    if (maxWidth < lineWidth) {
                        maxWidth = lineWidth;
                    }
                    lineWidth = 0;
                } else {
                    lineWidth += proportional ? (width >> 1) : width;
                }
            } else {
                entry = &windowFontGlyphs[glyph + font * 37];
                if (proportional) {
                    lineWidth += entry->right - entry->left;
                } else {
                    lineWidth += width;
                }
            }
        }
        if (maxWidth < lineWidth) {
            maxWidth = lineWidth;
        }
        originX -= maxWidth >> 1;
    }
    cursorX = originX;
    for (i = 0; i < count; i++) {
        s8 *character = text + i;
        s32 glyph = lSzDuel_GetFontIndex(*character);
        s32 offset = 0;
        s32 shear = 0;
        Glyph_001B6F70 *entry;
        s32 glyphWidth;
        s32 glyphHeight;
        u16 top;
        u16 left;
        u16 right;

        if (glyph < 0) {
            if (*character == '\n') {
                cursorX = originX;
                cursorY += lineHeight;
            } else {
                cursorX += proportional ? (width >> 1) : width;
            }
        } else {
            entry = &windowFontGlyphs[glyph + font * 37];
            ExAssignTexture(&sprite, *(void **)(state + 0x6A0 + entry->texture * 4), 0);
            ((UV_001B6F70 *)&sprite.corners[0].uv)->u = entry->left * 16 + 8;
            ((UV_001B6F70 *)&sprite.corners[0].uv)->v = entry->top * 16 + 8;
            ((UV_001B6F70 *)&sprite.corners[1].uv)->u = entry->right * 16 + 8;
            ((UV_001B6F70 *)&sprite.corners[1].uv)->v = entry->top * 16 + 8;
            ((UV_001B6F70 *)&sprite.corners[2].uv)->u = entry->left * 16 + 8;
            ((UV_001B6F70 *)&sprite.corners[2].uv)->v = entry->bottom * 16 + 8;
            ((UV_001B6F70 *)&sprite.corners[3].uv)->u = entry->right * 16 + 8;
            ((UV_001B6F70 *)&sprite.corners[3].uv)->v = entry->bottom * 16 + 8;
            glyphWidth = entry->right - entry->left;
            glyphHeight = entry->bottom - entry->top;
            if (!proportional) {
                offset = (width - glyphWidth) * 8;
            }
            if (italic) {
                shear = (width * 16) / 6;
            }
            top = cursorY * 16;
            left = (cursorX << 4) + offset;
            right = offset + (cursorX + glyphWidth) * 16;
            sprite.corners[0].xyz.x = shear + left;
            sprite.corners[0].xyz.y = top;
            sprite.corners[1].xyz.x = shear + right;
            sprite.corners[1].xyz.y = top;
            sprite.corners[2].xyz.x = left;
            sprite.corners[2].xyz.y = (cursorY + glyphHeight) * 16;
            sprite.corners[3].xyz.x = right;
            sprite.corners[3].xyz.y = (cursorY + glyphHeight) * 16;
            packet = ExSortPrim_Pipe(packet, (s32)&sprite, 0, 0);
            cursorX += proportional ? glyphWidth : width;
        }
    }
    return packet;
}

/* The glyph index of a character in the window font (A-Z, 0-9, ?), or -1. */
static s32 lSzDuel_GetFontIndex(s8 character) {
    s32 result = -1;

    if (character >= 'A' && character <= 'Z') {
        result = character - 'A';
    } else if (character >= 'a' && character <= 'z') {
        result = character - 'a';
    } else if (character >= '0' && character <= '9') {
        result = character - '0' + 26;
    } else if (character == '?') {
        result = 36;
    }
    return result;
}

typedef struct Glyph_001B76E0 {
    u16 unk0;
    u16 left;
    u16 unk4;
    u16 right;
    u16 unk8;
} Glyph_001B76E0;

extern u8 windowFontSizes[]; /* original: gSzDuel_abFontSize */
extern u8 D_002BE951[];
extern Glyph_001B76E0 windowFontGlyphs[]; /* original: gSzDuel_Font */

/* Measures `count` characters of `text` in window font `font`: the width and height through
   `outWidth`/`outHeight`. */
void lSzDuel_GetFontSize(s32 font, s32 flags, s32 count, s8 *text, s32 *outWidth, s32 *outHeight) {
    s32 width;
    s32 lineHeight;
    s32 proportional;
    s32 maxWidth;
    s32 lineWidth;
    s32 height;
    s32 i;
    s32 halfWidth;
    s32 glyphBase;
    s8 *character;
    s32 glyph;
    Glyph_001B76E0 *entry;

    width = windowFontSizes[font * 2];
    lineHeight = D_002BE951[font * 2];
    proportional = 0;
    maxWidth = 0;
    lineWidth = 0;
    height = 0;
    if (flags & 1) {
        proportional = 1;
    }
    for (i = 0; i < count; i++) {
        halfWidth = width >> 1;
        glyphBase = font * 37;
        character = text + i;
        glyph = lSzDuel_GetFontIndex(*character);
        if (glyph < 0) {
            if (*character == '\n') {
                if (maxWidth < lineWidth) {
                    maxWidth = lineWidth;
                }
                height += lineHeight;
                lineWidth = 0;
            } else {
                lineWidth += proportional ? halfWidth : width;
            }
        } else {
            entry = &windowFontGlyphs[glyph + glyphBase];
            if (proportional) {
                lineWidth += entry->right - entry->left;
            } else {
                lineWidth += width;
            }
        }
    }
    if (maxWidth < lineWidth) {
        maxWidth = lineWidth;
    }
    height += lineHeight;
    if (outWidth != 0) {
        *outWidth = maxWidth;
    }
    if (outHeight != 0) {
        *outHeight = height;
    }
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B7820;

typedef struct {
    u8 texture;
    u8 padding;
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
} Texture_001B7820;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B7820;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B7820;

typedef struct {
    u64 uv;
    Vertex_001B7820 xyz;
} Corner_001B7820;

typedef struct {
    u64 tag[2];
    u8 r, g, b, a;
    f32 q;
    Corner_001B7820 corners[4];
    u64 extra[4];
} Packet_001B7820;

typedef struct {
    f32 v[4][4];
} Quad_001B7820;

typedef struct {
    s32 v[4];
} Rotation_001B7820;

typedef struct {
    f32 m[4][4];
} Matrix_001B7820;

typedef struct {
    u8 pad000[0x6A0];
    void *textures[16];
    u8 pad6E0[0x578];
    s32 depth;
} State_001B7820;

/* Draws the DualShock 2 controller picture at (x, y), turned towards the current side. */
s32 lSzDuel_DrawWindow_DualShock2_Pipe(s32 packet, s32 x, s32 y, s32 alpha) {
    extern Quad_001B7820 D_002912E0;
    extern Rotation_001B7820 D_00291320;
    extern u8 D_0029080A[];
    extern void RhGeom_MulMatrixVectorArray(void *, s32, void *, s32);
    State_001B7820 *state;
    Texture_001B7820 *texture;
    s32 originX;
    s32 originY;
    u8 *player;
    s32 base;
    s32 halfWidth;
    s32 halfHeight;
    Quad_001B7820 corners;
    Rotation_001B7820 rotation;
    Matrix_001B7820 matrix;
    Packet_001B7820 sprite __attribute__((aligned(8)));

    state = (State_001B7820 *)duelState.b;
    player = duelState.b + WhoGoesFirst * 0x350;
    texture = (Texture_001B7820 *)D_0029080A;
    originX = x + 0x6C0;
    originY = y + 0x720;
    halfWidth = (texture->right - texture->left) >> 1;
    halfHeight = (texture->bottom - texture->top) >> 1;
    corners = D_002912E0;
    base = WhoGoesFirst ? 0xC000 : 0x4000;
    corners.v[0][0] = -(f32)halfWidth;
    corners.v[0][1] = -(f32)halfHeight;
    corners.v[1][0] = (f32)halfWidth;
    corners.v[1][1] = -(f32)halfHeight;
    corners.v[2][0] = -(f32)halfWidth;
    corners.v[2][1] = (f32)halfHeight;
    corners.v[3][0] = (f32)halfWidth;
    corners.v[3][1] = (f32)halfHeight;
    rotation = D_00291320;
    rotation.v[2] = -(*(s32 *)(player + 0x1D4) - base);
    ((Tag_001B7820 *)sprite.tag)->flags = 0x24;
    ((Tag_001B7820 *)sprite.tag)->count = 9;
    ((Tag_001B7820 *)sprite.tag)->registers = 0x424242421ULL;
    ((Tag_001B7820 *)sprite.tag)->padding = 0;
    ((Tag_001B7820 *)sprite.tag)->flags |= 0x800;
    ExAssignAlpha(&sprite, 0x8000000044ULL);
    sprite.r = 0x80;
    sprite.g = 0x80;
    sprite.b = 0x80;
    sprite.a = alpha;
    sprite.q = 1.0f;
    ExAssignTexture(&sprite, state->textures[texture->texture], 0);
    ((UV_001B7820 *)&sprite.corners[0].uv)->u = texture->left * 16;
    ((UV_001B7820 *)&sprite.corners[0].uv)->v = texture->top * 16;
    ((UV_001B7820 *)&sprite.corners[1].uv)->u = texture->right * 16;
    ((UV_001B7820 *)&sprite.corners[1].uv)->v = texture->top * 16;
    ((UV_001B7820 *)&sprite.corners[2].uv)->u = texture->left * 16;
    ((UV_001B7820 *)&sprite.corners[2].uv)->v = texture->bottom * 16;
    ((UV_001B7820 *)&sprite.corners[3].uv)->u = texture->right * 16;
    ((UV_001B7820 *)&sprite.corners[3].uv)->v = texture->bottom * 16;
    RhGeom_GetRotXYZMatrix(&matrix, &rotation);
    RhGeom_PushMatrix((s32)&matrix);
    RhGeom_MulMatrixVectorArray((void *)SCRATCHPAD_ADDR, 0, &corners, 4);
    RhGeom_PopMatrix();
    sprite.corners[0].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[0]) - 8;
    sprite.corners[0].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[1]) - 8;
    sprite.corners[0].xyz.z = state->depth;
    sprite.corners[0].xyz.fog = 0;
    sprite.corners[1].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[4]) - 8;
    sprite.corners[1].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[5]) - 8;
    sprite.corners[1].xyz.z = state->depth;
    sprite.corners[1].xyz.fog = 0;
    sprite.corners[2].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[8]) - 8;
    sprite.corners[2].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[9]) - 8;
    sprite.corners[2].xyz.z = state->depth;
    sprite.corners[2].xyz.fog = 0;
    sprite.corners[3].xyz.x = (originX << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[12]) - 8;
    sprite.corners[3].xyz.y = (originY << 4) + (s32)(16.0f * ((f32 *)SCRATCHPAD_ADDR)[13]) - 8;
    sprite.corners[3].xyz.z = state->depth;
    sprite.corners[3].xyz.fog = 0;
    packet = RhBase_SetZBufferMode(packet, 0);
    packet = ExSortPrim_Pipe(packet, (s32)&sprite, 0, 0);
    return RhBase_SetZBufferMode(packet, 1);
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B7D60;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001B7D60;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B7D60;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B7D60;

typedef struct {
    u64 tag[2];
    Color_001B7D60 color;
    u64 uv0;
    Vertex_001B7D60 vertex0;
    u64 uv1;
    Vertex_001B7D60 vertex1;
    u64 test;
    u64 texture0;
    u64 texture1;
    u64 clamp;
} Packet_001B7D60;

/* Sets a sprite corner's texture coordinates. */
static inline void set_uv_001B7D60(UV_001B7D60 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}

/* Draws item picture `item` at (left, top), w x h, at depth `depth`. */
s32 lSzDuel_DrawWindow_PicItem_Pipe(s32 cursor, s32 item, s32 left, s32 top, s32 w, s32 h,
                  s64 depth) {
    extern s32 SzText_InitClutManage();
    u8 *state = duelState.b;
    s32 x = left + 0x6C0;
    s32 y = top + 0x720;
    void **image;
    s32 address;
    Packet_001B7D60 packet __attribute__((aligned(8)));

    image = SzText_GetReadyItem(1, item);
    if (image == NULL) {
        return cursor;
    }
    if (**(s32 **)image == 0x324852) {
        address = *(s32 *)(state + 0xC7C);
        address += SzText_InitClutManage(address, 1);
        cursor = SzText_Load_Pipe(cursor, (s32)*image, address, 0);
        cursor = RhText_SetTextureFlush(cursor);
        ((Tag_001B7D60 *)packet.tag)->flags = 0x26;
        ((Tag_001B7D60 *)packet.tag)->count = 5;
        ((Tag_001B7D60 *)packet.tag)->registers = 0x42421;
        ((Tag_001B7D60 *)packet.tag)->padding = 0;
        ((Tag_001B7D60 *)packet.tag)->flags |= 0x800;
        ExAssignTexture(packet.tag, *image, 0);
        packet.color.r = 0x80;
        packet.color.g = 0x80;
        packet.color.b = 0x80;
        packet.color.a = 0x80;
        packet.color.q = 1.0f;
        set_uv_001B7D60((UV_001B7D60 *)&packet.uv0, 8, 8);
        set_uv_001B7D60((UV_001B7D60 *)&packet.uv1, 0x808, 0x808);
        packet.vertex0.x = x << 4;
        packet.vertex0.y = y << 4;
        packet.vertex0.z = depth;
        packet.vertex0.fog = 0;
        packet.vertex1.x = (x + w) << 4;
        packet.vertex1.y = (y + h) << 4;
        packet.vertex1.z = depth;
        packet.vertex1.fog = 0;
        cursor = ExSortPrim_Pipe(cursor, (s32)packet.tag, 0, 0);
    }
    return cursor;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B7F90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001B7F90;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001B7F90;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B7F90;

typedef struct {
    u64 tag[2];
    Color_001B7F90 color;
    u64 uv0;
    Vertex_001B7F90 vertex0;
    u64 uv1;
    Vertex_001B7F90 vertex1;
    u64 test;
    u64 texture0;
    u64 texture1;
    u64 clamp;
} Packet_001B7F90;

/* Sets a sprite corner's texture coordinates. */
static inline void set_uv_001B7F90(UV_001B7F90 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}

/* Draws duelist portrait `picture` at (left, top), w x h, at depth `depth`, bright or dimmed. */
s32 lSzDuel_DrawWindow_PicMini_Pipe(s32 cursor, s32 picture, s32 left, s32 top, s32 w, s32 h,
                  s64 depth, s32 bright) {
    extern s32 SzText_InitClutManage();
    u8 *state = duelState.b;
    s32 x = left + 0x6C0;
    s32 y = top + 0x720;
    void **image;
    s32 address;
    u8 color;
    Packet_001B7F90 packet __attribute__((aligned(8)));

    image = SzText_GetReadyItem(2, picture);
    if (image == NULL) {
        return cursor;
    }
    if (**(s32 **)image == 0x324852) {
        address = *(s32 *)(state + 0xC7C);
        address += SzText_InitClutManage(address, 1);
        cursor = SzText_Load_Pipe(cursor, (s32)*image, address, 0);
        cursor = RhText_SetTextureFlush(cursor);
        ((Tag_001B7F90 *)packet.tag)->flags = 0x26;
        ((Tag_001B7F90 *)packet.tag)->count = 5;
        ((Tag_001B7F90 *)packet.tag)->registers = 0x42421;
        ((Tag_001B7F90 *)packet.tag)->padding = 0;
        ((Tag_001B7F90 *)packet.tag)->flags |= 0x800;
        ExAssignTexture(packet.tag, *image, 0);
        color = bright ? 0x80 : 0x30;
        packet.color.r = packet.color.g = packet.color.b = color;
        packet.color.a = 0x80;
        packet.color.q = 1.0f;
        set_uv_001B7F90((UV_001B7F90 *)&packet.uv0, 8, 8);
        set_uv_001B7F90((UV_001B7F90 *)&packet.uv1, 0x288, 0x208);
        packet.vertex0.x = x << 4;
        packet.vertex0.y = y << 4;
        packet.vertex0.z = depth;
        packet.vertex0.fog = 0;
        packet.vertex1.x = (x + w) << 4;
        packet.vertex1.y = (y + h) << 4;
        packet.vertex1.z = depth;
        packet.vertex1.fog = 0;
        cursor = ExSortPrim_Pipe(cursor, (s32)packet.tag, 0, 0);
    }
    return cursor;
}

/* Draws the fade over the screen while two cards join. */
void SzDuel_DrawJoinFade(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawJoinFade_Pipe(RhBase_GetVifPacketArea()));
}

/* Draws the join fade, if one is running. */
s32 SzDuel_DrawJoinFade_Pipe(s32 packet) {
    u8 *state = duelState.b;

    if (ScreenFadeAmount == 0) {
        return packet;
    }
    lSzDuel_Draw_Fade_Pipe(packet, 0, 0, 0x280, 0x1C0, state[0xD3A]);
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001B8260;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001B8260;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001B8260;

typedef struct {
    u64 tag[2];
    Color_001B8260 color;
    Vertex_001B8260 vertices[2];
} Packet_001B8260;

/* Draws a black rectangle at (left, top), w x h, with alpha `alpha`. */
s32 lSzDuel_Draw_Fade_Pipe(s32 cursor, s32 left, s32 top, s32 w, s32 h, s32 alpha) {
    s32 x;
    s32 y;
    Packet_001B8260 packet;

    ((Tag_001B8260 *) packet.tag)->flags = 6;
    ((Tag_001B8260 *) packet.tag)->count = 3;
    ((Tag_001B8260 *) packet.tag)->registers = 0x441;
    x = left + 0x6C0;
    y = top + 0x720;
    ((Tag_001B8260 *) packet.tag)->padding = 0;
    ExAssignAlpha(packet.tag, ExGetAlphaVal(2));
    packet.color.r = 0xFF;
    packet.color.g = 0xFF;
    packet.color.b = 0xFF;
    packet.color.a = alpha;
    packet.color.q = 1.0f;
    packet.vertices[0].x = x << 4;
    packet.vertices[0].y = y << 4;
    packet.vertices[0].z = 0xFFFFFD;
    packet.vertices[0].fog = 0;
    packet.vertices[1].x = (x + w) << 4;
    packet.vertices[1].y = (y + h) << 4;
    packet.vertices[1].z = 0xFFFFFD;
    packet.vertices[1].fog = 0;
    cursor = RhBase_SetZBufferMode(cursor, 0);
    cursor = ExSortPrim_Pipe(cursor, (s32) &packet, 0, 0);
    return RhBase_SetZBufferMode(cursor, 1);
}

/* Draws the two cards being joined (fusion or equip). */
void SzDuel_DrawJoinCard(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawJoinCard_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct Flags_001B83F0 {
    s8 unused : 4;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
} Flags_001B83F0;

typedef struct Draw_001B83F0 {
    u8 pad00[0x43];
    u8 alpha;
    u8 pad44[0x3D];
    Flags_001B83F0 flags;
    u8 pad82[0xE];
} Draw_001B83F0;

/* Draws the two cards being joined, on top of the fade. */
s32 SzDuel_DrawJoinCard_Pipe(s32 packet) {
    extern void SzDuel_ClearDrawCard();
    extern s32 CurrentlySelectedUnit;
    u8 *state = duelState.b;
    Draw_001B83F0 draw;

    if (CurrentlySelectedUnit == 0) {
        return packet;
    }
    if (*(s32 *)(state + 0x6CC) == 0) {
        return packet;
    }
    if (state[0xD3B] == 0) {
        return packet;
    }
    SzDuel_ClearDrawCard(&draw);
    draw.flags.colored = 0;
    draw.alpha = state[0xD3B];
    packet = SzDuel_StartCardSession_Pipe(packet);
    SzDuel_SetCardDefPrioZ(0xFFFFFE);
    SzDuel_GetCardNodeOnScreen(&draw, 0, -150.0f, 0.0f);
    packet = SzDuel_DrawCard_Pipe(SzDuel_SetupCard2_Pipe(packet, *(s32 *)(state + 0x6C8), &draw), (s32)&draw);
    SzDuel_GetCardNodeOnScreen(&draw, 0, 150.0f, 0.0f);
    packet = SzDuel_DrawCard_Pipe(SzDuel_SetupCard2_Pipe(packet, *(s32 *)(state + 0x6CC), &draw), (s32)&draw);
    return SzDuel_FinishCardSession_Pipe(packet);
}
